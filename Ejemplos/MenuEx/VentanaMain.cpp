#include "StdAfx.h"
#include "VentanaMain.h"
#include "resource.h"

#define ID_MENU1	3366
#define ID_MENU2	3367
#define ID_SUBMENU1 3368
#define ID_SUBMENU2 3369

VentanaMain::VentanaMain(void) {
	Crear();
}

VentanaMain::~VentanaMain(void) {
}

void VentanaMain::Crear(void) {
	CrearVentana(NULL, TEXT("Ejemplo"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, TEXT("Ejemplo MenuEx"), DWL_CENTRADO, DWL_CENTRADO, 207, 205, NULL);
	Menu.Texto(TEXT("Menu de ejemplo"));
	Menu.AgregarMenu(ID_MENU1, TEXT("Menu1"), IDI_ICON1);
	DWL::ControlesEx::DWLMenuEx *SubMenu = Menu.AgregarMenu(ID_MENU2, TEXT("Menu2"), IDI_ICON2);
	SubMenu->AgregarMenu(ID_SUBMENU1, TEXT("SubMenu1"), IDI_ICON3);
	SubMenu->AgregarMenu(ID_SUBMENU2, TEXT("SubMenu2"), NULL);
}

LRESULT VentanaMain::Evento_Cerrar(void) {
	PostQuitMessage(0);
	return 0;
}

LRESULT VentanaMain::Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param) {
	if (Boton == 1) Menu.MostrarMenuEx(_hWnd, true);
    return 0;
}

/*LRESULT CALLBACK VentanaMain::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		ENLACE_Evento_Cerrar();
		ENLACE_Evento_Mouse_BotonSoltado();
		ENLACE_MenuEx_Evento_Menu_Pulsado();
	}
	return DWLVentana::GestorMensajes(uMsg, wParam, lParam);
}*/

LRESULT VentanaMain::Evento_MenuEx_Menu_Pulsado(DWL::ControlesEx::DWLMenuEx *MenuPulsado, const UINT IDMenuExPadre) {
//	Menu.OcultarTodo();
	DWL::DWLString Txt = TEXT("Menu Pulsado : ");
	Txt += MenuPulsado->Texto();
	MessageBox(_hWnd, Txt(), TEXT("Ejemplo"), MB_OK);
    return 0;
}
