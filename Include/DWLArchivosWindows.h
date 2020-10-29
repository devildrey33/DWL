/*! \file DWLArchivosWindows.h
	\brief		Archivo que contiene funciones para la creación de archivos especiales de windows.


	\details	La clase DWLArchivosWindows contiene una funcion para poder crear accesos directos.
																																						\n
	\author		devildrey33
	\version	0.95
	\date		10/12/2009

	\remarks
				Archivo creado por devildrey33 el dia [26/02/2009] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n	
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n	
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n	
 
*/
#ifndef DWL_ARCHIVOSWINDOWS_H
#define DWL_ARCHIVOSWINDOWS_H

#include <shlobj.h>

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Archivos
	namespace Archivos {
		//! Clase estatica para crear archivos especiales de windows
		class DWLArchivosWindows {
		 public: ///////////////// Miembros publicos
								
								//! Constructor
								/*! Este constructor esta vacio.
										\fn			DWLArchivosWindows(void);
										\return		No devuelve nada.
										\sa		   ~DWLArchivosWindows()
								*/
								DWLArchivosWindows(void) { 
								};
								
								//! Destructor
								/*! Este destructor esta vacio.
										\fn			~DWLArchivosWindows(void);
										\return		No devuelve nada.
										\sa			DWLArchivosWindows()
								*/
							   ~DWLArchivosWindows(void) { 
								};
								
							    //! Función para crear un aceso directo del windows (*.lnk)
								/*! Esta funcion crea un acceso directo de windows segun los parametros especificados.
										\fn			static const bool CrearAccesoDirecto(const TCHAR *PathEjecutable, const TCHAR *DirectorioTrabajo, const TCHAR *Argumentos, const TCHAR *Descripcion, const TCHAR *PathIcono, const int IndiceIcono, const TCHAR *PathArchivoLnk);
										\param[in]  PathEjecutable		: Path del archivo ejecutable.
										\param[in]  DirectorioTrabajo	: Directorio donde reside el archivo ejecutable.
										\param[in]  Argumentos			: Argumentos para el archivo ejecutable (puede ser NULL)
										\param[in]  Descripcion			: Descripcion del archivo ejecutanle (puede ser NULL)
										\param[in]  PathIcono			: Ruta completa del icono para este acceso directo.
										\param[in]  IndiceIcono			: Indice del icono dentro del path.
										\param[in]  PathArchivoLnk		: Path final para el archivo LNK.
										\return		Devuelve TRUE si la operacion ha salido correctamente, FALSE en caso contrario.
										\sa			DWLArchivosWindows()
								*/
		 static const bool		CrearAccesoDirecto(const TCHAR *PathEjecutable, const TCHAR *DirectorioTrabajo, const TCHAR *Argumentos, const TCHAR *Descripcion, const TCHAR *PathIcono, const int IndiceIcono, const TCHAR *PathArchivoLnk) {
									CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
									IShellLink *psl; 
									// Creo el objeto COM destinado a crear LNKs
									HRESULT		hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (PVOID *) &psl);  
									if (SUCCEEDED(hres)) {
										IPersistFile* ppf; 
										// Asigno los valores del lnk
										psl->SetPath((DWLLPCSTR) PathEjecutable); 
										psl->SetWorkingDirectory((DWLLPCSTR) DirectorioTrabajo);
										psl->SetArguments((DWLLPCSTR) Argumentos);
										psl->SetDescription((DWLLPCSTR) Descripcion); 
										psl->SetIconLocation((DWLLPCSTR) PathIcono, IndiceIcono);								
										// Pruebo a crear el acceso directo en memoria para ver si hay algun problema
										hres = psl->QueryInterface(IID_IPersistFile, (PVOID *) &ppf); 
										if (SUCCEEDED(hres)) {
											#if defined UNICODE
												hres = ppf->Save(PathArchivoLnk, TRUE); 
												ppf->Release(); 
											#else
												WCHAR wsz[MAX_PATH]; 
												// Paso el path ejecutable a unicode
												MultiByteToWideChar(CP_ACP, 0, (LPCSTR) PathArchivoLnk, -1, wsz, MAX_PATH); 
												// Guardo el .LNK 
												hres = ppf->Save(wsz, TRUE); 
												ppf->Release(); 
											#endif
										}
//										psl->Release(); 
									}
									CoUninitialize();
									return SUCCEEDED(hres);
								};
		};						//
		////////////////////////// Fin class DWLArchivosWindows;
	}
}

#endif
