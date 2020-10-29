#ifndef DWL_EDICIONEX_NUCLEO_CPP
#define DWL_EDICIONEX_NUCLEO_CPP

#include "DWLEdicionEx_Nucleo.h"
 
namespace DWL {
	namespace ControlesEx {

        DWLEdicionEx_Nucleo::DWLEdicionEx_Nucleo(void) {
			EdicionEx_Estilos.Fuente.Enlazar(DWL::SO::DWLEstilos::Fuentes.Tahoma13);
			_EdicionEx_CursorX = 0;
			_EdicionEx_TeclaShiftPresionada = false;
			_EdicionEx_TeclaControlPresionada = false;
			_EdicionEx_UltimoObjetoMouse = -1;
			_EdicionEx_Activado = true;
			_EdicionEx_MaximoAltoLinea = 0;
			_EdicionEx_MaximoAnchoLinea = 0;
        }

        DWLEdicionEx_Nucleo::~DWLEdicionEx_Nucleo(void) {
            EdicionEx_BorrarTexto();
        }


		const long DWLEdicionEx_Nucleo::_EdicionEx_ObtenerObjetoCoordenadas(HWND hWndControl, const int cX, const int cY) {
			long XAbsoluta = _BarraScrollEx_ValorH + cX;
			long YAbsoluta = _BarraScrollEx_ValorV + cY;
			long XActual = 0;
			long YActual = 0;
			long PosObjeto;
			long XLinea = 0;
			_EdicionEx_CursorX = 0;
			SIZE nTam = { 0, 0 };

			HDC hDC = GetDC(hWndControl);
			HFONT VFont = static_cast<HFONT>(SelectObject(hDC, EdicionEx_Estilos.Fuente()));

			DWLEdicionEx_ObjetoSaltoLinea *nSalto = NULL;
			SIZE TamTexto;
			DWLString TmpStr;
			for (PosObjeto = 0; PosObjeto < static_cast<long>(_EdicionEx_Objetos.size() -1); PosObjeto++) {
				switch (_EdicionEx_Objetos[PosObjeto]->Tipo()) {
					case DWL_Enum_EdicionEx_TipoObjeto_Fuente :
						SelectObject(hDC, _EdicionEx_Objetos[PosObjeto]->Fuente()->Fuente);
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_INICIO :
					case DWL_Enum_EdicionEx_TipoObjeto_FINAL :
					case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
						XLinea = 0;
						if (YActual < YAbsoluta) { 
							nSalto = _EdicionEx_Objetos[PosObjeto]->SaltoLinea();
							YActual +=  nSalto->TamY;
						}
						else {
							if (PosObjeto == 0) return 1;
							if (PosObjeto > static_cast<long>(_EdicionEx_Objetos.size() -2)) return static_cast<long>(_EdicionEx_Objetos.size() -2);
							SelectObject(hDC, VFont);
							ReleaseDC(hWndControl, hDC);
							return PosObjeto;
						}
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_Caracter :
						if (YActual >= YAbsoluta) { 
							TmpStr = _EdicionEx_Objetos[PosObjeto]->Caracter();
							GetTextExtentPoint32(hDC, TmpStr(), TmpStr.Tam(), &TamTexto);
							XLinea += TamTexto.cx;
							XActual = PosObjeto;
							if (XLinea > XAbsoluta) {
								SelectObject(hDC, VFont);
								ReleaseDC(hWndControl, hDC);
								if (PosObjeto > static_cast<long>(_EdicionEx_Objetos.size()) -1)	return _EdicionEx_Objetos.size() -2;
								else																return PosObjeto;
							}
						}
						break;
				}
			}

			SelectObject(hDC, VFont);
			ReleaseDC(hWndControl, hDC);
			return _EdicionEx_Objetos.size() -2;
		}


		void DWLEdicionEx_Nucleo::_EdicionEx_HacerVisibleCursor(HWND hWndControl) {
			// 1 calculamos la X y Y absolutas en pixeles de la posicion del cursor
			long XAbsoluta = 0;
			long YAbsoluta = 0;
			bool Salir = false;
			DWLString TmpStr;
			DWLEdicionEx_ObjetoSaltoLinea *nSaltoLinea = _EdicionEx_Objetos[0]->SaltoLinea();
			DWLEdicionEx_ObjetoFuente     *nFuente = NULL;
			HDC hDC = GetDC(hWndControl);
			HFONT VFont = static_cast<HFONT>(SelectObject(hDC, EdicionEx_Estilos.Fuente()));
			SIZE nTam = { 0, 0 };
			for (size_t i = 1; i < _EdicionEx_Objetos.size(); i++) {
				switch (_EdicionEx_Objetos[i]->Tipo()) {
					case DWL_Enum_EdicionEx_TipoObjeto_Fuente :
						SelectObject(hDC, _EdicionEx_Objetos[i]->Fuente()->Fuente);
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
						YAbsoluta +=  nSaltoLinea->TamY;
						XAbsoluta = 0;
						nSaltoLinea = _EdicionEx_Objetos[i]->SaltoLinea();
						TmpStr.Borrar();
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_Cursor :
						Salir = true;
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_Caracter :
						TmpStr = _EdicionEx_Objetos[i]->Caracter();
						GetTextExtentPoint32(hDC, TmpStr(), TmpStr.Tam(), &nTam);
						XAbsoluta += nTam.cx;
						break;
				}
				if (Salir == true) break;
			}
			if (EdicionEx_Estilos.PintarBorde == true && XAbsoluta != 0) XAbsoluta += 3;

			SelectObject(hDC, VFont);
			ReleaseDC(hWndControl, hDC);

			// 2 Miramos si hay que cambiar los valores del scroll V
			if (YAbsoluta - _BarraScrollEx_ValorV > (_BarraScrollEx_PaginaV - nSaltoLinea->TamY))	BarraScrollEx_ValorV((YAbsoluta - (_BarraScrollEx_PaginaV - nSaltoLinea->TamY)));
			if (YAbsoluta - _BarraScrollEx_ValorV < 0)												BarraScrollEx_ValorV(YAbsoluta);
			// 3 Miramos si hay que cambiar los valores del scroll H
			if (XAbsoluta - _BarraScrollEx_ValorH > _BarraScrollEx_PaginaH)	BarraScrollEx_ValorH((XAbsoluta - _BarraScrollEx_PaginaH) + 1);
			if (XAbsoluta - _BarraScrollEx_ValorH < 0)						BarraScrollEx_ValorH(XAbsoluta);
		}


		const SIZE DWLEdicionEx_Nucleo::_EdicionEx_CalcularScrolls(HWND hWndControl, const long ValorV, const long ValorH, const bool HacerVisibleCursor) {
			SIZE TamFinal = { 0, 0 };
			for (size_t i = 0; i < _EdicionEx_Objetos.size(); i++) {
				switch (_EdicionEx_Objetos[i]->Tipo()) {
					case DWL_Enum_EdicionEx_TipoObjeto_INICIO :
					case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
						if (TamFinal.cx < _EdicionEx_Objetos[i]->SaltoLinea()->TamX) TamFinal.cx = _EdicionEx_Objetos[i]->SaltoLinea()->TamX;
						TamFinal.cy += _EdicionEx_Objetos[i]->SaltoLinea()->TamY;
						break;
				}
			}
			
			RECT RC;
			GetClientRect(hWndControl, &RC);
			int Borde = 2;
			if (EdicionEx_Estilos.PintarBorde == true) Borde = 6;

			_BarraScrollEx_MaximoH = TamFinal.cx + 5;
			_BarraScrollEx_MaximoV = TamFinal.cy;
			_BarraScrollEx_PaginaH = RC.right - Borde;
			_BarraScrollEx_PaginaV = RC.bottom - Borde;

			if (BarraScrollEx_VisibleH() == TRUE && BarraScrollEx_VisibleV() == TRUE) {
				_BarraScrollEx_PaginaV -= 21;
				_BarraScrollEx_PaginaH -= 21;
			}
			else if (BarraScrollEx_VisibleH() == TRUE && BarraScrollEx_VisibleV() == FALSE) {
				_BarraScrollEx_PaginaV -= 21;
				if (BarraScrollEx_VisibleV() == TRUE) _BarraScrollEx_PaginaH -= 21;
			}
			else if (BarraScrollEx_VisibleH() == FALSE && BarraScrollEx_VisibleV() == TRUE) {
				 _BarraScrollEx_PaginaH -= 21;
				if (BarraScrollEx_VisibleH() == TRUE) _BarraScrollEx_PaginaV -= 21;
			}

			if (ValorV != 0) BarraScrollEx_ValorV(ValorV);
			if (ValorH != 0) BarraScrollEx_ValorH(ValorH);
			if (HacerVisibleCursor == true) _EdicionEx_HacerVisibleCursor(hWndControl);

			// Correccion de valores por si se pasan del maximo
			if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) _BarraScrollEx_ValorV = (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
			if (_BarraScrollEx_ValorH > (_BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH)) _BarraScrollEx_ValorH = (_BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH);


			BarraScrollEx_CalcularScrollV(EdicionEx_Estilos.PintarBorde);
			BarraScrollEx_CalcularScrollH(EdicionEx_Estilos.PintarBorde);
			BarraScrollEx_PosicionarScrolls(hWndControl, &RC, false, EdicionEx_Estilos.PintarBorde);
			return TamFinal;
		}

		// Funcion que elimina los objetos Seleccion del array de objetos.
		void DWLEdicionEx_Nucleo::_EdicionEx_LimpiarSeleccion(void) {
			for (long Pos = static_cast<long>(_EdicionEx_Objetos.size() - 1); Pos != 0; Pos --) {
				if (_EdicionEx_Objetos[Pos]->Tipo() == DWL_Enum_EdicionEx_TipoObjeto_Seleccion) {
					delete _EdicionEx_Objetos[Pos];
					_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + Pos);
				}
			}
		}

		// Funcion que elimina los objetos Seleccion del array de objetos.
		void DWLEdicionEx_Nucleo::_EdicionEx_BorrarCursor(void) {
			for (long Pos = static_cast<long>(_EdicionEx_Objetos.size() - 1); Pos != 0; Pos --) {
				if (_EdicionEx_Objetos[Pos]->Tipo() == DWL_Enum_EdicionEx_TipoObjeto_Cursor) {
					delete _EdicionEx_Objetos[Pos];
					_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + Pos);
					return;
				}
			}
		}


		// Funcion que nos dice los puntos seleccionados dentro del texto.
		void DWLEdicionEx_Nucleo::_EdicionEx_PosicionSeleccion(long &PosSel1, long &PosSel2) {
			long PosCursor = 0;
			PosSel1 = -1;
			PosSel2 = -1;
			for (PosCursor = 0; PosCursor < static_cast<long>(_EdicionEx_Objetos.size()); PosCursor ++) {
				if (_EdicionEx_Objetos[PosCursor]->Tipo() == DWL_Enum_EdicionEx_TipoObjeto_Seleccion) {
					if (PosSel1 == -1)  PosSel1 = PosCursor;
					else {
						PosSel2 = PosCursor;
						return;
					}
				}
			}
		}

		//  Esta funcion retorna la posicion del cursor
		const long DWLEdicionEx_Nucleo::_EdicionEx_PosicionCursor(void) {
			long PosCursor = 0;
			for (PosCursor = 0; PosCursor < static_cast<long>(_EdicionEx_Objetos.size()); PosCursor ++) {
				if (_EdicionEx_Objetos[PosCursor]->Tipo() == DWL_Enum_EdicionEx_TipoObjeto_Cursor) return PosCursor;
			}
			return -1; // No deberia devolver -1 NUNCA
		}


		// Devuelve el salto de linea que hay detras de Pos
		const long DWLEdicionEx_Nucleo::_EdicionEx_SaltoLineaAnterior(const long Pos) {
			long nPos = Pos;
			DWLEdicionEx_Objeto *TmpObjeto = NULL;
			do {
				nPos --;
				if (nPos > 0 && nPos < static_cast<long>(_EdicionEx_Objetos.size()))	TmpObjeto = _EdicionEx_Objetos[nPos];
				else																	return -1;
			} while (TmpObjeto->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_INICIO && TmpObjeto->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea);
			return nPos;
		}


		// Devuelve el salto de linea que hay delante de Pos o -1 si se llega al final
		const long DWLEdicionEx_Nucleo::_EdicionEx_SaltoLineaSiguiente(const long Pos) {
			long nPos = Pos;
			DWLEdicionEx_Objeto *TmpObjeto = NULL;
			do {
				nPos ++;
				if (nPos > 0 && nPos < static_cast<long>(_EdicionEx_Objetos.size()))	TmpObjeto = _EdicionEx_Objetos[nPos];
				else																	return -1;
			} while (TmpObjeto->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea);
			return nPos;
		}

		
		void DWLEdicionEx_Nucleo::_EdicionEx_BorrarCaracter(HWND hWndControl, const bool TeclaSuprimir) {
			long PosCursor = 0;
			long PosFinal = 0;
			bool Salir = false;
			DWLEdicionEx_ObjetoFuente     *nFuente     = NULL;
			DWLEdicionEx_ObjetoSaltoLinea *nSaltoLinea = _EdicionEx_Objetos[0]->SaltoLinea();
			// Buscamos el cursor y el salto de linea al que corresponde teniendo en cuenta la ultima fuente
			for (PosCursor = 0; PosCursor < static_cast<long>(_EdicionEx_Objetos.size()); PosCursor ++) {
				switch (_EdicionEx_Objetos[PosCursor]->Tipo()) {
					case DWL_Enum_EdicionEx_TipoObjeto_Fuente :
						nFuente = _EdicionEx_Objetos[PosCursor]->Fuente();
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_Cursor :
						Salir = true;
						break;
				}
				if (Salir == true) break;
			}

			if (TeclaSuprimir == false) PosFinal = PosCursor -1;
			else						PosFinal = PosCursor +1;
			if (PosFinal >= static_cast<long>(_EdicionEx_Objetos.size())) return;
			if (_EdicionEx_Objetos[PosFinal]->Tipo() == DWL_Enum_EdicionEx_TipoObjeto_FINAL) return;
			DWLEdicionEx_Objeto *nObjeto = _EdicionEx_Objetos[PosFinal]; // Objeto anterior al cursor
			while (nObjeto->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_Caracter && nObjeto->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea) {
				if (_EdicionEx_Objetos[PosFinal]->Tipo() == DWL_Enum_EdicionEx_TipoObjeto_INICIO || PosFinal < 2) return; // no se puede borrar el objeto inicial NI LA PRIMERA FUENTE, salimos de la funcion.
				delete nObjeto;
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosFinal);
				if (TeclaSuprimir == false) PosFinal --;
				else						PosFinal ++;
				nObjeto = _EdicionEx_Objetos[PosFinal];
			}
			delete nObjeto;
			_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosFinal);


			// Recalculamos la linea
			// - 1 obtenemos la direccion del tamaño de la linea mirando el salto de linea.
			do {
				PosFinal --;
				nObjeto = _EdicionEx_Objetos[PosFinal];
			} while (nObjeto->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_INICIO && nObjeto->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea);
			nSaltoLinea = nObjeto->SaltoLinea();

			// - 2 obtenemos el texto de la linea
			DWLString TmpStr;
			Salir = false;
			HDC hDC = GetDC(hWndControl);
			SIZE nTam = { 0, 0 };
			HFONT VFont = static_cast<HFONT>(SelectObject(hDC, nFuente->Fuente));

			long TamX = 0;
			long TamY = 0;
			long LineaBase = 0;
			TEXTMETRIC Medidas;
			for (long i = PosFinal + 1; i < static_cast<long>(_EdicionEx_Objetos.size()); i++) {
				switch (_EdicionEx_Objetos[i]->Tipo()) {
					case DWL_Enum_EdicionEx_TipoObjeto_Caracter :
						TmpStr += _EdicionEx_Objetos[i]->Caracter();
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
					case DWL_Enum_EdicionEx_TipoObjeto_FINAL :
						GetTextMetrics(hDC, &Medidas);
						GetTextExtentPoint32(hDC, TmpStr(), TmpStr.Tam(), &nTam);
						if (TamY < nTam.cy) TamY = nTam.cy;
						if (LineaBase < Medidas.tmAscent) LineaBase = Medidas.tmAscent;
						TamX += nTam.cx;
						TmpStr.Borrar();
						Salir = true;
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_Fuente :
						GetTextMetrics(hDC, &Medidas);
						GetTextExtentPoint32(hDC, TmpStr(), TmpStr.Tam(), &nTam);
						if (TamY < nTam.cy) TamY = nTam.cy;
						if (LineaBase < Medidas.tmAscent) LineaBase = Medidas.tmAscent;
						TamX += nTam.cx;
						nFuente = _EdicionEx_Objetos[i]->Fuente();
						SelectObject(hDC, nFuente->Fuente);
						TmpStr.Borrar();

						break;
				}
				if (Salir == true) break;
			}

			nSaltoLinea->TamX = TamX;
			nSaltoLinea->TamY = TamY;
			nSaltoLinea->LineaBase = LineaBase;

			SelectObject(hDC, VFont);
			ReleaseDC(hWndControl, hDC);

			_EdicionEx_CalcularScrolls(hWndControl, 0, 0, true);
		}


		void DWLEdicionEx_Nucleo::_EdicionEx_AgregarIntro(HWND hWndControl) {
			long PosCursor = 0;
			long PosLinea1 = 0;
			bool Salir = false;
			DWLEdicionEx_ObjetoFuente *nFuente = NULL;
			DWLEdicionEx_ObjetoSaltoLinea *nSaltoLinea = NULL;
			for (PosCursor = 0; PosCursor < static_cast<long>(_EdicionEx_Objetos.size()); PosCursor ++) {
				switch (_EdicionEx_Objetos[PosCursor]->Tipo()) { 
					case DWL_Enum_EdicionEx_TipoObjeto_Fuente :
						nFuente = _EdicionEx_Objetos[PosCursor]->Fuente();
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_Cursor :
						Salir = true;
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
					case DWL_Enum_EdicionEx_TipoObjeto_INICIO :
						nSaltoLinea = _EdicionEx_Objetos[PosCursor]->SaltoLinea();
						PosLinea1 = PosCursor;
						break;
				}
				if (Salir == true) break;
			}
			DWLString TmpStr;
			// Medimos la linea donde estaba el cursor (por si nos hemos llevado algun caracter hacia abajo)
			for (PosLinea1 = PosLinea1; PosLinea1 < PosCursor; PosLinea1 ++) {
				switch (_EdicionEx_Objetos[PosLinea1]->Tipo()) { 
					case DWL_Enum_EdicionEx_TipoObjeto_Caracter :
						TmpStr += _EdicionEx_Objetos[PosLinea1]->Caracter();
						break;
				}
			}
			TmpStr += TEXT(' ');
			HDC hDC = GetDC(hWndControl);
			HFONT VFont = static_cast<HFONT>(SelectObject(hDC, nFuente->Fuente));
			SIZE nTam = { 0, 0 };
			nSaltoLinea->TamX = 0;
			GetTextExtentPoint32(hDC, TmpStr(), TmpStr.Tam(), &nTam);
			nSaltoLinea->TamX = nTam.cx;
			nSaltoLinea->TamY = nTam.cy;
			TmpStr.Borrar();
			Salir = false;
			// Medimos la linea nueva que se ha creado
			for (PosLinea1 = PosCursor; PosLinea1 < static_cast<long>(_EdicionEx_Objetos.size()); PosLinea1 ++) {
				switch (_EdicionEx_Objetos[PosLinea1]->Tipo()) { 
					case DWL_Enum_EdicionEx_TipoObjeto_Caracter :
						TmpStr += _EdicionEx_Objetos[PosLinea1]->Caracter();
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_FINAL :
					case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
						Salir = true;
						break;
				}
			}
			SIZE TamFinal;
			TamFinal.cy = nSaltoLinea->TamY;
			TamFinal.cx = 0;
			if (TmpStr.Tam() > 0) {
				GetTextExtentPoint32(hDC, TmpStr(), TmpStr.Tam(), &nTam);
				TamFinal.cx = nTam.cx;
				TamFinal.cy = nTam.cy;
			}

			SelectObject(hDC, VFont);
			ReleaseDC(hWndControl, hDC);
			long LineaBase = nSaltoLinea->LineaBase;
			nSaltoLinea = new DWLEdicionEx_ObjetoSaltoLinea(TamFinal.cx, TamFinal.cy, LineaBase);
			DWLEdicionEx_Objeto *nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea, nSaltoLinea);
			_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + PosCursor, nObjeto);
			_BarraScrollEx_MaximoV += TamFinal.cy;

			_EdicionEx_CalcularScrolls(hWndControl, 0, 0, true);
		}


		void DWLEdicionEx_Nucleo::_EdicionEx_AgregarCaracter(HWND hWndControl, const TCHAR nCaracter) {
			long PosCursor = 0;
			long PosLineaActual = 0;
			DWLEdicionEx_ObjetoFuente     *nFuente = NULL;
			DWLEdicionEx_ObjetoSaltoLinea *nSaltoLinea = NULL;
			bool Salir = false;

			// Buscamos el cursor y el salto de linea al que corresponde
			for (PosCursor = 0; PosCursor < static_cast<long>(_EdicionEx_Objetos.size()); PosCursor ++) {
				switch (_EdicionEx_Objetos[PosCursor]->Tipo()) { 
					case DWL_Enum_EdicionEx_TipoObjeto_Cursor :
						Salir = true;
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
					case DWL_Enum_EdicionEx_TipoObjeto_INICIO :
						nSaltoLinea = _EdicionEx_Objetos[PosCursor]->SaltoLinea();
						PosLineaActual = PosCursor;
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_Fuente :
						nFuente = _EdicionEx_Objetos[PosCursor]->Fuente();
						break;
				}
				if (Salir == true) break;
			}

			DWLEdicionEx_Objeto *nObjeto;
			TCHAR *NuevoCaracter = new TCHAR(nCaracter);
			// Agregamos el caracter detras del cursor
			nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Caracter, NuevoCaracter);
			_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + PosCursor, nObjeto);

			SIZE Tam;
			DWLString TmpStr;

			for (int i = PosLineaActual + 1; i < static_cast<long>(_EdicionEx_Objetos.size()); i++) {
				switch (_EdicionEx_Objetos[i]->Tipo()) {
					case DWL_Enum_EdicionEx_TipoObjeto_Caracter :
						TmpStr += _EdicionEx_Objetos[i]->Caracter();
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
					case DWL_Enum_EdicionEx_TipoObjeto_FINAL :
						TmpStr += TEXT(' ');
						HDC hDC = GetDC(GetDesktopWindow());
						HFONT VFont = static_cast<HFONT>(SelectObject(hDC, nFuente->Fuente));
						GetTextExtentPoint32(hDC, TmpStr(), TmpStr.Tam(), &Tam);
						SelectObject(hDC, VFont);
						ReleaseDC(GetDesktopWindow(), hDC);
						nSaltoLinea->TamX = Tam.cx;
						nSaltoLinea->TamY = Tam.cy;
						if (_EdicionEx_MaximoAnchoLinea < nSaltoLinea->TamX) _EdicionEx_MaximoAnchoLinea = nSaltoLinea->TamX;
						if (_EdicionEx_MaximoAltoLinea < nSaltoLinea->TamY) _EdicionEx_MaximoAltoLinea = nSaltoLinea->TamY;
						_EdicionEx_CalcularScrolls(hWndControl, 0, 0, true);
						return;
				}
			}
		}

		UINT DWLEdicionEx_Nucleo::EdicionEx_LongitudTexto(void) const {
			UINT Ret = 0;
			for (size_t i = 0; i < _EdicionEx_Objetos.size(); i++) {
				switch (_EdicionEx_Objetos[i]->Tipo()) {
					case DWL_Enum_EdicionEx_TipoObjeto_Caracter :
					case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
						Ret ++;
						break;
				}
			}
			return Ret;
		}

		const TCHAR *DWLEdicionEx_Nucleo::EdicionEx_ObtenerTexto(void) {
			_EdicionEx_TmpTxt.Borrar();
			for (size_t i = 0; i < _EdicionEx_Objetos.size(); i++) {
				switch (_EdicionEx_Objetos[i]->Tipo()) {
					case DWL_Enum_EdicionEx_TipoObjeto_Caracter :
						_EdicionEx_TmpTxt += _EdicionEx_Objetos[i]->Caracter();
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
						_EdicionEx_TmpTxt += TEXT('\n');
						break;
				}
			}
			_EdicionEx_TmpTxt += TEXT('\0');
			return _EdicionEx_TmpTxt();
		}


		void DWLEdicionEx_Nucleo::EdicionEx_AgregarColorFondo(COLORREF nColor) {
			DWLEdicionEx_Objeto *nObjeto;
			nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_ColorFondo, reinterpret_cast<LPVOID>(nColor));
			_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + (_EdicionEx_Objetos.size() -1), nObjeto);
		}

		void DWLEdicionEx_Nucleo::EdicionEx_AgregarColorTexto(COLORREF nColor) {
			DWLEdicionEx_Objeto *nObjeto;
			nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_ColorTexto, reinterpret_cast<LPVOID>(nColor));
			_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + (_EdicionEx_Objetos.size() -1), nObjeto);
		}

		void DWLEdicionEx_Nucleo::EdicionEx_AgregarColorFondoCursor(COLORREF nColor) {
			DWLEdicionEx_Objeto *nObjeto;
			nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_ColorFondo, reinterpret_cast<LPVOID>(nColor));
			_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + _EdicionEx_PosicionCursor(), nObjeto);
		}

		void DWLEdicionEx_Nucleo::EdicionEx_AgregarColorTextoCursor(COLORREF nColor) {
			DWLEdicionEx_Objeto *nObjeto;
			nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_ColorTexto, reinterpret_cast<LPVOID>(nColor));
			_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + _EdicionEx_PosicionCursor(), nObjeto);
		}

		// NO HAY CARACTERES DETRAS
		void DWLEdicionEx_Nucleo::EdicionEx_AgregarFuente(HWND hWndControl, HFONT nFuenteAgregada) {
			long PosSaltoLinea = 0;
			// Busco el salto de linea
			DWLEdicionEx_ObjetoSaltoLinea *nSaltoLinea = NULL;
			DWLEdicionEx_ObjetoFuente     *nFuente     = NULL;
			DWLEdicionEx_Objeto           *nObjeto     = NULL;
			bool Salir = false;
			for (long i = _EdicionEx_Objetos.size() - 1; i != -1; i --) {
				switch (_EdicionEx_Objetos[i]->Tipo()) {
					case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
					case DWL_Enum_EdicionEx_TipoObjeto_INICIO :
						nSaltoLinea = _EdicionEx_Objetos[i]->SaltoLinea();
						Salir = true;
						break;
				}
				if (Salir == true) break;
			}
			HDC hDC = GetDC(hWndControl);
			HFONT VFont =  static_cast<HFONT>(SelectObject(hDC, nFuenteAgregada));

			TEXTMETRIC Medidas;
			GetTextMetrics(hDC, &Medidas);
			nFuente = new DWLEdicionEx_ObjetoFuente(nFuenteAgregada, Medidas.tmAscent, Medidas.tmDescent);
			if (nSaltoLinea->LineaBase < Medidas.tmAscent) nSaltoLinea->LineaBase = Medidas.tmAscent;
			nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Fuente, nFuente);
			_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + (_EdicionEx_Objetos.size() -1), nObjeto);

			_EdicionEx_CalcularScrolls(hWndControl, (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV));
			SelectObject(hDC, VFont);
			ReleaseDC(hWndControl, hDC);
		}


		void DWLEdicionEx_Nucleo::EdicionEx_AgregarFuenteCursor(HWND hWndControl, HFONT nFuente) {
			DWLEdicionEx_Objeto *nObjeto;

			long PosCursor = -1;
			long Contador = 1;
			DWLEdicionEx_ObjetoFuente *FuenteActual = NULL;
			DWLEdicionEx_ObjetoSaltoLinea *nSaltoLinea = NULL;
			DWLString StrLineaActual;
			DWLString StrFinLineaActual;
			bool Salir = false;
			nSaltoLinea = _EdicionEx_Objetos[0]->SaltoLinea();
			for (Contador = 1; Contador < static_cast<long>(_EdicionEx_Objetos.size()); Contador ++) {
				switch (_EdicionEx_Objetos[Contador]->Tipo()) {
					case DWL_Enum_EdicionEx_TipoObjeto_Fuente :
						FuenteActual = _EdicionEx_Objetos[Contador]->Fuente();
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_Cursor :
						PosCursor = Contador;
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
						if (PosCursor == -1) {
							StrLineaActual.Borrar();
							nSaltoLinea = _EdicionEx_Objetos[Contador]->SaltoLinea();
						}
						else {
							Salir = true;
						}
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_Caracter :
						if (PosCursor == -1) StrLineaActual		+= _EdicionEx_Objetos[Contador]->Caracter();
						else                 StrFinLineaActual	+= _EdicionEx_Objetos[Contador]->Caracter();
						break;
				}
				if (Salir == true) break;
			}
			SIZE Tam2, Tam3;
			HDC hDC = GetDC(hWndControl);
			// Mido el texto en pixeles desde el principio de la linea actual hasta donde se colocara la nueva fuente
			HFONT VFont =  static_cast<HFONT>(SelectObject(hDC, FuenteActual->Fuente));

			if (StrLineaActual.Tam() == 0) {
				StrLineaActual = TEXT(" "); // Si el texto esta vacio, agrego un espacio para que calcule su altura
				GetTextExtentPoint32(hDC, StrLineaActual(), StrLineaActual.Tam(), &Tam2);
				Tam2.cx = 0;
			}
			else {
				StrLineaActual = TEXT(" "); 
				GetTextExtentPoint32(hDC, StrLineaActual(), StrLineaActual.Tam(), &Tam2);
			}
			
			// Mido el texto en pixeles desde donde se colocara la nueva fuente hasta el final de la linea
			SelectObject(hDC, nFuente);
			if (StrFinLineaActual.Tam() == 0) {
				StrFinLineaActual = TEXT(' '); // Si el texto esta vacio, agrego un espacio para que calcule su altura
				GetTextExtentPoint32(hDC, StrFinLineaActual(), StrFinLineaActual.Tam(), &Tam3);
				Tam3.cx = 0;
			}
			else {
				StrFinLineaActual += TEXT(' ');
				GetTextExtentPoint32(hDC, StrFinLineaActual(), StrFinLineaActual.Tam(), &Tam3);
			}

			// Asigno el nuevo tamaño de la linea
			if (Tam2.cy > Tam3.cy)	nSaltoLinea->TamY = Tam2.cy;
			else					nSaltoLinea->TamY = Tam3.cy;
			if (_EdicionEx_MaximoAltoLinea < nSaltoLinea->TamY) _EdicionEx_MaximoAltoLinea = nSaltoLinea->TamY;
			nSaltoLinea->TamX = Tam2.cx + Tam3.cx;
			if (_EdicionEx_MaximoAnchoLinea < nSaltoLinea->TamX) _EdicionEx_MaximoAnchoLinea = nSaltoLinea->TamX;
			TEXTMETRIC Medidas;
			GetTextMetrics(hDC, &Medidas);
			FuenteActual = new DWLEdicionEx_ObjetoFuente(nFuente, Medidas.tmAscent, Medidas.tmDescent);
			if (nSaltoLinea->LineaBase < Medidas.tmAscent) nSaltoLinea->LineaBase = Medidas.tmAscent;
			nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Fuente, FuenteActual);
			_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + PosCursor, nObjeto);

			_EdicionEx_CalcularScrolls(hWndControl, (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV));
			SelectObject(hDC, VFont);
			ReleaseDC(hWndControl, hDC);
		}


		void DWLEdicionEx_Nucleo::_EdicionEx_CalcularLinea(HWND hWndControl, DWLEdicionEx_ObjetoSaltoLinea *nSaltoLinea) {
			if (_EdicionEx_Objetos.size() < 2) return;
			DWLEdicionEx_ObjetoFuente *nFuente    = _EdicionEx_Objetos[1]->Fuente();
			bool                       Calculando = false;
			DWLString				   TmpStr;
			long					   TamX       = 0;
			long					   TamY       = 0;
			long					   LineaBase  = 0;
			SIZE					   Tam;
			HDC                        hDC        = GetDC(hWndControl);
			HFONT                      VFont      = static_cast<HFONT>(SelectObject(hDC, EdicionEx_Estilos.Fuente()));
//			TEXTMETRIC                 Medidas;
			bool                       Salir      = false;
			for (long i = 0; i < static_cast<long>(_EdicionEx_Objetos.size()); i++) {
				switch (_EdicionEx_Objetos[i]->Tipo()) {
					case DWL_Enum_EdicionEx_TipoObjeto_Fuente :
						nFuente = _EdicionEx_Objetos[i]->Fuente();
						SelectObject(hDC, nFuente->Fuente);
						if (Calculando == true) {
//							GetTextMetrics(hDC, &Medidas);
							if (LineaBase < nFuente->Ascent) LineaBase = nFuente->Ascent;
						}
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
					case DWL_Enum_EdicionEx_TipoObjeto_INICIO :
						if (nSaltoLinea == _EdicionEx_Objetos[i]->SaltoLinea()) { 
							Calculando = true;
							if (LineaBase < nFuente->Ascent) LineaBase = nFuente->Ascent;
							TamX = 0;
							TamY = 0;
						}
						else {
							if (Calculando == true) {
								Salir = true;
								TmpStr = TEXT(' ');
								GetTextExtentPoint32(hDC, TmpStr(), TmpStr.Tam(), &Tam);
								TamX += Tam.cx;
								if (TamY < Tam.cy) TamY = Tam.cy;
							}
						}
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_FINAL :
						TmpStr = TEXT(' ');
						GetTextExtentPoint32(hDC, TmpStr(), TmpStr.Tam(), &Tam);
						TamX += Tam.cx;
						if (TamY < Tam.cy) TamY = Tam.cy;
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_Caracter :
						if (Calculando == true) {
							TmpStr = _EdicionEx_Objetos[i]->Caracter();
							GetTextExtentPoint32(hDC, TmpStr(), TmpStr.Tam(), &Tam);
							TamX += Tam.cx;
							if (TamY < Tam.cy) TamY = Tam.cy;
						}
						break;
				}
				if (Salir == true) break;
			}
			nSaltoLinea->TamX = TamX;
			nSaltoLinea->TamY = TamY;
			nSaltoLinea->LineaBase = LineaBase;
			if (_EdicionEx_MaximoAltoLinea < nSaltoLinea->TamY) _EdicionEx_MaximoAltoLinea = nSaltoLinea->TamY;
			if (_EdicionEx_MaximoAnchoLinea < nSaltoLinea->TamX) _EdicionEx_MaximoAnchoLinea = nSaltoLinea->TamX;
			ReleaseDC(hWndControl, hDC);
		}


        void DWLEdicionEx_Nucleo::EdicionEx_AgregarTexto(HWND hWndControl, const TCHAR *nTexto) {
			HDC                            hDC         = GetDC(hWndControl);
			HFONT                          VFont       = static_cast<HFONT>(SelectObject(hDC, EdicionEx_Estilos.Fuente()));
			bool EdicionExVacio = false;
			DWLEdicionEx_Objeto           *nObjeto     = NULL;
			DWLEdicionEx_ObjetoSaltoLinea *nSaltoLinea = NULL;
			DWLEdicionEx_ObjetoFuente     *nFuente     = NULL;
			TEXTMETRIC                     Medidas;
			long i;

			// Si no hay objetos agregamos un nuevo texto con la funcion EdicionEx_Texto
			if (_EdicionEx_Objetos.size() == 0) {
				EdicionExVacio = true;
				// Agrego el objeto inicial
				GetTextMetrics(hDC, &Medidas);
				nSaltoLinea = new DWLEdicionEx_ObjetoSaltoLinea(0, 0, Medidas.tmAscent);
				nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_INICIO, nSaltoLinea);
				_EdicionEx_Objetos.push_back(nObjeto);
				// Agrego la fuente inicial
				nFuente = new DWLEdicionEx_ObjetoFuente(EdicionEx_Estilos.Fuente(), Medidas.tmAscent, Medidas.tmDescent);
				nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Fuente, nFuente);
				_EdicionEx_Objetos.push_back(nObjeto);
				// Agrego el cursor
				nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.push_back(nObjeto);
				// Agrego el objeto final
				nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_FINAL, 0);
				_EdicionEx_Objetos.push_back(nObjeto);
			}

			// Buscamos el salto de linea anterior
			long PosSaltoLinea = -1;
			for (i = _EdicionEx_Objetos.size() - 1; i != -1; i --) {
				switch (_EdicionEx_Objetos[i]->Tipo()) {
					case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
					case DWL_Enum_EdicionEx_TipoObjeto_INICIO :
						if (PosSaltoLinea == -1) {
							nSaltoLinea = _EdicionEx_Objetos[i]->SaltoLinea();
							PosSaltoLinea = i;
						}
						break;
				}
				if (PosSaltoLinea != -1) break;
			}


			long TamTexto = DWLStrLen(nTexto) + 1;
//			SIZE Tam;
			long LineaBase = 0;
			long Contador = _EdicionEx_Objetos.size() -1;
			TCHAR *NuevoCaracter;
			for (i = 0; i < TamTexto; i++) {
				if (nTexto[i] == TEXT('\n')) { // final de la linea
					_EdicionEx_CalcularLinea(hWndControl, nSaltoLinea);
					LineaBase = nSaltoLinea->LineaBase;
					nSaltoLinea = new DWLEdicionEx_ObjetoSaltoLinea(0, 0, LineaBase);
					nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea, nSaltoLinea);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Contador, nObjeto);
					Contador ++;
				}
				else if (nTexto[i] == TEXT('\0')) { // final del texto
					_EdicionEx_CalcularLinea(hWndControl, nSaltoLinea);
				}
				else { // normal
					NuevoCaracter = new TCHAR(nTexto[i]);
					nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Caracter, NuevoCaracter);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Contador, nObjeto);
					Contador ++;

				}
			}

			_EdicionEx_CalcularScrolls(hWndControl, (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV));

			SelectObject(hDC, VFont);
			ReleaseDC(hWndControl, hDC);
		}



        void DWLEdicionEx_Nucleo::EdicionEx_AgregarTextoCursor(HWND hWndControl, const TCHAR *nTexto) {
			HDC hDC = GetDC(hWndControl);
			HFONT VFont = static_cast<HFONT>(SelectObject(hDC, EdicionEx_Estilos.Fuente()));
			bool EdicionExVacio = false;
			DWLEdicionEx_Objeto           *nObjeto     = NULL;
			DWLEdicionEx_ObjetoSaltoLinea *nSaltoLinea = NULL;
			DWLEdicionEx_ObjetoFuente     *nFuente = NULL;
			TEXTMETRIC Medidas;
			// Si no hay objetos agregamos un nuevo texto con la funcion EdicionEx_Texto
			if (_EdicionEx_Objetos.size() == 0) {
				EdicionExVacio = true;
				// Agrego el objeto inicial
				GetTextMetrics(hDC, &Medidas);
				nSaltoLinea = new DWLEdicionEx_ObjetoSaltoLinea(0, 0, Medidas.tmAscent);
				nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_INICIO, nSaltoLinea);
				_EdicionEx_Objetos.push_back(nObjeto);
				// Agrego la fuente inicial
				nFuente = new DWLEdicionEx_ObjetoFuente(EdicionEx_Estilos.Fuente(), Medidas.tmAscent, Medidas.tmDescent);
				nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Fuente, nFuente);
				_EdicionEx_Objetos.push_back(nObjeto);
				// Agrego el cursor
				nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.push_back(nObjeto);
				// Agrego el objeto final
				nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_FINAL, 0);
				_EdicionEx_Objetos.push_back(nObjeto);
			}

			// buscamos el cursor, obtenemos la ultima fuente, y obtenemos el texto de la linea actual
			long PosCursor = -1;
			long Contador = 1;
			bool Salir = false;
			nSaltoLinea = _EdicionEx_Objetos[0]->SaltoLinea();
			long AnchoMaximo = 0;
			DWLString StrLineaActual;
			DWLString StrFinLineaActual;
			for (Contador; Contador < static_cast<long>(_EdicionEx_Objetos.size()); Contador ++) {
				switch (_EdicionEx_Objetos[Contador]->Tipo()) {
					case DWL_Enum_EdicionEx_TipoObjeto_Fuente :
						nFuente = _EdicionEx_Objetos[Contador]->Fuente();
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_Cursor :
						PosCursor = Contador;
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
						if (PosCursor == -1) {
							StrLineaActual.Borrar();
							if (AnchoMaximo < nSaltoLinea->TamX) AnchoMaximo = nSaltoLinea->TamX;
							nSaltoLinea = _EdicionEx_Objetos[Contador]->SaltoLinea();
						}
						else {
							Salir = true;
						}
						break;
					case DWL_Enum_EdicionEx_TipoObjeto_Caracter :
						if (PosCursor == -1) StrLineaActual		+= _EdicionEx_Objetos[Contador]->Caracter();
						else                 StrFinLineaActual	+= _EdicionEx_Objetos[Contador]->Caracter();
						break;
				}
				if (Salir == true) break;
			}

			// Agregamos los caracteres nuevos
			long UltimaCY = 0;
			SelectObject(hDC, nFuente->Fuente);
			Contador = PosCursor;
			size_t TamTexto = DWLStrLen(nTexto) + 1;
//			SIZE Tam;
			long LineaBase = 0;
			TCHAR *NuevoCaracter;
			for (size_t i = 0; i < TamTexto; i++) {
				if (nTexto[i] == TEXT('\n')) { // final de la linea
					_EdicionEx_CalcularLinea(hWndControl, nSaltoLinea);
					/*StrLineaActual += TEXT(' ');
					GetTextExtentPoint32(hDC, StrLineaActual(), StrLineaActual.Tam(), &Tam);
					nSaltoLinea->TamX = Tam.cx;
					if (nSaltoLinea->TamY < Tam.cy) nSaltoLinea->TamY = Tam.cy;
					if (AnchoMaximo < nSaltoLinea->TamX) AnchoMaximo = nSaltoLinea->TamX;
					if (_EdicionEx_MaximoAltoLinea < nSaltoLinea->TamY) _EdicionEx_MaximoAltoLinea = nSaltoLinea->TamY;
					if (_EdicionEx_MaximoAnchoLinea < nSaltoLinea->TamX) _EdicionEx_MaximoAnchoLinea = nSaltoLinea->TamX;
					StrLineaActual.Borrar();*/
					LineaBase = nSaltoLinea->LineaBase;
					nSaltoLinea = new DWLEdicionEx_ObjetoSaltoLinea(0, 0, LineaBase);
					nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea, nSaltoLinea);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Contador, nObjeto);
					Contador ++;
				}
				else if (nTexto[i] == TEXT('\0')) { // final del texto
					/*StrLineaActual += TEXT(' ');
					StrLineaActual += StrFinLineaActual; // Añado la parte final de la linea (Si el cursor tenia palabras por delante, tambien hay que calcularlas)
					GetTextExtentPoint32(hDC, StrLineaActual(), StrLineaActual.Tam(), &Tam);
					nSaltoLinea->TamX = Tam.cx;
					if (AnchoMaximo < nSaltoLinea->TamX) AnchoMaximo = nSaltoLinea->TamX;
					if (nSaltoLinea->TamY < Tam.cy) nSaltoLinea->TamY = Tam.cy;
					if (_EdicionEx_MaximoAltoLinea < nSaltoLinea->TamY) _EdicionEx_MaximoAltoLinea = nSaltoLinea->TamY;
					if (_EdicionEx_MaximoAnchoLinea < nSaltoLinea->TamX) _EdicionEx_MaximoAnchoLinea = nSaltoLinea->TamX;
					StrLineaActual.Borrar();*/
					_EdicionEx_CalcularLinea(hWndControl, nSaltoLinea);
				}
				else { // normal
					NuevoCaracter = new TCHAR(nTexto[i]);
					nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Caracter, NuevoCaracter);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Contador, nObjeto);
					Contador ++;

				}
			}

			_EdicionEx_CalcularScrolls(hWndControl, (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV));

			SelectObject(hDC, VFont);
			ReleaseDC(hWndControl, hDC);
		}

		
        void DWLEdicionEx_Nucleo::EdicionEx_BorrarTexto(void) {
			for (size_t i = 0; i < _EdicionEx_Objetos.size(); i++) delete _EdicionEx_Objetos[i];
            _EdicionEx_Objetos.resize(0);
        }

		const long DWLEdicionEx_Nucleo::_EdicionEx_PintarTexto(HDC hDCDest, HDC Buffer, DWLString &Txt, const int cX, const int cY, DWLEdicionEx_ObjetoSaltoLinea *SaltoLinea, DWLEdicionEx_ObjetoFuente *Fuente, COLORREF nColorFondo, COLORREF nColorTexto) {
			if (Txt.Tam() == 0) return 0;
			SIZE TamTexto;
			SetBkMode(Buffer, TRANSPARENT);
			SetTextColor(Buffer, nColorTexto);

			GetTextExtentPoint32(Buffer, Txt(), Txt.Tam(), &TamTexto); 
			RECT RC = { 0, 0, SaltoLinea->TamX, SaltoLinea->TamY };
			HBRUSH Brocha = CreateSolidBrush(nColorFondo);
			FillRect(Buffer, &RC, Brocha);
			DeleteObject(Brocha);
			TEXTMETRIC Medidas;
			GetTextMetrics(Buffer, &Medidas); 
//			TextOut(Buffer, 0, SaltoLinea->TamY - TamTexto.cy, Txt(), Txt.Tam());
			if (Medidas.tmAscent == SaltoLinea->LineaBase)	TextOut(Buffer, 0, 0, Txt(), Txt.Tam());
			else											TextOut(Buffer, 0, (SaltoLinea->LineaBase - Medidas.tmAscent), Txt(), Txt.Tam());
			int Borde = 2;
			if (EdicionEx_Estilos.PintarBorde == true) Borde = 7;
			if (cX + TamTexto.cx > _BarraScrollEx_PaginaH + Borde) 
				TamTexto.cx = (_BarraScrollEx_PaginaH + Borde) - cX;
			if (cY + TamTexto.cy > _BarraScrollEx_PaginaV + Borde) 
				TamTexto.cy = (_BarraScrollEx_PaginaV + Borde) - cY;
			BitBlt(hDCDest, cX, cY, TamTexto.cx, SaltoLinea->TamY, Buffer, 0, 0, SRCCOPY);
			return TamTexto.cx;
		}


        void DWLEdicionEx_Nucleo::EdicionEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco, const bool PintarConMascara) {
			RECT	RC            = { 0, 0, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top };
            RECT    EspacioEdit   = { 1, 1, (Espacio->right - Espacio->left) - 2, (Espacio->bottom - Espacio->top) - 2 };
			HDC		hDCCompatible = CreateCompatibleDC(hDC);
			HBITMAP BMPCompatible = CreateCompatibleBitmap(hDC, RC.right, RC.bottom);
			HBITMAP BMPViejo      = static_cast<HBITMAP>(SelectObject(hDCCompatible, BMPCompatible));
			HRGN	Region        = CreateRoundRectRgn(0, 0, RC.right + 1, RC.bottom + 1, 2, 2);
			HPEN    PlumaVieja    = static_cast<HPEN>(SelectObject(hDCCompatible, static_cast<HPEN>(GetStockObject(BLACK_PEN))));
            
			// HDC Compatible para pintar una linea de texto
			HDC     hDCLinea	  = CreateCompatibleDC(hDC);
			HBITMAP BMPLinea	  = CreateCompatibleBitmap(hDC, _EdicionEx_MaximoAnchoLinea, _EdicionEx_MaximoAltoLinea);
			HBITMAP BMPViejoLinea = static_cast<HBITMAP>(SelectObject(hDCLinea, BMPLinea));
            HFONT   VFuente       = static_cast<HFONT>(SelectObject(hDCLinea, EdicionEx_Estilos.Fuente()));

            // Pinto la mascara del control si se requiere
			if (PintarConMascara == true) {
				FillRect(hDCCompatible, &RC, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));
				FillRgn(hDCCompatible, Region, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
				BitBlt(hDC, Espacio->left, Espacio->top, RC.right, RC.bottom, hDCCompatible, 0, 0, SRCAND);
			}
            
			COLORREF RGBFondo;
			COLORREF RGBFondo2;
			COLORREF RGBTexto;
			HBRUSH ColorFondo;
			if (_EdicionEx_Activado == false)	{
				RGBTexto = EdicionEx_Estilos.Colores.TextoDesactivado();
				RGBFondo = EdicionEx_Estilos.Colores.FondoDesactivado();
				RGBFondo2 = EdicionEx_Estilos.Colores.FondoDesactivado();
				ColorFondo = CreateSolidBrush(EdicionEx_Estilos.Colores.FondoDesactivado()); // Creo el color del fondo			
			}
			else {
				RGBTexto = EdicionEx_Estilos.Colores.Texto();
				RGBFondo = EdicionEx_Estilos.Colores.Fondo();
				RGBFondo2 = EdicionEx_Estilos.Colores.Fondo();
				ColorFondo = CreateSolidBrush(EdicionEx_Estilos.Colores.Fondo()); // Creo el color del fondo			
			}
            // Pinto el fondo del control
			FillRect(hDCCompatible, &RC, ColorFondo); // Pinto el fondo
			DeleteObject(ColorFondo);

            // Recalculo el espacio para la edición
            if (EdicionEx_Estilos.PintarBorde == true) {
                EspacioEdit.left    = 3;
                EspacioEdit.top     = 3;
                EspacioEdit.right  -= 6;
                EspacioEdit.bottom -= 6;
            }
            // Recalculo el espacio para la edición según los scrolls que puedan haber visibles
            if (BarraScrollEx_VisibleV() == TRUE)	EspacioEdit.right  -= 17;
			if (BarraScrollEx_VisibleH() == TRUE)	EspacioEdit.bottom -= 17;

			if (_EdicionEx_Objetos.size() > 0) {
				DWLString TmpStr;
				long XActual = EspacioEdit.left;
				long YActual = EspacioEdit.top;
				long XCursor = 0;
				long YCursor = 0;
				long Y2Cursor = 0;
				bool Seleccion = false;
				SIZE TamTexto;
				DWLEdicionEx_ObjetoFuente     *nFuente = NULL;
				DWLEdicionEx_ObjetoSaltoLinea *nSaltoLinea = _EdicionEx_Objetos[0]->SaltoLinea();

				for (size_t i = 1; i < _EdicionEx_Objetos.size(); i++) {
					switch (_EdicionEx_Objetos[i]->Tipo()) {
						case DWL_Enum_EdicionEx_TipoObjeto_Fuente :
							if ((_BarraScrollEx_ValorV - nSaltoLinea->TamY) <= YActual) {
								XActual += _EdicionEx_PintarTexto(hDCCompatible, hDCLinea, TmpStr, XActual - _BarraScrollEx_ValorH, YActual - _BarraScrollEx_ValorV, nSaltoLinea, nFuente, RGBFondo, RGBTexto);
								TmpStr.Borrar();
							}
							//////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Seleccionamos la fuente para que _EdicionEx_PintarTexto pueda detectar que tamaño necesita el buffer //
							// NO QUITAR EL SELECTOBJECT DE AQUI, ES NECESARIO EN _EdicionEx_PintarTexto							//
	//						SelectObject(hDCCompatible, _EdicionEx_Objetos[i]->Fuente());											//
							SelectObject(hDCLinea, _EdicionEx_Objetos[i]->Fuente()->Fuente);										//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////
							nFuente = _EdicionEx_Objetos[i]->Fuente();
							break;
						case DWL_Enum_EdicionEx_TipoObjeto_ColorTexto :
							if ((_BarraScrollEx_ValorV - nSaltoLinea->TamY) <= YActual) {
								XActual += _EdicionEx_PintarTexto(hDCCompatible, hDCLinea, TmpStr, XActual - _BarraScrollEx_ValorH, YActual - _BarraScrollEx_ValorV, nSaltoLinea, nFuente, RGBFondo, RGBTexto);
								TmpStr.Borrar();
							}
							RGBTexto = _EdicionEx_Objetos[i]->ColorTexto();
							break;
						case DWL_Enum_EdicionEx_TipoObjeto_ColorFondo :
							if (Seleccion == false) {
								if ((_BarraScrollEx_ValorV - nSaltoLinea->TamY) <= YActual) {
									XActual += _EdicionEx_PintarTexto(hDCCompatible, hDCLinea, TmpStr, XActual - _BarraScrollEx_ValorH, YActual - _BarraScrollEx_ValorV, nSaltoLinea, nFuente, RGBFondo, RGBTexto);
									TmpStr.Borrar();
								}
								RGBFondo = _EdicionEx_Objetos[i]->ColorFondo();
							}
							else {
								RGBFondo2 = _EdicionEx_Objetos[i]->ColorFondo();
							}
							break;
						case DWL_Enum_EdicionEx_TipoObjeto_Seleccion :
							if ((_BarraScrollEx_ValorV - nSaltoLinea->TamY) <= YActual) {
								XActual += _EdicionEx_PintarTexto(hDCCompatible, hDCLinea, TmpStr, XActual - _BarraScrollEx_ValorH, YActual - _BarraScrollEx_ValorV, nSaltoLinea, nFuente, RGBFondo, RGBTexto);
								TmpStr.Borrar();
							}
							if (Seleccion == false) {
								Seleccion = true;
								RGBFondo2 = RGBFondo;
								RGBFondo = EdicionEx_Estilos.Colores.FondoSeleccionado();
							}
							else {
								Seleccion = false;
								RGBFondo = RGBFondo2;
							}
							break;
						case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
							if ((_BarraScrollEx_ValorV - nSaltoLinea->TamY) <= YActual) {
								TmpStr += TEXT(' ');
								_EdicionEx_PintarTexto(hDCCompatible, hDCLinea, TmpStr, XActual - _BarraScrollEx_ValorH, YActual - _BarraScrollEx_ValorV, nSaltoLinea, nFuente, RGBFondo, RGBTexto);
								TmpStr.Borrar();
								XActual = EspacioEdit.left;
							}
							YActual += nSaltoLinea->TamY;
							nSaltoLinea = _EdicionEx_Objetos[i]->SaltoLinea();
							// Esta fuera, salimos del bucle
							if (YActual - nSaltoLinea->TamY > _BarraScrollEx_ValorV  + _BarraScrollEx_PaginaV) i = _EdicionEx_Objetos.size();
							break;
						case DWL_Enum_EdicionEx_TipoObjeto_Cursor :
							GetTextExtentPoint32(hDCLinea, TmpStr(), TmpStr.Tam(), &TamTexto); 
							XCursor = TamTexto.cx + ((XActual - _BarraScrollEx_ValorH) - 1);
							YCursor = (YActual - _BarraScrollEx_ValorV);
							Y2Cursor = YCursor + nSaltoLinea->TamY;
							break; 
						case DWL_Enum_EdicionEx_TipoObjeto_Caracter :
							if (_BarraScrollEx_ValorV - nSaltoLinea->TamY <= YActual) TmpStr += _EdicionEx_Objetos[i]->Caracter();
							break;
						case DWL_Enum_EdicionEx_TipoObjeto_FINAL :
							if (_BarraScrollEx_ValorV - nSaltoLinea->TamY <= YActual) {
								_EdicionEx_PintarTexto(hDCCompatible, hDCLinea, TmpStr, XActual - _BarraScrollEx_ValorH, YActual - _BarraScrollEx_ValorV, nSaltoLinea, nFuente,  RGBFondo, RGBTexto);
								TmpStr.Borrar();
								XActual = EspacioEdit.left;
							}
							break;
					}
				}
				// Pinto el cursor si esta en la parte visible
				if (_EdicionEx_CursorVisible == true && _EdicionEx_Activado == true) {
					if (XCursor > -1 && XCursor <= _BarraScrollEx_PaginaH && YCursor > -1 && YCursor <= _BarraScrollEx_PaginaV) {
						MoveToEx(hDCCompatible, XCursor, YCursor, NULL);
						LineTo(hDCCompatible, XCursor, Y2Cursor);
					}
				}
			}

            // Pinto el borde del control
            if (EdicionEx_Estilos.PintarBorde == true) {
			    HBRUSH Brocha;
			    if (TieneFoco == true)	Brocha = CreateSolidBrush(EdicionEx_Estilos.Colores.BordeSeleccionado());
			    else					Brocha = CreateSolidBrush(EdicionEx_Estilos.Colores.Borde());
			    FrameRgn(hDCCompatible, Region, Brocha, 1, 1);
                DeleteObject(Brocha);
            }

          	BarraScrollEx_PintarV(hDCCompatible);
			BarraScrollEx_PintarH(hDCCompatible);	

			if (PintarConMascara == false)	BitBlt(hDC, Espacio->left, Espacio->top, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top, hDCCompatible, 0, 0, SRCCOPY);
			else							BitBlt(hDC, Espacio->left, Espacio->top, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top, hDCCompatible, 0, 0, SRCPAINT);

            SelectObject(hDCLinea, VFuente);
            SelectObject(hDCLinea, BMPViejoLinea);
			DeleteObject(BMPLinea);
			DeleteDC(hDCLinea);
			
			DeleteObject(Region);
			SelectObject(hDCCompatible, PlumaVieja);
            SelectObject(hDCCompatible, BMPViejo);
			DeleteObject(BMPCompatible);
			DeleteDC(hDCCompatible);
        }


		const bool DWLEdicionEx_Nucleo::_EdicionEx_Tecla_Inicio(void) {
			DWLEdicionEx_Objeto *TmpObjeto = NULL;
			long PosCursor = 0;
			long Salto1    = 0;
			long PosSel1   = 0;
			long PosSel2   = 0;

			if (_EdicionEx_TeclaControlPresionada == FALSE && _EdicionEx_TeclaShiftPresionada == FALSE) { // Normal
				_EdicionEx_LimpiarSeleccion();
				PosCursor = _EdicionEx_PosicionCursor();
				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);
				Salto1 = _EdicionEx_SaltoLineaAnterior(PosCursor);
				if (Salto1 < 2) Salto1 = 2;
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto1, TmpObjeto);
			}
			else if (_EdicionEx_TeclaControlPresionada == TRUE && _EdicionEx_TeclaShiftPresionada == FALSE) { // Control
				_EdicionEx_LimpiarSeleccion();
				PosCursor = _EdicionEx_PosicionCursor();
				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + 1, TmpObjeto);
			}
			else if (_EdicionEx_TeclaControlPresionada == FALSE && _EdicionEx_TeclaShiftPresionada == TRUE) { // Shift
				PosCursor = _EdicionEx_PosicionCursor();
				_EdicionEx_PosicionSeleccion(PosSel1, PosSel2);
				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);
				Salto1 = _EdicionEx_SaltoLineaAnterior(PosCursor);
				if (Salto1 == -1) Salto1 = 2;

				if (PosSel1 == -1) { //	no hay seleccion
					TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + PosCursor, TmpObjeto);
				}
				else {
					if (_EdicionEx_Objetos[PosSel1 -1]->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_Seleccion) {
						delete _EdicionEx_Objetos[PosSel1];
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosSel1);				
					}
					else {
						delete _EdicionEx_Objetos[PosSel1 - 1];
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosSel1 - 1);				
					}
				}
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto1, TmpObjeto);
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto1, TmpObjeto);
			}
			else if (_EdicionEx_TeclaControlPresionada == TRUE && _EdicionEx_TeclaShiftPresionada == TRUE) { // Control + Shift
				PosCursor = _EdicionEx_PosicionCursor();
				_EdicionEx_PosicionSeleccion(PosSel1, PosSel2);

				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);
				if (PosSel1 == -1) { //	no hay seleccion
					TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + PosCursor, TmpObjeto);
				}
				else {
					if (_EdicionEx_Objetos[PosSel1 -1]->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_Seleccion) {
						delete _EdicionEx_Objetos[PosSel1];
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosSel1);
					}
					else {
						delete _EdicionEx_Objetos[PosSel1 -1];
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosSel1 -1);
					}
				}
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + 1, TmpObjeto);
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + 1, TmpObjeto);
			}
			return true;
		}

		const bool DWLEdicionEx_Nucleo::_EdicionEx_Tecla_Fin(void) {
			DWLEdicionEx_Objeto *TmpObjeto = NULL;
			long PosCursor = 0;
			long Salto1    = 0;
			long PosSel1   = 0;
			long PosSel2   = 0;
			if (_EdicionEx_TeclaControlPresionada == FALSE && _EdicionEx_TeclaShiftPresionada == FALSE) {
				_EdicionEx_LimpiarSeleccion();
				PosCursor = _EdicionEx_PosicionCursor();
				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);
				Salto1 = _EdicionEx_SaltoLineaSiguiente(PosCursor);
				if (Salto1 == -1) Salto1 = _EdicionEx_Objetos.size() - 1;
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto1, TmpObjeto);
			}
			else if (_EdicionEx_TeclaControlPresionada == FALSE && _EdicionEx_TeclaShiftPresionada == TRUE) { // shift
				PosCursor = _EdicionEx_PosicionCursor();
				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);

				Salto1 = _EdicionEx_SaltoLineaSiguiente(PosCursor);
				if (Salto1 == -1) Salto1 = _EdicionEx_Objetos.size() - 1;

				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto1, TmpObjeto);		

				_EdicionEx_PosicionSeleccion(PosSel1, PosSel2);
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto1, TmpObjeto);

				if (PosSel1 == -1) { //	no hay seleccion
					TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + PosCursor, TmpObjeto);
//					Salto1++;
				}
				else {
					if (_EdicionEx_Objetos[PosSel2]->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_Seleccion) {
						delete _EdicionEx_Objetos[PosSel2 + 1];
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + (PosSel2 + 1));				
					}
					else {
						delete _EdicionEx_Objetos[PosSel2];
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + (PosSel2));				
					}
				}
			}
			else if (_EdicionEx_TeclaControlPresionada == TRUE && _EdicionEx_TeclaShiftPresionada == FALSE) { // control
				_EdicionEx_LimpiarSeleccion();
				PosCursor = _EdicionEx_PosicionCursor();
				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + _EdicionEx_Objetos.size() - 1, TmpObjeto);
			}
			else if (_EdicionEx_TeclaControlPresionada == TRUE && _EdicionEx_TeclaShiftPresionada == TRUE) { // control + shift
				PosCursor = _EdicionEx_PosicionCursor();
				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);
				_EdicionEx_PosicionSeleccion(PosSel1, PosSel2);

				if (PosSel1 == -1) { //	no hay seleccion
					TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + PosCursor, TmpObjeto);
				}
				else {
					if (_EdicionEx_Objetos[PosSel2]->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_Seleccion) {
						delete _EdicionEx_Objetos[PosSel2]; // observar hacia donde sale la seleccion +1 o -1
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosSel2);
					}
					else {
						delete _EdicionEx_Objetos[PosSel2];
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosSel2);
					}
				}
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + _EdicionEx_Objetos.size() -1, TmpObjeto);
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + _EdicionEx_Objetos.size() - 1, TmpObjeto);

			}
			return true;
		}

		const bool DWLEdicionEx_Nucleo::_EdicionEx_Tecla_Arriba(void) {
			DWLEdicionEx_Objeto *TmpObjeto = NULL;
			long PosCursor = 0;
			long Salto1    = 0;
			long Salto2    = 0;
			long PosSel1   = 0;
			long PosSel2   = 0;
			long XPos      = 0;

			if (_EdicionEx_TeclaControlPresionada == FALSE && _EdicionEx_TeclaShiftPresionada == FALSE) { // normal
				_EdicionEx_LimpiarSeleccion();
				PosCursor = _EdicionEx_PosicionCursor();
				Salto1 = _EdicionEx_SaltoLineaAnterior(PosCursor);
				Salto2 = _EdicionEx_SaltoLineaAnterior(Salto1);
			
				if (Salto1 == -1) return false;
				for (Salto1 = Salto1; Salto1 < PosCursor; Salto1 ++) {
					if (_EdicionEx_Objetos[Salto1]->Tipo() == DWL_Enum_EdicionEx_TipoObjeto_Caracter) XPos ++;
				}
				if (_EdicionEx_CursorX < XPos) _EdicionEx_CursorX = XPos;
				else                           XPos = _EdicionEx_CursorX;
				XPos++;

				if (Salto2 == -1) Salto2 = 0; // estamos al principio
				for (Salto2 = Salto2 + 1; Salto2 < static_cast<long>(_EdicionEx_Objetos.size()); Salto2 ++) {
					switch (_EdicionEx_Objetos[Salto2]->Tipo()){ 
						case DWL_Enum_EdicionEx_TipoObjeto_Caracter : XPos --; break;
						case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
							XPos = 0;
							break;
						case DWL_Enum_EdicionEx_TipoObjeto_INICIO :
							return false; // estamos lo mas arriba posible
							break;
					}
					if (XPos == 0) break;
				}
				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);

				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto2, TmpObjeto);
			}
			else if (_EdicionEx_TeclaControlPresionada == FALSE && _EdicionEx_TeclaShiftPresionada == TRUE) { // Shift
				PosCursor = _EdicionEx_PosicionCursor();
				Salto1 = _EdicionEx_SaltoLineaAnterior(PosCursor);
				Salto2 = _EdicionEx_SaltoLineaAnterior(Salto1);
			
				if (Salto1 == -1) return false;
				for (Salto1 = Salto1; Salto1 < PosCursor; Salto1 ++) {
					if (_EdicionEx_Objetos[Salto1]->Tipo() == DWL_Enum_EdicionEx_TipoObjeto_Caracter) XPos ++;
				}
				if (_EdicionEx_CursorX < XPos) _EdicionEx_CursorX = XPos;
				else                           XPos = _EdicionEx_CursorX;
				XPos++;

				if (Salto2 == -1) Salto2 = 0; // estamos al principio
				for (Salto2 = Salto2 + 1; Salto2 < static_cast<long>(_EdicionEx_Objetos.size()); Salto2 ++) {
					switch (_EdicionEx_Objetos[Salto2]->Tipo()){ 
						case DWL_Enum_EdicionEx_TipoObjeto_Caracter : XPos --; break;
						case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
							XPos = 0;
							break;
						case DWL_Enum_EdicionEx_TipoObjeto_INICIO :
							return false; // estamos lo mas arriba posible
							break;
					}
					if (XPos == 0) break;
				}
				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);

				_EdicionEx_PosicionSeleccion(PosSel1, PosSel2);
				if (PosSel1 == -1) { // no hay seleccion
					TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + PosCursor, TmpObjeto);	
//					Salto2 ++;
				}
				else {
					if (_EdicionEx_Objetos[PosSel1]->Tipo() == DWL_Enum_EdicionEx_TipoObjeto_Seleccion) {
						delete _EdicionEx_Objetos[PosSel1];
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosSel1);
					}
					else {
						delete _EdicionEx_Objetos[PosSel1];
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosSel1);
					}
				}

				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto2, TmpObjeto);	
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto2, TmpObjeto);	
			}
			return true;	
		}

		const bool DWLEdicionEx_Nucleo::_EdicionEx_Tecla_Abajo(void) {
			DWLEdicionEx_Objeto *TmpObjeto = NULL;
			long PosCursor = 0;
			long Salto1    = 0;
			long Salto2    = 0;
			long PosSel1   = 0;
			long PosSel2   = 0;
			long XPos      = 0;

			if (_EdicionEx_TeclaControlPresionada == FALSE && _EdicionEx_TeclaShiftPresionada == FALSE) {
				_EdicionEx_LimpiarSeleccion();
				PosCursor = _EdicionEx_PosicionCursor();
				Salto1 = _EdicionEx_SaltoLineaAnterior(PosCursor);
				if (Salto1 == -1) Salto1 = 0;
				for (Salto1 = Salto1; Salto1 < PosCursor; Salto1 ++) {
					if (_EdicionEx_Objetos[Salto1]->Tipo() == DWL_Enum_EdicionEx_TipoObjeto_Caracter) XPos ++;
				}
				if (_EdicionEx_CursorX < XPos) _EdicionEx_CursorX = XPos;
				else                           XPos = _EdicionEx_CursorX;

				Salto2 = _EdicionEx_SaltoLineaSiguiente(PosCursor);
				if (Salto2 == -1) return false; // estamos lo mas abajo posible
				if (XPos > 0) {
					for (Salto2 = Salto2 + 1; Salto2 < static_cast<long>(_EdicionEx_Objetos.size()); Salto2 ++) {
						switch (_EdicionEx_Objetos[Salto2]->Tipo()){ 
							case DWL_Enum_EdicionEx_TipoObjeto_Caracter : XPos --; break;
							case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
								XPos = 0;
								Salto2 --;
								break;
							case DWL_Enum_EdicionEx_TipoObjeto_FINAL :
								return false;
						}
						if (XPos == 0) break;
					}
				}
				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);

				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto2, TmpObjeto);
			}
			if (_EdicionEx_TeclaControlPresionada == FALSE && _EdicionEx_TeclaShiftPresionada == TRUE) {
				PosCursor = _EdicionEx_PosicionCursor();
				Salto1 = _EdicionEx_SaltoLineaAnterior(PosCursor);
				if (Salto1 == -1) Salto1 = 0;
				for (Salto1 = Salto1; Salto1 < PosCursor; Salto1 ++) {
					if (_EdicionEx_Objetos[Salto1]->Tipo() == DWL_Enum_EdicionEx_TipoObjeto_Caracter) XPos ++;
				}
				if (_EdicionEx_CursorX < XPos) _EdicionEx_CursorX = XPos;
				else                           XPos = _EdicionEx_CursorX;

				Salto2 = _EdicionEx_SaltoLineaSiguiente(PosCursor);
				if (Salto2 == -1) return false; // estamos lo mas abajo posible
				if (XPos > 0) {
					for (Salto2 = Salto2 + 1; Salto2 < static_cast<long>(_EdicionEx_Objetos.size()); Salto2 ++) {
						switch (_EdicionEx_Objetos[Salto2]->Tipo()){ 
							case DWL_Enum_EdicionEx_TipoObjeto_Caracter : XPos --; break;
							case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :
								XPos = 0;
								Salto2 --;
								break;
							case DWL_Enum_EdicionEx_TipoObjeto_FINAL :
								return false;
						}
						if (XPos == 0) break;
					}
				}
				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);

				_EdicionEx_PosicionSeleccion(PosSel1, PosSel2);
				if (PosSel1 == -1) { // no hay seleccion
					TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + PosCursor, TmpObjeto);	
					Salto2++;
				}
				else {
					Salto2--;
					if (_EdicionEx_Objetos[PosSel2]->Tipo() == DWL_Enum_EdicionEx_TipoObjeto_Seleccion) {
						delete _EdicionEx_Objetos[PosSel2];
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosSel2);
					}
					else {
						delete _EdicionEx_Objetos[PosSel2];
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosSel2);
					}
				}

				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto2, TmpObjeto);		
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto2, TmpObjeto);		
			}

			return true;
		}

		const bool DWLEdicionEx_Nucleo::_EdicionEx_Tecla_Izquierda(void) {
			long PosCursor = 0;
			long Salto1   = 0;
			long PosSel1  = 0;
			long PosSel2  = 0;

			if (_EdicionEx_TeclaControlPresionada == FALSE && _EdicionEx_TeclaShiftPresionada == FALSE) {
				_EdicionEx_LimpiarSeleccion();
				PosCursor = _EdicionEx_PosicionCursor();
				if (PosCursor == 0) return false;
				Salto1 = PosCursor -1;
				DWLEdicionEx_Objeto *TmpObjeto = _EdicionEx_Objetos[Salto1];
				while (TmpObjeto->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_Caracter && TmpObjeto->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea) {
					Salto1 --;
					if (Salto1 < 0) return false;
					TmpObjeto = _EdicionEx_Objetos[Salto1];
				}
				// Borro el cursor
				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);
				// Inserto el cursor
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto1, TmpObjeto);
			}
			else if (_EdicionEx_TeclaControlPresionada == FALSE && _EdicionEx_TeclaShiftPresionada == TRUE) {
				PosCursor = _EdicionEx_PosicionCursor();
				if (PosCursor == 0) return false;
				Salto1 = PosCursor -1;
				DWLEdicionEx_Objeto *TmpObjeto = _EdicionEx_Objetos[Salto1];
				while (TmpObjeto->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_Caracter && TmpObjeto->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea) {
					Salto1 --;
					if (Salto1 < 0) return false;
					TmpObjeto = _EdicionEx_Objetos[Salto1];
				}
				// Borro el cursor
				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);

				_EdicionEx_PosicionSeleccion(PosSel1, PosSel2);

				if (PosSel1 == -1) { // Creo la primera parte de la seleccion
					TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + PosCursor, TmpObjeto);
				}
				else { // elimino la primera parte de la seleccion 
					if (PosSel1 < PosCursor) {
						delete _EdicionEx_Objetos[PosSel2];
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosSel2);
					}
					else {
						delete _EdicionEx_Objetos[PosSel1];
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosSel1);
					}
				}

				// Segunda parte de la seleccion
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto1, TmpObjeto);
				// Inserto el cursor
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto1, TmpObjeto);
			}
			_EdicionEx_CursorX = 0;		
			return true;
		}


		const bool DWLEdicionEx_Nucleo::_EdicionEx_Tecla_Derecha(void) {
			long PosCursor = 0;
			long Salto1   = 0;
			long PosSel1  = 0;
			long PosSel2  = 0;

			if (_EdicionEx_TeclaControlPresionada == FALSE && _EdicionEx_TeclaShiftPresionada == FALSE) {
				_EdicionEx_LimpiarSeleccion();
				PosCursor = _EdicionEx_PosicionCursor();
				if (_EdicionEx_Objetos.size() == 0) return false;
				Salto1 = PosCursor + 1;
				DWLEdicionEx_Objeto *TmpObjeto = _EdicionEx_Objetos[Salto1];
				while (TmpObjeto->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_Caracter && TmpObjeto->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea) {
					Salto1 ++;
					if (Salto1 == _EdicionEx_Objetos.size()) return false;
					TmpObjeto = _EdicionEx_Objetos[Salto1];
				}
				// Borro el cursor
				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);
				// Inserto el cursor
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto1, TmpObjeto);
				_EdicionEx_CursorX = 0;
			}
			else if (_EdicionEx_TeclaControlPresionada == FALSE && _EdicionEx_TeclaShiftPresionada == TRUE) {
				PosCursor = _EdicionEx_PosicionCursor();
				if (_EdicionEx_Objetos.size() == 0) return false;
				Salto1 = PosCursor + 1;
				DWLEdicionEx_Objeto *TmpObjeto = _EdicionEx_Objetos[Salto1];
				while (TmpObjeto->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_Caracter && TmpObjeto->Tipo() != DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea) {
					Salto1 ++;
					if (Salto1 == _EdicionEx_Objetos.size()) return false;
					TmpObjeto = _EdicionEx_Objetos[Salto1];
				}
				// Borro el cursor
				delete _EdicionEx_Objetos[PosCursor];
				_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);
				_EdicionEx_CursorX = 0;

				_EdicionEx_PosicionSeleccion(PosSel1, PosSel2);

				if (PosSel1 == -1) { // Creo la primera parte de la seleccion
					TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + PosCursor, TmpObjeto);
					Salto1 ++;
				}
				else { // elimino la segunda parte de la seleccion 
					if (PosSel2 > PosCursor) {
						delete _EdicionEx_Objetos[PosSel1];
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosSel1);
						Salto1 --;
					}
					else {
						delete _EdicionEx_Objetos[PosSel2];
						_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosSel2);
						Salto1 --;
					}
				}
				// Segunda parte de la seleccion
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto1, TmpObjeto);
				// Inserto el cursor
				TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
				_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + Salto1, TmpObjeto);

			}
			return true;
		}

   		void DWLEdicionEx_Nucleo::EdicionEx_Teclado_TeclaPresionada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params) {
			if (_EdicionEx_Activado == false) return;
			bool HacerVisibleCursor = false;
			switch (Caracter) {
				case VK_SHIFT :		_EdicionEx_TeclaShiftPresionada = true;							break;
				case VK_CONTROL :	_EdicionEx_TeclaControlPresionada = true;						break;
				case VK_HOME :		HacerVisibleCursor = _EdicionEx_Tecla_Inicio();					break;
				case VK_END :		HacerVisibleCursor = _EdicionEx_Tecla_Fin();					break;
				case VK_UP :		HacerVisibleCursor = _EdicionEx_Tecla_Arriba();					break;
				case VK_DOWN :		HacerVisibleCursor = _EdicionEx_Tecla_Abajo();					break;
				case VK_LEFT :		HacerVisibleCursor = _EdicionEx_Tecla_Izquierda();				break;
				case VK_RIGHT :		HacerVisibleCursor = _EdicionEx_Tecla_Derecha();				break;
				case VK_DELETE :
					if (EdicionEx_Estilos.TextoModificable == false) return;
					_EdicionEx_CursorVisible = true;
					_EdicionEx_BorrarCaracter(hWndControl, true);
					break;
			}			
			_EdicionEx_CursorVisible = true;
			if (HacerVisibleCursor == true) _EdicionEx_HacerVisibleCursor(hWndControl);
        }


   		void DWLEdicionEx_Nucleo::EdicionEx_Teclado_TeclaSoltada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params) {
			switch (Caracter) {
				case VK_SHIFT :		_EdicionEx_TeclaShiftPresionada = false;				break;
				case VK_CONTROL :	_EdicionEx_TeclaControlPresionada = false;				break;
			}
		}

   		void DWLEdicionEx_Nucleo::EdicionEx_Teclado_Caracter(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params) {
			if (_EdicionEx_Activado == false) return;
			switch (Caracter) {
				case VK_RETURN :
					if (EdicionEx_Estilos.TextoModificable == false) return;
					_EdicionEx_CursorVisible = true;
					if (EdicionEx_Estilos.MultiLinea == true) _EdicionEx_AgregarIntro(hWndControl);
					break;
				case VK_BACK :
					if (EdicionEx_Estilos.TextoModificable == false) return;
					_EdicionEx_CursorVisible = true;
					_EdicionEx_BorrarCaracter(hWndControl, false);
					break;
				case VK_ESCAPE :
					_EdicionEx_LimpiarSeleccion();
					break;
				default :
					if (EdicionEx_Estilos.TextoModificable == false) return;
					_EdicionEx_CursorVisible = true;
					_EdicionEx_AgregarCaracter(hWndControl, Caracter);
					break;
			}
		}

		void DWLEdicionEx_Nucleo::_EdicionEx_EliminarCursor(void) {
			long PosCursor = _EdicionEx_PosicionCursor();
			delete _EdicionEx_Objetos[PosCursor];
			_EdicionEx_Objetos.erase(_EdicionEx_Objetos.begin() + PosCursor);
		}

		void DWLEdicionEx_Nucleo::_EdicionEx_CrearCursor(const long nPosCursor) {
			DWLEdicionEx_Objeto *nObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
			_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + nPosCursor, nObjeto);
		}

   		const BOOL DWLEdicionEx_Nucleo::EdicionEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			if (_EdicionEx_Activado == false) return TRUE;
			if (BarraScrollEx_Mouse_BotonPresionado(hWndControl, RectaControl, Boton, cX, cY, Param) == TRUE) return TRUE;
			if (_EdicionEx_TeclaShiftPresionada == false) _EdicionEx_LimpiarSeleccion();
			SetCapture(hWndControl);
			_EdicionEx_UltimoObjetoMouse = _EdicionEx_ObtenerObjetoCoordenadas(hWndControl, cX, cY);
			
			_EdicionEx_EliminarCursor();
			_EdicionEx_CrearCursor(_EdicionEx_UltimoObjetoMouse);
            return TRUE;
        }

   		const BOOL DWLEdicionEx_Nucleo::EdicionEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			if (_EdicionEx_Activado == false) return TRUE;
			ReleaseCapture();
			if (BarraScrollEx_Mouse_BotonSoltado(hWndControl, RectaControl, Boton, cX, cY, Param) == TRUE) return TRUE;
			_EdicionEx_UltimoObjetoMouse = -1;
            return TRUE;
        }

        const BOOL DWLEdicionEx_Nucleo::EdicionEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param) {
			if (_EdicionEx_Activado == false) return TRUE;
			if (BarraScrollEx_Mouse_Movimiento(hWndControl, RectaControl, cX, cY, Param, EdicionEx_Estilos.PintarBorde) == TRUE) return TRUE;
			if (_EdicionEx_UltimoObjetoMouse != -1) {
				DWLEdicionEx_Objeto *TmpObjeto = NULL;
				long PosObjetoMouse = _EdicionEx_ObtenerObjetoCoordenadas(hWndControl, cX, cY);
				if (_EdicionEx_UltimoObjetoMouse > PosObjetoMouse) {
					_EdicionEx_LimpiarSeleccion();
					_EdicionEx_BorrarCursor();
					PosObjetoMouse = _EdicionEx_ObtenerObjetoCoordenadas(hWndControl, cX, cY);
					TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + _EdicionEx_UltimoObjetoMouse, TmpObjeto);
					TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + PosObjetoMouse, TmpObjeto);
					TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + PosObjetoMouse, TmpObjeto);
				}
				else if (_EdicionEx_UltimoObjetoMouse < PosObjetoMouse) {
					_EdicionEx_LimpiarSeleccion();
					_EdicionEx_BorrarCursor();
					PosObjetoMouse = _EdicionEx_ObtenerObjetoCoordenadas(hWndControl, cX, cY);
					TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Cursor, 0);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + PosObjetoMouse, TmpObjeto);
					TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + PosObjetoMouse, TmpObjeto);
					TmpObjeto = new DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto_Seleccion, 0);
					_EdicionEx_Objetos.insert(_EdicionEx_Objetos.begin() + _EdicionEx_UltimoObjetoMouse, TmpObjeto);
				}

			}
			
            return TRUE;
        }

		const BOOL DWLEdicionEx_Nucleo::EdicionEx_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey) {
			if (_EdicionEx_Activado == false) return TRUE;
			return TRUE;
		}


	};
};
#endif