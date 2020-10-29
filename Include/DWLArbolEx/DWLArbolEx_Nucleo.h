#ifndef DWL_ARBOLEX_NUCLEO_H
#define DWL_ARBOLEX_NUCLEO_H

//#include "DWLArbolEx_Colores.h"
//#include "DWLArbolEx_ColoresNodo.h"
#include "DWLArbolEx_TerminarLabelEdit.h"
#include "DWLArbolEx_ParametrosClick.h"
#include "..\DWLBarraScrollEx.h"
#include "..\DWLToolTipEx.h"



 

//! Definicion para añadir nodos al principio
#define DWL_ARBOLEX_PRINCIPIO				 0
//! Definicion para añadir nodos ordenados alfabeticamente
#define DWL_ARBOLEX_ORDENADO				-1
//! Definicion para añadir nodos al final
#define DWL_ARBOLEX_FIN						-2

//! Enumeración de las alternativas para el HitTest.
enum DWL_Enum_ArbolEx_HitTest {
	DWL_Enum_ArbolEx_HitTest_Texto,			// Solo el texto
	DWL_Enum_ArbolEx_HitTest_Icono,			// Solo el icono
	DWL_Enum_ArbolEx_HitTest_Expansor,		// Solo el expansor
	DWL_Enum_ArbolEx_HitTest_Texto_Icono	// Texto icono y expansor
};

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

//        class DWLToolTipEx;
		//! Clase Nucleo del ArbolEx que hereda de DWLBarraScrollEx_Nucleo
		/*! Esta clase contiene las funciones de pintado, funciones de control para el teclado y el raton, y algunos eventos que podemos sobre-escribir.		*/
		class DWLArbolEx_Nucleo : public DWLBarraScrollEx_Nucleo {
		 public : ////////////////////////////

											//! Constructor.
											/*! Este constructor inicializa los datos internos del arbol por defecto.
													\fn			DWLArbolEx_Nucleo(void);
													\return		No devuelve nada.
											*/
											DWLArbolEx_Nucleo(void);

											//! Destructor.
											/*! Este destructor elimina de memoria los datos internos del arbol.
													\fn			~DWLArbolEx_Nucleo(void);
													\return		No devuelve nada.
											*/
										   ~DWLArbolEx_Nucleo(void);

											//! Función virtual que debera sobreescribir el control para repintar.
											/*! Esta funcion virtual debe ser re-escrita en la clase contenedora de este control para pintar todo el control.
													\fn			virtual void Repintar(const bool Forzar = false);
													\param[in]	nForzar	: Valor que determina si se fuerza el repintado.
													\return		No devuelve nada.
													\remarks	Si se espeficica false en nForzar, la funcion repintar debera decidir si se repinta el control o no.
											*/
		 virtual void						Repintar(const bool nForzar = false) {
										    };

											//! Función que pinta el arbol en el DC y espacio especificados.
											/*! Esta funcion pinta el ArbolEx en las coordenadas y DC especificados.
													\fn			void ArbolEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true, const bool PintarConMascara = false);;
													\param[in]	hDC					: DC en el que se va a pintar el ArbolEx.
													\param[in]	Espacio				: Recta que delimita el espacio donde se puede pintar el ArbolEx.
													\param[in]	TieneFoco			: Valor que determina si el arbol tiene el foco del raton (por defecto se usara la funcion Foco()).
													\param[in]	PintarConMascara	: Valor que determina si se va a pintar el contorno del control con SRCAND antes de pintar el control.
													\return		No devuelve nada.
													\remarks	Esta función esta preparada para pintar el ArbolEx en un DC que no sea el suyo, o que sea compartido.
																Por ello debemos especificar las coordenadas donde se va a pintar, si tiene el foco del raton o no, y por ultimo si debemos
																pintar la mascara.
																El parametro PintarMascara solo es necesario si vamos a pintar el ArbolEx en un DC que no es el suyo y requerimos el pintado
																del borde del control. Entonces la funcion de pintado pintara el contorno del ArbolEx con SRCAND, y luego pintara el control
																con SRC_PAINT para que no se vean graficos desfasados en el borde.
													\sa			ArbolEx_PintarNodo()
											*/
		 void								ArbolEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true, const bool PintarConMascara = false);

											//! Función que pinta un nodo del arbol en el DC y espacio especificados.
											/*! Esta función pinta el nodo del ArbolEx en el espacio y dc especificados.
													\fn			void ArbolEx_PintarNodo(HDC hDC, RECT *Espacio, DWLArbolEx_Nodo *nNodo, const int PosPag);
													\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
													\param[in]	Espacio	: Espacio del ArbolEx.
													\param[in]	PosPag	: Posicion del nodo en la pagina.
													\return		No devuelve nada.
													\remarks	La recta del Espacio debe contener el espacio para todo el ArbolEx, y no solo el del nodo.
																Luego dependiendo de la posicion de la pagina la función calcula internamente la recta para el nodo.
																La variable PosPag debe ser un numero entre 0 y _BarraScrollEx_Pagina.
													\sa			Repintar()
											*/
		 void								ArbolEx_PintarNodo(HDC hDC, RECT *Espacio, DWLArbolEx_Nodo *nNodo, const int PosPag);

											//! Función virtual que pinta el icono del nodo.
											/*! Esta función virtual pinta el icono del DWLArbolEx_Nodo en el espacio y dc especificados.
													\fn			virtual void ArbolEx_Evento_Pintar_Icono(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
													\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
													\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el icono.
													\param[in]	Espacio	: Espacio de 18x18 donde se va a pintar el icono.
													\return		No devuelve nada.
													\remarks	Esta funcion solo pinta iconos de 16x16, la razon de requerir 18 pixeles es para dejar
																uno de borde y otro para cuando se presiona el nodo.
											*/
		 virtual void						ArbolEx_Evento_Pintar_Icono(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);

											//! Función virtual que pinta el estado normal del nodo.
											/*! Esta función virtual pinta el texto del nodo en su estado normal.
													\fn			virtual void ArbolEx_Evento_Pintar_NodoNormal(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
													\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
													\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el texto.
													\param[in]	Espacio	: Espacio donde se pintara el texto del nodo.
													\return		No devuelve nada.
													\remarks	Esta funcion pone el color del texto, y luego lo pinta.
													\sa			ArbolEx_Pintar(), ArbolEx_Evento_Pintar_NodoResaltado(), ArbolEx_Evento_Pintar_NodoSeleccionado(), ArbolEx_Evento_Pintar_NodoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoPresionado();
											*/
		 virtual void						ArbolEx_Evento_Pintar_NodoNormal(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);

											//! Función virtual que pinta el estado resaltado del nodo.
											/*! Esta función virtual pinta el texto del nodo en su estado resaltado.
													\fn			virtual void ArbolEx_Evento_Pintar_NodoResaltado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
													\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
													\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el texto.
													\param[in]	Espacio	: Espacio donde se pintara el texto del nodo.
													\return		No devuelve nada.
													\remarks	Esta funcion pone el color del texto, y luego lo pinta.
													\sa			ArbolEx_Pintar(), ArbolEx_Evento_Pintar_NodoNormal(), ArbolEx_Evento_Pintar_NodoSeleccionado(), ArbolEx_Evento_Pintar_NodoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoPresionado();
											*/
		 virtual void						ArbolEx_Evento_Pintar_NodoResaltado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);

											//! Función virtual que pinta el estado seleccionado del nodo.
											/*! Esta función virtual pinta el texto del nodo en su estado seleccionado.
													\fn			virtual void ArbolEx_Evento_Pintar_NodoSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
													\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
													\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el texto.
													\param[in]	Espacio	: Espacio donde se pintara el texto del nodo.
													\return		No devuelve nada.
													\remarks	Esta funcion pone el color del texto, y luego lo pinta.
													\sa			ArbolEx_Pintar(), ArbolEx_Evento_Pintar_NodoNormal(), ArbolEx_Evento_Pintar_NodoResaltado(), ArbolEx_Evento_Pintar_NodoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoPresionado();
											*/
		 virtual void						ArbolEx_Evento_Pintar_NodoSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);

											//! Función virtual que pinta el estado sub-seleccionado del nodo.
											/*! Esta función virtual pinta el texto del nodo en su estado sub-seleccionado.
													\fn			virtual void ArbolEx_Evento_Pintar_NodoSubSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
													\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
													\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el texto.
													\param[in]	Espacio	: Espacio donde se pintara el texto del nodo.
													\return		No devuelve nada.
													\remarks	Esta funcion pone el color del texto, y luego lo pinta.
													\sa			ArbolEx_Pintar(), ArbolEx_Evento_Pintar_NodoNormal(), ArbolEx_Evento_Pintar_NodoResaltado(), ArbolEx_Evento_Pintar_NodoSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoPresionado();
											*/
		 virtual void						ArbolEx_Evento_Pintar_NodoSubSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);

											//! Función virtual que pinta el estado resaltado seleccionado del nodo.
											/*! Esta función virtual pinta el texto del nodo en su estado resaltado seleccionado.
													\fn			virtual void ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
													\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
													\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el texto.
													\param[in]	Espacio	: Espacio donde se pintara el texto del nodo.
													\return		No devuelve nada.
													\remarks	Esta funcion pone el color del texto, y luego lo pinta.
													\sa			ArbolEx_Pintar(), ArbolEx_Evento_Pintar_NodoNormal(), ArbolEx_Evento_Pintar_NodoResaltado(), ArbolEx_Evento_Pintar_NodoSeleccionado(), ArbolEx_Evento_Pintar_NodoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoPresionado();
											*/
		 virtual void						ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);

											//! Función virtual que pinta el estado resaltado sub-seleccionado del nodo.
											/*! Esta función virtual pinta el texto del nodo en su estado resaltado sub-seleccionado.
													\fn			virtual void ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
													\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
													\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el texto.
													\param[in]	Espacio	: Espacio donde se pintara el texto del nodo.
													\return		No devuelve nada.
													\remarks	Esta funcion pone el color del texto, y luego lo pinta.
													\sa			ArbolEx_Pintar(), ArbolEx_Evento_Pintar_NodoNormal(), ArbolEx_Evento_Pintar_NodoResaltado(), ArbolEx_Evento_Pintar_NodoSeleccionado(), ArbolEx_Evento_Pintar_NodoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(), ArbolEx_Evento_Pintar_NodoPresionado();
											*/
		 virtual void						ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);

											//! Función virtual que pinta el estado presionado del nodo.
											/*! Esta función virtual pinta el texto del nodo en su estado presionado.
													\fn			virtual void ArbolEx_Evento_Pintar_NodoPresionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
													\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
													\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el texto.
													\param[in]	Espacio	: Espacio donde se pintara el texto del nodo.
													\return		No devuelve nada.
													\remarks	Esta funcion pone el color del texto, y luego lo pinta.
													\sa			ArbolEx_Pintar(), ArbolEx_Evento_Pintar_NodoNormal(), ArbolEx_Evento_Pintar_NodoResaltado(), ArbolEx_Evento_Pintar_NodoSeleccionado(), ArbolEx_Evento_Pintar_NodoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado();
											*/
		 virtual void						ArbolEx_Evento_Pintar_NodoPresionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);

											//! Función virtual que pinta el fondo del arbol con AlphaBlend.
											/*! Esta función virtual pinta el fondo del arbol con AlphaBlend.
													\fn			virtual void ArbolEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio);
													\param[in]	hDC		: hDC donde se va a pintar el fondo del arbol.
													\param[in]	Espacio	: Espacio donde se pintara fondo del arbol.
													\return		No devuelve nada.
													\remarks	Si ArbolEx_Estilos.Transparencias es false, esta función no se usara.
											*/
		 virtual void						ArbolEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio);

											//! Función virtual que pinta el borde del ArbolEx.
											/*! Esta función virtual pinta el borde del ArbolEx.
													\fn			virtual void ArbolEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco);
													\param[in]	hDC			: hDC donde se va a pintar el borde del arbol.
													\param[in]	Region		: Region donde se pintara borde del arbol.
													\param[in]	TieneFoco	: Valor en el que determinamos si pintamos el borde con foco o sin foco.
													\return		No devuelve nada.
													\remarks	Si ArbolEx_Estilos.PintarBorde es false, esta función no se usara.
													\sa			ArbolEx_Pintar()
											*/
		 virtual void						ArbolEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco);

											//! Función virtual que pinta el expansor del DWLArbolEx_Nodo.
											/*! Esta función virtual pinta el expansor del DWLArbolEx_Nodo.
													\fn			virtual void ArbolEx_Evento_Pintar_Expansor(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
													\param[in]	hDC		: hDC donde se va a pintar el expansor del DWLArbolEx_Nodo.
													\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el expansor.
													\param[in]	Espacio	: Espacio donde se pintara el expansor del nodo.
													\return		No devuelve nada.
													\sa			ArbolEx_Pintar()
											*/
		 virtual void						ArbolEx_Evento_Pintar_Expansor(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);

											//! Función virtual que es llamada cuando se expande un DWLArbolEx_Nodo.
											/*! Esta función virtual es llamada cuando se expande un DWLArbolEx_Nodo.
													\fn			virtual void ArbolEx_Evento_Expandir(DWLArbolEx_Nodo *nNodoExpandido);
													\param[in]	nNodo	: DWLArbolEx_Nodo que se va a expandir.
													\return		No devuelve nada.
													\remarks    Esta función se usa principalmente si estamos creando el arbol al vuelo.
																Por ejemplo con una lista de directorios que se va rellenando cuando abres un directorio.
													\sa			ArbolEx_PintarNodo()
											*/
		 virtual void						ArbolEx_Evento_Expandir(DWLArbolEx_Nodo *nNodoExpandido) { };

											//! Función que procesa las teclas presionadas en el ArbolEx.
											/*! Esta función procesa las teclas presionadas en el ArbolEx.
													\fn			void ArbolEx_Teclado_TeclaPresionada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Param);
													\param[in]	hWndControl	: HWND del control que contiene el ArbolEx.
													\param[in]	Tecla		: Tecla que se ha presionado.
													\param[in]	Repeticion  : Repeticion de la tecla.
													\param[in]	Param		: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
													\return		No devuelve nada.
													\remarks    Esta función debe ser enlazada con el Evento_TeclaPresionada del control que vaya a contener el ArbolEx.
													\sa			ArbolEx_Teclado_TeclaPresionada()
											*/
		 void								ArbolEx_Teclado_TeclaPresionada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Param);

											//! Función que procesa las teclas soltadas en el ArbolEx.
											/*! Esta función procesa las teclas presionadas en el ArbolEx.
													\fn			void ArbolEx_Teclado_TeclaSoltada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Param);
													\param[in]	hWndControl	: HWND del control que contiene el ArbolEx.
													\param[in]	Tecla		: Tecla que se ha soltado.
													\param[in]	Repeticion  : Repeticion de la tecla.
													\param[in]	Param		: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
													\return		No devuelve nada.
													\remarks    Esta función debe ser enlazada con el Evento_TeclaSoltada del control que vaya a contener el ArbolEx.
													\sa			ArbolEx_Teclado_TeclaSoltada()
											*/
		 void								ArbolEx_Teclado_TeclaSoltada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Param);

											//! Función que procesa el movimiento del mouse en el ArbolEx.
											/*! Esta función procesa el movimiento del mouse en el ArbolEx.
													\fn			BOOL ArbolEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param);
													\param[in]	hWndControl		: HWND del control que contiene el ArbolEx.
													\param[in]	RectaControl	: Recta con el espacio del ArbolEx.
													\param[in]	cX				: Coordenada X del mouse relativa al control.
													\param[in]	cX				: Coordenada Y del mouse relativa al control.
													\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
													\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
													\remarks    Esta función debe ser enlazada con el Evento_Mouse_Movimiento del control que vaya a contener el ArbolEx.
													\sa			ArbolEx_Mouse_BotonPresionado(), ArbolEx_Mouse_BotonSoltado()
											*/
		 BOOL   							ArbolEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT wParam);

											//! Función que procesa los botones presionados del mouse en el ArbolEx.
											/*! Esta función procesa los botones presionados del mouse en el ArbolEx.
													\fn			BOOL ArbolEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
													\param[in]	hWndControl		: HWND del control que contiene el ArbolEx.
													\param[in]	RectaControl	: Recta con el espacio del ArbolEx.
													\param[in]	Boton			: Boton del mouse presionado.
													\param[in]	cX				: Coordenada X del mouse relativa al control.
													\param[in]	cX				: Coordenada Y del mouse relativa al control.
													\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
													\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
													\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonPresionado del control que vaya a contener el ArbolEx.
													\sa			ArbolEx_Mouse_Movimiento(), ArbolEx_Mouse_BotonSoltado()
											*/
		 BOOL   							ArbolEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);

											//! Función que procesa los botones soltados del mouse en el ArbolEx.
											/*! Esta función procesa los botones soltados del mouse en el ArbolEx.
													\fn			BOOL ArbolEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
													\param[in]	hWndControl		: HWND del control que contiene el ArbolEx.
													\param[in]	RectaControl	: Recta con el espacio del ArbolEx.
													\param[in]	Boton			: Boton del mouse presionado.
													\param[in]	cX				: Coordenada X del mouse relativa al control.
													\param[in]	cX				: Coordenada Y del mouse relativa al control.
													\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
													\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
													\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonSoltado del control que vaya a contener el ArbolEx.
													\sa			ArbolEx_Mouse_Movimiento(), ArbolEx_Mouse_BotonPresionado()
											*/
		 BOOL   							ArbolEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);

											//! Función que retorna el primer nodo visible en el ArbolEx.
											/*! Esta función retorna el primer nodo visible en el ArbolEx.
													\fn			DWLArbolEx_Nodo *ArbolEx_NodoInicioPagina(void);
													\return		Devuelve el primer DWLArbolEx_Nodo visible en el ArbolEx.
													\remarks    Esta funcion devolvera el primer nodo visible del arbol si existen nodos. En caso contrario retornara NULL.
													\sa			ArbolEx_NodoFinPagina()
											*/
		 DWLArbolEx_Nodo                   *ArbolEx_NodoInicioPagina(void);

											//! Función que retorna el ultimo nodo visible en el ArbolEx
											/*! Esta función retorna el ultimo nodo visible en el ArbolEx.
													\fn			DWLArbolEx_Nodo *ArbolEx_NodoFinPagina(void);
													\return		Devuelve el ultimo DWLArbolEx_Nodo visible en el ArbolEx.
													\remarks    Esta funcion devolvera el ultimo nodo visible del arbol si existen nodos. En caso contrario retornara NULL.
													\sa			ArbolEx_NodoInicioPagina()
											*/
		 DWLArbolEx_Nodo                   *ArbolEx_NodoFinPagina(void);

                                            //! Estilos para el ArbolEx
         DWLArbolEx_Estilos                 ArbolEx_Estilos;

											//! Función que recalcula los tamaños de todos los textos del ArbolEx.
											/*! Esta función recaltula los tamaños de todos los textos del ArbolEx.
													\fn			void ArbolEx_ActualizarTamTexto(void);
													\return		No devuelve nada.
											*/
		 void								ArbolEx_ActualizarTamTexto(void);

											//! Función que agrega un nodo al ArbolEx.
											/*! Esta función agrega un nodo al ArbolEx.
													\fn			DWLArbolEx_Nodo *ArbolEx_AgregarNodo(DWLArbolEx_Nodo *nPadre = NULL, const int nIcono = NULL, const TCHAR *nTexto = NULL, const int PosicionNodo = DWL_ARBOLEX_ORDENADO);
													\param[in]	nPadre			: Nodo padre de este nodo. Puede ser NULL.
													\param[in]	nIcono			: ID del icono para este nodo.
													\param[in]	nTexto			: Texto para el nodo.
													\param[in]	nPosicionNodo	: Posicion para el nodo que puede ser DWL_ARBOLEX_PRINCIPIO, DWL_ARBOLEX_ORDENADO, DWL_ARBOLEX_FIN, o un numero valido de posición.
													\return		Devuelve un puntero al DWLArbolEx_Nodo que se ha creado.
													\remarks	Cuando no necesites añadir mas nodos deberas llamar a la funcion ArbolEx_ActualizarTodo() para actualizar las listas enlazadas.
													\sa			ArbolEx_ActualizarTodo();
											*/
         inline DWLArbolEx_Nodo			   *ArbolEx_AgregarNodo(DWLArbolEx_Nodo *nPadre = NULL, const int nIcono = NULL, const TCHAR *nTexto = NULL, const int PosicionNodo = DWL_ARBOLEX_ORDENADO) {
                                                return ArbolEx_AgregarNodo(NULL, nPadre, nIcono, nTexto, PosicionNodo);
                                            };

											//! Función que agrega un nodo al ArbolEx.
											/*! Esta función agrega un nodo al ArbolEx.
													\fn			DWLArbolEx_Nodo *ArbolEx_AgregarNodo(DWLArbolEx_Nodo *nNodo = NULL, DWLArbolEx_Nodo *nPadre = NULL, const int nIcono = NULL, const TCHAR *nTexto = NULL, const int PosicionNodo = DWL_ARBOLEX_ORDENADO);
													\param[in]	nNodo			: Clase que hereda de DWLArbolEx_Nodo creada anteriormente. Puede ser NULL.
													\param[in]	nPadre			: Nodo padre de este nodo. Puede ser NULL.
													\param[in]	nIcono			: ID del icono para este nodo.
													\param[in]	nTexto			: Texto para el nodo.
													\param[in]	nPosicionNodo	: Posicion para el nodo que puede ser DWL_ARBOLEX_PRINCIPIO, DWL_ARBOLEX_ORDENADO, DWL_ARBOLEX_FIN, o un numero valido de posición.
													\return		Devuelve un puntero al DWLArbolEx_Nodo que se ha creado.
													\remarks	Puedes heredar la clase DWLArbolEx_Nodo y agregarle mas miembros, para luego añadirla al arbol utilizando esta funcion.
																Para ello deberas crear en memoria tu clase heredada, y pasarsela en el parametro nNodo.
																Una vez echo esto ya te puedes olvidar de eliminarla de memoria, ya que el mismo arbol se encargara de ello cuando no la necesite mas.
																Por ultimo cuando no necesites añadir mas nodos deberas llamar a la funcion ArbolEx_ActualizarTodo() para actualizar las listas enlazadas.
													\sa			ArbolEx_ActualizarTodo();
											*/
		 DWLArbolEx_Nodo				   *ArbolEx_AgregarNodo(DWLArbolEx_Nodo *nNodo = NULL, DWLArbolEx_Nodo *nPadre = NULL, const int nIcono = NULL, const TCHAR *nTexto = NULL, const int PosicionNodo = DWL_ARBOLEX_ORDENADO);

											//! Función que borra un nodo del ArbolEx.
											/*! Esta función borra el nodo especificado del ArbolEx.
													\fn			void ArbolEx_EliminarNodo(HWND hWndControl, DWLArbolEx_Nodo *bNodo, const bool Actualizar = true);
													\param[in]	hWndControl	: HWND del control que contiene el ArbolEx.
													\param[in]	nNodo		: DWLArbolEx_Nodo que se quiere eliminar.
													\param[in]	Actualizar	: Valor para decidir si se debe actualizar el ArbolEx.
													\return		No devuelve nada.
													\sa			ArbolEx_EliminarNodosSeleccionados(), ArbolEx_EliminarTodosLosNodos()
											*/
		 void								ArbolEx_EliminarNodo(HWND hWndControl, DWLArbolEx_Nodo *bNodo, const bool Actualizar = true);

											//! Función que borra todos los nodos selecionados.
											/*! Esta función borra todos los nodos selecionados del ArbolEx.
													\fn			void ArbolEx_EliminarNodosSeleccionados(HWND hWndControl, DWLArbolEx_Nodo *bNodo = NULL);
													\param[in]	hWndControl	: HWND del control que contiene el ArbolEx.
													\param[in]	bNodo		: DWLArbolEx_Nodo del que partira la busqueda de nodos seleccionados. Puede ser NULL.
													\return		No devuelve nada.
													\sa			ArbolEx_EliminarNodo(), ArbolEx_EliminarTodosLosNodos()
											*/
		 void								ArbolEx_EliminarNodosSeleccionados(HWND hWndControl, DWLArbolEx_Nodo *bNodo = NULL);

											//! Función que borra todos los nodos del ArbolEx.
											/*! Esta función borra todos los nodos del ArbolEx.
													\fn			void ArbolEx_EliminarTodosLosNodos(void);
													\return		No devuelve nada.
													\sa			ArbolEx_EliminarNodo(), ArbolEx_EliminarNodosSeleccionados()
											*/
		 void                               ArbolEx_EliminarTodosLosNodos(void);

											//! Función que des-seleciona todos los nodos.
											/*! Esta función des-selecciona todos los nodos del ArbolEx.
													\fn			void ArbolEx_DesSeleccionarTodo(const bool nRepintar = false);
													\param[in]	nRepintar	: Parametro en el que especificamos si deseamos repintar el ArbolEx.
													\return		No devuelve nada.
											*/
		 void                               ArbolEx_DesSeleccionarTodo(const bool nRepintar = false);

											//! Función que retorna el nodo que esta debajo de las coordenadas especificadas.
											/*! Esta función retorna el nodo o la parte del nodo que esta debajo de las coordenadas especificadas.
													\fn			DWLArbolEx_Nodo *ArbolEx_HitTest(const int cX, const int cY, const DWL_Enum_ArbolEx_HitTest Tipo = DWL_Enum_ArbolEx_HitTest_Texto_Icono);
													\param[in]	cX		: Coordenada X.
													\param[in]	cY		: Coordenada Y.
													\param[in]	nTipo	: Tipo de busqueda.
													\return		No devuelve nada.
													\remarks	Hay varios tipos de busqueda : [DWL_Enum_ArbolEx_HitTest_Texto] Solo el texto, [DWL_Enum_ArbolEx_HitTest_Icono] Solo el icono, [DWL_Enum_ArbolEx_HitTest_Expansor] Solo el expansor, [DWL_Enum_ArbolEx_HitTest_Texto_Icono] Texto, icono y expansor.
											*/
		 DWLArbolEx_Nodo				   *ArbolEx_HitTest(const int cX, const int cY, const DWL_Enum_ArbolEx_HitTest nTipo = DWL_Enum_ArbolEx_HitTest_Texto_Icono);

											//! Función que retorna el nodo padre de la posicion especificada.
											/*! Esta funcion devuelve el nodo padre de la posicion especificada.
													\fn			inline DWLArbolEx_Nodo *ArbolEx_Nodo(const size_t Pos);
													\param[in]	Pos : Posicion del DWLArbolEx_Nodo padre.
													\return		Devuelve el nodo especificado.
													\remarks	Esta funcion te da acceso solo a los nodos padre, si quieres acceso a todos los nodos del ArbolEx en una lista utiliza ArbolEx_NodoLineal()
													\sa			ArbolEx_TotalNodos(), ArbolEx_NodoLineal(), ArbolEx_NodoResaltado(), ArbolEx_NodoPresionado(), ArbolEx_NodoMarcado()
											*/
		 inline DWLArbolEx_Nodo		       *ArbolEx_Nodo(const size_t Pos) {
/*												if (Pos > _ArbolEx_Nodos.size()) {
													throw(1);
													return NULL;
												}*/
												return _ArbolEx_Nodos[Pos];
											};

											//! Función que retorna el nodo lineal de la posicion especificada.
											/*! Esta funcion devuelve el nodo lineal de la posicion especificada.
													\fn			inline DWLArbolEx_Nodo *ArbolEx_NodoLineal(const size_t Pos);
													\param[in]	Pos : Posicion del DWLArbolEx_Nodo lineal.
													\return		Devuelve el nodo especificado.
													\remarks	Esta funcion te da acceso a todos los nodos, si quieres acceso a solo a los nodos padre en una lista utiliza ArbolEx_Nodo().
													\sa			ArbolEx_TotalNodosLineales(), ArbolEx_Nodo(), ArbolEx_NodoResaltado(), ArbolEx_NodoPresionado(), ArbolEx_NodoMarcado()
											*/
		 inline DWLArbolEx_Nodo		       *ArbolEx_NodoLineal(const size_t Pos) {
												return _ArbolEx_NodosLineales[Pos];
											};

											//! Función que retorna el nodo resaltado.
											/*! Esta funcion devuelve el nodo resaltado.
													\fn			inline DWLArbolEx_Nodo *ArbolEx_NodoResaltado(void);
													\return		Devuelve el nodo resaltado, o NULL si no hay nodo resaltado.
													\sa			ArbolEx_Nodo(), ArbolEx_NodoLineal(), ArbolEx_NodoPresionado(), ArbolEx_NodoMarcado()
											*/
		 inline DWLArbolEx_Nodo            *ArbolEx_NodoResaltado(void) {
												return _ArbolEx_NodoResaltado;
											};

											//! Función que retorna el nodo presionado.
											/*! Esta funcion devuelve el nodo presionado.
													\fn			inline DWLArbolEx_Nodo *ArbolEx_NodoPresionado(void);
													\return		Devuelve el nodo presionado, o NULL si no hay nodo presionado.
													\sa			ArbolEx_Nodo(), ArbolEx_NodoLineal(), ArbolEx_NodoResaltado(), ArbolEx_NodoMarcado()
											*/
		 inline DWLArbolEx_Nodo            *ArbolEx_NodoPresionado(void) {
												return _ArbolEx_NodoPresionado;
											};

											//! Función que retorna el nodo marcado.
											/*! Esta funcion devuelve el nodo marcado.
													\fn			inline DWLArbolEx_Nodo *ArbolEx_NodoMarcado(void);
													\return		Devuelve el nodo marcado, o NULL si no hay nodo marcado.
													\sa			ArbolEx_Nodo(), ArbolEx_NodoLineal(), ArbolEx_NodoResaltado(), ArbolEx_NodoPresionado()
													\remarks	El nodo marcado es el nodo que tiene un borde distinto, y es por decirlo de una manera el cursor del teclado.
											*/
		 inline DWLArbolEx_Nodo            *ArbolEx_NodoMarcado(void) {
												return _ArbolEx_NodoMarcado;
											};

											//! Función que retorna el total de nodos en el ArbolEx.
											/*! Esta funcion devuelve el total de nodos padre en el ArbolEx.
													\fn			inline UINT ArbolEx_TotalNodos(void) const;
													\return		Devuelve el total de nodos padre.
													\sa			ArbolEx_Nodo(), ArbolEx_NodoLineal(), ArbolEx_TotalNodosLineales()
											*/
		 inline UINT            			ArbolEx_TotalNodos(void) const {
												return static_cast<unsigned int>(_ArbolEx_Nodos.size());
											};

											//! Función que retorna el total de nodos lineales en el ArbolEx.
											/*! Esta funcion devuelve el total de nodos lineales en el ArbolEx.
													\fn			inline UINT ArbolEx_TotalNodosLineales(void);
													\return		Devuelve el total de nodos lineales.
													\sa			ArbolEx_Nodo(), ArbolEx_NodoLineal(), ArbolEx_TotalNodos()
											*/
		 inline UINT			            ArbolEx_TotalNodosLineales(void) const {
												return static_cast<UINT>(_ArbolEx_NodosLineales.size());
											};

											//! Función que obtiene el espacio que necesita el nodo para ser pintado.
											/*! Esta funcion obtiene el espacio que necesita el nodo para ser pintado.
													\fn			void ArbolEx_ObtenerRectaNodo(DWLArbolEx_Nodo *nNodo, RECT *Rectangulo);
													\param[in]	nNodo		: Nodo del que queremos obtener el espacio.
													\param[out]	Rectangulo	: Recta en la que se asignara el espacio necesario para el nodo.
													\return		No devuelve nada.
											*/
		 void                               ArbolEx_ObtenerRectaNodo(DWLArbolEx_Nodo *nNodo, RECT *Rectangulo);

											//! Función que hace visible en la pantalla el nodo especificado.
											/*! Esta funcion hace visible en la pantalla el nodo especificado.
													\fn			void ArbolEx_HacerVisible(HWND hWndControl, DWLArbolEx_Nodo *vNodo, const bool nRepintar = false);
													\param[in]	hWndControl	: HWND del control que contiene el ArbolEx.
													\param[in]	nNodo		: Nodo que queremos hacer visible.
													\param[in]	nRepintar	: Variable en la que especificamos si hay que repintar.
													\return		No devuelve nada.
											*/
		 void                               ArbolEx_HacerVisible(HWND hWndControl, DWLArbolEx_Nodo *vNodo, const bool nRepintar = false);

											//! Función para expandir / contraer el nodo especificado.
											/*! Esta función expande / contrae el nodo especificado.
													\fn			void ArbolEx_Expandir(HWND hWndControl, DWLArbolEx_Nodo *vNodo, const bool nExpandir, const bool nRepintar = false);
													\param[in]	hWndControl	: HWND del control que contiene el ArbolEx.
													\param[in]	nNodo		: Nodo que queremos expandir / contraer.
													\param[in]	nExpandir	: Variable en la que especificamos si hay que expandir o contraer.
													\param[in]	nRepintar	: Variable en la que especificamos si hay que repintar.
													\return		No devuelve nada.
											*/
		 void                               ArbolEx_Expandir(HWND hWndControl, DWLArbolEx_Nodo *vNodo, const bool nExpandir, const bool nRepintar = false);

											//! Función que actualiza todos los datos del ArbolEx.
											/*! Esta función actualiza todos los datos del ArbolEx.
													\fn			void ArbolEx_ActualizarTodo(HWND hWndControl, RECT *Espacio, const bool ExpandirNodos);
													\param[in]	hWndControl	  : HWND del control que contiene el ArbolEx.
													\param[in]	Espacio		  : Recta que debe contener el espacio para el ArbolEx.
                                                    \param[in]  ExpandirNodos : Especifica true para que todos los nodos salgan expandidos, en caso contrario se mantendran como estaban.
													\return		No devuelve nada.
													\remarks	Esta función se usa para actualizar todos los estilos y nodos del ArbolEx. Si necesitas actualizar el tamaño de los textos por haber cambiado la fuente, deberas usar tambien ArbolEx_ActualizarTamTexto()
											*/
		 void                               ArbolEx_ActualizarTodo(HWND hWndControl, RECT *Espacio, const bool ExpandirNodos = false);

											//! Función que retorna los pixeles que tendra de alto cada nodo del ArbolEx.
											/*! Esta función retorna los pixeles que tendra de alto cada nodo del ArbolEx..
													\fn			inline int ArbolEx_AltoLinea(void) const;
													\return		Devuelve el alto de un nodo en pixeles.
													\remarks	Si vas a usar una fuente mas grande deberas asignar este tamaño manualmente.
											*/
		 inline int			        	    ArbolEx_AltoLinea(void) const {
												return _ArbolEx_AltoLinea;
											};

											//! Función para asignar los pixeles que tendra de alto cada nodo del ArbolEx.
											/*! Esta función asigna los pixeles que tendra de alto cada nodo del ArbolEx.
													\fn			void ArbolEx_AltoLinea(const int nAlto);
													\param[in]	nAlto : Nueva altura para los nodos del ArbolEx.
													\return		No devuelve nada.
													\remarks	Si vas a usar una fuente mas grande deberas asignar este tamaño manualmente.
											*/
		 void				                ArbolEx_AltoLinea(const int nAlto) {
												_ArbolEx_AltoLinea = nAlto;
											};

											//! Función para desactivar / activar las transparencias en el ArbolEx.
											/*! Esta función desactiva / activa las transparencias en el ArbolEx.
													\fn			void ArbolEx_DesactivarAlphaBlend(const bool nDesactivar);
													\param[in]	nDesactivar : True para desactivar transparencias, False para activarlas.
													\return		No devuelve nada.
													\remarks	Por defecto las transparecinas estan habilitadas.
											*/
/*		 void				                ArbolEx_DesactivarAlphaBlend(const bool nDesactivar) {
												_ArbolEx_DesactivarBlend = nDesactivar;
											};*/

											//! Función que procesa la tecla AvPag.
											/*! Esta función procesa la tecla AvPag.
													\fn			void ArbolEx_Tecla_AvancePagina(HWND hWndControl, const bool nRepintar = true);
													\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
													\param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
													\return		No devuelve nada.
											*/
		 void								ArbolEx_Tecla_AvancePagina(HWND hWndControl, const bool nRepintar = true);

											//! Función que procesa la tecla RePag.
											/*! Esta función procesa la tecla RePag.
													\fn			void ArbolEx_Tecla_RetrocesoPagina(HWND hWndControl, const bool nRepintar = true);
													\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
													\param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
													\return		No devuelve nada.
											*/
		 void								ArbolEx_Tecla_RetrocesoPagina(HWND hWndControl, const bool nRepintar = true);

											//! Función que procesa la tecla Inicio.
											/*! Esta función procesa la tecla Inicio.
													\fn			void ArbolEx_Tecla_Inicio(HWND hWndControl, const bool nRepintar = true);
													\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
													\param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
													\return		No devuelve nada.
											*/
		 void								ArbolEx_Tecla_Inicio(HWND hWndControl, const bool nRepintar = true);

											//! Función que procesa la tecla Fin.
											/*! Esta función procesa la tecla Fin.
													\fn			void ArbolEx_Tecla_Fin(HWND hWndControl, const bool nRepintar = true);
													\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
													\param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
													\return		No devuelve nada.
											*/
		 void								ArbolEx_Tecla_Fin(HWND hWndControl, const bool nRepintar = true);

											//! Función que procesa la tecla cursor Arriba.
											/*! Esta función procesa la tecla cursor Arriba.
													\fn			void ArbolEx_Tecla_Arriba(HWND hWndControl, const bool nRepintar = true);
													\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
													\param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
													\return		No devuelve nada.
											*/
		 void								ArbolEx_Tecla_Arriba(HWND hWndControl, const bool nRepintar = true);

											//! Función que procesa la tecla cursor Abajo.
											/*! Esta función procesa la tecla cursor Abajo.
													\fn			void ArbolEx_Tecla_Abajo(HWND hWndControl, const bool nRepintar = true);
													\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
													\param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
													\return		No devuelve nada.
											*/
		 void								ArbolEx_Tecla_Abajo(HWND hWndControl, const bool nRepintar = true);

											//! Función que procesa la tecla cursor Derecha.
											/*! Esta función procesa la tecla cursor Derecha.
													\fn			void ArbolEx_Tecla_Derecha(HWND hWndControl, const bool nRepintar = true);
													\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
													\param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
													\return		No devuelve nada.
											*/
		 void								ArbolEx_Tecla_Derecha(HWND hWndControl, const bool nRepintar = true);

											//! Función que procesa la tecla cursor Izquierda.
											/*! Esta función procesa la tecla cursor Izquierda.
													\fn			void ArbolEx_Tecla_Izquierda(HWND hWndControl, const bool nRepintar = true);
													\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
													\param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
													\return		No devuelve nada.
											*/
		 void								ArbolEx_Tecla_Izquierda(HWND hWndControl, const bool nRepintar = true);

											//! Función para empezar la edicion de un nodo.
											/*! Esta función inicia la edicion de un nodo.
													\fn			HWND ArbolEx_EmpezarLabelEdit(HWND hWndControl, DWLArbolEx_Nodo *nNodo, const bool Numerico);
													\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
													\param[in]	nNodo		: Nodo que se va a editar.
													\param[in]	Numerico	: True para que la edicion solo acepte digitos, false para que acepte todos los caracteres.
													\return		Devuelve el HWND del EditBox creado para editar el nodo.
													\sa			ArbolEx_TerminarLabelEdit(), ArbolEx_CancelarLabelEdit()
											*/
		 HWND								ArbolEx_EmpezarLabelEdit(HWND hWndControl, DWLArbolEx_Nodo *nNodo, const bool Numerico);

											//! Función para terminar la edicion de un nodo guardando los datos.
											/*! Esta función termina la edicion de un nodo guardando los datos.
													\fn			HWND ArbolEx_TerminarLabelEdit(HWND hWndControl);
													\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
													\return		No devuelve nada.
													\sa			ArbolEx_EmpezarLabelEdit(), ArbolEx_CancelarLabelEdit()
											*/
		 void								ArbolEx_TerminarLabelEdit(HWND hWndControl);

											//! Función para cancelar la edicion de un nodo sin guardar los datos.
											/*! Esta función cancela la edicion de un nodo sin guardar los datos.
													\fn			HWND ArbolEx_CancelarLabelEdit(HWND hWndControl);
													\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
													\return		No devuelve nada.
													\sa			ArbolEx_EmpezarLabelEdit(), ArbolEx_TerminarLabelEdit()
											*/
		 void								ArbolEx_CancelarLabelEdit(HWND hWndControl);

											//! Función virtual que monta los datos del tooltip antes de mostrarlo
											/*! Esta función virtual es llamada cuando el ArbolEx quiere mostrar un tooltip de un nodo.
													\fn			virtual void ArbolEx_Evento_MostrarToolTip(DWLArbolEx_Nodo *ttNodo);
													\param[in]	ttNodo : Nodo del que se va a mostrar la informacion.
													\return		No devuelve nada.
													\remarks	Por defecto el tooltip muestra el nombre y icono del nodo, y luego una lista con los 10 hijos siguientes.
																Puedes re-emplazar esta función y mostrar los datos que desees del nodo.
											*/
//		 virtual void						ArbolEx_Evento_MostrarToolTip(DWLArbolEx_Nodo *ttNodo);

											//! Clase que se ocupa de los tooltips
//		 DWLToolTipEx                       ArbolEx_ToolTip;
		protected : ////////////////////////// Miembros protegidos

											//! Función virtual que recibe cuando se hace un dobleclick en el control.
											/*! Esta función virtual es llamada cuando el ArbolEx recibe un doble click del mouse.
													\fn			virtual LRESULT ArbolEx_Evento_Mouse_DobleClick(const UINT Boton, const int cX, const int cY);
													\param[in]	Boton	: Boton del mouse presionado.
													\param[in]	cX		: Coordenada X del mouse.
													\param[in]	cY		: Coordenada Y del mouse.
													\return		No devuelve nada.
											*/
		 virtual LRESULT					ArbolEx_Evento_Mouse_DobleClick(const UINT Boton, const int cX, const int cY) { return 0; };

											//! Función que borra toda la memoria del ArbolEx.
											/*! Esta función borra toda la memora del ArbolEx, incluidos los nodos y sus fuentes propias.
													\fn			void ArbolEx_BorrarMemoria(void);
													\return		No devuelve nada.
											*/
		 void                               ArbolEx_BorrarMemoria(void);

											//! Función que retorna la fila donde esta posicionado el nodo en la pantalla.
											/*! Esta función retorna la fila donde esta posicionado el nodo en la pantalla.
													\fn			int ArbolEx_PosicionVisibleNodo(DWLArbolEx_Nodo *vNodo);
													\param[in]	vNodo : Nodo del que se quere averiguar su posicion visible.
													\return		Devuelve su posicion visible dentro del ArbolEx.
													\remarks	Esta funcion siempre retornara una posicion positiva, y puede retornar posiciones que quedan fuera del area visible del control.
											*/
		 int							    ArbolEx_PosicionVisibleNodo(DWLArbolEx_Nodo *vNodo);

											//! Función que enlaza todos los nodos lienales entre ellos.
											/*! Esta función enlaza todos los nodos lienales entre ellos.
													\fn			void ArbolEx_ActualizarVectorLineal(HWND hWndControl, const bool ExpandirTodo = false);;
													\param[in]	hWndControl		: HWND del control que contiene el ArbolEx.
													\param[in]	ExpandirTodo	: Parametro en el que especificamos si queremos los nodos expandidos o contraidos.
													\return		No devuelve nada.
											*/
		 void                               ArbolEx_ActualizarVectorLineal(HWND hWndControl, const bool ExpandirTodo = false);

											//! Función que recorre un nodo para enumerar todos sus nodos hijos y asi agregarlos al vector lineal.
											/*! Esta función recorre un nodo para enumerar todos sus nodos hijos y asi agregarlos al vector lineal.
													\fn			void ArbolEx_MirarHijosVectorLineal(DWLArbolEx_Nodo *nNodo, const bool ExpandirTodo);
													\param[in]	hWndControl		: HWND del control que contiene el ArbolEx.
													\param[in]	ExpandirTodo	: Parametro en el que especificamos si queremos los nodos expandidos o contraidos.
													\return		No devuelve nada.
													\remarks	Funcion de uso interno para ArbolEx_ActualizarVectorLineal().
											*/
		 void								ArbolEx_MirarHijosVectorLineal(DWLArbolEx_Nodo *nNodo, const bool ExpandirTodo);

											//! Función que pinta el borde del nodo marcado.
											/*! Esta función pinta el borde del nodo marcado.
													\fn			inline void _ArbolEx_EnmarcarRecta(HDC hDC, RECT *Espacio);
													\param[in]	hDC		: HDC donde se esta pintado el ArbolEx.
													\param[in]	Espacio	: Recta que contiene el espacio para el borde de la marca.
													\return		No devuelve nada.
													\remarks	Funcion de uso interno para ArbolEx_PintarNodo().
											*/
		 inline void					   _ArbolEx_EnmarcarRecta(HDC hDC, RECT *Espacio) {
												HBRUSH Brocha = CreateSolidBrush(ArbolEx_Estilos.Colores.BordeSeleccion());
												FrameRect(hDC, Espacio, Brocha);
												DeleteObject(Brocha);
												SetPixel(hDC, Espacio->left, Espacio->top, ArbolEx_Estilos.Colores.Fondo());
												SetPixel(hDC, Espacio->left, Espacio->bottom -1, ArbolEx_Estilos.Colores.Fondo());
												SetPixel(hDC, Espacio->right -1, Espacio->top, ArbolEx_Estilos.Colores.Fondo());
												SetPixel(hDC, Espacio->right -1, Espacio->bottom -1, ArbolEx_Estilos.Colores.Fondo());
											};

											//! Función que pinta una linea en las coordenadas especificadas.
											/*! Esta función pinta una linea en las coordenadas especificadas.
													\fn			inline void _ArbolEx_PintarLinea(HDC hDC, const int cX, const int cY, const int cX2, const int cY2)
													\param[in]	hDC	: HDC donde se esta pintado el ArbolEx.
													\param[in]	cX	: Coordenada X.
													\param[in]	cY	: Coordenada Y.
													\param[in]	cX2	: Coordenada X2.
													\param[in]	cY2	: Coordenada Y2.
													\return		No devuelve nada.
													\remarks	Funcion de uso interno para ArbolEx_PintarNodo().
											*/
		 inline void                       _ArbolEx_PintarLinea(HDC hDC, const int cX, const int cY, const int cX2, const int cY2) {
												MoveToEx(hDC, cX, cY, NULL);
												LineTo(hDC, cX2, cY2);
											};

											//! Nodo presionado
		 DWLArbolEx_Nodo				  *_ArbolEx_NodoPresionado;

											//! Nodo que marca el inicio del Shift
		 DWLArbolEx_Nodo			      *_ArbolEx_NodoShifteado;

											//! Nodo marcado (no es lo mismo que selecionado ni presionado)
		 DWLArbolEx_Nodo                  *_ArbolEx_NodoMarcado;

											//! Nodo resaltado
		 DWLArbolEx_Nodo                  *_ArbolEx_NodoResaltado;

											//! Ultimo nodo resaltado
		 DWLArbolEx_Nodo                  *_ArbolEx_UNodoResaltado;

											//! Nodo del ultimo click
		 DWLArbolEx_Nodo                  *_ArbolEx_PosUltimoClick;

											//! Expansor presionado
		 DWLArbolEx_Nodo                  *_ArbolEx_ExpansorPresionado;

											//! Expansor resaltado
		 DWLArbolEx_Nodo                  *_ArbolEx_ExpansorResaltado;

											//! Ultimo expansor resaltado
		 DWLArbolEx_Nodo                  *_ArbolEx_UExpansorResaltado;

											//! Tiempo que debe transcurrir para el dobleclick
		 DWORD						       _ArbolEx_UltimoClick;

											//! Ultimo boton presionado
		 UINT    						   _ArbolEx_UltimoBoton;

											//! Vector de nodos (Este vector solo contiene los nodos 'padre' del arbol)
		 std::vector<DWLArbolEx_Nodo *>    _ArbolEx_Nodos;

											//! Vector de nodos (Este vector contiene todos los nodos ordenados tal y como salen en el control)
		 std::vector<DWLArbolEx_Nodo *>    _ArbolEx_NodosLineales;

											//! HDC del buffer que se usa para pintar el control
		 HDC                               _ArbolEx_Buffer;

											//! Bitmap del buffer del control
		 HBITMAP                           _ArbolEx_Bmp;

											//! Bitmap antiguo del control
		 HBITMAP                           _ArbolEx_Viejo;

											//! DC para la foto de fondo
		 HDC                               _ArbolEx_FondoDC;

											//! Bitmap para la foto de fondo
		 HBITMAP                           _ArbolEx_BmpFondo;

											//! Bitmap antiguo del la foto de fondo
		 HBITMAP                           _ArbolEx_ViejoFondo;

											//! Fuente antigua
		 HFONT                             _ArbolEx_VFuente;

											//! Posicion de la ultima busqueda
		 unsigned int                      _ArbolEx_PosBuscar;

											//! Ultima tecla virtual presionada
		 UINT                              _ArbolEx_UVirtKey;

											//! Array para el teclado
		 bool				               _ArbolEx_Teclado[256];

											//! Ultima posicion Y del mouse
		 int                               _ArbolEx_UYMouse;

											//! Permitir multiseleccion
//		 bool							   _ArbolEx_MultiSeleccion;

											//! Permitir subseleccion
//		 bool							   _ArbolEx_SubSeleccion;

											//! Transparencias desactivadas
//		 bool                              _ArbolEx_DesactivarBlend;

											//! Altura de cada linea
		 int							   _ArbolEx_AltoLinea;

											//! Arbol activado / desactivado
//		 BOOL							   _ArbolEx_Activado;

											//! Variable que determina si hay que pintar el borde
//		 bool						       _ArbolEx_PintarBorde;

											//! Variable que determina si el arbol tiene el foco del raton
		 bool							   _ArbolEx_FocoRaton;

											//! Variable que determina si el arbol tiene el utilmo foco del raton
		 bool							   _ArbolEx_UFocoRaton;
		 /////////////////////////////////////

											//! WindowProcedure que usara el Editbox en la Función ArbolEx_EmpezarLabelEdit().
											/*! WindowProcedure que usara el Editbox en la Función ArbolEx_EmpezarLabelEdit().
													\fn			static LRESULT CALLBACK _ArbolEx_GestorMensajesEdit(HWND dhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
													\param[in]	dhWnd	: HWND del EditBox.
													\param[in]	uMsg	: Mensaje.
													\param[in]	wParam	: Parametro1.
													\param[in]	lParam	: Parametro2.
													\return		Devuelve un valor acorde al mensaje especificado.
													\remarks	Funcion de uso interno para ArbolEx_EmpezarLabelEdit().
											*/
		 static LRESULT CALLBACK	       _ArbolEx_GestorMensajesEdit(HWND dhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

											//! Nodo en edicion
		 DWLArbolEx_Nodo                  *_ArbolEx_eNodo;

											//! WindowProcedure Original del EditBox
		 WNDPROC					       _ArbolEx_GestorMensajesOriginalEdit;

											//! Brocha del fondo del EditBox
		 HBRUSH			                   _ArbolEx_BrochaFondoEdit;

											//! Valor para saber el arbol esta en estado de edicion
		 bool                              _ArbolEx_Editando;

											//! Handle del EditBox
		 HWND						       _ArbolEx_hWndEdit;

											//! Ultimo nodo resaltado al inicio de la cuenta atras de tiempo
		 DWLArbolEx_Nodo				  *_ArbolEx_TT_UltimoNodo;
		  private : ////////////////////////// Miembros privados

                                            //! Constructor copia des-habilitado
                                            DWLArbolEx_Nucleo(const DWLArbolEx_Nucleo &) :  _ArbolEx_NodoPresionado(NULL), _ArbolEx_NodoShifteado(NULL), _ArbolEx_NodoMarcado(NULL), _ArbolEx_NodoResaltado(NULL), _ArbolEx_UNodoResaltado(NULL), _ArbolEx_PosUltimoClick(NULL),
                                                                                            _ArbolEx_ExpansorPresionado(NULL), _ArbolEx_ExpansorResaltado(NULL),	 _ArbolEx_UExpansorResaltado(NULL), _ArbolEx_UltimoClick(0), _ArbolEx_UltimoBoton(-1), _ArbolEx_Nodos(), _ArbolEx_NodosLineales(),
                                                                                            _ArbolEx_Buffer(NULL), _ArbolEx_Bmp(NULL), _ArbolEx_Viejo(NULL), _ArbolEx_FondoDC(NULL), _ArbolEx_BmpFondo(NULL), _ArbolEx_ViejoFondo(NULL), _ArbolEx_VFuente(NULL), _ArbolEx_PosBuscar(0), _ArbolEx_UVirtKey(0),
                                                                                            /*_ArbolEx_Teclado,*/ _ArbolEx_UYMouse(-1), _ArbolEx_AltoLinea(16), _ArbolEx_FocoRaton(false), _ArbolEx_UFocoRaton(false), _ArbolEx_eNodo(NULL), _ArbolEx_GestorMensajesOriginalEdit(NULL),
                                                                                            _ArbolEx_BrochaFondoEdit(NULL), _ArbolEx_Editando(false), _ArbolEx_hWndEdit(NULL), _ArbolEx_TT_UltimoNodo(NULL), ArbolEx_Estilos() {
                                            };
                                            //! Operador = des-habilitado
		 inline DWLArbolEx_Nucleo             &operator=(const DWLArbolEx_Nucleo &) { return *this; };
											//
		 friend class DWLArbolEx_Nodo;		//
		};									//
		//////////////////////////////////////

    };
};

#endif
