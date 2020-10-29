#include "DWLString.h"
#include <stdio.h>
//#include <strsafe.h>
//#include "DWLVisualC6.h"

namespace DWL {

	/*
	//
	// Constructor por defecto que inicia los valores a 0
	DWLString::DWLString(void) {
		_Tam = 0;
		_Texto = NULL;
	} 
	//
	// Constructor que crea el string a partir de una clase DWLString
//#if (COMPILADOR != COMPILADOR_VC6)
	DWLString::DWLString(const DWL::DWLString &nTexto) {
		_Tam = 0;
		_Texto = NULL;
		CopiarTexto(nTexto._Texto, nTexto._Tam);
	}
//#endif

	//
	// Destructor que llama a la Función para borrar de memoria el string
	DWLString::~DWLString(void) {
		Borrar();
	}

	//
	// Función que borra de la memoria el texto
	void DWLString::Borrar(void) {
	   if (_Tam != 0 && _Texto != NULL) delete [] _Texto;
	   _Tam = 0;
	   _Texto = NULL;
	};

	//
	// Función para construir un texto al estilo sprintf
	void DWLString::sprintf(const TCHAR *Txt, ...) {
		TCHAR       T[1024];
		va_list     Marker;
		va_start(Marker, Txt);
        DWLvsPrintf(T, 1024, Txt, Marker);
		va_end(Marker);
		CopiarTexto(T);
	}

	int DWLString::NumeroEntero(void) {
		return DWLStrToInt(_Texto);
	}

	//
	// Función que retorna una parte de la cadena de esta clase
	DWLString DWLString::SubStr(const UINT PosInicio, const UINT Tam) {
		DWLString Ret;
		Ret.CopiarTexto(&_Texto[PosInicio], Tam);
		return Ret;
	}

	//
	// Función que retorna una parte de la cadena de esta clase
	DWLString *DWLString::SubStrPtr(const UINT PosInicio, const UINT Tam) {
		DWLString *Ret = new DWLString;
		Ret->CopiarTexto(&_Texto[PosInicio], Tam);
		return Ret;
	}

	//
	// Función que retorna el total de lineas que tiene esta cadena
	UINT DWLString::TotalLineas(void) {
		unsigned int Ret = 1;
		for (unsigned int z = 0; z < _Tam; z++) {
			if (_Texto[z] == TEXT('\n')) Ret ++;
		}
		return Ret;
	}

	//
	// Función que concatena los TCHAR * introducidos
	void DWLString::Concatenar(const UINT NumTCHARs, ...) {
		va_list Lista;
		va_start(Lista, NumTCHARs);
		for (UINT i = 0; i < NumTCHARs; i++) this->operator+= (va_arg(Lista, TCHAR *));
		va_end(Lista);
	}

	//
	// Función que retorna la linea especificada dentro del texto
	// Objetivos :
	//				Poder separar mas comodamente una cadena por lineas
	// NOTA :
	//				Si introduces una linea que se salga del rango, la función retornara una cadena vacia
	DWLString DWLString::Linea(const unsigned int NumLinea) {
		int InicioLinea = -1;
		int FinalLinea = -1;
		if (NumLinea == 0) InicioLinea = 0;
		unsigned int NL = 0;
		for (unsigned int z = 0; z < _Tam; z++) {
			if (_Texto[z] == TEXT('\n')) {
				NL ++;
				if (NumLinea <= NL) {
					if (InicioLinea == -1) {
						InicioLinea = z;
					}
					else {
						FinalLinea = z;
						break;
					}
				}
			}
			else if (_Texto[z] == 0) {
				if (InicioLinea == -1) InicioLinea = z;
				if (FinalLinea == -1)  FinalLinea = z;
				break;
			}
		}
		if (FinalLinea == -1) {
			if (InicioLinea != -1)	FinalLinea = _Tam;
			else					FinalLinea = 0;
		}
		if (InicioLinea != 0) InicioLinea ++; // Si no es la primera linea quitamos el intro (o si pasa del final y es -1, la ponemos a 0 para retornar toda la cadena)
		DWLString Ret;
		Ret.AgregarTexto(&_Texto[InicioLinea], FinalLinea - InicioLinea);
		return Ret;
	}

	//
	// Función que comprueba si el texto es un numero entero o decimal
	// Objetivos :
	//				Determinar si el texto son todo numeros, o existe algun caracter el cual hace el texto un numero valido.
	// NOTA :
	//				Tanto un numero entero como un numero decimal retornaran un resultado positivo
	//				Si la cadena contiene espacios ya no sera considerada como un numero
	bool DWLString::EsNumero(void) {
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

	//
	// Función que comprueba si el texto es un numero entero
	// Objetivos :
	//				Determinar si el texto son todo numeros, o existe algun caracter el cual hace el texto un numero valido.
	// NOTA :
	//				Si la cadena contiene espacios ya no sera considerada como un numero entero
	bool DWLString::EsNumeroEntero(void) {
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

	//
	// Función que comprueba si el texto es un numero decimal
	//
	// Objetivos :
	//				Determinar si el texto son todo numeros y simbolos de puntuacion, o existe algun caracter el cual
	//				hace el texto no sea un numero decimal valido.
	// NOTA :
	//				Los numeros enteros nunca seran considerados decimales
	//				Si la cadena contiene espacios ya no sera considerada como un numero decimal
	bool DWLString::EsNumeroDecimal(void) {
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

	//
	// Función para agregar un caracter al final de la cadena
	void DWLString::AgregarCaracter(const TCHAR nTexto) {
		TCHAR       *TextoFinal = new TCHAR [_Tam + 2];
		unsigned int TamFinal = _Tam + 1;
		unsigned int i = 0;
		for (i = 0; i < _Tam; i++)	TextoFinal[i] = _Texto[i];
		for (i = 0; i < _Tam; i++)	TextoFinal[i] = _Texto[i];
		TextoFinal[TamFinal -1] = nTexto;
		TextoFinal[TamFinal] = 0;
		Borrar();
		_Texto = TextoFinal;
		_Tam = TamFinal;
	}

	//
	// Función para agregar un texto wchar_t a la clase sin importar si es ANSI o UNICODE
	//
	// Objetivos :
	//				Esta Función ademas de agregar texto a la cadena, lo transforma si es necesario a ANSI o UNICODE
	//				dependiendo de la plataforma con la que estemos trabajando.
	//				Es decir, si estamos trabajando en ANSI, la Función pasara el texto directamente a ANSI.
	// NOTA :
	//				Cualquier texto se mantendra, y el nuevo texto se colocara detras
	void DWLString::AgregarTexto(const wchar_t *nTexto, const int nTam) {
		if (nTexto == NULL) return;
		#if defined UNICODE
			unsigned int TamFinal = _Tam;
			if (nTam == -1) TamFinal += wcslen(nTexto);
			else			TamFinal += nTam;
			wchar_t *TextoFinal = new wchar_t [TamFinal +1];
			unsigned int i = 0;
			for (i = 0; i < _Tam; i++)				TextoFinal[i]			= _Texto[i];
			for (i = 0; i < (TamFinal - _Tam); i++) TextoFinal[i + _Tam]	= nTexto[i];
			Borrar();
			TextoFinal[TamFinal] = 0;
			_Tam = TamFinal;
			_Texto = TextoFinal;
		#else
			unsigned int TamFinal = _Tam;
			unsigned int TamnTexto = wcslen(nTexto);
			if (nTam == -1) TamFinal += TamnTexto;
			else			TamFinal += nTam;
			char *TextoFinal = new char [TamFinal +1];
			unsigned int i = 0;
			for (i = 0; i < _Tam; i++)				TextoFinal[i]			= _Texto[i];
			char Destino[2048];
			WideCharToMultiByte(CP_ACP, WC_DEFAULTCHAR, nTexto, TamnTexto, Destino, 2048, NULL, NULL);
			for (i = 0; i < (TamFinal - _Tam); i++) TextoFinal[i + _Tam]	= Destino[i];
			Borrar();
			TextoFinal[TamFinal] = 0;
			_Tam = TamFinal;
			_Texto = TextoFinal;
		#endif
	};

	//
	// Función para agregar un texto char a la clase sin importar si es ANSI o UNICODE
	//
	// Objetivos :
	//				Esta Función ademas de agregar texto a la cadena, lo transforma si es necesario a ANSI o UNICODE
	//				dependiendo de la plataforma con la que estemos trabajando.
	//				Es decir, si estamos trabajando en UNICODE, la Función pasara el texto directamente a UNICODE.
	//				En ANSI no se necesita conversion, asi que solo se añadira el texto tal cual.
	// NOTA :
	//				Cualquier texto se mantendra, y el nuevo texto se colocara detras
	void DWLString::AgregarTexto(const char *nTexto, const int nTam) {
		if (nTexto == NULL) return;
		#if defined UNICODE
			unsigned int TamFinal = _Tam;
			unsigned int TamnTexto = strlen(nTexto);
			if (nTam == -1) TamFinal += TamnTexto;
			else			TamFinal += nTam;
			wchar_t *TextoFinal = new wchar_t [TamFinal +1];
			unsigned int i = 0;
			for (i = 0; i < _Tam; i++)				TextoFinal[i]			= _Texto[i];
			wchar_t Destino[2048];
			MultiByteToWideChar(CP_OEMCP, MB_PRECOMPOSED, nTexto, TamnTexto, Destino, 2048);
			for (i = 0; i < (TamFinal - _Tam); i++) TextoFinal[i + _Tam]	= Destino[i];
			Borrar();
			TextoFinal[TamFinal] = 0;
			_Tam = TamFinal;
			_Texto = TextoFinal;
		#else
			unsigned int TamFinal = _Tam;
			if (nTam == -1) TamFinal += strlen(nTexto);
			else			TamFinal += nTam;
			char *TextoFinal = new char [TamFinal +1];
			unsigned int i = 0;
			for (i = 0; i < _Tam; i++)				TextoFinal[i]			= _Texto[i];
			for (i = 0; i < (TamFinal - _Tam); i++) TextoFinal[i + _Tam]	= nTexto[i];
			Borrar();
			TextoFinal[TamFinal] = 0;
			_Tam = TamFinal;
			_Texto = TextoFinal;
		#endif
	};

	//
	// Función para copiar un texto wchar_t a la clase sin importar si es ANSI o UNICODE
	//
	// Objetivos :
	//				Esta Función ademas de agregar texto a la cadena, lo transforma si es necesario a ANSI o UNICODE
	//				dependiendo de la plataforma con la que estemos trabajando.
	//				Es decir, si estamos trabajando en ANSI, la Función pasara el texto directamente a ANSI.
	// NOTA :
	//				Cualquier texto anterior sera borrado
	void DWLString::CopiarTexto(const wchar_t *nTexto, const int nTam) {
		if (nTexto == NULL) return;
		#if defined UNICODE
			Borrar();
			if (nTam == -1) _Tam += wcslen(nTexto);
			else			_Tam += nTam;
			_Texto = new wchar_t [_Tam + 1];
//			StringCbCopy(_Texto, (_Tam + 1) * sizeof(wchar_t), nTexto);
			for (unsigned int i = 0; i < _Tam; i++)	{
				_Texto[i] = nTexto[i];
				if (nTexto[i] == 0) return;
			}
			_Texto[_Tam] = 0;
		#else
			Borrar();
			unsigned int TamnTexto = wcslen(nTexto);
			if (nTam == -1) _Tam += TamnTexto;
			else			_Tam += nTam;
			_Texto = new char [_Tam + 1];
			char Destino[2048];
			WideCharToMultiByte(CP_ACP, 0, nTexto, TamnTexto, Destino, 2048, NULL, NULL);
			for (unsigned int i = 0; i < _Tam; i++)	_Texto[i] = Destino[i];
			_Texto[_Tam] = 0;
		#endif
	};

	//
	// Función para copiar un texto char a la clase sin importar si es ANSI o UNICODE
	//
	// Objetivos :
	//				Esta Función ademas de agregar texto a la cadena, lo transforma si es necesario a ANSI o UNICODE
	//				dependiendo de la plataforma con la que estemos trabajando.
	//				Es decir, si estamos trabajando en UNICODE, la Función pasara el texto directamente a UNICODE.
	// NOTA :
	//				Cualquier texto anterior sera borrado, y las cadenas solo se copiaran hasta el caracter '\0' finalizador de string.
	void DWLString::CopiarTexto(const char *nTexto, const int nTam) {
		if (nTexto == NULL) return;
		#if defined UNICODE
			Borrar();
//			unsigned int TamnTexto = strlen(nTexto); // El strlen mira hasta que encuentra un caracter con valor 0
			if (nTam == -1) _Tam += strlen(nTexto);
			else			_Tam += nTam;
			_Texto = new wchar_t [_Tam + 1];
//			wchar_t Destino[2048];
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, nTexto, _Tam, _Texto, _Tam + 1);
//			for (unsigned int i = 0; i < _Tam; i++)	_Texto[i] = Destino[i];
			_Texto[_Tam] = 0;
		#else
			Borrar();
			if (nTam == -1) _Tam += strlen(nTexto);
			else			_Tam += nTam;
			_Texto = new char [_Tam + 1];
			for (unsigned int i = 0; i < _Tam; i++)	_Texto[i] = nTexto[i];
			_Texto[_Tam] = 0;
		#endif
	};

	//
	// Función para comparar un texto con el texto de la clase
	// Podemos usar una Enums::Comparacion_Binaria o una Enums::Comparacion_Texto. Por defencto esta puesta la comparacion de texto
	bool DWLString::Comparar(const TCHAR *nTexto, DWL_Enum_String_Comparar Comparacion) {
		int Comp;
        if (_Texto == NULL) {
            if (nTexto == NULL) return true;
            else                return false;
        }
		if (Comparacion == DWL_Enum_String_Comparar_Texto)	Comp = DWLStrCmpi(nTexto, _Texto);
		else												Comp = DWLStrCmp(nTexto, _Texto);
		if (Comp == 0) return true;
		return false;
	}

	//
	// Operador de copia para cadenas wchar_t
	DWLString &DWLString::operator = (const wchar_t *nTexto) {
		CopiarTexto(nTexto);
		return *this;
	}

	//
	// Operador de copia para cadenas char
	DWLString &DWLString::operator = (const char *nTexto) {
		CopiarTexto(nTexto);
		return *this;
	}

	//
	// Operador de copia para caracteres
	DWLString &DWLString::operator = (const TCHAR nTexto) {
		Borrar();
		_Texto = new TCHAR [2];
		_Texto[0] = nTexto;
		_Texto[1] = 0;
		_Tam = 1;
		return *this;
	}


	//
	// Operador de copia para clases DWLString
	DWLString &DWLString::operator = (DWLString nTexto) {
		CopiarTexto(nTexto._Texto, nTexto._Tam);
		return *this;
	}

	//
	// Operador de copia para el tipo int
	DWLString &DWLString::operator = (const int nTexto) {
		TCHAR Dest[512];
		DWLIntToText(static_cast<const int>(nTexto), Dest, 512, 10);
		CopiarTexto(Dest);
		return *this;
	}

	//
	// Operador de copia para el tipo unsigned int
	DWLString &DWLString::operator = (const unsigned int nTexto) {
		TCHAR Dest[512];
		DWLIntToText(static_cast<const int>(nTexto), Dest, 512, 10);
		CopiarTexto(Dest);
		return *this;
	}

	//
	// Operador de copia para el tipo long
	DWLString &DWLString::operator = (const long nTexto) {
		TCHAR Dest[512];
		DWLIntToText(static_cast<const int>(nTexto), Dest, 512, 10);
		CopiarTexto(Dest);
		return *this;
	}

	//
	// Operador de copia para el tipo unsigned long
	DWLString &DWLString::operator = (const unsigned long nTexto) {
		TCHAR Dest[512];
		DWLIntToText(static_cast<const int>(nTexto), Dest, 512, 10);
		CopiarTexto(Dest);
		return *this;
	}

	//
	// Operador de copia para el tipo float
	DWLString &DWLString::operator = (const float nTexto) {
		TCHAR Dest[512];
		sprintf(TEXT("%0.2f"), nTexto);
		CopiarTexto(Dest);
		return *this;
	}

	//
	// Operador para comparar esta clase con un TCHAR *
	bool DWLString::operator == (const TCHAR *nTexto) {
		return Comparar(nTexto);
	}

	//
	// Operador para comparar esta clase con otra clase DWLString
	bool DWLString::operator == (DWLString &nTexto) {
		return Comparar(nTexto());
	}

	//
	// Operador para comparar esta clase con un TCHAR *
	bool DWLString::operator != (const TCHAR *nTexto) {
		return !Comparar(nTexto);
	}

	//
	// Operador para comparar esta clase con otra clase DWLString
	bool DWLString::operator != (DWLString &nTexto) {
		return !Comparar(nTexto());
	}

	//
	// Operador de suma para caracteres
	const DWLString &DWLString::operator += (const char nTexto) {
		AgregarCaracter(nTexto);
		return *this;
	}

	//
	// Operador de suma para caracteres
	const DWLString &DWLString::operator += (const wchar_t nTexto) {
		AgregarCaracter(nTexto);
		return *this;
	}

	//
	// Operador de suma para cadenas wchar_t
	const DWLString &DWLString::operator += (const wchar_t *nTexto) {
		AgregarTexto(nTexto);
		return *this;
	}

	//
	// Operador de suma para cadenas char
	const DWLString &DWLString::operator += (const char *nTexto) {
		AgregarTexto(nTexto);
		return *this;
	}

	//
	// Operador de suma para clases DWLString
	const DWLString	&DWLString::operator += (DWLString &nTexto) {
		AgregarTexto(nTexto.Texto(), nTexto.Tam());
		return *this;
	}
	//
	// Operador de suma para el tipo int
	const DWLString &DWLString::operator += (const int nTexto) {
		TCHAR Dest[512];
		DWLIntToText(static_cast<const int>(nTexto), Dest, 512, 10);
		AgregarTexto(Dest);
		return *this;
	}

	//
	// Operador de suma para el tipo unsigned int
	const DWLString &DWLString::operator += (const unsigned int nTexto) {
		TCHAR Dest[512];
		DWLIntToText(static_cast<const int>(nTexto), Dest, 512, 10);
		AgregarTexto(Dest);
		return *this;
	}

	//
	// Operador de suma para el tipo long
	const DWLString &DWLString::operator += (const long nTexto) {
		TCHAR Dest[512];
		DWLIntToText(static_cast<const int>(nTexto), Dest, 512, 10);
		AgregarTexto(Dest);
		return *this;
	}

	//
	// Operador de suma para el tipo unsigned long
	const DWLString &DWLString::operator += (const unsigned long nTexto) {
		TCHAR Dest[512];
		DWLIntToText(static_cast<const int>(nTexto), Dest, 512, 10);
		AgregarTexto(Dest);
		return *this;
	}

	//
	// Operador de suma para el tipo float
	const DWLString &DWLString::operator += (const float nTexto) {
		sprintf(TEXT("%s%0.2f"), _Texto, nTexto);
		return *this;
	}

	//
	// Operador de suma para el tipo double
	const DWLString &DWLString::operator += (const double nTexto) {
		sprintf(TEXT("%s%0.2f"), _Texto, nTexto);
		return *this;
	}
*/
}
