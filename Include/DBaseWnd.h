#ifndef DBASEWND_H
#define DBASEWND_H

#include "DObjeto.h"
#include "DMensajesWnd.h"

#include <commctrl.h>

#pragma comment(lib, "UxTheme.lib")		// Libreria para los temas extendidos de windows (a partir de windows XP)
#include <Uxtheme.h>

// Estilo visual XP+
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#ifndef GET_X_LPARAM
//! Macro para obtener la coordenada X de un LPARAM
#define GET_X_LPARAM(lp)			((int)(short)LOWORD(lp))
#endif

#ifndef GET_Y_LPARAM
//! Macro para obtener la coordenada Y de un LPARAM 
#define GET_Y_LPARAM(lp)			((int)(short)HIWORD(lp))
#endif

//! Espacio de nombres DWL
namespace DWL {

/*	// Tipos de clase BaseWnd
	enum DEnum_TipoBaseWnd {
		DEnum_TipoBaseWnd_Indefinido,
		// Ventanas / Dialogos
		DEnum_TipoBaseWnd_Ventana,
		DEnum_TipoBaseWnd_Dialogo,
		DEnum_TipoBaseWnd_DialogoModal,
		// Controles de windows
		DEnum_TipoBaseWnd_Button,
		DEnum_TipoBaseWnd_ComboBox,
		DEnum_TipoBaseWnd_EditBox,
		DEnum_TipoBaseWnd_ListView,
		DEnum_TipoBaseWnd_TreeView,
		DEnum_TipoBaseWnd_TreeViewDirectorios
	};*/


	//! Clase super base para cualquier ventana y control
	class DBaseWnd  {
	  public: //////////////////////////////////// Miembros publicos
		  virtual const DEnum_Objeto			Objeto_Tipo(void) { return DEnum_Objeto_BaseWnd; };

												//! Constructor.
												/*! Constructor.
														\fn			DBaseWnd(void);
														\return		No devuelve nada.
												*/
												DBaseWnd(void) : _hWnd(0) { };

												//! Función para mostrar / ocultar la ventana / control.
												/*! Esta función muestra / oculta la ventana / control.
														\fn			virtual void Visible(const bool nMostrar);
														\param[in]	nMostrar : True para mostrar la ventana / control, false para ocultarlo.
														\return		No devuelve nada.
												*/
		virtual void					        Visible(const bool nMostrar);

												//! Función que retorna si la ventana / control es visible.
												/*!	Esta funcion devuelve si la ventana / control es visible.
														\fn			const bool Visible(void);
														\return		Devuelve TRUE si la ventana / control es visible, FALSE en caso contrario.
												*/
		const bool				        	    Visible(void);

												//! Función para activar / desactivar la ventana / control.
												/*!	Esta función activa / desactiva la ventana / control.
														\fn			void Activado(const bool nActivar);
														\param[in]	nActivar	: Parametro en el que especificaremos si queremos activar o desactivar la ventana / control.
														\return		No devuelve nada.
												*/
		virtual void					        Activado(const bool nActivar);

												//! Función que retorna si la ventana / control esta activado.
												/*!	Esta funcion devuelve si la ventana / control esta activado.
														\fn			virtual const bool Activado(void);
														\return		Devuelve TRUE si la ventana / control esta activado, FALSE en caso contrario.
												*/
		virtual const bool 						Activado(void);

												//! Función que asigna el foco a esta ventana / control.
												/*!	Esta funcion asigna el foco a esta ventana / control.
														\fn			virtual void AsignarFoco(void);
														\return		No devuelve nada.
												*/
		virtual void					        AsignarFoco(void);

												//! Función que retorna si esta ventana /control tiene el foco del teclado.
												/*!	Esta funcion devuelve si esta ventana /control tiene el foco del teclado.
														\fn			virtual bool TieneFoco(void);
														\return		Devuelve true si esta ventana tiene el foco del teclado, false en caso contrario.
												*/
		virtual bool					    	TieneFoco(void);

												//! Función que retorna si esta ventana /control tiene el mouse encima.
												/*!	Esta funcion devuelve si esta ventana /control tiene el mouse encima.
														\fn			virtual bool MouseEncima(void);
														\return		Devuelve true si esta ventana tiene el cursor del raton encima, false en caso contrario.
												*/
		virtual bool                            MouseEncima(void);

												//! Función que asigna una region a esta ventana / control.
												/*!	Esta funcion asigna una region a esta ventana / control.
														\fn			virtual int AsignarRegion(HRGN nRegion, const BOOL nRepintar = true);
														\param[in]	nRegion		: Region que queremos asignar a esta ventana / control.
														\param[in]	nRepintar	: Valor en el que especificamos si se debe repintar la ventana / control.
														\return		Devuelve 0 si la funcion ha fallado, cualquier otro numero para advertir que se ha asignado la region correctamente.
												*/
		virtual int							    AsignarRegion(HRGN nRegion, const BOOL nRepintar = true);

												//! Función que retorna el identificador de ventana HWND.
												/*!	Esta funcion devuelve el identificador de ventana HWND.
														\fn			HWND hWnd(void);
														\return		Devuelve el HWND para esta ventana / control.
												*/
		HWND							        hWnd(void);

												//! Función para mover la ventana / control a la posicion y el tamaño especificados.
												/*!	Esta función mueve la ventana / control a la posicion y tamaño especificados.
														\fn			virtual void Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = true);
														\param[in]	cX			: Nueva posicion X para la ventana / control.
														\param[in]	cY			: Nueva posicion Y para la ventana / control.
														\param[in]	cAncho		: Nuevo ancho para la ventana / control.
														\param[in]	cAlto		: Nueva altura para la ventana / control.
														\param[in]	cRepintar	: True para repintar la ventana / control, false para dejarlo sin repintar.
														\return		No devuelve nada.
												*/
		virtual void							Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = false);

												//! Función para crear un temporizador en esta ventana / control.
												/*!	Esta función crea un temporizador en esta ventana / control.
														\fn			void CrearTemporizador(const UINT nID, const UINT nMiliSegundos);
														\param[in]	nID				: ID para el temporizador.
														\param[in]	nMiliSegundos	: Tiempo en milisegundos que pasara hasta que salte el temporizador.
														\return		No devuelve nada.
														\remarks	Para obtener cuando salta un temporizador debemos usaar la funcion Evento_Temporizador()
												*/
		void					        		CrearTemporizador(const UINT nID, const UINT nMiliSegundos);

												//! Función para eliminar un temporizador en esta ventana / control.
												/*!	Esta función elimina un temporizador en esta ventana / control.
														\fn			void EliminarTemporizador(const UINT nID);
														\param[in]	nID				: ID del temporizador a eliminar.
														\return		No devuelve nada.
												*/
		void				        			EliminarTemporizador(const UINT nID);

												//! Función que destruye esta ventana / control.
												/*!	Esta funcion destruye esta ventana / control.
														\fn			virtual BOOL Destruir(void);
														\return		Devuelve TRUE si la operación se completo, FALSE en caso contrario.
												*/
		virtual BOOL						    Destruir(void);

												//! Función que asigna la opacidad para la ventana / control.
												/*!	Esta funcion asigna la opacidad para la ventana / control.
														\fn			void Opacidad(const BYTE nNivel);
														\param[in]	nNivel : Nivel de opacidad (0-255)
														\return		No devuelve nada.
														\remarks	Función no soportada en VC6.
												*/
		void	        						Opacidad(const BYTE nNivel);

												//! Función que retorna la ID esta ventana / control.
												/*!	Esta funcion devuelve la ID de esta ventana / control.
														\fn			const int ID(void);
														\return		Devuelve la ID de esta ventana / control.
												*/
		virtual UINT					        ID(void);



//		static DBaseWnd                        *ObtenerBaseWnd(HWND nhWnd);
//		virtual const DEnum_TipoBaseWnd        TipoBaseWnd(void)   { return DEnum_TipoBaseWnd_Indefinido; };

//		static DBaseWnd *hWnd_a_BaseWnd(HWND hWnd);

	protected: ////////////////////////////// Miembros protegidos

//		void                                  _AgregarAppBaseWnd(const UINT nID, DBaseWnd *nPadre);

												//! Función que registra la clase ventana.
												/*!	Esta funcion registra la clase ventana.
														\fn			ATOM _RegistrarClase(const TCHAR *nNombre, HBRUSH nColorFondo, const int nIconoRecursos, WNDPROC WindowProcedureInicial);
														\param[in]	nNombre					: Nombre para la clase ventana.
														\param[in]  WindowProcedureInicial	: WindowProcedure estatico que enlazara con el GestorMensajes virtual
														\param[in]	nIconoRecursos			: ID del icono de los recursos que se asignara a la ventana. Puede ser 32512 para que se asigne el icono de la aplicación.
														\param[in]	nColorFondo				: Brocha con el color del fondo de la ventana. Puede ser NULL.
														\return		Devuelve el ATOM creado con RegisterClassEx, NULL en caso de error.
												*/
		ATOM                                   _RegistrarClase(const TCHAR *nNombre, WNDPROC WindowProcedureInicial, const int nIconoRecursos = 0, HBRUSH nColorFondo = 0);

												//! Identificador para la ventana / control.
		HWND				                   _hWnd;
	};
	//////////////////////////////////////////////


};

#endif