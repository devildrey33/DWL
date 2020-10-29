#ifndef DWL_VENTANAMDI_H
#define DWL_VENTANAMDI_H

#include "DWLEventosBase.h"


namespace DWL {
    namespace ControlesEx {
        class DWLMenuEx;
    }
 
	namespace Ventanas {

        class DWLVentanaMDI : public Base::DWLEventosBase<LRESULT> {
		   public : ////////////////// -Declaraciones publicas
									// Constructor  
									DWLVentanaMDI(void);

									//
									// Destructor (Vacio)
								   ~DWLVentanaMDI(void);
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
           HWND                     CrearVentanaMDI(const TCHAR *nNombre, UINT nEstilos, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, HMENU nMenu, DWORD nEstiloExtendido, HBRUSH nColorFondo, const int nIconoRecursos);

                                    //
									// Función para asignar si la ventana se puede maximizar
									// virtual void Maximizable(const bool nMax);
		   virtual void             Maximizable(const bool nMax);

                                    //
									// Función que retorna si la ventana se puede maximizar
									// const bool Maximizable(void);
		   virtual const bool       Maximizable(void);

									//
									// Función para asignar si la ventana se puede minimizar
									// void Minimizable(const bool nMin);
		   virtual void             Minimizable(const bool nMin);

									//
									// Función que retorna si la ventana se puede minimizar
									// virtual const bool Minimizable(void);
		   virtual const bool       Minimizable(void);

									//
									// Función que posiciona la ventana siempre delante de todo
									// virtual void SiempreDelante(const bool SD);
		   virtual void				SiempreDelante(const bool SD);

           /////////////////////////// Eventos
							        //! Función virtual que recibira cuando se pulsa encima de un MenuEx.
							        /*! Esta función virtual recibira cuando se pulsa encima de un MenuEx.
									        \fn			inline virtual LRESULT Evento_MenuEx_Menu_Pulsado(DWL::ControlesEx::DWLMenuEx *MenuPulsado, const UINT IDMenuExPadre);
									        \param[in]	MenuPulsado	  : clase DWLMenuEx que se ha pulsado.
									        \param[in]	IDMenuExPadre : ID del menu pulsado.
									        \return		Si re-emplazas esta funcion, debes retornar 0.
							        */
		   inline virtual LRESULT   Evento_MenuEx_Menu_Pulsado(DWL::ControlesEx::DWLMenuEx *MenuPulsado, const UINT IDMenuExPadre);
								
							        //! Función virtual que recibira cuando se muestra un MenuEx.
							        /*! Esta función virtual recibira cuando se muestra un MenuEx.
									        \fn			inline virtual LRESULT Evento_MenuEx_Menu_Mostrado(UINT IDMenuEx);
									        \param[in]	IDMenuEx	  : clase DWLMenuEx que se ha mostrado.
									        \return		Si re-emplazas esta funcion, debes retornar 0.
							        */
		   inline virtual LRESULT   Evento_MenuEx_Menu_Mostrado(const UINT IDMenuEx);
								
							        //! Función virtual que recibira cuando se oculta un MenuEx.
							        /*! Esta función virtual recibira cuando se oculta un MenuEx.
									        \fn			inline virtual LRESULT Evento_MenuEx_Menu_Ocultado(UINT IDMenuEx);
									        \param[in]	IDMenuEx	  : clase DWLMenuEx que se ha ocultado.
									        \return		Si re-emplazas esta funcion, debes retornar 0.
							        */
		   inline virtual LRESULT   Evento_MenuEx_Menu_Ocultado(const UINT IDMenuEx);

		                            //! Función que retorna el identificador de la ventana cliente.
		                            /*! Esta función que retorna el identificador de la ventana cliente.
				                            \fn			inline HWND hWndCliente(void);
				                            \return		Devuelve el HWND de la ventana cliente.
		                            */
           inline HWND              hWndCliente(void) { return _hWndCliente; };

		  protected: ///////////////// -Declaraciones protegidas (Solo podran usarse en la clase heredada no desde fuera)

				    			    //! hWnd de la ventana cliente
	       HWND                    _hWndCliente;

								    //! Esqueleto para los mensajes de la ventana MDI.
								    /*! Esta función es el esqueleto para los mensajes de la ventana MDI.
										    \fn			virtual LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
										    \param[in]	uMsg	: Mensaje.
										    \param[in]	wParam	: Parametro1.
										    \param[in]	lParam	: Parametro2.
										    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
								    */
		   virtual LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);

								    //! Esqueleto para los mensajes de la ventana MDI cliente.
								    /*! Esta función es el esqueleto para los mensajes de la ventana MDI cliente.
										    \fn			virtual LRESULT CALLBACK GestorMensajesCliente(UINT uMsg, WPARAM wParam, LPARAM lParam);
										    \param[in]	uMsg	: Mensaje.
										    \param[in]	wParam	: Parametro1.
										    \param[in]	lParam	: Parametro2.
										    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
								    */
           virtual LRESULT CALLBACK	GestorMensajesCliente(UINT uMsg, WPARAM wParam, LPARAM lParam);

								    //! Esqueleto inicial que enlaza esta clase con el envoltorio de la ventana MDI.
								    /*! Esta función es el esqueleto  inicial que enlaza esta clase con el envoltorio de la ventana MDI..
										    \fn			static LRESULT CALLBACK _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
										    \param[in]	HandleVentana	: Identificador de ventana.
										    \param[in]	uMsg			: Mensaje.
										    \param[in]	wParam			: Parametro1.
										    \param[in]	lParam			: Parametro2.
										    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
								    */
           static LRESULT CALLBACK _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);

								    //! Esqueleto inicial que enlaza esta clase con la ventana MDI.
								    /*! Esta función es el esqueleto inicial que enlaza esta clase con la ventana MDI.
										    \fn			static LRESULT CALLBACK _GestorMensajesCliente(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
										    \param[in]	HandleVentana	: Identificador de ventana.
										    \param[in]	uMsg			: Mensaje.
										    \param[in]	wParam			: Parametro1.
										    \param[in]	lParam			: Parametro2.
										    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
								    */
           static LRESULT CALLBACK _GestorMensajesCliente(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);

								    //! WindowProcedure orignal de la ventana cliente.
           WNDPROC                 _GestorMensajesOriginalCliente;
		};			     			//
		////////////////////////////// Fin DWLVentanaMDI
    };
};
#endif
