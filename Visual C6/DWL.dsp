# Microsoft Developer Studio Project File - Name="DWL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=DWL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DWL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DWL.mak" CFG="DWL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DWL - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "DWL - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DWL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0xc0a /d "NDEBUG"
# ADD RSC /l 0xc0a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "DWL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0xc0a /d "_DEBUG"
# ADD RSC /l 0xc0a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "DWL - Win32 Release"
# Name "DWL - Win32 Debug"
# Begin Group "SO"

# PROP Default_Filter ""
# Begin Group "Estilos"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\Include\DWLEstilos.cpp"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLEstilos.h"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLEstilos\DWLEstilos_Color.h"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLEstilos\DWLEstilos_Colores.h"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLEstilos\DWLEstilos_Fuente.cpp"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLEstilos\DWLEstilos_Fuente.h"
# End Source File
# End Group
# Begin Source File

SOURCE=..\Include\DWLDirectoriosWindows.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLDirectoriosWindows.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListaIconos.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListaIconos.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLMedidasSistema.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLMedidasSistema.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLMouse.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLPortaPapeles.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLRegistro.h
# End Source File
# End Group
# Begin Group "Ventanas"

# PROP Default_Filter ""
# Begin Group "BaseWnd"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLBarraTareas.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBarraTareas.h
# End Source File
# Begin Source File

SOURCE="..\Include\DWLBaseWnd.cpp"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLBaseWnd.h"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLEventosBase.h"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLEventosPadre.h"
# End Source File
# End Group
# Begin Group "Dialogos comunes"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\Include\DWLDialogoAbrir.cpp"
# End Source File
# Begin Source File

SOURCE=".\Include\DWLDialogoAbrir.h"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLDialogoColores.cpp"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLDialogoColores.h"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLDialogoDirectorios.cpp"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLDialogoDirectorios.h"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLDialogoFuentes.cpp"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLDialogoFuentes.h"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLDialogoGuardar.cpp"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLDialogoGuardar.h"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLDialogoImpresoras.cpp"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLDialogoImpresoras.h"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLDialogosComunes.h"
# End Source File
# End Group
# Begin Source File

SOURCE=..\Include\DWLDialogo.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLDialogo.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLVentana.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLVentana.h
# End Source File
# Begin Source File

SOURCE="..\Include\DWLVentanaErrorGrave.cpp"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLVentanaErrorGrave.h"
# End Source File
# Begin Source File

SOURCE=..\Include\DWLVentanaMDI.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLVentanaMDI.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLVentanaMDIChild.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLVentanaMDIChild.h
# End Source File
# End Group
# Begin Group "Archivos"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLArchivoBinario.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLArchivoLog.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLArchivosWindows.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBusquedaRecursiva.h
# End Source File
# End Group
# Begin Group "Controles"

# PROP Default_Filter ""
# Begin Group "BaseControles"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\Include\DWLControl.cpp"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLControl.h"
# End Source File
# End Group
# Begin Source File

SOURCE=..\Include\DWLComboBox.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLEditBox.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLImageList.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListBox.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListView.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListView.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLMenu.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLStaticText.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLTreeView.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLTreeView.h
# End Source File
# End Group
# Begin Group "ControlesEx"

# PROP Default_Filter ""
# Begin Group "DWLArbolEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLArbolEx.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLArbolEx.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLArbolEx\DWLArbolEx_Colores.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLArbolEx\DWLArbolEx_ColoresNodo.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLArbolEx\DWLArbolEx_Nodo.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLArbolEx\DWLArbolEx_Nodo.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLArbolEx\DWLArbolEx_Nucleo.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLArbolEx\DWLArbolEx_Nucleo.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLArbolEx\DWLArbolEx_ParametrosClick.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLArbolEx\DWLArbolEx_TerminarLabelEdit.h
# End Source File
# End Group
# Begin Group "DWLBarraEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLBarraEx.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBarraEx.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBarraEx\DWLBarraEx_Colores.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBarraEx\DWLBarraEx_Nucleo.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBarraEx\DWLBarraEx_Nucleo.h
# End Source File
# End Group
# Begin Group "DWLBarraScrollEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLBarraScrollEx.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBarraScrollEx.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBarraScrollEx\DWLBarraScrollEx_Boton.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBarraScrollEx\DWLBarraScrollEx_Colores.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBarraScrollEx\DWLBarraScrollEx_ParametrosClick.h
# End Source File
# End Group
# Begin Group "DWLBotonEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLBotonEx.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBotonEx.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBotonEx\DWLBotonEx_Colores.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBotonEx\DWLBotonEx_Nucleo.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBotonEx\DWLBotonEx_Nucleo.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBotonEx\DWLBotonEx_ParametrosClick.h
# End Source File
# End Group
# Begin Group "DWLExplorarDirectorios"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLExplorarDirectorios.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLExplorarDirectorios.h
# End Source File
# End Group
# Begin Group "DWLListaEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLListaEx.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListaEx.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListaEx\DWLListaEx_Colores.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListaEx\DWLListaEx_ColoresColumna.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListaEx\DWLListaEx_ColoresItem.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListaEx\DWLListaEx_Columna.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListaEx\DWLListaEx_Columna.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListaEx\DWLListaEx_DatosSubItem.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListaEx\DWLListaEx_Item.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListaEx\DWLListaEx_Item.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListaEx\DWLListaEx_Nucleo.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListaEx\DWLListaEx_Nucleo.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListaEx\DWLListaEx_ParametrosClick.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLListaEx\DWLListaEx_TerminarLabelEdit.h
# End Source File
# End Group
# Begin Group "DWLMarcaEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLMarcaEx.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLMarcaEx.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLMarcaEx\DWLMarcaEx_Colores.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLMarcaEx\DWLMarcaEx_Nucleo.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLMarcaEx\DWLMarcaEx_Nucleo.h
# End Source File
# End Group
# Begin Group "DWLMenuEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLMenuEx.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLMenuEx.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLMenuEx\DWLMenuEx_Colores.h
# End Source File
# End Group
# Begin Group "DWLToolTipEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLToolTipEx.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLToolTipEx.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLToolTipEx\DWLToolTipEx_Colores.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLToolTipEx\DWLToolTipEx_Objeto.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLToolTipEx\DWLToolTipEx_ObjetoIconoTexto.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLToolTipEx\DWLToolTipEx_ObjetoTextoCaracterIcono.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLToolTipEx\DWLToolTipEx_ObjetoTextoCaracterTexto.h
# End Source File
# End Group
# Begin Group "Base"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\Include\DWLControlEx.cpp"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLControlEx.h"
# End Source File
# End Group
# Begin Group "DWLEdicionEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLEdicionEx.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLEdicionEx.h
# End Source File
# Begin Source File

SOURCE="..\Include\DWLEdicionEx\DWLEdicionEx_Colores.h"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLEdicionEx\DWLEdicionEx_Estilos.h"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLEdicionEx\DWLEdicionEx_Nucleo.cpp"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLEdicionEx\DWLEdicionEx_Nucleo.h"
# End Source File
# Begin Source File

SOURCE="..\Include\DWLEdicionEx\DWLEdicionEx_Objeto.h"
# End Source File
# End Group
# Begin Group "DWLEdicionDesplegableEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLEdicionDesplegableEx.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLEdicionDesplegableEx.h
# End Source File
# End Group
# End Group
# Begin Group "GDI"

# PROP Default_Filter ""
# Begin Group "BaseGDI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLEnumsGDI.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLGraficos.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Include\DWLBrocha.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLBrocha.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLColor.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLFuente.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLFuente.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLhDC.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLhDC.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLIcono.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLIcono.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLMapaBits.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLMapaBits.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLPluma.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLPluma.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLRecta.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLRecta.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLRegion.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLRegion.h
# End Source File
# End Group
# Begin Group "Compiladores"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\Include\Compiladores\DWL_Compilador_MINGW.h"
# End Source File
# Begin Source File

SOURCE="..\Include\Compiladores\DWL_Compilador_MSC1200.h"
# End Source File
# Begin Source File

SOURCE="..\Include\Compiladores\DWL_Compilador_MSC1300.h"
# End Source File
# Begin Source File

SOURCE="..\Include\Compiladores\DWL_Compilador_MSC1400.h"
# End Source File
# Begin Source File

SOURCE="..\Include\Compiladores\DWL_Compilador_MSC1500.h"
# End Source File
# Begin Source File

SOURCE="..\Include\Compiladores\DWL_Compilador_MSC1600.h"
# End Source File
# Begin Source File

SOURCE=..\Include\Compiladores\DWL_ITaskBar.h
# End Source File
# End Group
# Begin Group "Debug"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLDebug.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLDebug.h
# End Source File
# End Group
# Begin Group "String"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\DWLString.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLString.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLString\DWLString_char.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLString\DWLString_char.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLString\DWLString_wchar_t.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLString\DWLString_wchar_t.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Include\DWL.h
# End Source File
# Begin Source File

SOURCE=..\Include\DWLAplicacion.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DWLAplicacion.h
# End Source File
# End Target
# End Project
