/*! \file DWLToolTipEx.h
	\brief		Archivo que contiene las declaraciones de las clases del ToolTipEx.

	\details	La clase DWLToolTipEx esta enfocada de forma que podamos crear tooltips facilmente y con un aspecto agradable ademas de ordenado.		\n	
				Para mostrar un ToolTipEx lo primero que hay que hacer es añadirle aquellos datos que queremos mostrar.									\n
				Tenemos varias funciones que se ajustan a las formas mas comunes de mostrar tooltips, 
				para empezar tenemos la función DWL::ControlesEx::DWLToolTipEx::AgregarTextoNegrita()
				que nos permite agregar un texto de una o varias lineas al tooltip, y que podriamos usar como titulo.									\n
				En segundo lugar podriamos utilizar la función DWL::ControlesEx::DWLToolTipEx::AgregarTextoCaracterTexto() para añadirle
				una linea con 2 textos delimitados por un caracter separador. Podriamos usar esta funcion tantas veces como se necesite para 
				hacer una lista de datos ordenada y justificada por columnas.																			\n
																																						
				<table border = 0 align ='right'><tr><td> \image html ToolTipEx.jpg </td></tr></table>
 
				\section Clases_Sec Descripción breve de las clases que contiene este archivo :
				 - DWL::ControlesEx::DWLToolTipEx_Colores :																								\n
						Clase que enlaza los colores a la configuracion del skin por defecto.															\n\n
				 - DWL::ControlesEx::DWLToolTipEx_ObjetoTextoCaracterTexto :																			\n
						Clase que contiene un dos textos alineados por un caracter separador.															\n\n
				 - DWL::ControlesEx::DWLToolTipEx_ObjetoTextoCaracterIcono :																			\n
						Clase que contiene un texto y un icono alineados por un caracter separador.														\n\n
				 - DWL::ControlesEx::DWLToolTipEx_ObjetoIconoTexto :																					\n
						Clase que contiene un icono y un texto (ideal para mostrar titulos).															\n\n		
				 - DWL::ControlesEx::DWLToolTipEx_Objeto :																								\n
						Clase que engloba todos los objetos posibles en el ToolTipEx.																	\n\n		
				 - DWL::ControlesEx::DWLToolTipEx :																										\n
						Clase que controla el ToolTipEx.																								\n		


	\author		devildrey33
	\version	0.5
	\date		10/12/2009

	\remarks
				Archivo creado por devildrey33 el dia [26/02/2009] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n	
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n	
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n	

*/


#ifndef DWL_TOOLTIPEX_H
#define DWL_TOOLTIPEX_H

#include ".\DWLToolTipEx\DWLToolTipEx_Objeto.h"
#include ".\DWLToolTipEx\DWLToolTipEx_Estilos.h"
#include <vector>
#include "DWLControlEx.h"

#define DWL_TIMER_TOOLTIP  WM_USER + 5454
#define DWL_TIEMPO_TOOLTIP 2200

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

		//! Clase que hereda de DWL::Ventanas::DWLVentana para formar un control DWLToolTipEx.
        class DWLToolTipEx : public DWL::ControlesEx::Base::DWLControlEx {
		 public : //////////////////////////////// Miembros publicos

												//! Constructor.
												/*! Constructor.
														\fn			DWLToolTipEx(void);
														\return		No devuelve nada.
												*/
												DWLToolTipEx(void);

												//! Destructor.
												/*! Destructor.
														\fn			~DWLToolTipEx(void);
														\return		No devuelve nada.
												*/
							                   ~DWLToolTipEx(void);

												//! Función que muestra el ToolTipEx con la opaciodad especificada.
												/*! Esta función muestra el ToolTipEx con la opaciodad especificada.
														\fn			void MostrarToolTipEx(const BYTE nOpacidad = 240);
														\param[in]	nOpacidad : Valor en el que especificamos la opacidad del ToolTipEx (0-255)
														\return		No devuelve nada.
														\remarks	El ToolTipEx se colocara de forma que quede a la derecha inferior del raton.
												*/
  	     void									MostrarToolTipEx(const BYTE nOpacidad = 240);
												
												//! Función que elimina todos los datos del ToolTipEx.
												/*! Esta función elimina todos los datos del ToolTipEx.
														\fn			void BorrarMemoria(void);
														\return		No devuelve nada.
												*/
		 void									BorrarMemoria(void);

												//! Función que agrega un texto al ToolTipEx que puede ser de varias lineas.
												/*! Esta función agrega un texto al ToolTipEx que puede ser de varias lineas.
														\fn			DWLString *AgregarTexto(const TCHAR *nTexto);
														\param[in]	nTexto : Texto que vamos a agregar al ToolTipEx.
														\return		Devuelve la clase DWLString creada que va a contener este texto.
														\remarks	Este objeto no se alineara con otros objetos.
														\sa			AgregarTextoNegrita()
												*/
		 DWLString							   *AgregarTexto(const TCHAR *nTexto);

												//! Función que agrega un texto en negrita al ToolTipEx que puede ser de varias lineas.
												/*! Esta función agrega un texto en negrita al ToolTipEx que puede ser de varias lineas.
														\fn			DWLString *AgregarTextoNegrita(const TCHAR *nTexto);
														\param[in]	nTexto : Texto que vamos a agregar al ToolTipEx.
														\return		Devuelve la clase DWLString creada que va a contener este texto.
														\remarks	Este objeto no se alineara con otros objetos.
														\sa			AgregarTexto()
												*/
		 DWLString							   *AgregarTextoNegrita(const TCHAR *nTexto);

												//! Función que agrega una secuencia de Texto Caracter Texto.
												/*! Esta función agrega una secuencia de Texto Caracter Texto.
														\fn			DWLToolTipEx_ObjetoTextoCaracterTexto *AgregarTextoCaracterTexto(const TCHAR *nTexto1, const TCHAR nCaracter = TEXT(':'), const TCHAR *nTexto2 = NULL);
														\param[in]	nTexto1		: Texto que quedara alineado a la izquierda del todo.
														\param[in]	nCaracter	: Caracter que delimitara el espacio entre los dos textos.
														\param[in]	nTexto2		: Texto que quedara alineado a la derecha del caracter separador.
														\return		Devuelve la clase DWLToolTipEx_ObjetoTextoCaracterTexto que contiene este objeto.
														\remarks	Esta funcion se ha creado para poder hacer listas de datos alineadas, de una forma facil.
																	Al mostrar el tooltip se calcula el ancho de todos los textos 1 para saber donde empezar a poner el separador,
																	y luego se mostraran todos los textos 2 alineados con el separador. NOTA : Es compatible con objetos del tipo Texto Caracter Icono.
												*/
		 DWLToolTipEx_ObjetoTextoCaracterTexto *AgregarTextoCaracterTexto(const TCHAR *nTexto1, const TCHAR nCaracter = TEXT(':'), const TCHAR *nTexto2 = NULL);

												//! Función que agrega una secuencia de Texto Caracter Texto.
												/*! Esta función agrega una secuencia de Texto Caracter Texto.
														\fn			DWLToolTipEx_ObjetoTextoCaracterTexto *AgregarTextoCaracterTexto(const TCHAR *nTexto1, const TCHAR nCaracter = TEXT(':'), const int nTexto2 = 0);
														\param[in]	nTexto1		: Texto que quedara alineado a la izquierda del todo.
														\param[in]	nCaracter	: Caracter que delimitara el espacio entre los dos textos.
														\param[in]	nTexto2		: Valor que se convertira a texto para ser mostrado normalmente y se situara a la derecha del caracter separador.
														\return		Devuelve la clase DWLToolTipEx_ObjetoTextoCaracterTexto que contiene este objeto.
														\remarks	Esta funcion se ha creado para poder hacer listas de datos alineadas, de una forma facil.
																	Al mostrar el tooltip se calcula el ancho de todos los textos 1 para saber donde empezar a poner el separador,
																	y luego se mostraran todos los textos 2 alineados con el separador. 
																	NOTA : Los objetos tipo Texto Caracter Icono, tambien se alinearan junto con este.
												*/
		 DWLToolTipEx_ObjetoTextoCaracterTexto *AgregarTextoCaracterTexto(const TCHAR *nTexto1, const TCHAR nCaracter = TEXT(':'), const int nTexto2 = 0);

												//! Función que agrega una secuencia de Texto Caracter Icono.
												/*! Esta función agrega una secuencia de Texto Caracter Icono.
														\fn			DWLToolTipEx_ObjetoTextoCaracterIcono *AgregarTextoCaracterIcono(const TCHAR *nTexto, const TCHAR nCaracter = TEXT(':'), const int nIcono = NULL, const int AnchoIcono = 16, const int AltoIcono = 16, const float nFraccion = 1.0f);
														\param[in]	nTexto		: Texto que quedara alineado a la izquierda del todo.
														\param[in]	nCaracter	: Caracter que delimitara el espacio entre el texto y el icono.
														\param[in]	nIcono		: ID del icono en los recursos.
														\param[in]  nAnchoIcono : Ancho en pixeles del icono (16)
														\param[in]	nAltoIcono	: Altura en pixeles del icono (16)
														\param[in]	nFraccion	: Fracción que se usara para pintar el icono.
														\return		Devuelve la clase DWLToolTipEx_ObjetoTextoCaracterIcono que contiene este objeto.
														\remarks	Esta funcion se ha creado para poder hacer listas de datos alineadas, de una forma facil.
																	Al mostrar el tooltip se calcula el ancho de todos los textos para saber donde empezar a poner el separador,
																	y luego se mostraran todos los iconos alineados con el separador. 
																	NOTA : Los objetos tipo Texto Caracter Texto, tambien se alinearan junto con este.
												*/
		 DWLToolTipEx_ObjetoTextoCaracterIcono *AgregarTextoCaracterIcono(const TCHAR *nTexto, const TCHAR nCaracter = TEXT(':'), const int nIcono = NULL, const int AnchoIcono = 16, const int AltoIcono = 16, const float nFraccion = 1.0f);

												//! Función que agrega un Icono seguido de un Texto en negrita.
												/*! Esta función agrega un Icono seguido de un Texto en negrita..
														\fn			DWLToolTipEx_ObjetoIconoTexto *AgregarIconoTexto(const int nIcono, const int AnchoIcono, const int AltoIcono, const TCHAR *nTexto);
														\param[in]	nIcono		: ID del icono en los recursos.
														\param[in]  nAnchoIcono : Ancho en pixeles del icono (16)
														\param[in]	nAltoIcono	: Altura en pixeles del icono (16)
														\param[in]	nTexto		: Texto que quedara alineado a la izquierda del todo.
														\return		Devuelve la clase DWLToolTipEx_ObjetoIconoTexto que contiene este objeto.
														\remarks	Esta función solo soporta una linea, y no se alineara con ningun objeto.
												*/
		 DWLToolTipEx_ObjetoIconoTexto		   *AgregarIconoTexto(const int nIcono, const int AnchoIcono, const int AltoIcono, const TCHAR *nTexto);

		 DWLToolTipEx_Estilos                   Estilos;

		protected: /////////////////////////////// Miembros protegidos

												//! Función que calcula el ancho y alto necesarios para mostrar los objetos.
												/*! Esta función calcula el ancho y alto necesarios para mostrar los objetos.
														\fn			void CalcularTam(void);
														\return		No devuelve nada.
												*/
		 void									CalcularTam(void);

		 SIZE                                  _ObtenerTamTexto(HDC hDC, DWL::DWLString &nTexto);
		 const UINT                            _PintarTexto(HDC hDC, DWL::DWLString &nTexto, const int cX, const int cY);

												//! Función que pinta todo el ToolTipEx cuado se recibe un mensaje WM_PAINT.
												/*!	Esta función pinta el ToolTipEx cuando se recibe un mensaje WM_PAINT.
														\fn			LRESULT Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);
														\param[in]	hDC	: hDC donde se pintara todo el ToolTipEx.
														\param[in]	PS	: Estructura que contiene los datos del pintado.
   												        \return		Si re-emplazas esta funcion debes retornar 0.
												*/																								
		 LRESULT								Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);

												//! Función predefinida del mensaje WM_MOUSEMOVE.
												/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEMOVE.
														\fn			virtual void Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);
														\param[in]	cX		: Coordenada X del mouse.
														\param[in]	cY		: Coordenada Y del mouse.
														\param[in]	wParam	: Teclas extendidas presionadas.
   											        	\return		Si re-emplazas esta funcion debes retornar 0.
												*/																								
		 virtual LRESULT						Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);

												//! Función predefinida del mensaje WM_*BUTTONDOWN (Virtual)
												/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONDOWN.
														\fn			virtual LRESULT Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param)
														\param[in]	Boton	: Boton presionado.
														\param[in]	cX		: Coordenada X del mouse.
														\param[in]	cY		: Coordenada Y del mouse.
														\param[in]	Param	: Teclas extendidas presionadas.
   												        \return		Si re-emplazas esta funcion debes retornar 0.
												*/																								
		 virtual LRESULT						Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param);

												//! Función predefinida del mensaje WM_*BUTTONUP (Virtual)
												/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONUP.
														\fn			virtual LRESULT Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
														\param[in]	Boton	: Boton presionado.
														\param[in]	cX		: Coordenada X del mouse.
														\param[in]	cY		: Coordenada Y del mouse.
														\param[in]	Param	: Teclas extendidas presionadas.
   												        \return		Si re-emplazas esta funcion debes retornar 0.
												*/																								
		 virtual LRESULT						Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);

												//! Función predefinida del mensaje WM_CLOSE.
												/*!	Esta función es la encargada de procesar el mensaje WM_CLOSE.
														\fn			LRESULT Evento_Cerrar(void);
														\return		Devuelve 0 si se permite cerrar la ventana, 1 si no se permite cerrar la ventana.
												*/																								
		 LRESULT								Evento_Cerrar(void);

												//! Ancho de la primera columna de texto
		 int								   _AnchoTexto1;
												
												//! Ancho total requerido para mostrar el control.
		 int				                   _AnchoRequerido;

												//! Altura total requerida para mostrar el control.
		 int				                   _AltoRequerido;

												//! Variable que determina si se ha entrado en el primer mouse move
//		 bool                                  _PrimerMouseMove;

												//! Vector de objetos que mostrara el tooltip.
		 std::vector<DWLToolTipEx_Objeto *>    _Objetos;
		};										//
		////////////////////////////////////////// DWLToolTipEx
	};
};


#endif // DWL_TOOLTIPEX_H

// Version 0.5 [26/02/2009]
// Primera version de esta clase la cual permite implemetar tooltips en muy poco tiempo, y de forma que queden en la linea de la libreria
// en cuanto a graficos.
// Esta cabecera incluye las siguientes clases :
// - DWLToolTipEx							: Clase principal
// - DWLToolTipEx_Colores					: Colores del tooltip
// - DWLToolTipEx_Fuentes					: Fuentes del tooltop
// - DWLToolTipEx_Objeto					: Clase que engloba varios objetos del tooltip (de uso interno)
// - DWLToolTipEx_ObjetoTextoCaracterTexto	: Clase para los objetos con Texto Caracter Texto (de uso interno)
// - DWLToolTipEx_ObjetoIconoTexto			: Clase para los objetos con Icono Texto (de uso interno)

// Version 0.5b [27/02/2007]
// -Solucionado pequeño memory leak al pintar los datos
// -Añadida clase DWLToolTipEx_ObjetoTextoCaracterIcono (de uso interno)
// -Reducida drasticamente la carga de callbacks durante el repintado y el calculo del tamaño.
