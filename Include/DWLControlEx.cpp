#include "DWLControlEx.h"
#include "DWLToolTipEx.h"
 
// Necesario para que VC6 me reconozca el gestor de mensajes de EventosBase
using namespace DWL::Ventanas::Base;


namespace DWL {
    namespace ControlesEx {
        namespace Base {

		    //! Constructor.
		    /*! Constructor.
			    \fn			DWLControlEx(void);
			    \return		No devuelve nada.
		    */
            DWLControlEx::DWLControlEx(void) : DWL::Ventanas::Base::DWLEventosBase<LRESULT>() {
			    _MouseDentro = false; 
			    _ID = 0;
		    };

		    //! Destructor.
		    /*! Destructor.
			    \fn		   ~DWLControlEx(void);
			    \return		No devuelve nada.
		    */
            DWLControlEx::~DWLControlEx(void) { 
			    Destruir();
		    };

		    //! Función que crea el control.
		    /*!	Esta función crea el control.
				    \fn			HWND CrearControl(HWND nParent, const TCHAR *nNombre, UINT nEstilos, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, const UINT nID, DWORD nEstiloExtendido = NULL, HBRUSH nColorFondo = NULL);
				    \param[in]	nParent				: HWND de la ventana que va a contener este control extendido.
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
            HWND DWLControlEx::CrearControl(HWND Parent, const TCHAR *Nombre, UINT Estilo, const TCHAR *Text, const int cX, const int cY, const int cAncho, const int cAlto, const UINT nID, DWORD EstiloExtendido, HBRUSH ColorFondo) { 
			    RegistrarClase(Nombre, ColorFondo, 0, _GestorMensajes); 
			    int NX = cX; 
			    int NY = cY;
			    if (cX == DWL_CENTRADO) NX = _CalcularCentrado(Parent, true, cAncho);
			    if (cY == DWL_CENTRADO) NY = _CalcularCentrado(Parent, false, cAlto); 
			    _ID = nID;
			    _hWnd = CreateWindowEx(EstiloExtendido, Nombre, Text, Estilo, NX, NY, cAncho, cAlto, Parent, reinterpret_cast<HMENU>(IntToPtr(nID)), GetModuleHandle(NULL), this);
			    SOLO_DEBUG(
				    if (_hWnd == NULL) DWL::DWLDebug::MostrarUltimoError();
			    );
			    SendMessage(GetParent(_hWnd), DWL_TAB_AGREGAR_CONTROL, static_cast<WPARAM>(PtrToLong(this)), 0); // Agrego el control a la lista de tabulacion
			    return _hWnd;
		    };


		    //! Función que conecta este control con un control del dialogo.
		    /*!	Esta función conecta el control con un control del dialogo.
				    \fn			HWND _ConectarControl(const UINT ID_Control, HWND hWndParent);
				    \param[in]	ID_Control : ID del control.
				    \param[in]	hWndParent : HWND del dialogo.
				    \return		Devuelve el HWND del control.
		    */											
            HWND DWLControlEx::_ConectarControl(const UINT ID_Control, HWND hWndParent) { 
			    _hWnd = GetDlgItem(hWndParent, ID_Control); 
			    if (_hWnd != NULL) {
				    SetWindowLongPtr(_hWnd, GWL_USERDATA, PtrToLong(this));
				    SetWindowLongPtr(_hWnd, GWL_WNDPROC, PtrToLong(_GestorMensajes));
				    SendMessage(GetParent(_hWnd), DWL_TAB_AGREGAR_CONTROL, static_cast<WPARAM>(PtrToLong(this)), 0); // Agrego el control a la lista de tabulacion
			    }
			    return _hWnd;
		    };


			//! Función que recibe cuando hay que mostrar el tooltip
			/*! Esta función recibe cuando hay que mostrar el tooltip de este control.
					\fn         virtual LRESULT Evento_MostrarToolTip(const UINT IDControl, LPARAM Param);
					\param[in]  IDControl : ID del control 
					\param[in]  Param     : Si param no es 0 hace referencia a la ID de un boton extra del control
					\return     Debes retornar 0 si re-emplazas esta función.
					\remarks    Param hace referencia a la ID de un boton extras que provengan de una DWLBarraScrollEx.
			*/
			LRESULT DWLControlEx::Evento_MostrarToolTip(const UINT IDControl, LPARAM Param) {
				KillTimer(_hWnd, DWL_TIMER_TOOLTIP);
				return SendMessage(GetParent(_hWnd), DWL_TOOLTIPEX_MOSTRAR, IDControl, Param);
			}

			//! Función que recibe cuando hay que ocultar el tooltip
			/*! Esta función recibe cuando hay que ocultar el tooltip de este control.
					\fn         virtual LRESULT Evento_OcultarToolTip(const UINT IDControl, LPARAM Param);
					\param[in]  IDControl : ID del control 
					\param[in]  Param     : Si param no es 0 hace referencia a la ID de un boton extra del control
					\return     Debes retornar 0 si re-emplazas esta función.
					\remarks    Param hace referencia a la ID de un boton extras que provengan de una DWLBarraScrollEx.
			*/
			LRESULT DWLControlEx::Evento_OcultarToolTip(const UINT IDControl, LPARAM Param) {
				KillTimer(_hWnd, DWL_TIMER_TOOLTIP);
				return SendMessage(GetParent(_hWnd), DWL_TOOLTIPEX_OCULTAR, IDControl, Param);
			}
			
		    //! Esqueleto inicial que enlaza esta clase con el control extendido.
		    /*! Esta función es el esqueleto inicial que enlaza esta clase con el control extendido.
				    \fn			static LRESULT CALLBACK _GestorMensajes(HWND HandleControlEx, UINT uMsg, WPARAM wParam, LPARAM lParam);
				    \param[in]	HandleControlEx	: Identificador de ventana.
				    \param[in]	uMsg			: Mensaje.
				    \param[in]	wParam			: Parametro1.
				    \param[in]	lParam			: Parametro2.
				    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
		    */
            LRESULT CALLBACK DWLControlEx::_GestorMensajes(HWND HandleControlEx, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			    HWND hWndParent = NULL;
			    switch (uMsg) {
				    case WM_CREATE : {
					    DWLControlEx *PreControlEx = reinterpret_cast<DWLControlEx *>(((CREATESTRUCT *)lParam)->lpCreateParams); 
					    if (PreControlEx == NULL) return FALSE;
					    PreControlEx->_hWnd = HandleControlEx;
					    ::SetWindowLongPtr(HandleControlEx, GWL_USERDATA, PtrToLong(PreControlEx));
					    hWndParent = GetParent(HandleControlEx);
					    PreControlEx->GestorMensajes(uMsg, wParam, lParam);
					    return TRUE;
				    }
				    default : {
					    DWLControlEx *ControlEx = reinterpret_cast<DWLControlEx *>(LongToPtr(::GetWindowLongPtr(HandleControlEx, GWL_USERDATA)));
					    if (ControlEx != NULL) {
                            LRESULT Ret = ControlEx->GestorMensajes(uMsg, wParam, lParam);
                            if (Ret == DWL_USAR_GESTOR_POR_DEFECTO) Ret = DefWindowProc(HandleControlEx, uMsg, wParam, lParam);
                            return Ret;
					    }
   					    return DefWindowProc(HandleControlEx, uMsg, wParam, lParam);
				    }
			    }
		    };




            //! Esqueleto para los mensajes de la ventana.
            /*! Esta función es el esqueleto para los mensajes del dialogo.
		            \fn			inline virtual BOOL CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
		            \param[in]	uMsg	: Mensaje.
		            \param[in]	wParam	: Parametro1.
		            \param[in]	lParam	: Parametro2.
		            \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
            */
            LRESULT CALLBACK DWLControlEx::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
                switch (uMsg) {
                    // Tabulaciones
                    case WM_CHAR :	
					    if (wParam == VK_TAB) {
						    if (GetKeyState(VK_SHIFT) & DWL_TECLA_PRESIONADA)	return SendMessage(GetParent(_hWnd), DWL_TAB_ANTERIOR, 0, 0);
						    else												return SendMessage(GetParent(_hWnd), DWL_TAB_SIGUIENTE, 0, 0);
					    }
                        return Evento_Teclado_Caracter(static_cast<UINT>(wParam), LOWORD(lParam), HIWORD(lParam));
                    case WM_SETFOCUS :
					    SendMessage(GetParent(_hWnd), DWL_TAB_CAMBIO_FOCO, static_cast<WPARAM>(PtrToLong(this)), 0);
                        return Evento_Foco_Obtenido(reinterpret_cast<HWND>(wParam));
					// Añadidos para mostrar tooltips en los controles extendidos
					case WM_MOUSELEAVE :
						KillTimer(_hWnd, DWL_TIMER_TOOLTIP); // Si el mouse sale desactivo el timer del tooltip
						SendMessage(GetParent(_hWnd), DWL_TOOLTIPEX_OCULTAR, _ID, 0);
						break;
					case WM_MOUSEMOVE :
						if (_MouseDentro == false) 
							SetTimer(_hWnd, DWL_TIMER_TOOLTIP, DWL_TIEMPO_TOOLTIP, NULL); // Si el mouse entra activo el timer del tooltip
						break;
					case WM_TIMER :
						if (static_cast<UINT>(wParam) == DWL_TIMER_TOOLTIP) {
							if (Visible() == TRUE) Evento_MostrarToolTip(_ID, 0);
						}
						break;

                }
				#if (COMPILADOR == COMPILADOR_VC6)
					return DWLEventosBase<LRESULT>::GestorMensajes(uMsg, wParam, lParam);
				#else
					return DWL::Ventanas::Base::DWLEventosBase<LRESULT>::GestorMensajes(uMsg, wParam, lParam);
				#endif
            }





        };
    };
};
