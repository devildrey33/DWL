#ifndef DWL_LISTAEX_DATOSSUBITEM_H
#define DWL_LISTAEX_DATOSSUBITEM_H

#include "DWLListaEx_Estilos.h"
#include "DWLListaEx_Colores.h"
#include "..\DWLString.h"
 
namespace DWL {
	namespace ControlesEx {
		//! Clase nucleo para la ListaEx
		class DWLListaEx_Nucleo;
		//! Clase que une DWLBaseControlEx con DWLListaEx_Nucleo, para formar un control ListaEx
		class DWLListaEx;

		//! Clase que contiene los datos para un SubItem
		class DWLListaEx_DatosSubItem {
		public : ///////////////////////////// Metodos publicos

                                            //! Constructor por defecto.
                                            /*! Constructor por defecto.
                                                    \fn			DWLListaEx_DatosSubItem(void);
                                                    \return		No devuelve nada.
                                            */
                                            DWLListaEx_DatosSubItem(void) : Texto(), _Fuentes(NULL), _Colores(NULL) {
                                                _Fuentes = NULL;
                                                _Colores = NULL;
                                            };

                                            //! Constructor asignador.
                                            /*! Constructor asignador.
                                                    \fn			DWLListaEx_DatosSubItem(const TCHAR *nTexto);
                                                    \param[in]	nTexto : Nuevo texto del subitem.
                                                    \return		No devuelve nada.
                                            */
                                            DWLListaEx_DatosSubItem(const TCHAR *nTexto) : _Fuentes(NULL), _Colores(NULL) {
                                                Texto = nTexto;
                                                _Colores = NULL;
                                                _Fuentes = NULL;
                                            };

                                            //! Destructor.
                                            /*! Destructor.
                                                    \fn			~DWLListaEx_DatosSubItem(void);
                                                    \return		No devuelve nada.
                                            */
                                           ~DWLListaEx_DatosSubItem(void) {
                                               if (_Colores != NULL) delete _Colores;
                                               if (_Fuentes != NULL) delete _Fuentes;
                                            };

                                            //! Clase que contiene el texto del subitem
         DWLString						    Texto;

                                            //! Función que retorna los colores de este subitem.
                                            /*! Esta función retorna los colores de este subitem.
                                                    \fn			DWLListaEx_ColoresItem *Colores(void);
                                                    \return		Devuelve un puntero a la clase DWLListaEx_ColoresItem que contiene los colores para este subitem.
                                                    \remarks	Por defecto todos los subitems se enlazan a los colores de la ListaEx padre, si usamos esta clase,
                                                                estamos creando una nueva definicion de colores para este subitem, que por defecto tendra los mismos colores que su clase padre.
                                            */
		 DWLListaEx_ColoresItem		       *Colores(void) {
                                                if (_Colores == NULL) _Colores = new DWLListaEx_ColoresItem;
                                                return _Colores;
                                            };

                                            //! Función que retorna las fuentes de este subitem.
                                            /*! Esta función retorna las fuentes de este subitem.
                                                    \fn			DWLListaEx_Fuentes *Fuentes(void);
                                                    \return		Devuelve un puntero a la clase DWLListaEx_Fuentes que contiene las fuentes para este subitem.
                                                    \remarks	Por defecto todos los subitems se enlazan a las fuentes de la ListaEx padre, si usamos esta clase,
                                                                estamos creando una nueva definicion de fuentes para este subitem, que por defecto tendra las mismas fuentes que su clase padre.
                                            */
		 DWLListaEx_Fuentes				   *Fuentes(void) {
                                                if (_Fuentes == NULL) _Fuentes = new DWLListaEx_Fuentes;
                                                return _Fuentes;
                                            };
		protected : ////////////////////////// Miembros protegidos

                                            //! Fuentes del subitem
		 DWLListaEx_Fuentes               *_Fuentes;

                                            //! Colores del subitem
		 DWLListaEx_ColoresItem	    	  *_Colores;
        private : //////////////////////////// Miembros privados

                                            //! Constructor copia des-habilitado
                                            DWLListaEx_DatosSubItem(const DWLListaEx_DatosSubItem &) : Texto(), _Fuentes(NULL), _Colores(NULL) { };
                                            //! Operador = des-habilitado
		 inline DWLListaEx_DatosSubItem    &operator=(const DWLListaEx_DatosSubItem &) { return *this; };

		 friend class					    DWLListaEx;
		 friend class					    DWLListaEx_Nucleo;
		};								    //
		////////////////////////////////////// Final DWLListaEx_DatosSubItem

    };
};

#endif
