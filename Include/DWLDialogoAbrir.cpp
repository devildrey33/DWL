/*! \file		DWLDialogoAbrir.cpp
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

#ifndef DWL_DIALOGOABRIR_CPP
#define DWL_DIALOGOABRIR_CPP

#include "DWLDialogoAbrir.h"
#include <commdlg.h>
#include <shlobj.h>             // Libreria para los objetos Shell

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Ventanas
	namespace Ventanas {

			//! Función que muestra el diálogo para abrir archivos.
			/*!	Función que muestra el diálogo para abrir archivos según los parametros especificados.
					\fn			UINT MostrarAbrir(const TCHAR *PathSh, const TCHAR *Filtro, const TCHAR *Titulo, const bool MultiSeleccion, HWND hWndPadre) {
					\param[in]	PathSh			: Ruta inicial desde donde empezara el dialogo abrir
					\param[in]  Filtro			: Filtro de archivos
					\param[in]  Titulo			: Titulo del dialogo
					\param[in]  MultiSeleccion	: Habilitar multiselección
					\param[in]  hWndPadre		: Ventana padre, puede ser NULL. Si especificamos una ventana padre, esta se desactivara mientras el dialogo este activo.
					\return		Devuelve el numero de archivos seleccionados.
					\remarks    Titulo debera estar formateado de la siguiente forma :\n
								\code Todos los archivos\0*.*\0\0 \endcode
								Observad que primero hay un string con el nombre del filtro, luego el tipo de filtro, y por ultimo termina con un doble caracter <b>\\0</b>. \n\n
								Si por ejemplo queremos tener un filtro para documentos de texto debemos construirlo de una forma similar a este : \n
								\code Todos los archivos\0*.*\0Documentos de texto\0*.doc;*.txt;*.rtf\0\0 \endcode
								Observad que esta vez hemos añadido 3 tipos de archivo para el filtro Documentos de texto, esos tipos de archivo deben estar separados por el caracter <b>;</b>
			*/
		    UINT DWLDialogoAbrir::MostrarAbrir(const TCHAR *PathSh, const TCHAR *Filtro, const TCHAR *Titulo, const bool MultiSeleccion, HWND hWndPadre) {
				OPENFILENAME	ofn;
				TCHAR			szFile[4096]; 
				bool		    Multi = false; 
				TCHAR			Path[512]; 
				TCHAR			Archi[512];
				TCHAR		    UltimoDir[MAX_PATH +1];
				DWL::DWLString  Tmp;
				int				N = 0;
				int				i;
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lpstrCustomFilter	= NULL; 
				ofn.nFilterIndex		= 1;
				ofn.lpstrFile			= szFile; 
				ofn.nMaxFile			= 4096;
				ofn.lpstrFileTitle		= NULL;
				ofn.nMaxFileTitle		= 4096;
				ofn.lpstrInitialDir		= TEXT(".\0");
				ofn.lpstrTitle			= Titulo;
				ofn.lpstrFilter			= Filtro;
				ofn.lStructSize			= sizeof(OPENFILENAME);
				ofn.hwndOwner			= hWndPadre; 
				if (MultiSeleccion == true) ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT;
				else						ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
				_Archivos.clear();
				for (i = 0; i < 4096; i++) szFile[i] = 0; 
				szFile[0] = '\0'; 
				// Obtengo el directorio actual para luego volverlo a asignar
				GetCurrentDirectory(MAX_PATH +1, UltimoDir); 
				SetCurrentDirectory(PathSh); 
				if (GetOpenFileName(&ofn)) { 
					DWLStrCopy(Path, 512, szFile);
					i = static_cast<int>(DWLStrLen(Path));
					while (szFile[i] != 0 || szFile[i+ 1] != 0) {
						i++;   
						if (szFile[i] != 0) { 
							Archi[N] = szFile[i];   
							N++;   
						}   
						else {
							Archi[N] = 0;	
							N = 0;
							Multi = true;
							Tmp = Path;  
							if (Tmp[Tmp.Tam() -1] != '\\') {
								Tmp += '\\'; 
							} 
							Tmp += Archi;	
							_Archivos.push_back(Tmp);   
						}  
					}  
					if (Multi == false) { 
						Tmp = szFile;   _Archivos.push_back(Tmp); 
					} 
				} 
				SetCurrentDirectory(UltimoDir); 
				return _Archivos.size();
			};   
	}
}


#endif // DWL_DIALOGOSCOMUNES_CPP
