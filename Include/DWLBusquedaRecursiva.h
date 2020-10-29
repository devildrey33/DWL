/*! \file DWLBusquedaRecursiva.h
	\brief		Archivo que contiene funciones hacer busquedas recursivas de archivos en windows.


	\details	La clase DWLBusquedaRecursiva es una clase simple pensada para buscar archivos a partir de una ruta.									\n	
				Esta clase tiene 3 funciónes basicas, la primera es DWL::Archivos::DWLBusquedaRecursiva::Buscar(), 
				la cual hace una busqueda recursiva segun el path especificado. Luego tenemos las funciones virtuales 
				DWL::Archivos::DWLBusquedaRecursiva::EncontradoArchivo() y DWL::Archivos::DWLBusquedaRecursiva::EncontradoDirectorio(),
				las cuales seran llamadas cada vez que se encuentre un archivo / directorio dentro de los parametros establecidos.						\n\n

				Basicamente hay que heredar esta clase, reescribir las funciónes virtuales DWL::Archivos::DWLBusquedaRecursiva::EncontradoArchivo()
				y DWL::Archivos::DWLBusquedaRecursiva::EncontradoDirectorio() para satisfacer nuestras necesidades, y iniciar la busqueda.																									
																																						\n
	\author		devildrey33
	\version	0.95
	\date		18/11/2009

	\remarks
				Archivo creado por devildrey33 el dia [23/09/2004] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n	
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n	
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n	

*/
 

#ifndef DWL_BUSQUEDARECURSIVA_H
#define DWL_BUSQUEDARECURSIVA_H

#define DWL_CLASE_BUSQUEDA_RECURSIVA_BUSCANDO	   -10	// Si se retorna este valor es que ya se ha iniciado una 
														// busqueda y aun no ha terminado.

#define DWL_CLASE_BUSQUEDA_RECURSIVA_PATH_INVALIDO  -9	// Si se retorna este valor es que el path de la 
														// busqueda no es correcto.

#include <string>

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Archivos
	namespace Archivos {
		//! Clase para realizar busquedas recursivas
		/*! Esta clase se ha diseñado de forma que se pueda heredar facilmente y a partir de alli hacer busquedas recursivas comodamente.
		*/
		class DWLBusquedaRecursiva {
		public: ////////////////// Miembros publicos
								
								//! Constructor por defecto
								/*! Este constructor inicializa los miembros internos.
										\fn			DWLBusquedaRecursiva(void);
										\return		No devuelve nada.
										\sa			~DWLBusquedaRecursiva()
								*/
								DWLBusquedaRecursiva(void) {
									_Buscando = false;
								};
								
								//! Destructor
								/*! Destructor vacio.
										\fn			~DWLBusquedaRecursiva(void);
										\return		No devuelve nada.
										\sa			DWLBusquedaRecursiva()
								*/
							   ~DWLBusquedaRecursiva(void) {
								};
								
								//! Función que empieza la busqueda recursiva
								/*! Esta función busca partiendo del path especificado, y llama internamente a la funcion _BusquedaRecursiva por cada directorio que encuentra.
										\fn			const int Buscar(const TCHAR *Path);
										\param[in]	Path : Ruta completa a partir de donde se tiene que buscar.
										\return		Devuleve el numero de archivos encontrados.
										\remarks	En caso de error devolvera DWL_CLASE_BUSQUEDA_RECURSIVA_BUSCANDO si has intentado iniciar una busqueda mientras se estaba buscando,
													o DWL_CLASE_BUSQUEDA_RECURSIVA_PATH_INVALIDO si el path especificado no es valido.
										\sa			_BusquedaRecursiva(), EncontradoArchivo(), EncontradoDirectorio(), Terminado()
								*/
		 const int		        Buscar(const TCHAR *Path) {
									if (_Buscando == true) return DWL_CLASE_BUSQUEDA_RECURSIVA_BUSCANDO;
									_Buscando = true;
									int Ret = _BusquedaRecursiva(Path);
									_Buscando = false;
									return Ret;
								};
								
								//! Función VIRTUAL que es ejecutada cada vez que la función buscar encuentra un archivo valido.
								/*! Esta función es llamada cuando la busqueda encuentra un archivo.
										\fn			virtual void EncontradoArchivo(const TCHAR *Path, DWORD Atributos);
										\param[in]	Path		: Ruta completa del archivo encontrado.
										\param[in]	Atributos	: Atributos del archivo encontrado.
										\return		No devuelve nada.
										\remarks	Puedes heredar esta funcion y sobre-escribirla segun tus necesidades.
										\sa			EncontradoDirectorio(), _BusquedaRecursiva(), Buscar(), Terminado()
								*/
		 virtual void			EncontradoArchivo(const TCHAR *Path, DWORD Atributos) {
								};
								
								//! Función VIRTUAL que es ejecutada cada vez que la función buscar encuentra un directorio valido.
								/*! Esta función es llamada cuando la busqueda encuentra un directorio.
										\fn			virtual void EncontradoDirectorio(const TCHAR *Path, DWORD Atributos);
										\param[in]	Path		: Ruta completa del directorio encontrado.
										\param[in]	Atributos	: Atributos del directorio encontrado.
										\return		No devuelve nada.
										\remarks	Puedes heredar esta funcion y sobre-escribirla segun tus necesidades.
										\sa			EncontradoArchivo(), _BusquedaRecursiva(), Buscar(), Terminado()
								*/
		 virtual void			EncontradoDirectorio(const TCHAR *Path, DWORD Atributos) {
								};
								
								//! Función VIRTUAL que es ejecutada cuando la función buscar termina todo el proceso.
								/*! Esta función es llamada cuando la busqueda finaliza.
										\fn			virtual void Terminado(const unsigned int TotalArchivos, const unsigned int TotalDirectorios);
										\param[in]	TotalArchivos		: Total de archivos encontrados.
										\param[in]	TotalDirectorios	: Atributos del directorio encontrado.
										\return		No devuelve nada.
										\remarks	Puedes heredar esta funcion y sobre-escribirla segun tus necesidades.
										\sa			EncontradoArchivo(), EncontradoDirectorio(), _BusquedaRecursiva(), Buscar()
								*/
		 virtual void			Terminado(const unsigned int TotalArchivos, const unsigned int TotalDirectorios) {
								};
		protected : ////////////// Mimebros privados
								
								//! Función que controla la busqueda, y que se llama a ella misma recursivamente.
								/*! Esta función es el nucleo de la busqueda. 
										\fn			const int _BusquedaRecursiva(const TCHAR *Path);
										\param[in]	Path		: Path por donde empezar a buscar.
										\return		Devuelve el total de archivos encontrados.
										\sa			EncontradoArchivo(), EncontradoDirectorio(), Terminado(), Buscar()
								*/
		 const int			   _BusquedaRecursiva(const TCHAR *Path) {
									#if defined UNICODE	//////////////////////////////////////
									std::wstring		PathFinal					= Path; //
									#else  // NOT DEFINED UNICODE ////////////////////////////
									std::string			PathFinal					= Path; //
									#endif ///////////////////////////////////////////////////
									WIN32_FIND_DATA		FindInfoPoint;
									HANDLE				hFind						= NULL;
									unsigned int		TotalArchivosEncontrados	= 0;
									unsigned int		TotalDirectoriosEncontrados	= 0;
									int					TmpRet						= 0;
									TCHAR				TmpPath[MAX_PATH];

									GetShortPathName(Path, TmpPath, MAX_PATH); 
									if (TmpPath[0] == 0) return DWL_CLASE_BUSQUEDA_RECURSIVA_PATH_INVALIDO;

									if (PathFinal[PathFinal.size() -1] != TEXT('\\'))	PathFinal += TEXT("\\*.*");
									else												PathFinal += TEXT("*.*");
									hFind = FindFirstFile(PathFinal.c_str(), &FindInfoPoint);
									while (FindNextFile(hFind, &FindInfoPoint) != 0) {
										PathFinal = Path;
										if (PathFinal[PathFinal.size() -1] != TEXT('\\'))	PathFinal += TEXT('\\');

										if (_Comprobacion(FindInfoPoint.cFileName) == true) {
											PathFinal += FindInfoPoint.cFileName;
											// Si es un directorio y no empieza por ".", llamo a esta Función recursiva de nuevo
											if (FindInfoPoint.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && FindInfoPoint.cFileName[0] != TEXT('.')) {
												EncontradoDirectorio(PathFinal.c_str(), FindInfoPoint.dwFileAttributes);
												TotalDirectoriosEncontrados ++;
												TmpRet = _BusquedaRecursiva(PathFinal.c_str());
												if (TmpRet < 0) return TmpRet; // Retorno en caso de error
												TotalArchivosEncontrados += TmpRet;
											}
											// Si es un archivo, llamo a la Función Encontrado y le paso los datos pertinentes
											else {
												TotalArchivosEncontrados ++;
												EncontradoArchivo(PathFinal.c_str(), FindInfoPoint.dwFileAttributes);
											}
										}
									}
									FindClose(hFind);
									Terminado(TotalArchivosEncontrados, TotalDirectoriosEncontrados);
									return static_cast<int>(TotalArchivosEncontrados);
								};
								
								//! Función que comprueba el nombre del archivo y decide si es valido o no
								/*! Esta función se utiliza basicamente para saber si el directorio es valido. 
										\fn			const bool _Comprobacion(const TCHAR *Path);
										\param[in]	Path : Path del directorio que queremos saber si es valido.
										\return		Devuelve true si es un directorio valido, false en caso contrario.
								*/
		 const bool			   _Comprobacion(const TCHAR *Path) {
				 					if (Path[0] == TEXT('.') && Path[1] == 0) return false;
									if (Path[0] == TEXT('.') && Path[1] == TEXT('.') && Path[2] == 0) return false;
									return true;
								};
								
								//! Valor que determina si se esta buscando.
		 bool				   _Buscando;
		};						//
		//////////////////////////
	}
}

#endif
