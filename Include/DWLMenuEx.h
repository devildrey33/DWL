/*! \file DWLMenuEx.h
	\brief		Archivo que contiene las declaraciones de las clases del MenuEx.


	\details	La clase DWLMenuEx se ha creado para tener una alternativa a los menus estandar de windows. Entre otras cosas es totalmente configurable en cuanto a la disposicion de colores, y ademas acepta iconos de 16*16 que son mucho mas faciles de encontrar que los iconos de 12*12 que utilizan los menus estandar de windows. 		\n

				Para crear un menu extendido, basta con crear la clase y a�adirle los menus que se requieran con la funci�n DWLMenuEx::AgregarMenu() , echa un vistazo al siguiente ejemplo : \n

				<table border = 0 align ='right'><tr><td> \image html MenuEx.jpg </td></tr></table>



 
																																						\n
				\section Clases_Sec Descripci�n breve de las clases que contiene este archivo :
				 - DWL::ControlesEx::DWLMenuEx_Colores :																								\n
						Clase que enlaza los colores a la configuraci�n del skin por defecto.															\n\n
				 - DWL::ControlesEx::DWLMenuEx :																										\n
						Clase que controla el MenuEx.																								\n\n


	\author		devildrey33
	\date		Creado el [05/12/2004], ultima modificaci�n el [29/12/2006]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas informaci�n consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catal�, traduccion no oficial)															\n

				\section Clases_Sic Ejemplo de la creaci�n de un menu extendido :

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


//! Enumeraci�n para el tipo de men�
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

                                        //! Funci�n que agrega un menu hijo a este men�.
										/*!	Funci�n para agregar un menu hijo a este men�.
												\fn		    DWLMenuEx *AgregarMenu(const UINT IDM, const TCHAR *Txt, const UINT IconoRecursos = NULL, const int Posicion = -1, const bool WM_SysCommand = false, const bool nActivado = true);;
                                                \param[in]  IDM           : ID para el nuevo men�.
                                                \param[in]  Txt           : Texto para el nuevo men�.
                                                \param[in]  IconoRecursos : Icono de los recursos que usara el nuevo men�.
                                                \param[in]  Posicion      : Posicion para el nuevo men�. -1 para que se ponga al final.
                                                \param[in]  WM_SysCommand : true para mandar la notificacion con el mensaje WM_SYSCOMMAND, de esta forma podemos simular men�s del sistema.
                                                \param[in]  nActivado     : Valor que determina si el men� estara activado.
												\return	    Devuelve la clase DWLMenuEx creada.
                                                \Remarks    Si asignamos WM_SysCommand a true para simular por ejemplo el menu Cerrar de una ventana,
                                                            en la ID de nuestro men� habra que especificar la id SC_CLOSE que corresponde al men� cerrar de cualquier ventana estandar.
												\sa			AgregarSeparador()
										*/
          DWLMenuEx                    *AgregarMenu(const UINT IDM, const TCHAR *Txt, const UINT IconoRecursos = NULL, const int Posicion = -1, const bool WM_SysCommand = false, const bool nActivado = true);

                                        //! Funci�n que agrega un separador a este men�.
										/*!	Funci�n para agregar un separador a este men�.
												\fn		    DWLMenuEx *AgregarSeparador(const int Posicion = -1);
                                                \param[in]  Posicion : Posicion para el nuevo men�. -1 para situar el separador al final.
												\return	    No devuelve nada.
                                                \Remarks    Los separadores no tienen ID, y cuando el usuario presiona encima la ventana destino no recibe notificaciones.
												\sa			AgregarMenu()
										*/
		  void                          AgregarSeparador(const int Posicion = -1);

                                        //! Funci�n para mostrar este menu.
										/*!	Funci�n para agregar un separador a este men�.
												\fn		    const int MostrarMenuEx(HWND hWndDest, const bool Esperar = true, const bool DesactivarBlend = false);
                                                \param[in]  hWndDest        : HWND de la ventana que recibira los mensajes de este men�.
                                                \param[in]  Esperar         : Si se asigna true, esta funci�n no retornara hasta que se cierre el men� (false por defecto).
                                                \param[in]  DesactivarBlend : Desactivar las transparencias del men� (false por defecto).
												\return	    Si asignamos Esperar a true retorna la ID del menu presionado, en caso contrario puede retornar cualquier cosa.
                                                \Remarks    No es aconsejable usar el parametro Esperar a true en aplicaciones grandes, ya que situa un bucle de mensajes en medio que puede que no nos venga del todo bien.
                                                            Este parametro se dise�o de cara a aplicaciones senzillas para poder crear un men� y recibir sus mensajes con mas facilidad.
										*/
		  int                           MostrarMenuEx(HWND hWndDest, const bool Esperar = true, const bool DesactivarBlend = false);

										//! Funci�n que retorna el total de submenus que contiene este men�.
										/*! Esta funcion retorna el total de submenus que contiene este men�.
												\fn			inline const UINT TotalMenus(void);
												\return		Devuelve el total de menus.
										*/
		  inline UINT                   TotalMenus(void) const {
											return static_cast<UINT>(_Items.size());
										};

										//! Funci�n que retorna texto de este men�.
										/*! Esta funcion retorna texto de este men�.
												\fn			inline const TCHAR *Texto(void);
												\return		Devuelve el texto de este men�.
										*/
		  inline const TCHAR           *Texto(void) {
											return _Texto();
										};

										//! Funci�n que asigna texto de este men�.
										/*! Esta funcion asigna texto de este men�.
												\fn			inline void Texto(const TCHAR *Txt);
                                                \param[in]  Txt : Nuevo texto para el men�.
												\return		No devuelve nada.
										*/
		  inline void					Texto(const TCHAR *Txt) {
											_Texto = Txt;
										};

										//! Funci�n que retorna el submenu indicado por la posici�n.
										/*! Esta funcion retorna el submenu indicado por la posici�n.
												\fn			inline DWLMenuEx *Menu(const UINT Pos);
                                                \param[in]  Pos : Posicion del submenu que queremos obtener.
												\return		Devuelve una clase DWLMenuEx con el submenu indicado en la posici�n.
										*/
		  inline DWLMenuEx             *Menu(const UINT Pos) {
											return _Items[Pos];
										};

										//! Funci�n que retorna el siguiente men� a este.
										/*! Esta funcion retorna el siguiente men� a este.
												\fn			inline DWLMenuEx *Siguiente(void);
												\return		Devuelve una clase DWLMenuEx con el siguiente men�. Devuelve NULL si no existe un men� siguiente.
										*/
		  inline DWLMenuEx	           *Siguiente(void) {
											return _Next;
										};

										//! Funci�n que retorna el anterior men� a este.
										/*! Esta funcion retorna el anterior men� a este.
												\fn			inline DWLMenuEx *Anterior(void);
												\return		Devuelve una clase DWLMenuEx con el anterior men�. Devuelve NULL si no existe un men� anterior.
										*/
		  inline DWLMenuEx	           *Anterior(void) {
											return _Prev;
										};

										//! Funci�n que retorna el men� padre de este.
										/*! Esta funcion retorna el men� padre de este.
												\fn			inline DWLMenuEx *Padre(void);
												\return		Devuelve una clase DWLMenuEx con men� padre. Devuelve NULL si no existe un men� padre.
										*/
		  inline DWLMenuEx             *Padre(void) {
											return _Parent;
										};

										//! Funci�n que retorna el icono de este men�.
										/*! Esta funcion retorna el icono de este men�.
												\fn			inline UINT Icono(void) const;
												\return		Devuelve la ID del icono para este men�.
                                                \remarks    El icono debe estar a�adido en los recursos de la aplicaci�n.
										*/
		  inline UINT                   Icono(void) const {
											return _Iko;
										};

										//! Funci�n que asigna el icono de este men�.
										/*! Esta funcion asigna el icono de este men�.
												\fn			inline void Icono(const UINT nIcono);
                                                \param[in]  nIcono : ID del nuevo icono para el men�.
												\return		No devuelve nada.
                                                \remarks    El icono debe estar a�adido en los recursos de la aplicaci�n.
										*/
		  inline void                   Icono(const UINT nIcono) {
											_Iko = nIcono;
										};

										//! Funci�n que activa / descativa este men�.
										/*! Esta funcion activa / descativa este men�.
												\fn			inline void Activado(const bool Activar);
                                                \param[in]  Activar : true para activar el men�, false para desactivarlo.
												\return		No devuelve nada.
										*/
		  inline void                   Activado(const bool Activar) {
											_Enabled = Activar;
										};

										//! Funci�n que retorna si el menu esta activado o desactivado.
										/*! Esta funcion retorna si el menu esta activado o desactivado.
												\fn			inline BOOL Activado(void);
												\return		Devuelve TRUE si el men� esta activado, FALSE si esta desactivado.
										*/
		  inline BOOL                   Activado(void) {
											return static_cast<BOOL>(_Enabled);
										};

										//! Funci�n que busca la ID de un menu y retorna la clase DWLMenuEx asociada a el.
										/*! Esta funcion busca la ID de un menu y retorna la clase DWLMenuEx asociada a el.
												\fn			DWLMenuEx *BuscarID(const int bID);
                                                \param[in]  bID : ID del men� que se quiere buscar.
												\return		Devuelve la clase DWLMenuEx con la ID especificada, o NULL si no existe esa ID.
                                                \remarks    Esta funci�n busca la ID a partir de sus submenus, y no encontrara ids de menus que no esten dentro de el.
										*/
		  DWLMenuEx                    *BuscarID(const int bID);

										//! Funci�n que borra el men� especificado en la posici�n.
										/*! Esta funcion borra el men� especificado en la posici�n.
												\fn			void BorrarMenu(const UINT Pos);
                                                \param[in]  Pos : Posici�n del men� a borrar.
												\return		No devuelve nada
										*/
		  void                          BorrarMenu(const UINT Pos);

										//! Funci�n que borra todos los submenus.
										/*! Esta funcion borra todos los submenus.
												\fn			void BorrarTodo(void);
												\return		No devuelve nada
										*/
		  void                          BorrarTodo(void);

										//! Funci�n que oculta todos los menus.
										/*! Esta funcion oculta todos los menus.
												\fn			void OcultarTodo(void);
												\return		No devuelve nada
										*/
		  void                          OcultarTodo(void);

										//! Operador que retorna la clase DWLMenuEx especificada el la posici�n.
										/*! Este operador retorna la clase DWLMenuEx especificada el la posici�n.
												\fn			inline DWLMenuEx *operator[] (const UINT Pos);
												\return		No devuelve nada
										*/
		  inline DWLMenuEx   		   *operator[] (const UINT Pos) {
											return _Items[Pos];
										};

										//! Funci�n que retorna el identificador de este men�.
										/*! Esta funcion retorna el identificador de este men�.
												\fn			inline UINT IDMenu(void) const;
												\return		Devuelve la ID de este men�.
										*/
		  inline UINT			    	IDMenu(void) const {
											return _ID;
										};

		  DWLMenuEx_Estilos             Estilos;

		 protected :////////////////////// Miembros protegidos

                                        //! Funci�n virtual que se invoca al terminar de pintar toda la ventana.
										/*! Esta funcion virtual es invocada al terminar de pintar todo la ventana.
												\fn			inline virtual LRESULT Evento_Pintar_Finalizado(HDC hDC);
                                                \param[in]  hDC : HDC en el que podemos pintar mas cosas.
												\return		Si re-emplazas esta funci�n debes retornar 0.
										*/
		  inline virtual LRESULT        Evento_Pintar_Finalizado(HDC hDC) {
                                            return 0;
										};

                                        //! Funci�n virtual que se invoca al terminar de pintar el men�.
										/*! Esta funcion virtual es invocada al terminar de pintar el men�.
												\fn			inline virtual LRESULT Evento_PintarMenu_Finalizado(HDC hDC,const int pID, RECT *Espacio);
                                                \param[in]  hDC     : HDC en el que podemos pintar mas cosas.
                                                \param[in]  pID     : ID del men� que se ha pintado.
                                                \param[in]  Espacio : Recta que contiene el espacio del men�.
												\return		Si re-emplazas esta funci�n debes retornar 0.
										*/
		  inline virtual LRESULT        Evento_PintarMenu_Finalizado(HDC hDC, const int pID, RECT *Espacio) {
                                            return 0;
										};

										//! Funci�n predefinida del mensaje WM_*BUTTONDOWN (Virtual)
										/*!	Esta funci�n es la encargada de procesar los mensajes WN_*BUTTONDOWN.
												\fn			virtual LRESULT Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param)
												\param[in]	Boton	: Boton presionado.
												\param[in]	cX		: Coordenada X del mouse.
												\param[in]	cY		: Coordenada Y del mouse.
												\param[in]	wParam	: Teclas extendidas presionadas.
										        \return		Si re-emplazas esta funcion debes retornar 0.
										*/
		  LRESULT                       Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Params);

										//! Funci�n predefinida del mensaje WM_*BUTTONUP (Virtual)
										/*!	Esta funci�n es la encargada de procesar los mensajes WN_*BUTTONUP.
												\fn			virtual LRESULT Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
												\param[in]	Boton	: Boton presionado.
												\param[in]	cX		: Coordenada X del mouse.
												\param[in]	cY		: Coordenada Y del mouse.
												\param[in]	Param	: Teclas extendidas presionadas.
										        \return		Si re-emplazas esta funcion debes retornar 0.
										*/
		  LRESULT                       Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Params);

										//! Funci�n predefinida del mensaje WM_MOUSEMOVE.
										/*!	Esta funci�n es la encargada de procesar los mensajes WN_MOUSEMOVE.
												\fn			virtual LRESULT Evento_Mouse_Movimiento(const int cX, const int cY, const UINT wParam);
												\param[in]	cX		: Coordenada X del mouse.
												\param[in]	cY		: Coordenada Y del mouse.
												\param[in]	Param	: Teclas extendidas presionadas.
										        \return		Si re-emplazas esta funcion debes retornar 0.
										*/
		  LRESULT                       Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Params);

										//! Funci�n predefinida del mensaje WM_KEYDOWN (Virtual)
										/*!	Esta funci�n es la encargada de procesar los mensajes WM_KEYDOWN.
												\fn			virtual LRESULT Evento_Teclado_TeclaPresionada(const UINT Tecla, const UINT Repeticion, const UINT Param);
												\param[in]	Caracter   : Tecla virtual soltada.
												\param[in]	Repeticion : Repeticiones de la tecla
												\param[in]	Params	   : Teclas extendidas soltadas.
										        \return		Si re-emplazas esta funcion debes retornar 0.
										*/
		  LRESULT                       Evento_Teclado_TeclaPresionada(const UINT Tecla, const UINT Repeticion, const UINT Param);

										//! Funci�n predefinida del mensaje WM_KEYUP (Virtual)
										/*!	Esta funci�n es la encargada de procesar los mensajes WM_KEYUP.
												\fn			virtual LRESULT Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Param);
												\param[in]	Caracter   : Tecla virtual soltada.
												\param[in]	Repeticion : Repeticiones de la tecla
												\param[in]	Param	   : Teclas extendidas soltadas.
										        \return		Si re-emplazas esta funcion debes retornar 0.
										*/
		  LRESULT                       Evento_Teclado_TeclaSoltada(const UINT Tecla, const UINT Repeticion, const UINT Params) {
                                            return 0;
                                        };

										//! Funci�n que pinta todo el MenuEx cuado se recibe un mensaje WM_PAINT.
										/*!	Esta funci�n pinta el MenuEx cuando se recibe un mensaje WM_PAINT.
												\fn			LRESULT Evento_Pintar(HDC hDC);
												\param[in]	hDC	: hDC donde se pintara todo el MenuEx.
										        \return		Si re-emplazas esta funcion debes retornar 0.
										*/
		  LRESULT                       Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);

                                        //! Funci�n interna para mostrar los submenus.
										/*!	Esta funci�n se usa internamente para mostrar los submenus.
												\fn			void _Mostrar(HWND hWndDest, const int cX, const int cY, const int NAncho, const int NAlto, const bool DesactivarBlend);
												\param[in]	hWndDest	    : HWND del men� padre.
												\param[in]	cX	            : Coordenada X del men�.
												\param[in]	cY	            : Coordenada Y del men�.
												\param[in]	NAncho	        : Ancho del men�.
												\param[in]	NAlto	        : Alto del men�.
												\param[in]	DesactivarBlend	: Desactivar transparencias del men�.
										        \return		No devuelve nada.
										*/
		  void                         _Mostrar(HWND hWndDest, const int cX, const int cY, const int NAncho, const int NAlto, const bool DesactivarBlend);

										//! Funci�n que oculta este men�.
										/*! Esta funcion oculta este men�.
												\fn			void Ocultar(void);
												\return		No devuelve nada
										*/
		  void                          Ocultar(void);

                                        //! Funci�n para mostrar el submenu especificado en la posici�n.
										/*!	Esta funci�n se usa para mostrar el submenu especificado en la posici�n.
												\fn			DWLMenuEx *MostrarSubMenu(HWND hWndDest, const int Pos);
												\param[in]	hWndDest : HWND del men� padre.
												\param[in]	Pos      : Posici�n del men�.
										        \return		Devuelve la clase DWLMenuEx especificada en la posici�n.
										*/
		  DWLMenuEx                    *MostrarSubMenu(HWND hWndDest, const int Pos);

										//! Funci�n que borra los objetos GDI creados para mostrar los menus.
										/*! Esta funcion borra los objetos GDI creados para mostrar los menus.
												\fn			void BorrarFondoDC(void);
												\return		No devuelve nada
										*/
		  void                          BorrarFondoDC(void);

										//! Funci�n para calcular el tama�o de los menus.
										/*! Esta funci�n calcula el tama�o de los menus.
												\fn			POINT CalcularMedidas(void);
												\return		Devuelve la estructura POINT con el ancho y el alto necesarios para el men�.
										*/
		  POINT			                CalcularMedidas(void);

										//! Funci�n que pinta todos los items del men�.
										/*! Esta funci�n pinta todos los items del men�.
												\fn			POINT PintarItems(void);
												\return		No devuelve nada.
										*/
		  void                          PintarItems(void);

										//! Funci�n para pintar un Item especifico del men�.
										/*! Esta funci�n pinta un Item especifico del men�.
												\fn			void PintarItem(HDC hDC, const int NItem, const int Estado = 0);
                                                \param[in]  hDC    : HDC donde se pintara el item / men�.
                                                \param[in]  NItem  : Posicion del item / men�.
                                                \param[in]  Estado : Estado del item / men�.
												\return		No devuelve nada.
										*/
		  void                          PintarItem(HDC hDC, const int NItem, const int Estado = 0);

										//! Funci�n para pintar el borde de selecci�n del men�.
										/*! Esta funci�n pinta el borde de selecci�n del men�.
												\fn			void PintarSeleccion(HDC hDC, const int NItem);
                                                \param[in]  hDC    : HDC donde se pintara el borde.
                                                \param[in]  NItem  : Posicion del item / men�.
												\return		No devuelve nada.
										*/
		  void                          PintarSeleccion(HDC hDC, const int NItem);

                                        //! Funci�n que retorna la ID del MenuEx.
                                        /*!	Esta funcion devuelve la ID del MenuEx
                                                \fn			inline UINT ID(void);
                                                \return		Devuelve la ID del MenuEx.
                                        */
         inline UINT                    ID(void) { return _ID; };

									    //! Esqueleto para los mensajes del MenuEx.
									    /*! Esta funci�n es el esqueleto para los mensajes del MenuEx.
											    \fn			LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
											    \param[in]	uMsg	: Mensaje.
											    \param[in]	wParam	: Parametro1.
											    \param[in]	lParam	: Parametro2.
											    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
											    \remarks	Esta funci�n es el esqueleto del MenuEx por donde pasaran todos sus mensajes.
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

                                        //! ID del men� extendido
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
  Se ha retocado la funci�n que recibe los clicks del mouse para que no mande mensajes si el item pulsado esta desactivado. \n

- [29/12/2006] <b>0.81</b>  \n
  Se ha solucionado un problema con multiples pantallas, el menu solo salia en la pantalla principal. \n
  Se ha optimizado aun mas el proceso de pintado. \n

- [07/09/2005] <b>0.80</b>  \n
  Se han reemplazado varios nombres de funci�nes en ingles por castellano. \n
  Se han a�adido 2 nuevos eventos (Evento_Pintar_Finalizado, y Evento_PintarMenu_Finalizado) los cuales nos permiten pintar algo mas encima del menu.  \n
  Ahora es posible cambiar el texto del menu padre utilizando la funci�n DWLMenuEx::Texto() en la clase padre.\n
  Se han a�adido varios eventos con sus correspondientes macros. \n

- [05/12/2004] <b>0.71</b>  \n
  En las funciones de mostrar se retorna la ID del menu pulsado si no se indica Esperar = false, en ese caso retornara -1 \n
  La funci�n para agregar menus consta haora de un nuevo parametro (WM_SysCommand = false) si esta a falso enviara un WM_COMMAND de ese item, si esta true enviara un WM_SYSCOMMAND \n
  Las funci�nes de mostrar tenian un bug si se especificaba false al esperar el cual no mostraba el menu... \n
  Los Items desactivados tenian un bug, el cual seguia usando el item como si fuera normal (es decir cuando presionabas el item desactivado funcionaba como si no lo estubiera, mandando el mensaje a su ventana padre) \n
  Cuando presionas fuera del menu este mensaje no era percibido por la ventana que esta inmediatamente abajo, ahora si que lo recibe (basicamente el Evento_Mouse_BotonPresionado) \n
  Se ha modificado el codigo para que quede mas bonito de ver y facil de reprogramar... \n
  A�adida opcion para desactivar los AlphaBlend y substituirlos por un BitBlt. \n

*/
