#ifndef DWL_STRING_WCHAR_T_CPP
#define DWL_STRING_WCHAR_T_CPP
 
#include "DWLString_wchar_t.h"
#include "DWLString_char.h"
#include "..\DWL.h"
#include <stdio.h>

namespace DWL {
	DWLString_wchar_t::DWLString_wchar_t(const DWL::DWLString_char &nTexto)	: _Tam(0), _Texto(NULL) { 
		AgregarTexto(nTexto._Texto, nTexto._Tam);	
	};


	void DWLString_wchar_t::Borrar(void) { 	
		if (_Tam != 0 && _Texto != NULL) delete [] _Texto;
		_Tam = 0;
		_Texto = NULL;
	};


	void DWLString_wchar_t::AgregarCaracter(const wchar_t nTexto) {
		wchar_t     *TextoFinal = new wchar_t [_Tam + 2];
		UINT TamFinal = _Tam + 1;
		UINT i = 0;
		for (i = 0; i < _Tam; i++)	TextoFinal[i] = _Texto[i];
		TextoFinal[TamFinal -1] = nTexto;
		TextoFinal[TamFinal] = 0;
		Borrar();
		_Texto = TextoFinal;
		_Tam = TamFinal;
	}

	void DWLString_wchar_t::AgregarCaracter(const char nTexto) {
		wchar_t     *TextoFinal = new wchar_t [_Tam + 2];
		UINT TamFinal = _Tam + 1;
		UINT i = 0;
		for (i = 0; i < _Tam; i++)	TextoFinal[i] = _Texto[i];
		char NuevoTexto[2];
		wchar_t NuevoTextoW[2];
		NuevoTexto[0] = nTexto; NuevoTexto[1] = 0;
		MultiByteToWideChar(CP_OEMCP, MB_PRECOMPOSED, NuevoTexto, 2, NuevoTextoW, 2);
		TextoFinal[TamFinal -1] = NuevoTextoW[0];
		TextoFinal[TamFinal] = 0;
		Borrar();
		_Texto = TextoFinal;
		_Tam = TamFinal;
	}

	const UINT DWLString_wchar_t::AgregarTexto(const DWL::DWLString_wchar_t &nTexto)  {
		if (nTexto._Tam == 0) return 0;
		UINT TamFinal = _Tam;
		TamFinal += nTexto._Tam;
		wchar_t *TextoFinal = new wchar_t [TamFinal +1];
		UINT i = 0;
		for (i = 0; i < _Tam; i++)				TextoFinal[i]			= _Texto[i];
		for (i = 0; i < (TamFinal - _Tam); i++) TextoFinal[i + _Tam]	= nTexto._Texto[i];
		Borrar();
		TextoFinal[TamFinal] = 0;
		_Tam = TamFinal;
		_Texto = TextoFinal;
		return nTexto._Tam;
	}

	const UINT DWLString_wchar_t::AgregarTexto(const wchar_t *nTexto, const int nTam) {
		if (nTexto == NULL) return 0;
		UINT TamFinal = _Tam;
		if (nTam == -1) TamFinal += wcslen(nTexto);
		else			TamFinal += nTam;
		wchar_t *TextoFinal = new wchar_t [TamFinal +1];
		UINT i = 0;
		for (i = 0; i < _Tam; i++)				TextoFinal[i]			= _Texto[i];
		for (i = 0; i < (TamFinal - _Tam); i++) TextoFinal[i + _Tam]	= nTexto[i];
		Borrar();
		TextoFinal[TamFinal] = 0;
		_Tam = TamFinal;
		_Texto = TextoFinal;
		return TamFinal - _Tam;
	}

	const UINT DWLString_wchar_t::AgregarTexto(const DWL::DWLString_char &nTexto)  {
		if (nTexto._Tam == 0) return 0;
		UINT TamFinal = _Tam;
		UINT TamnTexto = nTexto._Tam;
		TamFinal += nTexto._Tam;
		wchar_t *TextoFinal = new wchar_t [TamFinal + 1];
		UINT i = 0;
		for (i = 0; i < _Tam; i++)	TextoFinal[i] = _Texto[i];
		wchar_t *Destino = new wchar_t [TamnTexto + 1];
		MultiByteToWideChar(CP_OEMCP, MB_PRECOMPOSED, nTexto._Texto, TamnTexto + 1, Destino, TamnTexto + 1);
		for (i = 0; i < (TamFinal - _Tam); i++) TextoFinal[i + _Tam]	= Destino[i];
		Borrar();
		TextoFinal[TamFinal] = 0;
		_Tam = TamFinal;
		_Texto = TextoFinal;
		delete [] Destino;
		return nTexto._Tam;
	}

	const UINT DWLString_wchar_t::AgregarTexto(const char *nTexto, const int nTam)  {
		if (nTexto == NULL) return 0;
		UINT TamFinal = _Tam;
		UINT TamnTexto = 0; 
		if (nTam == -1) TamnTexto = strlen(nTexto);
		else			TamnTexto = nTam;
		TamFinal += TamnTexto;
		wchar_t *TextoFinal = new wchar_t [TamFinal + 1];
		UINT i = 0;
		for (i = 0; i < _Tam; i++)	TextoFinal[i] = _Texto[i];
		wchar_t *Destino = new wchar_t [TamnTexto + 1];
		MultiByteToWideChar(CP_OEMCP, MB_PRECOMPOSED, nTexto, TamnTexto + 1, Destino, TamnTexto + 1);
		for (i = 0; i < (TamFinal - _Tam); i++) TextoFinal[i + _Tam]	= Destino[i];
		Borrar();
		TextoFinal[TamFinal] = 0;
		_Tam = TamFinal;
		_Texto = TextoFinal;
		delete [] Destino;
		return TamnTexto;
	}


	const bool DWLString_wchar_t::EsNumero(void) {
		if (_Tam == 0) return false;
		for (unsigned int i = 0; i < _Tam; i++) {
			switch (_Texto[i]) {
				case TEXT('0') :	case TEXT('1') :	case TEXT('2') :	case TEXT('3') :	case TEXT('4') :
				case TEXT('5') :	case TEXT('6') :	case TEXT('7') :	case TEXT('8') :	case TEXT('9') :
				case TEXT('\0'):	case TEXT('.') :	case TEXT(',') :
					break;
				default :
					return false;
			}
		}
		return true;
	}

	const bool DWLString_wchar_t::EsNumeroEntero(void) {
		if (_Tam == 0) return false;
		for (unsigned int i = 0; i < _Tam; i++) {
			switch (_Texto[i]) {
				case TEXT('0') :	case TEXT('1') :	case TEXT('2') :	case TEXT('3') :	case TEXT('4') :
				case TEXT('5') :	case TEXT('6') :	case TEXT('7') :	case TEXT('8') :	case TEXT('9') :
				case TEXT('\0'):
					break;
				default :
					return false;
			}
		}
		return true;
	}

	const bool DWLString_wchar_t::EsNumeroDecimal(void) {
		bool Decimal = false;
		if (_Tam == 0) return false;
		for (unsigned int i = 0; i < _Tam; i++) {
			switch (_Texto[i]) {
				case TEXT('0') :	case TEXT('1') :	case TEXT('2') :	case TEXT('3') :	case TEXT('4') :
				case TEXT('5') :	case TEXT('6') :	case TEXT('7') :	case TEXT('8') :	case TEXT('9') :
				case TEXT('\0'):
					break;
				case TEXT('.') :	case TEXT(',') :
					Decimal = true;
					break;
				default :
					return false;
			}
		}
		return Decimal;
	}


	const bool DWLString_wchar_t::Comparar(const char *nTexto, const bool ComparacionBinaria) {
		UINT TamnTexto = strlen(nTexto);
		wchar_t *Destino = new wchar_t [TamnTexto + 1];
		MultiByteToWideChar(CP_OEMCP, MB_PRECOMPOSED, nTexto, TamnTexto, Destino, TamnTexto);

		int Comp = 0;
        if (_Texto == NULL) {
            if (nTexto == NULL) return true;
            else                return false;
        }
		if (ComparacionBinaria == false)	Comp = _wcsicmp(Destino, _Texto);
		else								Comp = wcscmp(Destino, _Texto);
		delete [] Destino;
		if (Comp == 0) return true;
		return false;
	}

	const bool DWLString_wchar_t::Comparar(DWL::DWLString_char &nTexto, const bool ComparacionBinaria) {
		UINT TamnTexto = nTexto._Tam;
		wchar_t *Destino = new wchar_t [TamnTexto + 1];
		MultiByteToWideChar(CP_OEMCP, MB_PRECOMPOSED, nTexto(), TamnTexto, Destino, TamnTexto);
		int Comp;
        if (_Texto == NULL) {
			if (nTexto._Tam == 0)	return true;
            else					return false;
        }
		if (ComparacionBinaria == false)	Comp = _wcsicmp(Destino, _Texto);
		else								Comp = wcscmp(Destino, _Texto);
		delete [] Destino;
		if (Comp == 0) return true;
		return false;
	}

	const bool DWLString_wchar_t::Comparar(const wchar_t *nTexto, const bool ComparacionBinaria) {
		int Comp;
        if (_Texto == NULL) {
            if (nTexto == NULL) return true;
            else                return false;
        }
		if (ComparacionBinaria == false)	Comp = _wcsicmp(nTexto, _Texto);
		else								Comp = wcscmp(nTexto, _Texto);
		if (Comp == 0) return true;
		return false;
	}

	const bool DWLString_wchar_t::Comparar(DWL::DWLString_wchar_t &nTexto, const bool ComparacionBinaria) {
		int Comp;
        if (_Texto == NULL) {
			if (nTexto._Tam == 0)	return true;
            else					return false;
        }
		if (ComparacionBinaria == false)	Comp = _wcsicmp(nTexto._Texto, _Texto);
		else								Comp = wcscmp(nTexto._Texto, _Texto);
		if (Comp == 0) return true;
		return false;
	}

	#if COMPILADOR == COMPILADOR_VC6
		#define swprintf_s(BUFFER, TAM, FORMATO, NUMERO) swprintf(BUFFER, FORMATO, NUMERO);
	#endif

	const UINT DWLString_wchar_t::AgregarEntero(const int nNumero, const UINT NumEnteros) {
		wchar_t Formato[2048];
		switch (NumEnteros) {
			case 0  : swprintf_s(Formato, 2048, TEXT("%d"), nNumero);	break;
			case 1  : swprintf_s(Formato, 2048, TEXT("%01d"), nNumero);	break;
			case 2  : swprintf_s(Formato, 2048, TEXT("%02d"), nNumero);	break;
			case 3  : swprintf_s(Formato, 2048, TEXT("%03d"), nNumero);	break;
			case 4  : swprintf_s(Formato, 2048, TEXT("%04d"), nNumero);	break;
			case 5  : swprintf_s(Formato, 2048, TEXT("%05d"), nNumero);	break;
			case 6  : swprintf_s(Formato, 2048, TEXT("%06d"), nNumero);	break;
			case 7  : swprintf_s(Formato, 2048, TEXT("%07d"), nNumero);	break;
			case 8  : swprintf_s(Formato, 2048, TEXT("%08d"), nNumero);	break;
			case 9  : swprintf_s(Formato, 2048, TEXT("%09d"), nNumero);	break;
			case 10 : swprintf_s(Formato, 2048, TEXT("%010d"), nNumero);	break;
		}
		return AgregarTexto(Formato);
	}

	const UINT DWLString_wchar_t::AgregarEntero(const UINT nNumero, const UINT NumEnteros) {
		wchar_t Formato[2048];
		switch (NumEnteros) {
			case 0  : swprintf_s(Formato, 2048, TEXT("%d"), nNumero);	break;
			case 1  : swprintf_s(Formato, 2048, TEXT("%01d"), nNumero);	break;
			case 2  : swprintf_s(Formato, 2048, TEXT("%02d"), nNumero);	break;
			case 3  : swprintf_s(Formato, 2048, TEXT("%03d"), nNumero);	break;
			case 4  : swprintf_s(Formato, 2048, TEXT("%04d"), nNumero);	break;
			case 5  : swprintf_s(Formato, 2048, TEXT("%05d"), nNumero);	break;
			case 6  : swprintf_s(Formato, 2048, TEXT("%06d"), nNumero);	break;
			case 7  : swprintf_s(Formato, 2048, TEXT("%07d"), nNumero);	break;
			case 8  : swprintf_s(Formato, 2048, TEXT("%08d"), nNumero);	break;
			case 9  : swprintf_s(Formato, 2048, TEXT("%09d"), nNumero);	break;
			case 10 : swprintf_s(Formato, 2048, TEXT("%010d"), nNumero);	break;
		}
		return AgregarTexto(Formato);
	}

	const UINT DWLString_wchar_t::AgregarEntero(const long nNumero, const UINT NumEnteros) {
		wchar_t Formato[2048];
		switch (NumEnteros) {
			case 0  : swprintf_s(Formato, 2048, TEXT("%d"), nNumero);	break;
			case 1  : swprintf_s(Formato, 2048, TEXT("%01d"), nNumero);	break;
			case 2  : swprintf_s(Formato, 2048, TEXT("%02d"), nNumero);	break;
			case 3  : swprintf_s(Formato, 2048, TEXT("%03d"), nNumero);	break;
			case 4  : swprintf_s(Formato, 2048, TEXT("%04d"), nNumero);	break;
			case 5  : swprintf_s(Formato, 2048, TEXT("%05d"), nNumero);	break;
			case 6  : swprintf_s(Formato, 2048, TEXT("%06d"), nNumero);	break;
			case 7  : swprintf_s(Formato, 2048, TEXT("%07d"), nNumero);	break;
			case 8  : swprintf_s(Formato, 2048, TEXT("%08d"), nNumero);	break;
			case 9  : swprintf_s(Formato, 2048, TEXT("%09d"), nNumero);	break;
			case 10 : swprintf_s(Formato, 2048, TEXT("%010d"), nNumero);	break;
		}
		return AgregarTexto(Formato);
	}

	const UINT DWLString_wchar_t::AgregarEntero(const ULONG nNumero, const UINT NumEnteros) {
		wchar_t Formato[2048];
		switch (NumEnteros) {
			case 0  : swprintf_s(Formato, 2048, TEXT("%d"), nNumero);	break;
			case 1  : swprintf_s(Formato, 2048, TEXT("%01d"), nNumero);	break;
			case 2  : swprintf_s(Formato, 2048, TEXT("%02d"), nNumero);	break;
			case 3  : swprintf_s(Formato, 2048, TEXT("%03d"), nNumero);	break;
			case 4  : swprintf_s(Formato, 2048, TEXT("%04d"), nNumero);	break;
			case 5  : swprintf_s(Formato, 2048, TEXT("%05d"), nNumero);	break;
			case 6  : swprintf_s(Formato, 2048, TEXT("%06d"), nNumero);	break;
			case 7  : swprintf_s(Formato, 2048, TEXT("%07d"), nNumero);	break;
			case 8  : swprintf_s(Formato, 2048, TEXT("%08d"), nNumero);	break;
			case 9  : swprintf_s(Formato, 2048, TEXT("%09d"), nNumero);	break;
			case 10 : swprintf_s(Formato, 2048, TEXT("%010d"), nNumero);	break;
		}
		return AgregarTexto(Formato);
	}

	const UINT DWLString_wchar_t::AgregarDecimal(const double nDecimal, const UINT NumDecimales) {
		wchar_t Formato[2048];
		switch (NumDecimales) {
			case 0  : swprintf_s(Formato, 2048, TEXT("%f"), nDecimal);		break;
			case 1  : swprintf_s(Formato, 2048, TEXT("%0.1f"), nDecimal);	break;
			case 2  : swprintf_s(Formato, 2048, TEXT("%0.2f"), nDecimal);	break;
			case 3  : swprintf_s(Formato, 2048, TEXT("%0.3f"), nDecimal);	break;
			case 4  : swprintf_s(Formato, 2048, TEXT("%0.4f"), nDecimal);	break;
			case 5  : swprintf_s(Formato, 2048, TEXT("%0.5f"), nDecimal);	break;
			case 6  : swprintf_s(Formato, 2048, TEXT("%0.6f"), nDecimal);	break;
			case 7  : swprintf_s(Formato, 2048, TEXT("%0.7f"), nDecimal);	break;
			case 8  : swprintf_s(Formato, 2048, TEXT("%0.8f"), nDecimal);	break;
			case 9  : swprintf_s(Formato, 2048, TEXT("%0.9f"), nDecimal);	break;
			case 10 : swprintf_s(Formato, 2048, TEXT("%0.10f"), nDecimal);	break;
		}
		return AgregarTexto(Formato);
	}

	const UINT DWLString_wchar_t::AgregarDecimal(const float nDecimal, const UINT NumDecimales) {
		wchar_t Formato[2048];
		switch (NumDecimales) {
			case 0  : swprintf_s(Formato, 2048, TEXT("%f"), nDecimal);		break;
			case 1  : swprintf_s(Formato, 2048, TEXT("%0.1f"), nDecimal);	break;
			case 2  : swprintf_s(Formato, 2048, TEXT("%0.2f"), nDecimal);	break;
			case 3  : swprintf_s(Formato, 2048, TEXT("%0.3f"), nDecimal);	break;
			case 4  : swprintf_s(Formato, 2048, TEXT("%0.4f"), nDecimal);	break;
			case 5  : swprintf_s(Formato, 2048, TEXT("%0.5f"), nDecimal);	break;
			case 6  : swprintf_s(Formato, 2048, TEXT("%0.6f"), nDecimal);	break;
			case 7  : swprintf_s(Formato, 2048, TEXT("%0.7f"), nDecimal);	break;
			case 8  : swprintf_s(Formato, 2048, TEXT("%0.8f"), nDecimal);	break;
			case 9  : swprintf_s(Formato, 2048, TEXT("%0.9f"), nDecimal);	break;
			case 10 : swprintf_s(Formato, 2048, TEXT("%0.10f"), nDecimal);	break;
		}
		return AgregarTexto(Formato);
	}

	DWLString_wchar_t DWLString_wchar_t::SubStr(const UINT PosInicio, const UINT Tam) {
		DWLString_wchar_t Ret;
		Ret.AgregarTexto(&_Texto[PosInicio], Tam);
		return Ret;
	}

	DWLString_wchar_t *DWLString_wchar_t::SubStrPtr(const UINT PosInicio, const UINT Tam) {
		DWLString_wchar_t *Ret = new DWLString_wchar_t;
		Ret->AgregarTexto(&_Texto[PosInicio], Tam);
		return Ret;
	}

	DWLString_char DWLString_wchar_t::Char(const UINT PosInicio, const UINT Tam) {
		DWLString_char Ret(&_Texto[PosInicio], Tam);
		return Ret;
	}

	DWLString_char *DWLString_wchar_t::CharPtr(const UINT PosInicio, const UINT Tam) {
		DWLString_char *Ret = new DWLString_char(&_Texto[PosInicio], Tam);
		return Ret;
	}

	const int DWLString_wchar_t::sprintf(const wchar_t *Txt, ...) {
		va_list     Marker;
		va_start(Marker, Txt);
		#if COMPILADOR == COMPILADOR_VC6
			wchar_t Buffer[4096 * 2];
			int len = vswprintf(Buffer, Txt, Marker);
			if (len < 1) {
				va_end(Marker);
				return 0;
			}
			Borrar();
			AgregarTexto(Buffer, len);
			return len;
		#else
			int len = _vscwprintf( Txt, Marker ) + 1;
			if (len < 1) {
				va_end(Marker);
				return 0;
			}
			wchar_t *T = new wchar_t [len];
			vswprintf_s(T, len, Txt, Marker);
			va_end(Marker);
			Borrar();
			AgregarTexto(T);
			delete [] T;
			return len;
		#endif
	}




};

#endif
