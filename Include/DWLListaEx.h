//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DWLListaEx.h																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Descripción :																																//
//					Este control simula un Listview de windows, con algunas innovaciones, ademas de ser totalmente configurable de apariencia.	//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Este archivo contiene varias clases descritas a continuacion :																				//
// - DWLListaEx_Colores				:	Clase que enlaza los colores a la configuracion del skin por defecto									//
//										Puedes modificar cualquier color de esta clase, solo deberas repintar el arbol al terminar.				//
//																																				//
// - DWLListaEx_ColoresItem			:	Clase que enlaza los colores del Item a la configuracion skin por defecto.								//
//																																				//
// - DWLListaEx_ColoresColumna		:	Clase que enlaza los colores de la columna a la configuracion skin por defecto.							//
//																																				//
// - DWLListaEx_ParametrosClick		:	Clase utilizada internamente para pasar los datos de un click a la ventana padre.						//
//																																				//
// - DWLListaEx_TerminarLabelEdit	:	Clase utilizada internamente para pasar los datos de una edicion a la ventana padre.					//
//																																				//
// - DWLListaEx_Item				:	Clase que contiene los datos de un item (Puede ser heredada).											//
//																																				//
// - DWLListaEx_DatosSubItem		:	Clase que contiene los datos de un subitem.																//
//																																				//
// - DWLListaEx_Columna				:	Clase que contiene los datos de una columna (Puede ser heredada).										//
//																																				//
// - DWLListaEx_Nucleo				:	Clase que contiene las Funciónes basicas para pintar y controlar los eventos de la lista.				//
//										Esta clase se ha creado de forma que puede compartir un control con otra clase, aunque es poco probable	//
//										que se requiera compartir un arbol con otro control, es muy interesante la posibilidad de poder pintar	//
//										el control en cualquier hDC.																			//
//																																				//
// - DWLListaEx						:	Clase que hereda de DWLListaEx_Nucleo y lo enlaza a un control para el solo.							//
//										Esta clase es la que deberiamos usar para crear una lista estandar sin complicaciones.					//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Archivo creado por devildrey33 el dia 06/12/2004	para http://www.devildrey33.es																//
// Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :		//
//  http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																		//
//  http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)																//
//  http://www.softcatala.cat/wiki/GPL3		 (Catalá, traduccion no oficial)																	//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Version 0.95																																	//
// Ultima modificación : 12/11/2009																												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file DWLListaEx.h
	\brief Archivo que contiene las definiciones de las clases de la ListaEx

	\todo Revisar implementacion del teclado.
*/ 
#ifndef DWL_LISTAEX_H
#define DWL_LISTAEX_H


#include "DWLControlEx.h"
#include ".\DWLListaEx\DWLListaEx_Nucleo.h"



//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

		//! Clase que une DWLControlEx con DWLListaEx_Nucleo, para formar un control ListaEx
        class DWLListaEx : public DWL::ControlesEx::Base::DWLControlEx, public DWLListaEx_Nucleo {
		public : ///////////////////////// Metodos publicos

										//! Constructor.
										/*!	Constructor por defecto.
												\fn		DWLListaEx(void);
												\return	No devuelve nada.
										*/
										DWLListaEx(void);

										//! Destructor.
										/*!	Destructor.
												\fn		~DWLListaEx(void);
												\return	No devuelve nada.
										*/
									   ~DWLListaEx(void);

                                        //! Función que retorna la ID de la ListaEx.
                                        /*!	Esta funcion devuelve la ID de la ListaEx.
                                                \fn			inline UINT ID(void);
                                                \return		Devuelve la ID de la ListaEx.
                                        */
         inline UINT                    ID(void) { return _ListaEx_ID; };

										//! Función que retorna si esta ventana tiene el raton encima.
										/*!	Esta funcion devuelve si esta ventana tiene el raton encima.
												\fn			virtual bool Foco(void);
												\return		Devuelve true si el raton esta encima del control, false en caso contrario.
										*/
		 virtual bool				    Foco(void);

										//! Función que repinta todo la ListaEx.
										/*!	Esta función repinta todo la ListaEx incluyendo barras de scroll y botones extra.
												\fn			void Repintar(const bool Forzar = false);
												\param[in]	Forzar : True para forzar el repintado, false para que la funcion decida si repintar.
												\return		No devuelve nada.
												\remarks	Cuando Forzar es false, esta función mira si ha cambiado algun estado interno,
															y de ser asi repinta el control, en caso contrario no hace nada.
										*/
		 void                           Repintar(const bool Forzar = false);

										//! Función que crea la ListaEx.
										/*!	Esta funcion crea la ListaEx.
												\fn			HWND CrearListaEx(const long Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const bool nPintarBorde = true, const int nTipoVisionado = DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL);
												\param[in]	Estilos			: Estilos para la ListaEx (WS_CHILD | WS_VISIBLE).
												\param[in]	hWndParent		: HWND del control que sera el padre de la ListaEx.
												\param[in]	cX				: Posicion X.
												\param[in]	cY				: Posicion Y.
												\param[in]	cAncho			: Ancho de la ListaEx.
												\param[in]	cAlto			: Alto de la ListaEx.
												\param[in]	cID				: ID de la ListaEx.
												\param[in]	cPintarBorde	: Parametro que indica si se tiene que pintar el borde de la ListaEx.
												\param[in]	nTipoVisionado	: Tipo de visionado que puede ser : DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL o DWL_LISTAEX_FILAS_HORIZONTAL.
												\return		Devuelve el HWND de la ListaEx. En caso de error devolvera NULL.
										*/
		 HWND                           CrearListaEx(const long Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const bool nPintarBorde = true, const int nTipoVisionado = DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL);

										//! Función que conecta la ListaEx de un dialogo.
										/*!	Esta funcion conecta la ListaEx de un dialogo.
												\fn			HWND ConectarListaEx(HWND hWndParent, const int cID, const bool nPintarBorde = true, const int nTipoVisionado = DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL);
												\param[in]	hWndParent		: HWND del control que sera el padre de la ListaEx.
												\param[in]	cID				: ID de la ListaEx.
												\param[in]	cPintarBorde	: Parametro que indica si se tiene que pintar el borde de la ListaEx.
												\param[in]	nTipoVisionado	: Tipo de visionado que puede ser : DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL o DWL_LISTAEX_FILAS_HORIZONTAL.
												\return		Devuelve el HWND de la ListaEx. En caso de error devolvera NULL.
                                                \remarks    Esta función solo debe usarse con controles que se creen durante la creación del dialogo, si esta clase no pertenece a un dialogo, o se va a crear dinamicamente, no debes usar esta función.
										*/
		 HWND                           ConectarListaEx(HWND hWndParent, const int cID, const bool nPintarBorde = true, const int nTipoVisionado = DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL);

										//! Función que retorna si la ListaEx esta activada.
										/*!	Esta funcion devuelve si la ListaEx esta activada.
												\fn			BOOL Activado(void);
												\return		Devuelve TRUE si la ListaEx esta activada, FALSE en caso contrario.
										*/
		 BOOL                           Activado(void);

										//! Función para activar / desactivar la ListaEx.
										/*!	Esta funcion activa / desactiva la ListaEx.
												\fn			inline virtual void Activado(const bool nActivar);
												\param[in]	nActivar	: Parametro en el que especificaremos si queremos activar o desactivar el ArbolEx.
												\return		No devuelve nada.
										*/
		 void		                    Activado(const bool Activar);

										//! Función virtual que actualiza todos los datos de la ListaEx.
										/*! Esta función virtual actualiza todos los datos de la ListaEx.
												\fn			virtual void ActualizarTodo(const bool nRepintar = false);
                                                \param[in]  nRepintar     : true para repintar el control, false para mantenerlo sin repintar.
												\return		No devuelve nada.
												\remarks	Esta función se usa para actualizar todos los estilos y items de la ListaEx. Si necesitas actualizar el tamaño de los textos por haber cambiado la fuente, deberas usar tambien ListaEx_ActualizarTamTexto().
										*/
		 virtual void                   ActualizarTodo(const bool nRepintar = false) {
											RECT RC;
											GetClientRect(_hWnd, &RC);
											ListaEx_ActualizarTodo(_hWnd, &RC);
                                            if (nRepintar == true) Repintar(true);
										};


										//! Función para mover la ListaEx a la posicion y el tamaño especificados.
										/*!	Esta función mueve la ListaEx a la posicion y tamaño especificados.
												\fn			void Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = true);
												\param[in]	cX			: Nueva posicion X para la ListaEx.
												\param[in]	cY			: Nueva posicion Y para la ListaEx.
												\param[in]	cAncho		: Nuevo ancho para la ListaEx.
												\param[in]	cAlto		: Nueva altura para la ListaEx.
												\param[in]	cRepintar	: True para repintar el control, false para dejarlo sin repintar.
												\return		No devuelve nada.
										*/
		 void							Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool Repintar = false);

										//! Función para decidir si mostramos los encabezados de las columnas.
										/*! Esta función determina si se van a mostrar los encabezados de las columnas.
												\fn			inline void MostrarEncabezadosColumnas(const bool nMostrarEncabezados);
												\param[in]	nMostrarEncabezados : True para mostrar los encabezados de las columnas, false para dejarlos ocultos.
												\return		No devuelve nada.
										*/
		 inline void					MostrarEncabezadosColumnas(const bool MostrarEncabezados) {
											ListaEx_Estilos.MostrarEncabezadosColumnas = MostrarEncabezados;
										};

										//! Función para decidir si mostramos los iconos.
										/*! Esta función determina si se van a mostrar los iconos de los items.
												\fn			inline void MostrarIconos(const bool nPintarIconos);
												\param[in]	nPintarIconos : True para pintar los iconos, false para no pintar iconos.
												\return		No devuelve nada.
										*/
		 inline void                    MostrarIconos(const bool nPintarIconos) {
											ListaEx_Estilos.PintarIconos = nPintarIconos;
										};

										//! Función que retorna si se van a pintar iconos de los items.
										/*! Esta función develve si se van a pintar los iconos de los items.
												\fn			inline bool MostrarIconos(void) const;
												\return		Devuelve true si se van a pintar iconos, false en caso contrario.
										*/
		 inline bool                    MostrarIconos(void) const {
											return ListaEx_Estilos.PintarIconos;
										};

										//! Función que retorna el item que esta debajo de las coordenadas especificadas.
										/*! Esta función retorna el item o la parte del nodo que esta debajo de las coordenadas especificadas.
												\fn			DWLListaEx_Item *HitTest(const int cX, const int cY, const DWL_Enum_ListaEx_HitTest Tipo = DWL_Enum_ListaEx_HitTest_Texto_Icono);
												\param[in]	cX		: Coordenada X.
												\param[in]	cY		: Coordenada Y.
												\param[in]	nTipo	: Tipo de busqueda.
												\return		No devuelve nada.
												\remarks	Hay varios tipos de busqueda : [HitTest_Texto] Solo el texto, [HitTest_Icono] Solo el icono, [HitTest_Texto_Icono] Texto y icono.
										*/
		 inline DWLListaEx_Item		   *HitTest(const int cX, const int cY, const DWL_Enum_ListaEx_HitTest Tipo = DWL_Enum_ListaEx_HitTest_Texto_Icono) {
											return ListaEx_HitTest(_hWnd, cX, cY, Tipo);
										};

										//! Función que agrega una columna a la ListaEx.
										/*! Esta función agrega una columna a la ListaEx.
												\fn			void AgregarColumna(const int nAncho = DWL_LISTAEX_ANCHO_AUTOMATICO, const int nAlineacion = DWL_LISTAEX_TEXTO_IZQUIERDA, const TCHAR *NombreColumna = NULL);
												\param[in]	nAncho			: Ancho en pixeles para la columna (puede ser DWL_LISTAEX_ANCHO_AUTOMATICO).
												\param[in]	nAlineacion		: Alineacion del texto de la columna (puede ser DWL_LISTAEX_TEXTO_IZQUIERDA, DWL_LISTAEX_TEXTO_CENTRADO, DWL_LISTAEX_TEXTO_DERECHA).
												\param[in]	NombreColumna	: Nombre para la columna (NULL por defecto).
												\return		No devuelve nada.
												\remarks	Si vas a usar la lista en modo DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL debes crear como minimo una columna, en caso de usar el modo DWL_LISTAEX_FILAS_HORIZONTAL las columnas no se tienen en cuenta.
										*/
		 inline void                    AgregarColumna(const int nAncho = DWL_LISTAEX_ANCHO_AUTOMATICO, const int nAlineacion = DT_LEFT, const TCHAR *NombreColumna = NULL) {
											ListaEx_AgregarColumna(nAncho, nAlineacion, NombreColumna);
										};

										//! Función para eliminar la columna especificada.
										/*! Esta función elimina la columna especificada.
												\fn			void EliminarColumna(const int Pos);
												\param[in]	nPos		: Posicion de la columna a eliminar.
												\return		No devuelve nada.
												\remarks	Cuando eliminamos una columna, NO SE ELIMINAN los datos de los items referentes a esa posicion de la columna.
										*/
		 inline void                    EliminarColumna(const int Pos) {
											ListaEx_EliminarColumna(_hWnd, Pos);
											Repintar(true);
										};

										//! Función para eliminar todas las columnas.
										/*! Esta funcion elimina todas las columnas de la ListaEx.
												\fn			void EliminarTodasLasColumnas(const bool nRepintar = false);
												\param[in]	nRepintar : Parametro en el que especificamos si se debe repintar la ListaEx.
												\return		No devuelve nada.
												\remarks	Cuando eliminamos todas las columnas, NO SE ELIMINAN los datos de los items para las posiciones de las columnas.
										*/
		 inline void					EliminarTodasLasColumnas(const bool nRepintar = false) {
											ListaEx_EliminarTodasLasColumnas(_hWnd);
											Repintar(nRepintar);
										};

										//! Función que destruye esta ListaEx.
										/*!	Esta funcion destruye la ListaEx.
												\fn			BOOL Destruir(void);
												\return		Devuelve TRUE si la operacion se completo, FALSE en caso contrario.
										*/
		 BOOL                           Destruir(void);

										//! Función para agregar un item.
										/*! Esta función se usa para agregar un item a la ListaEx.
												\fn			DWLListaEx_Item *AgregarItem(DWLListaEx_Item *nItem = NULL, const int nIcono = NULL, const int Posicion = DWL_LISTAEX_FIN, const TCHAR *Txt = NULL, ...);
												\param[in]	nItem		: Item heredado, en caso de ser un DWLListaEx_Item puedes especificar NULL.
												\param[in]	nIcono		: Icono para el item.
												\param[in]	nPosicion	: Posicion en la que se agregara el item. Puede ser (DWL_LISTAEX_FIN, DWL_LISTAEX_INICIO, y DWL_LISTAEX_ORDENADO)
												\param[in]	nTexto		: Texto para el item.
												\param[in]	...			: Parametros opcionales en los que debemos especificar los textos para los subitems.
												\return		Devuelve un puntero a la clase DWLListaEx_Item que acabamos de crear / añadir.
												\remarks	Se deben añadir tantos textos en los parametros opcionales como columnas -1 tenga la lista.
										*/
		 inline DWLListaEx_Item        *AgregarItem(DWLListaEx_Item *nItem = NULL, const int nIcono = NULL, const int Posicion = DWL_LISTAEX_FIN, const TCHAR *Txt = NULL, ...) {
											va_list Marker;
											va_start(Marker, Txt);
											DWLListaEx_Item *ItemNuevo = ListaEx_AgregarItem(nItem, nIcono, Posicion, Txt, Marker);
											va_end(Marker);
											return ItemNuevo;
										};

										//! Función que enlaza todos los items entre ellos y calcula los valores del scroll.
										/*!	Esta función es la encargada de enlazar todos los items entre ellos y calcular las posiciones para los scrolls.
												\fn			void FinAgregarItems(void);
												\return		No devuelve nada.
												\remarks	Esta función debe ser llamada cuando terminemos de agregar el ultimo item a la lista.
										*/
/*		 inline void                    FinAgregarItems(void) {
											ListaEx_FinAgregarItems(_hWnd);
										};*/

										//! Función para eliminar un item y sus subitems.
										/*! Esta funcion elimina el item especificado.
												\fn			void EliminarItem(const unsigned int nPos, const bool nRepintar = false);
												\param[in]	nPos		: Posicion del item que se va a eliminar.
												\param[in]	nRepintar	: Parametro en el que especificamos si la ListaEx debe ser repintada.
												\return		No devuelve nada.
												\remarks	Cuando eliminamos un item se borra toda su memoria, incluso si ese item es heredado lo eliminamos por completo. Asegurate de tener un destructor que elimine los datos de tus items heredados.
										*/
		 inline void                    EliminarItem(const unsigned int Pos, const bool nRepintar = false) {
											ListaEx_EliminarItem(_hWnd, Pos, nRepintar);
										};

										//! Función para eliminar un item y sus subitems.
										/*! Esta funcion elimina el item especificado.
												\fn			void EliminarItem(DWLListaEx_Item *nItem, const bool nRepintar = false);
												\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
												\param[in]	nItem		: Clase DWLListaEx_Item que se va a eliminar.
												\param[in]	nRepintar	: Parametro en el que especificamos si la ListaEx debe ser repintada.
												\return		No devuelve nada.
												\remarks	Cuando eliminamos un item se borra toda su memoria, incluso si ese item es heredado lo eliminamos por completo. Asegurate de tener un destructor que elimine los datos de tus items heredados.
										*/
		 inline void                    EliminarItem(DWLListaEx_Item *eItem, const bool nRepintar = false) {
											ListaEx_EliminarItem(_hWnd, eItem, nRepintar);
										};

										//! Función para eliminar los items seleccionados.
										/*! Esta función elimina todos los items seleccionados de la ListaEx.
												\fn			UINT EliminarItemsSeleccionados(const bool nRepintar = true);
												\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
												\param[in]	nRepintar	: Parametro en el que especificamos si la ListaEx debe ser repintada.
												\return		Devuelve el total de items eliminados.
												\remarks	Cuando eliminamos un item se borra toda su memoria, incluso si ese item es heredado lo eliminamos por completo. Asegurate de tener un destructor que elimine los datos de tus items heredados.
										*/
		 inline UINT                    EliminarItemsSeleccionados(const bool nRepintar = true) {
											return ListaEx_EliminarItemsSeleccionados(_hWnd, nRepintar);
										};

										//! Función para eliminar todos los items.
										/*! Esta función elimina todos los items de la ListaEx.
												\fn			void EliminarTodosLosItems(const bool nRepintar = true);
												\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
												\param[in]	nRepintar	: Parametro en el que especificamos si la ListaEx debe ser repintada.
												\return		No devuelve nada.
												\remarks	Cuando eliminamos un item se borra toda su memoria, incluso si ese item es heredado lo eliminamos por completo. Asegurate de tener un destructor que elimine los datos de tus items heredados.
										*/
		 inline void                    EliminarTodosLosItems(const bool nRepintar = true) {
											ListaEx_EliminarTodosLosItems(_hWnd, nRepintar);
										};

										//! Función que retorna el item especificado.
										/*! Esta función devuelve el item especificado.
												\fn			inline DWLListaEx_Item *Item(const unsigned int nPos);
												\param[in]	nPos	: Posicion del item que queremos obtener.
												\return		Devuelve un puntero a la clase DWLListaEx_Item especificada en el parametro nPos.
										*/
		 inline DWLListaEx_Item        *Item(const unsigned int Pos) {
											return _ListaEx_Items[Pos];
										};

										//! Función que retorna la columna especificada.
										/*! Esta función devuelve la columna especificada.
												\fn			inline DWLListaEx_Columna *Columna(const unsigned int nPos);
												\param[in]	nPos	: Posicion de la columna que queremos obtener.
												\return		Devuelve un puntero a la clase DWLListaEx_Columna especificada en el parametro nPos.
										*/
		 inline DWLListaEx_Columna     *Columna(const unsigned int Pos) {
											return _ListaEx_Columnas[Pos];
										};

										//! Función que retorna la altura de un item en pixeles.
										/*! Esta función devuelve la altura de un item en pixeles.
												\fn			inline UINT AltoLinea(void) const;
												\return		Devuelve la altura de un item en pixeles.
										*/
		 inline UINT                    AltoLinea(void) const {
											return _ListaEx_AltoLinea;
										};

										//! Función que asigna la altura de un item en pixeles.
										/*! Esta función asigna la altura de un item en pixeles.
												\fn			void AltoLinea(const UINT nAlto);
												\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
												\param[in]	nAlto		: Nueva altura en pixeles para los items.
												\return		No devuelve nada.
										*/
		 inline void                    AltoLinea(const UINT nAlto) {
											ListaEx_AltoLinea(_hWnd, nAlto);
										};

										//! Función que elimina el estado de selección en todos los items.
										/*! Esta función elimina el estado de selección en todos los items.
												\fn			void DesSeleccionarTodo(const bool bRepintar = true);
												\param[in]	bRepintar	: Valor en el que especificamos si debemos repintar la ListaEx.
												\return		No devuelve nada.
										*/
		 inline void                    DesSeleccionarTodo(const bool bRepintar = true) {
											ListaEx_DesSeleccionarTodo(bRepintar);
										};

										//! Función que muestra en pantalla el item especificado.
										/*! Esta función muestra en pantalla el item especificado.
												\fn			void MostrarItem(const int nPos);
												\param[in]	nPos	: Posición del item que queremos mostrar.
												\return		No devuelve nada.
										*/
		 inline void                    MostrarItem(const int nPos) {
											ListaEx_MostrarItem(_ListaEx_Items[nPos]);
										};

										//! Función que muestra en pantalla el item especificado.
										/*! Esta función muestra en pantalla el item especificado.
												\fn			void MostrarItem(DWLListaEx_Item *vItem);
												\param[in]	vItem	: Clase DWLListaEx_Item que queremos mostrar.
												\return		No devuelve nada.
										*/
		 inline void                    MostrarItem(DWLListaEx_Item *vItem) {
											ListaEx_MostrarItem(vItem);
										};

										//! Función que retorna el total de items que contiene la ListaEx.
										/*! Esta función devuelve el total de items que contiene la ListaEx.
												\fn			inline const int unsigned TotalItems(void);
												\return		Devuelve el total de items de la ListaEx.
										*/
		 inline UINT            		TotalItems(void) const {
											return static_cast<int>(_ListaEx_Items.size());
										}

										//! Función que retorna el total de items seleccionados que contiene la ListaEx.
										/*! Esta función devuelve el total de items seleccionados que contiene la ListaEx.
												\fn			inline UINT TotalItemsSeleccionados(void) const;
												\return		Devuelve el total de items seleccionados de la ListaEx.
										*/
		 inline UINT            		TotalItemsSeleccionados(void) const {
											return ListaEx_TotalItemsSeleccionados();
										};

										//! Función que retorna el total de columnas que contiene la ListaEx.
										/*! Esta función devuelve el total de columnas que contiene la ListaEx.
												\fn			inline UINT TotalColumnas(void) const;
												\return		Devuelve el total de columnas de la ListaEx.
										*/
		 inline UINT                    TotalColumnas (void) const {
											return _ListaEx_Columnas.size();
										};

										//! Función para empezar la edicion de un item.
										/*! Esta función inicia la edicion de un item.
												\fn			HWND EmpezarLabelEdit(DWLListaEx_Item *eItem, const unsigned int eSubItem = 0, const bool Numerico);
												\param[in]	eItem		: Clase DWLListaEx_Item que se va a editar.
												\param[in]	eSubItem	: Posicion del subitem que se va a editar.
												\param[in]	Numerico	: True para que la edicion solo acepte digitos, false para que acepte todos los caracteres.
												\return		Devuelve el HWND del EditBox creado para editar el nodo.
												\sa			TerminarLabelEdit(), CancelarLabelEdit()
										*/
		 inline HWND                    EmpezarLabelEdit(DWLListaEx_Item *eItem, const unsigned int eSubItem = 0, const bool Numerico = false) {
											return ListaEx_EmpezarLabelEdit(_hWnd, eItem, eSubItem, Numerico);
										};

										//! Función para terminar la edicion de un item guardando los datos.
										/*! Esta función termina la edicion de un item guardando los datos.
												\fn			HWND TerminarLabelEdit(void);
												\return		No devuelve nada.
												\sa			EmpezarLabelEdit(), CancelarLabelEdit()
										*/
		 inline void			        TerminarLabelEdit(void) {
											ListaEx_TerminarLabelEdit(_hWnd);
										};

										//! Función para cancelar la edicion de un item sin guardar los datos.
										/*! Esta función cancela la edicion de un item sin guardar los datos.
												\fn			HWND CancelarLabelEdit(void);
												\return		No devuelve nada.
												\sa			EmpezarLabelEdit(), TerminarLabelEdit()
										*/
		 inline void	                CancelarLabelEdit(void) {
											ListaEx_CancelarLabelEdit(_hWnd);
										};

										//! Función que asigna el item resaltado.
										/*! Esta funcion asigna el item resaltado.
												\fn			inline void ItemResaltado(DWLListaEx_Item *nSel);
												\param[in]	nSel	: Puntero a la clase DWLListaEx_Item que queremos resaltar.
												\return		No devuelve nada.
												\sa			ItemMarcado(), SubItemResaltado(), Item()
										*/
		 inline void                    ItemResaltado(DWLListaEx_Item *nSel) {
											_ListaEx_ItemResaltado = nSel;
											Repintar(true);
										};

										//! Función que retorna el item resaltado.
										/*! Esta funcion devuelve el item resaltado.
												\fn			inline DWLListaEx_Item *ItemResaltado(void);
												\return		Devuelve el item resaltado, o NULL si no hay item resaltado.
												\sa			ItemMarcado(), SubItemResaltado(), Item()
										*/
		 inline DWLListaEx_Item        *ItemResaltado(void) {
											return _ListaEx_ItemResaltado;
										};

										//! Función que retorna el item marcado.
										/*! Esta funcion devuelve el item marcado.
												\fn			inline DWLListaEx_Item *ItemMarcado(void);
												\return		Devuelve el item resaltado, o NULL si no hay item resaltado.
												\sa			ItemResaltado(), SubItemResaltado(), Item()
										*/
		 inline DWLListaEx_Item         *ItemMarcado(void) {
											return _ListaEx_ItemMarcado;
										};

										//! Función que asigna el item marcado.
										/*! Esta funcion asigna el item marcado.
												\fn			inline void ItemMarcado(DWLListaEx_Item *nSel);
												\param[in]	nSel	: Puntero a la clase DWLListaEx_Item que queremos remarcar.
												\return		No devuelve nada.
												\sa			ListaEx_ItemResaltado(), ListaEx_SubItemResaltado(), ListaEx_Item()
										*/
		 inline void                    ItemMarcado(DWLListaEx_Item *nSel) {
											_ListaEx_ItemMarcado = nSel;
											Repintar(true);
										};

										//! Función que retorna la posicion del subitem resaltado dentro del item.
										/*! Esta funcion devuelve la posicion del subitem resaltado dentro del item.
												\fn			inline int SubItemResaltado(void) const;
												\return		Devuelve la posicion del subitem resaltado.
												\sa			ItemResaltado(), ItemMarcado(), Item()
										*/
		 inline int			        	SubItemResaltado(void) const {
											return _ListaEx_SubItemResaltado;
										};

										//! Función para desactivar / activar las transparencias en la ListaEx.
										/*! Esta función desactiva / activa las transparencias en la ListaEx.
												\fn			void DesactivarAlphaBlend(const bool nDesactivar);
												\param[in]	nDesactivar : True para desactivar transparencias, False para activarlas.
												\return		No devuelve nada.
												\remarks	Por defecto las transparecinas estan habilitadas.
										*/
		 inline void                    DesactivarAlphaBlend(const bool nDesactivar) {
											ListaEx_Estilos.Transparencias = !nDesactivar;
										};

										//! Función que retorna el hWnd del EditBox cuando se esta haciendo un LabelEdit.
										/*! Esta función retorna el HWND del EditBox cuando se esta haciendo un LabelEdit.
												\fn			inline HWND hWndEditBox(void);
												\return		Devuelve el HWND del EditBox que se esta usando para la edición.
												\sa			ListaEx_EmpezarLabelEdit()
										*/
		 inline HWND                    hWndEditBox(void) {
											 return _ListaEx_hWndEdit;
										};

										//! Función que retorna si este control tiene habilitada la multiselección.
										/*! Esta funcion devuelve si este control tiene habilitada la multiselección.
												\fn			inline bool MultiSeleccion(void) const;
												\return		Devuelve true si la multiseleccion esta habilitada, false en caso contrario.
										*/
		 inline bool				    MultiSeleccion(void) const {
											return ListaEx_Estilos.MultiSeleccion;
										};

										//! Función que habilita / deshabilita la multiselección.
										/*! Esta funcion habilita / deshabilita la multiselección.
												\fn			inline void MultiSeleccion(const bool nMultiSeleccion);
												\param[in]	nMultiSeleccion : True para habilitar la multiseleccion, false para deshabilitarla.
												\return		No devuelve nada.
										*/
		 inline void					MultiSeleccion(const bool nMultiSeleccion) {
											ListaEx_Estilos.MultiSeleccion = nMultiSeleccion;
										};

										//! Función para habilitar / deshabilitar los tooltips.
										/*! Esta función habilita / deshabilita los tooltips.
												\fn			void MostrarToolTip(const bool nMostrar);
												\param[in]	nMostrar : True para mostrar los tooltips cuando sea necesario, false para no mostrar nunca los tooltips.
												\return		No devuelve nada.
										*/
/*		 inline void					MostrarToolTip(const bool nMostrar) {
											ListaEx_MostrarToolTip(_hWnd, nMostrar);
										};*/

										//! Función que pinta toda la ListaEx cuado se recibe un mensaje WM_PAINT.
										/*!	Esta función pinta la ListaEx cuando se recibe un mensaje WM_PAINT.
												\fn			LRESULT Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);
												\param[in]	hDC	: hDC donde se pintara toda la ListaEx.
												\param[in]	PS	: Estructura con informacion sobre el pintado.
   												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT                Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);

										//! Función predefinida del mensaje WM_KEYUP (Virtual)
										/*!	Esta función es la encargada de procesar los mensajes WM_KEYUP.
												\fn			virtual LRESULT Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Params);
												\param[in]	Caracter   : Tecla virtual presionada.
												\param[in]	Repeticion : Repeticion de la tecla.
												\param[in]	Param	   : Teclas extendidas presionadas.
   												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT                Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Param);

										//! Función predefinida del mensaje WM_KEYDOWN (Virtual)
										/*!	Esta función es la encargada de procesar los mensajes WM_KEYDOWN.
												\fn			virtual LRESULT Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Param);
												\param[in]	Caracter   : Tecla virtual presionada.
												\param[in]	Repeticion : Repeticion de la tecla.
												\param[in]	Param	   : Teclas extendidas presionadas.
   												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT                Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Param);

										//! Función predefinida del mensaje WM_MOUSEMOVE.
										/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEMOVE.
												\fn			virtual LRESULT Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);
												\param[in]	cX		: Coordenada X del mouse.
												\param[in]	cY		: Coordenada Y del mouse.
												\param[in]	Param	: Teclas extendidas presionadas.
   												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT                Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);

										//! Función predefinida del mensaje WM_*BUTTONUP (Virtual)
										/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONUP.
												\fn			virtual LRESULT Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
												\param[in]	Boton	: Boton presionado.
												\param[in]	cX		: Coordenada X del mouse.
												\param[in]	cY		: Coordenada Y del mouse.
												\param[in]	wParam	: Teclas extendidas presionadas.
   												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT                Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);

										//! Función predefinida del mensaje WM_*BUTTONDOWN (Virtual)
										/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONDOWN.
												\fn			virtual LRESULT Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param)
												\param[in]	Boton	: Boton presionado.
												\param[in]	cX		: Coordenada X del mouse.
												\param[in]	cY		: Coordenada Y del mouse.
												\param[in]  Param	: Teclas extendidas presionadas.
   												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT                Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param);

										//! Función predefinida del mensaje WM_MOUSEWHEEL.
										/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEWHEEL.
												\fn			virtual LRESULT Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey);
												\param[in]	Delta	: Valor de desplazamiento del mouse.
												\param[in]	cX		: Coordenada X.
												\param[in]	cY		: Coordenada Y.
												\param[in]	VirtKey	: Tecla virtual presionada.
   												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT				Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey);

										//! Función que recibe cuando el mouse se va del control
										/*!	Esta función es la encargada de procesar los mensajes WN_MOUSELEAVE.
												\fn			virtual LRESULT Evento_Mouse_Saliendo(void);
												\return		No devuelve nada.
   												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT				Evento_Mouse_Saliendo(void);

										//! Función que procesa el mensaje WM_SETFOCUS
										/*! Esta funcion es la encargada de procesar el mensaje WM_SETFOCUS
												\fn			virtual LRESULT Evento_Foco_Obtenido(HWND FocoAnterior);
												\param[in]	FocoAnterior	: HWND de la ventana que tenia el foco antes que esta.
												\return		No devuelve nada.
   												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT				Evento_Foco_Obtenido(HWND FocoAnterior);

										//! Función que procesa el mensaje WM_KILLFOCUS
										/*! Esta funcion es la encargada de procesar el mensaje WM_KILLFOCUS
												\fn			virtual LRESULT Evento_Foco_Perdido(HWND NuevoFoco);
												\param[in]	NuevoFoco	: HWND de la ventana que recibira el foco despues de esta.
												\return		No devuelve nada.
   												\return		Si re-emplazas esta funcion debes retornar 0.
										*/
		 virtual LRESULT				Evento_Foco_Perdido(HWND NuevoFoco);

										//! Función que enlaza el mensaje WM_TIMER con la ListaEx.
										/*! Esta función enlaza el mensaje WM_TIMER con la ListaEx.
												\fn			virtual LRESULT Evento_Temporizador(const UINTs cID);
												\param[in]	cID : ID del temporizador.
												\return		No devuelve nada.
										*/
		 virtual LRESULT				Evento_Temporizador(const UINT cID);
		protected : //////////////////////

										//! Esqueleto para los mensajes del ArbolEx.
										/*! Esta función es el esqueleto para los mensajes del ArbolEx.
												\fn			LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
												\param[in]	uMsg	: Mensaje.
												\param[in]	wParam	: Parametro1.
												\param[in]	lParam	: Parametro2.
												\return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
												\remarks	Esta función es el esqueleto del ArbolEx por donde pasaran todos sus mensajes.
										*/
		 virtual LRESULT CALLBACK		GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
		////////////////////////////////// Final editbox
										//
										// Clases Amigas
		 friend class					DWLListaEx_Item;
		 friend class					DWLListaEx_Columna;
		 friend class					DWLListaEx_Fuentes;
		 friend class					DWLListaEx_DatosSubItem;
		}; /////////////////////////////// Final DWLListaEx





	}
}

#endif // DWL_LISTAEX_H

// Version 0.6
// Primera version de este control con varias Funciónabilidades a remarcar :
// - Para empezar este control es una simulacion de como me gustaria que fuese un ListView en modo report.
//
// - Dispone de control completo de colores y fuentes para items / subitems de forma que requiera el minimo de memoria posible
// - Se pueden editar los textos de los items / subitems con la Función EmpezarLabelEdit
// - Se puede reemplazar la Función Evento_PintarBackGround para pintar un fondo en el control
// - Existe la posibilidad de desactivar los Blendings para aquellos ordenadores que no lo soporten bien
//    Si los desactivas no se podran pintar fondos personalizados.
// - Posibilidad de heredar tanto el scrollbar como la lista y pintarlos a gusto
//    Estas dos clases tienen varias Funciónes On...Paint vituales para facilitar la tarea (NOTA la Función Evento_Pintar no es virtual en estas clases)
// - Bugs:
//    - Al reasignar la altura del item no se modificaba bien el buffer de tamaño con lo que seguia pintado 17 pixeles de alto.
//    - Al pintar un texto que excediera el espacio reservado para la columna seguia pintando en la siguiente columna
//		Esto producia que los textos de las columnas se mezclaran.
//
//------------------------------------------------------------------------------------------------------------------------------------------------
//
// Version 0.61
// - El maximo de caracteres para el editbox del label edit ha sido ampliado a 1024. antes solo soportaba los caracteres que cabian en pantalla.
// Version 0.62
// - Haora al hacer click con el boton izquierdo este mira si hay mas de un item seleiconado, si los hay no seleciona el item que tiene debajo,
//	 en caso contrario se selecionara el item que hay debajo del mouse
// Version 0.7
// -Se han reemplazado varios nombres de Funciónes medio en ingles medio en castellano para que pasen a ser totalmente en castellano.
// -Se han eliminado todas las macros que empezaban por On.
//  Haora existen nuevas macros que empiezan por ENLACE_
// -Se han eliminado las notificaciones estandard que retornaba este control
//  Haora este control retorna sus propios mensajes :
//   -Mensaje								-Macro													   -Prototipos para las Funciónes que reciben el evento
//    DWL_LISTAEX_CLICK_DERECHO				 ENLACE_ListaEx_Evento_Mouse_Click							(const UINT Boton, const int cX, const int cY, const int ID)
//    DWL_LISTAEX_CLICK_IZQUIERDO			 ENLACE_ListaEx_Evento_Mouse_Click							(const UINT Boton, const int cX, const int cY, const int ID)
//    DWL_LISTAEX_CLICK_MEDIO				 ENLACE_ListaEx_Evento_Mouse_Click							(const UINT Boton, const int cX, const int cY, const int ID)
//    DWL_LISTAEX_DOBLECLICK_DERECHO		 ENLACE_ListaEx_Evento_Mouse_DobleClick						(const UINT Boton, const int cX, const int cY, const int ID)
//    DWL_LISTAEX_DOBLECLICK_IZQUIERDO		 ENLACE_ListaEx_Evento_Mouse_DobleClick						(const UINT Boton, const int cX, const int cY, const int ID)
//    DWL_LISTAEX_DOBLECLICK_MEDIO			 ENLACE_ListaEx_Evento_Mouse_DobleClick						(const UINT Boton, const int cX, const int cY, const int ID)
//    DWL_LISTAEX_TECLADO_PRESIONADO		 ENLACE_ListaEx_Evento_Teclado_TeclaPresionada				(const int TeclaVirtual, const int ID)
//    DWL_LISTAEX_TECLADO_SOLTADO			 ENLACE_ListaEx_Evento_Teclado_TeclaSoltada					(const int TeclaVirtual, const int ID)
//    DWL_LISTAEX_TECLADO_INTRO				 ENLACE_ListaEx_Evento_Teclado_Intro						(const int ID)
//    DWL_LISTAEX_FOCO_OBTENIDO			     ENLACE_ListaEx_Evento_Foco_Obtenido						(const int ID)
//    DWL_LISTAEX_FOCO_PERDIDO				 ENLACE_ListaEx_Evento_Foco_Perdido							(const int ID)

// Version 0.72
// Se ha optimizado bastante el tema de añadir items a la lista, antes con 50000 me tardaba 31 segundos, haora me tarda 1.5 segundos :)
// Por ello haora se requiere usar la nueva Función CalcularLista una vez se sepa que se ha terminado de añadir una serie de items.
// Para optimizar mas en el aspecto de la velocidad se tendria que crear la memoria toda de golpe, y no item por item, aunque por el momento no lo creo necesario.

// Version 0.73
// Las macros haora apuntan a Funciónes ya creadas en ClaseVentana y ClaseDialogo que pertenecen a la clase Enlaces_ListaEx

// Version 0.80		[06/02/2006]
// Varios cambios con el scrollbar, haora viene con la clase BaseControlExScroll
// Se ha cambiado el sistema de acceso a los items, haora se usan punteros en ve de posiciones reales.

// Version 0.82		[10/04/2006]
// Se ha añadido la posibilidad de activar / desactivar la Multiseleccion, hasta haora estaba siempre activada.
// Se han eliminado las brochas precreadas de la clase ColoresDWLListaEx
// Se ha solucionado un memory leak al destruir este control (no se eliminaba la memoria de los items y columnas)

// Version 0.90		[27/03/2007]
// Haora la lista puede redimensionarse, y puede tener items pintados a medias.
// Se ha modificado la forma en que se recibia el label edit, actualmente se reciben los datos encapsulados dentro de una clase ListaEx_TerminarLabelEdit

// Version 0.91		[08/06/2007]
// El scroll que se usaba antes se ha eliminado (ClaseBarraScrolEx), y actualmente el mismo control tiene los scrolls incorporados tanto horizontales, como verticales!! (BaseControlExScroll)
// Ademas la clase BaseControlExScroll tiene Funciónes para realizar cambios en su tamaño, y para poder mostrar y ocultar los scrolls tanto manualmente como de forma automatica.
// Optimizaciones varias en los repintados

// Version 0.91b	[05/02/2009]
// Solucionados algunos fallos con el scroll que no se actualizaba correctamente al mover el scroll con la rueda y con el teclado

// Version 0.92     [26/02/2009]
// -Retocados eventos de click del mouse, se han simplificado, y son mas intuitivos de cara al usuario final.
// -Simplificados mensajes de click, y se ha añadido soporte para botones X
//  DWL_LISTAEX_CLICK_DERECHO, DWL_LISTAEX_CLICK_IZQUIERDO, DWL_LISTAEX_CLICK_MEDIO y DWL_LISTAEX_CLICK_X Se han remplazado por DWL_LISTAEX_CLICK.
// -Añadido soporte para tooltips
//  Para empezar se ha añadido la Función MostrarTooltip, la cual nos permite activar el uso de estos.
//  Despues tenemos el Evento_MostrarToolTip virtual, en el cual podemos personalizar el tooltip al maximo.
//  Y por ultimo el objeto ToolTip que consiste en una clase DWLToolTip, el cual es de uso interno.

// Version 0.93		[17/06/2009]
// -Solucionado problema con el repintado, este problema sucedia al arrastrar ventanas por encima, y hacia que no se repintara el control.

// Version 0.94		[04/10/2009]
// -Añadidas las siguientes Funciónes para mostrar encabezados de las columnas : MostrarEncabezadosColumnas(), Evento_ColumnaPresionada()
// -Actualmente el tema de las columnas esta en fase beta, mas adelante se implementaran formas automaticas de orden al clicar en ellas.
// -Ahora las columnas tambien disponen de un espacio para asignarles un nombre visible.
// -Se han añadido mas colores configurables, esta vez para los encabezados de las columnas.
// -Se ha añadido una nueva visualizacion, ahora la lista puede utilizarse en modo report(por defecto) o en modo lista horizontal.
//  Estos cambios se han pensado para hacer una lista tipo explorador, cosas basicas para hacer un futuro dialogo abrir / guardar extendido.
//  Falta por programar Funciónes de teclado relacionadas con el shift y el control en la nueva visualizacion.

// Version 0.94b	[23/10/2009]
// -Solucionado problema con la tecla Control que no acababa de Funciónar correctamente.

// Version 0.95
// -Añadida posibilidad de pintar un borde redondeado al control, NO UTILIZAR MAS el estilo WS_BORDER.
// -Se ha creado la clase DWLListaEx_Nucleo, que a partir de ahora sera la clase general para las operaciones de la lista.
//  Para crear un control unico con la lista aun disponemos de DWLListaEx.
// -Se ha actualizado la forma de editar los colores segun el nuevo standard de la DWL
//  Ahora es mucho mas facil cambiar un solo color, o todo el skin de la apariencia.
