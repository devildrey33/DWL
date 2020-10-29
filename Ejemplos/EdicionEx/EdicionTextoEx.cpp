// EdicionTextoEx.cpp: define el punto de entrada de la aplicación.
//

#include "stdafx.h"
#include "EdicionTextoEx.h"

#include "VentanaMain.h"
#include "..\..\Include\DWLAplicacion.h"

class EdicionTextoApp : public DWL::DWLAplicacion {
 public :
				EdicionTextoApp(void) {};
			   ~EdicionTextoApp(void) {};
 const BOOL		Inicio(void) {
					Ventana.Crear();
					return TRUE;
				};
 protected :
 VentanaMain	Ventana;
};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    DWL::DWL_Iniciar<EdicionTextoApp> Aplicacion;
    return Aplicacion.Ejecutar();
}
