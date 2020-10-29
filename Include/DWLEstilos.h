/*! \file DWLEstilos.h
	\brief		 Archivo que contiene las configuraciones de colores para los controles extendidos.
    */
#ifndef DWL_ESTILOS_H
#define DWL_ESTILOS_H

#include ".\DWLEstilos\DWLEstilos_Colores.h"
#include ".\DWLEstilos\DWLEstilos_Color.h"
#include ".\DWLEstilos\DWLEstilos_Fuentes.h"
#include ".\DWLEstilos\DWLEstilos_Fuente.h"
 
//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres SO
    namespace SO {
        //! Clase que contiene los estilos para los controles extendidos
        class DWLEstilos {
         public: ///////////////////////////// Miembros publicos

											//! Constructor.
											/*! Constructor.
													\fn			DWLEstilos(void);
													\return		No devuelve nada.
											*/
                                            DWLEstilos(void) { };
                                            //! Colores para los controles extendidos
          static DWLEstilos_Colores         Colores;
										    //! Fuentes para los controles extendidos
          static DWLEstilos_Fuentes     	Fuentes;

										    //! Función que inicia las fuentes la primera vez que se consultan y son NULL.
										    /*! Esta función inicia las fuentes la primera vez que se consultan y son NULL.
												    \fn			satic void IniciarFuentes(void);
												    \return		No devuelve nada.
												    \remarks    Esta funcion se ejecuta automaticamente cuando se requiere una fuente y no esta disponible.
										    */
	      static void                       IniciarFuentes(void) {
												Fuentes.Tahoma13.Crear(TEXT("Tahoma"));
												Fuentes.Tahoma13_Negrita.Crear(TEXT("Tahoma"), 13, FW_BOLD);
												Fuentes.Tahoma13_Negrita_SubRayada.Crear(TEXT("Tahoma"), 13, FW_BOLD, false, true);
												Fuentes.Tahoma13_Negrita_Cursiva.Crear(TEXT("Tahoma"), 13, FW_BOLD, true);
												Fuentes.Tahoma13_Negrita_Cursiva_SubRayada.Crear(TEXT("Tahoma"), 13, FW_BOLD, true, true);
												Fuentes.Tahoma13_SubRayada.Crear(TEXT("Tahoma"), 13, FW_NORMAL, false, true);
												Fuentes.Tahoma13_Cursiva.Crear(TEXT("Tahoma"), 13, FW_NORMAL, true);
												Fuentes.Tahoma13_Cursiva_SubRayada.Crear(TEXT("Tahoma"), 13, FW_NORMAL, true, true);
	                                        };

										    //! Función para re-inicializar todos los colores.
										    /*! Esta función reinicializa todos los colores de la clase.
												    \fn			satic void Restaurar_Colores_Por_Defecto(void);
												    \return		No devuelve nada.
										    */
          static void                       Restaurar_Colores_Por_Defecto(void) {
		                                        Colores.VentanaEx_Borde_Claro						= RGB(190, 190, 190);
		                                        Colores.VentanaEx_Borde_Oscuro						= RGB(128, 128, 128); 
		                                        Colores.VentanaEx_Fondo_DegradadoSuperior			= RGB(200, 200, 200); 
		                                        Colores.VentanaEx_Fondo_DegradadoInferior			= RGB(100, 100, 100); 
		                                        Colores.VentanaEx_Texto_TituloNormal				= RGB(255, 255, 255);
		                                        Colores.VentanaEx_Texto_TituloSombra				= RGB(  0,   0,   0);
		                                        Colores.ControlEx_Borde_Normal						= RGB(120, 120, 120);
		                                        Colores.ControlEx_Borde_FocoRaton					= RGB(192, 192, 192);
		                                        Colores.ControlEx_Borde_Claro						= RGB(180, 180, 180);
		                                        Colores.ControlEx_Fondo_DegradadoSuperior			= RGB(192, 192, 192);
		                                        Colores.ControlEx_Fondo_DegradadoInferior			= RGB(128, 128, 128);
		                                        Colores.ControlEx_Fondo_DegradadoResaltado			= RGB(210, 210, 210);
		                                        Colores.ControlEx_Fondo_Seleccionado				= RGB(173, 214, 255); //
		                                        Colores.ControlEx_Texto_Normal						= RGB(255, 255, 255);
		                                        Colores.ControlEx_Texto_Resaltado					= RGB(255, 255,   0);
		                                        Colores.ControlEx_Texto_Presionado					= RGB(192, 192, 192);
		                                        Colores.ContenedorEx_Borde_Normal					= RGB(120, 120, 120);
		                                        Colores.ContenedorEx_Borde_Resaltado				= RGB(180, 180, 180);
		                                        Colores.ContenedorEx_Borde_Seleccionado				= RGB(100, 100,   0);
		                                        Colores.ContenedorEx_Cursor							= RGB(100, 100, 100);
		                                        Colores.ContenedorEx_Fondo_Claro					= RGB(255, 255, 255);
		                                        Colores.ContenedorEx_Fondo_Normal					= RGB(235, 235, 235);
		                                        Colores.ContenedorEx_Fondo_Desactivado				= RGB(210, 210, 210);
		                                        Colores.ContenedorEx_Fondo_Resaltado				= RGB(240, 240, 240);
		                                        Colores.ContenedorEx_Fondo_Presionado				= RGB(  0,   0, 100);
		                                        Colores.ContenedorEx_Fondo_Seleccionado				= RGB(173, 214, 255); // 
		                                        Colores.ContenedorEx_Fondo_SeleccionadoResaltado	= RGB(183, 224, 255); //
		                                        Colores.ContenedorEx_Fondo_SubSeleccionado			= RGB(100, 100, 235);
		                                        Colores.ContenedorEx_Fondo_SubSeleccionadoResaltado	= RGB(100, 100, 255);
		                                        Colores.ContenedorEx_Texto_Normal					= RGB(  0,   0,   0);
		                                        Colores.ContenedorEx_Texto_Resaltado				= RGB(100, 100,  64);
		                                        Colores.ContenedorEx_Texto_Presionado				= RGB(192, 192, 192);
		                                        Colores.ContenedorEx_Texto_Seleccionado				= RGB(  0,   0,   0);
		                                        Colores.ContenedorEx_Texto_SeleccionadoResaltado	= RGB(100, 100,   0);
		                                        Colores.ContenedorEx_Texto_SubSeleccionado			= RGB(  0,   0,   0);
		                                        Colores.ContenedorEx_Texto_SubSeleccionadoResaltado	= RGB(255, 255,   0);
		                                        Colores.ContenedorEx_Controles_Texto_Normal			= RGB(  0,   0,   0);
		                                        Colores.ContenedorEx_Controles_Texto_Resaltado		= RGB(255, 255, 255);
		                                        Colores.ContenedorEx_Controles_Texto_Presionado		= RGB(192, 192, 192);
		                                        Colores.ContenedorEx_Controles_Fondo_Normal			= RGB(250, 250, 250);
		                                        Colores.ContenedorEx_Controles_Fondo_Resaltado		= RGB(173, 214, 255); //
		                                        Colores.ContenedorEx_Controles_Fondo_Presionado		= RGB(128, 128, 128);	
	                                        };
        };

    };
};

#endif
