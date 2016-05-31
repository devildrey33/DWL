#include "stdafx.h"
#include "DBaseWnd.h"
#include "DAplicacion.h"

namespace DWL {
    //! Función para mostrar / ocultar la ventana / control.
	/*! Esta función muestra / oculta la ventana / control.
			\fn			void Visible(const bool nMostrar);
			\param[in]	nMostrar : True para mostrar la ventana / control, false para ocultarlo.
			\return		No devuelve nada.
	*/
    void DBaseWnd::Visible(const bool nMostrar) {
        ShowWindow(_hWnd, (nMostrar == true) ? SW_SHOW : SW_HIDE);
    };


	//! Función que retorna si la ventana / control es visible.
	/*!	Esta funcion devuelve si la ventana / control es visible.
			\fn			BOOL Visible(void);
			\return		Devuelve TRUE si la ventana / control es visible, FALSE en caso contrario.
	*/
    const bool DBaseWnd::Visible(void) {
        if (IsWindowVisible(_hWnd)) return true;
        else                        return false;
    };

	//! Función para activar / desactivar la ventana / control.
	/*!	Esta función activa / desactiva la ventana / control.
			\fn			void Activado(const bool nActivar);
			\param[in]	nActivar	: Parametro en el que especificaremos si queremos activar o desactivar la ventana / control.
			\return		No devuelve nada.
	*/
    void DBaseWnd::Activado(const bool nActivar) {
        EnableWindow(_hWnd, nActivar);
	};

	//! Función que retorna si la ventana / control esta activado.
	/*!	Esta funcion devuelve si la ventana / control esta activado.
			\fn			virtual const bool Activado(void);
			\return		Devuelve TRUE si la ventana / control esta activado, FALSE en caso contrario.
	*/
	const bool DBaseWnd::Activado(void) {
        if (IsWindowEnabled(_hWnd)) return true;
        else                        return false;
	};

	//! Función que asigna el foco a esta ventana / control.
	/*!	Esta funcion asigna el foco a esta ventana / control.
			\fn			inline virtual void AsignarFoco(void);
			\return		No devuelve nada.
	*/
    void DBaseWnd::AsignarFoco(void) {
		SetFocus(_hWnd);
	};

	//! Función que retorna si esta ventana /control tiene el raton encima.
	/*!	Esta funcion devuelve si esta ventana /control tiene el raton encima.
			\fn			virtual bool Foco(void);
			\return		Devuelve true si la ventana tiene el foco del teclado
	*/
	bool DBaseWnd::TieneFoco(void) {
        return (GetFocus() == _hWnd);
	};

	//! Función que retorna si esta ventana /control tiene el mouse encima.
	/*!	Esta funcion devuelve si esta ventana /control tiene el mouse encima.
			\fn			virtual bool MouseEncima(void);
			\return		Devuelve true si esta ventana tiene el cursor del raton encima, false en caso contrario.
	*/
    bool DBaseWnd::MouseEncima(void) {
		bool TieneFoco = false;
		POINT Pt;
		GetCursorPos(&Pt);
		if (_hWnd == WindowFromPoint(Pt)) { // Tiene el foco del raton
			TieneFoco = true;
		}
		return TieneFoco;
    }

	//! Función que asigna una region a esta ventana / control.
	/*!	Esta funcion asigna una region a esta ventana / control.
			\fn			inline virtual int AsignarRegion(HRGN nRegion, const BOOL nRepintar = true);
			\param[in]	nRegion		: Region que queremos asignar a esta ventana / control.
			\param[in]	nRepintar	: Valor en el que especificamos si se debe repintar la ventana / control.
			\return		Devuelve 0 si la funcion ha fallado, cualquier otro numero para advertir que se ha asignado la region correctamente.
	*/
	int DBaseWnd::AsignarRegion(HRGN nRegion, const BOOL nRepintar) {
		return SetWindowRgn(_hWnd, nRegion, nRepintar);
	};

	//! Función que retorna el identificador de ventana HWND.
	/*!	Esta funcion devuelve el identificador de ventana HWND.
			\fn			inline HWND hWnd(void);
			\return		Devuelve el HWND para esta ventana / control.
	*/
	HWND DBaseWnd::hWnd(void) {
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
    void DBaseWnd::Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar) {
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
	void DBaseWnd::CrearTemporizador(const UINT nID, const UINT nMiliSegundos) {
		SetTimer(_hWnd, nID, nMiliSegundos, NULL);
	};

	//! Función para eliminar un temporizador en esta ventana / control.
	/*!	Esta función elimina un temporizador en esta ventana / control.
			\fn			inline void EliminarTemporizador(const unsigned int nID);
			\param[in]	nID				: ID del temporizador a eliminar.
			\return		No devuelve nada.
	*/
	void DBaseWnd::EliminarTemporizador(const UINT nID) {
		KillTimer(_hWnd, nID);
	};

	//! Función que destruye esta ventana / control.
	/*!	Esta funcion destruye esta ventana / control.
			\fn			virtual BOOL Destruir(void);
			\return		Devuelve TRUE si la operación se completo, FALSE en caso contrario.
	*/
    BOOL DBaseWnd::Destruir(void) {
//        _APLICACION->_EliminarBaseWnd(this);
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
	void DBaseWnd::Opacidad(const BYTE nNivel) {
//		#if (COMPILADOR != COMPILADOR_VC6)
		SetWindowLongPtr(_hWnd, GWL_EXSTYLE, 0x00080000 | WS_EX_TOPMOST | WS_EX_TOOLWINDOW);
		SetLayeredWindowAttributes(_hWnd, 0, nNivel, LWA_ALPHA);
//		#endif
	};

	//! Función que retorna la ID esta ventana / control.
	/*!	Esta funcion devuelve la ID de esta ventana / control.
			\fn			UINT ID(void);
			\return		Devuelve la ID de esta ventana / control.
	*/
	UINT DBaseWnd::ID(void) {
        return static_cast<UINT>(GetWindowLongPtr(_hWnd, GWLP_ID));
	};

	// 
	/*DBaseWnd *DBaseWnd::ObtenerBaseWnd(HWND nhWnd) {
		if (IsWindow(nhWnd)) return reinterpret_cast<DBaseWnd *>(GetWindowLongPtr(nhWnd, GWLP_USERDATA));
		return NULL;
	}*/


	//! Función que registra la clase ventana.
	/*!	Esta funcion registra la clase ventana.
			\fn			ATOM RegistrarClase(const TCHAR *nNombre, HBRUSH nColorFondo, const int nIconoRecursos);
			\param[in]	nNombre			       : Nombre para la clase ventana.
            \param[in]  WindowProcedureInicial : WindowProcedure estatico que enlazara con el GestorMensajes virtual
			\param[in]	nIconoRecursos		   : ID del icono de los recursos que se asignara a la ventana. Puede ser 32512 para que se asigne el icono de la aplicación.
			\param[in]	nColorFondo			   : Brocha con el color del fondo de la ventana. Puede ser NULL.
			\return		Devuelve el ATOM creado con RegisterClassEx, NULL en caso de error.
	*/
    ATOM DBaseWnd::_RegistrarClase(const TCHAR *nNombre, WNDPROC WindowProcedureInicial, const int nIconoRecursos, HBRUSH nColorFondo) {
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
			WndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE  + 1);
//			WndClass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
		}
		WndClass.lpszMenuName = 0;
		WndClass.lpszClassName = nNombre;
		return RegisterClassEx(&WndClass);
	};


/*    void DBaseWnd::_AgregarAppBaseWnd(const UINT nID, DBaseWnd *nPadre) {
//        _APLICACION->_AgregarBaseWnd(this, TipoBaseWnd(), nID, nPadre);
    }*/


};