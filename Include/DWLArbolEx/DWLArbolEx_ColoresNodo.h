/*! \file DWLArbolEx_ColoresNodo.h
	\brief		 Archivo que contiene las definiciones para los colores de los nodos del ArbolEx.
    */ 
#ifndef DWL_ARBOLEX_COLORESNODO_H
#define DWL_ARBOLEX_COLORESNODO_H

#include "..\DWLEstilos.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {
		//! Clase que contiene los colores de un nodo
		class DWLArbolEx_ColoresNodo {
		 public : //////////////////////// Miembros publicos

									    //! Constructor por defecto.
									    /*! Este constructor enlaza todos los colores a la clase DWLEstilos.
											    \fn			DWLArbolEx_ColoresNodo(void);
											    \return		No devuelve nada.
									    */
									    DWLArbolEx_ColoresNodo(void) :
										    FondoNormal(					&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Normal						),
										    FondoResaltado(					&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Resaltado					),
										    FondoPresionado(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Presionado					),
										    FondoSeleccionado(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Seleccionado				),
										    FondoSeleccionadoResaltado(		&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_SeleccionadoResaltado		),
										    FondoSubSeleccionado(			&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_SubSeleccionado			),
										    FondoSubSeleccionadoResaltado(	&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_SubSeleccionadoResaltado	),
										    TextoNormal(					&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_Normal						),
										    TextoResaltado(					&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_Resaltado					),
										    TextoPresionado(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_Presionado					),
										    TextoSeleccionado(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_Seleccionado				),
										    TextoSeleccionadoResaltado(		&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_SeleccionadoResaltado		),
										    TextoSubSeleccionado(			&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_SubSeleccionado			),
										    TextoSubSeleccionadoResaltado(	&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_SubSeleccionadoResaltado	),
										    PMTextoNormal(					&DWL::SO::DWLEstilos::Colores.ContenedorEx_Controles_Texto_Normal			),
										    PMTextoResaltado(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Controles_Texto_Resaltado		),
										    PMTextoPresionado(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Controles_Texto_Presionado		),
										    PMFondoNormal(					&DWL::SO::DWLEstilos::Colores.ContenedorEx_Controles_Fondo_Normal			),
										    PMFondoResaltado(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Controles_Fondo_Resaltado		),
										    PMFondoPresionado(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Controles_Fondo_Presionado		) {
									    };

										DWLArbolEx_ColoresNodo(DWLArbolEx_ColoresNodo &nColores) : 
											FondoNormal(					nColores.FondoNormal()						),
										    FondoResaltado(					nColores.FondoResaltado()					),
										    FondoPresionado(				nColores.FondoPresionado()					),
										    FondoSeleccionado(				nColores.FondoSeleccionado()				),
										    FondoSeleccionadoResaltado(		nColores.FondoSeleccionadoResaltado()		),
										    FondoSubSeleccionado(			nColores.FondoSubSeleccionado()				),
										    FondoSubSeleccionadoResaltado(	nColores.FondoSubSeleccionadoResaltado()	),
										    TextoNormal(					nColores.TextoNormal()						),
										    TextoResaltado(					nColores.TextoResaltado()					),
										    TextoPresionado(				nColores.TextoPresionado()					),
										    TextoSeleccionado(				nColores.TextoSeleccionado()				),
										    TextoSeleccionadoResaltado(		nColores.TextoSeleccionadoResaltado()		),
										    TextoSubSeleccionado(			nColores.TextoSubSeleccionado()				),
										    TextoSubSeleccionadoResaltado(	nColores.TextoSubSeleccionadoResaltado()	),
										    PMTextoNormal(					nColores.PMTextoNormal()					),
										    PMTextoResaltado(				nColores.PMTextoResaltado()					),
										    PMTextoPresionado(				nColores.PMTextoPresionado()				),
										    PMFondoNormal(					nColores.PMFondoNormal()					),
										    PMFondoResaltado(				nColores.PMFondoResaltado()					),
										    PMFondoPresionado(				nColores.PMFondoPresionado()				) {
										};

									    //! Color del fondo normal
         DWL::SO::DWLEstilos_Color		FondoNormal;

									    //! Color del fondo resaltado
		 DWL::SO::DWLEstilos_Color		FondoResaltado;

									    //! Color del fondo presionado
		 DWL::SO::DWLEstilos_Color		FondoPresionado;

									    //! Color del fondo selecionado
		 DWL::SO::DWLEstilos_Color		FondoSeleccionado;

									    //! Color del fondo selecionado resaltado
		 DWL::SO::DWLEstilos_Color		FondoSeleccionadoResaltado;

									    //! Color del fondo sub selecionado
		 DWL::SO::DWLEstilos_Color		FondoSubSeleccionado;

									    //! Color del fondo sub selecionado resaltado
		 DWL::SO::DWLEstilos_Color		FondoSubSeleccionadoResaltado;

									    //! Color del texto normal
		 DWL::SO::DWLEstilos_Color		TextoNormal;

									    //! Color del texto resaltado
		 DWL::SO::DWLEstilos_Color		TextoResaltado;

									    //! Color del texto presionado
		 DWL::SO::DWLEstilos_Color		TextoPresionado;

									    //! Color del texto selecionado
		 DWL::SO::DWLEstilos_Color		TextoSeleccionado;

									    //! Color del texto selecionado resaltado
		 DWL::SO::DWLEstilos_Color		TextoSeleccionadoResaltado;

									    //! Color del texto sub selecionado
		 DWL::SO::DWLEstilos_Color		TextoSubSeleccionado;

									    //! Color del texto sub selecionado resaltado
		 DWL::SO::DWLEstilos_Color		TextoSubSeleccionadoResaltado;

									    //! Color del texto normal (para el recuadro expandir contraer)
		 DWL::SO::DWLEstilos_Color		PMTextoNormal;

									    //! Color del texto resaltado (para el recuadro expandir contraer)
		 DWL::SO::DWLEstilos_Color		PMTextoResaltado;

									    //! Color del texto presionado (para el recuadro expandir contraer)
		 DWL::SO::DWLEstilos_Color		PMTextoPresionado;

									    //! Color del fondo normal (para el recuadro expandir contraer)
		 DWL::SO::DWLEstilos_Color		PMFondoNormal;

									    //! Color del fondo resaltado (para el recuadro expandir contraer)
		 DWL::SO::DWLEstilos_Color		PMFondoResaltado;

									    //! Color del fondo presionado (para el recuadro expandir contraer)
		 DWL::SO::DWLEstilos_Color		PMFondoPresionado;
		};							    //
		////////////////////////////////// DWLArbolEx_ColoresNodo


    };
};

#endif
