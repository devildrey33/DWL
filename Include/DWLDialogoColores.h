/*! \file		DWLDialogoColores.h
	\brief		Archivo que contiene una clase para mostrar un dialogo para seleccionar un color del sistema.
	\author		devildrey33
	\date		Creado el [10/06/2004], ultima modificación el [05/10/2010]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es																			\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

*/ 

#ifndef DWL_DIALOGOCOLORES_H
#define DWL_DIALOGOCOLORES_H

//#pragma warning( disable : 4786 )
//#include <vector>
//#include "DWLString.h"
#include "DWL.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Ventanas
	namespace Ventanas {
		//! Clase para mostrar un dialogo para seleccionar un color del sistema
		class DWLDialogoColores {
		  public : /////////// Miembros publicos

							//! Constructor.
							/*!	Constructor por defecto.
									\fn		DWLDialogoColores(void);
									\return	No devuelve nada.
							*/
							DWLDialogoColores(void) { 
							};

							//! Función que muestra el diálogo seleccionar un color.
							/*!	Función que muestra el diálogo seleccionar un color.
									\fn			COLORREF MostrarColores(void);
									\return		Devuelve el color selecionado.
							*/
			COLORREF		MostrarColores(void);

							//! Función que devuelve el color seleccionado
							/*!	Esta funcion devuelve el color seleccionado
									\fn			inline COLORREF	Color(void);
									\return		Devuelve una COLORREF con el color seleccionado.
							*/
			inline COLORREF	Color(void) {	return _Color;		};

		  private : ////////// Miembros privados

							//! Color seleccionado
			COLORREF       _Color;
		};

	}
}


#endif // DWL_DIALOGOCOLORES_H


// Version 0.53 [15/08/2007]
// - Se ha solucionado un fallo en la clase DlgDirectorio que creaba una excepcion no valida al seleccionar "MI PC" como directorio

// Version 0.6  [01/10/2009]
// - Se ha añadido la opcion para que el dialogo abrir no tenga multiseleccion