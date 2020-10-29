/*! \file		DWLDialogoGuardar.cpp
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
 
#ifndef DWL_DIALOGOGUARDAR_CPP
#define DWL_DIALOGOGUARDAR_CPP

#include "DWLDialogoGuardar.h"
#include <commdlg.h>
#include <shlobj.h>             // Libreria para los objetos Shell

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Ventanas
	namespace Ventanas {

			//! Función que muestra el diálogo para guardar archivos.
			/*!	Función que muestra el diálogo para guardar archivos según los parametros especificados.
					\fn			UINT MostrarAbrir(const TCHAR *Path, const TCHAR *Filtro, const TCHAR *Titulo) {
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
			const TCHAR *DWLDialogoGuardar::MostrarGuardar(const TCHAR *Path, const TCHAR *Filtro, const TCHAR *Titulo) { 
				OPENFILENAME ofn; 
				TCHAR szFile[MAX_PATH +1];
				TCHAR UltimoDir[MAX_PATH +1];
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = NULL; 
				ofn.lpstrFile = szFile;
				ofn.lpstrTitle = Titulo;
				ofn.lpstrFile[0] = 0;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = Filtro;
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL; 
				ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT;
				_Archivo = TEXT("");
				GetCurrentDirectory(MAX_PATH + 1, UltimoDir);
				SetCurrentDirectory(Path);
				if (GetSaveFileName(&ofn) == TRUE)	_Archivo = szFile; 
				else								_Archivo = TEXT("");
				SetCurrentDirectory(UltimoDir);
				return _Archivo();
			}; 

	}
}


#endif // DWL_DIALOGOSCOMUNES_CPP
