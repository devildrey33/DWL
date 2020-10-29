#ifndef DWL_BARRASCROLLEX_COLORES_H
#define DWL_BARRASCROLLEX_COLORES_H
 
#include "..\DWLEstilos.h"

namespace DWL {
	namespace ControlesEx {
		//! Clase que contiene los colores para la barra de scroll
		class DWLBarraScrollEx_Colores {
		public:	////////////////////////////// Miembros publicos
									        //
									        //! Constructor por defecto.
									        /*! Este constructor enlaza todos los colores a la clase DWLEstilos.
											        \fn			DWLBarraScrollEx_Colores(void);
											        \return		No devuelve nada.
									        */
									        DWLBarraScrollEx_Colores(void) :
                                                BordeNormal(		&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_Normal),
										        BordeFocoRaton(		&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_FocoRaton),
										        FlechitaResaltada(	&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Resaltado),
										        FlechitaNormal(		&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Normal),
										        FlechitaPresionada( &DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Presionado),
										        DegradadoSuperior(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoSuperior),
										        DegradadoInferior(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoInferior),
										        DegradadoResaltado( &DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoResaltado),
										        FondoNormal(		&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Normal),
										        FondoResaltado(		&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Resaltado),
										        FondoPresionado(	&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Claro) {
									        };

									        //! Primer color del degradado
         DWL::SO::DWLEstilos_Color	    DegradadoSuperior;

									        //! Segundo color del degradado
		 DWL::SO::DWLEstilos_Color	    DegradadoInferior;

				        					//! Color del degradado resaltado
		 DWL::SO::DWLEstilos_Color	    DegradadoResaltado;

		        							//! Color de la flecha normal
		 DWL::SO::DWLEstilos_Color	    FlechitaNormal;

									        //! Color de la flecha resaltada
		 DWL::SO::DWLEstilos_Color	    FlechitaResaltada;

									        //! Color de la flecha presionada
		 DWL::SO::DWLEstilos_Color	    FlechitaPresionada;

									        //! Color del borde
		 DWL::SO::DWLEstilos_Color	    BordeNormal;

									        //! Color del borde cuando tiene el foco del raton
		 DWL::SO::DWLEstilos_Color	    BordeFocoRaton;

									        //! Color del fondo normal
		 DWL::SO::DWLEstilos_Color	    FondoNormal;

									        //! Color del fondo resaltado
		 DWL::SO::DWLEstilos_Color	    FondoResaltado;

									        //! Color del fondo presionado
		 DWL::SO::DWLEstilos_Color	    FondoPresionado;
		 private: //////////////////////////// Miembros privados
                                            //! Constructor copia des-habilitado
                                            DWLBarraScrollEx_Colores(const DWLBarraScrollEx_Colores &)  :
                                                BordeNormal(		&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_Normal),
										        BordeFocoRaton(		&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_FocoRaton),
										        FlechitaResaltada(	&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Resaltado),
										        FlechitaNormal(		&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Normal),
										        FlechitaPresionada( &DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Presionado),
										        DegradadoSuperior(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoSuperior),
										        DegradadoInferior(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoInferior),
										        DegradadoResaltado( &DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoResaltado),
										        FondoNormal(		&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Normal),
										        FondoResaltado(		&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Resaltado),
										        FondoPresionado(	&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Claro) {
									        };
                                            //! Operador = des-habilitado
		 inline DWLBarraScrollEx_Colores   &operator=(const DWLBarraScrollEx_Colores &) { return *this; };

		};							        //
		////////////////////////////////////// Fin DWLBarraScrollEx_Colores

    };
};

#endif
