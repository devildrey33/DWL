// Modulo que contiene la clase DWLMapaBits que es un derivado del objeto HBITMAP de windows.
// Esta clase se ha creado pensando en facilitar la vida al programador, por ello incluye Funciónes para interactuar con varios objetos.
// Ultima modificación 28/04/2009
// Version 1.0

#ifndef DWL_GDI_MAPA_BITS_H
#define DWL_GDI_MAPA_BITS_H

#include "DWLEnumsGDI.h"

namespace DWL {
	namespace GDI {

		class DWLRecta;		// DWLRecta		(Clase para manipular RECT)
//		class DWLRegion;	// DWLRegion	(Clase para manipular HRGN)
//		class DWLBrocha;	// DWLBrocha	(Clase para manipular HBRUSH)
//		class DWLPluma;		// DWLPluma		(Clase para manipular HPEN)
//		class DWLMapaBits;	// DWLMapaBits	(Clase para manipular HBITMAP)
//		class DWLFuente;	// DWLFuente	(Clase para manipular HFONT)
//		class DWLIcono;		// DWLIcono		(Clase para manipular HICON)
//		class DWLColor;		// DWLColor		(Clase para manipular COLORREF)
		class DWLhDC;		// DWLhDC		(Clase para manipular HDC)

		// Clase para manipular objeto de clase HBITMAP
		class DWLMapaBits {
		public : ///////////// Miembors publicos
							//
							// Constructor
							// DWLMapaBits(void);
							DWLMapaBits(void) : _MapaBits(NULL) {
								_MapaBits = NULL;
							};
							//
							// Constructor const TCHAR * (Para cargar un BMP del HD)
							// DWLMapaBits(TCHAR *Archivo);
							DWLMapaBits(TCHAR *Archivo) : _MapaBits(NULL) {
								_MapaBits = static_cast<HBITMAP>(LoadImage(GetModuleHandle(NULL), Archivo, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
							};
							//
							// Constructor para crear un HBITMAP compatible con el hDC
							// DWLMapaBits(HDC hDC, const int Ancho, const int Alto);
							DWLMapaBits(HDC hDC, const int Ancho, const int Alto) : _MapaBits(NULL) {
								_MapaBits = CreateCompatibleBitmap(hDC, Ancho, Alto);
							};
							//
							// Constructor para crear un HBITMAP compatible con el hDC
							// DWLMapaBits(DWLhDC *hDC, const int Ancho, const int Alto);
							DWLMapaBits(DWLhDC *hDC, const int Ancho, const int Alto);
							//
							// Destructor
							// ~DWLMapaBits(void);
						   ~DWLMapaBits(void) {
								if (_MapaBits != NULL) DeleteObject(_MapaBits);
							};
							//
							// Función para borrar el HBITMAP y el hDC
							// inline void Borrar(void);
		 inline void		Borrar(void) {
							   if (_MapaBits != NULL) DeleteObject(_MapaBits);
							   _MapaBits = NULL;
							};
							//
							// Función para crear un HBITMAP Compatible con el hDC introducido
							// inline void CrearCompatibleBitmap(HDC hDC, const int Ancho, const int Alto);
		 inline void		CrearCompatibleBitmap(HDC hDC, const int Ancho, const int Alto) {
								Borrar();
								_MapaBits = CreateCompatibleBitmap(hDC, Ancho, Alto);
							};
							//
							// Función para cargar un BMP del disco duro
							// const bool CrearBitmapArchivo(const TCHAR *Archivo);
		 bool			    CrearBitmapArchivo(const TCHAR *Archivo) {
								Borrar();
								_MapaBits = static_cast<HBITMAP>(LoadImage(GetModuleHandle(NULL), Archivo, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
								if (_MapaBits != NULL) return true;
								return false;
							};
							//
							// Función que pinta el BMP en el hDC destino (BitBlt). Esta funncion crea su hDC compatible con el HBITMAP para pintarlo y luego lo borra
							// inline void PintarMapaBits(HDC hDCDest, const int X, const int Y, const int Ancho, const int Alto, const int SrcX, const int SrcY);
		 inline void		PintarMapaBits(HDC hDCDest, const int X, const int Y, const int Ancho, const int Alto, const int SrcX, const int SrcY) {
								HDC hDC = CreateCompatibleDC(hDCDest);
								HBITMAP Viejo = static_cast<HBITMAP>(SelectObject(hDC, _MapaBits));
								BitBlt(hDCDest, X, Y, Ancho, Alto, hDC, SrcX, SrcY, SRCCOPY);
								SelectObject(hDC, Viejo);
								DeleteDC(hDC);
							};
							//
							// Función para pintar el BMP en el hDC usando las medidas de un RECT
							// inline void PintarMapaBits(HDC hDCDest, RECT *Recta, const int SrcX, const int SrcY);
		 inline void		PintarMapaBits(HDC hDCDest, RECT *Recta, const int SrcX, const int SrcY) {
								HDC hDC = CreateCompatibleDC(hDCDest);
								HBITMAP Viejo = static_cast<HBITMAP>(SelectObject(hDC, _MapaBits));
								BitBlt(hDCDest, Recta->left, Recta->right, Recta->top, Recta->bottom, hDC, SrcX, SrcY, SRCCOPY);
								SelectObject(hDC, Viejo);
								DeleteDC(hDC);
							};
							//
							// Función que devuelve el HBRUSH de esta clase
							// inline HBITMAP MapaBits(void);
		 inline HBITMAP		MapaBits(void) {
								return _MapaBits;
							};
							//
							// Operador que retorna la brocha interna de esta clase
							// inline HBITMAP operator () (void);
		 inline HBITMAP		operator () (void) {
								return _MapaBits;
							};
							//
							// Función para crear un HBITMAP Compatible con el hDC introducido
							// void	CrearCompatibleBitmap(DWLhDC *hDC, const int Ancho, const int Alto);
		 void				CrearCompatibleBitmap(DWLhDC *hDC, const int Ancho, const int Alto);
							//
							// Función que pinta el BMP en el hDC destino (BitBlt). Esta funncion crea su hDC compatible con el HBITMAP para pintarlo y luego lo borra
							// void	PintarMapaBits(DWLhDC *hDCDest, const int X, const int Y, const int Ancho, const int Alto, const int SrcX, const int SrcY);
		 void				PintarMapaBits(DWLhDC *hDCDest, const int X, const int Y, const int Ancho, const int Alto, const int SrcX, const int SrcY);
							//
							// Función para pintar el BMP en el hDC usando las medidas de un DWLRecta. Esta funncion crea su hDC compatible con el HBITMAP para pintarlo y luego lo borra
							// void PintarMapaBits(DWLhDC *hDCDest, DWLRecta *Recta, const int ScrX, const int ScrY);
		 void				PintarMapaBits(DWLhDC *hDCDest, DWLRecta *Recta, const int ScrX, const int ScrY);
		private : //////////// Miembros privados

                            // Constructor copia des-habilitado
                            DWLMapaBits(const DWL::GDI::DWLMapaBits &) : _MapaBits(NULL) { };
                            // Operador = des-habilitado
		 inline DWLMapaBits &operator=(const DWL::GDI::DWLMapaBits &) { return *this; };
							//
							// HBITMAP  esta clase
		 HBITMAP           _MapaBits;
		};					//
		////////////////////// Fin DWLMapaBits
	};
};

#endif
