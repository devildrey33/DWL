// Modulo que contiene la clase DWLRecta que es un derivado del objeto RECT de windows.
// Esta clase se ha creado pensando en facilitar la vida al programador, por ello incluye funciones para interactuar con varios objetos.
// Ademas esta clase soporta perfectamente los objetos basicos utilizados en el GDI de windows como son HDC, HBRUSH, HRGN, etc...
// Ultima modificación 28/04/2009
// Version 1.0

#ifndef DWL_GDI_RECTA_H
#define DWL_GDI_RECTA_H

#include "DWLEnumsGDI.h"
#include "DWLhDC.h"

namespace DWL {
	namespace GDI {
 
		class DWLRegion;



		// Clase para usar Objetos de tipo RECT
		class DWLRecta {
		public : ///////////// Miembros publicos
							//
							// Constructor
							// DWLRecta(void);
 							DWLRecta(void) : _Recta() {
 							    _Recta.left = 0;
 							    _Recta.top = 0;
 							    _Recta.right = 0;
 							    _Recta.bottom = 0;
							};
							//
                            // Constructor copia
                            DWLRecta(DWLRecta &R) : _Recta() {
                                _Recta.left     = R._Recta.left;
                                _Recta.right    = R._Recta.right;
                                _Recta.top      = R._Recta.top;
                                _Recta.bottom   = R._Recta.bottom;
                            };
							//
							// Constructor que obtiene la recta a partir de una region HRGN
							// DWLRecta(HRGN Region);
							DWLRecta(HRGN Region) : _Recta() {
								GetRgnBox(Region, &_Recta);
							};
							// Constructor &DWLRegion
 	 	 					DWLRecta(DWLRegion *Region);
							//
							// Constructor que obtiene la recta a partir de una ventana (HWND)
							// - RectaVentana == true  : se obtendra la recta de la ventana
							// - RectaVentana == false : se obtendra la recta cliente de la ventana (Ancho y alto solo)
							// DWLRecta(HWND hWnd, bool RectaVentana = false);
							DWLRecta(HWND hWnd, const bool RectaVentana = false) : _Recta() {
								if (RectaVentana == false)	GetClientRect(hWnd, &_Recta);
								else						GetWindowRect(hWnd, &_Recta);
							};
							//
							// Constructor por coordenadas
							// DWLRecta(const int cLeft, const int cTop, const int cRight, const int cBottom);
							DWLRecta(const int cLeft, const int cTop, const int cRight, const int cBottom)  : _Recta() {
								_Recta.left		= cLeft;
								_Recta.top		= cTop;
								_Recta.right	= cRight;
								_Recta.bottom	= cBottom;
							};
							//
							// Destructor (vacio)
							// ~DWLRecta(void);
						   ~DWLRecta(void) {
						    };
							//
							// Función pra asignar la Recta mediante coordenadas
						    // inline void Asignar(const int cLeft, const int cTop, const int cRight, const int cBottom);
		 inline void		Asignar(const int cLeft, const int cTop, const int cRight, const int cBottom) {
								_Recta.left		= cLeft;
								_Recta.top		= cTop;
								_Recta.right	= cRight;
								_Recta.bottom	= cBottom;
							};
							//
							// Función que devuelve un puntero al RECT de esta clase
							// inline RECT *Recta(void);
		 inline RECT       *Recta(void) {
								return &_Recta;
							};
							//
							// Función para pintar en el HDC el rectangulo de esta clase utilizando el HBRUSH especificado
							// inline void PintarRecta(HDC hDC, HBRUSH Brocha)
		 inline void		PintarRecta(HDC hDC, HBRUSH Brocha) {
								FillRect(hDC, &_Recta, Brocha);
							};
							//
							// Función para pintar en el DWLhDC el rectangulo de esta clase utilizando la DWLBrocha especificada
							// inline void PintarRecta(DWLhDC *hDC, DWLBrocha *Brocha);
		 inline void		PintarRecta(DWLhDC *hDC, DWLBrocha *Brocha);
							//
							// Función para pintar en el HDC un borde con el rectangulo de esta clase utilizando el HBRUSH especificado
							// inline void EnmarcarRecta(HDC hDC, HBRUSH Brocha);
		 inline void		EnmarcarRecta(HDC hDC, HBRUSH Brocha) {
								FrameRect(hDC, &_Recta, Brocha);
							};
							//
							// Función para pintar en el DWLhDC un borde con el rectangulo de esta clase utilizando la DWLBrocha especificada
							// inline void EnmarcarRecta(DWLhDC *hDC, DWLBrocha *Brocha);
		 inline void		EnmarcarRecta(DWLhDC *hDC, DWLBrocha *Brocha);
							//
							// Función para obtener las medidas de la ventana relativas al escritorio actual {GetWindowRect}
							// inline void ObtenerRectaVentana(HWND hWndVentana);
		 inline void		ObtenerRectaVentana(HWND hWndVentana) {
								GetWindowRect(hWndVentana, &_Recta);
							};
							//
							// Función para obtener el ancho y el alto de la ventana {GetClientRect)
							// inline void ObtenerRectaCliente(HWND hWndCliente);
		 inline void		ObtenerRectaCliente(HWND hWndCliente) {
								GetClientRect(hWndCliente, &_Recta);
							};
							//
							// Función para obtener las medidas del HRNG (GetRgnBox)
							// inline void ObtenerRectaRegion(HRGN Region);
		 inline void		ObtenerRectaRegion(HRGN Region) {
								GetRgnBox(Region, &_Recta);
							};
							//
							// Función para obtener las medidas de la *DWLRegion (GetRgnBox)
							// inline void ObtenerRectaRegion(DWLRegion *Region);
		 inline void		ObtenerRectaRegion(DWLRegion *Region);
							//
							// Función para determinar si las coordenadas estan dentro de la recta
							// inline BOOL PuntoEnRecta(const int X, const int Y);
		 inline BOOL		PuntoEnRecta(const int X, const int Y) {
								POINT PT = { X, Y };
								return PtInRect(&_Recta, PT);
							};
							//
							// Función para determinar si el POINT esta en la recta
							// inline BOOL PuntoEnRecta(POINT Punto);
		 inline BOOL		PuntoEnRecta(POINT Punto) {
								return PtInRect(&_Recta, Punto);
							};
							//
							// Función que suma valores a la recta
							// inline void Sumar(const LONG mLeft = 0, const LONG mTop = 0, const LONG mRight = 0, const LONG mBottom = 0);
		 inline void		Sumar(const LONG mLeft = 0, const LONG mTop = 0, const LONG mRight = 0, const LONG mBottom = 0)	{
								_Recta.left		+= mLeft;
								_Recta.top		+= mTop;
								_Recta.right	+= mRight;
								_Recta.bottom	+= mBottom;
							};
/*							//
							// Operador de asignacion (* DWLRecta)
							// inline void operator = (DWLRecta *R);
		 inline void		operator = (DWLRecta *R) {
								_Recta.bottom	= R->_Recta.bottom;
								_Recta.top		= R->_Recta.top;
								_Recta.left		= R->_Recta.left;
								_Recta.right	= R->_Recta.right;
							}; */
							//
							// Operador de asignacion DWLRecta
							// inline DWLRecta &operator = (DWLRecta &R);
		 inline DWLRecta &  operator = (const DWLRecta &R) {
								 _Recta.bottom	= R._Recta.bottom;
								 _Recta.top		= R._Recta.top;
								 _Recta.left	= R._Recta.left;
								 _Recta.right	= R._Recta.right;
								 return *this;
							};
							//
							// Operador de asignacion RECT
							// inline DWLRecta &operator = (RECT &R);
		 inline DWLRecta   &operator = (const RECT &R) {
								_Recta.bottom	= R.bottom;
								_Recta.top		= R.top;
								_Recta.left		= R.left;
								_Recta.right	= R.right;
								return *this;
							};
							//
							// Operador para sumar 1 a todos sus miembros
							// inline DWLRecta &operator ++ (void);
		 inline DWLRecta   &operator ++ (void) {
								_Recta.top		++;
								_Recta.bottom	++;
								_Recta.left		++;
								_Recta.right	++;
								return *this;
							};
							//
							// Operador para sumar X a todos sus miembros
							// inline void operator += (const LONG nSuma);
		 inline void		operator += (const LONG nSuma) {
								_Recta.top		+= nSuma;
								_Recta.bottom	+= nSuma;
								_Recta.left		+= nSuma;
								_Recta.right	+= nSuma;
							};
							//
							// Operador para restar 1 a todos sus miembros
							// inline DWLRecta &operator -- (void);
		 inline DWLRecta   &operator -- (void) {
								_Recta.top		--;
								_Recta.bottom	--;
								_Recta.left		--;
								_Recta.right	--;
								return *this;
							};
							//
							// Operador para restar X a todos sus miembros
							// inline void operator -= (const LONG nSuma);
		 inline void		operator -= (const LONG nSuma) {
								_Recta.top		-= nSuma;
								_Recta.bottom	-= nSuma;
								_Recta.left		-= nSuma;
								_Recta.right	-= nSuma;
							};
							//
							// Operador que retorna la Recta de esta Clase
							// inline RECT *operator () (void);
		 inline RECT       *operator () (void) {
								return &_Recta;
							};
							//
							// Operador que compara con una DWLRecta &
							// inline BOOL operator == (DWLRecta &R2) const;
		 inline BOOL	    operator == (DWLRecta &R2) const {
								if (R2._Recta.left == _Recta.left && R2._Recta.top == _Recta.top && R2._Recta.right == _Recta.right && R2._Recta.bottom == _Recta.bottom) return TRUE;
								return FALSE;
							};
							//
							// Operador que compara con una RECT &
							// inline BOOL operator == (RECT &R2) const;
		 inline BOOL	    operator == (RECT &R2) const {
								if (R2.left == _Recta.left && R2.top == _Recta.top && R2.right == _Recta.right && R2.bottom == _Recta.bottom) return TRUE;
								return FALSE;
							};
							//
							// Operador de negacion con una DWLRecta &
							// inline BOOL operator != (DWLRecta &R2) const;
		 inline BOOL	    operator != (DWLRecta &R2) const {
								if (R2.Left() != _Recta.left || R2.Top() != _Recta.top || R2.Right() == _Recta.right || R2.Bottom() != _Recta.bottom) return TRUE;
								return FALSE;
							};
							//
							// Operador de negacion con una RECT &
							// inline BOOL operator != (RECT &R2) const;
		 inline BOOL	    operator != (RECT &R2) const {
								if (R2.left != _Recta.left || R2.top != _Recta.top || R2.right != _Recta.right || R2.bottom != _Recta.bottom) return TRUE;
								return FALSE;
							};
							//
							// Función que retorna el valor Left
							// inline LONG Left(void) const;
		 inline LONG	    Left(void) const {
								return _Recta.left;
							};
							//
							// Función que asigna un valor al miembro Left
							// void	Left(const LONG nLeft);
		 void				Left(const LONG nLeft) {
								_Recta.left = nLeft;
							};
							//
							// Función que le suma al valor Left
							// void	SumarLeft(const LONG nLeft);
		 void				SumarLeft(const LONG nLeft) {
								_Recta.left += nLeft;
							};
							//
							// Función que retorna el valor Right
							// inline LONG Right(void) const;
		 inline LONG    	Right(void) const {
								return _Recta.right;
							};
							//
							// Función que asigna un valor al miembro Right
							// void Right(const LONG nRight)
		 void				Right(const LONG nRight) {
								_Recta.right = nRight;
							};
							//
							// Función que le suma al valor Right
							// void	SumarRight(const LONG nRight);
		 void				SumarRight(const LONG nRight) {
								_Recta.right += nRight;
							};
							//
							// Función que retorna el valor Top
							// inline LONG Top(void) const;
		 inline LONG	    Top(void) {
								return _Recta.top;
							};
							//
							// Función que asigna un valor al miembro Top
							// void Top(const LONG nTop);
		 void				Top(const LONG nTop) {
								_Recta.top = nTop;
							};
							//
							// Función que le suma al valor Top
							// void SumarTop(const LONG nTop);
		 void				SumarTop(const LONG nTop) {
								_Recta.top += nTop;
							};
							//
							// Función que retorna el valor Bottom
							// inline  LONG Bottom(void) const;
		 inline LONG	    Bottom(void) const {
								return _Recta.bottom;
							};
							//
							// Función que asigna un valor al miembro Bottom
							// void Bottom(const LONG nBottom);
		 void				Bottom(const LONG nBottom) {
								_Recta.bottom = nBottom;
							};
							//
							// Función que le suma al valor Bottom
							// void	SumarBottom(const LONG nBottom);
		 void				SumarBottom(const LONG nBottom) {
								_Recta.bottom += nBottom;
							};
		protected :	////////// Miembros protegidos
							//
							// Recta de esa clase
		 RECT              _Recta;
                            // Operador = des-habilitado
//		 inline HFONT       operator=(const DWL::GDI::DWLRecta &) { };
							//
       #if COMPILADOR != COMPILADOR_MINGW
		 friend class		DWLRecta;
  	   #endif
		};					//
		////////////////////// Fin DWLRecta
	};
};

#endif
