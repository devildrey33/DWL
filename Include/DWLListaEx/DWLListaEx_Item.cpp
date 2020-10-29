#include "DWLListaEx_Item.h"
#include "DWLListaEx_Nucleo.h"

namespace DWL {
	namespace ControlesEx {

		//! Constructor por defecto.
		/*! Constructor por defecto.
				\fn			DWLListaEx_Item(void);
				\return		No devuelve nada.
		*/
        DWLListaEx_Item::DWLListaEx_Item(void) : _SubItems(), _Icono(0), _Ancho(0), _Seleccionado(false), _Anterior(NULL), _Siguiente(NULL), _ListaEx(NULL) {
		};


		//! Constructor asignador.
		/*! Constructor asignador.
				\fn			DWLListaEx_Item(DWLListaEx_Nucleo *LE);
				\param[in]	LE : Puntero a la ListaEx que contiene este item.
				\return		No devuelve nada.
		*/
		DWLListaEx_Item::DWLListaEx_Item(DWLListaEx_Nucleo *LE)  : _SubItems(), _Icono(0), _Ancho(0), _Seleccionado(false), _Anterior(NULL), _Siguiente(NULL), _ListaEx(LE) {
		}


		//! Destructor.
		/*! Destructor.
				\fn		   ~DWLListaEx_Item(void);
				\return		No devuelve nada.
		*/
		DWLListaEx_Item::~DWLListaEx_Item(void) {
			for (unsigned int i = 0; i < _SubItems.size(); i++) {
				delete _SubItems[i];
                _SubItems[i] = NULL;
			}
		}

		//! Función para asignar el texto del item / subitem
		/*! Esta función asigna el texto del item / subitem especificado.
				\fn			void Texto(const unsigned int nColumna, const TCHAR *nTxt, const bool nRepintar = true);
				\param[in]	nColumna	: Numero de columna al que pertenece el item / subitem.
				\param[in]	nTxt		: Nuevo texto para el item / subitem.
				\param[in]	nRepintar	: Valor que especifica si la ListaEx debe repintarse.
				\return		No devuelve nada.
		*/
		void DWLListaEx_Item::Texto(const unsigned int Columna, const TCHAR *Txt, const bool nRepintar)  {
			_SubItems[Columna]->Texto = Txt;
			if (nRepintar == true) _ListaEx->Repintar(true);
		}

		//! Función que asigna el icono del item.
		/*! Esta función asigna el icono del item.
				\fn			void Icono(const int nIko, const bool nRepintar = true);
				\param[in]	nIko		: ID de los recursos para el icono que queremos añadir.
				\param[in]	nRepintar	: Valor que especifica si la ListaEx debe repintarse.
				\return		No devuelve nada.
		*/
		void DWLListaEx_Item::Icono(const int nIko, const bool nRepintar) {
			_Icono = nIko;
			if (nRepintar == true) _ListaEx->Repintar(true);
		}

		//! Función para hacer visible este item en la ListaEx.
		/*! Esta función hace visible este item en la ListaEx.
				\fn			void HacerVisible(void);
				\return		No devuelve nada.
				\remarks	Esta funcion mira si el item se ve en la lista, en caso contrario ajusta el scroll para que se vea.
		*/
		void DWLListaEx_Item::HacerVisible(void) {
			_ListaEx->ListaEx_MostrarItem(this);
		}


		//! Función que retorna el estado de selección del item.
		/*! Esta función devuelve el estado de selección del item.
				\fn			inline const bool Seleccionado(void);
				\return		Devuelve true si el item esta seleccionado, false en caso contrario.
		*/
		void DWLListaEx_Item::Seleccionado(const bool Sel, const bool nRepintar) {
			_Seleccionado = Sel;
			if (nRepintar == true) _ListaEx->Repintar(true);
		}


		//! Función que retorna la posición del item dentro del vector de items de la ListaEx.
		/*! Esta función devuelve la posición del item dentro del vector de items de la ListaEx.
				\fn			int Posicion(void);
				\return		Devuelve la posicion del item dentro del vector de items de la ListaEx.
		*/
		int DWLListaEx_Item::Posicion(void) {
			int i = 0;
			for (i = _ListaEx->ListaEx_TotalItems() -1; i >-1; i--) {
				if (_ListaEx->ListaEx_Item(i) == this) return i;
			}
			return i;
		}

    };
};

