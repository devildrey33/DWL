// BarraEx.cpp: define el punto de entrada de la aplicación.
//

#include "stdafx.h"
#include "BarraEx.h"

#include "VentanaMain.h"
#include "..\..\include\DWLAplicacion.h"

class BarraExApp : public DWL::DWLAplicacion {
public:
				BarraExApp(void) { };
	           ~BarraExApp(void) { };
	const BOOL  Inicio(void) { 
					Ventana.Crear();
					return TRUE; 
				};
	VentanaMain Ventana;

};


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    DWL::DWL_Iniciar<BarraExApp> Aplicacion;
    return Aplicacion.Ejecutar();
}
