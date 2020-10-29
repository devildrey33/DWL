/*! \file DWLBotonEx_Estilos.h
	\brief		 Archivo que contiene las definiciones para los estilos del BotonEx.
    */ 
#ifndef DWL_BOTONEX_ESTILOS_H
#define DWL_BOTONEX_ESTILOS_H

#include "DWLBotonEx_Colores.h"



//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

		class DWLBotonEx_Fuentes {
		  public:
										DWLBotonEx_Fuentes(void) {
											Normal.Enlazar(DWL::SO::DWLEstilos::Fuentes.Tahoma13);
											SubRayada.Enlazar(DWL::SO::DWLEstilos::Fuentes.Tahoma13_SubRayada);
										};
			DWL::SO::DWLEstilos_Fuente	Normal;
			DWL::SO::DWLEstilos_Fuente	SubRayada;
		};

		//! Clase que contiene los estilos para el BotonEx
		class DWLBotonEx_Estilos {
		 public : //////////////////////////// Miembros publicos
									        //! Constructor por defecto
									        /*! Este constructor inicia los estilos del BotonEx.
											        \fn			DWLBotonEx_Estilos(const UINT nBorde = 1);
                                                    \param[in]  Borde       : Borde para el control (1 PIXEL DE BORDE, 2 PIXELES DE BORDE)
                                                    \param[in]  Orientacion : Orientación y tipo de control (DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL , DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL, DWL_BARRAEX_PROGRESO_HORIZONTAL y DWL_BARRAEX_PROGRESO_VERTICAL)
											        \return		No devuelve nada.
									        */
									        DWLBotonEx_Estilos(const UINT nBorde = 1) : Borde(nBorde), Colores(), Fuentes() {
									        };

									        //! Colores de este control.
											/*! Clase que contiene los colores de este control.
													\fn			DWLBotonEx_Colores Colores;
													\remarks	Necesitaras repintar el control si modificas este miembro.
											*/
		  DWLBotonEx_Colores		    	Colores;

									        //! Fuentes de este control.
											/*! Clase que contiene las fuentes de este control.
													\fn			DWLBotonEx_Fuentes Fuentes;
													\remarks	Necesitaras repintar el control si modificas este miembro.
											*/
		  DWLBotonEx_Fuentes				Fuentes;

                                            //! Borde para el control (0 SIN BORDE, 1 PIXEL DE BORDE, 2 PIXELES DE BORDE)
											/*! Borde para el control (0 SIN BORDE, 1 PIXEL DE BORDE, 2 PIXELES DE BORDE)
													\fn			UINT Borde;
													\remarks	Necesitaras repintar el control si modificas este miembro.
											*/
          UINT                              Borde;

		};							        //
		////////////////////////////////////// Fin DWLBarraEx_Estilos

    };
};

#endif
