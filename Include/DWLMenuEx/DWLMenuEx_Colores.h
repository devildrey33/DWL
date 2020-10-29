#ifndef DWL_MENUEX_COLORES_H
#define DWL_MENUEX_COLORES_H
 
#include "..\DWLEstilos.h"
//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres ControlesEx
	namespace ControlesEx {
        //! Clase que contiene los colores para el MenuEx
		class DWLMenuEx_Colores {
		 public : //////////////////////// Metodos publicos

									    //! Constructor.
									    /*!	Constructor por defecto.
											    \fn		DWLMenuEx_Colores(void);
											    \return	No devuelve nada.
									    */
									    DWLMenuEx_Colores(void) :
										    DegradadoSuperior(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoSuperior),
										    DegradadoInferior(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoInferior),
										    TextoNormal(		&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Normal),
										    TextoResaltado(   	&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Resaltado),
										    TextoDesactivado(	&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Presionado),
										    FlechaNormal(		&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Normal),
										    FlechaResaltada(  	&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Resaltado),
										    FlechaDesactivada(	&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Presionado),
										    FondoSeleccion(		&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_Seleccionado),
										    Borde(				&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_Normal) {
									    };

									    //! Destructor.
									    /*!	Destructor.
											    \fn		~DWLMenuEx_Colores(void);
											    \return	No devuelve nada.
									    */
								       ~DWLMenuEx_Colores(void) {
									    };

						    			//! Primer color del degradado
		 DWL::SO::DWLEstilos_Color		DegradadoSuperior;

					    				//! Segundo color del degradado
		 DWL::SO::DWLEstilos_Color		DegradadoInferior;

					    				//! Color del texto normal
		 DWL::SO::DWLEstilos_Color		TextoNormal;

					    				//! Color del texto resaltado
		 DWL::SO::DWLEstilos_Color		TextoResaltado;

					    				//! Color del texto desactivado
		 DWL::SO::DWLEstilos_Color		TextoDesactivado;

					    				//! Color de la flecha normal
		 DWL::SO::DWLEstilos_Color		FlechaNormal;

					    				//! Color de la flecha resaltada
		 DWL::SO::DWLEstilos_Color		FlechaResaltada;

					    				//! Color de la flecha desactivada
		 DWL::SO::DWLEstilos_Color		FlechaDesactivada;

					    				//! Color del fondo de la selecion
		 DWL::SO::DWLEstilos_Color		FondoSeleccion;

									    //! Color del borde
		 DWL::SO::DWLEstilos_Color		Borde;
		};			                    //
		////////////////////////////////// Final DWLMenuEx_Colores

    };
};

#endif
