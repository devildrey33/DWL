/*! \file DWLListBox.h
	\brief		Archivo que contiene funciones para la utilización de un listbox en windows.


	\details	Clase diseñada para poder controlar un listbox de windows.																				\n
				Esta clase en breve no formara parte del proyecto y por lo tanto no recibira actualizaciones.											\n
				Si quieres utilizar un control del estilo del edit box con la DWL se recomienda usar DWLListaEx										\n
				Para la version 1.0 de la DWL esta clase probablemente desaparecera.																	\n

																																						\n
	\author		devildrey33
	\version	0.95
	\date		22/05/2005

	\remarks
				Archivo creado por devildrey33 el dia [15/06/2004] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

*/
#ifndef DWL_LISTBOXEX_H
#define DWL_LISTBOXEX_H

//#include <string>
//#include <commctrl.h>
#include "DWLControl.h"





namespace DWL {
	namespace Controles {
		//! Clase para controlar un ListBox de windows.
        class DWLListBox : public DWL::Controles::Base::DWLControl {
		public: //////////////////// Miembros publicos
									//! Constructor
									//  DWLListBox(void);
									DWLListBox(void) {
										_hWnd = NULL;
									};
									//
									//! Destructor
									// ~DWLListBox(void);
								   ~DWLListBox(void) {
									   Destruir();
									};
									//
									//! Función para crear un control ListBox
									//  void Crear(const long Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID);
		 void						Crear(const long Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID) {
										_ColorTexto = GetSysColor(COLOR_WINDOWTEXT);
										_ColorFondo = GetSysColorBrush(COLOR_WINDOW);
										_ColorFondoRGB = GetSysColor(COLOR_WINDOWTEXT);
										int NX = cX;
										int NY = cY;
										if (cX == DWL_CENTRADO) NX = _CalcularCentrado(hWndParent, true, cAncho);
										if (cY == DWL_CENTRADO) NY = _CalcularCentrado(hWndParent, false, cAlto);
										_hWnd = CreateWindow(TEXT("LISTBOX"), TEXT(""), Estilos, NX, NY, cAncho, cAlto, hWndParent, reinterpret_cast<HMENU>(IntToPtr(cID)), GetModuleHandle(NULL), NULL);
										ConectarControl();
										_Fuente = (HFONT)SendMessage(_hWnd, WM_GETFONT, 0, 0);
									};
									//
									//! Función para asignar un listbox ya creado en un Dialogo
									//  void Asignar(HWND hWndParent, const int ID_Control);
		 void						Asignar(HWND hWndParent, const int ID_Control) {
										_ColorTexto = GetSysColor(COLOR_WINDOWTEXT);
										_ColorFondo = GetSysColorBrush(COLOR_WINDOW);
										_ColorFondoRGB = GetSysColor(COLOR_WINDOWTEXT);
										_hWnd = GetDlgItem(hWndParent, ID_Control);
										ConectarControl();
										_Fuente = (HFONT)SendMessage(_hWnd, WM_GETFONT, 0, 0);
									};
									//
									//! Función para insertar un texto en la linea especificada del ListBox
									//  inline void	AgregarString(const TCHAR *Txt, const unsigned int Pos = 0);
		 inline void				AgregarString(const TCHAR *Txt, const unsigned int Pos = 0) {
										SendMessage(_hWnd, LB_INSERTSTRING, Pos, (LPARAM)Txt);
									};
									//
									//! Función para borrar una linea del ListBox
									//  inline void	BorrarString(const unsigned int Pos);
		 inline void				BorrarString(const unsigned int Pos) {
										SendMessage(_hWnd, LB_DELETESTRING, Pos, 0);
									};
									//
									//! Función para borrar todo el ListBox
									//  inline void BorrarTodo(void);
		 inline void				BorrarTodo(void) {
										SendMessage(_hWnd, LB_RESETCONTENT, 0, 0);
									};
									//
									//! Función que retorna el numero total de lineas
									//  inline UINT TotalStrings(void)
		 inline UINT            	TotalStrings(void) {
										return static_cast<UINT>(SendMessage(_hWnd, LB_GETCOUNT, 0, 0));
									 };
									//
									//! Función que retorna el numero total de lineas selecionadas
									//  inline const unsigned int TotalStringsSeleccionados(void);
		 inline UINT            	TotalStringsSeleccionados(void) {
										return static_cast<UINT>(SendMessage(_hWnd, LB_GETSELCOUNT, 0, 0));
									};
									//
									//! Asigna el estado de selecion de un String
									//  inline void Seleccion(const unsigned int Pos, const bool Sel);
		 inline void				Seleccion(const unsigned int Pos, const bool Sel) {
										SendMessage(_hWnd, LB_SETSEL, (WPARAM)Sel, Pos);
									};
									//
									//! Retorna el estado de selecion de un String
									//  inline const bool Seleccion(const unsigned int Pos);
		 inline const bool			Seleccion(const unsigned int Pos) {
										if (SendMessage(_hWnd, LB_GETSEL, Pos, 0) == 0) return false;
										else											return true;
									};
									//
									//! Asigna el String selecionado por el marco
									//  inline void PosicionMarca(const unsigned int Pos);
		 inline void				PosicionMarca(const unsigned int Pos) {
										SendMessage(_hWnd, LB_SETCURSEL, Pos, 0);
									};
									//
									//! Retorna el String selecionado por el marco
									//  inline const int unsigned PosicionMarca(void);
		 inline UINT            	PosicionMarca(void) {
										return static_cast<UINT>(SendMessage(_hWnd, LB_GETCURSEL, 0, 0));
									};
									//
									//! Función que retorna el texto de una linea
									//  void ObtenerTexto(const unsigned int Linea, TCHAR *Txt);
		 void						ObtenerTexto(const unsigned int Linea, TCHAR *Txt) {
										SendMessage(_hWnd, LB_GETTEXT, Linea, (WPARAM)Txt);
									};
									//
									//! Función que retorna el color del texto
									//  inline COLORREF ColorTexto(void);
		 inline COLORREF			ColorTexto(void) {
										return _ColorTexto;
									};
									//
									//! Función para asignar el color del texto
									//  inline void ColorTexto(COLORREF nCol)
		 inline void				ColorTexto(COLORREF nCol) {
										_ColorTexto = nCol;
									};
									//
									//! Función que retorna el color del fondo
									//  inline COLORREF ColorFondo(void)
		 inline COLORREF			ColorFondo(void) {
										return _ColorFondoRGB;
									};
									//
									//! Función para asignar el color del fondo
									//  inline void ColorFondo(COLORREF nBrocha)
		 inline void				ColorFondo(COLORREF nColor) {
										DeleteObject(_ColorFondo);
										_ColorFondo = CreateSolidBrush(nColor);
										_ColorFondoRGB = nColor;
									};
									//
									//! Función que retorna la fuente usada por este control
									//  inline HFONT Fuente(void)
		 inline HFONT				Fuente(void) {
										return _Fuente;
									};
									//
									//! Función que asigna la fuente que se usara para pintar texto en este control
									//  inline void Fuente(HFONT nFuente)
		 inline void				Fuente(HFONT nFuente) {
										if (nFuente != NULL) {
											_Fuente = nFuente;
											SendMessage(_hWnd, WM_SETFONT, (WPARAM)_Fuente , 0);
										}
									};
									//
									//! Función para destruir el Control ListBox y liberar toda la memoria reservada
									//  const BOOL Destruir(void);
		  BOOL					    Destruir(void) {
										BOOL R = DWLControl::Destruir();
										if (_ColorFondo != NULL) DeleteObject(_ColorFondo);
										_ColorFondo = NULL;
										return R;
									};
		protected : ////////////////// Declaraciones protegidas (Solo podran usarse en la clase heredada no desde fuera)
									//
									//! Brocha que contendra el color del fondo
		 HBRUSH                    _ColorFondo;
									//
									//! Color RGB del Fondo
		 COLORREF                  _ColorFondoRGB;
									//
									//! Color del texto
		 COLORREF                  _ColorTexto;
									//
									//! Fuente que se usara para pintar el texto
		 HFONT                     _Fuente;
									//
									//! WindowProcedure original del ListBox
		 WNDPROC                   _GestorMensajes;
									//
									//! Window procedure que reemplazara al WindowProcedure del ListBox
									//  LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
		 LRESULT CALLBACK           GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
										NMHDR T; T.hwndFrom = _hWnd;
										T.idFrom   = GetWindowLongPtr(_hWnd, GWL_ID);
										switch (uMsg) {
											case WM_CTLCOLORLISTBOX :
												SetTextColor((HDC)wParam, _ColorTexto);
												SetBkColor((HDC)wParam, _ColorFondoRGB);
												return (LRESULT)_ColorFondo;
											case WM_LBUTTONUP :
												PostMessage(GetParent(_hWnd), DWL_LISTBOX_CLICK_IZQUIERDO, ID(), lParam);
												break;
											case WM_RBUTTONUP :
												PostMessage(GetParent(_hWnd), DWL_LISTBOX_CLICK_DERECHO, ID(), lParam);
												break;
											case WM_MBUTTONUP :
												PostMessage(GetParent(_hWnd), DWL_LISTBOX_CLICK_MEDIO, ID(), lParam);
												break;
											case WM_LBUTTONDBLCLK :
												PostMessage(GetParent(_hWnd), DWL_LISTBOX_DOBLECLICK_IZQUIERDO, ID(), 0);
												break;
											case WM_RBUTTONDBLCLK :
												PostMessage(GetParent(_hWnd), DWL_LISTBOX_DOBLECLICK_DERECHO, ID(), 0);
												break;
											case WM_MBUTTONDBLCLK :
												PostMessage(GetParent(_hWnd), DWL_LISTBOX_DOBLECLICK_MEDIO, ID(), 0);
												break;
											case WM_KEYDOWN :
												PostMessage(GetParent(_hWnd), DWL_LISTBOX_TECLADO_PRESIONADO, wParam, (LPARAM)ID());
												break;
											case WM_KEYUP :
												PostMessage(GetParent(_hWnd), DWL_LISTBOX_TECLADO_SOLTADO, wParam, (LPARAM)ID());
												if (wParam == 13) {
													PostMessage(GetParent(_hWnd), DWL_LISTBOX_TECLADO_INTRO, wParam, (LPARAM)ID());
												}
												break;
											case WM_SETFOCUS :
												PostMessage(GetParent(_hWnd), DWL_LISTBOX_FOCO_OBTENIDO, ID(), 0);
												break;
											case WM_KILLFOCUS :
												PostMessage(GetParent(_hWnd), DWL_LISTBOX_FOCO_PERDIDO, ID(), 0);
												break;
										}
										return DWLControl::GestorMensajes(uMsg, wParam, lParam);
									};
		};							//
		////////////////////////////// Final ClaseListBox
 
	}
}

#endif // DWL_LISTBOXEX_H


// Ver 0.9a
// -Se han modificado varias Funciónes para que sean en linea (inline ...)
// -El codigo ha sido modificado para poder editarlo mejor

// Version 0.95
// -Se han eliminado todas las macros que empezaban por On.
//  Haora existen nuevas macros que empiezan por ENLACE_
// -Se han eliminado las notificaciones estandard que retornaba este control
//  Haora este control retorna sus propios mensajes :
//   -Mensaje								-Macro
//    DWL_LISTBOX_CLICK_DERECHO				 ENLACE_ListBox_Evento_Mouse_Click
//    DWL_LISTBOX_CLICK_IZQUIERDO			 ENLACE_ListBox_Evento_Mouse_Click
//    DWL_LISTBOX_CLICK_MEDIO				 ENLACE_ListBox_Evento_Mouse_Click
//    DWL_LISTBOX_DOBLECLICK_DERECHO		 ENLACE_ListBox_Evento_Mouse_DobleClick
//    DWL_LISTBOX_DOBLECLICK_IZQUIERDO		 ENLACE_ListBox_Evento_Mouse_DobleClick
//    DWL_LISTBOX_DOBLECLICK_MEDIO			 ENLACE_ListBox_Evento_Mouse_DobleClick
//    DWL_LISTBOX_TECLADO_PRESIONADO		 ENLACE_ListBox_Evento_Teclado_TeclaPresionada
//    DWL_LISTBOX_TECLADO_SOLTADO			 ENLACE_ListBox_Evento_Teclado_TeclaSoltada
//    DWL_LISTBOX_TECLADO_INTRO				 ENLACE_ListBox_Evento_Teclado_Intro
//    DWL_LISTBOX_FOCO_OBTENIDO				 ENLACE_ListBox_Evento_Foco_Obtenido
//    DWL_LISTBOX_FOCO_PERDIDO				 ENLACE_ListBox_Evento_Foco_Perdido
