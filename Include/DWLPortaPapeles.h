/////////////////////////////////////////////////////////////////////////////////////////////////
// Esta clase han sido creada por [\DReY\] el dia 08/03/2006 y es uno de los ejemplos de       //
// http://www.webpersonal.net/devildrey33 (DReY Visual C++ page)                               //
// Puedes modificar esta clase a tu gusto. Si realizas alguna modificacion que creas que es    //
// mejor para esta clase porfavor mandamela por e-mail para que pueda verla :)                 // 
// E-Mail & MSN Messenger : devildrey33@hotmail.com                                            //
//                                                                                             //
// Version 0.5                                                                                 //
// Ultima modificación : 08/03/2006                                                            //
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef DWL_CLASEPORTAPAPELES_H
#define DWL_CLASEPORTAPAPELES_H
 
#include "DWLString.h"

namespace DWL {
	namespace SO {
		class DWLPortaPapeles {
		public: ////////////////// Miembros publicos
								//
								// Constructor
								// DWLPortaPapeles(void);
								DWLPortaPapeles(void) {
									//OleInitialize(NULL);
								};
								//
								// Destructor
								// ~ClasePortapapeles(void);
							   ~DWLPortaPapeles(void) {
									//OleUninitialize();
								};
								// 	
								// Función que retorna el texto del porta papeles (hWnd no puede ser NULL)
								// static DWLString &ObtenerTexto(HWND hWndPaste);
		 static DWLString      &ObtenerTexto(HWND hWndPaste) {
									HGLOBAL				Paste = NULL;
									LPTSTR				Str = NULL;
									static DWLString    Txt;
									if (OpenClipboard(hWndPaste) == TRUE) {
										#if defined UNICODE
											Paste = GetClipboardData(CF_UNICODETEXT);
										#else
											Paste = GetClipboardData(CF_TEXT);
										#endif
										//DWLDebug::MostrarUltimoError();
										if (Paste != NULL) {
											Str = static_cast<LPTSTR>(GlobalLock(Paste));
											if (Str == NULL) return Txt;
											Txt = Str;
											GlobalUnlock(Paste);
										}
										CloseClipboard();
									}
									return Txt;
							    };
								// 	
								// Función para asignar texto al porta papeles
								// static void AsignarTexto(const TCHAR *nTexto);
		/* static void		    AsignarTexto(const TCHAR *nTexto) {
									if (nTexto == NULL) return;
									int Len = DWLStrLen(nTexto) + 1;
									if (Len == 0) return;
									if (OpenClipboard(NULL) == TRUE) {
										HGLOBAL Copy = GlobalAlloc(GMEM_MOVEABLE, Len * sizeof(TCHAR)); 
										LPTSTR  Str  = NULL;
										if (Copy != NULL) { 
											Str = static_cast<LPTSTR>(GlobalLock(Copy)); 
											//memcpy(Str, &nTexto[0], (Len - 1) * sizeof(TCHAR)); 
											if (Str != NULL) {
												memcpy(Str, nTexto, (Len - 1) * sizeof(TCHAR)); 
												Str[Len - 1] = static_cast<TCHAR>(0);
												GlobalUnlock(Copy);  
												EmptyClipboard();
												#if defined UNICODE
													SetClipboardData(CF_UNICODETEXT, Copy); 
												#else
													SetClipboardData(CF_TEXT, Copy); 
												#endif			
												CloseClipboard();
											}
										}
									}
								};			*/				
								// 	
								// Función para asignar texto al porta papeles
								// static void AsignarTexto(const TCHAR *nTexto);
		 static void		    AsignarTexto(const TCHAR *nTexto) {
									if (nTexto == NULL) return;
									int Len = DWLStrLen(nTexto) + 1;
									if (Len == 0) return;
									if (OpenClipboard(NULL) == TRUE) {
										HGLOBAL Copy = GlobalAlloc(GMEM_MOVEABLE, Len * sizeof(TCHAR)); 
										LPTSTR  Str  = NULL;
										if (Copy) { 
											Str = static_cast<LPTSTR>(GlobalLock(Copy)); 
											//memcpy(Str, &nTexto[0], (Len - 1) * sizeof(TCHAR)); 
											if (Str) {
												wcscpy_s(Str, Len, nTexto);
//												memcpy(Str, nTexto, (Len - 1) * sizeof(TCHAR)); 
												Str[Len - 1] = static_cast<TCHAR>(0);
												GlobalUnlock(Copy);  
												EmptyClipboard();
												#if defined UNICODE
													SetClipboardData(CF_UNICODETEXT, Copy); 
												#else
													SetClipboardData(CF_TEXT, Copy); 
												#endif			
												CloseClipboard();
											}
										}
									}
								};
		};						//
		//////////////////////////
	}
}

#endif // DWL_CLASEPORTAPAPELES_H
