/*! \file DWLEditBox.h
	\brief		Archivo que contiene funciones para la utilización de un editbox en windows.


	\details	Clase diseñada para poder controlar un editbox de windows.																				\n
				Esta clase en breve no formara parte del proyecto y por lo tanto no recibira actualizaciones.											\n
				Si quieres utilizar un control del estilo del edit box con la DWL se recomienda usar DWLEdicionEx										\n
				Para la version 1.0 de la DWL esta clase probablemente desaparecera.																	\n

																																						\n
	\author		devildrey33
	\version	0.95
	\date		20/05/2005

	\remarks
				Archivo creado por devildrey33 el dia [10/03/2004] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

*/

#ifndef DWL_EDITBOX_H
#define DWL_EDITBOX_H

//#include <string>
//#include <commctrl.h>
#include "DWLControl.h"




namespace DWL {
	namespace Controles {
		//! Clase para controlar un EditBox de windows.
        class DWLEditBox : public Base::DWLControl {
		 public : //////////////////// Declaraciones publicas
									//! Constructor
									//  DWLEditBox(void);
									DWLEditBox(void) : _ColorFondo(NULL), _ColorFondoRGB(RGB(0,0,0)), _ColorTexto(RGB(255,255,255)), _Fuente(NULL), _FuentesPropias(false) {
	  								};
									//
									//! Destructor
									// ~DWLEditBox(void);
								   ~DWLEditBox(void) {
										if (_ColorFondo != NULL) DeleteObject(_ColorFondo);
										_ColorFondo = NULL;
									};
									//
									//! Función para crear un control EditBox
									//  void	Crear(const long Estilos, HWND hWndParent, const TCHAR *Text, const int cX, const int cY, const int cAncho, const int cAlto, const int cID);
		 void			            Crear(const long Estilos, HWND hWndParent, const TCHAR *Text, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, HFONT nFuente = NULL) {
										_ColorFondoRGB = GetSysColor(COLOR_WINDOW);
										_ColorTexto = GetSysColor(COLOR_WINDOWTEXT);
										_ColorFondo = GetSysColorBrush(COLOR_WINDOW);
										int NX = cX;
										int NY = cY;
										if (cX == DWL_CENTRADO) NX = _CalcularCentrado(hWndParent, true, cAncho);
										if (cY == DWL_CENTRADO) NY = _CalcularCentrado(hWndParent, false, cAlto);
										_hWnd = CreateWindow(TEXT("EDIT"), Text, Estilos, NX, NY, cAncho, cAlto, hWndParent, reinterpret_cast<HMENU>(IntToPtr(cID)), GetModuleHandle(NULL), NULL);
										ConectarControl();
										if (nFuente == NULL) {
											_Fuente = CreateFont(13, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_ROMAN, TEXT("Tahoma"));
											_FuentesPropias = true;
										}
										else {
											_FuentesPropias = false;
											_Fuente = nFuente;
										}
										SendMessage(_hWnd, WM_SETFONT, (WPARAM)_Fuente , 0);
									};
									//
									//! Función para Asignar el Foco a la ventana
									//  inline virtual void AsignarFoco(void);
		 inline virtual void		AsignarFoco(const bool SeleccionarTodo = false) {
										if (SeleccionarTodo == true) Seleccion(0, -1);
										SetFocus(_hWnd);
									};
									//
									//! Función para asignar un EditBox ya creado en un Dialogo
									//  void Asignar(HWND hWndParent, const int ID_Control);
		 HWND						Asignar(HWND hWndParent, const int ID_Control) {
										_ColorFondoRGB = GetSysColor(COLOR_WINDOW);
//										RECT Medidas;
										_ColorTexto = GetSysColor(COLOR_WINDOWTEXT);
										_ColorFondo = GetSysColorBrush(COLOR_WINDOW);
										_hWnd = GetDlgItem(hWndParent, ID_Control);
										ConectarControl();
//										GetWindowRect(_hWnd, &Medidas);
										_Fuente = (HFONT)SendMessage(_hWnd, WM_GETFONT, 0, 0);
										return _hWnd;
									};
									//
									//! Función para selecionar determinado texto del EditBox
									//  inline void Seleccion(const int Inicio, const int Caracteres);
		 inline void				Seleccion(const int Inicio, const int Caracteres) {
										SetFocus(_hWnd);
										SendMessage(_hWnd, EM_SETSEL, Inicio, Caracteres);
									};
									//
									//! Función para posicionar el cursor del EditBox
									//  inline void PosicionCursor(const int Pos);
		 inline void				PosicionCursor(const int Pos) {
										SetFocus(_hWnd);
										SendMessage(_hWnd, EM_SETSEL, Pos, 0);
									};
									//
									//! Función para Asignar el Maximo de texto que podra tener el EditBox
									//  void MaximoCaracteres(const long Max);
		 inline void				MaximoCaracteres(const long Max) {
										SendMessage(_hWnd, EM_SETLIMITTEXT, Max, 0);
									};
									//
									//! Función para Obtener el Maximo de texto que podra tenet el EditBox
									//  inline const long MaximoTexto(void);
		 inline long			    MaximoCaracteres(void) {
										return static_cast<long>(SendMessage(_hWnd, EM_GETLIMITTEXT, 0, 0));
									};
									//
									//! Función para obtener el texto de una linea del EditBox
									//  void ObtenerLinea(const unsigned int Linea, TCHAR *Txt);
		 void						ObtenerLinea(const unsigned int Linea, TCHAR *Txt, const unsigned int TamTxt) {
//										TCHAR TMP[4096];
										#if defined UNICODE
											Txt[0] = TamTxt;
										#else
											Txt[0] = HIWORD(TamTxt);
											Txt[1] = LOWORD(TamTxt);
										#endif
										SendMessage(_hWnd, EM_GETLINE, Linea, reinterpret_cast<LPARAM>(Txt));
//										DWLString Str = TMP;
//										return Str;
									};
									//
									//! Función para obtener el numero de lineas que tiene el EditBox
									//  inline  int TotalLineas(void);
		 inline int			        TotalLineas(void) {
										return static_cast<int>(SendMessage(_hWnd, EM_GETLINECOUNT, 0, 0));
									};
									//
									//! Función para obtener los caracteres de una linea
									//  inline const int LongitudLinea(const int Linea);
		 inline int			        LongitudLinea(const int Linea) {
										return static_cast<int>(SendMessage(_hWnd, EM_LINELENGTH, Linea, 0));
									};
									//
									//! Función para asignar el caracter del password
									//  inline void CaracterPassword(const TCHAR NC);
		 inline void				CaracterPassword(const TCHAR NC) {
										SendMessage(_hWnd, EM_SETPASSWORDCHAR, NC, 0);
									};
									//
									//! Función para obtener el caracter del password
									//  inline const TCHAR CaracterPassword(void);
		 inline TCHAR			    CaracterPassword(void) {
										return static_cast<TCHAR>(SendMessage(_hWnd, EM_GETPASSWORDCHAR, 0, 0));
									};
									//
									//! Función para reemplzar el texto selecionado en el EditBox por otro
									//  inline void ReemplazarSeleccion(const TCHAR *Txt);
		 inline void				ReemplazarSeleccion(const TCHAR *Txt) {
										SendMessage(_hWnd, EM_REPLACESEL, FALSE, (LPARAM)(LPCSTR)Txt);
									};
									//
									//! Función para asignar el estado SoloLectura
									//  inline void SoloLectura(const bool SL);
		 inline void				SoloLectura(const bool SL) {
										SendMessage(_hWnd, EM_SETREADONLY, SL, 0);
									};
									//
									//! Función para reemplazar el texto del control
									//  inline void AsignarTexto(const TCHAR *Txt);
		 inline void				AsignarTexto(const TCHAR *Txt) {
										SetDlgItemText(GetParent(_hWnd), GetWindowLongPtr(_hWnd, GWL_ID), Txt);
									};
									//
									//! Función que retorna el texto de este control
									//  const TCHAR *Texto(void);
		 void						ObtenerTexto(TCHAR *Txt, const int TamTxt) {
										GetDlgItemText(GetParent(_hWnd), GetWindowLongPtr(_hWnd, GWL_ID), Txt, TamTxt);
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
									//  inline HBRUSH ColorFondo(void)
		 inline COLORREF			ColorFondo(void) {
										return _ColorFondoRGB;
									};
									//
									//! Función para asignar el color del fondo
									//  inline void ColorFondo(HBRUSH nBrocha)
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
											SendMessage(_hWnd, WM_SETFONT, (WPARAM)nFuente , 0);
											if (_FuentesPropias == true) DeleteObject(_Fuente);
											_FuentesPropias = false;
											_Fuente = nFuente;
										}
									};
									//
 									//! Función para destruir el Control EditBox y liberar toda la memoria reservada
									//  const BOOL Destruir(void);
		 BOOL					    Destruir(void) {
                                        BOOL R = DWLControl::Destruir();
										if (_ColorFondo != NULL) DeleteObject(_ColorFondo);
										if (_FuentesPropias == true) DeleteObject(_Fuente);
										_FuentesPropias = false;
										_ColorFondo = NULL;
										return R;
									};
		protected ://///////////////// Declaraciones protegidas (Solo podran usarse en la clase heredada no desde fuera)
									//
									//! Brocha que contendra el color del fondo
		 HBRUSH					   _ColorFondo;
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
									//! Variable que nos dice si el control utiliza fuente propia o del sistema
		 bool					   _FuentesPropias;
									//
									//! Window procedure que reemplazara al WindowProcedure del EditBox
									//  LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
		 LRESULT CALLBACK           GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
										NMHDR T;
										T.hwndFrom = _hWnd;
										T.idFrom = GetWindowLongPtr(_hWnd, GWL_ID);
										switch (uMsg) {
											case WM_CTLCOLOREDIT :   case WM_CTLCOLORSTATIC :
												SetTextColor((HDC)wParam, _ColorTexto);
												SetBkColor((HDC)wParam, _ColorFondoRGB);
												return (LRESULT)_ColorFondo;
											case WM_LBUTTONUP :
												PostMessage(GetParent(_hWnd), DWL_EDITBOX_CLICK_IZQUIERDO, ID(), lParam);
												break;
											case WM_RBUTTONUP :
												PostMessage(GetParent(_hWnd), DWL_EDITBOX_CLICK_DERECHO, ID(), lParam);
												break;
											case WM_MBUTTONUP :
												PostMessage(GetParent(_hWnd), DWL_EDITBOX_CLICK_MEDIO, ID(), lParam);
												break;
											case WM_LBUTTONDBLCLK :
												PostMessage(GetParent(_hWnd), DWL_EDITBOX_DOBLECLICK_IZQUIERDO, ID(), 0);
												break;
											case WM_RBUTTONDBLCLK :
												PostMessage(GetParent(_hWnd), DWL_EDITBOX_DOBLECLICK_DERECHO, ID(), 0);
												break;
											case WM_MBUTTONDBLCLK :
												PostMessage(GetParent(_hWnd), DWL_EDITBOX_DOBLECLICK_MEDIO, ID(), 0);
												break;
											case WM_KEYDOWN :
												PostMessage(GetParent(_hWnd), DWL_EDITBOX_TECLADO_PRESIONADO, wParam, (LPARAM)ID());
												break;
											case WM_KEYUP :
												PostMessage(GetParent(_hWnd), DWL_EDITBOX_TECLADO_SOLTADO, wParam, (LPARAM)ID());
												if (wParam == 13) {
													PostMessage(GetParent(_hWnd), DWL_EDITBOX_TECLADO_INTRO, wParam, (LPARAM)ID());
												}
												break;
											case WM_SETFOCUS :
												PostMessage(GetParent(_hWnd), DWL_EDITBOX_FOCO_OBTENIDO, ID(), 0);
												break;
											case WM_KILLFOCUS :
												PostMessage(GetParent(_hWnd), DWL_EDITBOX_FOCO_PERDIDO, ID(), 0);
												break;
										} 
										return DWLControl::GestorMensajes(uMsg, wParam, lParam);
									};
          private :
                                    // Constructor copia des-habilitado
                                    DWLEditBox(const DWLEditBox &) : _ColorFondo(NULL), _ColorFondoRGB(RGB(0,0,0)), _ColorTexto(RGB(255,255,255)), _Fuente(NULL), _FuentesPropias(false) { }
                                    // Operador = des-habilitado
		 inline DWLEditBox         &operator=(const DWLEditBox &) { return *this; };

		};							//
		////////////////////////////// Final class DWLEditBox;



		//! Clase para controlar un EditBox numerico con decimales de windows.
		class DWLEditBox_Float : public DWLEditBox {
		 public : //////////////////// Miembros publicos
									//
									//! Costructor
									//  DWLEditBox_Float(void);
									DWLEditBox_Float(void) {
									};
									//
									//! Destructor
									// ~DWLEditBox_Float)void);
								   ~DWLEditBox_Float(void) {
									};
									//
									//! Función que retorna el texto como un numero decimal (float)
									//  inline const float ObtenerTexto_Float(void);
		 inline float   			ObtenerTexto_Float(void) {
										TCHAR Txt[512];
										ObtenerTexto(Txt, 512);
										#if defined UNICODE
										    wchar_t **EndPtr = NULL;
											return static_cast<float>(wcstod(Txt, EndPtr));
										#else
											return static_cast<float>(atof(Txt));
										#endif
									};
		 protected: ////////////////// Miembros protegidos
									//
									//! Window procedure que reemplazara al WindowProcedure del EditBox
									//  LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
		 LRESULT CALLBACK           GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
										TCHAR Caracter;
										switch (uMsg) {
											case WM_CHAR :
												Caracter = static_cast<TCHAR>(wParam);
												switch (Caracter) {
													case TEXT('0') :	case TEXT('1') :	case TEXT('2') :	case TEXT('3') :
													case TEXT('4') :	case TEXT('5') :	case TEXT('6') :	case TEXT('7') :
													case TEXT('8') :	case TEXT('9') :	case TEXT('.') :	case 8	:
													case VK_TAB :
														break;
													case TEXT(',') :
														wParam = TEXT('.');
														break;
													default :
														return 0;
												}
												break;
										}
										return DWLEditBox::GestorMensajes(uMsg, wParam, lParam);
									};
		}; /////////////////////////// Fin class DWLEditBox_Float;



		//! Clase para controlar un EditBox numerico de windows.
		class DWLEditBox_Int : public DWLEditBox {
		 public : ////////////////////
									//! Constructor
									//  DWLEditBox_Int(void);
									DWLEditBox_Int(void) {
									};
									//
									//! Destructor
									// ~DWLEditBox_Int(void);
								   ~DWLEditBox_Int(void) {
									};
								    //
								    //! Función que retorna el texto como un numero entero (int)
									//  inline const int ObtenerTexto_Int(void);
		 inline int			        ObtenerTexto_Int(void) {
										TCHAR Txt[512];
										ObtenerTexto(Txt, 512);
										#if defined UNICODE
											return _wtoi(Txt);
										#else
											return atoi(Txt);
										#endif
									};
		 protected: ////////////////// Miembros protegidos
									//
									//! Window procedure que reemplazara al WindowProcedure del EditBox
									//  LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
		 LRESULT CALLBACK           GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
										TCHAR Caracter;
										switch (uMsg) {
											case WM_CHAR :
												Caracter = static_cast<TCHAR>(wParam);
												switch (Caracter) {
													case TEXT('0') :	case TEXT('1') :	case TEXT('2') :	case TEXT('3') :
													case TEXT('4') :	case TEXT('5') :	case TEXT('6') :	case TEXT('7') :
													case TEXT('8') :	case TEXT('9') :	case 8	:
													case VK_TAB :
														break;
													default :
														return 0;
												}
												break;
										}
										return DWLEditBox::GestorMensajes(uMsg, wParam, lParam);
									};
		}; /////////////////////////// Fin class DWLEditBox_Int;


	}
}

#endif // DWL_EDITBOX_H

// Ver 0.9a
// -Se ha solucionado un bug con los EditBox en Multilinea que no repintaba bien el scroll. (Gracias a cofuben por encontrar este error)
// -El codigo ha sido modificado para poder editarlo mejor



// Version 0.95
// -Se han eliminado todas las macros que empezaban por On.
//  Haora existen nuevas macros que empiezan por ENLACE_
// -Se han eliminado las notificaciones estandard que retornaba este control
//  Haora este control retorna sus propios mensajes :
//   -Mensaje								-Macro
//    DWL_EDITBOX_CLICK_DERECHO				 ENLACE_EditBox_Evento_Mouse_Click
//    DWL_EDITBOX_CLICK_IZQUIERDO			 ENLACE_EditBox_Evento_Mouse_Click
//    DWL_EDITBOX_CLICK_MEDIO				 ENLACE_EditBox_Evento_Mouse_Click
//    DWL_EDITBOX_DOBLECLICK_DERECHO		 ENLACE_EditBox_Evento_Mouse_DobleClick
//    DWL_EDITBOX_DOBLECLICK_IZQUIERDO		 ENLACE_EditBox_Evento_Mouse_DobleClick
//    DWL_EDITBOX_DOBLECLICK_MEDIO			 ENLACE_EditBox_Evento_Mouse_DobleClick
//    DWL_EDITBOX_TECLADO_PRESIONADO		 ENLACE_EditBox_Evento_Teclado_TeclaPresionada
//    DWL_EDITBOX_TECLADO_SOLTADO			 ENLACE_EditBox_Evento_Teclado_TeclaSoltada
//    DWL_EDITBOX_TECLADO_INTRO				 ENLACE_EditBox_Evento_Teclado_Intro
//    DWL_EDITBOX_FOCO_OBTENIDO				 ENLACE_EditBox_Evento_Foco_Obtenido
//    DWL_EDITBOX_FOCO_PERDIDO				 ENLACE_EditBox_Evento_Foco_Perdido
