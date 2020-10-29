// Modulo que contiene la clase DWLFuente que es un derivado del objeto HFONT de windows.
// Esta clase se ha creado pensando en facilitar la vida al programador, por ello incluye Funciónes para interactuar con varios objetos.
// Ultima modificación 28/04/2009
// Version 1.0
 
// PENDIENTE DE REVISION

#ifndef DWL_GDI_FUENTE_H
#define DWL_GDI_FUENTE_H

#include "DWLEnumsGDI.h"
//#include "DWLhDC.h"

//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres GDI
	namespace GDI {
        class DWLhDC;
        class DWLColor;

		//! Clase que encapsula un objeto HFONT
		class DWLFuente {
		public: ////////// Miembros publicos

						//! Constructor.
						/*!	Constructor por defecto.
								\fn		DWLFuente(void);
								\return	No devuelve nada.
						*/
						DWLFuente(void) : _Fuente(NULL) {
						};

						//! Constructor que crea una fuente segun el nombre, tamaño, y demas parametros especificados.
						/*!	Constructor que crea una fuente segun el nombre, tamaño, y demas parametros especificados.
								\fn		   DWLFuente(const TCHAR *nNombre, const int nTam, const bool nNegrita = false, const bool nSubrayada = false, const bool nCursiva = false, const bool nTachada = false);
                                \param[in] nNombre    : Nombre de la fuente.
                                \param[in] nTam       : Tamaño de la fuente.
                                \param[in] nNegrita   : Fuente en negrita.
                                \param[in] nSubrayada : Fuente subrayada.
                                \param[in] nCursiva   : Fuente cursiva.
                                \param[in] nTachada   : Fuente tachada.
								\return	   No devuelve nada.
						*/
					    DWLFuente(const TCHAR *nNombre, const int nTam, const bool nNegrita = false, const bool nSubrayada = false, const bool nCursiva = false, const bool nTachada = false) : _Fuente(NULL) {
							_Fuente = CreateFont(nTam, 0, 0, 0, (nNegrita == false) ? FW_NORMAL : FW_BOLD, nCursiva, nSubrayada, nTachada, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_ROMAN, nNombre);
						};

						//! Destructor.
						/*!	Destructor.
								\fn		~DWLBrocha(void);
								\return	No devuelve nada.
						*/
					   ~DWLFuente(void) {
							if (_Fuente != NULL) DeleteObject(_Fuente);
						};

						//! Función para borrar la fuente.
						/*!	Esta función borra la fuente.
								\fn		inline void Borrar(void);
								\return	No devuelve nada.
						*/
		 inline void    Borrar(void) {
							if (_Fuente != NULL) DeleteObject(_Fuente);
							_Fuente = NULL;
						};

						//! Función que crea una fuente segun el nombre, tamaño, y demas parametros especificados.
						/*!	Esta función crea una fuente segun el nombre, tamaño, y demas parametros especificados.
								\fn		   inline void CrearFuente(TCHAR *nNombre, const int Tam = 13, const bool Negrita = false, const bool Subrayada = false, const bool Cursiva = false, const bool Tachada = false);
                                \param[in] nNombre    : Nombre de la fuente.
                                \param[in] nTam       : Tamaño de la fuente.
                                \param[in] nNegrita   : Fuente en negrita.
                                \param[in] nSubrayada : Fuente subrayada.
                                \param[in] nCursiva   : Fuente cursiva.
                                \param[in] nTachada   : Fuente tachada.
								\return	   No devuelve nada.
						*/
		 inline void    CrearFuente(TCHAR *nNombre, const int Tam = 13, const bool Negrita = false, const bool Subrayada = false, const bool Cursiva = false, const bool Tachada = false) {
							if (_Fuente != NULL) DeleteObject(_Fuente);
							_Fuente = CreateFont(Tam, 0, 0, 0, ((Negrita == false) ? FW_NORMAL : FW_BOLD), Cursiva, Subrayada, Tachada, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_ROMAN, nNombre);
						};

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
		 void           PintarTexto(HDC hDC, const TCHAR *nTexto, const int nX, const int nY, COLORREF nColorTexto, const bool nTransparente);

						//! Función para pintar texto basada en TextOut.
						/*!	Esta función pinta el texto utilizando la API TextOut.
								\fn		   void PintarTexto(DWLhDC &hDC, const TCHAR *nTexto, const int nX, const int nY, DWLColor &nColorTexto, const bool nTransparente);
                                \param[in] hDC           : Clase DWLhDC donde se va a pintar.
                                \param[in] nTexto        : Texto que se va a pintar.
                                \param[in] nX            : Coordenada X donde se va a pintar.
                                \param[in] nY            : Coordenada Y donde se va a pintar.
                                \param[in] nColorTexto   : Clase DWLColor con el color del texto.
                                \param[in] nTransparente : Pintar el fondo transparente.
								\return	   No devuelve nada.
						*/
		 void           PintarTexto(DWLhDC &hDC, const TCHAR *nTexto, const int nX, const int nY, DWLColor &nColorTexto, const bool nTransparente);

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
		 void           PintarTextoSombra(HDC hDC, const TCHAR *nTexto, const int nX, const int nY, COLORREF nColorTexto, COLORREF nColorSombra);

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
		 void           PintarTextoSombra(DWLhDC &hDC, const TCHAR *nTexto, const int nX, const int nY, DWLColor &nColorTexto, DWLColor &nColorSombra);

					    //! Función que retorna el HFONT de esta clase.
					    /*!	Esta función retorna el HFONT de esta clase.
							    \fn		   inline HFONT Fuente(void);
							    \return    Devuelve el HFONT que contiene esta clase.
					    */
		 inline HFONT   Fuente(void) {
							return _Fuente;
						};

					    //! Operador que retorna el HFONT de esta clase.
					    /*!	Este operador retorna el HFONT de esta clase.
							    \fn		   inline HFONT operator () (void);
							    \return    Devuelve el HFONT que contiene esta clase.
					    */
		 inline HFONT   operator () (void) {
							return _Fuente;
						};

		private: ///////// Miembros privados

                        // Constructor copia des-habilitado
                        DWLFuente(const DWL::GDI::DWLFuente &) : _Fuente(NULL) { };
                        // Operador = des-habilitado
		 inline HFONT   operator=(const DWL::GDI::DWLFuente &) { };

					    //! Fuente de esta clase
		 HFONT         _Fuente;
		};
		////////////////// Fin DWLFuente


	};
};

#endif
