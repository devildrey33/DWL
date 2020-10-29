/*! \file DWLArchivoBinario.h
	\brief		Archivo que contiene funciones para la lectura y escritura de archivos en windows.


	\details	La clase DWLArchivoBinario es una clase para utilizar archivos de lectura / escritura con el API de windows de una forma rapida.		\n	
																																						\n
	\author		devildrey33
	\version	0.95
	\date		10/12/2009

	\remarks
				Archivo creado por devildrey33 el dia [26/02/2009] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n	
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n	
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)															\n	

*/



#ifndef DWL_ARCHIVOBINARIO_H
#define DWL_ARCHIVOBINARIO_H

#include <fstream>
#include "DWLString.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Archivos
	namespace Archivos {
		//! Clase para utilizar archivos binarios en windows
		/*! Clase para la utilizacion de archivos binarios en windows.
			Dispone de funciones para lectura y escritura en disco.
		*/
		class DWLArchivoBinario {
		public: ////////////////////////// 
										//! Constructor por defecto
										/*! Este constructor inicializa los miembros internos.
												\return		No devuelve nada.
												\sa			DWLArchivoBinario(), ~DWLArchivoBinario()
										*/
										DWLArchivoBinario(void) { 
											_Archivo			= INVALID_HANDLE_VALUE;
											_FinalDelArchivo	= false;
											_CaracteresLeidos   = 0;
										};
										 
										//! Constructor que abre un archivo
										/*! 
										Este constructor inicializa los miembros internos y abre el archivo especificado en el parametro Path.
												\fn			DWLArchivoBinario(const TCHAR *Path, const bool Abrir_si_no_existe = true);
												\param[in]  Path				: Ruta completa del archivo a abrir.
												\param[in]  Abrir_si_no_existe	: True (por defecto) para abrir el archivo si no existe, false para lo contrario.
												\return		No devuelve nada.
												\sa			DWLArchivoBinario(), ~DWLArchivoBinario(), CerrarArchivo()
										*/
										DWLArchivoBinario(const TCHAR *Path, const bool Abrir_si_no_existe = true) { 
											_FinalDelArchivo	= false;
											_Archivo			= INVALID_HANDLE_VALUE;
											_CaracteresLeidos   = 0;
											AbrirArchivo(Path, Abrir_si_no_existe);
										};
										 
										//! Destructor
										/*! Destructor que cierra el archivo y elimina los datos de memoria.
												\fn			~DWLArchivoBinario(void);
												\return		No devuelve nada.
												\sa			DWLArchivoBinario()
										*/
									   ~DWLArchivoBinario(void) { 
											CerrarArchivo();
										};
										 
										//! Función para abrir un archivo lectura / escritura
										/*! Esta funcion abre el archivo especificado en el parametro Path.
												\fn			const bool AbrirArchivo(const TCHAR *Path, const bool Abrir_si_no_existe = false);
												\param[in]	Path			   : Ruta completa del archivo a abrir.
												\param[in]	Abrir_si_no_existe : True (por defecto) para abrir el archivo si no existe, false para lo contrario.
												\return		Si todo va bien devuelve true, en caso de error devuelve false.
												\sa			AbrirArchivoLectura(), AbrirArchivoEscritura(), CerrarArchivo()
										*/
		 const bool				        AbrirArchivo(const TCHAR *Path, const bool Abrir_si_no_existe = false) {
											CerrarArchivo();
											if (Abrir_si_no_existe == true) {
												_Archivo = CreateFile(Path, FILE_READ_DATA | FILE_WRITE_DATA, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
											}
											else {
												_Archivo = CreateFile(Path, FILE_READ_DATA | FILE_WRITE_DATA, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
											}
											_FinalDelArchivo = false;
											if (_Archivo != INVALID_HANDLE_VALUE)	return true;
											else									return false;
										};
										 
										//! Función para abrir un archivo solo lectura
										/*! Esta funcion abre el archivo especificado en el parametro Path solo para lectura.
												\fn			const bool AbrirArchivoLectura(const TCHAR *Path);
												\param[in]  Path : Ruta completa del archivo a abrir.
												\return		Si todo va bien devuelve true, en caso de error devuelve false.
												\sa			AbrirArchivo(), AbrirArchivoEscritura(), CerrarArchivo()
										*/
		 const bool				        AbrirArchivoLectura(const TCHAR *Path) {
											CerrarArchivo();
											_FinalDelArchivo = false;
											_Archivo = CreateFile(Path, FILE_READ_DATA, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
											if (_Archivo != INVALID_HANDLE_VALUE)	return true;
											else									return false;
										};
										 
										//! Función para abrir un archivo solo escritura
										/*! Esta funcion abre el archivo especificado en el parametro Path solo para escritura.
												\fn			const bool AbrirArchivoEscritura(const TCHAR *Path);
												\param[in]  Path : Ruta completa del archivo a abrir.
												\return		Si todo va bien devuelve true, en caso de error devuelve false.
												\sa			AbrirArchivo(), AbrirArchivoLectura(), CerrarArchivo()
										*/
		 const bool		        		AbrirArchivoEscritura(const TCHAR *Path) {
											CerrarArchivo();
											_FinalDelArchivo = false;
											_Archivo = CreateFile(Path, FILE_WRITE_DATA, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
											if (_Archivo != INVALID_HANDLE_VALUE)	return true;
											else									return false;
										};
										 
										//! Función para cerrar un archivo cargado
										/*! Esta funcion cierra el archivo.
												\fn			inline void CerrarArchivo(void);
												\return		No devuelve nada.
												\sa			AbrirArchivo(), AbrirArchivoLectura(), AbrirArchivoEscritura()
										*/
		 inline void					CerrarArchivo(void) {
											if (_Archivo != INVALID_HANDLE_VALUE) CloseHandle(_Archivo);
											_Archivo = INVALID_HANDLE_VALUE;
											_CaracteresLeidos = 0;
										};
										 
										//! Función que retorna si el archivo esta abierto
										/*! Esta funcion mira que el identificador del archivo sea valido. En caso de no ser valido el archivo no esta abierto.
												\fn			inline const bool EstaAbierto(void);
												\return		Devuelve true si el archivo esta abierto, false en caso contrario.
												\sa			AbrirArchivo(), AbrirArchivoLectura(), AbrirArchivoEscritura(), CerrarArchivo()
										*/
		 inline const bool				EstaAbierto(void) {
											if (_Archivo != INVALID_HANDLE_VALUE)	return true;
											else									return false;
										};
										 
										//! Función para leer datos del archivo
										/*! Esta funcion lee los bytes especificados y los introduce en el Buffer.
												\fn			template <class T> const BOOL Leer(T Buffer, const size_t LongitudEnBytes);
												\param[out] Buffer			: Buffer para los datos.
												\param[in]  LongirudEnBytes	: Tamaño en bytes a leer.
												\return		Devuelve el total de bytes leidos.
												\remarks	El buffer debe tener suficiente espacio para almacenar los bytes especificados en LongitudEnBytes.
															Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			Guardar()
										*/
		 template <class T> const BOOL	Leer(T Buffer, const size_t LongitudEnBytes) {
											_CaracteresLeidos	= 0;							
											BOOL	Ret		= ReadFile(_Archivo, reinterpret_cast<LPVOID>(Buffer), LongitudEnBytes, &_CaracteresLeidos, NULL);
											SOLO_DEBUG(if (Ret == 0) DWL::DWLDebug::MostrarUltimoError());
											if (_CaracteresLeidos == 0) _FinalDelArchivo = true;
											else						_FinalDelArchivo = false;
											return _CaracteresLeidos;
										};		 
										 
										//! Función para guardar datos en el archivo
										/*! Esta funcion guarda el Buffer en el archivo.
												\fn			template <class T> const BOOL Guardar(T Buffer, const size_t LongitudEnBytes);
												\param[in]  Buffer			: Buffer que contiene los datos a escribir.
												\param[in]  LongirudEnBytes	: Tamaño en bytes a leer.
												\return		Devuelve TRUE si la operacion se realizo, FALSE en caso contrario.
												\sa			Leer()
										*/
		 template <class T> const BOOL	Guardar(T Buffer, const size_t LongitudEnBytes) {
											DWORD Guardado = 0;			
											#if defined _DEBUG
												if (WriteFile(_Archivo, reinterpret_cast<LPCVOID>(Buffer), LongitudEnBytes, &Guardado, NULL) == 0) DWLDebug::MostrarUltimoError();
											#else
												WriteFile(_Archivo, reinterpret_cast<LPCVOID>(Buffer), LongitudEnBytes, &Guardado, NULL);
											#endif
											return static_cast<BOOL>(Guardado == LongitudEnBytes);
										};

										//! Función para leer datos del archivo
										/*! Esta funcion lee los bytes especificados y los introduce en el Buffer.
												\fn			const BOOL Leer(char *Buffer, const size_t LongitudEnCaracteres);
												\param[out] Buffer			     : Buffer para los datos.
												\param[in]  LongitudEnCaracteres : Tamaño en bytes a leer.
												\return		Devuelve el total de bytes leidos.
												\remarks	El buffer debe tener suficiente espacio para almacenar los bytes especificados en LongitudEnCaracteres.
															Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			Guardar()
										*/
		 const BOOL	                    Leer(char *Buffer, const size_t LongitudEnCaracteres) {
											_CaracteresLeidos	= 0;							
											BOOL	Ret		= ReadFile(_Archivo, reinterpret_cast<LPVOID>(Buffer), LongitudEnCaracteres * sizeof(char), &_CaracteresLeidos, NULL);
											if (_CaracteresLeidos < LongitudEnCaracteres)	_FinalDelArchivo = true;
											else											_FinalDelArchivo = false;
											return _CaracteresLeidos;
										};		 
										 
										//! Función para guardar datos en el archivo
										/*! Esta funcion guarda el Buffer en el archivo.
												\fn			const BOOL Guardar(char *Buffer, const size_t LongitudEnCaracteres);
												\param[in]  Buffer		     	 : Buffer que contiene los datos a escribir.
												\param[in]  LongitudEnCaracteres : Tamaño en bytes a leer.
												\return		Devuelve el total de bytes guardados.
												\sa			Leer()
										*/
		 const BOOL	                    Guardar(char *Buffer, const size_t LongitudEnCaracteres) {
											DWORD Guardado = 0;			
											return WriteFile(_Archivo, reinterpret_cast<LPCVOID>(Buffer), LongitudEnCaracteres * sizeof(char), &Guardado, NULL);
										};
										 
										//! Función para leer un DWLString del archivo
										/*! Esta funcion lee un string del archivo y lo almacena en una clase DWLString.
												\fn			const BOOL LeerString(DWL::DWLString &Val);
												\param[out]	Val	: Clase DWLString que se utilizara como buffer de lectura.
												\return		Devuelve el total de bytes leidos.
												\remarks	Para guardar el string en el archivo primero se guarda un integer sin signo que contiene el tamaño en caracteres, y luego se guarda la cadena.
															Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarString()
										*/
		 const BOOL			        	LeerString(DWL::DWLString &Val) {
											unsigned int TamStr = 0;
											TCHAR       *TmpChar = NULL;
											int R = sizeof(TCHAR *);
											if (Leer(&TamStr, sizeof(unsigned int)) == false) return false; // Leo el tamaño
											TmpChar = new TCHAR [TamStr + 1];
											BOOL Ret = Leer(TmpChar, TamStr * sizeof(TCHAR));
                                            if (Ret != static_cast<int>(TamStr * sizeof(TCHAR))) {
                                                delete [] TmpChar;
                                                return FALSE;
                                            }
											TmpChar[TamStr] = 0;
											Val.Borrar();
											Val.AgregarTexto(TmpChar, TamStr);
											delete [] TmpChar;
											return Ret; // + sizeof(unsigned int);
										};
										
										//! Función para guardar una clase DWLString en el archivo
										/*! Esta funcion guarda el contenido de una clase DWLString en el archivo.
												\fn			const BOOL GuardarString(DWL::DWLString &Val, const bool GuardarTam = true);
												\param[in]	Val			: Clase DWLString que constiene los datos que se van a guardar en el archivo.
												\param[in]	GuardarTam	: Si especificamos true (por defecto) se guarda primero el tamaño del string.
												\return		Devuelve el total de bytes guardados.
												\remarks	Si no guardamos el tamaño del string al leerlo deberemos saber de antemano que tamaño tiene.
												\sa			LeerString()
										*/
		 const BOOL				        GuardarString(DWL::DWLString &Val, const bool GuardarTam = true) {
											BOOL			Ret = 0;
											unsigned int	Tam = Val.Tam();
											if (GuardarTam == true) Ret = Guardar(&Tam, sizeof(unsigned int));
											if (Ret == 0)	return FALSE;
											return Guardar(&Val[0], Tam * sizeof(TCHAR)) + sizeof(unsigned int);
										};
										 
										//! Función para leer un std::wstring del archivo
										/*! Esta funcion lee un string del archivo y lo almacena en una clase std::wstring.
												\fn			const BOOL LeerString(std::wstring &Val);
												\param[out]	Val	: Clase std::wstring que se utilizara como buffer de lectura.
												\return		Devuelve el total de bytes leidos.
												\remarks	Para guardar el string en el archivo primero se guarda un integer sin signo que contiene el tamaño en caracteres, y luego se guarda la cadena.
															Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarString()
										*/
		 const BOOL				        LeerString(std::wstring &Val) {
											size_t   TamStr  = 0;
											wchar_t *TmpChar = NULL;
											if (Leer(&TamStr, sizeof(size_t)) == false) return false; // Leo el tamaño
											TmpChar = new wchar_t [TamStr + 1];
											BOOL Ret = Leer(TmpChar, TamStr * sizeof(wchar_t));
                                            if (Ret != static_cast<int>(TamStr * sizeof(TCHAR))) {
                                                delete [] TmpChar;
                                                return FALSE;
                                            }
											TmpChar[TamStr] = 0;
											Val = TmpChar;
											delete [] TmpChar;
											return Ret; // + sizeof(size_t);
										};
										 
										//! Función para guardar un wstring en el archivo
										/*! Esta funcion guarda el contenido de una clase std::wstring en el archivo.
												\fn			const BOOL GuardarString(std::wstring &Val, const bool GuardarTam = true);
												\param[in]	Val			: Clase std::wstring que contiene los datos que se van a guardar en el archivo.
												\param[in]	GuardarTam	: Si especificamos true (por defecto) se guarda primero el tamaño del string.
												\return		Devuelve el total de bytes guardados.
												\remarks	Si no guardamos el tamaño del string al leerlo deberemos saber de antemano que tamaño tiene.
												\sa			LeerString()
										*/
		 const BOOL				        GuardarString(std::wstring &Val, const bool GuardarTam = true) {
											BOOL	Ret = 0;
											size_t	nTam = Val.size();
//                                            for (nTam = Val.size(); nTam > 0; nTam--) {
 //                                               if (Val[nTam -1] == 0) 
 //                                                   break;
   //                                         }
											if (GuardarTam == true) Ret = Guardar(&nTam, sizeof(size_t));
											if (Ret == 0)	return FALSE;
											return Guardar(&Val[0], nTam * sizeof(wchar_t)) + sizeof(size_t);
										};
										 
										//! Función para leer un std::string del archivo
										/*! Esta funcion lee un string del archivo y lo almacena en una clase std::string.
												\fn			const BOOL LeerString(std::string &Val);
												\param[out]	Val	: Clase std::string que se utilizara como buffer de lectura.
												\return		Devuelve el total de bytes leidos.
												\remarks	Para guardar el string en el archivo primero se guarda un integer sin signo que contiene el tamaño en caracteres, y luego se guarda la cadena.
															Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarString()
										*/
		 const BOOL				        LeerString(std::string &Val) {
											size_t TamStr  = 0;
											char  *TmpChar = NULL;
											if (Leer(&TamStr, sizeof(size_t)) == false) return false; // Leo el tamaño
											TmpChar = new char [TamStr + 1];
											BOOL Ret = Leer(TmpChar, TamStr * sizeof(char));
                                            if (Ret != static_cast<int>(TamStr * sizeof(char))) {
                                                delete [] TmpChar;
                                                return FALSE;
                                            }
											TmpChar[TamStr] = 0;
											Val = TmpChar;
											delete [] TmpChar;
											return Ret; // + sizeof(size_t);
										};
										 
										//! Función para guardar un string en el archivo
										/*! Esta funcion guarda el contenido de una clase std::string en el archivo.
												\fn			inline const BOOL GuardarString(std::string &Val, const bool GuardarTam = true);
												\param[in]	Val			: Clase std::string que contiene los datos que se van a guardar en el archivo.
												\param[in]	GuardarTam	: Si especificamos true (por defecto) se guarda primero el tamaño del string.
												\return		Devuelve el total de bytes guardados.
												\remarks	Si no guardamos el tamaño del string al leerlo deberemos saber de antemano que tamaño tiene.
												\sa			LeerString()
										*/
		 const BOOL				        GuardarString(std::string &Val, const bool GuardarTam = true) {
											BOOL	Ret = 0;
											size_t	Tam = Val.size();
											if (GuardarTam == true) Ret = Guardar(&Tam, sizeof(size_t));
											if (Ret == 0)	return FALSE;
											Ret = Guardar(&Val[0], Tam * sizeof(char));
											return Ret; // + sizeof(size_t);
										};
										 
										//! Función para leer un int del archivo
										/*! Esta funcion lee un integer del archivo y lo almacena en el buffer Val.
												\fn			inline const BOOL LeerInt(int &Val);
												\param[out]	Val	: Integer que se usara como buffer de lectura.
												\return		Devuelve el total de bytes leidos. 
												\remarks	Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarInt()
										*/
		 inline const BOOL				LeerInt(int &Val) {
											return Leer(&Val, sizeof(int));
										};
										 
										//! Función para guardar un int en el archivo
										/*! Esta funcion guarda un int en el archivo.
												\fn			inline const BOOL GuardarInt(const int Val);
												\param[in]	Val : int que se guardara en el archivo.
												\return		Devuelve el total de bytes guardados.
												\sa			LeerInt()
										*/
		 inline const BOOL				GuardarInt(const int Val) { 
											return Guardar(&Val, sizeof(int));
										};
										 
										//! Función para leer un __int64 del archivo
										/*! Esta funcion lee un __int64 del archivo y lo almacena en el buffer Val.
												\fn			inline const BOOL LeerInt64(__int64 &Val);
												\param[out]	Val	: __int64 que se usara como buffer de lectura.
												\return		Devuelve el total de bytes leidos. 
												\remarks	Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarInt64()
										*/
		 inline const BOOL				LeerInt64(__int64 &Val) {
											return Leer(&Val, sizeof(__int64));
										};
										 
										//! Función para guardar un __int64 en el archivo
										/*! Esta funcion guarda un __int64 en el archivo.
												\fn			inline const BOOL GuardarInt64(__int64 &Val);
												\param[in]	Val : __int64 que se guardara en el archivo.
												\return		Devuelve el total de bytes guardados.
												\sa			LeerInt64()
										*/
		 inline const BOOL				GuardarInt64(__int64 &Val) { 
											return Guardar(&Val, sizeof(__int64));
										};
										 
										//! Función para leer un long del archivo
										/*! Esta funcion lee un long del archivo y lo almacena en el buffer Val.
												\fn			inline const BOOL LeerLong(long &Val);
												\param[out]	Val	: long que se usara como buffer de lectura.
												\return		Devuelve el total de bytes leidos. 
												\remarks	Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarLong()
										*/
		 inline const BOOL				LeerLong(long &Val) {
											return Leer(&Val, sizeof(long));
										};
										
										//! Función para guardar un long en el archivo
										/*! Esta funcion guarda un long en el archivo.
												\fn			inline const BOOL GuardarLong(long &Val);
												\param[in]	Val : long que se guardara en el archivo.
												\return		Devuelve el total de bytes guardados.
												\sa			LeerLong()
										*/
		 inline const BOOL				GuardarLong(long &Val) { 
											return Guardar(&Val, sizeof(long));
										};
										 
										//! Función para leer un unsigned int del archivo
										/*! Esta funcion lee un unsigned int del archivo y lo almacena en el buffer Val.
												\fn			inline const BOOL LeerUnsignedInt(unsigned int &Val);
												\param[out]	Val	: unsigned int que se usara como buffer de lectura.
												\return		Devuelve el total de bytes leidos. 
												\remarks	Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarUnsignedInt()
										*/
		 inline const BOOL				LeerUnsignedInt(unsigned int &Val) {
											return Leer(&Val, sizeof(unsigned int));
										};

										//! Función para leer un unsigned int del archivo
										/*! Esta funcion lee un unsigned int del archivo y lo almacena en el buffer Val.
												\fn			inline const BOOL LeerUINT(UINT &Val);
												\param[out]	Val	: UINT que se usara como buffer de lectura.
												\return		Devuelve el total de bytes leidos. 
												\remarks	Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarUnsignedInt()
										*/
		 inline const BOOL				LeerUINT(UINT &Val) {
											return Leer(&Val, sizeof(UINT));
										};
										 
										//! Función para guardar un unsigned int en el archivo
										/*! Esta funcion guarda un unsigned int en el archivo.
												\fn			inline const BOOL GuardarUnsignedInt(unsigned int &Val);
												\param[in]	Val : unsigned int que se guardara en el archivo.
												\return		Devuelve el total de bytes guardados.
												\sa			LeerUnsignedInt()
										*/
		 inline const BOOL				GuardarUnsignedInt(unsigned int &Val) { 
											return Guardar(&Val, sizeof(unsigned int));
										};

										//! Función para guardar un UINT en el archivo
										/*! Esta funcion guarda un UINT en el archivo.
												\fn			inline const BOOL GuardarUINT(UINT &Val);
												\param[in]	Val : unsigned int que se guardara en el archivo.
												\return		Devuelve el total de bytes guardados.
												\sa			LeerUnsignedInt()
										*/
		 inline const BOOL				GuardarUINT(UINT &Val) { 
											return Guardar(&Val, sizeof(UINT));
										};
										 
										//! Función para leer un unsigned long del archivo
										/*! Esta funcion lee un unsigned int del archivo y lo almacena en el buffer Val.
												\fn			inline const BOOL LeerUnsignedLong(unsigned long &Val);
												\param[out]	Val	: unsigned long que se usara como buffer de lectura.
												\return		Devuelve el total de bytes leidos. 
												\remarks	Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarUnsignedLong()
										*/
		 inline const BOOL				LeerUnsignedLong(unsigned long &Val) {
											return Leer(&Val, sizeof(unsigned long));
										};
										 
										//! Función para guardar un unsigned long en el archivo
										/*! Esta funcion guarda un unsigned long en el archivo.
												\fn			inline const BOOL GuardarUnsignedLong(unsigned long &Val);
												\param[in]	Val : unsigned long que se guardara en el archivo.
												\return		Devuelve el total de bytes guardados.
												\sa			LeerUnsignedLong()
										*/
		 inline const BOOL				GuardarUnsignedLong(unsigned long &Val) { 
											return Guardar(&Val, sizeof(unsigned long));
										};
										 
										//! Función para leer un size_t del archivo
										/*! Esta funcion lee un size_t del archivo y lo almacena en el buffer Val.
												\fn			inline const BOOL LeerSizeT(size_t &Val);
												\param[out]	Val	: size_t que se usara como buffer de lectura.
												\return		Devuelve el total de bytes leidos. 
												\remarks	Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarSizeT()
										*/
		 inline const BOOL				LeerSizeT(size_t &Val) {
											return Leer(&Val, sizeof(size_t));
										};
										
										//! Función para guardar un size_t en el archivo
										/*! Esta funcion guarda un size_t en el archivo.
												\fn			inline const BOOL GuardarSizeT(size_t &Val);
												\param[in]	Val : size_t que se guardara en el archivo.
												\return		Devuelve el total de bytes guardados.
												\sa			LeerSizeT()
										*/
		 inline const BOOL				GuardarSizeT(size_t &Val) { 
											return Guardar(&Val, sizeof(size_t));
										};
										 
										//! Función para leer un float del archivo
										/*! Esta funcion lee un float del archivo y lo almacena en el buffer Val.
												\fn			inline const BOOL LeerFloat(float &Val);
												\param[out]	Val	: float que se usara como buffer de lectura.
												\return		Devuelve el total de bytes leidos. 
												\remarks	Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarFloat()
										*/
		 inline const BOOL				LeerFloat(float &Val) {
											return Leer(&Val, sizeof(float));
										};
										 
										//! Función para guardar un float en el archivo
										/*! Esta funcion guarda un float en el archivo.
												\fn			inline const BOOL GuardarFloat(float &Val);
												\param[in]	Val : float que se guardara en el archivo.
												\return		Devuelve el total de bytes guardados.
												\sa			LeerFloat()
										*/
		 inline const BOOL				GuardarFloat(float &Val) { 
											return Guardar(&Val, sizeof(float));
										};
										
										//! Función para leer un DWORD del archivo
										/*! Esta funcion lee un DWORD del archivo y lo almacena en el buffer Val.
												\fn			inline const BOOL LeerDword(DWORD &Val);
												\param[out]	Val	: DWORD que se usara como buffer de lectura.
												\return		Devuelve el total de bytes leidos. 
												\remarks	Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarDword()
										*/
		 inline const BOOL				LeerDword(DWORD &Val) {
											return Leer(&Val, sizeof(DWORD));
										};
										 
										//! Función para guardar un DWORD en el archivo
										/*! Esta funcion guarda un DWORD en el archivo.
												\fn			inline const BOOL GuardarDword(DWORD &Val);
												\param[in]	Val : DWORD que se guardara en el archivo.
												\return		Devuelve el total de bytes guardados.
												\sa			LeerDword()
										*/
		 inline const BOOL				GuardarDword(DWORD &Val) { 
											return Guardar(&Val, sizeof(DWORD));
										};
										 
										//! Función para leer una estructura SYSTEMTIME del archivo
										/*! Esta funcion lee una estructura SYSTEMTIME del archivo y lo almacena en el buffer Val.
												\fn			inline const BOOL LeerSystemTime(SYSTEMTIME &Val);
												\param[out]	Val	: SYSTEMTIME que se usara como buffer de lectura.
												\return		Devuelve el total de bytes leidos. 
												\remarks	Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarSystemTime()
										*/
		 inline const BOOL				LeerSystemTime(SYSTEMTIME &Val) {
											return Leer(&Val, sizeof(SYSTEMTIME));
										};
										 
										//! Función para guardar un SYSTEMTIME en el archivo
										/*! Esta funcion guarda un SYSTEMTIME en el archivo.
												\fn			inline const BOOL GuardarSystemTime(SYSTEMTIME &Val);
												\param[in]	Val : SYSTEMTIME que se guardara en el archivo.
												\return		Devuelve el total de bytes guardados.
												\sa			LeerSystemTime()
										*/
		 inline const BOOL				GuardarSystemTime(SYSTEMTIME &Val) { 
											return Guardar(&Val, sizeof(SYSTEMTIME));
										};
										 
										//! Función para leer un char del archivo
										/*! Esta funcion lee un char del archivo y lo almacena en el buffer Val.
												\fn			inline const BOOL LeerChar(char &Val);
												\param[out]	Val	: char que se usara como buffer de lectura.
												\return		Devuelve el total de bytes leidos. 
												\remarks	Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarChar()
										*/
		 inline const BOOL				LeerChar(char &Val) {
											return Leer(&Val, sizeof(char));
										};
										 
										//! Función para guardar un char en el archivo
										/*! Esta funcion guarda un char en el archivo.
												\fn			inline const BOOL GuardarChar(char &Val);
												\param[in]	Val : char que se guardara en el archivo.
												\return		Devuelve el total de bytes guardados.
												\sa			LeerChar()
										*/
		 inline const BOOL				GuardarChar(char &Val) { 
											return Guardar(&Val, sizeof(char));
										};

										//! Función para leer un unsigned char del archivo
										/*! Esta funcion lee un unsigned char del archivo y lo almacena en el buffer Val.
												\fn			inline const BOOL LeerUnsignedChar(unsigned char &Val);
												\param[out]	Val	: unsigned char que se usara como buffer de lectura.
												\return		Devuelve el total de bytes leidos. 
												\remarks	Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarUnsignedChar()
										*/
		 inline const BOOL				LeerUnsignedChar(unsigned char &Val) {
											return Leer(&Val, sizeof(unsigned char));
										};

										//! Función para guardar un unsigned char en el archivo
										/*! Esta funcion guarda un unsigned char en el archivo.
												\fn			inline const BOOL GuardarUnsignedChar(unsigned char &Val);
												\param[in]	Val : unsigned char que se guardara en el archivo.
												\return		Devuelve el total de bytes guardados.
												\sa			LeerUnsignedChar()
										*/
		 inline const BOOL				GuardarUnsignedChar(unsigned char &Val) { 
											return Guardar(&Val, sizeof(unsigned char));
										};
										
										//! Función para leer un unsigned short del archivo
										/*! Esta funcion lee un unsigned short del archivo y lo almacena en el buffer Val.
												\fn			inline const BOOL LeerUnsignedShort(unsigned short &Val);
												\param[out]	Val	: unsigned short que se usara como buffer de lectura.
												\return		Devuelve el total de bytes leidos. 
												\remarks	Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarUnsignedShort()
										*/
		 inline const BOOL				LeerUnsignedShort(unsigned short &Val) {
											return Leer(&Val, sizeof(unsigned short));
										};
										
										//! Función para guardar un unsigned short en el archivo
										/*! Esta funcion guarda un unsigned short en el archivo.
												\fn			inline const BOOL GuardarUnsignedShort(unsigned short &Val);
												\param[in]	Val : unsigned short que se guardara en el archivo.
												\return		Devuelve el total de bytes guardados.
												\sa			LeerUnsignedShort()
										*/
		 inline const BOOL				GuardarUnsignedShort(unsigned short &Val) { 
											return Guardar(&Val, sizeof(unsigned short));
										};
										 
										//! Función para leer un BYTE del archivo
										/*! Esta funcion lee un BYTE del archivo y lo almacena en el buffer Val.
												\fn			inline const BOOL LeerByte(BYTE &Val);
												\param[out]	Val	: BYTE que se usara como buffer de lectura.
												\return		Devuelve el total de bytes leidos. 
												\remarks	Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarByte()
										*/
		 inline const BOOL				LeerByte(BYTE &Val) {
											return Leer(&Val, sizeof(BYTE));
										};
										 
										//! Función para guardar un BYTE en el archivo
										/*! Esta funcion guarda un BYTE en el archivo.
												\fn			inline const BOOL GuardarByte(BYTE &Val);
												\param[in]	Val : BYTE que se guardara en el archivo.
												\return		Devuelve el total de bytes guardados.
												\sa			LeerByte()
										*/
		 inline const BOOL				GuardarByte(BYTE &Val) { 
											return Guardar(&Val, sizeof(BYTE));
										};
										 
										//! Función para leer un bool del archivo
										/*! Esta funcion lee un bool del archivo y lo almacena en el buffer Val.
												\fn			inline const BOOL LeerBool(bool &Val);
												\param[out]	Val	: bool que se usara como buffer de lectura.
												\return		Devuelve el total de bytes leidos. 
												\remarks	Si la funcion retorna 0 es que se ha llegado al final del archivo o se ha producido un error. Utiliza GetLastError() para una descripcion detallada.
												\sa			GuardarBool()
										*/
		 inline const BOOL				LeerBool(bool &Val) {
											return Leer(&Val, sizeof(bool));
										};
										 
										//! Función para guardar un bool en el archivo
										/*! Esta funcion guarda un bool en el archivo.
												\fn			inline const BOOL GuardarBool(bool &Val);
												\param[in]	Val : bool que se guardara en el archivo.
												\return		Devuelve el total de bytes guardados.
												\sa			LeerBool()
										*/
		 inline const BOOL				GuardarBool(bool &Val) { 
											return Guardar(&Val, sizeof(bool));
										};
										 
										//! Función que posiciona el puntero de lectura/escritura
										/*! Esta funcion se utiliza para situar el puntero dentro del archivo. Este puntero es la posición actual de lectura / escritura.
												\fn			inline const ULONG Posicion(const long Pos, const bool Desde_El_Final = false);
												\param[in]	Pos				: Posiciones a desplazarse.
												\param[in]	Desde_El_Final	: Si se especifica true, empezaremos con el puntero en el final. False para empezar del principio.
												\return		Devuelve la posicion actual del puntero.
										*/
		 inline const ULONG				Posicion(const long Pos, const bool Desde_El_Final = false) {
											if (Desde_El_Final == false)	return SetFilePointer(_Archivo, Pos, NULL, FILE_BEGIN);
											else							return SetFilePointer(_Archivo, Pos, NULL, FILE_END);
										};

										//! Función que retorna la posición del cursor de lectura/escritura
										/*! Esta funcion se utiliza para obtener el puntero dentro del archivo. Este puntero es la posición actual de lectura / escritura.
												\fn			inline const ULONG Posicion(void);
												\return		Devuelve la posicion actual del puntero.
										*/
		 inline const ULONG             Posicion(void) {
											return SetFilePointer(_Archivo, 0, NULL, FILE_CURRENT);
										}
										 
										//! Función que indica si se ha llegado al final del archivo (EOF)
										/*! Esta funcion nos indica si se ha llegado al final del archivo.
												\fn			inline const bool FinalDelArchivo(void);
												\return		Devuelve true si estamos en el final del archivo, false en caso contrario.
										*/
		 inline const bool				FinalDelArchivo(void) {
											return _FinalDelArchivo;
										}

										//! Función que nos dice los caracteres que se han leido en la ultima operación de lectura
										/*! Esta funcion nos dice los caracteres que se han leido en la ultima operación de lectura.
												\fn			inline const DWORD CaracteresLeidos(void);
												\return		Devuelve el total de caracteres leidos.
										*/
		 inline const DWORD             CaracteresLeidos(void) {
											return _CaracteresLeidos;
										}

										// Función que devuelve el tamaño en bytes del archivo abierto.
										/*! Esta funcion devuelve el tamaño en bytes del archivo que tenemos abierto
												\fn			inline const DWORD Tam(void);
												\return		Devuelve el total de bytes que ocupa el archivo.
										*/
		 inline const DWORD				Tam(void) {
											return GetFileSize(_Archivo, NULL);
										}
		protected : ////////////////////// Miembros protegidos
										 
										//! Miembro que contiene la ID del archivo.
		 HANDLE				           _Archivo;

										//! Miembro que contiene los caracteres leidos en la ultima operación de lectura
		 DWORD                         _CaracteresLeidos;
										 
										//! Miembro que indica si se ha llegado al final del archivo
		 bool						   _FinalDelArchivo;
		}; ///////////////////////////////


/*		#if _MSC_VER > 1200	
			//! PENDIENTE DE ELIMINACION (Esta calse funciona practicamente igual a la de arriba, pero no compila en VC6 + UNICODE cosa que la de arriba si)
			class DWLArchivoBinario {
			public: //////////////////////
										//! Constructor por defecto
										//  DWLArchivoBinario(void);
										DWLArchivoBinario(void) { 
										};
										//
										//! Constructor que requiere path
										//  DWLArchivoBinario(const TCHAR *Path, const bool Abrir_si_no_existe = true);
										DWLArchivoBinario(const TCHAR *Path, const bool Abrir_si_no_existe = true) { 
											AbrirArchivo(Path, Abrir_si_no_existe);
										};
										//
										//! Destructor
										// ~DWLArchivoBinario(void);
									   ~DWLArchivoBinario(void) { 
											CerrarArchivo();
										};
										//
										//! Función para abrir un archivo lectura / escritura
										//  inline const bool AbrirArchivo(const TCHAR *Path, const bool Abrir_si_no_existe = false);
			 inline const bool          AbrirArchivo(const TCHAR *Path, const bool Abrir_si_no_existe = false) {
											CerrarArchivo();
											if (Abrir_si_no_existe == true) {
												_BDG.open(Path, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
												return true;
											}
											else {
												_BDG.open(Path, std::ios::in | std::ios::out | std::ios::binary);
												return _BDG.is_open();
											}
										};
										//
										//! Función para abrir un archivo solo lectura
										//  inline const bool AbrirArchivoLectura(const TCHAR *Path);
			 inline const bool          AbrirArchivoLectura(const TCHAR *Path) {
											CerrarArchivo();
											_BDG.open(Path, std::ios::in | std::ios::binary);
											return _BDG.is_open();
										};
										//
										//! Función para abrir un archivo solo escritura
										//  inline const bool AbrirArchivoLectura(const TCHAR *Path);
			 inline const bool          AbrirArchivoEscritura(const TCHAR *Path) {
											CerrarArchivo();
											_BDG.open(Path, std::ios::out | std::ios::binary);
											return _BDG.is_open();
										};
										//
										//! Función para abrir cerrar un archivo cargado
										//  inline void CerrarArchivo(void);
			 inline void                CerrarArchivo(void) {
											if (_BDG.is_open() == true)	
												_BDG.close();
										};
										//
										//! Función que retorna si el archivo esta abierto
										//  inline const bool EstaAbierto(void);
			 inline const bool          EstaAbierto(void) {
											return _BDG.is_open();
										};
										//
										//! Función para leer datos del archivo
										//  inline const size_t Leer(char *Val, const unsigned long Tam);
			 inline const size_t		Leer(char *Val, const unsigned long Tam) {
											_BDG.read(Val, Tam);
											return _BDG.gcount();								
										};
										//
										//! Función para guardar datos en el archivo
										//  inline void Guardar(char *Val, const unsigned long Tam);
			 inline void				Guardar(char *Val, const unsigned long Tam) {
											_BDG.write(Val, Tam);
										};
										// 
										//! Función para leer un wstring del archivo
										//  inline void LeerString(DWL::DWLString &Val);
			 inline void				LeerString(DWL::DWLString &Val) {
											unsigned int Tam = 0;
											TCHAR     *Tmp;
											_BDG.read(reinterpret_cast<char *>(&Tam), sizeof(unsigned int));	 // Leo Tamaño del string
 											Tmp = new TCHAR [Tam + 1];
											_BDG.read(reinterpret_cast<char *>(&Tmp[0]), Tam * sizeof(TCHAR)); // Leo el string
											Tmp[Tam] = 0;
											Val = Tmp;
											delete [] Tmp;
										};
										//
										//! Función para guardar un wstring en el archivo
										//  inline void GuardarString(DWL::DWLString &Val, const bool GuardarTam = true);
			 inline void				GuardarString(DWL::DWLString &Val, const bool GuardarTam = true) {
											unsigned int Tmp = static_cast<unsigned int>(Val.Tam());
											if (GuardarTam == true) _BDG.write(reinterpret_cast<char *>(&Tmp), sizeof(unsigned int));	// Tamaño del texto
											_BDG.write(reinterpret_cast<char *>(&Val[0]), Tmp * sizeof(TCHAR));						// Texto
										};
										//
										//! Función para leer un wstring del archivo
										//  inline void LeerString(std::wstring &Val);
			 inline void				LeerString(std::wstring &Val) {
											unsigned int Tam = 0;
											wchar_t     *Tmp;
											_BDG.read(reinterpret_cast<char *>(&Tam), sizeof(unsigned int));	 // Leo Tamaño del string
 											Tmp = new wchar_t [Tam + 1];
											_BDG.read(reinterpret_cast<char *>(&Tmp[0]), Tam * sizeof(wchar_t)); // Leo el string
											Tmp[Tam] = 0;
											Val = Tmp;
											delete [] Tmp;
										};
										//
										//! Función para guardar un wstring en el archivo
										//  inline void GuardarString(std::wstring &Val, const bool GuardarTam = true);
			 inline void				GuardarString(std::wstring &Val, const bool GuardarTam = true) {
											unsigned int Tmp = static_cast<unsigned int>(Val.size());
											if (GuardarTam == true) _BDG.write(reinterpret_cast<char *>(&Tmp), sizeof(unsigned int));	// Tamaño del texto
											_BDG.write(reinterpret_cast<char *>(&Val[0]), Tmp * sizeof(wchar_t));						// Texto
										};
										//
										//! Función para leer un string del archivo
										//  inline void LeerString(std::string &Val);
			 inline void				LeerString(std::string &Val) {
											unsigned int Tam = 0;
											char        *Tmp;
											_BDG.read(reinterpret_cast<char *>(&Tam), sizeof(unsigned int));	// Leo Tamaño del string
 											Tmp = new char [Tam + 1];
											_BDG.read(reinterpret_cast<char *>(&Tmp[0]), Tam * sizeof(char));	// Leo el string
											Tmp[Tam] = 0;
											Val = Tmp;
											delete [] Tmp;
										};
										//
										//! Función para guardar un string en el archivo
										//  inline void GuardarString(std::string &Val, const bool GuardarTam = true);
			 inline void				GuardarString(std::string &Val, const bool GuardarTam = true) {
											unsigned int Tmp = static_cast<unsigned int>(Val.size());
											if (GuardarTam == true) _BDG.write(reinterpret_cast<char *>(&Tmp), sizeof(unsigned int));	// Tamaño del texto
											_BDG.write(reinterpret_cast<char *>(&Val[0]), Tmp * sizeof(char));							// Texto
										};
										//
										//! Función para leer un int del archivo
										//  inline void LeerInt(int &Val);
			 inline void				LeerInt(int &Val) {
											_BDG.read(reinterpret_cast<char *>(&Val), sizeof(int));
										};
										// 
										//! Función para guardar un int en el archivo
										//  inline void GuardarInt(int &Val);
			 inline void				GuardarInt(int &Val) { 
											_BDG.write(reinterpret_cast<char *>(&Val), sizeof(int));
										};
										//
										//! Función para leer un int del archivo
										//  inline void LeerInt64(int &Val);
			 inline void				LeerInt64(__int64 &Val) {
											_BDG.read(reinterpret_cast<char *>(&Val), sizeof(int));
										};
										//
										//! Función para guardar un int en el archivo
										//  inline void GuardarInt64(__int64 &Val);
			 inline void				GuardarInt64(__int64 &Val) { 
											_BDG.write(reinterpret_cast<char *>(&Val), sizeof(int));
										};
										//
										//! Función para leer un long del archivo
										//  inline void LeerLong(long &Val);
			 inline void				LeerLong(long &Val) {
											_BDG.read(reinterpret_cast<char *>(&Val), sizeof(long));
										};
										//
										//! Función para guardar un long en el archivo
										//  inline void GuardarLong(long &Val);
			 inline void				GuardarLong(long &Val) { 
											_BDG.write(reinterpret_cast<char *>(&Val), sizeof(long));
										};
										//
										//! Función para leer un unsigned int del archivo
										//  inline void LeerUnsignedInt(unsigned int &Val);
			 inline void				LeerUnsignedInt(unsigned int &Val) {
											_BDG.read(reinterpret_cast<char *>(&Val), sizeof(unsigned int));
										};
										//
										//! Función para guardar un unsigned int en el archivo
										//  inline void GuardarUnsignedInt(unsigned int &Val);
			 inline void				GuardarUnsignedInt(unsigned int &Val) { 
											_BDG.write(reinterpret_cast<char *>(&Val), sizeof(unsigned int));
										};
										// 
										//! Función para leer un unsigned long del archivo
										//  inline void LeerUnsignedLong(unsigned long &Val);
			 inline void				LeerUnsignedLong(unsigned long &Val) {
											_BDG.read(reinterpret_cast<char *>(&Val), sizeof(unsigned long));
										};
										//
										//! Función para guardar un unsigned long en el archivo
										//  inline void GuardarUnsignedLong(unsigned long &Val);
			 inline void				GuardarUnsignedLong(unsigned long &Val) { 
											_BDG.write(reinterpret_cast<char *>(&Val), sizeof(unsigned long));
										};
										//
										//! Función para leer un size_t del archivo
										//  inline void LeerSizeT(size_t &Val);
			 inline void				LeerSizeT(size_t &Val) {
											_BDG.read(reinterpret_cast<char *>(&Val), sizeof(unsigned long));
										};
										//
										//! Función para guardar un size_t en el archivo
										//  inline void GuardarSizeT(size_t &Val);
			 inline void				GuardarSizeT(size_t &Val) { 
											_BDG.write(reinterpret_cast<char *>(&Val), sizeof(unsigned long));
										};
										//
										//! Función para leer un float del archivo
										//  inline void LeerFloat(float &Val);
			 inline void				LeerFloat(float &Val) {
											_BDG.read(reinterpret_cast<char *>(&Val), sizeof(float));
										};
										//
										//! Función para guardar un float en el archivo
										//  inline void GuardarFloat(float &Val);
			 inline void				GuardarFloat(float &Val) { 
											_BDG.write(reinterpret_cast<char *>(&Val), sizeof(float));
										};
										//
										//! Función para leer un DWORD del archivo
										//  inline void LeerDword(DWORD &Val);
			 inline void				LeerDword(DWORD &Val) {
											_BDG.read(reinterpret_cast<char *>(&Val), sizeof(DWORD));
										};
										//
										//! Función para guardar un DWORD en el archivo
										//  inline void GuardarDword(DWORD &Val);
			 inline void				GuardarDword(DWORD &Val) { 
											_BDG.write(reinterpret_cast<char *>(&Val), sizeof(DWORD));
										};
										//
										//! Función para leer un SYSTEMTIME del archivo
										//  inline void LeerSystemTime(SYSTEMTIME &Val);
			 inline void				LeerSystemTime(SYSTEMTIME &Val) {
											_BDG.read(reinterpret_cast<char *>(&Val), sizeof(SYSTEMTIME));
										};
										//
										//! Función para guardar un SYSTEMTIME en el archivo
										//  inline void GuardarSistemTime(SYSTEMTIME &Val);
			 inline void				GuardarSystemTime(SYSTEMTIME &Val) { 
											_BDG.write(reinterpret_cast<char *>(&Val), sizeof(SYSTEMTIME));
										};
										//
										//! Función para leer un char del archivo
										//  inline void LeerChar(char &Val);
			 inline void				LeerChar(char &Val) {
											_BDG.read(reinterpret_cast<char *>(&Val), sizeof(char));
										};
										//
										//! Función para guardar un char en el archivo
										//  inline void GuardarChar(char &Val);
			 inline void				GuardarChar(char &Val) { 
											_BDG.write(reinterpret_cast<char *>(&Val), sizeof(char));
										};
										//
										//! Función para leer un unsigned char del archivo
										//  inline void LeerUnsignedChar(unsigned char &Val);
			 inline void				LeerUnsignedChar(unsigned char &Val) {
											_BDG.read(reinterpret_cast<char *>(&Val), sizeof(unsigned char));
										};
										//
										//! Función para guardar un unsigned char en el archivo
										//  inline void GuardarUnsignedChar(unsigned char &Val);
			 inline void				GuardarUnsignedChar(unsigned char &Val) { 
											_BDG.write(reinterpret_cast<char *>(&Val), sizeof(unsigned char));
										};
										//
										//! Función para leer un unsigned short del archivo
										//  inline void LeerUnsignedShort(unsigned short &Val);
			 inline void				LeerUnsignedShort(unsigned short &Val) {
											_BDG.read(reinterpret_cast<char *>(&Val), sizeof(unsigned short));
										};
										//
										//! Función para guardar un unsigned short en el archivo
										//  inline void GuardarUnsignedShort(unsigned short &Val);
			 inline void				GuardarUnsignedShort(unsigned short &Val) { 
											_BDG.write(reinterpret_cast<char *>(&Val), sizeof(unsigned short));
										};
										//
										//! Función para leer un BYTE del archivo
										//  inline void LeerByte(BYTE &Val);
			 inline void				LeerByte(BYTE &Val) {
											_BDG.read(reinterpret_cast<char *>(&Val), sizeof(BYTE));
										};
										//
										//! Función para guardar un BYTE en el archivo
										//  inline void GuardarByte(BYTE &Val);
			 inline void				GuardarByte(BYTE &Val) { 
											_BDG.write(reinterpret_cast<char *>(&Val), sizeof(BYTE));
										};
										//
										//! Función para leer un bool del archivo
										//  inline void LeerBool(bool &Val);
			 inline void				LeerBool(bool &Val) {
											_BDG.read(reinterpret_cast<char *>(&Val), sizeof(bool));
										};
										//
										//! Función para guardar un bool en el archivo
										//  inline void GuardarBool(bool &Val);
			 inline void				GuardarBool(bool &Val) { 
											_BDG.write(reinterpret_cast<char *>(&Val), sizeof(bool));
										};
										//
										//! Función que posiciona el puntero de lectura
										//  inline const unsigned long Posicion_Lectura(const long Pos, const bool Desde_El_Final = false);
			 inline const unsigned long Posicion_Lectura(const long Pos, const bool Desde_El_Final = false) {
											if (Desde_El_Final == false) _BDG.seekg(Pos, std::ios_base::beg);
											else						 _BDG.seekg(Pos, std::ios_base::end);
											return _BDG.tellg();
										};
										//
										//! Función que retorna la posicion del puntero de lectura
										//  inline const unsigned long Posicion_Lectura(void);
			 inline const unsigned long Posicion_Lectura(void) {
											return _BDG.tellg();
										};
										// 
										//! Función que posiciona el puntero de escritura
										//  inline void Posicion_Escritura(const long Pos, const bool Desde_El_Final = false);
			 inline const unsigned long Posicion_Escritura(const long Pos, const bool Desde_El_Final = false) {
											if (Desde_El_Final == false) _BDG.seekp(Pos, std::ios_base::beg);
											else					     _BDG.seekp(Pos, std::ios_base::end);
											return _BDG.tellp();
										};
										//
										//! Función que retorna la posicion del puntero de lectura
										//  inline const unsigned long Posicion_Escritura(void);
			 inline const unsigned long Posicion_Escritura(void) {
											return _BDG.tellp();
										};
										//
										//! Función que retorna true si la posicion esta en el final del archivo
										//  inline const bool FinalDelArchivo(void);
			 inline const bool			FinalDelArchivo(void) {
											return _BDG.eof();
										};	
										//
										//! Función que retorna true si ha sucedido algun error
										//  inline const bool Error(void);										
			 inline const bool			Error(void) {
											return _BDG.bad();
										};	
			protected : ////////////////// Miembros protegidos
										//
										//! FileStream que se usa internamente para las operaciones lectura/escritura de esta clase
			 std::fstream	           _BDG;
			}; ///////////////////////////

		#endif*/




	}
}


#endif // DWL_ARCHIVOBINARIO_H
