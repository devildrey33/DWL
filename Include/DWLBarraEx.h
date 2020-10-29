/*! \file DWLBarraEx.h
	\brief		 Archivo que contiene las definiciones de las clases de la BarraEx.


	\details	Este control se puede usar como una barra de desplazamiento, o como una barra de progreso y admite tanto alineaciones verticales como horizontales.																								\n
				<table border = 0 align ='right'><tr><td> \image html BarraEx.jpg </td></tr></table>
																																												\n
				\section Clases_Sec		Este archivo contiene varias clases descritas a continuación  :
				 - DWL::ControlesEx::DWLBarraEx_Colores :																														\n
					Clase que enlaza los colores a la configuración del skin por defecto.																						\n
					Puedes modificar cualquier color de esta clase, solo deberas repintar la barra al terminar.																	\n
																																												\n
				 - DWL::ControlesEx::DWLBarraEx_Nucleo :																														\n
					Clase que contiene las funciónes basicas para pintar y controlar los eventos de la barra.																	\n
					Esta clase se ha creado de forma que puede compartir un control con otra clase, asi podemos hacer controles	tipo ComboBox y de una forma mucho mas limpia.	\n
																																												\n
				 - DWL::ControlesEx::DWLBarraEx :																																\n
					Clase que hereda de DWLBarraEx_Nucleo y lo enlaza a un control para el solo.																				\n
					Esta clase es la que deberiamos usar para crear una barra estandar sin complicaciones.																		\n
 
																																																																\n
	\author		devildrey33
	\date		Creado el [12/04/2005], ultima modificación el [02/11/2009]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

	\todo		Implementar tooltips informativos al desplazar la barra.
*/


#ifndef DWL_BARRAEX_H
#define DWL_BARRAEX_H

#include "DWLControlEx.h"
#include ".\DWLBarraEx\DWLBarraEx_Nucleo.h"




namespace DWL {
	namespace ControlesEx {
		//! Clase que une DWLControlEx con DWLBarraEx_Nucleo, para formar un control BarraEx
        class DWLBarraEx : public DWL::ControlesEx::Base::DWLControlEx, public DWLBarraEx_Nucleo {
		public: ////////////////////////////////////////// Miembros publicos

														//! Constructor por defecto.
														/*! Constructor por defecto.
																\fn			DWLBarraEx(void);
																\return		No devuelve nada.
														*/
														DWLBarraEx(void);

														//! Destructor.
														/*! Destructor.
																\fn			~DWLBarraEx(void);
																\return		No devuelve nada.
														*/
													   ~DWLBarraEx(void);

														//! Función que retorna si esta ventana tiene el raton encima.
														/*!	Esta funcion devuelve si esta ventana tiene el raton encima.
																\fn			virtual const bool Foco(void);
																\return		Devuelve true si el raton esta encima del control, false en caso contrario.
														*/
		virtual bool								    Foco(void);

														//! Función que crea la BarraEx
														/*!	Esta funcion crea la BarraEx.
																\fn			HWND CrearBarraEx(const long Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const int Tipo = DWL_BARRAEX_PROGRESO_HORIZONTAL, const long nMinimo = 0, const long nMaximo = 1000);
																\param[in]	nEstilos			: Estilos para el ArbolEx (WS_CHILD | WS_VISIBLE).
																\param[in]	hWndParent			: HWND del control que sera el padre de la BarraEx.
																\param[in]	cX					: Posicion X.
																\param[in]	cY					: Posicion Y.
																\param[in]	cAncho				: Ancho de la BarraEx.
																\param[in]	cAlto				: Alto de la BarraEx.
																\param[in]	cID					: ID de la BarraEx.
																\param[in]	int					: Tipo de barra [DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL, DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL, DWL_BARRAEX_PROGRESO_HORIZONTAL, DWL_BARRAEX_PROGRESO_VERTICAL].
																\param[in]	nMinimo				: Valor minimo inicial (0 por defecto).
																\param[in]	nMaximo				: Valor maximo inicial (1000 por defecto).
																\return		Devuelve el HWND de la BarraEx. En caso de error devolvera NULL.
														*/
		 HWND											CrearBarraEx(const long nEstilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const int Tipo = DWL_BARRAEX_PROGRESO_HORIZONTAL, const long nMinimo = 0, const long nMaximo = 1000);

														//! Función que conecta la BarraEx de un dialogo.
														/*!	Esta funcion conecta la BarraEx de un dialogo.
																\fn			HWND ConectarBarraEx(HWND hWndParent, const int cID, const int Tipo = DWL_BARRAEX_PROGRESO_HORIZONTAL, const long nMinimo = 0, const long nMaximo = 1000);
																\param[in]	hWndParent			: HWND del control que sera el padre de la BarraEx.
																\param[in]	cID					: ID de la BarraEx.
																\param[in]	nTipo				: Tipo de barra [DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL, DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL, DWL_BARRAEX_PROGRESO_HORIZONTAL, DWL_BARRAEX_PROGRESO_VERTICAL].
																\param[in]	nMinimo				: Valor minimo inicial (0 por defecto).
																\param[in]	nMaximo				: Valor maximo inicial (1000 por defecto).
																\return		Devuelve el HWND de la BarraEx. En caso de error devolvera NULL.
                                                                \remarks    Esta función solo debe usarse con controles que se creen durante la creación del dialogo, si esta clase no pertenece a un dialogo, o se va a crear dinamicamente, no debes usar esta función.
														*/
		 HWND											ConectarBarraEx(HWND hWndParent, const int cID, const int Tipo = DWL_BARRAEX_PROGRESO_HORIZONTAL, const long nMinimo = 0, const long nMaximo = 1000);

														//! Función que repinta todo la BarraEx.
														/*!	Esta función repinta todo la BarraEx.
																\fn			void Repintar(const bool Forzar = false);
																\param[in]	Forzar : True para forzar el repintado, false para que la funcion decida si repintar.
																\return		No devuelve nada.
																\remarks	Cuando Forzar es false, esta función mira si ha cambiado algun estado interno,
																			y de ser asi repinta el control, en caso contrario no hace nada.
														*/
		 void											Repintar(const bool Forzar = false);

														//! Función que asigna el valor minimo para la BarraEx.
														/*! Esta funcion asigna el valor minimo para la BarraEx.
																\fn			inline void Minimo(const long nMinimo);
																\param[in]	nMinimo : Nuevo valor minimo.
																\return		No devuelve nada.
																\sa			Maximo(), Valor()
														*/
		 inline void									Minimo(const long nMinimo) {
															_BarraEx_Minimo = nMinimo;
															Repintar(true);
														};

														//! Función que retorna el valor minimo para la BarraEx.
														/*! Esta funcion devuelve el valor minimo para la BarraEx.
																\fn			inline long Minimo(void) const;
																\return		Devuelve el valor minimo para la BarraEx.
																\sa			Maximo(), Valor()
														*/
		 inline long							        Minimo(void) const {
															return _BarraEx_Minimo;
														};

														//! Función que asigna el valor maximo para la BarraEx.
														/*! Esta funcion asigna el valor maximo para la BarraEx.
																\fn			inline void Maximo(const long nMaximo);
																\param[in]	nMaximo : Nuevo valor maximo.
																\return		No devuelve nada.
																\sa			Minimo(), Valor()
														*/
		 inline void									Maximo(const long nMaximo) {
															_BarraEx_Maximo = nMaximo;
															Repintar(true);
														};

														//! Función que retorna el valor maximo para la BarraEx.
														/*! Esta funcion devuelve el valor maximo para la BarraEx.
																\fn			inline long Maximo(void) const;
																\return		Devuelve el valor maximo para la BarraEx.
																\sa			Minimo(), Valor()
														*/
		 inline long								    Maximo(void) const {
															return _BarraEx_Maximo;
														};

														//! Función que asigna el valor actual para la BarraEx.
														/*! Esta funcion asigna el valor actual para la BarraEx.
																\fn			inline virtual void Valor(const long nValor);
																\param[in]	nValor : Nuevo valor actual.
																\return		No devuelve nada.
																\sa			Minimo(), Maximo()
														*/
		 inline virtual void							Valor(const long nValor) {
															_BarraEx_Valor = nValor;
															Repintar(true);
														};

														//! Función que retorna el valor actual para la BarraEx.
														/*! Esta funcion devuelve el valor actual para la BarraEx.
																\fn			inline long Valor(void) const;
																\return		Devuelve el valor actual para la BarraEx.
																\sa			Minimo(), Maximo()
														*/
		 inline long							        Valor(void) const {
															return _BarraEx_Valor;
														};

														//! Función que suma el valor actual para la BarraEx.
														/*! Esta funcion suma el valor actual para la BarraEx.
																\fn			inline int Valor_SumarValor(const long SumValor);
																\param[in]	SumValor : Valor que se sumara al valor actual de la BarraEx.
																\return		Devuelve el valor actual.
														*/
		 inline int								        Valor_SumarValor(const long SumValor) {
															if (_BarraEx_Valor + SumValor < _BarraEx_Maximo)	_BarraEx_Valor += SumValor;
															else												_BarraEx_Valor = _BarraEx_Maximo;
															Repintar(true);
															return _BarraEx_Valor;
														};

														//! Función que resta el valor actual para la BarraEx.
														/*! Esta funcion resta el valor actual para la BarraEx.
																\fn			inline int Valor_RestarValor(const long RestValor);
																\param[in]	RestValor : Valor que se restara al valor actual de la BarraEx.
																\return		Devuelve el valor actual.
														*/
		 inline int								        Valor_RestarValor(const long RestValor) {
															if (_BarraEx_Valor - RestValor > 0)	_BarraEx_Valor -= RestValor;
															else								_BarraEx_Valor = 0;
															Repintar(true);
															return _BarraEx_Valor;
														};

														//! Función que pinta todo la BarraEx cuado se recibe un mensaje WM_PAINT.
														/*!	Esta función pinta la BarraEx cuando se recibe un mensaje WM_PAINT.
																\fn			LRESULT Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);
																\param[in]	hDC	: hDC donde se pintara todo la BarraEx.
                                                                \param[in]  PS  : Estructura con los datos de pintado.
																\return		No devuelve nada.
                												\return		Si re-emplazas esta funcion debes retornar 0.
														*/
		 LRESULT					        			Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);

														//! Función para asignar el ancho de borde a la BarraEx.
														/*! Esta funcion asigna el ancho del borde para la BarraEx.
																\fn			inline virtual void TamBorde(const int NumPixels);
																\param[in]	NumPixels : Tamaño en pixeles del borde.
																\return		No devuelve nada.
														*/
/*		 inline void									TamBorde(const int NumPixels) {
                                                            BarraEx_Estilos.Borde = NumPixels;
//															_BarraEx_TamBorde = NumPixels;
															Repintar(true);
														};*/

														//! Función para mover la BarraEx a la posicion y el tamaño especificados.
														/*!	Esta función mueve la BarraEx a la posicion y tamaño especificados.
																\fn			void Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = true);
																\param[in]	cX			: Nueva posicion X para la BarraEx.
																\param[in]	cY			: Nueva posicion Y para la BarraEx.
																\param[in]	cAncho		: Nuevo ancho para la BarraEx.
																\param[in]	cAlto		: Nueva altura para la BarraEx.
																\param[in]	cRepintar	: True para repintar el control, false para dejarlo sin repintar.
																\return		No devuelve nada.
														*/
		 inline void									Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = false) {
															SetWindowRgn(_hWnd, CreateRoundRectRgn(0, 0, cAncho, cAlto, 5, 5), FALSE);
															MoveWindow(_hWnd, cX, cY, cAncho, cAlto, cRepintar);
														};

														//! Función para retornar el estado de la BarraEx.
														/*! Esta funcion devuelve el estado de la BarraEx.
																\fn			inline DWL_Enum_BarraEx_Estados Estado(void) const;
																\return		Devuelve el estado de la BarraEx.
																\sa			DWL_Enum_BarraEx_Estados()
														*/
		 inline DWL_Enum_BarraEx_Estados				    Estado(void) const {
															return _BarraEx_Estado;
														};
		protected : ////////////////////////////////////// Miembros protegidos

														//! Función predefinida del mensaje WM_*BUTTONUP (Virtual)
														/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONUP.
																\fn			virtual LRESULT Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
																\param[in]	Boton	: Boton presionado.
																\param[in]	cX		: Coordenada X del mouse.
																\param[in]	cY		: Coordenada Y del mouse.
																\param[in]	Param	: Teclas extendidas presionadas.
																\return		No devuelve nada.
														*/
		 virtual LRESULT								Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);

														//! Función predefinida del mensaje WM_*BUTTONDOWN (Virtual)
														/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONDOWN.
																\fn			virtual LRESULT Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param)
																\param[in]	Boton	: Boton presionado.
																\param[in]	cX		: Coordenada X del mouse.
																\param[in]	cY		: Coordenada Y del mouse.
																\param[in]	Param	: Teclas extendidas presionadas.
																\return		No devuelve nada.
														*/
		 virtual LRESULT								Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param);

														//! Función predefinida del mensaje WM_MOUSEMOVE.
														/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEMOVE.
																\fn			virtual LRESULT Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);
																\param[in]	cX		: Coordenada X del mouse.
																\param[in]	cY		: Coordenada Y del mouse.
																\param[in]	Param	: Teclas extendidas presionadas.
																\return		No devuelve nada.
														*/
		 virtual LRESULT								Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);

														//! Función que recibe cuando el mouse se va del control
														/*!	Esta función es la encargada de procesar los mensajes WN_MOUSELEAVE.
																\fn			virtual LRESULT Evento_Mouse_Saliendo(void);
																\return		No devuelve nada.
                												\return		Si re-emplazas esta funcion debes retornar 0.
														*/
		 virtual LRESULT					            Evento_Mouse_Saliendo(void);
		};												//
		////////////////////////////////////////////////// Fin DWLBarraEx
	}
}

#endif // DWL_CLASEBARRAEX_H

/*! \file DWLBarraEx.h
	\version

 - [01/11/2009] <b>0.95</b>
   Se ha adaptado la clase a la nueva configuracion de colores.\n
   Nueva clase DWLBarraEx_Nucleo. Esta clase se ha echo para poder implementar este control dentro de otro control compartiendo su hWnd.

 - [12/04/2005] <b>0.9</b>
   Primera versión de este control.\n
   Esta barra puede ser usada como barra de desplazamiento, o como barra de progreso tanto horizontal como vertical.\n
   La barra de desplazamiento es la que el usuario puede utilizar para cambiar un valor.\n
   La barra de progreso es la que se usa normalmente para mostrar un porcentaje de una tarea.

*/
