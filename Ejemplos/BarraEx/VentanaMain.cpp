#include "StdAfx.h"
#include "VentanaMain.h"
#include "resource.h"

#define ID_BARRA1 3366
#define ID_BARRA2 3367

VentanaMain::VentanaMain(void) {
}

VentanaMain::~VentanaMain(void) {
}

void VentanaMain::Crear(void) {
    HWND hWndDlg = CrearDialogo(IDD_DIALOG1, 100, 100);
//	CrearVentana(NULL, TEXT("Ejemplo"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, TEXT("Ejemplo BarraEx"), DWL_CENTRADO, DWL_CENTRADO, 250, 200, NULL);
    Barra1.ConectarBarraEx(_hWnd, IDC_CUSTOM1, DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL, 0, 1000);
    Barra2.ConectarBarraEx(_hWnd, IDC_CUSTOM2, DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL, 0, 1000);
//	Barra1.CrearBarraEx(WS_CHILD | WS_VISIBLE, hWnd(), 10, 10, 170, 8, ID_BARRA1, DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL, 0, 1000, 1); 
//	Barra2.CrearBarraEx(WS_CHILD | WS_VISIBLE, hWnd(), 10, 20, 8, 140, ID_BARRA2, DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL, 0, 1000, 1); 
    Visible(true);
}

BOOL VentanaMain::Evento_Cerrar(void) {
	PostQuitMessage(0);
	return 0;
}

/*LRESULT CALLBACK VentanaMain::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		ENLACE_Evento_Cerrar();
	}
	return DWLVentana::GestorMensajes(uMsg, wParam, lParam);
}*/
