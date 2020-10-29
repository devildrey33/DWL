#include "DWLFuente.h"
#include "DWLhDC.h"
#include "DWLColor.h"

//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres GDI
	namespace GDI { 
		//! Función para pintar texto basada en TextOut.
		/*!	Esta función pinta el texto utilizando la API TextOut.
				\fn		   void PintarTexto(HDC hDC, const TCHAR *nTexto, const int nX, const int nY, COLORREF nColorTexto, const bool nTransparente);
                \param[in] hDC           : hDC donde se va a pintar.
                \param[in] nTexto        : Texto que se va a pintar.
                \param[in] nX            : Coordenada X donde se va a pintar.
                \param[in] nY            : Coordenada Y donde se va a pintar.
                \param[in] nColorTexto   : Color del texto.
                \param[in] nTransparente : Pintar el fondo transparente.
				\return	   No devuelve nada.
		*/
        void DWLFuente::PintarTexto(HDC hDC, const TCHAR *nTexto, const int nX, const int nY, COLORREF nColorTexto, const bool nTransparente)  { 
			HFONT Viejo = NULL; 
			if (_Fuente != (HFONT)GetCurrentObject(hDC, OBJ_FONT)) Viejo = (HFONT)SelectObject(hDC, _Fuente); 
			if (nTransparente == true) SetBkMode(hDC, TRANSPARENT);
			SetTextColor(hDC, nColorTexto); 
			TextOut(hDC, nX, nY, nTexto, lstrlen(nTexto));
			if (Viejo != NULL)	SelectObject(hDC, Viejo); 
		};

		//! Función para pintar texto basada en TextOut.
		/*!	Esta función pinta el texto utilizando la API TextOut.
				\fn		   void PintarTexto(DWLhDC &hDC, const TCHAR *nTexto, const int nX, const int nY, COLORREF nColorTexto, const bool nTransparente);
                \param[in] hDC           : Clase DWLhDC donde se va a pintar.
                \param[in] nTexto        : Texto que se va a pintar.
                \param[in] nX            : Coordenada X donde se va a pintar.
                \param[in] nY            : Coordenada Y donde se va a pintar.
                \param[in] nColorTexto   : Clase DWLColor con el color del texto.
                \param[in] nTransparente : Pintar el fondo transparente.
				\return	   No devuelve nada.
		*/
		void DWLFuente::PintarTexto(DWLhDC &hDC, const TCHAR *nTexto, const int nX, const int nY, DWLColor &nColorTexto, const bool nTransparente) { 
			HFONT Viejo = NULL; 
			if (_Fuente != (HFONT)GetCurrentObject(hDC.hDC(), OBJ_FONT)) { 
				Viejo = static_cast<HFONT>(SelectObject(hDC.hDC(), _Fuente)); 
			} 
			if (nTransparente == true) { 
				SetBkMode(hDC.hDC(), TRANSPARENT); 
			}
			SetTextColor(hDC.hDC(), nColorTexto()); 
			TextOut(hDC.hDC(), nX, nY, nTexto, static_cast<int>(DWLStrLen(nTexto))); 
			if (Viejo != NULL) { 
				SelectObject(hDC.hDC(), Viejo); 
			} 
		}; 

		//! Función para pintar texto con sombra basada en TextOut.
		/*!	Esta función pinta el texto con sombra utilizando la API TextOut.
				\fn		   void PintarTextoSombra(HDC hDC, const TCHAR *nTexto, const int nX, const int nY, COLORREF nColorTexto, COLORREF nColorSombra);
                \param[in] hDC           : hDC donde se va a pintar.
                \param[in] nTexto        : Texto que se va a pintar.
                \param[in] nX            : Coordenada X donde se va a pintar.
                \param[in] nY            : Coordenada Y donde se va a pintar.
                \param[in] nColorTexto   : Color del texto.
                \param[in] nColorSombra  : Color de la sombra.
				\return	   No devuelve nada.
		*/
        void DWLFuente::PintarTextoSombra(HDC hDC, const TCHAR *nTexto, const int nX, const int nY, COLORREF nColorTexto, COLORREF nColorSombra) { 
			HFONT Viejo = NULL;
			if (_Fuente != (HFONT)GetCurrentObject(hDC, OBJ_FONT)) { 
				Viejo = (HFONT)SelectObject(hDC, _Fuente); 
			} 
            int Tam = lstrlen(nTexto);
			SetBkMode(hDC, TRANSPARENT); 
			SetTextColor(hDC, nColorSombra); 
			TextOut(hDC, nX + 1, nY + 1, nTexto, Tam); 
			SetTextColor(hDC, nColorTexto); 
			TextOut(hDC, nX, nY, nTexto, Tam); 
			if (Viejo != NULL) SelectObject(hDC, Viejo);
		};  

		//! Función para pintar texto con sombra basada en TextOut.
		/*!	Esta función pinta el texto con sombra utilizando la API TextOut.
				\fn		   void PintarTextoSombra(DWLhDC &hDC, const TCHAR *nTexto, const int nX, const int nY, DWLColor &nColorTexto, DWLColor &nColorSombra);
                \param[in] hDC           : Clase DWLhDC donde se va a pintar.
                \param[in] nTexto        : Texto que se va a pintar.
                \param[in] nX            : Coordenada X donde se va a pintar.
                \param[in] nY            : Coordenada Y donde se va a pintar.
                \param[in] nColorTexto   : Clase DWLColor con el color del texto.
                \param[in] nColorSombra  : Clase DWLColor con el color de la sombra.
				\return	   No devuelve nada.
		*/
		void DWLFuente::PintarTextoSombra(DWLhDC &hDC, const TCHAR *nTexto, const int nX, const int nY, DWLColor &nColorTexto, DWLColor &nColorSombra) { 
			HFONT Viejo = NULL; 
			if (_Fuente != (HFONT)GetCurrentObject(hDC.hDC(), OBJ_FONT)) {
				Viejo = static_cast<HFONT>(SelectObject(hDC.hDC(), _Fuente)); 
			} 
            int Tam = lstrlen(nTexto);
			SetBkMode(hDC.hDC(), TRANSPARENT); 
			SetTextColor(hDC.hDC(), nColorSombra()); 
			TextOut(hDC.hDC(), nX + 1, nY + 1, nTexto, Tam); 
			SetTextColor(hDC.hDC(), nColorTexto()); 
			TextOut(hDC.hDC(), nX, nY, nTexto, Tam); 
			if (Viejo != NULL) { 
				SelectObject(hDC.hDC(), Viejo); 
			} 
		};




	};
};
