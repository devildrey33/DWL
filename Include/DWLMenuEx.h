/*! \file DWLMenuEx.h
	\brief		Archivo que contiene las declaraciones de las clases del MenuEx.


	\details	La clase DWLMenuEx se ha creado para tener una alternativa a los menus estandar de windows. Entre otras cosas es totalmente configurable en cuanto a la disposicion de colores, y ademas acepta iconos de 16*16 que son mucho mas faciles de encontrar que los iconos de 12*12 que utilizan los menus estandar de windows. 		\n

				Para crear un menu extendido, basta con crear la clase y añadirle los menus que se requieran con la función DWLMenuEx::AgregarMenu() , echa un vistazo al siguiente ejemplo : \n

				<table border = 0 align ='right'><tr><td> \image html MenuEx.jpg </td></tr></table>



 
																																						\n
				\section Clases_Sec Descripción breve de las clases que contiene este archivo :
				 - DWL::ControlesEx::DWLMenuEx_Colores :																								\n
						Clase que enlaza los colores a la configuración del skin por defecto.															\n\n
				 - DWL::ControlesEx::DWLMenuEx :																										\n
						Clase que controla el MenuEx.																								\n\n


	\author		devildrey33
	\date		Creado el [05/12/2004], ultima modificación el [29/12/2006]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)															\n

				\section Clases_Sic Ejemplo de la creación de un menu extendido :

				\code
// Creamos la clase MenuEx
DWL::ControlesEx::DWLMenuEx Menu;
// Asignamos el texto del titulo del MenuEx padre.
Menu.Texto(TEXT("Menu de ejemplo"));
// Agregamos un menu con el nombre 'Menu1'
Menu.AgregarMenu(ID_MENU1, TEXT("Menu1"), IDI_ICON1);
// Agregamos un menu con el nombre 'Menu2' y nos quedamos con la clase MenuEx resultante
DWL::ControlesEx::DWLMenuEx *SubMenu = Menu.AgregarMenu(ID_MENU2, TEXT("Menu2"), IDI_ICON2);
// Partiendo de la clase menuex resultante creamos un submenu dentro con el nombre 'SubMenu1'
SubMenu->AgregarMenu(ID_SUBMENU1, TEXT("SubMenu1"), IDI_ICON3);
// Creamos un submenu dentro del 'Menu2' con el nombre 'SubMenu2'
SubMenu->AgregarMenu(ID_SUBMENU2, TEXT("SubMenu2"), NULL);
				\endcode
*/
#ifndef DWL_MENUEX_H
#define DWL_MENUEX_H

// #define DWL_CLASEMENUEX_DEBUG // Descomenta esta linea para que se muestren mensajes de debug para este control

#include "DWLControlEx.h"
#include "DWLString.h"
#include ".\DWLMenuEx\DWLMenuEx_Estilos.h"


//! Enumeración para el tipo de menú
enum DWL_Enum_MenuEx_Tipo {
	DWL_Enum_MenuEx_Normal				= 0,
	DWL_Enum_MenuEx_Separador			= 1
};

//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres ControlesEx
	namespace ControlesEx {
        //! Clase que simula un popupmenu con transparencias y colores configurables
        class DWLMenuEx : public DWL::ControlesEx::Base::DWLControlEx {
		 public: ///////////////////////// Miembros publicos

										//! Constructor.
										/*!	Constructor por defecto.
												\fn		DWLMenuEx(void);
												\return	No devuelve nada.
										*/
										DWLMenuEx(void);

										//! Destructor.
										/*!	Destructor.
												\fn		~DWLMenuEx(void);
												\return	No devuelve nada.
										*/
									   ~DWLMenuEx(void);

                                        //! Función que agrega un menu hijo a este menú.
										/*!	Función para agregar un menu hijo a este menú.
												\fn		    DWLMenuEx *AgregarMenu(const UINT IDM, const TCHAR *Txt, const UINT IconoRecursos = NULL, const int Posicion = -1, const bool WM_SysCommand = false, const bool nActivado = true);;
                                                \param[in]  IDM           : ID para el nuevo menú.
                                                \param[in]  Txt           : Texto para el nuevo menú.
                                                \param[in]  IconoRecursos : Icono de los recursos que usara el nuevo menú.
                                                \param[in]  Posicion      : Posicion para el nuevo menú. -1 para que se ponga al final.
                                                \param[in]  WM_SysCommand : true para mandar la notificacion con el mensaje WM_SYSCOMMAND, de esta forma podemos simular menús del sistema.
                                                \param[in]  nActivado     : Valor que determina si el menú estara activado.
												\return	    Devuelve la clase DWLMenuEx creada.
                                                \Remarks    Si asignamos WM_SysCommand a true para simular por ejemplo el menu Cerrar de una ventana,
                                                            en la ID de nuestro menú habra que especificar la id SC_CLOSE que corresponde al menú cerrar de cualquier ventana estandar.
												\sa			AgregarSeparador()
										*/
          DWLMenuEx                    *AgregarMenu(const UINT IDM, const TCHAR *Txt, const UINT IconoRecursos = NULL, const int Posicion = -1, const bool WM_SysCommand = false, const bool nActivado = true);

                                        //! Función que agrega un separador a este menú.
										/*!	Función para agregar un separador a este menú.
												\fn		    DWLMenuEx *AgregarSeparador(const int Posicion = -1);
                                                \param[in]  Posicion : Posicion para el nuevo menú. -1 para situar el separador al final.
												\return	    No devuelve nada.
                                                \Remarks    Los separadores no tienen ID, y cuando el usuario presiona encima la ventana destino no recibe notificaciones.
												\sa			AgregarMenu()
										*/
		  void                          AgregarSeparador(const int Posicion = -1);

                                        //! Función para mostrar este menu.
										/*!	Función para agregar un separador a este menú.
												\fn		    const int MostrarMenuEx(HWND hWndDest, const bool Esperar = true, const bool DesactivarBlend = false);
                                                \param[in]  hWndDest        : HWND de la ventana que recibira los mensajes de este menú.
                                                \param[in]  Esperar         : Si se asigna true, esta función no retornara hasta que se cierre el menú (false por defecto).
                                                \param[in]  DesactivarBlend : Desactivar las transparencias del menú (false por defecto).
												\return	    Si asignamos Esperar a true retorna la ID del menu presionado, en caso contrario puede retornar cualquier cosa.
                                                \Remarks    No es aconsejable usar el parametro Esperar a true en aplicaciones grandes, ya que situa un bucle de mensajes en medio que puede que no nos venga del todo bien.
                                                            Este parametro se diseño de cara a aplicaciones senzillas para poder crear un menú y recibir sus mensajes con mas facilidad.
										*/
		  int                           MostrarMenuEx(HWND hWndDest, const bool Esperar = true, const bool DesactivarBlend = false);

										//! Función que retorna el total de submenus que contiene este menú.
										/*! Esta funcion retorna el total de submenus que contiene este menú.
												\fn			inline const UINT TotalMenus(void);
												\return		Devuelve el total de menus.
										*/
		  inline UINT                   TotalMenus(void) const {
											return static_cast<UINT>(_Items.size());
										};

										//! Función que retorna texto de este menú.
										/*! Esta funcion retorna texto de este menú.
												\fn			inline const TCHAR *Texto(void);
												\return		Devuelve el texto de este menú.
										*/
		  inline const TCHAR           *Texto(void) {
											return _Texto();
										};

										//! Función que asigna texto de este menú.
										/*! Esta funcion asigna texto de este menú.
												\fn			inline void Texto(const TCHAR *Txt);
                                                \param[in]  Txt : Nuevo texto para el menú.
												\return		No devuelve nada.
										*/
		  inline void					Texto(const TCHAR *Txt) {
											_Texto = Txt;
										};

										//! Función que retorna el submenu indicado por la posición.
										/*! Esta funcion retorna el submenu indicado por la posición.
												\fn			inline DWLMenuEx *Menu(const UINT Pos);
                                                \param[in]  Pos : Posicion del submenu que queremos obtener.
												\return		Devuelve una clase DWLMenuEx con el submenu indicado en la posición.
										*/
		  inline DWLMenuEx             *Menu(const UINT Pos) {
											return _Items[Pos];
										};

										//! Función que retorna el siguiente menú a este.
										/*! Esta funcion retorna el siguiente menú a este.
												\fn			inline DWLMenuEx *Siguiente(void);
												\return		Devuelve una clase DWLMenuEx con el siguiente menú. Devuelve NULL si no existe un menú siguiente.
										*/
		  inline DWLMenuEx	           *Siguiente(void) {
											return _Next;
										};

										//! Función que retorna el anterior menú a este.
										/*! Esta funcion retorna el anterior menú a este.
												\fn			inline DWLMenuEx *Anterior(void);
												\return		Devuelve una clase DWLMenuEx con el anterior menú. Devuelve NULL si no existe un menú anterior.
										*/
		  inline DWLMenuEx	           *Anterior(void) {
											return _Prev;
										};

										//! Función que retorna el menú padre de este.
										/*! Esta funcion retorna el menú padre de este.
												\fn			inline DWLMenuEx *Padre(void);
												\return		Devuelve una clase DWLMenuEx con menú padre. Devuelve NULL si no existe un menú padre.
										*/
		  inline DWLMenuEx             *Padre(void) {
											return _Parent;
										};

										//! Función que retorna el icono de este menú.
										/*! Esta funcion retorna el icono de este menú.
												\fn			inline UINT Icono(void) const;
												\return		Devuelve la ID del icono para este menú.
                                                \remarks    El icono debe estar añadido en los recursos de la aplicación.
										*/
		  inline UINT                   Icono(void) const {
											return _Iko;
										};

										//! Función que asigna el icono de este menú.
										/*! Esta funcion asigna el icono de este menú.
												\fn			inline void Icono(const UINT nIcono);
                                                \param[in]  nIcono : ID del nuevo icono para el menú.
												\return		No devuelve nada.
                                                \remarks    El icono debe estar añadido en los recursos de la aplicación.
										*/
		  inline void                   Icono(const UINT nIcono) {
											_Iko = nIcono;
										};

										//! Función que activa / descativa este menú.
										/*! Esta funcion activa / descativa este menú.
												\fn			inline void Activado(const bool Activar);
                                                \param[in]  Activar : true para activar el menú, false para desactivarlo.
												\return		No devuelve nada.
										*/
		  inline void                   Activado(const bool Activar) {
											_Enabled = Activar;
										};

										//! Función que retorna si el menu esta activado o desactivado.
										/*! Esta funcion retorna si el menu esta activado o desactivado.
												\fn			inline BOOL Activado(void);
												\return		Devuelve TRUE si el menú esta activado, FALSE si esta desactivado.
										*/
		  inline BOOL                   Activado(void) {
											return static_cast<BOOL>(_Enabled);
										};

										//! Función que busca la ID de un menu y retorna la clase DWLMenuEx asociada a el.
										/*! Esta funcion busca la ID de un menu y retorna la clase DWLMenuEx asociada a el.
												\fn			DWLMenuEx *BuscarID(const int bID);
                                                \param[in]  bID : ID del menú que se quiere buscar.
												\return		Devuelve la clase DWLMenuEx con la ID especificada, o NULL si no existe esa ID.
                                                \remarks    Esta función busca la ID a partir de sus submenus, y no encontrara ids de menus que no esten dentro de el.
										*/
		  DWLMenuEx                    *BuscarID(const int bID);

										//! Función que borra el menú especificado en la posición.
										/*! Esta funcion borra el menú especificado en la posición.
												\fn			void BorrarMenu(const UINT Pos);
                                                \param[in]  Pos : Posición del menú a borrar.
												\return		No devuelve nada
										*/
		  void                          BorrarMenu(const UINT Pos);

										//! Función que borra todos los submenus.
										/*! Esta funcion borra todos los submenus.
												\fn			void BorrarTodo(void);
												\return		No devuelve nada
										*/
		  void                          BorrarTodo(void);

										//! Función que oculta todos los menus.
										/*! Esta funcion oculta todos los menus.
												\fn			void OcultarTodo(void);
												\return		No devuelve nada
										*/
		  void                          OcultarTodo(void);

										//! Operador que retorna la clase DWLMenuEx especificada el la posición.
										/*! Este operador retorna la clase DWLMenuEx especificada el la posición.
												\fn			inline DWLMenuEx *operator[] (const UINT Pos);
												\return		No devuelve nada
										*/
		  inline DWLMenuEx   		   *operator[] (const UINT Pos) {
											return _Items[Pos];
										};

										//! Función que retorna el identificador de este menú.
										/*! Esta funcion retorna el identificador de este menú.
												\fn			inline UINT IDMenu(void) const;
												\return		Devuelve la ID de este menú.
										*/
		  inline UINT			    	IDMenu(void) const {
											return _ID;
										};

		  DWLMenuEx_Estilos             Estilos;

		 protected :////////////////////// Miembros protegidos

                                        //! Función virtual que se invoca al terminar de pintar toda la ventana.
										/*! Esta funcion virtual es invocada al terminar de pintar todo la ventana.
												\fn			inline virtual LRESULT Evento_Pintar_Finalizado(HDC hDC);
                                                \param[in]  hDC : HDC en el que podemos pintar mas cosas.
												\return		Si re-emplazas esta función debes retornar 0.
										*/
		  inline virtual LRESULT        Evento_Pintar_Finalizado(HDC hDC) {
                                            return 0;
										};

                                        //! Función virtual que se invoca al terminar de pintar el menú.
										/*! Esta funcion virtual es invocada al terminar de pintar el menú.
												\fn			inline virtual LRESULT Evento_PintarMenu_Finalizado(HDC hDC,const int pID, RECT *Espacio);
                                                \param[in]  hDC     : HDC en el que podemos pintar mas cosas.
                                                \param[in]  pID     : ID del menú que se ha pintado.
                                                \param[in]  Espacio : Recta que contiene el espacio del menú.
												\return		Si re-emplazas esta función debes retornar 0.
										*/
		  inline virtual LRESULT        Evento_PintarMenu_Finalizado(HDC hDC, const int pID, RECT *Espacio) {
                                            return 0;
										};

										//! Función predefinida del mensaje WM_*BUTTONDOWN (Virtual)
										/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONDOWN.
												\fn			virtual LRESULT Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param)
												\param[in]	Boton	: Boton presionado.
												\param[in]	cX		: Coordenada X del mouse.
												\param[in]	cY		: Coordenada Y del mouse.
												\param[in]	wParam	: Teclas extendidas presionadas.
										        \return		Si re-emplazas esta funcion debes retornar 0.
										*/
		  LRESULT                       Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Params);

										//! Función predefinida del mensaje WM_*BUTTONUP (Virtual)
										/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONUP.
												\fn			virtual LRESULT Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
												\param[in]	Boton	: Boton presionado.
												\param[in]	cX		: Coordenada X del mouse.
												\param[in]	cY		: Coordenada Y del mouse.
												\param[in]	Param	: Teclas extendidas presionadas.
										        \return		Si re-emplazas esta funcion debes retornar 0.
										*/
		  LRESULT                       Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Params);

										//! Función predefinida del mensaje WM_MOUSEMOVE.
										/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEMOVE.
												\fn			virtual LRESULT Evento_Mouse_Movimiento(const int cX, const int cY, const UINT wParam);
												\param[in]	cX		: Coordenada X del mouse.
												\param[in]	cY		: Coordenada Y del mouse.
												\param[in]	Param	: Teclas extendidas presionadas.
										        \return		Si re-emplazas esta funcion debes retornar 0.
										*/
		  LRESULT                       Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Params);

										//! Función predefinida del mensaje WM_KEYDOWN (Virtual)
										/*!	Esta función es la encargada de procesar los mensajes WM_KEYDOWN.
												\fn			virtual LRESULT Evento_Teclado_TeclaPresionada(const UINT Tecla, const UINT Repeticion, const UINT Param);
												\param[in]	Caracter   : Tecla virtual soltada.
												\param[in]	Repeticion : Repeticiones de la tecla
												\param[in]	Params	   : Teclas extendidas soltadas.
										        \return		Si re-emplazas esta funcion debes retornar 0.
										*/
		  LRESULT                       Evento_Teclado_TeclaPresionada(const UINT Tecla, const UINT Repeticion, const UINT Param);

										//! Función predefinida del mensaje WM_KEYUP (Virtual)
										/*!	Esta función es la encargada de procesar los mensajes WM_KEYUP.
												\fn			virtual LRESULT Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Param);
												\param[in]	Caracter   : Tecla virtual soltada.
												\param[in]	Repeticion : Repeticiones de la tecla
												\param[in]	Param	   : Teclas extendidas soltadas.
										        \return		Si re-emplazas esta funcion debes retornar 0.
										*/
		  LRESULT                       Evento_Teclado_TeclaSoltada(const UINT Tecla, const UINT Repeticion, const UINT Params) {
                                            return 0;
                                        };

										//! Función que pinta todo el MenuEx cuado se recibe un mensaje WM_PAINT.
										/*!	Esta función pinta el MenuEx cuando se recibe un mensaje WM_PAINT.
												\fn			LRESULT Evento_Pintar(HDC hDC);
												\param[in]	hDC	: hDC donde se pintara todo el MenuEx.
										        \return		Si re-emplazas esta funcion debes retornar 0.
										*/
		  LRESULT                       Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);

                                        //! Función interna para mostrar los submenus.
										/*!	Esta función se usa internamente para mostrar los submenus.
												\fn			void _Mostrar(HWND hWndDest, const int cX, const int cY, const int NAncho, const int NAlto, const bool DesactivarBlend);
												\param[in]	hWndDest	    : HWND del menú padre.
												\param[in]	cX	            : Coordenada X del menú.
												\param[in]	cY	            : Coordenada Y del menú.
												\param[in]	NAncho	        : Ancho del menú.
												\param[in]	NAlto	        : Alto del menú.
												\param[in]	DesactivarBlend	: Desactivar transparencias del menú.
										        \return		No devuelve nada.
										*/
		  void                         _Mostrar(HWND hWndDest, const int cX, const int cY, const int NAncho, const int NAlto, const bool DesactivarBlend);

										//! Función que oculta este menú.
										/*! Esta funcion oculta este menú.
												\fn			void Ocultar(void);
												\return		No devuelve nada
										*/
		  void                          Ocultar(void);

                                        //! Función para mostrar el submenu especificado en la posición.
										/*!	Esta función se usa para mostrar el submenu especificado en la posición.
												\fn			DWLMenuEx *MostrarSubMenu(HWND hWndDest, const int Pos);
												\param[in]	hWndDest : HWND del menú padre.
												\param[in]	Pos      : Posición del menú.
										        \return		Devuelve la clase DWLMenuEx especificada en la posición.
										*/
		  DWLMenuEx                    *MostrarSubMenu(HWND hWndDest, const int Pos);

										//! Función que borra los objetos GDI creados para mostrar los menus.
										/*! Esta funcion borra los objetos GDI creados para mostrar los menus.
												\fn			void BorrarFondoDC(void);
												\return		No devuelve nada
										*/
		  void                          BorrarFondoDC(void);

										//! Función para calcular el tamaño de los menus.
										/*! Esta función calcula el tamaño de los menus.
												\fn			POINT CalcularMedidas(void);
												\return		Devuelve la estructura POINT con el ancho y el alto necesarios para el menú.
										*/
		  POINT			                CalcularMedidas(void);

										//! Función que pinta todos los items del menú.
										/*! Esta función pinta todos los items del menú.
												\fn			POINT PintarItems(void);
												\return		No devuelve nada.
										*/
		  void                          PintarItems(void);

										//! Función para pintar un Item especifico del menú.
										/*! Esta función pinta un Item especifico del menú.
												\fn			void PintarItem(HDC hDC, const int NItem, const int Estado = 0);
                                                \param[in]  hDC    : HDC donde se pintara el item / menú.
                                                \param[in]  NItem  : Posicion del item / menú.
                                                \param[in]  Estado : Estado del item / menú.
												\return		No devuelve nada.
										*/
		  void                          PintarItem(HDC hDC, const int NItem, const int Estado = 0);

										//! Función para pintar el borde de selección del menú.
										/*! Esta función pinta el borde de selección del menú.
												\fn			void PintarSeleccion(HDC hDC, const int NItem);
                                                \param[in]  hDC    : HDC donde se pintara el borde.
                                                \param[in]  NItem  : Posicion del item / menú.
												\return		No devuelve nada.
										*/
		  void                          PintarSeleccion(HDC hDC, const int NItem);

                                        //! Función que retorna la ID del MenuEx.
                                        /*!	Esta funcion devuelve la ID del MenuEx
                                                \fn			inline UINT ID(void);
                                                \return		Devuelve la ID del MenuEx.
                                        */
         inline UINT                    ID(void) { return _ID; };

									    //! Esqueleto para los mensajes del MenuEx.
									    /*! Esta función es el esqueleto para los mensajes del MenuEx.
											    \fn			LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
											    \param[in]	uMsg	: Mensaje.
											    \param[in]	wParam	: Parametro1.
											    \param[in]	lParam	: Parametro2.
											    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
											    \remarks	Esta función es el esqueleto del MenuEx por donde pasaran todos sus mensajes.
									    */
		  LRESULT CALLBACK              GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
		////////////////////////////////// Variables

										//! Icono del menu
		  UINT                         _Iko;

										//! Posicion del menu
		  int                          _Pos;

										//! El menu esta presionado
		  int                          _Presionado;

										//! Estado del menu
		  int                          _Estado;

										//! Padre del menu
		  DWLMenuEx                   *_Parent;

										//! Menu siguiente
		  DWLMenuEx                   *_Next;

										//! Menu anterior
		  DWLMenuEx                   *_Prev;

										//! Ultimo menu
		  DWLMenuEx                   *_UMenu;

										//! Submenus
		  std::vector<DWLMenuEx *>     _Items;

										//! Texto del menu
		  DWL::DWLString               _Texto;

										//! Item selecionado del submenu
		  int                          _ItemSeleccionado;

										//! Destino de los mensajes WM_COMMAND
		  static HWND                  _hWndDestMsg;

										//! Tipo de menu
		  DWL_Enum_MenuEx_Tipo         _Tipo;

										//! El menu esta activado
		  bool                         _Enabled;

						  				//! ID que retorna el menu
		  int                          _IDFinal;

										//! Valor para saber si hay que mandar un WM_COMMAND o un WM_SYSCOMMAND
		  bool                         _WM_SysCommand;

										//! Valor para saber si hay que desactivar el Alpha Blend
		  bool                         _DesactivarBlend;
/*		  //////////////////////////////// Variables que requiere la Barra

										//! Minimo de la barra
		  int						   _Minimo;

										//! Maximo de la barra
		  int						   _Maximo;

										//! Valor actual de la barra
		  int						   _Valor;*/
		  //////////////////////////////// Objetos GDI que permaneceran en memoria mientras el menu este mostrado

										//! BackBuffer DC
		  HDC                          _hDC;

										//! Bitmap del BackBuffer
		  HBITMAP                      _MapaBits;

										//! Bitmap viejo del BackBuffer
		  HBITMAP                      _VMapaBits;

                                        //! ID del menú extendido
		  UINT                         _ID;

           private : ///////////////////// Miembros privados
                                        // Constructor copia des-habilitado
                                        DWLMenuEx(const DWLMenuEx &) : DWLControlEx(), _Iko(0), _Pos(0), _Presionado(-1), _Estado(-1), _Parent(NULL),
                                                                       _Next(NULL), _Prev(NULL), _UMenu(NULL), _Items(), _Texto(), _ItemSeleccionado(-1),
                                                                       _Tipo(DWL_Enum_MenuEx_Normal), _Enabled(true), _IDFinal(-1), _WM_SysCommand(false),
                                                                       _DesactivarBlend(false), _hDC(NULL), _MapaBits(NULL), _VMapaBits(NULL), _ID(0) { };
                                        // Operador = des-habilitado
		  inline DWLMenuEx             &operator=(const DWLMenuEx &) { return *this; };

#if COMPILADOR != COMPILADOR_MINGW
										//! Esta clase es amiga de ella misma
		  friend class                  DWLMenuEx;
#endif
		};								//
		////////////////////////////////// Final DWLMenuEx

	};
};

#endif


/*! \file DWLMenuEx.h
\version

- [24/10/2009] <b>0.95</b>  \n
  Se ha cambiado la clase que contenia el string internamente, antes se usaba la std::string, ahora se usa la DWL::DWLString \n
  Con este cambio esta clase queda habilitada para funcionar bajo VisualC6++ con UNICODE \n

- [12/04/2009] <b>0.82</b>  \n
  Se ha retocado la función que recibe los clicks del mouse para que no mande mensajes si el item pulsado esta desactivado. \n

- [29/12/2006] <b>0.81</b>  \n
  Se ha solucionado un problema con multiples pantallas, el menu solo salia en la pantalla principal. \n
  Se ha optimizado aun mas el proceso de pintado. \n

- [07/09/2005] <b>0.80</b>  \n
  Se han reemplazado varios nombres de funciónes en ingles por castellano. \n
  Se han añadido 2 nuevos eventos (Evento_Pintar_Finalizado, y Evento_PintarMenu_Finalizado) los cuales nos permiten pintar algo mas encima del menu.  \n
  Ahora es posible cambiar el texto del menu padre utilizando la función DWLMenuEx::Texto() en la clase padre.\n
  Se han añadido varios eventos con sus correspondientes macros. \n

- [05/12/2004] <b>0.71</b>  \n
  En las funciones de mostrar se retorna la ID del menu pulsado si no se indica Esperar = false, en ese caso retornara -1 \n
  La función para agregar menus consta haora de un nuevo parametro (WM_SysCommand = false) si esta a falso enviara un WM_COMMAND de ese item, si esta true enviara un WM_SYSCOMMAND \n
  Las funciónes de mostrar tenian un bug si se especificaba false al esperar el cual no mostraba el menu... \n
  Los Items desactivados tenian un bug, el cual seguia usando el item como si fuera normal (es decir cuando presionabas el item desactivado funcionaba como si no lo estubiera, mandando el mensaje a su ventana padre) \n
  Cuando presionas fuera del menu este mensaje no era percibido por la ventana que esta inmediatamente abajo, ahora si que lo recibe (basicamente el Evento_Mouse_BotonPresionado) \n
  Se ha modificado el codigo para que quede mas bonito de ver y facil de reprogramar... \n
  Añadida opcion para desactivar los AlphaBlend y substituirlos por un BitBlt. \n

*/
