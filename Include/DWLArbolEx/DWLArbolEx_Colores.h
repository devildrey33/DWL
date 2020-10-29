/*! \file DWLArbolEx_Colores.h
	\brief		 Archivo que contiene las definiciones para los colores del ArbolEx.
    */ 
#ifndef DWL_ARBOLEX_COLORES_H
#define DWL_ARBOLEX_COLORES_H

#include "DWLArbolEx_ColoresNodo.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

		//! Clase que contiene los colores para el ArbolEx
		class DWLArbolEx_Colores {
		public : ///////////////////////////// Miembros publicos

									        //! Constructor por defecto
									        /*! Este constructor enlaza todos los colores a la clase DWLEstilos.
											        \fn			DWLArbolEx_Colores(void);
											        \return		No devuelve nada.
									        */
									        DWLArbolEx_Colores(void) :
										        Lineas(			&DWL::SO::DWLEstilos::Colores.ContenedorEx_Cursor				),
										        BordeSeleccion(	&DWL::SO::DWLEstilos::Colores.ContenedorEx_Borde_Seleccionado	),
										        Fondo(			&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Normal			),
										        Borde(			&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_Normal			),
										        BordeClaro(		&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_FocoRaton			),
										        ColoresNodo() {
									        };

									        //! Color del borde del control
         DWL::SO::DWLEstilos_Color			Borde;

									        //! Color del borde claro del control
		 DWL::SO::DWLEstilos_Color 			BordeClaro;

									        //! Color del fondo normal
		 DWL::SO::DWLEstilos_Color			Fondo;

									        //! Color del borde de la selecion
		 DWL::SO::DWLEstilos_Color			BordeSeleccion;

								        	//! Color de las lineas
		 DWL::SO::DWLEstilos_Color 			Lineas;

									        //! Colores generales para los nodos
		 DWLArbolEx_ColoresNodo		        ColoresNodo;
		};							        //
		////////////////////////////////////// Fin DWLArbolEx_Colores

    };
};

#endif
