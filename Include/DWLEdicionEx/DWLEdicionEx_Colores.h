/*! \file		DWLEdicionEx_Colores.h
	\brief		Archivo que contiene las definiciones para los colores del EdicionEx.
	\author		devildrey33
	\date		Creado el [25-09-2010], ultima modificación el [05/10/2010]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es																			\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n
*/
#ifndef DWL_EDICIONEX_COLORES_H
#define DWL_EDICIONEX_COLORES_H
 
#include "..\DWLEstilos.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {
		//! Clase que contiene los colores para el EdicionEx
		class DWLEdicionEx_Colores {
		   public : ////////////////////////// Miembros publicos

											//! Constructor por defecto.
											/*! Este constructor enlaza todos los colores a la clase DWLEstilos.
													\fn			DWLEdicionEx_Colores(void);
													\return		No devuelve nada.
											*/
											DWLEdicionEx_Colores(void) :
												Borde(				&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_Normal),
												BordeSeleccionado(	&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_FocoRaton),
												Fondo(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Normal),
												FondoDesactivado(	&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Desactivado),
												FondoSeleccionado(	&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Seleccionado),
												Texto(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_Normal),
												TextoDesactivado(	&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_Presionado),
												Cursor(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Cursor) {
											};
										
											//! Color del fondo normal
			DWL::SO::DWLEstilos_Color		Fondo;

											//! Color del fondo normal
			DWL::SO::DWLEstilos_Color		FondoDesactivado;

											//! Color del fondo seleccionado (cuadrar de forma que el texto se vea bien igual)
			DWL::SO::DWLEstilos_Color		FondoSeleccionado;

											//! Color del texto
			DWL::SO::DWLEstilos_Color		Texto;

											//! Color del texto desactivado
			DWL::SO::DWLEstilos_Color		TextoDesactivado;

											//! Color del borde normal
			DWL::SO::DWLEstilos_Color		Borde;

											//! Color del borde seleccionado / resaltado
			DWL::SO::DWLEstilos_Color		BordeSeleccionado;

											//! Color del cursor
			DWL::SO::DWLEstilos_Color		Cursor;
		};

	};
};

#endif