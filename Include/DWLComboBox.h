/*! \file DWLComboBox.h
	\brief		Archivo que contiene funciones para la utilización de un combobox en windows.


	\details	Clase diseñada para poder controlar un combobox de windows.																				\n
				Esta clase en breve no formara parte del proyecto y por lo tanto no recibira actualizaciones.											\n
				Si quieres utilizar un control del estilo del combo box con la DWL se recomienda usar DWLEdicionDesplegableEx							\n
				Para la version 1.0 de la DWL esta clase probablemente desaparecera.																	\n

																																						\n
	\author		devildrey33
	\version	0.95
	\date		20/05/2005

	\remarks
				Archivo creado por devildrey33 el dia [26/04/2004] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n
 
*/
#ifndef DWL_COMBOBOX_H
#define DWL_COMBOBOX_H

#include <commctrl.h>
#include "DWLControl.h"
#include "DWLString.h"



//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Controles
	namespace Controles {
		//! Clase para controlar un ComboBox de windows
        class DWLComboBox : public Base::DWLControl  {
		public: ////////////////////// Miembros publicos
  									//! Constructor
									//  DWLComboBox(void);
									DWLComboBox(void) : _ColorFondo(NULL), _ColorFondoRGB(RGB(0,0,0)), _ColorTexto(RGB(255,255,255)), _Fuente(NULL) {
									};
									//
									//! Destructor
									// ~DWLComboBox(void);
								   ~DWLComboBox(void) {
									};
									//
									//! Función para crear el control
									//  HWND Crear(const long Estilos, HWND hWndParent, const TCHAR *Text, const int cX, const int cY, const int cAncho, const int cAlto, const int cID)
		 HWND                       Crear(const long Estilos, HWND hWndParent, const TCHAR *Text, const int cX, const int cY, const int cAncho, const int cAltoListaCombo, const int cID) {
										int NX = cX;
										int NY = cY;
										if (cX == DWL_CENTRADO) NX = _CalcularCentrado(hWndParent, true, cAncho);
										if (cY == DWL_CENTRADO) NY = _CalcularCentrado(hWndParent, false, 20);
										_ColorTexto = GetSysColor(COLOR_WINDOWTEXT);
										_ColorFondo = GetSysColorBrush(COLOR_WINDOW);
										_hWnd = CreateWindow(TEXT("COMBOBOX"), Text, Estilos, NX, NY, cAncho, cAltoListaCombo, hWndParent, reinterpret_cast<HMENU>(IntToPtr(cID)), GetModuleHandle(NULL), NULL);
										ConectarControl();
										if (Text != NULL) AsignarTexto(Text);
										_Fuente = (HFONT)SendMessage(_hWnd, WM_GETFONT, 0, 0);
										// LA ALTURA DE LA LISTA SE ASIGNA EN LA ALTURA DEL CONTROL
//										SendMessage(_hWnd, CB_SETDROPPEDWIDTH , AltoLista, 0);
										return _hWnd;
									};
									//
									//! Función que asigna la altura de la lista desplegable del control
									//  void AltoLista(const int nAlto);
		 void						AltoLista(const int nAlto) {
										SendMessage(_hWnd, CB_SETDROPPEDWIDTH , nAlto, 0);
									}
									//
									//! Función para asignar un EditBox ya creado en un Dialogo
									//  void Asignar(HWND hWndParent, const int ID_Control);
		 HWND                       Asignar(HWND hWndParent, const int ID_Control) {
										RECT Medidas;
										_ColorTexto = GetSysColor(COLOR_WINDOWTEXT);
										_ColorFondo = GetSysColorBrush(COLOR_WINDOW);
										_hWnd = GetDlgItem(hWndParent, ID_Control);
										ConectarControl();
										GetWindowRect(_hWnd, &Medidas);
										_Fuente = (HFONT)SendMessage(_hWnd, WM_GETFONT, 0, 0);
										return _hWnd;
									};
									//
									//! Función para agregar un item en la posicion especificada
									//  inline void AgregarItem(const TCHAR *Txt, const int Pos = -1);
		 inline void                AgregarItem(const TCHAR *Txt, const int Pos = -1) {
										SendMessage(_hWnd, CB_INSERTSTRING, Pos, (LPARAM)Txt);
									};
									//
									//! Función para borrar el item de la posicion especificada
									//  inline void BorrarItem(const int Pos);
		 inline void                BorrarItem(const int Pos) {
										SendMessage(_hWnd, CB_DELETESTRING, Pos, 0);
									};
									//
									//! Función que borra todo el combobox
									//  inline void BorrarTodo(void);
		 inline void                BorrarTodo(void) {
										SendMessage(_hWnd, CB_RESETCONTENT, 0, 0);
									};
									//
									//! Numero total de strings en el combo
									//  inline int TotalItems(void) ;
		 inline int                 TotalItems(void) const {
										return static_cast<int>(SendMessage(_hWnd, CB_GETCOUNT, 0, 0));
									};
									//
									//! Función que retorna el Item Seleccionado
									//  inline int Seleccion(void)
		 inline int                 Seleccion(void) const {
										return static_cast<int>(SendMessage(_hWnd, CB_GETCURSEL, 0, 0));
									};
									//
									//! Función que asigna el Item Seleccionado
									//  inline void Seleccion(const int Pos)
		 inline void                Seleccion(const int Pos) {
										SendMessage(_hWnd, CB_SETCURSEL, Pos, 0);
									};
									//
									//! Función para asignar texto
									//  void AsignarTexto(const TCHAR *Txt);
		 void                       AsignarTexto(const TCHAR *Txt) {
										SetDlgItemText(GetParent(_hWnd), GetWindowLongPtr(_hWnd, GWL_ID), Txt);
									};
									//
									//! Función que retorna el texto actual
									//  void ObtenerTexto(TCHAR *Txt, const int TamTxt);
		 void						ObtenerTexto(TCHAR *Txt, const int TamTxt) {
										GetDlgItemText(GetParent(_hWnd), GetWindowLongPtr(_hWnd, GWL_ID), Txt, TamTxt);
									};
									//
									//! Función que retorna el texto actual
									//  void ObtenerTexto(TCHAR *Txt, const int TamTxt);
		 void						ObtenerTexto(DWL::DWLString &Txt) {
										TCHAR Tmp[512] = TEXT("");
										GetDlgItemText(GetParent(_hWnd), GetWindowLongPtr(_hWnd, GWL_ID), Tmp, 512);
										Txt = Tmp;
									};
									//
									//! Función para destruir el combobox
									//  void Destruir(void);
		 BOOL                       Destruir(void) {
										BOOL R = DWLControl::Destruir();
										if (_ColorFondo != NULL) DeleteObject(_ColorFondo);
										_ColorFondo = NULL;
										return R;
									};
									//
									//! Función que retorna el color del texto
									//  inline COLORREF ColorTexto(void);
		 inline COLORREF            ColorTexto(void) {
										return _ColorTexto;
									};
									//
									//! Función para asignar el color del texto
									//  inline void ColorTexto(COLORREF nCol);
		 inline void                ColorTexto(COLORREF nCol) {
										_ColorTexto = nCol;
									};
									//
									//! Función que retorna el color del fondo
									//  inline COLORREF ColorFondo(void);
		 inline COLORREF            ColorFondo(void) {
										return _ColorFondoRGB;
									};
									//
									//! Función para asignar el color del fondo
									//  inline void ColorFondo(COLORREF nCol);
		 inline void                ColorFondo(COLORREF nColor) {
										DeleteObject(_ColorFondo);
										_ColorFondoRGB = nColor;
										_ColorFondo = CreateSolidBrush(nColor);
									};
									//
									//! Función que retorna la fuente usada por este control
									//  inline HFONT Fuente(void);
		 inline HFONT               Fuente(void) {
										return _Fuente;
									};
									//
									//! Función que asigna la fuente que se usara para pintar texto en este control
									//  inline void Fuente(HFONT Fuente);
		 inline void                Fuente(HFONT nFuente) {
										if (nFuente != NULL) _Fuente = nFuente;
									};
		protected : ////////////////// -Miembros protegidos
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
									//! Window procedure que reemplazara al WindowProcedure del ComboBox
									//  LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
		 LRESULT CALLBACK           GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
										switch (uMsg) {
											case WM_CTLCOLORLISTBOX :
											case WM_CTLCOLOREDIT :
												SetBkMode((HDC)wParam, TRANSPARENT);
												SetTextColor((HDC)wParam, _ColorTexto);
												return (LRESULT)_ColorFondo;
											case WM_LBUTTONUP :
												PostMessage(GetParent(_hWnd), DWL_COMBOBOX_CLICK_IZQUIERDO, ID(), lParam);
												break;
											case WM_RBUTTONUP :
												PostMessage(GetParent(_hWnd), DWL_COMBOBOX_CLICK_DERECHO, ID(), lParam);
												break;
											case WM_MBUTTONUP :
												PostMessage(GetParent(_hWnd), DWL_COMBOBOX_CLICK_MEDIO, ID(), lParam);
												break;
											case WM_LBUTTONDBLCLK :
												PostMessage(GetParent(_hWnd), DWL_COMBOBOX_DOBLECLICK_IZQUIERDO, ID(), lParam);
												break;
											case WM_RBUTTONDBLCLK :
												PostMessage(GetParent(_hWnd), DWL_COMBOBOX_DOBLECLICK_DERECHO, ID(), lParam);
												break;
											case WM_MBUTTONDBLCLK :
												PostMessage(GetParent(_hWnd), DWL_COMBOBOX_DOBLECLICK_MEDIO, ID(), lParam);
												break;
											case WM_KEYDOWN :
												PostMessage(GetParent(_hWnd), DWL_COMBOBOX_TECLADO_PRESIONADO, wParam, (LPARAM)ID());
												break;
											case WM_KEYUP :
												PostMessage(GetParent(_hWnd), DWL_COMBOBOX_TECLADO_SOLTADO, wParam, (LPARAM)ID());
												if (wParam == 13) {
													PostMessage(GetParent(_hWnd), DWL_COMBOBOX_TECLADO_INTRO, wParam, (LPARAM)ID());
												}
												break;
											case WM_SETFOCUS :
												PostMessage(GetParent(_hWnd), DWL_COMBOBOX_FOCO_OBTENIDO, ID(), lParam);
												break;
											case WM_KILLFOCUS :
												PostMessage(GetParent(_hWnd), DWL_COMBOBOX_FOCO_PERDIDO, ID(), lParam);
												break;
										}
										return DWLControl::GestorMensajes(uMsg, wParam, lParam);
									};
          private ://///////////////// Miembros privados
                                    // Constructor copia des-habilitado
                                    DWLComboBox(const DWLComboBox &) : _ColorFondo(NULL), _ColorFondoRGB(RGB(0,0,0)), _ColorTexto(RGB(255,255,255)), _Fuente(NULL) { }
                                    // Operador = des-habilitado
		 inline DWLComboBox        &operator=(const DWLComboBox &) { return *this; };

		};							//
		////////////////////////////// Final class DWLComboBox;

	}
}


#endif // DWL_CLASECOMBOBOXEX_H

// Ver 0.9a
// -El codigo ha sido modificado para poder editarlo mejor

// Version 0.95
// -Se han eliminado todas las macros que empezaban por On.
//  Haora existen nuevas macros que empiezan por ENLACE_
// -Se han eliminado las notificaciones estandard que retornaba este control
//  Haora este control retorna sus propios mensajes :
//   -Mensaje								-Macro													   -Función
//    DWL_COMBOBOX_CLICK_DERECHO			 ENLACE_ComboBox_Evento_Mouse_Click							ComboBox_Evento_Mouse_Click(const int Boton, const int ID)
//    DWL_COMBOBOX_CLICK_IZQUIERDO			 ENLACE_ComboBox_Evento_Mouse_Click							ComboBox_Evento_Mouse_Click(const int Boton, const int ID)
//    DWL_COMBOBOX_CLICK_MEDIO				 ENLACE_ComboBox_Evento_Mouse_Click							ComboBox_Evento_Mouse_Click(const int Boton, const int ID)
//    DWL_COMBOBOX_DOBLECLICK_DERECHO		 ENLACE_ComboBox_Evento_Mouse_DobleClick					ComboBox_Evento_Mouse_DobleClick(const int Boton, const int ID)
//    DWL_COMBOBOX_DOBLECLICK_IZQUIERDO		 ENLACE_ComboBox_Evento_Mouse_DobleClick					ComboBox_Evento_Mouse_DobleClick(const int Boton, const int ID)
//    DWL_COMBOBOX_DOBLECLICK_MEDIO			 ENLACE_ComboBox_Evento_Mouse_DobleClick					ComboBox_Evento_Mouse_DobleClick(const int Boton, const int ID)
//    DWL_COMBOBOX_TECLADO_PRESIONADO		 ENLACE_ComboBox_Evento_Teclado_TeclaPresionada				ComboBox_Evento_Teclado_TeclaPresionada(const int TeclaVirtual, const int ID)
//    DWL_COMBOBOX_TECLADO_SOLTADO			 ENLACE_ComboBox_Evento_Teclado_TeclaSoltada				ComboBox_Evento_Teclado_TeclaSoltada(const int TeclaVirtual, const int ID)
//    DWL_COMBOBOX_TECLADO_INTRO			 ENLACE_ComboBox_Evento_Teclado_Intro						ComboBox_Evento_Teclado_Intro(const int ID)
//    DWL_COMBOBOX_FOCO_OBTENIDO			 ENLACE_ComboBox_Evento_Foco_Obtenido						ComboBox_Evento_Foco_Obtenido(const int ID)
//    DWL_COMBOBOX_FOCO_PERDIDO				 ENLACE_ComboBox_Evento_Foco_Perdido						ComboBox_Evento_Foco_Perdido(const int ID)
