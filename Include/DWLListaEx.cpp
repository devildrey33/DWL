//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DWLListaEx.h																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Descripción :																																//
//					Este control simula un Listview de windows, con algunas innovaciones, ademas de ser totalmente configurable de apariencia.	//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Este archivo contiene varias clases descritas a continuacion :																				//
// - DWLListaEx_Colores				:	Clase que enlaza los colores a la configuracion del skin por defecto									//
//										Puedes modificar cualquier color de esta clase, solo deberas repintar el arbol al terminar.				//
//																																				//
// - DWLListaEx_ColoresItem			:	Clase que enlaza los colores del Item a la configuracion skin por defecto.								//
//																																				//
// - DWLListaEx_ColoresColumna		:	Clase que enlaza los colores de la columna a la configuracion skin por defecto.							//
//																																				//
// - DWLListaEx_ParametrosClick		:	Clase utilizada internamente para pasar los datos de un click a la ventana padre.						//
//																																				//
// - DWLListaEx_TerminarLabelEdit	:	Clase utilizada internamente para pasar los datos de una edicion a la ventana padre.					//
//																																				//
// - DWLListaEx_Item				:	Clase que contiene los datos de un item (Puede ser heredada).											//
//																																				//
// - DWLListaEx_DatosSubItem		:	Clase que contiene los datos de un subitem.																//
//																																				//
// - DWLListaEx_Columna				:	Clase que contiene los datos de una columna (Puede ser heredada).										//
//																																				//
// - DWLListaEx_Nucleo				:	Clase que contiene las Funciónes basicas para pintar y controlar los eventos de la lista.				//
//										Esta clase se ha creado de forma que puede compartir un control con otra clase, aunque es poco probable	//
//										que se requiera compartir un arbol con otro control, es muy interesante la posibilidad de poder pintar	//
//										el control en cualquier hDC.																			//
//																																				//
// - DWLListaEx						:	Clase que hereda de DWLListaEx_Nucleo y lo enlaza a un control para el solo.							//
//										Esta clase es la que deberiamos usar para crear una lista estandar sin complicaciones.					//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Archivo creado por devildrey33 el dia 06/12/2004	para http://www.devildrey33.es																//
// Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :		//
//  http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																		//
//  http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)																//
//  http://www.softcatala.cat/wiki/GPL3		 (Catalá, traduccion no oficial)																	//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Version 0.95																																	//
// Ultima modificación : 12/11/2009																												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "DWLListaEx.h"
#include "DWLListaIconos.h"
#include "DWLGraficos.h"


#define DWL_NOMBRE_CLASE_DWLLISTAEX    TEXT("DWL::ControlesEx::DWLListaEx")


namespace DWL {
	namespace ControlesEx {

		//! Constructor.
		/*!	Constructor por defecto.
				\fn		DWLListaEx(void);
				\return	No devuelve nada.
		*/
        DWLListaEx::DWLListaEx(void) : DWLControlEx(), DWLListaEx_Nucleo() {
            RegistrarClase(DWL_NOMBRE_CLASE_DWLLISTAEX, 0, 0, _GestorMensajes);
        };

		//! Destructor.
		/*!	Destructor.
				\fn		~DWLListaEx(void);
				\return	No devuelve nada.
		*/
		DWLListaEx::~DWLListaEx(void) {
			Destruir();
		}

		//! Función que retorna si esta ventana tiene el raton encima.
		/*!	Esta funcion devuelve si esta ventana tiene el raton encima.
				\fn			virtual bool Foco(void);
				\return		Devuelve true si el raton esta encima del control, false en caso contrario.
		*/
        bool DWLListaEx::Foco(void) {
			bool TieneFoco = false;
			if (_ListaEx_ItemPresionado != 0) return true;
			POINT Pt;
			GetCursorPos(&Pt);
			if (_hWnd == WindowFromPoint(Pt)) { // Tiene el foco del raton
				TieneFoco = true;
			}
			return TieneFoco;
		};

		//! Función que retorna si la ListaEx esta activada.
		/*!	Esta funcion devuelve si la ListaEx esta activada.
				\fn			BOOL Activado(void);
				\return		Devuelve TRUE si la ListaEx esta activada, FALSE en caso contrario.
		*/
		BOOL DWLListaEx::Activado(void) {
			return _BarraScrollEx_Activado;
		}


	    //! Función para activar / desactivar la ListaEx.
	    /*!	Esta funcion activa / desactiva la ListaEx.
			    \fn			inline virtual void Activado(const bool nActivar);
			    \param[in]	nActivar	: Parametro en el que especificaremos si queremos activar o desactivar el ArbolEx.
			    \return		No devuelve nada.
	    */
		void DWLListaEx::Activado(const bool nActivar) {
//			_ListaEx_VentanaActivada = static_cast<BOOL>(nActivar);
			BarraScrollEx_Activado(nActivar);
			Repintar(true);
		}


		//! Función que destruye esta ListaEx.
		/*!	Esta funcion destruye la ListaEx.
				\fn			BOOL Destruir(void);
				\return		Devuelve TRUE si la operacion se completo, FALSE en caso contrario.
		*/
		BOOL DWLListaEx::Destruir(void) {
			if (_ListaEx_FondoDC != NULL) {
				SelectObject(_ListaEx_FondoDC, _ListaEx_VFuente);
				SelectObject(_ListaEx_FondoDC, _ListaEx_Viejo);
				DeleteObject(_ListaEx_Bmp);
				DeleteDC(_ListaEx_FondoDC);
				_ListaEx_FondoDC = NULL;
			}
			BOOL R = DestroyWindow(_hWnd);
			_hWnd = NULL;
			return R;
		}
 
	    //! Función que crea la ListaEx.
	    /*!	Esta funcion crea la ListaEx.
			    \fn			HWND CrearListaEx(const long Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const bool nPintarBorde = true, const int nTipoVisionado = DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL);
			    \param[in]	Estilos			: Estilos para la ListaEx (WS_CHILD | WS_VISIBLE).
			    \param[in]	hWndParent		: HWND del control que sera el padre de la ListaEx.
			    \param[in]	cX				: Posicion X.
			    \param[in]	cY				: Posicion Y.
			    \param[in]	cAncho			: Ancho de la ListaEx.
			    \param[in]	cAlto			: Alto de la ListaEx.
			    \param[in]	cID				: ID de la ListaEx.
			    \param[in]	cPintarBorde	: Parametro que indica si se tiene que pintar el borde de la ListaEx.
			    \param[in]	nTipoVisionado	: Tipo de visionado que puede ser : DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL o DWL_LISTAEX_FILAS_HORIZONTAL.
			    \return		Devuelve el HWND de la ListaEx. En caso de error devolvera NULL.
	    */
		HWND DWLListaEx::CrearListaEx(const long Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const bool nPintarBorde, const int TipoVisionado) {
//			int  TotalLineas = (static_cast<int>(static_cast<float>(cAlto) / static_cast<float>(_ListaEx_AltoLinea)));
			CrearControl(hWndParent, DWL_NOMBRE_CLASE_DWLLISTAEX, Estilos, 0, cX, cY, cAncho, cAlto, cID);
			_ListaEx_ID = cID;

			ListaEx_Estilos.PintarBorde = nPintarBorde;
			if (ListaEx_Estilos.PintarBorde == true) {
				HRGN Region = CreateRoundRectRgn(0, 0, cAncho + 1, cAlto + 1, 2, 2);
				AsignarRegion(Region, false);
			}

			ListaEx_Estilos.ModoVisionado = TipoVisionado;

			RECT RectaFondo = { 0, 0, cAncho, cAlto };

			BarraScrollEx_CrearV(DWL_BARRASCROLLEX_AUTOMATICO, 0, cAlto, 0);
			BarraScrollEx_CrearH(DWL_BARRASCROLLEX_AUTOMATICO, 0, cAncho, 0);
			BarraScrollEx_PosicionarScrolls(_hWnd, &RectaFondo, false, ListaEx_Estilos.PintarBorde);

			_ListaEx_ItemMarcado			= NULL;
			_ListaEx_ItemPresionado			= NULL;
			_ListaEx_SubItemPresionado		= -1;
			_ListaEx_ItemResaltado			= NULL;
			_ListaEx_UItemResaltado			= NULL;
			_ListaEx_SubItemResaltado		= -1;
			_ListaEx_ItemShifteado			= NULL;
			_ListaEx_UltimoClick			= 0;

			HDC	hDC		= GetDC(NULL);
			_ListaEx_FondoDC    = CreateCompatibleDC(hDC);
			_ListaEx_Bmp        = CreateCompatibleBitmap(hDC, cAncho, cAlto + _ListaEx_AltoLinea);
			_ListaEx_Viejo      = static_cast<HBITMAP>(SelectObject(_ListaEx_FondoDC, _ListaEx_Bmp));
			_ListaEx_VFuente    = static_cast<HFONT>(SelectObject(_ListaEx_FondoDC, ListaEx_Estilos.Fuentes.Normal()));
			ReleaseDC(NULL, hDC);
			SetBkMode(_ListaEx_FondoDC, TRANSPARENT);
			ListaEx_FinAgregarItems(_hWnd);
			ListaEx_Evento_Pintar_Fondo(_ListaEx_FondoDC, &RectaFondo);
			_BarraScrollEx_PaginaH = cAncho;
			return _hWnd;
		}

	    //! Función que conecta la ListaEx de un dialogo.
	    /*!	Esta funcion conecta la ListaEx de un dialogo.
			    \fn			HWND ConectarListaEx(HWND hWndParent, const int cID, const bool nPintarBorde = true, const int nTipoVisionado = DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL);
			    \param[in]	hWndParent		: HWND del control que sera el padre de la ListaEx.
			    \param[in]	cID				: ID de la ListaEx.
			    \param[in]	cPintarBorde	: Parametro que indica si se tiene que pintar el borde de la ListaEx.
			    \param[in]	nTipoVisionado	: Tipo de visionado que puede ser : DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL o DWL_LISTAEX_FILAS_HORIZONTAL.
			    \return		Devuelve el HWND de la ListaEx. En caso de error devolvera NULL.
                \remarks    Esta función solo debe usarse con controles que se creen durante la creación del dialogo, si esta clase no pertenece a un dialogo, o se va a crear dinamicamente, no debes usar esta función.
	    */
        HWND DWLListaEx::ConectarListaEx(HWND hWndParent, const int cID, const bool nPintarBorde, const int nTipoVisionado) {
            _ConectarControl(cID, hWndParent);
            RECT RC;
            GetClientRect(_hWnd, &RC);

            int  TotalLineas = (static_cast<int>(static_cast<float>(RC.bottom) / static_cast<float>(_ListaEx_AltoLinea)));
			ListaEx_Estilos.PintarBorde = nPintarBorde;
			if (ListaEx_Estilos.PintarBorde == true) {
                HRGN Region = CreateRoundRectRgn(0, 0, RC.right +1, RC.bottom +1, 2, 2);
				AsignarRegion(Region, false);
			}

			ListaEx_Estilos.ModoVisionado = nTipoVisionado;

            BarraScrollEx_CrearV(DWL_BARRASCROLLEX_AUTOMATICO, 0, RC.bottom, 0);
            BarraScrollEx_CrearH(DWL_BARRASCROLLEX_AUTOMATICO, 0, RC.right, 0);
			BarraScrollEx_PosicionarScrolls(_hWnd, &RC, false, ListaEx_Estilos.PintarBorde);

			_ListaEx_ItemMarcado			= NULL;
			_ListaEx_ItemPresionado			= NULL;
			_ListaEx_SubItemPresionado		= -1;
			_ListaEx_ItemResaltado			= NULL;
			_ListaEx_UItemResaltado			= NULL;
			_ListaEx_SubItemResaltado		= -1;
			_ListaEx_ItemShifteado			= NULL;
			_ListaEx_UltimoClick			= 0;

			HDC	hDC		= GetDC(NULL);
			_ListaEx_FondoDC    = CreateCompatibleDC(hDC);
            _ListaEx_Bmp        = CreateCompatibleBitmap(hDC, RC.right, RC.bottom + _ListaEx_AltoLinea);
			_ListaEx_Viejo      = static_cast<HBITMAP>(SelectObject(_ListaEx_FondoDC, _ListaEx_Bmp));
			_ListaEx_VFuente    = static_cast<HFONT>(SelectObject(_ListaEx_FondoDC, ListaEx_Estilos.Fuentes.Normal()));
			ReleaseDC(NULL, hDC);
			SetBkMode(_ListaEx_FondoDC, TRANSPARENT);
			ListaEx_FinAgregarItems(_hWnd);
			ListaEx_Evento_Pintar_Fondo(_ListaEx_FondoDC, &RC);
            _BarraScrollEx_PaginaH = RC.right;
			return _hWnd;
        }


		//! Función para mover la ListaEx a la posicion y el tamaño especificados.
		/*!	Esta función mueve la ListaEx a la posicion y tamaño especificados.
				\fn			void Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = true);
				\param[in]	cX			: Nueva posicion X para la ListaEx.
				\param[in]	cY			: Nueva posicion Y para la ListaEx.
				\param[in]	cAncho		: Nuevo ancho para la ListaEx.
				\param[in]	cAlto		: Nueva altura para la ListaEx.
				\param[in]	cRepintar	: True para repintar el control, false para dejarlo sin repintar.
				\return		No devuelve nada.
		*/
		void DWLListaEx::Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar) {

			if (ListaEx_Estilos.PintarBorde == true) {
				HRGN Region = CreateRoundRectRgn(0, 0, cAncho + 1, cAlto + 1, 2, 2);
				AsignarRegion(Region, false);
			}

			MoveWindow(_hWnd, cX, cY, cAncho, cAlto, false);
			ListaEx_FinAgregarItems(_hWnd);

			if (_ListaEx_FondoDC != NULL) {
				SelectObject(_ListaEx_FondoDC, _ListaEx_VFuente);
				SelectObject(_ListaEx_FondoDC, _ListaEx_Viejo);
				DeleteObject(_ListaEx_Bmp);
				DeleteDC(_ListaEx_FondoDC);
				_ListaEx_FondoDC = NULL;
			}
			HDC	hDC		= GetDC(NULL);
			_ListaEx_FondoDC    = CreateCompatibleDC(hDC);
			_ListaEx_Bmp        = CreateCompatibleBitmap(hDC, cAncho, cAlto + _ListaEx_AltoLinea);
			_ListaEx_Viejo      = static_cast<HBITMAP>(SelectObject(_ListaEx_FondoDC, _ListaEx_Bmp));
			_ListaEx_VFuente    = static_cast<HFONT>(SelectObject(_ListaEx_FondoDC, ListaEx_Estilos.Fuentes.Normal()));

			ReleaseDC(NULL, hDC);
			SetBkMode(_ListaEx_FondoDC, TRANSPARENT);
			RECT RectaFondo = { 0, 0, cAncho, cAlto };

			ListaEx_Evento_Pintar_Fondo(_ListaEx_FondoDC, &RectaFondo);
			if (cRepintar == true) Repintar(true);
		}

		//! Función que pinta toda la ListaEx cuado se recibe un mensaje WM_PAINT.
		/*!	Esta función pinta la ListaEx cuando se recibe un mensaje WM_PAINT.
				\fn			LRESULT Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);
				\param[in]	hDC	: hDC donde se pintara toda la ListaEx.
				\param[in]	PS	: Estructura con informacion sobre el pintado.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLListaEx::Evento_Pintar(HDC hDC, PAINTSTRUCT &PS) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			ListaEx_Pintar(hDC, &RC, Foco());
            return 0;
		}

		//! Función predefinida del mensaje WM_KEYUP (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WM_KEYUP.
				\fn			virtual LRESULT Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Params);
				\param[in]	Caracter   : Tecla virtual presionada.
				\param[in]	Repeticion : Repeticion de la tecla.
				\param[in]	Param	   : Teclas extendidas presionadas.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
        LRESULT DWLListaEx::Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Params) {
			ListaEx_Teclado_TeclaSoltada(_hWnd, Caracter, Repeticion, Params);
			Repintar(true);
            return 0;
		}


		//! Función predefinida del mensaje WM_KEYDOWN (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WM_KEYDOWN.
				\fn			virtual LRESULT Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Param);
				\param[in]	Caracter   : Tecla virtual presionada.
				\param[in]	Repeticion : Repeticion de la tecla.
				\param[in]	Param	   : Teclas extendidas presionadas.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLListaEx::Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Params) {
			ListaEx_Teclado_TeclaPresionada(_hWnd, Caracter, Repeticion, Params);
			Repintar(true);
            return 0;
		}

		//! Función predefinida del mensaje WM_MOUSEMOVE.
		/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEMOVE.
				\fn			virtual LRESULT Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);
				\param[in]	cX		: Coordenada X del mouse.
				\param[in]	cY		: Coordenada Y del mouse.
				\param[in]	Param	: Teclas extendidas presionadas.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLListaEx::Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			ListaEx_Mouse_Movimiento(_hWnd, &RC, cX, cY, Param);
			Repintar();
            return 0;
		}



		//! Función predefinida del mensaje WM_*BUTTONUP (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONUP.
				\fn			virtual LRESULT Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	Boton	: Boton presionado.
				\param[in]	cX		: Coordenada X del mouse.
				\param[in]	cY		: Coordenada Y del mouse.
				\param[in]	wParam	: Teclas extendidas presionadas.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLListaEx::Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			ListaEx_Mouse_BotonSoltado(_hWnd, &RC, Boton, cX, cY, Param);
			Repintar(true);
            return 0;
		}


		//! Función predefinida del mensaje WM_*BUTTONDOWN (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONDOWN.
				\fn			virtual LRESULT Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param)
				\param[in]	Boton	: Boton presionado.
				\param[in]	cX		: Coordenada X del mouse.
				\param[in]	cY		: Coordenada Y del mouse.
				\param[in]  Param	: Teclas extendidas presionadas.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLListaEx::Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			ListaEx_Mouse_BotonPresionado(_hWnd, &RC, Boton, cX, cY, Param);
			Repintar();
            return 0;
		}


		//! Función que recibe cuando el mouse se va del control
		/*!	Esta función es la encargada de procesar los mensajes WN_MOUSELEAVE.
				\fn			virtual LRESULT Evento_Mouse_Saliendo(void);
				\return		No devuelve nada.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLListaEx::Evento_Mouse_Saliendo(void) {
			_ListaEx_ItemResaltado = NULL;
			_ListaEx_SubItemResaltado = -1;
			for (size_t i = 0; i < _ListaEx_Columnas.size(); i++) _ListaEx_Columnas[i]->_Estado = DWL_LISTAEX_ESTADO_NORMAL;
			BarraScrollEx_Mouse_Saliendo(_hWnd);
//			DWLControlEx::Evento_Mouse_Saliendo();
			Repintar(true);
            return 0;
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
		LRESULT DWLListaEx::Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey) {
			#if defined DWL_LISTAEX_DEBUG
				DWL::DWLDebug::ImprimirDebug(TEXT("DWLListaEx::Evento_Mouse_Rueda VirtKey %d | Delta %d | cX %d | cY %d\n"), VirtKey, Delta, cX, cY);
			#endif/*
			if (ListaEx_Estilos.ModoVisionado == DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL) {
				if ((_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) > 0 && _BarraScrollEx_ValorV < (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) +1) {
					if (Delta > 0) { // Hacia arriba
						_BarraScrollEx_ValorV -= 3;
						if (_BarraScrollEx_ValorV < 0) BarraScrollEx_ValorV(0);

					}
					else { // Hacia abajo
						_BarraScrollEx_ValorV += 3;
						if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
					}
//					_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;

					BarraScrollEx_CalcularScrollV();
					BarraScrollEx_CalcularScrollH();
				}
			}
			if (ListaEx_Estilos.ModoVisionado == DWL_LISTAEX_FILAS_HORIZONTAL) {
			}
			_ListaEx_ItemResaltado = NULL;
			Repintar(true);
            return 0;*/
			return ListaEx_Mouse_Rueda(Delta, cX, cY, VirtKey);
		}

		//! Función que repinta todo la ListaEx.
		/*!	Esta función repinta todo la ListaEx incluyendo barras de scroll y botones extra.
				\fn			void Repintar(const bool Forzar = false);
				\param[in]	Forzar : True para forzar el repintado, false para que la funcion decida si repintar.
				\return		No devuelve nada.
				\remarks	Cuando Forzar es false, esta función mira si ha cambiado algun estado interno,
							y de ser asi repinta el control, en caso contrario no hace nada.
		*/
		void DWLListaEx::Repintar(const bool Forzar) {
			if (_ListaEx_Editando == true) return;
			bool P = Forzar;
			if (P == false) {
				if (_BarraScrollEx_UValorV != _BarraScrollEx_ValorV)	P = true;
				if (_ListaEx_ItemResaltado != _ListaEx_UItemResaltado)	P = true;
				bool FocoActual = Foco();
				if (_ListaEx_FocoRaton != FocoActual) {
					_ListaEx_FocoRaton = FocoActual;
					P = true;
				}
			}
			_ListaEx_UItemResaltado = _ListaEx_ItemResaltado;
			_BarraScrollEx_UValorV = _BarraScrollEx_ValorV;
			if (P == true) {
				RECT RectaFondo;
				GetClientRect(_hWnd, &RectaFondo);
				ListaEx_Evento_Pintar_Fondo(_ListaEx_FondoDC, &RectaFondo);
                PAINTSTRUCT PS;
				HDC hDC = GetDC(_hWnd);
				Evento_Pintar(hDC, PS);
				ReleaseDC(_hWnd, hDC);
			}
		}

		//! Función que procesa el mensaje WM_KILLFOCUS
		/*! Esta funcion es la encargada de procesar el mensaje WM_KILLFOCUS
				\fn			virtual LRESULT Evento_Foco_Perdido(HWND NuevoFoco);
				\param[in]	NuevoFoco	: HWND de la ventana que recibira el foco despues de esta.
				\return		No devuelve nada.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLListaEx::Evento_Foco_Perdido(HWND NuevoFoco) {
			for (int i = 0; i < 256; i++) _ListaEx_Teclado[i] = false;
			_ListaEx_Presionado = false;
			_ListaEx_ItemPresionado = NULL;
			PostMessage(GetParent(_hWnd), DWL_LISTAEX_FOCO_PERDIDO, ID(), 0);
            return 0;
		}

		//! Función que procesa el mensaje WM_SETFOCUS
		/*! Esta funcion es la encargada de procesar el mensaje WM_SETFOCUS
				\fn			virtual LRESULT Evento_Foco_Obtenido(HWND FocoAnterior);
				\param[in]	FocoAnterior	: HWND de la ventana que tenia el foco antes que esta.
				\return		No devuelve nada.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLListaEx::Evento_Foco_Obtenido(HWND FocoAnterior) {
			ListaEx_CancelarLabelEdit(_hWnd);
			PostMessage(GetParent(_hWnd), DWL_LISTAEX_FOCO_OBTENIDO, ID(), 0);
            return 0;
		}

		//! Función que enlaza el mensaje WM_TIMER con la ListaEx.
		/*! Esta función enlaza el mensaje WM_TIMER con la ListaEx.
				\fn			virtual LRESULT Evento_Temporizador(const UINTs cID);
				\param[in]	cID : ID del temporizador.
				\return		No devuelve nada.
		*/
		LRESULT DWLListaEx::Evento_Temporizador(const UINT cID) {
			BarraScrollEx_Evento_Temporizador(_hWnd, cID, ListaEx_Estilos.PintarBorde);
/*			if (cID == DWL_TIMER_TOOLTIP) {
				if (Visible() == FALSE) return 0;
				if (_ListaEx_TT_UltimoItem == _ListaEx_ItemResaltado) {
					if (GetTickCount() - _ListaEx_TT_TiempoMS > DWL_TIEMPO_TOOLTIP && _ListaEx_TT_UltimoItem != NULL) {
						if (ListaEx_ToolTip.hWnd() == NULL) ListaEx_Evento_MostrarToolTip(_ListaEx_TT_UltimoItem);
					}
				}
				else {
					ListaEx_ToolTip.Destruir();
					_ListaEx_TT_UltimoItem = _ListaEx_ItemResaltado;
					_ListaEx_TT_TiempoMS = GetTickCount();
				}
			}*/
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
		LRESULT CALLBACK DWLListaEx::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
			switch (uMsg) {

				case DWL_LISTAEX_TECLADO_INTRO :
					TerminarLabelEdit();
					break;
				case DWL_LISTAEX_TECLADO_SOLTADO :
					if (wParam == VK_ESCAPE) CancelarLabelEdit();
					break;

				case WM_NOTIFY			:  // LabelEdit
					switch (((LPNMHDR)lParam)->code) {
		/*				case NM_KEYDOWN :
							switch(((LPNMKEY)lParam)->nVKey) {
								case VK_RETURN :
									TerminarLabelEdit();
									break;
								case VK_ESCAPE :
									CancelarLabelEdit();
									break;
							}
							break;*/
						case NM_KILLFOCUS :
							CancelarLabelEdit();
							break;
					}
					break;
				case WM_CTLCOLOREDIT :
				case WM_CTLCOLORSTATIC :
					if (_ListaEx_eItem->_SubItems[_ListaEx_eSubItem]->_Colores != NULL) SetTextColor((HDC)wParam, _ListaEx_eItem->_SubItems[_ListaEx_eSubItem]->_Colores->TextoNormal());
					else																SetTextColor((HDC)wParam, ListaEx_Estilos.Colores.ColoresItem.TextoNormal());
					SetBkMode((HDC)wParam, TRANSPARENT);
					return (LRESULT)_ListaEx_BrochaFondoEdit;

				case WM_VSCROLL			: // ScrollBar
					switch (static_cast<int>(LOWORD(wParam))) {
						case SB_BOTTOM :
							if (_BarraScrollEx_MaximoV > _BarraScrollEx_PaginaV) {
//								_BarraScrollEx_PosActualV = _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV;
								BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
							}
							break;
		//				case SB_ENDSCROLL : // no implementare aixo de moment... (acabar el scroll... perke?)
		//					break;
						case SB_LINEDOWN :
							if (_BarraScrollEx_ValorV < (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) {
								_BarraScrollEx_PosActualV ++;
								_BarraScrollEx_ValorV ++;
							}
							break;
						case SB_LINEUP :
							if (_BarraScrollEx_ValorV > 0) {
								_BarraScrollEx_PosActualV --;
								_BarraScrollEx_ValorV --;
							}
							break;
						case SB_PAGEDOWN :
							if (_BarraScrollEx_MaximoV > _BarraScrollEx_PaginaV) {
								if (_BarraScrollEx_PosActualV + _BarraScrollEx_PaginaV < (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) _BarraScrollEx_PosActualV += _BarraScrollEx_PaginaV;
								else												  _BarraScrollEx_PosActualV = (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
								_BarraScrollEx_ValorV = _BarraScrollEx_PosActualV;
							}
							break;
						case SB_PAGEUP :
							if (_BarraScrollEx_MaximoV > _BarraScrollEx_PaginaV) {
								if (_BarraScrollEx_PosActualV - _BarraScrollEx_PaginaV > 0) _BarraScrollEx_PosActualV -= _BarraScrollEx_PaginaV;
								else                                _BarraScrollEx_PosActualV = 0;
								_BarraScrollEx_ValorV = _BarraScrollEx_PosActualV;
							}
							break;
						case SB_THUMBPOSITION :
							_BarraScrollEx_ValorV = static_cast<int>(HIWORD(wParam));
							_BarraScrollEx_PosActualV = static_cast<int>(HIWORD(wParam));
							break;
		/*				case SB_THUMBTRACK :
							_BarraScrollEx_ValorV = static_cast<int>(HIWORD(wParam));
							break;*/
						case SB_TOP :
							_BarraScrollEx_PosActualV = 0;
							_BarraScrollEx_ValorV = 0;
							break;
					}
					BarraScrollEx_CalcularScrollV();
					BarraScrollEx_CalcularScrollH();
					Repintar();
					break;
			}


			return DWLControlEx::GestorMensajes(uMsg, wParam, lParam);
		}


















	}
}


// Falta acabar de millorar el Shift AV y Repag
