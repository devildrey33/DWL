#include "DWLMarcaEx_Nucleo.h"
#include "..\DWLGraficos.h"
 
namespace DWL {
	namespace ControlesEx {

        //! Constructor por defecto.
        /*! Constructor por defecto.
		        \fn			DWLMarcaEx_Nucleo(void);
		        \return		No devuelve nada.
        */
		DWLMarcaEx_Nucleo::DWLMarcaEx_Nucleo(void) : _MarcaEx_Presionado(false), _MarcaEx_Estado(0), _MarcaEx_PEstado(-1), _MarcaEx_Marcado(false), MarcaEx_Estilos(), _MarcaEx_Texto() {
//			MarcaEx_EstilosFuentes.Enlazar(DWL::SO::DWLEstilos::Fuentes);
		}

		//! Destructor.
		/*! Destructor.
				\fn			~DWLMarcaEx_Nucleo(void);
				\return		No devuelve nada.
		*/
		DWLMarcaEx_Nucleo::~DWLMarcaEx_Nucleo(void) {
		}

		//! Función que pinta la MarcaEx en el DC y espacio especificados.
		/*! Esta funcion pinta la MarcaEx en las coordenadas y DC especificados.
				\fn			void MarcaEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true);
				\param[in]	hDC					: DC en el que se va a pintar la ListaEx.
				\param[in]	Espacio				: Recta que delimita el espacio donde se puede pintar la ListaEx.
				\param[in]	TieneFoco			: Valor que determina si la lista tiene el foco del raton (por defecto se usara la funcion Foco()).
				\return		No devuelve nada.
				\remarks	Esta función esta preparada para pintar la MarcaEx en un DC que no sea el suyo, o que sea compartido.
		*/
		void DWLMarcaEx_Nucleo::MarcaEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco) {
			RECT    RC		 = { 0, 0, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top };
			HFONT   VFuente  = NULL;

			HDC     Fondo    = CreateCompatibleDC(hDC);
			HBITMAP BmpFondo = CreateCompatibleBitmap(hDC, RC.right, RC.bottom);
			HBITMAP VFondo   = static_cast<HBITMAP>(SelectObject(Fondo, BmpFondo));

			MarcaEx_Evento_PintarFondo(Fondo, &RC);

			RECT    RectaMarca            = { 2, 2, 16, 16 };
			RECT    RectaMarcaInterior    = { 3, 3, 15, 15 };
			HPEN	PlumaColorBordeMarca;
			if (TieneFoco == true)	PlumaColorBordeMarca = CreatePen(PS_SOLID, 1, MarcaEx_Estilos.Colores.BordeRectanguloFoco());
			else					PlumaColorBordeMarca = CreatePen(PS_SOLID, 1, MarcaEx_Estilos.Colores.BordeRectangulo());
			HBRUSH  BrochaTmp             = NULL;
			HPEN	PlumaVieja			  = static_cast<HPEN>(SelectObject(Fondo, PlumaColorBordeMarca));
			MoveToEx(Fondo, 2, 3, NULL);
			LineTo(Fondo, 2, 15);
			MoveToEx(Fondo, 3, 2, NULL);
			LineTo(Fondo, 15, 2);
			MoveToEx(Fondo, 14, 15, NULL);
			LineTo(Fondo, 2, 15);
			MoveToEx(Fondo, 15, 14, NULL);
			LineTo(Fondo, 15, 2);
			SelectObject(Fondo, PlumaVieja);


			RECT RectaTexto = { 21, 2, RC.right, 19 };
			SetBkMode(Fondo, TRANSPARENT);
			switch(_MarcaEx_Estado) {
				case 0: // Normal
					VFuente = (HFONT)SelectObject(Fondo, MarcaEx_Estilos.Fuentes.Normal());
					SetTextColor(Fondo, MarcaEx_Estilos.Colores.TextoNormal());
					DrawText(Fondo, _MarcaEx_Texto(), static_cast<int>(_MarcaEx_Texto.Tam()), &RectaTexto, DT_LEFT);
					BrochaTmp = CreateSolidBrush(MarcaEx_Estilos.Colores.FondoRectanguloNormal());
					FillRect(Fondo, &RectaMarcaInterior, BrochaTmp);
					break;
				case 1: // Resaltado
					VFuente = (HFONT)SelectObject(Fondo, MarcaEx_Estilos.Fuentes.SubRayada());
					SetTextColor(Fondo, MarcaEx_Estilos.Colores.TextoResaltado());
					DrawText(Fondo, _MarcaEx_Texto(), static_cast<int>(_MarcaEx_Texto.Tam()), &RectaTexto, DT_LEFT);
					BrochaTmp = CreateSolidBrush(MarcaEx_Estilos.Colores.FondoRectanguloResaltado());
					FillRect(Fondo, &RectaMarcaInterior, BrochaTmp);
					break;
				case 2: // Presionado
					VFuente = (HFONT)SelectObject(Fondo, MarcaEx_Estilos.Fuentes.SubRayada());
					RectaTexto.left ++; RectaTexto.top ++; RectaTexto.right ++; RectaTexto.bottom ++;
					SetTextColor(Fondo, MarcaEx_Estilos.Colores.TextoPresionado());
					DrawText(Fondo, _MarcaEx_Texto(), static_cast<int>(_MarcaEx_Texto.Tam()), &RectaTexto, DT_LEFT);
					BrochaTmp = CreateSolidBrush(MarcaEx_Estilos.Colores.FondoRectanguloPresionado());
					FillRect(Fondo, &RectaMarcaInterior, BrochaTmp);
					break;
				case 3 : // Desactivado
					VFuente = (HFONT)SelectObject(Fondo, MarcaEx_Estilos.Fuentes.Normal());
					SetTextColor(Fondo, MarcaEx_Estilos.Colores.TextoPresionado());
					DrawText(Fondo, _MarcaEx_Texto(), static_cast<int>(_MarcaEx_Texto.Tam()), &RectaTexto, DT_LEFT);
					BrochaTmp = CreateSolidBrush(MarcaEx_Estilos.Colores.FondoRectanguloNormal());
					FillRect(Fondo, &RectaMarcaInterior, BrochaTmp);
					break;
			}
			if (_MarcaEx_Marcado == true) {
				RectaMarca.top = 0;
				RectaMarca.left = 0;
				RectaMarca.right = 18;
				RectaMarca.bottom = 18;
				MarcaEx_Evento_PintarMarca(Fondo, &RC, _MarcaEx_Estado);
			}
			BitBlt(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, Fondo, 0, 0, SRCCOPY);
//			DeleteObject(BrochaColorBordeMarca);
			DeleteObject(PlumaColorBordeMarca);
			if (BrochaTmp != NULL)	DeleteObject(BrochaTmp);
			if (VFuente != NULL)	SelectObject(Fondo, VFuente);
			SelectObject(Fondo, VFondo);
			DeleteObject(BmpFondo);
			DeleteDC(Fondo);
		}


		//! Función virtual que pinta el fondo del control.
		/*! Esta función virtual pinta el fondo del control.
				\fn			virtual void MarcaEx_Evento_PintarFondo(HDC hDC, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar la MarcaEx.
				\param[in]	Espacio	: Espacio donde se pintara.
				\return		No devuelve nada.
		*/
		void DWLMarcaEx_Nucleo::MarcaEx_Evento_PintarFondo(HDC hDC, RECT *Espacio) {
			HBRUSH  BrochaColorFondo = CreateSolidBrush(MarcaEx_Estilos.Colores.Fondo());
			FillRect(hDC, Espacio, BrochaColorFondo);
			DeleteObject(BrochaColorFondo);
		}

		//! Función virtual que pinta la marca del control.
		/*! Esta función virtual pinta la marca del control.
				\fn			virtual void MarcaEx_Evento_PintarMarca(HDC hDC, RECT *Espacio, const int nEstado);
				\param[in]	hDC		: hDC donde se va a pintar la MarcaEx.
				\param[in]	Espacio	: Espacio donde se pintara.
				\param[in]	nEstado	: Estado del control : 0 = normal, 1 = resaltado, 2 = presionado.
				\return		No devuelve nada.
		*/
		void DWLMarcaEx_Nucleo::MarcaEx_Evento_PintarMarca(HDC hDC, RECT *Espacio, const int nEstado) {
			HPEN Pluma = NULL;
			switch (nEstado) {
				case 0: Pluma = CreatePen(PS_SOLID, 2, MarcaEx_Estilos.Colores.TextoNormal());		break;
				case 1: Pluma = CreatePen(PS_SOLID, 2, MarcaEx_Estilos.Colores.TextoResaltado());	break;
				default: Pluma = CreatePen(PS_SOLID, 2, MarcaEx_Estilos.Colores.TextoPresionado());	break;
			}
			HPEN VPluma = static_cast<HPEN>(SelectObject(hDC, Pluma));
			if (_MarcaEx_Estado != 2) {
				MoveToEx(hDC, 5, 5, NULL); LineTo(hDC, 12, 12);
				MoveToEx(hDC, 12, 5, NULL); LineTo(hDC, 5, 12);
			}
			else {
				MoveToEx(hDC, 6, 6, NULL); LineTo(hDC, 13, 13);
				MoveToEx(hDC, 13, 6, NULL); LineTo(hDC, 6, 13);
			}
			SelectObject(hDC, VPluma);
			DeleteObject(Pluma);
		}

		//! Función que procesa las teclas presionadas en la MarcaEx.
		/*! Esta función procesa las teclas presionadas en la MarcaEx.
				\fn			void MarcaEx_Teclado_TeclaPresionada(HWND hWndControl, const int Tecla, LPARAM lParam);
				\param[in]	hWndControl	: HWND del control que contiene la MarcaEx.
				\param[in]	Tecla		: Tecla que se ha presionado.
				\param[in]	lParam		: lParam que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		No devuelve nada.
				\remarks    Esta función debe ser enlazada con el Evento_TeclaPresionada del control que vaya a contener la MarcaEx.
				\sa			MarcaEx_Teclado_TeclaPresionada()
		*/
		void DWLMarcaEx_Nucleo::MarcaEx_Teclado_TeclaPresionada(HWND hWndControl, const int Tecla, LPARAM lParam) {
		}

		//! Función que procesa las teclas soltadas en la MarcaEx.
		/*! Esta función procesa las teclas presionadas en la MarcaEx.
				\fn			void MarcaEx_Teclado_TeclaSoltada(HWND hWndControl, const int Tecla, LPARAM lParam);
				\param[in]	hWndControl	: HWND del control que contiene la MarcaEx.
				\param[in]	Tecla		: Tecla que se ha soltado.
				\param[in]	lParam		: lParam que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		No devuelve nada.
				\remarks    Esta función debe ser enlazada con el Evento_TeclaSoltada del control que vaya a contener la MarcaEx.
				\sa			MarcaEx_Teclado_TeclaSoltada()
		*/
		void DWLMarcaEx_Nucleo::MarcaEx_Teclado_TeclaSoltada(HWND hWndControl, const int Tecla, LPARAM lParam) {
		}

		//! Función que procesa el movimiento del mouse en la MarcaEx.
		/*! Esta función procesa el movimiento del mouse en la MarcaEx.
				\fn			BOOL MarcaEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param);
				\param[in]	hWndControl		: HWND del control que contiene la MarcaEx.
				\param[in]	RectaControl	: Recta con el espacio de la MarcaEx.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	wParam			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_Movimiento del control que vaya a contener la MarcaEx.
				\sa			MarcaEx_Mouse_BotonPresionado(), MarcaEx_Mouse_BotonSoltado()
		*/
		BOOL DWLMarcaEx_Nucleo::MarcaEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param) {
			if (_MarcaEx_Estado == 3) return FALSE;
			POINT Pt = { cX, cY };
			BOOL DentroControl = PtInRect(RectaControl, Pt);
			if (_MarcaEx_Presionado == true) {
				if (DentroControl == TRUE)  _MarcaEx_Estado = 2;
				else						_MarcaEx_Estado = 0;
			}
			else {
				if (DentroControl == TRUE) _MarcaEx_Estado = 1;
				else					   _MarcaEx_Estado = 0;
			}
//			if (DentroControl == TRUE) PostMessage(GetParent(hWndControl), DWL_BOTONEX_MOUSE_MOVIMIENTO, (WPARAM)GetWindowLongPtr(hWndControl, GWL_ID), MAKELPARAM(cX ,cY));
			return DentroControl;
		}

		BOOL DWLMarcaEx_Nucleo::MarcaEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			if (_MarcaEx_Estado == 3) return FALSE;
			POINT Pt = { cX, cY };
			if (PtInRect(RectaControl, Pt) == TRUE) {
				if (Boton >= 3) return TRUE;
				SetCapture(hWndControl);
				_MarcaEx_Presionado = true;
				_MarcaEx_Estado = 2;
//				_MarcaEx_Params.Asignar(cX, cY, GetWindowLongPtr(hWndControl, GWL_ID), Boton, wParam);
//				PostMessage(GetParent(hWndControl), DWL_BOTONEX_MOUSE_BOTONPRESIONADO, reinterpret_cast<WPARAM>(&_BotonEx_Params), NULL);
				return TRUE;
			}
			return FALSE;
		}

		//! Función que procesa los botones presionados del mouse en la MarcaEx.
		/*! Esta función procesa los botones presionados del mouse en la MarcaEx.
				\fn			BOOL MarcaEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	hWndControl		: HWND del control que contiene la MarcaEx.
				\param[in]	RectaControl	: Recta con el espacio de la MarcaEx.
				\param[in]	Boton			: Boton del mouse presionado.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	wParam			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonPresionado del control que vaya a contener la MarcaEx.
				\sa			MarcaEx_Mouse_Movimiento(), MarcaEx_Mouse_BotonSoltado()
		*/
	    BOOL DWLMarcaEx_Nucleo::MarcaEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			if (_MarcaEx_Estado == 3) return FALSE;
			if (_MarcaEx_Presionado == true) {
				ReleaseCapture();
				_MarcaEx_Presionado = false;
			}
			if (_MarcaEx_Estado == 2) {
				if (Boton >= 3) return TRUE;
				POINT Pt = { cX, cY };
				if (PtInRect(RectaControl, Pt) != 0)	_MarcaEx_Estado = 1; // Estado resaltado
				else  									_MarcaEx_Estado = 0; // Estado normal
				if (_MarcaEx_Estado == 1) {
//					_MarcaEx_Params.Asignar(cX, cY, GetWindowLongPtr(hWndControl, GWL_ID), Boton, wParam);
//					PostMessage(GetParent(hWndControl), DWL_BOTONEX_CLICK, reinterpret_cast<WPARAM>(&_BotonEx_Params), NULL);
					PostMessage(GetParent(hWndControl), DWL_MARCAEX_CLICK_IZQUIERDO + Boton, GetWindowLongPtr(hWndControl, GWL_ID), (LPARAM)hWndControl);
				}
				return TRUE;
			}
			return FALSE;
		};




    };
};

