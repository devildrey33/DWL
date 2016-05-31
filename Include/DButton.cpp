#include "stdafx.h"
#include "DButton.h"

namespace DWL {

	//! Función para crear el Button (CreateWindowEx).
	/*! Esta función se usa para crear un Button dinamicamente.
			\fn         HWND Crear(DBaseWnd *nPadre, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, const UINT cID, const DEnum_Button_Tipo TipoBoton);
			\param[in]  nPadre               Clase DBaseWnd que contendra el button.
			\param[in]  nTexto               Texto para el Button.
			\param[in]  cX                   Coordenada X relativa a la ventana padre.
			\param[in]  cY                   Coordenada Y relativa a la ventana padre.
			\param[in]  cAncho               Ancho del Button en pixeles.
			\param[in]  cAlto                Altura del Button en pixeles
			\param[in]  cID                  ID para poder identificar el Button en sus eventos.
			\param[in]  TipoBoton            Tipo de boton, puede ser : DEnum_Button_Tipo_Normal (POR DEFECTO), DEnum_Button_Tipo_PorDefecto, DEnum_Button_Tipo_PushLike, DEnum_Button_Tipo_Split, DEnum_Button_Tipo_SplitPorDefecto, DEnum_Button_Tipo_Link, y DEnum_Button_Tipo_LinkPorDefecto.
			\return     Devuelve el HWND del Button o NULL en caso de error.
	*/
	HWND DButton::Crear(DBaseWnd *nPadre, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, const UINT cID, const DEnum_Button_Tipo TipoBoton) {
		DWORD Estilos = NULL;
		switch (TipoBoton) {
			case DEnum_Button_Tipo_Normal:				Estilos = WS_CHILD | WS_VISIBLE;						break;
			case DEnum_Button_Tipo_PorDefecto:			Estilos = WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON;		break;
			case DEnum_Button_Tipo_PushLike:			Estilos = WS_CHILD | WS_VISIBLE | BS_PUSHLIKE;			break;
			case DEnum_Button_Tipo_Split:				Estilos = WS_CHILD | WS_VISIBLE | BS_SPLITBUTTON;		break;
			case DEnum_Button_Tipo_SplitPorDefecto:		Estilos = WS_CHILD | WS_VISIBLE | BS_DEFSPLITBUTTON;	break;
			case DEnum_Button_Tipo_Link:				Estilos = WS_CHILD | WS_VISIBLE | BS_COMMANDLINK;		break;
			case DEnum_Button_Tipo_LinkPorDefecto:		Estilos = WS_CHILD | WS_VISIBLE | BS_DEFCOMMANDLINK;	break;
		}
		_hWnd = CreateWindowEx(NULL, TEXT("BUTTON"), nTexto, Estilos, cX, cY, cAncho, cAlto, nPadre->hWnd(), reinterpret_cast<HMENU>(IntToPtr(cID)), GetModuleHandle(NULL), this);
		_ConectarControl(cID, nPadre);
		return _hWnd;
	};



	//! Función para asignar esta clase a un Button de un dialogo.
	/*! Esta función se usa para asignar esta clase a un Button de un dialogo.
			\fn         HWND Asignar(DBaseWnd *Padre, const UINT cID);
			\param[in]  nPadre      Clase DBaseWnd que contendra el button.
			\param[in]  cID         ID para poder identificar el Button en sus eventos.
			\return     Devuelve el HWND del Button o NULL en caso de error.
			\remarks    Esta función solo debe utilizarse si tenemos un Button en un dialogo de los recursos.
	*/
	HWND DButton::Asignar(DBaseWnd *nPadre, const UINT cID) {
		_hWnd = GetDlgItem(nPadre->hWnd(), cID);
		_ConectarControl(cID, nPadre);
		return _hWnd;
	};

	//! Función para asignar el texto del button.
	/*! Esta función se usa para asignar el texto del button.
			\fn         void AsignarTexto(const TCHAR *nTexto);
			\param[in]  nTexto   Nuevo texto para el button.
			\return     No devuelve nada.
			\sa         ObtenerTexto().
	*/
	void DButton::AsignarTexto(const TCHAR *nTexto) {
		SetDlgItemText(GetParent(_hWnd), static_cast<int>(GetWindowLongPtr(_hWnd, GWL_ID)), nTexto);
	}

	//! Función para obtener el texto del button.
	/*! Esta función se usa para obtener el texto del button.
			\fn         void ObtenerTexto(std::wstring &nTexto);
			\param[out] nTexto   Clase DString donde se almacenara el texto del button.
			\return     No devuelve nada.
			\sa         AsignarTexto().
	*/
	void DButton::ObtenerTexto(std::wstring &nTexto) {
		static TCHAR Buffer[1024];
		GetDlgItemText(GetParent(_hWnd), static_cast<int>(GetWindowLongPtr(_hWnd, GWL_ID)), Buffer, 1024);
		nTexto = Buffer;
	}
}