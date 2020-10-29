#include "DWLBarraEx_Nucleo.h"
 
#include "..\DWLGraficos.h"

namespace DWL {
	namespace ControlesEx {


		//! Constructor por defecto.
		/*! Constructor por defecto.
				\fn			DWLBarraEx_Nucleo(void);
				\return		No devuelve nada.
		*/
        DWLBarraEx_Nucleo::DWLBarraEx_Nucleo(void) :
            BarraEx_Estilos(), _BarraEx_Minimo(0), _BarraEx_Maximo(100), _BarraEx_Valor(0), _BarraEx_Presionado(false),
            _BarraEx_Estado(DWL_Enum_BarraEx_Estados_Normal), _BarraEx_PEstado(DWL_Enum_BarraEx_Estados_NoDefinido) {
		};

		//! Destructor.
		/*! Destructor.
				\fn		   ~DWLBarraEx_Nucleo(void);
				\return		No devuelve nada.
		*/
        DWLBarraEx_Nucleo::~DWLBarraEx_Nucleo(void) { };

		//! Función para pintar este control en el DC y posicion especificados.
		/*! Esta función pinta la BarraEx en el DC y posicion especificadas.
				\fn			void BarraEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true, const bool PintarConMascara = false);
				\param[in]	hDC					: hDC del control donde se va a pintar la BarraEx.
				\param[in]	Espacio				: Espacio del control donde se va a pintar la BarraEx.
				\param[in]	TieneFoco			: Valor que determina si la BarraEx tiene el foco del raton (por defecto se usara la funcion Foco()).
				\param[in]	PintarConMascara	: Valor que determina si se va a pintar el contorno del control con SRCAND antes de pintar el control.
				\return		No devuelve nada.
				\remarks	Esta función esta preparada para pintar la BarraEx en un DC que no sea el suyo, o que sea compartido.
							Por ello debemos especificar las coordenadas donde se va a pintar, si tiene el foco del raton o no, y por ultimo si debemos
							pintar la mascara.
							El parametro PintarMascara solo es necesario si vamos a pintar la BarraEx en un DC que no es el suyo y requerimos el pintado
							del borde del control. Entonces la funcion de pintado pintara el contorno de la BarraEx con SRCAND, y luego pintara el control
							con SRC_PAINT para que no se vean graficos desfasados en el borde.
		*/
       void DWLBarraEx_Nucleo::BarraEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco, const bool PintarConMascara) {
			HDC		Buffer	= CreateCompatibleDC(hDC);
			RECT	RC		= { 0, 0, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top };
			RECT	EspacioInterior = { 1, 1, RC.right -2, RC.bottom -2 };
			HBITMAP Bmp		= CreateCompatibleBitmap(hDC, RC.right - 1, RC.bottom - 1);
			HBITMAP Viejo	= static_cast<HBITMAP>(SelectObject(Buffer, Bmp));
			float   Parte	= 0.0f;
			HRGN	Region	= CreateRoundRectRgn(0, 0, RC.right, RC.bottom, 5, 5);
			RECT	Barra;

			// Pinto la mascara del control si se requiere
			if (PintarConMascara == true) {
				FillRect(Buffer, &RC, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));
				FillRgn(Buffer, Region, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
				BitBlt(hDC, Espacio->left, Espacio->top, RC.right, RC.bottom, Buffer, 0, 0, SRCAND);
			}

			// Calculo la posicion de la barra partiendo de su orientacion
			Espacio->left ++; Espacio->top ++; //Espacio->right --; Espacio->bottom --;
			switch (BarraEx_Estilos.Orientacion) {
				case DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL	:
				case DWL_BARRAEX_PROGRESO_HORIZONTAL		:
					Barra.top = 1; Barra.bottom = RC.bottom -2;
					Barra.left = 1;
					Parte = static_cast<float>((Espacio->right - Espacio->left)) / static_cast<float>((_BarraEx_Maximo - _BarraEx_Minimo));
					Barra.right = static_cast<int>(Parte * static_cast<float>(_BarraEx_Valor  - _BarraEx_Minimo));
					break;
				case DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL	:
				case DWL_BARRAEX_PROGRESO_VERTICAL			:
					Barra.left = 1; Barra.right = RC.right -2;
					Barra.bottom = RC.bottom;
					Parte = static_cast<float>((Espacio->bottom - Espacio->top)) / static_cast<float>((_BarraEx_Maximo - _BarraEx_Minimo));
					Barra.top = Barra.bottom - static_cast<int>(Parte * static_cast<float>((_BarraEx_Valor - _BarraEx_Minimo))) - 1;
					break;
			}

			// Pinto el fondo
			BarraEx_Evento_Pintar_Fondo(Buffer, &EspacioInterior);

			// Pinto el degradado segun el estado y orientacion
			switch (_BarraEx_Estado) {
				case DWL_Enum_BarraEx_Estados_Normal     : BarraEx_Evento_Pintar_EstadoNormal(Buffer, &Barra);		break;
				case DWL_Enum_BarraEx_Estados_Resaltado  : BarraEx_Evento_Pintar_EstadoResaltado(Buffer, &Barra);	break;
				case DWL_Enum_BarraEx_Estados_Presionado : BarraEx_Evento_Pintar_EstadoPresionado(Buffer, &Barra);	break;
			}
			Espacio->left --; Espacio->top --; //Espacio->right ++; Espacio->bottom ++;

			// Pinto el borde
            if (BarraEx_Estilos.Orientacion == DWL_BARRAEX_PROGRESO_VERTICAL || BarraEx_Estilos.Orientacion == DWL_BARRAEX_PROGRESO_HORIZONTAL)
                BarraEx_Evento_Pintar_Borde(Buffer, Region, false);
            else
                BarraEx_Evento_Pintar_Borde(Buffer, Region, TieneFoco);


			// Pinto la barra ex en el DC especificado
			if (PintarConMascara == false)	BitBlt(hDC, Espacio->left, Espacio->top, RC.right-1, RC.bottom-1, Buffer, 0, 0, SRCCOPY);
			else							BitBlt(hDC, Espacio->left, Espacio->top, RC.right-1, RC.bottom-1, Buffer, 0, 0, SRCPAINT);

			// Elimino objetos GDI de la memoria
			DeleteObject(Region);
			SelectObject(Buffer, Viejo);
			DeleteObject(Bmp);
			DeleteDC(Buffer);
		};

		//! Función virtual que pinta la BarraEx en estado normal.
		/*! Esta función virtual pinta la BarraEx en su estado normal dentro del espacio y dc especificados.
				\fn			virtual inline void BarraEx_Evento_Pintar_EstadoNormal(HDC hDC, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar la BarraEx.
				\param[in]	Espacio	: Recta con el espacio del control BarraEx.
				\return		No devuelve nada.
				\remarks	Esta función pinta solo el estado normal de la BarraEx.
		*/
        void DWLBarraEx_Nucleo::BarraEx_Evento_Pintar_EstadoNormal(HDC hDC, RECT *Espacio) {
			if (BarraEx_Estilos.Orientacion == DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL || BarraEx_Estilos.Orientacion == DWL_BARRAEX_PROGRESO_VERTICAL)
				DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, BarraEx_Estilos.Colores.DegradadoSuperior(), BarraEx_Estilos.Colores.DegradadoInferior(), false);
			else
				DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, BarraEx_Estilos.Colores.DegradadoSuperior(), BarraEx_Estilos.Colores.DegradadoInferior(), true);
		};

		//! Función virtual que pinta la BarraEx en estado resaltado.
		/*! Esta función virtual pinta la BarraEx en su estado resaltado dentro del espacio y dc especificados.
				\fn			virtual inline void BarraEx_Evento_Pintar_EstadoResaltado(HDC hDC, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar la BarraEx.
				\param[in]	Espacio	: Recta con el espacio del control BarraEx.
				\return		No devuelve nada.
				\remarks	Esta función pinta solo el estado resaltado de la BarraEx.
		*/
        void DWLBarraEx_Nucleo::BarraEx_Evento_Pintar_EstadoResaltado(HDC hDC, RECT *Espacio) {
			if (BarraEx_Estilos.Orientacion == DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL || BarraEx_Estilos.Orientacion == DWL_BARRAEX_PROGRESO_VERTICAL)
				DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, BarraEx_Estilos.Colores.DegradadoResaltado(), BarraEx_Estilos.Colores.DegradadoInferior(), false);
			else
				DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, BarraEx_Estilos.Colores.DegradadoResaltado(), BarraEx_Estilos.Colores.DegradadoInferior(), true);
		};

		//! Función virtual que pinta la BarraEx en estado presionado.
		/*! Esta función virtual pinta la BarraEx en su estado presionado dentro del espacio y dc especificados.
				\fn			virtual inline void BarraEx_Evento_Pintar_EstadoPresionado(HDC hDC, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar la BarraEx.
				\param[in]	Espacio	: Recta con el espacio del control BarraEx.
				\return		No devuelve nada.
				\remarks	Esta función pinta solo el estado presionado de la BarraEx.
		*/
        void DWLBarraEx_Nucleo::BarraEx_Evento_Pintar_EstadoPresionado(HDC hDC, RECT *Espacio) {
			if (BarraEx_Estilos.Orientacion == DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL || BarraEx_Estilos.Orientacion == DWL_BARRAEX_PROGRESO_VERTICAL)
				DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, BarraEx_Estilos.Colores.DegradadoInferior(), BarraEx_Estilos.Colores.DegradadoSuperior(), false);
			else
				DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, BarraEx_Estilos.Colores.DegradadoInferior(), BarraEx_Estilos.Colores.DegradadoSuperior(), true);
		};

		//! Función virtual que pinta el fondo de la BarraEx.
		/*! Esta función virtual pinta el fondo BarraEx en el espacio y dc especificados.
				\fn			virtual inline void BarraEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar la BarraEx.
				\param[in]	Espacio	: Recta con el espacio del control BarraEx.
				\return		No devuelve nada.
				\remarks	Esta función pinta solo el fondo de la BarraEx.
		*/
        void DWLBarraEx_Nucleo::BarraEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio) {
			HBRUSH Brocha = CreateSolidBrush(BarraEx_Estilos.Colores.Fondo());
			FillRect(hDC, Espacio, Brocha);
			DeleteObject(Brocha);
		};

		//! Función virtual que pinta el borde de la BarraEx.
		/*! Esta función virtual pinta el borde BarraEx en el espacio y dc especificados.
				\fn			virtual inline void BarraEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco);
				\param[in]	hDC			: hDC donde se va a pintar la BarraEx.
				\param[in]	Region		: Region que contiene el borde de la BarraEx.
				\param[in]	TieneFoco	: Valor en el que determinamos si pintamos el borde con foco o sin foco.
				\return		No devuelve nada.
				\remarks	Esta función pinta solo el borde de la BarraEx.
		*/
        void DWLBarraEx_Nucleo::BarraEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco) {
			HBRUSH ColorBorde;
			if (TieneFoco == true)	ColorBorde = CreateSolidBrush(BarraEx_Estilos.Colores.BordeSeleccionado());
			else					ColorBorde = CreateSolidBrush(BarraEx_Estilos.Colores.Borde());

//			if (BarraEx_Estilos.Borde == true) {
			HBRUSH ColorBordeLight = CreateSolidBrush(BarraEx_Estilos.Colores.BordeClaro());
			FrameRgn(hDC, Region, ColorBordeLight, 2, 2);
			FrameRgn(hDC, Region, ColorBorde, 1, 1);
			DeleteObject(ColorBordeLight);
//			}
//			else {
//				FrameRgn(hDC, Region, ColorBorde, 1, 1);
//			}
			DeleteObject(ColorBorde);
		};


		//! Función que suma el valor actual para la BarraEx.
		/*! Esta funcion suma el valor actual para la BarraEx.
				\fn			inline virtual int BarraEx_Valor_SumarValor(const long SumValor);
				\param[in]	SumValor : Valor que se sumara al valor actual de la BarraEx.
				\return		Devuelve el valor actual.
		*/
        int DWLBarraEx_Nucleo::BarraEx_Valor_SumarValor(const long SumValor) {
			if (_BarraEx_Valor + SumValor < _BarraEx_Maximo)	_BarraEx_Valor += SumValor;
			else												_BarraEx_Valor = _BarraEx_Maximo;
			return _BarraEx_Valor;
		};

		//! Función que resta el valor actual para la BarraEx.
		/*! Esta funcion resta el valor actual para la BarraEx.
				\fn			inline virtual int BarraEx_Valor_RestarValor(const long RestValor);
				\param[in]	RestValor : Valor que se restara al valor actual de la BarraEx.
				\return		Devuelve el valor actual.
		*/
        int DWLBarraEx_Nucleo::BarraEx_Valor_RestarValor(const long RestValor) {
			if (_BarraEx_Valor - RestValor > _BarraEx_Minimo)	_BarraEx_Valor -= RestValor;
			else												_BarraEx_Valor = _BarraEx_Minimo;
			return _BarraEx_Valor;
		};


		//! Función que procesa el movimiento del mouse en la BarraEx.
		/*! Esta función procesa el movimiento del mouse en la BarraEx.
				\fn			BOOL BarraEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT wParam);
				\param[in]	hWndControl		: HWND del control que contiene la BarraEx.
				\param[in]	RectaControl	: Recta con el espacio de la BarraEx.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_Movimiento del control que vaya a contener la BarraEx.
				\sa			BarraEx_Mouse_BotonPresionado(), BarraEx_Mouse_BotonSoltado()
		*/
        BOOL DWLBarraEx_Nucleo::BarraEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param) {
			if (BarraEx_Estilos.Orientacion == DWL_BARRAEX_PROGRESO_HORIZONTAL || BarraEx_Estilos.Orientacion == DWL_BARRAEX_PROGRESO_VERTICAL) return FALSE;
			POINT Pt = { cX, cY };
			BOOL DentroControl = PtInRect(RectaControl, Pt);
			if (_BarraEx_Presionado == false) {
				if (DentroControl == TRUE)	_BarraEx_Estado = DWL_Enum_BarraEx_Estados_Resaltado;
				else						_BarraEx_Estado = DWL_Enum_BarraEx_Estados_Normal;
				return DentroControl;
			}
			else {
				if (hWndControl != NULL) PostMessage(GetParent(hWndControl), DWL_BARRAEX_NUEVO_VALOR, (WPARAM)GetWindowLongPtr(hWndControl, GWL_ID), 0);
				_BarraEx_Estado = DWL_Enum_BarraEx_Estados_Presionado;
				_BarraEx_Valor = BarraEx_MirarValor(RectaControl, cX, cY);
				return TRUE;
			}
		};

		//! Función que procesa los botones soltados del mouse en la BarraEx
		/*! Esta función procesa los botones soltados del mouse en la BarraEx.
				\fn			BOOL BarraEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	hWndControl		: HWND del control que contiene la BarraEx.
				\param[in]	RectaControl	: Recta con el espacio de la BarraEx.
				\param[in]	Boton			: Boton del mouse presionado.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonSoltado del control que vaya a contener la BarraEx.
				\sa			BarraEx_Mouse_Movimiento(), BarraEx_Mouse_BotonPresionado()
		*/
        BOOL DWLBarraEx_Nucleo::BarraEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			if (BarraEx_Estilos.Orientacion == DWL_BARRAEX_PROGRESO_HORIZONTAL || BarraEx_Estilos.Orientacion == DWL_BARRAEX_PROGRESO_VERTICAL) return false;
			if (_BarraEx_Presionado == true) {
				PostMessage(GetParent(hWndControl), DWL_BARRAEX_NUEVO_VALOR, (WPARAM)GetWindowLongPtr(hWndControl, GWL_ID), 0);
				PostMessage(GetParent(hWndControl), DWL_BARRAEX_MOUSE_BOTONSOLTADO, (WPARAM)GetWindowLongPtr(hWndControl, GWL_ID), (LPARAM)Boton);
				POINT Pt = { cX, cY };
				ReleaseCapture();
				_BarraEx_Presionado = false;
				if (PtInRect(RectaControl, Pt) != 0) { // Si esta dentro*/
					_BarraEx_Estado = DWL_Enum_BarraEx_Estados_Resaltado;
					_BarraEx_Valor = BarraEx_MirarValor(RectaControl, cX, cY);
				}
				else {
					_BarraEx_Estado = DWL_Enum_BarraEx_Estados_Normal;
				}
				return TRUE;
			}
			return FALSE;
		};

		//! Función que procesa los botones presionados del mouse en la BarraEx.
		/*! Esta función procesa los botones presionados del mouse en la BarraEx.
				\fn			BOOL BarraEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	hWndControl		: HWND del control que contiene la BarraEx.
				\param[in]	RectaControl	: Recta con el espacio de la BarraEx.
				\param[in]	Boton			: Boton del mouse presionado.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonPresionado del control que vaya a contener la BarraEx.
				\sa			BarraEx_Mouse_Movimiento(), BarraEx_Mouse_BotonSoltado()
		*/
        BOOL DWLBarraEx_Nucleo::BarraEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			POINT Pt = { cX, cY };
			if (PtInRect(RectaControl, Pt) == TRUE) {
				if (BarraEx_Estilos.Orientacion == DWL_BARRAEX_PROGRESO_HORIZONTAL || BarraEx_Estilos.Orientacion == DWL_BARRAEX_PROGRESO_VERTICAL) return false;
				PostMessage(GetParent(hWndControl), DWL_BARRAEX_NUEVO_VALOR, (WPARAM)GetWindowLongPtr(hWndControl, GWL_ID), 0);
				SetCapture(hWndControl);
				_BarraEx_Presionado = true;
				_BarraEx_Estado = DWL_Enum_BarraEx_Estados_Presionado;
				_BarraEx_Valor = BarraEx_MirarValor(RectaControl, cX, cY);
				return TRUE;
			}
			return FALSE;
		};

		//! Función que retorna el valor resultado de las coordenadas especificadas.
		/*! Esta función devuelve el valor resultado de las coordenadas especificadas.
				\fn         long BarraEx_MirarValor(RECT *Espacio, const int cX, const int cY);
				\param[in]	Espacio	: Recta que contiene el espacio de la BarraEx.
				\param[in]	cX		: Coordenada X.
				\param[in]	cY		: Coordenada Y.
				\return		Devuelve el valor que corresponderia a las coordenadas introducidas.
		*/
        long DWLBarraEx_Nucleo::BarraEx_MirarValor(RECT *Espacio, const int cX, const int cY) {
			float Parte = 0.0f;
			long  Ret = 0;
			if (BarraEx_Estilos.Orientacion == DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL || BarraEx_Estilos.Orientacion == DWL_BARRAEX_PROGRESO_HORIZONTAL)      {
				Parte = static_cast<float>(_BarraEx_Maximo - _BarraEx_Minimo) / static_cast<float>(Espacio->right - Espacio->left);
				Ret = static_cast<long>(static_cast<float>(cX - Espacio->left) * Parte) - _BarraEx_Minimo;
			}
			else /* (_Orientacion = BarraDesplazamientoVertical) */ {
				Parte = static_cast<float>(_BarraEx_Maximo - _BarraEx_Minimo) / static_cast<float>(Espacio->bottom - Espacio->top);
				Ret = (_BarraEx_Maximo - _BarraEx_Minimo) - static_cast<long>(static_cast<float>(cY - Espacio->top) * Parte) + _BarraEx_Minimo;
			}
			if (Ret > _BarraEx_Maximo) Ret = _BarraEx_Maximo;
			if (Ret < _BarraEx_Minimo) Ret = _BarraEx_Minimo;
			return Ret;
		};


    };
};
