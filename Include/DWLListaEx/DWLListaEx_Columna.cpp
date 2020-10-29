#include "DWLListaEx_Columna.h"
#include "DWLListaEx_Nucleo.h"
 
namespace DWL {
	namespace ControlesEx {

		//! Constructor por defecto.
		/*! Constructor por defecto.
				\fn			DWLListaEx_Columna(void);
				\return		No devuelve nada.
		*/
		DWLListaEx_Columna::DWLListaEx_Columna(void) : _Colores(NULL), _Fuentes(NULL), _Alineacion(0), _Ancho(DWL_LISTAEX_ANCHO_AUTOMATICO), _Nombre(), _Estado(DWL_LISTAEX_ESTADO_NORMAL), _ListaEx(NULL) {
		};

	    //! Constructor asignador.
	    /*! Constructor asignador.
			    \fn			DWLListaEx_Columna(DWLListaEx_Nucleo *LE);
			    \param[in]	LE : Puntero a la ListaEx que contiene esta columna.
			    \return		No devuelve nada.
	    */
		DWLListaEx_Columna::DWLListaEx_Columna(DWLListaEx_Nucleo *LE) : _Fuentes(NULL), _Colores(NULL), _Alineacion(0), _Ancho(DWL_LISTAEX_ANCHO_AUTOMATICO), _Nombre(), _Estado(DWL_LISTAEX_ESTADO_NORMAL), _ListaEx(LE) {
		}

		//! Destructor.
		/*! Destructor.
				\fn			~DWLListaEx_Columna(void);
				\return		No devuelve nada.
		*/
        DWLListaEx_Columna::~DWLListaEx_Columna(void) {
		   if (_Colores != NULL) delete _Colores;
		   if (_Fuentes != NULL) delete _Fuentes;
		};


		//! Función que asigna el ancho de esta columna.
		/*! Esta función asigna el ancho de esta columna.
				\fn			void Ancho(const int nAncho, const bool nRepintar = true);
				\param[in]	nAncho		: Nuevo ancho en pixeles para esta columna.
				\param[in]	nRepintar	: Valor que especifica si la ListaEx debe repintarse.
				\return		No devuelve nada.
		*/
		void DWLListaEx_Columna::Ancho(const int nAncho, const bool nRepintar) {
			_Ancho = nAncho;
			if (nRepintar == true) _ListaEx->Repintar(true);
		}

		//! Función que asigna la alineación del texto.
		/*! Esta función asigna la alineación del texto.
				\fn			void Alineacion(const int nAlineacion);
				\param[in]	nAlineacion : Parametro en el que especificamos la nueva alineacion, que puede ser : DWL_LISTAEX_TEXTO_IZQUIERDA, DWL_LISTAEX_TEXTO_CENTRADO y DWL_LISTAEX_TEXTO_DERECHA.
				\return		No devuelve nada.
		*/
		void DWLListaEx_Columna::Alineacion(const int nAlineacion) {
			_Alineacion = nAlineacion;
			_ListaEx->Repintar(true);
		};

    };
};

