/*! \file		DWLDialogoDirectorios.cpp
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

#ifndef DWL_DIALOGODIRECTORIOS_CPP
#define DWL_DIALOGODIRECTORIOS_CPP

#include "DWLDialogoDirectorios.h"
//#include <commdlg.h>
#include <shlobj.h>             // Libreria para los objetos Shell

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Ventanas
	namespace Ventanas {

			// DEPRECATED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//! Función que muestra el dialogo del sistema para seleccionar un directorio.
			/*!	Esta función muestra el dialogo del sistema para seleccionar un directorio.
					\fn			const TCHAR *MostrarDirectorios(const TCHAR *Titulo);
					\param[in]	Titulo : Cadena de caracteres con el titulo del dialogo
					\return		Devuelve la ruta del directorio seleccionado.
					\todo       Esta función usa API DEPRECATED, hay que re-emplazarla y mantener esta funcion para VC6
			*/
			const TCHAR *DWLDialogoDirectorios::MostrarDirectorios(const TCHAR *Titulo) { 
				BROWSEINFO   BuskaDir = { NULL, NULL, NULL, NULL, NULL, NULL, 0L, 0 }; 
				LPITEMIDLIST ID; 
				LPITEMIDLIST IDRoot;
				LPMALLOC     lpMalloc;
				TCHAR        Directori[512] = TEXT("");
				BuskaDir.hwndOwner = NULL; 
				BuskaDir.pidlRoot = NULL;
				BuskaDir.ulFlags = NULL; 
				BuskaDir.lpszTitle = Titulo; 
				BuskaDir.lpfn = NULL;
				HRESULT Res = SHGetSpecialFolderLocation(HWND_DESKTOP, CSIDL_DRIVES, &IDRoot);
				BuskaDir.pidlRoot = IDRoot;
				ID = SHBrowseForFolder(&BuskaDir);
				if (ID != NULL) {  SHGetPathFromIDList(ID, Directori);   _Directorio = Directori; }
				else			{  _Directorio = TEXT(""); return _Directorio(); }
				if (NOERROR == SHGetMalloc(&lpMalloc) && (NULL != lpMalloc)) {
					if (NULL != IDRoot) lpMalloc->Free(IDRoot);  
					if (NULL != ID)     lpMalloc->Free(ID); 
					lpMalloc->Release();  
				}
				if (_Directorio.Tam() > 0) {
					if (_Directorio[_Directorio.Tam() -1] != '\\') _Directorio += '\\';
				}
				return _Directorio();
			};

	}
}


#endif // DWL_DIALOGODIRECTORIOS_CPP
