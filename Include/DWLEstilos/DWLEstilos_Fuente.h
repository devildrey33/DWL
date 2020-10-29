/*! \file DWLEstilos_Fuente.h
	\brief		 Archivo que contiene una clase para enlazar las fuentes globales con los controles extendidos.
    */
#ifndef DWL_ESTILOS_FUENTE_H
#define DWL_ESTILOS_FUENTE_H
 
#include "..\DWLString.h"

//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres Estilos
    namespace SO {

		//! Clase contenedora de una fuente para los controles extendidos
	    class DWLEstilos_Fuente {
		  public : /////////////////////// Miembros publicos
									    //! Constructor por defecto.
									    /*! Constructor por defecto.
											    \fn		DWLEstilos_Fuente(void);
											    \return	No devuelve nada.
									    */
										DWLEstilos_Fuente(void) : _Fuente(NULL), _FuenteEnlazada(NULL), _Nombre(), _Tam(0), _Grosor(0), _Cursiva(false), _SubRayada(false), _Tachada(false) { SOLO_DEBUG(_FuentesEnlazadas = 0); };
										//! Destructor.
										/*! Destructor que elimina de memoria las fuentes.
												\fn		~DWLEstilos_Fuente(void);
												\return	No devuelve nada.
										*/
									   ~DWLEstilos_Fuente(void);

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
										DWLEstilos_Fuente(const TCHAR *nNombre, const UINT nTam = 13, const UINT nGrosor = FW_NORMAL, const bool nCursiva = false, const bool nSubRayada = false, const bool nTachada = false);

									    //! Constructor copia que se enlaza a una DWLEstilos_Fuente.
									    /*! Constructor copia que se enlaza a una DWLEstilos_Fuente.
											    \fn		DWLEstilos_Fuente(DWL::SO::DWLEstilos_Fuente &nFuente);
											    \return	No devuelve nada.
									    */
                                        DWLEstilos_Fuente(DWL::SO::DWLEstilos_Fuente &nFuente);

									    //! Constructor copia que se enlaza a un HFONT.
									    /*! Constructor copia que se enlaza a un HFONT.
											    \fn		DWLEstilos_Fuente(HFONT &nFuente);
											    \return	No devuelve nada.
									    */
//                                        DWLEstilos_Fuente(HFONT &nFuente);

									    //! Operador = que se enlaza a una DWLEstilos_Fuente.
									    /*! Operador = que se enlaza a una DWLEstilos_Fuente.
											    \fn		DWLEstilos_Fuente &operator = (DWLEstilos_Fuente &nFuente);
											    \return	Devuelve la referencia de este objeto.
									    */
			DWLEstilos_Fuente          &operator = (DWLEstilos_Fuente &nFuente);

									    //! Operador = que se enlaza a un HFONT.
									    /*! Operador = que se enlaza a un HFONT.
											    \fn		DWLEstilos_Fuente &operator = (HFONT &nFuente);
											    \return	Devuelve la referencia de este objeto.
									    */
//			DWLEstilos_Fuente          &operator = (HFONT &nFuente);

									    //! Función con la que podemos enlazar una fuente del DWLEstilos con esta clase.
								        /*! Esta función se usa para enlazar esta fuente con una fuente de la clase DWLEstilos.
										    De esta forma varios controles pueden compartir una misma fuente.
											    \fn			inline void Enlazar(DWLEstilos_Fuente &FuenteNueva);
											    \param[in]	FuenteNueva : Referencia que apunta a una clase DWLEstilos_Fuente anteriormente creada.
											    \return		No devuelve nada.
											    \remarks	Cuando enlazamos esta clase a otra DWLEstilos_Fuente, las fuentes que pertenecian a esta clase son eliminadas de memoria.
									    */
	        void      					Enlazar(DWLEstilos_Fuente &FuenteNueva);

									    //! Función para crear una fuente.
									    /*! Esta función crea una fuente para esta clase.
											    \fn			void Crear(const TCHAR *nNombre, const UINT nTam = 13, const UINT nGrosor = FW_NORMAL);
											    \param[in]	nNombre	   : Nombre de la fuente a crear.
											    \param[in]  nTam	   : Tamaño de la fuente.
												\param[in]  nGrosor    : Grosor del texto que se pintara, (FW_NORMAL, FW_BOLD, etc...)
												\param[in]  nCursiva   : Texto Cursiva / Italic
												\param[in]  nSubRayada : Texto Sub-rayado
												\param[in]  nTachada   : Texto tachado
											    \return		No devuelve nada.
											    \remarks	Cuando creamos una fuente en esta clase realmente se crean 3 fuentes : una normal, una subrayada y la ultima en negrita.
									    */
	        void						Crear(const TCHAR *nNombre, const UINT nTam = 13, const UINT nGrosor = FW_NORMAL, const bool nCursiva = false, const bool nSubRayada = false, const bool nTachada = false);

									    //! Función que devuelve el tamaño de esta fuente.
									    /*! Esta función devuelve el tamaño de la fuente.
											    \fn		inline UINT Tam(void);
											    \return	Devuelve tamño del HFONT en pixeles.
									    */
			inline UINT                 Tam(void) { if (_FuenteEnlazada == NULL) return _Tam; else return _FuenteEnlazada->_Tam; };

									    //! Función que devuelve el grosor de esta fuente.
									    /*! Esta función devuelve el grosor de la fuente.
											    \fn		inline UINT Grosor(void);
											    \return	Devuelve el grosor del HFONT (FW_NORMAL, FW_BOLD, etc...).
									    */
			inline UINT                 Grosor(void) { if (_FuenteEnlazada == NULL) return _Grosor; else return _FuenteEnlazada->_Grosor; };

									    //! Función que devuelve si la fuente es cursiva.
									    /*! Esta función devuelve si la fuente es cursiva.
											    \fn		inline bool Cursiva(void);
											    \return	Devuelve true si la fuente es cursiva, false en caso contrario.
									    */
			inline bool                 Cursiva(void) { if (_FuenteEnlazada == NULL) return _Cursiva; else return _FuenteEnlazada->_Cursiva; };

									    //! Función que devuelve si la fuente esta sub-rayada.
									    /*! Esta función devuelve si la fuente esta sub-rayada.
											    \fn		inline bool SubRayada(void);
											    \return	Devuelve true si la fuente esta sub-rayada, false en caso contrario.
									    */
			inline bool                 SubRayada(void) { if (_FuenteEnlazada == NULL) return _SubRayada; else return _FuenteEnlazada->_SubRayada; };

									    //! Función que devuelve si la fuente esta tachada.
									    /*! Esta función devuelve si la fuente esta tachada.
											    \fn		inline bool Tachada(void);
											    \return	Devuelve true si la fuente esta tachada, false en caso contrario.
									    */
			inline bool                 Tachada(void) { if (_FuenteEnlazada == NULL) return _Tachada; else return _FuenteEnlazada->_Tachada; };

									    //! Función que devuelve el nombre de esta fuente.
									    /*! Esta función devuelve el nombre de la fuente.
											    \fn		inline UINT Nombre(void);
											    \return	Devuelve nombre del HFONT.
									    */
			inline const TCHAR         *Nombre(void) { if (_FuenteEnlazada == NULL) return _Nombre(); else return _FuenteEnlazada->_Nombre(); };

									    //! Operador () que retorna el HFONT.
									    /*! Operador () que retorna el HFONT tanto si esta enlazado, como si es propio.
											    \fn		inline HFONT operator () (void);
											    \return	Devuelve el HFONT que representa la fuente de esta clase.
									    */
			inline HFONT                operator () (void) { if (_FuenteEnlazada == NULL) return _Fuente; else return _FuenteEnlazada->_Fuente; };
		  private :
										//! HFONT que contiene la fuente
			HFONT                      _Fuente;
//			bool                       _FuentePropia;
										//! clase DWLEstilos_Fuente enlazada
			DWLEstilos_Fuente         *_FuenteEnlazada;
										//! Nombre de la fuente (esta vacio si es enlazada)
			DWL::DWLString             _Nombre;
										//! Tamaño de la fuente (0 si esta enlazada)
			UINT                       _Tam;
										//! Grosor (0 si esta enlazada)
			UINT                       _Grosor;
										//! Cursiva (false si esta enlazada)
			bool					   _Cursiva;
										//! Sub-Rayada (false si esta enlazada)
			bool                       _SubRayada;
										//! Tachada (false si esta enlazada)
			bool                       _Tachada;
										//! Numero de fuentes enlazadas (SOLO PARA DEBUG)
			SOLO_DEBUG(UINT            _FuentesEnlazadas);
		};
	    ////////////////////////////////// Fin DWLEstilos_Fuente
    };
};

#endif
