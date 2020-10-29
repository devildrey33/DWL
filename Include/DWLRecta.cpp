#include "DWLRecta.h"
#include "DWLRegion.h"
#include "DWLBrocha.h"
#include "DWLhDC.h"

namespace DWL {
	namespace GDI {
		// Constructor *DWLRegion
		DWLRecta::DWLRecta(DWLRegion *Region) : _Recta() {
			GetRgnBox(Region->Region(), &_Recta);
		};

 
		// Función para pintarb una recta con una *DWLBrocha
		void DWLRecta::PintarRecta(DWLhDC *hDC, DWLBrocha *Brocha) {
			FillRect(hDC->hDC(), &_Recta, Brocha->Brocha());
		};


		// Función para pintar el borde de un rectangulo usando una clase DWLBrocha
		void DWLRecta::EnmarcarRecta(DWLhDC *hDC, DWLBrocha *Brocha) {
			FrameRect(hDC->hDC(), &_Recta, Brocha->Brocha());
		};


		// Función para obtener las medidas de la *DWLRegion (GetRgnBox)
		void DWLRecta::ObtenerRectaRegion(DWLRegion *Region) {
			GetRgnBox(Region->Region(), &_Recta);
		};

	};
};
