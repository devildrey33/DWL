#ifndef DWL_LISTAEX_PARAMETROSCLICK_H
#define DWL_LISTAEX_PARAMETROSCLICK_H

#include "DWLListaEx_Item.h"

 
namespace DWL {
	namespace ControlesEx {
		//! Clase que contiene los parametros de un click para pasarlos a la función de su ventana padre.
		class DWLListaEx_ParametrosClick {
		 public : //////////////////////////////// Miembros publicos

                                                //! Constructor.
                                                /*!	Constructor por defecto.
                                                        \fn			DWLListaEx_ParametrosClick(void);
                                                        \return		No devuelve nada.
                                                */
                                                DWLListaEx_ParametrosClick(void) : _Item(NULL), _X(0), _Y(0), _IDListaEx(0), _Boton(0) {
                                                };

                                                //! Constructor que define todos los valores
                                                /*!	Constructor asignador de datos.
                                                        \fn			DWLListaEx_ParametrosClick(DWLListaEx_Item *nItem, const int cX, const int cY, const int cID, const int nBoton);
                                                        \param[in]	nItem	: Item que se ha presionado / soltado.
                                                        \param[in]	cX		: Coordenada X del mouse.
                                                        \param[in]	cY		: Coordenada Y del mouse.
                                                        \param[in]	cID		: ID de la ListaEx.
                                                        \param[in]	cBoton	: Boton del mouse presionado / soltado.
                                                        \return		No devuelve nada.
                                                */
                                                DWLListaEx_ParametrosClick(DWLListaEx_Item *nItem, const int cX, const int cY, const UINT cID, const UINT nBoton)  : _Item(nItem), _X(cX), _Y(cY), _IDListaEx(cID), _Boton(nBoton) {
                                                };

                                                //! Destructor.
                                                /*!	Destructor.
                                                        \fn			~DWLArbolEx_ParametrosClick(void);
                                                        \return		No devuelve nada.
                                                */
                                               ~DWLListaEx_ParametrosClick(void) {
                                                };

                                                //! Función que retorna el item.
                                                /*!	Esta funcion devuelve el item presionado / soltado.
                                                        \fn			inline DWLListaEx_Item *Item(void);
                                                        \return		Devuelve el item presionado / soltado.
                                                */
		 inline DWLListaEx_Item                *Item(void) {
                                                    return _Item;
                                                };

                                                //! Función que retorna la coordenada X del mouse.
                                                /*!	Esta funcion devuelve la coordenada X del mouse.
                                                        \fn			inline int X(void) const;
                                                        \return		Devuelve la coordenada X del mouse.
                                                */
		 inline int			                    X(void) const {
                                                    return _X;
                                                };

                                                //! Función que retorna la coordenada Y del mouse.
                                                /*!	Esta funcion devuelve la coordenada Y del mouse.
                                                        \fn			inline  int Y(void) const;
                                                        \return		Devuelve la coordenada Y del mouse.
                                                */
		 inline int			                    Y(void) const {
                                                    return _Y;
                                                };

                                                //! Función que retorna la ID de la ListaEx.
                                                /*!	Esta funcion devuelve la ID de la ListaEx.
                                                        \fn			inline UINT IDListaEx(void) const;
                                                        \return		Devuelve la ID de la ListaEx.
                                                */
		 inline UINT			                IDListaEx(void) const {
                                                    return _IDListaEx;
                                                };

                                                //! Función que retorna el boton presionado / soltado.
                                                /*!	Esta funcion devuelve el boton del mouse presionado / soltado.
                                                        \fn			inline UINT Boton(void) const;
                                                        \return		Devuelve el boton del mouse pulsado.
                                                */
		 inline UINT			                Boton(void) const {
                                                    return _Boton;
                                                };
		 private : /////////////////////////////// Miembros privados

                                                //! Item presionado
		 DWLListaEx_Item	                  *_Item;

                                                //! X del mouse
		 int			                       _X;

                                                //! Y del mouse
		 int		            			   _Y;

                                                //! ID de la ListaEx
		 UINT			                       _IDListaEx;

                                                //! Boton del mouse
		 UINT	 	            	           _Boton;

                                                //! Constructor copia des-habilitado
                                                DWLListaEx_ParametrosClick(DWLListaEx_ParametrosClick &) : _Item(NULL), _X(0), _Y(0), _IDListaEx(0), _Boton(0) { };

                                                //! Operador = des-habilitado
		 inline DWLListaEx_ParametrosClick     &operator=(DWLListaEx_ParametrosClick &) { return *this; };
		};							//
		////////////////////////////// Fin DWLListaEx_ParametrosClick

    };
};

#endif
