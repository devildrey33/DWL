#include "DWLBrocha.h"
#include "DWLRecta.h"
#include "DWLhDC.h"
#include "DWLRegion.h"
#include "DWLMapaBits.h"
#include "DWLFuente.h"
#include "DWLPluma.h"
#include "DWLIcono.h"

namespace DWL {
	namespace GDI {

		// 
		// Funion para pintar una clase DWLRecta usando una clase DWLBrocha
		void DWLhDC::PintarRecta(DWLRecta *Recta, DWLBrocha *Brocha) {
			FillRect(_hDC, Recta->Recta(), Brocha->Brocha()); 
		};

		//
		// Funion para pintar una recta redondeada usando una Brocha
		void DWLhDC::PintarRectaRedondeada(const int cX, const int cY, const int cAncho, const int cAlto, const int xFact, const int yFact, DWLBrocha *Brocha) {
			SelectObject(_hDC, Brocha->Brocha()); 
			RoundRect(_hDC, cX, cY, cAncho, cAlto, xFact, yFact); 
		};

		//
		// Función para pintar el botde de la clase DWLRecta usando una clase DWLBrocha
		int DWLhDC::EnmarcarRecta(DWLRecta *Recta, DWLBrocha *Brocha) {
			return FrameRect(_hDC, Recta->Recta(), Brocha->Brocha());
		};

		//
		// Función para pintar la clase DWLRegion usando una clase DBricha
		void DWLhDC::PintarRegion(DWLRegion *Region, DWLBrocha *Brocha) {
			FillRgn(_hDC, Region->Region(), Brocha->Brocha()); 
		};

		//
		// Función para pintar el borde de la clase DWLRecta usando una clase DWLBrocha
		void DWLhDC::EnmarcarRegion(DWLRegion *Region, DWLBrocha *Brocha, const int TamAlto, const int TamAncho) {
			FrameRgn(_hDC, Region->Region(), Brocha->Brocha(), TamAlto, TamAncho); 
		};

		//
		// Función para pintar texto partiendo de una clase DWLRecta
		void DWLhDC::PintarTexto(const TCHAR *Texto, DWLRecta *Rect) {
			DrawText(_hDC, Texto, static_cast<int>(DWLStrLen(Texto)), Rect->Recta(), DT_LEFT); 
		};

		//
		// Función para pintar el texto centrado partiendo de una Clase DWLRecta
		void DWLhDC::PintarTextoCentrado(const TCHAR *Texto, DWLRecta *R) {
			DrawText(_hDC, Texto, static_cast<int>(DWLStrLen(Texto)), R->Recta(), DT_CENTER); 
		};
		
		//
		// Funciónes para pintar este hDC en un hDC Destino
		void DWLhDC::PintarMapaBits(DWLhDC *hDCDest, DWLRecta *Recta, const int SrcX, const int SrcY, DWORD Valor) {
			BitBlt(hDCDest->hDC(), Recta->Left(), Recta->Top(), Recta->Right(), Recta->Bottom(), _hDC, SrcX, SrcY, Valor);
		};

		//
		// Funciónes para pintar el hDC en otro hDC de forma que se vea translucido
		void DWLhDC::PintarMapaBitsTranslucido(DWLhDC *hDCDest, DWLRecta *RDest, DWLRecta *RSrc, const BYTE Transparencia) {
			BLENDFUNCTION BF; 
			BF.AlphaFormat			= 0; 
			BF.BlendOp				= 0; 
			BF.BlendFlags			= 0; 
			BF.SourceConstantAlpha	= Transparencia;
			AlphaBlend(hDCDest->hDC(), RDest->Left(), RDest->Top(), RDest->Right(), RDest->Bottom(), _hDC, RSrc->Left(), RSrc->Top(), RSrc->Right(), RSrc->Bottom(), BF);
		};

		//
		// Función para pintar una clase DWLIcono
		void DWLhDC::PintarIcono(const int X, const int Y, const int Ancho, const int Alto, DWLIcono *Icono) {
			DrawIconEx(_hDC, X, Y, Icono->Icono(), Ancho, Alto, 0, 0, DI_NORMAL); 
		};

		/////////////////////////////////////////////////////////////////////////////////////////////
		// Función para obtener el tamaño del texto en pixeles                                     // 
		// Si el texto contiene varias lienas esta Función obtiene el ancho y el alto              //
		// mirando una por una las lineas de texto y sumando 4 por cada linea a la altura          // 
		// para simular el espacio entre linea y linea                                             //
		/////////////////////////////////////////////////////////////////////////////////////////////
		SIZE DWLhDC::ObtenerMedidasTexto(const TCHAR *Txt) {                                          // 
			TCHAR T[512];
			SIZE R;
			int  MaximoAncho = 0;
			int  Ultimo      = 0;
			int  Alto        = 0;
			int  StrLen      = static_cast<int>(DWLStrLen(Txt));
			for (int i = 0; i < StrLen; i++) {
				T[Ultimo] = Txt[i];
				Ultimo ++;
				if (Txt[i] == '\n' || Txt[i] == '\0' || Txt[i] == 0) {
					T[Ultimo] = '\0';
					Ultimo = 0;
					GetTextExtentPoint32(_hDC, T, static_cast<int>(DWLStrLen(T)), &R);
					Alto = Alto + 4 + R.cy;
					if (MaximoAncho < R.cx) MaximoAncho = R.cx;
				}
			}
			R.cx = MaximoAncho;
			R.cy = Alto;
			if (MaximoAncho == 0) GetTextExtentPoint32(_hDC, Txt, static_cast<int>(StrLen), &R);
			return R;
		}

		//
		// Función para pintar un Gradient en el DC con los colores espeficicados
		void DWLhDC::PintaGradient(COLORREF Col1, COLORREF Col2, RECT *Recta, const bool Horizontal) {                      
			TRIVERTEX     GCVertex[2];
			GRADIENT_RECT tGRect;
			GCVertex[0].Red		= DWL_RGB_OBTENER_R(Col1);
			GCVertex[0].Green	= DWL_RGB_OBTENER_G(Col1);
			GCVertex[0].Blue	= DWL_RGB_OBTENER_B(Col1);
			GCVertex[0].x = Recta->left;
			GCVertex[0].y = Recta->top;
			GCVertex[1].Red		= DWL_RGB_OBTENER_R(Col2);
			GCVertex[1].Green	= DWL_RGB_OBTENER_G(Col2);
			GCVertex[1].Blue	= DWL_RGB_OBTENER_B(Col2);
			GCVertex[1].x = Recta->right;
			GCVertex[1].y = Recta->bottom;
			tGRect.UpperLeft = 0;  tGRect.LowerRight = 1;
			GradientFill(_hDC, GCVertex, 2, &tGRect, 1, (Horizontal == true) ? DWLGRADIENT_FILL_RECT_H : DWLGRADIENT_FILL_RECT_V);
		}

		//
		// Función para pintar un Gradient en el DC con los colores espeficicados 
		void DWLhDC::PintaGradient(COLORREF Col1, COLORREF Col2, DWLRecta *Recta, const bool Horizontal) {
			TRIVERTEX     GCVertex[2];
			GRADIENT_RECT tGRect;
			GCVertex[0].Red		= DWL_RGB_OBTENER_R(Col1);
			GCVertex[0].Green	= DWL_RGB_OBTENER_G(Col1);
			GCVertex[0].Blue	= DWL_RGB_OBTENER_B(Col1);                                                 
			GCVertex[0].x = Recta->Left();
			GCVertex[0].y = Recta->Top();
			GCVertex[1].Red		= DWL_RGB_OBTENER_R(Col2);                                                      
			GCVertex[1].Green	= DWL_RGB_OBTENER_G(Col2);                                                            
			GCVertex[1].Blue	= DWL_RGB_OBTENER_B(Col2);                                                 
			GCVertex[1].x = Recta->Right();
			GCVertex[1].y = Recta->Bottom();
			tGRect.UpperLeft = 0;  tGRect.LowerRight = 1;
			GradientFill(_hDC, GCVertex, 2, &tGRect, 1, (Horizontal == true) ? DWLGRADIENT_FILL_RECT_H : DWLGRADIENT_FILL_RECT_V);
		}                                                                                                                 
	}
}
