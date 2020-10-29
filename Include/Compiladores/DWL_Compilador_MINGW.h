/*! \file DWL_Compilador_MINGW.h
	\brief Archivo que proporciona compatibilidad con el compilador MINGW.
*/
 

#if defined __MINGW32__
    #ifndef DWL_COMPILADOR_MINGW
        #define DWL_COMPILADOR_MINGW

        #if!defined WINVER
    		#define WINVER			0x0600
   		#endif
    	#if!defined _WIN32_WINNT
    		#define _WIN32_WINNT	0x0600
   		#endif
    	#if!defined _WIN32_WINDOWS
    		#define _WIN32_WINDOWS  0x0410
   		#endif
    	#if!defined _WIN32_IE
    		#define _WIN32_IE		0x0700
    	#endif


		#if defined UNICODE
			// Funciones estandar UNICODE para MINGW y vc6
        	#define DWLStrCopy(Destino, Longitud_Destino, Origen)					wcscpy(Destino, Origen)
        	#define DWLStrLen(Texto)												wcslen(Texto)
        	#define DWLStrCmpi(Texto1, Texto2)									   _wcsicmp(Texto1, Texto2)
        	#define DWLStrCmp(Texto1, Texto2)										wcscmp(Texto1, Texto2)
        	#define DWLStrToInt(Texto)											   _wtoi(Texto)
        	#define DWLFOpen(FILE, Path, Modo)							           _wfopen(FILE, Path, Modo)
        	#define DWLvsPrintf(Buffer, Longitud_Buffer, Formato_Texto, VA_LIST)	vswprintf(Buffer, Formato_Texto, VA_LIST)
            #define DWLIntToText(Numero, Destino, Longitud_Destino, Base)          _itow(Numero, Destino, Base);
		#else
			// Funciones estandar ANSI para MINGW y vc6
        	#define DWLStrCopy(Destino, Longitud_Destino, Origen)					strcpy(Destino, Origen)
        	#define DWLStrLen(Texto)												strlen(Texto)
        	#define DWLStrCmpi(Texto1, Texto2)									   _strcmpi(Texto1, Texto2)
        	#define DWLStrCmp(Texto1, Texto2)										strcmp(Texto1, Texto2)
        	#define DWLStrToInt(Texto)											    atoi(Texto)
        	#define DWLFOpen(FILE, Path, Modo)										FILE = fopen(Path, Modo)
        	#define DWLvsPrintf(Buffer, Longitud_Buffer, Formato_Texto, VA_LIST)    vsprintf(Buffer, Formato_Texto, VA_LIST)
            #define DWLIntToText(Numero, Destino, Longitud_Destino, Base)          _itoa(Numero, Destino, Base);
		#endif

        #include <windows.h>
        #include <commctrl.h>
		// NOTA : Para MINGW no existe la directiva "#pragma comment" por lo que es necesario añadir las librerias manualmente.
		//		  Deberas añadir las siguientes librerias : libcomctl32.a, libmsimg32.a, libmpr.a, libole32.a, libshell32.a y libdbghelp.a

        // Esta estructura no se encuentra definida en MINGW y es necesaria para obtener pulsaciones de teclado
        // Sobretodo para labeledits en treeviews y listviews, ya que necesitamos saber cuando se presiona el intro.
        typedef struct tagNMKEY
        {
            NMHDR hdr;
            UINT  nVKey;
            UINT  uFlags;
        } NMKEY, *LPNMKEY;

        // CSLID para MYDOCUMENTS
        // En MINGW no existe esta definicion, que es la misma que CSIDL_PERSONAL
        // A mi me parece mucho mas descriptiva la de MisDocumentos, y por eso la incluyo.
        #define CSIDL_MYDOCUMENTS               CSIDL_PERSONAL //  Personal was just a silly name for My Documents

        // Re-emplazo las macros MAKEINTRESOURCE
        #undef  MAKEINTRESOURCEA
        #define MAKEINTRESOURCEA(i) ((LPSTR)((ULONG_PTR)(i)))
        #undef  MAKEINTRESOURCEW
        #define MAKEINTRESOURCEW(i) ((LPWSTR)((ULONG_PTR)(i)))

    #endif
#endif
