// COMENTADO COMO EL CULO
/*! \file DWLListaEx_Estilos.h
	\brief		 Archivo que contiene las definiciones para los estilos de la ListaEx.
    */
#ifndef DWL_LISTAEX_ESTILOS_H
#define DWL_LISTAEX_ESTILOS_H
 
#include "DWLListaEx_Colores.h"
#include "..\DWLEstilos.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

		class DWLListaEx_Fuentes {
		  public:
										DWLListaEx_Fuentes(void) { 
											Normal.Enlazar(DWL::SO::DWLEstilos::Fuentes.Tahoma13);
											SubRayada.Enlazar(DWL::SO::DWLEstilos::Fuentes.Tahoma13_SubRayada);
										};
			DWL::SO::DWLEstilos_Fuente	Normal;
			DWL::SO::DWLEstilos_Fuente	SubRayada;
		};

		//! Clase que contiene los estilos para el ArbolEx
        //! \remarks Necesitaras utilizar ArbolEx::ActualizarTodo() o ArbolEx_Nucleo::ArbolEx_ActualizarTodo() al realizar cualquier cambio para que este se vea reflejado correctamente
		class DWLListaEx_Estilos {
		 public : //////////////////////// Miembros publicos

									        //! Constructor por defecto
									        /*! Este constructor inicia los estilos del ArbolEx.
											        \fn			DWLListaEx_Estilos(const bool nPintarFondo = true, const bool nPintarBorde = true, const bool nPintarIconos = true, const bool nPintarLineas = true, const bool nMultiSeleccion = true, const bool nSubSeleccion = true, const bool nTransparencias = true);
                                                    \param[in]  nPintarBorde				: true para pintar el borde, false para no pintar nada.
                                                    \param[in]  nPintarIconos				: true para pintar los iconos, false para no pintar nada.
                                                    \param[in]  nPintarLineas				: true para pintar las lineas, false para no pintar nada.
                                                    \param[in]  nMultiseleccion				: true para habilitar la multiselección, false para des-habilitarla.
                                                    \param[in]  nSubSeleccion				: true para habilitar la sub-selección, false para des-habilitarla.
                                                    \param[in]  nTransparencias				: true para pintar transparencias en los nodos, false para pintarlos opacos.
                                                    \param[in]  nMostrarEncabezadosColumnas : true para mostrar las cabeceras de las columnas, false para no mostrar nada.
											        \return		No devuelve nada.
									        */
									        DWLListaEx_Estilos(/*const bool nPintarFondo = true,*/ const bool nPintarBorde = true, const bool nPintarIconos = true, const bool nPintarLineas = true, const bool nMultiSeleccion = true, const bool nSubSeleccion = true, const bool nTransparencias = true, const bool nMostrarEncabezadosColumnas = false) :
/*                                                
                                                
                                                PintarLineas(   nPintarLineas),
                                                SubSeleccion(   nSubSeleccion),*/
												PintarIconos(   nPintarIconos),												
												PintarBorde(    nPintarBorde),
                                                Transparencias( nTransparencias),
                                                MultiSeleccion( nMultiSeleccion),
												MostrarEncabezadosColumnas(nMostrarEncabezadosColumnas) {
									        };

									        //! Destructor
									        /*! Este constructor esta vacio.
											        \fn			DWLListaEx_Estilos(void);
											        \return		No devuelve nada.
									        */
	    							       ~DWLListaEx_Estilos(void) {
    									    };

                                            //! Pintar el borde
          bool                              PintarBorde;

                                            //! Pintar los iconos
          bool                              PintarIconos;

                                            //! Pintar las lineas
    //      bool                              PintarLineas;

                                            //! Multiselección activada/desactivada
          bool                              MultiSeleccion;

                                            //! Sub-selección activada/desactivada
        //  bool                              SubSeleccion;

											//! Ancho maximo para el item (solo valido en modo DWL_LISTAEX_FILAS_HORIZONTAL).
	      int			  				    AnchoMaximoItem;

											//! Modo de visionado (DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL, o DWL_LISTAEX_FILAS_HORIZONTAL)
		  int						 	    ModoVisionado;

                                            //! Pintar los nodos con transparencias
          bool                              Transparencias;

											//! Mostrar encabezados de las columnas (AÑADIR AL CONSTRUCTOR)
		  bool                              MostrarEncabezadosColumnas;

									        //! Colores de este control y todos sus nodos.
		  DWLListaEx_Colores	    		Colores;

									        //! Fuentes de este control y todos sus nodos.
		  DWLListaEx_Fuentes				Fuentes;
		};							        //
		////////////////////////////////////// Fin DWLArbolEx_Estilos

    };
};

#endif
