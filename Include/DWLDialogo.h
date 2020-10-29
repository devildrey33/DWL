/*! \file DWLDialogo.h
	\brief		Archivo que contiene las definiciones para la clase DWLDialogo.
	\author		devildrey33
	\date		Creado el [15/06/2005], ultima modificación el [05/10/2010]
*/ 
#ifndef DWL_DIALOGO_H
#define DWL_DIALOGO_H

#include "DWLEventosPadre.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Ventanas
	namespace Ventanas {
		//! Clase para controlar un dialogo
        class DWLDialogo : public Base::DWLEventosPadre<BOOL> {
		  public: //////////////////// Declaraciones Publicas

									//! Constructor.
									/*!	Constructor por defecto.
											\fn		DWLDialogo(void);
											\return	No devuelve nada.
									*/
									DWLDialogo(void);

									//! Función para asignar si el dialogo se puede maximizar
									/*!	Esta función asigna si el dialogo tiene la capacidad de ser maximizado.
											\fn			virtual void Maximizable(const bool nMax);
											\param[in]	nMax	: Parametro en el que especificaremos si el dialogo puede ser maximizado.
											\return		No devuelve nada.
									*/
		 virtual void               Maximizable(const bool nMax);

									//! Función para obtener si el dialogo se puede maximizar
									/*!	Esta función se usa para obtener si el dialogo tiene la capacidad de ser maximizado.
											\fn			virtual const bool Maximizable(void); 
											\return		Devuelve true si se puede maximizar, false en caso contrario.
									*/
		 virtual const bool         Maximizable(void); 

									//! Función para asignar si el dialogo se puede minimizar
									/*!	Esta función asigna si el dialogo tiene la capacidad de ser minimizado.
											\fn			virtual void Minimizable(const bool nMin);
											\param[in]	nMin	: Parametro en el que especificaremos si el dialogo puede ser minimizado.
											\return		No devuelve nada.
									*/
		 virtual void               Minimizable(const bool nMin);

									//! Función para obtener si el dialogo se puede minimizar
									/*!	Esta funcion se usa para obtener si el dialogo tiene la capacidad de ser minimizado.
											\fn			virtual const bool Minimizable(void); 
											\return		Devuelve true si se puede minimizar, false en caso contrario.
									*/
		 virtual const bool         Minimizable(void);

									//! Función que posiciona el dialogo siempre delante de todo
									/*!	Esta función posiciona el dialogo siempre delante de todas las otras ventanas.
											\fn			virtual void SiempreDelante(const bool SD);
											\param[in]	SD	: Parametro en el que si el dialogo estara siempre delante.
											\return		No devuelve nada.
									*/
		 virtual void				SiempreDelante(const bool SD);

							        //! Función que crea el dialogo.
							        /*!	Esta función crea el dialogo.
									        \fn			HWND CrearDialogo(int ID_Dialogo, const int cX, const int cY);
									        \param[in]	ID_Dialogo	: ID del dialogo en los recursos.
									        \param[in]	cX			: Posicion X. Puedes especificar DWL_CENTRADO para que se centre.
									        \param[in]	cY			: Posicion Y. Puedes especificar DWL_CENTRADO para que se centre.
									        \return		Devuelve el HWND del dialogo. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para ver el error.
							        */
	     HWND	                    CrearDialogo(int ID_Dialogo, const int cX, const int cY);

		protected: /////////////////// Declaraciones protegidas (Solo podran usarse en la clase heredada no desde fuera)

							        //! Esqueleto inicial que enlaza esta clase con el dialogo.
							        /*! Esta función es el esqueleto inicial que enlaza esta clase con el dialogo.
									        \fn			static BOOL CALLBACK _GestorMensajes(HWND HandleDialogo, UINT uMsg, WPARAM wParam, LPARAM lParam);
									        \param[in]	HandleVentana	: Identificador de ventana.
									        \param[in]	uMsg			: Mensaje.
									        \param[in]	wParam			: Parametro1.
									        \param[in]	lParam			: Parametro2.
									        \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
							        */
	     static BOOL CALLBACK      _GestorMensajes(HWND HandleDialogo, UINT uMsg, WPARAM wParam, LPARAM lParam);
		};							//
		////////////////////////////// Fin ClaseDialogo

	}
}

#endif // DWL_DIALOGO_H

