#include "DWLControl.h"
 
//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres Controles
    namespace Controles {
        //! Espacio de nombres Base
        namespace Base {


		    //! Constructor.
		    /*! Constructor.
				    \fn			DWLControl(void);
				    \return		No devuelve nada.
		    */
            DWLControl::DWLControl(void) : DWL::Ventanas::Base::DWLEventosBase<LRESULT, DWL_USAR_GESTOR_POR_DEFECTO>() {
			    _GestorMensajesOriginal = NULL;
		    };

		    //! Destructor.
		    /*! Destructor.
				    \fn		   ~DWLControl(void);
				    \return		No devuelve nada.
		    */
            DWLControl::~DWLControl(void) {
			    Destruir();
		    };

	   	    //! Esqueleto para los mensajes del control.
		    /*! Esta función es el esqueleto para los mensajes del control.
				    \fn			inline virtual LRESULT CALLBACK	GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
				    \param[in]	uMsg	: Mensaje.
				    \param[in]	wParam	: Parametro1.
				    \param[in]	lParam	: Parametro2.
				    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
		    */
            LRESULT CALLBACK DWLControl::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
			    switch (uMsg) {
                    case WM_CHAR :
					    if (wParam == VK_TAB) {
						    if (GetKeyState(VK_SHIFT) & DWL_TECLA_PRESIONADA)	return SendMessage(GetParent(_hWnd), DWL_TAB_ANTERIOR, 0, 0);
						    else												return SendMessage(GetParent(_hWnd), DWL_TAB_SIGUIENTE, 0, 0);
					    }
                        break;
                    case WM_SETFOCUS :
					    SendMessage(GetParent(_hWnd), DWL_TAB_CAMBIO_FOCO, static_cast<WPARAM>(PtrToLong(this)), 0);
                        break;
			    }
			    return CallWindowProc(_GestorMensajesOriginal, _hWnd, uMsg, wParam, lParam);
		    };

		    //! Función que conecta este control con un dialogo.
		    /*!	Esta función que conecta este control con un dialogo.
				    \fn			void ConectarControl(void);
				    \return		No devuelve nada.
		    */
            void DWLControl::ConectarControl(void) {
			    if (_hWnd != NULL && _GestorMensajesOriginal == NULL) {
				    SetWindowLongPtr(_hWnd, GWLP_USERDATA, PtrToLong(this));
				    _GestorMensajesOriginal = (WNDPROC)LongToPtr(SetWindowLongPtr(_hWnd, GWLP_WNDPROC, PtrToLong(_GestorMensajes)));
				    SendMessage(GetParent(_hWnd), DWL_TAB_AGREGAR_CONTROL, static_cast<WPARAM>(PtrToLong(this)), 0); // Agrego el control a la lista de tabulacion
			    }
		    };

		    //! Función que destruye este control.
		    /*!	Esta funcion destruye este control.
				    \fn			BOOL Destruir(void);
				    \return		Devuelve TRUE si la operación se completo, FALSE en caso contrario.
		    */
            BOOL DWLControl::Destruir(void) {
			    BOOL R = DWLBaseWnd::Destruir();
			    _GestorMensajesOriginal = NULL;
			    return R;
		    };

		    //! Función que cambia la posición de este control dentro de la lista de tabulaciones.
		    /*!	Esta funcion cambia la posición de este control dentro de la lista de tabulaciones.
				    \fn			void PosicionTab(const int nPos);
				    \param[in]	nPos : Nueva posicion para el control en la lista de tabulaciones.
				    \return		No devuelve nada.
		    */
            void DWLControl::PosicionTab(const int nPos) {
			    SendMessage(GetParent(_hWnd), DWL_TAB_CAMBIAR_POSICION, static_cast<WPARAM>(PtrToLong(this)), static_cast<LPARAM>(nPos));
		    };

		    //! Función que retorna la posición de este control dentro de la lista de tabulaciones.
		    /*!	Esta funcion devuelve la posición de este control dentro de la lista de tabulaciones.
				    \fn			size_t PosicionTab(void);
				    \return		Devuelve la posicion de este control dentro de la lista de tabulaciones.
		    */
            size_t DWLControl::PosicionTab(void) {
			    return static_cast<size_t>(SendMessage(GetParent(_hWnd), DWL_TAB_OBTENER_POSICION, static_cast<WPARAM>(PtrToLong(this)), 0));
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
            LRESULT CALLBACK DWLControl::_GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			    DWLControl *Control = reinterpret_cast<DWLControl *>(LongToPtr(GetWindowLongPtr(HandleVentana, GWL_USERDATA)));
			    if (Control == NULL) return FALSE;
                LRESULT Ret = 0;
                if (uMsg == WM_PAINT) {
                    return (Control->_GestorMensajesOriginal)(HandleVentana, uMsg, wParam, lParam);
                    //Control->GestorMensajes(uMsg, wParam, lParam);
                }
                else {
                    Ret = Control->GestorMensajes(uMsg, wParam, lParam);
                    if (Ret == DWL_USAR_GESTOR_POR_DEFECTO) return (Control->_GestorMensajesOriginal)(HandleVentana, uMsg, wParam, lParam);
                }
			    return Ret;
		    };

        };
    };
};
