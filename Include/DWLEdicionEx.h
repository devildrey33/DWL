// creacion : 25-09-2010

// OBJETIVOS :
//  Tener un control que pueda editar textos multilinea, y que ademas pueda tener fuentes y colores distintos en la misma linea.
// ENFOQUE :
//  La mejor forma de controlar tanto la posicion del cursor como los clicks del mouse es parseando el texto.
//  La idea es tener un objeto que controle los atributos del texto, fuente, color, etc.. e ir insertando dichos objetos a un array que formara una linea
//  ObjetoTexto { Fuente, Tamaño en pixeles X-Y, Color fondo, Color texto , Texto }
//  ObjetoLinea = ObjetoTexto, ObjetoTexto, etc...
//  DWLEdicionEx2_Nucleo = ObjetoLinea, ObjetoLinea, etc...
// PROBLEMAS PRINCIPALES :
//  Tipo de parsing que deberia seguir? es decir deberia hacer algo tipo doc, o a mi bola?
//  Como insertar datos a posiciones medias

// FASE BETA
 
#ifndef DWL_EDICIONTEXTOEX_H
#define DWL_EDICIONTEXTOEX_H

#include "DWLControlEx.h"
#include "DWLEdicionEx\DWLEdicionEx_Nucleo.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {
		//! Clase para la edición de texto
        class DWLEdicionEx : public ControlesEx::Base::DWLControlEx, public DWLEdicionEx_Nucleo {
		 public: ///////////////////////////////////// Miembros publicos

												    //! Constructor.
												    /*! Constructor.
													    \fn			DWLEdicionEx(void);
													    \return		No devuelve nada.
												    */
													DWLEdicionEx(void);

												    //! Destructor.
												    /*! Destructor.
													    \fn		   ~DWLEdicionEx(void);
													    \return		No devuelve nada.
												    */
                                                   ~DWLEdicionEx(void);

													//! Función que crea el EdicionEx.
													/*!	Esta funcion crea el EdicionEx.
															\fn			HWND CrearEdicionEx(const long Estilos, HWND hWndParent, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const bool nPintarBorde = true, const bool cMultiLinea = false);
															\param[in]	Estilos			: Estilos para el ArbolEx (WS_CHILD | WS_VISIBLE).
															\param[in]	hWndParent		: HWND del control que sera el padre del ArbolEx.
															\param[in]	cX				: Posicion X.
															\param[in]	cY				: Posicion Y.
															\param[in]	cAncho			: Ancho del ArbolEx.
															\param[in]	cAlto			: Alto del ArbolEx.
															\param[in]	cID				: ID del ArbolEx.
															\param[in]	cPintarBorde	: Parametro que indica si se tiene que pintar el borde del ArbolEx.
															\param[in]	cMultiLinea		: Parametro en el que especificaremos si el control acepta mas de una linea.
															\return		Devuelve el HWND del EdicionEx. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para mas información del error.
													*/
		 HWND                                       CrearEdicionEx(const long Estilos, HWND hWndParent, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const bool nPintarBorde = true, const bool cMultiLinea = false);

													//! Función que conecta el EdicionEx de un dialogo.
													/*!	Esta funcion conecta el EdicionEx de un dialogo.
															\fn			HWND ConectarEdicionEx(HWND hWndParent, const TCHAR *nTexto, const int cID, const bool nPintarBorde = true, const bool cMultiLinea = false);
															\param[in]	hWndParent		: HWND del control que sera el padre del EdicionEx.
															\param[in]	cID				: ID del EdicionEx.
															\param[in]	cPintarBorde	: Parametro que indica si se tiene que pintar el borde del EdicionEx.
															\param[in]	cMultiLinea		: Parametro en el que especificaremos si el control acepta mas de una linea.
															\return		Devuelve el HWND del EdicionEx. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para mas información del error.
															\remarks    Esta función solo debe usarse con controles que se creen durante la creación del dialogo, si esta clase no pertenece a un dialogo, o se va a crear dinamicamente, no debes usar esta función.
													*/
		 HWND                                       ConectarEdicionEx(HWND hWndParent, const TCHAR *nTexto, const int cID, const bool nPintarBorde = true, const bool cMultiLinea = false);
		 		 
												    //! Función para activar / desactivar el control
												    /*!	Esta función activa / desactiva  el control
														    \fn			void Activado(const bool nActivar);
														    \param[in]	nActivar	: Parametro en el que especificaremos si queremos activar o desactivar el control
														    \return		No devuelve nada.
												    */
		 inline void                                Activado(const bool Activar) {
														_EdicionEx_Activado = Activar;
														Repintar();
													};

												    //! Función que retorna si el control esta activado.
												    /*!	Esta funcion devuelve si el control esta activado.
														    \fn			virtual BOOL Activado(void);
														    \return		Devuelve TRUE si la el control esta activado, FALSE en caso contrario.
												    */
		 inline BOOL								Activado(void) {
														return static_cast<BOOL>(_EdicionEx_Activado);
													};

												    //! Función que asigna el texto del control.
												    /*!	Esta funcion asigna el texto del control.
														    \fn			void Texto(const TCHAR *nTexto);
															\param[in]  nTexto : Nueva cadena de caracteres para el control.
														    \return		No devuelve nada
												    */
         void                                       Texto(const TCHAR *nTexto);

												    //! Función que devuelve el texto del control.
												    /*!	Esta funcion devuelve el texto del control.
														    \fn			const TCHAR *Texto(void);
														    \return		Devuelve una cadena de caracteres con el texto del control.
												    */
         const TCHAR                               *Texto(void);

													//! Función virtual que sobre-escribe DWLBarraScrollEx::Repintar y permite el repintado del scroll.
													/*! Esta función virtual que sobre-escribe DWLBarraScrollEx::Repintar y permite el repintado del scroll.
															\fn			virtual void Repintar(const bool Forzar = false);
															\param[in]	nForzar	: Valor que determina si se fuerza el repintado.
															\return		No devuelve nada.
															\remarks	Si se espeficica false en nForzar la función repintar debera decidir si se repinta el control o no.
													*/
		 virtual void								Repintar(const bool Forzar = false);

												    //! Función para mover el control a la posición y el tamaño especificados.
												    /*!	Esta función mueve el control a la posición y tamaño especificados.
														    \fn			virtual void Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = true);
														    \param[in]	cX			: Nueva posición X para el control.
														    \param[in]	cY			: Nueva posición Y para el control.
														    \param[in]	cAncho		: Nuevo ancho para el control.
														    \param[in]	cAlto		: Nueva altura para el control.
														    \param[in]	cRepintar	: True para repintar el control, false para dejarlo sin repintar.
														    \return		No devuelve nada.
												    */
	     void										Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = false);


													//! Función predefinida del mensaje WM_KEYDOWN (Virtual)
													/*!	Esta función es la encargada de procesar los mensajes WM_KEYDOWN.
															\fn			virtual LRESULT Evento_Teclado_TeclaPresionada(const UINT Tecla, const UINT Repeticion, const UINT Param);
															\param[in]	Caracter   : Tecla virtual soltada.
															\param[in]	Repeticion : Repeticiones de la tecla
															\param[in]	Param	   : Teclas extendidas soltadas.
															\return		Si re-emplazas esta funcion debes retornar 0.
													*/
		 virtual LRESULT		    				Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Params);

													//! Función predefinida del mensaje WM_KEYUP (Virtual)
													/*!	Esta función es la encargada de procesar los mensajes WM_KEYUP.
															\fn			virtual LRESULT Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Param);
															\param[in]	Caracter   : Tecla virtual soltada.
															\param[in]	Repeticion : Repeticiones de la tecla
															\param[in]	Param	   : Teclas extendidas soltadas.
															\return		Si re-emplazas esta funcion debes retornar 0.
													*/
		 virtual LRESULT	    					Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Params);

									                //! Función enlazada al mensaje WM_CHAR
											        /*! Esta función se utiliza para responder al mensaje WM_CHAR.
													        \fn			inline virtual LRESULT Evento_Teclado_Caracter(const UINT Tecla, const UINT Repeticion, const UINT Params);
                                                            \param[in]  Tecla      : Tecla presionada
                                                            \param[in]  Repeticion : Repeticiones de la tecla
                                                            \param[in]  Params     : Teclas especiales presionadas
													        \return		Si vas a re-emplazar este mensaje debes retornar 0.
											        */
		 virtual LRESULT                            Evento_Teclado_Caracter(const UINT Caracter, const UINT Repeticion, const UINT Params);

													//! Función que pinta todo el EdicionEx cuado se recibe un mensaje WM_PAINT.
													/*!	Esta función pinta el EdicionEx cuando se recibe un mensaje WM_PAINT.
															\fn			LRESULT Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);
															\param[in]	hDC	: hDC donde se pintara todo el EdicionEx.
															\param[in]  PS  : Estructura que contiene los datos del pintado.
															\return		Si re-emplazas esta funcion debes retornar 0.
													*/
		 virtual LRESULT    						Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);
		 
													//! Función predefinida del mensaje WM_MOUSEMOVE.
													/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEMOVE.
															\fn			virtual LRESULT Evento_Mouse_Movimiento(const int cX, const int cY, const UINT wParam);
															\param[in]	cX		: Coordenada X del mouse.
															\param[in]	cY		: Coordenada Y del mouse.
															\param[in]	Param	: Teclas extendidas presionadas.
															\return		Si re-emplazas esta funcion debes retornar 0.
													*/
         virtual LRESULT                            Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);

													//! Función predefinida del mensaje WM_*BUTTONDOWN (Virtual)
													/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONDOWN.
															\fn			virtual LRESULT Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param)
															\param[in]	Boton	: Boton presionado.
															\param[in]	cX		: Coordenada X del mouse.
															\param[in]	cY		: Coordenada Y del mouse.
															\param[in]	wParam	: Teclas extendidas presionadas.
															\return		Si re-emplazas esta funcion debes retornar 0.
													*/
         virtual LRESULT                            Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param);

													//! Función predefinida del mensaje WM_*BUTTONUP (Virtual)
													/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONUP.
															\fn			virtual LRESULT Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
															\param[in]	Boton	: Boton presionado.
															\param[in]	cX		: Coordenada X del mouse.
															\param[in]	cY		: Coordenada Y del mouse.
															\param[in]	Param	: Teclas extendidas presionadas.
															\return		Si re-emplazas esta funcion debes retornar 0.
													*/
		 virtual LRESULT                            Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);

													//! Función predefinida del mensaje WM_MOUSEWHEEL.
													/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEWHEEL.
															\fn			virtual LRESULT Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey);
															\param[in]	Delta	: Valor de desplazamiento del mouse.
															\param[in]	cX		: Coordenada X.
															\param[in]	cY		: Coordenada Y.
															\param[in]	VirtKey	: Tecla virtual presionada.
															\return		Si re-emplazas esta funcion debes retornar 0.
													*/
		 virtual LRESULT                            Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey);

													//! Función que recibe cuando el mouse se va del control
													/*!	Esta función es la encargada de procesar los mensajes WN_MOUSELEAVE.
															\fn			virtual LRESULT Evento_Mouse_Saliendo(void);
															\return		Si re-emplazas esta funcion debes retornar 0.
													*/
		 virtual LRESULT                            Evento_Mouse_Saliendo(void);

													//! Función que enlaza el mensaje WM_TIMER con el control EdicionEx.
													/*! Esta función enlaza el mensaje WM_TIMER con el control EdicionEx.
															\fn			virtual LRESULT Evento_Temporizador(const UINT cID);
															\param[in]	cID : ID del temporizador.
															\return		No devuelve nada.
													*/
		 virtual LRESULT							Evento_Temporizador(const UINT cID);

													//! Función que procesa el mensaje WM_SETFOCUS
													/*! Esta funcion es la encargada de procesar el mensaje WM_SETFOCUS
															\fn			virtual LRESULT Evento_Foco_Obtenido(HWND FocoAnterior);
															\param[in]	FocoAnterior	: HWND de la ventana que tenia el foco antes que esta.
															\return		Si re-emplazas esta funcion debes retornar 0.
													*/
		 virtual LRESULT                            Evento_Foco_Obtenido(HWND FocoAnterior);

													//! Función que procesa el mensaje WM_KILLFOCUS
													/*! Esta funcion es la encargada de procesar el mensaje WM_KILLFOCUS
															\fn			virtual LRESULT Evento_Foco_Perdido(HWND NuevoFoco);
															\param[in]	NuevoFoco	: HWND de la ventana que recibira el foco despues de esta.
															\return		Si re-emplazas esta funcion debes retornar 0.
													*/
		 virtual LRESULT                            Evento_Foco_Perdido(HWND NuevoFoco);

		protected :
//		 virtual LRESULT CALLBACK					GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);

		};
    };
};

#endif