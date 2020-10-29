#ifndef DWL_STRING_CHAR_CPP
#define DWL_STRING_CHAR_CPP
 
#include "DWLString_char.h"
#include "DWLString_wchar_t.h"
#include "..\DWL.h"
#include <stdio.h>
#include <wchar.h>

namespace DWL {
	DWLString_char::DWLString_char(const DWL::DWLString_wchar_t &nTexto) : _Tam(0), _Texto(NULL) {
		AgregarTexto(nTexto);			
	};


	void DWLString_char::Borrar(void) { 	
		if (_Tam != 0 && _Texto != NULL) delete [] _Texto;
		_Tam = 0;
		_Texto = NULL;
	};


	void DWLString_char::AgregarCaracter(const wchar_t nTexto) {
		char     *TextoFinal = new char [_Tam + 2];
		UINT TamFinal = _Tam + 1;
		UINT i = 0;
		for (i = 0; i < _Tam; i++)	TextoFinal[i] = _Texto[i];
		char NuevoTexto[2];
		wchar_t NuevoTextoW[2];
		NuevoTextoW[0] = nTexto; NuevoTextoW[1] = 0;
		WideCharToMultiByte(CP_ACP, WC_DEFAULTCHAR, NuevoTextoW, 2, NuevoTexto, 2, NULL, NULL);
		TextoFinal[TamFinal -1] = NuevoTexto[0];
		TextoFinal[TamFinal] = 0;
		Borrar();
		_Texto = TextoFinal;
		_Tam = TamFinal;
	}

	void DWLString_char::AgregarCaracter(const char nTexto) {
		char     *TextoFinal = new char [_Tam + 2];
		UINT TamFinal = _Tam + 1;
		UINT i = 0;
		for (i = 0; i < _Tam; i++)	TextoFinal[i] = _Texto[i];
		TextoFinal[TamFinal -1] = nTexto;
		TextoFinal[TamFinal] = 0;
		Borrar();
		_Texto = TextoFinal;
		_Tam = TamFinal;
	}

	const UINT DWLString_char::AgregarTexto(const DWL::DWLString_wchar_t &nTexto)  {
		if (nTexto._Tam == 0) return 0;
		UINT TamFinal = _Tam;
		UINT TamnTexto = nTexto._Tam;
		TamFinal += nTexto._Tam;
		char *TextoFinal = new char [TamFinal + 1];
		UINT i = 0;
		for (i = 0; i < _Tam; i++)	TextoFinal[i] = _Texto[i];
		char *Destino = new char [TamnTexto + 1];
		WideCharToMultiByte(CP_ACP, WC_DEFAULTCHAR, nTexto._Texto, TamnTexto + 1, Destino, TamnTexto + 1, NULL, NULL);
		for (i = 0; i < (TamFinal - _Tam); i++) TextoFinal[i + _Tam]	= Destino[i];
		Borrar();
		TextoFinal[TamFinal] = 0;
		_Tam = TamFinal;
		_Texto = TextoFinal;
		delete [] Destino;
		return nTexto._Tam;
	}

	const UINT DWLString_char::AgregarTexto(const wchar_t *nTexto, const int nTam) {
		if (nTexto == NULL) return 0;
		UINT TamFinal = _Tam;
		UINT TamnTexto = 0;
		if (nTam == -1) TamnTexto = wcslen(nTexto);
		else			TamnTexto = nTam;
		TamFinal += TamnTexto;
		char *TextoFinal = new char [TamFinal + 1];
		UINT i = 0;
		for (i = 0; i < _Tam; i++)	TextoFinal[i] = _Texto[i];
		char *Destino = new char [TamnTexto + 1];
		WideCharToMultiByte(CP_ACP, 0, nTexto, TamnTexto + 1, Destino, TamnTexto + 1, NULL, NULL);
		for (i = 0; i < (TamFinal - _Tam); i++) TextoFinal[i + _Tam]	= Destino[i];
		Borrar();
		TextoFinal[TamFinal] = 0;
		_Tam = TamFinal;
		_Texto = TextoFinal;
		delete [] Destino;
		return TamnTexto;
	}

	const UINT DWLString_char::AgregarTexto(const DWL::DWLString_char &nTexto)  {
		if (nTexto._Tam == 0) return 0;
		UINT TamFinal = _Tam;
		TamFinal += nTexto._Tam;
		char *TextoFinal = new char [TamFinal +1];
		UINT i = 0;
		for (i = 0; i < _Tam; i++)				TextoFinal[i]			= _Texto[i];
		for (i = 0; i < (TamFinal - _Tam); i++) TextoFinal[i + _Tam]	= nTexto._Texto[i];
		Borrar();
		TextoFinal[TamFinal] = 0;
		_Tam = TamFinal;
		_Texto = TextoFinal;
		return nTexto._Tam;
	}

	const UINT DWLString_char::AgregarTexto(const char *nTexto, const int nTam)  {
		if (nTexto == NULL) return 0;
		UINT TamFinal = _Tam;
		if (nTam == -1) TamFinal += strlen(nTexto);
		else			TamFinal += nTam;
		char *TextoFinal = new char [TamFinal +1];
		UINT i = 0;
		for (i = 0; i < _Tam; i++)				TextoFinal[i]			= _Texto[i];
		for (i = 0; i < (TamFinal - _Tam); i++) TextoFinal[i + _Tam]	= nTexto[i];
		Borrar();
		TextoFinal[TamFinal] = 0;
		_Tam = TamFinal;
		_Texto = TextoFinal;
		return TamFinal - _Tam;
	}


	const bool DWLString_char::EsNumero(void) {
		if (_Tam == 0) return false;
		for (unsigned int i = 0; i < _Tam; i++) {
			switch (_Texto[i]) {
				case '0' :	case '1' :	case '2' :	case '3' :	case '4' :
				case '5' :	case '6' :	case '7' :	case '8' :	case '9' :
				case '\0':	case '.' :	case ',' :
					break;
				default :
					return false;
			}
		}
		return true;
	}

	const bool DWLString_char::EsNumeroEntero(void) {
		if (_Tam == 0) return false;
		for (unsigned int i = 0; i < _Tam; i++) {
			switch (_Texto[i]) {
				case '0' :	case '1' :	case '2' :	case '3' :	case '4' :
				case '5' :	case '6' :	case '7' :	case '8' :	case '9' :
				case '\0':
					break;
				default :
					return false;
			}
		}
		return true;
	}

	const bool DWLString_char::EsNumeroDecimal(void) {
		bool Decimal = false;
		if (_Tam == 0) return false;
		for (unsigned int i = 0; i < _Tam; i++) {
			switch (_Texto[i]) {
				case '0' :	case '1' :	case '2' :	case '3' :	case '4' :
				case '5' :	case '6' :	case '7' :	case '8' :	case '9' :
				case '\0':
					break;
				case '.' :	case ',' :
					Decimal = true;
					break;
				default :
					return false;
			}
		}
		return Decimal;
	}


	const bool DWLString_char::Comparar(const char *nTexto, const bool ComparacionBinaria) {
		int Comp;
        if (_Texto == NULL) {
            if (nTexto == NULL) return true;
            else                return false;
        }
		if (ComparacionBinaria == false)	Comp = _strcmpi(nTexto, _Texto);
		else								Comp = strcmp(nTexto, _Texto);
		if (Comp == 0) return true;
		return false;
	}

	const bool DWLString_char::Comparar(DWL::DWLString_char &nTexto, const bool ComparacionBinaria) {
		int Comp;
        if (_Texto == NULL) {
			if (nTexto._Tam == 0)	return true;
            else					return false;
        }
		if (ComparacionBinaria == false)	Comp = _strcmpi(nTexto._Texto, _Texto);
		else								Comp = strcmp(nTexto._Texto, _Texto);
		if (Comp == 0) return true;
		return false;
	}

	const bool DWLString_char::Comparar(const wchar_t *nTexto, const bool ComparacionBinaria) {
		UINT TamnTexto = wcslen(nTexto) + 1;
		char *Destino = new char [TamnTexto];
		WideCharToMultiByte(CP_ACP, WC_DEFAULTCHAR, nTexto, TamnTexto, Destino, TamnTexto, NULL, NULL);

		int Comp = 0;
        if (_Texto == NULL) {
            if (nTexto == NULL) return true;
            else                return false;
        }
		if (ComparacionBinaria == false)	Comp = _strcmpi(Destino, _Texto);
		else								Comp = strcmp(Destino, _Texto);
		delete [] Destino;
		if (Comp == 0) return true;
		return false;
	}

	const bool DWLString_char::Comparar(DWL::DWLString_wchar_t &nTexto, const bool ComparacionBinaria) {
		UINT TamnTexto = nTexto._Tam + 1;
		char *Destino = new char [TamnTexto];
		WideCharToMultiByte(CP_ACP, WC_DEFAULTCHAR, nTexto(), TamnTexto, Destino, TamnTexto, NULL, NULL);
		int Comp;
        if (_Texto == NULL) {
			if (nTexto._Tam == 0)	return true;
            else					return false;
        }
		if (ComparacionBinaria == false)	Comp = _strcmpi(Destino, _Texto);
		else								Comp = strcmp(Destino, _Texto);
		delete [] Destino;
		if (Comp == 0) return true;
		return false;
	}


	#if COMPILADOR == COMPILADOR_VC6
		#define sprintf_s(BUFFER, TAM, FORMATO, NUMERO) sprintf(BUFFER, FORMATO, NUMERO);
	#endif

	const UINT DWLString_char::AgregarEntero(const int nNumero, const UINT NumEnteros) {
		char Formato[2048];
		switch (NumEnteros) {
			case 0  : sprintf_s(Formato, 2048, "%d", nNumero);		 break;
			case 1  : sprintf_s(Formato, 2048, "%01d", nNumero);	 break;
			case 2  : sprintf_s(Formato, 2048, "%02d", nNumero);	 break;
			case 3  : sprintf_s(Formato, 2048, "%03d", nNumero);	 break;
			case 4  : sprintf_s(Formato, 2048, "%04d", nNumero);	 break;
			case 5  : sprintf_s(Formato, 2048, "%05d", nNumero);	 break;
			case 6  : sprintf_s(Formato, 2048, "%06d", nNumero);	 break;
			case 7  : sprintf_s(Formato, 2048, "%07d", nNumero);	 break;
			case 8  : sprintf_s(Formato, 2048, "%08d", nNumero);	 break;
			case 9  : sprintf_s(Formato, 2048, "%09d", nNumero);	 break;
			case 10 : sprintf_s(Formato, 2048, "%010d", nNumero);	 break;
		}
		return AgregarTexto(Formato);
	}

	const UINT DWLString_char::AgregarEntero(const UINT nNumero, const UINT NumEnteros) {
		char Formato[2048];
		switch (NumEnteros) {
			case 0  : sprintf_s(Formato, 2048, "%d", nNumero); 		 break;
			case 1  : sprintf_s(Formato, 2048, "%01d", nNumero);	 break;
			case 2  : sprintf_s(Formato, 2048, "%02d", nNumero);	 break;
			case 3  : sprintf_s(Formato, 2048, "%03d", nNumero);	 break;
			case 4  : sprintf_s(Formato, 2048, "%04d", nNumero);	 break;
			case 5  : sprintf_s(Formato, 2048, "%05d", nNumero);	 break;
			case 6  : sprintf_s(Formato, 2048, "%06d", nNumero);	 break;
			case 7  : sprintf_s(Formato, 2048, "%07d", nNumero);	 break;
			case 8  : sprintf_s(Formato, 2048, "%08d", nNumero);	 break;
			case 9  : sprintf_s(Formato, 2048, "%09d", nNumero);	 break;
			case 10 : sprintf_s(Formato, 2048, "%010d", nNumero);	 break;
		}
		return AgregarTexto(Formato);
	}

	const UINT DWLString_char::AgregarEntero(const long nNumero, const UINT NumEnteros) {
		char Formato[2048];
		switch (NumEnteros) {
			case 0  : sprintf_s(Formato, 2048, "%d", nNumero);	     break;
			case 1  : sprintf_s(Formato, 2048, "%01d", nNumero);	 break;
			case 2  : sprintf_s(Formato, 2048, "%02d", nNumero);	 break;
			case 3  : sprintf_s(Formato, 2048, "%03d", nNumero);	 break;
			case 4  : sprintf_s(Formato, 2048, "%04d", nNumero);	 break;
			case 5  : sprintf_s(Formato, 2048, "%05d", nNumero);	 break;
			case 6  : sprintf_s(Formato, 2048, "%06d", nNumero);	 break;
			case 7  : sprintf_s(Formato, 2048, "%07d", nNumero);	 break;
			case 8  : sprintf_s(Formato, 2048, "%08d", nNumero);	 break;
			case 9  : sprintf_s(Formato, 2048, "%09d", nNumero);	 break;
			case 10 : sprintf_s(Formato, 2048, "%010d", nNumero);    break;
		}
		return AgregarTexto(Formato);
	}

	const UINT DWLString_char::AgregarEntero(const ULONG nNumero, const UINT NumEnteros) {
		char Formato[2048];
		switch (NumEnteros) {
			case 0  : sprintf_s(Formato, 2048, "%d", nNumero);	 break;
			case 1  : sprintf_s(Formato, 2048, "%01d", nNumero);	 break;
			case 2  : sprintf_s(Formato, 2048, "%02d", nNumero);	 break;
			case 3  : sprintf_s(Formato, 2048, "%03d", nNumero);	 break;
			case 4  : sprintf_s(Formato, 2048, "%04d", nNumero);	 break;
			case 5  : sprintf_s(Formato, 2048, "%05d", nNumero);	 break;
			case 6  : sprintf_s(Formato, 2048, "%06d", nNumero);	 break;
			case 7  : sprintf_s(Formato, 2048, "%07d", nNumero);	 break;
			case 8  : sprintf_s(Formato, 2048, "%08d", nNumero);	 break;
			case 9  : sprintf_s(Formato, 2048, "%09d", nNumero);	 break;
			case 10 : sprintf_s(Formato, 2048, "%010d", nNumero); break;
		}
		return AgregarTexto(Formato);
	}

	const UINT DWLString_char::AgregarDecimal(const double nDecimal, const UINT NumDecimales) {
		char Formato[2048];
		switch (NumDecimales) {
			case 0  : sprintf_s(Formato, 2048, "%f", nDecimal);		break;
			case 1  : sprintf_s(Formato, 2048, "%0.1f", nDecimal);	break;
			case 2  : sprintf_s(Formato, 2048, "%0.2f", nDecimal);	break;
			case 3  : sprintf_s(Formato, 2048, "%0.3f", nDecimal);	break;
			case 4  : sprintf_s(Formato, 2048, "%0.4f", nDecimal);	break;
			case 5  : sprintf_s(Formato, 2048, "%0.5f", nDecimal);	break;
			case 6  : sprintf_s(Formato, 2048, "%0.6f", nDecimal);	break;
			case 7  : sprintf_s(Formato, 2048, "%0.7f", nDecimal);	break;
			case 8  : sprintf_s(Formato, 2048, "%0.8f", nDecimal);	break;
			case 9  : sprintf_s(Formato, 2048, "%0.9f", nDecimal);	break;
			case 10 : sprintf_s(Formato, 2048, "%0.10f", nDecimal);	break;
		}
		return AgregarTexto(Formato);
	}

	const UINT DWLString_char::AgregarDecimal(const float nDecimal, const UINT NumDecimales) {
		char Formato[2048];
		switch (NumDecimales) {
			case 0  : sprintf_s(Formato, 2048, "%f", nDecimal);		break;
			case 1  : sprintf_s(Formato, 2048, "%0.1f", nDecimal);	break;
			case 2  : sprintf_s(Formato, 2048, "%0.2f", nDecimal);	break;
			case 3  : sprintf_s(Formato, 2048, "%0.3f", nDecimal);	break;
			case 4  : sprintf_s(Formato, 2048, "%0.4f", nDecimal);	break;
			case 5  : sprintf_s(Formato, 2048, "%0.5f", nDecimal);	break;
			case 6  : sprintf_s(Formato, 2048, "%0.6f", nDecimal);	break;
			case 7  : sprintf_s(Formato, 2048, "%0.7f", nDecimal);	break;
			case 8  : sprintf_s(Formato, 2048, "%0.8f", nDecimal);	break;
			case 9  : sprintf_s(Formato, 2048, "%0.9f", nDecimal);	break;
			case 10 : sprintf_s(Formato, 2048, "%0.10f", nDecimal);	break;
		}
		return AgregarTexto(Formato);
	}

	DWLString_char DWLString_char::SubStr(const UINT PosInicio, const UINT Tam) {
		DWLString_char Ret;
		Ret.AgregarTexto(&_Texto[PosInicio], Tam);
		return Ret;
	}

	DWLString_char *DWLString_char::SubStrPtr(const UINT PosInicio, const UINT Tam) {
		DWLString_char *Ret = new DWLString_char;
		Ret->AgregarTexto(&_Texto[PosInicio], Tam);
		return Ret;
	}

	DWLString_wchar_t DWLString_char::WChar(const UINT PosInicio, const UINT Tam) {
		DWLString_wchar_t Ret(&_Texto[PosInicio], Tam);
		return Ret;
	}

	DWLString_wchar_t *DWLString_char::WCharPtr(const UINT PosInicio, const UINT Tam) {
		DWLString_wchar_t *Ret = new DWLString_wchar_t(&_Texto[PosInicio], Tam);
		return Ret;
	}

	const int DWLString_char::sprintf(const char *Txt, ...) {
		va_list     Marker;
		va_start(Marker, Txt);
		#if COMPILADOR == COMPILADOR_VC6
			char Buffer[4096 * 2];
			int len = vsprintf(Buffer, Txt, Marker);
			if (len < 1) {
				va_end(Marker);
				return 0;
			}
			Borrar();
			AgregarTexto(Buffer, len);
			return len;
		#else
			int len = _vscprintf( Txt, Marker ) + 1;
			if (len < 1) {
				va_end(Marker);
				return 0;
			}
			char *T = new char [len];
			vsprintf_s(T, len, Txt, Marker);
			va_end(Marker);
			Borrar();
			AgregarTexto(T, len);
			delete [] T;
			return len;
		#endif
	}


};

#endif
