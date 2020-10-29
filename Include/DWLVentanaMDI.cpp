#include "DWLVentanaMDI.h"
#include "DWLMenuEx.h"

namespace DWL {
	namespace Ventanas {

		// Constructor  
        DWLVentanaMDI::DWLVentanaMDI(void) : DWL::Ventanas::Base::DWLEventosBase<LRESULT>() { 
		};
		//
		// Destructor 
        DWLVentanaMDI::~DWLVentanaMDI(void) { 
            Destruir();
		};
 
	    //! Función que crea la ventana MDI.
	    /*!	Esta función crea la ventana MDI.
			    \fn			HWND CrearVentanaMDI(const TCHAR *nNombre, UINT nEstilos, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, HMENU nMenu, DWORD nEstiloExtendido = NULL, HBRUSH nColorFondo = NULL, const int nIconoRecursos = NULL);
			    \param[in]	nNombre				: Nombre para la clase ventana.
			    \param[in]	nEstilos			: Estilos validos para ventanas MDI.
			    \param[in]	nTexto				: Titulo para la ventana.
			    \param[in]	cX					: Posicion X. Puedes especificar DWL_CENTRADO para que se centre.
			    \param[in]	cY					: Posicion Y. Puedes especificar DWL_CENTRADO para que se centre.
			    \param[in]	cAncho				: Ancho de la ventana.
			    \param[in]	cAlto				: Alto de la ventana.
			    \param[in]	nMenu				: Menu para la ventana.
			    \param[in]	nEstiloExtendido	: Estilos extendidos validos.
			    \param[in]	nColorFondo			: Brocha con el color del fondo de la ventana. Puede ser NULL.
			    \param[in]	nIconoRecursos		: ID del icono de los recursos que se asignara a la ventana. Puede ser 32512 para que se asigne el icono de la aplicación.
			    \return		Devuelve el HWND de la ventana. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para ver el error.
	    */
        HWND DWLVentanaMDI::CrearVentanaMDI(const TCHAR *nNombre, UINT nEstilos, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, HMENU nMenu, DWORD nEstiloExtendido, HBRUSH nColorFondo, const int nIconoRecursos) { 
		    if (_hWnd != NULL) Destruir();
		    RegistrarClase(nNombre, nColorFondo, nIconoRecursos, _GestorMensajes); 
		    int NX = cX; 
		    int NY = cY;
		    if (cX == DWL_CENTRADO) NX = _CalcularCentrado(NULL, true, cAncho);
		    if (cY == DWL_CENTRADO) NY = _CalcularCentrado(NULL, false, cAlto); 
		    _hWnd = CreateWindowEx(nEstiloExtendido, nNombre, nTexto, nEstilos, NX, NY, cAncho, cAlto, NULL, nMenu, GetModuleHandle(NULL), this);
		    RECT R;
		    GetClientRect(_hWnd, &R);
		    CLIENTCREATESTRUCT ccs;
		    ccs.idFirstChild = 0;
		    _hWndCliente = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("MDICLIENT"), NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, 0, 0, R.right, R.bottom, _hWnd, (HMENU)1, GetModuleHandle(NULL), (LPVOID)&ccs);
		    SetWindowLongPtr(_hWndCliente, GWLP_USERDATA, PtrToLong(this));
		    _GestorMensajesOriginalCliente = (WNDPROC)LongToPtr(SetWindowLongPtr(_hWndCliente, GWLP_WNDPROC, PtrToLong(_GestorMensajesCliente)));
		    return _hWnd;
	    };

		//
		// Función para asignar si la ventana se puede maximizar
		// virtual void Maximizable(const bool nMax);
        void DWLVentanaMDI::Maximizable(const bool nMax) { 
			long Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE); 
			if (Estilos & WS_MAXIMIZEBOX)	Estilos = Estilos & ~ WS_MAXIMIZEBOX;  
			if (nMax == true)				Estilos = Estilos | WS_MAXIMIZEBOX;
			SetWindowLongPtr(_hWnd, GWL_STYLE, Estilos); 
		};
		//
		// Función que retorna si la ventana se puede maximizar
		// const bool Maximizable(void);
        const bool DWLVentanaMDI::Maximizable(void) {
			long Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE); 
			if (Estilos & WS_MAXIMIZEBOX) return true; 
			else                          return false;
		};
		//
		// Función para asignar si la ventana se puede minimizar
		// void Minimizable(const bool nMin);
        void DWLVentanaMDI::Minimizable(const bool nMin) { 
			long Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE);
			if (Estilos & WS_MINIMIZEBOX)	Estilos = Estilos & ~ WS_MINIMIZEBOX; 
			if (nMin == true)				Estilos = Estilos | WS_MINIMIZEBOX; 
			SetWindowLongPtr(_hWnd, GWL_STYLE, Estilos); 
		};
		//
		// Función que retorna si la ventana se puede minimizar
		// virtual const bool Minimizable(void);
        const bool DWLVentanaMDI::Minimizable(void) { 
			long Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE); 
			if (Estilos & WS_MINIMIZEBOX) return true; 
			else						  return false;
		};
		//
		// Función que posiciona la ventana siempre delante de todo
		// virtual void SiempreDelante(const bool SD);
        void DWLVentanaMDI::SiempreDelante(const bool SD) {
			if (SD == true) SetWindowPos(_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE); 
			else			SetWindowPos(_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);		
		};

/////////////////////////// Eventos
        //! Función virtual que recibira cuando se pulsa encima de un MenuEx.
        /*! Esta función virtual recibira cuando se pulsa encima de un MenuEx.
		        \fn			inline virtual LRESULT Evento_MenuEx_Menu_Pulsado(DWL::ControlesEx::DWLMenuEx *MenuPulsado, const UINT IDMenuExPadre);
		        \param[in]	MenuPulsado	  : clase DWLMenuEx que se ha pulsado.
		        \param[in]	IDMenuExPadre : ID del menu pulsado.
		        \return		Si re-emplazas esta funcion, debes retornar 0.
        */
        LRESULT DWLVentanaMDI::Evento_MenuEx_Menu_Pulsado(DWL::ControlesEx::DWLMenuEx *MenuPulsado, const UINT IDMenuExPadre) {
            return 0;
        };
	
        //! Función virtual que recibira cuando se muestra un MenuEx.
        /*! Esta función virtual recibira cuando se muestra un MenuEx.
		        \fn			inline virtual LRESULT Evento_MenuEx_Menu_Mostrado(UINT IDMenuEx);
		        \param[in]	IDMenuEx	  : clase DWLMenuEx que se ha mostrado.
		        \return		Si re-emplazas esta funcion, debes retornar 0.
        */
        LRESULT DWLVentanaMDI::Evento_MenuEx_Menu_Mostrado(const UINT IDMenuEx) {
            return 0;
        };
	
        //! Función virtual que recibira cuando se oculta un MenuEx.
        /*! Esta función virtual recibira cuando se oculta un MenuEx.
		        \fn			inline virtual LRESULT Evento_MenuEx_Menu_Ocultado(UINT IDMenuEx);
		        \param[in]	IDMenuEx	  : clase DWLMenuEx que se ha ocultado.
		        \return		Si re-emplazas esta funcion, debes retornar 0.
        */
        LRESULT DWLVentanaMDI::Evento_MenuEx_Menu_Ocultado(const UINT IDMenuEx) {
            return 0;
        };

		//
		// WindowProcedure para la Ventana (CreateWindow)
		// virtual LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);  
        LRESULT CALLBACK DWLVentanaMDI::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) { 
            switch (uMsg) {
                // MenuEx
                case DWL_MENUEX_MENU_PULSADO :																								
	                return Evento_MenuEx_Menu_Pulsado(reinterpret_cast<DWL::ControlesEx::DWLMenuEx *>(wParam), static_cast<UINT>(lParam));	
	            case DWL_MENUEX_MENU_MOSTRADO :									
		            return Evento_MenuEx_Menu_Mostrado(static_cast<UINT>(wParam));	
	            case DWL_MENUEX_MENU_OCULTADO :									
		            return Evento_MenuEx_Menu_Ocultado(static_cast<UINT>(wParam));	
            }
			return DefFrameProc(_hWnd, _hWndCliente, uMsg, wParam, lParam);
		};  

	    //! Esqueleto para los mensajes de la ventana MDI cliente.
	    /*! Esta función es el esqueleto para los mensajes de la ventana MDI cliente.
			    \fn			inline virtual LRESULT CALLBACK	GestorMensajesCliente(UINT uMsg, WPARAM wParam, LPARAM lParam);
			    \param[in]	uMsg	: Mensaje.
			    \param[in]	wParam	: Parametro1.
			    \param[in]	lParam	: Parametro2.
			    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
	    */
        LRESULT CALLBACK DWLVentanaMDI::GestorMensajesCliente(UINT uMsg, WPARAM wParam, LPARAM lParam) {
		    return CallWindowProc(_GestorMensajesOriginalCliente, _hWndCliente, uMsg, wParam, lParam); 
	    };

	    //! Esqueleto inicial que enlaza esta clase con el envoltorio de la ventana MDI.
	    /*! Esta función es el esqueleto  inicial que enlaza esta clase con el envoltorio de la ventana MDI..
			    \fn			static LRESULT CALLBACK _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
			    \param[in]	HandleVentana	: Identificador de ventana.
			    \param[in]	uMsg			: Mensaje.
			    \param[in]	wParam			: Parametro1.
			    \param[in]	lParam			: Parametro2.
			    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
	    */
        LRESULT CALLBACK DWLVentanaMDI::_GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		    switch (uMsg) {
			    case WM_CREATE : {
				    DWLVentanaMDI *PreVentana = reinterpret_cast<DWLVentanaMDI *>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams); 
				    if (PreVentana == NULL) return FALSE;
				    PreVentana->_hWnd = HandleVentana;
				    SetWindowLongPtr(HandleVentana, GWLP_USERDATA, PtrToLong(PreVentana));
				    PreVentana->GestorMensajes(uMsg, wParam, lParam);
				    return TRUE;
			    }

			    default : {
				    DWLVentanaMDI *Ventana = reinterpret_cast<DWLVentanaMDI *>(LongToPtr(::GetWindowLongPtr(HandleVentana, GWL_USERDATA)));
				    if (Ventana != NULL) {
                        LRESULT Ret = Ventana->GestorMensajes(uMsg, wParam, lParam);
                        if (Ret == DWL_USAR_GESTOR_POR_DEFECTO) return DefFrameProc(HandleVentana, NULL, uMsg, wParam, lParam);
                        return Ret;
				    }	
				    return DefFrameProc(HandleVentana, NULL, uMsg, wParam, lParam);
			    }
		    }
	    };

	    //! Esqueleto inicial que enlaza esta clase con la ventana MDI.
	    /*! Esta función es el esqueleto inicial que enlaza esta clase con la ventana MDI.
			    \fn			static LRESULT CALLBACK _GestorMensajesCliente(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
			    \param[in]	HandleVentana	: Identificador de ventana.
			    \param[in]	uMsg			: Mensaje.
			    \param[in]	wParam			: Parametro1.
			    \param[in]	lParam			: Parametro2.
			    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
	    */
        LRESULT CALLBACK DWLVentanaMDI::_GestorMensajesCliente(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		    DWLVentanaMDI *Ventana = reinterpret_cast<DWLVentanaMDI *>(LongToPtr(::GetWindowLongPtr(HandleVentana, GWL_USERDATA)));
		    return Ventana->GestorMensajesCliente(uMsg, wParam, lParam);
	    };


    };
};
