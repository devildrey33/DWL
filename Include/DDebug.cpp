#include "stdafx.h"
#include "DDebug.h"
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
	void DDebug::ImprimirDebug(const TCHAR *Txt, ...) {
		static TCHAR T[2048];
		va_list      Marker;
		va_start(Marker, Txt);
		vswprintf_s(T, 1024, Txt, Marker);
		va_end(Marker);
		OutputDebugString(T);
	};

	//! Función que muestra un MessageBox con el ultimo error del sistema.
	/*! Función que muestra un MessageBox con el ultimo error del sistema. Ademas puedes añadir texto delante del mensaje del sistema.
	\fn			static void	MostrarUltimoError(const TCHAR *Mensaje = NULL);
	\param[in]	Mensaje	: Puntero a una cadena de texto con texto extra para el mensaje. Puede ser NULL.
	\return     No devuelve nada
	*/
	void DDebug::MostrarUltimoError(const TCHAR *Mensaje, ...){
		DWORD  ErrNum = GetLastError();
		LPVOID lpMsgBuf;
		int    RetMsg = IDNO;
		if (ErrNum == 0) return;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, ErrNum, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
		if (Mensaje == NULL) {
			RetMsg = MessageBox(NULL, (LPCTSTR)lpMsgBuf, TEXT("Error"), MB_OK | MB_ICONINFORMATION | MB_APPLMODAL);
			if (RetMsg == IDYES) _ASSERT(0);
		}
		else {
			TCHAR T[2048];
			TCHAR Buffer[4096];
#if defined UNICODE
			va_list      Marker;
			va_start(Marker, Mensaje);
			vswprintf_s(T, 2048, Mensaje, Marker);
			va_end(Marker);
			wsprintf(Buffer, TEXT("%s\n%s\n%s"), T, Mensaje, (LPCTSTR)lpMsgBuf);
			RetMsg = MessageBox(NULL, Buffer, TEXT("Error"), MB_OK | MB_ICONINFORMATION | MB_APPLMODAL);
			if (RetMsg == IDYES) _ASSERT(0);
#else
			/*      			#if COMPILADOR == COMPILADOR_VC6 || COMPILADOR == COMPILADOR_MINGW	// VC6 - mingw
			sprintf(Buffer, TEXT("%s\n%s"), Mensaje, (LPCTSTR)lpMsgBuf);
			#else	*/
			sprintf_s(Buffer, 2048, TEXT("%s\n%s"), Mensaje, (LPCTSTR)lpMsgBuf);
			//				#endif
			RetMsg = MessageBox(NULL, Buffer, TEXT("Error"), MB_OK | MB_ICONINFORMATION | MB_YESNO);
			if (RetMsg == IDYES) _ASSERT(0);
#endif
		}
		LocalFree(lpMsgBuf);
	};

};