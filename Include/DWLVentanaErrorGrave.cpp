#include "DWLVentanaErrorGrave.h"
#include "DWLGraficos.h"
#include "DWLDirectoriosWindows.h"
#if (COMPILADOR == COMPILADOR_VC9 || COMPILADOR == COMPILADOR_VC10)
	#include <dbghelp.h>
#endif

//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres Ventanas
    namespace Ventanas {
        DWLVentanaErrorGrave::DWLVentanaErrorGrave(void) { 
            _ExceptionInfo = NULL; 
        };

        DWLVentanaErrorGrave::~DWLVentanaErrorGrave(void) { 
        }; 


        const BOOL DWLVentanaErrorGrave::Crear(const TCHAR *PathDump) { 
		    if (CrearVentana(0, TEXT("DWLVentanaErrorGrave"), WS_CAPTION | WS_POPUP | WS_SYSMENU, TEXT("Error Grave"), DWL_CENTRADO, DWL_CENTRADO, 500, 230, 0) == 0) return FALSE;
			_BotonGuardar.CrearBotonEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("Guardar"), 170, 170, 70, 20, 101);
		    _BotonTerminar.CrearBotonEx(WS_CHILD | WS_VISIBLE, _hWnd, TEXT("Terminar"), 260, 170, 70, 20, 100);
		    _EditPathDump.CrearEdicionEx(WS_CHILD | WS_VISIBLE, _hWnd, PathDump, 10, 140, 470, 20, 102, false);
		    return TRUE;
	    };

        const BOOL DWLVentanaErrorGrave::Mostrar(struct _EXCEPTION_POINTERS* ExceptionInfo) { 
		    if (ExceptionInfo == NULL) { // prueba en debug
				_BotonGuardar.Activado(false);
				_EditPathDump.Activado(false);
			}
			ShowWindow(_hWnd, SW_SHOW);
			_ExceptionInfo = ExceptionInfo;
		    return TRUE;
		}
		
		LRESULT DWLVentanaErrorGrave::Evento_Cerrar(void) {
		    PostQuitMessage(0);
		    return 0;
	    };

        LRESULT DWLVentanaErrorGrave::Evento_Pintar(HDC hDC, PAINTSTRUCT &PS) {
			// Creo la fuente para mostrar el error
		    HFONT FuenteTahoma = CreateFont(13, 0, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_ROMAN, TEXT("Tahoma")); 
		    HFONT FuenteVieja = static_cast<HFONT>(SelectObject(hDC, FuenteTahoma));
			// Pinto el fondo blanco
			HBRUSH BrochaBlanca = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
			RECT RC;
			GetClientRect(_hWnd, &RC);
			FillRect(hDC, &RC, BrochaBlanca);
			// Pinto el texto
			TCHAR Descripcion[] = TEXT("Ha ocurrido un error grave en la aplicación, y esta debe cerrarse.\nSi lo deseas puedes crear un archivo con información detallada sobre el error.\nEste archivo no contiene ningún dato confidencial, y puede ser de gran ayuda para encontrar y\nreparar errores infrecuentes en las aplicaciones.\nNOTA : en windows vista y superiores es recomendable guardar el archivo en la ruta inicial.\nPresiona Guardar para guardar el archivo de log y salir, o Terminar para salir.");
		    RECT Espacio = { 10, 10, 500, 240 };
		    DrawText(hDC, Descripcion, wcslen(Descripcion), &Espacio, DT_LEFT);
			// Elimino objetos de la memoria
		    SelectObject(hDC, FuenteVieja);
		    DeleteObject(FuenteTahoma);
            return 0;
	    };

        LRESULT DWLVentanaErrorGrave::Evento_BotonEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDBotonEx, const UINT Param) {
		    if (Boton == 0 && IDBotonEx == 100)	PostQuitMessage(0);
		    if (Boton == 0 && IDBotonEx == 101) {
			    if (CrearDump(_ExceptionInfo, _EditPathDump.Texto()) == TRUE)	PostQuitMessage(0);
			    else												            MessageBox(_hWnd, TEXT("Error escribiendo el archivo dump"), TEXT("Error"), MB_OK);
		    }
            return 0;
	    };

        
	    const BOOL DWLVentanaErrorGrave::CrearDump(_EXCEPTION_POINTERS *ExceptionInfo, const TCHAR *PathDump) {
		    #if (COMPILADOR == COMPILADOR_VC9 || COMPILADOR == COMPILADOR_VC10)
                if (ExceptionInfo == NULL) return FALSE;
			    HANDLE hFile = CreateFile( PathDump, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 

			    if((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))  {
				    // Create the minidump 

				    MINIDUMP_EXCEPTION_INFORMATION mdei; 

				    mdei.ThreadId           = GetCurrentThreadId(); 
				    mdei.ExceptionPointers  = ExceptionInfo; 
				    mdei.ClientPointers     = FALSE; 

				    MINIDUMP_CALLBACK_INFORMATION mci; 

				    mci.CallbackRoutine     = NULL; //(MINIDUMP_CALLBACK_ROUTINE)MyMiniDumpCallback; 
				    mci.CallbackParam       = 0; 
				    MINIDUMP_TYPE mdt       = MiniDumpNormal; 

//				    MINIDUMP_TYPE mdt       = (MINIDUMP_TYPE)(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory); 

				    BOOL rv = MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(), hFile, mdt, (ExceptionInfo != 0) ? &mdei : 0, 0, &mci ); 

	    //			if (!rv) 	_tprintf( _T("MiniDumpWriteDump failed. Error: %u \n"), GetLastError() ); 
	    //			else 		_tprintf( _T("Minidump created.\n") ); 

				    // Close the file 

				    CloseHandle(hFile); 
				    return TRUE;
			    }
		    #endif
		    return FALSE;
	    }


    };
};
