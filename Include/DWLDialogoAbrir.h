/*! \file		DWLDialogoAbrir.h
	\brief		Archivo que contiene una clase para mostrar el dialogo abrir del sistema.
	\author		devildrey33
	\date		Creado el [10/06/2004], ultima modificación el [05/10/2010]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es																			\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

*/
 
#ifndef DWL_DIALOGOABRIR_H
#define DWL_DIALOGOABRIR_H

//#pragma warning( disable : 4786 )
#include <vector>
#include "DWLString.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Ventanas
	namespace Ventanas {
		//! Clase para mostrar un dialogo abrir del sistema
		class DWLDialogoAbrir {
	  	  public : /////////////////////////// Miembros publicos

											//! Constructor.
											/*!	Constructor por defecto.
													\fn		DWLDialogoAbrir(void);
													\return	No devuelve nada.
											*/
											DWLDialogoAbrir(void) { 
											};

											//! Constructor que muestra el diálogo.
											/*!	Constructor que muestra el diálogo directamente según los parametros especificados.
													\fn			DWLDialogoAbrir(const TCHAR *PathSh, const TCHAR *Filtro, const TCHAR *Titulo, const bool MultiSeleccion = true, HWND hWndPadre = NULL);
													\param[in]	PathSh			: Ruta inicial desde donde empezara el dialogo abrir
													\param[in]  Filtro			: Filtro de archivos
													\param[in]  Titulo			: Titulo del dialogo
													\param[in]  MultiSeleccion	: Habilitar multiselección
													\param[in]  hWndPadre		: Ventana padre, puede ser NULL. Si especificamos una ventana padre, esta se desactivara mientras el dialogo este activo.
													\return		No devuelve nada.
													\remarks    Filtro debera estar formateado de la siguiente forma :\n
																\code Todos los archivos\0*.*\0\0 \endcode

																Observad que primero hay un string con el nombre del filtro, luego el tipo de filtro, y por ultimo termina con un doble caracter <b>\\0</b>. \n\n
																Si por ejemplo queremos tener un filtro para documentos de texto debemos construirlo de una forma similar a este : \n
																\code Todos los archivos\0*.*\0Documentos de texto\0*.doc;*.txt;*.rtf\0\0 \endcode
																Observad que esta vez hemos añadido 3 tipos de archivo para el filtro Documentos de texto, esos tipos de archivo deben estar separados por el caracter <b>;</b>
											*/
											DWLDialogoAbrir(const TCHAR *PathSh, const TCHAR *Filtro, const TCHAR *Titulo, const bool MultiSeleccion = true, HWND hWndPadre = NULL) { 
						 						MostrarAbrir(PathSh, Filtro, Titulo, MultiSeleccion, hWndPadre); 
											};

											//! Función que muestra el diálogo para abrir archivos.
											/*!	Función que muestra el diálogo para abrir archivos según los parametros especificados.
													\fn			UINT MostrarAbrir(const TCHAR *PathSh, const TCHAR *Filtro, const TCHAR *Titulo, const bool MultiSeleccion = true, HWND hWndPadre = NULL) {
													\param[in]	PathSh			: Ruta inicial desde donde empezara el dialogo abrir
													\param[in]  Filtro			: Filtro de archivos
													\param[in]  Titulo			: Titulo del dialogo
													\param[in]  MultiSeleccion	: Habilitar multiselección
													\param[in]  hWndPadre		: Ventana padre, puede ser NULL. Si especificamos una ventana padre, esta se desactivara mientras el dialogo este activo.
													\return		Devuelve el numero de archivos seleccionados.
													\remarks    Filtro debera estar formateado de la siguiente forma :\n
																\code Todos los archivos\0*.*\0\0 \endcode
																Observad que primero hay un string con el nombre del filtro, luego el tipo de filtro, y por ultimo termina con un doble caracter <b>\\0</b>. \n\n
																Si por ejemplo queremos tener un filtro para documentos de texto debemos construirlo de una forma similar a este : \n
																\code Todos los archivos\0*.*\0Documentos de texto\0*.doc;*.txt;*.rtf\0\0 \endcode
																Observad que esta vez hemos añadido 3 tipos de archivo para el filtro Documentos de texto, esos tipos de archivo deben estar separados por el caracter <b>;</b>
											*/
		    UINT							MostrarAbrir(const TCHAR *PathSh, const TCHAR *Filtro, const TCHAR *Titulo, const bool MultiSeleccion = true, HWND hWndPadre = NULL); 

											//! Función que devuelve el total de archivos seleccionados
											/*!	Esta funcion devuelve el total de archivos seleccionados.
													\fn		inline UINT TotalArchivos(void);
													\return	Devuelve el total de archivos seleccionados.
													\sa		Archivos(), operator [].
											*/
			inline UINT						TotalArchivos(void) {
												return _Archivos.size();
											}

											//! Función que devuelve la ruta del archivo especificado
											/*!	Esta funcion devuelve la ruta del archivo especificado en el parametro Pos
													\fn			inline const TCHAR *Archivos(const int Pos)
													\param[in]	Pos : Posición en el array de archivos seleccionados
													\return		Devuelve una cadena de caracteres con la ruta del archivo.
													\sa			TotalArchivos().
											*/
			inline const TCHAR             *Archivos(const int Pos) { 
												return _Archivos[Pos].Texto(); 
											};

											//! Operador que devuelve la ruta del archivo especificado
											/*!	Esta operador devuelve la ruta del archivo especificado en el parametro Pos
													\fn			inline const TCHAR *operator [] (const int Pos);
													\param[in]	Pos : Posición en el array de archivos seleccionados
													\return		Devuelve una cadena de caracteres con la ruta del archivo.
													\sa			TotalArchivos().
											*/
			inline const TCHAR        	   *operator [] (const int Pos) { 
												return _Archivos[Pos].Texto(); 
											};

		  private : ////////////////////////// Miembros privados
											
											//! Vector de archivos seleccionados con las rutas completas
			std::vector<DWL::DWLString>    _Archivos;
		};




	}
}


#endif // DWL_DIALOGOSCOMUNES_H

// Version 0.6  [01/10/2009]
// - Se ha añadido la opcion para des-habilitar la multiselección en el dialogo abrir

// Version 0.53 [15/08/2007]
// - Se ha solucionado un fallo en la clase DlgDirectorio que creaba una excepcion no valida al seleccionar "MI PC" como directorio

