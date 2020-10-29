#include "DWLBotonEx_Nucleo.h"
#include "..\DWLGraficos.h"
 
namespace DWL {
	namespace ControlesEx {


		//! Constructor.
		/*! Constructor que enlaza la fuente de este control a la clase DWLEstilos.
			\fn			DWLBotonEx_Nucleo(void);
			\return		No devuelve nada.
		*/
        DWLBotonEx_Nucleo::DWLBotonEx_Nucleo(void) {
//			BotonEx_Estilos.Fuentes.Enlazar(DWL::SO::DWLEstilos::Fuentes);
			_BotonEx_Activado = true;
			_BotonEx_TeclaPresionada = false;
		};

		//! Función para repintar el BotonEx.
		/*! Esta funcion se usa para repintar el BotonEx desde el nucleo.
			\fn			void BotonEx_Repintar(HWND hWndControl, const bool Forzar = false);
			\param[in]	hWndControl : HWND del control que contiene el nucleo del botonex.
			\param[in]  Forzar      : Forzar el repintado (por defecto false)
			\return		No devuelve nada.
		*/
		void DWLBotonEx_Nucleo::BotonEx_Repintar(HWND hWndControl, const bool Forzar) {
			if (hWndControl == NULL) return;
			if (Forzar == false) {
				if (_BotonEx_PEstado == _BotonEx_Estado) return;
			}
			_BotonEx_PEstado = _BotonEx_Estado;
			HDC hDC = GetDC(hWndControl);


			bool TieneFoco = false;
			if (_BotonEx_Estado == 2) TieneFoco = false;
			else {
				POINT Pt;
				GetCursorPos(&Pt);
				if (hWndControl == WindowFromPoint(Pt)) { // Tiene el foco del raton
					TieneFoco = true;
				}
			}


			RECT R;
			GetClientRect(hWndControl, &R);
			BotonEx_Pintar(hDC, &R, TieneFoco);
			ReleaseDC(hWndControl, hDC);

		}

		//! Función que pinta el boton en el DC y espacio especificados.
		/*! Esta funcion pinta el BotonEx en las coordenadas y DC especificados.
				\fn			void BotonEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true, const bool PintarConMascara = false);;
				\param[in]	hDC					: DC en el que se va a pintar el BotonEx.
				\param[in]	Espacio				: Recta que delimita el espacio donde se puede pintar el BotonEx.
				\param[in]	TieneFoco			: Valor que determina si el arbol tiene el foco del raton (por defecto se usara la funcion Foco()).
				\param[in]	PintarConMascara	: Valor que determina si se va a pintar el contorno del control con SRCAND antes de pintar el control.
				\return		No devuelve nada.
				\remarks	Esta funcion esta preparada para pintar el BotonEx en un DC que no sea el suyo, o que sea compartido.
							Por ello debemos especificar las coordenadas donde se va a pintar, si tiene el foco del raton o no, y por ultimo si debemos
							pintar la mascara.
							El parametro PintarMascara solo es necesario si vamos a pintar el BotonEx en un DC que no es el suyo y requerimos el pintado
							del borde del control. Entonces la funcion de pintado pintara el contorno del BotonEx con SRCAND, y luego pintara el control
							con SRC_PAINT para que no se vean graficos desfasados en el borde.
		*/
        void DWLBotonEx_Nucleo::BotonEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco, const bool PintarConMascara) {
			// Creacion del buffer grafico y de la region del control
			RECT	RC		= { 0, 0, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top };
			HDC		Buffer	= CreateCompatibleDC(hDC);
			HBITMAP Bmp		= CreateCompatibleBitmap(hDC, RC.right, RC.bottom);
			HBITMAP Viejo	= static_cast<HBITMAP>(SelectObject(Buffer, Bmp));
			HRGN	Region	= CreateRoundRectRgn(0, 0, RC.right + 1, RC.bottom + 1, 2, 2);

			// Pinto la mascara del control si se requiere
			if (PintarConMascara == true) {
				FillRect(Buffer, &RC, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));
				FillRgn(Buffer, Region, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
				BitBlt(hDC, Espacio->left, Espacio->top, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top, Buffer, 0, 0, SRCAND);
			}
			SetBkMode(Buffer, TRANSPARENT);

			// Pinto el fondo y el texto del boton
			switch (_BotonEx_Estado) {
				case 0 :	BotonEx_Evento_Pintar_EstadoNormal(Buffer, &RC);		break; // Estado normal
				case 1 : 	BotonEx_Evento_Pintar_EstadoResaltado(Buffer, &RC);		break; // Estado resaltado
				case 2 : 	BotonEx_Evento_Pintar_EstadoPresionado(Buffer, &RC);	break; // Estado presionado
				case 3 : 	BotonEx_Evento_Pintar_EstadoDesactivado(Buffer, &RC);	break; // Estado desactivado
			}

			// Pinto el borde del boton
			BotonEx_Evento_Pintar_Borde(Buffer, Region, TieneFoco);
			DeleteObject(Region);

			// Pinto el boton en el hDC especificado
			if (PintarConMascara == false)	BitBlt(hDC, Espacio->left, Espacio->top, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top, Buffer, 0, 0, SRCCOPY);
			else							BitBlt(hDC, Espacio->left, Espacio->top, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top, Buffer, 0, 0, SRCPAINT);

			// Elimino objetos gdi de la memoria
			SelectObject(Buffer, Viejo);
			DeleteObject(Bmp);
			DeleteDC(Buffer);
	    };

		//! Función virtual que pinta el estado normal del boton.
		/*! Esta función virtual pinta el BotonEx en su estado normal.
				\fn			virtual void BotonEx_Evento_Pintar_EstadoNormal(HDC hDC, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar el BotonEx.
				\param[in]	Espacio	: Espacio donde se pintara el BotonEx.
				\return		No devuelve nada.
				\remarks	Esta funcion pinta el fondo y el texto del boton.
				\sa			BotonEx_Evento_Pintar_EstadoResaltado(), BotonEx_Evento_Pintar_EstadoPresionado(), BotonEx_Evento_Pintar_EstadoDesactivado(), BotonEx_Evento_Pintar_Borde()
		*/
        void DWLBotonEx_Nucleo::BotonEx_Evento_Pintar_EstadoNormal(HDC hDC, RECT *Espacio) {
			HFONT VFuente = static_cast<HFONT>(SelectObject(hDC, BotonEx_Estilos.Fuentes.Normal()));
			SetTextColor(hDC, BotonEx_Estilos.Colores.TextoNormal());
			if (_BotonEx_Marcado == false) {
				GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, BotonEx_Estilos.Colores.DegradadoSuperior(), BotonEx_Estilos.Colores.DegradadoInferior());
				DrawText(hDC, _BotonEx_Texto(), static_cast<int>(_BotonEx_Texto.Tam()), Espacio, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			else {
				DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, BotonEx_Estilos.Colores.DegradadoInferior(), BotonEx_Estilos.Colores.DegradadoSuperior());
				DrawText(hDC, _BotonEx_Texto(), static_cast<int>(_BotonEx_Texto.Tam()), Espacio, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			SelectObject(hDC, VFuente);
		};

		//! Función virtual que pinta el estado resaltado del boton.
		/*! Esta función virtual pinta el BotonEx en su estado resaltado.
				\fn			virtual void BotonEx_Evento_Pintar_EstadoResaltado(HDC hDC, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar el BotonEx.
				\param[in]	Espacio	: Espacio donde se pintara el BotonEx.
				\return		No devuelve nada.
				\remarks	Esta funcion pinta el BotonEx_Evento_Pintar_EstadoNormal y el texto del boton.
				\sa			BotonEx_Evento_Pintar_EstadoNormal(), BotonEx_Evento_Pintar_EstadoPresionado(), BotonEx_Evento_Pintar_EstadoDesactivado(), BotonEx_Evento_Pintar_Borde()
		*/
        void DWLBotonEx_Nucleo::BotonEx_Evento_Pintar_EstadoResaltado(HDC hDC, RECT *Espacio) {
			HFONT VFuente = static_cast<HFONT>(SelectObject(hDC, BotonEx_Estilos.Fuentes.SubRayada()));
			SetTextColor(hDC, BotonEx_Estilos.Colores.TextoResaltado());
			if (_BotonEx_Marcado == false) {
				DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, BotonEx_Estilos.Colores.DegradadoResaltado(), BotonEx_Estilos.Colores.DegradadoInferior());
				DrawText(hDC, _BotonEx_Texto(), static_cast<int>(_BotonEx_Texto.Tam()), Espacio, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			else {
				DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, BotonEx_Estilos.Colores.DegradadoInferior(), BotonEx_Estilos.Colores.DegradadoResaltado());
				DrawText(hDC, _BotonEx_Texto(), static_cast<int>(_BotonEx_Texto.Tam()), Espacio, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			SelectObject(hDC, VFuente);
		};

		//! Función virtual que pinta el estado presionado del boton.
		/*! Esta función virtual pinta el BotonEx en su estado presionado.
				\fn			virtual void BotonEx_Evento_Pintar_EstadoPresionado(HDC hDC, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar el BotonEx.
				\param[in]	Espacio	: Espacio donde se pintara el BotonEx.
				\return		No devuelve nada.
				\remarks	Esta funcion pinta el BotonEx_Evento_Pintar_EstadoNormal y el texto del boton.
				\sa			BotonEx_Evento_Pintar_EstadoNormal(), BotonEx_Evento_Pintar_EstadoResaltado(), BotonEx_Evento_Pintar_EstadoDesactivado(), BotonEx_Evento_Pintar_Borde()
		*/
        void DWLBotonEx_Nucleo::BotonEx_Evento_Pintar_EstadoPresionado(HDC hDC, RECT *Espacio) {
			HFONT VFuente = static_cast<HFONT>(SelectObject(hDC, BotonEx_Estilos.Fuentes.SubRayada()));
			SetTextColor(hDC, BotonEx_Estilos.Colores.TextoResaltado());
			DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, BotonEx_Estilos.Colores.DegradadoInferior(), BotonEx_Estilos.Colores.DegradadoSuperior());
			Espacio->left ++; Espacio->top ++;
			DrawText(hDC, _BotonEx_Texto(), static_cast<int>(_BotonEx_Texto.Tam()), Espacio, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			Espacio->left --; Espacio->top --;
			SelectObject(hDC, VFuente);
		};

		//! Función virtual que pinta el estado desactivado del boton.
		/*! Esta función virtual pinta el BotonEx en su estado desactivado.
				\fn			virtual void BotonEx_Evento_Pintar_EstadoDesactivado(HDC hDC, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar el BotonEx.
				\param[in]	Espacio	: Espacio donde se pintara el BotonEx.
				\return		No devuelve nada.
				\remarks	Esta funcion pinta el BotonEx_Evento_Pintar_EstadoNormal y el texto del boton.
				\sa			BotonEx_Evento_Pintar_EstadoNormal(), BotonEx_Evento_Pintar_EstadoResaltado(), BotonEx_Evento_Pintar_EstadoPresionado(), BotonEx_Evento_Pintar_Borde()
		*/
        void DWLBotonEx_Nucleo::BotonEx_Evento_Pintar_EstadoDesactivado(HDC hDC, RECT *Espacio) {
			HFONT VFuente = static_cast<HFONT>(SelectObject(hDC, BotonEx_Estilos.Fuentes.Normal()));
			SetTextColor(hDC, BotonEx_Estilos.Colores.TextoDesactivado());
			DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, BotonEx_Estilos.Colores.DegradadoSuperior(), BotonEx_Estilos.Colores.DegradadoInferior());
			DrawText(hDC, _BotonEx_Texto(), static_cast<int>(_BotonEx_Texto.Tam()), Espacio, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			SelectObject(hDC, VFuente);
		};

		//! Función virtual que pinta el borde del boton.
		/*! Esta función virtual pinta el borde del BotonEx.
				\fn			virtual void BotonEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco);
				\param[in]	hDC			: hDC donde se va a pintar el BotonEx.
				\param[in]	Region		: Region que contiene el borde del BotonEx.
				\param[in]	TieneFoco	: Valor en el que determinamos si pintamos el borde con foco o sin foco.
				\return		No devuelve nada.
				\remarks	Esta funcion pinta el BotonEx_Evento_Pintar_EstadoNormal y el texto del boton.
				\sa			BotonEx_Evento_Pintar_EstadoNormal(), BotonEx_Evento_Pintar_EstadoResaltado(), BotonEx_Evento_Pintar_EstadoPresionado(), BotonEx_Evento_Pintar_Borde()
		*/
        void DWLBotonEx_Nucleo::BotonEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco) {
			HBRUSH Brocha;
			if (TieneFoco == true)	Brocha = CreateSolidBrush(BotonEx_Estilos.Colores.BordeSeleccionado());
			else					Brocha = CreateSolidBrush(BotonEx_Estilos.Colores.Borde());

            if (BotonEx_Estilos.Borde > 1) {
				HBRUSH ColorBordeLight = CreateSolidBrush(BotonEx_Estilos.Colores.BordeClaro());
				FrameRgn(hDC, Region, ColorBordeLight, BotonEx_Estilos.Borde, BotonEx_Estilos.Borde);
				FrameRgn(hDC, Region, Brocha, BotonEx_Estilos.Borde - (BotonEx_Estilos.Borde / 2), BotonEx_Estilos.Borde - (BotonEx_Estilos.Borde / 2));
				DeleteObject(ColorBordeLight);
			}
			else {
				FrameRgn(hDC, Region, Brocha, 1, 1);
			}
			DeleteObject(Brocha);
		};

		//! Función que procesa las teclas presionadas en el BotonEx.
		/*! Esta función procesa las teclas presionadas en el BotonEx.
				\fn			void BotonEx_Teclado_TeclaPresionada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params);
				\param[in]	hWndControl	: HWND del control que contiene el BotonEx.
				\param[in]	Caracter    : Tecla que se ha presionado.
                \param[in]  Repeticion  : Repeticion de la tecla.
				\param[in]	Param		: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		No devuelve nada.
				\remarks    Esta función debe ser enlazada con el Evento_TeclaPresionada del control que vaya a contener el BotonEx.
				\sa			BotonEx_Teclado_TeclaSoltada()
		*/
        void DWLBotonEx_Nucleo::BotonEx_Teclado_TeclaPresionada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params) {
			if (_BotonEx_Estado == 3) return;
			if (Caracter == VK_SPACE || Caracter == VK_RETURN) {
				_BotonEx_Presionado = true;
				_BotonEx_Estado = 2;
			}
			_BotonEx_TeclaPresionada = true;
			PostMessage(GetParent(hWndControl), DWL_BOTONEX_TECLADO_PRESIONADO, static_cast<WPARAM>(Caracter), static_cast<LPARAM>(GetWindowLongPtr(hWndControl, GWL_ID)));
		};

		//! Función que procesa las teclas soltadas en el BotonEx.
		/*! Esta función procesa las teclas presionadas en el BotonEx.
				\fn			void BotonEx_Teclado_TeclaSoltada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params);
				\param[in]	hWndControl	: HWND del control que contiene el BotonEx.
				\param[in]	Tecla		: Tecla que se ha soltado.
                \param[in]  Repeticion  : Repeticion de la tecla.
				\param[in]	Param		: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		No devuelve nada.
				\remarks    Esta función debe ser enlazada con el Evento_TeclaSoltada del control que vaya a contener el BotonEx.
				\sa			BotonEx_Teclado_TeclaPresionada()
		*/
        void DWLBotonEx_Nucleo::BotonEx_Teclado_TeclaSoltada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params) {
			if (_BotonEx_Estado == 3) return;
			if (_BotonEx_TeclaPresionada == true) { // Aveces el boton puede recibir solo el WM_KEYUP, y no es correcto, hay que recibir tambien el WM_KEYDOWN, si no presupondremos que no es para el.
				_BotonEx_TeclaPresionada = false;
				_BotonEx_Estado = 0;
				if (Caracter == VK_SPACE || Caracter == VK_RETURN) {
					_BotonEx_Params.Asignar(1, 1, GetWindowLongPtr(hWndControl, GWL_ID), 0, 0);
					PostMessage(GetParent(hWndControl), DWL_BOTONEX_CLICK, reinterpret_cast<WPARAM>(&_BotonEx_Params), 0);
				}
				PostMessage(GetParent(hWndControl), DWL_BOTONEX_TECLADO_SOLTADO, static_cast<WPARAM>(Caracter), static_cast<LPARAM>(GetWindowLongPtr(hWndControl, GWL_ID)));
			}
		};

		//! Función que procesa el movimiento del mouse en el BotonEx.
		/*! Esta función procesa el movimiento del mouse en el BotonEx.
				\fn			BOOL BotonEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param);
				\param[in]	hWndControl		: HWND del control que contiene el BotonEx.
				\param[in]	RectaControl	: Recta con el espacio del BotonEx.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_Movimiento del control que vaya a contener el BotonEx.
				\sa			BotonEx_Mouse_BotonPresionado(), BotonEx_Mouse_BotonSoltado()
		*/
        BOOL DWLBotonEx_Nucleo::BotonEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param) {
			if (_BotonEx_Estado == 3) return TRUE;
			POINT Pt = { cX, cY };
			BOOL DentroControl = PtInRect(RectaControl, Pt);
			if (_BotonEx_Presionado == true) {
				if (DentroControl == TRUE)  _BotonEx_Estado = 2;
				else						_BotonEx_Estado = 0;
			}
			else {
				if (DentroControl == TRUE) _BotonEx_Estado = 1;
				else					   _BotonEx_Estado = 0;
			}
			if (DentroControl == TRUE) PostMessage(GetParent(hWndControl), DWL_BOTONEX_MOUSE_MOVIMIENTO, (WPARAM)GetWindowLongPtr(hWndControl, GWL_ID), MAKELPARAM(cX ,cY));
			return DentroControl;
		};

		//! Función que procesa los botones presionados del mouse en el BotonEx.
		/*! Esta función procesa los botones presionados del mouse en el BotonEx.
				\fn			BOOL BotonEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	hWndControl		: HWND del control que contiene el BotonEx.
				\param[in]	RectaControl	: Recta con el espacio del BotonEx.
				\param[in]	Boton			: Boton del mouse presionado.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonPresionado del control que vaya a contener el BotonEx.
				\sa			BotonEx_Mouse_Movimiento(), BotonEx_Mouse_BotonSoltado()
		*/
        BOOL DWLBotonEx_Nucleo::BotonEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			if (_BotonEx_Estado == 3) return TRUE;
			POINT Pt = { cX, cY };
			if (PtInRect(RectaControl, Pt) == TRUE) {
				if (Boton >= 3) return TRUE;
				SetCapture(hWndControl);
				_BotonEx_Presionado = true;
				_BotonEx_Estado = 2;
				_BotonEx_Params.Asignar(cX, cY, GetWindowLongPtr(hWndControl, GWL_ID), Boton, Param);
				BotonEx_Repintar(hWndControl, false);
				PostMessage(GetParent(hWndControl), DWL_BOTONEX_MOUSE_BOTONPRESIONADO, reinterpret_cast<WPARAM>(&_BotonEx_Params), 0);
				return TRUE;
			}
			return FALSE;
		};

		//! Función que procesa los botones soltados del mouse en el BotonEx.
		/*! Esta función procesa los botones soltados del mouse en el BotonEx.
				\fn			BOOL BotonEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	hWndControl		: HWND del control que contiene el BotonEx.
				\param[in]	RectaControl	: Recta con el espacio del BotonEx.
				\param[in]	Boton			: Boton del mouse presionado.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonSoltado del control que vaya a contener el BotonEx.
				\sa			BotonEx_Mouse_Movimiento(), BotonEx_Mouse_BotonPresionado()
		*/
        BOOL DWLBotonEx_Nucleo::BotonEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			if (_BotonEx_Estado == 3) return TRUE;
			if (_BotonEx_Estado == 2) {
				ReleaseCapture();
				if (Boton >= 3) return TRUE;
				POINT Pt = { cX, cY };
				_BotonEx_Presionado = false;
				if (PtInRect(RectaControl, Pt) != 0)	_BotonEx_Estado = 1; // Estado resaltado
				else  									_BotonEx_Estado = 0; // Estado normal
				_BotonEx_Params.Asignar(cX, cY, GetWindowLongPtr(hWndControl, GWL_ID), Boton, Param);
				BotonEx_Repintar(hWndControl, false);
				if (_BotonEx_Estado == 1) {
					SendMessage(GetParent(hWndControl), DWL_BOTONEX_CLICK, reinterpret_cast<WPARAM>(&_BotonEx_Params), 0);
				}
				PostMessage(GetParent(hWndControl), DWL_BOTONEX_MOUSE_BOTONSOLTADO, reinterpret_cast<WPARAM>(&_BotonEx_Params), 0);
				return TRUE;
			}
			return FALSE;
		};


    };
};

