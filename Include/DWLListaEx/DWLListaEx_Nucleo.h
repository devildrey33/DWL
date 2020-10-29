#ifndef DWL_LISTAEX_NUCLEO_H
#define DWL_LISTAEX_NUCLEO_H

#include "DWLListaEx_Item.h"
#include "DWLListaEx_Columna.h"
#include "DWLListaEx_ParametrosClick.h"
#include "DWLListaEx_ParametrosLabelEdit.h"
 
#include "..\DWLBarraScrollEx.h"
#include "..\DWLToolTipEx.h"

/////////// Modo Debug ///////////
//#define DWL_LISTAEX_DEBUG		// Descomenta esta linea para que se muestren mensajes de debug para este control
//////////////////////////////////



//! Definicion para a�adir items al principio
#define DWL_LISTAEX_PRINCIPIO						0
//! Definicion para a�adir items ordenados alfabeticamente
#define DWL_LISTAEX_ORDENADO						-1
//! Definicion para a�adir items al final
#define DWL_LISTAEX_FIN								-2


//! Definicion que establece la alineacion del texto a la izquierda
#define DWL_LISTAEX_TEXTO_IZQUIERDA					DT_LEFT
//! Definicion que establece la alineacion del texto al centro
#define DWL_LISTAEX_TEXTO_CENTRADO					DT_CENTER
//! Definicion que establece la alineacion del texto a la derecha
#define DWL_LISTAEX_TEXTO_DERECHA					DT_RIGHT


//! Definicion que establece la ListaEx con Filas y Columnas verticales
#define DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL		0
//! Definicion que establece la ListaEx con Filas horizontales
#define DWL_LISTAEX_FILAS_HORIZONTAL				1

//! Enumeraci�n de posibles HitTest.
enum DWL_Enum_ListaEx_HitTest {
	DWL_Enum_ListaEx_HitTest_Texto			= 0, // Solo el texto
	DWL_Enum_ListaEx_HitTest_Icono			= 1, // Solo el icono
	DWL_Enum_ListaEx_HitTest_Texto_Icono	= 2  // Texto y expansor
};


namespace DWL {
	namespace ControlesEx {
		//! Clase nucleo de la ListaEx que hereda de DWLBarraScrollEx_Nucleo.
		class DWLListaEx_Nucleo : public DWLBarraScrollEx_Nucleo {
		public : ///////////////////////////////////// Miembros publicos

													//! Constructor por defecto.
													/*! Constructor por defecto.
															\fn			DWLListaEx_Nucleo(void);
															\return		No devuelve nada.
													*/
													DWLListaEx_Nucleo(void);

													//! Destructor.
													/*! Destructor.
															\fn			~DWLListaEx_Nucleo(void);
															\return		No devuelve nada.
													*/
												   ~DWLListaEx_Nucleo(void);

													//! Funci�n virtual que debera sobreescribir el control para repintar.
													/*! Esta funcion virtual debe ser re-escrita en la clase contenedora de este control para pintar todo el control.
															\fn			virtual void Repintar(const bool Forzar = false);
															\param[in]	nForzar	: Valor que determina si se fuerza el repintado.
															\return		No devuelve nada.
															\remarks	Si se espeficica false en nForzar, la funcion repintar debera decidir si se repinta el control o no.
													*/
		 virtual void								Repintar(const bool Forzar = false) {
												    };

													//! Funci�n que pinta la listaex en el DC y espacio especificados.
													/*! Esta funcion pinta la ListaEx en las coordenadas y DC especificados.
															\fn			void ListaEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true, const bool PintarConMascara = false);;
															\param[in]	hDC					: DC en el que se va a pintar la ListaEx.
															\param[in]	Espacio				: Recta que delimita el espacio donde se puede pintar la ListaEx.
															\param[in]	TieneFoco			: Valor que determina si la lista tiene el foco del raton (por defecto se usara la funcion Foco()).
															\param[in]	PintarConMascara	: Valor que determina si se va a pintar el contorno del control con SRCAND antes de pintar el control.
															\return		No devuelve nada.
															\remarks	Esta funci�n esta preparada para pintar la ListaEx en un DC que no sea el suyo, o que sea compartido.
																		Por ello debemos especificar las coordenadas donde se va a pintar, si tiene el foco del raton o no, y por ultimo si debemos
																		pintar la mascara.
																		El parametro PintarMascara solo es necesario si vamos a pintar la ListaEx en un DC que no es el suyo y requerimos el pintado
																		del borde del control. Entonces la funci�n de pintado pintara el contorno de la ListaEx con SRCAND, y luego pintara el control
																		con SRC_PAINT para que no se vean graficos desfasados en el borde.
															\sa			ListaEx_PintarItem_Filas_y_Columnas_Vertical(), ListaEx_PintarItem_Filas_Horizontal().
													*/
		 void										ListaEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true, const bool PintarConMascara = false);

													//! Funci�n para decidir si mostramos los encabezados de las columnas.
													/*! Esta funci�n determina si se van a mostrar los encabezados de las columnas.
															\fn			inline void ListaEx_MostrarEncabezadosColumnas(const bool nMostrarEncabezados);
															\param[in]	nMostrarEncabezados : True para mostrar los encabezados de las columnas, false para dejarlos ocultos.
															\return		No devuelve nada.
													*/
		 inline void								ListaEx_MostrarEncabezadosColumnas(const bool nMostrarEncabezados) {
														ListaEx_Estilos.MostrarEncabezadosColumnas = nMostrarEncabezados;
													};

													//! Funci�n para decidir si mostramos los iconos.
													/*! Esta funci�n determina si se van a mostrar los iconos de los items.
															\fn			inline void ListaEx_MostrarIconos(const bool nPintarIconos);
															\param[in]	nPintarIconos : True para pintar los iconos, false para no pintar iconos.
															\return		No devuelve nada.
													*/
		 inline void				                ListaEx_MostrarIconos(const bool nPintarIconos) {
														ListaEx_Estilos.PintarIconos = nPintarIconos;
													};

													//! Funci�n que retorna si se van a pintar iconos de los items.
													/*! Esta funci�n develve si se van a pintar los iconos de los items.
															\fn			inline bool ListaEx_MostrarIconos(void) const;
															\return		Devuelve true si se van a pintar iconos, false en caso contrario.
													*/
		 inline bool							    ListaEx_MostrarIconos(void) const {
														return ListaEx_Estilos.PintarIconos;
													};

													//! Funci�n que se usa para pintar los encabezados de las columnas.
													/*! Esta funci�n se usa para pintar los encabezados de las columnas.
															\fn			void ListaEx_PintarColumnas(HDC hDC, RECT *EspacioControl);
															\param[in]	hDC				: HDC donde se va a pintar los encabezados de las columnas.
															\param[in]  EspacioControl	: Espacio de todo el control ListaEx.
															\return		No devuelve nada.
													*/
		 void										ListaEx_PintarColumnas(HDC hDC, RECT *EspacioControl);

													//! Funci�n que retorna el item que esta debajo de las coordenadas especificadas.
													/*! Esta funci�n retorna el item o la parte del nodo que esta debajo de las coordenadas especificadas.
															\fn			DWLListaEx_Item *ListaEx_HitTest(HWND hWndControl, const int cX, const int cY, const DWL_Enum_ListaEx_HitTest Tipo = HitTest_Texto_Icono);
															\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
															\param[in]	cX			: Coordenada X.
															\param[in]	cY			: Coordenada Y.
															\param[in]	nTipo		: Tipo de busqueda.
															\return		No devuelve nada.
															\remarks	Hay varios tipos de busqueda : [HitTest_Texto] Solo el texto, [HitTest_Icono] Solo el icono, [HitTest_Texto_Icono] Texto y icono.
													*/
		 DWLListaEx_Item						   *ListaEx_HitTest(HWND hWndControl, const int cX, const int cY, const DWL_Enum_ListaEx_HitTest Tipo = DWL_Enum_ListaEx_HitTest_Texto_Icono);

													//! Funci�n que agrega una columna a la ListaEx.
													/*! Esta funci�n agrega una columna a la ListaEx.
															\fn			void ListaEx_AgregarColumna(const int nAncho = DWL_LISTAEX_ANCHO_AUTOMATICO, const int nAlineacion = DWL_LISTAEX_TEXTO_IZQUIERDA, const TCHAR *NombreColumna = NULL);
															\param[in]	nAncho			: Ancho en pixeles para la columna (puede ser DWL_LISTAEX_ANCHO_AUTOMATICO).
															\param[in]	nAlineacion		: Alineacion del texto de la columna (puede ser DWL_LISTAEX_TEXTO_IZQUIERDA, DWL_LISTAEX_TEXTO_CENTRADO, DWL_LISTAEX_TEXTO_DERECHA).
															\param[in]	NombreColumna	: Nombre para la columna (NULL por defecto).
															\return		No devuelve nada.
															\remarks	Si vas a usar la lista en modo DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL debes crear como minimo una columna, en caso de usar el modo DWL_LISTAEX_FILAS_HORIZONTAL las columnas no se tienen en cuenta.
													*/
		 void										ListaEx_AgregarColumna(const int nAncho = DWL_LISTAEX_ANCHO_AUTOMATICO, const int nAlineacion = DWL_LISTAEX_TEXTO_IZQUIERDA, const TCHAR *NombreColumna = NULL);

													//! Funci�n para eliminar la columna especificada.
													/*! Esta funci�n elimina la columna especificada.
															\fn			void ListaEx_EliminarColumna(HWND hWndControl, const int Pos);
															\param[in]	hWndControl : HWND del control que contiene la ListaEx.
															\param[in]	nPos		: Posicion de la columna a eliminar.
															\return		No devuelve nada.
															\remarks	Cuando eliminamos una columna, NO SE ELIMINAN los datos de los items referentes a esa posicion de la columna.
													*/
		 void										ListaEx_EliminarColumna(HWND hWndControl, const int nPos);

													//! Funci�n para eliminar todas las columnas.
													/*! Esta funcion elimina todas las columnas de la ListaEx.
															\fn			void ListaEx_EliminarTodasLasColumnas(HWND hWndControl);
															\param[in]	hWndControl : HWND del control que contiene la ListaEx.
															\return		No devuelve nada.
															\remarks	Cuando eliminamos todas las columnas, NO SE ELIMINAN los datos de los items para las posiciones de las columnas.
													*/
		 void										ListaEx_EliminarTodasLasColumnas(HWND hWndControl);

													//! Funci�n para agregar un item (INTERNA).
													/*! Esta funci�n es de uso interno para la clase DWLListaEx de forma que pueda pasar los parametros opcionales a esta.
															\fn			DWLListaEx_Item *ListaEx_AgregarItem(DWLListaEx_Item *nItem, const int nIcono, const int Posicion, const TCHAR *Txt, va_list Marker);
															\param[in]	nItem		: Item heredado, en caso de ser un DWLListaEx_Item puedes especificar NULL.
															\param[in]	nIcono		: Icono para el item.
															\param[in]	nPosicion	: Posicion en la que se agregara el item. Puede ser (DWL_LISTAEX_FIN, DWL_LISTAEX_INICIO, y DWL_LISTAEX_ORDENADO)
															\param[in]	nTexto		: Texto para el item.
															\param[in]	Marker		: Parametro que contiene una lista de parametros opcionales.
															\return		Devuelve un puntero a la clase DWLListaEx_Item que acabamos de crear / a�adir.
															\remarks	Se deben a�adir tantos textos en los parametros opcionales como columnas -1 tenga la lista.
													*/
		 DWLListaEx_Item                           *ListaEx_AgregarItem(DWLListaEx_Item *nItem, const int nIcono, const int nPosicion, const TCHAR *nTexto, va_list Marker);

													//! Funci�n para agregar un item.
													/*! Esta funci�n se usa para agregar un item a la ListaEx.
															\fn			DWLListaEx_Item *ListaEx_AgregarItem(DWLListaEx_Item *nItem = NULL, const int nIcono = NULL, const int Posicion = DWL_LISTAEX_FIN, const TCHAR *Txt = NULL, ...);
															\param[in]	nItem		: Item heredado, en caso de ser un DWLListaEx_Item puedes especificar NULL.
															\param[in]	nIcono		: Icono para el item.
															\param[in]	nPosicion	: Posicion en la que se agregara el item. Puede ser (DWL_LISTAEX_FIN, DWL_LISTAEX_INICIO, y DWL_LISTAEX_ORDENADO)
															\param[in]	nTexto		: Texto para el item.
															\param[in]	...			: Parametros opcionales en los que debemos especificar los textos para los subitems.
															\return		Devuelve un puntero a la clase DWLListaEx_Item que acabamos de crear / a�adir.
															\remarks	Se deben a�adir tantos textos en los parametros opcionales como columnas -1 tenga la lista.
													*/
		 DWLListaEx_Item                           *ListaEx_AgregarItem(DWLListaEx_Item *nItem = NULL, const int nIcono = NULL, const int Posicion = DWL_LISTAEX_FIN, const TCHAR *Txt = NULL, ...);

													//! Funci�n que enlaza todos los items entre ellos y calcula los valores del scroll.
													/*!	Esta funci�n es la encargada de enlazar todos los items entre ellos y calcular las posiciones para los scrolls.
															\fn			void ListaEx_FinAgregarItems(HWND hWndControl);
															\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
															\return		No devuelve nada.
															\remarks	Esta funci�n debe ser llamada cuando terminemos de agregar el ultimo item a la lista.
													*/
		 void										ListaEx_FinAgregarItems(HWND hWndControl);

													//! Funci�n que actualiza todos los datos de la ListaEx.
													/*! Esta funci�n actualiza todos los datos de la ListaEx.
															\fn			void ListaEx_ActualizarTodo(HWND hWndControl, RECT *Espacio);
															\param[in]	hWndControl	  : HWND del control que contiene la ListaEx.
															\param[in]	Espacio		  : Recta que debe contener el espacio para la ListaEx.
															\return		No devuelve nada.
															\remarks	Esta funci�n se usa para actualizar todos los estilos y nodos del ListaEx. Si necesitas actualizar el tama�o de los textos por haber cambiado la fuente, deberas usar tambien ListaEx_ActualizarTamTexto().
													*/
		 void                                       ListaEx_ActualizarTodo(HWND hWndControl, RECT *Espacio);


													//! Funci�n que recalcula los tama�os de todos los textos de la ListaEx.
													/*! Esta funci�n recaltula los tama�os de todos los textos de la ListaEx.
															\fn			void ListaEx_ActualizarTamTexto(void);
															\return		No devuelve nada.
													*/
		 void                                       ListaEx_ActualizarTamTexto(void);

													//! Funci�n para eliminar un item y sus subitems.
													/*! Esta funcion elimina el item especificado.
															\fn			void ListaEx_EliminarItem(HWND hWndControl, const unsigned int nPos, const bool nRepintar = false);
															\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
															\param[in]	nPos		: Posicion del item que se va a eliminar.
															\param[in]	nRepintar	: Parametro en el que especificamos si la ListaEx debe ser repintada.
															\return		No devuelve nada.
															\remarks	Cuando eliminamos un item se borra toda su memoria, incluso si ese item es heredado lo eliminamos por completo. Asegurate de tener un destructor que elimine los datos de tus items heredados.
													*/
		 void										ListaEx_EliminarItem(HWND hWndControl, const unsigned int nPos, const bool nRepintar = false);

													//! Funci�n para eliminar un item y sus subitems.
													/*! Esta funcion elimina el item especificado.
															\fn			void ListaEx_EliminarItem(HWND hWndControl, DWLListaEx_Item *nItem, const bool nRepintar = false);
															\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
															\param[in]	nItem		: Clase DWLListaEx_Item que se va a eliminar.
															\param[in]	nRepintar	: Parametro en el que especificamos si la ListaEx debe ser repintada.
															\return		No devuelve nada.
															\remarks	Cuando eliminamos un item se borra toda su memoria, incluso si ese item es heredado lo eliminamos por completo. Asegurate de tener un destructor que elimine los datos de tus items heredados.
													*/
		 void										ListaEx_EliminarItem(HWND hWndControl, DWLListaEx_Item *nItem, const bool nRepintar = false);

													//! Funci�n para eliminar los items seleccionados.
													/*! Esta funci�n elimina todos los items seleccionados de la ListaEx.
															\fn			UINT ListaEx_EliminarItemsSeleccionados(HWND hWndControl, const bool nRepintar = true);
															\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
															\param[in]	nRepintar	: Parametro en el que especificamos si la ListaEx debe ser repintada.
															\return		Devuelve el total de items eliminados.
															\remarks	Cuando eliminamos un item se borra toda su memoria, incluso si ese item es heredado lo eliminamos por completo. Asegurate de tener un destructor que elimine los datos de tus items heredados.
													*/
		 UINT				        				ListaEx_EliminarItemsSeleccionados(HWND hWndControl, const bool nRepintar = true);

													//! Funci�n para eliminar todos los items.
													/*! Esta funci�n elimina todos los items de la ListaEx.
															\fn			void ListaEx_EliminarTodosLosItems(HWND hWndControl, const bool nRepintar = true);
															\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
															\param[in]	nRepintar	: Parametro en el que especificamos si la ListaEx debe ser repintada.
															\return		No devuelve nada.
															\remarks	Cuando eliminamos un item se borra toda su memoria, incluso si ese item es heredado lo eliminamos por completo. Asegurate de tener un destructor que elimine los datos de tus items heredados.
													*/
		 void										ListaEx_EliminarTodosLosItems(HWND hWndControl, const bool nRepintar = true);

													//! Funci�n que retorna el item especificado.
													/*! Esta funci�n devuelve el item especificado.
															\fn			inline DWLListaEx_Item *ListaEx_Item(const unsigned int nPos);
															\param[in]	nPos	: Posicion del item que queremos obtener.
															\return		Devuelve un puntero a la clase DWLListaEx_Item especificada en el parametro nPos.
													*/
		 inline DWLListaEx_Item				       *ListaEx_Item(const unsigned int nPos) {
														return _ListaEx_Items[nPos];
													};

													//! Funci�n que retorna la columna especificada.
													/*! Esta funci�n devuelve la columna especificada.
															\fn			inline DWLListaEx_Columna *ListaEx_Columna(const unsigned int nPos);
															\param[in]	nPos	: Posicion de la columna que queremos obtener.
															\return		Devuelve un puntero a la clase DWLListaEx_Columna especificada en el parametro nPos.
													*/
		 inline DWLListaEx_Columna                 *ListaEx_Columna(const unsigned int nPos) {
														return _ListaEx_Columnas[nPos];
													};

													//! Funci�n que retorna la altura de un item en pixeles.
													/*! Esta funci�n devuelve la altura de un item en pixeles.
															\fn			inline UINT ListaEx_AltoLinea(void) const;
															\return		Devuelve la altura de un item en pixeles.
													*/
		 inline UINT            					ListaEx_AltoLinea(void) const {
														return _ListaEx_AltoLinea;
													};

													//! Funci�n que asigna la altura de un item en pixeles.
													/*! Esta funci�n asigna la altura de un item en pixeles.
															\fn			void ListaEx_AltoLinea(HWND hWndControl, const unsigned int nAlto);
															\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
															\param[in]	nAlto		: Nueva altura en pixeles para los items.
															\return		No devuelve nada.
													*/
		 void										ListaEx_AltoLinea(HWND hWndControl, const unsigned int nAlto);

													//! Funci�n que elimina el estado de selecci�n en todos los items.
													/*! Esta funci�n elimina el estado de selecci�n en todos los items.
															\fn			void ListaEx_DesSeleccionarTodo(const bool bRepintar = true);
															\param[in]	bRepintar	: Valor en el que especificamos si debemos repintar la ListaEx.
															\return		No devuelve nada.
													*/
		 void										ListaEx_DesSeleccionarTodo(const bool bRepintar = true);

													//! Funci�n que muestra en pantalla el item especificado.
													/*! Esta funci�n muestra en pantalla el item especificado.
															\fn			void ListaEx_MostrarItem(const int nPos);
															\param[in]	nPos	: Posici�n del item que queremos mostrar.
															\return		No devuelve nada.
													*/
		 void										ListaEx_MostrarItem(const int nPos);

													//! Funci�n que muestra en pantalla el item especificado.
													/*! Esta funci�n muestra en pantalla el item especificado.
															\fn			void ListaEx_MostrarItem(DWLListaEx_Item *vItem);
															\param[in]	vItem	: Clase DWLListaEx_Item que queremos mostrar.
															\return		No devuelve nada.
													*/
		 void										ListaEx_MostrarItem(DWLListaEx_Item *vItem);

													//! Funci�n que retorna el total de items que contiene la ListaEx.
													/*! Esta funci�n devuelve el total de items que contiene la ListaEx.
															\fn			inline UINT ListaEx_TotalItems(void) const;
															\return		Devuelve el total de items de la ListaEx.
													*/
		 inline UINT            					ListaEx_TotalItems(void) const {
														return static_cast<UINT>(_ListaEx_Items.size());
													};

													//! Funci�n que retorna el total de items seleccionados que contiene la ListaEx.
													/*! Esta funci�n devuelve el total de items seleccionados que contiene la ListaEx.
															\fn			inline UINT ListaEx_TotalItemsSeleccionados(void) const;
															\return		Devuelve el total de items seleccionados de la ListaEx.
													*/
		 inline UINT            					ListaEx_TotalItemsSeleccionados(void) const {
														int R = 0;
														for (unsigned int i = 0; i < _ListaEx_Items.size(); i++) {
															if (_ListaEx_Items[i]->_Seleccionado == true) R++;
														}
														return R;
													};

													//! Funci�n que retorna el total de columnas que contiene la ListaEx.
													/*! Esta funci�n devuelve el total de columnas que contiene la ListaEx.
															\fn			inline UINT ListaEx_TotalColumnas(void) const;
															\return		Devuelve el total de columnas de la ListaEx.
													*/
		 inline UINT            					ListaEx_TotalColumnas(void) const {
														return static_cast<UINT>(_ListaEx_Columnas.size());
													};

													//! Funci�n para empezar la edicion de un item.
													/*! Esta funci�n inicia la edicion de un item.
															\fn			HWND ListaEx_EmpezarLabelEdit(HWND hWndControl, DWLListaEx_Item *eItem, const unsigned int eSubItem = 0, const bool Numerico);
															\param[in]	hWndControl : HWND del control que contiene la ListaEx.
															\param[in]	eItem		: Clase DWLListaEx_Item que se va a editar.
															\param[in]	eSubItem	: Posicion del subitem que se va a editar.
															\param[in]	Numerico	: True para que la edicion solo acepte digitos, false para que acepte todos los caracteres.
															\return		Devuelve el HWND del EditBox creado para editar el nodo.
															\sa			ListaEx_TerminarLabelEdit(), ListaEx_CancelarLabelEdit()
													*/
		 HWND										ListaEx_EmpezarLabelEdit(HWND hWndControl, DWLListaEx_Item *eItem, const unsigned int eSubItem = 0, const bool Numerico = false);

													//! Funci�n para terminar la edicion de un item guardando los datos.
													/*! Esta funci�n termina la edicion de un item guardando los datos.
															\fn			HWND ListaEx_TerminarLabelEdit(HWND hWndControl);
															\param[in]	hWndControl : HWND del control que contiene la ListaEx.
															\return		No devuelve nada.
															\sa			ListaEx_EmpezarLabelEdit(), ListaEx_CancelarLabelEdit()
													*/
		 void										ListaEx_TerminarLabelEdit(HWND hWndControl);

													//! Funci�n para cancelar la edicion de un item sin guardar los datos.
													/*! Esta funci�n cancela la edicion de un item sin guardar los datos.
															\fn			HWND ListaEx_CancelarLabelEdit(HWND hWndControl);
															\param[in]	hWndControl : HWND del control que contiene la ListaEx.
															\return		No devuelve nada.
															\sa			ListaEx_EmpezarLabelEdit(), ListaEx_TerminarLabelEdit()
													*/
		 void										ListaEx_CancelarLabelEdit(HWND hWndControl);

													//! Funci�n que obtiene el espacio que necesita el subitem para ser pintado.
													/*! Esta funcion obtiene el espacio que necesita el subitem para ser pintado.
															\fn			RECT *ListaEx_ObtenerRectaItem(const int nItem, const int nSubItem, RECT *Ret);
															\param[in]	nItem		: Numero de Item del que queremos obtener el espacio.
															\param[in]	nSubItem	: Numero de SubItem del que queremos obtener el espacio.
															\param[out]	Ret			: Recta en la que se asignara el espacio necesario para el subitem.
															\return		Devuelve un puntero al parametro Ret.
													*/
		 RECT                                      *ListaEx_ObtenerRectaItem(const int nItem, const int nSubItem, RECT *Ret);

													//! Funci�n que obtiene el espacio que necesita el subitem para ser pintado.
													/*! Esta funcion obtiene el espacio que necesita el subitem para ser pintado.
															\fn			RECT *ListaEx_ObtenerRectaItem(DWLListaEx_Item *nItem, const int nSubItem, RECT *Ret);
															\param[in]	nItem		: Clase DWLListaEx_Item de la que queremos obtener el espacio.
															\param[in]	nSubItem	: Numero de SubItem del que queremos obtener el espacio.
															\param[out]	Ret			: Recta en la que se asignara el espacio necesario para el subitem.
															\return		Devuelve un puntero al parametro Ret.
													*/
		 RECT                                      *ListaEx_ObtenerRectaItem(DWLListaEx_Item *nItem, const int nSubItem, RECT *Ret);

													//! Funci�n que asigna el item resaltado.
													/*! Esta funcion asigna el item resaltado.
															\fn			inline void ListaEx_ItemResaltado(DWLListaEx_Item *nSel);
															\param[in]	nSel	: Clase DWLListaEx_Item que queremos resaltar.
															\return		No devuelve nada.
															\sa			ListaEx_ItemMarcado(), ListaEx_SubItemResaltado(), ListaEx_Item()
													*/
		 inline void								ListaEx_ItemResaltado(DWLListaEx_Item *nSel) {
														_ListaEx_ItemResaltado = nSel;
													};

													//! Funci�n que retorna el item resaltado.
													/*! Esta funcion devuelve el item resaltado.
															\fn			inline DWLListaEx_Item *ListaEx_ItemResaltado(void);
															\return		Devuelve el item resaltado, o NULL si no hay item resaltado.
															\sa			ListaEx_ItemMarcado(), ListaEx_SubItemResaltado(), ListaEx_Item()
													*/
		 inline DWLListaEx_Item                    *ListaEx_ItemResaltado(void) {
														return _ListaEx_ItemResaltado;
													};

													//! Funci�n que retorna el item marcado.
													/*! Esta funcion devuelve el item marcado.
															\fn			inline DWLListaEx_Item *ListaEx_ItemMarcado(void);
															\return		Devuelve el item resaltado, o NULL si no hay item resaltado.
															\sa			ListaEx_ItemResaltado(), ListaEx_SubItemResaltado(), ListaEx_Item()
													*/
		 inline DWLListaEx_Item                    *ListaEx_ItemMarcado(void) {
														return _ListaEx_ItemMarcado;
													};

													//! Funci�n que asigna el item marcado.
													/*! Esta funcion asigna el item marcado.
															\fn			inline void ListaEx_ItemMarcado(DWLListaEx_Item *nSel);
															\param[in]	nSel	: Puntero a la clase DWLListaEx_Item que queremos remarcar.
															\return		No devuelve nada.
															\sa			ListaEx_ItemResaltado(), ListaEx_SubItemResaltado(), ListaEx_Item()
													*/
		 inline void								ListaEx_ItemMarcado(DWLListaEx_Item *nSel) {
														_ListaEx_ItemMarcado = nSel;
													};

													//! Funci�n que retorna la posicion del subitem resaltado dentro del item.
													/*! Esta funcion devuelve la posicion del subitem resaltado dentro del item.
															\fn			inline int ListaEx_SubItemResaltado(void) const;
															\return		Devuelve la posicion del subitem resaltado.
															\sa			ListaEx_ItemResaltado(), ListaEx_ItemMarcado(), ListaEx_Item()
													*/
		 inline int							        ListaEx_SubItemResaltado(void) const {
														return _ListaEx_SubItemResaltado;
													};

													//! Funci�n para desactivar / activar las transparencias en la ListaEx.
													/*! Esta funci�n desactiva / activa las transparencias en la ListaEx.
															\fn			void ListaEx_DesactivarAlphaBlend(const bool nDesactivar);
															\param[in]	nDesactivar : True para desactivar transparencias, False para activarlas.
															\return		No devuelve nada.
															\remarks	Por defecto las transparecinas estan habilitadas.
													*/
		 inline void								ListaEx_DesactivarAlphaBlend(const bool Desactivar) {
														ListaEx_Estilos.Transparencias = !Desactivar;
													};

													//! Funci�n que retorna el hWnd del EditBox cuando se esta haciendo un LabelEdit.
													/*! Esta funci�n retorna el HWND del EditBox cuando se esta haciendo un LabelEdit.
															\fn			inline HWND ListaEx_hWndEditBox(void);
															\return		Devuelve el HWND del EditBox que se esta usando para la edici�n.
															\sa			ListaEx_EmpezarLabelEdit()
													*/
		 inline HWND								ListaEx_hWndEditBox(void) {
														 return _ListaEx_hWndEdit;
													};

													//! Funci�n que retorna si este control tiene habilitada la multiselecci�n.
													/*! Esta funcion devuelve si este control tiene habilitada la multiselecci�n.
															\fn			inline bool ListaEx_MultiSeleccion(void) const;
															\return		Devuelve true si la multiseleccion esta habilitada, false en caso contrario.
													*/
		 inline bool							    ListaEx_MultiSeleccion(void) const {
														return ListaEx_Estilos.MultiSeleccion;
													};

													//! Funci�n que habilita / deshabilita la multiselecci�n.
													/*! Esta funcion habilita / deshabilita la multiselecci�n.
															\fn			inline void ListaEx_MultiSeleccion(const bool nMultiSeleccion);
															\param[in]	nMultiSeleccion : True para habilitar la multiseleccion, false para deshabilitarla.
															\return		No devuelve nada.
													*/
		 inline void								ListaEx_MultiSeleccion(const bool nMultiSeleccion) {
														ListaEx_Estilos.MultiSeleccion = nMultiSeleccion;
													};

													//! Funci�n virtual que pinta el encabezado de una columna de la ListaEx.
													/*! Esta funci�n virtual pinta el encabezado de una columna de la ListaEx.
															\fn			virtual void ListaEx_Evento_Pintar_Columna(HDC hDC, RECT *Espacio, DWLListaEx_Columna *pColumna);
															\param[in]	hDC			: hDC donde se va a pintar la ListaEx.
															\param[in]	Espacio		: Espacio donde se pintara.
															\param[in]	pColumna	: Puntero a la clase DWLListaEx_Columna que se va a pintar.
															\return		No devuelve nada.
															\remarks	Si _ListaEx_MostrarEncabezadosColumnas es false, esta funci�n no se usara.
													*/
		 virtual void								ListaEx_Evento_Pintar_Columna(HDC hDC, RECT *Espacio, DWLListaEx_Columna *pColumna);

													//! Funci�n virtual que pinta el fondo de la ListaEx con AlphaBlend.
													/*! Esta funci�n virtual pinta el fondo de la ListaEx con AlphaBlend.
															\fn			virtual void ListaEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio);
															\param[in]	hDC		: hDC donde se va a pintar la ListaEx.
															\param[in]	Espacio	: Espacio donde se pintara.
															\return		No devuelve nada.
															\remarks	Si _ListaEx_DesactivarBlend es false, esta funci�n no se usara.
													*/
		 virtual void								ListaEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio);

													//! Funci�n virtual que pinta el icono de un item de la ListaEx.
													/*! Esta funci�n virtual ppinta el icono de un item de la ListaEx.
															\fn			virtual void ListaEx_Evento_Pintar_Icono(HDC hDC, DWLListaEx_Item *nItem, RECT *Espacio);
															\param[in]	hDC			: hDC donde se va a pintar la ListaEx.
															\param[in]	nItem		: Puntero a la clase DWLListaEx_Item que contiene el icono que se va a pintar.
															\param[in]	Espacio		: Espacio donde se pintara.
															\return		No devuelve nada.
															\remarks	Si _ListaEx_MostrarEncabezadosColumnas es false, esta funci�n no se usara.
													*/
		 virtual void								ListaEx_Evento_Pintar_Icono(HDC hDC, DWLListaEx_Item *nItem, RECT *Espacio);

													//! Funci�n virtual que pinta el texto normal de un item de la ListaEx.
													/*! Esta funci�n virtual ppinta el texto normal de un item de la ListaEx.
															\fn			virtual void ListaEx_Evento_Pintar_Item(HDC hDC, DWLListaEx_Item *nItem, const int nSubItem, RECT *Espacio, const int EstadoItem);
															\param[in]	hDC			: hDC donde se va a pintar la ListaEx.
															\param[in]	nItem		: Puntero a la clase DWLListaEx_Item que contiene el icono que se va a pintar.
															\param[in]	nSubItem	: Posicion del subitem del que se va a pintar el texto.
															\param[in]	Espacio		: Espacio donde se pintara.
															\return		No devuelve nada.
													*/
		 virtual void								ListaEx_Evento_Pintar_Item(HDC hDC, DWLListaEx_Item *nItem, const int nSubItem, RECT *Espacio, const int EstadoItem);

													//! Funci�n virtual que monta los datos del tooltip antes de mostrarlo
													/*! Esta funci�n virtual es llamada cuando la ListaEx quiere mostrar un tooltip de un Item.
															\fn			virtual void ListaEx_Evento_MostrarToolTip(DWLListaEx_Item *ttItem);
															\param[in]	ttItem : Item del que se va a mostrar la informacion.
															\return		No devuelve nada.
															\remarks	Por defecto el tooltip muestra el texto del primer subitem y icono del item.
																		Puedes re-emplazar esta funci�n y mostrar los datos que desees del item.
													*/
//		 virtual void								ListaEx_Evento_MostrarToolTip(DWLListaEx_Item *ttItem);

													//! Funci�n virtual que se recibe cuando se presiona una columna.
													/*! Esta funci�n virtual se recibe cuando se presiona una columna.
															\fn			void ListaEx_Evento_ColumnaPresionada(DWLListaEx_Columna *ColumnaPresionada, const UINT Boton, const UINT wParam);
															\param[in]	ColumnaPresionada	: Puntero a la clase DWLListaEx_Columna que se ha presionado.
															\param[in]	Boton				: Boton del mouse que se ha presionado.
															\param[in]	Param				: wParam que contiene si se ha pulsado shift / control y otras teclas extendidas.
															\return		No devuelve nada.
													*/
		 virtual void								ListaEx_Evento_ColumnaPresionada(DWLListaEx_Columna *ColumnaPresionada, const UINT Boton, const UINT Param) { };

													//! Funci�n virtual que pinta el borde de la ListaEx.
													/*! Esta funci�n virtual pinta el borde de la ListaEx.
															\fn			virtual void ListaEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco);
															\param[in]	hDC			: hDC donde se va a pintar el borde de la ListaEx.
															\param[in]	Region		: Region donde se pintara borde de la ListaEx.
															\param[in]	TieneFoco	: Valor en el que determinamos si pintamos el borde con foco o sin foco.
															\return		No devuelve nada.
															\remarks	Si _ListaEx_PintarBorde es false, esta funci�n no se usara.
															\sa			ListaEx_Pintar()
													*/
		 virtual void								ListaEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco);

													//! Funci�n que procesa las teclas presionadas en la ListaEx.
													/*! Esta funci�n procesa las teclas presionadas en la ListaEx.
															\fn			void ListaEx_Teclado_TeclaPresionada(HWND hWndControl, const int Tecla, LPARAM lParam);
															\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
															\param[in]	Tecla		: Tecla que se ha presionado.
															\param[in]	Repeticion	: Repeticion de la tecla.
															\param[in]	Param		: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
															\return		No devuelve nada.
															\remarks    Esta funci�n debe ser enlazada con el Evento_TeclaPresionada del control que vaya a contener la ListaEx.
															\sa			ListaEx_Teclado_TeclaPresionada()
													*/
		 void										ListaEx_Teclado_TeclaPresionada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params);

													//! Funci�n que procesa las teclas soltadas en la ListaEx.
													/*! Esta funci�n procesa las teclas presionadas en la ListaEx.
															\fn			void ListaEx_Teclado_TeclaSoltada(HWND hWndControl, const int Tecla, LPARAM lParam);
															\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
															\param[in]	Tecla		: Tecla que se ha soltado.
															\param[in]	Repeticion	: Repeticion de la tecla.
															\param[in]	Param		: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
															\return		No devuelve nada.
															\remarks    Esta funci�n debe ser enlazada con el Evento_TeclaSoltada del control que vaya a contener la ListaEx.
															\sa			ListaEx_Teclado_TeclaSoltada()
													*/
		 void										ListaEx_Teclado_TeclaSoltada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params);

													//! Funci�n que procesa el movimiento del mouse en la ListaEx.
													/*! Esta funci�n procesa el movimiento del mouse en la ListaEx.
															\fn			BOOL ListaEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT wParam);
															\param[in]	hWndControl		: HWND del control que contiene la ListaEx.
															\param[in]	RectaControl	: Recta con el espacio de la ListaEx.
															\param[in]	cX				: Coordenada X del mouse relativa al control.
															\param[in]	cX				: Coordenada Y del mouse relativa al control.
															\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
															\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
															\remarks    Esta funci�n debe ser enlazada con el Evento_Mouse_Movimiento del control que vaya a contener la ListaEx.
															\sa			ListaEx_Mouse_BotonPresionado(), ListaEx_Mouse_BotonSoltado()
													*/
		 BOOL									    ListaEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param);

													//! Funci�n que procesa los botones presionados del mouse en la ListaEx.
													/*! Esta funci�n procesa los botones presionados del mouse en la ListaEx.
															\fn			BOOL ListaEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
															\param[in]	hWndControl		: HWND del control que contiene la ListaEx.
															\param[in]	RectaControl	: Recta con el espacio de la ListaEx.
															\param[in]	Boton			: Boton del mouse presionado.
															\param[in]	cX				: Coordenada X del mouse relativa al control.
															\param[in]	cX				: Coordenada Y del mouse relativa al control.
															\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
															\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
															\remarks    Esta funci�n debe ser enlazada con el Evento_Mouse_BotonPresionado del control que vaya a contener la ListaEx.
															\sa			ListaEx_Mouse_Movimiento(), ListaEx_Mouse_BotonSoltado()
													*/
		 BOOL									    ListaEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT wParam);

													//! Funci�n que procesa los botones soltados del mouse en la ListaEx.
													/*! Esta funci�n procesa los botones soltados del mouse en la ListaEx.
															\fn			BOOL ListaEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
															\param[in]	hWndControl		: HWND del control que contiene la ListaEx.
															\param[in]	RectaControl	: Recta con el espacio de la ListaEx.
															\param[in]	Boton			: Boton del mouse presionado.
															\param[in]	cX				: Coordenada X del mouse relativa al control.
															\param[in]	cX				: Coordenada Y del mouse relativa al control.
															\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
															\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
															\remarks    Esta funci�n debe ser enlazada con el Evento_Mouse_BotonSoltado del control que vaya a contener la ListaEx.
															\sa			ListaEx_Mouse_Movimiento(), ListaEx_Mouse_BotonPresionado()
													*/
		 BOOL									    ListaEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT wParam);

													//! Funci�n que procesa la rueda del raton dentro de la ListaEx.
													/*!	Esta funci�n es la encargada de procesar la rueda del raton dentro de la ListaEx.
															\fn			virtual LRESULT ListaEx_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey);
															\param[in]	Delta	: Valor de desplazamiento del mouse.
															\param[in]	cX		: Coordenada X.
															\param[in]	cY		: Coordenada Y.
															\param[in]	VirtKey	: Tecla virtual presionada.
															\return		Devuelve TRUE.
															\remarks    Esta funci�n debe ser enlazada con el Evento_Mouse_Rueda del control que vaya a contener la ListaEx.
													*/
		 BOOL									    ListaEx_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey);

													//! Funci�n para habilitar / deshabilitar los tooltips.
													/*! Esta funci�n habilita / deshabilita los tooltips.
															\fn			void ListaEx_MostrarToolTip(HWND hWndControl, const bool nMostrar);
															\param[in]	hWndControl : HWND del control que contiene la ListaEx.
															\param[in]	nMostrar : True para mostrar los tooltips cuando sea necesario, false para no mostrar nunca los tooltips.
															\return		No devuelve nada.
													*/
//		 void										ListaEx_MostrarToolTip(HWND hWndControl, const bool nMostrar);

													//! Clase que se ocupa de los tooltips.
//		 DWL::ControlesEx::DWLToolTipEx				ListaEx_ToolTip;

		 DWLListaEx_Estilos                         ListaEx_Estilos;
													//! Clase que contiene los colores para la lista.
//		 DWLListaEx_Colores							ListaEx_Colores;

													//! Clase que contiene las fuentes para la lista.
//		 DWL::SO::DWLEstilos_Fuente			ListaEx_Fuentes;
		protected : //////////////////////////////////

													//! Funci�n virtual que recibe cuando se hace un dobleclick en el control.
													/*! Esta funci�n virtual es llamada cuando la ListaEx recibe un doble click del mouse.
															\fn			virtual void ListaEx_Evento_Mouse_DobleClick(const UINT Boton, const int cX, const int cY);
															\param[in]	Boton	: Boton del mouse presionado.
															\param[in]	cX		: Coordenada X del mouse.
															\param[in]	cY		: Coordenada Y del mouse.
															\return		No devuelve nada.
													*/
		 virtual void								ListaEx_Evento_Mouse_DobleClick(const UINT Boton, const int cX, const int cY) { };

													//! Funci�n para pintar un item de la lista en modo DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL.
													/*! Esta funcion se usa para pintar un item de la lista en modo DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL.
															\fn			void ListaEx_PintarItem_Filas_y_Columnas_Vertical(HDC hDC, RECT *EspacioControl, DWLListaEx_Item *pItem);
															\param[in]	hDC				: HDC donde se pintara la ListaEx.
															\param[in]	EspacioControl	: Espacio de todo el control de la ListaEx.
															\param[in]	pItem			: Puntero a la clase DWLListaEx_Item que se va a pintar.
															\return		No devuelve nada.
															\remarks	Funci�n de uso interno para ListaEx_Pintar().
													*/
		 void										ListaEx_PintarItem_Filas_y_Columnas_Vertical(HDC hDC, RECT *EspacioControl, DWLListaEx_Item *pItem);

													//! Funci�n para pintar un item de la lista en modo DWL_LISTAEX_FILAS_HORIZONTAL.
													/*! Esta funcion se usa para pintar un item de la lista en modo DWL_LISTAEX_FILAS_HORIZONTAL.
															\fn			void ListaEx_PintarItem_Filas_Horizontal(HDC hDC, RECT *EspacioControl, DWLListaEx_Item *pItem, const int PosX, const int PosY);
															\param[in]	hDC				: HDC donde se pintara la ListaEx.
															\param[in]	EspacioControl	: Espacio de todo el control de la ListaEx.
															\param[in]	pItem			: Puntero a la clase DWLListaEx_Item que se va a pintar.
															\param[in]	PosX			: Posicion X del item.
															\param[in]	PosY			: Posicion Y del item.
															\return		No devuelve nada.
															\remarks	Funci�n de uso interno para ListaEx_Pintar().
													*/
		 void										ListaEx_PintarItem_Filas_Horizontal(HDC hDC, RECT *EspacioControl, DWLListaEx_Item *pItem, const int PosX, const int PosY);

													//! Columnas de la lista
		 std::vector<DWLListaEx_Columna *>         _ListaEx_Columnas;

													//! Items de la lista
		 std::vector<DWLListaEx_Item *>		       _ListaEx_Items;

													//! Valor para saber si la lista esta presionada
		 bool						               _ListaEx_Presionado;

													//! Item presionado en la lista
		 DWLListaEx_Item			              *_ListaEx_ItemPresionado;

													//! Posicion del item del Ultimo click en la lista
		 int								       _ListaEx_PosUltimoClick;

													//! Posicion del item del Ultimo click en la lista
		 int								       _ListaEx_UltimoBoton;

													//! SubItem presionado en la lista
		 int							           _ListaEx_SubItemPresionado;

													//! Item resaltado de la lista
		 DWLListaEx_Item		         		  *_ListaEx_ItemResaltado;

													//! Ultimo item resaltado
		 DWLListaEx_Item                          *_ListaEx_UItemResaltado;

													//! SubItem resaltado de la lista
		 int                                       _ListaEx_SubItemResaltado;

													//! Item marcado de la lista
		 DWLListaEx_Item                          *_ListaEx_ItemMarcado;

													//! Item en el que se presiono por ultima vez la tecla Shift
		 DWLListaEx_Item				          *_ListaEx_ItemShifteado;

													//! Array para el teclado
		 bool								       _ListaEx_Teclado[256];

													//! DC para el fondo
		 HDC						               _ListaEx_FondoDC;

													//! Bitmap para el fondo
		 HBITMAP								   _ListaEx_Bmp;

													//! Bitmap viejo del FondoDC
		 HBITMAP							       _ListaEx_Viejo;

													//! Fuente vieja del FondoDC
		 HFONT						               _ListaEx_VFuente;

													//! Ultimo item presionado
		 DWORD							           _ListaEx_UltimoClick;

													//! Valor para determinar si hay que pintar con AlphaBlend o no
//		 bool								       _ListaEx_DesactivarBlend;

													//! Valor que determina si se han de pintar iconos
//		 bool							           _ListaEx_PintarIconos;

													//! Altura de cada linea
		 int								       _ListaEx_AltoLinea;

													//! Valor que decide si se pinta el borde.
//		 bool									   _ListaEx_PintarBorde;

													//! Valor que decide si se tiene el foco del raton.
		 bool									   _ListaEx_FocoRaton;
		 ///////////////////////////////////////////// -Miembros usados para mostrar tooltips

													//! Valor para mostrar el tooltip o no
//		 bool									   _ListaEx_TT_Mostrar;

													//! Tiempo en milisegundos que tarda en salir el tooltip
//		 DWORD									   _ListaEx_TT_TiempoMS;

													//! Ultimo item resaltado al inicio de la cuenta atras de tiempo
		 DWLListaEx_Item						  *_ListaEx_TT_UltimoItem;
		 ///////////////////////////////////////////// Editbox para la edicion del item

													//! WindowProcedure que usara el Editbox en la Funci�n ListaEx_EmpezarLabelEdit().
													/*! WindowProcedure que usara el Editbox en la Funci�n ListaEx_EmpezarLabelEdit().
															\fn			static LRESULT CALLBACK _ListaEx_GestorMensajesEdit(HWND dhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
															\param[in]	dhWnd	: HWND del EditBox.
															\param[in]	uMsg	: Mensaje.
															\param[in]	wParam	: Parametro1.
															\param[in]	lParam	: Parametro2.
															\return		Devuelve un valor acorde al mensaje especificado.
															\remarks	Funcion de uso interno para ListaEx_EmpezarLabelEdit().
													*/
		 static LRESULT CALLBACK				   _ListaEx_GestorMensajesEdit(HWND dhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

													//! WindowProcedure Original del EditBox
		 WNDPROC								   _ListaEx_GestorMensajesOriginalEdit;

													//! Brocha del fondo del EditBox
		 HBRUSH									   _ListaEx_BrochaFondoEdit;

													//! Item en Edicion
		 DWLListaEx_Item                   	      *_ListaEx_eItem;

													//! SubItem en Edicion
		 int									   _ListaEx_eSubItem;

													//! Valor para saber si la lista esta en estado de edicion.
		 bool							           _ListaEx_Editando;

													//! Handle del EditBox.
		 HWND								       _ListaEx_hWndEdit;

													//! Multiseleccion de items.
//		 bool									   _ListaEx_MultiSeleccion;

													//! Parametro que decide si se van a mostrar los encabezados de las columnas.
//		 bool									   _ListaEx_MostrarEncabezadosColumnas;

													//! Ancho maximo para el item (solo valido en modo DWL_LISTAEX_FILAS_HORIZONTAL).
//		 int			  						   _ListaEx_AnchoMaximoItem;

													//! Ultima posicion X.
		 int									   _ListaEx_UltimoIntX;

													//! Ultima posicion Y.
		 int									   _ListaEx_UltimoIntY;

													//! Modo de visionado (DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL, o DWL_LISTAEX_FILAS_HORIZONTAL)
//		 int								 	   _ListaEx_ModoVisionado;

                                                    //! ID para la ListaEx
		 UINT                                      _ListaEx_ID;

		 private : /////////////////////////////////// Miembros privados

                                                    //! Constructor copia des-habilitado
                                                    DWLListaEx_Nucleo(const DWLListaEx_Nucleo &) :  _ListaEx_Columnas(), _ListaEx_Items(), _ListaEx_Presionado(false),
                                                                                                    _ListaEx_ItemPresionado(NULL), _ListaEx_PosUltimoClick(-1), _ListaEx_UltimoBoton(-1),
                                                                                                    _ListaEx_ItemResaltado(NULL), _ListaEx_UItemResaltado(NULL), _ListaEx_SubItemResaltado(-1), _ListaEx_ItemMarcado(NULL),
                                                                                                    /*_ListaEx_Teclado(),*/ _ListaEx_SubItemPresionado(-1), _ListaEx_FondoDC(NULL), _ListaEx_Bmp(NULL), _ListaEx_Viejo(NULL),
                                                                                                    _ListaEx_ItemShifteado(NULL), _ListaEx_VFuente(NULL), _ListaEx_UltimoClick(0), 
                                                                                                    _ListaEx_AltoLinea(17), _ListaEx_FocoRaton(false), _ListaEx_TT_UltimoItem(NULL), _ListaEx_GestorMensajesOriginalEdit(NULL), _ListaEx_BrochaFondoEdit(NULL), _ListaEx_eItem(NULL),
                                                                                                    _ListaEx_eSubItem(-1), _ListaEx_Editando(false), _ListaEx_hWndEdit(NULL), 
                                                                                                    _ListaEx_UltimoIntX(-1), _ListaEx_UltimoIntY(-1), _ListaEx_ID(0) { };
                                                    //! Operador = des-habilitado
		 inline DWLListaEx_Nucleo                  &operator=(const DWLListaEx_Nucleo &) { return *this; };
		};											//
		////////////////////////////////////////////// Fin DWLBarraScrollEx_Nucleo

    };
};

#endif
