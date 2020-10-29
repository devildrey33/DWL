// Modulo que contiene la clase DWLhDC que es un derivado del objeto HDC de windows.
// Esta clase se ha creado pensando en facilitar la vida al programador, por ello incluye Funciónes para interactuar con varios objetos.
// Ademas esta clase nos permite crear region a partir de imagenes BMP, guardar regiones al disco, y cargar regiones del disco.
// Ultima modificación 28/04/2009
// Version 1.0


// TINC 2 FUNCIONS PER CALCULAR EL TAMANY DEL TEXTE DIFERENTS AMB NOMS DIFERENTS!!!!

#ifndef DWL_GDI_HDC_H
#define DWL_GDI_HDC_H

#include "DWLEnumsGDI.h"

namespace DWL { 
	namespace GDI {

		class DWLRecta;		// DWLRecta		(Clase para manipular RECT)
		class DWLRegion;	// DWLRegion	(Clase para manipular HRGN)
		class DWLBrocha;	// DWLBrocha	(Clase para manipular HBRUSH)
		class DWLPluma;		// DWLPluma		(Clase para manipular HPEN)
		class DWLMapaBits;	// DWLMapaBits	(Clase para manipular HBITMAP)
		class DWLFuente;	// DWLFuente	(Clase para manipular HFONT)
		class DWLIcono;		// DWLIcono		(Clase para manipular HICON)
		class DWLColor;		// DWLColor		(Clase para manipular COLORREF)
//		class DWLhDC;		// DWLhDC		(Clase para manipular HDC)

		// Clase para usar objetos de tipo HDC
		class DWLhDC {
		public : ///////////// Miembros publicos
							//
							// Constructor (No crea nada)
							// DWLhDC(void);
							DWLhDC(void) : _hWndVentana(NULL), _VBrocha(NULL), _VPluma(NULL), _VFuente(NULL), _MapaBits(NULL), _hDC(NULL), _VMapaBits(NULL), _Eliminable(true) {
							};
							//
							// Constructor para obtener el DC de la ventana
							// DWLhDC(HWND hWndVentana);
							DWLhDC(HWND hWndVentana) : _hWndVentana(NULL), _VBrocha(NULL), _VPluma(NULL), _VFuente(NULL), _MapaBits(NULL), _hDC(NULL), _VMapaBits(NULL), _Eliminable(true) {
								_hDC = GetDC(hWndVentana);
							};
							//
							// Constructor para asignar el DC a esta clase (Este no se borrara automaticamente)
							// DWLhDC(HDC hDC);
							DWLhDC(HDC hDC) : _hWndVentana(NULL), _VBrocha(NULL), _VPluma(NULL), _VFuente(NULL), _MapaBits(NULL), _hDC(NULL), _VMapaBits(NULL), _Eliminable(false) {
								Borrar();
								_hDC        = hDC;
								_Eliminable = false;
							};
							//
							// Constructor para crear un DC compatible
							// DWLhDC(HDC hDC, const int Ancho, const int Alto);
							DWLhDC(HDC hDC, const int Ancho, const int Alto) : _hWndVentana(NULL), _VBrocha(NULL), _VPluma(NULL), _VFuente(NULL), _MapaBits(NULL), _hDC(NULL), _VMapaBits(NULL), _Eliminable(true) {
								_hDC         = CreateCompatibleDC(hDC);
								_MapaBits    = CreateCompatibleBitmap(hDC, Ancho, Alto);
								_VMapaBits   = static_cast<HBITMAP>(SelectObject(_hDC, _MapaBits));
							};
							//
							// Constructor para crear un DC compatible
							// DWLhDC(DWLhDC *hDC, const int Ancho, const int Alto);
							DWLhDC(DWLhDC *hDC, const int Ancho, const int Alto) : _hWndVentana(NULL), _VBrocha(NULL), _VPluma(NULL), _VFuente(NULL), _MapaBits(NULL), _hDC(NULL), _VMapaBits(NULL), _Eliminable(true) {
								_hDC         = CreateCompatibleDC(hDC->hDC());
								_MapaBits    = CreateCompatibleBitmap(hDC->hDC(), Ancho, Alto);
								_VMapaBits   = static_cast<HBITMAP>(SelectObject(_hDC, _MapaBits));
							};
							//
							// Constructor para cargar un BMP del disco duro
							// DWLhDC(const TCHAR *Archivo)
							DWLhDC(const TCHAR *Archivo) : _hWndVentana(NULL), _VBrocha(NULL), _VPluma(NULL), _VFuente(NULL), _MapaBits(NULL), _hDC(NULL), _VMapaBits(NULL), _Eliminable(true) {
								_MapaBits    = static_cast<HBITMAP>(LoadImage(GetModuleHandle(NULL), Archivo, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
								_hDC         = CreateCompatibleDC(NULL);
								_VMapaBits   = static_cast<HBITMAP>(SelectObject(_hDC, _MapaBits));
							};
							//
							// Destructor
							// ~DWLhDC(void);
						   ~DWLhDC(void) {
								Borrar();
						    };
						    //
							// Función para asignar un DC a esta clase
							// NOTA : Cualquier DC que le pases deberas eliminarlo tu mas tarde (si el sistema no lo hace).
							//        Esto es debido a que algunos mensajes como el WM_ERASEBKGRND nos pasan un DC que
							//        luego borra el mismo mensaje con lo qual no debo borrarlo con esta clase.
						    // inline void AsignarDC(HDC hDC);
 	     inline void		AsignarDC(HDC hDC) {
							   Borrar();
							   _hDC = hDC;
							   _Eliminable = false;
							};
							//
							// Función para obtener un DC partiendo de un hWnd (GetDC)
							// inline void ObtenerDC(HWND hWnd);
		 inline void		ObtenerDC(HWND hWnd) {
								Borrar();
								_hDC = GetDC(hWnd);
								_hWndVentana = hWnd;
								_Eliminable = true;
							};
							//
							// Función que crea un DC compatible con el especificado. Tambien crea un HBITMAP compatible.
							// inline void CrearCompatibleDCBMP(HDC hDC, const int Ancho, const int Alto);
		 inline void		CrearCompatibleDCBMP(HDC hDC, const int Ancho, const int Alto) {
								Borrar();
								_hDC = CreateCompatibleDC(hDC);
								_MapaBits = CreateCompatibleBitmap(hDC, Ancho, Alto);
								_VMapaBits = static_cast<HBITMAP>(SelectObject(_hDC, _MapaBits));
								_Eliminable = true;
							};
							//
							// Función que crea un DC compatible con el especificado. Tambien crea un HBITMAP compatible.
							// inline void CrearCompatibleDCBMP(DWLhDC *hDC, const int Ancho, const int Alto);
		 inline void		CrearCompatibleDCBMP(DWLhDC *hDC, const int Ancho, const int Alto) {
								Borrar();
								_hDC = CreateCompatibleDC(hDC->hDC());
								_MapaBits = CreateCompatibleBitmap(hDC->hDC(), Ancho, Alto);
								_VMapaBits = static_cast<HBITMAP>(SelectObject(_hDC, _MapaBits));
								_Eliminable = true;
							};
							//
							// Función para pintar un RECT usado un HBRUSH
							// inline void PintarRecta(RECT *Recta, HBRUSH Brocha);
		 inline void		PintarRecta(RECT *Recta, HBRUSH Brocha) {
								FillRect(_hDC, Recta, Brocha);
							};
							//
							// Función para pintar un RECT usado un HBRUSH
							// inline void PintarRectaRedondeada(const int cX, const int cY, const int cAncho, const int cAlto, const int xFact, const int yFact, HBRUSH Brocha);
		 inline void		PintarRectaRedondeada(const int cX, const int cY, const int cAncho, const int cAlto, const int xFact, const int yFact, HBRUSH Brocha) {
								HBRUSH Viejo = static_cast<HBRUSH>(SelectObject(_hDC, Brocha));
								RoundRect(_hDC, cX, cY, cAncho, cAlto, xFact, yFact);
								SelectObject(_hDC, Viejo);
							};
							//
							// Función para pintar el bordede un RECT usando un HBRUSH
							// inline void EnmarcarRecta(RECT *Recta, HBRUSH Brocha);
		 inline void		EnmarcarRecta(RECT *Recta, HBRUSH Brocha) {
								FrameRect(_hDC, Recta, Brocha);
							};
							//
							// Función para pintar el HRNG usando un HBRUSH
							// inline void PintarRegion(HRGN Region, HBRUSH Brocha);
		 inline void		PintarRegion(HRGN Region, HBRUSH Brocha) {
								FillRgn(_hDC, Region, Brocha);
							};
							//
							// Función para pintar el borde del RECT usando un HBRUSH
							// inline void EnmarcarRegion(HRGN Region, HBRUSH Brocha, const int TamAlto, const int TamAncho);
		 inline void		EnmarcarRegion(HRGN Region, HBRUSH Brocha, const int TamAlto, const int TamAncho) {
								FrameRgn(_hDC, Region, Brocha, TamAlto, TamAncho);
							};
/*							//
							// Función para pintar una linea usando un HPEN que no es el seleccionado
							// inline void PintarLinea(HPEN nPluma, const int X, const int Y, const int X2, const int Y2)
		 inline void		PintarLinea(HPEN nPluma, const int X, const int Y, const int X2, const int Y2) {
								HPEN Viejo = NULL;
								if (nPluma != static_cast<HPEN>(GetCurrentObject(_hDC, OBJ_PEN))) {
									Viejo = static_cast<HPEN>(SelectObject(_hDC, nPluma));
								}
								MoveToEx(_hDC, X, Y, NULL);
								LineTo(_hDC, X2, Y2);
								if (Viejo != NULL) SelectObject(_hDC, Viejo);
							};*/
							//
							// Función para pintar una linea usando la Puluma selecionada en el DC
							// inline void PintarLinea(const int X, const int Y, const int X2, const int Y2);
		 inline void		PintarLinea(const int X, const int Y, const int X2, const int Y2) {
								MoveToEx(_hDC, X, Y, NULL);
								LineTo(_hDC, X2, Y2);
							};
							//
							// Función para pintar texto en las coordenadas especificadas usando la Fuente, Color y ModoBk actuales.
							// NOTAS :  - Esta Función utiliza TextOut internamente.
							//			- No puedes utilizar cadenas multilinea.
							// inline void PintarTexto(const TCHAR *Texto, const int X, const int Y);
		 inline void		PintarTexto(const TCHAR *Texto, const int X, const int Y) {
								TextOut(_hDC, X, Y, Texto, static_cast<int>(DWLStrLen(Texto)));
							};
							//
							// Función para pintar texto en las coordenadas especificadas, con un tope de ancho y alto.
							// NOTAS :  - Esta Función utiliza internamente DrawText para pintar el texto.
							//			- Puedes utilizar cadenas con varias lineas.
							// inline void PintarTexto(const TCHAR *cTexto, const int cX, const int cY, const int cAncho, const int cAlto, UINT cFormato = DT_LEFT | DT_NOPREFIX);
		 inline void		PintarTexto(const TCHAR *cTexto, const int cX, const int cY, const int cAncho, const int cAlto, UINT cFormato = DT_LEFT | DT_NOPREFIX) {
								RECT R = { cX, cY, cAncho, cAlto };
								DrawText(_hDC, cTexto, static_cast<int>(DWLStrLen(cTexto)), &R, cFormato);
							};
							//
							// Función para pintar texto en las coordenadas especificadas, con un tope de ancho y alto.
							// NOTAS :  - Esta Función utiliza internamente DrawText para pintar el texto.
							//			- Puedes utilizar cadenas con varias lineas.
							// inline void PintarTexto(const TCHAR *cTexto, RECT *Espacio, UINT cFormato = DT_LEFT | DT_NOPREFIX);
		 inline void		PintarTexto(const TCHAR *cTexto, RECT *Espacio, UINT cFormato = DT_LEFT | DT_NOPREFIX) {
								DrawText(_hDC, cTexto, static_cast<int>(DWLStrLen(cTexto)), Espacio, cFormato);
							};
							//
							// Función para pintar el texto centrado partiendo de un RECT
							// NOTAS :  - Esta Función utiliza internamente DrawText para pintar el texto.
							//			- Puedes utilizar cadenas con varias lineas.
							//			- Para que el texto se centre debes especificar el valor DT_CENTER dentro de cFormato.
							// inline void PintarTextoCentrado(const TCHAR *Texto, RECT *R, UINT cFormato = DT_CENTER | DT_NOPREFIX);
		 inline void		PintarTextoCentrado(const TCHAR *Texto, RECT *R, UINT cFormato = DT_CENTER | DT_NOPREFIX) {
								DrawText(_hDC, Texto, static_cast<int>(DWLStrLen(Texto)), R, cFormato);
							};
							//
							// Función para pintar el texto centrado en el espacio designado.
							// NOTAS :  - Esta Función utiliza internamente DrawText para pintar el texto.
							//			- Puedes utilizar cadenas con varias lineas.
							//			- Para que el texto se centre debes especificar el valor DT_CENTER dentro de cFormato.
							// inline void PintarTextoCentrado(const TCHAR *cTexto, const int cX, const int cY, const int cAncho, const int cAlto, UINT cFormato = DT_CENTER | DT_NOPREFIX);
		 inline void		PintarTextoCentrado(const TCHAR *cTexto, const int cX, const int cY, const int cAncho, const int cAlto, UINT cFormato = DT_CENTER | DT_NOPREFIX) {
								RECT R = { cX, cY, cAncho, cAlto };
								DrawText(_hDC, cTexto, static_cast<int>(DWLStrLen(cTexto)), &R, cFormato);
							};
							//
							// Función para pintar este DWLhDC en un hDC Destino usando un RECT para las coordenadas de destino
							// inline void PintarMapaBits(HDC hDCDest, RECT *Recta, const int ScrX, const int ScrY, DWORD Flag = SRCCOPY);
		 inline void		PintarMapaBits(HDC hDCDest, RECT *Recta, const int ScrX, const int ScrY, DWORD Flag = SRCCOPY) {
								BitBlt(hDCDest, Recta->left, Recta->top, Recta->right, Recta->bottom, _hDC, ScrX, ScrY, Flag);
							};
							//
							// Función para pintar este DWLhDC en un hDC Destino.
							// inline void PintarMapaBits(HDC hDCDest, const int X, const int Y, const int Ancho, const int Alto, const int SrcX, const int SrcY, DWORD Flag = SRCCOPY);
		 inline void		PintarMapaBits(HDC hDCDest, const int X, const int Y, const int Ancho, const int Alto, const int SrcX, const int SrcY, DWORD Flag = SRCCOPY) {
								BitBlt(hDCDest, X, Y, Ancho, Alto, _hDC, SrcX, SrcY, Flag);
							};
							//
							// Función para pintar este DWLhDC en un DWLhDC Destino.
							// inline void PintarMapaBits(DWLhDC *hDCDest, const int X, const int Y, const int Ancho, const int Alto, const int SrcX, const int SrcY, DWORD Flag = SRCCOPY);
		 inline void		PintarMapaBits(DWLhDC *hDCDest, const int X, const int Y, const int Ancho, const int Alto, const int SrcX, const int SrcY, DWORD Flag = SRCCOPY) {
								BitBlt(hDCDest->hDC(), X, Y, Ancho, Alto, _hDC, SrcX, SrcY, Flag);
							};
							//
							// Función para pintar el DWLhDC en otro hDC de forma que se vea translucido
							// inline void PintarMapaBitsTranslucido(HDC hDCDest, const int DestX, const int DestY, const int DestAncho, const int DestAlto, const int SrcX, const int SrcY, const int SrcAncho, const int SrcAlto, const BYTE Transparencia);
		 inline void		PintarMapaBitsTranslucido(HDC hDCDest, const int DestX, const int DestY, const int DestAncho, const int DestAlto, const int SrcX, const int SrcY, const int SrcAncho, const int SrcAlto, const BYTE Transparencia) {
								BLENDFUNCTION BF;
								BF.AlphaFormat			= 0;
								BF.BlendOp				= 0;
								BF.BlendFlags			= 0;
								BF.SourceConstantAlpha	= Transparencia;
								AlphaBlend(hDCDest, DestX, DestY, DestAncho, DestAlto, _hDC, SrcX, SrcY, SrcAncho, SrcAlto, BF);
							};
							//
							// Función para pintar el DWLhDC en otro DWLhDC de forma que se vea translucido
							// inline void PintarMapaBitsTranslucido(DWLhDC *hDCDest, const int DestX, const int DestY, const int DestAncho, const int DestAlto, const int SrcX, const int SrcY, const int SrcAncho, const int SrcAlto, const BYTE Transparencia);
		 inline void		PintarMapaBitsTranslucido(DWLhDC &hDCDest, const int DestX, const int DestY, const int DestAncho, const int DestAlto, const int SrcX, const int SrcY, const int SrcAncho, const int SrcAlto, const BYTE Transparencia) {
								BLENDFUNCTION BF;
								BF.AlphaFormat			= 0;
								BF.BlendOp				= 0;
								BF.BlendFlags			= 0;
								BF.SourceConstantAlpha	= Transparencia;
								AlphaBlend(hDCDest(), DestX, DestY, DestAncho, DestAlto, _hDC, SrcX, SrcY, SrcAncho, SrcAlto, BF);
							};
							//
							// Función para pintar un icono partiendo de su id de los recursos.
							// NOTA :  - Esta Función carga, pinta y elimina el icono de memoria internamente.
							// inline void PintarIcono(const int X, const int Y, const int Ancho, const int Alto, const int IDResIko);
		 inline void		PintarIcono(const int X, const int Y, const int Ancho, const int Alto, const int IDResIko) {
								HICON Iko = static_cast<HICON>(LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDResIko), IMAGE_ICON, Ancho, Alto, LR_DEFAULTCOLOR));
								DrawIconEx(_hDC, X, Y, Iko, Ancho, Alto, 0, 0, DI_NORMAL);
								DestroyIcon(Iko);
							};
							//
							// Función para pintar un icono utilizando un HICON
							// inline void PintarIcono(const int X, const int Y, const int Ancho, const int Alto, HICON Iko);
		 inline void		PintarIcono(const int X, const int Y, const int Ancho, const int Alto, HICON Iko) {
								DrawIconEx(_hDC, X, Y, Iko, Ancho, Alto, 0, 0, DI_NORMAL);
							};
							//
							// Función para cargar el estado del DC previamente guardado
							// inline BOOL RestaurarDC(int EstadoDC);
		 inline BOOL		RestaurarDC(int EstadoDC) {
								return RestoreDC(_hDC, EstadoDC);
							};
							//
							// Función para guardar el estado del DC
							// inline int GuardarDC(void);
		 inline int			GuardarDC(void) {
								return SaveDC(_hDC);
							};
							//
							// Función para obtener el color del fondo (Texto)
							// inline COLORREF ColorFondo(void);
		 inline COLORREF	ColorFondo(void) {
								return GetBkColor(_hDC);
							};
							//
							// Función para asignar el color del fondo (Texto)
							// inline COLORREF ColorFondo(COLORREF Color);
		 inline COLORREF	ColorFondo(COLORREF Color) {
								return SetBkColor(_hDC, Color);
							};
							//
							// Función para obtener el color del texto
							// inline COLORREF ColorTexto(void);
		 inline COLORREF	ColorTexto(void) {
								return GetTextColor(_hDC);
							};
							//
							// Función para asignar el color del texto
							// inline COLORREF ColorTexto(COLORREF Color);
		 inline COLORREF	ColorTexto(COLORREF Color) {
								return SetTextColor(_hDC, Color);
							};
							//
							// Función para obtener el modo del fondo (Opaco / Transparente)
							// inline int ModoBk(void);
		 inline int			ModoBk(void) {
								return GetBkMode(_hDC);
							};
							//
							// Función para asignar el modo del fondo (Opaco / Transparente)
							// inline int ModoBk(int Modo);
		 inline int			ModoBk(int Modo) {
								return SetBkMode(_hDC, Modo);
							};
							//
							// Función para obtener el color del pixel en las coordenadas especificadas.
							// inline COLORREF Pixel(const int X, const int Y);
		 inline COLORREF	Pixel(const int X, const int Y) {
								return GetPixel(_hDC, X, Y);
							};
							//
							// Función para obtener el color del pixel en e POINT especificado.
							// inline COLORREF Pixel(POINT Punto);
		 inline COLORREF	Pixel(POINT Punto) {
								return GetPixel(_hDC, Punto.x, Punto.y);
							};
							//
							// Función para asignar el color del pixel en las coordenadas especificadas.
							// inline COLORREF Pixel(const int X, const int Y, COLORREF Color);
		 inline COLORREF	Pixel(const int X, const int Y, COLORREF Color) {
								return SetPixel(_hDC, X, Y, Color);
							};
							//
							// Función para asignar el color del pixel en el POINT espcificado.
							// inline COLORREF Pixel(POINT Punto, COLORREF Color);
		 inline COLORREF	Pixel(POINT Punto, COLORREF Color) {
								return SetPixel(_hDC, Punto.x, Punto.y, Color);
							};
							//
							// Función para obtener el tamaño del ancho en pixeles del texto
							// inline long ObtenerAnchoTexto(const TCHAR *Txt);
		 inline long		ObtenerAnchoTexto(const TCHAR *Txt) {
								SIZE R;
								GetTextExtentPoint32(_hDC, Txt, static_cast<int>(DWLStrLen(Txt)), &R);
								return R.cx;
							};
							//
							// Función para obtener el tamaño de la altura en pixeles del texto
							// inline long ObtenerAltoTexto(const TCHAR *Txt);
		 inline long		ObtenerAltoTexto(const TCHAR *Txt) {
								SIZE R;
								GetTextExtentPoint32(_hDC, Txt, static_cast<int>(DWLStrLen(Txt)), &R);
								return R.cy;
							};
							//
							// Función para obtener el tamaño en pixeles del texto
							// inline void ObtenerTamTexto(const TCHAR *Txt, SIZE *Tam);
		 inline void		ObtenerTamTexto(const TCHAR *Txt, SIZE *Tam) {
								GetTextExtentPoint32(_hDC, Txt, static_cast<int>(DWLStrLen(Txt)), Tam);
							};
							//
							// Función para selecionar un HBRUSH en el DC
							// inline void Brocha(HBRUSH Brocha);
		 inline void		Brocha(HBRUSH Brocha) {
								if (Brocha == NULL) {
									SelectObject(_hDC, _VBrocha);
									_VBrocha = NULL;
								}
								else {
									_VBrocha = static_cast<HBRUSH>(SelectObject(_hDC, Brocha));
								}
							};
							//
							// Función que retorna la brocha selecionada actualmente en el DC
							// inline HBRUSH Brocha(void);
		 inline HBRUSH		Brocha(void) {
								return static_cast<HBRUSH>(GetCurrentObject(_hDC, OBJ_BRUSH));
							};
							//
							// Función para selecionar un HBITMAP en el DC
							// NOTA :  - Si se usa NULL en MapaBits, se asigna el HBITMAP que se crea por defecto con el DC.
							// inline void MapaBits(HBITMAP MapaBits);
		 inline void		MapaBits(HBITMAP MapaBits) {
								if (MapaBits == NULL) {
									SelectObject(_hDC, _VMapaBits);
									_VMapaBits = NULL;
								}
								else {
									_VMapaBits = static_cast<HBITMAP>(SelectObject(_hDC, MapaBits));
								}
							};
							//
							// Función que retorna el HBITMAP selecionado actualmente en el DC
							// inline HBITMAP MapaBits(void);
		 inline HBITMAP		MapaBits(void) {
								return static_cast<HBITMAP>(GetCurrentObject(_hDC, OBJ_BITMAP));
							};
							//
							// Función para selecionar un HFONT en el DC
							// NOTA :  - Si se usa NULL en nFuente, se asigna la fuente por defecto que se crea con el DC.
							// inline void Fuente(HFONT nFuente);
		 inline void		Fuente(HFONT nFuente) {
								if (nFuente == NULL) {
									SelectObject(_hDC, _VFuente);
									_VFuente = NULL;
								}
								else {
									_VFuente = static_cast<HFONT>(SelectObject(_hDC, nFuente));
								}
							};
							//
							// Función que retorna el HFONT que esta actualmente selecionado en el DC
							// inline HFONT Fuente(void);
		 inline HFONT		Fuente(void) {
								return static_cast<HFONT>(GetCurrentObject(_hDC, OBJ_FONT));
							};
							//
							// Función para selecionar un HPEN en el DC
							// NOTA :  - Si se utiliza NULL en nPluma, se asigna la pluma que se crea por defecto con el DC.
		 inline void		Pluma(HPEN nPluma) {
								if (nPluma == NULL) {
									SelectObject(_hDC, _VPluma);
									_VPluma = NULL;
								}
								else {
									_VPluma = static_cast<HPEN>(SelectObject(_hDC, nPluma));
								}
							};
							//
							// Función que retorna el HPEN actualmente selecionado en el DC
							// inline HPEN Pluma(void);
		 inline HPEN		Pluma(void) {
								return static_cast<HPEN>(GetCurrentObject(_hDC, OBJ_PEN));
							};
							//
							// Función que retorna el hDC de esta clase
							// inline HDC hDC(void);
		 inline HDC			hDC(void) {
								return _hDC;
							};
							//
							// Función que retorna el Mapa de Bits compatible creado en un DC Compatible
							// inline HBITMAP MapaBitsCompatible(void);
		 inline HBITMAP		MapaBitsCompatible(void) {
								return _MapaBits;
							};
							//
							// Desseleciona todos sus objetos y luego borra/libera el DC si es necesario
							// inline void Borrar(void);
		 void		        Borrar(void) {
								if (_hDC != NULL) {
									if (_VPluma != NULL) 	SelectObject(_hDC, _VPluma);
									if (_VBrocha != NULL)   SelectObject(_hDC, _VBrocha);
									if (_VFuente != NULL)	SelectObject(_hDC, _VFuente);
									if (_VMapaBits != NULL)	SelectObject(_hDC, _VMapaBits);
									if (_MapaBits != NULL)	DeleteObject(_MapaBits);
									if (_Eliminable == true) {
										if (_hWndVentana != NULL)	ReleaseDC(_hWndVentana, _hDC);
										else						DeleteDC(_hDC);
									}
								}
								_hDC			= NULL;
								_Eliminable	= false;
								_VPluma		= NULL;
								_VBrocha		= NULL;
								_VMapaBits		= NULL;
								_MapaBits		= NULL;
								_hWndVentana	= NULL;
							};
							//
							// Operador que retorna el hDC interno
							// inline HDC operator () (void);
		 inline HDC			operator () (void) {
								return _hDC;
							};
							//
							// Funion para pintar una  clase DWLRecta usando una clase DWLBrocha
							// void PintarRecta(DWLRecta *Recta, DWLBrocha *Brocha);
		 void				PintarRecta(DWLRecta *Recta, DWLBrocha *Brocha);
							//
							// Funion para pintar una recta redondeada usando una Brocha
							// void PintarRectaRedondeada(const int cX, const int cY, const int cAncho, const int cAlto, const int xFact, const int yFact, DWLBrocha *Brocha);
		 void				PintarRectaRedondeada(const int cX, const int cY, const int cAncho, const int cAlto, const int xFact, const int yFact, DWLBrocha *Brocha);
							//
							// Función para pintar el botde de la clase DWLRecta usando una clase DWLBrocha
							// int EnmarcarRecta(DWLRecta *Recta, DWLBrocha *Brocha);
		 int				EnmarcarRecta(DWLRecta *Recta, DWLBrocha *Brocha);
							//
							// Función para pintar la clase DWLRegion usando una clase DBricha
							// void PintarRegion(DWLRegion *Region, DWLBrocha *Brocha);
		 void				PintarRegion(DWLRegion *Region, DWLBrocha *Brocha);
							//
							// Función para pintar el borde de la clase DWLRecta usando una clase DWLBrocha
							// void EnmarcarRegion(DWLRegion *Region, DWLBrocha *Brocha, const int TamAlto, const int TamAncho);
		 void				EnmarcarRegion(DWLRegion *Region, DWLBrocha *Brocha, const int TamAlto, const int TamAncho);
							//
							// Función para pintar texto partiendo de una clase DWLRecta
							// void PintarTexto(const TCHAR *Texto, DWLRecta *Rect);
		 void				PintarTexto(const TCHAR *Texto, DWLRecta *Rect);
							//
							// Función para pintar el texto centrado partiendo de una Clase DWLRecta
							// void	PintarTextoCentrado(const TCHAR *Texto, DWLRecta *R);
		 void				PintarTextoCentrado(const TCHAR *Texto, DWLRecta *R);
							//
							// Funciónes para pintar este hDC en un hDC Destino
							// void	PintarMapaBits(DWLhDC *hDCDest, DWLRecta *Recta, const int SrcX, const int SrcY, DWORD Flag = SRCCOPY);
		 void				PintarMapaBits(DWLhDC *hDCDest, DWLRecta *Recta, const int SrcX, const int SrcY, DWORD Flag = SRCCOPY);
							//
							// Funciónes para pintar el hDC en otro hDC de forma que se vea translucido
							// void PintarMapaBitsTranslucido(DWLhDC *hDCDest, DWLRecta *RDest, DWLRecta *RSrc, const BYTE Transparencia);
		 void				PintarMapaBitsTranslucido(DWLhDC *hDCDest, DWLRecta *RDest, DWLRecta *RSrc, const BYTE Transparencia);
							//
							// Función para pintar una clase DWLIcono
							// void PintarIcono(const int X, const int Y, const int Ancho, const int Alto, DWLIcono *Icono);
		 void				PintarIcono(const int X, const int Y, const int Ancho, const int Alto, DWLIcono *Icono);
							//
							// Función para pintar un Gradiente
							// void	PintaGradient(COLORREF Col1, COLORREF Col2, DWLRecta *Recta, const bool Horizontal);
		 void				PintaGradient(COLORREF Col1, COLORREF Col2, DWLRecta *Recta, const bool Horizontal);
							//
							// Función para pintar un Gradiente
							// void	PintaGradient(COLORREF Col1, COLORREF Col2, RECT *Recta, const bool Horizontal);
		 void				PintaGradient(COLORREF Col1, COLORREF Col2, RECT *Recta, const bool Horizontal);
							//
							// Función para obtener el tamaño en pixeles del texto
							// SIZE	ObtenerMedidasTexto(const TCHAR *Txt);
		 SIZE				ObtenerMedidasTexto(const TCHAR *Txt);

							// Funciónes NO AÑADIDAS
							// La razon es que si ponemos NULL en el argumento, el compilador no sabe que version de la función elegir.
							// Y total no es muy complicado usar el operador () del objeto o su función que retorne el objeto base

							// Función para selecionar una clase DWLBrocha en el DC
/*		 inline void		Brocha(DWLBrocha *Brocha) {
								if (Brocha == NULL) {
									SelectObject(_hDC, _VBrocha);
									_VBrocha = NULL;
								}
								else {
									_VBrocha = static_cast<HBRUSH>(SelectObject(_hDC, Brocha->Brocha()));
								}
							};
							// Función para selecionar una clase DWLMapaBits en el DC
		 inline void		MapaBits(DWLMapaBits *MapaBits) {
								if (MapaBits == NULL) {
									SelectObject(_hDC, _VMapaBits);
									_VMapaBits = NULL;
								}
								else {
									_VMapaBits = static_cast<HBITMAP>(SelectObject(_hDC, MapaBits->MapaBits()));
								}
							};
							// Función para selecionar una clase DWLFuente en el DC
		 inline void		Fuente(DWLFuente *Fuente) {
								if (Fuente == NULL) {
									SelectObject(_hDC, _VFuente);
									_VFuente = NULL;
								}
								else {
									_VFuente = static_cast<HFONT>(SelectObject(_hDC, Fuente->Fuente()));
								}
							};
							// Función para selecionar una cse DWLPluma en el DC
		 inline void		Pluma(DWLPluma *Pluma) {
								if (Pluma == NULL) {
								SelectObject(_hDC, _VPluma);
								_VPluma = NULL; } else { _VPluma = static_cast<HPEN>(SelectObject(_hDC, Pluma->Pluma())); } }; */


		protected : ////////// Metodos protegidos
                            // Constructor copia des-habilitado
                            DWLhDC(const DWL::GDI::DWLhDC &): _hWndVentana(NULL), _VBrocha(NULL), _VPluma(NULL), _VFuente(NULL), _MapaBits(NULL), _hDC(NULL), _VMapaBits(NULL), _Eliminable(true) { };
                            // Operador = des-habilitado
		 inline HFONT       operator=(const DWL::GDI::DWLhDC &) { };
							//
							// hDC de esta clase
		 HDC               _hDC;
							//
					  	    // Brocha inicial
		 HBRUSH            _VBrocha;
							//
						    // Pluma inicial
		 HPEN              _VPluma;
							//
						    // Fuente inicial
		 HFONT             _VFuente;
							//
						    // Mapa de Bits inicial
		 HBITMAP           _VMapaBits;
							//
						    // Handle de la ventana de la que se ha obtenido el DC
		 HWND              _hWndVentana;
							//
						    // Mapa de bits para crear DC's y BMP's compatibles
		 HBITMAP           _MapaBits;
							//
						    // Flag para determinar si se tiene que borrar el hDC o no
		 bool              _Eliminable;
		 private : /////////// Miembros privados


		};					//
		////////////////////// Fin DWLhDC

	};
};

#endif
