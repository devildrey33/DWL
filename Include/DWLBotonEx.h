//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DWLBotonEx.h																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Descripción :																																//
//					Este control se puede usar como boton estandard, o como un boton marca (se queda presionado, y luego se des-presiona).		//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Este archivo contiene varias clases descritas a continuacion :																				//
// - DWLBotonEx_Colores			:	Clase que enlaza los colores a la configuracion del skin por defecto										//
//									Puedes modificar cualquier color de esta clase, solo deberas repintar el boton al terminar.					//
//																																				//
// - DWLBotonEx_ParametrosClick :	Clase utilizada internamente para pasar los datos de un click a la ventana padre.							//
//																																				//
// - DWLBotonEx_Nucleo			:	Clase que contiene las Funciónes basicas para pintar y controlar los eventos del boton.						//
//									Esta clase se ha creado de forma que puede compartir un control con otra clase, asi podemos hacer controles	//
//									tipo ComboBox y de una forma mucho mas limpia.																//
//																																				//
// - DWLBotonEx					:	Clase que hereda de DWLBotonEx_Nucleo y lo enlaza a un control para el solo.								//
//									Esta clase es la que deberiamos usar para crear un boton estandar sin complicaciones.						//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Archivo creado por devildrey33 el dia 05/12/2004	para http://www.devildrey33.es																//
// Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :		//
//  http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																		//
//  http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)																//
//  http://www.softcatala.cat/wiki/GPL3		 (Catalá, traduccion no oficial)																	//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Version 0.95																																	//
// Ultima modificación : 02/11/2009																												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
/*! \file DWLBotonEx.h
	\brief Archivo que contiene las definiciones de las clases del BotonEx

	\todo Implementar posibilidad de mostrar iconos solos, o con texto.
*/


#ifndef DWL_BOTONEX_H
#define DWL_BOTONEX_H

#include "DWLControlEx.h"
#include ".\DWLBotonEx\DWLBotonEx_Nucleo.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

		//! Clase que hereda de DWLBotonEx_Nucleo y DWLControlEx para formar un control BotonEx
        class DWLBotonEx : public DWL::ControlesEx::Base::DWLControlEx, public DWLBotonEx_Nucleo {
		public : ///////////////////////// Miembros publicos

										//! Constructor.
										/*!	Constructor por defecto.
												\fn		DWLBotonEx(void);
												\return	No devuelve nada.
										*/
										DWLBotonEx(void);

										//! Destructor.
										/*!	Destructor.
												\fn		~DWLBotonEx(void);
												\return	No devuelve nada.
										*/
  								       ~DWLBotonEx(void);

										//! Función que retorna si esta ventana tiene el raton encima.
										/*!	Esta funcion devuelve si esta ventana tiene el raton encima.
												\fn			virtual bool Foco(void);
												\return		Devuelve true si el raton esta encima del control, false en caso contrario.
										*/
		 virtual bool				    Foco(void);

										//! Función que crea el BotonEx
										/*!	Esta funcion crea el BotonEx.
												\fn			HWND CrearBotonEx(const long Estilos, HWND hWndParent, const TCHAR *nTxt, const int cX, const int cY, const int cAncho, const int cAlto, const UINT ID);
												\param[in]	Estilos			: Estilos para el BotonEx (WS_CHILD | WS_VISIBLE).
												\param[in]	hWndParent		: HWND del control que sera el padre del BotonEx.
												\param[in]	nTxt			: Texto para el BotonEx.
												\param[in]	cX				: Posicion X.
												\param[in]	cY				: Posicion Y.
												\param[in]	cAncho			: Ancho del BotonEx.
												\param[in]	cAlto			: Alto del BotonEx.
												\param[in]	cID				: ID del BotonEx.
												\return		Devuelve el HWND del BotonEx. En caso de error devolvera NULL.
										*/
		 HWND							CrearBotonEx(const long Estilos, HWND hWndParent, const TCHAR *nTxt, const int cX, const int cY, const int cAncho, const int cAlto, const UINT ID);

										//! Función que crea el BotonEx
										/*!	Esta funcion crea el BotonEx.
												\fn			HWND ConectarBotonEx(HWND hWndParent, const TCHAR *nTxt, const UINT cID);
												\param[in]	hWndParent		: HWND del control que sera el padre del BotonEx.
												\param[in]	nTxt			: Texto para el BotonEx.
												\param[in]	cID				: ID del BotonEx.
												\return		Devuelve el HWND del BotonEx. En caso de error devolvera NULL.
                                                \remarks    Esta función solo debe usarse con controles que se creen durante la creación del dialogo, si esta clase no pertenece a un dialogo, o se va a crear dinamicamente, no debes usar esta función.
										*/
		 HWND							ConectarBotonEx(HWND hWndParent, const TCHAR *nTxt, const UINT cID);

										//! Función para mover el BotonEx a la posicion y el tamaño especificados.
										/*!	Esta función mueve el BotonEx a la posicion y tamaño especificados.
												\fn			void Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = true);
												\param[in]	cX			: Nueva posicion X para el BotonEx.
												\param[in]	cY			: Nueva posicion Y para el BotonEx.
												\param[in]	cAncho		: Nuevo ancho para el BotonEx.
												\param[in]	cAlto		: Nueva altura para el BotonEx.
												\param[in]	cRepintar	: True para repintar el control, false para dejarlo sin repintar.
												\return		No devuelve nada.
										*/
		 void							Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool nRepintar = false) {
											SetWindowRgn(_hWnd, CreateRoundRectRgn(0, 0, cAncho + 1, cAlto + 1, 2, 2), FALSE);
											MoveWindow(_hWnd, cX, cY, cAncho, cAlto, nRepintar);
										};

										//! Función para marcar el boton.
										/*! Esta función se usa para marcar / desmarcar el BotonEx.
												\fn			inline virtual void Marcado(const bool nMarcar);
												\param[in]	nMarcar : True para marcar el BotonEx, false para desmarcarlo.
												\return		No devuelve nada.
										*/
		 inline void					Marcado(const bool nMarcar) {
											_BotonEx_Marcado = nMarcar;
											Repintar(true);
										};

										//! Función que retorna si el boton esta marcado o no.
										/*! Esta función devuelve si el BotonEx esta marcado o no.
												\fn			inline bool Marcado(void);
												\return		Devuelve true si esta macado, false en caso contrario.
										*/
		 inline bool				    Marcado(void) {
											return _BotonEx_Marcado;
										};

										//! Función para asignar el texto del boton.
										/*! Esta función se usa para asignar el texto del BotonEx.
												\fn			inline void Texto(const TCHAR *Txt);
												\param[in]	nTxt : Cadena de caracteres que sera el nuevo texto del BotonEx.
												\return		No devuelve nada.
										*/
		 inline void					Texto(const TCHAR *Txt) {
											_BotonEx_Texto = Txt;
											Repintar(true);
										};

										//! Función que retorna el texto del boton.
										/*! Esta función devuelve el texto del BotonEx.
												\fn			inline const TCHAR *Texto(void);
												\return		Devuelve un puntero al texto del boton.
										*/
		 inline const TCHAR            *Texto(void) {
											return _BotonEx_Texto();
										};

										//! Función que repinta todo el BotonEx.
										/*!	Esta función repinta todo el BotonEx incluyendo barras de scroll y botones extra.
												\fn			void Repintar(const bool Forzar = false);
												\param[in]	Forzar : True para forzar el repintado, false para que la funcion decida si repintar.
												\return		No devuelve nada.
												\remarks	Cuando Forzar es false, esta función mira si ha cambiado algun estado interno,
															y de ser asi repinta el control, en caso contrario no hace nada.
										*/
		 void							Repintar(const bool Forzar = false);

										//! Función para activar / desactivar el BotonEx.
										/*!	Esta funcion activa / desactiva el BotonEx.
												\fn			void Activado(const bool nActivar);
												\param[in]	nActivar	: Parametro en el que especificaremos si queremos activar o desactivar el BotonEx.
												\return		No devuelve nada.
										*/
		 void							Activado(const bool Activar);

										//! Función que retorna si el BotonEx esta activado.
										/*!	Esta funcion devuelve si el BotonEx esta activado.
												\fn			inline BOOL Activado(void);
												\return		Devuelve TRUE si el BotonEx esta activado, FALSE en caso contrario.
										*/
		 inline BOOL				    Activado(void) {
											return _BotonEx_Activado;
										};

										//! Función para mostrar / ocultar el boton.
										/*! Esta función muestra / oculta el BotonEx.
												\fn			void Visible(const bool nMostrar);
												\param[in]	nMostrar : True para mostrar el control, false para ocultarlo.
												\return		No devuelve nada.
										*/
		 void                           Visible(const bool nMostrar);

										//! Función que pinta todo el BotonEx cuado se recibe un mensaje WM_PAINT.
										/*!	Esta función pinta el BotonEx cuando se recibe un mensaje WM_PAINT.
												\fn			virtual LRESULT Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);
												\param[in]	hDC	: hDC donde se pintara todo el BotonEx.
                                                \param[in]  PS  : Estructura que contiene datos del pintado.
												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT				Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);

		protected : ////////////////////// Miembros protegidos

										//! Función predefinida del mensaje WM_*BUTTONUP (Virtual)
										/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONUP.
												\fn			virtual LRESULT Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
												\param[in]	Boton	: Boton presionado.
												\param[in]	cX		: Coordenada X del mouse.
												\param[in]	cY		: Coordenada Y del mouse.
												\param[in]	Param	: Teclas extendidas presionadas.
												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT				Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);

										//! Función predefinida del mensaje WM_*BUTTONDOWN (Virtual)
										/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONDOWN.
												\fn			virtual LRESULT Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param)
												\param[in]	Boton	: Boton presionado.
												\param[in]	cX		: Coordenada X del mouse.
												\param[in]	cY		: Coordenada Y del mouse.
												\param[in]	Param	: Teclas extendidas presionadas.
												\return		No devuelve nada.
												\return		Si re-emplazas esta funcion debes retornar 0.
                                        */
		 virtual LRESULT    			Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param);

										//! Función predefinida del mensaje WM_MOUSEMOVE.
										/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEMOVE.
												\fn			virtual LRESULT Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);
												\param[in]	cX		: Coordenada X del mouse.
												\param[in]	cY		: Coordenada Y del mouse.
												\param[in]	wParam	: Teclas extendidas presionadas.
												\return		Si re-emplazas esta funcion debes retornar 0.
                                        */
		 virtual LRESULT				Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);

										//! Función que recibe cuando el mouse se va del control.
										/*!	Esta función es la encargada de procesar los mensajes WN_MOUSELEAVE.
												\fn			virtual LRESULT Evento_Mouse_Saliendo(void);
												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT				Evento_Mouse_Saliendo(void);

										//! Función predefinida del mensaje WM_KEYDOWN (Virtual)
										/*!	Esta función es la encargada de procesar los mensajes WM_KEYDOWN.
												\fn			virtual LRESULT Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Param);
												\param[in]	Caracter   : Tecla virtual presionada.
                                                \param[in]  Repeticion : Repeticion de la tecla.
												\param[in]	Param	   : Teclas extendidas presionadas.
												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 LRESULT						Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Param);

										//! Función predefinida del mensaje WM_KEYUP (Virtual)
										/*!	Esta función es la encargada de procesar los mensajes WM_KEYUP.
												\fn			virtual void Evento_Teclado_TeclaSoltada(const int VirtKey, LPARAM lParam);
												\param[in]	Caracter   : Tecla virtual soltada.
                                                \param[in]  Repeticion : Repeticion de la tecla.
												\param[in]	Param	   : Teclas extendidas soltadas.
												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 LRESULT						Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Param);

										//! Esqueleto para los mensajes del BotonEx.
										/*! Esta función es el esqueleto para los mensajes del BotonEx.
												\fn			LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
												\param[in]	uMsg	: Mensaje.
												\param[in]	wParam	: Parametro1.
												\param[in]	lParam	: Parametro2.
												\return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
												\remarks	Esta función es el esqueleto del BotonEx por donde pasaran todos sus mensajes.
										*/
//		 LRESULT CALLBACK				GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
		};								//
		////////////////////////////////// Fin DWLBotonEx
	}
}


#endif // DWL_BOTONEX_H

// Version 0.72
// -Se ha cambiado la forma de mirar si el mouse esta encima del control o no
// 	 Antes se hacia con un SetCapture.. haora se usa TrackMouseEvent , y luego reservo SetCapture para cuando se pulsa el mouse solo
//   De esta forma al estar encima del boton no estara capturado y podras usar las teclas del sistema.
// -La distribucion del codigo ha cambiado de forma que sea mas facil editar tanto la clase independiente como la normal
// -Tambien se han comentado todas las Funciónes en el header

// Version 0.8
// -Se ha creado la clase Eventos_ClaseBotonEx
// -Se han añadido varios mensajes y ENLACES nuevos a este control


// Version 0.9 [31/12/2007]
// -Añadido pintado especial cuando el control tiene el foco
// -Añadido control sobre las pulsaciones del Intro y del Espacio para que actuen como si se presionara el control con el raton

// Version 0.9c [12/12/2008]
// -Reemplazada la std::string por la nueva clase DWLString

// Version 0.91 [25/02/2009]
// -Simplificados los mensajes de mouse, se han eliminado varios, y ahora se soporta los botones X

// Version 0.95 [02/11/2009]
// -Las clases para colores y fuentes han cambiado para que sean mas faciles de utilizar.
// -Se ha creado una clase Nucleo que contiene las Funciónes para el pintado y el control de eventos de forma que pueda ser compartida en un solo control.
// -Haora todos los eventos se pasan con PostMessage, de esta forma evitamos errores inesperados.
