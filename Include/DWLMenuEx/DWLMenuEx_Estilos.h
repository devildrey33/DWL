#ifndef DWL_MENUEX_ESTILOS_H
#define DWL_MENUEX_ESTILOS_H
 
#include "..\DWLEstilos.h"
#include "DWLMenuEx_Colores.h"

namespace DWL {
	namespace ControlesEx {

		class DWLMenuEx_Fuentes {
		  public:
										DWLMenuEx_Fuentes(void) { 
											Normal.Enlazar(DWL::SO::DWLEstilos::Fuentes.Tahoma13);
											Negrita.Enlazar(DWL::SO::DWLEstilos::Fuentes.Tahoma13_Negrita);
											SubRayada.Enlazar(DWL::SO::DWLEstilos::Fuentes.Tahoma13_SubRayada);
										};
			DWL::SO::DWLEstilos_Fuente  Normal;
			DWL::SO::DWLEstilos_Fuente  Negrita;
			DWL::SO::DWLEstilos_Fuente  SubRayada;

		};

		//! Clase que contiene los colores para el tooltip
		class DWLMenuEx_Estilos {
		public : ///////////////////////// Miembros publicos

									//! Constructor por defecto.
									/*! Este constructor enlaza todos los colores a la clase DWLEstilos.
										    \fn			DWLToolTipEx_Estilos(void);
										    \return		No devuelve nada.
									*/
									DWLMenuEx_Estilos(void) {
									};

									//! Clase que contiene los colores para esta clase.
		 DWLMenuEx_Colores			Colores;
			
									//! Clase que contiene las fuentes para esta clase.
		 DWLMenuEx_Fuentes			Fuentes;
		};							//
		////////////////////////////// Fin DWLToolTipEx_Colores

    };
};

#endif
