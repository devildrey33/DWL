/*! \file		DWLDialogoGuardar.h
	\brief		Archivo que contiene una clase para mostrar el dialogo guardar del sistema.
	\author		devildrey33
	\date		Creado el [10/06/2004], ultima modificación el [05/10/2010]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es																			\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

*/
 

#ifndef DWL_DIALOGOGUARDAR_H
#define DWL_DIALOGOGUARDAR_H

//#pragma warning( disable : 4786 )
//#include <vector>
#include "DWLString.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Ventanas
	namespace Ventanas {
		//! Clase para mostrar un dialogo guardar del sistema
		class DWLDialogoGuardar {
		  public : /////////////// Miembros publicos

								//! Constructor.
								/*!	Constructor por defecto.
										\fn		DWLDialogoGuardar(void);
										\return	No devuelve nada.
								*/
								DWLDialogoGuardar(void)	{ 
								};


								//! Constructor que muestra el diálogo.
								/*!	Constructor que muestra el diálogo directamente según los parametros especificados.
										\fn			DWLDialogoGuardar(const TCHAR *Path, const TCHAR *Filtro, const TCHAR *Titulo) 
										\param[in]	Path			: Ruta inicial desde donde empezara el dialogo guardar
										\param[in]  Filtro			: Filtro de archivos
										\param[in]  Titulo			: Titulo del dialogo
										\return		No devuelve nada.
										\remarks    Filtro debera estar formateado de la siguiente forma :\n
													\code Todos los archivos\0*.*\0\0 \endcode

													Observad que primero hay un string con el nombre del filtro, luego el tipo de filtro, y por ultimo termina con un doble caracter <b>\\0</b>. \n\n
													Si por ejemplo queremos tener un filtro para documentos de texto debemos construirlo de una forma similar a este : \n
													\code Todos los archivos\0*.*\0Documentos de texto\0*.doc;*.txt;*.rtf\0\0 \endcode
													Observad que esta vez hemos añadido 3 tipos de archivo para el filtro Documentos de texto, esos tipos de archivo deben estar separados por el caracter <b>;</b>
								*/
								DWLDialogoGuardar(const TCHAR *Path, const TCHAR *Filtro, const TCHAR *Titulo) { 
									MostrarGuardar(Path, Filtro, Titulo); 
								};

								//! Función que muestra el diálogo para guardar archivos.
								/*!	Función que muestra el diálogo para guardar archivos según los parametros especificados.
										\fn			UINT MostrarAbrir(const TCHAR *Path, const TCHAR *Filtro, const TCHAR *Titulo);
										\param[in]	Path 			: Ruta inicial desde donde empezara el dialogo guardar
										\param[in]  Filtro			: Filtro de archivos
										\param[in]  Titulo			: Titulo del dialogo
										\return		Devuelve el archivo selecionado.
										\remarks    Filtro debera estar formateado de la siguiente forma :\n
													\code Todos los archivos\0*.*\0\0 \endcode
													Observad que primero hay un string con el nombre del filtro, luego el tipo de filtro, y por ultimo termina con un doble caracter <b>\\0</b>. \n\n
													Si por ejemplo queremos tener un filtro para documentos de texto debemos construirlo de una forma similar a este : \n
													\code Todos los archivos\0*.*\0Documentos de texto\0*.doc;*.txt;*.rtf\0\0 \endcode
													Observad que esta vez hemos añadido 3 tipos de archivo para el filtro Documentos de texto, esos tipos de archivo deben estar separados por el caracter <b>;</b>
								*/
			const TCHAR        *MostrarGuardar(const TCHAR *Path, const TCHAR *Filtro, const TCHAR *Titulo);

								//! Función que devuelve la ruta del archivo seleccionado
								/*!	Esta funcion devuelve la ruta del archivo seleccionado
										\fn			inline const TCHAR *Archivo(void)
										\return		Devuelve una cadena de caracteres con la ruta del archivo.
								*/
			inline const TCHAR *Archivo(void) {
									return _Archivo(); 
								};

		  private : ////////////// Miembros privados

								//! DWLString que guarda el archivo seleccionado en el dialogo guardar
			DWL::DWLString     _Archivo;
		};

	}
}


#endif // DWL_DIALOGOSCOMUNES_H


// Version 0.53 [15/08/2007]
// - Se ha solucionado un fallo en la clase DlgDirectorio que creaba una excepcion no valida al seleccionar "MI PC" como directorio

// Version 0.6  [01/10/2009]
// - Se ha añadido la opcion para que el dialogo abrir no tenga multiseleccion