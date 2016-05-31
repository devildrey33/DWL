#include "stdafx.h"
#include "DControl.h"
#include <assert.h>
#include "DDebug.h"

namespace DWL {


	//! Constructor.
	/*! Constructor.
			\fn			DControl(void);
			\return		No devuelve nada.
			*/
	DControl::DControl(void) { };

	//! Destructor.
	/*! Destructor.
			\fn		   ~DControlEstandard(void);
			\return		No devuelve nada.
			*/
	DControl::~DControl(void) {
		Destruir();
	};



	//! Función que crea un control NO estandard.
	/*!	Esta función crea un control NO estandard y lo enlaza con la DWL.
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
			\param[in]	nIconoRecursos		: ID del icono de los recursos que se asignara a la ventana. Puede ser 32512 para que se asigne el icono de la aplicación.
			\return		Devuelve el HWND de la ventana hija. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para ver el error.
	*/
	HWND DControl::CrearControl(DBaseWnd *nPadre, const TCHAR *nNombre, UINT Estilo, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, const UINT nID, DWORD EstiloExtendido, HBRUSH ColorFondo) {
		ATOM CA = _RegistrarClase(nNombre, _GestorMensajes, 0, ColorFondo);
		_hWnd = CreateWindowEx(EstiloExtendido, nNombre, nTexto, Estilo, cX, cY, cAncho, cAlto, nPadre->hWnd(), reinterpret_cast<HMENU>(IntToPtr(nID)), GetModuleHandle(NULL), this);
//		_hWnd = CreateWindowEx(NULL, nNombre, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 100, 100, nPadre->hWnd(), reinterpret_cast<HMENU>(IntToPtr(nID)), GetModuleHandle(NULL), this);
//		_ConectarControl(nID, nPadre);
		return _hWnd;
	}


	//! Esqueleto para los mensajes del control.
	/*! Esta función es el esqueleto para los mensajes del control.
			\fn			virtual LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
			\param[in]	uMsg	: Mensaje.
			\param[in]	wParam	: Parametro1.
			\param[in]	lParam	: Parametro2.
			\return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
			*/
	LRESULT CALLBACK DControl::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
		return DEventosBase<LRESULT>::GestorMensajes(uMsg, wParam, lParam);
	};


	//! Función que conecta este control con un dialogo.
	/*!	Esta función que conecta este control con un dialogo.
			\fn			void ConectarControl(const UINT nID, DBaseWnd *Padre);
			\param[in]  nID     ID del control.
			\param[in]  nPadre  Clase DBaseWnd que hace de padre para el control.
			\return		No devuelve nada.
			*/
	void DControl::_ConectarControl(const UINT nID, DBaseWnd *nPadre) {
		if (_hWnd != NULL) {
			SetWindowLongPtr(_hWnd, GWLP_USERDATA, PtrToLong(this));
			SetWindowLongPtr(_hWnd, GWLP_WNDPROC, PtrToLong(_GestorMensajes));
//			SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
			//_GestorMensajesOriginal = (WNDPROC)SetWindowLongPtr(_hWnd, GWLP_WNDPROC, (LONG_PTR)_GestorMensajes);
//			SetWindowTheme(_hWnd, TEXT("Explorer"), NULL);
		}
	};

	//! Esqueleto inicial que enlaza esta clase con el control.
	/*! Esta función es el esqueleto inicial que enlaza esta clase con el control.
			\fn			static LRESULT CALLBACK _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
			\param[in]	HandleVentana	: Identificador de ventana.
			\param[in]	uMsg			: Mensaje.
			\param[in]	wParam			: Parametro1.
			\param[in]	lParam			: Parametro2.
			\return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
			*/
	LRESULT CALLBACK DControl::_GestorMensajes(HWND nhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		HWND hWndParent = NULL;
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
				DControl *ControlEx = reinterpret_cast<DControl *>(GetWindowLongPtr(nhWnd, GWLP_USERDATA));
				if (ControlEx != NULL) {
					LRESULT Ret = ControlEx->GestorMensajes(uMsg, wParam, lParam);
					if (Ret == DWL_USAR_GESTOR_POR_DEFECTO) Ret = DefWindowProc(nhWnd, uMsg, wParam, lParam);
					return Ret;
				}
				return DefWindowProc(nhWnd, uMsg, wParam, lParam);
			}
		}
	};

};