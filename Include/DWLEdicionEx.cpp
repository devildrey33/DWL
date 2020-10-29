#include "DWLEdicionEx.h"

namespace DWL {
	namespace ControlesEx {
		
		#define DWL_NOMBRE_CLASE_DWLEdicionEx  TEXT("DWL::ControlesEx::DWLEdicionEx")

        DWLEdicionEx::DWLEdicionEx(void) : DWLControlEx(), DWLEdicionEx_Nucleo() {
            RegistrarClase(DWL_NOMBRE_CLASE_DWLEdicionEx, NULL, NULL, _GestorMensajes);
        }


		DWLEdicionEx::~DWLEdicionEx(void) {
            Destruir();
		} 

		HWND DWLEdicionEx::CrearEdicionEx(const long Estilos, HWND hWndParent, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const bool nPintarBorde, const bool cMultiLinea) {
            CrearControl(hWndParent, DWL_NOMBRE_CLASE_DWLEdicionEx, Estilos, TEXT(""), cX, cY, cAncho, cAlto, cID);
            EdicionEx_Estilos.MultiLinea = cMultiLinea;
            EdicionEx_Estilos.PintarBorde = nPintarBorde;
            if (EdicionEx_Estilos.PintarBorde == true) {
			    HRGN Rgn = CreateRoundRectRgn(0, 0, cAncho + 1, cAlto + 1, 2, 2);
			    SetWindowRgn(_hWnd, Rgn, false);
            }
			RECT RC = { 0, 0, cAncho, cAlto };
            BarraScrollEx_CrearH(DWL_BARRASCROLLEX_AUTOMATICO, 0, 0, 0);
            BarraScrollEx_CrearV(DWL_BARRASCROLLEX_AUTOMATICO, 0, 0, 0);
			BarraScrollEx_PosicionarScrolls(_hWnd, &RC, false, EdicionEx_Estilos.PintarBorde);
            Texto(nTexto);
			SetFocus(_hWnd);
			CrearTemporizador(DWL_EDICIONEX_TEMPORIZADOR_CURSOR, 500);
			return _hWnd;
		}

        HWND DWLEdicionEx::ConectarEdicionEx(HWND hWndParent, const TCHAR *nTexto, const int cID, const bool nPintarBorde, const bool cMultiLinea) {
            _ConectarControl(cID, hWndParent);
            RECT RC;
            GetClientRect(_hWnd, &RC);
            EdicionEx_Estilos.MultiLinea = cMultiLinea;
            EdicionEx_Estilos.PintarBorde = nPintarBorde;
            if (EdicionEx_Estilos.PintarBorde == true) {
			    HRGN Rgn = CreateRoundRectRgn(0, 0, RC.right + 1, RC.bottom + 1, 2, 2);
			    SetWindowRgn(_hWnd, Rgn, false);
            }
            BarraScrollEx_CrearH(DWL_BARRASCROLLEX_AUTOMATICO, 0, 0, 0);
            BarraScrollEx_CrearV(DWL_BARRASCROLLEX_AUTOMATICO, 0, 0, 0);
			BarraScrollEx_PosicionarScrolls(_hWnd, &RC, false, EdicionEx_Estilos.PintarBorde);
            EdicionEx_AgregarTexto(_hWnd, nTexto);
			SetFocus(_hWnd);
			CrearTemporizador(DWL_EDICIONEX_TEMPORIZADOR_CURSOR, 500);
			return _hWnd;
        }

        void DWLEdicionEx::Texto(const TCHAR *nTexto) {
            EdicionEx_AgregarTexto(_hWnd, nTexto);
            Repintar();
        }

		const TCHAR *DWLEdicionEx::Texto(void) {
			return EdicionEx_ObtenerTexto();
		}

		void DWLEdicionEx::Repintar(const bool Forzar) {
			HDC hDC = GetDC(_hWnd);
			RECT RC;
			GetClientRect(_hWnd, &RC);
			EdicionEx_Pintar(hDC, &RC, Foco(), false);
			ReleaseDC(_hWnd, hDC);
		}



		LRESULT DWLEdicionEx::Evento_Pintar(HDC hDC, PAINTSTRUCT &PS) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			EdicionEx_Pintar(hDC, &RC, Foco(), false);
            return 0;
		}

		LRESULT DWLEdicionEx::Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Param) {
			EdicionEx_Teclado_TeclaSoltada(_hWnd, Caracter, Repeticion, Param);
			Repintar();
            return 0;
		}


		LRESULT DWLEdicionEx::Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Param) {
			EdicionEx_Teclado_TeclaPresionada(_hWnd, Caracter, Repeticion, Param);
			Repintar();
            return 0;
		}


		LRESULT DWLEdicionEx::Evento_Teclado_Caracter(const UINT Caracter, const UINT Repeticion, const UINT Param) {
			EdicionEx_Teclado_Caracter(_hWnd, Caracter, Repeticion, Param);
			Repintar();
            return 0;
		}

        LRESULT DWLEdicionEx::Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			EdicionEx_Mouse_BotonPresionado(_hWnd, &RC, Boton, cX, cY, Param);
            SetFocus(_hWnd);
            return 0;
        }

        LRESULT DWLEdicionEx::Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			EdicionEx_Mouse_BotonSoltado(_hWnd, &RC, Boton, cX, cY, Param);
			Repintar();
            return 0;
        };

		LRESULT DWLEdicionEx::Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param) {
   			RECT RC;
			GetClientRect(_hWnd, &RC);
			EdicionEx_Mouse_Movimiento(_hWnd, &RC, cX, cY, Param);
			Repintar();
            return 0;
        };

		LRESULT DWLEdicionEx::Evento_Mouse_Saliendo(void) {
			BarraScrollEx_Mouse_Saliendo(_hWnd);
			Repintar();
			return DWLControlEx::Evento_Mouse_Saliendo();
		}

		LRESULT DWLEdicionEx::Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey) {
			EdicionEx_Mouse_Rueda(Delta, cX, cY, VirtKey);
			return 0;
		}

		LRESULT DWLEdicionEx::Evento_Temporizador(const UINT cID) {
			if (cID == DWL_EDICIONEX_TEMPORIZADOR_CURSOR) {
				_EdicionEx_CursorVisible = !_EdicionEx_CursorVisible;
				Repintar();
			}
			BarraScrollEx_Evento_Temporizador(_hWnd, cID, EdicionEx_Estilos.PintarBorde);
			return 0;
		}

		LRESULT DWLEdicionEx::Evento_Foco_Obtenido(HWND FocoAnterior) {
			CrearTemporizador(DWL_EDICIONEX_TEMPORIZADOR_CURSOR, 500);
			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("DWLEdicionEx::Evento_Foco_Obtenido\n")));
			_EdicionEx_CursorVisible = true;
            return 0;
		}


		LRESULT DWLEdicionEx::Evento_Foco_Perdido(HWND NuevoFoco) {
			EliminarTemporizador(DWL_EDICIONEX_TEMPORIZADOR_CURSOR);
			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("DWLEdicionEx::Evento_Foco_Perdido\n")));
			_EdicionEx_CursorVisible = false;
			_EdicionEx_TeclaControlPresionada = false;
			_EdicionEx_TeclaShiftPresionada = false;
			Repintar();
            return 0;
		}

		void DWLEdicionEx::Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar) {
			DWLControlEx::Mover(cX, cY, cAncho, cAlto, false);
			_EdicionEx_CalcularScrolls(_hWnd, 0, 0, false);
			if (cRepintar == true) Repintar(true);
		}
    };
};
