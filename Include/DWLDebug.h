/*! \file DWLDebug.h
	\brief		Archivo que contiene funciones utiles para la depuraci�n.
	\author		devildrey33
	\date		Creado el [01/02/2004], ultima modificaci�n el [05/10/2010]
*/ 

#ifndef DWL_DEBUG_H
#define DWL_DEBUG_H

#include "DWL.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Clase para mostrar informaci�n de depuraci�n
	class DWLDebug {
	public : ///////////// Miembros publicos
		                //! Constructor
                        /*! Constructor por defecto.
		                        \fn			DWLDebug(void);
                                \return     No devuelve nada
                        */
						DWLDebug(void) { };

		                //! Funci�n que imprime texto por la pantallita de debug
                        /*! Funci�n que imprime texto por la pantallita de debug, al estilo del printf
		                        \fn			static void	ImprimirDebug(const TCHAR *Txt, ...);
								\param[in]	Txt		: Puntero a una cadena de texto
								\param[in]	...		: Parametros opcionales
                                \return     No devuelve nada
                        */
	 static void		ImprimirDebug(const TCHAR *Txt, ...);

		                //! Funci�n que imprime texto por la pantallita de debug, calculando el tiempo.
                        /*! Funci�n que imprime texto por la pantallita de debug, al estilo del printf. Ademas esta funci�n calcula el tiempo que ha transcurrido desde la ultima vez que se llamo a esta funci�n. 
		                        \fn			static void	ImprimirDebugMS(const TCHAR *Txt, ...);
								\param[in]	Txt		: Puntero a una cadena de texto
								\param[in]	...		: Parametros opcionales
                                \return     No devuelve nada
                        */
	 static void		ImprimirDebugMS(const TCHAR *Txt, ...);

		                //! Funci�n que muestra un MessageBox con el ultimo error del sistema.
                        /*! Funci�n que muestra un MessageBox con el ultimo error del sistema. Ademas puedes a�adir texto delante del mensaje del sistema. 
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
	A�adida funci�n MostrarUltimoError, para poder mostrar mensajes de error del sistema personalizados.

  [01/02/2004] <b>0.4</b> \n
	Creada clase estatica con varias funciones para ayudar en la depuraci�n.
*/