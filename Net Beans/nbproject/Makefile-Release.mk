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
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1926721337/DWLBaseWnd.o \
	${OBJECTDIR}/_ext/1926721337/DWLIcono.o \
	${OBJECTDIR}/_ext/2010942847/DWLEdicionEx_Nucleo.o \
	${OBJECTDIR}/_ext/1926721337/DWLListaIconos.o \
	${OBJECTDIR}/_ext/1926721337/DWLDialogoColores.o \
	${OBJECTDIR}/_ext/810148909/DWLListaEx_Columna.o \
	${OBJECTDIR}/_ext/1926721337/DWLArbolEx.o \
	${OBJECTDIR}/_ext/1926721337/DWLDirectoriosWindows.o \
	${OBJECTDIR}/_ext/1926721337/DWLListView.o \
	${OBJECTDIR}/_ext/1926721337/DWLFuente.o \
	${OBJECTDIR}/_ext/810148909/DWLListaEx_Item.o \
	${OBJECTDIR}/_ext/1926721337/DWLString.o \
	${OBJECTDIR}/_ext/1926721337/DWLRegion.o \
	${OBJECTDIR}/_ext/1740930690/DWLArbolEx_Nucleo.o \
	${OBJECTDIR}/_ext/1926721337/DWLRecta.o \
	${OBJECTDIR}/_ext/1926721337/DWLBarraScrollEx.o \
	${OBJECTDIR}/_ext/1926721337/DWLListaEx.o \
	${OBJECTDIR}/_ext/1926721337/DWLVentanaErrorGrave.o \
	${OBJECTDIR}/_ext/1926721337/DWLControlEx.o \
	${OBJECTDIR}/_ext/1926721337/DWLDialogo.o \
	${OBJECTDIR}/_ext/1926721337/DWLMedidasSistema.o \
	${OBJECTDIR}/_ext/1926721337/DWLhDC.o \
	${OBJECTDIR}/_ext/1926721337/DWLBrocha.o \
	${OBJECTDIR}/_ext/810148909/DWLListaEx_Nucleo.o \
	${OBJECTDIR}/_ext/1926721337/DWLDialogoGuardar.o \
	${OBJECTDIR}/_ext/1740930690/DWLArbolEx_Nodo.o \
	${OBJECTDIR}/_ext/1926721337/DWLDialogoAbrir.o \
	${OBJECTDIR}/_ext/1926721337/DWLTreeView.o \
	${OBJECTDIR}/_ext/1926721337/DWLEdicionDesplegableEx.o \
	${OBJECTDIR}/_ext/1926721337/DWLPluma.o \
	${OBJECTDIR}/_ext/1926721337/DWLToolTipEx.o \
	${OBJECTDIR}/_ext/1926721337/DWLDialogoFuentes.o \
	${OBJECTDIR}/_ext/1926721337/DWLExplorarDirectorios.o \
	${OBJECTDIR}/_ext/1926721337/DWLVentana.o \
	${OBJECTDIR}/_ext/1926721337/DWLControl.o \
	${OBJECTDIR}/_ext/1926721337/DWLDebug.o \
	${OBJECTDIR}/_ext/1325267438/DWLBarraEx_Nucleo.o \
	${OBJECTDIR}/_ext/1926721337/DWLVentanaMDIChild.o \
	${OBJECTDIR}/_ext/1926721337/DWLVentanaMDI.o \
	${OBJECTDIR}/_ext/1926721337/DWLMarcaEx.o \
	${OBJECTDIR}/_ext/1926721337/DWLBarraEx.o \
	${OBJECTDIR}/_ext/1926721337/DWLDialogoDirectorios.o \
	${OBJECTDIR}/_ext/1926721337/DWLEdicionEx.o \
	${OBJECTDIR}/_ext/1926721337/DWLMapaBits.o \
	${OBJECTDIR}/_ext/1854159114/DWLEstilos_Fuente.o \
	${OBJECTDIR}/_ext/1926721337/DWLDialogoImpresoras.o \
	${OBJECTDIR}/_ext/922689162/DWLBotonEx_Nucleo.o \
	${OBJECTDIR}/_ext/1926721337/DWLMenuEx.o \
	${OBJECTDIR}/_ext/153108404/DWLMarcaEx_Nucleo.o \
	${OBJECTDIR}/_ext/1926721337/DWLBotonEx.o \
	${OBJECTDIR}/_ext/1926721337/DWLAplicacion.o \
	${OBJECTDIR}/_ext/1926721337/DWLEstilos.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Release.mk ../Lib/DWL.a

../Lib/DWL.a: ${OBJECTFILES}
	${MKDIR} -p ../Lib
	${RM} ../Lib/DWL.a
	${AR} -rv ../Lib/DWL.a ${OBJECTFILES} 
	$(RANLIB) ../Lib/DWL.a

${OBJECTDIR}/_ext/1926721337/DWLBaseWnd.o: ../Include/DWLBaseWnd.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLBaseWnd.o ../Include/DWLBaseWnd.cpp

${OBJECTDIR}/_ext/1926721337/DWLIcono.o: ../Include/DWLIcono.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLIcono.o ../Include/DWLIcono.cpp

${OBJECTDIR}/_ext/2010942847/DWLEdicionEx_Nucleo.o: ../Include/DWLEdicionEx/DWLEdicionEx_Nucleo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2010942847
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2010942847/DWLEdicionEx_Nucleo.o ../Include/DWLEdicionEx/DWLEdicionEx_Nucleo.cpp

${OBJECTDIR}/_ext/1926721337/DWLListaIconos.o: ../Include/DWLListaIconos.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLListaIconos.o ../Include/DWLListaIconos.cpp

${OBJECTDIR}/_ext/1926721337/DWLDialogoColores.o: ../Include/DWLDialogoColores.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLDialogoColores.o ../Include/DWLDialogoColores.cpp

${OBJECTDIR}/_ext/810148909/DWLListaEx_Columna.o: ../Include/DWLListaEx/DWLListaEx_Columna.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/810148909
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/810148909/DWLListaEx_Columna.o ../Include/DWLListaEx/DWLListaEx_Columna.cpp

${OBJECTDIR}/_ext/1926721337/DWLArbolEx.o: ../Include/DWLArbolEx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLArbolEx.o ../Include/DWLArbolEx.cpp

${OBJECTDIR}/_ext/1926721337/DWLDirectoriosWindows.o: ../Include/DWLDirectoriosWindows.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLDirectoriosWindows.o ../Include/DWLDirectoriosWindows.cpp

${OBJECTDIR}/_ext/1926721337/DWLListView.o: ../Include/DWLListView.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLListView.o ../Include/DWLListView.cpp

${OBJECTDIR}/_ext/1926721337/DWLFuente.o: ../Include/DWLFuente.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLFuente.o ../Include/DWLFuente.cpp

${OBJECTDIR}/_ext/810148909/DWLListaEx_Item.o: ../Include/DWLListaEx/DWLListaEx_Item.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/810148909
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/810148909/DWLListaEx_Item.o ../Include/DWLListaEx/DWLListaEx_Item.cpp

${OBJECTDIR}/_ext/1926721337/DWLString.o: ../Include/DWLString.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLString.o ../Include/DWLString.cpp

${OBJECTDIR}/_ext/1926721337/DWLRegion.o: ../Include/DWLRegion.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLRegion.o ../Include/DWLRegion.cpp

${OBJECTDIR}/_ext/1740930690/DWLArbolEx_Nucleo.o: ../Include/DWLArbolEx/DWLArbolEx_Nucleo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1740930690
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1740930690/DWLArbolEx_Nucleo.o ../Include/DWLArbolEx/DWLArbolEx_Nucleo.cpp

${OBJECTDIR}/_ext/1926721337/DWLRecta.o: ../Include/DWLRecta.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLRecta.o ../Include/DWLRecta.cpp

${OBJECTDIR}/_ext/1926721337/DWLBarraScrollEx.o: ../Include/DWLBarraScrollEx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLBarraScrollEx.o ../Include/DWLBarraScrollEx.cpp

${OBJECTDIR}/_ext/1926721337/DWLListaEx.o: ../Include/DWLListaEx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLListaEx.o ../Include/DWLListaEx.cpp

${OBJECTDIR}/_ext/1926721337/DWLVentanaErrorGrave.o: ../Include/DWLVentanaErrorGrave.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLVentanaErrorGrave.o ../Include/DWLVentanaErrorGrave.cpp

${OBJECTDIR}/_ext/1926721337/DWLControlEx.o: ../Include/DWLControlEx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLControlEx.o ../Include/DWLControlEx.cpp

${OBJECTDIR}/_ext/1926721337/DWLDialogo.o: ../Include/DWLDialogo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLDialogo.o ../Include/DWLDialogo.cpp

${OBJECTDIR}/_ext/1926721337/DWLMedidasSistema.o: ../Include/DWLMedidasSistema.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLMedidasSistema.o ../Include/DWLMedidasSistema.cpp

${OBJECTDIR}/_ext/1926721337/DWLhDC.o: ../Include/DWLhDC.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLhDC.o ../Include/DWLhDC.cpp

${OBJECTDIR}/_ext/1926721337/DWLBrocha.o: ../Include/DWLBrocha.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLBrocha.o ../Include/DWLBrocha.cpp

${OBJECTDIR}/_ext/810148909/DWLListaEx_Nucleo.o: ../Include/DWLListaEx/DWLListaEx_Nucleo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/810148909
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/810148909/DWLListaEx_Nucleo.o ../Include/DWLListaEx/DWLListaEx_Nucleo.cpp

${OBJECTDIR}/_ext/1926721337/DWLDialogoGuardar.o: ../Include/DWLDialogoGuardar.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLDialogoGuardar.o ../Include/DWLDialogoGuardar.cpp

${OBJECTDIR}/_ext/1740930690/DWLArbolEx_Nodo.o: ../Include/DWLArbolEx/DWLArbolEx_Nodo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1740930690
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1740930690/DWLArbolEx_Nodo.o ../Include/DWLArbolEx/DWLArbolEx_Nodo.cpp

${OBJECTDIR}/_ext/1926721337/DWLDialogoAbrir.o: ../Include/DWLDialogoAbrir.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLDialogoAbrir.o ../Include/DWLDialogoAbrir.cpp

${OBJECTDIR}/_ext/1926721337/DWLTreeView.o: ../Include/DWLTreeView.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLTreeView.o ../Include/DWLTreeView.cpp

${OBJECTDIR}/_ext/1926721337/DWLEdicionDesplegableEx.o: ../Include/DWLEdicionDesplegableEx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLEdicionDesplegableEx.o ../Include/DWLEdicionDesplegableEx.cpp

${OBJECTDIR}/_ext/1926721337/DWLPluma.o: ../Include/DWLPluma.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLPluma.o ../Include/DWLPluma.cpp

${OBJECTDIR}/_ext/1926721337/DWLToolTipEx.o: ../Include/DWLToolTipEx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLToolTipEx.o ../Include/DWLToolTipEx.cpp

${OBJECTDIR}/_ext/1926721337/DWLDialogoFuentes.o: ../Include/DWLDialogoFuentes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLDialogoFuentes.o ../Include/DWLDialogoFuentes.cpp

${OBJECTDIR}/_ext/1926721337/DWLExplorarDirectorios.o: ../Include/DWLExplorarDirectorios.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLExplorarDirectorios.o ../Include/DWLExplorarDirectorios.cpp

${OBJECTDIR}/_ext/1926721337/DWLVentana.o: ../Include/DWLVentana.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLVentana.o ../Include/DWLVentana.cpp

${OBJECTDIR}/_ext/1926721337/DWLControl.o: ../Include/DWLControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLControl.o ../Include/DWLControl.cpp

${OBJECTDIR}/_ext/1926721337/DWLDebug.o: ../Include/DWLDebug.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLDebug.o ../Include/DWLDebug.cpp

${OBJECTDIR}/_ext/1325267438/DWLBarraEx_Nucleo.o: ../Include/DWLBarraEx/DWLBarraEx_Nucleo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1325267438
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1325267438/DWLBarraEx_Nucleo.o ../Include/DWLBarraEx/DWLBarraEx_Nucleo.cpp

${OBJECTDIR}/_ext/1926721337/DWLVentanaMDIChild.o: ../Include/DWLVentanaMDIChild.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLVentanaMDIChild.o ../Include/DWLVentanaMDIChild.cpp

${OBJECTDIR}/_ext/1926721337/DWLVentanaMDI.o: ../Include/DWLVentanaMDI.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLVentanaMDI.o ../Include/DWLVentanaMDI.cpp

${OBJECTDIR}/_ext/1926721337/DWLMarcaEx.o: ../Include/DWLMarcaEx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLMarcaEx.o ../Include/DWLMarcaEx.cpp

${OBJECTDIR}/_ext/1926721337/DWLBarraEx.o: ../Include/DWLBarraEx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLBarraEx.o ../Include/DWLBarraEx.cpp

${OBJECTDIR}/_ext/1926721337/DWLDialogoDirectorios.o: ../Include/DWLDialogoDirectorios.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLDialogoDirectorios.o ../Include/DWLDialogoDirectorios.cpp

${OBJECTDIR}/_ext/1926721337/DWLEdicionEx.o: ../Include/DWLEdicionEx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLEdicionEx.o ../Include/DWLEdicionEx.cpp

${OBJECTDIR}/_ext/1926721337/DWLMapaBits.o: ../Include/DWLMapaBits.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLMapaBits.o ../Include/DWLMapaBits.cpp

${OBJECTDIR}/_ext/1854159114/DWLEstilos_Fuente.o: ../Include/DWLEstilos/DWLEstilos_Fuente.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1854159114
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1854159114/DWLEstilos_Fuente.o ../Include/DWLEstilos/DWLEstilos_Fuente.cpp

${OBJECTDIR}/_ext/1926721337/DWLDialogoImpresoras.o: ../Include/DWLDialogoImpresoras.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLDialogoImpresoras.o ../Include/DWLDialogoImpresoras.cpp

${OBJECTDIR}/_ext/922689162/DWLBotonEx_Nucleo.o: ../Include/DWLBotonEx/DWLBotonEx_Nucleo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/922689162
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/922689162/DWLBotonEx_Nucleo.o ../Include/DWLBotonEx/DWLBotonEx_Nucleo.cpp

${OBJECTDIR}/_ext/1926721337/DWLMenuEx.o: ../Include/DWLMenuEx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLMenuEx.o ../Include/DWLMenuEx.cpp

${OBJECTDIR}/_ext/153108404/DWLMarcaEx_Nucleo.o: ../Include/DWLMarcaEx/DWLMarcaEx_Nucleo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/153108404
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/153108404/DWLMarcaEx_Nucleo.o ../Include/DWLMarcaEx/DWLMarcaEx_Nucleo.cpp

${OBJECTDIR}/_ext/1926721337/DWLBotonEx.o: ../Include/DWLBotonEx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLBotonEx.o ../Include/DWLBotonEx.cpp

${OBJECTDIR}/_ext/1926721337/DWLAplicacion.o: ../Include/DWLAplicacion.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLAplicacion.o ../Include/DWLAplicacion.cpp

${OBJECTDIR}/_ext/1926721337/DWLEstilos.o: ../Include/DWLEstilos.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926721337
	${RM} $@.d
	$(COMPILE.cc) -O3 -DUNICODE -D_UNICODE -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1926721337/DWLEstilos.o ../Include/DWLEstilos.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} ../Lib/DWL.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
