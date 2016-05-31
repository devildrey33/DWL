#include "stdafx.h"
#include "DProgressBar.h"

namespace DWL {

	DProgressBar::DProgressBar(void) {
		static bool Cargado = false;
		if (Cargado == false) {
			INITCOMMONCONTROLSEX Comm;
			Comm.dwSize = sizeof(INITCOMMONCONTROLSEX);
			Comm.dwICC = ICC_PROGRESS_CLASS;
			InitCommonControlsEx(&Comm);
			Cargado = true;
		}
	}


	HWND DProgressBar::CrearProgressBar(DBaseWnd *nPadre, const UINT nEstilos, const int cX, const int cY, const int cAncho, const int cAlto, const UINT cID, const int nMin, const int nMax, const int nValor) {
		_hWnd = CreateWindowEx(NULL, PROGRESS_CLASS, NULL, nEstilos, cX, cY, cAncho, cAlto, nPadre->hWnd(), reinterpret_cast<HMENU>(IntToPtr(cID)), GetModuleHandle(NULL), this);
		_ConectarControl(cID, nPadre);
		return _hWnd;
	};
	
	// Función para asignar el minimo y el maximo para la progressbar
	void DProgressBar::AsignarRango(const int nMinimo, const int nMaximo) {
		SendMessage(_hWnd, PBM_SETRANGE, 0, MAKELPARAM(nMinimo, nMaximo));
	}

	// Función para asignar el minimo y el maximo para la progressbar
	void DProgressBar::ObtenerRango(int &nMinimo, int &nMaximo) {
		PBRANGE Rango;
		SendMessage(_hWnd, PBM_GETRANGE, 0, reinterpret_cast<LPARAM>(&Rango));
		nMinimo = Rango.iLow;
		nMaximo = Rango.iHigh;
	}

	// -Función para obtener el minimo de la progressbar
	const int DProgressBar::Minimo(void) {
		return static_cast<int>(SendMessage(_hWnd, PBM_GETRANGE, FALSE, NULL));
	}

	// -Función para obtener el maximo de la progressbar
	const int DProgressBar::Maximo(void) {
		return static_cast<int>(SendMessage(_hWnd, PBM_GETRANGE, TRUE, NULL));
	}

	// -Función para obtener el maximo de la progressbar
	const UINT DProgressBar::Valor(void) {
		return static_cast<int>(SendMessage(_hWnd, PBM_GETPOS, TRUE, NULL));
	}

	// -Función para asignar el maximo de la progressbar
	void DProgressBar::Valor(const int nValor) {
		SendMessage(_hWnd, PBM_SETPOS, static_cast<WPARAM>(nValor), NULL);
	}
};