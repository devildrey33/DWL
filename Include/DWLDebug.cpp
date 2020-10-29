/*! \file DWLDebug.cpp
	\brief		Archivo que contiene funciones utiles para la depuración.
	\author		devildrey33
	\date		Creado el [01/02/2004], ultima modificación el [05/10/2010]
*/
#include "DWLDebug.h"
#include <stdio.h>
#include <crtdbg.h>

namespace DWL {

	//! Función que imprime texto por la pantallita de debug
    /*! Función que imprime texto por la pantallita de debug, al estilo del printf
		    \fn			static void	ImprimirDebug(const TCHAR *Txt, ...);
			\param[in]	Txt		: Puntero a una cadena de texto
			\param[in]	...		: Parametros opcionales
            \return     No devuelve nada
    */
	void DWLDebug::ImprimirDebug(const TCHAR *Txt, ...) {
		TCHAR       T[1024];
		va_list     Marker;
		va_start(Marker, Txt);     
		DWLvsPrintf(T, 1024, Txt, Marker);
		va_end(Marker);
		OutputDebugString(T);
	};


	//! Función que imprime texto por la pantallita de debug, calculando el tiempo.
    /*! Función que imprime texto por la pantallita de debug, al estilo del printf. Ademas esta función calcula el tiempo que ha transcurrido desde la ultima vez que se llamo a esta función. 
		    \fn			static void	ImprimirDebugMS(const TCHAR *Txt, ...);
			\param[in]	Txt		: Puntero a una cadena de texto
			\param[in]	...		: Parametros opcionales
            \return     No devuelve nada
    */
	void DWLDebug::ImprimirDebugMS(const TCHAR *Txt, ...) {
		static DWORD      _IDMSDWORD = 0;
		TCHAR       T[1024];
		DWORD       Time = GetTickCount();
		TCHAR       T2[1024];
		va_list     Marker;
		va_start(Marker, Txt);     
		#if defined UNICODE
			#if COMPILADOR == COMPILADOR_VC9 || COMPILADOR == COMPILADOR_VC10
				vswprintf_s(T, 1024, Txt, Marker);
				wsprintf(T2, TEXT("[%.08d] %s"), Time - _IDMSDWORD, T);
			#else // VC6 - devc++
				vswprintf(T, Txt, Marker);
				wsprintf(T2, TEXT("[%.08d] %s"), Time - _IDMSDWORD, T);
			#endif
		#else
			#if COMPILADOR == COMPILADOR_VC9 || COMPILADOR == COMPILADOR_VC10
				vsprintf_s(T, 1024, Txt, Marker);
				sprintf_s(T2, 1024, TEXT("[%.08d] %s"), Time - _IDMSDWORD, T);
			#else					// VC7 o mas
				vsprintf(T, Txt, Marker);
				sprintf(T2, TEXT("[%.08d] %s"), Time - _IDMSDWORD, T);
			#endif

		#endif
		_IDMSDWORD = Time;
		va_end(Marker);
		OutputDebugString(T2);
	};
 
	//! Función que muestra un MessageBox con el ultimo error del sistema.
    /*! Función que muestra un MessageBox con el ultimo error del sistema. Ademas puedes añadir texto delante del mensaje del sistema. 
		    \fn			static void	MostrarUltimoError(const TCHAR *Mensaje = NULL);
			\param[in]	Mensaje	: Puntero a una cadena de texto con texto extra para el mensaje. Puede ser NULL.
            \return     No devuelve nada
    */
	void DWLDebug::MostrarUltimoError(const TCHAR *Mensaje){
		DWORD  ErrNum = GetLastError();
		LPVOID lpMsgBuf;
		int    RetMsg = IDNO;
		if (ErrNum == 0) return;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, ErrNum, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);
		if (Mensaje == NULL) {
			RetMsg = MessageBox(NULL, (LPCTSTR)lpMsgBuf, TEXT("Error"), MB_OK | MB_ICONINFORMATION | MB_YESNO);
			if (RetMsg == IDYES) _ASSERT(0);
		}
		else {
			TCHAR Buffer[2048];
			#if defined UNICODE
				wsprintf(Buffer, TEXT("%s\n%s"), Mensaje, (LPCTSTR)lpMsgBuf);
				RetMsg = MessageBox(NULL, Buffer, TEXT("Error"), MB_OK | MB_ICONINFORMATION | MB_YESNO);
				if (RetMsg == IDYES) _ASSERT(0);
			#else
      			#if COMPILADOR == COMPILADOR_VC6 || COMPILADOR == COMPILADOR_MINGW	// VC6 - mingw
					sprintf(Buffer, TEXT("%s\n%s"), Mensaje, (LPCTSTR)lpMsgBuf);
				#else	
					sprintf_s(Buffer, 2048, TEXT("%s\n%s"), Mensaje, (LPCTSTR)lpMsgBuf);
				#endif
				RetMsg = MessageBox(NULL, Buffer, TEXT("Error"), MB_OK | MB_ICONINFORMATION | MB_YESNO);								
				if (RetMsg == IDYES) _ASSERT(0);
			#endif
		}
		LocalFree(lpMsgBuf);
	};


};
