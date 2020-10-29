/*! \file DWL_Compilador_MSC1300.h
	\brief Archivo que proporciona compatibilidad con el compilador Visual Studio 2003 C++.
*/ 

#if _MSC_VER == 1300	
    #ifndef	DWL_COMPILADOR_MSC1300
	    #define DWL_COMPILADOR_MSC1300

	    #define UNICODE	// Si no quieres compilar la aplicacion para unicode, comenta esta linea
		#include <tchar.h>

		#ifndef WINVER                      // Especifica que la plataforma mínima requerida es Windows XP.
            #define WINVER 0x0500           // Cambiar al valor apropiado correspondiente a otras versiones de Windows.
        #endif
        #ifndef _WIN32_WINNT                // Especifica que la plataforma mínima requerida es Windows XP.
            #define _WIN32_WINNT 0x0500     // Cambiar al valor apropiado correspondiente a otras versiones de Windows.
        #endif
        #ifndef _WIN32_WINDOWS              // Especifica que la plataforma mínima requerida es Windows 98.
            #define _WIN32_WINDOWS 0x0410   // Cambiar al valor apropiado correspondiente a Windows Me o posterior.
        #endif
        #ifndef _WIN32_IE                   // Especifica que la plataforma mínima requerida es Internet Explorer 6.0.
            #define _WIN32_IE 0x0600        // Cambiar al valor apropiado correspondiente a otras versiones de IE.
        #endif

        #include <windows.h>
        #include <commctrl.h>
		#pragma comment(lib, "comctl32.lib")	// Libreria para los common controls de windows
		#pragma comment(lib, "msimg32.lib")		// Libreria del AlphaBlend y GradientFill
		#pragma comment(lib, "mpr.lib")			// Libreria para redes de microsoft windows
		#pragma comment(lib, "ole32.lib")		// Libreria para objetos Ole32
		#pragma comment(lib, "shell32.lib")     // Libreria para los dialogos comunes
		#pragma comment(lib, "dbghelp.lib")		// Libreria para las excepciones graves

        // Definimos macros para funciones basicas dependiendo de si la configuracion es UNICODE o ANSI
        #if defined UNICODE
			// Funciones seguras UNICODE para VC9
			#define DWLStrCopy(Destino, Longitud_Destino, Origen)					wcscpy_s(Destino, Longitud_Destino, Origen)
        	#define DWLStrLen(Texto)												wcslen(Texto)
        	#define DWLStrCmpi(Texto1, Texto2)									   _wcsicmp(Texto1, Texto2)
        	#define DWLStrCmp(Texto1, Texto2)										wcscmp(Texto1, Texto2)
        	#define DWLStrToInt(Texto)											   _wtoi(Texto)
        	#define DWLFOpen(FILE, Path, Modo)							           _wfopen_s(FILE, Path, Modo)
        	#define DWLvsPrintf(Buffer, Longitud_Buffer, Formato_Texto, VA_LIST)	vswprintf_s(Buffer, Longitud_Buffer, Formato_Texto, VA_LIST)
            #define DWLIntToText(Numero, Destino, Longitud_Destino, Base)          _itow_s(Numero, Destino, Longitud_Destino, Base);
         	#define DWLLPCSTR														LPCWSTR        
		#else
			// Funciones ANSI para Visual Studio 9 con funciones seguras
        	#define DWLStrCopy(Destino, Longitud_Destino, Origen)					strcpy_s(Destino, Longitud_Destino, Origen)
        	#define DWLStrLen(Texto)												strlen(Texto)
        	#define DWLStrCmpi(Texto1, Texto2)									   _strcmpi(Texto1, Texto2)
        	#define DWLStrCmp(Texto1, Texto2)										strcmp(Texto1, Texto2)
        	#define DWLStrToInt(Texto)											    atoi(Texto)
        	#define DWLFOpen(FILE, Path, Modo)										fopen_s(FILE, Path, Modo)
        	#define DWLvsPrintf(Buffer, Longitud_Buffer, Formato_Texto, VA_LIST)    vsprintf_s(Buffer, Longitud_Buffer, Formato_Texto, VA_LIST)
            #define DWLIntToText(Numero, Destino, Longitud_Destino, Base)          _itoa_s(Numero, Destino, Longitud_Destino, Base);
         	#define DWLLPCSTR														LPCSTR        
		#endif

    #endif
#endif