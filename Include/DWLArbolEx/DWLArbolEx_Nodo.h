/*! \file DWLArbolEx_Nodo.h
	\brief		 Archivo que contiene la clase que hace de nodo dentro del ArbolEx.
    */ 
#ifndef DWL_ARBOLEX_NODO_H
#define DWL_ARBOLEX_NODO_H

#include <vector>
#include "..\DWLString.h"
#include "DWLArbolEx_Estilos.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {
   		//! Clase Nucleo del ArbolEx
		/*! Esta clase contiene las funciones de pintado, funciones de control para el teclado y el raton, y algunos eventos que podemos sobre-escribir.		*/
		class DWLArbolEx_Nucleo;
		class DWLExplorarDirectorios;

//! Clase que contiene un nodo del ArbolEx
/*! Esta clase puede ser heredada de forma que podamos almacenar mas datos dentro de un nodo. \n
	De esta forma podemos almacenar datos en memoria del mismo nodo para asi tenerlos ordenados y perfectamente accesibles cuando sea necesario. \n
	A continuación podemos ver un ejemplo de como deberiamos crear una clase que herede de DWLArbolEx_Nodo :
	\code // Clase que hereda de DWLArbolEx_Nodo con un valor extra.
class NodoHeredado : public DWL::ControlesEx::DWLArbolEx_Nodo {
 public:
			NodoHeredado(void) { ValorExtra = 0; };
		   ~NodoHeredado(void) { };
	int		ValorExtra;
};
	\endcode
	Una vez ya se disponga de una clase nodo heredada con todos los valores extras necesarios, nos faltara hacer una función para agregar nodos del tipo NodoHeredado utilizando DWLArbolEx_Nucleo::ArbolEx_AgregarNodo() :

	\code // Nuestra nueva función para agregar nodos del tipo NodoHeredado al arbol
void AgregarNodo(NodoHeredado *NodoPadre, const int IDIcono, const TCHAR *TextoNodo, const int NuevoValor) {
	NodoHeredado *NuevoNodo = new NodoHeredado;
	NuevoNodo->ValorExtra = NuevoValor;
	ArbolEx_AgregarNodo(NuevoNodo, NodoPadre, IDIcono, TextoNodo, DWL_ARBOLEX_ORDENADO);
};
	\endcode
	\remarks	Como puedes ver en el ejemplo de arriba, cuando quieras agregar un nodo heredado con la función DWLArbolEx_Nucleo::ArbolEx_AgregarNodo(), deberas pasarle como primer parametro un puntero a un nuevo nodo heredado que tienes que haber creado antes.
	\sa			DWLArbolEx_Nucleo::ArbolEx_AgregarNodo()

*/
		class DWLArbolEx_Nodo {
		public : ///////////////////////////// Miembros publicos

											//! Constructor por defecto
											/*! Este constructor inicializa los datos internos del nodo por defecto.
													\fn			DWLArbolEx_Nodo(void);
													\return		No devuelve nada.
											*/
											DWLArbolEx_Nodo(void);

											//! Constructor asignador de valores
											/*! Este constructor inicializa los datos internos del nodo segun los valores especificados.
													\fn			DWLArbolEx_Nodo(DWLArbolEx_Nucleo *nArbol, DWLArbolEx_Nodo *nPadre, DWLArbolEx_Nodo *nAnteior);
													\param[in]	nArbol		: Puntero a la clase DWLArbolEx que va a contener este nodo.
													\param[in]	nPadre		: Puntero al padre de este nodo (Puede ser NULL si este nodo es el padre).
													\param[in]	nAnterior	: Puntero al nodo inmediatamente anterior a este.
													\return		No devuelve nada.
											*/
											DWLArbolEx_Nodo(DWLArbolEx_Nucleo *nArbol, DWLArbolEx_Nodo *nPadre, DWLArbolEx_Nodo *nAnteior);

											//! Destructor
											/*! Destructor que borra la memoria relacionada con el nodo.
													\fn			~DWLArbolEx_Nodo(void);
													\return		No devuelve nada.
											*/
										   ~DWLArbolEx_Nodo(void);

											//! Función que retorna el texto de este nodo
											/*! Esta función retorna el texto del nodo.
													\fn			const TCHAR *Texto(void);
													\return		Devuelve el texto del nodo.
											*/
		 const TCHAR                       *Texto(void);

											//! Función para asignar el texto de este nodo
											/*! Esta función asigna el texto del nodo.
													\fn			void Texto(const TCHAR *nTxt, const bool nRepintar = true);
													\param[in]	nTxt		: Puntero a la cadena de texto que queremos asignar.
													\param[in]	nRepintar	: Valor que decide si se repintara el nodo.
													\return		No devuelve nada.
													\remarks	Si vas a cambiar el texto a 20 nodos por poner un ejemplo, solo deberias repintar cuando cambies el texto del ultimo nodo, de esta forma ahorraras 19 repintados inutiles al ordenador.
											*/
		 void                               Texto(const TCHAR *nTxt, const bool nRepintar = true);

											//! Función que retorna el icono de este nodo
											/*! Esta función retorna el icono del nodo.
													\fn			inline int Icono(void);
													\return		Devuelve el icono del nodo.
											*/
         inline int                         Icono(void) {
                                                return _Icono;
                                            };

											//! Función para asignar el icono de este nodo.
											/*! Esta función asigna el icono del nodo.
													\fn			void Icono(const int nIcono, const bool nRepintar = true);
													\param[in]	nIcono		: ID del nuevo icono.
													\param[in]	nRepintar	: Valor que decide si se repintara el nodo.
													\return		No devuelve nada.
													\remarks	Si vas a cambiar el icono a 20 nodos por poner un ejemplo, solo deberias repintar cuando cambies el icono del ultimo nodo, de esta forma ahorraras 19 repintados inutiles al ordenador.
											*/
		 void						        Icono(const int nIcono, const bool nRepintar = true);

											//! Función que retorna el tamaño en caracteres del texto.
											/*! Esta función retorna la longitud en caracteres del texto del nodo.
													\fn			inline UINT LongitudTexto(void);
													\return		Devuelve la longitud en caracteres del nodo.
											*/
         inline UINT			            LongitudTexto(void) {
                                                return _Texto.Tam();
                                            };

											//! Función que retorna el nodo siguiente.
											/*! Esta función retorna el nodo siguiente a este.
													\fn			inline DWLArbolEx_Nodo *Siguiente(void);
													\return		Devuelve el nodo siguiente a este.
													\remarks	Solo los nodos que esten inmediatamente al lado y tengan el mismo padre pueden ser el nodo siguiente.
													\sa			Anterior(),	Padre(), Hijo(), TotalHijos()
											*/
		 inline DWLArbolEx_Nodo            *Siguiente(void) {
		                                    	return _Siguiente;
		                                    };

											//! Función que retorna el nodo anterior.
											/*! Esta función retorna el nodo anterior a este.
													\fn			inline DWLArbolEx_Nodo *Anterior(void);
													\return		Devuelve el nodo anterior a este.
													\remarks	Solo los nodos que esten inmediatamente al lado y tengan el mismo padre pueden ser el nodo anterior.
													\sa			Siguiente(), Padre(), Hijo(), TotalHijos()
											*/
         inline DWLArbolEx_Nodo		       *Anterior(void) {
                                                return _Anterior;
                                            };

											//! Función que retorna el nodo padre.
											/*! Esta función retorna el nodo padre.
													\fn			inline DWLArbolEx_Nodo *Padre(void);
													\return		Devuelve el nodo padre.
													\remarks	Si la funcion retorna NULL es que este nodo es el primer nodo padre.
													\sa			Siguiente(), Anterior(), Hijo(), TotalHijos()
											*/
         inline DWLArbolEx_Nodo		       *Padre(void) {
                                                return _Padre;
                                            };

											//! Función que retorna el hijo especificado
											/*! Esta función retorna el nodo hijo especificado.
													\fn			inline DWLArbolEx_Nodo *Hijo(const int Pos);
													\param[in]	Pos : Posicion del nodo hijo que queremos obtener.
													\return		Devuelve el nodo hijo especificado.
													\remarks	Si la funcion retorna NULL es que o no tiene hijos, o que la posicion del hijo no es valida.
													\sa			Siguiente(), Anterior(), Padre(), TotalHijos()
											*/
		 inline DWLArbolEx_Nodo            *Hijo(const int Pos) {
			                                    return (_Hijos.size() == 0) ? NULL : _Hijos[Pos];
		                                    };

											//! Función que retorna el total de hijos de este nodo.
											/*! Esta función retorna el total de hijos para este nodo.
													\fn			inline UINT TotalHijos(void);
													\return		Devuelve el total del hijos de este nodo.
													\sa			Siguiente(), Anterior(), Padre(), Hijo()
											*/
		 inline UINT                        TotalHijos(void) {
			                                    return static_cast<UINT>(_Hijos.size());
		                                    };

											//! Función quwe retorna si este nodo esta expandido
											/*! Esta función retorna si el nodo esta expandido.
													\fn			bool Expandido(void);
													\return		Devuelve true si esta expandido, false en caso contrario.
													\sa			Seleccionado(), SubSeleccionado()
											*/
		 bool                               Expandido(void);

											//! Función que expande este nodo
											// void Expandir(const bool nExpandir, const bool nRepintar = false);
//		 void                               Expandir(HWND hWndControl, const bool nExpandir, const bool nRepintar = false);

											//! Función que retorna si este nodo esta selecionado (Los nodos subselecionados tambien estan selecionados)
											/*! Esta función retorna si el nodo esta seleccionado.
													\fn			bool Seleccionado(void);
													\return		Devuelve true si esta seleccionado, false en caso contrario.
													\sa			Expandido(), SubSeleccionado()
											*/
         inline bool				        Seleccionado(void) {
                                                return _Seleccionado;
                                            };

											//! Función que seleciona este nodo y hace la subselecion a todos sus hijos
											/*! Esta función asigna el estado seleccionado para este nodo, y ademas aplica la sub-seleccion a todos sus nodos hijos.
													\fn			void Seleccionado(const bool Sel, const bool Repintar = false);
													\param[in]	nSel		: true para seleccionar el nodo, false para des-seleccionar.
													\param[in]	nRepintar	: true para repintar el nodo, false para no hacer nada.
													\sa			Expandido(), SubSeleccionado()
											*/
		 void                               Seleccionado(const bool nSel, const bool nRepintar = false);

											//! Función que retorna si este nodo esta SubSeleccionado (Los nodos subselecionados tambien estan selecionados)
											/*! Esta función retorna si el nodo esta sub-seleccionado.
													\fn			bool SubSeleccionado(void);
													\return		Devuelve true si esta sub-seleccionado, false en caso contrario.
													\remarks	Los nodos sub-seleccionados son aquellos que tienen un nodo padre seleccionado. Puedes deshabilitar la sub seleccion con la funcion ArbolEx_SubSeleccion().
													\sa			Expandido(), SubSeleccionado()
											*/
		 bool							    SubSeleccionado(void);

											//! Función que crea un espacio en memoria para almacenar internamente los colores especificos para este nodo
											/*! Esta función retorna el puntero _Colores de esta clase si no es NULL, en caso contrario retorna los colores del ArbolEx.
													\fn			DWLArbolEx_ColoresNodo *Colores(void);
													\return		Devuelve la clase DWLArbolEx_ColoresNodo asociada a este nodo.
													\remarks	Por defecto todos los nodos enlazan a los colores del ArbolEx, pero si queremos modificar un color de un nodo en concreto podemos utilizar esta funcion. Esta funcion crea internamente una clase DWLArbolEx_ColoresNodo que solo usara este nodo, y que puedes modificar a tu gusto sin interferir en los demas colores del ArbolEx.
													\sa			Fuentes()
											*/
		 DWLArbolEx_ColoresNodo			   *Colores(void);

											//! Función que crea un espacio en memoria para almacenar internamente las fuentes especificas para este nodo
											/*! Esta función retorna el puntero _Fuentes de esta clase si no es NULL, en caso contrario retorna las fuentes del ArbolEx.
													\fn			DWLArbolEx_Fuentes *Fuentes(void);
													\return		Devuelve la clase DWLArbolEx_Fuentes asociada a este nodo.
													\remarks	Por defecto todos los nodos enlazan a las fuentes del ArbolEx, pero si queremos modificar una fuente de un nodo en concreto podemos utilizar esta funcion. Esta funcion crea internamente una clase DWL::SO::DWLEstilos_Fuente que solo usara este nodo, y que puedes modificar a tu gusto sin interferir en las demas fuentes del ArbolEx.
													\sa			Colores()
											*/
		 DWLArbolEx_Fuentes			       *Fuentes(void);
		protected : ////////////////////////// Miembros protegidos

						 					//! Colores de este nodo
											/*! Este miembro puede ser NULL, en ese caso se miraran los colores del ArbolEx
											*/
		 DWLArbolEx_ColoresNodo			  *_Colores;

											//! Función que borra este nodo y reasigna a sus hermanos y padre los nuevos nodos
											/*! Esta función elimina el nodo de memoria, y recalcula los nodos anteriores, siguientes y padre de los nodos cercanos
													\fn			void _BorrarNodo(void);
													\return		No devuelve nada
											*/
		 void				               _BorrarNodo(void);

											//! Ancho del texto de este nodo
		 int                               _AnchoTexto;

											//! Numero de nodos superiores (padre, abuelo, etc..)
		 unsigned short                    _NumNodosSuperiores;

											//! Nodo siguiente
		 DWLArbolEx_Nodo                  *_Siguiente;

											//! Nodo anterior
		 DWLArbolEx_Nodo                  *_Anterior;

											//! Nodo padre
		 DWLArbolEx_Nodo			      *_Padre;

											//! Vector de nodos hijos
		 std::vector<DWLArbolEx_Nodo *>    _Hijos;

											//! Texto
		 DWL::DWLString					   _Texto;

											//! Icono
		 int                               _Icono;

											//! Estado expandido
		 bool                              _Expandido;

											//! Seleccion del nodo
		 bool							   _Seleccionado;

											//! Subselecion del nodo
		 bool                              _ArbolEx_SubSeleccion;

											//! Arbol padre de este nodo
		 DWLArbolEx_Nucleo                *_Arbol;

											//! Fuentes de este nodo
		 									/*! Este miembro puede ser NULL, en ese caso se miraran las fuentes del ArbolEx		*/
		 DWLArbolEx_Fuentes               *_Fuentes;
		private : //////////////////////////// Mimebros privados
                                            // Constructor copia des-habilitado
                                            DWLArbolEx_Nodo(const DWLArbolEx_Nodo &) : _Expandido(false), _Arbol(NULL), _ArbolEx_SubSeleccion(false), _Seleccionado(false), _Colores(NULL), _Fuentes(NULL), _Padre(NULL), _Anterior(NULL), _Siguiente(NULL), _AnchoTexto(0), _NumNodosSuperiores(0), _Hijos(), _Texto(), _Icono(0) { };
                                            // Operador = des-habilitado
		 inline DWLArbolEx_Nodo            &operator=(const DWLArbolEx_Nodo &) { return *this; };
											//
       #if (COMPILADOR != COMPILADOR_MINGW)
		 friend class DWLArbolEx_Nodo;		//
	   #endif
		 friend class DWLArbolEx_Nucleo;	//
		 friend class DWLArbolEx;			//
		 friend class DWLExplorarDirectorios;
		}; /////////////////////////////////// Fin DWLArbolEx_Nodo
    };
};

#endif
