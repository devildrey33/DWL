#include "stdafx.h"
#include "DControlEstandard.h"
#include <assert.h>
#include "DDebug.h"

namespace DWL {


	//! Constructor.
	/*! Constructor.
			\fn			DControlEstandard(void);
			\return		No devuelve nada.
			*/
	DControlEstandard::DControlEstandard(void) : DBaseWnd(), _GestorMensajesOriginal(NULL) { };

	//! Destructor.
	/*! Destructor.
			\fn		   ~DControlEstandard(void);
			\return		No devuelve nada.
			*/
	DControlEstandard::~DControlEstandard(void) {
		Destruir();
	};



	//! Funci�n que crea un control NO estandard.
	/*!	Esta funci�n crea un control NO estandard y lo enlaza con la DWL.
			\fn			HWND CrearControl(DBaseWnd *nPadre, const TCHAR *nNombre, UINT nEstilos, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, const UINT nID, DWORD nEstiloExtendido = NULL, HBRUSH nColorFondo = NULL);
			\param[in]	nPadre				: Objeto DBaseWnd que representa el padre para este control.
			\param[in]	nNombre				: Nombre para la clase ventana.
			\param[in]	nEstilos			: Estilos validos para controles (WS_CHILD | WS_VISIBLE).
			\param[in]	nTexto				: Texto para el control.
			\param[in]	cX					: Posicion X. Puedes especificar DWL_CENTRADO para que se centre.
			\param[in]	cY					: Posicion Y. Puedes especificar DWL_CENTRADO para que se centre.
			\param[in]	cAncho				: Ancho del ArbolEx.
			\param[in]	cAlto				: Alto del ArbolEx.
			\param[in]	nMenu				: Menu para la ventana.
			\param[in]	nEstiloExtendido	: Estilos extendidos validos.
			\param[in]	nColorFondo			: Brocha con el color del fondo de la ventana. Puede ser NULL.
			\param[in]	nIconoRecursos		: ID del icono de los recursos que se asignara a la ventana. Puede ser 32512 para que se asigne el icono de la aplicaci�n.
			\return		Devuelve el HWND de la ventana hija. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para ver el error.
	*/
/*	HWND DControlEstandard::CrearControl(DBaseWnd *nPadre, const TCHAR *nNombre, UINT Estilo, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, const UINT nID, DWORD EstiloExtendido, HBRUSH ColorFondo) {
		ATOM CA = _RegistrarClase(nNombre, _GestorMensajes, 0, ColorFondo);
		_hWnd = CreateWindowEx(EstiloExtendido, nNombre, nTexto, Estilo, cX, cY, cAncho, cAlto, nPadre->hWnd(), reinterpret_cast<HMENU>(IntToPtr(nID)), GetModuleHandle(NULL), this);
//		_hWnd = CreateWindowEx(NULL, nNombre, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 100, 100, nPadre->hWnd(), reinterpret_cast<HMENU>(IntToPtr(nID)), GetModuleHandle(NULL), this);
		_ConectarControl(nID, nPadre);
		DDebug::MostrarUltimoError();
		// No puc crear el puto boton cerrar....
//		assert(_hWnd != NULL);
		return _hWnd;
	}*/


	//! Esqueleto para los mensajes del control.
	/*! Esta funci�n es el esqueleto para los mensajes del control.
			\fn			virtual LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
			\param[in]	uMsg	: Mensaje.
			\param[in]	wParam	: Parametro1.
			\param[in]	lParam	: Parametro2.
			\return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
			*/
	LRESULT CALLBACK DControlEstandard::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
		return CallWindowProc(_GestorMensajesOriginal, _hWnd, uMsg, wParam, lParam);
	};

	//! Funci�n que destruye este control.
	/*!	Esta funcion destruye este control.
			\fn			const BOOL Destruir(void);
			\return		Devuelve TRUE si la operaci�n se completo, FALSE en caso contrario.
			*/
	BOOL DControlEstandard::Destruir(void) {
		BOOL R = DBaseWnd::Destruir();
		_GestorMensajesOriginal = NULL;
		return R;
	};

	//! Funci�n que conecta este control con un dialogo.
	/*!	Esta funci�n que conecta este control con un dialogo.
			\fn			void ConectarControl(const UINT nID, DBaseWnd *Padre);
			\param[in]  nID     ID del control.
			\param[in]  nPadre  Clase DBaseWnd que hace de padre para el control.
			\return		No devuelve nada.
			*/
	void DControlEstandard::_ConectarControl(const UINT nID, DBaseWnd *nPadre) {
		if (_hWnd != NULL && _GestorMensajesOriginal == NULL) {
			SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
			_GestorMensajesOriginal = (WNDPROC)SetWindowLongPtr(_hWnd, GWLP_WNDPROC, (LONG_PTR)_GestorMensajes);
			SetWindowTheme(_hWnd, TEXT("Explorer"), NULL);
		}
	};

	//! Esqueleto inicial que enlaza esta clase con el control.
	/*! Esta funci�n es el esqueleto inicial que enlaza esta clase con el control.
			\fn			static LRESULT CALLBACK _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
			\param[in]	HandleVentana	: Identificador de ventana.
			\param[in]	uMsg			: Mensaje.
			\param[in]	wParam			: Parametro1.
			\param[in]	lParam			: Parametro2.
			\return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
			*/
	LRESULT CALLBACK DControlEstandard::_GestorMensajes(HWND nhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		DControlEstandard *Control = reinterpret_cast<DControlEstandard *>(GetWindowLongPtr(nhWnd, GWLP_USERDATA));
		if (Control == NULL) return FALSE;
		//        assert(Control->_hWnd == nhWnd);
		LRESULT Ret = 0;
/*		if (uMsg == WM_PAINT) {
			return (Control->_GestorMensajesOriginal)(nhWnd, uMsg, wParam, lParam);
			//Control->GestorMensajes(uMsg, wParam, lParam);
		}
		else {*/
			Ret = Control->GestorMensajes(uMsg, wParam, lParam);
			if (Ret == DWL_USAR_GESTOR_POR_DEFECTO) {
				return (Control->_GestorMensajesOriginal)(nhWnd, uMsg, wParam, lParam);
			}
//		}
		return Ret;
/*		HWND hWndParent = NULL;
		switch (uMsg) {
			case WM_CREATE: {
				DControl *PreControlEx = reinterpret_cast<DControl *>(((CREATESTRUCT *)lParam)->lpCreateParams);
				if (PreControlEx == NULL) return FALSE; 
				PreControlEx->_hWnd = nhWnd;
				::SetWindowLongPtr(nhWnd, GWLP_USERDATA, PtrToLong(PreControlEx));
				hWndParent = GetParent(nhWnd);
				PreControlEx->GestorMensajes(uMsg, wParam, lParam);
				return TRUE;
			}
			default: {
				DControl *ControlEx = reinterpret_cast<DControl *>(LongToPtr(::GetWindowLongPtr(nhWnd, GWLP_USERDATA)));
				if (ControlEx != NULL) {
					LRESULT Ret = ControlEx->GestorMensajes(uMsg, wParam, lParam);
					if (Ret == DWL_USAR_GESTOR_POR_DEFECTO) Ret = DefWindowProc(nhWnd, uMsg, wParam, lParam);
					return Ret;
				}
				return DefWindowProc(nhWnd, uMsg, wParam, lParam);
			}
		}
		*/

	};

};