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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Pozyx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Pozyx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=FastTransfer/crc.c FastTransfer/ft.c FastTransfer/parser.c FastTransfer/ring_buffer.c mcc_generated_files/can1.c mcc_generated_files/dma.c mcc_generated_files/ecan1.c PozyxPIC_I2C.c Pozyx_lib.c Pozyx_Core.c Initialize.c main.c Timers.c PozyxWrapper.c DataPublishing.c FastTransfer_CAN.c uart1_config.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/FastTransfer/crc.o ${OBJECTDIR}/FastTransfer/ft.o ${OBJECTDIR}/FastTransfer/parser.o ${OBJECTDIR}/FastTransfer/ring_buffer.o ${OBJECTDIR}/mcc_generated_files/can1.o ${OBJECTDIR}/mcc_generated_files/dma.o ${OBJECTDIR}/mcc_generated_files/ecan1.o ${OBJECTDIR}/PozyxPIC_I2C.o ${OBJECTDIR}/Pozyx_lib.o ${OBJECTDIR}/Pozyx_Core.o ${OBJECTDIR}/Initialize.o ${OBJECTDIR}/main.o ${OBJECTDIR}/Timers.o ${OBJECTDIR}/PozyxWrapper.o ${OBJECTDIR}/DataPublishing.o ${OBJECTDIR}/FastTransfer_CAN.o ${OBJECTDIR}/uart1_config.o
POSSIBLE_DEPFILES=${OBJECTDIR}/FastTransfer/crc.o.d ${OBJECTDIR}/FastTransfer/ft.o.d ${OBJECTDIR}/FastTransfer/parser.o.d ${OBJECTDIR}/FastTransfer/ring_buffer.o.d ${OBJECTDIR}/mcc_generated_files/can1.o.d ${OBJECTDIR}/mcc_generated_files/dma.o.d ${OBJECTDIR}/mcc_generated_files/ecan1.o.d ${OBJECTDIR}/PozyxPIC_I2C.o.d ${OBJECTDIR}/Pozyx_lib.o.d ${OBJECTDIR}/Pozyx_Core.o.d ${OBJECTDIR}/Initialize.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/Timers.o.d ${OBJECTDIR}/PozyxWrapper.o.d ${OBJECTDIR}/DataPublishing.o.d ${OBJECTDIR}/FastTransfer_CAN.o.d ${OBJECTDIR}/uart1_config.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/FastTransfer/crc.o ${OBJECTDIR}/FastTransfer/ft.o ${OBJECTDIR}/FastTransfer/parser.o ${OBJECTDIR}/FastTransfer/ring_buffer.o ${OBJECTDIR}/mcc_generated_files/can1.o ${OBJECTDIR}/mcc_generated_files/dma.o ${OBJECTDIR}/mcc_generated_files/ecan1.o ${OBJECTDIR}/PozyxPIC_I2C.o ${OBJECTDIR}/Pozyx_lib.o ${OBJECTDIR}/Pozyx_Core.o ${OBJECTDIR}/Initialize.o ${OBJECTDIR}/main.o ${OBJECTDIR}/Timers.o ${OBJECTDIR}/PozyxWrapper.o ${OBJECTDIR}/DataPublishing.o ${OBJECTDIR}/FastTransfer_CAN.o ${OBJECTDIR}/uart1_config.o

# Source Files
SOURCEFILES=FastTransfer/crc.c FastTransfer/ft.c FastTransfer/parser.c FastTransfer/ring_buffer.c mcc_generated_files/can1.c mcc_generated_files/dma.c mcc_generated_files/ecan1.c PozyxPIC_I2C.c Pozyx_lib.c Pozyx_Core.c Initialize.c main.c Timers.c PozyxWrapper.c DataPublishing.c FastTransfer_CAN.c uart1_config.c



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

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Pozyx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP512GM604
MP_LINKER_FILE_OPTION=,--script=p33EP512GM604.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/FastTransfer/crc.o: FastTransfer/crc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FastTransfer" 
	@${RM} ${OBJECTDIR}/FastTransfer/crc.o.d 
	@${RM} ${OBJECTDIR}/FastTransfer/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FastTransfer/crc.c  -o ${OBJECTDIR}/FastTransfer/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FastTransfer/crc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/FastTransfer/crc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FastTransfer/ft.o: FastTransfer/ft.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FastTransfer" 
	@${RM} ${OBJECTDIR}/FastTransfer/ft.o.d 
	@${RM} ${OBJECTDIR}/FastTransfer/ft.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FastTransfer/ft.c  -o ${OBJECTDIR}/FastTransfer/ft.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FastTransfer/ft.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/FastTransfer/ft.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FastTransfer/parser.o: FastTransfer/parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FastTransfer" 
	@${RM} ${OBJECTDIR}/FastTransfer/parser.o.d 
	@${RM} ${OBJECTDIR}/FastTransfer/parser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FastTransfer/parser.c  -o ${OBJECTDIR}/FastTransfer/parser.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FastTransfer/parser.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/FastTransfer/parser.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FastTransfer/ring_buffer.o: FastTransfer/ring_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FastTransfer" 
	@${RM} ${OBJECTDIR}/FastTransfer/ring_buffer.o.d 
	@${RM} ${OBJECTDIR}/FastTransfer/ring_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FastTransfer/ring_buffer.c  -o ${OBJECTDIR}/FastTransfer/ring_buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FastTransfer/ring_buffer.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/FastTransfer/ring_buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/can1.o: mcc_generated_files/can1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/can1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/can1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/can1.c  -o ${OBJECTDIR}/mcc_generated_files/can1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/can1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/can1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/dma.o: mcc_generated_files/dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dma.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/dma.c  -o ${OBJECTDIR}/mcc_generated_files/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/dma.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/ecan1.o: mcc_generated_files/ecan1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/ecan1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/ecan1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/ecan1.c  -o ${OBJECTDIR}/mcc_generated_files/ecan1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/ecan1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/ecan1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PozyxPIC_I2C.o: PozyxPIC_I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PozyxPIC_I2C.o.d 
	@${RM} ${OBJECTDIR}/PozyxPIC_I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PozyxPIC_I2C.c  -o ${OBJECTDIR}/PozyxPIC_I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PozyxPIC_I2C.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/PozyxPIC_I2C.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Pozyx_lib.o: Pozyx_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Pozyx_lib.o.d 
	@${RM} ${OBJECTDIR}/Pozyx_lib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Pozyx_lib.c  -o ${OBJECTDIR}/Pozyx_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Pozyx_lib.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/Pozyx_lib.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Pozyx_Core.o: Pozyx_Core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Pozyx_Core.o.d 
	@${RM} ${OBJECTDIR}/Pozyx_Core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Pozyx_Core.c  -o ${OBJECTDIR}/Pozyx_Core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Pozyx_Core.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/Pozyx_Core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Initialize.o: Initialize.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Initialize.o.d 
	@${RM} ${OBJECTDIR}/Initialize.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Initialize.c  -o ${OBJECTDIR}/Initialize.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Initialize.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/Initialize.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Timers.o: Timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Timers.o.d 
	@${RM} ${OBJECTDIR}/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timers.c  -o ${OBJECTDIR}/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Timers.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/Timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PozyxWrapper.o: PozyxWrapper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PozyxWrapper.o.d 
	@${RM} ${OBJECTDIR}/PozyxWrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PozyxWrapper.c  -o ${OBJECTDIR}/PozyxWrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PozyxWrapper.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/PozyxWrapper.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/DataPublishing.o: DataPublishing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DataPublishing.o.d 
	@${RM} ${OBJECTDIR}/DataPublishing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  DataPublishing.c  -o ${OBJECTDIR}/DataPublishing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DataPublishing.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/DataPublishing.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FastTransfer_CAN.o: FastTransfer_CAN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FastTransfer_CAN.o.d 
	@${RM} ${OBJECTDIR}/FastTransfer_CAN.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FastTransfer_CAN.c  -o ${OBJECTDIR}/FastTransfer_CAN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FastTransfer_CAN.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/FastTransfer_CAN.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uart1_config.o: uart1_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart1_config.o.d 
	@${RM} ${OBJECTDIR}/uart1_config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uart1_config.c  -o ${OBJECTDIR}/uart1_config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uart1_config.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/uart1_config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/FastTransfer/crc.o: FastTransfer/crc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FastTransfer" 
	@${RM} ${OBJECTDIR}/FastTransfer/crc.o.d 
	@${RM} ${OBJECTDIR}/FastTransfer/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FastTransfer/crc.c  -o ${OBJECTDIR}/FastTransfer/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FastTransfer/crc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/FastTransfer/crc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FastTransfer/ft.o: FastTransfer/ft.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FastTransfer" 
	@${RM} ${OBJECTDIR}/FastTransfer/ft.o.d 
	@${RM} ${OBJECTDIR}/FastTransfer/ft.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FastTransfer/ft.c  -o ${OBJECTDIR}/FastTransfer/ft.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FastTransfer/ft.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/FastTransfer/ft.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FastTransfer/parser.o: FastTransfer/parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FastTransfer" 
	@${RM} ${OBJECTDIR}/FastTransfer/parser.o.d 
	@${RM} ${OBJECTDIR}/FastTransfer/parser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FastTransfer/parser.c  -o ${OBJECTDIR}/FastTransfer/parser.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FastTransfer/parser.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/FastTransfer/parser.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FastTransfer/ring_buffer.o: FastTransfer/ring_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FastTransfer" 
	@${RM} ${OBJECTDIR}/FastTransfer/ring_buffer.o.d 
	@${RM} ${OBJECTDIR}/FastTransfer/ring_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FastTransfer/ring_buffer.c  -o ${OBJECTDIR}/FastTransfer/ring_buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FastTransfer/ring_buffer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/FastTransfer/ring_buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/can1.o: mcc_generated_files/can1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/can1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/can1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/can1.c  -o ${OBJECTDIR}/mcc_generated_files/can1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/can1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/can1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/dma.o: mcc_generated_files/dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dma.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/dma.c  -o ${OBJECTDIR}/mcc_generated_files/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/dma.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/ecan1.o: mcc_generated_files/ecan1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/ecan1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/ecan1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/ecan1.c  -o ${OBJECTDIR}/mcc_generated_files/ecan1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/ecan1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/ecan1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PozyxPIC_I2C.o: PozyxPIC_I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PozyxPIC_I2C.o.d 
	@${RM} ${OBJECTDIR}/PozyxPIC_I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PozyxPIC_I2C.c  -o ${OBJECTDIR}/PozyxPIC_I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PozyxPIC_I2C.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/PozyxPIC_I2C.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Pozyx_lib.o: Pozyx_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Pozyx_lib.o.d 
	@${RM} ${OBJECTDIR}/Pozyx_lib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Pozyx_lib.c  -o ${OBJECTDIR}/Pozyx_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Pozyx_lib.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/Pozyx_lib.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Pozyx_Core.o: Pozyx_Core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Pozyx_Core.o.d 
	@${RM} ${OBJECTDIR}/Pozyx_Core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Pozyx_Core.c  -o ${OBJECTDIR}/Pozyx_Core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Pozyx_Core.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/Pozyx_Core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Initialize.o: Initialize.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Initialize.o.d 
	@${RM} ${OBJECTDIR}/Initialize.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Initialize.c  -o ${OBJECTDIR}/Initialize.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Initialize.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/Initialize.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Timers.o: Timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Timers.o.d 
	@${RM} ${OBJECTDIR}/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timers.c  -o ${OBJECTDIR}/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Timers.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/Timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PozyxWrapper.o: PozyxWrapper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PozyxWrapper.o.d 
	@${RM} ${OBJECTDIR}/PozyxWrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PozyxWrapper.c  -o ${OBJECTDIR}/PozyxWrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PozyxWrapper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/PozyxWrapper.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/DataPublishing.o: DataPublishing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DataPublishing.o.d 
	@${RM} ${OBJECTDIR}/DataPublishing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  DataPublishing.c  -o ${OBJECTDIR}/DataPublishing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DataPublishing.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/DataPublishing.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FastTransfer_CAN.o: FastTransfer_CAN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FastTransfer_CAN.o.d 
	@${RM} ${OBJECTDIR}/FastTransfer_CAN.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FastTransfer_CAN.c  -o ${OBJECTDIR}/FastTransfer_CAN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FastTransfer_CAN.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/FastTransfer_CAN.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uart1_config.o: uart1_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart1_config.o.d 
	@${RM} ${OBJECTDIR}/uart1_config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uart1_config.c  -o ${OBJECTDIR}/uart1_config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uart1_config.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/uart1_config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Pozyx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Pozyx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Pozyx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Pozyx.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Pozyx.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   
	
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
