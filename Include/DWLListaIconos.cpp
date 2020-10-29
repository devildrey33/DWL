#include "DWLListaIconos.h"
#include <shlobj.h>

namespace DWL {
	namespace SO {
		std::vector<DWLListaIconos_Icono *>  DWLListaIconos::_Iconos;
        int                                  DWLListaIconos::_IDActual = -1;

		DWLListaIconos::DWLListaIconos(void) {
		}

		DWLListaIconos::~DWLListaIconos(void) {
			Borrar();
		}

		void DWLListaIconos::Borrar(void) {
			for (size_t i = 0; i < _Iconos.size(); i++) {
				if (_Iconos[i]->_Icono != NULL) DestroyIcon(_Iconos[i]->_Icono);
				delete _Iconos[i];
			}
			_Iconos.resize(0);
		}

		DWLListaIconos_Icono *DWLListaIconos::BuscarIcono(const int bID, const int bAncho, const int bAlto) {
			//DWLListaIconos_Icono *Ico = NULL;
			for (size_t i = 0; i < _Iconos.size(); i++) {
//				Ico = _Iconos[i];
				if (_Iconos[i]->_ID == bID && _Iconos[i]->_Alto == bAlto && _Iconos[i]->_Ancho == bAncho) return _Iconos[i];
			}
			HICON Ico = static_cast<HICON>(LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(bID), IMAGE_ICON, bAncho, bAlto, LR_DEFAULTCOLOR));
			DWLListaIconos_Icono *nIcono = new DWLListaIconos_Icono(Ico, bID, bAncho, bAlto);
			_Iconos.push_back(nIcono);
			return nIcono;
		}

		void DWLListaIconos::PintarIcono(HDC hDC, const int cX, const int cY, const int cAnchoIco, const int cAltoIco, const int IDIco) {
			if (IDIco == 0) return;
			DWLListaIconos_Icono *Icono = BuscarIcono(IDIco, cAnchoIco, cAltoIco);
/*			if (Icono == 0) {
				HICON Ico = static_cast<HICON>(LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDIco), IMAGE_ICON, cAnchoIco, cAltoIco, LR_DEFAULTCOLOR));
				Icono = new DWLListaIconos_Icono(Ico, IDIco, cAnchoIco, cAltoIco);
				_Iconos.push_back(Icono);
			}*/
			DrawIconEx(hDC, cX, cY, Icono->_Icono, cAnchoIco, cAltoIco, 0, 0, DI_NORMAL);
		}

		void DWLListaIconos::PintarIconoResaltado(HDC hDC, const int cX, const int cY, const int cAnchoIco, const int cAltoIco, const int IDIco, COLORREF ColorResaltado) {
			if (IDIco == 0) return;
			DWLListaIconos_Icono *Icono = BuscarIcono(IDIco, cAnchoIco, cAltoIco);
/*			if (Icono == 0) {
				HICON Ico = static_cast<HICON>(LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDIco), IMAGE_ICON, cAnchoIco, cAltoIco, LR_DEFAULTCOLOR));
				Icono = new DWLListaIconos_Icono(Ico, IDIco, cAnchoIco, cAltoIco);
				_Iconos.push_back(Icono);
			}*/

			HDC Buffer = CreateCompatibleDC(hDC);
			HBITMAP Bmp = CreateCompatibleBitmap(Buffer, cAnchoIco + 4, cAltoIco + 4);
			HBITMAP VBmp = static_cast<HBITMAP>(SelectObject(Buffer, Bmp));
			RECT RC = { 0, 0, cAnchoIco + 4, cAltoIco + 4 };
			
			FillRect(Buffer, &RC, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));
			DrawIconEx(Buffer, cX - 2, cY - 2, Icono->_Icono, cAnchoIco + 4, cAltoIco + 4, 0, 0, DI_MASK);
			BitBlt(hDC, cX - 2, cY - 2, cAnchoIco + 4, cAltoIco + 4, Buffer, 0, 0, SRCAND);
			
//			HBRUSH Brocha = CreateSolidBrush(ColorResaltado);
			BitBlt(Buffer, cX - 2, cY - 2, cAnchoIco + 4, cAltoIco + 4, Buffer, 0, 0, DSTINVERT);
//			FillRect(Buffer, &RC, Brocha);
//			BitBlt(hDC, cX - 1, cY - 1, cAnchoIco + 2, cAltoIco + 2, Buffer, 0, 0, SRCPAINT);
			// Pinto el icono final
			BitBlt(hDC, cX - 2, cY - 2, cAnchoIco + 4, cAltoIco + 4, Buffer, 0, 0, SRCPAINT);
			DrawIconEx(hDC, 1, 1, Icono->_Icono, cAnchoIco, cAltoIco, 0, 0, DI_NORMAL);

//			DeleteObject(Brocha);
			SelectObject(Buffer, VBmp);
			DeleteObject(Bmp);
			DeleteDC(Buffer);
		}

		DWLListaIconos_Icono *DWLListaIconos::AgregarIconoExterno(HICON nIcono, const int IDNegativa, const int cAnchoIco, const int cAltoIco, const TCHAR *nIDStr, const int nStrPosicion) {
			if (nIcono == 0) return 0;
			DWLListaIconos_Icono *Icono = new DWLListaIconos_Icono(nIcono, IDNegativa, cAnchoIco, cAltoIco, nIDStr, nStrPosicion);
			_Iconos.push_back(Icono);
			return Icono;
		}

		DWLListaIconos_Icono *DWLListaIconos::BuscarIDStr(const TCHAR *nIDStr, const int nPosicionStr) {
			for (size_t i = 0; i < _Iconos.size(); i++) {
//				Ico = _Iconos[i];
				if (_Iconos[i]->_IDStr.Tam() > 0) {
					if (DWLStrCmpi(_Iconos[i]->_IDStr(), nIDStr) == 0 && _Iconos[i]->_PosicionStr == nPosicionStr)
						return _Iconos[i];
				}
			}
			return 0;
		}

		//! Función que carga un icono de un ejecutable.
	    /*! Esta funcion carga un icono de un ejecutable.
			    \fn			int CargarIcono(const TCHAR *Path);
			    \param[in]	Path : HWND de la ventana que recibira el foco despues de esta.
	            \return		Devuelve el indice del icono en la lista de iconos.
	    */
		int DWLListaIconos::CargarIcono(const TCHAR *Path) {
			HRESULT hr;
			LPITEMIDLIST pidl = 0;
            #if defined UNICODE
			SHFILEINFOW sfi = {0};
			#else
			SHFILEINFOA sfi = {0};
			#endif
			hr = SHGetFileInfo(Path, 0, &sfi, sizeof(sfi), SHGFI_ICONLOCATION);
			DWLString Nombre;
			Nombre = sfi.szDisplayName;
			int		  PosIco = sfi.iIcon;
			DWLListaIconos_Icono *TmpIco = BuscarIDStr(Nombre(), PosIco);
			// No existe, lo creamos
			if (TmpIco == 0) {
				hr = SHGetFileInfo(Path, 0, &sfi, sizeof(sfi), SHGFI_ICON);
				if (SUCCEEDED(hr)) TmpIco = AgregarIconoExterno(sfi.hIcon, _IDActual, 16, 16, Nombre(), PosIco);
				_IDActual --;
			}
			if (TmpIco == 0) return 0;
			return TmpIco->ID();
		}


		//! Función que carga un icono de un CSIDL.
		/*! Esta funcion carga un icono de un CSIDL.
				\fn			int CargarIcono(const int CSIDL);
				\param[in]	CSIDL : ID del icono correspondiente.
		        \return		Devuelve el indice del icono en la lista de iconos.
		*/
		int DWLListaIconos::CargarIcono(const int CSIDL) {
			HRESULT hr;
			LPITEMIDLIST pidl = 0;
			#if defined UNICODE
			    SHFILEINFOW sfi = {0};
			#else
			    SHFILEINFOA sfi = {0};
			#endif
			hr = SHGetSpecialFolderLocation(0, CSIDL, &pidl);

			hr = SHGetFileInfo((LPCTSTR)pidl, -1, &sfi, sizeof(sfi), SHGFI_PIDL | SHGFI_ICONLOCATION);
			DWLString Nombre;
			Nombre = sfi.szDisplayName;
			int		  PosIco = sfi.iIcon;
		    DWLListaIconos_Icono *TmpIco = BuscarIDStr(Nombre(), PosIco);
			// No existe, lo creamos
			if (TmpIco == 0) {
				hr = SHGetFileInfo((LPCTSTR)pidl, -1, &sfi, sizeof(sfi), SHGFI_PIDL | SHGFI_ICON);
				if (SUCCEEDED(hr))	TmpIco = AgregarIconoExterno(sfi.hIcon, _IDActual, 16, 16, Nombre(), PosIco);
				else				return 0; // No se ha podido crear el icono, lo dejamos a 0
				_IDActual --;
			}
			return TmpIco->ID();
		}
    };
}; 
