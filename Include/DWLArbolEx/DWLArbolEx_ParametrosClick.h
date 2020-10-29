#ifndef DWL_ARBOLEX_PARAMETROSCLICK_H
#define DWL_ARBOLEX_PARAMETROSCLICK_H

#include "DWLArbolEx_Nodo.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

		//! Clase que contiene los parametros de un click para pasarlos a la función de su ventana padre.
		class DWLArbolEx_ParametrosClick {
		 public : //////////////////////////// Miembros publicos

                                            //! Constructor.
                                            /*!	Constructor por defecto.
                                                    \fn			DWLArbolEx_ParametrosClick(void);
                                                    \return		No devuelve nada.
                                            */
                                            DWLArbolEx_ParametrosClick(void) : _Nodo(NULL), _X(0), _Y(0), _IDArbolEx(0), _Boton(0) {
                                            };

                                            //! Constructor que define todos los valores
                                            /*!	Constructor asignador de datos.
                                                    \fn			DWLArbolEx_ParametrosClick(DWLArbolEx_Nodo *nNodo, const int cX, const int cY, const UINT cID, const UINT nBoton);
                                                    \param[in]	nNodo	: Nodo que se ha presionado / soltado.
                                                    \param[in]	cX		: Coordenada X del mouse.
                                                    \param[in]	cY		: Coordenada Y del mouse.
                                                    \param[in]	cID		: ID del ArbolEx.
                                                    \param[in]	cBoton	: Boton del mouse presionado / soltado.
                                                    \return		No devuelve nada.
                                            */
                                            DWLArbolEx_ParametrosClick(DWLArbolEx_Nodo *nNodo, const int cX, const int cY, const UINT cID, const UINT nBoton) :
                                                _Nodo(nNodo), _X(cX), _Y(cY), _IDArbolEx(cID), _Boton(nBoton) {
                                            };

                                            //! Destructor.
                                            /*!	Destructor.
                                                    \fn			~DWLArbolEx_ParametrosClick(void);
                                                    \return		No devuelve nada.
                                            */
                                           ~DWLArbolEx_ParametrosClick(void) {
                                            };

                                            //! Función que retorna el nodo.
                                            /*!	Esta funcion devuelve el nodo presionado / soltado.
                                                    \fn			inline DWLArbolEx_Nodo *Nodo(void);
                                                    \return		Devuelve el nodo presionado / soltado.
                                            */
		 inline DWLArbolEx_Nodo            *Nodo(void) {
                                                return _Nodo;
                                            };

                                            //! Función que retorna la coordenada X del mouse.
                                            /*!	Esta funcion devuelve la coordenada X del mouse.
                                                    \fn			inline int X(void);
                                                    \return		Devuelve la coordenada X del mouse.
                                            */
		 inline int			                X(void) {
                                                return _X;
                                            };

                                            //! Función que retorna la coordenada Y del mouse.
                                            /*!	Esta funcion devuelve la coordenada Y del mouse.
                                                    \fn			inline int Y(void);
                                                    \return		Devuelve la coordenada Y del mouse.
                                            */
		 inline int			                Y(void) {
                                                return _Y;
                                            };

                                            //! Función que retorna la ID del ArbolEx.
                                            /*!	Esta funcion devuelve la ID del ArbolEx.
                                                    \fn			inline UINT IDArbolEx(void);
                                                    \return		Devuelve la ID del ArbolEx.
                                            */
		 inline UINT			            IDArbolEx(void) {
                                                return _IDArbolEx;
                                            };

                                            //! Función que retorna el boton presionado / soltado.
                                            /*!	Esta funcion devuelve el boton del mouse presionado / soltado.
                                                    \fn			inline const UINT Boton(void);
                                                    \return		Devuelve el boton del mouse pulsado.
                                            */
		 inline UINT			            Boton(void) {
                                                return _Boton;
                                            };
		 private : /////////////////////////// Miembros privados
                                            //! Nodo seleccionado / clickeado
		  DWLArbolEx_Nodo                 *_Nodo;

                                            //! Posicion X del mouse
		  int			                   _X;

                                            //! Posicion Y del mouse
		  int					           _Y;

                                            //! ID del arbol
		  UINT		                       _IDArbolEx;

                                            //! Boton del mouse presionado
		  UINT		                       _Boton;

                                            //! Constructor copia des-habilitado
                                            DWLArbolEx_ParametrosClick(const DWLArbolEx_ParametrosClick &) : _Nodo(NULL), _X(0), _Y(0), _IDArbolEx(0), _Boton(0) { };
                                            //! Operador = des-habilitado
		 inline DWLArbolEx_ParametrosClick &operator=(const DWLArbolEx_ParametrosClick &) { return *this; };

		};							//
		////////////////////////////// DWLArbolEx_ParametrosClick
    };
};

#endif
