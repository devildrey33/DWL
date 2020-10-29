#include "StdAfx.h"
#include "VentanaMain.h"

#define ID_BOTON1 3366
#define ID_BOTON2 3367

VentanaMain::VentanaMain(void) {
}

VentanaMain::~VentanaMain(void) {
}

void VentanaMain::Crear(void) {
	CrearVentana(NULL, TEXT("Ejemplo"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, TEXT("Ejemplo BotonEx"), DWL_CENTRADO, DWL_CENTRADO, 210, 100, NULL);
	Boton1.CrearBotonEx(WS_CHILD | WS_VISIBLE, hWnd(), TEXT("Boton 1"), 10, 20, 80, 18, ID_BOTON1); 
	Boton2.CrearBotonEx(WS_CHILD | WS_VISIBLE, hWnd(), TEXT("Boton 2"), 105, 20, 80, 18, ID_BOTON2); 
}

LRESULT VentanaMain::Evento_Cerrar(void) {
	PostQuitMessage(0);
	return 0;
}

/*LRESULT CALLBACK VentanaMain::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		ENLACE_Evento_Cerrar();
		ENLACE_BotonEx_Evento_Mouse_Click();
	}
	return DWLVentana::GestorMensajes(uMsg, wParam, lParam);
}*/

LRESULT VentanaMain::Evento_BotonEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDBotonEx, const UINT Param) {
	if (IDBotonEx == ID_BOTON1)	MessageBox(hWnd(), TEXT("Boton Presionado!"), TEXT("Info"), MB_OK);
	else						Boton2.Marcado(!Boton2.Marcado());
    return 0;
}
