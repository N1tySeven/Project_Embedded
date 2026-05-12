#include "mfrc522.h"
#include "../spi/spi.h"
#include "../utils/delay.h"

#define MFRC522_CS_LOW()   PORTB &= ~(1 << PB2)
#define MFRC522_CS_HIGH()  PORTB |= (1 << PB2)

#define CommandReg      0x01
#define CommIEnReg      0x02
#define CommIrqReg      0x04
#define ErrorReg        0x06
#define Status2Reg      0x08
#define FIFODataReg     0x09
#define FIFOLevelReg    0x0A
#define ControlReg      0x0C
#define BitFramingReg   0x0D
#define ModeReg         0x11
#define TxControlReg    0x14
#define TxASKReg        0x15
#define TModeReg        0x2A
#define TPrescalerReg   0x2B
#define TReloadRegL     0x2D
#define TReloadRegH     0x2C
#define VersionReg      0x37

#define PCD_IDLE        0x00
#define PCD_TRANSCEIVE  0x0C

static void mfrc522_write(uint8_t addr, uint8_t val)
{
    MFRC522_CS_LOW();

    spi_transfer((addr << 1) & 0x7E);
    spi_transfer(val);

    MFRC522_CS_HIGH();
}

static uint8_t mfrc522_read(uint8_t addr)
{
    uint8_t val;

    MFRC522_CS_LOW();

    spi_transfer(((addr << 1) & 0x7E) | 0x80);
    val = spi_transfer(0x00);

    MFRC522_CS_HIGH();

    return val;
}

static void antenna_on(void)
{
    uint8_t temp = mfrc522_read(TxControlReg);

    if(!(temp & 0x03))
    {
        mfrc522_write(TxControlReg, temp | 0x03);
    }
}

void mfrc522_init(void)
{
    DDRB |= (1 << PB2);
    DDRC |= (1 << PC5); // Moved RST from PB1 to PC5
    
    // Deselect RFID by default
    PORTB |= (1 << PB2);

    // Hard Reset (RST pin LOW then HIGH)
    PORTC &= ~(1 << PC5);
    delay_ms(50);
    PORTC |= (1 << PC5);
    delay_ms(50);

    spi_init();

    // Soft Reset Command
    mfrc522_write(CommandReg, 0x0F);
    delay_ms(50);

    mfrc522_write(TModeReg, 0x8D);
    mfrc522_write(TPrescalerReg, 0x3E);
    mfrc522_write(TReloadRegL, 30);
    mfrc522_write(TReloadRegH, 0);

    mfrc522_write(TxASKReg, 0x40);
    mfrc522_write(ModeReg, 0x3D);

    antenna_on();
}

static uint8_t mfrc522_to_card(uint8_t command,
                               uint8_t *sendData,
                               uint8_t sendLen,
                               uint8_t *backData,
                               uint16_t *backLen)
{
    uint8_t status = 1;
    uint8_t irqEn = 0x00;
    uint8_t waitIRq = 0x00;
    uint8_t n;
    uint16_t i;

    if(command == PCD_TRANSCEIVE)
    {
        irqEn = 0x77;
        waitIRq = 0x30;
    }

    mfrc522_write(CommIEnReg, irqEn | 0x80);
    mfrc522_write(CommIrqReg, 0x7F);
    mfrc522_write(FIFOLevelReg, 0x80);

    mfrc522_write(CommandReg, PCD_IDLE);

    for(i = 0; i < sendLen; i++)
    {
        mfrc522_write(FIFODataReg, sendData[i]);
    }

    mfrc522_write(CommandReg, command);

    if(command == PCD_TRANSCEIVE)
    {
        uint8_t temp = mfrc522_read(BitFramingReg);
        mfrc522_write(BitFramingReg, temp | 0x80);
    }

    i = 2000;

    do
    {
        n = mfrc522_read(CommIrqReg);
        i--;
    }
    while((i != 0) && !(n & 0x01) && !(n & waitIRq));

    uint8_t temp = mfrc522_read(BitFramingReg);
    mfrc522_write(BitFramingReg, temp & (~0x80));

    if(i != 0)
    {
        if(!(mfrc522_read(ErrorReg) & 0x1B))
        {
            status = 0;

            if(n & irqEn & 0x01)
            {
                status = 1;
            }

            if(command == PCD_TRANSCEIVE)
            {
                n = mfrc522_read(FIFOLevelReg);

                *backLen = n;

                for(i = 0; i < n; i++)
                {
                    backData[i] = mfrc522_read(FIFODataReg);
                }
            }
        }
    }

    return status;
}

uint8_t mfrc522_request(uint8_t reqMode, uint8_t *TagType)
{
    uint8_t status;
    uint16_t backBits;

    TagType[0] = reqMode;

    mfrc522_write(BitFramingReg, 0x07);

    status = mfrc522_to_card(
        PCD_TRANSCEIVE,
        TagType,
        1,
        TagType,
        &backBits
    );

    return status;
}

uint8_t mfrc522_anticoll(uint8_t *serNum)
{
    uint8_t status;
    uint16_t unLen;

    serNum[0] = PICC_ANTICOLL;
    serNum[1] = 0x20;

    mfrc522_write(BitFramingReg, 0x00);

    status = mfrc522_to_card(
        PCD_TRANSCEIVE,
        serNum,
        2,
        serNum,
        &unLen
    );

    return status;
}

uint8_t mfrc522_get_version(void)
{
    return mfrc522_read(VersionReg);
}