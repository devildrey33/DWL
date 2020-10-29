// EdicionTextoEx.cpp: define el punto de entrada de la aplicaci�n.
//

#include "stdafx.h"

#include "..\..\Include\DWLAplicacion.h"
#include "..\..\Include\DWLVentanaErrorGrave.h"

class VErrorGrave : public DWL::Ventanas::DWLVentanaErrorGrave {
 public :
                VErrorGrave(void) { };
               ~VErrorGrave(void) { };
//     LRESULT    Evento_Pintar(HDC hDC, PAINTSTRUCT &PS) { return 0; };
};

class ErrorGraveApp : public DWL::DWLAplicacion {
 public :
				ErrorGraveApp(void) {};
			   ~ErrorGraveApp(void) {};
 const BOOL		Inicio(void) {
                    VErrorGrave MiVentanaError;
                    AsignarVentanaErrorGrave(&MiVentanaError);
                    #if defined _DEBUG // En modo DEBUG mostramos la ventana directamente para ver su colocacion
                        MostrarExcepcionGrave(NULL);
                    #else              // En modo RELEASE provocamos una violacion de acceso para que se muestre todo correctamente 
                                       // (SOLO FUNCIONARA DESDE FUERA DEL COMPILADOR, DESDE EL COMPILADOR NOS MOSTRARA HERRAMIENTAS DE DEPURACION)
                        ErrorGraveApp *ErrorBestia = NULL;
                        ErrorBestia->Inicio();
                    #endif
					return FALSE;
				};
 protected :
};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    DWL::DWL_Iniciar<ErrorGraveApp> Aplicacion;
    return Aplicacion.Ejecutar();
}
