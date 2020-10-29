#ifndef DWL_LISTAEX_COLORES_H
#define DWL_LISTAEX_COLORES_H

#include "DWLListaEx_ColoresItem.h"
#include "DWLListaEx_ColoresColumna.h"
 
//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres ControlesEx
	namespace ControlesEx {
		//! Clase que contiene los colores para la ListaEx
		class DWLListaEx_Colores {
			public : /////////////////////////

										    //! Constructor por defecto.
										    /*! Este constructor enlaza todos los colores a la clase DWLEstilos.
												    \fn			DWLListaEx_Colores(void);
												    \return		No devuelve nada.
										    */
										    DWLListaEx_Colores(void) :
											    BordeSeleccion(		&DWL::SO::DWLEstilos::Colores.ContenedorEx_Borde_Seleccionado),
											    Fondo(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Normal),
											    Borde(				&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_Normal),
											    BordeFocoRaton(		&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_FocoRaton),
											    ColoresItem(),
											    ColoresColumna() {
										    };

										    //! Color del borde del control
			 DWL::SO::DWLEstilos_Color		Borde;

										    //! Color del borde claro del control
			 DWL::SO::DWLEstilos_Color		BordeFocoRaton;

										    //! Color del borde de la marca de selecion
			 DWL::SO::DWLEstilos_Color		BordeSeleccion;

										    //! Color del fondo normal
			 DWL::SO::DWLEstilos_Color		Fondo;

										    //! Colores para los items
			 DWLListaEx_ColoresItem		    ColoresItem;

										    //! Colores para los items
			 DWLListaEx_ColoresColumna	    ColoresColumna;
		};								    //
		////////////////////////////////////// Fin DWLListaEx_Colores

    };
};

#endif
