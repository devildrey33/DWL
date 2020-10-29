#ifndef DWL_BARRAEX_COLORES_H
#define DWL_BARRAEX_COLORES_H

#include "..\DWLEstilos.h"

namespace DWL {
	namespace ControlesEx {
		//! Clase que contiene los colores de la BarraEx.
		class DWLBarraEx_Colores {
		public : /////////////////////////

									    //! Constructor que enlaza a los colores del skin.
									    /*! Constructor que enlaza a los colores del skin.
											    \fn			DWLBarraEx_Colores(void);
											    \return		No devuelve nada.
									    */
									    DWLBarraEx_Colores(void) :
										    DegradadoSuperior(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoSuperior	),
										    DegradadoInferior(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoInferior	),
										    DegradadoResaltado(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoResaltado),
										    Borde(				&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_Normal			),
										    BordeClaro(			&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_Claro				),
										    BordeSeleccionado(	&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_FocoRaton			),
										    Fondo(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Normal			) {
									    };


									    //! Función que reinicia los colores.
									    /*! Función que reinicia los colores.
											    \fn			void ReiniciarColores(void);
											    \return		No devuelve nada.
									    */
		 void                           ReiniciarColores(void) {
											DegradadoSuperior.Enlazar(&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoSuperior);
											DegradadoInferior.Enlazar(&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoInferior);
											DegradadoResaltado.Enlazar(&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoResaltado);
											Borde.Enlazar(&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_Normal);
											BordeClaro.Enlazar(&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_Claro);
											BordeSeleccionado.Enlazar(&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_FocoRaton);
											Fondo.Enlazar(&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Normal);
									    };

									    //! Color para el degradado superior
         DWL::SO::DWLEstilos_Color		DegradadoSuperior;

									    //! Color para el degradado inferior
		 DWL::SO::DWLEstilos_Color		DegradadoInferior;

									    //! Color para el degradado resaltado
		 DWL::SO::DWLEstilos_Color		DegradadoResaltado;

									    //! Color para el fondo
		 DWL::SO::DWLEstilos_Color		Fondo;

									    //! Color para el borde
		 DWL::SO::DWLEstilos_Color		Borde;

									    //! Color para el borde claro
		 DWL::SO::DWLEstilos_Color		BordeClaro;

									    //! Color para el borde seleccionado
		 DWL::SO::DWLEstilos_Color		BordeSeleccionado;
		};							    //
		////////////////////////////////// Fin DWLBarraEx_Colores

    };
};

#endif
