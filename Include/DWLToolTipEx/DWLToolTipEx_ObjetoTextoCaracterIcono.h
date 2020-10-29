#ifndef DWL_TOOLTIPEX_OBJETOTEXTOCARACTERICONO_H
#define DWL_TOOLTIPEX_OBJETOTEXTOCARACTERICONO_H

#include "..\DWLString.h"
 
namespace DWL {
	namespace ControlesEx {
		//! Clase que contiene un objeto de tipo Texto Caracter Icono
		class DWLToolTipEx_ObjetoTextoCaracterIcono  {
		public : ///////////////// Miembros publicos

								//! Constructor.
								/*! Constructor.
										\fn			DWLToolTipEx_ObjetoTextoCaracterIcono(void);
										\return		No devuelve nada.
								*/
								DWLToolTipEx_ObjetoTextoCaracterIcono(void) : _Icono(0), _Caracter(), _Fraccion(0.0f), _AltoIcono(0), _AnchoIcono(0) {
								};

								//! Constructor asignador.
								/*! Constructor asignador.
										\fn			DWLToolTipEx_ObjetoTextoCaracterIcono(const TCHAR *nTexto, const TCHAR nCaracter, const int nIcono, const int nAltoIcono, const int nAnchoIcono, const float nFraccion = 1.0f);
										\param[in]  nTexto		: Texto que se alineara a la izquierda.
										\param[in]  nCaracter	: Caracter separador.
										\param[in]  nIcono		: Icono que se alineara a la derecha del caracter separador.
										\param[in]  nAnchoIcono : Ancho en pixeles del icono (16)
										\param[in]  nAltoIcono	: Alto en pixeles del icono (16)
										\param[in]  nFraccion	: Este parametro indica las veces que se pintara el icono, una fraccion de 0.5 pintara solo medio icono, una fraccion de 5.0 pintara 5 iconos uno detras de otro.
										\return		No devuelve nada.
								*/
								DWLToolTipEx_ObjetoTextoCaracterIcono(const TCHAR *nTexto, const TCHAR nCaracter, const int nIcono, const int nAnchoIcono, const int nAltoIcono, const float nFraccion = 1.0f) : _Icono(nIcono), _Fraccion(nFraccion), _AltoIcono(nAltoIcono), _AnchoIcono(nAnchoIcono) {
									_Texto = nTexto;
									_Caracter = nCaracter;
								};

								//! Destructor.
								/*! Destructor.
										\fn			~DWLToolTipEx_ObjetoTextoCaracterIcono(void);
										\return		No devuelve nada.
								*/
							   ~DWLToolTipEx_ObjetoTextoCaracterIcono(void) {
								};

								//! Funci�n que retorna el texto que se alinea a la izquierda del todo.
								/*! Esta funci�n devuelve el texto que se alinea a la izquierda del todo.
										\fn			inline const TCHAR *Texto(void);
										\return		Devuelve la cadena de caracteres asociada con el texto.
								*/
		 inline const TCHAR    *Texto(void) {
									return _Texto();
								};

								//! Funci�n que retorna el icono que se alinea a la derecha del caracter separador.
								/*! Esta funci�n devuelve el texto que se alinea a la derecha del caracter separador.
										\fn			inline int Icono(void) const;
										\return		Devuelve la ID del icono que se pintara a la derecha del caracter separador.
								*/
		 inline int             Icono(void) const {
									return _Icono;
								};

								//! Funci�n que retorna el ancho del icono en pixeles.
								/*! Esta funci�n devuelve el ancho del icono en pixeles.
										\fn			inline int AnchoIcono(void) const;
										\return		Devuelve el ancho del icono en pixeles.
								*/
		 inline int             AnchoIcono(void) const {
									return _AnchoIcono;
								};

								//! Funci�n que retorna la altura del icono en pixeles.
								/*! Esta funci�n devuelve la altura del icono en pixeles.
										\fn			inline int AltoIcono(void) const;
										\return		Devuelve la altura del icono en pixeles.
								*/
		 inline int             AltoIcono(void) const {
									return _AltoIcono;
								};

								//! Funci�n que retorna el tama�o en caracteres del texto.
								/*! Esta funci�n devuelve la longitud en caracteres del texto.
										\fn			inline const UINT TamTexto(void);
										\return		Devuelve la longitud en caracteres del texto.
								*/
		 inline const UINT      TamTexto(void) {
									return _Texto.Tam();
								}

								//! Funci�n que retorna el caracter que hace de separador.
								/*! Esta funci�n devuelve el caracter que hace de separador.
										\fn			inline const TCHAR *Caracter(void) const;
										\return		Devuelve el caracter que hace de separador.
								*/
		 inline const TCHAR    *Caracter(void) {
									return _Caracter();
								};

								//! Funci�n que retorna la fracci�n que se usara para pintar el icono.
								/*! Esta funci�n devuelve la fracci�n que se usara para pintar el icono.
										\fn			inline float Fraccion(void)(void) const;
										\return		Devuelve la fraccion que se usara para pintar el icono.
										\remarks	Una fraccion de 1.0 pintara el icono entero, una fraccion de 5.0 pintara 5 veces el icono uno detras de otro, una fraccion de 0.2 pintara solo un 20 porciento del icono.
								*/
		 inline float	        Fraccion(void) const {
									return _Fraccion;
								};

		protected: /////////////// Miembros protegidos

								//! Clase DWLString que contiene el texto.
		 DWLString			   _Texto;

								//! ID para el icono de los recursos.
		 int			       _Icono;

								//! Fraccion que se usara para pintar el icono.
		 float				   _Fraccion;

								//! Caracter que delimitara el texto y el icono
		 DWLString			   _Caracter;

								//! Altura en pixeles del icono
		 int				   _AltoIcono;

								//! Ancho en p�xeles del icono
		 int				   _AnchoIcono;
		};						//
		////////////////////////// Fin DWLToolTipEx_ObjetoTextoCaracterIcono


    };
};

#endif
