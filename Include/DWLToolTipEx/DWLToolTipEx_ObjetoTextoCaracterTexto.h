#ifndef DWL_TOOLTIPEX_OBJETOTEXTOCARACTERTEXTO_H
#define DWL_TOOLTIPEX_OBJETOTEXTOCARACTERTEXTO_H

#include "..\DWLString.h"

namespace DWL {
	namespace ControlesEx {
		class DWLToolTipEx;

		//! Clase que contiene un objeto de tipo Texto Caracter Texto
		class DWLToolTipEx_ObjetoTextoCaracterTexto  {
		public : ///////////////// Miembros publicos

								//! Constructor.
								/*! Constructor.
										\fn			DWLToolTipEx_ObjetoTextoCaracterTexto(void);
										\return		No devuelve nada.
								*/
								DWLToolTipEx_ObjetoTextoCaracterTexto(void) : _Texto1(), _Texto2(), _Caracter() {
								};

								//! Constructor asignador.
								/*! Constructor asignador.
										\fn			DWLToolTipEx_ObjetoTextoCaracterTexto(const TCHAR *nTexto1, const TCHAR nCaracter, const TCHAR *nTexto2);
										\param[in]	nTexto1		: Texto que se alineara a la izquierda.
										\param[in]	nCaracter	: Caracter que se usara como separador (lo normal es poner ':').
										\param[in]	nTexto2		: Texto que se alineara a la derecha del caracter separador.
										\return		No devuelve nada.
								*/
								DWLToolTipEx_ObjetoTextoCaracterTexto(const TCHAR *nTexto1, const TCHAR nCaracter, const TCHAR *nTexto2) {
									_Texto1 = nTexto1;
									_Texto2 = nTexto2;
									_Caracter = nCaracter;
								};

								//! Destructor.
								/*! Destructor.
										\fn			~DWLToolTipEx_ObjetoTextoCaracterTexto(void);
										\return		No devuelve nada.
								*/
							   ~DWLToolTipEx_ObjetoTextoCaracterTexto(void){
								};

								//! Función que retorna el texto que se alinea a la izquierda del todo.
								/*! Esta función devuelve el texto que se alinea a la izquierda del todo.
										\fn			inline const TCHAR *Texto1(void);
										\return		Devuelve la cadena de caracteres asociada con el texto 1.
								*/
		 inline const TCHAR    *Texto1(void) {
									return _Texto1();
								};

								//! Función que retorna el texto que se alinea a la derecha del caracter delimitador.
								/*! Esta función devuelve el texto que se alinea a la derecha del caracter delimitador.
										\fn			inline const TCHAR *Texto2(void);
										\return		Devuelve la cadena de caracteres asociada con el texto 2.
								*/
		 inline const TCHAR    *Texto2(void) {
									return _Texto2();
								};

								//! Función que retorna el tamaño en caracteres del texto 1.
								/*! Esta función devuelve la longitud en caracteres del texto 1.
										\fn			inline const UINT TamTexto1(void);
										\return		Devuelve la longitud en caracteres del texto 1.
								*/
		 inline const UINT      TamTexto1(void) {
									return _Texto1.Tam();
								};

								//! Función que retorna el tamaño en caracteres del texto 2.
								/*! Esta función devuelve la longitud en caracteres del texto 2.
										\fn			inline const UINT TamTexto2(void);
										\return		Devuelve la longitud en caracteres del texto 2.
								*/
		 inline const UINT      TamTexto2(void)	{
									return _Texto2.Tam();
								};

								//! Función que retorna el caracter que hace de separador.
								/*! Esta función devuelve el caracter que hace de separador.
										\fn			inline const TCHAR *Caracter(void);
										\return		Devuelve el caracter que hace de separador.
								*/
		 inline const TCHAR    *Caracter(void) {
									return _Caracter();
								};

		protected : ////////////// Miembros protegidos

								//! Texto que se alineara a la izquierda del todo.
		 DWLString			   _Texto1;

								//! Texto que se alineara a la izquierda del caracter separador.
		 DWLString		       _Texto2;

								//! Caracter que separa el Texto1 del Texto2 y sirve para justificarlos.
		 DWLString			   _Caracter;

		 friend class DWLToolTipEx;
		};						//
		////////////////////////// Fin DWLToolTipEx_ObjetoTextoCaracterTexto



    };
};

#endif
