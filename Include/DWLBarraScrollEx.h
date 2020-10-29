/*! \file DWLBarraScrollEx.h
	\brief Archivo que contiene las definiciones de las clases de la BarraScrollEx.

    \details Esta clase se usa para crear controles que vayan a utilizar scrollbars de esta libreria.
			 Para ello trae los siguientes metodos que deberiamos utilizar a la hora de capturar el mouse :
			 - BarraScrollEx_Nucleo::BarraScrollEx_Mouse_MovimientoScroll()
			 - BarraScrollEx_Nucleo::BarraScrollEx_Mouse_MovimientoV()
			 - BarraScrollEx_Nucleo::BarraScrollEx_Mouse_MovimientoH()
			 - BarraScrollEx_Nucleo::BarraScrollEx_Mouse_BotonPresionado()
			 - BarraScrollEx_Nucleo::BarraScrollEx_Mouse_BotonPresionadoV()
			 - BarraScrollEx_Nucleo::BarraScrollEx_Mouse_BotonPresionadoH()
			 - BarraScrollEx_Nucleo::BarraScrollEx_Mouse_BotonSoltado()
			 - BarraScrollEx_Nucleo::BarraScrollEx_Mouse_BotonSoltadoV()
			 - BarraScrollEx_Nucleo::BarraScrollEx_Mouse_BotonSoltadoH()
             \n
			 Cada uno de estos metodos retorna true en caso de haber realizado alguna operacion y false en caso contrario.
			 Para tenerlo mas claro retornan true si las coordenadas introducidas coinciden con parte del control.
			 De esta forma el codigo del control deberia montarse mas o menos asi en cada evento :
			  if (BarraScrollEx_Mouse_....() == FALSE) { ... } // si es true no hay que hacer nada, porque el evento es para el scroll

			 Para pintar los scrollbars debes usar las funciones BarraScrollEx_PintarV() y BarraScrollEx_PintarH() en el Evento_Pintar()

			 Despues el scroll cuando cambia de posicion, llama a la función virtual Repintar y a la función Evento_Scroll_CambioPos.
			 Y finalmente tiene varias funciones para asignar y obtener el maximo, valor y pagina para cada scroll.
			 BarraScrollEx_MaximoV(), BarraScrollEx_PaginaV(), BarraScrollEx_ValorV()
			 BarraScrollEx_MaximoH(), BarraScrollEx_PaginaH(), BarraScrollEx_ValorH()

			 Ademas si lo deseas puedes reemplazar las funciones de pintado tanto para los botones como para el fondo como para el scroll

			 Por ultimo tambien deberas enlazar la función BarraScrollEx_Evento_Temporizador al Evento_Temporizador del control, para que los botones y el scroll funcionen correctamente.

			 Todas estas funciones se ejecutaran siempre que el estado del scroll sea visible.

	\author	 devildrey33
	\date	 Creado el [20/05/2007], ultima modificación el [31/05/2010]

	\remarks
			 Archivo creado por devildrey33 para http://www.devildrey33.es														\n
			 Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
			  - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
			  - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
			  - http://www.softcatala.cat/wiki/GPL3		 (Catalá, traduccion no oficial)																\n

	\sa      DWL::ControlesEx::DWLListaEx_Nucleo, DWL::ControlesEx::DWLArbolEx_Nucleo
*/


#ifndef DWL_BARRASCROLLEX_H
#define DWL_BARRASCROLLEX_H

//#define DWL_BaseControlExScroll_DEBUG // Descomenta esta linea para pasar al modo debug de esta clase


//#include "DWLControlEx.h"
#include <vector>
#include ".\DWLBarraScrollEx\DWLBarraScrollEx_Boton.h"
#include ".\DWLBarraScrollEx\DWLBarraScrollEx_Colores.h"
#include ".\DWLBarraScrollEx\DWLBarraScrollEx_ParametrosClick.h"

//! Estado automatico de visibilidad para los scrolls
#define DWL_BARRASCROLLEX_AUTOMATICO -1




//! Objeto presionado NINGUNO
#define DWL_BARRASCROLLEX_OBJETO_NINGUNO			0
//! Objeto presionado boton superior / izquierdo
#define DWL_BARRASCROLLEX_OBJETO_BOTON_SUPERIOR		1
//! Objeto presionado boton izquierdo / superior
#define DWL_BARRASCROLLEX_OBJETO_BOTON_IZQUIERDO	1
//! Objeto presionado boton inferior / derecho
#define DWL_BARRASCROLLEX_OBJETO_BOTON_INFERIOR		2
//! Objeto presionado boton derecho / inferior
#define DWL_BARRASCROLLEX_OBJETO_BOTON_DERECHO		2
//! Objeto presionado Scroll
#define DWL_BARRASCROLLEX_OBJETO_SCROLL				3
//! Objeto presionado fondo superior / izquierdo
#define DWL_BARRASCROLLEX_OBJETO_FONDO_SUPERIOR		4
//! Objeto presionado fondo izquierdo / superior
#define DWL_BARRASCROLLEX_OBJETO_FONDO_IZQUIERDO	4
//! Objeto presionado fondo inferior / derecho
#define DWL_BARRASCROLLEX_OBJETO_FONDO_INFERIOR		5
//! Objeto presionado fondo derecho / inferior
#define DWL_BARRASCROLLEX_OBJETO_FONDO_DERECHO		5
//! Objeto presionado boton extendido
#define DWL_BARRASCROLLEX_OBJETO_BOTON_EXTENDIDO	6


//! Enumeración de los posibles estados del scroll
enum DWL_Enum_BarraScrollEx_Estado {
	DWL_Enum_BarraScrollEx_Estado_Normal,
	DWL_Enum_BarraScrollEx_Estado_BotonSuperiorResaltado,
	DWL_Enum_BarraScrollEx_Estado_BotonSuperiorPresionado,
	DWL_Enum_BarraScrollEx_Estado_BotonInferiorResaltado,
	DWL_Enum_BarraScrollEx_Estado_BotonInferiorPresionado,
	DWL_Enum_BarraScrollEx_Estado_FondoSuperiorResaltado,
	DWL_Enum_BarraScrollEx_Estado_FondoSuperiorPresionado,
	DWL_Enum_BarraScrollEx_Estado_FondoInferiorResaltado,
	DWL_Enum_BarraScrollEx_Estado_FondoInferioPresionado,
	DWL_Enum_BarraScrollEx_Estado_ScrollResaltado,
	DWL_Enum_BarraScrollEx_Estado_ScrollPresionado,
	DWL_Enum_BarraScrollEx_Estado_BotonExtendidoResaltado,
	DWL_Enum_BarraScrollEx_Estado_BotonExtendidoPresionado
};
															
//! Enumeración de los controles presionados dentro del scroll
enum DWL_Enum_BarraScrollEx_ControlPresionado {
	DWL_Enum_BarraScrollEx_ControlPresionado_Ninguno,
	DWL_Enum_BarraScrollEx_ControlPresionado_BotonSuperior,
	DWL_Enum_BarraScrollEx_ControlPresionado_BotonInferior,
	DWL_Enum_BarraScrollEx_ControlPresionado_FondoSuperior,
	DWL_Enum_BarraScrollEx_ControlPresionado_FondoInferior,
	DWL_Enum_BarraScrollEx_ControlPresionado_Scroll,
	DWL_Enum_BarraScrollEx_ControlPresionado_BotonExtendido
};

//! Enumeración del tipo de area presionada
enum DWL_Enum_BarraScrollEx_TipoScroll {
	DWL_Enum_BarraScrollEx_TipoScroll_VerticalSuperior,
	DWL_Enum_BarraScrollEx_TipoScroll_VerticalInferior,
	DWL_Enum_BarraScrollEx_TipoScroll_Vertical,
	DWL_Enum_BarraScrollEx_TipoScroll_HorizontalDerecho,
	DWL_Enum_BarraScrollEx_TipoScroll_HorizontalIzquierdo,
	DWL_Enum_BarraScrollEx_TipoScroll_Horizontal
};

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {
		//! Clase base para crear controles extendidos que necesiten una o dos barras de scroll
		class DWLBarraScrollEx_Nucleo {
		public : ///////////////////////////////////////////// Miembros publicos

															//! Constructor.
															/*! Constructor.
																\fn			DWLBarraScrollEx_Nucleo(void);
																\return		No devuelve nada.
															*/
															DWLBarraScrollEx_Nucleo(void);

															//! Destructor.
															/*! Destructor.
																\fn			~DWLBarraScrollEx_Nucleo(void);
																\return		No devuelve nada.
															*/
	 	 virtual										   ~DWLBarraScrollEx_Nucleo(void);

															//! Función que crea la barra de scroll vertical.
															/*! Esta funcion crea la barra de scroll vertical en nuestro control.
																\fn			void BarraScrollEx_CrearV(const BOOL nVisible = DWL_BARRASCROLLEX_AUTOMATICO, const long nMaximo = 10, const long nPagina = 5, const long nValor = 0);
																\param[in]	nVisible	: TRUE para que sea visible, FALSE para que sea invisible. Tambien puedes especificar el parametro DWL_BARRASCROLLEX_AUTOMATICO.
																\param[in]	nMaximo		: Valor maximo para el scroll.
																\param[in]	nPagina		: Valor de la pagina para el scroll.
																\param[in]	nValor		: Valor actual para el scroll.
																\return		No devuelve nada.
																\remarks	Si nVisible es DWL_BARRASCROLLEX_AUTOMATICO, se mirara si _BarraScrollEx_MaximoV es mas grande que _BarraScrollEx_PaginaV para decidir si el scroll es visible.
																			Si el maximo supera la pagina el scroll sera visible, en caso contrario no se vera.
																\sa			BarraScrollEx_CrearH()
															*/
		 void												BarraScrollEx_CrearV(const BOOL nVisible = DWL_BARRASCROLLEX_AUTOMATICO, const long nMaximo = 10, const long nPagina = 5, const long nValor = 0);

															//! Función que crea la barra de scroll horizontal.
															/*! Esta funcion crea la barra de scroll horizontal en nuestro control.
																\fn			void BarraScrollEx_CrearH(const BOOL nVisible = DWL_BARRASCROLLEX_AUTOMATICO, const long nMaximo = 10, const long nPagina = 5, const long nValor = 0);
																\param[in]	nVisible	: TRUE para que sea visible, FALSE para que sea invisible. Tambien puedes especificar el parametro DWL_BARRASCROLLEX_AUTOMATICO.
																\param[in]	nMaximo		: Valor maximo para el scroll.
																\param[in]	nPagina		: Valor de la pagina para el scroll.
																\param[in]	nValor		: Valor actual para el scroll.
																\return		No devuelve nada.
																\remarks	Si nVisible es DWL_BARRASCROLLEX_AUTOMATICO, se mirara si _BarraScrollEx_MaximoH es mas grande que _BarraScrollEx_PaginaH para decidir si el scroll es visible.
																			Si el maximo supera la pagina el scroll sera visible, en caso contrario no se vera.
																\sa			BarraScrollEx_CrearV()
															*/
		 void												BarraScrollEx_CrearH(const BOOL nVisible = DWL_BARRASCROLLEX_AUTOMATICO, const long nMaximo = 10, const long nPagina = 5, const long nValor = 0);

	                                                        //! Función que agrega un boton extendido a la barra de scroll vertical.
	                                                        /*! Esta funcion agrega un boton extendido a la barra de scroll vertical.
		                                                        \fn			BOOL BarraScrollEx_AgregarBotonV(const UINT IconoRecursos, const UINT IDBoton);
		                                                        \param[in]	IconoRecursos	: ID del icono de los recursos que usara este boton.
		                                                        \param[in]	IDBoton			: ID de este boton extendido.
		                                                        \return		Devuelve TRUE si se ha creado correctamente, FALSE si la ID del boton ya existe.
		                                                        \remarks	Los botones comparten el estado visible de su barra, es decir si la barra vertical es visible los botones verticales tambien.
		                                                        \sa			BarraScrollEx_AgregarBotonH(), BarraScrollEx_Evento_BotonExtendido_Click()

	                                                        */
		 BOOL 										        BarraScrollEx_AgregarBotonV(const UINT IconoRecursos, const UINT IDBoton);

															//! Función que agrega un boton extendido a la barra de scroll horizontal.
															/*! Esta funcion agrega un boton extendido a la barra de scroll horizontal.
																\fn			void BarraScrollEx_AgregarBotonH(const UINT IconoRecursos, const UINT IDBoton);
																\param[in]	IconoRecursos	: ID del icono de los recursos que usara este boton.
																\param[in]	IDBoton			: ID de este boton extendido.
		                                                        \return		Devuelve TRUE si se ha creado correctamente, FALSE si la ID del boton ya existe.
																\remarks	Los botones comparten el estado visible de su barra, es decir si la barra horizontal es visible los botones horizontales tambien.
																\sa			BarraScrollEx_AgregarBotonV(), BarraScrollEx_Evento_BotonExtendido_Click()

															*/
		 BOOL			    								BarraScrollEx_AgregarBotonH(const UINT IconoRecursos, const UINT IDBoton);

		                                                    //! Función que elimina un boton extendido a la barra de scroll vertical.
		                                                    /*! Esta funcion elimina un boton extendido a la barra de scroll vertical.
			                                                    \fn			BOOL BarraScrollEx_EliminarBotonV(const UINT IDBoton);
			                                                    \param[in]	IDBoton			: ID de este boton extendido.
			                                                    \return		Devuelve TRUE si se ha eliminado correctamente, FALSE si la ID del boton no existe.
			                                                    \remarks	Los botones comparten el estado visible de su barra, es decir si la barra horizontal es visible los botones horizontales tambien.
			                                                    \sa			BarraScrollEx_AgregarBotonV(), BarraScrollEx_Evento_BotonExtendido_Click()
		                                                    */
         BOOL                                               BarraScrollEx_EliminarBotonV(const UINT IDBoton);

	                                                        //! Función que elimina los botones extendido a la barra de scroll vertical.
	                                                        /*! Esta funcion elimina los botones extendido a la barra de scroll vertical.
		                                                        \fn			void BarraScrollEx_EliminarBotonesV(void);
		                                                        \return		Esta función no devuelve nada.
		                                                        \remarks	Los botones comparten el estado visible de su barra, es decir si la barra horizontal es visible los botones horizontales tambien.
		                                                        \sa			BarraScrollEx_AgregarBotonV(), BarraScrollEx_Evento_BotonExtendido_Click()
	                                                        */
        void                                                BarraScrollEx_EliminarBotonesV(void);

		                                                    //! Función que elimina los botones extendido a la barra de scroll horizontal.
		                                                    /*! Esta funcion elimina los botones extendido a la barra de scroll horizontal.
			                                                    \fn			void BarraScrollEx_EliminarBotonesH(void);
			                                                    \return		Esta función no devuelve nada.
			                                                    \remarks	Los botones comparten el estado visible de su barra, es decir si la barra horizontal es visible los botones horizontales tambien.
			                                                    \sa			BarraScrollEx_AgregarBotonV(), BarraScrollEx_Evento_BotonExtendido_Click()
		                                                    */
        void                                                BarraScrollEx_EliminarBotonesH(void);

		                                                    //! Función que elimina un boton extendido a la barra de scroll horizontal.
		                                                    /*! Esta funcion elimina un boton extendido a la barra de scroll horizontal.
			                                                    \fn			BOOL BarraScrollEx_EliminarBotonH(const UINT IDBoton);
			                                                    \param[in]	IDBoton			: ID de este boton extendido.
			                                                    \return		Devuelve TRUE si se ha eliminado correctamente, FALSE si la ID del boton no existe.
			                                                    \remarks	Los botones comparten el estado visible de su barra, es decir si la barra horizontal es visible los botones horizontales tambien.
			                                                    \sa			BarraScrollEx_AgregarBotonV(), BarraScrollEx_Evento_BotonExtendido_Click()
		                                                    */
         BOOL                                                BarraScrollEx_EliminarBotonH(const UINT IDBoton);

															//! Función para asignar el estado de visibilidad para el scroll vertical.
															/*! Esta funcion asigna el estado de visibilidad para el scroll vertical.
																\fn			void BarraScrollEx_VisibleV(const BOOL sVisible);
																\param[in]	sVisible : TRUE para que sea visible FALSE para que no sea visible, y DWL_BARRASCROLLEX_AUTOMATICO para que sea automatico.
																\return		No devuelve nada.
															*/
		 inline void										BarraScrollEx_VisibleV(const BOOL sVisible) {
																_BarraScrollEx_VisibleV = sVisible;
															};

															//! Función para obtener el estado de visibilidad para el scroll vertical.
															/*! Esta función devuelve el estado de visibilidad para el scroll vertical.
																\fn			inline BOOL BarraScrollEx_VisibleV(void);
																\return		Devuelve TRUE si es visible, FALSE en caso contrario.
																\remarks	Esta función devuelve siempre TRUE o FALSE aunque el scroll este en modo automatico (DWL_BARRASCROLLEX_AUTOMATICO).
															*/
		 inline BOOL									    BarraScrollEx_VisibleV(void) {
																if (_BarraScrollEx_VisibleV == DWL_BARRASCROLLEX_AUTOMATICO) return (_BarraScrollEx_MaximoV > _BarraScrollEx_PaginaV);
																return _BarraScrollEx_VisibleV;
															};

															//! Función para obtener el valor actual del scroll vertical.
															/*! Esta función devuelve el valor actual del scroll vertical.
																\fn			inline long BarraScrollEx_ValorV(void);
																\return		Devuelve el valor actual del scroll vertical.
															*/
		 inline long									    BarraScrollEx_ValorV(void) {
																return _BarraScrollEx_ValorV;
															};

															//! Función para obtener el valor maximo del scroll vertical.
															/*! Esta función devuelve el valor maximo del scroll vertical.
																\fn			inline long BarraScrollEx_MaximoV(void);
																\return		Devuelve el valor maximo del scroll vertical.
															*/
		 inline long									    BarraScrollEx_MaximoV(void) {
																return _BarraScrollEx_MaximoV;
															};

															//! Función para obtener el valor de una pagina del scroll vertical.
															/*! Esta función devuelve el valor de una pagina del scroll vertical.
																\fn			inline long BarraScrollEx_PaginaV(void);
																\return		Devuelve el valor maximo del scroll vertical.
																\remarks	La pagina es el total de objetos que caben en la vista vertical.
															*/
		 inline long									    BarraScrollEx_PaginaV(void) {
																return _BarraScrollEx_PaginaV;
															};

															//! Función para asignar el valor actual para el scroll vertical.
															/*! Esta función asigna el valor actual para el scroll vertical.
																\fn			void BarraScrollEx_ValorV(const long nValor);
																\param[in]	nValor : Nuevo valor actual para el scroll vertical.
																\return		No devuelve nada.
															*/
		 inline void										BarraScrollEx_ValorV(const long nValor) {
																_BarraScrollEx_PosActualV = nValor;
																_BarraScrollEx_ValorV = nValor;
																BarraScrollEx_CalcularScrollV();
															};

															//! Función para asignar el valor maximo para el scroll vertical.
															/*! Esta función asigna el valor maximo para el scroll vertical.
																\fn			void BarraScrollEx_MaximoV(const long nMaximo);
																\param[in]	nMaximo : Nuevo valor maximo para el scroll vertical.
																\return		No devuelve nada.
															*/
		 inline void										BarraScrollEx_MaximoV(const long nMaximo) {
																_BarraScrollEx_MaximoV = nMaximo;
																BarraScrollEx_CalcularScrollV();
															};

															//! Función para asignar el valor de la pagina para el scroll vertical.
															/*! Esta función asigna el valor de la pagina para el scroll vertical.
																\fn			void BarraScrollEx_PaginaV(const long nPagina);
																\param[in]	nPagina : Nuevo valor de la pagina para el scroll vertical.
																\return		No devuelve nada.
															*/
		 inline void										BarraScrollEx_PaginaV(const long nPagina) {
																_BarraScrollEx_PaginaV = nPagina;
																BarraScrollEx_CalcularScrollV();
															};

															//! Función para asignar el estado de visibilidad para el scroll horizontal.
															/*! Esta funcion asigna el estado de visibilidad para el scroll horizontal.
																\fn			void BarraScrollEx_VisibleH(const BOOL sVisible);
																\param[in]	sVisible : TRUE para que sea visible FALSE para que no sea visible, y DWL_BARRASCROLLEX_AUTOMATICO para que sea automatico.
																\return		No devuelve nada.
															*/
		 inline void										BarraScrollEx_VisibleH(const BOOL sVisible) {
																_BarraScrollEx_VisibleH = sVisible;
															};

															//! Función para obtener el estado de visibilidad para el scroll horizontal.
															/*! Esta función devuelve el estado de visibilidad para el scroll horizontal.
																\fn			inline BOOL BarraScrollEx_VisibleH(void);
																\return		Devuelve TRUE si es visible, FALSE en caso contrario.
																\remarks	Esta función devuelve siempre TRUE o FALSE aunque el scroll este en modo automatico (DWL_BARRASCROLLEX_AUTOMATICO).
															*/
		 inline BOOL									    BarraScrollEx_VisibleH(void) {
																if (_BarraScrollEx_VisibleH == DWL_BARRASCROLLEX_AUTOMATICO) return (_BarraScrollEx_MaximoH > _BarraScrollEx_PaginaH);
																return _BarraScrollEx_VisibleH;
															};

															//! Función para obtener el valor actual del scroll horizontal.
															/*! Esta función devuelve el valor actual del scroll horizontal.
																\fn			inline long BarraScrollEx_ValorH(void);
																\return		Devuelve el valor actual del scroll horizontal.
															*/
		 inline long									    BarraScrollEx_ValorH(void) {
																return _BarraScrollEx_ValorH;
															};

															//! Función para obtener el valor maximo del scroll horizontal.
															/*! Esta función devuelve el valor maximo del scroll horizontal.
																\fn			inline long BarraScrollEx_MaximoH(void);
																\return		Devuelve el valor maximo del scroll horizontal.
															*/
		 inline long									    BarraScrollEx_MaximoH(void) {
																return _BarraScrollEx_MaximoH;
															};

															//! Función para obtener el valor de una pagina del scroll horizontal.
															/*! Esta función devuelve el valor de una pagina del scroll horizontal.
																\fn			inline long BarraScrollEx_PaginaH(void);
																\return		Devuelve el valor maximo del scroll horizontal.
																\remarks	La pagina es el total de objetos que caben en la vista horizontal.
															*/
		 inline long									    BarraScrollEx_PaginaH(void) {
																return _BarraScrollEx_PaginaH;
															};

															//! Función para asignar el valor actual para el scroll horizontal.
															/*! Esta función asigna el valor actual para el scroll horizontal.
																\fn			void BarraScrollEx_ValorH(const long nPagina);
																\param[in]	nPagina : Nuevo valor actual para el scroll horizontal.
																\return		No devuelve nada.
															*/
		 inline void										BarraScrollEx_ValorH(const long nValor) {
																_BarraScrollEx_PosActualH = nValor;
																_BarraScrollEx_ValorH = nValor;
																BarraScrollEx_CalcularScrollH();
															};

															//! Función para asignar el valor maximo para el scroll horizontal.
															/*! Esta función asigna el valor maximo para el scroll horizontal.
																\fn			void BarraScrollEx_MaximoH(const long nMaximo);
																\param[in]	nMaximo : Nuevo valor maximo para el scroll horizontal.
																\return		No devuelve nada.
															*/
		 inline void										BarraScrollEx_MaximoH(const long nMaximo) {
																_BarraScrollEx_MaximoH = nMaximo;
																BarraScrollEx_CalcularScrollH();
															};

															//! Función para asignar el valor de la pagina para el scroll horizontal.
															/*! Esta función asigna el valor de la pagina para el scroll horizontal.
																\fn			void BarraScrollEx_PaginaH(const long nPagina);
																\param[in]	nPagina : Nuevo valor de la pagina para el scroll horizontal.
																\return		No devuelve nada.
															*/
		 inline void										BarraScrollEx_PaginaH(const long nPagina) {
																_BarraScrollEx_PaginaH = nPagina;
																BarraScrollEx_CalcularScrollH();
															};

															//! Función que pinta el scroll vertical en el DC especificado.
															/*! Esta función pinta el scroll vertical en el DC especificado.
																\fn			void BarraScrollEx_PintarV(HDC hDC);
																\param[in]	hDC : hDC donde se pintara la barra de scroll vertical.
																\return		No devuelve nada.
															*/
		 void												BarraScrollEx_PintarV(HDC hDC);

															//! Función que pinta el scroll horizontal en el DC especificado.
															/*! Esta función pinta el scroll horizontal en el DC especificado.
																\fn			void BarraScrollEx_PintarH(HDC hDC);
																\param[in]	hDC : hDC donde se pintara la barra de scroll horizontal.
																\return		No devuelve nada.
															*/
		 void												BarraScrollEx_PintarH(HDC hDC);

															//! Función virtual que debera sobreescribir el control para repintar.
															/*! Esta funcion virtual debe ser re-escrita en la clase contenedora de este control para pintar todo el control.
																	\fn			virtual void Repintar(const bool Forzar = false);
																	\param[in]	nForzar	: Valor que determina si se fuerza el repintado.
																	\return		No devuelve nada.
																	\remarks	Si se espeficica false en nForzar, la funcion repintar debera decidir si se repinta el control o no.
															*/
		 virtual void										Repintar(const bool Forzar = false) { };

															//! Función para repintar las barras de scroll.
															/*! Esta funcion repinta las barras de scroll si es necesario o si se especifica true en Forzar.
																	\fn			void BarraScrollEx_Repintar(HWND hWndControl, const bool Forzar = false);
																	\param[in]	hWndControl	: HWND de la ventana destino donde se van a repintar los scrolls.
																	\param[in]	nForzar		: Valor que determina si se fuerza el repintado.
																	\return		No devuelve nada.
															*/
		 void												BarraScrollEx_Repintar(HWND hWndControl, const bool Forzar = false);

															//! Clase que contiene los colores para las barras de scroll.
		 DWLBarraScrollEx_Colores						    BarraScrollEx_Colores;

		 inline void                                        BarraScrollEx_Activado(const bool nActivado) { _BarraScrollEx_Activado = nActivado; };
		protected : ////////////////////////////////////////// Miembros protegidos

															//! Función que calcula las posiciones de todos los controles del scroll.
															/*! Esta funcion calcula las posiciones de todos los controles del scroll.
																	\fn			void BarraScrollEx_PosicionarScrolls(HWND hWndControl, RECT *EspacioControl, const bool nRepintar = false, const bool TieneBorde = false);
																	\param[in]	hWndControl		: HWND de la ventana destino donde se van a repintar los scrolls.
																	\param[in]	EspacioControl	: Espacio de todo el control (no solo de la barra de scroll).
																	\param[in]  nRepintar		: Valor que especifica si se repintara el control.
																	\param[in]  nTieneBorde		: Valor en el que especificamos si el control tiene borde.
																	\return		No devuelve nada.
																	\remarks	Si en el parametro nTieneBorde especificamos true, el scroll se reducira 2 pixeles de tamaño para no engancharse con el borde del control. Esta funcion deberia ser usada siempre que se cambie el tamaño del control.
															*/
		 void												BarraScrollEx_PosicionarScrolls(HWND hWndControl, RECT *EspacioControl, const bool nRepintar = false, const bool TieneBorde = false);

															//! Función virtual que recibe cuando se presiona un boton extendido del scroll.
															/*! Esta funcion virtual recibe cuando se presiona un boton extendido del scroll.
																	\fn			void BarraScrollEx_Evento_BotonExtendido_Click(DWLBarraScrollEx_Boton *nBotonExtendido);
																	\param[in]	nBotonExtendido	: Puntero a la clase DWLBarraScrollEx_Boton de la que viene el boton extendido pulsado.
																	\return		No devuelve nada.
																	\remarks	Si quieres controlar las pulsaciones de botones extendidos desde la misma clase del control, debes re-escribir esta función.
															*/
		 virtual void										BarraScrollEx_Evento_BotonExtendido_Click(DWLBarraScrollEx_Boton *nBotonExtendido) { };

															//! Función virtual que recibe cuando se cambia la posicion del scroll.
															/*! Esta funcion virtual recibe cuando se cambia la posicion del scroll.
																	\fn			void BarraScrollEx_Evento_Scroll_CambioPos(void);
																	\return		No devuelve nada.
																	\remarks	Si quieres controlar los cambios de posicion desde la misma clase del control, debes re-escribir esta función.
															*/
		 virtual void										BarraScrollEx_Evento_Scroll_CambioPos(void) { };

															//! Función virtual que pinta un boton en cualquier de sus estados.
															/*! Esta funcion virtual que pinta un boton en cualquier de sus estados.
																	\fn			void BarraScrollEx_Evento_Pintar_Boton(HDC hDC, RECT *Espacio, const int TipoBoton, const int IDIcono = 0, const int EstadoBotonEx = 0);
																	\param[in]	hDC			: hDC donde se pintara el boton.
																	\param[in]  Espacio		: Recta que contiene el espacio del boton.
																	\param[in]	TipoBoton	: Tipo de boton.
																	\return		No devuelve nada.
																	\remarks	Si re-escribes esta función, deberas encargarte de pintar el fondo del boton, el borde y su imagen.
															*/
		 virtual void										BarraScrollEx_Evento_Pintar_Boton(HDC hDC, RECT *Espacio, const int TipoBoton, const int IDIcono = 0, const int EstadoBotonEx = 0);

															//! Función virtual que pinta el scroll en cualquier de sus estados.
															/*! Esta funcion virtual que pinta el scroll en cualquier de sus estados.
																	\fn			void BarraScrollEx_Evento_Pintar_Scroll(HDC hDC, RECT *Espacio, DWL_Enum_BarraScrollEx_TipoScroll TipoScroll);
																	\param[in]	hDC			: hDC donde se pintara el boton.
																	\param[in]  Espacio		: Recta que contiene el espacio del boton.
																	\param[in]	TipoScroll	: Tipo de scroll.
																	\return		No devuelve nada.
																	\remarks	Si re-escribes esta función, deberas encargarte de pintar el fondo del control y su borde.
															*/
		 virtual void										BarraScrollEx_Evento_Pintar_Scroll(HDC hDC, RECT *Espacio, DWL_Enum_BarraScrollEx_TipoScroll TipoScroll);

															//! Función que procesa el movimiento del mouse en el scoll.
															/*! Esta función procesa el movimiento del mouse en el scroll.
																	\fn			BOOL BarraScrollEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param, const bool TieneBorde);
																	\param[in]	hWndControl		: HWND del control que contiene el scroll.
																	\param[in]	RectaControl	: Recta con el espacio del scroll.
																	\param[in]	cX				: Coordenada X del mouse relativa al control.
																	\param[in]	cX				: Coordenada Y del mouse relativa al control.
																	\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
																	\param[in]	TieneBorde  	: Parametro en el que debemos especificar si el control tiene borde.
																	\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
																	\remarks    Esta función debe ser enlazada con el Evento_Mouse_Movimiento del control que vaya a contener el scrollex.
																				Si solo vas a crear un scroll puedes usar las funcion terminada en V o H, de esta forma ahorraras el tener que procesar los mensajes para la otra barra si no va a existir.
																	\sa			BarraScrollEx_Mouse_BotonPresionado(), BarraScrollEx_Mouse_BotonSoltado()
															*/
		 BOOL											    BarraScrollEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param, const bool TieneBorde);

															//! Función que procesa los botones presionados del mouse en el scoll.
															/*! Esta función procesa los botones presionados del mouse en el scoll.
																	\fn			BOOL BarraScrollEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
																	\param[in]	hWndControl		: HWND del control que contiene el scoll.
																	\param[in]	RectaControl	: Recta con el espacio del scoll.
																	\param[in]	Boton			: Boton del mouse presionado.
																	\param[in]	cX				: Coordenada X del mouse relativa al control.
																	\param[in]	cX				: Coordenada Y del mouse relativa al control.
																	\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
																	\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
																	\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonPresionado del control que vaya a contener el scoll.
																				Si solo vas a crear un scroll puedes usar las funcion terminada en V o H, de esta forma ahorraras el tener que procesar los mensajes para la otra barra si no va a existir.
																	\sa			BarraScrollEx_Mouse_Movimiento(), BarraScrollEx_Mouse_BotonSoltado()
															*/
		 BOOL       										BarraScrollEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);

															//! Función que procesa los botones soltados del mouse en el scroll
															/*! Esta función procesa los botones soltados del mouse en el scroll.
																	\fn			BOOL BarraScrollEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT wParam);
																	\param[in]	hWndControl		: HWND del control que contiene el scroll.
																	\param[in]	RectaControl	: Recta con el espacio del scroll.
																	\param[in]	Boton			: Boton del mouse presionado.
																	\param[in]	cX				: Coordenada X del mouse relativa al control.
																	\param[in]	cX				: Coordenada Y del mouse relativa al control.
																	\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
																	\param[in]	TieneBorde  	: Parametro en el que debemos especificar si el control tiene borde.
																	\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
																	\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonSoltado del control que vaya a contener el ArbolEx.
																				Si solo vas a crear un scroll puedes usar las funcion terminada en V o H, de esta forma ahorraras el tener que procesar los mensajes para la otra barra si no va a existir.
																	\sa			BarraScrollEx_Mouse_Movimiento(), BarraScrollEx_Mouse_BotonPresionado()
															*/
		 BOOL       										BarraScrollEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);

															//! Función que procesa el movimiento del mouse en el scoll vertical.
															/*! Esta función procesa el movimiento del mouse en el scroll vertical.
																	\fn			BOOL BarraScrollEx_Mouse_MovimientoV(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param, const bool TieneBorde);
																	\param[in]	hWndControl		: HWND del control que contiene el scroll.
																	\param[in]	RectaControl	: Recta con el espacio del scroll.
																	\param[in]	cX				: Coordenada X del mouse relativa al control.
																	\param[in]	cX				: Coordenada Y del mouse relativa al control.
																	\param[in]	wParam			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
																	\param[in]	TieneBorde  	: Parametro en el que debemos especificar si el control tiene borde.
																	\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
																	\remarks    Esta funcion es especifica solo para el scroll vertical, si vas a usar ambos scrolls utiliza la funcion BarraScrollEx_Mouse_Movimiento() en ve de esta.
																	\sa			BarraScrollEx_Mouse_BotonPresionadoV(), BarraScrollEx_Mouse_BotonSoltadoV()
															*/
		 BOOL											    BarraScrollEx_Mouse_MovimientoV(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param, const bool TieneBorde);

															//! Función que procesa los botones presionados del mouse en el scoll vertical.
															/*! Esta función procesa los botones presionados del mouse en el scoll vertical.
																	\fn			BOOL BarraScrollEx_Mouse_BotonPresionadoV(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT wParam);
																	\param[in]	hWndControl		: HWND del control que contiene el scoll.
																	\param[in]	RectaControl	: Recta con el espacio del scoll.
																	\param[in]	Boton			: Boton del mouse presionado.
																	\param[in]	cX				: Coordenada X del mouse relativa al control.
																	\param[in]	cX				: Coordenada Y del mouse relativa al control.
																	\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
																	\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
																	\remarks    Esta funcion es especifica solo para el scroll vertical, si vas a usar ambos scrolls utiliza la funcion BarraScrollEx_Mouse_BotonPresionado() en ve de esta.
																	\sa			BarraScrollEx_Mouse_MovimientoV(), BarraScrollEx_Mouse_BotonSoltadoV()
															*/
		 BOOL										        BarraScrollEx_Mouse_BotonPresionadoV(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);

															//! Función que procesa los botones soltados del mouse en el scroll vertical.
															/*! Esta función procesa los botones soltados del mouse en el scroll vertical.
																	\fn			BOOL BarraScrollEx_Mouse_BotonSoltadoV(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
																	\param[in]	hWndControl		: HWND del control que contiene el scroll.
																	\param[in]	RectaControl	: Recta con el espacio del scroll.
																	\param[in]	Boton			: Boton del mouse presionado.
																	\param[in]	cX				: Coordenada X del mouse relativa al control.
																	\param[in]	cX				: Coordenada Y del mouse relativa al control.
																	\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
																	\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
																	\remarks    Esta funcion es especifica solo para el scroll vertical, si vas a usar ambos scrolls utiliza la funcion BarraScrollEx_Mouse_BotonSoltado() en ve de esta.
																	\sa			BarraScrollEx_Mouse_MovimientoV(), BarraScrollEx_Mouse_BotonPresionadoV()
															*/
		 BOOL   											BarraScrollEx_Mouse_BotonSoltadoV(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);

															//! Función que procesa el movimiento del mouse en el scoll horizontal.
															/*! Esta función procesa el movimiento del mouse en el scroll horizontal.
																	\fn			BOOL BarraScrollEx_Mouse_MovimientoH(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param, const bool TieneBorde);
																	\param[in]	hWndControl		: HWND del control que contiene el scroll.
																	\param[in]	RectaControl	: Recta con el espacio del scroll.
																	\param[in]	cX				: Coordenada X del mouse relativa al control.
																	\param[in]	cX				: Coordenada Y del mouse relativa al control.
																	\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
																	\param[in]	TieneBorde  	: Parametro en el que debemos especificar si el control tiene borde.
																	\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
																	\remarks    Esta funcion es especifica solo para el scroll horizontal, si vas a usar ambos scrolls utiliza la funcion BarraScrollEx_Mouse_Movimiento() en ve de esta.
																	\sa			BarraScrollEx_Mouse_BotonPresionadoH(), BarraScrollEx_Mouse_BotonSoltadoH()
															*/
		 BOOL   											BarraScrollEx_Mouse_MovimientoH(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param, const bool TieneBorde);

															//! Función que procesa los botones presionados del mouse en el scoll horizontal.
															/*! Esta función procesa los botones presionados del mouse en el scoll horizontal.
																	\fn			BOOL BarraScrollEx_Mouse_BotonPresionadoH(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT wParam);
																	\param[in]	hWndControl		: HWND del control que contiene el scoll.
																	\param[in]	RectaControl	: Recta con el espacio del scoll.
																	\param[in]	Boton			: Boton del mouse presionado.
																	\param[in]	cX				: Coordenada X del mouse relativa al control.
																	\param[in]	cX				: Coordenada Y del mouse relativa al control.
																	\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
																	\param[in]	TieneBorde  	: Parametro en el que debemos especificar si el control tiene borde.
																	\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
																	\remarks    Esta funcion es especifica solo para el scroll horizontal, si vas a usar ambos scrolls utiliza la funcion BarraScrollEx_Mouse_BotonPresionado() en ve de esta.
																	\sa			BarraScrollEx_Mouse_MovimientoH(), BarraScrollEx_Mouse_BotonSoltadoH()
															*/
		 BOOL       										BarraScrollEx_Mouse_BotonPresionadoH(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT wParam);

															//! Función que procesa los botones soltados del mouse en el scroll horizontal.
															/*! Esta función procesa los botones soltados del mouse en el scroll horizontal.
																	\fn			BOOL BarraScrollEx_Mouse_BotonSoltadoH(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT wParam);
																	\param[in]	hWndControl		: HWND del control que contiene el scroll.
																	\param[in]	RectaControl	: Recta con el espacio del scroll.
																	\param[in]	Boton			: Boton del mouse presionado.
																	\param[in]	cX				: Coordenada X del mouse relativa al control.
																	\param[in]	cX				: Coordenada Y del mouse relativa al control.
																	\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
																	\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
																	\remarks    Esta funcion es especifica solo para el scroll horizontal, si vas a usar ambos scrolls utiliza la funcion BarraScrollEx_Mouse_BotonSoltado() en ve de esta.
																	\sa			BarraScrollEx_Mouse_MovimientoH(), BarraScrollEx_Mouse_BotonPresionadoH()
															*/
		 BOOL   											BarraScrollEx_Mouse_BotonSoltadoH(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);

															//! Función que debe ser usada cuando el control reciba un mensaje WM_MOUSELEAVE.
															/*!	Esta función debe ser usada cuando el control reciba un mensaje WM_MOUSELEAVE.
																	\fn			virtual void BarraScrollEx_Mouse_Saliendo(HWND hWndControl);
																	\param[in]	hWndControl	: HWND del control que contiene el scroll.
																	\return		No devuelve nada.
																	\remarks	Si no se llama a esta funcion cuando se recibe un mensaje WM_MOUSELEAVE, no funcionaran bien los repintados del control.
															*/
		 void												BarraScrollEx_Mouse_Saliendo(HWND hWndControl);

															//! Función virtual destinada a pintar el fondo del scroll.
															/*!	Esta función se encarga de pintar el fondo del scroll.
																	\fn			virtual void BarraScrollEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio, DWL_Enum_BarraScrollEx_TipoScroll TipoScroll);
																	\param[in]	hDC			: HDC del control donde se pintara el scroll.
																	\param[in]	Espacio		: Recta con el espacio del fondo del scroll.
																	\param[in]	TipoScroll	: Tipo de scroll.
																	\return		No devuelve nada.
															*/
		 virtual void										BarraScrollEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio, DWL_Enum_BarraScrollEx_TipoScroll TipoScroll);

															//! Función que debe ser usada cuando el control reciba un mensaje WM_TIMER.
															/*!	Esta función debe ser usada cuando el control reciba un mensaje WM_TIMER.
																	\fn			virtual void BarraScrollEx_Evento_Temporizador(HWND hWndControl, const UINT cID, const bool TieneBorde);
																	\param[in]	hWndControl : HWND de la ventana que contiene el scrollbar.
																	\param[in]	cID			: ID del temporizador.
                                                                    \param[in]  TieneBorde  : Parametro en el que debemos especificar si el control tiene borde.
																	\return		No devuelve nada.
																	\remarks	Si no se llama a esta funcion cuando se recibe un mensaje WM_TIMER, no funcionaran las pulsaciones sobre los fondos y botones del scroll.
															*/
		 void												BarraScrollEx_Evento_Temporizador(HWND hWndControl, const UINT cID, const bool TieneBorde);

															//! Función para calcular los tamaños del scroll vertical.
															/*!	Esta función calcula todos los tamaños de los controles que se usan en el scroll vertical, incluyendo botones extendidos.
																	\fn			void BarraScrollEx_CalcularScrollV(const bool TieneBorde = true);
                                                                    \param[in]  TieneBorde : Parametro en el que debemos especificar si el control tiene borde
																	\return		No devuelve nada.
																	\remarks	Función de uso interno.
															*/
		 void												BarraScrollEx_CalcularScrollV(const bool TieneBorde = true);

															//! Función para calcular los tamaños del scroll horizontal.
															/*!	Esta función calcula todos los tamaños de los controles que se usan en el scroll horizontal, incluyendo botones extendidos.
																	\fn			void BarraScrollEx_CalcularScrollH(const bool TieneBorde = true);
                                                                    \param[in]  TieneBorde : Parametro en el que debemos especificar si el control tiene borde
																	\return		No devuelve nada.
																	\remarks	Función de uso interno.
															*/
		 void												BarraScrollEx_CalcularScrollH(const bool TieneBorde = true);

															//! Función que pinta el borde de varios controles del scroll.
															/*! Esta función pinta el borde de varios controles del scroll.
																	\fn			inline void _BarraScrollEx_EnmarcarRecta(HDC hDC, RECT *Espacio, COLORREF ColorBorde);
																	\param[in]	hDC			: HDC donde se esta pintado el ArbolEx.
																	\param[in]	Espacio		: Recta que contiene el espacio para el borde de la marca.
																	\param[in]	ColorBorde	: Color que se usara para pintar el borde.
																	\return		No devuelve nada.
															*/
		 void						                       _BarraScrollEx_EnmarcarRecta(HDC hDC, RECT *Espacio, COLORREF ColorBorde);

															//! Miembro que determina si las barras de scroll estan activadas.
		 bool                                              _BarraScrollEx_Activado;

															//! Rectangulo del fondo superior
		 RECT								               _BarraScrollEx_RectaFondoSuperiorV;

															//! Rectangulo del fondo inferior
		 RECT								               _BarraScrollEx_RectaFondoInferiorV;

															//! Rectangulo del scroll
		 RECT								               _BarraScrollEx_RectaScrollV;

															//! Rectangulo boton superior
		 RECT								               _BarraScrollEx_RectaBotonSuperiorV;

															//! Rectangulo boton inferior
		 RECT								               _BarraScrollEx_RectaBotonInferiorV;

															//! Valor maximo para el scroll vertical
		 long                                              _BarraScrollEx_MaximoV;

															//! Valor actual para el scroll vertical
		 long                                              _BarraScrollEx_ValorV;

															//! Ultimo valor actual para el scroll vertical
		 long                                              _BarraScrollEx_UValorV;

															//! Valor de la pagina para el scroll vertical
		 long                                              _BarraScrollEx_PaginaV;

															//! Valor que decide si el scroll vertical es visible o no.
															/*! Valor que decide si el scroll vertical es visible o no.
																\fn			BOOL _BarraScrollEx_VisibleV;
																\remarks	Si el valor es -1, es que esta en DWL_BARRASCROLLEX_AUTOMATICO y por ello deberás mirar si el maximo del scroll es mas grande que la pagina. También puedes usar la función BarraScrollEx_VisibleV() que realizara dichas comprobaciones por ti.
															*/
		 BOOL		                                       _BarraScrollEx_VisibleV;

															//! Valor que indica si el control esta capturado
		 bool								               _BarraScrollEx_Capturado;

															//! Posicion actual del scroll vertical
		 long						                       _BarraScrollEx_PosActualV;

															//! Posicion actual del scroll horizontal
		 long							                   _BarraScrollEx_PosActualH;

															//! Rectangulo del fondo superior
		 RECT								               _BarraScrollEx_RectaFondoSuperiorH;

															//! Rectangulo del fondo inferior
		 RECT								               _BarraScrollEx_RectaFondoInferiorH;

															//! Rectangulo del scroll
		 RECT								               _BarraScrollEx_RectaScrollH;

															//! Rectangulo boton superior
		 RECT								               _BarraScrollEx_RectaBotonIzquierdoH;

															//! Rectangulo boton inferior
		 RECT						                       _BarraScrollEx_RectaBotonDerechoH;

															//! Valor maximo para el scroll horizontal
		 long                                              _BarraScrollEx_MaximoH;

															//! Valor actual para el scroll horizontal
		 long                                              _BarraScrollEx_ValorH;

															//! Ultimo valor actual para el scroll horizontal
		 long                                              _BarraScrollEx_UValorH;

															//! Valor de la pagina para el scroll horizontal
		 long						                       _BarraScrollEx_PaginaH;

															//! Valor que decide si el scroll horizontal es visible o no.
															/*! Valor que decide si el scroll horizontal es visible o no.
																\fn			BOOL _BarraScrollEx_VisibleH;
																\remarks	Si el valor es -1, es que esta en DWL_BARRASCROLLEX_AUTOMATICO y por ello deberás mirar si el maximo del scroll es mas grande que la pagina. También puedes usar la función BarraScrollEx_VisibleH() que realizara dichas comprobaciones por ti.
															*/
		 BOOL		                                       _BarraScrollEx_VisibleH;

															//! Punto de partida del mouse al presionarlo
		 POINT				               				   _BarraScrollEx_PosInicio;

															//! Espacio para la barra de scroll vertical
		 RECT								               _BarraScrollEx_EspacioV;

															//! Espacio para la barra de scroll horizontal
		 RECT								               _BarraScrollEx_EspacioH;

															//! Valor que define que parte del scroll vertical esta presionada
		 DWL_Enum_BarraScrollEx_ControlPresionado			   _BarraScrollEx_PresionadoV;

															//! Valor que define que parte del scroll horizontal esta presionada
		 DWL_Enum_BarraScrollEx_ControlPresionado			   _BarraScrollEx_PresionadoH;

															//! Estado del scroll vertical
		 DWL_Enum_BarraScrollEx_Estado				           _BarraScrollEx_EstadoV;

															//! Estado del scroll horizontal
		 DWL_Enum_BarraScrollEx_Estado				           _BarraScrollEx_EstadoH;

															//! Ultimo estado del scroll vertical
		 DWL_Enum_BarraScrollEx_Estado				           _BarraScrollEx_UEstadoV;

															//! Ultimo estado del scroll horizontal
		 DWL_Enum_BarraScrollEx_Estado				           _BarraScrollEx_UEstadoH;

															//! Vector de botones extendidos verticales
		 std::vector <DWLBarraScrollEx_Boton *>	           _BarraScrollEx_BotonesV;

															//! Vector de botones extendidos horizontales
		 std::vector <DWLBarraScrollEx_Boton *>	           _BarraScrollEx_BotonesH;

															//! Variable que contiene los datos que se envian con los mensajes del mouse
		 DWLBarraScrollEx_ParametrosClick			       _BarraScrollEx_ParamsMouse;
		};													//
		////////////////////////////////////////////////////// Fin DWLBarraScrollEx

	}
}

#endif

/*! \file DWLBarraScrollEx.h
\version
  [31/05/2010] <b>0.96</b>\n
  Retocadas las funciones que calculaban las posiciones de los scrolls ya que en algunos casos no se mostraban perfectamente alineados.\n
  Añadidas varias funciones para borrar botones del scroll.\n
  Retocada la funcion para añadir botones al scroll, ahora no sera posible agregar 2 ID's iguales en la misma barra de scroll.\n\n
  [11/11/2009] <b>0.95b</b>\n
  Se ha solucionado un error de posicionamiento del scroll horizontal, que cuando presionabas la parte del fondo derecho, se podia desplazar mas de lo debido.\n
  Se han retocado los calculos para mostrar la barra de scroll horizontal de forma que se muestre bien centrada en el control.\n\n
  [04/11/2009] <b>0.95</b>\n
  Se ha eliminado la clase base DWLBarraScrollEx que funcionaba independientemente de cualquier control, ahora solo existe la clase DWLBarraScrollEx_Nucleo que sera heredada por los controles que requieran barras de scroll.\n\n
  [27/10/2009] <b>0.9c</b>\n
  Cuando se movia el scroll, si situabas el mouse fuera de su area ya no Funciónaba, ahora se captura el mouse de forma general.\n
  Retocadas las configuraciones de colores, ahora usan el nuevo sistema que permite editar solo un color con facilidad.\n\n
  [22/09/2009] <b>0.9b</b>\n
  Se ha retocado el repintado de los botones extras, para que cuando el mouse salga del control, los botones se queden en estado normal.\n\n
  [16/09/2009] <b>0.9</b>\n
  Se han añadido 2 funciones para agregar botones extras al scroll AgregarBotonV() y AgregarBotonH(), tambien se ha creado un evento  para recibir cuando se pulsan : BarraScrollEx_Evento_BotonExtendido_Click().\n
  La función BarraScrollEx_PosicionarScrolls ahora es privada, para que nadie la use desde fuera.\n\n
  [17/06/2009] <b>0.81</b>\n
  Los scrolls horizontales no tenian bien calculadas las posiciones a las que debia moverse. Y por ello al pulsar sobre el boton derecho del scroll_h hacia como si se pulsara en el fondo derecho del scroll, y el fondo derecho del scroll al ser pulsado hcia como si fuera el boton derecho.\n\n
  [08/04/2009] <b>0.8</b>\n
  Se han unificado los mensajes para botones del mouse a 2, MOUSE_PRESIONADO y MOUSE_SOLTADO. Ademas ahora soportan los botones X.\n
  Optimizada la fase de repintado, al mover el scroll pulsando en la parte movil se repintaba mas veces de la cuenta.\n\n
  [17/08/2007] <b>0.7</b>\n
  Se ha añadido el evento Evento_Scroll_CambioPos, para poder controlar cuando se hace un cambio de posición.\n
  Se ha solucionado un pequeño fallo a la hora de asignar valores a los scrolls, ahora se asignan de forma correcta, y no causan problemas al volver a cambiar su posicion.\n\n
  [08/06/2007] <b>0.6</b>\n
  Versión estable.\n\n
  [20/05/2007] <b>0.5</b>\n
  Primera versión de esta clase destinada a contener scrollbars de forma que el mismo control las controle internamente.


*/
