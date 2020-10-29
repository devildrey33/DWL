#ifndef DWL_ARBOLEX_TERMINARLABELEDIT_H
#define DWL_ARBOLEX_TERMINARLABELEDIT_H
 
#include "DWLArbolEx_Nodo.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

        //! Clase que contiene los datos que se necesitan al terminar la edicion de un nodo.
		class DWLArbolEx_TerminarLabelEdit {
		public : ///////////////////////////////// Miembros publicos

                                                //! Constructor por defecto.
                                                /*!	Constructor por defecto.
                                                        \fn			DWLArbolEx_TerminarLabelEdit(void);
                                                        \return		No devuelve nada.
                                                */
                                                DWLArbolEx_TerminarLabelEdit(void) : Cancelar(false), NuevoTexto(), _Nodo(NULL) {
                                                };

                                                //! Constructor asignador de datos.
                                                /*!	Constructor asignador de datos.
                                                        \fn			DWLArbolEx_TerminarLabelEdit(DWLArbolEx_Nodo *nNodo, const TCHAR *nNuevoTexto);
                                                        \param[in]	nNodo		: Nodo que se esta editando.
                                                        \param[in]	nNuevoTexto : Nuevo texto para el nodo.
                                                        \return		No devuelve nada.
                                                */
                                                DWLArbolEx_TerminarLabelEdit(DWLArbolEx_Nodo *nNodo, const TCHAR *nNuevoTexto) : Cancelar(false), _Nodo(nNodo) {
													NuevoTexto = nNuevoTexto;
												};

                                                //! Destructor.
                                                /*!	Destructor.
                                                        \fn			~DWLArbolEx_TerminarLabelEdit(void);
                                                        \return		No devuelve nada.
                                                */
                                               ~DWLArbolEx_TerminarLabelEdit(void) {
                                                };

                                                //! Función que retorna un puntero al DWLArbolEx_Nodo correspondiente a este nodo en edición.
                                                /*!	Esta función retorna un puntero al DWLArbolEx_Nodo correspondiente a este nodo en edición.
                                                        \fn			inline DWLArbolEx_Nodo *Nodo(void);
                                                        \return		Devuelve el nodo que se esta editando.
                                                */
         inline DWLArbolEx_Nodo                *Nodo(void) {
                                                    return _Nodo;
                                                };

                                                //! Estado de cancelacion para esta edicion
		 bool		                            Cancelar;

                                                //! Nuevo texto que se va a aplicar
		 DWL::DWLString		                    NuevoTexto;
		private : ///////////////////////////////// Miembros privados

                                                //! Clase DNodo que contiene el nodo que se esta editando
		 DWLArbolEx_Nodo                      *_Nodo;
                                                // Constructor copia des-habilitado
                                                DWLArbolEx_TerminarLabelEdit(const DWLArbolEx_TerminarLabelEdit &) : Cancelar(false), NuevoTexto(), _Nodo(NULL) { };
                                                // Operador = des-habilitado
		 inline DWLArbolEx_TerminarLabelEdit   &operator=(const DWLArbolEx_TerminarLabelEdit &) { return *this; };
		};						                //
		//////////////////////////////////////////
    };
};

#endif
