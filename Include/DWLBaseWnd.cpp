#include "DWLBaseWnd.h"

namespace DWL {
    namespace Ventanas {
        namespace Base {

            //! Constructor.
		    /*! Constructor.
				    \fn			DWLBaseWnd(void);
				    \return		No devuelve nada.
		    */
            DWLBaseWnd::DWLBaseWnd(void) : _hWnd(NULL) {
            }

		    //! Destructor.
		    /*! Destructor.
				    \fn		   ~DWLBaseWnd(void);
				    \return		No devuelve nada.
		    */
            DWLBaseWnd::~DWLBaseWnd(void) {
//                Destruir();
            }

		    //! Función para mostrar / ocultar la ventana / control.
		    /*! Esta función muestra / oculta la ventana / control.
				    \fn			void Visible(const bool nMostrar);
				    \param[in]	nMostrar : True para mostrar la ventana / control, false para ocultarlo.
				    \return		No devuelve nada.
		    */
            void DWLBaseWnd::Visible(const bool nMostrar) {
                ShowWindow(_hWnd, (nMostrar == true) ? SW_SHOW : SW_HIDE);
            };


		    //! Función que retorna si la ventana / control es visible.
		    /*!	Esta funcion devuelve si la ventana / control es visible.
				    \fn			BOOL Visible(void);
				    \return		Devuelve TRUE si la ventana / control es visible, FALSE en caso contrario.
		    */
            BOOL DWLBaseWnd::Visible(void) {
                return static_cast<BOOL>(IsWindowVisible(_hWnd));
            };

		    //! Función para activar / desactivar la ventana / control.
		    /*!	Esta función activa / desactiva la ventana / control.
				    \fn			void Activado(const bool nActivar);
				    \param[in]	nActivar	: Parametro en el que especificaremos si queremos activar o desactivar la ventana / control.
				    \return		No devuelve nada.
		    */
            void DWLBaseWnd::Activado(const bool nActivar) {
                EnableWindow(_hWnd, nActivar);
		    };

		    //! Función que retorna si la ventana / control esta activado.
		    /*!	Esta funcion devuelve si la ventana / control esta activado.
				    \fn			virtual BOOL Activado(void);
				    \return		Devuelve TRUE si la ventana / control esta activado, FALSE en caso contrario.
		    */
		    BOOL DWLBaseWnd::Activado(void) {
				return static_cast<BOOL>(IsWindowEnabled(_hWnd));
			};

		    //! Función que asigna el foco a esta ventana / control.
		    /*!	Esta funcion asigna el foco a esta ventana / control.
				    \fn			inline virtual void AsignarFoco(void);
				    \return		No devuelve nada.
		    */
            void DWLBaseWnd::AsignarFoco(void) {
				SetFocus(_hWnd);
		    };

		    //! Función que retorna si esta ventana /control tiene el raton encima.
		    /*!	Esta funcion devuelve si esta ventana /control tiene el raton encima.
				    \fn			virtual bool Foco(void);
				    \return		Devuelve true si el raton esta encima del control / ventana, false en caso contrario.
		    */
            bool DWLBaseWnd::Foco(void) {
			    bool TieneFoco = false;
			    POINT Pt;
			    GetCursorPos(&Pt);
			    if (_hWnd == WindowFromPoint(Pt)) { // Tiene el foco del raton
				    TieneFoco = true;
			    }
			    return TieneFoco;
		    };

		    //! Función que asigna una region a esta ventana / control.
		    /*!	Esta funcion asigna una region a esta ventana / control.
				    \fn			inline virtual int AsignarRegion(HRGN nRegion, const BOOL nRepintar = true);
				    \param[in]	nRegion		: Region que queremos asignar a esta ventana / control.
				    \param[in]	nRepintar	: Valor en el que especificamos si se debe repintar la ventana / control.
				    \return		Devuelve 0 si la funcion ha fallado, cualquier otro numero para advertir que se ha asignado la region correctamente.
		    */
		    int DWLBaseWnd::AsignarRegion(HRGN nRegion, const BOOL nRepintar) {
			    return SetWindowRgn(_hWnd, nRegion, nRepintar);
		    };

		    //! Función que retorna el identificador de ventana HWND.
		    /*!	Esta funcion devuelve el identificador de ventana HWND.
				    \fn			inline HWND hWnd(void);
				    \return		Devuelve el HWND para esta ventana / control.
		    */
		    HWND DWLBaseWnd::hWnd(void) {
			    return _hWnd;
		    };

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
            void DWLBaseWnd::Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar) {
                MoveWindow(_hWnd, cX, cY, cAncho, cAlto, cRepintar);
		    };

		    //! Función para crear un temporizador en esta ventana / control.
		    /*!	Esta función crea un temporizador en esta ventana / control.
				    \fn			inline void CrearTemporizador(const unsigned int nID, const unsigned int nMiliSegundos);
				    \param[in]	nID				: ID para el temporizador.
				    \param[in]	nMiliSegundos	: Tiempo en milisegundos que pasara hasta que salte el temporizador.
				    \return		No devuelve nada.
				    \remarks	Para obtener cuando salta un temporizador debemos usaar la funcion Evento_Temporizador()
		    */
		    void DWLBaseWnd::CrearTemporizador(const UINT nID, const UINT nMiliSegundos) {
				SetTimer(_hWnd, nID, nMiliSegundos, NULL);
		    };

		    //! Función para eliminar un temporizador en esta ventana / control.
		    /*!	Esta función elimina un temporizador en esta ventana / control.
				    \fn			inline void EliminarTemporizador(const unsigned int nID);
				    \param[in]	nID				: ID del temporizador a eliminar.
				    \return		No devuelve nada.
		    */
		    void DWLBaseWnd::EliminarTemporizador(const UINT nID) {
				KillTimer(_hWnd, nID);
			};

		    //! Función que destruye esta ventana / control.
		    /*!	Esta funcion destruye esta ventana / control.
				    \fn			virtual BOOL Destruir(void);
				    \return		Devuelve TRUE si la operación se completo, FALSE en caso contrario.
		    */
            BOOL DWLBaseWnd::Destruir(void) {
			    if (_hWnd == NULL) return TRUE;
			    BOOL R = DestroyWindow(_hWnd);
			    //SOLO_DEBUG(if (R == FALSE) DWL::DWLDebug::MostrarUltimoError());
			    _hWnd = NULL;
			    return R;
		    };

		    //! Función que asigna la opacidad para la ventana / control.
		    /*!	Esta funcion asigna la opacidad para la ventana / control.
				    \fn			inline void Opacidad(const BYTE nNivel);
				    \param[in]	nNivel : Nivel de opacidad (0-255)
				    \return		No devuelve nada.
				    \remarks	Función no soportada en VC6.
		    */ 
		    void DWLBaseWnd::Opacidad(const BYTE nNivel) {
			    #if (COMPILADOR != COMPILADOR_VC6)
				    SetWindowLongPtr(_hWnd, GWL_EXSTYLE, 0x00080000 | WS_EX_TOPMOST | WS_EX_TOOLWINDOW);
				    SetLayeredWindowAttributes(_hWnd, 0, nNivel, LWA_ALPHA);
			    #endif
		    };

		    //! Función que retorna la ID esta ventana / control.
		    /*!	Esta funcion devuelve la ID de esta ventana / control.
				    \fn			UINT ID(void);
				    \return		Devuelve la ID de esta ventana / control.
		    */
		    UINT DWLBaseWnd::ID(void) {
                return static_cast<UINT>(GetWindowLongPtr(_hWnd, GWL_ID));
		    };


		    //! Función para calcular la X o la Y de la ventana quando esta necesita ser centrada.
		    /*!	Esta funcion sirve para para calcular la X o la Y de la ventana quando esta necesita ser centrada.
				    \fn			int _CalcularCentrado(HWND chWndParent, const bool cAncho, const int cValor);
				    \param[in]	chWndParent	: HWND de la ventana que contiene esta ventana / control.
				    \param[in]	cAncho		: True para obtener el ancho centrado, false para obtener el alto centrado.
				    \param[in]	cValor		: Valor a centrar.
				    \return		Devuelve la posición centrada.
				    \remarks	Función de uso interno.
		    */
            int DWLBaseWnd::_CalcularCentrado(HWND chWndParent, const bool cAncho, const int cValor) {
			    RECT RectParent;
			    if (chWndParent != NULL) {
				    GetClientRect(chWndParent, &RectParent);
				    if (cAncho == true) return static_cast<int>((RectParent.right - cValor) / 2);
				    else 				return static_cast<int>((RectParent.bottom - cValor) / 2);
			    }
			    else {
				    if (cAncho == true)	return static_cast<int>((GetSystemMetrics(SM_CXSCREEN) - cValor) /2);
				    else				return static_cast<int>((GetSystemMetrics(SM_CYSCREEN) - cValor) /2);
			    }
		    };




		    //! Función que registra la clase ventana.
		    /*!	Esta funcion registra la clase ventana.
				    \fn			ATOM RegistrarClase(const TCHAR *nNombre, HBRUSH nColorFondo, const int nIconoRecursos);
				    \param[in]	nNombre			       : Nombre para la clase ventana.
				    \param[in]	nColorFondo			   : Brocha con el color del fondo de la ventana. Puede ser NULL.
				    \param[in]	nIconoRecursos		   : ID del icono de los recursos que se asignara a la ventana. Puede ser 32512 para que se asigne el icono de la aplicación.
                    \param[in]  WindowProcedureInicial : WindowProcedure estatico que enlazara con el GestorMensajes virtual
				    \return		Devuelve el ATOM creado con RegisterClassEx, NULL en caso de error.
		    */
            ATOM DWLBaseWnd::RegistrarClase(const TCHAR *nNombre, HBRUSH nColorFondo, const int nIconoRecursos, WNDPROC WindowProcedureInicial) {
			    WNDCLASSEX WndClass;
			    WndClass.cbSize = sizeof(WNDCLASSEX);
			    WndClass.style = 0;
			    WndClass.lpfnWndProc = (WNDPROC)WindowProcedureInicial;
			    WndClass.cbClsExtra = 0;
			    WndClass.cbWndExtra = 0;
			    WndClass.hInstance = GetModuleHandle(NULL);
			    if (nIconoRecursos != 0) {
				    WndClass.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(nIconoRecursos));
				    WndClass.hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(nIconoRecursos));
			    }
			    else {
				    WndClass.hIcon = LoadIcon(GetModuleHandle(NULL), IDI_APPLICATION);
				    WndClass.hIconSm = LoadIcon(GetModuleHandle(NULL), IDI_APPLICATION);
			    }
			    WndClass.hCursor = LoadCursor (0, IDC_ARROW);
			    if (nColorFondo != NULL) {
				    WndClass.hbrBackground = nColorFondo;
			    }
			    else {
				    WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			    }
			    WndClass.lpszMenuName = 0;
			    WndClass.lpszClassName = nNombre;
			    return RegisterClassEx (&WndClass);
		    };

















		    //! Constructor.
		    /*! Constructor.
			    \fn			DWLListaTabuladores(void);
			    \return		No devuelve nada.
		    */
            DWLListaTabuladores::DWLListaTabuladores(void) {
			    _Posicion = 0;
		    };

		    //! Destructor.
		    /*! Destructor.
			    \fn			~DWLListaTabuladores(void);
			    \return		No devuelve nada.
		    */
            DWLListaTabuladores::~DWLListaTabuladores(void) {
            };

		    //! Función que agrega un control a la lista.
		    /*!	Esta funcion agrega un control a la lista.
				    \fn			void AgregarControl(DWLBaseWnd *nControl);
				    \param[in]	nControl : Clase DWLBaseWnd que queremos agregar a la lista de tabulaciones.
				    \return		No devuelve nada.
		    */
            void DWLListaTabuladores::AgregarControl(DWLBaseWnd *nControl) {
				try {
					_ListaControles.push_back(nControl);
				}
				catch (...) {
				}
			    #if defined DWL_LISTATABULADORES_DEBUG
				    DWL::DWLDebug::ImprimirDebug(TEXT("DWLListaTabuladores::AgregarControl %d\n"), PtrToLong(Control));
			    #endif
		    };

		    //! Función que asigna el foco al siguiente control de la lista.
		    /*!	Esta funcion asigna el foco al siguiente control de la lista.
				    \fn			void Siguiente(void);
				    \return		No devuelve nada.
		    */
            void DWLListaTabuladores::Siguiente(void) {
			    if (_ListaControles.size() == 0) return;
			    do {
				    if (_Posicion < _ListaControles.size() -1)	_Posicion ++;
				    else										_Posicion = 0;
			    } while (_ListaControles[_Posicion]->Activado() != TRUE || _ListaControles[_Posicion]->Visible() != TRUE);
			    _ListaControles[_Posicion]->AsignarFoco();
		    };

		    //! Función que asigna el foco al anterior control de la lista.
		    /*!	Esta funcion asigna el foco al anterior control de la lista.
				    \fn			void Anterior(void);
				    \return		No devuelve nada.
		    */
            void DWLListaTabuladores::Anterior(void) {
			    if (_ListaControles.size() == 0) return;
			    do {
				    if (_Posicion != 0) _Posicion --;
				    else				_Posicion = _ListaControles.size() -1;
			    } while (_ListaControles[_Posicion]->Activado() != TRUE || _ListaControles[_Posicion]->Visible() != TRUE);
			    _ListaControles[_Posicion]->AsignarFoco();
		    };

		    //! Función que devuelve la posicion del control especificado dentro de la lista.
		    /*!	Esta funcion devuelve la posicion del control especificado dentro de la lista.
				    \fn			int ObtenerPosicion(DWLBaseWnd *bControl);
				    \param[in]	bControl : Clase DWLBaseWnd de la que queremos saber la posicion dentro de la lista
				    \return		Devuelve la posicion de la lista. En caso de no existir devuelve -1.
		    */
            int DWLListaTabuladores::ObtenerPosicion(DWLBaseWnd *bControl) {
			    for (size_t i = 0; i < _ListaControles.size(); i++) {
				    if (_ListaControles[i] == bControl) return static_cast<int>(i);
			    }
			    return -1;
		    };

		    //! Función que cambia la posicion del control especificado dentro de la lista.
		    /*!	Esta funcion cambia la posicion del control especificado dentro de la lista.
				    \fn			void CambiarPosicion(DWLBaseWnd *bControl, const size_t nPos)
				    \param[in]	bControl	: Clase DWLBaseWnd de la que queremos mover dentro de la lista
				    \param[in]	nPos		: Nueva posicion dentro de la lista
				    \return		No devuelve nada.
				    \remarks	FUNCIÓN PENDIENTE POR PROGRAMAR.
		    */
            void DWLListaTabuladores::CambiarPosicion(DWLBaseWnd *bControl, const size_t nPos) {
    /*			size_t   Tmp_pos = nPos;
		        BaseWnd *Tmp = NULL;
		        if (Tmp_pos > _ListaControles.size() - 1) Tmp_Pos = _ListaControles.size() -1;
		        // Busco el control y lo marco como NULL en la lista
		        for (size_t i = 0; i < _ListaControles.size(); i++) {
			        if (_ListaControles[i] == bControl) _ListaControles[i] = NULL;
		        }

		        for (size_t i = 0; i < _ListaControles.size(); i++) {
			        if (nPos == i) {
				        Tmp = _ListaControles[i];
				        _ListaControles[i] = bControl;
			        }
		        }*/
		    };

		    //! Función que borra la lista de tabulaciones.
		    /*!	Esta funcion borra la lista de tabulaciones.
				    \fn			void BorrarLista(void);
				    \return		No devuelve nada.
		    */
            void DWLListaTabuladores::BorrarLista(void) {
			    _Posicion = 0;
			    _ListaControles.resize(0);
		    };

		    //! Función que borra un control de la lista de tabulaciones.
		    /*!	Esta funcion borra un control de la lista de tabulaciones.
				    \fn			void BorrarControl(DWLBaseWnd *bControl);
				    \param[in]	bControl : Clase DWLBaseWnd que queremos eliminar de la lista de tabulaciones.
				    \return		No devuelve nada.
		    */
            void DWLListaTabuladores::BorrarControl(DWLBaseWnd *bControl) {
			     for (size_t i = 0; i < _ListaControles.size(); i++) {
				     if (_ListaControles[i] == bControl) {
					     _ListaControles.erase(_ListaControles.begin() + i);
					     return;
				     }
			     }
		    };

		    //! Función que asigna el indice de la tabulacion.
		    /*!	Esta funcion asigna el indice de la tabulacion.
				    \fn			void AsignarNuevaPosicion(DWLBaseWnd *bControl);
				    \param[in]	bControl : Clase DWLBaseWnd que queremos establecer como actual.
				    \return		No devuelve nada.
		    */
            void DWLListaTabuladores::AsignarNuevaPosicion(DWLBaseWnd *bControl) {
			    _Posicion = 0;
			    for (size_t i = 0; i < _ListaControles.size(); i++) {
				    if (_ListaControles[i] == bControl) _Posicion = i;
			    }
			    #if defined DWL_LISTATABULADORES_DEBUG
				    DWL::DWLDebug::ImprimirDebug(TEXT("DWLListaTabuladores::AsignarNuevaPosicion %d\n"), _Posicion);
			    #endif
		    };

        };
    };
};
