/*! \file DWLToolTipEx.cpp
	\brief		Archivo que contiene las definiciones de las clases del ToolTipEx.


	\details	La clase DWLToolTipEx esta enfocada de forma que podamos crear tooltips facilmente y con un aspecto agradable ademas de ordenado.		\n	
				Para mostrar un ToolTipEx lo primero que hay que hacer es añadirle aquellos datos que queremos mostrar.									\n
				Tenemos varias funciones que se ajustan a las formas mas comunes de mostrar tooltips, 
				para empezar tenemos la función DWL::ControlesEx::DWLToolTipEx::AgregarTextoNegrita()
				que nos permite agregar un texto de una o varias lineas al tooltip, y que podriamos usar como titulo.									\n
				En segundo lugar podriamos utilizar la función DWL::ControlesEx::DWLToolTipEx::AgregarTextoCaracterTexto() para añadirle
				una linea con 2 textos delimitados por un caracter separador. Podriamos usar esta funcion tantas veces como se necesite para 
				hacer una lista de datos ordenada y justificada por columnas.																			\n
																																						\n
				<table border = 0 align ='right'><tr><td> \image html ToolTipEx.jpg </td></tr></table>

				\section Clases_Sec Descripción breve de las clases que contiene este archivo :
				 - DWL::ControlesEx::DWLToolTipEx_Colores :																								\n
						Clase que enlaza los colores a la configuracion del skin por defecto.															\n\n
				 - DWL::ControlesEx::DWLToolTipEx_ObjetoTextoCaracterTexto :																			\n
						Clase que contiene un dos textos alineados por un caracter separador.															\n\n
				 - DWL::ControlesEx::DWLToolTipEx_ObjetoTextoCaracterIcono :																			\n
						Clase que contiene un texto y un icono alineados por un caracter separador.														\n\n
				 - DWL::ControlesEx::DWLToolTipEx_ObjetoIconoTexto :																					\n
						Clase que contiene un icono y un texto (ideal para mostrar titulos).															\n\n		
				 - DWL::ControlesEx::DWLToolTipEx_Objeto :																								\n
						Clase que engloba todos los objetos posibles en el ToolTipEx.																	\n\n		
				 - DWL::ControlesEx::DWLToolTipEx :																										\n
						Clase que controla el ToolTipEx.																								\n		


	\author		devildrey33
	\version	0.5
	\date		10/12/2009

	\remarks
				Archivo creado por devildrey33 el dia [26/02/2009] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n	
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n	
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n	
*/

#include "DWLToolTipEx.h"
#include "DWLGraficos.h"


#define TT_MARGEN		 16 // 8 pixeles por banda
#define TT_ESPACIO_ANCHO 5 
#define TT_ESPACIO_ALTO  3 
#define TT_CURVA_REGION  11


namespace DWL {
	namespace ControlesEx {

        DWLToolTipEx::DWLToolTipEx(void) : DWL::ControlesEx::Base::DWLControlEx() {
			_AnchoRequerido = 0;
			_AltoRequerido = 0;
//			Fuentes.Enlazar(DWL::SO::DWLEstilos::Fuentes);
		}

		DWLToolTipEx::~DWLToolTipEx(void) {
			BorrarMemoria();
            Destruir();
		}

		void DWLToolTipEx::BorrarMemoria(void) {
			for (size_t i = 0; i < _Objetos.size(); i++) delete _Objetos[i];
			_Objetos.resize(0);
		}

		void DWLToolTipEx::MostrarToolTipEx(const BYTE nOpacidad) {
			if (_hWnd != NULL) return;
			if (_Objetos.size() == 0) return;
			HWND hWndFoco = GetFocus();

//			_PrimerMouseMove = true;

			POINT Pos; 
			GetCursorPos(&Pos);

			CalcularTam();
			#if COMPILADOR != COMPILADOR_VC6
				// Obtenemos el monitor que esta debajo del mouse
				HMONITOR Monitor = MonitorFromPoint(Pos, MONITOR_DEFAULTTONEAREST);
				MONITORINFO MonitorInfo;
				MonitorInfo.cbSize = sizeof(MONITORINFO);
				GetMonitorInfo(Monitor, &MonitorInfo);
			
				// pisara el mouse, lo mostramos por la punta contraria
				if ((Pos.x + 10) + _AnchoRequerido > MonitorInfo.rcWork.right && (Pos.y + 20) + _AltoRequerido > MonitorInfo.rcWork.bottom) {
					Pos.x -= _AnchoRequerido + 10;
					Pos.y -= _AltoRequerido + 20;
				}
				else if ((Pos.x + 10) + _AnchoRequerido > MonitorInfo.rcWork.right) {
					Pos.x = (MonitorInfo.rcWork.right - _AnchoRequerido) - 10;
				}
				else if ((Pos.y + 20) + _AltoRequerido > MonitorInfo.rcWork.bottom) {
					Pos.y = (MonitorInfo.rcWork.bottom - _AltoRequerido) - 20;
				}
			#endif
			_hWnd = CrearControl(0, TEXT("DWL::ControlesEx::DWLToolTipEx"), WS_POPUP, 0, Pos.x + 10, Pos.y + 20, _AnchoRequerido, _AltoRequerido, 0, WS_EX_TOPMOST | WS_EX_TOOLWINDOW, 0);
			HRGN Region = CreateRoundRectRgn(0, 0, _AnchoRequerido + 1, _AltoRequerido + 1, TT_CURVA_REGION, TT_CURVA_REGION);
			SetWindowRgn(_hWnd, Region, FALSE); // Asigno la region a la ventana
			// Una vez se asigna la region pasa a formar parte del sistema y la que teniamos queda invalidada,
			// por lo que hay que volverla a crear.
			Opacidad(nOpacidad);
			Visible(true);
			SetWindowPos(_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			SetFocus(hWndFoco);
			
		}

		LRESULT DWLToolTipEx::Evento_Cerrar(void) {
			BorrarMemoria();
			return 0;
		}

		DWLString *DWLToolTipEx::AgregarTexto(const TCHAR *nTexto) {
			DWLString *Tmp = new DWLString;
			Tmp->operator = (nTexto);
			DWLToolTipEx_Objeto *ObjetoTmp = new DWLToolTipEx_Objeto(PtrToLong(Tmp), Enum_ToolTipEx_TiposObjeto_Texto);
			_Objetos.push_back(ObjetoTmp);
			return Tmp;
		}

		DWLString *DWLToolTipEx::AgregarTextoNegrita(const TCHAR *nTexto) {
			DWLString *Tmp = new DWLString;
			Tmp->operator = (nTexto);
			DWLToolTipEx_Objeto *ObjetoTmp = new DWLToolTipEx_Objeto(PtrToLong(Tmp), Enum_ToolTipEx_TiposObjeto_TextoNegrita);
			_Objetos.push_back(ObjetoTmp);
			return Tmp;
		}

		DWLToolTipEx_ObjetoTextoCaracterTexto *DWLToolTipEx::AgregarTextoCaracterTexto(const TCHAR *nTexto1, const TCHAR nCaracter, const TCHAR *nTexto2) {
			DWLToolTipEx_ObjetoTextoCaracterTexto *Tmp = new DWLToolTipEx_ObjetoTextoCaracterTexto(nTexto1, nCaracter, nTexto2);
			DWLToolTipEx_Objeto *ObjetoTmp = new DWLToolTipEx_Objeto(PtrToLong(Tmp), Enum_ToolTipEx_TiposObjeto_TextoCaracterTexto);
			_Objetos.push_back(ObjetoTmp);
			return Tmp;
		}

		DWLToolTipEx_ObjetoTextoCaracterTexto *DWLToolTipEx::AgregarTextoCaracterTexto(const TCHAR *nTexto1, const TCHAR nCaracter, const int nTexto2) {
			DWLString TmpTxt2;
			TmpTxt2 = nTexto2;
			DWLToolTipEx_ObjetoTextoCaracterTexto *Tmp = new DWLToolTipEx_ObjetoTextoCaracterTexto(nTexto1, nCaracter, TmpTxt2());
			DWLToolTipEx_Objeto *ObjetoTmp = new DWLToolTipEx_Objeto(PtrToLong(Tmp), Enum_ToolTipEx_TiposObjeto_TextoCaracterTexto);
			_Objetos.push_back(ObjetoTmp);
			return Tmp;
		}

		DWLToolTipEx_ObjetoTextoCaracterIcono *DWLToolTipEx::AgregarTextoCaracterIcono(const TCHAR *nTexto, const TCHAR nCaracter, const int nIcono, const int nAnchoIcono, const int nAltoIcono, const float nFraccion) {
			DWLToolTipEx_ObjetoTextoCaracterIcono *Tmp = new DWLToolTipEx_ObjetoTextoCaracterIcono(nTexto, nCaracter, nIcono, nAltoIcono, nAnchoIcono, nFraccion);
			DWLToolTipEx_Objeto *ObjetoTmp = new DWLToolTipEx_Objeto(PtrToLong(Tmp), Enum_ToolTipEx_TiposObjeto_TextoCaracterIcono);
			_Objetos.push_back(ObjetoTmp);
			return Tmp;
		}

		DWLToolTipEx_ObjetoIconoTexto *DWLToolTipEx::AgregarIconoTexto(const int nIcono, const int nAnchoIcono, const int nAltoIcono, const TCHAR *nTexto) {
			DWLToolTipEx_ObjetoIconoTexto *Tmp = new DWLToolTipEx_ObjetoIconoTexto(nIcono, nAnchoIcono, nAltoIcono, nTexto);
			DWLToolTipEx_Objeto *ObjetoTmp = new DWLToolTipEx_Objeto(PtrToLong(Tmp), Enum_ToolTipEx_TiposObjeto_IconoTexto);
			_Objetos.push_back(ObjetoTmp);
			return Tmp;
		}
		
		SIZE DWLToolTipEx::_ObtenerTamTexto(HDC hDC, DWL::DWLString &nTexto) {
			SIZE   Ret = { 0, 0 };
			SIZE   TmpSize;
			size_t Cont = 0;
			DWL::DWLString TmpTexto;
			// Escaneamos todo el string y lo separamos por lineas para calcular su tamaño en pixeles
			for (size_t i = 0; i < nTexto.Tam(); i++) {
				if (nTexto[i] == TEXT('\n') || i == nTexto.Tam() -1) {
					TmpTexto.Borrar();
					TmpTexto = nTexto.SubStr(Cont, (i - Cont) + 1);
					TmpSize.cx = 0;
					TmpSize.cy = 0;
					GetTextExtentPoint32(hDC, TmpTexto(), TmpTexto.Tam(), &TmpSize);
					if (TmpSize.cx > Ret.cx) Ret.cx = TmpSize.cx;
					Ret.cy += TmpSize.cy + TT_ESPACIO_ALTO;
					Cont = i;
				}
			}
			return Ret;
		}

		// Función que calcula el ancho y alto necesarios para mostrar todos los objetos
		void DWLToolTipEx::CalcularTam(void) {
			HDC	   		hDC			= CreateCompatibleDC(NULL);
			HBITMAP		Bmp			= CreateCompatibleBitmap(hDC, 100, 100);
			HBITMAP		Viejo		= static_cast<HBITMAP>(SelectObject(hDC, Bmp));
			HFONT		FViejo		= static_cast<HFONT>(SelectObject(hDC, Estilos.Fuentes.Normal()));
			SIZE		Ret			= { 0, 0 };
			int			AnchoTmp	= TT_MARGEN;
			DWLString  *Tmp			= NULL; 
			DWLString	TextoSeparado;
			_AnchoRequerido = TT_MARGEN;
			_AltoRequerido  = TT_MARGEN;

			DWLToolTipEx_ObjetoTextoCaracterIcono *OTCI = NULL;
			DWLToolTipEx_ObjetoTextoCaracterTexto *OTCT = NULL;
			DWLToolTipEx_ObjetoIconoTexto		  *OIT  = NULL;
			DWLString							  *OT   = NULL;

			// Miramos el ancho mas grande del primer texto de todos los objetos TextoCaracterTexto
			// esto se hace porque el Texto2 va justificado segun el ancho mas grande del Texto2
			int AnchoCaracter	= 0;
			size_t			i	= 0;
			_AnchoTexto1 = 0;
			for (i = 0; i < _Objetos.size(); i++) {
				if (_Objetos[i]->Tipo() == Enum_ToolTipEx_TiposObjeto_TextoCaracterTexto || _Objetos[i]->Tipo() == Enum_ToolTipEx_TiposObjeto_TextoCaracterIcono) {
					OTCT = _Objetos[i]->ObtenerTextoCaracterTexto();
					GetTextExtentPoint32(hDC, OTCT->Texto1(), OTCT->TamTexto1(), &Ret);
					if (_AnchoTexto1 < Ret.cx) _AnchoTexto1 = Ret.cx;
				}
			}
			
			// Miramos todos los anchos definitivos de los objetos y elegimos el mas grande, ademas de obtener el alto total necesario
			for (i = 0; i < _Objetos.size(); i++) {
				switch (_Objetos[i]->Tipo()) {
					// Falta implementar para varias lineas de texto
					case Enum_ToolTipEx_TiposObjeto_Texto :
						OT = _Objetos[i]->ObtenerTexto();
						SelectObject(hDC, Estilos.Fuentes.Normal());
						Ret = _ObtenerTamTexto(hDC, *OT);
//						GetTextExtentPoint32(hDC, OT->Texto(), OT->Tam(), &Ret);
						AnchoTmp = Ret.cx + TT_MARGEN;
						if (_AnchoRequerido < AnchoTmp) _AnchoRequerido = AnchoTmp;
						_AltoRequerido += Ret.cy;
						break;
					case Enum_ToolTipEx_TiposObjeto_TextoNegrita :
						OT = _Objetos[i]->ObtenerTexto();
						SelectObject(hDC, Estilos.Fuentes.Negrita());
//						GetTextExtentPoint32(hDC, OT->Texto(), OT->Tam(), &Ret);
						Ret = _ObtenerTamTexto(hDC, *OT);
						AnchoTmp = Ret.cx + TT_MARGEN;
						if (_AnchoRequerido < AnchoTmp) _AnchoRequerido = AnchoTmp;
						_AltoRequerido += Ret.cy;
						break;
					case Enum_ToolTipEx_TiposObjeto_TextoCaracterTexto :
						OTCT = _Objetos[i]->ObtenerTextoCaracterTexto();
						SelectObject(hDC, Estilos.Fuentes.Normal());
						GetTextExtentPoint32(hDC, OTCT->Caracter(), 1, &Ret);
//						Ret = _ObtenerTamTexto(hDC, *OTCT->_Texto1);
						AnchoCaracter = Ret.cx;
						if (OTCT->TamTexto2() > 0) Ret = _ObtenerTamTexto(hDC, OTCT->_Texto2);
							//GetTextExtentPoint32(hDC, OTCT->Texto2(), OTCT->TamTexto2(), &Ret);
						AnchoTmp = TT_MARGEN + _AnchoTexto1 + TT_ESPACIO_ANCHO + AnchoCaracter + TT_ESPACIO_ANCHO + Ret.cx; // Ancho = MARGEN + TEXTO1 + ESPACIO_ANCHO + CARACTER + ESPACIO_ANCHO + TEXTO2
						if (_AnchoRequerido < AnchoTmp) _AnchoRequerido = AnchoTmp;
						_AltoRequerido += Ret.cy;
						break;
					case Enum_ToolTipEx_TiposObjeto_TextoCaracterIcono :
						OTCI = _Objetos[i]->ObtenerTextoCaracterIcono();
						SelectObject(hDC, Estilos.Fuentes.Normal());
						GetTextExtentPoint32(hDC, OTCI->Caracter(), 1, &Ret);
						AnchoCaracter = Ret.cx;
						AnchoTmp = TT_MARGEN + _AnchoTexto1 + TT_ESPACIO_ANCHO + AnchoCaracter + TT_ESPACIO_ANCHO + static_cast<int>(static_cast<float>(OTCI->AnchoIcono()) * OTCI->Fraccion()); // Ancho = MARGEN + TEXTO1 + ESPACIO_ANCHO + CARACTER + ESPACIO_ANCHO + (ICONO * FRACCION)
						if (_AnchoRequerido < AnchoTmp) _AnchoRequerido = AnchoTmp;
						if ((Ret.cy + TT_ESPACIO_ALTO) > (OTCI->AltoIcono() + 2))	_AltoRequerido += Ret.cy;	// Alto += TEXTO + ESPACIO_ALTO
						else														_AltoRequerido += OTCI->AltoIcono() + 2;						// Alto += ICONO + ESPACIO_ALTO
						break;
					case Enum_ToolTipEx_TiposObjeto_IconoTexto :
						OIT = _Objetos[i]->ObtenerIconoTexto();
						SelectObject(hDC, Estilos.Fuentes.Negrita());
						Ret = _ObtenerTamTexto(hDC, OIT->_Texto);
//						GetTextExtentPoint32(hDC, OIT->Texto(), OIT->TamTexto(), &Ret);
						AnchoTmp = TT_MARGEN + (OIT->AnchoIcono() + 2) + Ret.cx + TT_ESPACIO_ALTO;								// Ancho = MARGEN + ICONO + TEXTO + 1 (SOMBRA)
						if ((Ret.cy + TT_ESPACIO_ALTO) > (OIT->AltoIcono() + 2))	_AltoRequerido += Ret.cy;	// Alto += TEXTO + ESPACIO_ALTO
						else														_AltoRequerido += OIT->AltoIcono() + 2;						// Alto += ICONO + ESPACIO_ALTO
						if (_AnchoRequerido < AnchoTmp) _AnchoRequerido = AnchoTmp;
						break;
				}
			}
			// Eliminando objetos de memoria
			SelectObject(hDC, FViejo);
			SelectObject(hDC, Viejo);
			DeleteObject(Bmp);
			DeleteDC(hDC);
		}

		const UINT DWLToolTipEx::_PintarTexto(HDC hDC, DWL::DWLString &nTexto, const int cX, const int cY) {
			SIZE   Ret = { 0, 0 };
			SIZE   TmpSize;
			size_t Cont = 0;
			DWL::DWLString TmpTexto;
			// Escaneamos todo el string y lo separamos por lineas para calcular su tamaño en pixeles
			for (size_t i = 0; i < nTexto.Tam(); i++) {
				if (nTexto[i] == TEXT('\n') || i == nTexto.Tam() -1) {
					TmpTexto.Borrar();
					TmpTexto.AgregarTexto(&nTexto[Cont], (i - Cont) + 1);
					TmpSize.cx = 0;
					TmpSize.cy = 0;
					SetTextColor(hDC, Estilos.Colores.TextoSombra());
					TextOut(hDC, cX + 1, cY + 1 + Ret.cy, TmpTexto(), TmpTexto.Tam());
					SetTextColor(hDC, Estilos.Colores.TextoNormal());
					TextOut(hDC, cX, cY + Ret.cy, TmpTexto(), TmpTexto.Tam());
					GetTextExtentPoint32(hDC, TmpTexto(), TmpTexto.Tam(), &TmpSize);
//					if (TmpSize.cx > Ret.cx) Ret.cx = TmpSize.cx;
					Ret.cy += TmpSize.cy + TT_ESPACIO_ALTO;
					Cont = i;
				}
			}
			if (nTexto.Tam() == 0) {
				GetTextExtentPoint32(hDC, TEXT(" "), 1, &TmpSize);
				Ret.cy += TmpSize.cy + TT_ESPACIO_ALTO;
			}
			return Ret.cy;
		}

		LRESULT DWLToolTipEx::Evento_Pintar(HDC hDC, PAINTSTRUCT &PS) {
			HDC		Buffer			= CreateCompatibleDC(hDC);
			HBITMAP Bmp				= CreateCompatibleBitmap(hDC, _AnchoRequerido, _AltoRequerido);
			HBITMAP Viejo			= static_cast<HBITMAP>(SelectObject(Buffer, Bmp));
			HRGN	Region			= CreateRoundRectRgn(0, 0, _AnchoRequerido + 1, _AltoRequerido + 1, TT_CURVA_REGION, TT_CURVA_REGION); //
			HBRUSH  Borde			= CreateSolidBrush(Estilos.Colores.Borde()); //
			HFONT   FViejo			= static_cast<HFONT>(SelectObject(Buffer, Estilos.Fuentes.Normal()));
			int		YA				= TT_MARGEN / 2; // Y de inicio
			SIZE	Ret				= { 0, 0 };
			int		AnchoA			= 0;
			int     AltoNormal		= 0;
			int     AltoNegrita		= 0;
			int     AltoNegritaF	= 0;
			HICON   Icono			= NULL;
			int		CentradoY		= 0;
			int		K				= 0;
			float   ParteIcono		= 0.0f;
			HDC		hDCPI			= NULL;
			HBITMAP	BMPPI			= NULL;
			HBITMAP	ViejoPI			= NULL;

			DWLToolTipEx_ObjetoTextoCaracterIcono *OTCI	= NULL;
			DWLToolTipEx_ObjetoTextoCaracterTexto *OTCT	= NULL;
			DWLToolTipEx_ObjetoIconoTexto         *OIT	= NULL;
			DWLString							  *OT   = NULL;
			
			// Obtengo tamaños de las alturas de lina para las 2 fuentes
			GetTextExtentPoint32(Buffer, TEXT(" "), 1, &Ret); // Obtengo el tamaño de la linea normal
			AltoNormal = Ret.cy;
			SelectObject(Buffer, Estilos.Fuentes.Normal());
			GetTextExtentPoint32(Buffer, TEXT(" "), 1, &Ret); // Obtengo el tamaño de la linea negrita
			AltoNegrita = Ret.cy;
			if (AltoNegrita < 16) AltoNegritaF = 16; // Si es mas pequeño que 16 asigno el tamaño del icono
			else				  AltoNegritaF = AltoNegrita;
			
			// Pinto el fondo y el borde
			DWL::GDI::PintarGradient(Buffer, 0, 0, _AnchoRequerido, _AltoRequerido, Estilos.Colores.DegradadoSuperior(), Estilos.Colores.DegradadoInferior());

			FrameRgn(Buffer, Region, Borde, 2, 2);
			DeleteObject(Borde);
			DeleteObject(Region);
			UINT MasY = 0;
			// Pinto los objetos
			SetTextColor(Buffer, Estilos.Colores.TextoNormal());
			SetBkMode(Buffer, TRANSPARENT);
			for (size_t i = 0; i < _Objetos.size(); i++) {
				switch (_Objetos[i]->Tipo()) {
					case Enum_ToolTipEx_TiposObjeto_Texto :
						OT = _Objetos[i]->ObtenerTexto();
						SelectObject(Buffer, Estilos.Fuentes.Normal());
						MasY = _PintarTexto(Buffer, *OT, TT_MARGEN / 2, YA);
/*						SetTextColor(Buffer, Estilos.Colores.TextoSombra());
						TextOut(Buffer, (TT_MARGEN / 2) + 1, YA + 1, OT->Texto(), OT->Tam());
						SetTextColor(Buffer, Estilos.Colores.TextoNormal());
						TextOut(Buffer, TT_MARGEN / 2, YA, OT->Texto(), OT->Tam());*/
						YA += MasY;
//						YA += AltoNormal + TT_ESPACIO_ALTO;
						break;
					case Enum_ToolTipEx_TiposObjeto_TextoNegrita :
						OT = _Objetos[i]->ObtenerTexto();
						SelectObject(Buffer, Estilos.Fuentes.Negrita());
						MasY = _PintarTexto(Buffer, *OT, TT_MARGEN / 2, YA);
/*						SetTextColor(Buffer, Estilos.Colores.TextoSombra());
						TextOut(Buffer, (TT_MARGEN / 2) + 1, YA + 1, OT->Texto(), OT->Tam());
						SetTextColor(Buffer, Estilos.Colores.TextoNormal());
						TextOut(Buffer, TT_MARGEN / 2, YA, OT->Texto(), OT->Tam());*/
						YA += MasY;
//						YA += AltoNegrita + TT_ESPACIO_ALTO;
						break;
					case Enum_ToolTipEx_TiposObjeto_TextoCaracterTexto :
						OTCT = _Objetos[i]->ObtenerTextoCaracterTexto();
						SelectObject(Buffer, Estilos.Fuentes.Normal());
						SetTextColor(Buffer, Estilos.Colores.TextoSombra());
						AnchoA = ((TT_MARGEN / 2) + _AnchoTexto1) + TT_ESPACIO_ANCHO;
						TextOut(Buffer, (TT_MARGEN / 2) + 1, YA + 1, OTCT->Texto1(), OTCT->TamTexto1());
						TextOut(Buffer, AnchoA + 1, YA + 1, OTCT->Caracter(), 1);
						//TextOut(Buffer, AnchoA + (TT_ESPACIO_ANCHO * 2) + 1, YA + 1, OTCT->Texto2(), OTCT->TamTexto2());
						SetTextColor(Buffer, Estilos.Colores.TextoNormal());
						TextOut(Buffer, TT_MARGEN / 2, YA, OTCT->Texto1(), OTCT->TamTexto1());
						TextOut(Buffer, AnchoA, YA, OTCT->Caracter(), 1);
						//TextOut(Buffer, AnchoA + (TT_ESPACIO_ANCHO * 2), YA, OTCT->Texto2(), OTCT->TamTexto2());
						MasY = _PintarTexto(Buffer, OTCT->_Texto2, AnchoA + (TT_ESPACIO_ANCHO * 2), YA);

						YA += MasY;
//						YA += AltoNormal + TT_ESPACIO_ALTO;
						break;
					case Enum_ToolTipEx_TiposObjeto_TextoCaracterIcono :
						OTCI = _Objetos[i]->ObtenerTextoCaracterIcono();
						SelectObject(Buffer, Estilos.Fuentes.Normal());
						// Pinto sombras del texto
						SetTextColor(Buffer, Estilos.Colores.TextoSombra());
						AnchoA = ((TT_MARGEN / 2) + _AnchoTexto1) + TT_ESPACIO_ANCHO;
						TextOut(Buffer, (TT_MARGEN / 2) + 1, YA + 1, OTCI->Texto(), OTCI->TamTexto());
						TextOut(Buffer, AnchoA + 1, YA + 1, OTCI->Caracter(), 1);
						// Pinto el texto
						SetTextColor(Buffer, Estilos.Colores.TextoNormal());
						TextOut(Buffer, TT_MARGEN / 2, YA, OTCI->Texto(), OTCI->TamTexto());
						TextOut(Buffer, AnchoA, YA, OTCI->Caracter(), 1);
						// Pinto el icono multiplicado tantas veces como diga la fraccion
						Icono = static_cast<HICON>(LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(OTCI->Icono()), IMAGE_ICON, OTCI->AnchoIcono(), OTCI->AltoIcono(), LR_DEFAULTCOLOR));
						for (K = 0; K < static_cast<int>(OTCI->Fraccion()); K ++) {
							DrawIconEx(Buffer, (AnchoA + (TT_ESPACIO_ANCHO * 2)) + (K * OTCI->AnchoIcono()), YA, Icono, OTCI->AnchoIcono(), OTCI->AltoIcono(), 0, 0, DI_NORMAL);
						}
						ParteIcono = (OTCI->Fraccion() - static_cast<float>(K));
						// Si queda menos de una unidad tengo que pintar solo un trozo del icono
						if (ParteIcono != 0.0f) {
							hDCPI = CreateCompatibleDC(Buffer);
							BMPPI = CreateCompatibleBitmap(Buffer, OTCI->AnchoIcono(), OTCI->AltoIcono());
							ViejoPI = static_cast<HBITMAP>(SelectObject(hDCPI, BMPPI));
							BitBlt(hDCPI, 0, 0, OTCI->AnchoIcono(), OTCI->AltoIcono(), Buffer, (AnchoA + (TT_ESPACIO_ANCHO * 2)) + (K * OTCI->AnchoIcono()), YA, SRCCOPY);
							DrawIconEx(hDCPI, 0, 0, Icono, OTCI->AnchoIcono(), OTCI->AltoIcono(), 0, 0, DI_NORMAL);
							BitBlt(Buffer, (AnchoA + (TT_ESPACIO_ANCHO * 2)) + (K * OTCI->AnchoIcono()), YA, static_cast<int>(ParteIcono * static_cast<float>(OTCI->AnchoIcono())), OTCI->AltoIcono(), hDCPI, 0, 0, SRCCOPY);
							SelectObject(hDCPI, ViejoPI);
							DeleteObject(BMPPI);
							DeleteDC(hDCPI);
						}
						//AnchoA = (((TT_MARGEN / 2) + _AnchoTexto1) + TT_ESPACIO_ANCHO) + (TT_ESPACIO_ANCHO * 2);
						DestroyIcon(Icono);
						YA += AltoNormal + TT_ESPACIO_ALTO;
						break;
					case Enum_ToolTipEx_TiposObjeto_IconoTexto :
						OIT = _Objetos[i]->ObtenerIconoTexto();
						SelectObject(Buffer, Estilos.Fuentes.Negrita());
						Icono = static_cast<HICON>(LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(OIT->Icono()), IMAGE_ICON, OIT->AnchoIcono(), OIT->AltoIcono(), LR_DEFAULTCOLOR));
						CentradoY = (AltoNegritaF - AltoNegrita) / 2;
						DrawIconEx(Buffer, (TT_MARGEN / 2) -1 , YA, Icono, OIT->AnchoIcono(), OIT->AltoIcono(), 0, 0, DI_NORMAL);
						SetTextColor(Buffer, Estilos.Colores.TextoSombra());
						TextOut(Buffer, ((TT_MARGEN / 2) + (OIT->AnchoIcono() + 2)) + 1, (YA + 1) + CentradoY, OIT->Texto(), OIT->TamTexto());
						SetTextColor(Buffer, Estilos.Colores.TextoNormal());
						TextOut(Buffer, (TT_MARGEN / 2) + (OIT->AnchoIcono() + 2), YA + CentradoY, OIT->Texto(), OIT->TamTexto());
						DestroyIcon(Icono);
						YA += AltoNegritaF + TT_ESPACIO_ALTO + 1;
						break;
				}
			}
			BitBlt(hDC, 0, 0, _AnchoRequerido, _AltoRequerido, Buffer, 0, 0, SRCCOPY);

			SelectObject(Buffer, FViejo);
			SelectObject(Buffer, Viejo);
			DeleteObject(Bmp);
			DeleteDC(Buffer);
            return 0;
		}

		LRESULT DWLToolTipEx::Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param) {
//			if (_PrimerMouseMove == true)	_PrimerMouseMove = false;
			Destruir();
            return 0;
		}

		LRESULT DWLToolTipEx::Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			Destruir();
            return 0;
		}

		LRESULT DWLToolTipEx::Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			Destruir();
            return 0;
		}


	}
}
