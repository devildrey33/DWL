/*! \file DEventosBase.h
	\brief Archivo que contiene los eventos basicos para cualquier ventana / control.\n
	NOTA : para los controles de windows estandard no se debe utilizar esta clase, ya cada uno controla los eventos como quiere, y si estos se requieren deben ser personalizados para cada control.
*/
#ifndef DEVENTOSBASE_H
#define DEVENTOSBASE_H

#include "DBaseWnd.h"

#define DWL_EVENTOS_VALOR_DEVUELTO 0

//! Espacio de nombres DWL
namespace DWL {
    //! Clase base para los eventos por defecto de cualquier ventana / control
    template <typename TIPO_DEVUELTO> class DEventosBase : public DBaseWnd {

        public : //////////////////////////////// Mimebros publicos
			virtual const DEnum_Objeto		Objeto_Tipo(void) { return DEnum_Objeto::DEnum_Objeto_EventosBase; };


		                                    //! Constructor.
		                                    /*! Constructor.
													\fn			DEventosBase(void);
													\return		No devuelve nada.
		                                    */
											DEventosBase(void) : DBaseWnd(), _MouseDentro(false), _VentanaActivada(false) {};

									        //! Función enlazada al mensaje WM_ERASEBKGND
											/*! Esta función se utiliza para responder al mensaje WM_ERASEBKGND.
													\fn			inline virtual TIPO_DEVUELTO Evento_BorrarFondoHDC(HDC hDC);
													\param[in]	hDC	: HDC para borrar.
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
			 								*/
			inline virtual TIPO_DEVUELTO    Evento_BorrarFondoHDC(HDC hDC)																		{ return DWL_USAR_GESTOR_POR_DEFECTO; };

									        //! Función enlazada al mensaje WM_PAINT
											/*! Esta función se utiliza para responder al mensaje WM_PAINT, hay que utilizar BeginPaint y EndPaint para crear el DC.
													\fn			inline virtual TIPO_DEVUELTO Evento_Pintar(void);
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
			inline virtual TIPO_DEVUELTO    Evento_Pintar(void)																					{ return DWL_USAR_GESTOR_POR_DEFECTO; };

											//! Función enlazada al mensaje WM_PRINTCLIENT
											/*! Esta función se utiliza para responder al mensaje WM_PRINTCLIENT.
													\fn			inline virtual TIPO_DEVUELTO Evento_PintarCliente(HDC hDC, LPARAM lParam);
													\param[in]	hDC					: hDC donde hay que pintar
													\param[in]  lOpcionesPintado	: opciones de pintado consulta http://msdn.microsoft.com/en-us/library/windows/desktop/dd145217(v=vs.85).aspx
													\return		Si vas a re-emplazar este mensaje debes retornar TRUE.
											*/
			inline virtual TIPO_DEVUELTO    Evento_PintarCliente(HDC hDC, LPARAM lOpcionesPintado)												{ return DWL_USAR_GESTOR_POR_DEFECTO; };

											//! Función enlazada al mensaje WM_NCPAINT
											/*! Esta función se utiliza para responder al mensaje WM_NCPAINT.
													\fn			inline virtual TIPO_DEVUELTO Evento_NCPintar(HRGN RegionVentana);
													\param[in]	RegionVentana	: Region de la ventana.
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
			inline virtual TIPO_DEVUELTO    Evento_NCPintar(HRGN RegionVentana)																	{ return DWL_USAR_GESTOR_POR_DEFECTO; };

											//! Función enlazada al mensaje WM_NCCALCSIZE
											/*! Esta función se utiliza para responder al mensaje WM_NCCALCSIZE.
													\fn				inline virtual TIPO_DEVUELTO Evento_NCCalcularTam(WPARAM wAccion, LPARAM lParam);
													\param[inout]	lParam	: Si wAccion es TRUE, lParam es un puntero hacia una estructura NCCALCSIZE_PARAMS. Si wAccion es FALSE lParam es un puntero hacia una estructura RECT.
													\return			Si vas a re-emplazar este mensaje debes retornar 0. Para mas info consulta el mensaje WM_NCCALCSIZE en la MSDN.
											*/
			inline virtual TIPO_DEVUELTO    Evento_NCCalcularTam(WPARAM wAccion, LPARAM lParam)													{ return DWL_USAR_GESTOR_POR_DEFECTO; };

											//! Función enlazada al mensaje WM_NCHITTEST
											/*! Esta función se utiliza para responder al mensaje WM_NCHITTEST.
													\fn			inline virtual TIPO_DEVUELTO Evento_NCHitTest(const int nX, const int nY);
													\param[in]	nX	: Coordenada X.
													\param[in]	nY	: Coordenada Y.
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
			inline virtual TIPO_DEVUELTO    Evento_NCHitTest(const int nX, const int nY)														{ return DWL_USAR_GESTOR_POR_DEFECTO; };

											//! Función enlazada al mensaje WM_NCACTIVATE
											/*! Esta función se utiliza para responder al mensaje WM_NCACTIVATE.
													\fn				inline virtual TIPO_DEVUELTO Evento_NCActivar(WPARAM wActivado, LPARAM lEstiloVisual);
													\param[in]		wActivado		: TRUE si la barra de titulo está activa, FALSE en caso contrario.
													\param[inout]	lEstiloVisual	: Solo se usa si no hay un estilo visual activo, consulta el mensaje WM_NCACTIVATE en la MSDN para mas info.
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
			inline virtual TIPO_DEVUELTO    Evento_NCActivar(WPARAM wActivado, LPARAM lEstiloVisual)											{ return DWL_USAR_GESTOR_POR_DEFECTO; };

											//! Función enlazada al mensaje WM_MOUSEMOVE
											/*! Esta función se utiliza para responder al mensaje WM_MOUSEMOVE.
													\fn			inline virtual TIPO_DEVUELTO Evento_NCMouse_Movimiento(const int cX, const int cY, const UINT HitTest);
													\param[in]  cX      : Coordenada X del mouse
													\param[in]  cY      : Coordenada Y del mouse
													\param[in]  HitTest : Identificador para los controles del marco de la ventana
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
			inline virtual TIPO_DEVUELTO    Evento_NCMouse_Movimiento(const int cX, const int cY, const UINT HitTest)							{ return DWL_EVENTOS_VALOR_DEVUELTO; };

											//! Función que recibe cuando el mouse entra en el control
											/*!	Esta función es la encargada de procesar cuando el mouse entra en el control.
													\fn			virtual TIPO_DEVUELTO Evento_NCMouse_Entrando(const int cX, const int cY, const UINT HitTest);
													\param[in]  cX      : Coordenada X del mouse
													\param[in]  cY      : Coordenada Y del mouse
													\param[in]  HitTest : Identificador para los controles del marco de la ventana
													\return		Si re-emplazas esta funcion debes retornar 0.
											*/
			inline virtual TIPO_DEVUELTO	Evento_NCMouse_Entrando(const int cX, const int cY, const UINT HitTest)								{ return DWL_EVENTOS_VALOR_DEVUELTO; };

											//! Función que recibe cuando el mouse se va del control
											/*!	Esta función es la encargada de procesar los mensajes WN_MOUSELEAVE.
													\fn			virtual TIPO_DEVUELTO Evento_NCMouse_Saliendo(void);
   												    \return		Si re-emplazas esta funcion debes retornar 0.
											*/
			inline virtual TIPO_DEVUELTO	Evento_NCMouse_Saliendo(void)																		{ return DWL_EVENTOS_VALOR_DEVUELTO; };


											//! Función enlazada al mensaje WM_CLOSE
											/*! Esta función se utiliza para responder al mensaje WM_CLOSE.
													\fn			inline virtual TIPO_DEVUELTO Evento_Cerrar(void);
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
            inline virtual TIPO_DEVUELTO    Evento_Cerrar(void)																					{ return DWL_USAR_GESTOR_POR_DEFECTO; };

									        //! Función enlazada al mensaje WM_DESTROY
											/*! Esta función se utiliza para responder al mensaje WM_DESTROY.
													\fn			inline virtual TIPO_DEVUELTO Evento_Destruir(void);
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
            inline virtual TIPO_DEVUELTO    Evento_Destruir(void)																				{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada al mensaje WM_SIZING
											/*! Esta función se utiliza para responder al mensaje WM_SIZING.
													\fn			inline virtual TIPO_DEVUELTO Evento_CambiandoTam(const UINT Lado, RECT *Rectangulo);
                                                    \param[in]  Lado       : Lateral por donde esta el mouse
                                                    \param[in]  Rectangulo : Nuevo rectangulo de la ventana
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
            inline virtual TIPO_DEVUELTO    Evento_CambiandoTam(const UINT Lado, RECT *Rectangulo)												{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada al mensaje WM_SIZE
											/*! Esta función se utiliza para responder al mensaje WM_SIZE.
													\fn			inline virtual TIPO_DEVUELTO Evento_CambioTam(const UINT Tipo, const int nAncho, const int nAlto);
                                                    \param[in]  Tipo   : Tipo de redimensión
                                                    \param[in]  nAncho : Nuevo ancho de la ventana
                                                    \param[in]  nAlto  : Nueva altura de la ventana
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
            inline virtual TIPO_DEVUELTO    Evento_CambioTam(const UINT Tipo, const int nAncho, const int nAlto)								{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada a los mensajes WM_*BUTTONDBLCLK
											/*! Esta función se utiliza para responder a los mensajes WM_*BUTTONDBLCLK.
													\fn			inline virtual TIPO_DEVUELTO Evento_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT Param);
                                                    \param[in]  Boton : Boton del mouse presionado
                                                    \param[in]  cX    : Coordenada X del mouse
                                                    \param[in]  cY    : Coordenada Y del mouse
                                                    \param[in]  Param : Teclas especiales presionadas.
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
            inline virtual TIPO_DEVUELTO    Evento_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT Param)				{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada a los mensajes WM_*BUTTONUP
											/*! Esta función se utiliza para responder a los mensajes WM_*BUTTONUP.
													\fn			inline virtual TIPO_DEVUELTO Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
                                                    \param[in]  Boton : Boton del mouse presionado
                                                    \param[in]  cX    : Coordenada X del mouse
                                                    \param[in]  cY    : Coordenada Y del mouse
                                                    \param[in]  Param : Teclas especiales presionadas.
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
            inline virtual TIPO_DEVUELTO    Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param)			{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada a los mensajes WM_*BUTTONDOWN
											/*! Esta función se utiliza para responder a los mensajes WM_*BUTTONDOWN.
													\fn			inline virtual TIPO_DEVUELTO Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param);
                                                    \param[in]  Boton : Boton del mouse presionado
                                                    \param[in]  cX    : Coordenada X del mouse
                                                    \param[in]  cY    : Coordenada Y del mouse
                                                    \param[in]  Param : Teclas especiales presionadas
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
            inline virtual TIPO_DEVUELTO    Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, UINT const Param)		{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada a los mensajes WM_NC*BUTTONDBLCLK
											/*! Esta función se utiliza para responder a los mensajes WM_NC*BUTTONDBLCLK.
													\fn			inline virtual TIPO_DEVUELTO Evento_NCMouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT HitTest);
                                                    \param[in]  Boton : Boton del mouse presionado
                                                    \param[in]  cX    : Coordenada X del mouse
                                                    \param[in]  cY    : Coordenada Y del mouse
                                                    \param[in]  Param : Teclas especiales presionadas.
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
			inline virtual TIPO_DEVUELTO    Evento_NCMouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT HitTest)				{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada a los mensajes WM_NC*BUTTONUP
											/*! Esta función se utiliza para responder a los mensajes WM_NC*BUTTONUP.
													\fn			inline virtual TIPO_DEVUELTO Evento_NCMouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT HitTest);
                                                    \param[in]  Boton : Boton del mouse presionado
                                                    \param[in]  cX    : Coordenada X del mouse
                                                    \param[in]  cY    : Coordenada Y del mouse
                                                    \param[in]  Param : Teclas especiales presionadas.
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
			inline virtual TIPO_DEVUELTO    Evento_NCMouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT HitTest)			{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada a los mensajes WM_NC*BUTTONDOWN
											/*! Esta función se utiliza para responder a los mensajes WM_NC*BUTTONDOWN.
													\fn			inline virtual TIPO_DEVUELTO Evento_NCMouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT HitTest);
                                                    \param[in]  Boton : Boton del mouse presionado
                                                    \param[in]  cX    : Coordenada X del mouse
                                                    \param[in]  cY    : Coordenada Y del mouse
                                                    \param[in]  Param : Teclas especiales presionadas
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
			inline virtual TIPO_DEVUELTO    Evento_NCMouse_BotonPresionado(const UINT Boton, const int cX, const int cY, UINT const HitTest)		{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada al mensaje WM_MOUSEMOVE
											/*! Esta función se utiliza para responder al mensaje WM_MOUSEMOVE.
													\fn			inline virtual TIPO_DEVUELTO Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);
                                                    \param[in]  cX    : Coordenada X del mouse
                                                    \param[in]  cY    : Coordenada Y del mouse
                                                    \param[in]  Param : Teclas especiales presionadas
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
            inline virtual TIPO_DEVUELTO    Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param)								{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada al mensaje WM_MOUSEWHEEL
											/*! Esta función se utiliza para responder al mensaje WM_MOUSEWHEEL.
													\fn			inline virtual TIPO_DEVUELTO Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const int VirtKey);
                                                    \param[in]  Delta   : Mobimiento de la rueda
                                                    \param[in]  cX      : Coordenada X del mouse
                                                    \param[in]  cY      : Coordenada Y del mouse
                                                    \param[in]  VirtKey : Teclas especiales presionadas
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
		    inline virtual TIPO_DEVUELTO    Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey)			{ return DWL_EVENTOS_VALOR_DEVUELTO; };

											//! Función que recibe cuando el mouse entra en el control
											/*!	Esta función es la encargada de procesar cuando el mouse entra en el control.
													\fn			virtual TIPO_DEVUELTO Evento_Mouse_Entrando(void);
   												    \return		Si re-emplazas esta funcion debes retornar 0.
											*/
			inline virtual TIPO_DEVUELTO	Evento_Mouse_Entrando(const int cX, const int cY, const UINT Param)									{ return DWL_EVENTOS_VALOR_DEVUELTO; };

											//! Función que recibe cuando el mouse se va del control
											/*!	Esta función es la encargada de procesar los mensajes WN_MOUSELEAVE.
													\fn			virtual TIPO_DEVUELTO Evento_Mouse_Saliendo(void);
   												    \return		Si re-emplazas esta funcion debes retornar 0.
											*/
			inline virtual TIPO_DEVUELTO	Evento_Mouse_Saliendo(void)																			{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada al mensaje WM_KEYDOWN
											/*! Esta función se utiliza para responder al mensaje WM_KEYDOWN.
													\fn			inline virtual TIPO_DEVUELTO Evento_Teclado_TeclaPresionada(const UINT Tecla, const UINT Repeticion, const UINT Params);
                                                    \param[in]  Tecla      : Tecla presionada
                                                    \param[in]  Repeticion : Repeticiones de la tecla
                                                    \param[in]  Params     : Teclas especiales presionadas
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
            inline virtual TIPO_DEVUELTO    Evento_Teclado_TeclaPresionada(const UINT Tecla, const UINT Repeticion, const UINT Params)			{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada al mensaje WM_KEYUP
											/*! Esta función se utiliza para responder al mensaje WM_KEYUP.
													\fn			inline virtual TIPO_DEVUELTO Evento_Teclado_TeclaSoltada(const UINT Tecla, const UINT Repeticion, const UINT Params);
                                                    \param[in]  Tecla      : Tecla soltada
                                                    \param[in]  Repeticion : Repeticiones de la tecla
                                                    \param[in]  Params     : Teclas especiales presionadas
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
            inline virtual TIPO_DEVUELTO    Evento_Teclado_TeclaSoltada(const UINT Tecla, const UINT Repeticion, const UINT Params)				{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada al mensaje WM_CHAR
											/*! Esta función se utiliza para responder al mensaje WM_CHAR.
													\fn			inline virtual TIPO_DEVUELTO Evento_Teclado_Caracter(const UINT Tecla, const UINT Repeticion, const UINT Params);
                                                    \param[in]  Tecla      : Tecla presionada
                                                    \param[in]  Repeticion : Repeticiones de la tecla
                                                    \param[in]  Params     : Teclas especiales presionadas
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
            inline virtual TIPO_DEVUELTO    Evento_Teclado_Caracter(const UINT Tecla, const UINT Repeticion, const UINT Params)					{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada al mensaje WM_SYSCHAR
											/*! Esta función se utiliza para responder al mensaje WM_SYSCHAR.
													\fn			inline virtual TIPO_DEVUELTO Evento_Teclado_CaracterDelSistema(const UINT Tecla, const UINT Repeticion, const UINT Params);
                                                    \param[in]  Tecla      : Tecla presionada
                                                    \param[in]  Repeticion : Repeticiones de la tecla
                                                    \param[in]  Params     : Teclas especiales presionadas
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
            inline virtual TIPO_DEVUELTO    Evento_Teclado_CaracterDelSistema(const UINT Tecla, const UINT Repeticion, const UINT Params)		{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada al mensaje WM_COMMAND
											/*! Esta función se utiliza para responder al mensaje WM_COMMAND.
													\fn			inline virtual TIPO_DEVUELTO Evento_Comando(const int cID, const UINT CodigoNotificacion, HWND hWndControl);
                                                    \param[in]  cID                : ID del control
                                                    \param[in]  CodigoNotificacion : Codigo de notificacion
                                                    \param[in]  hWndControl        : HWND del control
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
		    inline virtual TIPO_DEVUELTO    Evento_Comando(const int cID, const UINT CodigoNotificacion, HWND hWndControl)						{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada al mensaje WM_SYSCOMMAND
											/*! Esta función se utiliza para responder al mensaje WM_SYSCOMMAND.
													\fn			inline virtual TIPO_DEVUELTO Evento_ComandoDelSistema(const UINT cID, const int cX, const int cY)
                                                    \param[in]  cID : ID del menú
                                                    \param[in]  cX  : Coordenada X del mouse
                                                    \param[in]  cY  : Coordenada Y del mouse
													\return		Si vas a re-emplazar esta función deberias retornar DefWindowProc para los mensajes que no vayas a utilizar, y 0 para los mensajes que re-emplaces.
											*/
            inline virtual TIPO_DEVUELTO    Evento_ComandoDelSistema(const UINT cID, const int cX, const int cY)								{ return DefWindowProc(_hWnd, WM_SYSCOMMAND, static_cast<WPARAM>(cID), MAKELPARAM(cX, cY)); };

									        //! Función enlazada al mensaje WM_NOTIFY
											/*! Esta función se utiliza para responder al mensaje WM_NOTIFY.
													\fn			inline virtual TIPO_DEVUELTO Evento_Notificacion(const UINT cID, LPNMHDR Datos)
                                                    \param[in]  cID   : ID del control
                                                    \param[in]  Datos : Estructura que contiene mas datos sobre la notificación
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
		    inline virtual TIPO_DEVUELTO    Evento_Notificacion(const UINT cID, LPNMHDR Datos)													{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada al mensaje WM_TIMER
											/*! Esta función se utiliza para responder al mensaje WM_TIMER.
													\fn			inline virtual TIPO_DEVUELTO Evento_Temporizador(const UINT cID)
                                                    \param[in]  cID   : ID del temporizador
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
		    inline virtual TIPO_DEVUELTO   	Evento_Temporizador(const UINT cID)																	{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada al mensaje WM_SETFOCUS
											/*! Esta función se utiliza para responder al mensaje WM_SETFOCUS.
													\fn			inline virtual TIPO_DEVUELTO Evento_Foco_Obtenido(HWND FocoAnterior);
                                                    \param[in]  FocoAnterior        HWND del ultimo foco.
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
		    inline virtual TIPO_DEVUELTO    Evento_Foco_Obtenido(HWND FocoAnterior)																{ return DWL_EVENTOS_VALOR_DEVUELTO; };

									        //! Función enlazada al mensaje WM_KILLFOCUS
											/*! Esta función se utiliza para responder al mensaje WM_KILLFOCUS.
													\fn			inline virtual TIPO_DEVUELTO Evento_Foco_Obtenido(HWND NuevoFoco);
                                                    \param[in]  NuevoFoco       HWND del nuevo foco
													\return		Si vas a re-emplazar este mensaje debes retornar 0.
											*/
		    inline virtual TIPO_DEVUELTO    Evento_Foco_Perdido(HWND NuevoFoco)																	{ return DWL_EVENTOS_VALOR_DEVUELTO; };

				 							//! Función que recibe cuando hay que mostrar el tooltip
											/*! Esta función recibe cuando hay que mostrar el tooltip de este control.
													\fn         virtual TIPO_DEVUELTO Evento_MostrarToolTip(const UINT IDControl, LPARAM Param);
													\param[in]  IDControl : ID del control 
													\param[in]  Param     : Si param no es 0 hace referencia a la ID de un boton extra del control
													\return     Debes retornar 0 si re-emplazas esta función.
													\remarks    Param hace referencia a la ID de un boton extras que provengan de una DWLBarraScrollEx.
											*/
//			inline virtual TIPO_DEVUELTO    Evento_MostrarToolTip(const UINT IDControl, LPARAM Param)											{ return DWL_EVENTOS_VALOR_DEVUELTO; };

				 							//! Función que recibe cuando hay que ocultar el tooltip
											/*! Esta función recibe cuando hay que ocultar el tooltip de este control.
													\fn         virtual TIPO_DEVUELTO Evento_OcultarToolTip(const UINT IDControl, LPARAM Param);
													\param[in]  IDControl : ID del control 
													\param[in]  Param     : Si param no es 0 hace referencia a la ID de un boton extra del control
													\return     Debes retornar 0 si re-emplazas esta función.
													\remarks    Param hace referencia a la ID de un boton extras que provengan de una DWLBarraScrollEx.
											*/
//			inline virtual TIPO_DEVUELTO	Evento_OcultarToolTip(const UINT IDControl, LPARAM Param)											{ return DWL_EVENTOS_VALOR_DEVUELTO; };
 
          protected : ///////////////////////// Miembros protegidos

										    //! Esqueleto para los mensajes de la ventana.
										    /*! Esta función es el esqueleto para los mensajes del dialogo.
												    \fn			virtual TIPO_DEVUELTO CALLBACK	GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
												    \param[in]	uMsg	: Mensaje.
												    \param[in]	wParam	: Parametro1.
												    \param[in]	lParam	: Parametro2.
												    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
										    */
            virtual TIPO_DEVUELTO CALLBACK	GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
                                                static TIPO_DEVUELTO Ret = 0;
				                                switch (uMsg) {
                                                    // Eventos
                                                    case WM_ERASEBKGND :
                                                        return Evento_BorrarFondoHDC(reinterpret_cast<HDC>(wParam));
													case WM_PRINTCLIENT:
														return Evento_PintarCliente((HDC)wParam, lParam);
                                                    case WM_PAINT :
/*			                                            HDC DC;
			                                            PAINTSTRUCT ps;
			                                            DC = BeginPaint(_hWnd, &ps);                                                        
			                                            Ret = Evento_Pintar(DC, ps);
			                                            EndPaint(_hWnd, &ps);*/
														return Evento_Pintar();
													case WM_NCCALCSIZE:
														return Evento_NCCalcularTam(wParam, lParam);
													case WM_NCHITTEST:
														return Evento_NCHitTest(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
													case WM_NCACTIVATE :
														_VentanaActivada = (BOOL)wParam;
														return Evento_NCActivar(wParam, lParam);
													case WM_NCPAINT:
														return Evento_NCPintar((HRGN)wParam);

													case WM_NCMOUSEMOVE:
														if (_MirarMouseLeave() == true) this->Evento_NCMouse_Entrando(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
														return this->Evento_NCMouse_Movimiento(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_NCMOUSELEAVE:
														_MouseDentro = false;
														return Evento_NCMouse_Saliendo();

/*														HDC DCNC;
														DCNC = GetDCEx(_hWnd, (HRGN)wParam, DCX_WINDOW | DCX_CACHE | DCX_INTERSECTRGN | DCX_LOCKWINDOWUPDATE);
														Ret = Evento_NCPintar(DCNC, ps);
														ReleaseDC(_hWnd, DCNC);
														return Ret;*/
														break;
                                                    case WM_CLOSE :
                                                        return Evento_Cerrar();
                                                    case WM_DESTROY :
                                                        return Evento_Destruir();
                                                    case WM_SIZING :
                                                        return Evento_CambiandoTam(static_cast<UINT>(wParam), reinterpret_cast<RECT *>(lParam));
                                                    case WM_SIZE :
                                                        return Evento_CambioTam(static_cast<UINT>(wParam), LOWORD(lParam), HIWORD(lParam));
													case WM_LBUTTONDBLCLK:
														return Evento_Mouse_DobleClick(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_RBUTTONDBLCLK:
														return Evento_Mouse_DobleClick(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_MBUTTONDBLCLK:
														return Evento_Mouse_DobleClick(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_XBUTTONDBLCLK:
														return Evento_Mouse_DobleClick(HIWORD(wParam) + 2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_NCLBUTTONDBLCLK:
														return Evento_NCMouse_DobleClick(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_NCRBUTTONDBLCLK:
														return Evento_NCMouse_DobleClick(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_NCMBUTTONDBLCLK:
														return Evento_NCMouse_DobleClick(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_NCXBUTTONDBLCLK:
														return Evento_NCMouse_DobleClick(HIWORD(wParam) + 2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_LBUTTONDOWN:
														return Evento_Mouse_BotonPresionado(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_RBUTTONDOWN:
														return Evento_Mouse_BotonPresionado(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_MBUTTONDOWN:
														return Evento_Mouse_BotonPresionado(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_XBUTTONDOWN:
														return Evento_Mouse_BotonPresionado(HIWORD(wParam) + 2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));														
													case WM_NCLBUTTONDOWN:
														return Evento_NCMouse_BotonPresionado(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_NCRBUTTONDOWN:
														return Evento_NCMouse_BotonPresionado(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_NCMBUTTONDOWN:
														return Evento_NCMouse_BotonPresionado(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_NCXBUTTONDOWN:
														return Evento_NCMouse_BotonPresionado(HIWORD(wParam) + 2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_LBUTTONUP:
														return Evento_Mouse_BotonSoltado(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_RBUTTONUP:
														return Evento_Mouse_BotonSoltado(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_MBUTTONUP:
														return Evento_Mouse_BotonSoltado(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_XBUTTONUP:
														return Evento_Mouse_BotonSoltado(HIWORD(wParam) + 2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_NCLBUTTONUP:
														return Evento_NCMouse_BotonSoltado(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_NCRBUTTONUP:
														return Evento_NCMouse_BotonSoltado(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_NCMBUTTONUP:
														return Evento_NCMouse_BotonSoltado(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
													case WM_NCXBUTTONUP:
														return Evento_NCMouse_BotonSoltado(HIWORD(wParam) + 2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
														// Mouse leave
                                                    case WM_MOUSEMOVE :
                                                        if (_MirarMouseLeave() == true) this->Evento_Mouse_Entrando(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
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
/*													case DWL_TOOLTIPEX_MOSTRAR :
														return Evento_MostrarToolTip(static_cast<UINT>(wParam), lParam);
													case DWL_TOOLTIPEX_OCULTAR : 
														return Evento_OcultarToolTip(static_cast<UINT>(wParam), lParam);*/
                                                }
                                                return DWL_USAR_GESTOR_POR_DEFECTO;
                                            };
											//! Función que habilita los mensajes WM_MOUSELEAVE.
											/*!	Esta funcion habilita los mensajes WM_MOUSELEAVE.
													\fn			inline bool _MirarMouseLeave(void);
													\return		Devuelve true si el mouse esta dentro, false en caso contrario.
											*/
            inline bool                    _MirarMouseLeave(void) {
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
		    bool                           _MouseDentro;
											//! Valor que determina si la ventana esta activa y ella o uno de sus hijos tiene el foco.
			BOOL						   _VentanaActivada;

    };

};

#endif
