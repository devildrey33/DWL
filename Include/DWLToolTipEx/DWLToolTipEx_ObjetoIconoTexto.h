#ifndef DWL_TOOLTIPEX_OBJETOICONOTEXTO_H
#define DWL_TOOLTIPEX_OBJETOICONOTEXTO_H

#include "..\DWLString.h"
 
namespace DWL {
	namespace ControlesEx {

		class DWLToolTipEx;
		//! Clase que contiene un objeto de tipo Icono y Texto, (Ideal para titulos)
		class DWLToolTipEx_ObjetoIconoTexto {
		public : ///////////////// Miembros publicos

								//! Constructor.
								/*! Constructor.
										\fn			DWLToolTipEx_ObjetoIconoTexto(void);
										\return		No devuelve nada.
								*/
								DWLToolTipEx_ObjetoIconoTexto(void) : _Texto(), _Icono(0), _AltoIcono(0), _AnchoIcono(0) {
								};

								//! Constructor asignador.
								/*! Constructor asignador .
										\fn			DWLToolTipEx_ObjetoIconoTexto(const int nIcono, const int nAnchoIcono, const int nAltoIcono, const TCHAR *nTexto);
										\param[in]	nIcono		: ID del icono a mostrar.
										\param[in]  nAnchoIcono : Ancho en pixeles del icono.
										\param[in]  nAltoIcono	: Altura en pixeles del icono
										\param[in]	nTexto		: Texto a mostrar.
										\return		No devuelve nada.
								*/
								DWLToolTipEx_ObjetoIconoTexto(const int nIcono, const int nAnchoIcono, const int nAltoIcono, const TCHAR *nTexto) : _Icono(nIcono), _AltoIcono(nAnchoIcono), _AnchoIcono(nAltoIcono) {
									_Texto = nTexto;
								};

								//! Destructor.
								/*! Destructor.
										\fn			~DWLToolTipEx_ObjetoIconoTexto(void);
										\return		No devuelve nada.
								*/
							   ~DWLToolTipEx_ObjetoIconoTexto(void){
							    };

								//! Función que retorna el texto que se alinea a la derecha del icono.
								/*! Esta función devuelve el texto que se alinea a la derecha del icono.
										\fn			inline const TCHAR *Texto(void);
										\return		Devuelve la cadena de caracteres asociada con el texto.
								*/
		 inline const TCHAR    *Texto(void) {
									return _Texto();
								};

								//! Función que retorna el tamaño en caracteres del texto.
								/*! Esta función devuelve la longitud en caracteres del texto.
										\fn			inline const UINT TamTexto(void);
										\return		Devuelve la longitud en caracteres del texto.
								*/
		 inline const UINT      TamTexto(void)  {
									return _Texto.Tam();
								};

								//! Función que retorna el icono que se alinea a la izquierda del todo.
								/*! Esta función devuelve el texto que se alinea a la izquierda del todo.
										\fn			inline int Icono(void) const;
										\return		Devuelve la ID del icono que se pintara a la izquierda del todo.
								*/
		 inline int             Icono(void) const {
									return _Icono;
								};

								//! Función que retorna el ancho del icono en pixeles.
								/*! Esta función devuelve el ancho del icono en pixeles.
										\fn			inline int AnchoIcono(void) const;
										\return		Devuelve el ancho del icono en pixeles.
								*/
		 inline int             AnchoIcono(void) const {
									return _AnchoIcono;
								};

								//! Función que retorna la altura del icono en pixeles.
								/*! Esta función devuelve la altura del icono en pixeles.
										\fn			inline int AltoIcono(void) const;
										\return		Devuelve la altura del icono en pixeles.
								*/
		 inline int             AltoIcono(void) const {
									return _AltoIcono;
								};

		protected: /////////////// Miembros protegidos

								//! Clase DWLString que contiene el texto.
		 DWLString			   _Texto;

								//! ID del icono de los recursos.
		 int				   _Icono;

								//! Altura del icono en pixeles.
		 int				   _AltoIcono;

								//! Ancho del icono en pixeles.
		 int				   _AnchoIcono;

		 friend class DWLToolTipEx;
		};						//
		////////////////////////// Fin DWLToolTipEx_ObjetoIconoTexto


    };
};

#endif
