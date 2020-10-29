#ifndef DWL_LISTAEX_COLUMNA_H
#define DWL_LISTAEX_COLUMNA_H
 
//#include "DWLListaEx_Colores.h"
#include "DWLListaEx_Estilos.h"
#include "..\DWLString.h"

//! Para que se asigne el ancho de la columna automaticamente mirando el tamaño del texto.
#define DWL_LISTAEX_ANCHO_AUTOMATICO				-1

//! Estado indefinido
#define DWL_LISTAEX_ESTADO_INDEFINIDO				0
//! Estado normal
#define DWL_LISTAEX_ESTADO_NORMAL					4
//! Estado resaltado
#define DWL_LISTAEX_ESTADO_RESALTADO				2
//! Estado seleccionado
#define DWL_LISTAEX_ESTADO_SELECCIONADO				5
//! Estado seleccionado resaltado
#define DWL_LISTAEX_ESTADO_SELECCIONADO_RESALTADO	3
//! Estado presionado
#define DWL_LISTAEX_ESTADO_PRESIONADO				1



namespace DWL {
	namespace ControlesEx {
		//! Clase nucleo para la ListaEx
		class DWLListaEx_Nucleo;
		//! Clase que une DWLBaseControlEx con DWLListaEx_Nucleo, para formar un control ListaEx
		class DWLListaEx;

		//! Clase que contiene los datos de una columna de la ListaEx
		class DWLListaEx_Columna {
		public : ///////////////////////////////////// Miembros publicos

													//! Constructor por defecto.
													/*! Constructor por defecto.
															\fn			DWLListaEx_Columna(void);
															\return		No devuelve nada.
													*/
													DWLListaEx_Columna(void);

													//! Constructor asignador.
													/*! Constructor asignador.
															\fn			DWLListaEx_Columna(DWLListaEx_Nucleo *LE);
															\param[in]	LE : Puntero a la ListaEx que contiene esta columna.
															\return		No devuelve nada.
													*/
													DWLListaEx_Columna(DWLListaEx_Nucleo *LE);

													//! Destructor.
													/*! Destructor.
															\fn			~DWLListaEx_Columna(void);
															\return		No devuelve nada.
													*/
												   ~DWLListaEx_Columna(void);

													//! Función que retorna la alineación del texto.
													/*! Esta función devuelve la alineación del texto.
															\fn			int Alineacion(void) const;
															\return		Devuelve la alineación para esta columna.
															\remarks	Las alineaciones posibles son : DWL_LISTAEX_TEXTO_IZQUIERDA, DWL_LISTAEX_TEXTO_CENTRADO y DWL_LISTAEX_TEXTO_DERECHA.
													*/
		 int									    Alineacion(void) const {
														return _Alineacion;
												    };

													//! Función que asigna la alineación del texto.
													/*! Esta función asigna la alineación del texto.
															\fn			void Alineacion(const int nAlineacion);
															\param[in]	nAlineacion : Parametro en el que especificamos la nueva alineacion, que puede ser : DWL_LISTAEX_TEXTO_IZQUIERDA, DWL_LISTAEX_TEXTO_CENTRADO y DWL_LISTAEX_TEXTO_DERECHA.
															\return		No devuelve nada.
													*/
		 void										Alineacion(const int nAlineacion);

													//! Función que retorna el ancho de esta columna.
													/*! Esta función devuelve el ancho de esta columna en pixeles.
															\fn			inline int Ancho(void) const;
															\return		Devuelve el ancho en pixeles de esta columna.
													*/
		 inline int		        					Ancho(void) const {
														return _Ancho;
													};

													//! Función que asigna el ancho de esta columna.
													/*! Esta función asigna el ancho de esta columna.
															\fn			void Ancho(const int nAncho, const bool nRepintar = true);
															\param[in]	nAncho		: Nuevo ancho en pixeles para esta columna.
															\param[in]	nRepintar	: Valor que especifica si la ListaEx debe repintarse.
															\return		No devuelve nada.
													*/
		 void										Ancho(const int nAncho, const bool nRepintar = true);

													//! Función que retorna los colores de esta columna.
													/*! Esta función retorna los colores de esta columna.
															\fn			DWLListaEx_ColoresColumna *Colores(void);
															\return		Devuelve un puntero a la clase DWLListaEx_ColoresColumna que contiene los colores para esta columna.
															\remarks	Por defecto todos las columnas se enlazan a los colores de la ListaEx padre, si usamos esta clase,
																		estamos creando una nueva definicion de colores para esta columna, que por defecto tendra los mismos colores que su clase padre.
													*/
		 DWLListaEx_ColoresColumna				   *Colores(void) {
														if (_Colores == NULL) _Colores = new DWLListaEx_ColoresColumna;
														return _Colores;
													};

													//! Función que retorna las fuentes de esta columna.
													/*! Esta función retorna las fuentes de esta columna.
															\fn			DWLListaEx_Fuentes *Fuentes(void);
															\return		Devuelve un puntero a la clase DWLListaEx_Fuentes que contiene las fuentes para esta columna.
															\remarks	Por defecto todos las columnas se enlazan a las fuentes de la ListaEx padre, si usamos esta clase,
																		estamos creando una nueva definicion de fuentes para esta columna, que por defecto tendra las mismas fuentes que su clase padre.
													*/
		 DWLListaEx_Fuentes						   *Fuentes(void) {
														if (_Fuentes == NULL) _Fuentes = new DWLListaEx_Fuentes;
														return _Fuentes;
													};
		private : //////////////////////////////////// Miembros privados

													//! Clase que contiene los colores para la columna
		 DWLListaEx_ColoresColumna				  *_Colores;

													//! Clase que contiene las fuentes para la columna
		 DWLListaEx_Fuentes						  *_Fuentes;

													//! Alineacion del texto
		 int									   _Alineacion;

													//! Ancho de la columna
		 int							           _Ancho;

													//! Nombre de la columna
		 DWL::DWLString						       _Nombre;

													//! Estado de la columna
		 int									   _Estado;

													//! Puntero a la DWLListaEx padre
		 DWLListaEx_Nucleo				          *_ListaEx;


                                                    //! Constructor copia des-habilitado
                                                    DWLListaEx_Columna(DWLListaEx_Columna &) : _Colores(NULL), _Alineacion(0), _Ancho(DWL_LISTAEX_ANCHO_AUTOMATICO), _Nombre(), _Estado(DWL_LISTAEX_ESTADO_NORMAL), _ListaEx(NULL), _Fuentes(NULL) { };

                                                    //! Operador = des-habilitado
		 inline DWLListaEx_Columna                 &operator=(DWLListaEx_Columna &) { return *this; };


		 friend class								DWLListaEx;
													//
		 friend class								DWLListaEx_Nucleo;
		};											//
		////////////////////////////////////////////// Final DWLListaEx_Columna

    };
};

#endif

