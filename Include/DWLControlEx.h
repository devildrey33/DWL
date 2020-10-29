#ifndef DWL_CONTROLEX
#define DWL_CONTROLEX
 
#include "DWLEventosBase.h"


//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres ControlesEx
    namespace ControlesEx {
        //! Espacio de nombres Base
        namespace Base {
		    //! Clase base para los controles extendidos
            class DWLControlEx : public DWL::Ventanas::Base::DWLEventosBase<LRESULT> {
		     public : //////////////////////////////// Miembros publicos

												    //! Constructor.
												    /*! Constructor.
													    \fn			DWLControlEx(void);
													    \return		No devuelve nada.
												    */
												    DWLControlEx(void);

												    //! Destructor.
												    /*! Destructor.
													    \fn		   ~DWLControlEx(void);
													    \return		No devuelve nada.
												    */
											       ~DWLControlEx(void);

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
		     HWND			                        CrearControl(HWND Parent, const TCHAR *Nombre, UINT Estilo, const TCHAR *Text, const int cX, const int cY, const int cAncho, const int cAlto, const UINT nID, DWORD EstiloExtendido = NULL, HBRUSH ColorFondo = NULL);

		                                            //! Función que retorna la ID de este control extendido.
		                                            /*!	Esta funcion devuelve la ID de este control extendido.
				                                            \fn			inline const UINT ID(void);
				                                            \return		Devuelve la ID de este control extendido.
		                                            */
//             inline const UINT                      ID(void) { return _ID; };

													//! Función que recibe cuando hay que mostrar el tooltip
													/*! Esta función recibe cuando hay que mostrar el tooltip de este control.
															\fn         virtual LRESULT Evento_MostrarToolTip(const UINT IDControl, LPARAM Param);
															\param[in]  IDControl : ID del control 
															\param[in]  Param     : Si param no es 0 hace referencia a la ID de un boton extra del control
															\return     Debes retornar 0 si re-emplazas esta función.
															\remarks    Param hace referencia a la ID de un boton extras que provengan de una DWLBarraScrollEx.
													*/
			 virtual LRESULT                        Evento_MostrarToolTip(const UINT IDControl, LPARAM Param);

													//! Función que recibe cuando hay que ocultar el tooltip
													/*! Esta función recibe cuando hay que ocultar el tooltip de este control.
															\fn         virtual LRESULT Evento_OcultarToolTip(const UINT IDControl, LPARAM Param);
															\param[in]  IDControl : ID del control 
															\param[in]  Param     : Si param no es 0 hace referencia a la ID de un boton extra del control
															\return     Debes retornar 0 si re-emplazas esta función.
															\remarks    Param hace referencia a la ID de un boton extras que provengan de una DWLBarraScrollEx.
													*/
			 virtual LRESULT                        Evento_OcultarToolTip(const UINT IDControl, LPARAM Param);

										            //! Esqueleto para los mensajes de la ventana.
										            /*! Esta función es el esqueleto para los mensajes del dialogo.
												            \fn			inline virtual BOOL CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
												            \param[in]	uMsg	: Mensaje.
												            \param[in]	wParam	: Parametro1.
												            \param[in]	lParam	: Parametro2.
												            \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
										            */
             virtual LRESULT CALLBACK               GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
            protected:
												    //! Función que conecta este control con un control del dialogo.
												    /*!	Esta función conecta el control con un control del dialogo.
														    \fn			HWND _ConectarControl(const UINT ID_Control, HWND hWndParent);
														    \param[in]	ID_Control : ID del control.
														    \param[in]	hWndParent : HWND del dialogo.
														    \return		Devuelve el HWND del control.
												    */
		     HWND					               _ConectarControl(const UINT ID_Control, HWND hWndParent);

												    //! ID del control
		     UINT								   _ID;

    //		private : //////////////////////////////// Meimbros privados

												    //! Esqueleto inicial que enlaza esta clase con el control extendido.
												    /*! Esta función es el esqueleto inicial que enlaza esta clase con el control extendido.
														    \fn			static LRESULT CALLBACK _GestorMensajes(HWND HandleControlEx, UINT uMsg, WPARAM wParam, LPARAM lParam);
														    \param[in]	HandleControlEx	: Identificador de ventana.
														    \param[in]	uMsg			: Mensaje.
														    \param[in]	wParam			: Parametro1.
														    \param[in]	lParam			: Parametro2.
														    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
												    */
		     static LRESULT CALLBACK			   _GestorMensajes(HWND HandleControlEx, UINT uMsg, WPARAM wParam, LPARAM lParam);

		    };										//
		    //////////////////////////////////////////
        };
    };
};

#endif
