// ListaEx.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#include "VentanaMain.h"
#include "ListaExApp.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    DWL::DWL_Iniciar<ListaExApp> AppListaEx;
    return AppListaEx.Ejecutar();
}