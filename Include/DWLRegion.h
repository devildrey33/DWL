// Modulo que contiene la clase DWLRegion que es un derivado del objeto HRGN de windows.
// Esta clase se ha creado pensando en facilitar la vida al programador, por ello incluye Funciónes para interactuar con varios objetos.
// Ademas esta clase nos permite crear region a partir de imagenes BMP, guardar regiones al disco, y cargar regiones del disco.
// Ultima modificación 28/04/2009
// Version 1.0

#ifndef DWL_GDI_REGION_H
#define DWL_GDI_REGION_H

#include "DWLEnumsGDI.h"
#include "DWLString.h"

namespace DWL {
	namespace GDI {

		class DWLhDC;
		class DWLBrocha;
 
		// Clase para manejar objetos de tipo HRGN
		class DWLRegion {
		public: ////////// Miembros publicos
						//
						// Constructor
						// DWLRegion(void);
						DWLRegion(void) : _Region(NULL) {
						};
						//
						// Constructor para crear una region rectangular
						// DWLRegion(const int X, const int Y, const int X2, const int Y2);
						DWLRegion(const int X, const int Y, const int X2, const int Y2) : _Region(NULL) {
							_Region = CreateRectRgn(X, Y, X2, Y2);
						};
						//
						// Constructor para crear una region rectangular redondeada
						// DWLRegion(const int X, const int Y, const int X2, const int Y2, const int CV, const int CH);
						DWLRegion(const int X, const int Y, const int X2, const int Y2, const int CV, const int CH) : _Region(NULL) {
							_Region = CreateRoundRectRgn(X, Y, X2, Y2, CH, CV);
						};
						//
						// Constructor para crear una region poligonal de 3 o mas costados
						// DWLRegion(const POINT *Puntos, const int NPuntos, const int Modo);
						DWLRegion(const POINT *Puntos, const int NPuntos, const int Modo) : _Region(NULL) {
							_Region = CreatePolygonRgn(Puntos, NPuntos, Modo);
						};
						//
						// Constructor para obtener la region de la ventana
						// DWLRegion(HWND hWndVentana);
						DWLRegion(HWND hWndVentana) : _Region(NULL) {
							_Region = CreateRectRgn(0, 0, 0, 0);
							GetWindowRgn(hWndVentana, _Region);
						};
						//
						// Constructor const TCHAR *  (Cargar regiones externas)
						// DWLRegion(const TCHAR *SHPPath);
						DWLRegion(const TCHAR *SHPPath) : _Region(NULL) {
							AbrirRegionDisco(SHPPath);
						};
						//
						// Constructor DWLString   (Cargar regiones externas)
						// DWLRegion(DWL::DWLString &SHPPath);
						DWLRegion(DWL::DWLString &SHPPath) : _Region(NULL) {
							AbrirRegionDisco(SHPPath());
						};
						//
						// Destructor
						// ~DWLRegion(void);
					   ~DWLRegion(void) {
							if (_Region != NULL) DeleteObject(_Region);
						};
						//
						// Función para borrar la region
					    // inline void Borrar(void);
		 inline void	Borrar(void) {
							if (_Region != NULL) DeleteObject(_Region);
							_Region = NULL;
						};
						//
						// Función para asignar una region a esta clase
						// inline void AsignarRegion(HRGN nRegion);
		 inline void    AsignarRegion(HRGN nRegion) {
							Borrar();
							_Region = nRegion;
						};
						//
					    // Función que asigna la region a la ventana especificada
						// inline void AsignarRegionVentana(HWND hWndVentana, const BOOL nRepintar = TRUE)
		 inline void    AsignarRegionVentana(HWND hWndVentana, const BOOL nRepintar = TRUE) {
							// 1 - Asignamos la region de esta clase a la ventana destino.
							// 2 - Creamos una nueva region sin borrar la anterior, porque ahora es propiedad del SO y no debemos tocarla.
							//	   Esta region la creamos porque necesitamos una region vacia creada, para poder obtener regiones de ventanas.
							// 3 - Obtenemos una nueva region igual a la que tiene la ventana para trabajar con ella.
							SetWindowRgn(hWndVentana, _Region, nRepintar);
							_Region = CreateRectRgn(0, 0, 0, 0);
							GetWindowRgn(hWndVentana, _Region);
						};
						//
					    // Función para obtener la region de la ventana especificada
						// inline void ObtenerRegionVentana(HWND hWnd);
		 inline void    ObtenerRegionVentana(HWND hWnd) {
							if (_Region != NULL) DeleteObject(_Region);
							_Region = CreateRectRgn(0, 0, 0, 0);
							GetWindowRgn(hWnd, _Region);
						};
						//
					    // Función pra crear una region rectangular
						// inline void CrearRegionRecta(const int X, const int Y, const int X2, const int Y2);
		 inline void    CrearRegionRecta(const int X, const int Y, const int X2, const int Y2) {
							if (_Region != NULL) DeleteObject(_Region);
							_Region = CreateRectRgn(X, Y, X2, Y2);
						};
						//
					    // Función para crear una region rectangular redondeada
						// inline void CrearRegionRectaRedondeada(const int X, const int Y, const int X2, const int Y2, const int CH, const int CV);
		 inline void    CrearRegionRectaRedondeada(const int X, const int Y, const int X2, const int Y2, const int CH, const int CV) {
							if (_Region != NULL) DeleteObject(_Region);
							_Region = CreateRoundRectRgn(X, Y, X2, Y2, CH, CV);
						};
						//
					    // Función para crear una Función poligonal (3 o mas costados)
						// inline void CrearRegionPoligonal(const POINT *Puntos, const int NPuntos, const int Modo);
		 inline void    CrearRegionPoligonal(const POINT *Puntos, const int NPuntos, const int Modo) {
							if (_Region != NULL) DeleteObject(_Region);
							_Region = CreatePolygonRgn(Puntos, NPuntos, Modo);
						};
						//
					    // Función que combina esta region con una segunda, y crea una tercera con las dos combinadas.
						// inline void CombinarRegion(DWLRegion *Region2, DWLRegion *Resultado, int Modo = RGN_AND);
		 inline void    CombinarRegion(DWLRegion *Region2, DWLRegion *Resultado, int Modo = RGN_AND) {
							if (_Region != NULL) {
								HRGN Rgn = CreateRectRgn(0, 0, 0, 0);
								CombineRgn(Rgn, _Region, Region2->Region(), Modo);
								Resultado->AsignarRegion(Rgn);
							}
						};
						//
					    // Funciónes para pintar la region
						// inline void PintarRegion(HDC hDC, HBRUSH Brocha);
		 inline void    PintarRegion(HDC hDC, HBRUSH Brocha) {
							FillRgn(hDC, _Region, Brocha);
						};
						//
					    // Funciónes para enmarcar la region
						// inline void EnmarcarRegion(HDC hDC, HBRUSH Brocha, const int TamAncho, const int TamAlto);
		 inline void    EnmarcarRegion(HDC hDC, HBRUSH Brocha, const int TamAncho, const int TamAlto) {
							FrameRgn(hDC, _Region, Brocha, TamAncho, TamAlto);
						};
						//
					    // Función para mover la region (OffsetRgn)
						// inline void MoverRegion(const int X, const int Y);
		 inline void    MoverRegion(const int X, const int Y) {
							OffsetRgn(_Region, X, Y);
						};
						//
					    // Función para determinar si el POINT esta dentro de la region
						// inline BOOL PuntoEnRegion(POINT Punto);
		 inline BOOL    PuntoEnRegion(POINT Punto) {
							return PtInRegion(_Region, Punto.x, Punto.y);
						};
						//
					    // Función para determinar si ls coordenadas estan dentro de la region
						// inline BOOL PuntoEnRegion(const int X, const int Y);
		 inline BOOL    PuntoEnRegion(const int X, const int Y) {
							return PtInRegion(_Region, X, Y);
						};
						//
					    // Función que devuelve la region de esta clase
						// inline HRGN Region(void);
		 inline HRGN    Region(void) {
							return _Region;
						};
						//
					    // Operadores de comparacion
						// inline BOOL operator == (HRGN Comp);
		 inline BOOL    operator == (HRGN Comp) {
							return EqualRgn(_Region, Comp);
						}
						//
					    // Operador que retorna la region interna de esta clase
						// inline HRGN operator () (void);
		 inline HRGN    operator () (void) {
							return _Region;
						};
						//
					    // Función que carga una region desde un archivo externo del disco duro
						// void AbrirRegionDisco(const TCHAR *SHPPath);
		 void           AbrirRegionDisco(const TCHAR *SHPPath);
						//
					    // Función para crear una region partiendo de un BMP.
					    // NOTA : Esta Función obtiene el color del primer pixel del dibujo (0,0) y luego interpreta todos
					    //		  los pixeles que tengan el mismo color que el primer pixel como transparentes.
						//        Todos los demas colores seran tratados como parte de la region.
						// void CrearRegionBmp(const TCHAR *BMPPath);
		 void           CrearRegionBmp(const TCHAR *BMPPath);
						//
					    // Función para guardar la region a un archivo del disco duro
						// void GuardarRegionDisco(const TCHAR *Dest);
		 void           GuardarRegionDisco(const TCHAR *Dest);
						//
					    // Funciónes para pintar la region
						// void PintarRegion(DWLhDC *hDC, DWLBrocha *Brocha);
		 void           PintarRegion(DWLhDC *hDC, DWLBrocha *Brocha);
						//
					    // Funciónes para enmarcar la region
						// void EnmarcarRegion(DWLhDC *hDC, DWLBrocha *Brocha, const int TamAncho, const int TamAlto);
		 void           EnmarcarRegion(DWLhDC *hDC, DWLBrocha *Brocha, const int TamAncho, const int TamAlto);
						//
					    // Operadores de comparacion
						// inline BOOL operator == (DWLRegion *Comp);
		 inline BOOL    operator == (DWLRegion *Comp);
		private: /////// Miembros protegidos
                        // Constructor copia des-habilitado
                        DWLRegion(const DWL::GDI::DWLRegion &) : _Region(NULL) { };
                        // Operador = des-habilitado
		 inline HFONT   operator=(const DWL::GDI::DWLRegion &) { };
					    // Region de esta clase
		 HRGN          _Region;
		};				//
	}; /////////////////// Fin DWLRegion
};

#endif
