/*! \file DWLDebug.h
	\brief		Archivo que contiene funciones utiles para la depuración.
	\author		devildrey33
	\date		Creado el [01/02/2004], ultima modificación el [05/10/2010]
*/ 

#ifndef DWL_DEBUG_H
#define DWL_DEBUG_H

#include "DWL.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Clase para mostrar información de depuración
	class DWLDebug {
	public : ///////////// Miembros publicos
		                //! Constructor
                        /*! Constructor por defecto.
		                        \fn			DWLDebug(void);
                                \return     No devuelve nada
                        */
						DWLDebug(void) { };

		                //! Función que imprime texto por la pantallita de debug
                        /*! Función que imprime texto por la pantallita de debug, al estilo del printf
		                        \fn			static void	ImprimirDebug(const TCHAR *Txt, ...);
								\param[in]	Txt		: Puntero a una cadena de texto
								\param[in]	...		: Parametros opcionales
                                \return     No devuelve nada
                        */
	 static void		ImprimirDebug(const TCHAR *Txt, ...);

		                //! Función que imprime texto por la pantallita de debug, calculando el tiempo.
                        /*! Función que imprime texto por la pantallita de debug, al estilo del printf. Ademas esta función calcula el tiempo que ha transcurrido desde la ultima vez que se llamo a esta función. 
		                        \fn			static void	ImprimirDebugMS(const TCHAR *Txt, ...);
								\param[in]	Txt		: Puntero a una cadena de texto
								\param[in]	...		: Parametros opcionales
                                \return     No devuelve nada
                        */
	 static void		ImprimirDebugMS(const TCHAR *Txt, ...);

		                //! Función que muestra un MessageBox con el ultimo error del sistema.
                        /*! Función que muestra un MessageBox con el ultimo error del sistema. Ademas puedes añadir texto delante del mensaje del sistema. 
		                        \fn			static void	MostrarUltimoError(const TCHAR *Mensaje = NULL);
								\param[in]	Mensaje	: Puntero a una cadena de texto con texto extra para el mensaje. Puede ser NULL.
                                \return     No devuelve nada
                        */
	 static void	    MostrarUltimoError(const TCHAR *Mensaje = NULL);
	};					//
	////////////////////// Fin DWL::DWLDebug

};


#endif // DWL_DEBUG_H

/*! \file DWLDebug.h
\version
  [03/02/2006] <b>0.5</b> \n
	Añadida función MostrarUltimoError, para poder mostrar mensajes de error del sistema personalizados.

  [01/02/2004] <b>0.4</b> \n
	Creada clase estatica con varias funciones para ayudar en la depuración.
*/