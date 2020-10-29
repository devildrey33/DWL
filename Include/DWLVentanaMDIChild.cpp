#include "DWLVentanaMDIChild.h"
#include "DWLVentanaMDI.h"

namespace DWL {
	namespace Ventanas {
 
        //
		// Constructor
        DWLVentanaMDIChild::DWLVentanaMDIChild(void) : DWL::Ventanas::Base::DWLEventosPadre<LRESULT>(){
		};
		//
		// Destructor (Vacio)
        DWLVentanaMDIChild::~DWLVentanaMDIChild(void) {
            Destruir();
		};

	    //! Función que crea la ventana MDI hija.
	    /*!	Esta función crea la ventana MDI hija.
			    \fn			HWND CrearVentanaMDIChild(DWLVentanaMDI *PadreMDI, const TCHAR *nNombre, UINT nEstilos, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, DWORD nEstiloExtendido, HBRUSH nColorFondo = NULL, const int nIconoRecursos = NULL);
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
			    \return		Devuelve el HWND de la ventana hija. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para ver el error.
	    */
        HWND DWLVentanaMDIChild::CrearVentanaMDIChild(DWLVentanaMDI *PadreMDI, const TCHAR *nNombre, UINT nEstilos, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, DWORD nEstiloExtendido, HBRUSH nColorFondo, const int nIconoRecursos) {
		    if (_hWnd != NULL) Destruir();
		    RegistrarClase(nNombre, nColorFondo, nIconoRecursos, _GestorMensajes);
		    int NX = cX;
		    int NY = cY;
		    Padre = PadreMDI;
		    HWND Parent = Padre->hWndCliente();
		    if (cX == DWL_CENTRADO) NX = _CalcularCentrado(Parent, true, cAncho);
		    if (cY == DWL_CENTRADO) NY = _CalcularCentrado(Parent, false, cAlto);
//		    DWLVentanaMDIChild *This = this;
		    _hWnd = CreateWindowEx(nEstiloExtendido , nNombre, 0, WS_THICKFRAME | WS_CHILD, cX, cY, cAncho, cAlto, Parent, 0, GetModuleHandle(NULL), this);
		    return _hWnd;
	    };

		//
		// Función para asignar si la ventana se puede maximizar
		// virtual void Maximizable(const bool nMax);
        void DWLVentanaMDIChild::Maximizable(const bool nMax) {
			long Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE);
			if (Estilos & WS_MAXIMIZEBOX)	Estilos = Estilos & ~ WS_MAXIMIZEBOX;
			if (nMax == true)				Estilos = Estilos | WS_MAXIMIZEBOX;
			SetWindowLongPtr(_hWnd, GWL_STYLE, Estilos);
		};
		//
		// Función que retorna si la ventana se puede maximizar
		// bool Maximizable(void);
        bool DWLVentanaMDIChild::Maximizable(void) {
			long Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE);
			if (Estilos & WS_MAXIMIZEBOX) return true;
			else                          return false;
		};
		//
		// Función para asignar si la ventana se puede minimizar
		// void Minimizable(const bool nMin);
        void DWLVentanaMDIChild::Minimizable(const bool nMin) {
			long Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE);
			if (Estilos & WS_MINIMIZEBOX)	Estilos = Estilos & ~ WS_MINIMIZEBOX;
			if (nMin == true)				Estilos = Estilos | WS_MINIMIZEBOX;
			SetWindowLongPtr(_hWnd, GWL_STYLE, Estilos);
		};
		//
		// Función que retorna si la ventana se puede minimizar
		// virtual const bool Minimizable(void);
        bool DWLVentanaMDIChild::Minimizable(void) {
			long Estilos = GetWindowLongPtr(_hWnd, GWL_STYLE);
			if (Estilos & WS_MINIMIZEBOX) return true;
			else						  return false;
		};
		//
		// Función que posiciona la ventana siempre delante de todo
		// virtual void SiempreDelante(const bool SD);
        void DWLVentanaMDIChild::SiempreDelante(const bool SD) {
			if (SD == true) SetWindowPos(_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE); // NTY
			else			SetWindowPos(_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);		// NTY
		};

	    //! Esqueleto inicial que enlaza esta clase de la ventana MDI hija.
	    /*! Esta función es el esqueleto  inicial que enlaza esta clase de la ventana MDI hija.
			    \fn			static LRESULT CALLBACK _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
			    \param[in]	HandleVentana	: Identificador de ventana.
			    \param[in]	uMsg			: Mensaje.
			    \param[in]	wParam			: Parametro1.
			    \param[in]	lParam			: Parametro2.
			    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
	    */
        LRESULT CALLBACK DWLVentanaMDIChild::_GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		    switch (uMsg) {
			    case WM_CREATE : {
				    DWLVentanaMDIChild *PreVentana = reinterpret_cast<DWLVentanaMDIChild *>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
				    if (PreVentana == NULL) return FALSE;
				    PreVentana->_hWnd = HandleVentana;
				    SetWindowLongPtr(HandleVentana, GWLP_USERDATA, PtrToLong(PreVentana));
				    PreVentana->GestorMensajes(uMsg, wParam, lParam);
				    return TRUE;
			    }

			    default : {
				    DWLVentanaMDIChild *Ventana = reinterpret_cast<DWLVentanaMDIChild *>(LongToPtr(GetWindowLongPtr(HandleVentana, GWL_USERDATA)));
                    if (Ventana != NULL) {
					    LRESULT Ret = Ventana->GestorMensajes(uMsg, wParam, lParam);
                        if (Ret == DWL_USAR_GESTOR_POR_DEFECTO) return DefMDIChildProc(HandleVentana, uMsg, wParam, lParam);
                        return Ret;
                    }
				    return DefMDIChildProc(HandleVentana, uMsg, wParam, lParam);
			    }
		    }
	    };

    };
};
