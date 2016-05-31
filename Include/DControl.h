#ifndef DCONTROL_H
	#define DCONTROL_H
 
	#include "DEventosPadre.h"
	#include <commctrl.h>

    namespace DWL {

	    //! Clase base para los controles estandar de windows (button, combobox, listview, treeview, etc...)
		class DControl : public DEventosPadre<LRESULT> {
	      public : /////////////////////////// Miembros publicos

										    //! Constructor.
										    /*! Constructor.
												    \fn			DControl(void);
												    \return		No devuelve nada.
										    */
											DControl(void);

										    //! Destructor.
										    /*! Destructor.
												    \fn		   ~DControl(void);
												    \return		No devuelve nada.
										    */
			  virtual					   ~DControl(void);

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
			  HWND							CrearControl(DBaseWnd *nPadre, const TCHAR *nNombre, UINT Estilo, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, const UINT nID, DWORD nEstiloExtendido = NULL, HBRUSH nColorFondo = NULL);

									   	    //! Esqueleto para los mensajes del control.
										    /*! Esta función es el esqueleto para los mensajes del control.
												    \fn			virtual LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
												    \param[in]	uMsg	: Mensaje.
												    \param[in]	wParam	: Parametro1.
												    \param[in]	lParam	: Parametro2.
												    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
										    */
			virtual LRESULT CALLBACK	    GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);

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
	    };                                  //
	    ////////////////////////////////////// Fin DControl
    };

#endif