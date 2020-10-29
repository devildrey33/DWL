/*! \file DWLTreeView.h
	\brief		Archivo que contiene funciones para la utilización de un treeview en windows.


	\details	Clase diseñada para poder controlar un treeview de windows.																		\n
				Esta clase en breve no formara parte del proyecto y por lo tanto no recibira actualizaciones.											\n
				Si quieres utilizar un control del estilo del edit box con la DWL se recomienda usar DWLArbolEx.										\n
				Para la version 1.0 de la DWL esta clase probablemente desaparecera.																	\n

																																						\n
	\author		devildrey33
	\version	0.95
	\date		24/07/2005

	\remarks
				Archivo creado por devildrey33 el dia [29/03/2004] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n	
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n	
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n	
 
*/
#ifndef DWL_TREEVIEW_H
#define DWL_TREEVIEW_H

#include "DWLControl.h"
#include "DWLString.h"




namespace DWL {
	namespace Controles {
		class DWLTreeView;
		class DWLTreeView_Nodo;

		//! Clase que controla un nodo del treeview
		class DWLTreeView_Nodo {
		public: ////////////////// Miembros publicos de esta clase
								//
								//! Constructor por defecto
								// DWLTreeView_Nodo(void);
								DWLTreeView_Nodo(void) { 
									_TV = NULL;
									_Nodo = NULL;
									_ColorFondo = 0;
									_ColorTexto = 0;
									_Fuente = NULL; 
								};
								//
								//! Constructor DWLTreeView y Nodo
								// DWLTreeView_Nodo(DWLTreeView *TV, HTREEITEM nNodo);
								DWLTreeView_Nodo(DWLTreeView *TV, HTREEITEM nNodo);
								//
  			  					//! Constructor DWLTreeView, Nodo y Colores
								// DWLTreeView_Nodo(DWLTreeView *TV, HTREEITEM nNodo, COLORREF nColorFondo, COLORREF nColorTexto);
								DWLTreeView_Nodo(DWLTreeView *TV, HTREEITEM nNodo, COLORREF nColorFondo, COLORREF nColorTexto);
								//
								//! Destructor vacio
								// ~DWLTreeView_Nodo(void);
							   ~DWLTreeView_Nodo(void) {
								};
								//
								//! Función para asignar el texto del nodo.
								// void Texto(const TCHAR *Txt);
		 void                   Texto(const TCHAR *Txt);
								//
								//! Función para obtener el texto del nodo.
								// const TCHAR *Texto(void);
		 const TCHAR           *Texto(void);
								//
								//! Función para asignar el icono del nodo.
								// void Icono(const int nIcono);
		 void                   Icono(const int nIcono);
								//
								//! Función para obtener el icono del nodo.
								// const int Icono(void);
		 const int              Icono(void);
								//
								//! Función para asignar el icono selecionado del nodo.
								// void IconoSeleccionado(const int nIcono);
		 void                   IconoSeleccionado(const int nIcono);
								//
								//! Función para obtener el icono selecionado del nodo.
								// const int IkoSeleccionado(void);
		 const int              IconoSeleccionado(void);
								//
								//! Función para asignar la fuente
								// inline HFONT Fuente(void);
		 inline HFONT           Fuente(void) { 
									return _Fuente; 
								};
								//
								//! Función para obtener la fuente
								// inline void Fuente(HFONT nFuente);
		 inline void            Fuente(HFONT nFuente) {
									_Fuente = nFuente; 
								};
								//
								//! Función para asignar el color del texto del nodo.
								// inline void ColorTexto(COLORREF nColor);
		 inline void            ColorTexto(COLORREF nColor) {
									_ColorTexto = nColor; 
								};
								//
								//! Función para obtener el color del texto del nodo.
								// inline COLORREF ColorTexto(void);
		 inline COLORREF        ColorTexto(void) {
									return _ColorTexto; 
								};
								//
								//! Función para asignar el color del fondo del nodo.
								// inline  void ColorFondo(COLORREF nColor);
		 inline void            ColorFondo(COLORREF nColor) {
									_ColorFondo = nColor; 
								};
								//
								//! Función para obtener el color del fondo del nodo.
								// inline  COLORREF ColorFondo(void);
		 inline COLORREF        ColorFondo(void) { 
									return _ColorFondo; 
								};
								//
								//! Función para obtener la ID unica del nodo.
								// inline  HTREEITEM hTreeItem(void);
		 inline HTREEITEM       hTreeItem(void) {
									return _Nodo; 
								};
								//
								//! Función para obtener un puntero de la Clase DWLTreeView_Nodo que apunte al nodo Hijo.
								// DWLTreeView_Nodo *NodoHijo(void);
		 DWLTreeView_Nodo      *NodoHijo(void);
								//
								//! Función para obtener un puntero de la Clase DWLTreeView_Nodo que apunte al nodo Padre.
								// DWLTreeView_Nodo *NodoPadre(void);
		 DWLTreeView_Nodo      *NodoPadre(void);
								//
								//! Función para obtener un puntero de la Clase DWLTreeView_Nodo que apunte al nodo Siguente.
								// DWLTreeView_Nodo *NodoSiguiente(void);
		 DWLTreeView_Nodo      *NodoSiguiente(void);
								//
								//! Función para obtener un puntero de la Clase DWLTreeView_Nodo que apunte al nodo Anterior.
								// DWLTreeView_Nodo *NodoAnterior(void);
		 DWLTreeView_Nodo      *NodoAnterior(void);
								//
								//! Función para obtener la ID unica del nodo Hijo.
								// HTREEITEM Hijo(void);
		 HTREEITEM              Hijo(void);
								//
								//! Función para obtener la ID unica del nodo Padre.
								// HTREEITEM Padre(void);
		 HTREEITEM              Padre(void);
								//
								//! Función para obtener la ID unica del nodo Siguiente.
								// HTREEITEM Siguiente(void);
		 HTREEITEM              Siguiente(void);
								//
								//! Función para obtener la ID unica del nodo Anterior.
								// HREEITEM Anterior(void);
		 HTREEITEM              Anterior(void);
								//
								//! Función para selecionar el Nodo en el TreeView.
								// void Seleccionar(void);
		 void                   Seleccionar(void);
								//
								//! Función para que se muestre este nodo en concreto
								// void HacerVisible(void);
		 void                   HacerVisible(void);
		protected: /////////////// Miembros protegidos de esta clase
								//
								//! Función para asignar los miembros basicos de esta clase (Esta Función es de uso interno para asignar clases derivadas)
								// void _AsignarBase(DWLTreeView *TV, HTREEITEM nNodo, COLORREF nColorFondo, COLORREF nColorTexto);
		 void                  _AsignarBase(DWLTreeView *TV, HTREEITEM nNodo, COLORREF nColorFondo, COLORREF nColorTexto);
								//
								//! Función para asignar los miembros basicos de esta clase (Esta Función es de uso interno para asignar clases derivadas)
								// void _AsignarBase(DWLTreeView *TV, HTREEITEM nNodo);
		 void                  _AsignarBase(DWLTreeView *TV, HTREEITEM nNodo);
								//
								//! ID unica de este nodo
		 HTREEITEM             _Nodo;
								//
								//! Color del fondo de este nodo
		 COLORREF              _ColorFondo;
								//
								//! Color del texto de este nodo
		 COLORREF              _ColorTexto;
								//
								//! Fuente de este nodo
		 HFONT                 _Fuente;
								//
								//! Puntero de la DWLTreeView de donde sale este nodo
		 DWLTreeView          *_TV;
		 friend class DWLTreeView; // Declaro la clase DWLTreeView amiga de esta clase
		};








		//! Clase que controla un TreeView de windows
        class DWLTreeView : public DWL::Controles::Base::DWLControl {
		public: ////////////////////////////// Miembros publicos de esta clase
											//
											//! Constructor.
											// DWLTreeView(void);
											DWLTreeView(void);
											//
											//! Destructor.
											// ~DWLTreeView(void);
										   ~DWLTreeView(void);
											//
											//! Función para crear el TreeView.
											// void Crear(DWORD Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, DWORD EstilosExtendidos = NULL);
		 void								Crear(DWORD Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, DWORD EstilosExtendidos = NULL);
											//
											//! Función para asignar esta clase a un TreeView creado anteriormente en el editor de recursos.
											// void Asignar(HWND hWndParent, const int cID);
		 void								Asignar(HWND hWndParent, const int cID);
											//
											//! Función para Agregar un Nodo partiendo de una clase derivada de DWLTreeView_Nodo.
											// HTREEITEM AgregarNodo(DWLTreeView_Nodo *Nodo, HTREEITEM Parent, const TCHAR *cTexto, const int cIko, HTREEITEM InsertarDespuesDe = NULL);
		 HTREEITEM							AgregarNodo(DWLTreeView_Nodo *nNodo, HTREEITEM Parent, const TCHAR *cTexto, const int cIko, HTREEITEM InsertarDespuesDe = NULL);
											//
											//! Función para Agregar un Nodo partiendo de una clase derivada de DWLTreeView_Nodo con sus colores.
											// HTREEITEM AgregarNodo(DWLTreeView_Nodo *Nodo, HTREEITEM Parent, const TCHAR *cTexto, const int cIko, COLORREF nColorTexto, COLORREF nColorFondo, HTREEITEM InsertarDespuesDe = NULL);
		 HTREEITEM							AgregarNodo(DWLTreeView_Nodo *nNodo, HTREEITEM Parent, const TCHAR *cTexto, const int cIko, COLORREF nColorTexto, COLORREF nColorFondo, HTREEITEM InsertarDespuesDe = NULL);
											//
											//! Función para Agregar un Nodo normal.
											// HTREEITEM AgregarNodo(HTREEITEM Parent, const TCHAR *cTexto, const int cIko, HTREEITEM InsertarDespuesDe = NULL);
		 HTREEITEM							AgregarNodo(HTREEITEM Parent, const TCHAR *cTexto, const int cIko, HTREEITEM InsertarDespuesDe = NULL);
											//
											//! Función para Agregar un Nodo normal especificando sus colores.
											// HTREEITEM AgregarNodo(HTREEITEM Parent, const TCHAR *cTexto, const int cIko, COLORREF nColorTexto, COLORREF nColorFondo, HTREEITEM InsertarDespuesDe = NULL);
		 HTREEITEM							AgregarNodo(HTREEITEM Parent, const TCHAR *cTexto, const int cIko, COLORREF nColorTexto, COLORREF nColorFondo, HTREEITEM InsertarDespuesDe = NULL);
											//
											//! Función para borrar un nodo por su ID
											// void BorrarNodo(HTREEITEM BNodo);
		 void								BorrarNodo(HTREEITEM BNodo);
											//
											//! Función para borrar un nodo por su posicion
											// void BorrarNodo(const unsigned int Pos);
		 void								BorrarNodo(const unsigned int Pos);
											//
											//! Función para borrar todos los nodos
											// void BorrarTodo(void);
		 void								BorrarTodo(void);
											//
											//! Función para asignar la selecion.
											// inline void Seleccion(HTREEITEM sNodo);
		 inline void						Seleccion(HTREEITEM sNodo) { 
												TreeView_SelectItem(_hWnd, sNodo); 
											};
											//
											//! Función para obtener la selecion.
											// inline HTREEITEM Seleccion(void);
		 inline HTREEITEM					Seleccion(void) { 
												return TreeView_GetSelection(_hWnd); 
											};
											//
											//! Función que retorna un puntero DWLTreeView_Nodo partiendo de la ID Unica especificada.
											// DWLTreeView_Nodo *BuscarNodo(HTREEITEM BNodo);
		 DWLTreeView_Nodo                  *BuscarNodo(HTREEITEM BNodo);
											//
											//! Función para asignar el color del texto.
											// Para utilizar el color del sistema seleccionado utilizar -1 como color / parametro
											// inline void ColorTexto(COLORREF Col);
		 inline void						ColorTexto(COLORREF Col) { 
												TreeView_SetTextColor(_hWnd, Col); 
											};
											//
											//! Función para obtener el color del texto.
											// inline COLORREF ColorTexto(void);
		 inline COLORREF				    ColorTexto(void) {
												return TreeView_GetTextColor(_hWnd); 
											};
											//
											//! Función para asignar el color del fondo.
											// Para utilizar el color del sistema seleccionado utilizar -1 como color / parametro
											// inline void ColorFondo(COLORREF Col);
		 inline void						ColorFondo(COLORREF Col) {
												TreeView_SetBkColor(_hWnd, Col); 
											};
											//
											// Función para obtener el color del fondo.
											// inline COLORREF ColorFondo(void);
		 inline COLORREF					ColorFondo(void) { 
												 return TreeView_GetBkColor(_hWnd); 
											};
											//
											//! Función para asignar el color del fondo del nodo selecionado.
											// inline void ColorFondoSeleccionado(COLORREF Col);
		 inline void						ColorFondoSeleccionado(COLORREF Col) {
												_ColorSeleccion = Col; 
											};
											//
											// Función para obtener el color del fondo del nodo selecionado.
											// inline COLORREF ColorFondoSeleccionado(void);
		 inline COLORREF					ColorFondoSeleccionado(void) { 
												return _ColorSeleccion; 
											};
											//
											//! Función para asignar el color del texto del nodo selecionado.
											// inline void ColorTextoSeleccionado(COLORREF Col);
		 inline void					    ColorTextoSeleccionado(COLORREF Col) {
												_ColorSeleccionTexto = Col; 
											};
											//
											//! Función para obtener el color del texto del nodo selecionado.
											// inline COLORREF ColorTextoSeleccionado(void);
		 inline COLORREF					ColorTextoSeleccionado(void) {
												return _ColorSeleccionTexto; 
											};
											//
											//! Función para obtener la ID Unica del Nodo que esta en las coordenadas especificadas.
											// HTREEITEM HitTest(const int cX, const int cY);
		 HTREEITEM							HitTest(const int cX, const int cY);
											//
											//! Función para obtener la ID Unica del Nodo que esta en bajo el mouse.
											// HTREEITEM HitTest(void);
		 HTREEITEM							HitTest(void);
											//
											//! Función que retorna el Nodo especificado en forma de Clase DWLTreeView_Nodo. 
											// DWLTreeView_Nodo *Nodo(const int Pos);
		 DWLTreeView_Nodo		           *Nodo(const unsigned int Pos);
											//
											//! Función que retorna el Numero total de Nodos en el TreeView.
											// const UINT TotalNodos(void);
		 inline UINT             			TotalNodos(void) const {
												return static_cast<UINT>(_Nodos.size()); 
											};
											//
											//! Función para asignar un ImageList al TreeView
											// inline void AsignarImageList(HIMAGELIST ImgList);
		 inline void						AsignarImageList(HIMAGELIST ImgList) {
												TreeView_SetImageList(_hWnd, ImgList, TVSIL_NORMAL); 
											};
											//
											//! Función para obtener la fuente
											// inline HFONT Fuente(void);
		 inline HFONT						Fuente(void) {
												return _Fuente; 
											};
											//
											//! Función para asignar la fuente
											// inline void Fuente(HFONT nFuente);
		 inline void						Fuente(HFONT nFuente) {
												if (nFuente != NULL) _Fuente = nFuente; 
											};
											// 
											//! Función para empezar la edicion de un nodo del arbol
											// HWND EmpezarLabelEdit(DWLTreeView_Nodo *nNodo, const bool Numerico = false);
		 HWND								EmpezarLabelEdit(DWLTreeView_Nodo *nNodo, const bool Numerico = false);
											// 
											//! Función que termina la edicion de un nodo
											// void TerminarLabelEdit(void);
		 void								TerminarLabelEdit(void);
											// 
											//! Función que cancela la edicion de un nodo
											// void CancelarLabelEdit(void);
		 void								CancelarLabelEdit(void);
											//
											//! Función para mostrar un item
											// inline void MostrarNodo(HTREEITEM mNodo);
		 inline void					    MostrarNodo(HTREEITEM mNodo) {
												TreeView_EnsureVisible(_hWnd, mNodo); 
											};
		protected : ////////////////////////// Declaraciones protegidas (Solo podran usarse en la clase heredada no desde fuera)
											//
											//! Fuente por defecto del control
		 HFONT					           _Fuente;
											//
											//! Función para llamar al WindowProcedure original del TreeView. 
		 LRESULT CALLBACK		            GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
											//
											//! Función que se encarga de especificar los colores y la Fuente del TreeView para cada nodo
		 LRESULT				           _CustomDraw(LPARAM Datos);
											//
										    //! Función para asignar si el nodo tiene hijos o no..
		 void				               _SetChildren(HTREEITEM IC, const bool TieneHijos);
											//
											//! Color para el Fondo del Nodo selecionado
		 COLORREF			               _ColorSeleccion;
											//
											//! Color para el Texto del Nodo selecionado
		 COLORREF                          _ColorSeleccionTexto;
											//
											//! Vector que contiene los Nodos
		 std::vector<DWLTreeView_Nodo *>   _Nodos;
											//
											//! Texto temporal
		 DWL::DWLString                    _TmpStr;
		 private: //////////////////////////// Miembros privados
		 ///////////////////////////////////// -Miembros usados en el LabelEdit-
											//
											//! WindowProcedure que usara el Editbox en la Función EmpezarLabelEdit
											// static LRESULT CALLBACK _GestorMensajesEdit(HWND dhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		 static LRESULT CALLBACK           _GestorMensajesEdit(HWND dhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
											//
											//! Nodo en edicion
		 DWLTreeView_Nodo		          *_eNodo;
											//
											//! WindowProcedure Original del EditBox
		 WNDPROC						   _GestorMensajesOriginalEdit;
											//
											//! Brocha del fondo del EditBox
		 HBRUSH					           _BrochaFondoEdit;
											//
											//! Valor para saber si la lista esta en estado de edicion
		 bool			                   _Editando;
											//
											//! Handle del EditBox
		 HWND							   _hWndEdit;
											//
		 friend class DWLTreeView_Nodo;      // Decalro la clase DWLTreeView_Nodo amiga de esta clase
		};									//
		////////////////////////////////////// Fin class DWLTreeView;




		//! Clase contenedora de los datos que se pueden necesitar al terminar la edicion de un nodo
		class DWLTreeView_TerminarLabelEdit {
		public : ///////////// Miembros publicos
									//
									//! Constructor por defecto (Nunca deberia usarse)
									// TreeView_TerminarLabelEdit(void);
									DWLTreeView_TerminarLabelEdit(void) {
										Cancelar = false;
									};
									//
									//! Constructor asignador de datos
									// TreeView_TerminarLabelEdit(DWLTreeView_Nodo *nNodo, const TCHAR *nNuevoTexto);
									DWLTreeView_TerminarLabelEdit(DWLTreeView_Nodo *nNodo, const TCHAR *nNuevoTexto) {
										Cancelar = false;
										_Nodo = nNodo;
										NuevoTexto = nNuevoTexto;
									};
									//
									//! Destructor
									// ~TreeView_TerminarLabelEdit(void);
								   ~DWLTreeView_TerminarLabelEdit(void) {
									};
									//
									//! Función que retorna un puntero al DWLTreeView_Nodo correspondiente a este nodo en edicion.
									// inline DWLTreeView_Nodo *Nodo(void);
		 inline DWLTreeView_Nodo	   *Nodo(void) {
										return _Nodo;
									};
									//
									//! Estado de cancelacion para esta edicion
		 bool						Cancelar;
									//
									//! Nuevo texto que se va a aplicar
		 DWL::DWLString				NuevoTexto;
		private : //////////////////// Miembros privados
									//
									//! Clase DWLTreeView_Nodo que contiene el nodo que se esta editando
		 DWLTreeView_Nodo          *_Nodo;
		};							//
		//////////////////////////////

	}
}
#endif // DWL_DWLTreeView_H

// Ver 1.0a
// -El codigo ha sido modificado para poder editarlo mejor


// Version 1.1
// -Se han reemplazado varios nombres de Funciónes medio en ingles medio en castellano para que pasen a ser totalmente en castellano.
// -Se han eliminado todas las macros que empezaban por On.
//  Haora existen nuevas macros que empiezan por ENLACE_
// -Se han eliminado las notificaciones estandard que retornaba este control
//  Haora este control retorna sus propios mensajes :
//   -Mensaje								-Macro													   -Prototipos para las Funciónes que reciben el evento
//    DWL_TREEVIEW_CLICK_DERECHO			 ENLACE_TreeView_Evento_Mouse_Click							(const int Boton, const int cX, const int cY, const int ID)
//    DWL_TREEVIEW_CLICK_IZQUIERDO			 ENLACE_TreeView_Evento_Mouse_Click							(const int Boton, const int cX, const int cY, const int ID)
//    DWL_TREEVIEW_CLICK_MEDIO				 ENLACE_TreeView_Evento_Mouse_Click							(const int Boton, const int cX, const int cY, const int ID)
//    DWL_TREEVIEW_DOBLECLICK_DERECHO		 ENLACE_TreeView_Evento_Mouse_DobleClick					(const int Boton, const int cX, const int cY, const int ID)
//    DWL_TREEVIEW_DOBLECLICK_IZQUIERDO		 ENLACE_TreeView_Evento_Mouse_DobleClick					(const int Boton, const int cX, const int cY, const int ID)	
//    DWL_TREEVIEW_DOBLECLICK_MEDIO			 ENLACE_TreeView_Evento_Mouse_DobleClick					(const int Boton, const int cX, const int cY, const int ID)
//    DWL_TREEVIEW_TECLADO_PRESIONADO		 ENLACE_TreeView_Evento_Teclado_TeclaPresionada				(const int TeclaVirtual, const int ID)
//    DWL_TREEVIEW_TECLADO_SOLTADO			 ENLACE_TreeView_Evento_Teclado_TeclaSoltada				(const int TeclaVirtual, const int ID)
//    DWL_TREEVIEW_TECLADO_INTRO			 ENLACE_TreeView_Evento_Teclado_Intro						(const int ID)	
//    DWL_TREEVIEW_FOCO_OBTENIDO			 ENLACE_TreeView_Evento_Foco_Obtenido						(const int ID)
//    DWL_TREEVIEW_FOCO_PERDIDO				 ENLACE_TreeView_Evento_Foco_Perdido						(const int ID)
