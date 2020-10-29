/*! \file DWLArchivoLog.h
	\brief		Cabecera que contiene una clase para la la creación de archivos log.


	\details	La clase DWLArchivoLog se ha diseñado para abrir un archivo e ir guardando de vez en cuando informacion relevante.						\n	
				Cuando agregas una entrada al log con la función GuardarLog, esta abre y cierra el archivo para guardar la información.					\n
				Lo malo de esto es que puede resultar lento en algunos casos.
																																						\n
	\author		devildrey33
	\date		Creado el [26/02/2009], ultima modificacion el [10/12/2009]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n	
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n	
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n	

*/ 
#ifndef DWL_ARCHIVOLOG_H
#define DWL_ARCHIVOLOG_H

#include "DWLString.h"

// Espacios que contiene la tabulacion, por defecto son 4
#define DWL_ARCHIVOLOG_TABULACION		TEXT("    ")

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Archivos
	namespace Archivos {
		//! Clase para la creacion de archivos Log
		/*! Esta clase tiene el objetivo de ser utilizada como un contenedor para nuestros archivos de log. Puedes abrir y cerrar corchetes para tabular el texto.
		*/
		class DWLArchivoLog {
		public: ////////// Miembros publicos
						
						//! Constructor
						/*! Este constructor inicializa los miembros internos.
								\fn			DWLArchivoLog(void);
								\return		No devuelve nada.
								\sa			DWLArchivoLog(), ~DWLArchivoLog()
						*/
						DWLArchivoLog(void) { 
							UltimoTick = GetTickCount();
							Espacios = 0;
						};
						
						//! Constructor con path
						/*! Este constructor requiere el path del archivo que queremos abrir.
								\fn			DWLArchivoLog(const TCHAR *nDest, const bool nBorrar = true);
								\param[in]	nDest	: Ruta completa para el archivo de log que queremos abrir.
								\param[in]	nBorrar : Especifica si quieres borrar el archivo, o dejarlo intacto.
								\return		No devuelve nada.
								\sa			DWLArchivoLog(), ~DWLArchivoLog()
						*/
						DWLArchivoLog(const TCHAR *nDest, const bool nBorrar = true) {
							Archivo(nDest, nBorrar); 
						};
						
						//! Destructor
						/*! Destructor que cierra el archivo y elimina los datos de memoria.
								\fn			~DWLArchivoLog(void);
								\return		No devuelve nada.
								\sa			DWLArchivoBinario()
						*/
					   ~DWLArchivoLog(void) { 
						};
						
						//! Función para indicar que archivo sera el contenedor del log
						/*! Esta funcion abre el archivo especificado para que sea el archivo de log.
								\fn			void Archivo(const TCHAR *nDest, const bool nBorrar = true);
								\param[in]	nDest	: Ruta completa para el archivo de log que queremos abrir.
								\param[in]	nBorrar : Especifica si quieres borrar el archivo, o dejarlo intacto.
								\return		No devuelve nada.
						*/
		 void			Archivo(const TCHAR *nDest, const bool nBorrar = true) {
							UltimoTick = GetTickCount();
							if (nBorrar == true) DeleteFile(nDest);
							PathArchivo = nDest;
							Espacios = 0;
    					};
						
						//! Función para guardar el prototipo de una Función.
						/*! Esta funcion guarda el protitipo de una función. Como parametro debes especificar __FUNCDNAME__ o __FUNCSIG__.
								\fn			void GuardarPrototipoFuncion(const char *nPrototipo);
								\param[in]	nPrototipo	: Buffer en el que debemos espeficicar el prototipo de la funcion, o podemos especificar __FUNCDNAME__ o __FUNCSIG__.
								\return		No devuelve nada.
						*/
		 void			GuardarPrototipoFuncion(const char *nPrototipo) {
							if (PathArchivo.Tam() == 0) return;
//							TCHAR			T[1024];
							DWORD			Tik		= GetTickCount();
							FILE           *Archivo = NULL;
							DWLString		Tmp;
							#if defined UNICODE								
								_wfopen_s(&Archivo, PathArchivo.Texto(), TEXT("at")); // Abro el Archivo de Log
							#else
								fopen_s(&Archivo, PathArchivo.Texto(), TEXT("at")); // Abro el Archivo de Log
							#endif
							for (unsigned int i = 0; i < Espacios; i++)	Tmp += DWL_ARCHIVOLOG_TABULACION;
							Tmp += nPrototipo;
							if (Archivo != NULL) {
								#if defined UNICODE
									fwprintf(Archivo, TEXT("[%.10d] %s {\n"), Tik - UltimoTick, Tmp.Texto());
								#else
									fprintf(Archivo, "[%.10d] %s\n {", Tik - UltimoTick, Tmp.Texto());
								#endif
								fclose(Archivo);
							}
							UltimoTick = GetTickCount();
							Espacios ++;
						}

						//! Función para guardar texto y valores en el archivo de log
						/*! Esta función guarda una cadena de texto en el log. Podemos usar esta funcion al estilo de las funciones printf
								\fn			void GuardarLog(const TCHAR *Txt, ...);
								\param[in]	Txt	: Texto a escribir dentro del archivo log.
								\param[in]	... : Parametros extra.
								\return		No devuelve nada.
						*/
		 void			GuardarLog(const TCHAR *Txt, ...) {
							if (PathArchivo.Tam() == 0) return;
							TCHAR			T[1024];
							DWLString		Tmp;							
							DWORD			Tik = GetTickCount();
							va_list			Marker;
							va_start(Marker, Txt);     
							#if defined UNICODE
								vswprintf_s(T, 1024, Txt, Marker);
							#else
								vsprintf_s(T, 1024, Txt, Marker);
							#endif
							va_end(Marker);
							if  (T[0] == TEXT('}'))	if (Espacios > 0) Espacios --;
							for (unsigned int i = 0; i < Espacios; i++)	Tmp += DWL_ARCHIVOLOG_TABULACION;
							Tmp += T;
							FILE *Archivo = NULL;
							#if defined UNICODE
								_wfopen_s(&Archivo, PathArchivo(), TEXT("at")); // Abro el Archivo de Log
							#else
								fopen_s(&Archivo, PathArchivo(), TEXT("at")); // Abro el Archivo de Log
							#endif
							if (Archivo != NULL) {
								#if defined UNICODE
									fwprintf(Archivo, TEXT("[%.10d] %s\n"), Tik - UltimoTick, Tmp.Texto());
								#else
									fprintf(Archivo, "[%.10d] %s\n", Tik - UltimoTick, Tmp.Texto());
								#endif
								fclose(Archivo);
							}
							UltimoTick = GetTickCount();
							#if defined UNICODE
								if (T[wcslen(T) -1] == TEXT('{')) Espacios ++;
							#else
								if (T[strlen(T) -1] == TEXT('{')) Espacios ++;
							#endif
						};
						//
						//! Función que cierra todos los corchetes abiertos en el log
						//  void TerminarLog(void);
						/*! Esta función cierra todos los corchetes abiertos dentro del archivo de log
								\fn			void TerminarLog(void);
								\return		No devuelve nada.
								\remarks	En cualquier momento del log puedes añadir corchetes para abrir y cerrar zonas. Al terminar el archivo log debes acordarte de utilizar esta funcion para que TODOS los corchetes queden bien cerrados.
						*/
		 void			TerminarLog(void) {
							while (Espacios != 0) GuardarLog(TEXT("}"));
						};
		private: ///////// Miembros privados
						// 
						//! Variable que contine el ultimo tick del sistema conocido
		 DWORD		    UltimoTick;
						//
						//! Variable donde guardamos el path del archivo log
		 DWLString		PathArchivo;
						//
						//! Variable que contiene el numero de corchetes abiertos
		 unsigned int	Espacios;
		}; /////////////// Fin DWLArchivoLog
	}
 }

#endif // DWL_ARCHIVOLOG_H

/*! \file DWLArchivoLog.h
 	\version

 - [14/09/2009] <b>0.95</b>
   Añadida función GuardarPrototipoFunción que guarda el prototipo de la función. \n
   Solucionado error en la version ANSI que utilizaba la Función UNICODE para escribir el texto.

 - [13/07/2008] <b>0.8</b>
   Primera versión de esta clase.

*/