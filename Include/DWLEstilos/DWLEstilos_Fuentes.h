/*! \file DWLEstilos_Fuentes.h
	\brief		 Archivo que contiene varias fuentes que utilizaran los controles extendidos.
    */
#ifndef DWL_ESTILOS_FUENTES_H
#define DWL_ESTILOS_FUENTES_H

#include "DWLEstilos_Fuente.h"

//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres Estilos
    namespace SO {

		//! Clase contenedora de una fuente para los controles extendidos
	    class DWLEstilos_Fuentes {
		  public : /////////////////////// Miembros publicos
										DWLEstilos_Fuentes(void) {	};
			  DWLEstilos_Fuente			Tahoma13;
			  DWLEstilos_Fuente			Tahoma13_SubRayada;
			  DWLEstilos_Fuente			Tahoma13_Negrita;
			  DWLEstilos_Fuente			Tahoma13_Negrita_SubRayada;
			  DWLEstilos_Fuente			Tahoma13_Negrita_Cursiva;
			  DWLEstilos_Fuente			Tahoma13_Negrita_Cursiva_SubRayada;
			  DWLEstilos_Fuente			Tahoma13_Cursiva;
			  DWLEstilos_Fuente			Tahoma13_Cursiva_SubRayada;
		};
	    ////////////////////////////////// Fin DWLEstilos_Fuentes
    };
};

#endif
