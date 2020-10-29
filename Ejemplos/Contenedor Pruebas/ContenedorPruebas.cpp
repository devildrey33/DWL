// Aplicacion pensada para testear memory leaks en controles
// Consiste en crear el control elegido dinamicamente y testear la memoria que usa.

#include "stdafx.h"
#include "VentanaMain.h"
#include "..\..\Include\DWLAplicacion.h"

using namespace DWL;

class ContenedorPruebasApp : public DWLAplicacion {
 public :
				ContenedorPruebasApp(void) {};
			   ~ContenedorPruebasApp(void) {};
  const BOOL	Inicio(void) {
					Ventana.Crear();
					return TRUE;
				};
 protected :
  VentanaMain	Ventana;
};



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    DWL::DWL_Iniciar<ContenedorPruebasApp> Aplicacion;
    return Aplicacion.Ejecutar();
}
