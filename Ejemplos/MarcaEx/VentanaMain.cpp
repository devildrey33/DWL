#include "StdAfx.h"
#include "VentanaMain.h"

#define ID_MARCA1 3366
#define ID_MARCA2 3367

VentanaMain::VentanaMain(void) {
}

VentanaMain::~VentanaMain(void) {
}

void VentanaMain::Crear(void) {
	CrearVentana(NULL, TEXT("Ejemplo"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, TEXT("Ejemplo MarcaEx"), DWL_CENTRADO, DWL_CENTRADO, 200, 100, NULL);
	Marca1.CrearMarcaEx(WS_CHILD | WS_VISIBLE, hWnd(), TEXT("Marca 1"), 10, 20, ID_MARCA1); 
	Marca2.CrearMarcaEx(WS_CHILD | WS_VISIBLE, hWnd(), TEXT("Marca 2"), 105, 20, ID_MARCA2); 
}

LRESULT VentanaMain::Evento_Cerrar(void) {
	PostQuitMessage(0);
	return 0;
}

/*LRESULT CALLBACK VentanaMain::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		ENLACE_Evento_Cerrar();
		ENLACE_MarcaEx_Evento_Mouse_Click();
	}
	return DWLVentana::GestorMensajes(uMsg, wParam, lParam);
}*/

LRESULT VentanaMain::Evento_MarcaEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDMarcaEx) {
	switch (IDMarcaEx) {
		case ID_MARCA1 :
			Marca1.Marcar(!Marca1.Marcado());
			break;
		case ID_MARCA2 :
			Marca2.Marcar(!Marca2.Marcado());
			break;
	}
    return 0;
}