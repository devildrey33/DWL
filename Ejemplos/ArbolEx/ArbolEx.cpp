// ArbolEx.cpp: define el punto de	 entrada de la aplicación.
//

#include "stdafx.h"

#include "VentanaMain.h"
#include "..\..\Include\DWLAplicacion.h"


class ArbolExApp : public DWL::DWLAplicacion {
public:
				ArbolExApp(void) { };
	           ~ArbolExApp(void) { };
	const BOOL  Inicio(void) {
					Ventana.Crear();
					return TRUE;
				};
protected:
	VentanaMain Ventana;
};



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    DWL::DWL_Iniciar<ArbolExApp> Aplicacion;
    return Aplicacion.Ejecutar();
}
