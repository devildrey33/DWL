/*! \file DWLArbolEx.cpp
	\brief		 Archivo que contiene las definiciones para las clases del ArbolEx.


	\details	Este control simula un TreeView de windows, con algunas innovaciones como pueden ser la sub-seleccion, tooltips propios facilmente configurables, scrolls que pueden contener botones extra, y ademas tiene una apariencia totalmente configurable.																												\n
				<table border = 0 align ='right'><tr><td> \image html ArbolEx.jpg </td></tr></table>
																																											\n
				\section Clases_Sec		Este archivo contiene varias clases descritas a continuación  :
				 - DWL::ControlesEx::DWLArbolEx_Colores	:																																																		\n
				   Clase que enlaza los colores a la configuracion del skin por defecto.																																										\n
				   Puedes modificar cualquier color de esta clase, solo deberas repintar el arbol al terminar.																																					\n
																																																																\n
				 - DWL::ControlesEx::DWLArbolEx_ColoresNodo	:																																																	\n
				   Clase que enlaza los colores del nodo a la configuracion skin por defecto.																																									\n
																																																																\n
				 - DWL::ControlesEx::DWLArbolEx_ParametrosClick	:																																																\n
				   Clase utilizada internamente para pasar los datos de un click a la ventana padre.																																							\n
																																																																\n
				 - DWL::ControlesEx::DWLArbolEx_TerminarLabelEdit :																																																\n
				   Clase utilizada internamente para pasar los datos de una edicion a la ventana padre.																																							\n
																																																																\n
				 - DWL::ControlesEx::DWLArbolEx_Nodo :																																																			\n
				   Clase que contiene los datos de un nodo (Puede ser heredada).																																												\n
																																																																\n
				 - DWL::ControlesEx::DWLArbolEx_Nucleo :																																																		\n
				   Clase que contiene las funciónes basicas para pintar y controlar los eventos del arbol.																																						\n
				   Esta clase se ha creado de forma que puede compartir un control con otra clase, aunque es poco probable que se requiera compartir un arbol con otro control, es muy interesante la posibilidad de poder pintar el control en cualquier hDC.  \n
																																																															    \n
				 - DWL::ControlesEx::DWLArbolEx :																																																				\n
				   Clase que hereda de DWLArbolEx_Nucleo y lo enlaza a un control para el solo.																																									\n
				   Esta clase es la que deberiamos usar para crear un arbol estandar sin complicaciones.																																						\n

																																																																\n
	\author		devildrey33
	\date		Creado el [20/02/2005], ultima modificación el [04/11/2009]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

	\todo		Revisar implementación del teclado, en especial teclas con control o shift.
*/
#include "DWLArbolEx.h"
#include "DWLToolTipEx.h"

//#define ANCHO_SCROLLBAR 16
#define DWL_NOMBRE_CLASE_DWLARBOLEX TEXT("DWL::ControlesEx::DWLArbolEx")


namespace DWL {
	namespace ControlesEx {
		//! Constructor.
		/*!	Constructor por defecto.
				\fn		DWLArbolEx(void);
				\return	No devuelve nada.
		*/
        DWLArbolEx::DWLArbolEx(void) : DWLControlEx(), DWLArbolEx_Nucleo() {
            RegistrarClase(DWL_NOMBRE_CLASE_DWLARBOLEX, 0, 0, _GestorMensajes);
		}


		//! Destructor.
		/*!	Destructor.
				\fn		~DWLArbolEx(void);
				\return	No devuelve nada.
		*/
		DWLArbolEx::~DWLArbolEx(void) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::~DWLArbolEx\n"));
			#endif
			Destruir();
		}

		//! Función que retorna si esta ventana tiene el raton encima.
		/*!	Esta funcion devuelve si esta ventana tiene el raton encima.
				\fn			virtual bool Foco(void);
				\return		Devuelve true si el raton esta encima del control, false en caso contrario.
		*/
        bool DWLArbolEx::Foco(void) {
			bool TieneFoco = false;
			if (_ArbolEx_NodoPresionado != NULL) return true;
			POINT Pt;
			GetCursorPos(&Pt);
			if (_hWnd == WindowFromPoint(Pt)) { // Tiene el foco del raton
				TieneFoco = true;
			}
			return TieneFoco;
		};

		//! Función que destruye este ArbolEx.
		/*!	Esta funcion destruye el ArbolEx.
				\fn			const BOOL Destruir(void);
				\return		Devuelve TRUE si la operacion se completo, FALSE en caso contrario.
		*/
		BOOL DWLArbolEx::Destruir(void) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Destruir\n"));
			#endif
			ArbolEx_BorrarMemoria();
			return DWLControlEx::Destruir();
		}
 
		//! Función que crea el ArbolEx.
		/*!	Esta funcion crea el ArbolEx.
				\fn			HWND CrearArbolEx(const long Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const bool cPintarBorde = true);
				\param[in]	Estilos			: Estilos para el ArbolEx (WS_CHILD | WS_VISIBLE).
				\param[in]	hWndParent		: HWND del control que sera el padre del ArbolEx.
				\param[in]	cX				: Posicion X.
				\param[in]	cY				: Posicion Y.
				\param[in]	cAncho			: Ancho del ArbolEx.
				\param[in]	cAlto			: Alto del ArbolEx.
				\param[in]	cID				: ID del ArbolEx.
				\param[in]	cPintarBorde	: Parametro que indica si se tiene que pintar el borde del ArbolEx.
				\return		Devuelve el HWND del ArbolEx. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para mas información del error.
		*/
		HWND DWLArbolEx::CrearArbolEx(const long Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const bool cPintarBorde) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::CrearArbolEx\n"));
			#endif
			_ArbolEx_Editando = false;
			int TotalLineas = (static_cast<int>(static_cast<float>(cAlto) / static_cast<float>(_ArbolEx_AltoLinea)));
			CrearControl(hWndParent, DWL_NOMBRE_CLASE_DWLARBOLEX, Estilos, 0, cX, cY, cAncho, cAlto, cID);
			_BarraScrollEx_PosActualV	= 0;
			ArbolEx_Estilos.PintarBorde	= cPintarBorde;
			_ArbolEx_NodoResaltado		= 0;
			_ArbolEx_UNodoResaltado		= 0;

			RECT RC = { 0, 0, cAncho, cAlto };
			if (ArbolEx_Estilos.PintarBorde == true) {
				HRGN Region = CreateRoundRectRgn(0, 0, cAncho + 1, cAlto + 1, 2, 2);
				AsignarRegion(Region, false);
			}

			BarraScrollEx_CrearV(DWL_BARRASCROLLEX_AUTOMATICO, 0, 0, 0);
			BarraScrollEx_CrearH(DWL_BARRASCROLLEX_AUTOMATICO, 0, 0, 0);
			BarraScrollEx_PosicionarScrolls(_hWnd, &RC, false, ArbolEx_Estilos.PintarBorde);

			HDC hDC				= GetDC(NULL);
			_ArbolEx_Buffer		= CreateCompatibleDC(NULL);
			_ArbolEx_Bmp		= CreateCompatibleBitmap(hDC, cAncho, _ArbolEx_AltoLinea);
			_ArbolEx_Viejo		= static_cast<HBITMAP>(SelectObject(_ArbolEx_Buffer, _ArbolEx_Bmp));
			_ArbolEx_VFuente	= static_cast<HFONT>(SelectObject(_ArbolEx_Buffer, ArbolEx_Estilos.Fuentes.Normal()));
			_ArbolEx_FondoDC    = CreateCompatibleDC(NULL);
			_ArbolEx_BmpFondo   = CreateCompatibleBitmap(hDC, cAncho, cAlto + _ArbolEx_AltoLinea);
			_ArbolEx_ViejoFondo = static_cast<HBITMAP>(SelectObject(_ArbolEx_FondoDC, _ArbolEx_BmpFondo));
			SetBkMode(_ArbolEx_Buffer, TRANSPARENT);
			ReleaseDC(_hWnd, hDC);
			ArbolEx_Evento_Pintar_Fondo(_ArbolEx_FondoDC, &RC);
            ArbolEx_ActualizarTodo(_hWnd, &RC);
//			ArbolEx_FinAgregarNodos(_hWnd);
			return _hWnd;
		}

		//! Función que conecta el ArbolEx de un dialogo.
		/*!	Esta funcion conecta el ArbolEx de un dialogo.
				\fn			HWND ConectarArbolEx(HWND hWndParent, const int cID, const bool cPintarBorde = true);
				\param[in]	hWndParent		: HWND del control que sera el padre del ArbolEx.
				\param[in]	cID				: ID del ArbolEx.
				\param[in]	cPintarBorde	: Parametro que indica si se tiene que pintar el borde del ArbolEx.
				\return		Devuelve el HWND del ArbolEx. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para mas información del error.
                \remarks    Esta función solo debe usarse con controles que se creen durante la creación del dialogo, si esta clase no pertenece a un dialogo, o se va a crear dinamicamente, no debes usar esta función.
		*/
        HWND DWLArbolEx::ConectarArbolEx(HWND hWndParent, const int cID, const bool cPintarBorde) {
			_ArbolEx_Editando = false;
            RECT RC;
            _ConectarControl(cID, hWndParent);
            GetClientRect(_hWnd, &RC);
            int TotalLineas = (static_cast<int>(static_cast<float>(RC.bottom) / static_cast<float>(_ArbolEx_AltoLinea)));
			_BarraScrollEx_PosActualV	= 0;
			ArbolEx_Estilos.PintarBorde	= cPintarBorde;
			_ArbolEx_NodoResaltado		= NULL;
			_ArbolEx_UNodoResaltado		= NULL;

			if (ArbolEx_Estilos.PintarBorde == true) {
                HRGN Region = CreateRoundRectRgn(0, 0, RC.right + 1, RC.bottom + 1, 2, 2);
				AsignarRegion(Region, false);
			}

			BarraScrollEx_CrearV(DWL_BARRASCROLLEX_AUTOMATICO, 0, 0, 0);
			BarraScrollEx_CrearH(DWL_BARRASCROLLEX_AUTOMATICO, 0, 0, 0);
			BarraScrollEx_PosicionarScrolls(_hWnd, &RC, false, ArbolEx_Estilos.PintarBorde);

			HDC hDC		= GetDC(NULL);
			_ArbolEx_Buffer		= CreateCompatibleDC(NULL);
			_ArbolEx_Bmp		= CreateCompatibleBitmap(hDC, RC.right, _ArbolEx_AltoLinea);
			_ArbolEx_Viejo		= static_cast<HBITMAP>(SelectObject(_ArbolEx_Buffer, _ArbolEx_Bmp));
			_ArbolEx_VFuente	= static_cast<HFONT>(SelectObject(_ArbolEx_Buffer, ArbolEx_Estilos.Fuentes.Normal()));
			_ArbolEx_FondoDC    = CreateCompatibleDC(NULL);
			_ArbolEx_BmpFondo   = CreateCompatibleBitmap(hDC, RC.right, RC.bottom + _ArbolEx_AltoLinea);
			_ArbolEx_ViejoFondo = static_cast<HBITMAP>(SelectObject(_ArbolEx_FondoDC, _ArbolEx_BmpFondo));
			SetBkMode(_ArbolEx_Buffer, TRANSPARENT);
			ReleaseDC(_hWnd, hDC);
			ArbolEx_Evento_Pintar_Fondo(_ArbolEx_FondoDC, &RC);
            ArbolEx_ActualizarTodo(_hWnd, &RC);
			return _hWnd;
        }


		//! Función que repinta todo el ArbolEx.
		/*!	Esta función repinta todo el ArbolEx incluyendo barras de scroll y botones extra.
				\fn			void Repintar(const bool Forzar = false);
				\param[in]	Forzar : True para forzar el repintado, false para que la funcion decida si repintar.
				\return		No devuelve nada.
				\remarks	Cuando Forzar es false, esta función mira si ha cambiado algun estado interno,
							y de ser asi repinta el control, en caso contrario no hace nada.
		*/
		void DWLArbolEx::Repintar(const bool Forzar) {
		#if defined DWL_ARBOLEX_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Repintar(Forzar %d)\n"), Forzar);
		#endif
			if (_ArbolEx_Editando == true) return;
			bool P = Forzar;
			if (P == false) {
				if (_BarraScrollEx_UValorV != _BarraScrollEx_ValorV)	P = true;
				if (_ArbolEx_UNodoResaltado != _ArbolEx_NodoResaltado)	P = true;
				bool FocoActual = Foco();
				if (_ArbolEx_FocoRaton != FocoActual) {
					_ArbolEx_FocoRaton = FocoActual;
					P = true;
				}
			}
			_BarraScrollEx_UValorV = _BarraScrollEx_ValorV;
			_ArbolEx_UNodoResaltado = _ArbolEx_NodoResaltado;
			if (P == true) {
				RECT RC;
                GetClientRect(_hWnd, &RC);
				ArbolEx_Evento_Pintar_Fondo(_ArbolEx_FondoDC, &RC);
                PAINTSTRUCT PS;
				HDC hDC = GetDC(_hWnd);
		//		_ScrollV->ReAjustarMedidas();
		//		_ScrollV->Repintar(true);
				Evento_Pintar(hDC, PS);
				ReleaseDC(_hWnd, hDC);
			}
		}


		//! Función predefinida del mensaje WM_MOUSEWHEEL.
		/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEWHEEL.
				\fn			virtual LRESULT Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey);
				\param[in]	Delta	: Valor de desplazamiento del mouse.
				\param[in]	cX		: Coordenada X.
				\param[in]	cY		: Coordenada Y.
				\param[in]	VirtKey	: Tecla virtual presionada.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLArbolEx::Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Mouse_Rueda  VirtKey %d | Delta %d | cX %d | cY %d\n"), VirtKey, Delta, cX, cY);
			#endif
			if ((_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) > 0 && _BarraScrollEx_ValorV < (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) +1) {
				if (Delta > 0) { // Hacia arriba
					_BarraScrollEx_ValorV -= 3;
					if (_BarraScrollEx_ValorV < 0) BarraScrollEx_ValorV(0);

				}
				else { // Hacia abajo
					_BarraScrollEx_ValorV += 3;
					if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
				}
				_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;
				_ArbolEx_NodoResaltado = NULL;
				_ArbolEx_ExpansorResaltado = NULL;
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
				BarraScrollEx_Repintar(_hWnd, true);
				Repintar(true);
			}
            RECT RC;
            GetClientRect(_hWnd, &RC);
			_ArbolEx_UYMouse = RC.bottom + _ArbolEx_AltoLinea;
            return 0;
		}


		//! Función para mover el ArbolEx a la posicion y el tamaño especificados.
		/*!	Esta función mueve el ArbolEx a la posicion y tamaño especificados.
				\fn			void Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = true);
				\param[in]	cX			: Nueva posicion X para el ArbolEx.
				\param[in]	cY			: Nueva posicion Y para el ArbolEx.
				\param[in]	cAncho		: Nuevo ancho para el ArbolEx.
				\param[in]	cAlto		: Nueva altura para el ArbolEx.
				\param[in]	cRepintar	: True para repintar el control, false para dejarlo sin repintar.
				\return		No devuelve nada.
		*/
		void DWLArbolEx::Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Mover\n"));
			#endif

			if (ArbolEx_Estilos.PintarBorde == true) {
				HRGN Region = CreateRoundRectRgn(0, 0, cAncho + 1, cAlto + 1, 2, 2);
				AsignarRegion(Region, false);
			}

			RECT RectaFondo = { 0, 0, cAncho, cAlto };
			MoveWindow(_hWnd, cX, cY, cAncho, cAlto, false);
			long UPaginaV = _BarraScrollEx_PaginaV;
			long UPaginaH = _BarraScrollEx_PaginaH;
			_BarraScrollEx_PaginaV = (static_cast<int>(static_cast<float>(cAlto) / static_cast<float>(_ArbolEx_AltoLinea)));
			_BarraScrollEx_PaginaH = cAncho;

			if (BarraScrollEx_VisibleH() == TRUE) _BarraScrollEx_PaginaV -= 1;
			if (BarraScrollEx_VisibleV() == TRUE) _BarraScrollEx_PaginaH -= 17;
			if (UPaginaV < _BarraScrollEx_PaginaV && _BarraScrollEx_ValorV > _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
			if (UPaginaH < _BarraScrollEx_PaginaH && _BarraScrollEx_ValorH > _BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH) BarraScrollEx_ValorH(_BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH);

			BarraScrollEx_PosicionarScrolls(_hWnd, &RectaFondo, true, ArbolEx_Estilos.PintarBorde);

			if (_ArbolEx_FondoDC != NULL) {
				SelectObject(_ArbolEx_FondoDC, _ArbolEx_VFuente);
				SelectObject(_ArbolEx_FondoDC, _ArbolEx_Viejo);
				DeleteObject(_ArbolEx_Bmp);
				DeleteDC(_ArbolEx_FondoDC);
				_ArbolEx_FondoDC = NULL;
				SelectObject(_ArbolEx_Buffer, _ArbolEx_VFuente);
				SelectObject(_ArbolEx_Buffer, _ArbolEx_ViejoFondo);
				DeleteObject(_ArbolEx_BmpFondo);
				DeleteDC(_ArbolEx_Buffer);
			}

			HDC	hDC		= GetDC(NULL);
			_ArbolEx_FondoDC    = CreateCompatibleDC(hDC);
			_ArbolEx_Bmp        = CreateCompatibleBitmap(hDC, cAncho, cAlto + _ArbolEx_AltoLinea);
			_ArbolEx_Viejo      = static_cast<HBITMAP>(SelectObject(_ArbolEx_FondoDC, _ArbolEx_Bmp));
			_ArbolEx_VFuente    = static_cast<HFONT>(SelectObject(_ArbolEx_FondoDC, ArbolEx_Estilos.Fuentes.Normal()));
			int AnchoBuffer = _BarraScrollEx_MaximoH;
			if (AnchoBuffer < cAncho) AnchoBuffer = cAncho;
			_ArbolEx_Buffer		= CreateCompatibleDC(hDC);
			_ArbolEx_BmpFondo	= CreateCompatibleBitmap(hDC, AnchoBuffer, _ArbolEx_AltoLinea);
			_ArbolEx_ViejoFondo = static_cast<HBITMAP>(SelectObject(_ArbolEx_Buffer, _ArbolEx_BmpFondo));
			_ArbolEx_VFuente    = static_cast<HFONT>(SelectObject(_ArbolEx_Buffer, ArbolEx_Estilos.Fuentes.Normal()));
			ReleaseDC(NULL, hDC);
			SetBkMode(_ArbolEx_FondoDC, TRANSPARENT);
			SetBkMode(_ArbolEx_Buffer, TRANSPARENT);
			ArbolEx_Evento_Pintar_Fondo(_ArbolEx_FondoDC, &RectaFondo);
			if (cRepintar == true) Repintar(true);
		}


		//! Función para asignar los pixeles que tendra de alto cada nodo del ArbolEx.
		/*!	Esta funcion asigna los pixeles que tendra de alto cada nodo del ArbolEx.
				\fn			void AltoLinea(const int nAlto);
				\param[in]	nAlto	: Nueva altura en pixeles para los nodos del ArbolEx.
				\return		No devuelve nada.
		*/
		void DWLArbolEx::AltoLinea(const int nAlto) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::AltoLinea\n"));
			#endif
            WINDOWPLACEMENT WP;
			WP.length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(_hWnd, &WP);
            RECT R;
            GetClientRect(_hWnd, &R);
			_ArbolEx_AltoLinea = nAlto;
			HDC hDC = GetDC(NULL);
			SelectObject(_ArbolEx_Buffer, _ArbolEx_VFuente);
			SelectObject(_ArbolEx_Buffer, _ArbolEx_Viejo);
			DeleteObject(_ArbolEx_Bmp);
			DeleteDC(_ArbolEx_Buffer);
			_ArbolEx_Buffer		= CreateCompatibleDC(NULL);
            _ArbolEx_Bmp		= CreateCompatibleBitmap(hDC, R.right, _ArbolEx_AltoLinea);
			_ArbolEx_Viejo		= (HBITMAP)SelectObject(_ArbolEx_Buffer, _ArbolEx_Bmp);
			_ArbolEx_VFuente    = static_cast<HFONT>(SelectObject(_ArbolEx_Buffer, ArbolEx_Estilos.Fuentes.Normal()));
			ReleaseDC(_hWnd, hDC);
			SetBkMode(_ArbolEx_Buffer, TRANSPARENT);

            int  TotalLineas = (static_cast<int>(static_cast<float>(R.bottom) / static_cast<float>(_ArbolEx_AltoLinea)));
            Mover(WP.rcNormalPosition.left, WP.rcNormalPosition.top, R.right, TotalLineas * _ArbolEx_AltoLinea);
/*			hDC = GetDC(_hWnd);
            PAINTSTRUCT PS;
			Evento_Pintar(hDC, &PS);
			ReleaseDC(_hWnd, hDC);*/
			Repintar(true);
		}

		//! Función predefinida del mensaje WM_*BUTTONDOWN (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONDOWN.
				\fn			virtual LRESULT Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param)
				\param[in]	Boton	: Boton presionado.
				\param[in]	cX		: Coordenada X del mouse.
				\param[in]	cY		: Coordenada Y del mouse.
				\param[in]	wParam	: Teclas extendidas presionadas.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLArbolEx::Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			ArbolEx_Mouse_BotonPresionado(_hWnd, &RC, Boton, cX, cY, Param);
			Repintar();
            return 0;
		}

		//! Función predefinida del mensaje WM_*BUTTONUP (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONUP.
				\fn			virtual LRESULT Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	Boton	: Boton presionado.
				\param[in]	cX		: Coordenada X del mouse.
				\param[in]	cY		: Coordenada Y del mouse.
				\param[in]	Param	: Teclas extendidas presionadas.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLArbolEx::Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			ArbolEx_Mouse_BotonSoltado(_hWnd, &RC, Boton, cX, cY, Param);
			Repintar();
            return 0;
		}

		//! Función predefinida del mensaje WM_MOUSEMOVE.
		/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEMOVE.
				\fn			virtual LRESULT Evento_Mouse_Movimiento(const int cX, const int cY, const UINT wParam);
				\param[in]	cX		: Coordenada X del mouse.
				\param[in]	cY		: Coordenada Y del mouse.
				\param[in]	Param	: Teclas extendidas presionadas.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLArbolEx::Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param) {
			/*if (_MouseDentro == false) {
				TRACKMOUSEEVENT Trk;
				Trk.cbSize = sizeof(TRACKMOUSEEVENT);
				Trk.dwFlags = TME_LEAVE;
				Trk.hwndTrack = _hWnd;
				TrackMouseEvent(&Trk);
				_MouseDentro = true;
			}*/
			RECT RC;
			GetClientRect(_hWnd, &RC);
			ArbolEx_Mouse_Movimiento(_hWnd, &RC, cX, cY, Param);
			Repintar();
            return 0;
		}


		//! Función que recibe cuando el mouse se va del control
		/*!	Esta función es la encargada de procesar los mensajes WN_MOUSELEAVE.
				\fn			virtual LRESULT Evento_Mouse_Saliendo(void);
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLArbolEx::Evento_Mouse_Saliendo(void) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Mouse_Saliendo\n"));
			#endif
			_ArbolEx_NodoResaltado = NULL;
			_ArbolEx_ExpansorResaltado = NULL;
			_MouseDentro = false;
			BarraScrollEx_Mouse_Saliendo(_hWnd);
			Repintar(true);
            return 0;
		}

	    //! Función que enlaza el mensaje WM_TIMER con el ArbolEx.
        /*! Esta función enlaza el mensaje WM_TIMER con el ArbolEx.
		        \fn			LRESULT DWLArbolEx::Evento_Temporizador(const UINT cID);
		        \param[in]	cID : ID del temporizador.
		        \return		No devuelve nada.
				\remarks	Si re-emplazas esta funcion debes retornar 0.
        */
		LRESULT DWLArbolEx::Evento_Temporizador(const UINT cID) {
			DWLBarraScrollEx_Nucleo::BarraScrollEx_Evento_Temporizador(_hWnd, cID, ArbolEx_Estilos.PintarBorde);
/*			if (cID == DWL_TIMER_TOOLTIP) {
				if (Visible() == FALSE) return 0;
				if (_ArbolEx_TT_UltimoNodo == _ArbolEx_NodoResaltado) {
					if (GetTickCount() - _ArbolEx_TT_TiempoMS > DWL_TIEMPO_TOOLTIP && _ArbolEx_TT_UltimoNodo != NULL) {
						if (ArbolEx_ToolTip.hWnd() == NULL) ArbolEx_Evento_MostrarToolTip(_ArbolEx_TT_UltimoNodo);
					}
				}
				else {
					ArbolEx_ToolTip.Destruir();
					_ArbolEx_TT_UltimoNodo = _ArbolEx_NodoResaltado;
					_ArbolEx_TT_TiempoMS = GetTickCount();
				}
			}*/
            return 0;
		}


		//! Función que pinta todo el ArbolEx cuado se recibe un mensaje WM_PAINT.
		/*!	Esta función pinta el ArbolEx cuando se recibe un mensaje WM_PAINT.
				\fn			LRESULT Evento_Pintar(HDC hDC);
				\param[in]	hDC	: hDC donde se pintara todo el ArbolEx.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLArbolEx::Evento_Pintar(HDC hDC, PAINTSTRUCT &PS) {
			if (_hWnd == NULL) return 0;
			RECT R;
			GetClientRect(_hWnd, &R);
			ArbolEx_Pintar(hDC, &R, Foco());
            return 0;
		}

		//! Función predefinida del mensaje WM_KEYDOWN (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WM_KEYDOWN.
				\fn			virtual LRESULT Evento_Teclado_TeclaPresionada(const UINT Tecla, const UINT Repeticion, const UINT Param);
				\param[in]	Caracter   : Tecla virtual soltada.
				\param[in]	Repeticion : Repeticiones de la tecla
				\param[in]	Params	   : Teclas extendidas soltadas.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLArbolEx::Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Param) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Teclado_TeclaPresionada\n"));
			#endif
			ArbolEx_Teclado_TeclaPresionada(_hWnd, Caracter, Repeticion, Param);
			Repintar(true);
            return 0;
		}

		//! Función predefinida del mensaje WM_KEYUP (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WM_KEYUP.
				\fn			virtual LRESULT Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Param);
				\param[in]	Caracter   : Tecla virtual soltada.
				\param[in]	Repeticion : Repeticiones de la tecla
				\param[in]	Params	   : Teclas extendidas soltadas.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLArbolEx::Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Param) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Teclado_TeclaSoltada\n"));
			#endif
			ArbolEx_Teclado_TeclaSoltada(_hWnd, Caracter, Repeticion, Param);
            return 0;
		}

		//! Función que procesa el mensaje WM_KILLFOCUS
		/*! Esta funcion es la encargada de procesar el mensaje WM_KILLFOCUS
				\fn			virtual LRESULT Evento_Foco_Perdido(HWND NuevoFoco);
				\param[in]	NuevoFoco	: HWND de la ventana que recibira el foco despues de esta.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLArbolEx::Evento_Foco_Perdido(HWND NuevoFoco) {
			int i;
			for (i = 0; i < 256; i++) _ArbolEx_Teclado[i] = false;
			_ArbolEx_NodoPresionado = 0;
			PostMessage(GetParent(_hWnd), DWL_ARBOLEX_FOCO_PERDIDO, ID(), 0);
            return 0;
		}

		//! Función que procesa el mensaje WM_SETFOCUS
		/*! Esta funcion es la encargada de procesar el mensaje WM_SETFOCUS
				\fn			virtual LRESULT Evento_Foco_Obtenido(HWND FocoAnterior);
				\param[in]	FocoAnterior	: HWND de la ventana que tenia el foco antes que esta.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLArbolEx::Evento_Foco_Obtenido(HWND FocoAnterior) {
			CancelarLabelEdit();
			PostMessage(GetParent(_hWnd), DWL_ARBOLEX_FOCO_OBTENIDO, ID(), 0);
            return 0;
		}

		//! Esqueleto para los mensajes del ArbolEx.
		/*! Esta función es el esqueleto para los mensajes del ArbolEx.
				\fn			LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
				\param[in]	uMsg	: Mensaje.
				\param[in]	wParam	: Parametro1.
				\param[in]	lParam	: Parametro2.
				\return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
				\remarks	Esta función es el esqueleto del ArbolEx por donde pasaran todos sus mensajes.
		*/
		LRESULT CALLBACK DWLArbolEx::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
			switch (uMsg) {
				case DWL_ARBOLEX_TECLADO_INTRO :
					TerminarLabelEdit();
					break;
				case DWL_ARBOLEX_TECLADO_SOLTADO :
					if (wParam == VK_ESCAPE) CancelarLabelEdit();
					break;

				case WM_NOTIFY			: // LabelEdit
					switch (((LPNMHDR)lParam)->code) {
						case NM_KILLFOCUS :
							CancelarLabelEdit();
							break;
					}
					break;
				case WM_CTLCOLOREDIT :
				case WM_CTLCOLORSTATIC :
					DWLArbolEx_ColoresNodo *Col;
					if (_ArbolEx_eNodo->_Colores != NULL)   Col = _ArbolEx_eNodo->_Colores;
					else									Col = &ArbolEx_Estilos.Colores.ColoresNodo;
					SetTextColor((HDC)wParam, Col->TextoNormal());
					SetBkColor((HDC)wParam, Col->FondoNormal());
					return (LRESULT)_ArbolEx_BrochaFondoEdit;

		/*		case WM_VSCROLL			: // ScrollBar
					switch (static_cast<int>(LOWORD(wParam))) {
						case SB_BOTTOM :
							if (_BarraScrollEx_MaximoV > _BarraScrollEx_PaginaV) {
								_BarraScrollEx_PosActualV = _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV;
								_PosMovimientoScrollV = _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV;
							}
							break;
		//				case SB_ENDSCROLL : // no implementare aixo de moment... (acabar el scroll... perke?)
		//					break;
						case SB_LINEDOWN :
							if (_PosMovimientoScrollV < (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) {
								_BarraScrollEx_PosActualV ++;
								_PosMovimientoScrollV ++;
							}
							break;
						case SB_LINEUP :
							if (_PosMovimientoScrollV > 0) {
								_BarraScrollEx_PosActualV --;
								_PosMovimientoScrollV --;
							}
							break;
						case SB_PAGEDOWN :
							if (_BarraScrollEx_MaximoV > _BarraScrollEx_PaginaV) {
								if (_BarraScrollEx_PosActualV + _BarraScrollEx_PaginaV < (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV))	_BarraScrollEx_PosActualV += _BarraScrollEx_PaginaV;
								else														_BarraScrollEx_PosActualV = (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
								_PosMovimientoScrollV = _BarraScrollEx_PosActualV;
							}
							break;
						case SB_PAGEUP :
							if (_BarraScrollEx_MaximoV > _BarraScrollEx_PaginaV) {
								if (_BarraScrollEx_PosActualV - _BarraScrollEx_PaginaV > 0) _BarraScrollEx_PosActualV -= _BarraScrollEx_PaginaV;
								else                                  _BarraScrollEx_PosActualV = 0;
								_PosMovimientoScrollV = _BarraScrollEx_PosActualV;
							}
							break;
						case SB_THUMBPOSITION :
							_PosMovimientoScrollV = static_cast<int>(HIWORD(wParam));
							_BarraScrollEx_PosActualV = static_cast<int>(HIWORD(wParam));
							break;
						case SB_TOP :
							_BarraScrollEx_PosActualV = 0;
							_PosMovimientoScrollV = 0;
							break;
					}
					Repintar();
		//			_ScrollV->ReAjustarMedidas();
		//			_ScrollV->Repintar(); // sha de mirar la posMovimiento si cambia per pintar..
					break;*/
			}
			return DWLControlEx::GestorMensajes(uMsg, wParam, lParam);
		}







	}
} // Fin DWL


// Mirar priority_queue<NodoArbol *,std::vector<NodoArbol *>, NodoArbol::compare> Nodo;   // greetings to ethernet

//struct compare
// 		{
//
// 			bool operator()(Node*& u, Node*& v)
// 			{
// 				if(u->weith() > v->weith())
// 					return true; //para que open.Top sea el menor
// 				return false;
// 			}
// 		};



// Falta el puto shift AV y Repag
