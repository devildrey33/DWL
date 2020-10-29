#ifndef DWL_STRING_CHAR_H
#define DWL_STRING_CHAR_H

#include "..\DWL.h" 

namespace DWL {
	class DWLString_wchar_t;

	class DWLString_char {
	  public :	
									DWLString_char(void)										: _Tam(0), _Texto(NULL)		{								};
									DWLString_char(const DWL::DWLString_wchar_t &nTexto);//		: _Tam(0), _Texto(NULL)		{ AgregarTexto(nTexto._Texto, nTexto._Tam);			};
									DWLString_char(const DWL::DWLString_char &nTexto)			: _Tam(0), _Texto(NULL)		{ AgregarTexto(nTexto._Texto, nTexto._Tam);			};
									DWLString_char(const wchar_t *nTexto, const int nTam = -1)	: _Tam(0), _Texto(NULL)		{ AgregarTexto(nTexto, nTam);	};
									DWLString_char(const char *nTexto, const int nTam = -1)		: _Tam(0), _Texto(NULL)		{ AgregarTexto(nTexto, nTam);	};
									DWLString_char(const wchar_t nTexto)						: _Tam(0), _Texto(NULL)		{ AgregarCaracter(nTexto);		};
									DWLString_char(const char nTexto)							: _Tam(0), _Texto(NULL)		{ AgregarCaracter(nTexto);		};
									DWLString_char(const int nNumero)							: _Tam(0), _Texto(NULL)		{ AgregarEntero(nNumero);		};
									DWLString_char(const UINT nNumero)							: _Tam(0), _Texto(NULL)		{ AgregarEntero(nNumero);		};
									DWLString_char(const long nNumero)							: _Tam(0), _Texto(NULL)		{ AgregarEntero(nNumero);		};
									DWLString_char(const ULONG nNumero)							: _Tam(0), _Texto(NULL)		{ AgregarEntero(nNumero);		};
									DWLString_char(const float nDecimal)						: _Tam(0), _Texto(NULL)		{ AgregarDecimal(nDecimal);		};
									DWLString_char(const double nDecimal)						: _Tam(0), _Texto(NULL)		{ AgregarDecimal(nDecimal);		};

		void						Borrar(void);

	    void						AgregarCaracter(const wchar_t nTexto);
	    void						AgregarCaracter(const char nTexto);
	    const UINT					AgregarTexto(const DWL::DWLString_wchar_t &nTexto);
	    const UINT					AgregarTexto(const DWL::DWLString_char &nTexto);
	    const UINT					AgregarTexto(const wchar_t *nTexto, const int nTam = -1);
	    const UINT					AgregarTexto(const char *nTexto, const int nTam = -1);
	    const UINT					AgregarEntero(const int nNumero, const UINT NumEnteros = 0);
	    const UINT					AgregarEntero(const UINT nNumero, const UINT NumEnteros = 0);
	    const UINT					AgregarEntero(const long nNumero, const UINT NumEnteros = 0);
	    const UINT					AgregarEntero(const ULONG nNumero, const UINT NumEnteros = 0);
	    const UINT					AgregarDecimal(const double nDecimal, const UINT NumDecimales = 0);
	    const UINT					AgregarDecimal(const float nDecimal, const UINT NumDecimales = 2);

		const int                   sprintf(const char *Txt, ...);

	    DWLString_char				SubStr(const UINT PosInicio, const UINT Tam = -1);
  	    DWLString_char			   *SubStrPtr(const UINT PosInicio, const UINT Tam = -1);

		DWLString_wchar_t			WChar(const UINT PosInicio = 0, const UINT Tam = -1);
		DWLString_wchar_t		   *WCharPtr(const UINT PosInicio = 0, const UINT Tam = -1);

		const bool					EsNumero(void);
		const bool					EsNumeroEntero(void);
		const bool					EsNumeroDecimal(void);

	    const bool			        Comparar(DWL::DWLString_wchar_t &nTexto, const bool ComparacionBinaria = false);
	    const bool			        Comparar(DWL::DWLString_char &nTexto, const bool ComparacionBinaria = false);
	    const bool			        Comparar(const wchar_t *nTexto, const bool ComparacionBinaria = false);
	    const bool			        Comparar(const char *nTexto, const bool ComparacionBinaria = false);

		inline char			       &Caracter(const UINT Posicion)			{ return _Texto[Posicion];	};
		inline const UINT			Tam(void)								{ return _Tam;				};
		inline const char          *Texto(void)								{ return _Texto;			};

		DWLString_char             &operator = (const DWLString_wchar_t &nTexto)	{ Borrar(); AgregarTexto(nTexto);		return *this;	};
		DWLString_char             &operator = (const DWLString_char &nTexto)		{ Borrar(); AgregarTexto(nTexto);		return *this;	};
		DWLString_char             &operator = (const wchar_t *nTexto)				{ Borrar(); AgregarTexto(nTexto);		return *this;	};
		DWLString_char             &operator = (const char *nTexto)					{ Borrar(); AgregarTexto(nTexto);		return *this;	};
		DWLString_char             &operator = (const wchar_t nTexto)				{ Borrar(); AgregarCaracter(nTexto);	return *this;	};
		DWLString_char             &operator = (const char nTexto)					{ Borrar(); AgregarCaracter(nTexto);	return *this;	};
		DWLString_char             &operator = (const int nNumero)					{ Borrar(); AgregarEntero(nNumero);		return *this;	};
		DWLString_char             &operator = (const UINT nNumero)					{ Borrar(); AgregarEntero(nNumero);		return *this;	};
		DWLString_char             &operator = (const long nNumero)					{ Borrar(); AgregarEntero(nNumero);		return *this;	};
		DWLString_char             &operator = (const ULONG nNumero)				{ Borrar(); AgregarEntero(nNumero);		return *this;	};
		DWLString_char             &operator = (const double nDecimal)				{ Borrar(); AgregarDecimal(nDecimal);	return *this;	};
		DWLString_char             &operator = (const float nDecimal)				{ Borrar(); AgregarDecimal(nDecimal);	return *this;	};

		DWLString_char	     	   &operator += (DWLString_wchar_t &nTexto) { AgregarTexto(nTexto);		return *this;	};
	    DWLString_char   		   &operator += (DWLString_char &nTexto)	{ AgregarTexto(nTexto);		return *this;	};
		DWLString_char             &operator += (const wchar_t *nTexto)		{ AgregarTexto(nTexto);		return *this;	};
		DWLString_char             &operator += (const char *nTexto)		{ AgregarTexto(nTexto);		return *this;	};
		DWLString_char             &operator += (const wchar_t nTexto)		{ AgregarCaracter(nTexto);	return *this;	};
		DWLString_char             &operator += (const char nTexto)			{ AgregarCaracter(nTexto);	return *this;	};
		DWLString_char             &operator += (const int nNumero)			{ AgregarEntero(nNumero);	return *this;	};
		DWLString_char             &operator += (const UINT nNumero)		{ AgregarEntero(nNumero);	return *this;	};
		DWLString_char             &operator += (const long nNumero)		{ AgregarEntero(nNumero);	return *this;	};
		DWLString_char             &operator += (const ULONG nNumero)		{ AgregarEntero(nNumero);	return *this;	};
		DWLString_char	           &operator += (const double nDecimal)		{ AgregarDecimal(nDecimal);	return *this;	};
		DWLString_char             &operator += (const float nDecimal)		{ AgregarDecimal(nDecimal); return *this;	};

		inline bool		            operator == (DWLString_wchar_t &nTexto) { return Comparar(nTexto);	};
	    inline bool		            operator == (DWLString_char &nTexto)	{ return Comparar(nTexto);	};
	    inline bool		            operator == (const wchar_t *nTexto)		{ return Comparar(nTexto);	};
	    inline bool		            operator == (const char *nTexto)		{ return Comparar(nTexto);	};
	    inline bool		            operator != (DWLString_wchar_t &nTexto) { return !Comparar(nTexto); };
	    inline bool		            operator != (DWLString_char &nTexto)	{ return !Comparar(nTexto); };
	    inline bool		            operator != (const wchar_t *nTexto)		{ return !Comparar(nTexto); };
	    inline bool		            operator != (const char *nTexto)		{ return !Comparar(nTexto); };

	    inline const char          *operator () (void)						{ return _Texto; 			};
		inline char  	           &operator [] (const UINT Posicion)		{ return _Texto[Posicion];	};
	  protected : ////////////////////
									//
									// Variable que contiene el texto de esta clase
	    char                      *_Texto;
									//
									// Tamaño del texto en caracteres
	    UINT                       _Tam;

		friend class				DWLString_wchar_t;

	};
};

#endif
