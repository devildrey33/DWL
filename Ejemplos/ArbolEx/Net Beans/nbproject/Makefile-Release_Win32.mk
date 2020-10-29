#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=g77.exe
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Release_Win32
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1472/MiArbolEx.o \
	${OBJECTDIR}/_ext/1472/VentanaMain.o \
	${OBJECTDIR}/_ext/1472/stdafx.o \
	${OBJECTDIR}/_ext/1472/ArbolEx.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../../Lib ../../../Net\ Beans/../lib/DWL_Debug.a ../../../../../MinGW/lib/libkernel32.a -luser32 -lgdi32 -lcomdlg32 -lshell32 -lole32 ../../../../../MinGW/lib/libmsimg32.a ../../../../../MinGW/lib/libmpr.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Release_Win32.mk ../../../Bin/ArbolEx.exe

../../../Bin/ArbolEx.exe: ../../../Net\ Beans/../lib/DWL_Debug.a

../../../Bin/ArbolEx.exe: ../../../../../MinGW/lib/libkernel32.a

../../../Bin/ArbolEx.exe: ../../../../../MinGW/lib/libmsimg32.a

../../../Bin/ArbolEx.exe: ../../../../../MinGW/lib/libmpr.a

../../../Bin/ArbolEx.exe: ${OBJECTFILES}
	${MKDIR} -p ../../../Bin
	${LINK.cc} -o ../../../Bin/ArbolEx.exe ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1472/MiArbolEx.o: ../MiArbolEx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_UNICODE -DUNICODE -D_WINDOWS -DWIN32 -I../../../Include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/MiArbolEx.o ../MiArbolEx.cpp

${OBJECTDIR}/_ext/1472/VentanaMain.o: ../VentanaMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_UNICODE -DUNICODE -D_WINDOWS -DWIN32 -I../../../Include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/VentanaMain.o ../VentanaMain.cpp

${OBJECTDIR}/_ext/1472/stdafx.o: ../stdafx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_UNICODE -DUNICODE -D_WINDOWS -DWIN32 -I../../../Include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/stdafx.o ../stdafx.cpp

${OBJECTDIR}/_ext/1472/ArbolEx.o: ../ArbolEx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_UNICODE -DUNICODE -D_WINDOWS -DWIN32 -I../../../Include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/ArbolEx.o ../ArbolEx.cpp

# Subprojects
.build-subprojects:
	cd ../../../Net\ Beans && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release_Win32
	${RM} ../../../Bin/ArbolEx.exe

# Subprojects
.clean-subprojects:
	cd ../../../Net\ Beans && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
