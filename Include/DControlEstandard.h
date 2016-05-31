#ifndef DCONTROLESTANDARD_H
	#define DCONTROLESTANDARD_H
 
	#include "DBaseWnd.h"
	#include <commctrl.h>

    namespace DWL {

	    //! Clase base para los controles estandar de windows (button, combobox, listview, treeview, etc...)
		class DControlEstandard : public DBaseWnd {
	      public : /////////////////////////// Miembros publicos

										    //! Constructor.
										    /*! Constructor.
												    \fn			DControlEstandard(void);
												    \return		No devuelve nada.
										    */
											DControlEstandard(void);

										    //! Destructor.
										    /*! Destructor.
												    \fn		   ~DControlEstandard(void);
												    \return		No devuelve nada.
										    */
			  virtual					   ~DControlEstandard(void);

									   	    //! Esqueleto para los mensajes del control.
										    /*! Esta función es el esqueleto para los mensajes del control.
												    \fn			virtual LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
												    \param[in]	uMsg	: Mensaje.
												    \param[in]	wParam	: Parametro1.
												    \param[in]	lParam	: Parametro2.
												    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
										    */
			virtual LRESULT CALLBACK	    GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);

										    //! Función que destruye este control.
										    /*!	Esta funcion destruye este control.
												    \fn			const BOOL Destruir(void);
												    \return		Devuelve TRUE si la operación se completo, FALSE en caso contrario.
										    */
			virtual BOOL                    Destruir(void);

	      protected : ////////////////////////// Miembros protegidos

										    //! Función que conecta este control con un dialogo.
										    /*!	Esta función que conecta este control con un dialogo.
												    \fn			void ConectarControl(const UINT nID, DBaseWnd *Padre);
                                                    \param[in]  nID     ID del control.
                                                    \param[in]  nPadre  Clase DBaseWnd que hace de padre para el control.
		                                            \return		No devuelve nada.
										    */
			  void	        			   _ConectarControl(const UINT nID, DBaseWnd *nPadre);

										    //! Esqueleto inicial que enlaza esta clase con el control.
										    /*! Esta función es el esqueleto inicial que enlaza esta clase con el control.
												    \fn			static LRESULT CALLBACK _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
												    \param[in]	HandleVentana	: Identificador de ventana.
												    \param[in]	uMsg			: Mensaje.
												    \param[in]	wParam			: Parametro1.
												    \param[in]	lParam			: Parametro2.
												    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
										    */
			  static LRESULT CALLBACK      _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);

										    //! WindowProcedure Orignal del control estándar
	        WNDPROC                        _GestorMensajesOriginal;
	    };                                  //
	    ////////////////////////////////////// Fin DControlEstandard
    };

#endif