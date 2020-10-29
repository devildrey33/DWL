#include "DWLIcono.h"
#include "DWLhDC.h"

namespace DWL {
	namespace GDI {

		void DWLIcono::PintarIcono(DWLhDC *hDC, const int X, const int Y, const int Ancho, const int Alto) { 
			DrawIconEx(hDC->hDC(), X, Y, _Icono, Ancho, Alto, 0, 0, DI_NORMAL); 
		};

	}; 
};
