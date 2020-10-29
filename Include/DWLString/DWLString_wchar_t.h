#ifndef DWL_STRING_WCHAR_T_H
#define DWL_STRING_WCHAR_T_H

#include "..\DWL.h" 

namespace DWL {

	class DWLString_char;

	class DWLString_wchar_t {
	  public :	
									DWLString_wchar_t(void)											: _Tam(0), _Texto(NULL)		{											};
									DWLString_wchar_t(const DWL::DWLString_wchar_t &nTexto)			: _Tam(0), _Texto(NULL)		{ AgregarTexto(nTexto._Texto, nTexto._Tam);	};
									DWLString_wchar_t(const DWL::DWLString_char &nTexto);//			: _Tam(0), _Texto(NULL)		{ AgregarTexto(nTexto._Texto, nTexto._Tam);	};
									DWLString_wchar_t(const wchar_t *nTexto, const int nTam = -1)	: _Tam(0), _Texto(NULL)		{ AgregarTexto(nTexto, nTam);				};
									DWLString_wchar_t(const char *nTexto, const int nTam = -1)		: _Tam(0), _Texto(NULL)		{ AgregarTexto(nTexto, nTam);				};
									DWLString_wchar_t(const wchar_t nTexto)							: _Tam(0), _Texto(NULL)		{ AgregarCaracter(nTexto);					};
									DWLString_wchar_t(const char nTexto)							: _Tam(0), _Texto(NULL)		{ AgregarCaracter(nTexto);					};
									DWLString_wchar_t(const int nNumero)							: _Tam(0), _Texto(NULL)		{ AgregarEntero(nNumero);					};
									DWLString_wchar_t(const UINT nNumero)							: _Tam(0), _Texto(NULL)		{ AgregarEntero(nNumero);					};
									DWLString_wchar_t(const long nNumero)							: _Tam(0), _Texto(NULL)		{ AgregarEntero(nNumero);					};
									DWLString_wchar_t(const ULONG nNumero)							: _Tam(0), _Texto(NULL)		{ AgregarEntero(nNumero);					};
									DWLString_wchar_t(const float nDecimal)							: _Tam(0), _Texto(NULL)		{ AgregarDecimal(nDecimal);					};
									DWLString_wchar_t(const double nDecimal)						: _Tam(0), _Texto(NULL)		{ AgregarDecimal(nDecimal);					};

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

		const int                   sprintf(const wchar_t *Txt, ...);

	    DWLString_wchar_t			SubStr(const UINT PosInicio, const UINT Tam = -1);
  	    DWLString_wchar_t		   *SubStrPtr(const UINT PosInicio, const UINT Tam = -1);

		DWLString_char				Char(const UINT PosInicio = 0, const UINT Tam = -1);
		DWLString_char			   *CharPtr(const UINT PosInicio = 0, const UINT Tam = -1);

		const bool					EsNumero(void);
		const bool					EsNumeroEntero(void);
		const bool					EsNumeroDecimal(void);

	    const bool			        Comparar(DWL::DWLString_wchar_t &nTexto, const bool ComparacionBinaria = false);
	    const bool			        Comparar(DWL::DWLString_char &nTexto, const bool ComparacionBinaria = false);
	    const bool			        Comparar(const wchar_t *nTexto, const bool ComparacionBinaria = false);
	    const bool			        Comparar(const char *nTexto, const bool ComparacionBinaria = false);

		inline wchar_t		       &Caracter(const UINT Posicion)			{ return _Texto[Posicion];	};
		inline const UINT			Tam(void)								{ return _Tam;				};
		inline const wchar_t       *Texto(void)								{ return _Texto;			};

		DWLString_wchar_t          &operator = (const DWLString_wchar_t &nTexto)	{ Borrar(); AgregarTexto(nTexto);		return *this;	};
		DWLString_wchar_t          &operator = (const DWLString_char &nTexto)		{ Borrar(); AgregarTexto(nTexto);		return *this;	};
		DWLString_wchar_t          &operator = (const wchar_t *nTexto)				{ Borrar(); AgregarTexto(nTexto);		return *this;	};
		DWLString_wchar_t          &operator = (const char *nTexto)					{ Borrar(); AgregarTexto(nTexto);		return *this;	};
		DWLString_wchar_t          &operator = (const wchar_t nTexto)				{ Borrar(); AgregarCaracter(nTexto);	return *this;	};
		DWLString_wchar_t          &operator = (const char nTexto)					{ Borrar(); AgregarCaracter(nTexto);	return *this;	};
		DWLString_wchar_t          &operator = (const int nNumero)					{ Borrar(); AgregarEntero(nNumero);		return *this;	};
		DWLString_wchar_t          &operator = (const UINT nNumero)					{ Borrar(); AgregarEntero(nNumero);		return *this;	};
		DWLString_wchar_t          &operator = (const long nNumero)					{ Borrar(); AgregarEntero(nNumero);		return *this;	};
		DWLString_wchar_t          &operator = (const ULONG nNumero)				{ Borrar(); AgregarEntero(nNumero);		return *this;	};
		DWLString_wchar_t          &operator = (const double nDecimal)				{ Borrar(); AgregarDecimal(nDecimal);	return *this;	};
		DWLString_wchar_t          &operator = (const float nDecimal)				{ Borrar(); AgregarDecimal(nDecimal);	return *this;	};

		DWLString_wchar_t		   &operator += (DWLString_wchar_t &nTexto) { AgregarTexto(nTexto);		return *this;	};
	    DWLString_wchar_t		   &operator += (DWLString_char &nTexto)	{ AgregarTexto(nTexto);		return *this;	};
		DWLString_wchar_t          &operator += (const wchar_t *nTexto)		{ AgregarTexto(nTexto);		return *this;	};
		DWLString_wchar_t          &operator += (const char *nTexto)		{ AgregarTexto(nTexto);		return *this;	};
		DWLString_wchar_t          &operator += (const wchar_t nTexto)		{ AgregarCaracter(nTexto);	return *this;	};
		DWLString_wchar_t          &operator += (const char nTexto)			{ AgregarCaracter(nTexto);	return *this;	};
		DWLString_wchar_t          &operator += (const int nNumero)			{ AgregarEntero(nNumero);	return *this;	};
		DWLString_wchar_t          &operator += (const UINT nNumero)		{ AgregarEntero(nNumero);	return *this;	};
		DWLString_wchar_t          &operator += (const long nNumero)		{ AgregarEntero(nNumero);	return *this;	};
		DWLString_wchar_t          &operator += (const ULONG nNumero)		{ AgregarEntero(nNumero);	return *this;	};
		DWLString_wchar_t          &operator += (const double nDecimal)		{ AgregarDecimal(nDecimal);	return *this;	};
		DWLString_wchar_t          &operator += (const float nDecimal)		{ AgregarDecimal(nDecimal); return *this;	};

		inline bool		            operator == (DWLString_wchar_t &nTexto) { return Comparar(nTexto);	};
	    inline bool		            operator == (DWLString_char &nTexto)	{ return Comparar(nTexto);	};
	    inline bool		            operator == (const wchar_t *nTexto)		{ return Comparar(nTexto);	};
	    inline bool		            operator == (const char *nTexto)		{ return Comparar(nTexto);	};
	    inline bool		            operator != (DWLString_wchar_t &nTexto) { return !Comparar(nTexto); };
	    inline bool		            operator != (DWLString_char &nTexto)	{ return !Comparar(nTexto); };
	    inline bool		            operator != (const wchar_t *nTexto)		{ return !Comparar(nTexto); };
	    inline bool		            operator != (const char *nTexto)		{ return !Comparar(nTexto); };

	    inline const wchar_t       *operator () (void)						{ return _Texto; 			};
		inline wchar_t	           &operator [] (const UINT Posicion)		{ return _Texto[Posicion];	};
	  protected : ////////////////////
									//
									// Variable que contiene el texto de esta clase
	    wchar_t                   *_Texto;
									//
									// Tamaño del texto en caracteres
	    UINT                       _Tam;

		friend class				DWLString_char;
	};
};

#endif
