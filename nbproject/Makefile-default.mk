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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MXBasic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MXBasic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c uart2.c uart2to1.c usb_config.c usb_host.c usb_host_hid.c usb_host_hid_device.c usb_host_hid_parser.c timer.c display.c character.c graphic.c ttbasic.c sound.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/uart2.o ${OBJECTDIR}/uart2to1.o ${OBJECTDIR}/usb_config.o ${OBJECTDIR}/usb_host.o ${OBJECTDIR}/usb_host_hid.o ${OBJECTDIR}/usb_host_hid_device.o ${OBJECTDIR}/usb_host_hid_parser.o ${OBJECTDIR}/timer.o ${OBJECTDIR}/display.o ${OBJECTDIR}/character.o ${OBJECTDIR}/graphic.o ${OBJECTDIR}/ttbasic.o ${OBJECTDIR}/sound.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/uart2.o.d ${OBJECTDIR}/uart2to1.o.d ${OBJECTDIR}/usb_config.o.d ${OBJECTDIR}/usb_host.o.d ${OBJECTDIR}/usb_host_hid.o.d ${OBJECTDIR}/usb_host_hid_device.o.d ${OBJECTDIR}/usb_host_hid_parser.o.d ${OBJECTDIR}/timer.o.d ${OBJECTDIR}/display.o.d ${OBJECTDIR}/character.o.d ${OBJECTDIR}/graphic.o.d ${OBJECTDIR}/ttbasic.o.d ${OBJECTDIR}/sound.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/uart2.o ${OBJECTDIR}/uart2to1.o ${OBJECTDIR}/usb_config.o ${OBJECTDIR}/usb_host.o ${OBJECTDIR}/usb_host_hid.o ${OBJECTDIR}/usb_host_hid_device.o ${OBJECTDIR}/usb_host_hid_parser.o ${OBJECTDIR}/timer.o ${OBJECTDIR}/display.o ${OBJECTDIR}/character.o ${OBJECTDIR}/graphic.o ${OBJECTDIR}/ttbasic.o ${OBJECTDIR}/sound.o

# Source Files
SOURCEFILES=main.c uart2.c uart2to1.c usb_config.c usb_host.c usb_host_hid.c usb_host_hid_device.c usb_host_hid_parser.c timer.c display.c character.c graphic.c ttbasic.c sound.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MXBasic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX695F512H
MP_LINKER_FILE_OPTION=,--script="sbdbt32app.ld"
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
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c   
	
${OBJECTDIR}/uart2.o: uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/uart2.o.d 
	@${RM} ${OBJECTDIR}/uart2.o 
	@${FIXDEPS} "${OBJECTDIR}/uart2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uart2.o.d" -o ${OBJECTDIR}/uart2.o uart2.c   
	
${OBJECTDIR}/uart2to1.o: uart2to1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/uart2to1.o.d 
	@${RM} ${OBJECTDIR}/uart2to1.o 
	@${FIXDEPS} "${OBJECTDIR}/uart2to1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uart2to1.o.d" -o ${OBJECTDIR}/uart2to1.o uart2to1.c   
	
${OBJECTDIR}/usb_config.o: usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_config.o.d 
	@${RM} ${OBJECTDIR}/usb_config.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_config.o.d" -o ${OBJECTDIR}/usb_config.o usb_config.c   
	
${OBJECTDIR}/usb_host.o: usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_host.o.d 
	@${RM} ${OBJECTDIR}/usb_host.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_host.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_host.o.d" -o ${OBJECTDIR}/usb_host.o usb_host.c   
	
${OBJECTDIR}/usb_host_hid.o: usb_host_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_host_hid.o.d 
	@${RM} ${OBJECTDIR}/usb_host_hid.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_host_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_host_hid.o.d" -o ${OBJECTDIR}/usb_host_hid.o usb_host_hid.c   
	
${OBJECTDIR}/usb_host_hid_device.o: usb_host_hid_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_host_hid_device.o.d 
	@${RM} ${OBJECTDIR}/usb_host_hid_device.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_host_hid_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_host_hid_device.o.d" -o ${OBJECTDIR}/usb_host_hid_device.o usb_host_hid_device.c   
	
${OBJECTDIR}/usb_host_hid_parser.o: usb_host_hid_parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_host_hid_parser.o.d 
	@${RM} ${OBJECTDIR}/usb_host_hid_parser.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_host_hid_parser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_host_hid_parser.o.d" -o ${OBJECTDIR}/usb_host_hid_parser.o usb_host_hid_parser.c   
	
${OBJECTDIR}/timer.o: timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timer.o.d 
	@${RM} ${OBJECTDIR}/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/timer.o.d" -o ${OBJECTDIR}/timer.o timer.c   
	
${OBJECTDIR}/display.o: display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/display.o.d 
	@${RM} ${OBJECTDIR}/display.o 
	@${FIXDEPS} "${OBJECTDIR}/display.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/display.o.d" -o ${OBJECTDIR}/display.o display.c   
	
${OBJECTDIR}/character.o: character.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/character.o.d 
	@${RM} ${OBJECTDIR}/character.o 
	@${FIXDEPS} "${OBJECTDIR}/character.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/character.o.d" -o ${OBJECTDIR}/character.o character.c   
	
${OBJECTDIR}/graphic.o: graphic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/graphic.o.d 
	@${RM} ${OBJECTDIR}/graphic.o 
	@${FIXDEPS} "${OBJECTDIR}/graphic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/graphic.o.d" -o ${OBJECTDIR}/graphic.o graphic.c   
	
${OBJECTDIR}/ttbasic.o: ttbasic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ttbasic.o.d 
	@${RM} ${OBJECTDIR}/ttbasic.o 
	@${FIXDEPS} "${OBJECTDIR}/ttbasic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ttbasic.o.d" -o ${OBJECTDIR}/ttbasic.o ttbasic.c   
	
${OBJECTDIR}/sound.o: sound.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sound.o.d 
	@${RM} ${OBJECTDIR}/sound.o 
	@${FIXDEPS} "${OBJECTDIR}/sound.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sound.o.d" -o ${OBJECTDIR}/sound.o sound.c   
	
else
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c   
	
${OBJECTDIR}/uart2.o: uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/uart2.o.d 
	@${RM} ${OBJECTDIR}/uart2.o 
	@${FIXDEPS} "${OBJECTDIR}/uart2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uart2.o.d" -o ${OBJECTDIR}/uart2.o uart2.c   
	
${OBJECTDIR}/uart2to1.o: uart2to1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/uart2to1.o.d 
	@${RM} ${OBJECTDIR}/uart2to1.o 
	@${FIXDEPS} "${OBJECTDIR}/uart2to1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uart2to1.o.d" -o ${OBJECTDIR}/uart2to1.o uart2to1.c   
	
${OBJECTDIR}/usb_config.o: usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_config.o.d 
	@${RM} ${OBJECTDIR}/usb_config.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_config.o.d" -o ${OBJECTDIR}/usb_config.o usb_config.c   
	
${OBJECTDIR}/usb_host.o: usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_host.o.d 
	@${RM} ${OBJECTDIR}/usb_host.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_host.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_host.o.d" -o ${OBJECTDIR}/usb_host.o usb_host.c   
	
${OBJECTDIR}/usb_host_hid.o: usb_host_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_host_hid.o.d 
	@${RM} ${OBJECTDIR}/usb_host_hid.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_host_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_host_hid.o.d" -o ${OBJECTDIR}/usb_host_hid.o usb_host_hid.c   
	
${OBJECTDIR}/usb_host_hid_device.o: usb_host_hid_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_host_hid_device.o.d 
	@${RM} ${OBJECTDIR}/usb_host_hid_device.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_host_hid_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_host_hid_device.o.d" -o ${OBJECTDIR}/usb_host_hid_device.o usb_host_hid_device.c   
	
${OBJECTDIR}/usb_host_hid_parser.o: usb_host_hid_parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_host_hid_parser.o.d 
	@${RM} ${OBJECTDIR}/usb_host_hid_parser.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_host_hid_parser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_host_hid_parser.o.d" -o ${OBJECTDIR}/usb_host_hid_parser.o usb_host_hid_parser.c   
	
${OBJECTDIR}/timer.o: timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timer.o.d 
	@${RM} ${OBJECTDIR}/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/timer.o.d" -o ${OBJECTDIR}/timer.o timer.c   
	
${OBJECTDIR}/display.o: display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/display.o.d 
	@${RM} ${OBJECTDIR}/display.o 
	@${FIXDEPS} "${OBJECTDIR}/display.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/display.o.d" -o ${OBJECTDIR}/display.o display.c   
	
${OBJECTDIR}/character.o: character.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/character.o.d 
	@${RM} ${OBJECTDIR}/character.o 
	@${FIXDEPS} "${OBJECTDIR}/character.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/character.o.d" -o ${OBJECTDIR}/character.o character.c   
	
${OBJECTDIR}/graphic.o: graphic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/graphic.o.d 
	@${RM} ${OBJECTDIR}/graphic.o 
	@${FIXDEPS} "${OBJECTDIR}/graphic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/graphic.o.d" -o ${OBJECTDIR}/graphic.o graphic.c   
	
${OBJECTDIR}/ttbasic.o: ttbasic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ttbasic.o.d 
	@${RM} ${OBJECTDIR}/ttbasic.o 
	@${FIXDEPS} "${OBJECTDIR}/ttbasic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ttbasic.o.d" -o ${OBJECTDIR}/ttbasic.o ttbasic.c   
	
${OBJECTDIR}/sound.o: sound.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sound.o.d 
	@${RM} ${OBJECTDIR}/sound.o 
	@${FIXDEPS} "${OBJECTDIR}/sound.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sound.o.d" -o ${OBJECTDIR}/sound.o sound.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MXBasic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    sbdbt32app.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MXBasic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,--defsym=_min_heap_size=10240,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MXBasic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   sbdbt32app.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MXBasic.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=10240,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MXBasic.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
