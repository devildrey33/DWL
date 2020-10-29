#ifndef DWL_LISTAEX_COLORESCOLUMNA_H
#define DWL_LISTAEX_COLORESCOLUMNA_H

#include "..\DWLEstilos.h"
 
namespace DWL {
	namespace ControlesEx {
		//! Clase que contiene los colores para las columnas de la ListaEx
		class DWLListaEx_ColoresColumna {
			public:	////////////////////////// Metodos publicos

										    //! Constructor por defecto.
										    /*! Este constructor enlaza todos los colores a la clase DWLEstilos.
												    \fn			DWLListaEx_ColoresColumna(void);
												    \return		No devuelve nada.
										    */
										    DWLListaEx_ColoresColumna(void) :
											    Columna_DegradadoSuperior(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoSuperior),
											    Columna_DegradadoInferior(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoInferior),
											    Columna_DegradadoResaltado(	&DWL::SO::DWLEstilos::Colores.ControlEx_Fondo_DegradadoResaltado),
											    Columna_TextoNormal(		&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Normal),
											    Columna_TextoResaltado(		&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Resaltado),
											    Columna_TextoPresionado(	&DWL::SO::DWLEstilos::Colores.ControlEx_Texto_Presionado) {
										    };

						    				//! Color del degradado superior de la columna
			 DWL::SO::DWLEstilos_Color		Columna_DegradadoSuperior;

						    				//! Color del degradado inferior de la columna
			 DWL::SO::DWLEstilos_Color		Columna_DegradadoInferior;

						    				//! Color del degradado resaltado de la columna
			 DWL::SO::DWLEstilos_Color		Columna_DegradadoResaltado;

						    				//! Color del texto normal para las columnas
			 DWL::SO::DWLEstilos_Color		Columna_TextoNormal;

						    				//! Color del texto resaltado para las columnas
			 DWL::SO::DWLEstilos_Color		Columna_TextoResaltado;

										    //! Color del texto presionado para las columnas
			 DWL::SO::DWLEstilos_Color		Columna_TextoPresionado;
		};								    //
		//////////////////////////////////////
    };
};

#endif
