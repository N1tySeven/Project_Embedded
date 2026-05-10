#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c keypad/keypad.c lcd/lcd.c utils/delay.c rfid/mfrc522.c spi/spi.c sdcard/sdcard.c fatfs/diskio.c fatfs/ff.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/keypad/keypad.o ${OBJECTDIR}/lcd/lcd.o ${OBJECTDIR}/utils/delay.o ${OBJECTDIR}/rfid/mfrc522.o ${OBJECTDIR}/spi/spi.o ${OBJECTDIR}/sdcard/sdcard.o ${OBJECTDIR}/fatfs/diskio.o ${OBJECTDIR}/fatfs/ff.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/keypad/keypad.o.d ${OBJECTDIR}/lcd/lcd.o.d ${OBJECTDIR}/utils/delay.o.d ${OBJECTDIR}/rfid/mfrc522.o.d ${OBJECTDIR}/spi/spi.o.d ${OBJECTDIR}/sdcard/sdcard.o.d ${OBJECTDIR}/fatfs/diskio.o.d ${OBJECTDIR}/fatfs/ff.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/keypad/keypad.o ${OBJECTDIR}/lcd/lcd.o ${OBJECTDIR}/utils/delay.o ${OBJECTDIR}/rfid/mfrc522.o ${OBJECTDIR}/spi/spi.o ${OBJECTDIR}/sdcard/sdcard.o ${OBJECTDIR}/fatfs/diskio.o ${OBJECTDIR}/fatfs/ff.o

# Source Files
SOURCEFILES=main.c keypad/keypad.c lcd/lcd.c utils/delay.c rfid/mfrc522.c spi/spi.c sdcard/sdcard.c fatfs/diskio.c fatfs/ff.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
Device=ATmega328P
ProjectDir="C:\Users\Apichatpong\MPLABXProjects\demo.X"
ProjectName=demo
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: ["D:\work\mplab\avrdude.exe" -C "D:\work\mplab\avrdude.conf" -c  usbasp -p m328p -B 10 -b 115200 -U flash:w:${ImagePath}:i]"
	@"D:\work\mplab\avrdude.exe" -C "D:\work\mplab\avrdude.conf" -c  usbasp -p m328p -B 10 -b 115200 -U flash:w:${ImagePath}:i
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=ATmega328P
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  .generated_files/2f2785389d6e89a1d0f38509077692a1ab20236.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
${OBJECTDIR}/keypad/keypad.o: keypad/keypad.c  .generated_files/b9b7e370e700cc29b0c5fb771a8f7ad7d1f2d7bd.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/keypad" 
	@${RM} ${OBJECTDIR}/keypad/keypad.o.d 
	@${RM} ${OBJECTDIR}/keypad/keypad.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/keypad/keypad.o.d" -MT "${OBJECTDIR}/keypad/keypad.o.d" -MT ${OBJECTDIR}/keypad/keypad.o -o ${OBJECTDIR}/keypad/keypad.o keypad/keypad.c 
	
${OBJECTDIR}/lcd/lcd.o: lcd/lcd.c  .generated_files/5f88ba8807f81ee43421182310c5b324ab1d02ee.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/lcd" 
	@${RM} ${OBJECTDIR}/lcd/lcd.o.d 
	@${RM} ${OBJECTDIR}/lcd/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/lcd/lcd.o.d" -MT "${OBJECTDIR}/lcd/lcd.o.d" -MT ${OBJECTDIR}/lcd/lcd.o -o ${OBJECTDIR}/lcd/lcd.o lcd/lcd.c 
	
${OBJECTDIR}/utils/delay.o: utils/delay.c  .generated_files/ac52de86f3db849fda7eb45c4073b67f7d694fca.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/utils" 
	@${RM} ${OBJECTDIR}/utils/delay.o.d 
	@${RM} ${OBJECTDIR}/utils/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/utils/delay.o.d" -MT "${OBJECTDIR}/utils/delay.o.d" -MT ${OBJECTDIR}/utils/delay.o -o ${OBJECTDIR}/utils/delay.o utils/delay.c 
	
${OBJECTDIR}/rfid/mfrc522.o: rfid/mfrc522.c  .generated_files/dec938831fb442f918d71dd7f137ddb1f3cde2d3.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/rfid" 
	@${RM} ${OBJECTDIR}/rfid/mfrc522.o.d 
	@${RM} ${OBJECTDIR}/rfid/mfrc522.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/rfid/mfrc522.o.d" -MT "${OBJECTDIR}/rfid/mfrc522.o.d" -MT ${OBJECTDIR}/rfid/mfrc522.o -o ${OBJECTDIR}/rfid/mfrc522.o rfid/mfrc522.c 
	
${OBJECTDIR}/spi/spi.o: spi/spi.c  .generated_files/dc20608352170a78e9432b63b9cd3e64d0ebcf3a.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/spi" 
	@${RM} ${OBJECTDIR}/spi/spi.o.d 
	@${RM} ${OBJECTDIR}/spi/spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/spi/spi.o.d" -MT "${OBJECTDIR}/spi/spi.o.d" -MT ${OBJECTDIR}/spi/spi.o -o ${OBJECTDIR}/spi/spi.o spi/spi.c 
	
${OBJECTDIR}/sdcard/sdcard.o: sdcard/sdcard.c  .generated_files/1a4c0b09e5ac48492a6870f58bdb5f9abeee358b.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/sdcard" 
	@${RM} ${OBJECTDIR}/sdcard/sdcard.o.d 
	@${RM} ${OBJECTDIR}/sdcard/sdcard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/sdcard/sdcard.o.d" -MT "${OBJECTDIR}/sdcard/sdcard.o.d" -MT ${OBJECTDIR}/sdcard/sdcard.o -o ${OBJECTDIR}/sdcard/sdcard.o sdcard/sdcard.c 
	
${OBJECTDIR}/fatfs/diskio.o: fatfs/diskio.c  .generated_files/210cadb5ef41bc07282ce696e55358ddbc883c67.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/fatfs" 
	@${RM} ${OBJECTDIR}/fatfs/diskio.o.d 
	@${RM} ${OBJECTDIR}/fatfs/diskio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/fatfs/diskio.o.d" -MT "${OBJECTDIR}/fatfs/diskio.o.d" -MT ${OBJECTDIR}/fatfs/diskio.o -o ${OBJECTDIR}/fatfs/diskio.o fatfs/diskio.c 
	
${OBJECTDIR}/fatfs/ff.o: fatfs/ff.c  .generated_files/eba91b2f209f8c1f479b07c64a26ef79675b6cb.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/fatfs" 
	@${RM} ${OBJECTDIR}/fatfs/ff.o.d 
	@${RM} ${OBJECTDIR}/fatfs/ff.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/fatfs/ff.o.d" -MT "${OBJECTDIR}/fatfs/ff.o.d" -MT ${OBJECTDIR}/fatfs/ff.o -o ${OBJECTDIR}/fatfs/ff.o fatfs/ff.c 
	
else
${OBJECTDIR}/main.o: main.c  .generated_files/f7ba77a01f5e63170ccc9a8c6c96506023e01af.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
${OBJECTDIR}/keypad/keypad.o: keypad/keypad.c  .generated_files/1f414fa01006a519f294ed831b67649b4697190f.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/keypad" 
	@${RM} ${OBJECTDIR}/keypad/keypad.o.d 
	@${RM} ${OBJECTDIR}/keypad/keypad.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/keypad/keypad.o.d" -MT "${OBJECTDIR}/keypad/keypad.o.d" -MT ${OBJECTDIR}/keypad/keypad.o -o ${OBJECTDIR}/keypad/keypad.o keypad/keypad.c 
	
${OBJECTDIR}/lcd/lcd.o: lcd/lcd.c  .generated_files/1a40ecfdb1f9d4759dc5a8035bb2494bc8667650.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/lcd" 
	@${RM} ${OBJECTDIR}/lcd/lcd.o.d 
	@${RM} ${OBJECTDIR}/lcd/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/lcd/lcd.o.d" -MT "${OBJECTDIR}/lcd/lcd.o.d" -MT ${OBJECTDIR}/lcd/lcd.o -o ${OBJECTDIR}/lcd/lcd.o lcd/lcd.c 
	
${OBJECTDIR}/utils/delay.o: utils/delay.c  .generated_files/e8495fbf8795ef371a478cfde407fe0609f89a9a.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/utils" 
	@${RM} ${OBJECTDIR}/utils/delay.o.d 
	@${RM} ${OBJECTDIR}/utils/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/utils/delay.o.d" -MT "${OBJECTDIR}/utils/delay.o.d" -MT ${OBJECTDIR}/utils/delay.o -o ${OBJECTDIR}/utils/delay.o utils/delay.c 
	
${OBJECTDIR}/rfid/mfrc522.o: rfid/mfrc522.c  .generated_files/8a7ceaa26427105f7eb16a098101eb16bdd466c9.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/rfid" 
	@${RM} ${OBJECTDIR}/rfid/mfrc522.o.d 
	@${RM} ${OBJECTDIR}/rfid/mfrc522.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/rfid/mfrc522.o.d" -MT "${OBJECTDIR}/rfid/mfrc522.o.d" -MT ${OBJECTDIR}/rfid/mfrc522.o -o ${OBJECTDIR}/rfid/mfrc522.o rfid/mfrc522.c 
	
${OBJECTDIR}/spi/spi.o: spi/spi.c  .generated_files/dc7ad18def97148fd7e8b67bf5da7e1660d099e9.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/spi" 
	@${RM} ${OBJECTDIR}/spi/spi.o.d 
	@${RM} ${OBJECTDIR}/spi/spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/spi/spi.o.d" -MT "${OBJECTDIR}/spi/spi.o.d" -MT ${OBJECTDIR}/spi/spi.o -o ${OBJECTDIR}/spi/spi.o spi/spi.c 
	
${OBJECTDIR}/sdcard/sdcard.o: sdcard/sdcard.c  .generated_files/7c6b2ac9f6bb5e08f52d4baf13107e639e24c1f3.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/sdcard" 
	@${RM} ${OBJECTDIR}/sdcard/sdcard.o.d 
	@${RM} ${OBJECTDIR}/sdcard/sdcard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/sdcard/sdcard.o.d" -MT "${OBJECTDIR}/sdcard/sdcard.o.d" -MT ${OBJECTDIR}/sdcard/sdcard.o -o ${OBJECTDIR}/sdcard/sdcard.o sdcard/sdcard.c 
	
${OBJECTDIR}/fatfs/diskio.o: fatfs/diskio.c  .generated_files/a8a685475cfaca83c2b51e5875320178b4a7aa6c.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/fatfs" 
	@${RM} ${OBJECTDIR}/fatfs/diskio.o.d 
	@${RM} ${OBJECTDIR}/fatfs/diskio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/fatfs/diskio.o.d" -MT "${OBJECTDIR}/fatfs/diskio.o.d" -MT ${OBJECTDIR}/fatfs/diskio.o -o ${OBJECTDIR}/fatfs/diskio.o fatfs/diskio.c 
	
${OBJECTDIR}/fatfs/ff.o: fatfs/ff.c  .generated_files/e3a3001dc47b565ccb4ff18e5c808e64d0b019fe.flag .generated_files/20399448a832cbd630475386a660c541583d2068.flag
	@${MKDIR} "${OBJECTDIR}/fatfs" 
	@${RM} ${OBJECTDIR}/fatfs/ff.o.d 
	@${RM} ${OBJECTDIR}/fatfs/ff.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/fatfs/ff.o.d" -MT "${OBJECTDIR}/fatfs/ff.o.d" -MT ${OBJECTDIR}/fatfs/ff.o -o ${OBJECTDIR}/fatfs/ff.o fatfs/ff.c 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/demo.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"   -gdwarf-2 -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -gdwarf-3     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/demo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o dist/${CND_CONF}/${IMAGE_TYPE}/demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/demo.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/demo.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -Wall -gdwarf-3     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/demo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o dist/${CND_CONF}/${IMAGE_TYPE}/demo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/demo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/demo.X.${IMAGE_TYPE}.hex"
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
