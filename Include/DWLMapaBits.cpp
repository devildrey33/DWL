#include "DWLMapaBits.h"
#include "DWLhDC.h"
#include "DWLRecta.h"
 
namespace DWL {
	namespace GDI {

		// Constructor DWLhDC
		DWLMapaBits::DWLMapaBits(DWLhDC *hDC, const int Ancho, const int Alto) : _MapaBits(NULL) {
			_MapaBits = CreateCompatibleBitmap(hDC->hDC(), Ancho, Alto);
		};

		// Función para crear un HBITMAP Compatible con el hDC introducido
		void DWLMapaBits::CrearCompatibleBitmap(DWLhDC *hDC, const int Ancho, const int Alto) {
			Borrar();
			_MapaBits = CreateCompatibleBitmap(hDC->hDC(), Ancho, Alto);
		};

		// Función que pinta el BMP en el hDC destino (BitBlt). Esta funncion crea su hDC compatible con el HBITMAP para pintarlo y luego lo borra
		void DWLMapaBits::PintarMapaBits(DWLhDC *hDCDest, const int X, const int Y, const int Ancho, const int Alto, const int SrcX, const int SrcY) {
			HDC hDC = CreateCompatibleDC(hDCDest->hDC());
			HBITMAP Viejo = static_cast<HBITMAP>(SelectObject(hDC, _MapaBits));
			BitBlt(hDCDest->hDC(), X, Y, Ancho, Alto, hDC, SrcX, SrcY, SRCCOPY);
			SelectObject(hDC, Viejo);
			DeleteObject(hDC);
		};

		// Función para pintar el BMP en el hDC usando las medidas de un DWLRecta. Esta funncion crea su hDC compatible con el HBITMAP para pintarlo y luego lo borra
		void DWLMapaBits::PintarMapaBits(DWLhDC *hDCDest, DWLRecta *Recta, const int SrcX, const int SrcY) {
			HDC hDC = CreateCompatibleDC(hDCDest->hDC());
			HBITMAP Viejo = static_cast<HBITMAP>(SelectObject(hDC, _MapaBits));
			BitBlt(hDCDest->hDC(), Recta->Left(), Recta->Top(), Recta->Right(), Recta->Bottom(), hDC, SrcX, SrcY, SRCCOPY);
			SelectObject(hDC, Viejo);
			DeleteDC(hDC);
		};

	};
};
