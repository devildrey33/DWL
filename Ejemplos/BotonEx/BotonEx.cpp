// DWLBotonEx.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "..\..\Include\DWLAplicacion.h"
#include "VentanaMain.h"

class BotonExApp : public DWL::DWLAplicacion {
 public:
             BotonExApp(void) { };
            ~BotonExApp(void) { };
 const BOOL  Inicio(void) {
                 Ventana.Crear();
                 return TRUE;
             };
 VentanaMain Ventana;
};


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    DWL::DWL_Iniciar<BotonExApp> Aplicacion;
    return Aplicacion.Ejecutar();
}