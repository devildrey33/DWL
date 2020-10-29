#ifndef DWL_LISTAEX_PARAMETROSLABELEDIT_H
#define DWL_LISTAEX_PARAMETROSLABELEDIT_H

#include "DWLListaEx_Item.h"
#include "..\DWLString.h"
 
namespace DWL {
	namespace ControlesEx {

		//! Clase contenedora de los datos que se pueden necesitar al terminar la edicion de un item / subitem
		class DWLListaEx_ParametrosLabelEdit {
		public : ///////////////////////////////// Miembros publicos

                                                //! Constructor por defecto.
                                                /*!	Constructor por defecto.
                                                        \fn			DWLListaEx_ParametrosLabelEdit(void);
                                                        \return		No devuelve nada.
                                                */
                                                DWLListaEx_ParametrosLabelEdit(void) : Cancelar(false), NuevoTexto(), _Item(NULL), _NumItem(0), _NumSubItem(0) {
                                                    Cancelar = false;
                                                };

                                                //! Constructor asignador de datos.
                                                /*!	Constructor asignador de datos.
                                                        \fn			DWLListaEx_ParametrosLabelEdit(DWLListaEx_Item *nItem, const UINT nNumItem, const UINT nNumSubItem, const TCHAR *nNuevoTexto);
                                                        \param[in]	nItem		: Item que se esta editando.
                                                        \param[in]	nNumItem	: Posici?n del item que se esta editando.
                                                        \param[in]	nNumSubItem	: Posici?n del subitem que se esta editando.
                                                        \param[in]	nNuevoTexto : Nuevo texto para el item.
                                                        \return		No devuelve nada.
                                                */
                                                DWLListaEx_ParametrosLabelEdit(DWLListaEx_Item *nItem, const UINT nNumItem, const UINT nNumSubItem, const TCHAR *nNuevoTexto/*, const UINT nID*/)  : Cancelar(false), _Item(nItem), _NumItem(nNumItem), _NumSubItem(nNumSubItem) {
													NuevoTexto = nNuevoTexto;
												};

                                                //! Destructor.
                                                /*!	Destructor.
                                                        \fn		   ~DWLListaEx_ParametrosLabelEdit(void);
                                                        \return		No devuelve nada.
                                                */
                                               ~DWLListaEx_ParametrosLabelEdit(void) {
                                                };

                                                //! Funci?n que retorna la posici?n del item que se esta editando.
                                                /*!	Esta funci?n devuelve la posici?n del item que se esta editando.
                                                        \fn			inline UINT NumItem(void) const;
                                                        \return		Devuelve la posicion del item que se esta editando.
                                                */
		 inline UINT			                NumItem(void) const {
                                                    return _NumItem;
                                                };

                                                //! Funci?n que retorna la posici?n del subitem que se esta editando.
                                                /*!	Esta funci?n devuelve la posici?n del subitem que se esta editando.
                                                        \fn			inline UINT NumSubItem(void) const;
                                                        \return		Devuelve la posicion del subitem que se esta editando.
                                                */
         inline UINT		    	            NumSubItem(void) const {
                                                    return _NumSubItem;
                                                };

                                                //! Funci?n que retorna un puntero al DWLListaEx_Item correspondiente a este item en edici?n.
                                                /*!	Esta funci?n devuelve un puntero al DWLListaEx_Item correspondiente a este item en edici?n.
                                                        \fn			inline DWLListaEx_Item *Item(void);
                                                        \return		Devuelve el DWLListaEx_Item correspondiente al item en edicion.
                                                */
		 inline DWLListaEx_Item                *Item(void) {
                                                    return _Item;
                                                };

                                                //! Función que retorna la ID correspondiente a la ListaEx que manda el mensaje.
                                                /*!	Esta función devuelve la ID correspondiente a la ListaEx que manda el mensaje.
                                                        \fn			inline const UINT ID(void);
                                                        \return		Devuelve la ID de la ListaEx que manda el mensaje.
                                                */
/*         inline const UINT                    ID(void) {
                                                    return _ID;
                                                };*/

                                                //! Estado de cancelacion para esta edicion
		 bool						            Cancelar;

                                                //! Nuevo texto que se va a aplicar
		 DWL::DWLString				            NuevoTexto;
		private : //////////////////////////////// Miembros privados

                                                //! ID de la lista que manda el mensaje
//		 const UINT                            _ID;

                                                //! Clase DWLListaEx_Item que contiene el item / subitem que se esta editando
		 DWLListaEx_Item                      *_Item;

                                                //! Numero del item actualmente en edicion
		 UINT                                  _NumItem;

                                                //! Numero del sub item actualmente en edicion
		 UINT                                  _NumSubItem;

                                                //! Constructor copia des-habilitado
                                                DWLListaEx_ParametrosLabelEdit(DWLListaEx_ParametrosLabelEdit &)  : Cancelar(false), NuevoTexto(), _Item(NULL), _NumItem(0), _NumSubItem(0) { };

                                                //! Operador = des-habilitado
		 inline DWLListaEx_ParametrosLabelEdit &operator=(DWLListaEx_ParametrosLabelEdit &) { return *this; };
		};							//
		////////////////////////////// Fin DWLListaEx_ParametrosLabelEdit

    };
};

#endif
