/*! \file		DWLDialogoFuentes.h
	\brief		Archivo que contiene una clase para mostrar un dialogo para seleccionar una fuente del sistema.
	\author		devildrey33
	\date		Creado el [10/06/2004], ultima modificación el [05/10/2010]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es																			\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

*/
 
#ifndef DWL_DIALOGOFUENTES_H
#define DWL_DIALOGOFUENTES_H

//#pragma warning( disable : 4786 )
//#include <vector>
//#include "DWLString.h"
#include "DWL.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Ventanas
	namespace Ventanas {
		//! Clase que muestra el dialogo para seleccionar una fuente del sistema
		class DWLDialogoFuentes {
		  public : /////////// Miembros publicos

							//! Constructor.
							/*!	Constructor por defecto.
									\fn		DWLDialogoFuentes(void);
									\return	No devuelve nada.
							*/
							DWLDialogoFuentes(void) { 
							};

							//! Función que muestra el diálogo seleccionar una fuente.
							/*!	Función que muestra el diálogo seleccionar una fuente.
									\fn			LOGFONT MostrarFuentes(void);
									\return		Devuelve la fuente selecionada.
							*/
			LOGFONT			MostrarFuentes(void);

							//! Función que devuelve la fuente seleccionada
							/*!	Esta funcion devuelve la fuente seleccionada
									\fn			inline LOGFONT	Fuente(void);
									\return		Devuelve un LOGFONT con la fuente seleccionada.
							*/
			inline LOGFONT	Fuente(void) { 
								return _Fuente; 
							};

		  private: /////////// Miembros privados

							//! Fuente seleccionada
			LOGFONT        _Fuente;
		};
	}
}


#endif // DWL_DIALOGOCOLORES_H


// Version 0.53 [15/08/2007]
// - Se ha solucionado un fallo en la clase DlgDirectorio que creaba una excepcion no valida al seleccionar "MI PC" como directorio

// Version 0.6  [01/10/2009]
// - Se ha añadido la opcion para que el dialogo abrir no tenga multiseleccion