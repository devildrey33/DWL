/*! \file DWLEventosBase.h
	\brief Archivo que contiene los eventos basicos para cualquier ventana / control.
*/
#ifndef DWL_EVENTOSBASE_H
#define DWL_EVENTOSBASE_H

//#include "DWLDebug.h"
#include "DWLBaseWnd.h"


//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres Ventanas
    namespace Ventanas {
        //! Espacio de nombres Base
        namespace Base {
            //! Clase base para los eventos por defecto de cualquier ventana / control
            template <typename TIPO_DEVUELTO, const long VALOR_DEVUELTO = 0> class DWLEventosBase : public DWLBaseWnd {

             public : //////////////////////////////// Mimebros publicos

		                                            //! Constructor.
		                                            /*! Constructor.
			                                            \fn			DWLEventosBase(void);
			                                            \return		No devuelve nada.
		                                            */
                                                    DWLEventosBase(void) : DWLBaseWnd(), _MouseDentro(false) { };

                                                    //! Destructor.
                                                    /*! Destructor.
                                                        \fn		   ~DWLEventosBase(void);
                                                        \return		No devuelve nada.
                                                    */
                 virtual                           ~DWLEventosBase(void) { };

									                //! Función enlazada al mensaje WM_ERASEBKGND
											        /*! Esta función se utiliza para responder al mensaje WM_ERASEBKGND.
													        \fn			inline virtual TIPO_DEVUELTO Evento_BorrarFondoHDC(HDC hDC);
													        \param[in]	hDC	: HDC para borrar.
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
			 								        */
                 inline virtual TIPO_DEVUELTO       Evento_BorrarFondoHDC(HDC hDC) { return VALOR_DEVUELTO; };

									                //! Función enlazada al mensaje WM_PAINT
											        /*! Esta función se utiliza para responder al mensaje WM_PAINT.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);
													        \param[in]	hDC	: HDC para borrar.
													        \param[in]	PS	: Estructura que contiene datos para el pintado.
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
                 inline virtual TIPO_DEVUELTO       Evento_Pintar(HDC hDC, PAINTSTRUCT &PS) { return VALOR_DEVUELTO; };

									                //! Función enlazada al mensaje WM_CLOSE
											        /*! Esta función se utiliza para responder al mensaje WM_CLOSE.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Cerrar(void);
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
                 inline virtual TIPO_DEVUELTO       Evento_Cerrar(void) { return VALOR_DEVUELTO; };

									                //! Función enlazada al mensaje WM_DESTROY
											        /*! Esta función se utiliza para responder al mensaje WM_DESTROY.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Destruir(void);
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
                 inline virtual TIPO_DEVUELTO       Evento_Destruir(void) { return VALOR_DEVUELTO; };

									                //! Función enlazada al mensaje WM_SIZING
											        /*! Esta función se utiliza para responder al mensaje WM_SIZING.
													        \fn			inline virtual TIPO_DEVUELTO Evento_CambiandoTam(const UINT Lado, RECT *Rectangulo);
                                                            \param[in]  Lado       : Lateral por donde esta el mouse
                                                            \param[in]  Rectangulo : Nuevo rectangulo de la ventana
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
                 inline virtual TIPO_DEVUELTO       Evento_CambiandoTam(const UINT Lado, RECT *Rectangulo) { return VALOR_DEVUELTO; };

									                //! Función enlazada al mensaje WM_SIZE
											        /*! Esta función se utiliza para responder al mensaje WM_SIZE.
													        \fn			inline virtual TIPO_DEVUELTO Evento_CambioTam(const UINT Tipo, const int nAncho, const int nAlto);
                                                            \param[in]  Tipo   : Tipo de redimensión
                                                            \param[in]  nAncho : Nuevo ancho de la ventana
                                                            \param[in]  nAlto  : Nueva altura de la ventana
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
                 inline virtual TIPO_DEVUELTO       Evento_CambioTam(const UINT Tipo, const int nAncho, const int nAlto) { return VALOR_DEVUELTO; };

									                //! Función enlazada a los mensajes WM_*BUTTONDBLCLK
											        /*! Esta función se utiliza para responder a los mensajes WM_*BUTTONDBLCLK.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT Param);
                                                            \param[in]  Boton : Boton del mouse presionado
                                                            \param[in]  cX    : Coordenada X del mouse
                                                            \param[in]  cY    : Coordenada Y del mouse
                                                            \param[in]  Param : Teclas especiales presionadas.
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
                 inline virtual TIPO_DEVUELTO       Evento_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT Param) { return VALOR_DEVUELTO; };

									                //! Función enlazada a los mensajes WM_*BUTTONUP
											        /*! Esta función se utiliza para responder a los mensajes WM_*BUTTONUP.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
                                                            \param[in]  Boton : Boton del mouse presionado
                                                            \param[in]  cX    : Coordenada X del mouse
                                                            \param[in]  cY    : Coordenada Y del mouse
                                                            \param[in]  Param : Teclas especiales presionadas.
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
                 inline virtual TIPO_DEVUELTO       Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param) { return VALOR_DEVUELTO; };

									                //! Función enlazada a los mensajes WM_*BUTTONDOWN
											        /*! Esta función se utiliza para responder a los mensajes WM_*BUTTONDOWN.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param);
                                                            \param[in]  Boton : Boton del mouse presionado
                                                            \param[in]  cX    : Coordenada X del mouse
                                                            \param[in]  cY    : Coordenada Y del mouse
                                                            \param[in]  Param : Teclas especiales presionadas
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
                 inline virtual TIPO_DEVUELTO       Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, UINT const Param) { return VALOR_DEVUELTO; };

									                //! Función enlazada al mensaje WM_MOUSEMOVE
											        /*! Esta función se utiliza para responder al mensaje WM_MOUSEMOVE.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);
                                                            \param[in]  cX    : Coordenada X del mouse
                                                            \param[in]  cY    : Coordenada Y del mouse
                                                            \param[in]  Param : Teclas especiales presionadas
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
                 inline virtual TIPO_DEVUELTO       Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param) { return VALOR_DEVUELTO; };

									                //! Función enlazada al mensaje WM_MOUSEWHEEL
											        /*! Esta función se utiliza para responder al mensaje WM_MOUSEWHEEL.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const int VirtKey);
                                                            \param[in]  Delta   : Mobimiento de la rueda
                                                            \param[in]  cX      : Coordenada X del mouse
                                                            \param[in]  cY      : Coordenada Y del mouse
                                                            \param[in]  VirtKey : Teclas especiales presionadas
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
		         inline virtual TIPO_DEVUELTO       Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey) { return VALOR_DEVUELTO; };

												    //! Función que recibe cuando el mouse entra en el control
												    /*!	Esta función es la encargada de procesar cuando el mouse entra en el control.
														    \fn			virtual TIPO_DEVUELTO Evento_Mouse_Entrando(void);
   												            \return		Si re-emplazas esta funcion debes retornar 0.
												    */
                 inline virtual TIPO_DEVUELTO		Evento_Mouse_Entrando(const int cX, const int cY, const UINT Param) { return 0; };

												    //! Función que recibe cuando el mouse se va del control
												    /*!	Esta función es la encargada de procesar los mensajes WN_MOUSELEAVE.
														    \fn			virtual TIPO_DEVUELTO Evento_Mouse_Saliendo(void);
   												            \return		Si re-emplazas esta funcion debes retornar 0.
												    */
                 inline virtual TIPO_DEVUELTO		Evento_Mouse_Saliendo(void) { return 0; };

									                //! Función enlazada al mensaje WM_KEYDOWN
											        /*! Esta función se utiliza para responder al mensaje WM_KEYDOWN.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Teclado_TeclaPresionada(const UINT Tecla, const UINT Repeticion, const UINT Params);
                                                            \param[in]  Tecla      : Tecla presionada
                                                            \param[in]  Repeticion : Repeticiones de la tecla
                                                            \param[in]  Params     : Teclas especiales presionadas
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
                 inline virtual TIPO_DEVUELTO       Evento_Teclado_TeclaPresionada(const UINT Tecla, const UINT Repeticion, const UINT Params) { return VALOR_DEVUELTO; };

									                //! Función enlazada al mensaje WM_KEYUP
											        /*! Esta función se utiliza para responder al mensaje WM_KEYUP.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Teclado_TeclaSoltada(const UINT Tecla, const UINT Repeticion, const UINT Params);
                                                            \param[in]  Tecla      : Tecla soltada
                                                            \param[in]  Repeticion : Repeticiones de la tecla
                                                            \param[in]  Params     : Teclas especiales presionadas
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
                 inline virtual TIPO_DEVUELTO       Evento_Teclado_TeclaSoltada(const UINT Tecla, const UINT Repeticion, const UINT Params) { return VALOR_DEVUELTO; };

									                //! Función enlazada al mensaje WM_CHAR
											        /*! Esta función se utiliza para responder al mensaje WM_CHAR.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Teclado_Caracter(const UINT Tecla, const UINT Repeticion, const UINT Params);
                                                            \param[in]  Tecla      : Tecla presionada
                                                            \param[in]  Repeticion : Repeticiones de la tecla
                                                            \param[in]  Params     : Teclas especiales presionadas
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
                 inline virtual TIPO_DEVUELTO       Evento_Teclado_Caracter(const UINT Tecla, const UINT Repeticion, const UINT Params) { return VALOR_DEVUELTO; };

									                //! Función enlazada al mensaje WM_SYSCHAR
											        /*! Esta función se utiliza para responder al mensaje WM_SYSCHAR.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Teclado_CaracterDelSistema(const UINT Tecla, const UINT Repeticion, const UINT Params);
                                                            \param[in]  Tecla      : Tecla presionada
                                                            \param[in]  Repeticion : Repeticiones de la tecla
                                                            \param[in]  Params     : Teclas especiales presionadas
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
                 inline virtual TIPO_DEVUELTO       Evento_Teclado_CaracterDelSistema(const UINT Tecla, const UINT Repeticion, const UINT Params) { return VALOR_DEVUELTO; };

									                //! Función enlazada al mensaje WM_COMMAND
											        /*! Esta función se utiliza para responder al mensaje WM_COMMAND.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Comando(const int cID, const UINT CodigoNotificacion, HWND hWndControl);
                                                            \param[in]  cID                : ID del control
                                                            \param[in]  CodigoNotificacion : Codigo de notificacion
                                                            \param[in]  hWndControl        : HWND del control
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
		         inline virtual TIPO_DEVUELTO       Evento_Comando(const int cID, const UINT CodigoNotificacion, HWND hWndControl) { return VALOR_DEVUELTO; };

									                //! Función enlazada al mensaje WM_SYSCOMMAND
											        /*! Esta función se utiliza para responder al mensaje WM_SYSCOMMAND.
													        \fn			inline virtual TIPO_DEVUELTO Evento_ComandoDelSistema(const UINT cID, const int cX, const int cY)
                                                            \param[in]  cID : ID del menú
                                                            \param[in]  cX  : Coordenada X del mouse
                                                            \param[in]  cY  : Coordenada Y del mouse
													        \return		Si vas a re-emplazar deberias retornar DefWindowProc para los mensajes que no vayas a utilizar, y 0 para los mensajes que re-emplaces.
											        */
                 inline virtual TIPO_DEVUELTO       Evento_ComandoDelSistema(const UINT cID, const int cX, const int cY) {
                                                        return DefWindowProc(_hWnd, WM_SYSCOMMAND, static_cast<WPARAM>(cID), MAKELPARAM(cX, cY));
                                                    };

									                //! Función enlazada al mensaje WM_NOTIFY
											        /*! Esta función se utiliza para responder al mensaje WM_NOTIFY.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Notificacion(const UINT cID, LPNMHDR Datos)
                                                            \param[in]  cID   : ID del control
                                                            \param[in]  Datos : Estructura que contiene mas datos sobre la notificación
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
		         inline virtual TIPO_DEVUELTO       Evento_Notificacion(const UINT cID, LPNMHDR Datos) { return VALOR_DEVUELTO; };

									                //! Función enlazada al mensaje WM_TIMER
											        /*! Esta función se utiliza para responder al mensaje WM_TIMER.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Temporizador(const UINT cID)
                                                            \param[in]  cID   : ID del temporizador
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
		         inline virtual TIPO_DEVUELTO   	Evento_Temporizador(const UINT cID) { return VALOR_DEVUELTO; };

									                //! Función enlazada al mensaje WM_SETFOCUS
											        /*! Esta función se utiliza para responder al mensaje WM_SETFOCUS.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Foco_Obtenido(HWND FocoAnterior)
                                                            \param[in]  FocoAnterior : HWND del ultimo foco
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
		         inline virtual TIPO_DEVUELTO       Evento_Foco_Obtenido(HWND FocoAnterior) { return VALOR_DEVUELTO; };

									                //! Función enlazada al mensaje WM_KILLFOCUS
											        /*! Esta función se utiliza para responder al mensaje WM_KILLFOCUS.
													        \fn			inline virtual TIPO_DEVUELTO Evento_Foco_Obtenido(HWND NuevoFoco)
                                                            \param[in]  NuevoFoco : HWND del nuevo foco
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
		         inline virtual TIPO_DEVUELTO       Evento_Foco_Perdido(HWND NuevoFoco) { return VALOR_DEVUELTO; };

				 									//! Función que recibe cuando hay que mostrar el tooltip
													/*! Esta función recibe cuando hay que mostrar el tooltip de este control.
															\fn         virtual TIPO_DEVUELTO Evento_MostrarToolTip(const UINT IDControl, LPARAM Param);
															\param[in]  IDControl : ID del control 
															\param[in]  Param     : Si param no es 0 hace referencia a la ID de un boton extra del control
															\return     Debes retornar 0 si re-emplazas esta función.
															\remarks    Param hace referencia a la ID de un boton extras que provengan de una DWLBarraScrollEx.
													*/
				 inline virtual TIPO_DEVUELTO		Evento_MostrarToolTip(const UINT IDControl, LPARAM Param) { return VALOR_DEVUELTO; };

				 									//! Función que recibe cuando hay que ocultar el tooltip
													/*! Esta función recibe cuando hay que ocultar el tooltip de este control.
															\fn         virtual TIPO_DEVUELTO Evento_OcultarToolTip(const UINT IDControl, LPARAM Param);
															\param[in]  IDControl : ID del control 
															\param[in]  Param     : Si param no es 0 hace referencia a la ID de un boton extra del control
															\return     Debes retornar 0 si re-emplazas esta función.
															\remarks    Param hace referencia a la ID de un boton extras que provengan de una DWLBarraScrollEx.
													*/
				 inline virtual TIPO_DEVUELTO		Evento_OcultarToolTip(const UINT IDControl, LPARAM Param) { return VALOR_DEVUELTO; };
 

										            //! Esqueleto para los mensajes de la ventana.
										            /*! Esta función es el esqueleto para los mensajes del dialogo.
												            \fn			inline virtual BOOL CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
												            \param[in]	uMsg	: Mensaje.
												            \param[in]	wParam	: Parametro1.
												            \param[in]	lParam	: Parametro2.
												            \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
										            */
                 virtual TIPO_DEVUELTO CALLBACK	    GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
                                                        TIPO_DEVUELTO Ret = 0;
				                                        switch (uMsg) {
                                                            // Eventos
                                                            case WM_ERASEBKGND :
                                                                return Evento_BorrarFondoHDC(reinterpret_cast<HDC>(wParam));
                                                            case WM_PAINT :
			                                                    HDC DC;
			                                                    PAINTSTRUCT ps;
			                                                    DC = BeginPaint(_hWnd, &ps);
			                                                    Ret = Evento_Pintar(DC, ps);
			                                                    EndPaint(_hWnd, &ps);
			                                                    return Ret;
                                                            case WM_CLOSE :
                                                                return Evento_Cerrar();
                                                            case WM_DESTROY :
                                                                return Evento_Destruir();
                                                            case WM_SIZING :
                                                                return Evento_CambiandoTam(static_cast<UINT>(wParam), reinterpret_cast<RECT *>(lParam));
                                                            case WM_SIZE :
                                                                return Evento_CambioTam(static_cast<UINT>(wParam), LOWORD(lParam), HIWORD(lParam));
                                                            case WM_LBUTTONDBLCLK :
                                                                return Evento_Mouse_DobleClick(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                            case WM_RBUTTONDBLCLK :
                                                                return Evento_Mouse_DobleClick(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                            case WM_MBUTTONDBLCLK :
                                                                return Evento_Mouse_DobleClick(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                            case WM_XBUTTONDBLCLK :
            			                                        return Evento_Mouse_DobleClick(HIWORD(wParam) + 2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                            case WM_LBUTTONDOWN :
                                                                return Evento_Mouse_BotonPresionado(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                            case WM_RBUTTONDOWN :
                                                                return Evento_Mouse_BotonPresionado(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                            case WM_MBUTTONDOWN :
                                                                return Evento_Mouse_BotonPresionado(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                            case WM_XBUTTONDOWN :
            			                                        return Evento_Mouse_BotonPresionado(HIWORD(wParam) + 2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                            case WM_LBUTTONUP :
                                                                return Evento_Mouse_BotonSoltado(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                            case WM_RBUTTONUP :
                                                                return Evento_Mouse_BotonSoltado(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                            case WM_MBUTTONUP :
                                                                return Evento_Mouse_BotonSoltado(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                            case WM_XBUTTONUP :
            			                                        return Evento_Mouse_BotonSoltado(HIWORD(wParam) + 2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                            // Mouse leave
                                                            case WM_MOUSEMOVE :
                                                                if (_MirarMouseLeave() == true) {
																	this->Evento_Mouse_Entrando(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
																}
                                                                return this->Evento_Mouse_Movimiento(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                            case WM_MOUSELEAVE :
                                                                 _MouseDentro = false;
                                                                return Evento_Mouse_Saliendo();
                                                            case WM_MOUSEWHEEL :
                                                                return Evento_Mouse_Rueda(static_cast<short>(HIWORD(wParam)), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(LOWORD(wParam)));
                                                            case WM_KEYDOWN :
                                                                return Evento_Teclado_TeclaPresionada(static_cast<UINT>(wParam), LOWORD(lParam), HIWORD(lParam));
                                                            case WM_KEYUP :
                                                                return Evento_Teclado_TeclaSoltada(static_cast<UINT>(wParam), LOWORD(lParam), HIWORD(lParam));
                                                            case WM_CHAR :
                                                                return Evento_Teclado_Caracter(static_cast<UINT>(wParam), LOWORD(lParam), HIWORD(lParam));
                                                            case WM_SYSCHAR :
                                                                return Evento_Teclado_CaracterDelSistema(static_cast<UINT>(wParam), LOWORD(lParam), HIWORD(lParam));
                                                            case WM_COMMAND :
                                                                return Evento_Comando(LOWORD(wParam), HIWORD(wParam), reinterpret_cast<HWND>(lParam));
                                                            case WM_SYSCOMMAND :
                                                                return Evento_ComandoDelSistema(static_cast<UINT>(wParam), LOWORD(lParam), HIWORD(lParam));
                                                            case WM_NOTIFY :
                                                                return Evento_Notificacion(static_cast<UINT>(wParam), reinterpret_cast<LPNMHDR>(lParam));
                                                            case WM_TIMER :
                                                                return Evento_Temporizador(static_cast<UINT>(wParam));
                                                            case WM_SETFOCUS :
                                                                return Evento_Foco_Obtenido(reinterpret_cast<HWND>(wParam));
                                                            case WM_KILLFOCUS :
                                                                return Evento_Foco_Perdido(reinterpret_cast<HWND>(wParam));
															case DWL_TOOLTIPEX_MOSTRAR :
																return Evento_MostrarToolTip(static_cast<UINT>(wParam), lParam);
															case DWL_TOOLTIPEX_OCULTAR : 
																return Evento_OcultarToolTip(static_cast<UINT>(wParam), lParam);
                                                        }
                                                        return DWL_USAR_GESTOR_POR_DEFECTO;
                                                    };
                 protected : ///////////////////////// Miembros protegidos
											        //! Función que habilita los mensajes WM_MOUSELEAVE.
											        /*!	Esta funcion habilita los mensajes WM_MOUSELEAVE.
													        \fn			inline bool _MirarMouseLeave(void);
													        \return		Devuelve true si el mouse esta dentro, false en caso contrario.
											        */
                  inline bool                      _MirarMouseLeave(void) {
			                                            if (_MouseDentro == false) {
				                                            TRACKMOUSEEVENT Trk;
				                                            Trk.cbSize = sizeof(TRACKMOUSEEVENT);
				                                            Trk.dwFlags = TME_LEAVE;
				                                            Trk.hwndTrack = _hWnd;
				                                            TrackMouseEvent(&Trk);
				                                            _MouseDentro = true;
				                                            return true;
			                                            }
			                                            return false;
		                                            };

												    //! Valor que determina si el mouse esta dentro del control
		          bool                             _MouseDentro;

            };

        };
    };
};

#endif
