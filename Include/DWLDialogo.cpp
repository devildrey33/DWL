#include "DWLDialogo.h"
 

namespace DWL {
	namespace Ventanas {

        //! Constructor.
		/*!	Constructor por defecto.
				\fn		DWLDialogo(void);
				\return	No devuelve nada.
		*/
        DWLDialogo::DWLDialogo(void) { 
			_hWnd = NULL; 
		};

		//! Función que crea el dialogo.
		/*!	Esta función crea el dialogo.
				\fn			HWND CrearDialogo(int ID_Dialogo, const int cX, const int cY);
				\param[in]	ID_Dialogo	: ID del dialogo en los recursos.
				\param[in]	cX			: Posicion X. Puedes especificar DWL_CENTRADO para que se centre.
				\param[in]	cY			: Posicion Y. Puedes especificar DWL_CENTRADO para que se centre.
				\return		Devuelve el HWND del dialogo. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para ver el error.
		*/
        HWND DWLDialogo::CrearDialogo(int ID_Dialogo, const int cX, const int cY) {
			if (_hWnd != NULL) Destruir();
			_hWnd = CreateDialogParam(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_Dialogo), HWND_DESKTOP, (DLGPROC)_GestorMensajes, (LPARAM)this); 
			RECT RC; 
			GetClientRect(_hWnd, &RC); 	
			int NX = cX; 
			int NY = cY; 	
			if (cX == DWL_CENTRADO) NX = _CalcularCentrado(NULL, true, RC.right); 
			if (cY == DWL_CENTRADO) NY = _CalcularCentrado(NULL, false, RC.bottom);
			Mover(NX, NY, RC.right, RC.bottom); 
			return _hWnd;
		};

		//! Función para asignar si el dialogo se puede maximizar
		/*!	Esta función asigna si el dialogo tiene la capacidad de ser maximizado.
				\fn			virtual void Maximizable(const bool nMax);
				\param[in]	nMax	: Parametro en el que especificaremos si el dialogo puede ser maximizado.
				\return		No devuelve nada.
		*/
        void DWLDialogo::Maximizable(const bool nMax) { 
			long Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE);
			if (Estilos & WS_MAXIMIZEBOX)	Estilos = Estilos & ~ WS_MAXIMIZEBOX;
			if (nMax == true)				Estilos = Estilos | WS_MAXIMIZEBOX; 
			SetWindowLongPtr(_hWnd, GWL_STYLE, Estilos); 
		};

		//! Función para obtener si el dialogo se puede maximizar
		/*!	Esta función se usa para obtener si el dialogo tiene la capacidad de ser maximizado.
				\fn			virtual const bool Maximizable(void); 
				\return		Devuelve true si se puede maximizar, false en caso contrario.
		*/
        const bool DWLDialogo::Maximizable(void) { 
			long Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE); 
			if (Estilos & WS_MAXIMIZEBOX)	return true; 
			else							return false; 
		};

		//! Función para asignar si el dialogo se puede minimizar
		/*!	Esta función asigna si el dialogo tiene la capacidad de ser minimizado.
				\fn			virtual void Minimizable(const bool nMin);
				\param[in]	nMin	: Parametro en el que especificaremos si el dialogo puede ser minimizado.
				\return		No devuelve nada.
		*/
        void DWLDialogo::Minimizable(const bool nMin) { 
			long Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE); 
			if (Estilos & WS_MINIMIZEBOX)	Estilos = Estilos & ~ WS_MINIMIZEBOX; 
			if (nMin == true)				Estilos = Estilos | WS_MINIMIZEBOX; 
			SetWindowLongPtr(_hWnd, GWL_STYLE, Estilos);
		};

		//! Función para obtener si el dialogo se puede minimizar
		/*!	Esta funcion se usa para obtener si el dialogo tiene la capacidad de ser minimizado.
				\fn			virtual const bool Minimizable(void); 
				\return		Devuelve true si se puede minimizar, false en caso contrario.
		*/
        const bool DWLDialogo::Minimizable(void) { 
			long Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE);
			if (Estilos & WS_MINIMIZEBOX)	return true; 
			else							return false; 
		};

		//! Función que posiciona el dialogo siempre delante de todo
		/*!	Esta función posiciona el dialogo siempre delante de todas las otras ventanas.
				\fn			virtual void SiempreDelante(const bool SD);
				\param[in]	SD	: Parametro en el que si el dialogo estara siempre delante.
				\return		No devuelve nada.
		*/
        void DWLDialogo::SiempreDelante(const bool SD) {
			if (SD == true) SetWindowPos(_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE); 
			else			SetWindowPos(_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);		
		};

		//! Esqueleto inicial que enlaza esta clase con el dialogo.
		/*! Esta función es el esqueleto inicial que enlaza esta clase con el dialogo.
				\fn			static BOOL CALLBACK _GestorMensajes(HWND HandleDialogo, UINT uMsg, WPARAM wParam, LPARAM lParam);
				\param[in]	HandleVentana	: Identificador de ventana.
				\param[in]	uMsg			: Mensaje.
				\param[in]	wParam			: Parametro1.
				\param[in]	lParam			: Parametro2.
				\return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
		*/
        BOOL CALLBACK DWLDialogo::_GestorMensajes(HWND HandleDialogo, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			switch (uMsg) {
				case WM_INITDIALOG : {
					DWLDialogo *PreDialogo = reinterpret_cast<DWLDialogo *>(lParam);
					PreDialogo->_hWnd = HandleDialogo;
					SetWindowLongPtr(HandleDialogo, GWL_USERDATA, (long)lParam);
					PreDialogo->GestorMensajes(uMsg, wParam, lParam);
					return TRUE;
				}

				default : {
					DWLDialogo *Dialogo = reinterpret_cast<DWLDialogo *>(LongToPtr(GetWindowLongPtr(HandleDialogo, GWL_USERDATA)));
					if (Dialogo == NULL) return FALSE;
//                    if (Dialogo == NULL) return DefDlgProc(HandleDialogo, uMsg, wParam, lParam);
                    BOOL Ret = Dialogo->GestorMensajes(uMsg, wParam, lParam);
                    if (Ret == DWL_USAR_GESTOR_POR_DEFECTO) return FALSE;
//                    if (Ret == DWL_USAR_GESTOR_POR_DEFECTO) return DefDlgProc(HandleDialogo, uMsg, wParam, lParam);
                    return Ret;
				}
			}
		};
	
    };
};
