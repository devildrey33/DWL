/////////////////////////////////////////////////////////////////////////////////////////////////
// Esta clase ha sido creada por [\DReY\] el dia 03/11/2003 y es uno de los ejemplos de        //
// http://www.webpersonal.net/devildrey33 (DReY Visual C++ page)                               //
// Puedes modificar esta clase a tu gusto. Si realizas alguna modificacion que creas que es    //
// mejor para esta clase porfavor mandamela por e-mail para que pueda verla :)                 // 
// E-Mail & MSN Messenger : devildrey33@hotmail.com                                            //
//                                                                                             //
// Version 1.2                                                                                 //
// Ultima modificación : 20/05/2005                                                            //
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef DWL_VENTANA_H
#define DWL_VENTANA_H

#include "DWLEventosPadre.h"


//#include "DWLMenuEx.h"
//#include "DWLMouse.h"
 
namespace DWL {

	namespace Ventanas {

        class DWLVentana : public Base::DWLEventosPadre<LRESULT> {
		   public : ////////////////// -Declaraciones publicas

									//! Constructor  
                                    /*! Constructor por defecto.
									        \fn			DWLVentana(void);
                                            \return     No devuelve nada
                                    */
									DWLVentana(void);

									//! Destructor  
                                    /*! Destructor por defecto.
									        \fn		   ~DWLVentana(void);
                                            \return     No devuelve nada
                                    */
								   ~DWLVentana(void);

								    //! Función que crea la ventana.
								    /*!	Esta función crea la ventana.
										    \fn			HWND CrearVentana(HWND hWndParent, const TCHAR *nNombre, UINT nEstilos, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, HMENU nMenu, DWORD nEstiloExtendido = NULL, HBRUSH nColorFondo = NULL, const int nIconoRecursos = 32512);
										    \param[in]	hWndParent			: HWND de la ventana que sera la ventana padre para esta. Puede ser NULL.
										    \param[in]	nNombre				: Nombre para la clase ventana.
										    \param[in]	nEstilos			: Estilos validos para ventanas (WS_OVERLAPPED | WS_VISIBLE | etc..)
										    \param[in]	nTexto				: Titulo para la ventana.
										    \param[in]	cX					: Posicion X. Puedes especificar DWL_CENTRADO para que se centre.
										    \param[in]	cY					: Posicion Y. Puedes especificar DWL_CENTRADO para que se centre.
										    \param[in]	cAncho				: Ancho de la ventana.
										    \param[in]	cAlto				: Alto del la ventana.
										    \param[in]	nMenu				: Menu para la ventana.
										    \param[in]	nEstiloExtendido	: Estilos extendidos validos.
										    \param[in]	nColorFondo			: Brocha con el color del fondo de la ventana. Puede ser NULL.
										    \param[in]	nIconoRecursos		: ID del icono de los recursos que se asignara a la ventana. Puede ser 32512 para que se asigne el icono de la aplicación.
										    \return		Devuelve el HWND de la ventana. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para ver el error.
								    */
           HWND			            CrearVentana(HWND hWndParent, const TCHAR *nNombre, UINT nEstilos, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, HMENU nMenu, DWORD nEstiloExtendido = NULL, HBRUSH nColorFondo = NULL, const int nIconoRecursos = 32512);

							        //! Función virtual para determinar si la ventana es maximizable.
							        /*! Esta función virtual determina si la ventana es maximizable.
									        \fn			virtual void Maximizable(const bool nMax);
									        \param[in]	nMax : Especifica true para que la ventana sea maximizable, false para lo contrario.
									        \return		Esta función no devuelve nada.
							        */
		   virtual void             Maximizable(const bool nMax);

							        //! Función virtual que nos dice si la ventana es maximizable.
							        /*! Esta función virtual nos dice si la ventana es maximizable.
									        \fn			virtual const bool Maximizable(void);
									        \return		Devuelve true si la ventana es maximizable, false en caso contrario.
							        */
		   virtual const bool       Maximizable(void);

							        //! Función que nos dice si la ventana esta maximizada en este momento.
							        /*! Esta función nos dice si la ventana esta maximizada en este momento.
									        \fn			const bool Maximizada(void);
									        \return		Devuelve true si la ventana esta maximizada, false en caso contrario.
							        */
           const bool				Maximizada(void);

							        //! Función virtual para determinar si la ventana es minimizable.
							        /*! Esta función virtual determina si la ventana es minimizable.
									        \fn			virtual void Minimizable(const bool nMin);
									        \param[in]	nMix : Especifica true para que la ventana sea minimizable, false para lo contrario.
									        \return		Esta función no devuelve nada.
							        */
		   virtual void             Minimizable(const bool nMin);

							        //! Función virtual que nos dice si la ventana es minimizable.
							        /*! Esta función virtual nos dice si la ventana es minimizable.
									        \fn			virtual const bool Minimizable(void);
									        \return		Devuelve true si la ventana es minimizable, false en caso contrario.
							        */
		   virtual const bool       Minimizable(void);

							        //! Función que nos dice si la ventana esta minimizada en este momento.
							        /*! Esta función nos dice si la ventana esta minimizada en este momento.
									        \fn			const bool Minimizada(void);
									        \return		Devuelve true si la ventana esta minimizada, false en caso contrario.
							        */
		   const bool				Minimizada(void);

							        //! Función para posicionar la ventana siempre delante de todas las otras ventanas.
							        /*! Esta función posiciona la ventana siempre delante de todas las otras ventanas.
									        \fn			virtual void SiempreDelante(const bool SD);
									        \param[in]	SD : Especifica true para que la ventana quede siempre por delante, false para que tenga un comportamiento normal segun su coordenada Z.
									        \return		Esta función no devuelve nada.
                                            \remarks    Por norma las ventanas se posicionan utilizando el OrdenZ, que es un indice para determinar en que posición estan las ventanas. 
                                                        Si por ejemplo creas dos ventanas la primera se pondra en el orden 1, y la segunda en el orden 0, 
                                                        de forma que si se crean en cascada deberias ver la segunda ventana por delante de todo.
							        */
		   virtual void				SiempreDelante(const bool SD);

							        //! Función para asignar el titulo de la ventana.
							        /*! Esta función asigna el titulo de la ventana.
									        \fn			virtual void Titulo(const TCHAR *Txt);
									        \param[in]	Txt : Nuevo texto para el titulo de la ventana.
									        \return		Esta función no devuelve nada.
							        */
		   virtual void		   		Titulo(const TCHAR *Txt);

							        //! Función para obtener el titulo de la ventana.
							        /*! Esta función obtiene el titulo de la ventana en el buffer especificado.
									        \fn			void Titulo(const TCHAR *Txt);
									        \param[in]	Txt    : Buffer de texto para obtener el titulo.
                                            \param[in]  TamTxt : Tamaño del buffer para el titulo.
									        \return		Esta función devuelve 0 en caso de error. En caso de exito devuelve el numero de caracteres que contiene el titulo sin incluir el terminador NULL.
							        */
		   int						Titulo(TCHAR *Txt, const int TamTxt);

		  protected: ///////////////// -Declaraciones protegidas (Solo podran usarse en la clase heredada no desde fuera)

								    //! Esqueleto inicial que enlaza esta clase con la ventana.
								    /*! Esta función es el esqueleto inicial que enlaza esta clase con la ventana.
										    \fn			static LRESULT CALLBACK _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
										    \param[in]	HandleVentana	: Identificador de ventana.
										    \param[in]	uMsg			: Mensaje.
										    \param[in]	wParam			: Parametro1.
										    \param[in]	lParam			: Parametro2.
										    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
								    */
           static LRESULT CALLBACK _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
		};			     			//
		////////////////////////////// Fin DWLVentana




	};
};

#endif // DWL_VENTANA_H



// Ver 1.1a
// -Se ha agregado la función :
//	 virtual void Evento_Mouse_Rueda(const int VirtKey, const short Delta, const short cX, const short cY); 
//   para poder controlar los mensajes de la ruedecita.
// -El codigo ha sido modificado para poder editarlo mejor



// Vesion 1.2
// Se han eliminado todas las macros que empezaban por On... y se han creado unas nuevas macros mas rapidas que las anteriores.
// Estas macros empiezan por ENLACE_... para cada evento tienes su macro, excepto para el Evento_Pintar que tiene 2 posibilidades
// pintar HDC o pintar DWLhDC.
// Todos los nombres de Funciónes que estaban medio en ingles medio en castellano han sido renombrados a castellano.




