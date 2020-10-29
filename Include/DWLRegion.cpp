#include "DWLBrocha.h"
//#include "DWLRecta.h"
#include "DWLhDC.h"
#include "DWLRegion.h"
#include "DWLArchivoBinario.h"
#include <stdio.h>

namespace DWL {
	namespace GDI {
		
		// Función para pintar la region
		void DWLRegion::PintarRegion(DWLhDC *hDC, DWLBrocha *Brocha) {
			FillRgn(hDC->hDC(), _Region, Brocha->Brocha()); 
		}; 


		      
		// Función para enmarcar la region
		void DWLRegion::EnmarcarRegion(DWLhDC *hDC, DWLBrocha *Brocha, const int TamAncho, const int TamAlto) { 
			FrameRgn(hDC->hDC(), _Region, Brocha->Brocha(), TamAncho, TamAlto); 
		};
		   

		// Operador de comparacion
		BOOL DWLRegion::operator == (DWLRegion *Comp) { 
			return EqualRgn(_Region, Comp->Region()); 
		}


		// Función para guardar una region externa
		void DWLRegion::AbrirRegionDisco(const TCHAR *SHPPath) {
			HRGN     temp;
			//FILE    *Archiu;
			RECT     lpRect;
			if (_Region != NULL) {
				DeleteObject(_Region);
			}
			_Region = CreateRectRgn(0 ,0 ,0 ,0);
			
			/*DWLFOpen(Archiu, SHPPath, TEXT("rb"));
			if (Archiu != NULL) {
				while (feof(Archiu) == 0) {
					fread(&lpRect, sizeof(RECT), 1, Archiu);
					temp = CreateRectRgnIndirect(&lpRect);
					CombineRgn(_Region, _Region, temp, RGN_OR);
					DeleteObject(temp);
				}
				fclose(Archiu);
			} 
			else {
				DeleteObject(_Region);
				_Region = NULL;
			}*/

			DWL::Archivos::DWLArchivoBinario Archivo2;
			Archivo2.AbrirArchivo(SHPPath, false);
			DWORD TotalRectas = 0;
			if (Archivo2.EstaAbierto() == TRUE) {
				Archivo2.LeerDword(TotalRectas);
				for (DWORD i = TotalRectas; i > -1; i--) {
					Archivo2.Leer(&lpRect, sizeof(RECT));
					temp = CreateRectRgnIndirect(&lpRect);
					CombineRgn(_Region, _Region, temp, RGN_OR);
					DeleteObject(temp);
				}
			}
			else {
				DeleteObject(_Region);
				_Region = NULL;
			}
		}

		 
		// Función para crear una region a partir de un BMP 
		void DWLRegion::CrearRegionBmp(const TCHAR *BMPPath) {	
			if (_Region != NULL) {
				DeleteObject(_Region);
			}
			HDC      hDC = GetDC(NULL);
			HDC      bmapDC;
			BITMAP   btmap;
			HBITMAP  iface;
			HBITMAP  Viejo;
			HRGN     temp;
			int      x;
			int      y;
			int      startx = 0;
			COLORREF trans;
			COLORREF tst;
			int      SavedDC = 0;
			iface = (HBITMAP)LoadImage(NULL, BMPPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			bmapDC = CreateCompatibleDC(hDC);
			GetObject(iface, sizeof(btmap), &btmap);
			SavedDC = SaveDC(bmapDC);
			Viejo = (HBITMAP) SelectObject(bmapDC, iface);
			ReleaseDC(0, hDC);
			trans = GetPixel(bmapDC, 0, 0);
			_Region = CreateRectRgn(0, 0, 0, 0);
			temp = CreateRectRgn(0,0,0,0);
			for (y = 0; y <= btmap.bmHeight - 1; y++) {
				for (x = 0; x <= btmap.bmWidth - 1; x++) {
					tst = GetPixel(bmapDC, x, y);
					if (tst != trans) {
						startx = x;
						while ((x <= btmap.bmWidth) && ((GetPixel(bmapDC, x, y)) != trans)) {
							 x++;
						}
						temp = CreateRectRgn(startx ,y ,x ,y + 1);
						CombineRgn(_Region ,_Region, temp, RGN_OR);
						DeleteObject(temp);
					}
				}
			}
			DeleteObject(temp);
			SelectObject(bmapDC, Viejo);
			DeleteObject(iface);
			DeleteDC(bmapDC);
		}		 

		 
		// Función para guardar la Region en un Archivo 
		void DWLRegion::GuardarRegionDisco(const TCHAR *Dest) {
//			LPRECT    lpRect = NULL;
			DWORD     BufSize = GetRegionData(_Region, 0, NULL);
			LPRGNDATA lpData = (LPRGNDATA)malloc(BufSize);
//			lpRect = (LPRECT)(lpData->Buffer);
			if(!GetRegionData(_Region, BufSize, lpData)) {
				free(lpData);
				return;
			}	
/*			if((DWLFOpen(Archivo, Dest, TEXT("w+b"))) == 0) {
				fwrite(&lpData->Buffer, sizeof(RECT), lpData->rdh.nCount, Archivo);
				fclose(Archivo);
			}*/
			if (lpData) {
				DWL::Archivos::DWLArchivoBinario Archivo2;
				Archivo2.AbrirArchivo(Dest, true);
				Archivo2.GuardarDword(lpData->rdh.nCount);
				Archivo2.Guardar(&lpData->Buffer, sizeof(RECT) * lpData->rdh.nCount);
				Archivo2.CerrarArchivo();
				free((void*)lpData);
			}

		}

	};
};
