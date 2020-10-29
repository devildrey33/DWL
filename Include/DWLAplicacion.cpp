#include "DWLAplicacion.h"
#include "DWLString.h"
 
namespace DWL {

	DWLAplicacion::DWLAplicacion(void) {
	}

	DWLAplicacion::~DWLAplicacion(void) {
	}

	void DWLAplicacion::Directorio(DWLString &Str) {
		TCHAR Buffer[MAX_PATH + 1];
		ZeroMemory(Buffer, sizeof(TCHAR) * (MAX_PATH + 1));
		GetModuleFileName(NULL, Buffer, MAX_PATH);
		for (size_t i = MAX_PATH; i > 0; i--) {
			if (Buffer[i - 1] == TEXT('\\')) {
				Buffer[i] = TEXT('\0');
				break;
			}
		}
		Str = Buffer;
	};

	void DWLAplicacion::Ejecutable(DWLString &Str) {
		TCHAR Buffer[MAX_PATH];
		GetModuleFileName(NULL, Buffer, MAX_PATH);
		Str = Buffer;
	};


	int DWLAplicacion::BucleMensajes(void) {
		MSG Msg;
		while (GetMessage(&Msg, NULL, 0, 0) > 0) {
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		return static_cast<int>(Msg.wParam);
	};

};
