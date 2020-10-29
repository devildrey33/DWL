#ifndef DWL_BOTONEX_COLORES_H
#define DWL_BOTONEX_COLORES_H
 
#include "..\DWLEstilos.h"

namespace DWL {
	namespace ControlesEx {
		//! Clase que contiene los colores para el BotonEx
		class DWLBotonEx_Colores {
		 public : //////////////////////// Miembros publicos

									    //! Constructor por defecto.
									    /*! Este constructor enlaza todos los colores a la clase DWLEstilos.
											    \fn			DWLBotonEx_Colores(void);
											    \return		No devuelve nada.
									    */
									    DWLBotonEx_Colores(void) :
										    DegradadoSuperior(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoSuperior),
										    DegradadoInferior(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoInferior),
										    DegradadoResaltado( &DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoResaltado),
										    TextoDesactivado(	&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Presionado),
										    TextoResaltado(		&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Resaltado),
										    TextoNormal(		&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Normal),
										    Borde(				&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_Normal),
										    BordeClaro(			&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_Claro),
										    BordeSeleccionado(	&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_FocoRaton),
										    FondoVentanaPadre(	&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Normal) {
									    };

									    //! Color para la parte de arriba del degradado
		 DWL::SO::DWLEstilos_Color	DegradadoSuperior;

									    //! Color para la parte de abajo del degradado
		 DWL::SO::DWLEstilos_Color	DegradadoInferior;

									    //! Color para el degradado resaltado
		 DWL::SO::DWLEstilos_Color	DegradadoResaltado;

									    //! Color del texto normal
		 DWL::SO::DWLEstilos_Color	TextoNormal;

									    //! Color del texto resaltado
		 DWL::SO::DWLEstilos_Color	TextoResaltado;

									    //! Color del texto desactivado / presionado
		 DWL::SO::DWLEstilos_Color	TextoDesactivado;

									    //! Color del fondo de la ventana padre
		 DWL::SO::DWLEstilos_Color	FondoVentanaPadre;

									    //! Color del borde del boton
		 DWL::SO::DWLEstilos_Color	Borde;

									    //! Color para el borde claro
		 DWL::SO::DWLEstilos_Color	BordeClaro;

									    //! Color del borde del boton cuando tiene el foco
		 DWL::SO::DWLEstilos_Color	BordeSeleccionado;
		};							    //
		////////////////////////////////// Final DWLBotonEx_Colores
    };
};

#endif
