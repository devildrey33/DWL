#include "DWLArbolEx_Nodo.h"
#include "DWLArbolEx_Nucleo.h"
 
//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

		//! Constructor por defecto
		/*! Este constructor inicializa los datos internos del nodo por defecto.
				\fn			DWLArbolEx_Nodo(void);
				\return		No devuelve nada.
		*/
        DWLArbolEx_Nodo::DWLArbolEx_Nodo(void) :
            _Expandido(false), _Arbol(NULL), _ArbolEx_SubSeleccion(false), _Seleccionado(false), _Colores(NULL), _Fuentes(NULL),
            _Padre(NULL), _Anterior(NULL), _Siguiente(NULL), _AnchoTexto(0), _NumNodosSuperiores(0), _Hijos(), _Texto(), _Icono(0) {
        };

		//! Constructor asignador de valores
		/*! Este constructor inicializa los datos internos del nodo segun los valores especificados.
				\fn			DWLArbolEx_Nodo(DWLArbolEx_Nucleo *nArbol, DWLArbolEx_Nodo *nPadre, DWLArbolEx_Nodo *nAnteior);
				\param[in]	nArbol		: Puntero a la clase DWLArbolEx que va a contener este nodo.
				\param[in]	nPadre		: Puntero al padre de este nodo (Puede ser NULL si este nodo es el padre).
				\param[in]	nAnterior	: Puntero al nodo inmediatamente anterior a este.
				\return		No devuelve nada.
		*/
		DWLArbolEx_Nodo::DWLArbolEx_Nodo(DWLArbolEx_Nucleo *nArbol, DWLArbolEx_Nodo *nPadre, DWLArbolEx_Nodo *nAnterior) :
		    _Expandido(false), _Arbol(nArbol), _ArbolEx_SubSeleccion(false), _Seleccionado(false), _Colores(NULL), _Fuentes(NULL),
            _Padre(nPadre), _Anterior(nAnterior), _Siguiente(NULL), _AnchoTexto(0), _NumNodosSuperiores(0), _Hijos(), _Texto(), _Icono(0) {
		};

		//! Destructor
		/*! Destructor que borra la memoria relacionada con el nodo.
				\fn			~DWLArbolEx_Nodo(void);
				\return		No devuelve nada.
		*/
        DWLArbolEx_Nodo::~DWLArbolEx_Nodo(void) {
		   for (unsigned int i = 0; i < _Hijos.size(); i++) delete _Hijos[i];
		   if (_Colores != NULL) delete _Colores;
		   if (_Fuentes != NULL) delete _Fuentes;
		};

		//! Función que retorna el texto de este nodo
		/*! Esta función retorna el texto del nodo.
				\fn			inline const TCHAR *Texto(void);
				\return		Devuelve el texto del nodo.
		*/
        const TCHAR *DWLArbolEx_Nodo::Texto(void) {
			return _Texto();
		};

		//! Función para asignar el texto de este nodo
		/*! Esta función asigna el texto del nodo.
				\fn			void Texto(const TCHAR *nTxt, const bool nRepintar = true);
				\param[in]	nTxt		: Puntero a la cadena de texto que queremos asignar.
				\param[in]	nRepintar	: Valor que decide si se repintara el nodo.
				\return		No devuelve nada.
				\remarks	Si vas a cambiar el texto a 20 nodos por poner un ejemplo, solo deberias repintar cuando cambies el texto del ultimo nodo, de esta forma ahorraras 19 repintados inutiles al ordenador.
		*/
		void DWLArbolEx_Nodo::Texto(const TCHAR *nTxt, const bool nRepintar) {
			_Texto = nTxt;
			SIZE Tam;
			GetTextExtentPoint(_Arbol->_ArbolEx_Buffer, _Texto(), static_cast<int>(_Texto.Tam()), &Tam);
			_AnchoTexto = Tam.cx;
			if (nRepintar == true) _Arbol->Repintar(true);
		}


		//! Función para asignar el icono de este nodo.
		/*! Esta función asigna el icono del nodo.
				\fn			void Icono(const int nIcono, const bool nRepintar = true);
				\param[in]	nIcono		: ID del nuevo icono.
				\param[in]	nRepintar	: Valor que decide si se repintara el nodo.
				\return		No devuelve nada.
				\remarks	Si vas a cambiar el icono a 20 nodos por poner un ejemplo, solo deberias repintar cuando cambies el icono del ultimo nodo, de esta forma ahorraras 19 repintados inutiles al ordenador.
		*/
		void DWLArbolEx_Nodo::Icono(const int nIcono, const bool nRepintar) {
			_Icono = nIcono;
			if (nRepintar == true) _Arbol->Repintar(true);
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx_Nodo::Icono(Icono = %d, Repintar = %d)\n"), _Icono, nRepintar);
			#endif

		}

		//! Función quwe retorna si este nodo esta expandido
		/*! Esta función retorna si el nodo esta expandido.
				\fn			bool Expandido(void);
				\return		Devuelve true si esta expandido, false en caso contrario.
				\sa			Seleccionado(), SubSeleccionado()
		*/
		bool DWLArbolEx_Nodo::Expandido(void) {
			DWLArbolEx_Nodo *Tmp = this;
			while (Tmp->_Padre != NULL) {
				Tmp = Tmp->_Padre;
				if (Tmp->_Expandido == false) return false;
			}
			return _Expandido;
		}

		//! Función que seleciona este nodo y hace la subselecion a todos sus hijos
		/*! Esta función asigna el estado seleccionado para este nodo, y ademas aplica la sub-seleccion a todos sus nodos hijos.
				\fn			void Seleccionado(const bool Sel, const bool Repintar = false);
				\param[in]	nSel		: true para seleccionar el nodo, false para des-seleccionar.
				\param[in]	nRepintar	: true para repintar el nodo, false para no hacer nada.
				\sa			Expandido(), SubSeleccionado()
		*/
		void DWLArbolEx_Nodo::Seleccionado(const bool Sel, const bool Repintar) {
			_Seleccionado = Sel;
			if (_Padre != NULL) {
				if (_Padre->_Seleccionado == false) _ArbolEx_SubSeleccion = false;
			}
			else {
				_ArbolEx_SubSeleccion = false;
			}
            if (_Arbol->ArbolEx_Estilos.SubSeleccion == true) {
				for (unsigned int i = 0; i < _Hijos.size(); i++) {
					_Hijos[i]->Seleccionado(Sel, false);
					_Hijos[i]->_ArbolEx_SubSeleccion = Sel;
				}
			}
			if (Repintar == true) {
				_Arbol->Repintar(true);
			}
		}

		//! Función que retorna si este nodo esta SubSeleccionado (Los nodos subselecionados tambien estan selecionados)
		/*! Esta función retorna si el nodo esta sub-seleccionado.
				\fn			bool SubSeleccionado(void);
				\return		Devuelve true si esta sub-seleccionado, false en caso contrario.
				\remarks	Los nodos sub-seleccionados son aquellos que tienen un nodo padre seleccionado. Puedes deshabilitar la sub seleccion con la funcion ArbolEx_SubSeleccion().
				\sa			Expandido(), SubSeleccionado()
		*/
		bool DWLArbolEx_Nodo::SubSeleccionado(void) {
			if (_Arbol->ArbolEx_Estilos.SubSeleccion == true)   return _ArbolEx_SubSeleccion;
			else										        return false;
		};

		//! Función que crea un espacio en memoria para almacenar internamente los colores especificos para este nodo
		/*! Esta función retorna el puntero _Colores de esta clase si no es NULL, en caso contrario retorna los colores del ArbolEx.
				\fn			DWLArbolEx_ColoresNodo *Colores(void);
				\return		Devuelve la clase DWLArbolEx_ColoresNodo asociada a este nodo.
				\remarks	Por defecto todos los nodos enlazan a los colores del ArbolEx, pero si queremos modificar un color de un nodo en concreto podemos utilizar esta funcion. Esta funcion crea internamente una clase DWLArbolEx_ColoresNodo que solo usara este nodo, y que puedes modificar a tu gusto sin interferir en los demas colores del ArbolEx.
				\sa			Fuentes()
		*/
        DWLArbolEx_ColoresNodo *DWLArbolEx_Nodo::Colores(void) {
			if (_Colores == NULL) _Colores = new DWLArbolEx_ColoresNodo(_Arbol->ArbolEx_Estilos.Colores.ColoresNodo);
			return _Colores;
		};

		//! Función que crea un espacio en memoria para almacenar internamente las fuentes especificas para este nodo
		/*! Esta función retorna el puntero _Fuentes de esta clase si no es NULL, en caso contrario retorna las fuentes del ArbolEx.
				\fn			DWLArbolEx_Fuentes *Fuentes(void);
				\return		Devuelve la clase DWL::SO::DWLEstilos_Fuente asociada a este nodo.
				\remarks	Por defecto todos los nodos enlazan a las fuentes del ArbolEx, pero si queremos modificar una fuente de un nodo en concreto podemos utilizar esta funcion. Esta funcion crea internamente una clase DWL::SO::DWLEstilos_Fuente que solo usara este nodo, y que puedes modificar a tu gusto sin interferir en las demas fuentes del ArbolEx.
				\sa			Colores()
		*/
        DWLArbolEx_Fuentes *DWLArbolEx_Nodo::Fuentes(void) {
			if (_Fuentes == NULL) _Fuentes = new DWLArbolEx_Fuentes(_Arbol->ArbolEx_Estilos.Fuentes);
			return _Fuentes;
		};


		//! Función que borra este nodo y reasigna a sus hermanos y padre los nuevos nodos
		/*! Esta función elimina el nodo de memoria, y recalcula los nodos anteriores, siguientes y padre de los nodos cercanos
				\fn			void _BorrarNodo(void);
				\return		No devuelve nada
		*/
        void DWLArbolEx_Nodo::_BorrarNodo(void) {
			if (_Anterior == NULL) {	// Estamos borrando el primero
				if (_Siguiente != NULL) _Siguiente->_Anterior = NULL;
			}
			else {						// No es el primero
				if (_Anterior != NULL)  _Anterior->_Siguiente = _Siguiente;
				if (_Siguiente != NULL) _Siguiente->_Anterior = _Anterior;
			}
		};


   };
};
