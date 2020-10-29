/*! \file DWLListView.h
	\brief		Archivo que contiene funciones para la utilización de un listview en windows.


	\details	Clase diseñada para poder controlar un listview de windows.																				\n
				Esta clase en breve no formara parte del proyecto y por lo tanto no recibira actualizaciones.											\n
				Si quieres utilizar un control del estilo del edit box con la DWL se recomienda usar DWLListaEx.									\n
				Para la version 1.0 de la DWL esta clase probablemente desaparecera.																	\n
 
																																						\n
	\author		devildrey33
	\version	0.95
	\date		07/12/2005

	\remarks
				Archivo creado por devildrey33 el dia [16/03/2004] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n	
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n	
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n	

*/

#ifndef DWL_LISTVIEW_H
#define DWL_LISTVIEW_H

#include "DWLControl.h"
#include "DWLString.h"




//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Controles
	namespace Controles {
		//! Clase para controlar una columna del ListView de windows
		class DWLListView_Columna;

		//! Clase para controlar un ListView de windows
		class DWLListView;

		//! Clase para controlar un item del ListView de windows
		class DWLListView_Item {
		public : ///////////////// Miembros publicos
								//
								//! Constructor
								//  DWLListView_Item(void);
								DWLListView_Item(void);
								//
								//! Constructor asignador
								//  DWLListView_Item(DWL::Controles::DWLListView *LV);
								DWLListView_Item(DWL::Controles::DWLListView *LV);
								//
								//! Destructor 
								// ~DWLListView_Item(void);
							   ~DWLListView_Item(void) {
								};
								//
								//! Función para asignar el texto del item.
								//  void Texto(const int SubItem, const TCHAR *Txt);
		 void                   Texto(const int SubItem, const TCHAR *Txt);
								//
								//! Función para obtener el texto del item.	
								//  const TCHAR *Texto(const int SubItem);
		 const TCHAR           *Texto(const int SubItem);
								//
								//! Función para asignar el icono del item.
								//  void Icono(const int nIko);
		 void                   Icono(const int nIko);
								//
								//! Función para obtener el icono del item.
								//  const int Iko(void);
		 const int              Icono(void);
								//
								//! Función para asignar la funete del item/subitem
								//  HFONT Fuente(const unsigned int SubItem);
		 HFONT                  Fuente(const unsigned int SubItem);
								//
								//! Función para obtener la funete del item/subitem
								//  void Fuente(const unsigned int SubItem, HFONT nFuente);
		 void                   Fuente(const unsigned int SubItem, HFONT nFuente);
								//
								//! Función para asignar el color del texto del item.
								//  void ColorTexto(const int SubItem, COLORREF nColor);
		 void                   ColorTexto(const int SubItem, COLORREF nColor);
								//
								//! Función para obtener el color del texto del item.
								//  COLORREF ColorTexto(const int SubItem);
		 COLORREF               ColorTexto(const int SubItem);
								//
								//! Función para asignar el color del fondo del item.
								//  void ColorFondo(const int SubItem, COLORREF nColor);
		 void                   ColorFondo(const int SubItem, COLORREF nColor);
								//
								//! Función para obtener el color del fondo del item.
								//  COLORREF ColorFondo(const int SubItem);
		 COLORREF               ColorFondo(const int SubItem);
								//
								//! Función que Asigna si el Item esta selecionado
								//  void Seleccionado(const bool Sel);
		 void                   Seleccionado(const bool Sel);
								//
								//! Función que retorna si el Item esta selecionado
								//  const bool Seleccionado(void);
		 const bool             Seleccionado(void);
								//
								//! Función que muestra este item
								//  void HacerVisible(void);
		 void                   HacerVisible(void);
		protected : ////////////// Miembros privados
								//
								//! Función para asignar un Puntero de la clase DWLListView a esta clase
								//  void _AsignarNuevo(DWLListView *LV);
		 void                  _AsignarNuevo(DWLListView *LV);
								//
								//! Vector de clases LTFuente
		 std::vector<HFONT>    _Fuente;
								//
								//! Vector de Colores del texto
		 std::vector<COLORREF> _ColorTexto;
								//
								//! Vector de Colores del fondo
		 std::vector<COLORREF> _ColorFondo;
								//
								//! Puntero a la clase DWLListView padre de este Item
		 DWLListView		  *_LV;
								//
								//! Esta clase es amiga de la DWLListView
		 friend class			DWLListView;
		};						//
		////////////////////////// Final DWLListView_Item



		//! Clase para controlar una columna del ListView de windows
		class DWLListView_Columna {
		public : ///////////////////// Miembros publicos
									//
									//! Constructor
									//  DWLListView_Columna(void);
									DWLListView_Columna(void) { 
									};
									//
									//! Constructor asignador
									//  DWLListView_Columna(DWLListView *LV);
									DWLListView_Columna(DWLListView *LV);
									//
									//! Destructor
									// ~DWLListView_Columna(void);
								   ~DWLListView_Columna(void) { };
									//
									//! Función para asignar el texto de la columna
									//  void Texto(const TCHAR *Txt);
		 void						Texto(const TCHAR *Txt);
									//
									//! Función que retorna el texto de la columna
									//  const TCHAR *Texto(void);
		 const TCHAR			   *Texto(void);
									//
									//! Función para asignar el ancho de la columna
									//  void Ancho(const int nAncho);
		 void						Ancho(const int nAncho);
									//
									//! Función que retorna el ancho de la columna
									//  const int Ancho(void);
		 const int					Ancho(void);
		protected : ////////////////// Metodos privados
									//
									//! Clase DWLListView padre
		 DWLListView	          *_LV;
									//
									// Esta clase es amiga de la DWLListView
		 friend class				DWLListView;
		};							//
		////////////////////////////// Final DWLListView_Columna




		//! Clase para controlar un ListView de windows
        class DWLListView : public DWL::Controles::Base::DWLControl {
		public : ///////////////////////////// Miembros publicos
											//
											//! Constructor que inicia las clases del ListView en los common controls
											//  DWLListView(void);
											DWLListView(void);
											//
											//! Destructor
											// ~DWLListView(void);
										   ~DWLListView(void);
											//
											//! Función para crear el ListView
											//  void Crear(DWORD Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, DWORD EstilosExtendidos = NULL);
		 void								Crear(DWORD Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, DWORD EstilosExtendidos = NULL);
											//
											//! Función para asignar esta clase a un ListView creado anteriormente en el editor de recursos
											//  HWND Asignar(HWND hWndParent, const int cID);
		 HWND								Asignar(HWND hWndParent, const int cID);
											//
											//! Función para agregar un Item Debes poner tantos subitems como columnas tengas creadas menos una (la que debes crear para que se muestre el texto en report)
											//  void AgregarItem(const int Iko, const TCHAR *Txt, ...);
		 void								AgregarItem(const int Iko, const TCHAR *Txt, ...);
											//
											//! Función para agregar un Item Debes poner tantos subitems como columnas tengas creadas menos una (la que debes crear para que se muestre el texto en report)
											//  void AgregarItem(const int Pos, const int Iko, const TCHAR *Txt, ...);
		 void								AgregarItem(const int Pos, const int Iko, const TCHAR *Txt, ...);
											//
											//! Función para agregar un Item Debes poner tantos subitems como columnas tengas creadas menos una (la que debes crear para que se muestre el texto en report)
											//  void AgregarItem(DWLListView_Item *Itm, const int Iko, const TCHAR *Txt, ...);
		 void								AgregarItem(DWLListView_Item *Itm, const int Iko, const TCHAR *Txt, ...);
											//
											//! Función para agregar un Item Debes poner tantos subitems como columnas tengas creadas menos una (la que debes crear para que se muestre el texto en report)
											//  void AgregarItem(DWLListView_Item *Itm, const int Pos, const int Iko, const TCHAR *Txt, ...);
		 void								AgregarItem(DWLListView_Item *Itm, const int Pos, const int Iko, const TCHAR *Txt, ...);
											//
											//! Función para borrar un Item
											//  void BorrarItem(const int nItem);
		 void								BorrarItem(const int nItem);
											//
											//! Función para borrar todos los items
											//  void BorrarTodosLosItems(void);
		 void								BorrarTodosLosItems(void);
											//
											//! Función para agregar una columna
											//  void AgregarColumna(const TCHAR *Txt, const int cAncho);
		 void								AgregarColumna(const TCHAR *Txt, const int cAncho);
											//
											//! Función para borrar una columna
											//  void BorrarColumna(const int Col);
		 void								BorrarColumna(const int Col);
											//
											//! Función para cambiar la selección actual del listview
											//  inline void Seleccion(const int Pos);
		 inline void						Seleccion(const int Pos) {
												ListView_SetItemState(_hWnd, Pos, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED); 
											};
											//
											//! Función para obtener la selección actual del listview
											//  const int Seleccion(void);
		 const int							Seleccion(void);
											//
											//! Función para obtener el total de items selecionados
											//  inline const int Seleccionados(void);
		 inline const int					Seleccionados(void) {
												return ListView_GetSelectedCount(_hWnd); 
											};
											//
											//! Función que deseleciona todos los items
											//  void DesSeleccionarTodo(void);
		 void								DesSeleccionarTodo(void);
											//
											//! Función para asignar un imagelist a este listview
											//  inline void AsignarImageList(HIMAGELIST ImgList, const int Tam);
		 inline void						AsignarImageList(HIMAGELIST ImgList, const int Tam) {
												ListView_SetImageList(_hWnd, ImgList, Tam); 
											};
											//
											//! Función que retorna un puntero a una clase DItem
											//  DWLListView_Item *Item(const int Num);
		 DWLListView_Item                   *Item(const int Num);
											//
											//! Función que retorna la columna especificada
											//  DWLListView_Columna *Columna(const int Num);
		 DWLListView_Columna               *Columna(const int Num);
											//
											//! Función que retorna el numero de items que caben en el trozo visible del ListView
											//  inline const int ItemsPorPagina(void);
		 inline const int					ItemsPorPagina(void) {
												return ListView_GetCountPerPage(_hWnd); 
											};
											//
											//! Función que retorna el numero total de items
											//  const int TotalItems(void);
		 const int							TotalItems(void);
											//
											//! Función que retorna el numero total de columnas
											//  const int TotalColumnas(void);
		 const int							TotalColumnas(void);
											//
											//! Función que empieza la edicion de un item/subitem
											//  HWND EmpezarLabelEdit(const unsigned int eItem, const unsigned int eSubItem, const bool Numerico = false);
		 HWND								EmpezarLabelEdit(const unsigned int eItem, const unsigned int eSubItem, const bool Numerico = false);
											//
											//! Función que termina la edicion de un item/subitem
											//  void TerminarLabelEdit(void);
		 void								TerminarLabelEdit(void);
											//
											//! Función que cancela la edicion de un item/subitem
											//  void CancelarLabelEdit(void);
		 void								CancelarLabelEdit(void);
											//
											//! Función para mostrar un item
											//  inline void MostrarItem(const int Pos);
		 inline void						MostrarItem(const int Pos) {
												ListView_EnsureVisible(_hWnd, Pos, false); 
											};
											//
											//! Función que retorna el item que hay debajo del mouse
											//  const int ItemHitTest(void);
		 const int							ItemHitTest(void);
											//
											//! Función que retorna el item que hay debajo de las coordenadas
											//  const int ItemHitTest(const int cX, const int cY);
		 const int							ItemHitTest(const int cX, const int cY);
											//
											//! Función que retorna el subitem que hay debajo del mouse
											//  const int SubItemHitTest(void);
		 const int							SubItemHitTest(void);
											//
											//! Función que retorna el subitem que hay debajo de las coordenadas
											//  const int SubItemHitTest(const int cX, const int cY);
		 const int							SubItemHitTest(const int cX, const int cY);
											//
											//! Función que retorna la fuente 
											//  inline HFONT Fuente(void);
		 inline HFONT						Fuente(void) {
												return _Fuente; 
											};
											//
											//! Función para asignar la fuente
											//  inline void Fuente(HFONT nFuente);
		 inline void						Fuente(HFONT nFuente) {
												_Fuente = nFuente; 
											};
											//
											//! Función para cambiar el color del fondo
											//  inline void ColorFondo(COLORREF nCol);
		 inline void						ColorFondo(COLORREF nCol) {
												ListView_SetBkColor(_hWnd, nCol); 
											};
											//
											//! Función que retorna el color del fondo
											//  inline COLORREF ColorFondo(void);
		 inline COLORREF					ColorFondo(void) {
												return ListView_GetBkColor(_hWnd); 
											};
											//
											//! Función para asignar el color del texto
											//  inline void ColorTexto(COLORREF nCol);
		 inline void					    ColorTexto(COLORREF nCol) { 
												ListView_SetTextColor(_hWnd, nCol);
											};
											//
											//! Función que retorna el color del texto	
											//  inline COLORREF ColorTexto(void);
		 inline COLORREF					ColorTexto(void) {
												return ListView_GetTextColor(_hWnd); 
											};
											//
											//! Notificacion de pintado (Antes de pintar el item)
											//  virtual LRESULT Evento_Pintar_InicioItem(LPNMLVCUSTOMDRAW lplvcd);
		 virtual LRESULT					Evento_Pintar_InicioItem(LPNMLVCUSTOMDRAW lplvcd);
											//
											//! Notificacion de pintado (Antes de pintar el item selecionado)
											//  virtual LRESULT Evento_Pintar_InicioItemSeleccionado(LPNMLVCUSTOMDRAW lplvcd);
		 virtual LRESULT					Evento_Pintar_InicioItemSeleccionado(LPNMLVCUSTOMDRAW lplvcd);
											//
											//! Notificacion de pintado (Despues de pintar el item)
											//  virtual LRESULT Evento_Pintar_FinItem(LPNMLVCUSTOMDRAW lplvcd);
		 virtual LRESULT					Evento_Pintar_FinItem(LPNMLVCUSTOMDRAW lplvcd);
											//
											//! Notificacion de pintado (Despues de pintar el item selecionado)
											//  virtual LRESULT Evento_Pintar_FinItemSeleccionado(LPNMLVCUSTOMDRAW lplvcd);
		 virtual LRESULT					Evento_Pintar_FinItemSeleccionado(LPNMLVCUSTOMDRAW lplvcd);
		protected ://///////////////////////// Declaraciones protegidas (Solo podran usarse en la clase heredada no desde fuera)
											//
											//! Nuevo WindowProcedure para el ListView
											//  virtual LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
		 virtual LRESULT CALLBACK			GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
											//
											//! Función que se encarga de especificar los colores y la Fuente del ListView para cada item
											//  LRESULT _CustomDraw(LPARAM Datos);
		 LRESULT                           _CustomDraw(LPARAM Datos);
											//
											//! Handle del WindowProcedure original del ListView
		 WNDPROC                           _GestorMensajes;
											//
											//! Clase que controla la fuente del ListView
		 HFONT                             _Fuente;
											//
											//! Vector de punteros a DWLListView_Item
		 std::vector<DWLListView_Item *>    _Items;
											//
											//! Vector de punteros a DWLListView_Columna
		 std::vector<DWLListView_Columna *> _Cols;
											//
											//! Color del fondo de la selecion
		 COLORREF                          _ColorSeleccion;
											//
											//! Color del Texto de la selecion
		 COLORREF                          _ColorSeleccionTexto;
											//
											//! Item en Edicion 
		 int                               _eItem;
											//
											//! SubItem en Edicion 
		 int                               _eSubItem;
											//
											//! Valor para determinar si se esta editando un item/subitem
		 bool                              _Editando;
											//
											//! Handle del EditBox
		 HWND                              _hWndEdit;
											//
											//! WindowProcedure que usara el Editbox en la Función EmpezarLabelEdit
											//  static LRESULT CALLBACK _GestorMensajesEdit(HWND dhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		 static LRESULT CALLBACK           _GestorMensajesEdit(HWND dhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
											//
											//! WindowProcedure Original del EditBox
		 WNDPROC                           _GestorMensajesOriginalEdit;
											//
											//! Brocha del fondo del EditBox
		 HBRUSH                            _BrochaFondoEdit;
											//
											//! String temporal
		 DWL::DWLString			    	   _TmpStr;
											//
		 friend class DWLListView_Item;	    // Esta clase es amiga de la clase DWLListView_Item
		 friend class DWLListView_Columna;	// Esta clase es amiga de la clase DWLListView_Columna
		};									//
		////////////////////////////////////// Final class DWLListView




		//! Clase contenedora de los datos que se pueden necesitar al terminar la edicion de un item / subitem
		class DWLListView_TerminarLabelEdit {
		public : ///////////////////// Miembros publicos
									//
									//! Constructor por defecto (Nunca deberia usarse)
									//  DWLListView_TerminarLabelEdit(void);
									DWLListView_TerminarLabelEdit(void) {
										Cancelar = false;
									};
									//
									//! Constructor asignador de datos
									//  DWLListView_TerminarLabelEdit(DWLListView_Item *nItem, const int nNumItem, const int nNumSubItem, const TCHAR *nNuevoTexto);
									DWLListView_TerminarLabelEdit(DWLListView_Item *nItem, const int nNumItem, const int nNumSubItem, const TCHAR *nNuevoTexto) {
										Cancelar = false;
										_NumItem = nNumItem;
										_NumSubItem = nNumSubItem;
										_Item = nItem;
										NuevoTexto = nNuevoTexto;
									};
									//
									//! Destructor
									// ~DWLListView_TerminarLabelEdit(void);
								   ~DWLListView_TerminarLabelEdit(void) {
									};
									//
									//! Función que retorna el numero del item dentro de la lista.
									//  inline const int NumItem(void);
		 inline const int			NumItem(void) {
										return _NumItem;
									};
									//
									//! Función que retorna el numero del sub item dentro de la lista.
									//  inline const int NumSubItem(void);
		 inline const int			NumSubItem(void) {
										return _NumSubItem;
									};
									//
									//! Función que retorna un puntero al DItem correspondiente a este item en edicion.
									//  inline DWLListView_Item *Item(void);
		 inline DWLListView_Item	   *Item(void) {
										return _Item;
									};
									//
									//! Estado de cancelacion para esta edicion
		 bool						Cancelar;
									//
									//! Nuevo texto que se va a aplicar
		 DWL::DWLString				NuevoTexto;
		private : //////////////////// Miembros privados
									//
									//! Clase DWLListView_Item que contiene el item / subitem que se esta editando
		 DWLListView_Item	      *_Item;
									//
									//! Numero del item actualmente en edicion
		 int			           _NumItem;
									//
									//! Numero del sub item actualmente en edicion
		 int			           _NumSubItem;
		};							//
		////////////////////////////// Fin class DWLListView_TerminarLabelEdit;

	}

}
#endif // DWL_LISTVIEW_H


// Ver 0.9a
// -Fallo extraño semicorregido al añadir un item bajo threads se ha solucionando agregando primero los datos al vector y luego mostrando el listview (Gracias a cofruben)
// -Se han modificado varias Funciónes para que sean en linea (inline ...)
// -El codigo ha sido modificado para poder editarlo mejor

// Version 0.95 [22/05/2005]
// -Se han eliminado todas las macros que empezaban por On.
//  Haora existen nuevas macros que empiezan por ENLACE_
// -Se han eliminado las notificaciones estandard que retornaba este control
//  Haora este control retorna sus propios mensajes :
//   -Mensaje								-Macro
//    DWL_LISTVIEW_CLICK_DERECHO			 ENLACE_ListView_Evento_Mouse_Click	
//    DWL_LISTVIEW_CLICK_IZQUIERDO			 ENLACE_ListView_Evento_Mouse_Click	
//    DWL_LISTVIEW_CLICK_MEDIO				 ENLACE_ListView_Evento_Mouse_Click
//    DWL_LISTVIEW_DOBLECLICK_DERECHO		 ENLACE_ListView_Evento_Mouse_DobleClick
//    DWL_LISTVIEW_DOBLECLICK_IZQUIERDO		 ENLACE_ListView_Evento_Mouse_DobleClick	
//    DWL_LISTVIEW_DOBLECLICK_MEDIO			 ENLACE_ListView_Evento_Mouse_DobleClick
//    DWL_LISTVIEW_TECLADO_PRESIONADO		 ENLACE_ListView_Evento_Teclado_TeclaPresionada
//    DWL_LISTVIEW_TECLADO_SOLTADO			 ENLACE_ListView_Evento_Teclado_TeclaSoltada
//    DWL_LISTVIEW_TECLADO_INTRO			 ENLACE_ListView_Evento_Teclado_Intro
//    DWL_LISTVIEW_FOCO_OBTENIDO			 ENLACE_ListView_Evento_Foco_Obtenido
//    DWL_LISTVIEW_FOCO_PERDIDO				 ENLACE_ListView_Evento_Foco_Perdido


// Version 0.95b [07/12/2005]
// Se ha agregado una nueva clase para asi hacer mas limpio el LabelEdit, esta clase contiene varios datos a tener en cuenta y permite validar
// la edicion o no segun convenga.
// Para esto se ha tenido que modificar la macro ENLACE_ListView_Evento_LabelEdit_Fin ademas del mensaje DWL_LISTVIEW_LABELEDIT_FIN para que haora
// retornen una clase del tipo DWLListView_TerminarLabelEdit.



// Problemas :
//  -Si se utiliza el flag para hacer LabelEdits automaticos no se pasa por la Función EmpezarLabelEdit y por lo tanto no llegan los mensajes
//   necesarios para controlar el editbox y para saber cuando se termina la edicion...
