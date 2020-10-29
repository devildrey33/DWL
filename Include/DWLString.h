// Este archivo forma parte de la DReY Windows Lib.
// Fecha de creación   : 11/12/2008
//
// Version 1.0b
// Ultima modificación : 02/03/2009

// Clase creada para facilitar al maximo el uso de strings
// No esta pensada para ser la mas rapida, pero si es muy comoda, para trabajar tanto con textos como con valores numericos.




#ifndef DWL_STRING_H
#define DWL_STRING_H
 
#include "DWL.h"
#include <vector>
#include "DWLString\DWLString_wchar_t.h"
#include "DWLString\DWLString_char.h"
/*
enum DWL_Enum_String_Comparar {
    DWL_Enum_String_Comparar_Binario,
    DWL_Enum_String_Comparar_Texto
};*/


namespace DWL {
	
	#if defined UNICODE
		typedef DWL::DWLString_wchar_t   DWLString;
	#else
		typedef DWL::DWLString_char      DWLString;
	#endif


	/*
	class DWLString {
	 public : //////////////////// Miembros publicos
								//
								// Constructor que inicia los valores a 0
								// DWLString(void);
								DWLString(void);

								//
								// Constructor para clases DWLString
								// DWLString(DWLString &nTexto);
//#if (COMPILADOR != COMPILADOR_VC6)
								DWLString(const DWL::DWLString &nTexto);
//#else
//								DWLString(DWL::DWLString &nTexto);
//#endif

#if (COMPILADOR != COMPILADOR_VC6)
	template <typename TipoStr1>
								DWLString(const TipoStr1 &String1) {
									_Tam = 0;
									_Texto = NULL;
									this->operator += (String1);
								};
#endif

								//
								// Destructor que elimina de memoria todos los datos
								// ~DWLString(void);
							   ~DWLString(void);
								//
							    // Función para borrar la cadena de la memoria
								// void Borrar(void):
      void						Borrar(void);
								//
								// Función para hacer un parsing de datos al estilo del sprintf
								// void sprintf(const TCHAR *Txt, ...);
								// ES MAS RECOMENDABLE UTILIZAR LA FUNCION Parsear
	  void						sprintf(const TCHAR *Txt, ...);
								//
								// Operador que retorna el caracter indicado por el miembro posicion
								// inline TCHAR &operator [] (const unsigned int Posicion);
	  TCHAR		          	   &Caracter (const unsigned int Posicion) { return _Texto[Posicion]; };
								//
								// Función que retorna el texto de esta clase
								// inline const TCHAR *Texto(void)
	  inline const TCHAR	   *Texto(void) { return _Texto; };
								//
								// Función que retorna el texto de esta clase pasado por atoi en un numero entero
								// inline int NumeroEntero(void)
	  int     			        NumeroEntero(void);
								//
								// Función que retorna el total de caracteres de el texto
								// inline UINT Tam(void) const;
	  inline UINT               Tam(void) const { return _Tam; };
								//
								// Función para comprobar si la cadena es un numero entero o decimal
								// const bool EsNumero(void);
	  bool				        EsNumero(void);
								//
								// Función para comprobar si la cadena es un numero entero
								// const bool EsNumeroEntero(void);
	  bool				        EsNumeroEntero(void);
								//
								// Función para comprobar si la cadena es un numero decimal
								// const bool EsNumeroDecimal(void);
	  bool				        EsNumeroDecimal(void);
								//
								// Función para agregar un caracter a la cadena
								// void AgregarCaracter(const TCHAR nTexto);
	  void						AgregarCaracter(const TCHAR nTexto);
								//
								// Función para agregar un wchar_t a la cadena de texto independientemente de si trabajamos en ANSI o UNICODE
								// void AgregarTexto(const wchar_t *nTexto, const int nTam = -1);
	  void                      AgregarTexto(const wchar_t *nTexto, const int nTam = -1);
								//
								// Función para agregar un char a la cadena de texto independientemente de si trabajamos en ANSI o UNICODE
								// void AgregarTexto(const char *nTexto, const int nTam = -1);
	  void                      AgregarTexto(const char *nTexto, const int nTam = -1);
								//
								// Función para copiar un wchar_t a la cadena de texto independientemente de si trabajamos en ANSI o UNICODE
								// void CopiarTexto(const wchar_t *nTexto, const int nTam = -1);
	  void					    CopiarTexto(const wchar_t *nTexto, const int nTam = -1);
								//
								// Función para copiar un char a la cadena de texto independientemente de si trabajamos en ANSI o UNICODE
								// void CopiarTexto(const char *nTexto, const int nTam = -1);
	  void					    CopiarTexto(const char *nTexto, const int nTam = -1);
								//
								// Función para comparar 2 cadenas
								// const bool Comparar(const TCHAR *nTexto, Enums::DWL_String_Comparar Comparacion = Enums::Comparacion_Texto);
	  bool				        Comparar(const TCHAR *nTexto, DWL_Enum_String_Comparar Comparacion = DWL_Enum_String_Comparar_Texto);

								// Función que concatena los TCHARs introducidos
	  void                      Concatenar(const UINT NumTCHARs, ...);
								//
								// Función que retorna la parte del texto especificada en otra clase DWLString
								// DWLString SubStr(const unsigned int PosInicio, const unsigned int Tam = -1);
	  DWLString					SubStr(const UINT PosInicio, const UINT Tam = -1);
								//
								// Función que retorna la parte del texto especificada en un puntero a otra clase DWLString
								// DWLString SubStr(const unsigned int PosInicio, const unsigned int Tam = -1);
								// A REMARCAR : debes eliminar el DWLString retornado cuando ya no lo necesites.
	  DWLString				   *SubStrPtr(const UINT PosInicio, const UINT Tam = -1);
								//
								// Función que retorna la linea especificada dentro de la cadena
								// NOTA : Si se introduce una linea invalida retornara una cadena vacia
								// DWLString Linea(const unsigned int NumLinea);
	  DWLString					Linea(const UINT NumLinea);
								//
								// Función que retorna el total de lineas de texto que contiene la cadena
								// UINT TotalLineas(void);
	  UINT              		TotalLineas(void);
								//
								// Operador de copia para cadenas wchar_t
								// DWLString &operator = (const wchar_t *nTexto);
	  DWLString		           &operator = (const wchar_t *nTexto);
								//
								// Operador de copia para cadenas char
								// DWLString &operator = (const char *nTexto);
	  DWLString		           &operator = (const char *nTexto);
								//
								// Operador de copia para caracteres sueltos
								// DWLString &operator = (const TCHAR nTexto);
	  DWLString		           &operator = (const TCHAR nTexto);
								//
								// Operador de copia para clases DWLString
								// DWLString &operator = (DWLString &nTexto);
	  DWLString		           &operator = (DWLString nTexto);
								//
								// Operador de copia para el tipo int
								// DWLString &operator = (const int nTexto);
	  DWLString		           &operator = (const int nTexto);
								//
								// Operador de copia para el tipo unsigned int
								// DWLString &operator = (const unsigned int nTexto);
	  DWLString		           &operator = (const unsigned int nTexto);
								//
								// Operador de copia para el tipo long
								// DWLString &operator = (const long nTexto);
	  DWLString		           &operator = (const long nTexto);
								//
								// Operador de copia para el tipo unsigned long
								// DWLString &operator = (const unsigned long nTexto);
	  DWLString		           &operator = (const unsigned long nTexto);
								//
								// Operador de copia para el tipo float
								// DWLString &operator = (const float nTexto);
	  DWLString		           &operator = (const float nTexto);
								//
								// Operador de comparacion
								// const bool operator == (const TCHAR *nTexto);
	  bool		                operator == (const TCHAR *nTexto);
								//
								// Operador de comparacion
								// const bool operator == (DWLString &nTexto);
	  bool		                operator == (DWLString &nTexto);
								//
								// Operador de comparacion
								// const bool operator == (const TCHAR *nTexto);
	  bool		                operator != (const TCHAR *nTexto);
								//
								// Operador de comparacion
								// const bool operator == (DWLString &nTexto);
	  bool		                operator != (DWLString &nTexto);
								//
								// Operador de suma para cadenas wchar_t
								// const DWLString &operator += (const wchar_t *nTexto);
	  const DWLString          &operator += (const wchar_t *nTexto);
								//
								// Operador de suma para cadenas char
								// const DWLString &operator += (const char *nTexto);
	  const DWLString          &operator += (const char *nTexto);
								//
								// Operador de suma para caracteres sueltos
								// const DWLString &operator += (const wchar_t nTexto);
	  const DWLString          &operator += (const wchar_t nTexto);
								//
								// Operador de suma para caracteres sueltos
								// const DWLString &operator += (const char nTexto);
	  const DWLString          &operator += (const char nTexto);
								//
								// Operador de suma para clases DWLString
								// const DWLString &operator += (DWLString &nTexto);
	  const DWLString		   &operator += (DWLString &nTexto);
								//
								// Operador de suma para el tipo int
								// const DWLString &operator += (const int nTexto);
	  const DWLString          &operator += (const int nTexto);
								//
								// Operador de suma para el tipo unsigned int
								// const DWLString &operator += (const unsigned int nTexto);
	  const DWLString          &operator += (const unsigned int nTexto);
								//
								// Operador de suma para el tipo long
								// const DWLString &operator += (const long nTexto);
	  const DWLString          &operator += (const long nTexto);
								//
								// Operador de suma para el tipo unsigned long
								// const DWLString &operator += (const unsigned long nTexto);
	  const DWLString          &operator += (const unsigned long nTexto);
								//
								// Operador de suma para el tipo float
								// const DWLString &operator += (const float nTexto);
	  const DWLString          &operator += (const float nTexto);
								//
								// Operador de suma para el tipo float
								// const DWLString &operator += (const double nTexto);
	  const DWLString          &operator += (const double nTexto);
								//
								// Operador que retorna el texto de esta clase
								// inline const TCHAR *operator () (void)
	  inline const TCHAR       *operator () (void) throw() { return _Texto; };
								//
								// Operador que retorna el caracter indicado por el miembro posicion
								// inline TCHAR &operator [] (const unsigned int Posicion);
	  inline TCHAR			   &operator [] (const unsigned int Posicion) { return _Texto[Posicion]; };
	 ///////////////////////////// Funciones template para el parseo por tipos
								// Estas funciones estan pensadas para substituir la funcion sprintf, y por el momento hay versiones para 1-10 parametros.
								// uso : DWLString Str; Str.Parsear("clase creada por devildrey ", 33, TEXT("que admite parseos de varios tipos))
								// devolveria "clase creada por devildrey 33 que admite parseos de varios tipos" en unicode o ansi dependiendo de como se compile esta aplicacion


	private : //////////////////// Miembros privados
								//
								// Variable que contiene el texto de esta clase
	  TCHAR		              *_Texto;
								//
								// Tamaño del texto en caracteres
	  UINT                     _Tam;

//	  static TCHAR             _BufferGeneral[MAX_INT];
#if (COMPILADOR != COMPILADOR_MINGW)// El Dev c++ no acepta clases amigas de ellas mismas
	  friend class              DWLString;
#endif
	}; /////////////////////////// Fin DWLString

	*/


	// 1  \  c:\dir1\dir2\dir3\
	// 2  \  c:\dir1\dir2\dir3\arch.txt

//	typedef DWLString * DWLStringPrt;

	// Clase para separar un texto partiendo de un delimitador
	// El delimitador no sera añadido a ninguna de las partes
	class DWLTexto_Separado {
	  public :
							DWLTexto_Separado(DWLString &Texto, TCHAR Delimitador) {
								size_t     Ultimo = 0;
								for (size_t i = 0; i < Texto.Tam(); i++) {
									if (Texto[i] == Delimitador) {
										_Textos.push_back(Texto.SubStrPtr(Ultimo, i - Ultimo));
										Ultimo = i + 1;
									}
								}
								if (Ultimo < Texto.Tam()) _Textos.push_back(Texto.SubStrPtr(Ultimo));
							};

							DWLTexto_Separado(const TCHAR *Texto, TCHAR Delimitador, const int TamTexto = -1) {
								size_t	   Tam = 0;
								size_t     Ultimo = 0;
								DWLString *TmpStr = NULL;
								if (TamTexto < 0)	Tam = DWLStrLen(Texto);
								else				Tam = TamTexto;
								for (size_t i = 0; i < Tam; i++) {
									if (Texto[i] == Delimitador) {
										TmpStr = new DWLString;
//										TmpStr->Borrar();
										TmpStr->AgregarTexto(&Texto[Ultimo], i - Ultimo);
									}
								}
								if (Ultimo < Tam) {
									TmpStr = new DWLString;
									TmpStr->AgregarTexto(&Texto[Ultimo]);
								}
							}


						   ~DWLTexto_Separado(void) {
							   for (size_t i = 0; i < _Textos.size(); i++) delete _Textos[i];
//							   delete [] _Textos;
							};

		inline const TCHAR *TextoTCHAR(const UINT Pos) {
								return _Textos[Pos]->Texto();
							};

		inline UINT         TotalTextos(void) { 
								return _Textos.size();
							}

		inline DWLString   &operator [] (const UINT Pos) {
								return *_Textos[Pos];
							};
	  private :
		std::vector<DWLString *> _Textos;
//		UINT               _TotalTextos;
	};

}








#endif




// Version 0.1      [11/12/2008]
// -Primera version de esta clase

// Version 1.0		[03/01/2009]
// -Añadida función para obtener una linea dentro de la cadena, y una Función para saber el total de lineas
// -Añadida una gran variedad de operadores para facilitar mas el trabajo con los strings

// Version 1.0b		[02/03/2009]
// -Reparado un bug en la version ASCII que no pasaba correctamente los caracteres unicode a ascii en conversiones de ese tipo
