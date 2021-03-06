// MarcaEx.cpp: define el punto de entrada de la aplicación.
//

#include "stdafx.h"
#include "MarcaEx.h"

#include "VentanaMain.h"
#include "..\..\Include\DWLAplicacion.h"


class MarcaExApp : public DWL::DWLAplicacion {
public:
				MarcaExApp(void) { };
	           ~MarcaExApp(void) { };
	const BOOL  Inicio(void) {
					Ventana.Crear();
					return TRUE;
				};
protected:
	VentanaMain Ventana;
};


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    DWL::DWL_Iniciar<MarcaExApp> AppListaEx;
    return AppListaEx.Ejecutar();
}
