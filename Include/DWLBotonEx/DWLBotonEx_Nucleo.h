#ifndef DWL_BOTONEX_NUCLEO_H
#define DWL_BOTONEX_NUCLEO_H

#include "DWLBotonEx_Estilos.h"
#include "DWLBotonEx_ParametrosClick.h"
#include "..\DWLString.h"


 
//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres ControlesEx
	namespace ControlesEx {
		//! Clase nucleo para el BotonEx
		/*! Esta clase contiene las funciones de pintado, funciones de control para el teclado y el raton, y algunos eventos que podemos sobre-escribir.		*/
		class DWLBotonEx_Nucleo {
		 public : //////////////////////// Miembros publicos

										//! Constructor.
										/*! Constructor que enlaza la fuente de este control a la clase DWLEstilos.
											\fn			DWLBotonEx_Nucleo(void);
											\return		No devuelve nada.
										*/
										DWLBotonEx_Nucleo(void);

										//! Función para repintar el BotonEx.
										/*! Esta funcion se usa para repintar el BotonEx desde el nucleo.
											\fn			void BotonEx_Repintar(HWND hWndControl, const bool Forzar = false);
											\param[in]	hWndControl : HWND del control que contiene el nucleo del botonex.
											\param[in]  Forzar      : Forzar el repintado (por defecto false)
											\return		No devuelve nada.
										*/
		void                            BotonEx_Repintar(HWND hWndControl, const bool Forzar = false);

										//! Función que pinta el boton en el DC y espacio especificados.
										/*! Esta funcion pinta el BotonEx en las coordenadas y DC especificados.
												\fn			void BotonEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true, const bool PintarConMascara = false);;
												\param[in]	hDC					: DC en el que se va a pintar el BotonEx.
												\param[in]	Espacio				: Recta que delimita el espacio donde se puede pintar el BotonEx.
												\param[in]	TieneFoco			: Valor que determina si el arbol tiene el foco del raton (por defecto se usara la funcion Foco()).
												\param[in]	PintarConMascara	: Valor que determina si se va a pintar el contorno del control con SRCAND antes de pintar el control.
												\return		No devuelve nada.
												\remarks	Esta función esta preparada para pintar el BotonEx en un DC que no sea el suyo, o que sea compartido.
															Por ello debemos especificar las coordenadas donde se va a pintar, si tiene el foco del raton o no, y por ultimo si debemos
															pintar la mascara.
															El parametro PintarMascara solo es necesario si vamos a pintar el BotonEx en un DC que no es el suyo y requerimos el pintado
															del borde del control. Entonces la funcion de pintado pintara el contorno del BotonEx con SRCAND, y luego pintara el control
															con SRC_PAINT para que no se vean graficos desfasados en el borde.
										*/
		void							BotonEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true, const bool PintarConMascara = false);

										//! Función virtual que pinta el estado normal del boton.
										/*! Esta función virtual pinta el BotonEx en su estado normal.
												\fn			virtual void BotonEx_Evento_Pintar_EstadoNormal(HDC hDC, RECT *Espacio);
												\param[in]	hDC		: hDC donde se va a pintar el BotonEx.
												\param[in]	Espacio	: Espacio donde se pintara el BotonEx.
												\return		No devuelve nada.
												\remarks	Esta funcion pinta el fondo y el texto del boton.
												\sa			BotonEx_Evento_Pintar_EstadoResaltado(), BotonEx_Evento_Pintar_EstadoPresionado(), BotonEx_Evento_Pintar_EstadoDesactivado(), BotonEx_Evento_Pintar_Borde()
										*/
		 virtual void                   BotonEx_Evento_Pintar_EstadoNormal(HDC hDC, RECT *Espacio);

										//! Función virtual que pinta el estado resaltado del boton.
										/*! Esta función virtual pinta el BotonEx en su estado resaltado.
												\fn			virtual void BotonEx_Evento_Pintar_EstadoResaltado(HDC hDC, RECT *Espacio);
												\param[in]	hDC		: hDC donde se va a pintar el BotonEx.
												\param[in]	Espacio	: Espacio donde se pintara el BotonEx.
												\return		No devuelve nada.
												\remarks	Esta funcion pinta el BotonEx_Evento_Pintar_EstadoNormal y el texto del boton.
												\sa			BotonEx_Evento_Pintar_EstadoNormal(), BotonEx_Evento_Pintar_EstadoPresionado(), BotonEx_Evento_Pintar_EstadoDesactivado(), BotonEx_Evento_Pintar_Borde()
										*/
		 virtual void					BotonEx_Evento_Pintar_EstadoResaltado(HDC hDC, RECT *Espacio);

										//! Función virtual que pinta el estado presionado del boton.
										/*! Esta función virtual pinta el BotonEx en su estado presionado.
												\fn			virtual void BotonEx_Evento_Pintar_EstadoPresionado(HDC hDC, RECT *Espacio);
												\param[in]	hDC		: hDC donde se va a pintar el BotonEx.
												\param[in]	Espacio	: Espacio donde se pintara el BotonEx.
												\return		No devuelve nada.
												\remarks	Esta funcion pinta el BotonEx_Evento_Pintar_EstadoNormal y el texto del boton.
												\sa			BotonEx_Evento_Pintar_EstadoNormal(), BotonEx_Evento_Pintar_EstadoResaltado(), BotonEx_Evento_Pintar_EstadoDesactivado(), BotonEx_Evento_Pintar_Borde()
										*/
		 virtual void                   BotonEx_Evento_Pintar_EstadoPresionado(HDC hDC, RECT *Espacio);

										//! Función virtual que pinta el estado desactivado del boton.
										/*! Esta función virtual pinta el BotonEx en su estado desactivado.
												\fn			virtual void BotonEx_Evento_Pintar_EstadoDesactivado(HDC hDC, RECT *Espacio);
												\param[in]	hDC		: hDC donde se va a pintar el BotonEx.
												\param[in]	Espacio	: Espacio donde se pintara el BotonEx.
												\return		No devuelve nada.
												\remarks	Esta funcion pinta el BotonEx_Evento_Pintar_EstadoNormal y el texto del boton.
												\sa			BotonEx_Evento_Pintar_EstadoNormal(), BotonEx_Evento_Pintar_EstadoResaltado(), BotonEx_Evento_Pintar_EstadoPresionado(), BotonEx_Evento_Pintar_Borde()
										*/
		 virtual void                   BotonEx_Evento_Pintar_EstadoDesactivado(HDC hDC, RECT *Espacio);

										//! Función virtual que pinta el borde del boton.
										/*! Esta función virtual pinta el borde del BotonEx.
												\fn			virtual void BotonEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco);
												\param[in]	hDC			: hDC donde se va a pintar el BotonEx.
												\param[in]	Region		: Region que contiene el borde del BotonEx.
												\param[in]	TieneFoco	: Valor en el que determinamos si pintamos el borde con foco o sin foco.
												\return		No devuelve nada.
												\remarks	Esta funcion pinta el BotonEx_Evento_Pintar_EstadoNormal y el texto del boton.
												\sa			BotonEx_Evento_Pintar_EstadoNormal(), BotonEx_Evento_Pintar_EstadoResaltado(), BotonEx_Evento_Pintar_EstadoPresionado(), BotonEx_Evento_Pintar_Borde()
										*/
		 virtual void                   BotonEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco);

										//! Función que procesa las teclas presionadas en el BotonEx.
										/*! Esta función procesa las teclas presionadas en el BotonEx.
												\fn			void BotonEx_Teclado_TeclaPresionada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params);
												\param[in]	hWndControl	: HWND del control que contiene el BotonEx.
												\param[in]	Caracter    : Tecla que se ha presionado.
                                                \param[in]  Repeticion  : Repeticion de la tecla.
												\param[in]	Param		: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
												\return		No devuelve nada.
												\remarks    Esta función debe ser enlazada con el Evento_TeclaPresionada del control que vaya a contener el BotonEx.
												\sa			BotonEx_Teclado_TeclaSoltada()
										*/
		 void							BotonEx_Teclado_TeclaPresionada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params);

										//! Función que procesa las teclas soltadas en el BotonEx.
										/*! Esta función procesa las teclas presionadas en el BotonEx.
												\fn			void BotonEx_Teclado_TeclaSoltada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params);
												\param[in]	hWndControl	: HWND del control que contiene el BotonEx.
												\param[in]	Tecla		: Tecla que se ha soltado.
                                                \param[in]  Repeticion  : Repeticion de la tecla.
												\param[in]	Param		: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
												\return		No devuelve nada.
												\remarks    Esta función debe ser enlazada con el Evento_TeclaSoltada del control que vaya a contener el BotonEx.
												\sa			BotonEx_Teclado_TeclaPresionada()
										*/
		 void							BotonEx_Teclado_TeclaSoltada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params);

										//! Función que procesa el movimiento del mouse en el BotonEx.
										/*! Esta función procesa el movimiento del mouse en el BotonEx.
												\fn			const BOOL BotonEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param);
												\param[in]	hWndControl		: HWND del control que contiene el BotonEx.
												\param[in]	RectaControl	: Recta con el espacio del BotonEx.
												\param[in]	cX				: Coordenada X del mouse relativa al control.
												\param[in]	cX				: Coordenada Y del mouse relativa al control.
												\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
												\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
												\remarks    Esta función debe ser enlazada con el Evento_Mouse_Movimiento del control que vaya a contener el BotonEx.
												\sa			BotonEx_Mouse_BotonPresionado(), BotonEx_Mouse_BotonSoltado()
										*/
		 BOOL						    BotonEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param);

										//! Función que procesa los botones presionados del mouse en el BotonEx.
										/*! Esta función procesa los botones presionados del mouse en el BotonEx.
												\fn			BOOL BotonEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
												\param[in]	hWndControl		: HWND del control que contiene el BotonEx.
												\param[in]	RectaControl	: Recta con el espacio del BotonEx.
												\param[in]	Boton			: Boton del mouse presionado.
												\param[in]	cX				: Coordenada X del mouse relativa al control.
												\param[in]	cX				: Coordenada Y del mouse relativa al control.
												\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
												\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
												\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonPresionado del control que vaya a contener el BotonEx.
												\sa			BotonEx_Mouse_Movimiento(), BotonEx_Mouse_BotonSoltado()
										*/
		 BOOL						    BotonEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);

										//! Función que procesa los botones soltados del mouse en el BotonEx.
										/*! Esta función procesa los botones soltados del mouse en el BotonEx.
												\fn			BOOL BotonEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
												\param[in]	hWndControl		: HWND del control que contiene el BotonEx.
												\param[in]	RectaControl	: Recta con el espacio del BotonEx.
												\param[in]	Boton			: Boton del mouse presionado.
												\param[in]	cX				: Coordenada X del mouse relativa al control.
												\param[in]	cX				: Coordenada Y del mouse relativa al control.
												\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
												\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
												\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonSoltado del control que vaya a contener el BotonEx.
												\sa			BotonEx_Mouse_Movimiento(), BotonEx_Mouse_BotonPresionado()
										*/
		 BOOL						    BotonEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);

										//! Función para marcar el boton.
										/*! Esta función se usa para marcar / desmarcar el BotonEx.
												\fn			inline virtual void BotonEx_Marcado(const bool nMarcar);
												\param[in]	nMarcar : True para marcar el BotonEx, false para desmarcarlo.
												\return		No devuelve nada.
										*/
		 inline virtual void			BotonEx_Marcado(const bool nMarcar) {
											_BotonEx_Marcado = nMarcar;
										};

										//! Función que retorna si el boton esta marcado o no.
										/*! Esta función devuelve si el BotonEx esta marcado o no.
												\fn			inline const BotonEx_Marcado(void);
												\return		Devuelve true si esta macado, false en caso contrario.
										*/
		 inline bool				    BotonEx_Marcado(void) {
											 return _BotonEx_Marcado;
										};

										//! Función para asignar el texto del boton.
										/*! Esta función se usa para asignar el texto del BotonEx.
												\fn			inline virtual void BotonEx_Texto(const TCHAR *Txt);
												\param[in]	nTxt : Cadena de caracteres que sera el nuevo texto del BotonEx.
												\return		No devuelve nada.
										*/
		 inline virtual void            BotonEx_Texto(const TCHAR *nTxt) {
											_BotonEx_Texto = nTxt;
										};

										//! Función que retorna el texto del boton.
										/*! Esta función devuelve el texto del BotonEx.
												\fn			inline virtual const TCHAR *BotonEx_Texto(void);
												\return		Devuelve un puntero al texto del boton.
										*/
		 inline virtual const TCHAR    *BotonEx_Texto(void) {
											return _BotonEx_Texto();
										};

                                        //! Clase que contiene los estilos para el BotonEx
         DWLBotonEx_Estilos             BotonEx_Estilos;
 										//! Clase que contiene los colores del BotonEx.
//		 DWLBotonEx_Colores				BotonEx_Colores;
										//
										//! Clase que contiene las fuentes del BotonEx.
//		 DWL::SO::DWLEstilos_Fuente     BotonEx_Fuentes;
		protected : //////////////////////

										//! Estado del boton
		 int                           _BotonEx_Estado;

										//! Ultimo estado del boton
		 int                           _BotonEx_PEstado;

										//! El boton esta presionado
		 bool                          _BotonEx_Presionado;

										//! Tecla presionada
		 bool                          _BotonEx_TeclaPresionada;

										//! Texto del boton
		 DWLString                     _BotonEx_Texto;

										//! El boton esta marcado
		 bool                          _BotonEx_Marcado;
										
										//! El boton esta activado
		 bool                          _BotonEx_Activado;

										//! Parametros para un click de mouse
		 DWLBotonEx_ParametrosClick    _BotonEx_Params;
		};								//
		////////////////////////////////// Fin DWLBotonEx_Nucleo
    };
};

#endif

