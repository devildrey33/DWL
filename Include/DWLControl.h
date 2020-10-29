#ifndef DWL_BASECONTROLWINDOWS
#define DWL_BASECONTROLWINDOWS
 
#include "DWLEventosBase.h"

//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres Controles
    namespace Controles {
        //! Espacio de nombres Base
        namespace Base {
		    //! Clase base para los controles normales
            class DWLControl : public DWL::Ventanas::Base::DWLEventosBase<LRESULT, DWL_USAR_GESTOR_POR_DEFECTO> {
		    public : ///////////////////////////// Miembros publicos

											    //! Constructor.
											    /*! Constructor.
													    \fn			DWLControl(void);
													    \return		No devuelve nada.
											    */
											    DWLControl(void);

											    //! Destructor.
											    /*! Destructor.
													    \fn		   ~DWLControl(void);
													    \return		No devuelve nada.
											    */
			 virtual					       ~DWLControl(void);

										   	    //! Esqueleto para los mensajes del control.
											    /*! Esta funci�n es el esqueleto para los mensajes del control.
													    \fn			virtual LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
													    \param[in]	uMsg	: Mensaje.
													    \param[in]	wParam	: Parametro1.
													    \param[in]	lParam	: Parametro2.
													    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
											    */
		     virtual LRESULT CALLBACK		    GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);

											    //! Funci�n que conecta este control con un dialogo.
											    /*!	Esta funci�n que conecta este control con un dialogo.
													    \fn			void ConectarControl(void);
													    \return		No devuelve nada.
											    */
		     void							    ConectarControl(void);

											    //! Funci�n que destruye este control.
											    /*!	Esta funcion destruye este control.
													    \fn			const BOOL Destruir(void);
													    \return		Devuelve TRUE si la operaci�n se completo, FALSE en caso contrario.
											    */
		     virtual BOOL                       Destruir(void);

											    //! Funci�n que cambia la posici�n de este control dentro de la lista de tabulaciones.
											    /*!	Esta funcion cambia la posici�n de este control dentro de la lista de tabulaciones.
													    \fn			void PosicionTab(const int nPos);
													    \param[in]	nPos : Nueva posicion para el control en la lista de tabulaciones.
													    \return		No devuelve nada.
											    */
		     void								PosicionTab(const int nPos);

											    //! Funci�n que retorna la posici�n de este control dentro de la lista de tabulaciones.
											    /*!	Esta funcion devuelve la posici�n de este control dentro de la lista de tabulaciones.
													    \fn			const size_t PosicionTab(void);
													    \return		Devuelve la posicion de este control dentro de la lista de tabulaciones.
											    */
		     size_t						        PosicionTab(void);

		    protected : ////////////////////////// Miembros protegidos
											    //! Esqueleto inicial que enlaza esta clase con el control.
											    /*! Esta funci�n es el esqueleto inicial que enlaza esta clase con el control.
													    \fn			static LRESULT CALLBACK _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
													    \param[in]	HandleVentana	: Identificador de ventana.
													    \param[in]	uMsg			: Mensaje.
													    \param[in]	wParam			: Parametro1.
													    \param[in]	lParam			: Parametro2.
													    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
											    */
		     static LRESULT CALLBACK	       _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);

											    //! WindowProcedure Orignal del control est�ndar
		     WNDPROC                           _GestorMensajesOriginal;
		    };                                  //
		    ////////////////////////////////////// Fin DWLControl


        };
    };
};
#endif

