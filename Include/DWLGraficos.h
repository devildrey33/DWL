/*! \file DWLGraficos.h
	\brief		  Modulo con funciones de pintado prefabricadas para los controles extendidos de la DWL
*/ 
#ifndef DWL_GRAFICOS_H
#define DWL_GRAFICOS_H

#include "DWL.h"
#include "DWLBrocha.h"
#include "DWLRecta.h"
#include "DWLRegion.h"
#include "DWLhDC.h"
#include "DWLMapaBits.h"
#include "DWLPluma.h"
#include "DWLIcono.h"
#include "DWLFuente.h"


#define DWL_DIRECCION_FLECHA_ARRIBA		8
#define DWL_DIRECCION_FLECHA_ABAJO		2
#define DWL_DIRECCION_FLECHA_DERECHA	6
#define DWL_DIRECCION_FLECHA_IZQUIERDA	4
#define DWL_DIRECCION_FLECHA_EXTENDIDA	1

//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres GDI
	namespace GDI {

	    //! Función para pintar un degradado.
	    /*! Función para pintar un degradado segun los valores especificados.
			    \fn			static BOOL PintarGradient(HDC hDC, const int cX, const int cY, const int cX2, const int cY2, COLORREF Col1, COLORREF Col2, const bool Vertical = true);
                \param[in]  hDC      : HDC destino donde se pintara el degradado.
                \param[in]  cX       : Coordenada X por donde se empezara a pintar.
                \param[in]  cY       : Coordenada Y por donde se empezara a pintar.
                \param[in]  cX2      : Coordenada X2 por donde se terminara de pintar.
                \param[in]  cY2      : Coordenada Y2 por donde se terminara de pintar.
                \param[in]  Col1     : Color que se usara al principio del degradado.
                \param[in]  Col2     : Color que se usara al final del degradado.
                \param[in]  Vertical : true para pintar el degradado vertical, false para pintarlo horizontal.
			    \return		Devuelve TRUE si se pinto el degradado correctamente, FALSE en caso contrario.
	    */
		static BOOL PintarGradient(HDC hDC, const int cX, const int cY, const int cX2, const int cY2, COLORREF Col1, COLORREF Col2, const bool Vertical = true) {
			TRIVERTEX     GCVertex[2];
			GRADIENT_RECT tGRect;
			GCVertex[0].Red		= DWL_RGB_OBTENER_R(Col1); // (unsigned short)((Col1 & 0xFF) * 0x100);
			GCVertex[0].Green	= DWL_RGB_OBTENER_G(Col1); // (unsigned short)(Col1 & 0xFF00);
			GCVertex[0].Blue	= DWL_RGB_OBTENER_B(Col1); // (unsigned short)((Col1 & 0xFF0000) / 0x100);
			GCVertex[0].x = cX;
			GCVertex[0].y = cY;
			GCVertex[1].Red		= DWL_RGB_OBTENER_R(Col2); // (unsigned short)((Col2 & 0xFF) * 0x100);
			GCVertex[1].Green	= DWL_RGB_OBTENER_G(Col2); // (unsigned short)(Col2 & 0xFF00);
			GCVertex[1].Blue	= DWL_RGB_OBTENER_B(Col2); // (unsigned short)((Col2 & 0xFF0000) / 0x100);
			GCVertex[1].x = cX2;
			GCVertex[1].y = cY2;
			tGRect.UpperLeft = 0;
			tGRect.LowerRight = 1;
			return GradientFill(hDC, GCVertex, 2, &tGRect, 1, (Vertical == true) ? DWLGRADIENT_FILL_RECT_V : DWLGRADIENT_FILL_RECT_H);
		};

	    //! Función para pintar una flecha.
	    /*! Función para pintar una flecha (utilizada por las barras de scroll y el edición desplegable).
			    \fn			static void PintarFlecha(HDC hDC, RECT *Espacio, COLORREF Color, const int TipoFlecha);
                \param[in]  hDC        : HDC destino donde se pintara la flecha.
                \param[in]  Espacio    : Recta que delimitara el espacio para la flecha.
                \param[in]  Color      : Color que se usara para pintar la flecha.
                \param[in]  TipoFlecha : Tipo de flecha : DWL_DIRECCION_FLECHA_ARRIBA, DWL_DIRECCION_FLECHA_ABAJO, DWL_DIRECCION_FLECHA_DERECHA, y DWL_DIRECCION_FLECHA_IZQUIERDA.
			    \return		No devuelve nada.
	    */
		static void PintarFlecha(HDC hDC, RECT *Espacio, COLORREF Color, const int TipoFlecha) {
			HPEN Pluma = CreatePen(PS_SOLID, 3, Color);
			HPEN Viejo = static_cast<HPEN>(SelectObject(hDC, Pluma));
			switch (TipoFlecha) {
				case DWL_DIRECCION_FLECHA_ARRIBA :
					MoveToEx(hDC, Espacio->left + 5,  Espacio->top + 10, NULL);
					LineTo(hDC, Espacio->left + 8, Espacio->top + 6);
					LineTo(hDC, Espacio->left + 11, Espacio->top + 10);
					break;
				case DWL_DIRECCION_FLECHA_ABAJO :
					MoveToEx(hDC, Espacio->left + 5,  Espacio->top + 6, NULL);
					LineTo(hDC, Espacio->left + 8, Espacio->top + 10);
					LineTo(hDC, Espacio->left + 11, Espacio->top + 6);
					break;
				case DWL_DIRECCION_FLECHA_DERECHA :
					MoveToEx(hDC, Espacio->left + 6,  Espacio->top + 5, NULL);
					LineTo(hDC, Espacio->left + 10, Espacio->top + 8);
					LineTo(hDC, Espacio->left + 6, Espacio->top + 11);
					break;
				case DWL_DIRECCION_FLECHA_IZQUIERDA :
					MoveToEx(hDC, Espacio->left + 10,  Espacio->top + 5, NULL);
					LineTo(hDC, Espacio->left + 6, Espacio->top + 8);
					LineTo(hDC, Espacio->left + 10, Espacio->top + 11);
					break;
			}
			SelectObject(hDC, Viejo);
			DeleteObject(Pluma);
		};

	    //! Función para pintar una flecha.
	    /*! Función para pintar una flecha (utilizada por las barras de scroll y el edición desplegable).
			    \fn			static void PintarFlecha(HDC hDC, const int cX, const int cY, COLORREF Color, const int TipoFlecha)
                \param[in]  hDC        : HDC destino donde se pintara la flecha.
                \param[in]  cX         : Coordenada X donde se empezara a pintar la flecha.
                \param[in]  cY         : Coordenada Y donde se empezara a pintar la flecha.
                \param[in]  Color      : Color que se usara para pintar la flecha.
                \param[in]  TipoFlecha : Tipo de flecha : DWL_DIRECCION_FLECHA_ARRIBA, DWL_DIRECCION_FLECHA_ABAJO, DWL_DIRECCION_FLECHA_DERECHA, y DWL_DIRECCION_FLECHA_IZQUIERDA.
			    \return		No devuelve nada.
	    */
		static void PintarFlecha(HDC hDC, const int cX, const int cY, COLORREF Color, const int TipoFlecha) {
			HPEN Pluma = CreatePen(PS_SOLID, 3, Color);
			HPEN Viejo = static_cast<HPEN>(SelectObject(hDC, Pluma));
			switch (TipoFlecha) {
				case DWL_DIRECCION_FLECHA_ARRIBA :
					MoveToEx(hDC, cX + 5,  cY + 10, NULL);
					LineTo(hDC, cX + 8, cY + 6);
					LineTo(hDC, cX + 11, cY + 10);
					break;
				case DWL_DIRECCION_FLECHA_ABAJO :
					MoveToEx(hDC, cX + 5, cY + 6, NULL);
					LineTo(hDC, cX + 8, cY + 10);
					LineTo(hDC, cX + 11, cY + 6);
					break;
				case DWL_DIRECCION_FLECHA_DERECHA :
					MoveToEx(hDC, cX + 6, cY + 5, NULL);
					LineTo(hDC, cX + 10, cY + 8);
					LineTo(hDC, cX + 6, cY + 11);
					break;
				case DWL_DIRECCION_FLECHA_IZQUIERDA :
					MoveToEx(hDC, cX + 10, cY + 5, NULL);
					LineTo(hDC, cX + 6, cY + 8);
					LineTo(hDC, cX + 10, cY + 11);
					break;
			}
			SelectObject(hDC, Viejo);
			DeleteObject(Pluma);
		};

	}
}

#endif


// [11/05/2008]
// -Renombradas las clases de una forma mas acorde a toda la libreria
// -Rediseñada la clase DWLRecta para que use menos memoria y sea mas facil de usar.

// [28/04/2009]
// -Redistribuidas todas las clases en archivos diferentes para mayor comodidad
