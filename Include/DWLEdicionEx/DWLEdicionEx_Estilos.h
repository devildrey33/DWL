/*! \file		DWLEdicionEx_Estilos.h
	\brief		Archivo que contiene las definiciones para los estilos del EdicionEx.
	\author		devildrey33
	\date		Creado el [25-09-2010], ultima modificación el [05/10/2010]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es																			\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n
*/
#ifndef DWL_EDICIONEX_ESTILOS_H
#define DWL_EDICIONEX_ESTILOS_H

//#include "..\DWLEstilos.h"
#include "DWLEdicionEx_Colores.h"
 

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

		//! Clase que contiene los estilos para el EdicionEx
		class DWLEdicionEx_Estilos {
		 public : //////////////////////////// Miembros publicos

									        //! Constructor por defecto
									        /*! Este constructor inicia los estilos del EdicionEx.
											        \fn			DWLEdicionEx_Estilos(const bool nPintarBorde = true, const bool nPintarIconos = true, const bool nPintarLineas = true, const bool nMultiSeleccion = true, const bool nSubSeleccion = true, const bool nTransparencias = true);
                                                    \param[in]  nPintarBorde		: true para pintar el borde, false para no pintar nada.
                                                    \param[in]  nMultiLinea			: true que el control acepte saltos de linea.
                                                    \param[in]  nTextoModificable   : true para poder modificar el texto del control.
											        \return		No devuelve nada.
									        */
									        DWLEdicionEx_Estilos(const bool nPintarBorde = true, const bool nMultiLinea = true, const bool nTextoModificable = true) :
												PintarBorde(nPintarBorde),
												MultiLinea(nMultiLinea),
												TextoModificable(nTextoModificable),
                                                Colores(),
                                                Fuente() {
									        };

                                            //! Pintar el borde
          bool                              PintarBorde;

                                            //! Permitir varias lineas de texto
          bool                              MultiLinea;

											//! Permitir modificaciones en el texto
		  bool                              TextoModificable;
		  // ESTILOS POR HACER :
		  // -ALINEACION
		  // -CARACTER PASSWORD
		  // -SIN BARRASCROLL H

									        //! Colores de este control.
		  DWLEdicionEx_Colores	    		Colores;

									        //! Este control solo necesita una fuente.
		  SO::DWLEstilos_Fuente				Fuente;
		};							        //
		////////////////////////////////////// Fin DWLEdicionEx_Estilos

    };
};

#endif