#ifndef DWL_BARRAEX_NUCLEO_H
#define DWL_BARRAEX_NUCLEO_H
 
#include "DWLBarraEx_Estilos.h"



//! Estados de la barra
enum DWL_Enum_BarraEx_Estados {
	DWL_Enum_BarraEx_Estados_NoDefinido,
	DWL_Enum_BarraEx_Estados_Normal,
	DWL_Enum_BarraEx_Estados_Resaltado,
	DWL_Enum_BarraEx_Estados_Presionado
};


//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

		//! Clase que contiene el nucleo de funciones para la BarraEx.
		/*! Clase que contiene el nucleo de Funciónes para la BarraEx sin requerir el hWnd de una ventana / control.
			Por ello puede ser usada dentro de cualquier control utilizando solo una parte de el
		*/
		class DWLBarraEx_Nucleo {
		 public : //////////////////////////////////////// Miembros publicos

														//! Constructor por defecto.
														/*! Constructor por defecto.
																\fn			DWLBarraEx_Nucleo(void);
																\return		No devuelve nada.
														*/
														DWLBarraEx_Nucleo(void);

														//! Destructor.
														/*! Destructor.
																\fn		   ~DWLBarraEx_Nucleo(void);
																\return		No devuelve nada.
														*/
		virtual 									   ~DWLBarraEx_Nucleo(void);

														//! Función para pintar este control en el DC y posicion especificados.
														/*! Esta función pinta la BarraEx en el DC y posicion especificadas.
																\fn			void BarraEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true, const bool PintarConMascara = false);
																\param[in]	hDC					: hDC del control donde se va a pintar la BarraEx.
																\param[in]	Espacio				: Espacio del control donde se va a pintar la BarraEx.
																\param[in]	TieneFoco			: Valor que determina si la BarraEx tiene el foco del raton (por defecto se usara la funcion Foco()).
																\param[in]	PintarConMascara	: Valor que determina si se va a pintar el contorno del control con SRCAND antes de pintar el control.
																\return		No devuelve nada.
																\remarks	Esta función esta preparada para pintar la BarraEx en un DC que no sea el suyo, o que sea compartido.
																			Por ello debemos especificar las coordenadas donde se va a pintar, si tiene el foco del raton o no, y por ultimo si debemos
																			pintar la mascara.
																			El parametro PintarMascara solo es necesario si vamos a pintar la BarraEx en un DC que no es el suyo y requerimos el pintado
																			del borde del control. Entonces la funcion de pintado pintara el contorno de la BarraEx con SRCAND, y luego pintara el control
																			con SRC_PAINT para que no se vean graficos desfasados en el borde.
														*/
		void											BarraEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true, const bool PintarConMascara = false);

														//! Función virtual que pinta la BarraEx en estado normal.
														/*! Esta función virtual pinta la BarraEx en su estado normal dentro del espacio y dc especificados.
																\fn			virtual inline void BarraEx_Evento_Pintar_EstadoNormal(HDC hDC, RECT *Espacio);
																\param[in]	hDC		: hDC donde se va a pintar la BarraEx.
																\param[in]	Espacio	: Recta con el espacio del control BarraEx.
																\return		No devuelve nada.
																\remarks	Esta función pinta solo el estado normal de la BarraEx.
														*/
		 virtual void	        						BarraEx_Evento_Pintar_EstadoNormal(HDC hDC, RECT *Espacio);

														//! Función virtual que pinta la BarraEx en estado resaltado.
														/*! Esta función virtual pinta la BarraEx en su estado resaltado dentro del espacio y dc especificados.
																\fn			virtual inline void BarraEx_Evento_Pintar_EstadoResaltado(HDC hDC, RECT *Espacio);
																\param[in]	hDC		: hDC donde se va a pintar la BarraEx.
																\param[in]	Espacio	: Recta con el espacio del control BarraEx.
																\return		No devuelve nada.
																\remarks	Esta función pinta solo el estado resaltado de la BarraEx.
														*/
		 virtual void		        					BarraEx_Evento_Pintar_EstadoResaltado(HDC hDC, RECT *Espacio);

														//! Función virtual que pinta la BarraEx en estado presionado.
														/*! Esta función virtual pinta la BarraEx en su estado presionado dentro del espacio y dc especificados.
																\fn			virtual inline void BarraEx_Evento_Pintar_EstadoPresionado(HDC hDC, RECT *Espacio);
																\param[in]	hDC		: hDC donde se va a pintar la BarraEx.
																\param[in]	Espacio	: Recta con el espacio del control BarraEx.
																\return		No devuelve nada.
																\remarks	Esta función pinta solo el estado presionado de la BarraEx.
														*/
		 virtual void	        						BarraEx_Evento_Pintar_EstadoPresionado(HDC hDC, RECT *Espacio);

														//! Función virtual que pinta el fondo de la BarraEx.
														/*! Esta función virtual pinta el fondo BarraEx en el espacio y dc especificados.
																\fn			virtual inline void BarraEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio);
																\param[in]	hDC		: hDC donde se va a pintar la BarraEx.
																\param[in]	Espacio	: Recta con el espacio del control BarraEx.
																\return		No devuelve nada.
																\remarks	Esta función pinta solo el fondo de la BarraEx.
														*/
		 virtual void				           			BarraEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio);

														//! Función virtual que pinta el borde de la BarraEx.
														/*! Esta función virtual pinta el borde BarraEx en el espacio y dc especificados.
																\fn			virtual inline void BarraEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco);
																\param[in]	hDC			: hDC donde se va a pintar la BarraEx.
																\param[in]	Region		: Region que contiene el borde de la BarraEx.
																\param[in]	TieneFoco	: Valor en el que determinamos si pintamos el borde con foco o sin foco.
																\return		No devuelve nada.
																\remarks	Esta función pinta solo el borde de la BarraEx.
														*/
		 virtual void			        				BarraEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco);

														//! Función que retorna el valor minimo para la BarraEx.
														/*! Esta funcion devuelve el valor minimo para la BarraEx.
																\fn			inline virtual long BarraEx_Minimo(void) const;
																\return		Devuelve el valor minimo para la BarraEx.
																\sa			BarraEx_Maximo(), BarraEx_Valor()
														*/
		 inline virtual long						    BarraEx_Minimo(void) const {
															return _BarraEx_Minimo;
														};

														//! Función que asigna el valor minimo para la BarraEx.
														/*! Esta funcion asigna el valor minimo para la BarraEx.
																\fn			inline virtual void BarraEx_Minimo(const long nMinimo);
																\param[in]	nMinimo : Nuevo valor minimo.
																\return		No devuelve nada.
																\sa			BarraEx_Maximo(), BarraEx_Valor()
														*/
		 inline virtual void							BarraEx_Minimo(const long nMinimo) {
															_BarraEx_Minimo = nMinimo;
														};

														//! Función que retorna el valor maximo para la BarraEx.
														/*! Esta funcion devuelve el valor maximo para la BarraEx.
																\fn			inline virtual long BarraEx_Maximo(void) const;
																\return		Devuelve el valor maximo para la BarraEx.
																\sa			BarraEx_Minimo(), BarraEx_Valor()
														*/
		 inline virtual long				    		BarraEx_Maximo(void) const {
															return _BarraEx_Maximo;
														};

														//! Función que asigna el valor maximo para la BarraEx.
														/*! Esta funcion asigna el valor maximo para la BarraEx.
																\fn			inline virtual void BarraEx_Maximo(const long nMaximo);
																\param[in]	nMaximo : Nuevo valor maximo.
																\return		No devuelve nada.
																\sa			BarraEx_Minimo(), BarraEx_Valor()
														*/
		 inline virtual void							BarraEx_Maximo(const long nMaximo) {
															_BarraEx_Maximo = nMaximo;
														};

														//! Función que retorna el valor actual para la BarraEx.
														/*! Esta funcion devuelve el valor actual para la BarraEx.
																\fn			inline virtual long BarraEx_Valor(void) const;
																\return		Devuelve el valor actual para la BarraEx.
																\sa			BarraEx_Minimo(), BarraEx_Maximo()
														*/
		 inline virtual long    					    BarraEx_Valor(void) const {
															return _BarraEx_Valor;
														};

														//! Función que asigna el valor actual para la BarraEx.
														/*! Esta funcion asigna el valor actual para la BarraEx.
																\fn			inline virtual void BarraEx_Valor(const long nValor);
																\param[in]	nValor : Nuevo valor actual.
																\return		No devuelve nada.
																\sa			BarraEx_Minimo(), BarraEx_Maximo()
														*/
		 inline virtual void							BarraEx_Valor(const long nValor) {
															_BarraEx_Valor = nValor;
														};

														//! Función que suma el valor actual para la BarraEx.
														/*! Esta funcion suma el valor actual para la BarraEx.
																\fn			virtual int BarraEx_Valor_SumarValor(const long SumValor);
																\param[in]	SumValor : Valor que se sumara al valor actual de la BarraEx.
																\return		Devuelve el valor actual.
														*/
		 virtual int					        	    BarraEx_Valor_SumarValor(const long SumValor);

														//! Función que resta el valor actual para la BarraEx.
														/*! Esta funcion resta el valor actual para la BarraEx.
																\fn			virtual int BarraEx_Valor_RestarValor(const long RestValor);
																\param[in]	RestValor : Valor que se restara al valor actual de la BarraEx.
																\return		Devuelve el valor actual.
														*/
		 virtual int					        	    BarraEx_Valor_RestarValor(const long RestValor);

														//! Función para asignar el ancho de borde a la BarraEx.
														/*! Esta funcion asigna el ancho del borde para la BarraEx.
																\fn			inline virtual void BarraEx_TamBorde(const int NumPixels);
																\param[in]	NumPixels : Tamaño en pixeles del borde.
																\return		No devuelve nada.
														*/
/*		 inline virtual void							BarraEx_TamBorde(const int NumPixels) {
															_BarraEx_TamBorde = NumPixels;
														};*/

														//! Función para retornar el ancho de borde a la BarraEx.
														/*! Esta funcion devuelve el ancho del borde para la BarraEx.
																\fn			inline const int BarraEx_TamBorde(void);
																\return		Devuelve el tamaño en pixeles del borde para la BarraEx.
														*/
/*		 inline const int 								BarraEx_TamBorde(void) {
															return _BarraEx_TamBorde;
														};*/

														//! Función para retornar el estado de la BarraEx.
														/*! Esta funcion devuelve el estado de la BarraEx.
																\fn			inline DWL_Enum_BarraEx_Estados BarraEx_Estado(void) const;
																\return		Devuelve el estado de la BarraEx.
														*/
		 inline DWL_Enum_BarraEx_Estados		    	    BarraEx_Estado(void) const {
															return _BarraEx_Estado;
														};

														//! Función para asignar la orientacion y el tipo de BarraEx.
														/*! Esta funcion asigna el orientacion y el tipo para la BarraEx.
																\fn			inline virtual void BarraEx_Orientacion(const int nOrientacion);
																\param[in]	nOrientacion : Tipo y orientacion para la BarraEx. Puede ser uno de los siguientes :
																						   DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL , DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL,
																						   DWL_BARRAEX_PROGRESO_HORIZONTAL y DWL_BARRAEX_PROGRESO_VERTICAL.
																\return		No devuelve nada.
														*/
/*		 void											BarraEx_Orientacion(const int nOrientacion) {
															_BarraEx_Orientacion = nOrientacion;
														};*/


														//! Estilos de la BarraEx.
		 DWLBarraEx_Estilos								BarraEx_Estilos;

														//! Función que procesa el movimiento del mouse en la BarraEx.
														/*! Esta función procesa el movimiento del mouse en la BarraEx.
																\fn			BOOL BarraEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT wParam);
																\param[in]	hWndControl		: HWND del control que contiene la BarraEx.
																\param[in]	RectaControl	: Recta con el espacio de la BarraEx.
																\param[in]	cX				: Coordenada X del mouse relativa al control.
																\param[in]	cX				: Coordenada Y del mouse relativa al control.
																\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
																\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
																\remarks    Esta función debe ser enlazada con el Evento_Mouse_Movimiento del control que vaya a contener la BarraEx.
																\sa			BarraEx_Mouse_BotonPresionado(), BarraEx_Mouse_BotonSoltado()
														*/
		 BOOL										    BarraEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param);

														//! Función que procesa los botones soltados del mouse en la BarraEx
														/*! Esta función procesa los botones soltados del mouse en la BarraEx.
																\fn			BOOL BarraEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
																\param[in]	hWndControl		: HWND del control que contiene la BarraEx.
																\param[in]	RectaControl	: Recta con el espacio de la BarraEx.
																\param[in]	Boton			: Boton del mouse presionado.
																\param[in]	cX				: Coordenada X del mouse relativa al control.
																\param[in]	cX				: Coordenada Y del mouse relativa al control.
																\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
																\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
																\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonSoltado del control que vaya a contener la BarraEx.
																\sa			BarraEx_Mouse_Movimiento(), BarraEx_Mouse_BotonPresionado()
														*/
		 BOOL										    BarraEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);

														//! Función que procesa los botones presionados del mouse en la BarraEx.
														/*! Esta función procesa los botones presionados del mouse en la BarraEx.
																\fn			BOOL BarraEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
																\param[in]	hWndControl		: HWND del control que contiene la BarraEx.
																\param[in]	RectaControl	: Recta con el espacio de la BarraEx.
																\param[in]	Boton			: Boton del mouse presionado.
																\param[in]	cX				: Coordenada X del mouse relativa al control.
																\param[in]	cX				: Coordenada Y del mouse relativa al control.
																\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
																\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
																\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonPresionado del control que vaya a contener la BarraEx.
																\sa			BarraEx_Mouse_Movimiento(), BarraEx_Mouse_BotonSoltado()
														*/
		 BOOL   										BarraEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);

		protected : //////////////////////////////////////

														//! Función que retorna el valor resultado de las coordenadas especificadas.
														/*! Esta función devuelve el valor resultado de las coordenadas especificadas.
																\fn			const long BarraEx_MirarValor(RECT *Espacio, const int cX, const int cY);
																\param[in]	Espacio	: Recta que contiene el espacio de la BarraEx.
																\param[in]	cX		: Coordenada X.
																\param[in]	cY		: Coordenada Y.
																\return		Devuelve el valor que corresponderia a las coordenadas introducidas.
														*/
         long	    						    		BarraEx_MirarValor(RECT *Espacio, const int cX, const int cY);

														//! Valor minimo de la barra
		 long								           _BarraEx_Minimo;

														//! Valor maximo de la barra
		 long								           _BarraEx_Maximo;

														//! Valor actual de la barra
		 long								           _BarraEx_Valor;

														//! Estado de la barra
		 DWL_Enum_BarraEx_Estados				           _BarraEx_Estado;

														//! Ultimo estado de la barra
		 DWL_Enum_BarraEx_Estados					       _BarraEx_PEstado;

														//! Barra presionada
		 bool							               _BarraEx_Presionado;

														//! Orientacion y tipo de la barra
														/* Parametros posibles :
															DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL , DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL,
															DWL_BARRAEX_PROGRESO_HORIZONTAL , DWL_BARRAEX_PROGRESO_VERTICAL
														*/
//		 int								           _BarraEx_Orientacion;

														//! Tamaño del borde
//		 int								           _BarraEx_TamBorde;
		};												//
		////////////////////////////////////////////////// Fin DWLBarraEx_Nucleo
    };
};

#endif
