#include "stdafx.h"
#include "DAplicacion.h"
#include <CommCtrl.h>

#pragma comment(lib, "Comctl32.lib")		// Libreria para InitCommonControlEx


namespace DWL {

	DAplicacion *_APLICACION = NULL;


	DAplicacion::DAplicacion(void) : _Terminar(false) {
	}

	DAplicacion::~DAplicacion(void) {
	}


	void DAplicacion::ObtenerPathApp(std::wstring &AppPath) {
		TCHAR PathApp[MAX_PATH + 1];
		DWORD Tam = GetModuleFileName(NULL, PathApp, MAX_PATH + 1);
		for (Tam; Tam > 0; Tam--) {
			if (PathApp[Tam] == TCHAR('\\')) break;
		}
		PathApp[Tam + 1] = 0;
		AppPath = PathApp;
	}

	const int DAplicacion::Ejecutar(void) {
		/*		INITCOMMONCONTROLSEX Comm;
		Comm.dwSize = sizeof(INITCOMMONCONTROLSEX);
		Comm.dwICC = ICC_STANDARD_CLASSES;
		InitCommonControlsEx(&Comm);*/

		_APLICACION->Evento_Empezar();

		_APLICACION->Evento_BuclePrincipal();

		int Ret = _APLICACION->Evento_Terminar();
		return Ret;
	}

	const int DAplicacion::EsperarEvento(void) {
		static MSG Msg;
		if (GetMessage(&Msg, NULL, 0, 0) == 0)
			_Terminar = true; // Se ha hecho un PostQuitMessage
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
		return static_cast<int>(Msg.wParam);
	}

	void DAplicacion::MirarEvento(void) {
		static MSG Msg;
		PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE);
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

};