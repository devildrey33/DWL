//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DWLMarcaEx.h																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Descripción :																																//
//					Este control simula un checkbox de windows.																					//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Este archivo contiene varias clases descritas a continuacion :																				//
// - DWLMarcaEx_Colores			:	Clase que enlaza los colores a la configuracion del skin por defecto										//
//									Puedes modificar cualquier color de esta clase, solo deberas repintar el control al terminar.				//
//																																				//
// - DWLMarcaEx_Nucleo			:	Clase que contiene las Funciónes basicas para pintar y controlar los eventos del control.						//
//									Esta clase se ha creado de forma que puede compartir un control con otra clase, asi podemos hacer controles	//
//									tipo ComboBox y de una forma mucho mas limpia.																//
//																																				//
// - DWLMarcaEx					:	Clase que hereda de DWLMarcaEx_Nucleo y lo enlaza a un control para el solo.								//
//									Esta clase es la que deberiamos usar para crear un boton estandar sin complicaciones.						//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Archivo creado por devildrey33 el dia 01/12/2004	para http://www.devildrey33.es																//
// Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :		//
//  http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																		//
//  http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)																//
//  http://www.softcatala.cat/wiki/GPL3		 (Catalá, traduccion no oficial)																	//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Version 0.95																																	//
// Ultima modificación : 05/11/2009																												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file DWLMarcaEx.h
	\brief Archivo que contiene las definiciones de las clases de la MarcaEx
*/ 

#ifndef DWL_MARCAEX_H
#define DWL_MARCAEX_H
#include "DWLControlEx.h"
#include ".\DWLMarcaEx\DWLMarcaEx_Nucleo.h"


//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

		//! Clase que une DWLControlEx con DWLMarcaEx_Nucleo, para formar un control MarcaEx
        class DWLMarcaEx : public DWLMarcaEx_Nucleo, public DWL::ControlesEx::Base::DWLControlEx {
		public : ///////////////////////// Miembros publicos

										//! Constructor.
										/*!	Constructor por defecto.
												\fn		DWLMarcaEx(void);
												\return	No devuelve nada.
										*/
										DWLMarcaEx(void);

										//! Destructor.
										/*!	Destructor.
												\fn		~DWLMarcaEx(void);
												\return	No devuelve nada.
										*/
									   ~DWLMarcaEx(void);

										//! Función que retorna si esta ventana tiene el raton encima.
										/*!	Esta funcion devuelve si esta ventana tiene el raton encima.
												\fn			virtual bool Foco(void);
												\return		Devuelve true si el raton esta encima del control, false en caso contrario.
										*/
		 virtual bool				    Foco(void);

										//! Función que crea la MarcaEx.
										/*!	Esta función crea la MarcaEx.
												\fn			HWND CrearMarcaEx(const long Estilos, HWND hWndParent, const TCHAR *Txt, const int cX, const int cY, const int cID, const bool cMarcado = false);
												\param[in]	Estilos		: Estilos para el ArbolEx (WS_CHILD | WS_VISIBLE).
												\param[in]	hWndParent	: HWND del control que sera el padre de la MarcaEx.
                                                \param[in]  Txt         : Texto para el control
												\param[in]	cX			: Posicion X.
												\param[in]	cY			: Posicion Y.
												\param[in]	cID			: ID de la MarcaEx.
												\param[in]	cMarcado	: Parametro si el control esta marcado o no inicialmente.
												\return		Devuelve el HWND de la MarcaEx. En caso de error devolvera NULL.
										*/
		 HWND                           CrearMarcaEx(const long Estilos, HWND hWndParent, const TCHAR *Txt, const int cX, const int cY, const int cID, const bool cMarcado = false);

										//! Función que conecta la MarcaEx de un dialogo.
										/*!	Esta función conecta la MarcaEx de un dialogo.
												\fn			HWND ConectarMarcaEx(HWND hWndParent, const TCHAR *Txt,const int cID, const bool cMarcado = false);
												\param[in]	hWndParent	: HWND del control que sera el padre de la MarcaEx.
                                                \param[in]  Txt         : Texto para el control
												\param[in]	cID			: ID de la MarcaEx.
												\param[in]	cMarcado	: Parametro si el control esta marcado o no inicialmente.
												\return		Devuelve el HWND de la MarcaEx. En caso de error devolvera NULL.
                                                \remarks    Esta función solo debe usarse con controles que se creen durante la creación del dialogo, si esta clase no pertenece a un dialogo, o se va a crear dinamicamente, no debes usar esta función.
										*/
		 HWND                           ConectarMarcaEx(HWND hWndParent, const TCHAR *Txt, const int cID, const bool cMarcado = false);

										//! Función para activar / desactivar la marca.
										/*!	Esta funcion activa / desactiva la marca.
												\fn			void Activado(const bool nActivar);
												\param[in]	nActivar	: Parametro en el que especificaremos si queremos activar o desactivar el BotonEx.
												\return		No devuelve nada.
										*/
		 void							Activado(const bool Activar);

										//! Función que retorna si la marca esta activada.
										/*!	Esta funcion devuelve si la marca esta activada.
												\fn			inline BOOL Activado(void);
												\return		Devuelve TRUE si la marca esta activada, FALSE en caso contrario.
										*/
		 inline BOOL				    Activado(void) {
											return (_MarcaEx_Estado != 3);
										};

										//! Función que repinta toda la MarcaEx.
										/*!	Esta función repinta toda la MarcaEx.
												\fn			void Repintar(const bool Forzar = false);
												\param[in]	Forzar : True para forzar el repintado, false para que la función decida si repintar.
												\return		No devuelve nada.
												\remarks	Cuando Forzar es false, esta función mira si ha cambiado algun estado interno,
															y de ser asi repinta el control, en caso contrario no hace nada.
										*/
		 void                           Repintar(const bool Forzar = false);

										//! Función que pinta toda la MarcaEx cuado se recibe un mensaje WM_PAINT.
										/*!	Esta función pinta la MarcaEx cuando se recibe un mensaje WM_PAINT.
												\fn			LRESULT Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);
												\param[in]	hDC	: hDC donde se pintara toda la MarcaEx.
                                                \param[in]  PS  : Estructura que contiene los datos del pintado
   												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT				Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);

										//! Función predefinida del mensaje WM_*BUTTONUP (Virtual)
										/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONUP.
												\fn			virtual LRESULT Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
												\param[in]	Boton	: Boton presionado.
												\param[in]	cX		: Coordenada X del mouse.
												\param[in]	cY		: Coordenada Y del mouse.
												\param[in]	wParam	: Teclas extendidas presionadas.
   												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT    			Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);

										//! Función predefinida del mensaje WM_*BUTTONDOWN (Virtual)
										/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONDOWN.
												\fn			virtual LRESULT Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param)
												\param[in]	Boton	: Boton presionado.
												\param[in]	cX		: Coordenada X del mouse.
												\param[in]	cY		: Coordenada Y del mouse.
												\param[in]	wParam	: Teclas extendidas presionadas.
   												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT				Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param);

										//! Función predefinida del mensaje WM_MOUSEMOVE.
										/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEMOVE.
												\fn			virtual LRESULT Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);
												\param[in]	cX		: Coordenada X del mouse.
												\param[in]	cY		: Coordenada Y del mouse.
												\param[in]	wParam	: Teclas extendidas presionadas.
   												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT				Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);

										//! Función que retorna si el control esta marcado.
										/*!	Esta funcion devuelve si el control esta marcado.
												\fn			inline bool Marcado(void) const;
												\return		Devuelve true si la MarcaEx esta marcada, false en caso contrario.
										*/
		 inline bool                    Marcado(void) const {
											return _MarcaEx_Marcado;
										};

										//! Función para marcar / desmarcar el control.
										/*!	Esta funcion marca / desmarca el control.
												\fn			inline void Marcar(const bool nMarca);
												\param[in]	nMarca	: True para marcar el control, false para desmarcarlo.
												\return		No devuelve nada.
										*/
		 inline void                    Marcar(const bool nMarca) {
											_MarcaEx_Marcado = nMarca;
											Repintar(true);
										};

										//! Función para asignar el texto del control.
										/*! Esta función se usa para asignar el texto del control.
												\fn			void Texto(const TCHAR *nTxt);
												\param[in]	nTxt : Cadena de caracteres que sera el nuevo texto del control.
												\return		No devuelve nada.
										*/
		 void                           Texto(const TCHAR *nTxt);

										//! Función que retorna el texto del control.
										/*! Esta función devuelve el texto del control.
												\fn			inline const TCHAR *Texto(void);
												\return		Devuelve un puntero al texto del control.
										*/
		 inline const TCHAR            *Texto(void) {
											return _MarcaEx_Texto();
										};

										//! Función que recibe cuando el mouse se va del control
										/*!	Esta función es la encargada de procesar los mensajes WN_MOUSELEAVE.
												\fn			virtual LRESULT Evento_Mouse_Saliendo(void);
   												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 LRESULT						Evento_Mouse_Saliendo(void);
		protected : ////////////////////// Miembros protegidos

										//! Esqueleto para los mensajes de la MarcaEx.
										/*! Esta función es el esqueleto para los mensajes de la MarcaEx.
												\fn			LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
												\param[in]	uMsg	: Mensaje.
												\param[in]	wParam	: Parametro1.
												\param[in]	lParam	: Parametro2.
												\return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
												\remarks	Esta función es el esqueleto del ArbolEx por donde pasaran todos sus mensajes.
										*/
		 virtual LRESULT CALLBACK		GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
		};								//
		////////////////////////////////// Fin DWLMarcaEx


	}
}




#endif // DWL_CLASEMARCAEX_H

// Version 0.8		[11/12/2007]
// -Se ha solucionado un memory leak bastante importante en la Función Evento_Pintar, ya que faltaba borrar el DC del Buffer.....
// -El codigo se ha modificado para poder editarlo mejor
// -Se han comentado las Funciónes del header


// Version 0.81		[31/12/2007]
// -Añadido pintado especial cuando el control tiene el foco
// -Añadido control sobre las pulsaciones del Intro y del Espacio para que actuen como si se presionara el control con el raton


// Version 0.95		[05/11/2009]
// -Retocado el sistema que se utilizaba para controlar los eventos del mouse, ahora solo se usara SetCapture al presionar el control.
// -Creada clase DWLMarcaEx_Nucleo, que contiene las Funciónes basicas de pintado y control de eventos para el control.
//  Ahora la clase DWLMarcaEx es un contenedor que hereda el nucleo y enlaza las Funciónes con sus respectivos eventos
