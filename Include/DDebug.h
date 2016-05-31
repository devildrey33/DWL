#ifndef DDEBUG_H
	#define DDEBUG_H

	#include "DObjeto.h"

	#ifdef _DEBUG
		#define DWL_SOLO_DEBUG(SD)				SD
		#define DWL_IMPRIMIR_DEBUG(...)         DDebug::ImprimirDebug(__VA_ARGS__);
		#define DWL_MOSTRAR_ULTIMO_ERROR(...)   DDebug::MostrarUltimoError(__VA_ARGS__);
	#else
		#define DWL_SOLO_DEBUG(SD)				
		#define DWL_IMPRIMIR_DEBUG(...)
		#define DWL_MOSTRAR_ULTIMO_ERROR(...)   
	#endif

	namespace DWL {
		class DDebug  {
		public:
			virtual const DEnum_Objeto			Objeto_Tipo(void) { return DEnum_Objeto_Debug; };
			DDebug(void) { };

			//! Función que imprime texto por la pantallita de debug
			/*! Función que imprime texto por la pantallita de debug, al estilo del printf
			\fn			static void	ImprimirDebug(const TCHAR *Txt, ...);
			\param[in]	Txt		: Puntero a una cadena de texto
			\param[in]	...		: Parametros opcionales
			\return     No devuelve nada
			*/
			static void     ImprimirDebug(const TCHAR *nTxt, ...);

			//! Función que muestra un MessageBox con el ultimo error del sistema.
			/*! Función que muestra un MessageBox con el ultimo error del sistema. Ademas puedes añadir texto delante del mensaje del sistema.
			\fn			static void	MostrarUltimoError(const TCHAR *Mensaje = NULL);
			\param[in]	Mensaje	: Puntero a una cadena de texto del estilo printf la cual puede ser NULL o puede contener datos extras del error
			\param[in]	...		: Parametros opcionales para añadir al estilo printf
			\return     No devuelve nada
			*/
			static void	    MostrarUltimoError(const TCHAR *Mensaje = NULL, ...);
		};
	};

#endif
