#include "stdafx.h"
#include "DVentana.h"
#include <assert.h>

namespace DWL {
            
	//! Destructor  
    /*! Destructor por defecto.
		    \fn		   ~DVentana(void);
            \return     No devuelve nada
    */
    DVentana::~DVentana(void) { 
        Destruir();
	};


    //! Función que crea la ventana.
    /*!	Esta función crea la ventana.
	        \fn			HWND DVentana::Crear(const TCHAR *nNombre, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, DWORD nEstilos, DWORD nEstilosExtendidos = NULL, HMENU nMenu = NULL, HBRUSH nColorFondo = NULL, const int nIconoRecursos = 32512);
	        \param[in]	nNombre				  Nombre para la clase ventana.
	        \param[in]	nTexto				  Titulo para la ventana.
	        \param[in]	cX					  Posicion X. Puedes especificar DWL_CENTRADO para que se centre.
	        \param[in]	cY					  Posicion Y. Puedes especificar DWL_CENTRADO para que se centre.
	        \param[in]	cAncho				  Ancho de la ventana.
	        \param[in]	cAlto				  Alto del la ventana.
	        \param[in]	nEstilos			  Estilos validos para ventanas (WS_OVERLAPPED | WS_VISIBLE | etc..)
	        \param[in]	nEstilosExtendidos	  Estilos extendidos validos.
	        \param[in]	nMenu				  Menu para la ventana, NULL si no hay menu. NOTA a diferencia de los controles creados con CreateWindow este parametro NO DEBE UTILIZARSE para especificar la ID de la ventana.
	        \param[in]	nColorFondo			  Brocha con el color del fondo de la ventana. Puede ser NULL.
	        \param[in]	nIconoRecursos		  ID del icono de los recursos que se asignara a la ventana. Puede ser 32512 para que se asigne el icono de la aplicación.
	        \return		Devuelve el HWND de la ventana. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para ver el error.
    */
    HWND DVentana::Crear(const TCHAR *nNombre, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, DWORD nEstilos, DWORD nEstilosExtendidos, HMENU nMenu, HBRUSH nColorFondo, const int nIconoRecursos) {
		if (_hWnd != NULL) Destruir();
//        _AgregarAppBaseWnd(0, NULL);

		ATOM RetRgistrarClase = _RegistrarClase(nNombre, _GestorMensajes, nIconoRecursos, nColorFondo);
		_hWnd = CreateWindowEx(nEstilosExtendidos, nNombre, nTexto, nEstilos, cX, cY, cAncho, cAlto, HWND_DESKTOP, nMenu, GetModuleHandle(NULL), this);
//        if (_hWnd == NULL) throw (DError(this, __PROTOTIPO_FUNCION__, DEnum_Error_CreateWindowEx));     
		assert(_hWnd != NULL);
		return _hWnd;
    }



    //! Función virtual para determinar si la ventana es maximizable.
    /*! Esta función virtual determina si la ventana es maximizable.
		    \fn			void DVentana::Maximizable(const bool nMax);
		    \param[in]	nMax    Especifica true para que la ventana sea maximizable, false para lo contrario.
		    \return		Esta función no devuelve nada.
    */
    void DVentana::Maximizable(const bool nMax) { 
		LONG_PTR Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE); 
		if (Estilos & WS_MAXIMIZEBOX)	Estilos = Estilos & ~ WS_MAXIMIZEBOX;  
		if (nMax == true)				Estilos = Estilos | WS_MAXIMIZEBOX;
		SetWindowLongPtr(_hWnd, GWL_STYLE, Estilos); 
	};

    //! Función virtual que nos dice si la ventana es maximizable.
    /*! Esta función virtual nos dice si la ventana es maximizable.
		    \fn			const bool DVentana::Maximizable(void);
		    \return		Devuelve true si la ventana es maximizable, false en caso contrario.
    */
    const bool DVentana::Maximizable(void) {
		LONG_PTR Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE); 
		if (Estilos & WS_MAXIMIZEBOX) return true; 
		return false;
	};

    //! Función que nos dice si la ventana esta maximizada en este momento.
    /*! Esta función nos dice si la ventana esta maximizada en este momento.
		    \fn			const bool DVentana::Maximizada(void);
		    \return		Devuelve true si la ventana esta maximizada, false en caso contrario.
    */
    const bool DVentana::Maximizada(void) {
		WINDOWPLACEMENT WndPl;
		GetWindowPlacement(_hWnd, &WndPl);
		if (WndPl.showCmd == SW_MAXIMIZE) return true;
		return false;
	};

    //! Función virtual para determinar si la ventana es minimizable.
    /*! Esta función virtual determina si la ventana es minimizable.
		    \fn			void DVentana::Minimizable(const bool nMin);
		    \param[in]	nMix : Especifica true para que la ventana sea minimizable, false para lo contrario.
		    \return		Esta función no devuelve nada.
    */
    void DVentana::Minimizable(const bool nMin) { 
		LONG_PTR Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE);
		if (Estilos & WS_MINIMIZEBOX)	Estilos = Estilos & ~ WS_MINIMIZEBOX; 
		if (nMin == true)				Estilos = Estilos | WS_MINIMIZEBOX; 
		SetWindowLongPtr(_hWnd, GWL_STYLE, Estilos); 
	};

    //! Función virtual que nos dice si la ventana es minimizable.
    /*! Esta función virtual nos dice si la ventana es minimizable.
		    \fn			const bool DVentana::Minimizable(void);
		    \return		Devuelve true si la ventana es minimizable, false en caso contrario.
    */
    const bool DVentana::Minimizable(void) { 
		LONG_PTR Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE); 
		if (Estilos & WS_MINIMIZEBOX) return true; 
		return false;
	};

    //! Función que nos dice si la ventana esta minimizada en este momento.
    /*! Esta función nos dice si la ventana esta minimizada en este momento.
		    \fn			const bool DVentana::Minimizada(void);
		    \return		Devuelve true si la ventana esta minimizada, false en caso contrario.
    */
    const bool DVentana::Minimizada(void) {
		WINDOWPLACEMENT WndPl;
		GetWindowPlacement(_hWnd, &WndPl);
		if (WndPl.showCmd == SW_MINIMIZE) return true;
		return false;
	};

    //! Función para posicionar la ventana siempre delante de todas las otras ventanas.
    /*! Esta función posiciona la ventana siempre delante de todas las otras ventanas.
		    \fn			void DVentana::SiempreDelante(const bool SD);
		    \param[in]	SD  Especifica true para que la ventana quede siempre por delante, false para que tenga un comportamiento normal segun su coordenada Z.
		    \return		Esta función no devuelve nada.
            \remarks    Por norma las ventanas se posicionan utilizando el OrdenZ, que es un indice para determinar en que posición estan las ventanas. 
                        Si por ejemplo creas dos ventanas la primera se pondra en el orden 1, y la segunda en el orden 0, 
                        de forma que si se crean en cascada deberias ver la segunda ventana por delante de todo.
    */
    void DVentana::SiempreDelante(const bool SD) {
		SetWindowPos(_hWnd, (SD == true) ? HWND_TOPMOST : HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	};

    //! Función para asignar el titulo de la ventana.
    /*! Esta función asigna el titulo de la ventana.
		    \fn			void DVentana::Titulo(const TCHAR *Txt);
		    \param[in]	Txt  Nuevo texto para el titulo de la ventana.
		    \return		Esta función no devuelve nada.
    */
    void DVentana::Titulo(const TCHAR *Txt) {
		SetWindowText(_hWnd, Txt);
	};

    //! Función para obtener el titulo de la ventana.
    /*! Esta función obtiene el titulo de la ventana en el buffer especificado.
		    \fn			void DVentana::Titulo(const TCHAR *Txt);
		    \param[in]	Txt     Buffer de texto para obtener el titulo.
            \param[in]  TamTxt  Tamaño del buffer para el titulo.
		    \return		Esta función devuelve 0 en caso de error. En caso de exito devuelve el numero de caracteres que contiene el titulo sin incluir el terminador NULL.
    */
    int DVentana::Titulo(TCHAR *Txt, const int TamTxt) { 
		return GetWindowText(_hWnd, Txt, TamTxt);
	};


	//! Esqueleto inicial que enlaza esta clase con la ventana.
	/*! Esta función es el esqueleto inicial que enlaza esta clase con la ventana.
			\fn			static LRESULT CALLBACK DVentana::_GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
			\param[in]	HandleVentana	: Identificador de ventana.
			\param[in]	uMsg			: Mensaje.
			\param[in]	wParam			: Parametro1.
			\param[in]	lParam			: Parametro2.
			\return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
	*/
    LRESULT CALLBACK DVentana::_GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg) {
			case WM_CREATE : {
				DVentana *PreVentana = reinterpret_cast<DVentana *>(((CREATESTRUCT *)lParam)->lpCreateParams); 
				if (PreVentana == NULL) return FALSE;
				PreVentana->_hWnd = HandleVentana;
				SetWindowLongPtr(HandleVentana, GWLP_USERDATA, (LONG_PTR)PreVentana);
				PreVentana->GestorMensajes(uMsg, wParam, lParam);
				return TRUE;
            }
            // CUSTOM DRAW (ListView y TreeView)
            case WM_NOTIFY : // OJO WM_NOTIFY debe ir encima de default: no le pongo un break porque solo quiero saber si es un CUSTOMDRAW, en caso contrario se debe tratar como un mensaje normal
                if (((LPNMHDR)lParam)->code == NM_CUSTOMDRAW)
                    return SendMessage(((LPNMHDR)lParam)->hwndFrom, DWL_CUSTOM_DRAWWND, wParam, lParam);
			default : {
				DVentana *Ventana = reinterpret_cast<DVentana *>(::GetWindowLongPtr(HandleVentana, GWLP_USERDATA));
                if (Ventana != NULL) {
                    LRESULT Ret = Ventana->GestorMensajes(uMsg, wParam, lParam);
                    if (Ret == DWL_USAR_GESTOR_POR_DEFECTO) Ret = DefWindowProc(HandleVentana, uMsg, wParam, lParam);
                    return Ret;
                }
    			return DefWindowProc(HandleVentana, uMsg, wParam, lParam);
            }
		}
	};

    LRESULT DVentana::Evento_Pintar(HDC hDC, PAINTSTRUCT &PS) {
        FillRect(hDC, &PS.rcPaint, (HBRUSH)(COLOR_BTNFACE  + 1));
        return 0;
    }


};
