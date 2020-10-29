#include "StdAfx.h"
#include "VentanaMain.h"
#include "..\..\Include\DWLListaIconos.h"

#define ID_ARBOL1 3366

#define ID_COMBOCONTROLES	3367
#define ID_BOTONCREAR		3368
#define ID_BOTONDESTRUIR	3369
#define ID_BOTONREPINTAR	3370
#define ID_CONTROL			3371

using namespace DWL;
using namespace DWL::ControlesEx;

VentanaMain::VentanaMain(void) {
//	ObjetosGDI = 0;
//	ObjetosUsuario = 0;
//	Crear();
}

VentanaMain::~VentanaMain(void) {
}

void VentanaMain::Crear(void) {
	CrearVentana(NULL, TEXT("Ejemplo"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, TEXT("Contenedor de Pruebas"), DWL_CENTRADO, DWL_CENTRADO, 400, 320, NULL);

	ComboControles.Crear(WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, _hWnd, TEXT(""), 10, 10, 100, 200, ID_COMBOCONTROLES);
	ComboControles.AgregarItem(TEXT("ArbolEx"));
	ComboControles.AgregarItem(TEXT("BarraEx"));
	ComboControles.AgregarItem(TEXT("BotonEx"));
	ComboControles.AgregarItem(TEXT("EdicionTextoEx"));
	ComboControles.AgregarItem(TEXT("MarcaEx"));
	ComboControles.AgregarItem(TEXT("ListaEx"));
	ComboControles.AgregarItem(TEXT("EdicionTextoExpandibleEx"));
	ComboControles.AgregarItem(TEXT("ExplorarDirectorios"));
	ComboControles.AltoLista(240);
	
	BotonCrear.CrearBotonEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("Crear"), 110, 10, 34, 22, ID_BOTONCREAR);
	BotonDestruir.CrearBotonEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("Destruir"), 145, 10, 45, 22, ID_BOTONDESTRUIR);
	BotonRepintar.CrearBotonEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("Repintar"), 191, 10, 50, 22, ID_BOTONREPINTAR);
	
//	ObjetosGDI		= MirarObjetosGDI();
//	ObjetosUsuario	= MirarObjetosUsuario();

//	DWL::DWLString Str;
//	Str.sprintf(TEXT("GDI[%d] ObjetosWnd[%d]"), ObjetosGDI, ObjetosUsuario);
//	Titulo(Str());
	ControlActual = NULL;
	TipoControlActual = Control_NoDefinido;
	CrearTemporizador(100, 200);
//    EditP.EdicionEx_Texto(TEXT("a\nbb\nccc\ndddd"));
}


LRESULT VentanaMain::Evento_Temporizador(const UINT cID) {
	PintarDatos();
    return 0;
}

LRESULT VentanaMain::Evento_BotonEx_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT IDBotonEx, const UINT Param) {
	switch (IDBotonEx) {
		case ID_BOTONCREAR		: CrearControl();		break;
		case ID_BOTONDESTRUIR	: DestruirControl();	break;
		case ID_BOTONREPINTAR	: RepintarControl();	break;
	}
    return 0;
}


void VentanaMain::CrearControl(void) {

	if (ControlActual != NULL) DestruirControl();

//	ObjetosGDI		= MirarObjetosGDI();
//	ObjetosUsuario	= MirarObjetosUsuario();
	size_t z = 0;
	DWL::DWLString Txt;
	ComboControles.ObtenerTexto(Txt);
	if		(Txt == TEXT("ArbolEx"))					TipoControlActual = Control_ArbolEx;
	else if (Txt == TEXT("ListaEx"))					TipoControlActual = Control_ListaEx;
	else if (Txt == TEXT("MarcaEx"))					TipoControlActual = Control_MarcaEx;
	else if (Txt == TEXT("BotonEx"))					TipoControlActual = Control_BotonEx;
	else if (Txt == TEXT("BarraEx"))					TipoControlActual = Control_BarraEx;
	else if (Txt == TEXT("EdicionTextoEx"))				TipoControlActual = Control_EdicionTextoEx;
	else if (Txt == TEXT("EdicionTextoExpandibleEx"))	TipoControlActual = Control_EdicionTextoExpandibleEx;
	else if (Txt == TEXT("ExplorarDirectorios"))		TipoControlActual = Control_ExplorarDirectorios;
	else												TipoControlActual = Control_NoDefinido;

	switch (TipoControlActual) {
		case Control_NoDefinido :
			MessageBox(_hWnd, TEXT("Selecciona un control de la lista"), TEXT("Error creando el control"), MB_OK);
			break;
		case Control_ExplorarDirectorios :
			DWLExplorarDirectorios *TmpExplorarDirectorios;
			ControlActual = new DWLExplorarDirectorios;
			TmpExplorarDirectorios = static_cast<DWLExplorarDirectorios *>(ControlActual);
			TmpExplorarDirectorios->CrearExplorarDirectorios(WS_CHILD, _hWnd, 10, 40, 240, 240, ID_CONTROL, true);
//			TmpExplorarDirectorios->AgregarNodo(NULL, NULL, 0, TEXT("Nodo de prueba"));
//			TmpExplorarDirectorios->FinAgregarNodos();
			TmpExplorarDirectorios->Visible(true);
			break;
		case Control_ArbolEx :
			DWLArbolEx *TmpArbolEx;
//			DWLArbolEx_Nodo *TmpNodo;
			ControlActual = new DWLArbolEx;
			TmpArbolEx = static_cast<DWLArbolEx *>(ControlActual);
			TmpArbolEx->CrearArbolEx(WS_CHILD, _hWnd, 10, 40, 240, 240, ID_CONTROL, true);
			TmpArbolEx->AgregarNodo(NULL, NULL, 0, TEXT("Nodo de prueba"));
			TmpArbolEx->ActualizarTodo();
			TmpArbolEx->Visible(true);
			break;
		case Control_ListaEx :
			DWLListaEx *TmpListaEx;
			ControlActual = new DWL::ControlesEx::DWLListaEx;
			TmpListaEx = static_cast<DWL::ControlesEx::DWLListaEx *>(ControlActual);
			TmpListaEx->CrearListaEx(WS_CHILD, _hWnd, 10, 40, 240, 240, ID_CONTROL, true);
			TmpListaEx->AgregarColumna(200);
/*			TmpListaEx->BarraScrollEx_AgregarBotonH(0, 100);
			TmpListaEx->BarraScrollEx_AgregarBotonH(0, 101);
			TmpListaEx->BarraScrollEx_AgregarBotonH(0, 102);*/
			for (z = 0; z < 20; z ++) TmpListaEx->AgregarItem(NULL, 0, 0, TEXT("Item de prueba"));
			TmpListaEx->FinAgregarItems();
			TmpListaEx->Visible(true);
			break;
		case Control_MarcaEx :
			DWLMarcaEx *TmpMarcaEx;
			ControlActual = new DWLMarcaEx;
			TmpMarcaEx = static_cast<DWLMarcaEx *>(ControlActual);
			TmpMarcaEx->CrearMarcaEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("DWLMarcaEx"), 10, 40, ID_CONTROL);
			break;
		case Control_BotonEx :
			DWL::ControlesEx::DWLBotonEx *TmpBotonEx;
			ControlActual = new DWLBotonEx;
			TmpBotonEx = static_cast<DWLBotonEx *>(ControlActual);
			TmpBotonEx->CrearBotonEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("DWLBotonEx"), 10, 40, 100, 20, ID_CONTROL);
			break;
		case Control_BarraEx :
			DWL::ControlesEx::DWLBarraEx *TmpBarraEx;
			ControlActual = new DWLBarraEx;
			TmpBarraEx = static_cast<DWLBarraEx *>(ControlActual);
			TmpBarraEx->CrearBarraEx(WS_CHILD | WS_VISIBLE, _hWnd, 10, 40, 240, 10, ID_CONTROL, DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL, 0, 1000);
			break;
		case Control_EdicionTextoEx :
			DWLEdicionEx *TmpEdicionTextoEx;
			ControlActual = new DWLEdicionEx;
			TmpEdicionTextoEx = static_cast<DWLEdicionEx *>(ControlActual);
			TmpEdicionTextoEx->CrearEdicionEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("DWLEdicionEx\n\naaaaa\n\nbbb\n"), 10, 40, 240, 240, ID_CONTROL, true);
			break;
		case Control_EdicionTextoExpandibleEx :
			DWLEdicionDesplegableEx *TmpEdicionTextoExpandibleEx;
			ControlActual = new DWLEdicionDesplegableEx;
			TmpEdicionTextoExpandibleEx = static_cast<DWLEdicionDesplegableEx *>(ControlActual);
			TmpEdicionTextoExpandibleEx->CrearEdicionDesplegableEx(WS_CHILD, _hWnd, TEXT("C:\\"), 10, 40, 240, 20, 100, ID_CONTROL, true, 0, Enums::Tipo_BuscarDirectorio);
//			TmpEdicionTextoExpandibleEx->AgregarItem(TEXT("Item de prueba"));
//			TmpEdicionTextoExpandibleEx->FinAgregarItems();
//			TmpEdicionTextoExpandibleEx->Texto(TEXT("DWLEdicionTextoDesplegableEx"), false);
			TmpEdicionTextoExpandibleEx->Visible(true);
			break;
	}
	PintarDatos();
}

void VentanaMain::DestruirControl(void) {
	switch (TipoControlActual) {
		case Control_ArbolEx					: delete static_cast<DWLArbolEx *>(ControlActual);				break;
		case Control_ListaEx					: delete static_cast<DWLListaEx *>(ControlActual);				break;
		case Control_MarcaEx					: delete static_cast<DWLMarcaEx *>(ControlActual);				break;
		case Control_BotonEx					: delete static_cast<DWLBotonEx *>(ControlActual);				break;
		case Control_BarraEx					: delete static_cast<DWLBarraEx *>(ControlActual);				break;
		case Control_EdicionTextoEx				: delete static_cast<DWLEdicionEx *>(ControlActual);			break;
		case Control_EdicionTextoExpandibleEx	: delete static_cast<DWLEdicionDesplegableEx *>(ControlActual);	break;
		case Control_ExplorarDirectorios		: delete static_cast<DWLExplorarDirectorios *>(ControlActual);	break;
	}
	DWL::SO::DWLListaIconos::Borrar();
	ControlActual = NULL;
	TipoControlActual = Control_NoDefinido;

	PintarDatos();
}


void VentanaMain::RepintarControl(void) {
	if (ControlActual != NULL)	RedrawWindow(ControlActual->hWnd(), NULL, NULL, RDW_UPDATENOW | RDW_ERASE);
	PintarDatos();
}


LRESULT VentanaMain::Evento_Cerrar(void) {
	PostQuitMessage(0);
	return 0;
}


LRESULT VentanaMain::Evento_Pintar(HDC hDC, PAINTSTRUCT &PS) {
	RECT R;
	GetClientRect(_hWnd, &R);
	HBRUSH Rojo = CreateSolidBrush(RGB(255,0,0));
	FillRect(hDC, &R, Rojo);
	DeleteObject(Rojo);
	PintarDatos(hDC);

//    EditP.EdicionEx_Pintar(hDC, &R, false, false);
    return 0;
}


void VentanaMain::PintarDatos(HDC hDC) {
	HDC		hDCFinal = hDC;
	bool	DCPropio = false;
	if (hDCFinal == NULL) {
		hDCFinal = GetDC(_hWnd);
		DCPropio = true;
	}
	RECT R;
	GetClientRect(_hWnd, &R);
	R.left = 250;
	HBRUSH Rojo = CreateSolidBrush(RGB(255,0,0));
	FillRect(hDCFinal, &R, Rojo);
	DeleteObject(Rojo);

//	FillRect(hDCFinal, &R, static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH)));

//	ObjetosGDI		= MirarObjetosGDI();
//	ObjetosUsuario	= MirarObjetosUsuario();
	
	DWLString Str;
	SetBkColor(hDCFinal, RGB(255,0,0));
	SetTextColor(hDCFinal, RGB(0,0,0));
//	TextOut(hDCFinal, 250, 10, TEXT("Datos iniciales :"), 31);
//	Str.sprintf(TEXT(" ObjetosGDI = %d"), ObjetosGDI);
//	TextOut(hDCFinal, 250, 30, Str(), Str.Tam());
//	Str.sprintf(TEXT(" ObjetosUsuario = %d"), ObjetosUsuario);
//	TextOut(hDCFinal, 250, 50, Str(), Str.Tam());
	TextOut(hDCFinal, 250, 70, TEXT("Datos actuales :"), 16);
	Str.sprintf(TEXT(" ObjetosGDI = %d"), MirarObjetosGDI());
	TextOut(hDCFinal, 250, 90, Str(), Str.Tam());
	Str.sprintf(TEXT(" ObjetosUsuario = %d"), MirarObjetosUsuario());
	TextOut(hDCFinal, 250, 110, Str(), Str.Tam());
	

	if (DCPropio == true) ReleaseDC(_hWnd, hDCFinal);
}

/*LRESULT CALLBACK VentanaMain::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		ENLACE_Evento_Cerrar();
		ENLACE_BotonEx_Evento_Mouse_Click();
		ENLACE_Evento_Pintar();
		ENLACE_Evento_Temporizador();
		ENLACE_Evento_CambioTam();
	}
	return DWLVentana::GestorMensajes(uMsg, wParam, lParam);
}*/


const DWORD VentanaMain::MirarObjetosGDI(void) {
#if (COMPILADOR == COMPILADOR_VC6) 
	return 0; // Funcion no soportada en VisualC6
#else
	return GetGuiResources(GetCurrentProcess(), GR_GDIOBJECTS);
#endif
}


const DWORD VentanaMain::MirarObjetosUsuario(void) {
#if (COMPILADOR == COMPILADOR_VC6) 
	return 0; // Funcion no soportada en VisualC6
#else
	return GetGuiResources(GetCurrentProcess(), GR_USEROBJECTS);
#endif
}


LRESULT VentanaMain::Evento_CambiandoTam(const UINT Lado, RECT *Rectangulo) {
	switch (TipoControlActual) {
		case Control_ArbolEx					: static_cast<DWLArbolEx *>(ControlActual)->Mover(10, 50, Rectangulo->right - 240, Rectangulo->bottom - 60, true);		        	break;
		case Control_ListaEx					: static_cast<DWLListaEx *>(ControlActual)->Mover(10, 50, Rectangulo->right - 240, Rectangulo->bottom - 60, true);					break;
		case Control_MarcaEx					: static_cast<DWLMarcaEx *>(ControlActual)->Mover(10, 50, Rectangulo->right - 240, Rectangulo->bottom - 60, true);					break;
		case Control_BotonEx					: static_cast<DWLBotonEx *>(ControlActual)->Mover(10, 50, Rectangulo->right - 240, Rectangulo->bottom - 60, true);					break;
		case Control_BarraEx					: static_cast<DWLBarraEx *>(ControlActual)->Mover(10, 50, Rectangulo->right - 240, Rectangulo->bottom - 60, true);					break;
		case Control_EdicionTextoEx				: static_cast<DWLEdicionEx *>(ControlActual)->Mover(10, 50, Rectangulo->right - 240, Rectangulo->bottom - 60, true);				break;
		case Control_EdicionTextoExpandibleEx	: static_cast<DWLEdicionDesplegableEx *>(ControlActual)->Mover(10, 50, Rectangulo->right - 240, Rectangulo->bottom - 60, true);	    break;
		case Control_ExplorarDirectorios		: static_cast<DWLExplorarDirectorios *>(ControlActual)->Mover(10, 50, Rectangulo->right - 240, Rectangulo->bottom - 60, true);		break;
	}
    return 0;
}