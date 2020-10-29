#include "StdAfx.h"
#include "VentanaMain.h"
#include "..\..\Include\DWLString.h"
//#include "..\..\Include\DWLPortaPapeles.h"

#define ID_MAS20ITEMS       1000
#define ID_AGREGARCOLUMNA   1001
#define ID_BORRARCOLUMNA    1002
#define ID_BORRARITEMS      1003
#define ID_SCROLLVVISIBLE   1004
#define ID_SCROLLHVISIBLE   1005
#define ID_FUENTES          1006
#define ID_TRANSPARENCIAS   1007
#define ID_AGREGARBOTON     1008
#define ID_ELIMINARBOTON    1009

#define ID_LISTA1 3366

VentanaMain::VentanaMain(void) {
}

VentanaMain::~VentanaMain(void) {
}

void VentanaMain::Crear(void) {

    Tahoma13.Crear(TEXT("Tahoma"), 13);
    Courier16.Crear(TEXT("Courier New"), 16);
    Comic21.Crear(TEXT("Comic sans"), 21);


	CrearVentana(NULL, TEXT("Ejemplo"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, TEXT("Ejemplo ListaEx"), DWL_CENTRADO, DWL_CENTRADO, 430, 380, NULL);
	Lista.CrearListaEx(WS_CHILD, hWnd(), 10, 110, 395, 225, ID_LISTA1, true/*, DWL::Enums::Filas_Horizontal*/);

    Boton_Mas20Items.CrearBotonEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("+ 20 items"), 10, 10, 65, 20, ID_MAS20ITEMS);
    Boton_BorrarItems.CrearBotonEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("Borrar items"), 80, 10, 70, 20, ID_BORRARITEMS);
    Boton_AgregarColumna.CrearBotonEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("+ Columna"), 155, 10, 65, 20, ID_AGREGARCOLUMNA);
    Boton_BorrarColumna.CrearBotonEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("- Columna"), 225, 10, 65, 20, ID_BORRARCOLUMNA);

    Boton_AgregarBoton.CrearBotonEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("Agregar boton scroll"), 10, 35, 110, 20, ID_AGREGARBOTON);
    Boton_EliminarBoton.CrearBotonEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("Eliminar boton scroll"), 125, 35, 110, 20, ID_ELIMINARBOTON);

    Combo_ScrollV.CrearEdicionDesplegableEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("ScrollV Autom�tico"), 10, 60, 120, 20, 60, ID_SCROLLVVISIBLE, false);
    Combo_ScrollV.AgregarItem(TEXT("ScrollV Autom�tico"));
    Combo_ScrollV.AgregarItem(TEXT("ScrollV Visible"));
    Combo_ScrollV.AgregarItem(TEXT("ScrollV Invisible"));
    Combo_ScrollV.FinAgregarItems();
    Combo_ScrollH.CrearEdicionDesplegableEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("ScrollH Autom�tico"), 135, 60, 120, 20, 60, ID_SCROLLHVISIBLE, false);
    Combo_ScrollH.AgregarItem(TEXT("ScrollH Autom�tico"));
    Combo_ScrollH.AgregarItem(TEXT("ScrollH Visible"));
    Combo_ScrollH.AgregarItem(TEXT("ScrollH Invisible"));
    Combo_ScrollH.FinAgregarItems();
    Combo_Fuentes.CrearEdicionDesplegableEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("Tahoma 13px"), 10, 85, 120, 20, 60, ID_FUENTES, false);
    Combo_Fuentes.AgregarItem(TEXT("Tahoma 13px"));
    Combo_Fuentes.AgregarItem(TEXT("Courier new 16px"));
    Combo_Fuentes.AgregarItem(TEXT("Comic sans 21px"));
    Combo_Fuentes.FinAgregarItems();


    Marca_Transparencias.CrearMarcaEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("Transparencias"), 260, 60, ID_TRANSPARENCIAS, true);

/*	Lista.AgregarColumna(90);
	Lista.AgregarColumna(50);
	Lista.MostrarToolTip(true);
//	DWL::SO::DWLPortaPapeles::AsignarTexto(TEXT("hola"));
	DWL::DWLString Txt; //= DWL::SO::DWLPortaPapeles::ObtenerTexto(_hWnd);
	for (unsigned int z = 0; z < 400; z++) {
		Txt.sprintf(TEXT("Item %d"), z + 1);
		Lista.AgregarItem(0, 0, DWL_LISTAEX_FIN, Txt(), TEXT("Subitem"));
	}
	
	Lista.FinAgregarItems();*/
	Lista.Visible(true);
}

LRESULT VentanaMain::Evento_Cerrar(void) {
	PostQuitMessage(0);
	return 0;
}

LRESULT VentanaMain::Evento_ListaEx_Mouse_Click(const UINT Boton, const int cX, const int cY, DWL::ControlesEx::DWLListaEx_Item *nItem, const UINT IDListaEx) {
	if (Boton == 1) Lista.EmpezarLabelEdit(Lista.ItemMarcado(), Lista.SubItemResaltado(), false);
    return 0;
}

/*LRESULT CALLBACK VentanaMain::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		ENLACE_Evento_Cerrar();
		ENLACE_ListaEx_Evento_Mouse_Click();
		ENLACE_Evento_CambioTam();
	}
	return DWLVentana::GestorMensajes(uMsg, wParam, lParam);
}*/

LRESULT VentanaMain::Evento_CambiandoTam(const UINT Lado, RECT *Rectangulo) {
    RECT R;
    GetClientRect(_hWnd, &R);
	Lista.Mover(10, 10, R.right - 40, R.bottom - 50, true);
    return 0;
}


LRESULT VentanaMain::Evento_ListaEx_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDListView) {
    if (TeclaVirtual == VK_DELETE) Lista.EliminarItemsSeleccionados(true);
    return 0;
}

LRESULT VentanaMain::Evento_BotonEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDBotonEx, const UINT Param) { 
	DWL::DWLString Txt;
	switch (IDBotonEx) {
		case ID_AGREGARCOLUMNA :
			Lista.AgregarColumna(100, 0, TEXT("Columna"));
			break;
		case ID_BORRARCOLUMNA :
			Lista.EliminarColumna(Lista.TotalColumnas() - 1);
			break;
		case ID_MAS20ITEMS :
			for (size_t mi = 20; mi > 0; mi --)	{
				Txt.sprintf(TEXT("Item %d"), mi);
				Lista.AgregarItem(NULL, 0, -1, Txt());
			}
			break;
        case ID_AGREGARBOTON :
            Lista.BarraScrollEx_AgregarBotonV(0, IDBotonesScroll);
	        Lista.BarraScrollEx_AgregarBotonH(0, IDBotonesScroll);
            IDBotonesScroll ++;
            break;
        case ID_ELIMINARBOTON :
            Lista.BarraScrollEx_EliminarBotonesH();
            Lista.BarraScrollEx_EliminarBotonesV();
			IDBotonesScroll = 0;
            break;
	}
    Lista.ActualizarTodo(true);
	return 0;
};

LRESULT VentanaMain::Evento_MarcaEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDMarcaEx) { 
	return 0;
};

LRESULT VentanaMain::Evento_EdicionDesplegableEx_CambioSeleccion(const TCHAR *NuevoTexto, const UINT IDEdicionTexto) { 
    DWL::DWLString Comparacion = NuevoTexto;
    switch (IDEdicionTexto) {
        case ID_SCROLLVVISIBLE :
            if (Comparacion == TEXT("ScrollV Autom�tico"))  Lista.BarraScrollEx_VisibleV(DWL_BARRASCROLLEX_AUTOMATICO);
            if (Comparacion == TEXT("ScrollV Visible"))     Lista.BarraScrollEx_VisibleV(TRUE);
            if (Comparacion == TEXT("ScrollV Invisible"))   Lista.BarraScrollEx_VisibleV(FALSE);
            break;
        case ID_SCROLLHVISIBLE :
            if (Comparacion == TEXT("ScrollH Autom�tico"))  Lista.BarraScrollEx_VisibleH(DWL_BARRASCROLLEX_AUTOMATICO);
            if (Comparacion == TEXT("ScrollH Visible"))     Lista.BarraScrollEx_VisibleH(TRUE);
            if (Comparacion == TEXT("ScrollH Invisible"))   Lista.BarraScrollEx_VisibleH(FALSE);
            break;
        case ID_FUENTES :
            if (Comparacion == TEXT("Tahoma 13px"))         Lista.ListaEx_Estilos.Fuentes.Enlazar(Tahoma13); 
            if (Comparacion == TEXT("Courier new 16px"))    Lista.ListaEx_Estilos.Fuentes.Enlazar(Courier16); 
            if (Comparacion == TEXT("Comic sans 21px"))     Lista.ListaEx_Estilos.Fuentes.Enlazar(Comic21); 
            Lista.ListaEx_ActualizarTamTexto();
            break;
    }
    Lista.ActualizarTodo(true);
    return 0;
};
