#include "StdAfx.h"
#include "VentanaMain.h"

#define ID_EDICION1 3366
#define ID_EDICION2 3367

VentanaMain::VentanaMain(void) {
}

VentanaMain::~VentanaMain(void) {
}

void VentanaMain::Crear(void) {
	CrearVentana(NULL, TEXT("Ejemplo"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, TEXT("Ejemplo EdicionEx"), DWL_CENTRADO, DWL_CENTRADO, 650, 600, NULL);
//	Edit1.CrearEdicionEx(WS_CHILD | WS_VISIBLE, hWnd(), TEXT("Prueba"), 10, 10, 220, 20, ID_EDICION1);
//	Edit1.Destruir();
	Edit1.CrearEdicionEx(WS_CHILD | WS_VISIBLE, hWnd(), TEXT("Prueba"), 10, 10, 620, 20, ID_EDICION1);
//	Edit2.CrearEdicionEx(WS_CHILD | WS_VISIBLE, hWnd(), TEXT("0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15 FIN TEXTO"), 10, 50, 220, 100, ID_EDICION2, true, true);
	Edit2.CrearEdicionEx(WS_CHILD | WS_VISIBLE, hWnd(), TEXT("FIN TEXTO\nFIN TEXTO2\nFIN TEXTO2\nFIN TEXTO2\nFIN TEXTO2\nFIN TEXTO2"), 10, 50, 620, 500, ID_EDICION2, true, true);

	DWL::DWLString Txt(TEXT("a\nb\nc"));
	DWL::DWLString z = Txt.Linea(3);
	unsigned int L = Txt.TotalLineas();

//    *(int*)0 = 1;	// Provocamos una violación de acceso para testear el filtro de errores.

}

LRESULT VentanaMain::Evento_Cerrar(void) {
	PostQuitMessage(0);
	return 0;
}
/*
LRESULT CALLBACK VentanaMain::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		ENLACE_Evento_Cerrar();
	}
	return DWLVentana::GestorMensajes(uMsg, wParam, lParam);
}*/

