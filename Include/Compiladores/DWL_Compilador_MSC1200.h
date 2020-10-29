/*! \file DWL_Compilador_MSC1200.h
	\brief Archivo que proporciona compatibilidad con el compilador VisualC6 del 1997.
*/
 
#if _MSC_VER == 1200
    #ifndef	DWL_COMPILADOR_MSC1200
	    #define DWL_COMPILADOR_MSC1200

//	    #pragma warning(disable: 4786) // Desactivo warnigs que lanza el VC6 cuando los nombres de funciones sobrepasan los 255 caracteres
    	
	    #define UNICODE	// Si no quieres compilar la aplicacion para unicode, comenta esta linea

        #if!defined WINVER
    	    #define WINVER			0x0410
   	    #endif
        #if!defined _WIN32_WINNT
    	    #define _WIN32_WINNT	0x0410
   	    #endif
        #if!defined _WIN32_WINDOWS
    	    #define _WIN32_WINDOWS  0x0410
   	    #endif
        #if!defined _WIN32_IE
    	    #define _WIN32_IE		0x0500
        #endif
    	
        #include <windows.h>
        #include <commctrl.h>
	    #pragma comment(lib, "comctl32.lib")	// Agrego la libreria comclt32.lib al proyecto
	    #pragma comment(lib, "msimg32.lib")		// Libreria del AlphaBlend y Gradientill
	    #pragma comment(lib, "Mpr.lib")			// Libreria para redes de microsoft windows
	    #pragma comment(lib, "ole32.lib")		// Libreria para objetos Ole32
	    #pragma comment(lib, "shell32.lib")     // Libreria para los dialogos comunes
    //	#pragma comment(lib, "dbghelp.lib")		// Libreria para las excepciones graves (no va en vc6)

	    // Tipos para win32/64 
	    typedef long			LONG_PTR, *PLONG_PTR;
	    typedef unsigned long	ULONG_PTR, *PULONG_PTR;

	    // Conversiones de punteros
	    #define LongToPtr(l)													((VOID *)(LONG_PTR)((long)l))
	    #define IntToPtr(i)														((VOID *)(INT_PTR)((int)i))
    //		#define PtrToLong(p)													((LONG)(LONG_PTR)(p))


	    // Definiciones de botones extendidos del mouse
	    #if!defined WM_XBUTTONDOWN
		    #define WM_XBUTTONDOWN													0x020B
		    #define WM_XBUTTONUP													0x020C
		    #define WM_XBUTTONDBLCLK												0x020D
	    #endif
    	
	    // Definiciones para AlphaBlend
	    #define LWA_ALPHA														0x00000002

	    // Definiciones para Get/SetWindowLongPtr
	    #define GWLP_WNDPROC											        (-4)
	    #define GWLP_USERDATA													(-21)

	    // Defino la macro _ASSERT vacia..
//	    #define _ASSERT(EXPRESION)


	    #if defined UNICODE
		    // Funciones estandar UNICODE para devc++ y vc6
    	    #define DWLStrCopy(Destino, Longitud_Destino, Origen)					wcscpy(Destino, Origen)
    	    #define DWLStrLen(Texto)												wcslen(Texto)
    	    #define DWLStrCmpi(Texto1, Texto2)									   _wcsicmp(Texto1, Texto2)
    	    #define DWLStrCmp(Texto1, Texto2)										wcscmp(Texto1, Texto2)
    	    #define DWLStrToInt(Texto)											   _wtoi(Texto)
    	    #define DWLFOpen(FILE, Path, Modo)							           _wfopen(FILE, Path, Modo)
    	    #define DWLvsPrintf(Buffer, Longitud_Buffer, Formato_Texto, VA_LIST)	vswprintf(Buffer, Formato_Texto, VA_LIST)
            #define DWLIntToText(Numero, Destino, Longitud_Destino, Base)          _itow(Numero, Destino, Base);
            #define DWLLPCSTR														LPCWSTR        
	    #else
		    // Funciones estandar ANSI para devc++ y vc6
    	    #define DWLStrCopy(Destino, Longitud_Destino, Origen)					strcpy(Destino, Origen)
    	    #define DWLStrLen(Texto)												strlen(Texto)
    	    #define DWLStrCmpi(Texto1, Texto2)									   _strcmpi(Texto1, Texto2)
    	    #define DWLStrCmp(Texto1, Texto2)										strcmp(Texto1, Texto2)
    	    #define DWLStrToInt(Texto)											    atoi(Texto)
    	    #define DWLFOpen(FILE, Path, Modo)										FILE = fopen(Path, Modo)
    	    #define DWLvsPrintf(Buffer, Longitud_Buffer, Formato_Texto, VA_LIST)    vsprintf(Buffer, Formato_Texto, VA_LIST)
            #define DWLIntToText(Numero, Destino, Longitud_Destino, Base)          _itoa(Numero, Destino, Base);
       	    #define DWLLPCSTR														LPCSTR        
	    #endif

	    // Re-emplazo de las funciones seguras de VC7 o superior por las funciones estandar de VC6
	    #define _itow_s(NUMERO, CHARDESTINO, TAMCHARDESTINO, BASE)				_itow(NUMERO, CHARDESTINO, BASE)
	    #define _itoa_s(NUMERO, CHARDESTINO, TAMCHARDESTINO, BASE)				_itoa(NUMERO, CHARDESTINO, BASE)
	    #define vswprintf_s(CHARDESTINO, TAMCHARDESTINO, CHARORIGEN, MARKER)	vswprintf(CHARDESTINO, CHARORIGEN, MARKER)
	    #define vsprintf_s(CHARDESTINO, TAMCHARDESTINO, CHARORIGEN, MARKER)		vsprintf(CHARDESTINO, CHARORIGEN, MARKER)
	    #define strcpy_s(CHARDESTINO, TAMCHARDESTINO, CHARORIGEN)				strcpy(CHARDESTINO, CHARORIGEN)
	    #define wcscpy_s(CHARDESTINO, TAMCHARDESTINO, CHARORIGEN)				wcscpy(CHARDESTINO, CHARORIGEN)
	    #define fopen_s(ARCHIVO, PATH, MODO)									*ARCHIVO = fopen(PATH, MODO)
	    #define _wfopen_s(ARCHIVO, PATH, MODO)									*ARCHIVO = _wfopen(PATH, MODO)
    	
	    #define GetWindowLongPtr(HWND, TIPOESTILO)								GetWindowLong(HWND, TIPOESTILO)
	    #define SetWindowLongPtr(HWND, TIPOESTILO, ESTILO)						SetWindowLong(HWND, TIPOESTILO, ESTILO)
	    #define TrackMouseEvent(TRACK)											_TrackMouseEvent(TRACK)

	    // Definiciones para la rudea del mouse
	    #if!defined WM_MOUSEWHEEL
		    #define WM_MOUSEWHEEL                   0x020A
		    #define GET_WHEEL_DELTA_WPARAM(wParam)  ((short)HIWORD(wParam))
	    #endif

	    // Definiciones para buscar directorios
	    #define CSIDL_COMMON_APPDATA            0x0023        // All Users\Application Data
	    #define CSIDL_CONNECTIONS               0x0031
	    #define CSIDL_COMPUTERSNEARME           0x003d
		#define CSIDL_COMMON_DOCUMENTS          0x002e        // All Users\Documents
		#define CSIDL_PERSONAL                  0x0005        // My Documents
		#define CSIDL_MYDOCUMENTS               CSIDL_PERSONAL //  Personal was just a silly name for My Documents
		#define CSIDL_COMMON_MUSIC              0x0035        // All Users\My Music
		#define CSIDL_COMMON_PICTURES           0x0036        // All Users\My Pictures
		#define CSIDL_COMMON_VIDEO              0x0037        // All Users\My Video
		#define CSIDL_MYMUSIC                   0x000d        // "My Music" folder
		#define CSIDL_MYVIDEO                   0x000e        // "My Videos" folder
		#define CSIDL_WINDOWS                   0x0024        // GetWindowsDirectory()
		#define CSIDL_MYPICTURES                0x0027        // C:\Program Files\My Pictures

	    #define SHGetFolderPath _SHGetFolderPath
    //		#define CSIDL_PERSONAL               0x0031

    #endif
#endif