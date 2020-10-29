/*! \file DWLMenuEx.cpp
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

				A continuación tienes un ejemplo de como crear un Menú extendido :\n

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

	\author		devildrey33
	\version	0.95
	\date		29/12/2006

	\remarks
				Archivo creado por devildrey33 el dia [05/12/2004] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)															\n

*/

#include "DWLGraficos.h"
#include "DWLMenuEx.h"

namespace DWL {
	namespace ControlesEx {

		HWND DWLMenuEx::_hWndDestMsg;

		//! Constructor.
		/*!	Constructor por defecto.
				\fn		DWLMenuEx(void);
				\return	No devuelve nada.
		*/
        DWLMenuEx::DWLMenuEx(void) : DWLControlEx(), _Iko(0), _Pos(0), _Presionado(-1), _Estado(-1), _Parent(NULL),
                                     _Next(NULL), _Prev(NULL), _UMenu(NULL), _Items(), _Texto(), _ItemSeleccionado(-1),
                                     _Tipo(DWL_Enum_MenuEx_Normal), _Enabled(true), _IDFinal(-1), _WM_SysCommand(false),
                                     _DesactivarBlend(false), _hDC(NULL), _MapaBits(NULL), _VMapaBits(NULL), _ID(0), Estilos() {
			_Texto = TEXT("Menú del Sistema");
//			Fuentes.Enlazar(DWL::SO::DWLEstilos::Fuentes);
		}

		//! Destructor.
		/*!	Destructor.
				\fn		~DWLMenuEx(void);
				\return	No devuelve nada.
		*/
		DWLMenuEx::~DWLMenuEx(void) {
			Ocultar();
			for (unsigned int i = 0; i < _Items.size(); i++) {
				delete _Items[i];
			}
			_hWndDestMsg = NULL;
		}


		//! Función para calcular el tamaño de los menus.
		/*! Esta función calcula el tamaño de los menus.
				\fn			POINT CalcularMedidas(void);
				\return		Devuelve la estructura POINT con el ancho y el alto necesarios para el menú.
		*/
		POINT DWLMenuEx::CalcularMedidas(void) {
			POINT Res;
			HDC   hDC   = GetDC(NULL);
			SIZE  R     = { 0, 0 };
			HFONT VFont = static_cast<HFONT>(SelectObject(hDC, Estilos.Fuentes.Negrita()));
			#if defined DWL_MENUEX_DEBUG
				DWL::DWLDebug::ImprimirDebug("DWLMenuEx::CalcularMedidas(hDC = %d)\n", hDC);
			#endif
			GetTextExtentPoint32(hDC, Texto(), static_cast<int>(DWLStrLen(Texto())), &R);
			#if defined DWL_MENUEX_DEBUG
				DWL::DWLDebug::ImprimirDebug("(%d) %s -> %d\n", ID(), Texto(), R.cx + 8);
			#endif
			Res.x = R.cx + 8; Res.y = 20;
			SelectObject(hDC, Estilos.Fuentes.Normal());
			for (unsigned int i = 0; i < _Items.size(); i++) {
				GetTextExtentPoint32(hDC, _Items[i]->Texto(), static_cast<int>(DWLStrLen(_Items[i]->Texto())), &R);
				if ((R.cx + 44) > Res.x) { Res.x = R.cx + 44; }
				#if defined DWL_MENUEX_DEBUG
					DWL::DWLDebug::ImprimirDebug("(%d) %s -> %d\n", _Items[i]->ID(), _Items[i]->Texto(), R.cx + 8);
				#endif
				Res.y += 20;
			}
			SelectObject(hDC, VFont);
			ReleaseDC(NULL, hDC);
			return Res;
		}



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
        DWLMenuEx *DWLMenuEx::AgregarMenu(const UINT IDM, const TCHAR *Txt, const UINT IconoRecursos, const int Posicion, const bool WM_SysCommand, const bool nActivado) {
			int Pos = Posicion;
			if (Pos == -1) {
				Pos = static_cast<int>(_Items.size());
			}
			DWLMenuEx *TmpMenu = new DWLMenuEx;
			TmpMenu->_Texto = Txt;
			TmpMenu->_Pos = Pos;
			TmpMenu->_Iko = IconoRecursos;
			TmpMenu->_ID = IDM;
			TmpMenu->_Parent = this;
			TmpMenu->_WM_SysCommand = WM_SysCommand;
			TmpMenu->_Tipo = DWL_Enum_MenuEx_Normal;
			TmpMenu->_Enabled = nActivado;
			if (Pos > 0) {
				TmpMenu->_Prev = _Items[Pos -1];
				_Items[Pos -1]->_Next = TmpMenu;
			}
			else {
				TmpMenu->_Prev = NULL;
			}
			if (Pos < static_cast<int>(_Items.size())) {
				TmpMenu->_Next = _Items[Pos];
				_Items[Pos]->_Prev = TmpMenu;
			}
			else {
				TmpMenu->_Next = NULL;
			}
			_Items.insert(_Items.begin() + Pos, TmpMenu);
			return _Items[Pos];
		};

        //! Función que agrega un separador a este menú.
		/*!	Función para agregar un separador a este menú.
				\fn		    DWLMenuEx *AgregarSeparador(const int Posicion = -1);
                \param[in]  Posicion : Posicion para el nuevo menú. -1 para situar el separador al final.
				\return	    No devuelve nada.
                \Remarks    Los separadores no tienen ID, y cuando el usuario presiona encima la ventana destino no recibe notificaciones.
				\sa			AgregarMenu()
		*/
        void DWLMenuEx::AgregarSeparador(const int Posicion) {
			int Pos = Posicion;
			if (Pos == -1) {
				Pos = static_cast<int>(_Items.size());
			}
			AgregarMenu(0, TEXT(""), 0, Pos);
			_Items[Pos]->_Tipo = DWL_Enum_MenuEx_Separador;
		};


        //! Función para mostrar este menu.
		/*!	Función para agregar un separador a este menú.
				\fn		    int MostrarMenuEx(HWND hWndDest, const bool Esperar = true, const bool DesactivarBlend = false);
                \param[in]  hWndDest        : HWND de la ventana que recibira los mensajes de este menú.
                \param[in]  Esperar         : Si se asigna true, esta función no retornara hasta que se cierre el menú (false por defecto).
                \param[in]  DesactivarBlend : Desactivar las transparencias del menú (false por defecto).
				\return	    Si asignamos Esperar a true retorna la ID del menu presionado, en caso contrario puede retornar cualquier cosa.
                \Remarks    No es aconsejable usar el parametro Esperar a true en aplicaciones grandes, ya que situa un bucle de mensajes en medio que puede que no nos venga del todo bien.
                            Este parametro se diseño de cara a aplicaciones senzillas para poder crear un menú y recibir sus mensajes con mas facilidad.
		*/
		int DWLMenuEx::MostrarMenuEx(HWND hWndDest, const bool Esperar, const bool DesactivarBlend) {
			_IDFinal = -1;
			POINT Punto;
			POINT Med;

			_DesactivarBlend = DesactivarBlend;

			GetCursorPos(&Punto);
			int TAncho = GetSystemMetrics(SM_CXFULLSCREEN);
			int FAncho = Punto.x;
			int TAlto = GetSystemMetrics(SM_CYFULLSCREEN);
			int FAlto = Punto.y;
			Med = CalcularMedidas();
			if (Med.x + Punto.x > TAncho) { FAncho = TAncho - Med.x; }
			if (Med.y + Punto.y > TAlto)  { FAlto -= Med.y; }
			_Mostrar(hWndDest, FAncho, FAlto, Med.x, Med.y, _DesactivarBlend);
			if (Esperar == true) {
				while (IsWindowVisible(_hWnd) == TRUE) {
					MSG msg;
					if (TRUE == GetMessage(&msg, 0, 0, 0)) {
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
			}
			return _IDFinal;
		};

		//! Función que busca la ID de un menu y retorna la clase DWLMenuEx asociada a el.
		/*! Esta funcion busca la ID de un menu y retorna la clase DWLMenuEx asociada a el.
				\fn			DWLMenuEx *BuscarID(const int bID);
                \param[in]  bID : ID del menú que se quiere buscar.
				\return		Devuelve la clase DWLMenuEx con la ID especificada, o NULL si no existe esa ID.
                \remarks    Esta función busca la ID a partir de sus submenus, y no encontrara ids de menus que no esten dentro de el.
		*/
        DWLMenuEx *DWLMenuEx::BuscarID(const int bID) {
			DWLMenuEx *R = NULL;
			for (unsigned int i = 0; i < _Items.size(); i++) {
				if (_Items[i]->_ID == bID)			return _Items[i];
				if (_Items[i]->TotalMenus() > 0)	R = _Items[i]->BuscarID(bID);
				if (R != NULL)						return R;
			}
			return NULL;
		};

		//! Función que borra el menú especificado en la posición.
		/*! Esta funcion borra el menú especificado en la posición.
				\fn			void BorrarMenu(const UINT Pos);
                \param[in]  Pos : Posición del menú a borrar.
				\return		No devuelve nada
		*/
        void DWLMenuEx::BorrarMenu(const UINT Pos) {
            if (Pos > 0)                _Items[Pos +1]->_Prev = _Items[Pos -1];
            if (Pos < _Items.size())    _Items[Pos -1]->_Next = _Items[Pos +1];
			delete _Items[Pos];
			_Items.erase(_Items.begin() + Pos);
		};

	    //! Función que borra todos los submenus.
	    /*! Esta funcion borra todos los submenus.
			    \fn			void BorrarTodo(void);
			    \return		No devuelve nada
	    */
        void DWLMenuEx::BorrarTodo(void) {
		    for (unsigned int i = 0; i < _Items.size(); i++) delete _Items[i];
		    _Items.resize(0);
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
        LRESULT DWLMenuEx::Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Params) {
			RECT  RC;
			POINT Pt = { cX, cY };
			GetClientRect(_hWnd, &RC);
			if (PtInRect(&RC, Pt) == FALSE) {
				OcultarTodo();
				POINT P;
				GetCursorPos(&P);
				HWND VentanaDeSalida = WindowFromPoint(P);
				RECT RCVS;
				GetWindowRect(VentanaDeSalida, &RCVS);
				switch (Boton) {
					case 0:	PostMessage(VentanaDeSalida, WM_LBUTTONDOWN, static_cast<WPARAM>(Params), MAKELPARAM(P.x - RCVS.left, P.y - RCVS.top)); break;
					case 1:	PostMessage(VentanaDeSalida, WM_RBUTTONDOWN, static_cast<WPARAM>(Params), MAKELPARAM(P.x - RCVS.left, P.y - RCVS.top)); break;
					case 2:	PostMessage(VentanaDeSalida, WM_MBUTTONDOWN, static_cast<WPARAM>(Params), MAKELPARAM(P.x - RCVS.left, P.y - RCVS.top)); break;
				}
				return 0;
			}
			_Presionado = _ItemSeleccionado;
			PintarItems();
            return 0;
		};

		//! Función predefinida del mensaje WM_*BUTTONUP (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONUP.
				\fn			virtual LRESULT Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	Boton	: Boton presionado.
				\param[in]	cX		: Coordenada X del mouse.
				\param[in]	cY		: Coordenada Y del mouse.
				\param[in]	Param	: Teclas extendidas presionadas.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
        LRESULT DWLMenuEx::Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Params) {
			try {
				if (_ItemSeleccionado < 0 || _ItemSeleccionado > static_cast<int>(_Items.size()) -1) return 0;
				if (_Items[_ItemSeleccionado]->_Enabled == true) {
					RECT  RC;
					POINT Pt = { cX, cY };
					GetClientRect(_hWnd, &RC);
					if (_ItemSeleccionado > -1 && PtInRect(&RC, Pt) == TRUE && _ItemSeleccionado == _Presionado) {
						if (_Items[_ItemSeleccionado]->TotalMenus() == 0) { OcultarTodo(); }
						else                                              { PintarItems(); }
						DWLMenuEx *T = _Items[_ItemSeleccionado];
						if (_Items[_ItemSeleccionado]->_WM_SysCommand == false)	{
							PostMessage(_hWndDestMsg, WM_COMMAND, _Items[_ItemSeleccionado]->_ID, 0);
						}
						else {
							PostMessage(_hWndDestMsg, WM_SYSCOMMAND, _Items[_ItemSeleccionado]->_ID, 0);
						}
						_IDFinal = _Items[_ItemSeleccionado]->_ID;
					}
					else {
						Ocultar();
					}
				}

				if (_Items[_ItemSeleccionado]->Activado() == TRUE) {
					PostMessage(_hWndDestMsg, DWL_MENUEX_MENU_PULSADO, reinterpret_cast<WPARAM>(_Items[_ItemSeleccionado]), static_cast<LPARAM>(_ID));
				}
				_Presionado = -1;
			}
			catch (...) {
				#if defined DWL_MENUEX_DEBUG
					DWL::DWLDebug::ImprimirDebug(TEXT("*** DWLMenuEx::Evento_Mouse_BotonSoltado [Error!!] _ItemSeleccionado = %d, _Items.size() = %d\n"), _ItemSeleccionado ,_Items.size());
				#endif
			}
			return 0;
		};

		//! Función predefinida del mensaje WM_MOUSEMOVE.
		/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEMOVE.
				\fn			virtual LRESULT Evento_Mouse_Movimiento(const int cX, const int cY, const UINT wParam);
				\param[in]	cX		: Coordenada X del mouse.
				\param[in]	cY		: Coordenada Y del mouse.
				\param[in]	Param	: Teclas extendidas presionadas.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
        LRESULT DWLMenuEx::Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Params) {
			RECT  RC;
			POINT Pt = { cX, cY };
			GetClientRect(_hWnd, &RC);
			if (PtInRect(&RC, Pt) == TRUE) {
				if (_ItemSeleccionado == static_cast<int>((cY + 3) / 20) -1) { return 0; }
				_ItemSeleccionado = static_cast<int>((cY + 3) / 20) -1;
			}
			else {
				POINT Punto;
				GetCursorPos(&Punto);
				HWND hh = WindowFromPoint(Punto);
				_ItemSeleccionado = -1;
				if (SendMessage(hh, DWL_MENUEX_ESMENU, 0, 0) == 33)  SetCapture(hh);
				return 0;
			}
			if (_ItemSeleccionado > -1 && _ItemSeleccionado < static_cast<int>(_Items.size())) {
				if (_UMenu != _Items[_ItemSeleccionado] && _UMenu != NULL) {
					_UMenu->Ocultar();   _UMenu = NULL;
				}
				if (_Items[_ItemSeleccionado]->TotalMenus() > 0 && _Items[_ItemSeleccionado]->_Enabled == true) {
					_UMenu = MostrarSubMenu(_hWndDestMsg, _ItemSeleccionado);
				}
			}
			else {
				if (_UMenu != NULL) {
					_UMenu->Ocultar();
					_UMenu = NULL;
				}
			}
			PintarItems();
            return 0;
		};

		//! Función predefinida del mensaje WM_KEYDOWN (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WM_KEYDOWN.
				\fn			virtual LRESULT Evento_Teclado_TeclaPresionada(const UINT Tecla, const UINT Repeticion, const UINT Param);
				\param[in]	Caracter   : Tecla virtual soltada.
				\param[in]	Repeticion : Repeticiones de la tecla
				\param[in]	Params	   : Teclas extendidas soltadas.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
        LRESULT DWLMenuEx::Evento_Teclado_TeclaPresionada(const UINT Tecla, const UINT Repeticion, const UINT Param) {
			if (Param & 24) OcultarTodo();
            return 0;
		};


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
		void DWLMenuEx::_Mostrar(HWND hWndDest, const int cX, const int cY, const int NAncho, const int NAlto, const bool DesactivarBlend) {
			#if defined DWL_MENUEX_DEBUG
				DWL::DWLDebug::ImprimirDebug(TEXT("DWLMenuEx::_Mostrar(x '%d'   y '%d'   ancho '%d'   alto '%d')\n"), cX, cY, NAncho, NAlto);
			#endif
			if (_hWnd == NULL) {
				CrearControl(NULL, TEXT("DWL::ControlesEx::DWLMenuEx"), WS_POPUP, 0, cX, cY, NAncho, NAlto, 0, WS_EX_TOPMOST | WS_EX_TOOLWINDOW, 0);
				_hWndDestMsg = hWndDest;
			}
			_DesactivarBlend = DesactivarBlend;
			Opacidad(240);
			SetWindowPos(_hWnd, HWND_TOPMOST, cX, cY, NAncho, NAlto, SWP_NOACTIVATE | SWP_SHOWWINDOW);
			SetCapture(_hWnd);
			HDC hDC = GetDC(_hWnd);
			BorrarFondoDC();
			_hDC = CreateCompatibleDC(NULL);
			_MapaBits = CreateCompatibleBitmap(hDC, NAncho, NAlto);
			_VMapaBits = static_cast<HBITMAP>(SelectObject(_hDC, _MapaBits));
			RECT RC;
			HBRUSH BrochaBorde = CreateSolidBrush(Estilos.Colores.Borde());
			GetClientRect(_hWnd, &RC);
			TRIVERTEX     GCVertex[2];
			GRADIENT_RECT tGRect;
			GCVertex[0].Red		= DWL_RGB_OBTENER_R(Estilos.Colores.DegradadoSuperior());
			GCVertex[0].Green	= DWL_RGB_OBTENER_G(Estilos.Colores.DegradadoSuperior());
			GCVertex[0].Blue	= DWL_RGB_OBTENER_B(Estilos.Colores.DegradadoSuperior());
			GCVertex[0].x = RC.left;
			GCVertex[0].y = RC.top;
			GCVertex[1].Red		= DWL_RGB_OBTENER_R(Estilos.Colores.DegradadoInferior());
			GCVertex[1].Green	= DWL_RGB_OBTENER_G(Estilos.Colores.DegradadoInferior());
			GCVertex[1].Blue	= DWL_RGB_OBTENER_B(Estilos.Colores.DegradadoInferior());
			GCVertex[1].x = RC.right;
			GCVertex[1].y = RC.bottom;
			tGRect.UpperLeft = 0;
			tGRect.LowerRight = 1;
			GradientFill(_hDC, GCVertex, 2, &tGRect, 1, DWLGRADIENT_FILL_RECT_V);
			FrameRect(_hDC, &RC, BrochaBorde);
			DeleteObject(BrochaBorde);
			ReleaseDC(_hWnd, hDC);
			SetCursor(LoadCursor(0, MAKEINTRESOURCE(IDC_ARROW)));
		};


		//! Función que oculta este menú.
		/*! Esta funcion oculta este menú.
				\fn			void Ocultar(void);
				\return		No devuelve nada
		*/
		void DWLMenuEx::Ocultar(void) {
			for (unsigned int i = 0; i < _Items.size(); i++) {
				_Items[i]->Ocultar();
				_Items[i]->_Estado = -1;
			}
			if (DestroyWindow(_hWnd) == TRUE) {
				BorrarFondoDC();
				PostMessage(_hWndDestMsg, DWL_MENUEX_MENU_OCULTADO, static_cast<WPARAM>(_ID), 0);
			#if defined DWL_CLASEMENUEX_DEBUG
					DWL::DWLDebug::ImprimirDebug("DWLMenuEx::Ocultar (Menu ID : %d Ocultado)\n");
				#endif
			}
			_hWnd = NULL;
			_UMenu = NULL;
		};


		//! Función que oculta todos los menus.
		/*! Esta funcion oculta todos los menus.
				\fn			void OcultarTodo(void);
				\return		No devuelve nada
		*/
		void DWLMenuEx::OcultarTodo(void) {
			#if defined DWL_MENUEX_DEBUG
				DWL::DWLDebug::ImprimirDebug("DWLMenuEx::OcultarTodo (Menu ID : %d)\n");
			#endif
			for (unsigned int i = 0; i < _Items.size(); i++) {
				_Items[i]->Ocultar();
				_Items[i]->_Estado = -1;
			}
			if (_Parent != NULL) {
				_Parent->OcultarTodo();
			}
			DestroyWindow(_hWnd);
			_hWnd = NULL;
			_UMenu = NULL;
			BorrarFondoDC();
		};

        //! Función para mostrar el submenu especificado en la posición.
		/*!	Esta función se usa para mostrar el submenu especificado en la posición.
				\fn			DWLMenuEx *MostrarSubMenu(HWND hWndDest, const int Pos);
				\param[in]	hWndDest : HWND del menú padre.
				\param[in]	Pos      : Posición del menú.
		        \return		Devuelve la clase DWLMenuEx especificada en la posición.
		*/
        DWLMenuEx *DWLMenuEx::MostrarSubMenu(HWND hWndDest, const int Pos) {
			int   TAncho = GetSystemMetrics(SM_CXFULLSCREEN);
			int   TAlto  = GetSystemMetrics(SM_CYFULLSCREEN);
            RECT M;
            GetWindowRect(_hWnd, &M);
			POINT Med    = _Items[Pos]->CalcularMedidas();
            int   FX     = M.left + (M.right - M.left) -1;
			int   FY     = M.top + 17 + (20 * Pos);
			if (FX + Med.x > TAncho)			FX = M.left - Med.x + 1;
            if (FY + Med.y > TAlto)				FY = (M.top - Med.y) + 37 + (20 * Pos);
			if (FY < 0)							FY = 0;
			if (_Items[Pos]->hWnd() == NULL)	_Items[Pos]->_Mostrar(hWndDest, FX, FY, Med.x, Med.y, _DesactivarBlend);
			_Items[Pos]->_ItemSeleccionado = -1;
			PostMessage(_hWndDestMsg, DWL_MENUEX_MENU_MOSTRADO, static_cast<WPARAM>(_ID), 0);
			return _Items[Pos];
		};


	    //! Función que pinta todos los items del menú.
	    /*! Esta función pinta todos los items del menú.
			    \fn			POINT PintarItems(void);
			    \return		No devuelve nada.
	    */
        void DWLMenuEx::PintarItems(void) {
		    HDC hDC = GetDC(_hWnd);
		    SetBkMode(hDC, TRANSPARENT);
		    int  Estado = -1;
            RECT R;
            GetClientRect(_hWnd, &R);
            int  An = R.right;
		    RECT RC;
		    for (unsigned int i = 0; i < _Items.size(); i++) {
			    if (_Items[i]->_Enabled == true) {
				    if (_ItemSeleccionado != static_cast<int>(i))	{ Estado = 0; }
				    else {
					    if (_Presionado != static_cast<int>(i))		{ Estado = 1; }
					    else										{ Estado = 2; }
				    }
			    }
			    else												{ Estado = 3; }
			    if (_Items[i]->_Estado != Estado) {
				    BitBlt(hDC, 0, (i *20) + 17, An, 20, _hDC, 0, (i *20) + 17, SRCCOPY);
				    PintarItem(hDC, i, Estado);
				    RC.left = 0; RC.top = (i *20) + 17; RC.right = An; RC.bottom = (i *20) + 37;
				    Evento_PintarMenu_Finalizado(hDC, _Items[i]->ID(), &RC);
			    }
		    }
		    ReleaseDC(_hWnd, hDC);
	    };


		//! Función para pintar el borde de selección del menú.
		/*! Esta función pinta el borde de selección del menú.
				\fn			void PintarSeleccion(HDC hDC, const int NItem);
                \param[in]  hDC    : HDC donde se pintara el borde.
                \param[in]  NItem  : Posicion del item / menú.
				\return		No devuelve nada.
		*/
        void DWLMenuEx::PintarSeleccion(HDC hDC, const int NItem) {
            RECT R;
            GetClientRect(_hWnd, &R);
            int An = R.right;
            int Al = R.bottom;
			HDC		TmpBkhDC	= CreateCompatibleDC(NULL);
			HBITMAP TmpBkBmp	= CreateCompatibleBitmap(hDC, An, Al);
			HBITMAP TmpBkBmpV	= static_cast<HBITMAP>(SelectObject(TmpBkhDC, TmpBkBmp));
			RECT    TmpR		= { 0, 0, An - 4, 20 };
			RECT    TmpR2		= { 2, (NItem * 20) + 17, An - 4, 20 };
			HBRUSH BF2 = CreateSolidBrush(Estilos.Colores.FondoSeleccion());
			FillRect(TmpBkhDC, &TmpR, BF2);
			FrameRect(TmpBkhDC, &TmpR, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
			if (_DesactivarBlend == false) {
				BLENDFUNCTION BF;
				BF.AlphaFormat = 0;
				BF.BlendOp = 0;
				BF.BlendFlags = 0;
				BF.SourceConstantAlpha = 96;
				AlphaBlend(hDC, TmpR2.left, TmpR2.top, TmpR2.right, TmpR2.bottom, TmpBkhDC, TmpR.left, TmpR.top, TmpR.right, TmpR.bottom, BF);
			}
			else {
				BitBlt(hDC, TmpR2.left, TmpR2.top, TmpR2.right, TmpR2.bottom, TmpBkhDC, TmpR.left, TmpR.top, SRCCOPY);
			}
			DeleteObject(BF2);
			SelectObject(TmpBkhDC, TmpBkBmpV);
			DeleteObject(TmpBkBmp);
			DeleteDC(TmpBkhDC);
		};


		//! Función que borra los objetos GDI creados para mostrar los menus.
		/*! Esta funcion borra los objetos GDI creados para mostrar los menus.
				\fn			void BorrarFondoDC(void);
				\return		No devuelve nada
		*/
		void DWLMenuEx::BorrarFondoDC(void) {
			if (_hDC != NULL) {
				SelectObject(_hDC, _VMapaBits);
				DeleteObject(_MapaBits);
				DeleteDC(_hDC);
				_VMapaBits = NULL;
				_MapaBits = NULL;
				_hDC = NULL;
			}
		};


		//! Función para pintar un Item especifico del menú.
		/*! Esta función pinta un Item especifico del menú.
				\fn			void PintarItem(HDC hDC, const int NItem, const int Estado = 0);
                \param[in]  hDC    : HDC donde se pintara el item / menú.
                \param[in]  NItem  : Posicion del item / menú.
                \param[in]  Estado : Estado del item / menú.
				\return		No devuelve nada.
		*/
		void DWLMenuEx::PintarItem(HDC hDC, const int NItem, const int nEstado) {
			RECT R;
            GetClientRect(_hWnd, &R);
            DWLMenuEx *Itm = _Items[NItem];
			Itm->_Estado = nEstado;
			#if defined DWL_MENUEX_DEBUG
				DWL::DWLDebug::ImprimirDebug("DWLMenuEx::PintarItem %d Estado %d Activado %d\n", NItem, nEstado, _Enabled));
			#endif
			switch (Itm->_Tipo) {
				case DWL_Enum_MenuEx_Normal : {
					HFONT VFont  = NULL;
					HICON ResIko = NULL;
					switch (nEstado) {
						case 0 : // Normal
							VFont = static_cast<HFONT>(SelectObject(hDC, Estilos.Fuentes.Normal()));
							SetTextColor(hDC, Estilos.Colores.TextoNormal());
							if (Itm->TotalMenus() > 0) {
                                DWL::GDI::PintarFlecha(hDC, R.right -16, (NItem * 20) + 20, Estilos.Colores.FlechaNormal(), DWL_DIRECCION_FLECHA_DERECHA);
//								PintarTrianguloSm(hDC, NItem, Colores.FlechaNormal(), false);
							}
							TextOut(hDC, 24, 20 + (20 * NItem), Itm->_Texto(), static_cast<int>(Itm->_Texto.Tam()));
							if (Itm->_Iko != 0) {
								ResIko = static_cast<HICON>(LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(Itm->_Iko), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR));
								DrawIconEx(hDC, 4, 19 + (20 * NItem), ResIko, 16, 16, 0, 0, DI_NORMAL);
								DestroyIcon(ResIko);
							}
							break;
						case 1 : // Seleccionado
							VFont = static_cast<HFONT>(SelectObject(hDC, Estilos.Fuentes.SubRayada()));
							SetTextColor(hDC, Estilos.Colores.TextoResaltado());
							PintarSeleccion(hDC, NItem);
							if (Itm->TotalMenus() > 0) {
								DWL::GDI::PintarFlecha(hDC, R.right -16, (NItem * 20) + 20, Estilos.Colores.FlechaResaltada(), DWL_DIRECCION_FLECHA_DERECHA);
//								PintarTrianguloSm(hDC, NItem, Colores.FlechaResaltada(), false);
							}
							TextOut(hDC, 24, 20 + (20 * NItem), Itm->_Texto(), static_cast<int>(Itm->_Texto.Tam()));
							if (Itm->_Iko != 0) {
								ResIko = static_cast<HICON>(LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(Itm->_Iko), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR));
								DrawIconEx(hDC, 4, 19 + (20 * NItem), ResIko, 16, 16, 0, 0, DI_NORMAL);
								DestroyIcon(ResIko);
							}
							break;
						case 2 : // Presionado
							VFont = static_cast<HFONT>(SelectObject(hDC, Estilos.Fuentes.SubRayada()));
							SetTextColor(hDC, Estilos.Colores.TextoResaltado());
							PintarSeleccion(hDC, NItem);
							if (Itm->TotalMenus() > 0) {
								DWL::GDI::PintarFlecha(hDC, (R.right -16) + 1, ((NItem * 20) + 20) + 1, Estilos.Colores.FlechaResaltada(), DWL_DIRECCION_FLECHA_DERECHA);
//								PintarTrianguloSm(hDC, NItem, Colores.FlechaResaltada(), true);
							}
							TextOut(hDC, 25, 21 + (20 * NItem), Itm->_Texto(), static_cast<int>(Itm->_Texto.Tam()));
							if (Itm->_Iko != 0) {
								ResIko = static_cast<HICON>(LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(Itm->_Iko), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR));
								DrawIconEx(hDC, 5, 20 + (20 * NItem), ResIko, 16, 16, 0, 0, DI_NORMAL);
								DestroyIcon(ResIko);
							}
							break;
						case 3 : // Desactivado
							VFont = static_cast<HFONT>(SelectObject(hDC, Estilos.Fuentes.Normal()));
							SetTextColor(hDC, Estilos.Colores.TextoDesactivado());
							if (Itm->TotalMenus() > 0) {
								DWL::GDI::PintarFlecha(hDC, R.right -16, (NItem * 20) + 20, Estilos.Colores.FlechaDesactivada(), DWL_DIRECCION_FLECHA_DERECHA);
								//PintarTrianguloSm(hDC, NItem, Colores.FlechaDesactivada(), false);
							}
							TextOut(hDC, 24, 20 + (20 * NItem), Itm->_Texto(), static_cast<int>(Itm->_Texto.Tam()));
							if (Itm->_Iko != 0) {
								ResIko = static_cast<HICON>(LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(Itm->_Iko), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR));	DrawIconEx(hDC, 4, 19 + (20 * NItem), ResIko, 16, 16, 0, 0, DI_NORMAL);
								DestroyIcon(ResIko);
							}
							break;
					}
					if (VFont != NULL) SelectObject(hDC, VFont);
					break;
				}
				case DWL_Enum_MenuEx_Separador : {
					RECT RS = { 5, (NItem *20) + 27, R.right - 5, ((NItem * 20) + 28) };
					HBRUSH Pluma = CreateSolidBrush(Estilos.Colores.Borde());
					FillRect(hDC, &RS, Pluma);
					DeleteObject(Pluma);
					break;
				}
/*				case DWL::Enums::MenuEx_BarraDesplazamiento : {
					//HBRUSH uBrocha = static_cast<HBRUSH>(SelectObject(hDC, GetStockObject(BLACK_BRUSH)));
					RECT RS = { 25, (NItem *20) + 26, Ancho() - 23, ((NItem * 20) + 29) };
					if (nEstado == 1 || nEstado == 2) PintarSeleccion(hDC, NItem);
					_EnmarcarBarra(hDC, &RS);
					//RoundRect(hDC, 24, (NItem *20) + 25, Ancho() - 24, ((NItem * 20) + 30), 1, 1);
					DWL::GDI::PintarGradient(hDC, RS.left, RS.top, RS.right - RS.left, RS.bottom - RS.top, Colores.DegradadoBarra1(), Colores.DegradadoBarra2(), true);
					//SelectObject(hDC, uBrocha);
					break;
				}*/
			}
		};





	    //! Esqueleto para los mensajes del MenuEx.
	    /*! Esta función es el esqueleto para los mensajes del MenuEx.
			    \fn			LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
			    \param[in]	uMsg	: Mensaje.
			    \param[in]	wParam	: Parametro1.
			    \param[in]	lParam	: Parametro2.
			    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
			    \remarks	Esta función es el esqueleto del MenuEx por donde pasaran todos sus mensajes.
	    */
		LRESULT CALLBACK DWLMenuEx::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
			switch (uMsg) {
				case DWL_MENUEX_ESMENU         : return 33;																													break;
				//case WM_CAPTURECHANGED : if (33 != SendMessage((HWND)lParam, DWL_MENUEX_ESMENU, 0, 0)) { SetCapture(_hWnd); }                   break;
			}
			return DWLControlEx::GestorMensajes(uMsg, wParam, lParam);
		}



		//! Función que pinta todo el MenuEx cuado se recibe un mensaje WM_PAINT.
		/*!	Esta función pinta el MenuEx cuando se recibe un mensaje WM_PAINT.
				\fn			virtual void Evento_Pintar(HDC hDC);
				\param[in]	hDC	: hDC donde se pintara todo el MenuEx.
                \param[in]  PS  : Estructura que contiene datos del pintado.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLMenuEx::Evento_Pintar(HDC hDC, PAINTSTRUCT &PS) {
            RECT R;
            GetClientRect(_hWnd, &R);
			int     An         = R.right;
			int     Al         = R.bottom;
			HDC     TmphDC     = CreateCompatibleDC(NULL);
			HBITMAP TmphDCBmp  = CreateCompatibleBitmap(hDC, An, Al);
			HBITMAP TmphDCBmpV = static_cast<HBITMAP>(SelectObject(TmphDC, TmphDCBmp));
			BitBlt(TmphDC, 0, 0, An, Al, _hDC, 0, 0, SRCCOPY);
			SetBkMode(TmphDC, TRANSPARENT);
			HFONT VFont = static_cast<HFONT>(SelectObject(TmphDC, Estilos.Fuentes.Negrita()));
			SetTextColor(TmphDC, Estilos.Colores.TextoResaltado());
            TextOut(TmphDC, 5, 3, Texto(), static_cast<int>(DWLStrLen(Texto())));
			for (unsigned int i = 0; i < _Items.size(); i++) {
				if (_Items[i]->_Enabled == true) {
					if (_ItemSeleccionado != static_cast<int>(i)) {
						PintarItem(TmphDC, i, 0);
					}
					else {
						if (_Presionado == static_cast<int>(i)) {
							PintarItem(TmphDC, i, 2);
						}
						else                  {
							PintarItem(TmphDC, i, 1);
						}
					}
				}
				else {
					PintarItem(TmphDC, i, 3);
				}
			}
			Evento_Pintar_Finalizado(TmphDC);
			BitBlt(hDC, 0, 0, An, Al, TmphDC, 0, 0, SRCCOPY);
			SelectObject(TmphDC, VFont);
			SelectObject(TmphDC, TmphDCBmpV);
			DeleteObject(TmphDCBmp);
			DeleteDC(TmphDC);
            return 0;
		};

	}
}

