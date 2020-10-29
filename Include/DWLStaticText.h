/*! \file DWLStaticText.h
	\brief		Archivo que contiene funciones para la utilización de un statictext/label en windows.


	\details	Clase diseñada para poder controlar un statictext/label en windows.																				\n
				Esta clase en breve no formara parte del proyecto y por lo tanto no recibira actualizaciones.											\n
				Para la version 1.0 de la DWL esta clase probablemente desaparecera.																	\n

																																						\n
	\author		devildrey33
	\version	0.95
	\date		08/12/2004

	\remarks
				Archivo creado por devildrey33 el dia [03/05/2003] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n	
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n	
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n	

*/ 
#ifndef DWL_STATICTEXT_H
#define DWL_STATICTEXT_H

#include "DWLControl.h"

namespace DWL {
	namespace Controles {
		//! Clase para controlar un statictext de windows.
		class DWLStaticText : public Base::DWLControl {
		public: ////////////////////// Miembros publicos
									//
									//! Constructor
									// DWLStaticText(void);
									DWLStaticText(void) {
									};
									//
									//! Destructor
									// ~ClaseStaticText(void);
								   ~DWLStaticText(void)  { 
									   Destruir();
									};
									//
									//! Función para crear el control static text
									// void Crear(const long Estilos, HWND hWndParent, const TCHAR *Txt, const int cX, const int cY, const int cAncho, const int cAlto, const int cID);
		 void                       Crear(const long Estilos, HWND hWndParent, const TCHAR *Txt, const int cX, const int cY, const int cAncho, const int cAlto, const int cID) {
										_ColorFondoRGB = GetSysColor(COLOR_WINDOWTEXT);
										_ColorTexto = GetSysColor(COLOR_WINDOWTEXT);
										_ColorFondo = GetSysColorBrush(COLOR_WINDOW); 
										int NX = cX; 
										int NY = cY; 
										if (cX == CENTRADO) NX = _CalcularCentrado(hWndParent, true, cAncho); 
										if (cY == CENTRADO) NY = _CalcularCentrado(hWndParent, false, cAlto); 
										_hWnd = CreateWindow(TEXT("STATIC"), Txt, Estilos, NX, NY, cAncho, cAlto, hWndParent, reinterpret_cast<HMENU>(IntToPtr(cID)), GetModuleHandle(NULL), NULL);
										ConectarControl();
										_Fuente = (HFONT)SendMessage(_hWnd, WM_GETFONT, 0, 0); 
									};
									//
									//! Función para asignar esta clase a un control static text
									// void Asignar(HWND hWndParent, const int ID_Control);
		 void                       Asignar(HWND hWndParent, const int ID_Control) {
										_ColorFondoRGB = GetSysColor(COLOR_WINDOWTEXT); 
										_ColorTexto = GetSysColor(COLOR_WINDOWTEXT);
										_ColorFondo = GetSysColorBrush(COLOR_WINDOW); 
										_hWnd = GetDlgItem(hWndParent, ID_Control);
										ConectarControl(); 
										_Fuente = (HFONT)SendMessage(_hWnd, WM_GETFONT, 0, 0);
									};
									//
									//! Función que retorna el texto de este control
									// void	ObtenerTexto(TCHAR *nTxt, const int TamTxt);
		 void						ObtenerTexto(TCHAR *nTxt, const int TamTxt) {
										GetDlgItemText(GetParent(_hWnd), GetWindowLongPtr(_hWnd, GWL_ID), nTxt, TamTxt);
									};
									//
									//! Función que asigna el texto de este control
									// void Texto(const TCHAR *Txt);
		 void                       AsignarTexto(const TCHAR *Txt) { 
										SetDlgItemText(GetParent(_hWnd), GetWindowLongPtr(_hWnd, GWL_ID), Txt); 
									};
									//
									//! Función que retorna el color del texto
									// inline COLORREF ColorTexto(void);
		 inline COLORREF            ColorTexto(void) {
										return _ColorTexto; 
									};
									//
									//! Función para asignar el color del texto
									// inline void ColorTexto(COLORREF nCol)
		 inline void                ColorTexto(COLORREF nCol) {
										_ColorTexto = nCol; 
									};
									//
									//! Función que retorna el color del fondo
									// inline HBRUSH ColorFondo(void)
		 inline COLORREF            ColorFondo(void) {
										return _ColorFondoRGB; 
									};
									//
									//! Función para asignar el color del fondo
									// inline void ColorFondo(HBRUSH nBrocha)
		 inline void                ColorFondo(COLORREF nColor) {
										DeleteObject(_ColorFondo);
										_ColorFondo = CreateSolidBrush(nColor); 
										_ColorFondoRGB = nColor; 
									};
									//
									//! Función que retorna la fuente usada por este control
									// inline HFONT Fuente(void)
		 inline HFONT               Fuente(void) {
										return _Fuente; 
									};
									//
									//! Función que asigna la fuente que se usara para pintar texto en este control
									// inline void Fuente(HFONT nFuente)
		 inline void                Fuente(HFONT nFuente) {
										if (nFuente != NULL) { 
											_Fuente = nFuente;
											SendMessage(_hWnd, WM_SETFONT, (WPARAM)_Fuente , 0); 
										} 
									};
									//
									//! Función para destruir el statictext
									// const BOOL Destruir(void);
		 const BOOL                 Destruir(void) { 
										BOOL R = BaseControl::Destruir();
										if (_ColorFondo != NULL) DeleteObject(_ColorFondo); 
										_ColorFondo = NULL;
										return R;
									};
		protected ://///////////////// Declaraciones protegidas (Solo podran usarse en la clase heredada no desde fuera)
									//
									//! Brocha que contendra el color del fondo
		 HBRUSH                    _ColorFondo;
									//
									//! Color del fondo 
		 COLORREF                  _ColorFondoRGB;
									//
									//! Color del texto
		 COLORREF                  _ColorTexto;
									//
									//! Fuente que se usara para pintar el texto
		 HFONT                     _Fuente;
									//
									//! Window procedure que reemplazara al WindowProcedure del EditBox
									// LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
		 LRESULT CALLBACK           GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
										NMHDR T; 
										T.hwndFrom = _hWnd;
										T.idFrom   = GetWindowLongPtr(_hWnd, GWL_ID); 
										switch (uMsg) {  
											case WM_CTLCOLORSTATIC : 
												SetTextColor((HDC)wParam, _ColorTexto); 
												SetBkMode((HDC)wParam, TRANSPARENT); 
												return (LRESULT)_ColorFondo; 
											case WM_LBUTTONUP : 
												PostMessage(GetParent(_hWnd), DWL_STATICTEXT_CLICK_IZQUIERDO, ID(), NULL);
												break; 
											case WM_RBUTTONUP : 
												PostMessage(GetParent(_hWnd), DWL_STATICTEXT_CLICK_DERECHO, ID(), NULL);
												break; 
											case WM_MBUTTONUP : 
												PostMessage(GetParent(_hWnd), DWL_STATICTEXT_CLICK_MEDIO, ID(), NULL);
												break; 
											case WM_LBUTTONDBLCLK : 
												PostMessage(GetParent(_hWnd), DWL_STATICTEXT_DOBLECLICK_IZQUIERDO, ID(), NULL);
												break; 
											case WM_RBUTTONDBLCLK : 
												PostMessage(GetParent(_hWnd), DWL_STATICTEXT_DOBLECLICK_DERECHO, ID(), NULL);
												break; 
											case WM_MBUTTONDBLCLK : 
												PostMessage(GetParent(_hWnd), DWL_STATICTEXT_DOBLECLICK_MEDIO, ID(), NULL);
												break; 
										} 
										return DWLControl::GestorMensajes(uMsg, wParam, lParam); 
									};
		};							//
		////////////////////////////// Final ClaseStaticText

	}
}


#endif // DWL_STATICTEXT_H

// Ver 1.0a
// -Bug en la Función crear que no asignaba correctamente el _hWnd del control con lo que la mitad de Funciónes no Funciónaban
// -El codigo ha sido modificado para poder editarlo mejor



// Version 1.1
// -Se han eliminado todas las macros que empezaban por On.
//  Haora existen nuevas macros que empiezan por ENLACE_
// -Se han eliminado las notificaciones estandard que retornaba este control
//  Haora este control retorna sus propios mensajes :
//   -Mensaje								-Macro
//    DWL_STATICTEXT_CLICK_DERECHO			 ENLACE_StaticText_Evento_Mouse_Click	
//    DWL_STATICTEXT_CLICK_IZQUIERDO		 ENLACE_StaticText_Evento_Mouse_Click	
//    DWL_STATICTEXT_CLICK_MEDIO			 ENLACE_StaticText_Evento_Mouse_Click
//    DWL_STATICTEXT_DOBLECLICK_DERECHO		 ENLACE_StaticText_Evento_Mouse_DobleClick
//    DWL_STATICTEXT_DOBLECLICK_IZQUIERDO	 ENLACE_StaticText_Evento_Mouse_DobleClick	
//    DWL_STATICTEXT_DOBLECLICK_MEDIO		 ENLACE_StaticText_Evento_Mouse_DobleClick


