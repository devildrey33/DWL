#ifndef DWL_LISTAEX_ITEM_H
#define DWL_LISTAEX_ITEM_H

#include "DWLListaEx_DatosSubItem.h"
#include <vector>
 
namespace DWL {
	namespace ControlesEx {
		//! Clase nucleo para la ListaEx
		class DWLListaEx_Nucleo;
		//! Clase que une DWLBaseControlEx con DWLListaEx_Nucleo, para formar un control ListaEx
		class DWLListaEx;

		//! Clase que contiene un Item de la ListaEx
		class DWLListaEx_Item {
		public : ///////////////////////////////////// Metodos publicos

													//! Constructor por defecto.
													/*! Constructor por defecto.
															\fn			DWLListaEx_Item(void);
															\return		No devuelve nada.
													*/
													DWLListaEx_Item(void);

													//! Constructor asignador.
													/*! Constructor asignador.
															\fn			DWLListaEx_Item(DWLListaEx_Nucleo *LE);
															\param[in]	LE : Puntero a la ListaEx que contiene este item.
															\return		No devuelve nada.
													*/
													DWLListaEx_Item(DWLListaEx_Nucleo *LE);

													//! Destructor.
													/*! Destructor.
															\fn			~DWLListaEx_Item(void);
															\return		No devuelve nada.
													*/
												   ~DWLListaEx_Item(void);

													//! Funci�n para asignar el texto del item / subitem
													/*! Esta funci�n asigna el texto del item / subitem especificado.
															\fn			void Texto(const unsigned int nColumna, const TCHAR *nTxt, const bool nRepintar = true);
															\param[in]	nColumna	: Numero de columna al que pertenece el item / subitem.
															\param[in]	nTxt		: Nuevo texto para el item / subitem.
															\param[in]	nRepintar	: Valor que especifica si la ListaEx debe repintarse.
															\return		No devuelve nada.
													*/
		 void										Texto(const unsigned int nColumna, const TCHAR *nTxt, const bool nRepintar = true);

													//! Funci�n que retorna el texto del item / subitem
													/*! Esta funci�n devuelve el texto del item / subitem especificado.
															\fn			inline const TCHAR *Texto(const unsigned int nColumna);
															\param[in]	nColumna	: Numero de columna al que pertenece el item / subitem.
															\return		Devuelve un puntero a la cadena de texto del item / subitem especificado.
													*/
		 inline const TCHAR						   *Texto(const unsigned int nColumna = 0) {
														return _SubItems[nColumna]->Texto();
													};

													//! Funci�n que retorna la longitud del texto del item / subitem en caracteres.
													/*! Esta funci�n devuelve la longitud del texto del item / subitem especificado en caracteres.
															\fn			inline UINT LongitudTexto(const int nColumna) const;
															\param[in]	nColumna : Numero de columna al que pertenece el item / subitem.
															\return		Devuelve el total de caracteres que tiene el texto del item / subitem especificado.
													*/
		 inline UINT            					LongitudTexto(const int nColumna = 0) const {
														return static_cast<UINT>(_SubItems[nColumna]->Texto.Tam());
													};

													//! Funci�n que asigna el icono del item.
													/*! Esta funci�n asigna el icono del item.
															\fn			void Icono(const int nIko, const bool nRepintar = true);
															\param[in]	nIko		: ID de los recursos para el icono que queremos a�adir.
															\param[in]	nRepintar	: Valor que especifica si la ListaEx debe repintarse.
															\return		No devuelve nada.
													*/
		 void										Icono(const int nIko, const bool nRepintar = true);

													//! Funci�n que retorna el icono del item.
													/*! Esta funci�n devuelve el icono del item.
															\fn			inline int Icono(void) const;
															\return		Devuelve el icono del item.
													*/
		 inline int							        Icono(void) const {
														return _Icono;
													};

													//! Funci�n que asigna el estado de selecci�n para este item.
													/*! Esta funci�n asigna el estado de selecci�n para este item.
															\fn			void Seleccionado(const bool nSel, const bool nRepintar = true);
															\param[in]	nSel		: True para que el item este seleccionado, false para lo contrario.
															\param[in]	nRepintar	: Valor que especifica si la ListaEx debe repintarse.
															\return		No devuelve nada.
													*/
		 void										Seleccionado(const bool nSel, const bool nRepintar = true);

													//! Funci�n que retorna el estado de selecci�n del item.
													/*! Esta funci�n devuelve el estado de selecci�n del item.
															\fn			inline bool Seleccionado(void) const;
															\return		Devuelve true si el item esta seleccionado, false en caso contrario.
													*/
		 inline bool							    Seleccionado(void) const {
														return _Seleccionado;
													};

													//! Funci�n que retorna la posici�n del item dentro del vector de items de la ListaEx.
													/*! Esta funci�n devuelve la posici�n del item dentro del vector de items de la ListaEx.
															\fn			int Posicion(void);
															\return		Devuelve la posicion del item dentro del vector de items de la ListaEx.
													*/
		 int									    Posicion(void);

													//! Funci�n para hacer visible este item en la ListaEx.
													/*! Esta funci�n hace visible este item en la ListaEx.
															\fn			void HacerVisible(void);
															\return		No devuelve nada.
															\remarks	Esta funcion mira si el item se ve en la lista, en caso contrario ajusta el scroll para que se vea.
													*/
		 void										HacerVisible(void);

													//! Funci�n que retorna el item anterior.
													/*! Esta funci�n devuelve el item anterior a este.
															\fn			inline DWLListaEx_Item *Anterior(void);
															\return		Devuelve el item anterior a este.
															\sa			Siguiente()
													*/
		 inline DWLListaEx_Item				       *Anterior(void) {
														return _Anterior;
													};

													//! Funci�n que retorna el item siguiente.
													/*! Esta funci�n devuelve el item siguiente a este.
															\fn			inline DWLListaEx_Item *Siguiente(void);
															\return		Devuelve el item siguiente a este.
															\sa			Anterior()
													*/
		 inline DWLListaEx_Item				       *Siguiente(void) {
														return _Siguiente;
													};

													//! Funci�n que retorna el subitem especificado.
													/*! Esta funci�n devuelve un puntero a la clase DWLListaEx_DatosSubItem que corresponde con el subitem especificado.
															\fn			inline DWLListaEx_DatosSubItem *SubItem(const int Pos);
															\param[in]	nPos : Posici�n del subitem que queremos obtener.
															\return		Devuelve un puntero a la clase DWLListaEx_DatosSubItem que corresponde con el subitem especificado.
															\sa			DWL::ControlesEx::DWLListaEx_DatosSubItem
													*/
		 inline DWLListaEx_DatosSubItem		       *SubItem(const int nPos) {
														return _SubItems[nPos];
													};
		 protected : ////////////////////////////// Miembros protegidos

													//! Datos de los SubItems
		 std::vector<DWLListaEx_DatosSubItem *>    _SubItems;

													//! Icono del item
		 int									   _Icono;

													//! Ancho del texto (solo se calcula en modo DWL_LISTAEX_FILAS_HORIZONTAL)
		 int									   _Ancho;

													//! Estado de selecion
		 bool									   _Seleccionado;

													//! Item Anterior a este
		 DWLListaEx_Item						  *_Anterior;

													//! Item Siguiente a este
		 DWLListaEx_Item						  *_Siguiente;

													//! DWLListaEx padre
		 DWLListaEx_Nucleo			              *_ListaEx;
          private : //////////////////////////////////

                                                    //! Constructor copia des-habilitado
                                                    DWLListaEx_Item(const DWLListaEx_Item &) : _SubItems(), _Icono(0), _Ancho(0), _Seleccionado(false), _Anterior(NULL), _Siguiente(NULL), _ListaEx(NULL) { };
                                                    //! Operador = des-habilitado
		 inline DWLListaEx_Item                    &operator=(const DWLListaEx_Item &) { return *this; };

		 friend class							    DWLListaEx;
		 friend class								DWLListaEx_Nucleo;
		};											//
		////////////////////////////////////////////// Final DWLListaEx_Item

    };
};

#endif

