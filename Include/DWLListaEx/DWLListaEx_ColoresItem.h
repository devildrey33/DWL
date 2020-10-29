#ifndef DWL_LISTAEX_COLORESITEM_H
#define DWL_LISTAEX_COLORESITEM_H
 
#include "..\DWLEstilos.h"

namespace DWL {
	namespace ControlesEx {

		//! Clase que contiene los colores para los items de la ListaEx
		class DWLListaEx_ColoresItem {
			public:	////////////////////////// Metodos publicos

										    //! Constructor por defecto.
										    /*! Este constructor enlaza todos los colores a la clase DWLEstilos.
												    \fn			DWLListaEx_ColoresItem(void);
												    \return		No devuelve nada.
										    */
										    DWLListaEx_ColoresItem(void) :
											    FondoNormal(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Normal),
											    FondoResaltado(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Resaltado),
											    FondoPresionado(			&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Presionado),
											    FondoSeleccionado(			&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Seleccionado),
											    FondoSeleccionadoResaltado(	&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_SeleccionadoResaltado),
											    TextoNormal(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_Normal),
											    TextoResaltado(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_Resaltado),
											    TextoPresionado(			&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_Presionado),
											    TextoSeleccionado(			&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_Seleccionado),
											    TextoSeleccionadoResaltado(	&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_SeleccionadoResaltado) {
										    };

										    //! Color del texto normal
			 DWL::SO::DWLEstilos_Color		TextoNormal;

										    //! Color del texto resaltado
			 DWL::SO::DWLEstilos_Color		TextoResaltado;

										    //! Color del texto selecionado
			 DWL::SO::DWLEstilos_Color		TextoSeleccionado;

										    //! Color del texto resaltado selecionado
			 DWL::SO::DWLEstilos_Color		TextoSeleccionadoResaltado;

										    //! Color del texto presionado
			 DWL::SO::DWLEstilos_Color		TextoPresionado;

										    //! Color del fondo normal
			 DWL::SO::DWLEstilos_Color		FondoNormal;
				
										    //! Color del fondo resaltado
			 DWL::SO::DWLEstilos_Color		FondoResaltado;

										    //! Color del fondo selecionado
			 DWL::SO::DWLEstilos_Color		FondoSeleccionado;

										    //! Color del fondo resaltado selecionado
			 DWL::SO::DWLEstilos_Color		FondoSeleccionadoResaltado;

										    //! Color del fondo presionado
			 DWL::SO::DWLEstilos_Color		FondoPresionado;
		};								    //
		////////////////////////////////////// Final ColoresDWLListaEx

    };
};

#endif
