/*! \file DWLBarraEx_Estilos.h
	\brief		 Archivo que contiene las definiciones para los estilos de la BarraEx.
    */ 
#ifndef DWL_BARRAEX_ESTILOS_H
#define DWL_BARRAEX_ESTILOS_H

#include "DWLBarraEx_Colores.h"

// Tipos de BarraEx posibles.
#define DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL	1
#define DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL		2
#define DWL_BARRAEX_PROGRESO_HORIZONTAL			3
#define DWL_BARRAEX_PROGRESO_VERTICAL			4


//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

		//! Clase que contiene los estilos para la BarraEx
		class DWLBarraEx_Estilos {
		 public : //////////////////////// Miembros publicos

									    //! Constructor por defecto
									    /*! Este constructor inicia los estilos de la BarraEx.
											    \fn			DWLBarraEx_Estilos(const UINT nOrientacion = DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL);
                                                \param[in]  Orientacion : Orientación y tipo de control (DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL , DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL, DWL_BARRAEX_PROGRESO_HORIZONTAL y DWL_BARRAEX_PROGRESO_VERTICAL)
											    \return		No devuelve nada.
									    */
									    DWLBarraEx_Estilos(const UINT nOrientacion = DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL) : Colores(), Orientacion(nOrientacion) {
									    };

									    //! Destructor
									    /*! Este constructor esta vacio.
											    \fn		   ~DWLBarraEx_Estilos(void);
											    \return		No devuelve nada.
									    */
								       ~DWLBarraEx_Estilos(void) {
									    };

									    //! Colores de este control.
		  DWLBarraEx_Colores			Colores;

                                        //! Borde para el control de 2 pixeles
//          bool                          Borde;

										//! Orientacion y tipo de la barra
										/*	Orientacion y tipo de la barra. Parametros posibles :
												DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL , DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL,
												DWL_BARRAEX_PROGRESO_HORIZONTAL , DWL_BARRAEX_PROGRESO_VERTICAL
												\fn			UINT Orientacion;
												\remarks	Necesitaras repintar el control si haces un cambio en la orientación
										*/
          UINT                          Orientacion;

		};							    //
		////////////////////////////////// Fin DWLBarraEx_Estilos

    };
};

#endif
