#include "ff.h"
#include "diskio.h"
#include "../sdcard/sdcard.h"

extern volatile uint32_t ms_counting;

/* MMC/SD command (SPI mode) */
#define CMD0	(0)			/* GO_IDLE_STATE */
#define CMD1	(1)			/* SEND_OP_COND (MMC) */
#define ACMD41	(0x80+41)	/* SEND_OP_COND (SDC) */
#define CMD8	(8)			/* SEND_IF_COND */
#define CMD9	(9)			/* SEND_CSD */
#define CMD10	(10)		/* SEND_CID */
#define CMD12	(12)		/* STOP_TRANSMISSION */
#define ACMD13	(0x80+13)	/* SD_STATUS (SDC) */
#define CMD16	(16)		/* SET_BLOCKLEN */
#define CMD17	(17)		/* READ_SINGLE_BLOCK */
#define CMD18	(18)		/* READ_MULTIPLE_BLOCK */
#define CMD23	(23)		/* SET_BLOCK_COUNT (MMC) */
#define ACMD23	(0x80+23)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(24)		/* WRITE_BLOCK */
#define CMD25	(25)		/* WRITE_MULTIPLE_BLOCK */
#define CMD32	(32)		/* ERASE_ER_BLK_START */
#define CMD33	(33)		/* ERASE_ER_BLK_END */
#define CMD38	(38)		/* ERASE */
#define CMD55	(55)		/* APP_CMD */
#define CMD58	(58)		/* READ_OCR */

/* Card type flags (CardType) */
#define CT_MMC		0x01		/* MMC ver 3 */
#define CT_SD1		0x02		/* SD ver 1 */
#define CT_SD2		0x04		/* SD ver 2 */
#define CT_SDC		(CT_SD1|CT_SD2)	/* SD */
#define CT_BLOCK	0x08		/* Block addressing */

static volatile DSTATUS Stat = STA_NOINIT;	/* Physical drive status */
static BYTE CardType;			/* Card type flags */

// Internal functions
static uint32_t get_time_ms() {
    return ms_counting;
}

static BYTE xchg_spi (BYTE dat)
{
    return sd_spi_transfer(dat);
}

static void rcvr_spi_m (BYTE *dst)
{
    *dst = sd_spi_transfer(0xFF);
}

static int wait_ready (void)
{
    BYTE d;
    uint32_t t = get_time_ms();
    do {
        d = xchg_spi(0xFF);
    } while (d != 0xFF && get_time_ms() - t < 500);

    return (d == 0xFF) ? 1 : 0;
}

static void deselect (void)
{
    sdcard_deselect();
    xchg_spi(0xFF); // Dummy clock
}

static int select (void)
{
    sdcard_select();
    if (wait_ready()) return 1;
    deselect();
    return 0;
}

static int rcvr_datablock (
    BYTE *buff,			/* Data buffer to store received data */
    UINT btr			/* Byte count (must be multiple of 4) */
)
{
    BYTE token;
    uint32_t t = get_time_ms();
    do {							/* Wait for data packet in timeout of 200ms */
        token = xchg_spi(0xFF);
    } while ((token == 0xFF) && get_time_ms() - t < 200);

    if(token != 0xFE) return 0;		/* If not valid data token, return with error */

    do {							/* Receive the data block into buffer */
        rcvr_spi_m(buff++);
        rcvr_spi_m(buff++);
    } while (btr -= 2);
    xchg_spi(0xFF);					/* Discard CRC */
    xchg_spi(0xFF);

    return 1;						/* Return with success */
}

#if FF_FS_READONLY == 0
static int xmit_datablock (
    const BYTE *buff,	/* 512 byte data block to be transmitted */
    BYTE token			/* Data/Stop token */
)
{
    BYTE resp;
    UINT wc;

    if (!wait_ready()) return 0;

    xchg_spi(token);					/* Xmit data token */
    if (token != 0xFD) {	/* Is data token */
        wc = 512;
        do {							/* Xmit the 512 byte data block to MMC */
            xchg_spi(*buff++);
            xchg_spi(*buff++);
        } while (wc -= 2);
        xchg_spi(0xFF);					/* CRC (Dummy) */
        xchg_spi(0xFF);
        resp = xchg_spi(0xFF);			/* Receive data response */
        if ((resp & 0x1F) != 0x05)		/* If not accepted, return with error */
            return 0;
    }

    return 1;
}
#endif


static BYTE send_cmd (
    BYTE cmd,		/* Command byte */
    DWORD arg		/* Argument */
)
{
    BYTE n, res;

    if (cmd & 0x80) {	/* ACMD<n> is the command sequense of CMD55-CMD<n> */
        cmd &= 0x7F;
        res = send_cmd(CMD55, 0);
        if (res > 1) return res;
    }

    /* Select the card and wait for ready except to stop multiple block read */
    if (cmd != CMD12) {
        deselect();
        if (!select()) return 0xFF;
    }

    /* Send command packet */
    xchg_spi(0x40 | cmd);				/* Start + Command index */
    xchg_spi((BYTE)(arg >> 24));		/* Argument[31..24] */
    xchg_spi((BYTE)(arg >> 16));		/* Argument[23..16] */
    xchg_spi((BYTE)(arg >> 8));			/* Argument[15..8] */
    xchg_spi((BYTE)arg);				/* Argument[7..0] */
    n = 0x01;							/* Dummy CRC + Stop */
    if (cmd == CMD0) n = 0x95;			/* Valid CRC for CMD0(0) + Stop */
    if (cmd == CMD8) n = 0x87;			/* Valid CRC for CMD8(0x1AA) Stop */
    xchg_spi(n);

    /* Receive command response */
    if (cmd == CMD12) xchg_spi(0xFF);	/* Skip a stuff byte when stop reading */
    n = 10;								/* Wait for a valid response in timeout of 10 attempts */
    do
        res = xchg_spi(0xFF);
    while ((res & 0x80) && --n);

    return res;			/* Return with the response value */
}


DSTATUS disk_status (BYTE pdrv)
{
    if (pdrv) return STA_NOINIT;
    return Stat;
}

DSTATUS disk_initialize (BYTE pdrv)
{
    BYTE n, cmd, ty, ocr[4];

    if (pdrv) return STA_NOINIT;

    for (n = 10; n; n--) xchg_spi(0xFF);	/* 80 dummy clocks */

    ty = 0;
    if (send_cmd(CMD0, 0) == 1) {			/* Enter Idle state */
        uint32_t t = get_time_ms();
        if (send_cmd(CMD8, 0x1AA) == 1) {	/* SDv2? */
            for (n = 0; n < 4; n++) ocr[n] = xchg_spi(0xFF);		/* Get trailing return value of R7 resp */
            if (ocr[2] == 0x01 && ocr[3] == 0xAA) {				/* The card can work at vdd range of 2.7-3.6V */
                while (get_time_ms() - t < 1000 && send_cmd(ACMD41, 1UL << 30));	/* Wait for leaving idle state (ACMD41 with HCS bit) */
                if (get_time_ms() - t < 1000 && send_cmd(CMD58, 0) == 0) {		/* Check CCS bit in the OCR */
                    for (n = 0; n < 4; n++) ocr[n] = xchg_spi(0xFF);
                    ty = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;
                }
            }
        } else {							/* SDv1 or MMCv3 */
            if (send_cmd(ACMD41, 0) <= 1) 	{
                ty = CT_SD1; cmd = ACMD41;	/* SDv1 */
            } else {
                ty = CT_MMC; cmd = CMD1;	/* MMCv3 */
            }
            while (get_time_ms() - t < 1000 && send_cmd(cmd, 0));			/* Wait for leaving idle state */
            if (get_time_ms() - t >= 1000 || send_cmd(CMD16, 512) != 0)	/* Set R/W block length to 512 */
                ty = 0;
        }
    }
    CardType = ty;
    deselect();

    if (ty) {			/* Initialization succeded */
        Stat &= ~STA_NOINIT;		/* Clear STA_NOINIT */
    } else {			/* Initialization failed */
        Stat |= STA_NOINIT;
    }

    return Stat;
}

DRESULT disk_read (BYTE pdrv, BYTE *buff, LBA_t sector, UINT count)
{
    if (pdrv || !count) return RES_PARERR;
    if (Stat & STA_NOINIT) return RES_NOTRDY;

    if (!(CardType & CT_BLOCK)) sector *= 512;	/* Convert to byte address if needed */

    if (count == 1) {	/* Single block read */
        if ((send_cmd(CMD17, sector) == 0)	/* READ_SINGLE_BLOCK */
            && rcvr_datablock(buff, 512)) {
            count = 0;
        }
    }
    else {				/* Multiple block read */
        if (send_cmd(CMD18, sector) == 0) {	/* READ_MULTIPLE_BLOCK */
            do {
                if (!rcvr_datablock(buff, 512)) break;
                buff += 512;
            } while (--count);
            send_cmd(CMD12, 0);				/* STOP_TRANSMISSION */
        }
    }
    deselect();

    return count ? RES_ERROR : RES_OK;
}

#if FF_FS_READONLY == 0
DRESULT disk_write (BYTE pdrv, const BYTE *buff, LBA_t sector, UINT count)
{
    if (pdrv || !count) return RES_PARERR;
    if (Stat & STA_NOINIT) return RES_NOTRDY;
    if (Stat & STA_PROTECT) return RES_WRPRT;

    if (!(CardType & CT_BLOCK)) sector *= 512;	/* Convert to byte address if needed */

    if (count == 1) {	/* Single block write */
        if ((send_cmd(CMD24, sector) == 0)	/* WRITE_BLOCK */
            && xmit_datablock(buff, 0xFE)) {
            count = 0;
        }
    }
    else {				/* Multiple block write */
        if (CardType & CT_SDC) send_cmd(ACMD23, count);
        if (send_cmd(CMD25, sector) == 0) {	/* WRITE_MULTIPLE_BLOCK */
            do {
                if (!xmit_datablock(buff, 0xFC)) break;
                buff += 512;
            } while (--count);
            if (!xmit_datablock(0, 0xFD)) count = 1;	/* STOP_TRAN token */
        }
    }
    deselect();

    return count ? RES_ERROR : RES_OK;
}
#endif

DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void *buff)
{
    DRESULT res;
    BYTE n, csd[16];
    DWORD csize;

    if (pdrv) return RES_PARERR;
    if (Stat & STA_NOINIT) return RES_NOTRDY;

    res = RES_ERROR;
    switch (cmd) {
    case CTRL_SYNC :		/* Make sure that no pending write process */
        if (select()) res = RES_OK;
        break;

    case GET_SECTOR_COUNT :	/* Get number of sectors on the disk (DWORD) */
        if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {
            if ((csd[0] >> 6) == 1) {	/* SDC ver 2.00 */
                csize = csd[9] + ((WORD)csd[8] << 8) + ((DWORD)(csd[7] & 63) << 16) + 1;
                *(DWORD*)buff = csize << 10;
            } else {					/* SDC ver 1.XX or MMC */
                n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
                csize = (csd[8] >> 6) + ((WORD)csd[7] << 2) + ((WORD)(csd[6] & 3) << 10) + 1;
                *(DWORD*)buff = csize << (n - 9);
            }
            res = RES_OK;
        }
        break;

    case GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (DWORD) */
        *(DWORD*)buff = 128;
        res = RES_OK;
        break;

    default:
        res = RES_PARERR;
    }


    deselect();

    return res;
}

/*---------------------------------------------------------*/
/* User Provided RTC Function for FatFs module             */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called from     */
/* FatFs module. Any valid time must be returned even if   */
/* the system does not support an RTC.                     */

DWORD get_fattime (void)
{
    /* Return a fixed timestamp since there is no RTC hardware */
    /* Year: 2026, Month: 5, Day: 10, Hour: 0, Min: 0, Sec: 0 */
    return    ((DWORD)(2026 - 1980) << 25)  /* Year 2026 */
            | ((DWORD)5 << 21)              /* Month 5 */
            | ((DWORD)10 << 16)             /* Mday 10 */
            | ((DWORD)0 << 11)              /* Hour 0 */
            | ((DWORD)0 << 5)               /* Min 0 */
            | ((DWORD)0 >> 1);              /* Sec 0 */
}
