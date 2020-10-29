/*! \file DWLEstilos_Fuente.cpp
	\brief		 Archivo que contiene una clase para enlazar las fuentes globales con los controles extendidos.
    */ 
#ifndef DWL_ESTILOS_FUENTE_CPP
#define DWL_ESTILOS_FUENTE_CPP

#include "..\DWLEstilos.h"

//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres SO
    namespace SO {


		//! Constructor creador de fuente.
		/*! Constructor creador de fuente.
				\fn			DWLEstilos_Fuente(const TCHAR *nNombre, const int nTam = 13);
				\param[in]	nNombre : Nombre de la fuente.
				\param[in]	nTam	: Tamaño de la fuente.
				\param[in]  nGrosor : Grosor del texto que se pintara, (FW_NORMAL, FW_BOLD, etc...)
				\param[in]  nCursiva   : Texto Cursiva / Italic
				\param[in]  nSubRayada : Texto Sub-rayado
				\param[in]  nTachada   : Texto tachado
				\return		No devuelve nada.
				\remarks	Este constructor inicia las fuentes internas segun el nombre y tamaños especificados.
		*/
        DWLEstilos_Fuente::DWLEstilos_Fuente(const TCHAR *nNombre, const UINT nTam, const UINT nGrosor, const bool nCursiva, const bool nSubRayada, const bool nTachada) : 
			_Tam(nTam), _Grosor(nGrosor), _FuenteEnlazada(NULL), _Nombre(nNombre), _Cursiva(nCursiva), _Tachada(nTachada), _SubRayada(nSubRayada) {
				SOLO_DEBUG(_FuentesEnlazadas = 0;);
			    _Fuente = CreateFont(nTam, 0, 0, 0, FW_NORMAL, nCursiva, nSubRayada, nTachada, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_ROMAN, nNombre);
	    };

		//! Constructor copia que se enlaza a una DWLEstilos_Fuente.
		/*! Constructor copia que se enlaza a una DWLEstilos_Fuente.
				\fn		DWLEstilos_Fuente(DWL::SO::DWLEstilos_Fuente &nFuente);
				\return	No devuelve nada.
		*/
        DWLEstilos_Fuente::DWLEstilos_Fuente(DWL::SO::DWLEstilos_Fuente &nFuente) : 
			_Fuente(NULL), _Cursiva(false), _Tachada(false), _SubRayada(false), _FuenteEnlazada(&nFuente), _Tam(0), _Grosor(0) {  
				SOLO_DEBUG(_FuentesEnlazadas = 0;);
		};

	    //! Destructor.
	    /*! Destructor que elimina de memoria las fuentes.
			    \fn		~DWLEstilos_Fuente(void);
			    \return	No devuelve nada.
	    */
        DWLEstilos_Fuente::~DWLEstilos_Fuente(void) {
			if (_Fuente != NULL) DeleteObject(_Fuente);
			SOLO_DEBUG(
				if (_FuenteEnlazada != NULL) {
					if (_FuenteEnlazada->_FuentesEnlazadas != 0) _FuenteEnlazada->_FuentesEnlazadas --;
				}
			);
	    };

		//! Operador = que se enlaza a una DWLEstilos_Fuente.
		/*! Operador = que se enlaza a una DWLEstilos_Fuente.
				\fn		DWLEstilos_Fuente &operator = (DWLEstilos_Fuente &nFuente);
				\return	Devuelve la referencia de este objeto.
		*/
		DWLEstilos_Fuente &DWLEstilos_Fuente::operator = (DWLEstilos_Fuente &nFuente) {
			if (_Fuente != NULL) {
				SOLO_DEBUG(if (_FuentesEnlazadas != 0) _ASSERT(0));
				DeleteObject(_Fuente);
				_Fuente = NULL;
			}
			SOLO_DEBUG(_FuentesEnlazadas = 0);
			SOLO_DEBUG(if (_FuenteEnlazada != NULL) _FuenteEnlazada->_FuentesEnlazadas --);
			_FuenteEnlazada = &nFuente;
			return *this;
		};

	    //! Función con la que podemos enlazar una fuente del DWLEstilos con esta clase.
        /*! Esta función se usa para enlazar esta fuente con una fuente de la clase DWLEstilos.
		    De esta forma varios controles pueden compartir una misma fuente.
			    \fn			void Enlazar(DWLEstilos_Fuente &FuenteNueva);
			    \param[in]	FuenteNueva : Referencia que apunta a una clase DWLEstilos_Fuente anteriormente creada.
			    \return		No devuelve nada.
			    \remarks	Cuando enlazamos esta clase a otra DWLEstilos_Fuente, las fuentes que pertenecian a esta clase son eliminadas de memoria.
	    */
        void DWLEstilos_Fuente::Enlazar(DWLEstilos_Fuente &FuenteNueva) {
			if (_Fuente != NULL) {
				SOLO_DEBUG(if (_FuentesEnlazadas != 0) _ASSERT(0));
				DeleteObject(_Fuente);
				_Fuente = NULL;
			}
			SOLO_DEBUG( _FuentesEnlazadas = 0;
						if (_FuenteEnlazada != NULL) { 
							if (_FuenteEnlazada->_FuentesEnlazadas != 0) _FuenteEnlazada->_FuentesEnlazadas --; 
						}
			);
			_FuenteEnlazada = &FuenteNueva;
	    };

	    //! Función para crear una fuente.
	    /*! Esta función crea una fuente para esta clase.
			    \fn			void Crear(const TCHAR *nNombre, const int Tam = 13);
			    \param[in]	nNombre	: Nombre de la fuente a crear.
			    \param[in]  nTam	: Tamaño de la fuente.
			    \return		No devuelve nada.
			    \remarks	Cuando creamos una fuente en esta clase realmente se crean 3 fuentes : una normal, una subrayada y la ultima en negrita.
	    */
        void DWLEstilos_Fuente::Crear(const TCHAR *nNombre, const UINT nTam, const UINT nGrosor, const bool nCursiva, const bool nSubRayada, const bool nTachada) {
			if (_Fuente != NULL) {
				SOLO_DEBUG(if (_FuentesEnlazadas != 0) _ASSERT(0));
				DeleteObject(_Fuente);
				_Fuente = NULL;
			}
			SOLO_DEBUG(	_FuentesEnlazadas = 0;
						if (_FuenteEnlazada != NULL) {
							if (_FuenteEnlazada->_FuentesEnlazadas != 0) _FuenteEnlazada->_FuentesEnlazadas --;
						}
			);
			_FuenteEnlazada = NULL;
			_Tam			= nTam;
			_Grosor			= nGrosor;
			_Cursiva		= nCursiva;
			_SubRayada		= nSubRayada;
			_Tachada		= nTachada;
			_Fuente			= CreateFont(_Tam, 0, 0, 0, _Grosor, _Cursiva, _SubRayada, _Tachada, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_ROMAN, nNombre);
	    };

    };
};

#endif
