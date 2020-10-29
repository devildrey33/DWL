#ifndef DWL_TOOLTIPEX_COLORES_H
#define DWL_TOOLTIPEX_COLORES_H
 
#include "..\DWLEstilos.h"

namespace DWL {
	namespace ControlesEx {
		//! Clase que contiene los colores para el tooltip
		class DWLToolTipEx_Colores {
		public : ///////////////////////// Miembros publicos

									    //! Constructor por defecto.
									    /*! Este constructor enlaza todos los colores a la clase DWLEstilos.
											    \fn			DWLToolTipEx_Colores(void);
											    \return		No devuelve nada.
									    */
									    DWLToolTipEx_Colores(void) :
										    TextoNormal(		&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Normal),
										    TextoSombra(		&DWL::SO::DWLEstilos::Colores.VentanaEx_Texto_TituloSombra),
										    DegradadoSuperior(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoSuperior),
										    DegradadoInferior(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoInferior),
										    Borde(				&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_Normal) {
									    };

									    //! Color del texto normal.
		 DWL::SO::DWLEstilos_Color		TextoNormal;

									    //! Color del texto con sombra.
		 DWL::SO::DWLEstilos_Color		TextoSombra;

									    //! Color del degradado superior.
		 DWL::SO::DWLEstilos_Color		DegradadoSuperior;

									    //! Color del degradado inferior
		 DWL::SO::DWLEstilos_Color		DegradadoInferior;

									    //! Color del borde.
		 DWL::SO::DWLEstilos_Color		Borde;
		};							    //
		////////////////////////////////// Fin DWLToolTipEx_Colores

    };
};

#endif
