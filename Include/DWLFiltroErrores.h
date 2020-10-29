/*! \file DWLFiltroErrores.h
	\brief Archivo que controlara los errores criticos
*/
// NO COMPILA EN VC6, Y EN MINGW ESTA POR PROBAR

#if (COMPILADOR == COMPILADOR_VC9 || COMPILADOR == COMPILADOR_VC10)

#ifndef DWL_FILTROERRORES_H
#define DWL_FILTROERRORES_H

#include "DWLString.h"

#include <ShellAPI.h>
#include <dbghelp.h>

// Clase plantilla que encapsula los errores graves
// DWL_CLASE_FILTRO debe ser una clase que tenga una funcion Mostrar : void Mostrar(const TCHAR *PathDump);
// En el parametro PathDump recibiremos el path donde se ha guardado el archivo.dmp con el error
namespace DWL {
	template <class DWL_CLASE_FILTRO> class DWLFiltroErrores {
	  public:									// Constructor vacio
												DWLFiltroErrores(void) { 
												};
												// Funcion que deberá enlazar el filtro de excepciones
												// Retorna true si todo va bien.
												// Retorna false si el archivo de dump no existe y se ha usado el parámetro -MostrarErrorCritico
												// el parametro nNombreApp esta echo para un nombre en ansi, NADA de acentos, ni simbolos de puntuacion, ni barras ni operadores aritmeticos!
		virtual const bool						Iniciar(const TCHAR *nNombreApp) { 
													_NombreApp = nNombreApp;
													bool    MostrarError = false;
													int		TotalArgs	 = 0;
													TCHAR **Args		 = CommandLineToArgvW(GetCommandLine(), &TotalArgs);
													if (TotalArgs > 1) {
														if (DWLStrCmp(Args[1] ,TEXT("-MostrarErrorCritico")) == 0) MostrarError = true;
													}
													if (MostrarError == false) {
														_Mostrado = false;
														_Mutex = NULL;
														_FiltroPorDefecto = SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)DWLFiltroErrores<DWL_CLASE_FILTRO>::_FiltroErrores);
														if (TotalArgs > 0) LocalFree(Args);
													}		
													else {
														TCHAR  _Path[MAX_PATH];
														TCHAR  _Buffer[MAX_PATH];
//														TCHAR  _Nombre[MAX_PATH];
//														TCHAR  *Arg0 = Args[0];
/*														size_t  TamTxt = 0;
														for (size_t z = wcslen(Args[0]); z > 0; z --) {
															if (Arg0[z - 1] == TEXT('\\')) {
																wcscpy_s(_Nombre, MAX_PATH, &Arg0[z]);
//																TamTxt = wcslen(_Nombre);
//																if (TamTxt > 5)	_Nombre[TamTxt - 4] = TEXT('\0');
																break;
															}
														}*/
														SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, _Buffer);
														swprintf_s(_Path, MAX_PATH, TEXT("%s\\DUMP %s.dmp"), _Buffer, _NombreApp());
														MessageBox(NULL, _Path, TEXT("Path Dump"), MB_OK);
														// Comprobar si existe el error.dmp, si no existe mostramos otro mensaje de error
														HANDLE Archivo = CreateFile(_Path, FILE_READ_DATA, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
														if (Archivo == INVALID_HANDLE_VALUE) return false;
														CloseHandle(Archivo);
														DWL_CLASE_FILTRO VentanaFiltroErrores;
														VentanaFiltroErrores.Mostrar(_Path);
//														VentanaFiltroErrores.Mostrar(static_cast<struct _EXCEPTION_POINTERS*>(pThis));
														MSG Msg;
														while (GetMessage(&Msg, NULL, 0, 0) > 0) {
															TranslateMessage(&Msg);
															DispatchMessage(&Msg);
														}
														if (TotalArgs > 0) LocalFree(Args);
														exit(0);
													}
													return true;
												};
	  protected:
												// Función que deberá iniciar un nuevo thread con los datos del dump
		static LONG WINAPI                     _FiltroErrores(struct _EXCEPTION_POINTERS* ExceptionInfo) {
													if (_Mostrado == true) return -1;
													_Mostrado = true;
													try {
														int		TotalArgs	 = 0;
														TCHAR **Args		 = CommandLineToArgvW(GetCommandLine(), &TotalArgs);
														TCHAR  *Arg0         = Args[0];
//														TCHAR  _Path[MAX_PATH];
														TCHAR  _Buffer[MAX_PATH];
														TCHAR  _Nombre[MAX_PATH];
														/*for (size_t z = wcslen(Arg0); z > 0; z --) {
															if (Arg0[z - 1] == TEXT('\\')) {
																wcscpy_s(_Path, MAX_PATH, &Arg0[z]);
																break;
															}
														}*/
														SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, _Nombre);
														swprintf_s(_Buffer, MAX_PATH, TEXT("%s\\DUMP %s.dmp"), _Nombre, _NombreApp());
														MessageBox(NULL, _Buffer, TEXT("ou"), MB_OK);

														if (ExceptionInfo == NULL) return -1;
														HANDLE hFile = CreateFile(_Buffer, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 

														if((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))  {
															// Create the minidump 
															MINIDUMP_EXCEPTION_INFORMATION mdei; 
															mdei.ThreadId           = GetCurrentThreadId(); 
															mdei.ExceptionPointers  = ExceptionInfo; 
															mdei.ClientPointers     = FALSE; 

															MINIDUMP_CALLBACK_INFORMATION mci; 

															mci.CallbackRoutine     = NULL; //(MINIDUMP_CALLBACK_ROUTINE)MyMiniDumpCallback; 
															mci.CallbackParam       = 0; 

															MINIDUMP_TYPE mdt       = (MINIDUMP_TYPE)(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory | MiniDumpNormal); 

															BOOL rv = MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(), hFile, mdt, (ExceptionInfo != 0) ? &mdei : 0, 0, &mci ); 

															CloseHandle(hFile); 
														}
														ShellExecute(NULL, TEXT("Open"), Arg0, TEXT("-MostrarErrorCritico"), NULL, SW_SHOW);
														if (TotalArgs > 0) LocalFree(Args);
													}
													catch (...) {
														exit(1);
													}
													return TRUE;
												};

		static unsigned long		           _ThreadExcepcionGrave(void *pThis) {
//													MessageBox(NULL, TEXT("filtro2"), TEXT("f2"), MB_OK);
													DWL_CLASE_FILTRO VentanaFiltroErrores;
													VentanaFiltroErrores.Crear(TEXT(""));
													VentanaFiltroErrores.Mostrar(static_cast<struct _EXCEPTION_POINTERS*>(pThis));
													MSG Msg;
													while (GetMessage(&Msg, NULL, 0, 0) > 0) {
														TranslateMessage(&Msg);
														DispatchMessage(&Msg);
													}
													// Libero el mutex y dejo que termine el filtro de errores
													ReleaseMutex(_Mutex);
													return 0;
												};

		static LPTOP_LEVEL_EXCEPTION_FILTER	   _FiltroPorDefecto;
		static HANDLE                          _Mutex;
		static bool                            _Mostrado;
		static DWL::DWLString                  _NombreApp;
	};

	template <class DWL_CLASE_FILTRO> LPTOP_LEVEL_EXCEPTION_FILTER	DWLFiltroErrores<DWL_CLASE_FILTRO>::_FiltroPorDefecto	= NULL;
	template <class DWL_CLASE_FILTRO> HANDLE						DWLFiltroErrores<DWL_CLASE_FILTRO>::_Mutex				= NULL;
	template <class DWL_CLASE_FILTRO> bool							DWLFiltroErrores<DWL_CLASE_FILTRO>::_Mostrado			= false;
	template <class DWL_CLASE_FILTRO> DWL::DWLString				DWLFiltroErrores<DWL_CLASE_FILTRO>::_NombreApp;
//	template <class DWL_CLASE_FILTRO> TCHAR							DWLFiltroErrores<DWL_CLASE_FILTRO>::_Path[MAX_PATH];
	//template <class DWL_CLASE_FILTRO> TCHAR							DWLFiltroErrores<DWL_CLASE_FILTRO>::_Buffer[MAX_PATH];
	//template <class DWL_CLASE_FILTRO> TCHAR							DWLFiltroErrores<DWL_CLASE_FILTRO>::_Nombre[MAX_PATH];
};

	#endif

#endif