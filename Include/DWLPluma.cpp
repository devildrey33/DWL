#include "DWLPluma.h"
#include "DWLhDC.h"

namespace DWL {
	namespace GDI {
			
		// Función para pintar una linea
		void DWLPluma::PintarLinea(DWLhDC *hDC, const int X, const int Y, const int X2, const int Y2) {
			HPEN Viejo = NULL;
			if (_Pluma != static_cast<HPEN>(GetCurrentObject(hDC->hDC(), OBJ_PEN))) { 
				Viejo = (HPEN)SelectObject(hDC->hDC(), _Pluma); 
			} 
			MoveToEx(hDC->hDC(), X, Y, NULL);
			LineTo(hDC->hDC(), X2, Y2); 
			if (Viejo != NULL) { 
				SelectObject(hDC->hDC(), Viejo); 
			} 
		};

	};
}; 
