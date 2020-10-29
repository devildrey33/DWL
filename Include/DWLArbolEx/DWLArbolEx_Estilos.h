/*! \file DWLArbolEx_Estilos.h
	\brief		 Archivo que contiene las definiciones para los estilos del ArbolEx.
    */ 
#ifndef DWL_ARBOLEX_ESTILOS_H
#define DWL_ARBOLEX_ESTILOS_H

#include "DWLArbolEx_Colores.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

		class DWLArbolEx_Fuentes {
		  public:
											DWLArbolEx_Fuentes(void) { 
												Normal.Enlazar(DWL::SO::DWLEstilos::Fuentes.Tahoma13);
												SubRayada.Enlazar(DWL::SO::DWLEstilos::Fuentes.Tahoma13_SubRayada);
											};
											DWLArbolEx_Fuentes(DWLArbolEx_Fuentes &nFuentes) : Normal(nFuentes.Normal), SubRayada(nFuentes.SubRayada) {	};
			DWL::SO::DWLEstilos_Fuente		Normal;
			DWL::SO::DWLEstilos_Fuente		SubRayada;
		};


		//! Clase que contiene los estilos para el ArbolEx
		//  Necesitaras utilizar ArbolEx::ActualizarTodo() o ArbolEx_Nucleo::ArbolEx_ActualizarTodo() al realizar cualquier cambio para que este se vea reflejado correctamente
		class DWLArbolEx_Estilos {
		 public : //////////////////////// Miembros publicos

									        //! Constructor por defecto
									        /*! Este constructor inicia los estilos del ArbolEx.
											        \fn			DWLArbolEx_Estilos(const bool nPintarBorde = true, const bool nPintarIconos = true, const bool nPintarLineas = true, const bool nMultiSeleccion = true, const bool nSubSeleccion = true, const bool nTransparencias = true);
                                                    \param[in]  nPintarBorde    : true para pintar el borde, false para no pintar nada.
                                                    \param[in]  nPintarIconos   : true para pintar los iconos, false para no pintar nada.
                                                    \param[in]  nPintarLineas   : true para pintar las lineas, false para no pintar nada.
                                                    \param[in]  nMultiseleccion : true para habilitar la multiselección, false para des-habilitarla.
                                                    \param[in]  nSubSeleccion   : true para habilitar la sub-selección, false para des-habilitarla.
                                                    \param[in]  nTransparencias : true para pintar transparencias en los nodos, false para pintarlos opacos.
											        \return		No devuelve nada.
									        */
									        DWLArbolEx_Estilos(const bool nPintarBorde = true, const bool nPintarIconos = true, const bool nPintarLineas = true, const bool nMultiSeleccion = true, const bool nSubSeleccion = true, const bool nTransparencias = true) :
                                                PintarBorde(    nPintarBorde),
                                                PintarIconos(   nPintarIconos),
                                                PintarLineas(   nPintarLineas),
                                                MultiSeleccion( nMultiSeleccion),
                                                SubSeleccion(   nSubSeleccion),
                                                Transparencias( nTransparencias),
                                                Colores() {
									        };

										    //! Miembro que determina si se tiene que pintar el borde.
										   	/*! Miembro que determina si se tiene que pintar el borde.
													\fn       bool PintarBorde;
													\remarks  Necesitaras utilizar DWLArbolEx::ActualizarTodo() o DWLArbolEx_Nucleo::ArbolEx_ActualizarTodo() si modificas este miembro.
											*/
          bool                              PintarBorde;

										   	//! Miembro que determina si se tienen que pintar iconos en los nodos
										   	/*! Miembro que determina si se tienen que pintar iconos en los nodos
													\fn       bool PintarIconos;
													\remarks  Necesitaras utilizar DWLArbolEx::ActualizarTodo() o DWLArbolEx_Nucleo::ArbolEx_ActualizarTodo() si modificas este miembro.
											*/
          bool                              PintarIconos;

										   	//! Miembro que determina si se tienen que pintar las lineas que enlazan los nodos
										   	/*! Miembro que determina si se tienen que pintar las lineas que enlazan los nodos
													\fn       bool PintarLineas;
													\remarks  Necesitaras utilizar DWLArbolEx::ActualizarTodo() o DWLArbolEx_Nucleo::ArbolEx_ActualizarTodo() si modificas este miembro.
											*/
          bool                              PintarLineas;

										   	//! Miembro que determina si la multiselección se encuentra habilitada
										   	/*! Miembro que determina si la multiselección se encuentra habilitada
													\fn       bool MultiSeleccion;
													\remarks  Necesitaras utilizar DWLArbolEx::ActualizarTodo() o DWLArbolEx_Nucleo::ArbolEx_ActualizarTodo() si modificas este miembro.
											*/
          bool                              MultiSeleccion;

										   	//! Miembro que determina si la subselección se encuentra habilitada
										   	/*! Miembro que determina si la subselección se encuentra habilitada
													\fn       bool SubSeleccion;
													\remarks  Necesitaras utilizar DWLArbolEx::ActualizarTodo() o DWLArbolEx_Nucleo::ArbolEx_ActualizarTodo() si modificas este miembro.
											*/
          bool                              SubSeleccion;

										   	//! Miembro que determina si hay que pintar transparencias
										   	/*! Miembro que determina si hay que pintar transparencias
													\fn       bool Transparencias;
													\remarks  Necesitaras utilizar DWLArbolEx::ActualizarTodo() o DWLArbolEx_Nucleo::ArbolEx_ActualizarTodo() si modificas este miembro.
											*/
          bool                              Transparencias;

										   	//! Clase que contiene todos los colores del ArbolEx
										   	/*! Clase que contiene todos los colores del ArbolEx
													\fn       DWLArbolEx_Colores Colores;
													\remarks  Si desactivas las transparencias no se pintara la imagen de fondo. Necesitaras utilizar DWLArbolEx::ActualizarTodo() o DWLArbolEx_Nucleo::ArbolEx_ActualizarTodo() si modificas este miembro.
											*/
		  DWLArbolEx_Colores	    		Colores;

										   	//! Clase que contiene todos las fuentes del ArbolEx
										   	/*! Clase que contiene todos las fuentes del ArbolEx
													\fn       DWLArbolEx_Fuentes Fuentes;
													\remarks  Necesitaras utilizar DWLArbolEx::ActualizarTodo() o DWLArbolEx_Nucleo::ArbolEx_ActualizarTodo() si modificas este miembro.
											*/
		  DWLArbolEx_Fuentes				Fuentes;
		};							        //
		////////////////////////////////////// Fin DWLArbolEx_Estilos

    };
};

#endif
