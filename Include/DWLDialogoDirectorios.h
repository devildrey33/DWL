/*! \file		DWLDialogoDirectorios.h
	\brief		Archivo que contiene una clase para mostrar un dialogo para seleccionar una directorio del sistema.
	\author		devildrey33
	\date		Creado el [10/06/2004], ultima modificación el [05/10/2010]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es																			\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

*/
 
#ifndef DWL_DIALOGODIRECTORIOS_H
#define DWL_DIALOGODIRECTORIOS_H

#include "DWLString.h"
#include "DWL.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Ventanas
	namespace Ventanas {
		//! Clase que muestra un dialogo del sistema para seleccionar un directorio.
		class DWLDialogoDirectorios {
		  public : /////////////// Miembros publicos

								//! Constructor.
								/*!	Constructor por defecto.
										\fn		DWLDialogoDirectorios(void);
										\return	No devuelve nada.
								*/
								DWLDialogoDirectorios(void) { 
								};

								//! Constructor que muestra el dialogo.
								/*!	Constructor que muestra el dialogo.
										\fn			DWLDialogoDirectorios(const TCHAR *Titulo);
										\param[in]	Titulo : Cadena de caracteres con el titulo del dialogo
										\return		No devuelve nada.
								*/
								DWLDialogoDirectorios(const TCHAR *Titulo) { 
									MostrarDirectorios(Titulo); 
								};

								// DEPRECATED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
								//! Función que muestra el dialogo del sistema para seleccionar un directorio.
								/*!	Esta función muestra el dialogo del sistema para seleccionar un directorio.
										\fn			const TCHAR *MostrarDirectorios(const TCHAR *Titulo);
										\param[in]	Titulo : Cadena de caracteres con el titulo del dialogo
										\return		Devuelve la ruta del directorio seleccionado.
										\todo       Esta función usa API de windows DEPRECATED, hay que re-emplazarla y mantener las deprecated solo para VC6
								*/
			const TCHAR        *MostrarDirectorios(const TCHAR *Titulo);

								//! Función que devuelve el directorio seleccionado
								/*!	Esta funcion devuelve el directorio seleccionado
										\fn			inline const TCHAR *Directorio(void);
										\return		Devuelve una cadena de caracteres con el directorio seleccionado.
								*/
			inline const TCHAR *Directorio(void) {
									return _Directorio(); 
								};

		  private : ////////////// Miembros privados

								//! Directorio seleccionado
			DWL::DWLString	   _Directorio;
		};
	}
}


#endif // DWL_DIALOGOCOLORES_H


// Version 0.53 [15/08/2007]
// - Se ha solucionado un fallo en la clase DlgDirectorio que creaba una excepcion no valida al seleccionar "MI PC" como directorio

// Version 0.6  [01/10/2009]
// - Se ha añadido la opcion para que el dialogo abrir no tenga multiseleccion