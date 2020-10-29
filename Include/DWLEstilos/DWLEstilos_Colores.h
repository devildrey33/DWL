/*! \file DWLEstilos_Colores.h
	\brief		 Archivo que contiene configuraciones globales para los colores de los controles extendidos.
    */ 
#ifndef DWL_ESTILOS_COLORES_H
#define DWL_ESTILOS_COLORES_H

#include "..\DWL.h"

#define DWL_COLOR_ROJO RGB(0, 255, 0)


//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres SO
    namespace SO {
        class DWLEstilos_Colores {
         public :
                                    DWLEstilos_Colores(void) :  VentanaEx_Borde_Claro(DWL_COLOR_ROJO),
                                                                VentanaEx_Borde_Oscuro(DWL_COLOR_ROJO),
                                                                VentanaEx_Fondo_DegradadoSuperior(DWL_COLOR_ROJO),
                                                                VentanaEx_Fondo_DegradadoInferior(DWL_COLOR_ROJO),
                                                                VentanaEx_Texto_TituloNormal(DWL_COLOR_ROJO),
                                                                VentanaEx_Texto_TituloSombra(DWL_COLOR_ROJO),
                                                                ControlEx_Borde_Normal(DWL_COLOR_ROJO),
                                                                ControlEx_Borde_Claro(DWL_COLOR_ROJO),
                                                                ControlEx_Borde_FocoRaton(DWL_COLOR_ROJO),
                                                                ControlEx_Fondo_Seleccionado(DWL_COLOR_ROJO),
                                                                ControlEx_Fondo_DegradadoSuperior(DWL_COLOR_ROJO),
                                                                ControlEx_Fondo_DegradadoInferior(DWL_COLOR_ROJO),
                                                                ControlEx_Fondo_DegradadoResaltado(DWL_COLOR_ROJO),
                                                                ControlEx_Texto_Normal(DWL_COLOR_ROJO),
                                                                ControlEx_Texto_Resaltado(DWL_COLOR_ROJO),
                                                                ControlEx_Texto_Presionado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Borde_Normal(DWL_COLOR_ROJO),
                                                                ContenedorEx_Borde_Resaltado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Borde_Seleccionado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Cursor(DWL_COLOR_ROJO),
                                                                ContenedorEx_Fondo_Claro(DWL_COLOR_ROJO),
                                                                ContenedorEx_Fondo_Normal(DWL_COLOR_ROJO),
                                                                ContenedorEx_Fondo_Desactivado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Fondo_Resaltado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Fondo_Presionado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Fondo_Seleccionado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Fondo_SeleccionadoResaltado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Fondo_SubSeleccionado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Fondo_SubSeleccionadoResaltado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Texto_Normal(DWL_COLOR_ROJO),
                                                                ContenedorEx_Texto_Resaltado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Texto_Presionado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Texto_Seleccionado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Texto_SeleccionadoResaltado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Texto_SubSeleccionado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Texto_SubSeleccionadoResaltado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Controles_Texto_Normal(DWL_COLOR_ROJO),
                                                                ContenedorEx_Controles_Texto_Resaltado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Controles_Texto_Presionado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Controles_Fondo_Normal(DWL_COLOR_ROJO),
                                                                ContenedorEx_Controles_Fondo_Resaltado(DWL_COLOR_ROJO),
                                                                ContenedorEx_Controles_Fondo_Presionado(DWL_COLOR_ROJO) {
                                    };
                                   ~DWLEstilos_Colores(void) { };
								    //! Color del borde claro para la VentanaEx
	      COLORREF					VentanaEx_Borde_Claro;
								    //! Color del borde oscuro para la VentanaEx
	      COLORREF					VentanaEx_Borde_Oscuro;
								    //! Color del fondo degradado superior para la VentanaEx
	      COLORREF					VentanaEx_Fondo_DegradadoSuperior;
								    //! Color del fondo degradado inferior para la VentanaEx
	      COLORREF					VentanaEx_Fondo_DegradadoInferior;
								    //! Color del texto para el titulo normal de la VentanaEx
	      COLORREF					VentanaEx_Texto_TituloNormal;
								    //! Color del texto para el titulo sombra de la VentanaEx
	      COLORREF					VentanaEx_Texto_TituloSombra;

         ///////////////////////////// ControlEx (Controles simples con degradados en el fondo. Ej : Boton, Scroll, Barra, etc..)
								    //! Color del borde normal para el ControlEx
	      COLORREF       			ControlEx_Borde_Normal;
								    //! Color del borde claro para el ControlEx
	      COLORREF       			ControlEx_Borde_Claro;
								    //! Color del borde cuando el control tiene el foco del raton (resaltado)
	      COLORREF       			ControlEx_Borde_FocoRaton;
								    //! Color del fondo degradado superior para el ControlEx
	      COLORREF      			ControlEx_Fondo_DegradadoSuperior;
								    //! Color del fondo degradado inferior para el ControlEx
	      COLORREF       			ControlEx_Fondo_DegradadoInferior;
								    //! Color del fondo degradado resaltado para el ControlEx
	      COLORREF      			ControlEx_Fondo_DegradadoResaltado;
								    //! Color del fondo seleccionado para el ControlEx
	      COLORREF       			ControlEx_Fondo_Seleccionado;
								    //! Color del texto normal para el ControlEx
	      COLORREF       			ControlEx_Texto_Normal;
								    //! Color del texto resaltado para el ControlEx
	      COLORREF      			ControlEx_Texto_Resaltado;
								    //! Color del texto presionado/desactivado para el ControlEx
	      COLORREF       			ControlEx_Texto_Presionado;

         ///////////////////////////// ContenedorEx (Controles complejos contenedores datos. Ej : Lista, Arbol, Edit, etc..)
								    //! Color del borde normal para el ContenedorEx
	      COLORREF       			ContenedorEx_Borde_Normal;
								    //! Color del borde resaltado para el ContenedorEx
	      COLORREF       			ContenedorEx_Borde_Resaltado;
								    //! Color del borde seleccionado para el ContenedorEx
	      COLORREF       			ContenedorEx_Borde_Seleccionado;
								    //! Color del cursor para el ContenedorEx
	      COLORREF       			ContenedorEx_Cursor;
								    //! Color del fondo claro para el ContenedorEx
	      COLORREF       			ContenedorEx_Fondo_Claro;
								    //! Color del fondo normal para el ContenedorEx
	      COLORREF       			ContenedorEx_Fondo_Normal;
									//! Color del fondo desactivado para el ContenedorEx
		  COLORREF					ContenedorEx_Fondo_Desactivado;
								    //! Color del fondo resaltado para el ContenedorEx
	      COLORREF       			ContenedorEx_Fondo_Resaltado;
								    //! Color del fondo presionado para el ContenedorEx
	      COLORREF       			ContenedorEx_Fondo_Presionado;
								    //! Color del fondo seleccionado para el ContenedorEx
	      COLORREF       			ContenedorEx_Fondo_Seleccionado;
								    //! Color del fondo seleccionado resaltado para el ContenedorEx
	      COLORREF       			ContenedorEx_Fondo_SeleccionadoResaltado;
								    //! Color del fondo sub-seleccionado para el ContenedorEx
	      COLORREF       			ContenedorEx_Fondo_SubSeleccionado;
								    //! Color del fondo sub-seleccionado resaltado para el ContenedorEx
	      COLORREF       			ContenedorEx_Fondo_SubSeleccionadoResaltado;
								    //! Color del texto normal para el ContenedorEx
	      COLORREF       			ContenedorEx_Texto_Normal;
								    //! Color del texto resaltado para el ContenedorEx
	      COLORREF       			ContenedorEx_Texto_Resaltado;
								    //! Color del texto presionado para el ContenedorEx
	      COLORREF       			ContenedorEx_Texto_Presionado;
								    //! Color del texto seleccionado para el ContenedorEx
	      COLORREF       			ContenedorEx_Texto_Seleccionado;
								    //! Color del texto seleccionado resaltado para el ContenedorEx
	      COLORREF       			ContenedorEx_Texto_SeleccionadoResaltado;
								    //! Color del texto sub-seleccionado para el ContenedorEx
	      COLORREF       			ContenedorEx_Texto_SubSeleccionado;
								    //! Color del texto sub-seleccionado resaltado para el ContenedorEx
	      COLORREF       			ContenedorEx_Texto_SubSeleccionadoResaltado;
								    //! Color del texto normal para un control dentro del ContenedorEx
	      COLORREF      			ContenedorEx_Controles_Texto_Normal;
								    //! Color del texto resaltado para un control dentro del ContenedorEx
	      COLORREF					ContenedorEx_Controles_Texto_Resaltado;
								    //! Color del texto presionado para un control dentro del ContenedorEx
	      COLORREF      			ContenedorEx_Controles_Texto_Presionado;
								    //! Color del fondo normal para un control dentro del ContenedorEx
	      COLORREF      			ContenedorEx_Controles_Fondo_Normal;
								    //! Color del fondo resaltado para un control dentro del ContenedorEx
	      COLORREF       			ContenedorEx_Controles_Fondo_Resaltado;
								    //! Color del fondo presionado para un control dentro del ContenedorEx
	      COLORREF					ContenedorEx_Controles_Fondo_Presionado;

                                    //! Operador que obtiene los colores de otra clase DWLEstilos_Colores
          DWLEstilos_Colores       &operator = (DWLEstilos_Colores &nEstiloColores) {
                                        VentanaEx_Borde_Claro                       = nEstiloColores.VentanaEx_Borde_Claro;
                                        VentanaEx_Borde_Oscuro                      = nEstiloColores.VentanaEx_Borde_Oscuro;
                                        VentanaEx_Fondo_DegradadoSuperior           = nEstiloColores.VentanaEx_Fondo_DegradadoSuperior;
                                        VentanaEx_Fondo_DegradadoInferior           = nEstiloColores.VentanaEx_Fondo_DegradadoInferior;
                                        VentanaEx_Texto_TituloNormal                = nEstiloColores.VentanaEx_Texto_TituloNormal;
                                        VentanaEx_Texto_TituloSombra                = nEstiloColores.VentanaEx_Texto_TituloSombra;
                                        ControlEx_Borde_Normal                      = nEstiloColores.ControlEx_Borde_Normal;
                                        ControlEx_Borde_Claro                       = nEstiloColores.ControlEx_Borde_Claro;
                                        ControlEx_Borde_FocoRaton                   = nEstiloColores.ControlEx_Borde_FocoRaton;
                                        ControlEx_Fondo_DegradadoSuperior           = nEstiloColores.ControlEx_Fondo_DegradadoSuperior;
                                        ControlEx_Fondo_DegradadoInferior           = nEstiloColores.ControlEx_Fondo_DegradadoInferior;
                                        ControlEx_Fondo_DegradadoResaltado          = nEstiloColores.ControlEx_Fondo_DegradadoResaltado;
                                        ControlEx_Fondo_Seleccionado                = nEstiloColores.ControlEx_Fondo_Seleccionado;
                                        ControlEx_Texto_Normal                      = nEstiloColores.ControlEx_Texto_Normal;
                                        ControlEx_Texto_Resaltado                   = nEstiloColores.ControlEx_Texto_Resaltado;
                                        ControlEx_Texto_Presionado                  = nEstiloColores.ControlEx_Texto_Presionado;
                                        ContenedorEx_Borde_Normal                   = nEstiloColores.ContenedorEx_Borde_Normal;
                                        ContenedorEx_Borde_Resaltado                = nEstiloColores.ContenedorEx_Borde_Resaltado;
                                        ContenedorEx_Borde_Seleccionado             = nEstiloColores.ContenedorEx_Borde_Seleccionado;
                                        ContenedorEx_Cursor                         = nEstiloColores.ContenedorEx_Cursor;
                                        ContenedorEx_Fondo_Claro                    = nEstiloColores.ContenedorEx_Fondo_Claro;
                                        ContenedorEx_Fondo_Normal                   = nEstiloColores.ContenedorEx_Fondo_Normal;
                                        ContenedorEx_Fondo_Desactivado              = nEstiloColores.ContenedorEx_Fondo_Desactivado;
                                        ContenedorEx_Fondo_Resaltado                = nEstiloColores.ContenedorEx_Fondo_Resaltado;
                                        ContenedorEx_Fondo_Presionado               = nEstiloColores.ContenedorEx_Fondo_Presionado;
                                        ContenedorEx_Fondo_Seleccionado             = nEstiloColores.ContenedorEx_Fondo_Seleccionado;
                                        ContenedorEx_Fondo_SeleccionadoResaltado    = nEstiloColores.ContenedorEx_Fondo_SeleccionadoResaltado;
                                        ContenedorEx_Fondo_SubSeleccionado          = nEstiloColores.ContenedorEx_Fondo_SubSeleccionado;
                                        ContenedorEx_Fondo_SubSeleccionadoResaltado = nEstiloColores.ContenedorEx_Fondo_SubSeleccionadoResaltado;
                                        ContenedorEx_Texto_Normal                   = nEstiloColores.ContenedorEx_Texto_Normal;
                                        ContenedorEx_Texto_Resaltado                = nEstiloColores.ContenedorEx_Texto_Resaltado;
                                        ContenedorEx_Texto_Presionado               = nEstiloColores.ContenedorEx_Texto_Presionado;
                                        ContenedorEx_Texto_Seleccionado             = nEstiloColores.ContenedorEx_Texto_Seleccionado;
                                        ContenedorEx_Texto_SeleccionadoResaltado    = nEstiloColores.ContenedorEx_Texto_SeleccionadoResaltado;
                                        ContenedorEx_Texto_SubSeleccionado          = nEstiloColores.ContenedorEx_Texto_SubSeleccionado;
                                        ContenedorEx_Texto_SubSeleccionadoResaltado = nEstiloColores.ContenedorEx_Texto_SubSeleccionadoResaltado;
                                        ContenedorEx_Controles_Texto_Normal         = nEstiloColores.ContenedorEx_Controles_Texto_Normal;
                                        ContenedorEx_Controles_Texto_Resaltado      = nEstiloColores.ContenedorEx_Controles_Texto_Resaltado;
                                        ContenedorEx_Controles_Texto_Presionado     = nEstiloColores.ContenedorEx_Controles_Texto_Presionado;
                                        ContenedorEx_Controles_Fondo_Normal         = nEstiloColores.ContenedorEx_Controles_Fondo_Normal;
                                        ContenedorEx_Controles_Fondo_Resaltado      = nEstiloColores.ContenedorEx_Controles_Fondo_Resaltado;
                                        ContenedorEx_Controles_Fondo_Presionado     = nEstiloColores.ContenedorEx_Controles_Fondo_Presionado;
                                        return *this;
                                    };
        };

    };
};

#endif
