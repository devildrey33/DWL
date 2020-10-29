#include "DWLArbolEx_Nucleo.h"
#include "..\DWLListaIconos.h"
#include "..\DWLArbolEx.h"
#include "..\DWLToolTipEx.h"
#include <ctype.h>
 
#define DWL_VALOR_ALPHA    110


namespace DWL {
	namespace ControlesEx {
		//! Constructor.
		/*! Este constructor inicializa los datos internos del arbol por defecto.
				\fn			DWLArbolEx_Nucleo(void);
				\return		No devuelve nada.
		*/
		DWLArbolEx_Nucleo::DWLArbolEx_Nucleo(void) :
		 _ArbolEx_NodoPresionado(NULL),
		 _ArbolEx_NodoShifteado(NULL),
		 _ArbolEx_NodoMarcado(NULL),
		 _ArbolEx_NodoResaltado(NULL),
		 _ArbolEx_UNodoResaltado(NULL),
		 _ArbolEx_PosUltimoClick(NULL),
		 _ArbolEx_ExpansorPresionado(NULL),
		 _ArbolEx_ExpansorResaltado(NULL),
		 _ArbolEx_UExpansorResaltado(NULL),
		 _ArbolEx_UltimoClick(0),
		 _ArbolEx_UltimoBoton(-1),
		 _ArbolEx_Nodos(),
		 _ArbolEx_NodosLineales(),
		 _ArbolEx_Buffer(NULL),
		 _ArbolEx_Bmp(NULL),
		 _ArbolEx_Viejo(NULL),
		 _ArbolEx_FondoDC(NULL),
		 _ArbolEx_BmpFondo(NULL),
		 _ArbolEx_ViejoFondo(NULL),
		 _ArbolEx_VFuente(NULL),
		 _ArbolEx_PosBuscar(0),
		 _ArbolEx_UVirtKey(0),
		 _ArbolEx_UYMouse(-1),
		 _ArbolEx_AltoLinea(16),
		 _ArbolEx_FocoRaton(false),
		 _ArbolEx_UFocoRaton(false),
		 _ArbolEx_eNodo(NULL),
		 _ArbolEx_GestorMensajesOriginalEdit(NULL),
		 _ArbolEx_BrochaFondoEdit(NULL),
		 _ArbolEx_Editando(false),
		 _ArbolEx_hWndEdit(NULL),
		 _ArbolEx_TT_UltimoNodo(NULL),
		 ArbolEx_Estilos() {

			for (unsigned char c = 0; c < 255; c++) _ArbolEx_Teclado[c] = false;
//            ArbolEx_Estilos.Fuentes.Enlazar(DWL::SO::DWLEstilos::Fuentes);
		};

		//! Destructor.
		/*! Este destructor elimina de memoria los datos internos del arbol.
				\fn			~DWLArbolEx_Nucleo(void);
				\return		No devuelve nada.
		*/
		DWLArbolEx_Nucleo::~DWLArbolEx_Nucleo(void) {
		    for (size_t i = 0; i < _ArbolEx_Nodos.size(); i++) delete _ArbolEx_Nodos[i];
//			for (unsigned int i = static_cast<int>(_ArbolEx_Nodos.size()) -1; i > -1; i--) delete _ArbolEx_Nodos[i];
			_ArbolEx_Nodos.resize(0);
	    };

		//! Función que pinta el arbol en el DC y espacio especificados.
		/*! Esta funcion pinta el ArbolEx en las coordenadas y DC especificados.
				\fn			void ArbolEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true, const bool PintarConMascara = false);;
				\param[in]	hDC					: DC en el que se va a pintar el ArbolEx.
				\param[in]	Espacio				: Recta que delimita el espacio donde se puede pintar el ArbolEx.
				\param[in]	TieneFoco			: Valor que determina si el arbol tiene el foco del raton (por defecto se usara la funcion Foco()).
				\param[in]	PintarConMascara	: Valor que determina si se va a pintar el contorno del control con SRCAND antes de pintar el control.
				\return		No devuelve nada.
				\remarks	Esta función esta preparada para pintar el ArbolEx en un DC que no sea el suyo, o que sea compartido.
							Por ello debemos especificar las coordenadas donde se va a pintar, si tiene el foco del raton o no, y por ultimo si debemos
							pintar la mascara.
							El parametro PintarMascara solo es necesario si vamos a pintar el ArbolEx en un DC que no es el suyo y requerimos el pintado
							del borde del control. Entonces la funcion de pintado pintara el contorno del ArbolEx con SRCAND, y luego pintara el control
							con SRC_PAINT para que no se vean graficos desfasados en el borde.
				\sa			ArbolEx_PintarNodo()
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco, const bool PintarConMascara) {
			RECT	RC		= { 0, 0, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top };
			HDC		Buffer	= CreateCompatibleDC(hDC);
			HBITMAP Bmp		= CreateCompatibleBitmap(hDC, RC.right, RC.bottom);
			HBITMAP Viejo	= static_cast<HBITMAP>(SelectObject(Buffer, Bmp));
			HRGN	Region	= NULL;

			if (PintarConMascara == true || ArbolEx_Estilos.PintarBorde == true) Region = CreateRoundRectRgn(0, 0, RC.right + 1, RC.bottom + 1, 2, 2);

			// Pinto la mascara del control si se requiere
			if (PintarConMascara == true) {
				FillRect(Buffer, &RC, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));
				FillRgn(Buffer, Region, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
				BitBlt(hDC, Espacio->left, Espacio->top, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top, Buffer, 0, 0, SRCAND);
			}

			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx_Nucleo::ArbolEx_Pintar\n"));
			#endif

			int     An			= RC.right;
			int     Al			= RC.bottom;

			int     i           = 0;
			if (BarraScrollEx_VisibleV() == TRUE)	An -= 17;
			if (BarraScrollEx_VisibleH() == TRUE)	Al -= 17;


			// Pinto el fondo
			HBRUSH	Brocha = CreateSolidBrush(ArbolEx_Estilos.Colores.Fondo());
			FillRect(Buffer, &RC, Brocha);
			DeleteObject(Brocha);
			/*if (ArbolEx_Estilos.Transparencias == false) {
				BLENDFUNCTION BF;
				BF.AlphaFormat = 0;
				BF.BlendOp = NULL;
				BF.BlendFlags = NULL;
				BF.SourceConstantAlpha = DWL_VALOR_ALPHA;
				AlphaBlend(Buffer, 0, 0, An, Al, _ArbolEx_FondoDC, 0, 0, An, Al, BF);
			}*/


			// Pinto los nodos
			if (_ArbolEx_Nodos.size() > 0) {
				DWLArbolEx_Nodo *NPosicion = ArbolEx_NodoInicioPagina();

				// Pinto todos los items que estan dentro de la pagina
				if (NPosicion != NULL) {
					for (i = 0; i < _BarraScrollEx_PaginaV + 1; i++) {
						ArbolEx_PintarNodo(Buffer, &RC, NPosicion, i);
						// Reposiciono el puntero del nodo al siguiente nodo que pueda ser pintado
						if (NPosicion->_Expandido == true && NPosicion->_Hijos.size() > 0)	{ // Si esta expandido
							NPosicion = NPosicion->_Hijos[0];
						}
						else {
							while (NPosicion->_Siguiente == NULL) {
								if (NPosicion->_Padre == NULL)	{ // Se ha llegado al final
									NPosicion = NULL;
									break;
								}
								NPosicion = NPosicion->_Padre;
							}
							if (NPosicion == NULL) {
								i++;
								break;
							}
							NPosicion = NPosicion->_Siguiente;
						}
					}
				}
			}

			// Pinto lo que falta del fondo

			if (i < _BarraScrollEx_PaginaV + 1  || _BarraScrollEx_PaginaV == 0) { // Pinto el resto del fondo (si no se ha pintado todo)
				if (ArbolEx_Estilos.Transparencias == true) {
					BLENDFUNCTION BF;
					BF.AlphaFormat = 0;
					BF.BlendOp = 0;
					BF.BlendFlags = 0;
					BF.SourceConstantAlpha = DWL_VALOR_ALPHA;
					AlphaBlend(Buffer, 0, (i * _ArbolEx_AltoLinea), An, Al  - (i * _ArbolEx_AltoLinea), _ArbolEx_FondoDC, 0, i * _ArbolEx_AltoLinea, An, Al  - (i * _ArbolEx_AltoLinea), BF);
				}
			}

			// Pinto los scrolls
			BarraScrollEx_PintarV(Buffer);
			BarraScrollEx_PintarH(Buffer);

			// Pinto el borde
			if (ArbolEx_Estilos.PintarBorde == true) ArbolEx_Evento_Pintar_Borde(Buffer, Region, TieneFoco);
			if (Region != NULL) DeleteObject(Region);

			// Pinto el boton en el hDC especificado
			if (PintarConMascara == false)	BitBlt(hDC, Espacio->left, Espacio->top, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top, Buffer, 0, 0, SRCCOPY);
			else							BitBlt(hDC, Espacio->left, Espacio->top, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top, Buffer, 0, 0, SRCPAINT);

			// Elimino objetos gdi de la memoria
			SelectObject(Buffer, Viejo);
			DeleteObject(Bmp);
			DeleteDC(Buffer);
		};

		//! Función virtual que pinta el borde del ArbolEx.
		/*! Esta función virtual pinta el borde del ArbolEx.
				\fn			virtual void ArbolEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco);
				\param[in]	hDC			: hDC donde se va a pintar el borde del arbol.
				\param[in]	Region		: Region donde se pintara borde del arbol.
				\param[in]	TieneFoco	: Valor en el que determinamos si pintamos el borde con foco o sin foco.
				\return		No devuelve nada.
				\remarks	Si ArbolEx_Estilos.PintarBorde es false, esta función no se usara.
				\sa			ArbolEx_Pintar()
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco) {
			HBRUSH Brocha;
			if (TieneFoco == true)	Brocha = CreateSolidBrush(ArbolEx_Estilos.Colores.BordeClaro());
			else					Brocha = CreateSolidBrush(ArbolEx_Estilos.Colores.Borde());
			FrameRgn(hDC, Region, Brocha, 1, 1);
			DeleteObject(Brocha);
		}


		// FER NOVA FUNCIO que no pinti tota la fila, nomes fins el espai del nodo
        //
        //! Función que pinta un nodo del arbol en el DC y espacio especificados.
		/*! Esta función pinta el nodo del ArbolEx en el espacio y dc especificados.
				\fn			void ArbolEx_PintarNodo(HDC hDC, RECT *Espacio, DWLArbolEx_Nodo *nNodo, const int PosPag);
				\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
				\param[in]	Espacio	: Espacio del ArbolEx.
				\param[in]	PosPag	: Posicion del nodo en la pagina.
				\return		No devuelve nada.
				\remarks	La recta del Espacio debe contener el espacio para todo el ArbolEx, y no solo el del nodo.
							Luego dependiendo de la posicion de la pagina la función calcula internamente la recta para el nodo.
							La variable PosPag debe ser un numero entre 0 y _BarraScrollEx_Pagina.
				\sa			Repintar()
		*/
		void DWLArbolEx_Nucleo::ArbolEx_PintarNodo(HDC hDC, RECT *Espacio, DWLArbolEx_Nodo *nNodo, const int PosPag) {
			if (nNodo == NULL)	return;
			if (PosPag < 0)		return;
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx_Nucleo::PintarNodo(PosPag = %d Texto = %s Icono %d)\n"), PosPag, nNodo->Texto(), nNodo->Icono());
			#endif

			int AnchoBuffer = _BarraScrollEx_MaximoH;
			int nBorde      = 0;
			if (Espacio->right > AnchoBuffer) AnchoBuffer = Espacio->right;
			if (ArbolEx_Estilos.PintarBorde == true) {
				nBorde = 1;
//				AnchoBuffer -= 2;
			}
            int AnchoIcono = 0;
            if (ArbolEx_Estilos.PintarIconos == true) AnchoIcono = 18;
			RECT	DR			= { nBorde + Espacio->left + ((nNodo->_NumNodosSuperiores + 1) * 18) + AnchoIcono,
									0,
									nBorde + Espacio->left +(((nNodo->_NumNodosSuperiores + 1) * 18) + AnchoIcono + nNodo->_AnchoTexto) + 2
									, _ArbolEx_AltoLinea }; // Recta con el tamaño del texto
			RECT	DR2			= { DR.left - 2, DR.top, DR.right, DR.bottom -1 };				// Recta del fondo del texto
			RECT    DR3			= { nBorde + Espacio->left, DR.top, AnchoBuffer, DR.bottom };	// Recta desde la derecha a izquierda del control con la altura del item especificado
			RECT	DRI			= { DR.left - 20, DR.top, DR.left - 4, DR.bottom	};			// Recta para el icono
			RECT	DRPM		= { DR.left - (17 + AnchoIcono), DR.top +3, DR.left - (8 + AnchoIcono), DR.bottom -4	};		// Recta para el recuadro de expandir / contraer
			DWLArbolEx_ColoresNodo *Col;
			if (nNodo->_Colores != NULL)	Col = nNodo->_Colores;
			else							Col = &ArbolEx_Estilos.Colores.ColoresNodo;
			HBRUSH	Brocha		= CreateSolidBrush(Col->FondoNormal());
			HPEN    PlumaLineas = CreatePen(PS_SOLID, 1, ArbolEx_Estilos.Colores.Lineas());
			HPEN    VPluma		= static_cast<HPEN>(SelectObject(_ArbolEx_Buffer, PlumaLineas));

			RECT RectaFila = { 0, DR3.top, DR3.right, DR3.bottom };
			FillRect(_ArbolEx_Buffer, &RectaFila, Brocha);
			DeleteObject(Brocha);

			// Calculo el color del fondo segun el estado del nodo y el arbol
			if (nNodo->_Seleccionado == true) {
				if (_BarraScrollEx_Activado == TRUE) {
					if (nNodo->SubSeleccionado() == true) {
						if		(nNodo == _ArbolEx_NodoPresionado)	Brocha = CreateSolidBrush(Col->FondoPresionado());
						else if	(nNodo == _ArbolEx_NodoResaltado)	Brocha = CreateSolidBrush(Col->FondoSubSeleccionadoResaltado());
						else										Brocha = CreateSolidBrush(Col->FondoSubSeleccionado());
					}
					else {
						if		(nNodo == _ArbolEx_NodoPresionado)	Brocha = CreateSolidBrush(Col->FondoPresionado());
						else if	(nNodo == _ArbolEx_NodoResaltado)	Brocha = CreateSolidBrush(Col->FondoSeleccionadoResaltado());
						else										Brocha = CreateSolidBrush(Col->FondoSeleccionado());
					}
				}
				else { // Si el arbol no esta activado, pinto las selecciones como si estubieran presionadas, para dar el efecto de desactivado
					Brocha = CreateSolidBrush(Col->FondoPresionado());
				}
			}
			else {
				if (nNodo == _ArbolEx_NodoResaltado)			Brocha = CreateSolidBrush(Col->FondoResaltado());
				else									Brocha = CreateSolidBrush(Col->FondoNormal());
			}

			if (nNodo == _ArbolEx_NodoPresionado) {	DR2.left ++;	DR2.top ++;		DR2.right ++;	DR2.bottom ++;	}
			FillRect(_ArbolEx_Buffer, &DR2, Brocha);
			DeleteObject(Brocha);

		    // Pinto las lineas que enlazan los nodos
            if (ArbolEx_Estilos.PintarLineas == true) {
			    _ArbolEx_PintarLinea(_ArbolEx_Buffer, DRPM.left + 4, DRPM.top + 4 , DRPM.left + 16, DRPM.top + 4);

			    if (nNodo->_Anterior == NULL && nNodo->_Padre == NULL) { // Primer nodo...
				    _ArbolEx_PintarLinea(_ArbolEx_Buffer, DRPM.left + 4, DRPM.top + 4 , DRPM.left + 4, DR.bottom);
			    }

			    else if (nNodo->_Siguiente == NULL) { // Ultimo nodo con o sin padre
				    _ArbolEx_PintarLinea(_ArbolEx_Buffer, DRPM.left + 4, DR.top , DRPM.left + 4, DRPM.bottom -5);
			    }

			    else {	// otros
				    _ArbolEx_PintarLinea(_ArbolEx_Buffer, DRPM.left + 4, DR.top , DRPM.left + 4, DR.bottom);
			    }
            }

			DWLArbolEx_Nodo *Tmp = nNodo;
			int Retro = 18;
			while (Tmp->_Padre != NULL) {
				Tmp = Tmp->_Padre;
				if (Tmp->_Siguiente != NULL) _ArbolEx_PintarLinea(_ArbolEx_Buffer, (DRPM.left + 4) - Retro, DR.top , (DRPM.left + 4) - Retro, DR.bottom);
				Retro += 18;
			}

			// Pinto el expansor
			ArbolEx_Evento_Pintar_Expansor(_ArbolEx_Buffer, nNodo, &DRPM);

			// Pinto el fondo del nodo
			BOOL T;
			if (ArbolEx_Estilos.Transparencias == true) {
				BLENDFUNCTION BF;
				BF.AlphaFormat = 0;
				BF.BlendOp = 0;
				BF.BlendFlags = 0;
				BF.SourceConstantAlpha = DWL_VALOR_ALPHA;
				T = AlphaBlend(_ArbolEx_Buffer, _BarraScrollEx_ValorH, 0, Espacio->right, _ArbolEx_AltoLinea, _ArbolEx_FondoDC, 0, PosPag * _ArbolEx_AltoLinea, Espacio->right, _ArbolEx_AltoLinea, BF);
			}

			if (ArbolEx_Estilos.PintarIconos == true) ArbolEx_Evento_Pintar_Icono(_ArbolEx_Buffer, nNodo, &DRI);

			// Pinto el texto y la seleccion del nodo
			if (nNodo->_Seleccionado == true) {
				if (nNodo->SubSeleccionado() == true) {
					if		(nNodo == _ArbolEx_NodoPresionado)	ArbolEx_Evento_Pintar_NodoPresionado(_ArbolEx_Buffer, nNodo, &DR);
					else if	(nNodo == _ArbolEx_NodoResaltado)	ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado(_ArbolEx_Buffer, nNodo, &DR);
					else										ArbolEx_Evento_Pintar_NodoSubSeleccionado(_ArbolEx_Buffer, nNodo, &DR);
				}
				else {
					if		(nNodo == _ArbolEx_NodoPresionado)	ArbolEx_Evento_Pintar_NodoPresionado(_ArbolEx_Buffer, nNodo, &DR);
					else if	(nNodo == _ArbolEx_NodoResaltado)	ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(_ArbolEx_Buffer, nNodo, &DR);
					else										ArbolEx_Evento_Pintar_NodoSeleccionado(_ArbolEx_Buffer, nNodo, &DR);
				}
			}
			else {
				if		(nNodo == _ArbolEx_NodoPresionado)	ArbolEx_Evento_Pintar_NodoPresionado(_ArbolEx_Buffer, nNodo, &DR);
				else if	(nNodo == _ArbolEx_NodoResaltado)	ArbolEx_Evento_Pintar_NodoResaltado(_ArbolEx_Buffer, nNodo, &DR);
				else										ArbolEx_Evento_Pintar_NodoNormal(_ArbolEx_Buffer, nNodo, &DR);
			}

			// Enmarco el nodo marcado
			if (_ArbolEx_NodoMarcado == nNodo) _ArbolEx_EnmarcarRecta(_ArbolEx_Buffer, &DR2);

			// Arreglo para pintar solo una parte del nodo cuando es mas grande que lo que queda de control
			int ArregloScrollH = _ArbolEx_AltoLinea;
			if (((PosPag +1) * _ArbolEx_AltoLinea) > (Espacio->bottom - 18) && BarraScrollEx_VisibleH() == TRUE) {
				if (ArbolEx_Estilos.PintarBorde == false)	ArregloScrollH = (Espacio->bottom - 19) - (PosPag * _ArbolEx_AltoLinea);
				else						        		ArregloScrollH = (Espacio->bottom - 22) - (PosPag * _ArbolEx_AltoLinea);
			}
			// ARREGLO PARA EL BORDE
			else if ((PosPag +1) * _ArbolEx_AltoLinea > (Espacio->bottom - 4) && BarraScrollEx_VisibleH() == FALSE && ArbolEx_Estilos.PintarBorde == true) {
				ArregloScrollH = (Espacio->bottom - 4) - (PosPag * _ArbolEx_AltoLinea);;
			}

			int AnchoBlt = Espacio->right;

			if (BarraScrollEx_VisibleV() == TRUE) AnchoBlt -= 19;
			if (ArbolEx_Estilos.PintarBorde == true) AnchoBlt -= 3;

			// Pinto el nodo en el DC
			BitBlt(hDC, DR3.left, (PosPag * _ArbolEx_AltoLinea) + 1, AnchoBlt, ArregloScrollH, _ArbolEx_Buffer, _BarraScrollEx_ValorH, 0, SRCCOPY);

			// Elimino objetos de memoria
			SelectObject(_ArbolEx_Buffer, VPluma);
			DeleteObject(PlumaLineas);
		}

		//! Función virtual que pinta el icono del nodo.
		/*! Esta función virtual pinta el icono del DWLArbolEx_Nodo en el espacio y dc especificados.
				\fn			virtual void ArbolEx_Evento_Pintar_Icono(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
				\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el icono.
				\param[in]	Espacio	: Espacio de 18x18 donde se va a pintar el icono.
				\return		No devuelve nada.
				\remarks	Esta funcion solo pinta iconos de 16x16, la razon de requerir 18 pixeles es para dejar
							uno de borde y otro para cuando se presiona el nodo.
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Evento_Pintar_Icono(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio) {
			#if defined DWL_ARBOLEX_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx_Nucleo::ArbolEx_Evento_Pintar_Icono\n"));
			#endif
			if (_ArbolEx_NodoPresionado == nNodo)	DWL::SO::DWLListaIconos::PintarIcono(hDC, Espacio->left + 2, Espacio->top + 1, 16, 16, nNodo->_Icono);
			else									DWL::SO::DWLListaIconos::PintarIcono(hDC, Espacio->left + 1, Espacio->top + 0, 16, 16, nNodo->_Icono);
		}


		//! Función virtual que pinta el estado normal del nodo.
		/*! Esta función virtual pinta el texto del nodo en su estado normal.
				\fn			virtual void ArbolEx_Evento_Pintar_NodoNormal(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
				\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el texto.
				\param[in]	Espacio	: Espacio donde se pintara el texto del nodo.
				\return		No devuelve nada.
				\remarks	Esta funcion pone el color del texto, y luego lo pinta.
				\sa			ArbolEx_Pintar(), ArbolEx_Evento_Pintar_NodoResaltado(), ArbolEx_Evento_Pintar_NodoSeleccionado(), ArbolEx_Evento_Pintar_NodoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoPresionado();
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Evento_Pintar_NodoNormal(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Pintar_NodoNormal\n"));
			#endif
			if (nNodo->_Fuentes != NULL)	SelectObject(hDC, nNodo->_Fuentes->Normal());
			else							SelectObject(hDC, ArbolEx_Estilos.Fuentes.Normal());
			if (_BarraScrollEx_Activado == true) {
				if (nNodo->_Colores != NULL)	SetTextColor(hDC, nNodo->_Colores->TextoNormal());
				else							SetTextColor(hDC, ArbolEx_Estilos.Colores.ColoresNodo.TextoNormal());
			}
			else {
				SetTextColor(hDC, ArbolEx_Estilos.Colores.ColoresNodo.TextoPresionado());
			}
			DrawText(hDC, nNodo->_Texto(), static_cast<int>(nNodo->_Texto.Tam()), Espacio, DT_LEFT | DT_NOPREFIX);
		}

	    //! Función virtual que pinta el estado resaltado del nodo.
	    /*! Esta función virtual pinta el texto del nodo en su estado resaltado.
			    \fn			virtual void ArbolEx_Evento_Pintar_NodoResaltado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
			    \param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
			    \param[in]	nNodo	: DWLArbolEx_Nodo que contiene el texto.
			    \param[in]	Espacio	: Espacio donde se pintara el texto del nodo.
			    \return		No devuelve nada.
			    \remarks	Esta funcion pone el color del texto, y luego lo pinta.
			    \sa			ArbolEx_Pintar(), ArbolEx_Evento_Pintar_NodoNormal(), ArbolEx_Evento_Pintar_NodoSeleccionado(), ArbolEx_Evento_Pintar_NodoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoPresionado();
	    */
		void DWLArbolEx_Nucleo::ArbolEx_Evento_Pintar_NodoResaltado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Pintar_ArbolEx_NodoResaltado\n"));
			#endif
			if (nNodo->_Fuentes != NULL)	SelectObject(hDC, nNodo->_Fuentes->SubRayada());
			else							SelectObject(hDC, ArbolEx_Estilos.Fuentes.SubRayada());
			if (_BarraScrollEx_Activado == true) {			
				if (nNodo->_Colores != NULL)	SetTextColor(hDC, nNodo->_Colores->TextoResaltado());
				else							SetTextColor(hDC, ArbolEx_Estilos.Colores.ColoresNodo.TextoResaltado());
			}
			else {
				SetTextColor(hDC, ArbolEx_Estilos.Colores.ColoresNodo.TextoPresionado());
			}
			DrawText(hDC, nNodo->_Texto(), static_cast<int>(nNodo->_Texto.Tam()), Espacio, DT_LEFT | DT_NOPREFIX);
		}

		//! Función virtual que pinta el estado seleccionado del nodo.
		/*! Esta función virtual pinta el texto del nodo en su estado seleccionado.
				\fn			virtual void ArbolEx_Evento_Pintar_NodoSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
				\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el texto.
				\param[in]	Espacio	: Espacio donde se pintara el texto del nodo.
				\return		No devuelve nada.
				\remarks	Esta funcion pone el color del texto, y luego lo pinta.
				\sa			ArbolEx_Pintar(), ArbolEx_Evento_Pintar_NodoNormal(), ArbolEx_Evento_Pintar_NodoResaltado(), ArbolEx_Evento_Pintar_NodoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoPresionado();
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Evento_Pintar_NodoSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Pintar_NodoSeleccionado\n"));
			#endif
			if (nNodo->_Fuentes != NULL)	SelectObject(hDC, nNodo->_Fuentes->Normal());
			else							SelectObject(hDC, ArbolEx_Estilos.Fuentes.Normal());
			if (nNodo->_Colores != NULL) {
				if (_BarraScrollEx_Activado == TRUE) SetTextColor(hDC, nNodo->_Colores->TextoSeleccionado());
				else								 SetTextColor(hDC, nNodo->_Colores->TextoPresionado());
			}
			else {
				if (_BarraScrollEx_Activado == TRUE) SetTextColor(hDC, ArbolEx_Estilos.Colores.ColoresNodo.TextoSeleccionado());
				else								 SetTextColor(hDC, ArbolEx_Estilos.Colores.ColoresNodo.TextoPresionado());
			}
			DrawText(hDC, nNodo->_Texto(), static_cast<int>(nNodo->_Texto.Tam()), Espacio, DT_LEFT | DT_NOPREFIX);
		}

		//! Función virtual que pinta el estado sub-seleccionado del nodo.
		/*! Esta función virtual pinta el texto del nodo en su estado sub-seleccionado.
				\fn			virtual void ArbolEx_Evento_Pintar_NodoSubSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
				\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el texto.
				\param[in]	Espacio	: Espacio donde se pintara el texto del nodo.
				\return		No devuelve nada.
				\remarks	Esta funcion pone el color del texto, y luego lo pinta.
				\sa			ArbolEx_Pintar(), ArbolEx_Evento_Pintar_NodoNormal(), ArbolEx_Evento_Pintar_NodoResaltado(), ArbolEx_Evento_Pintar_NodoSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoPresionado();
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Evento_Pintar_NodoSubSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Pintar_NodoSubSeleccionado\n"));
			#endif
			if (nNodo->_Fuentes != NULL)	SelectObject(hDC, nNodo->_Fuentes->Normal());
			else							SelectObject(hDC, ArbolEx_Estilos.Fuentes.Normal());
			if (nNodo->_Colores != NULL) {
				if (_BarraScrollEx_Activado == TRUE) SetTextColor(hDC, nNodo->_Colores->TextoSubSeleccionado());
				else								 SetTextColor(hDC, nNodo->_Colores->TextoPresionado());
			}
			else {
				if (_BarraScrollEx_Activado == TRUE) SetTextColor(hDC, ArbolEx_Estilos.Colores.ColoresNodo.TextoSubSeleccionado());
				else								 SetTextColor(hDC, ArbolEx_Estilos.Colores.ColoresNodo.TextoPresionado());
			}
			DrawText(hDC, nNodo->_Texto(), static_cast<int>(nNodo->_Texto.Tam()), Espacio, DT_LEFT | DT_NOPREFIX);
		}

		//! Función virtual que pinta el estado resaltado seleccionado del nodo.
		/*! Esta función virtual pinta el texto del nodo en su estado resaltado seleccionado.
				\fn			virtual void ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
				\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el texto.
				\param[in]	Espacio	: Espacio donde se pintara el texto del nodo.
				\return		No devuelve nada.
				\remarks	Esta funcion pone el color del texto, y luego lo pinta.
				\sa			ArbolEx_Pintar(), ArbolEx_Evento_Pintar_NodoNormal(), ArbolEx_Evento_Pintar_NodoResaltado(), ArbolEx_Evento_Pintar_NodoSeleccionado(), ArbolEx_Evento_Pintar_NodoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoPresionado();
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Pintar_ArbolEx_NodoResaltadoSeleccionado\n"));
			#endif
			if (nNodo->_Fuentes != NULL)	SelectObject(hDC, nNodo->_Fuentes->SubRayada());
			else							SelectObject(hDC, ArbolEx_Estilos.Fuentes.SubRayada());
			if (_BarraScrollEx_Activado == true) {			
				if (nNodo->_Colores != NULL)	SetTextColor(hDC, nNodo->_Colores->TextoSeleccionadoResaltado());
				else							SetTextColor(hDC, ArbolEx_Estilos.Colores.ColoresNodo.TextoSeleccionadoResaltado());
			}
			else {
				SetTextColor(hDC, ArbolEx_Estilos.Colores.ColoresNodo.TextoPresionado());
			}

			DrawText(hDC, nNodo->_Texto(), static_cast<int>(nNodo->_Texto.Tam()), Espacio, DT_LEFT | DT_NOPREFIX);
		}

		//! Función virtual que pinta el estado resaltado sub-seleccionado del nodo.
		/*! Esta función virtual pinta el texto del nodo en su estado resaltado sub-seleccionado.
				\fn			virtual void ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
				\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el texto.
				\param[in]	Espacio	: Espacio donde se pintara el texto del nodo.
				\return		No devuelve nada.
				\remarks	Esta funcion pone el color del texto, y luego lo pinta.
				\sa			ArbolEx_Pintar(), ArbolEx_Evento_Pintar_NodoNormal(), ArbolEx_Evento_Pintar_NodoResaltado(), ArbolEx_Evento_Pintar_NodoSeleccionado(), ArbolEx_Evento_Pintar_NodoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(), ArbolEx_Evento_Pintar_NodoPresionado();
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Pintar_ArbolEx_NodoResaltadoSubSeleccionado\n"));
			#endif
			if (nNodo->_Fuentes != NULL)	SelectObject(hDC, nNodo->_Fuentes->SubRayada());
			else							SelectObject(hDC, ArbolEx_Estilos.Fuentes.SubRayada());
			if (_BarraScrollEx_Activado == true) {			
				if (nNodo->_Colores != NULL)	SetTextColor(hDC, nNodo->_Colores->TextoSubSeleccionadoResaltado());
				else							SetTextColor(hDC, ArbolEx_Estilos.Colores.ColoresNodo.TextoSubSeleccionadoResaltado());
			}
			else {
				SetTextColor(hDC, ArbolEx_Estilos.Colores.ColoresNodo.TextoPresionado());
			}
			DrawText(hDC, nNodo->_Texto(), static_cast<int>(nNodo->_Texto.Tam()), Espacio, DT_LEFT | DT_NOPREFIX);
		}


		//! Función virtual que pinta el estado presionado del nodo.
		/*! Esta función virtual pinta el texto del nodo en su estado presionado.
				\fn			virtual void ArbolEx_Evento_Pintar_NodoPresionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar el DWLArbolEx_Nodo.
				\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el texto.
				\param[in]	Espacio	: Espacio donde se pintara el texto del nodo.
				\return		No devuelve nada.
				\remarks	Esta funcion pone el color del texto, y luego lo pinta.
				\sa			ArbolEx_Pintar(), ArbolEx_Evento_Pintar_NodoNormal(), ArbolEx_Evento_Pintar_NodoResaltado(), ArbolEx_Evento_Pintar_NodoSeleccionado(), ArbolEx_Evento_Pintar_NodoSubSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSeleccionado(), ArbolEx_Evento_Pintar_NodoResaltadoSubSeleccionado();
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Evento_Pintar_NodoPresionado(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Pintar_ArbolEx_NodoPresionado\n"));
			#endif
			if (nNodo->_Fuentes != NULL)	SelectObject(hDC, nNodo->_Fuentes->SubRayada());
			else							SelectObject(hDC, ArbolEx_Estilos.Fuentes.SubRayada());
			if (_BarraScrollEx_Activado == true) {			
				if (nNodo->_Colores != NULL)	SetTextColor(hDC, nNodo->_Colores->TextoPresionado());
				else							SetTextColor(hDC, ArbolEx_Estilos.Colores.ColoresNodo.TextoPresionado());
			}
			else {
				SetTextColor(hDC, ArbolEx_Estilos.Colores.ColoresNodo.TextoPresionado());
			}
			Espacio->left ++; Espacio->top ++; Espacio->bottom ++; Espacio->right ++;
			DrawText(hDC, nNodo->_Texto(), static_cast<int>(nNodo->_Texto.Tam()), Espacio, DT_LEFT | DT_NOPREFIX);
			Espacio->left --; Espacio->top --; Espacio->bottom --; Espacio->right --;
		}

	    //! Función virtual que pinta el fondo del arbol con AlphaBlend.
	    /*! Esta función virtual pinta el fondo del arbol con AlphaBlend.
			    \fn			virtual void ArbolEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio);
			    \param[in]	hDC		: hDC donde se va a pintar el fondo del arbol.
			    \param[in]	Espacio	: Espacio donde se pintara fondo del arbol.
			    \return		No devuelve nada.
			    \remarks	Si ArbolEx_Estilos.Transparencias es false, esta función no se usara.
	    */
		void DWLArbolEx_Nucleo::ArbolEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Pintar_Fondo\n"));
			#endif
			HBRUSH Brocha = CreateSolidBrush(ArbolEx_Estilos.Colores.Fondo());
			FillRect(hDC, Espacio, Brocha);
			DeleteObject(Brocha);
		}

		//! Función virtual que pinta el expansor del DWLArbolEx_Nodo.
		/*! Esta función virtual pinta el expansor del DWLArbolEx_Nodo.
				\fn			virtual void ArbolEx_Evento_Pintar_Expansor(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar el expansor del DWLArbolEx_Nodo.
				\param[in]	nNodo	: DWLArbolEx_Nodo que contiene el expansor.
				\param[in]	Espacio	: Espacio donde se pintara el expansor del nodo.
				\return		No devuelve nada.
				\sa			ArbolEx_Pintar()
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Evento_Pintar_Expansor(HDC hDC, DWLArbolEx_Nodo *nNodo, RECT *Espacio) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Pintar_MasMenos\n"));
			#endif
			if (nNodo->_Hijos.size() > 0) {
				HBRUSH ColFondo;
				HPEN   ColCruz;
                RECT   EspacioExpansor = { Espacio->left, Espacio->top, Espacio->right, Espacio->top + (Espacio->right - Espacio->left) }; // Lo hacemos cuadrado partiendo del ancho
				DWLArbolEx_ColoresNodo *Col;
				if (nNodo->_Colores != NULL)	Col = nNodo->_Colores;
				else							Col = &ArbolEx_Estilos.Colores.ColoresNodo;
				if (nNodo == _ArbolEx_ExpansorPresionado) {
					EspacioExpansor.left ++;
					EspacioExpansor.top ++;
					EspacioExpansor.right ++;
					EspacioExpansor.bottom ++;
					ColFondo = CreateSolidBrush(Col->PMFondoPresionado());
					ColCruz = CreatePen(PS_SOLID, 1, Col->PMTextoPresionado());
				}
				else {
					if (nNodo == _ArbolEx_ExpansorResaltado) {
						ColFondo = CreateSolidBrush(Col->PMFondoResaltado());
						ColCruz = CreatePen(PS_SOLID, 1, Col->PMTextoResaltado());
					}
					else {
						ColFondo = CreateSolidBrush(Col->PMFondoNormal());
						ColCruz = CreatePen(PS_SOLID, 1, Col->PMTextoNormal());
					}
				}
				HBRUSH Brocha = CreateSolidBrush(ArbolEx_Estilos.Colores.Lineas());
				HPEN VColCruz = static_cast<HPEN>(SelectObject(hDC, ColCruz));
				FillRect(hDC, &EspacioExpansor, ColFondo);
				_ArbolEx_EnmarcarRecta(hDC, &EspacioExpansor);
				_ArbolEx_PintarLinea(hDC, EspacioExpansor.left + 2, EspacioExpansor.top + 4, EspacioExpansor.right - 2, EspacioExpansor.top + 4);
				if (nNodo->_Expandido == false) _ArbolEx_PintarLinea(hDC, EspacioExpansor.left + 4, EspacioExpansor.top + 2, EspacioExpansor.left + 4, EspacioExpansor.bottom - 2);
				SelectObject(hDC, VColCruz);
				DeleteObject(ColCruz);
				DeleteObject(Brocha);
				DeleteObject(ColFondo);
			}
		}

		//! Función que retorna el primer nodo visible en el ArbolEx.
		/*! Esta función retorna el primer nodo visible en el ArbolEx.
				\fn			DWLArbolEx_Nodo *ArbolEx_NodoInicioPagina(void);
				\return		Devuelve el primer DWLArbolEx_Nodo visible en el ArbolEx.
				\remarks    Esta funcion devolvera el primer nodo visible del arbol si existen nodos. En caso contrario retornara NULL.
				\sa			ArbolEx_NodoFinPagina()
		*/
		DWLArbolEx_Nodo *DWLArbolEx_Nucleo::ArbolEx_NodoInicioPagina(void) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::NodoInicioPagina\n"));
			#endif
			if (_ArbolEx_Nodos.size() == 0) return NULL;
			DWLArbolEx_Nodo *NPosicion = _ArbolEx_Nodos[0];

			// Situo NPosicion al primer nodo que se ve en la pagina
			for (int i = 0; i < _BarraScrollEx_ValorV; i++) {
				if (NPosicion->_Expandido == true && NPosicion->_Hijos.size() > 0)	{ // Si esta expandido
					NPosicion = NPosicion->_Hijos[0];
				}
				else {
					while (NPosicion->_Siguiente == NULL) {
						if (NPosicion->_Padre == NULL)	{ // Se ha llegado al final
							return NULL;
						}
						NPosicion = NPosicion->_Padre;
					}
					NPosicion = NPosicion->_Siguiente;
				}
			}
			return NPosicion;
		};

		//! Función que retorna el ultimo nodo visible en el ArbolEx
		/*! Esta función retorna el ultimo nodo visible en el ArbolEx.
				\fn			DWLArbolEx_Nodo *ArbolEx_NodoFinPagina(void);
				\return		Devuelve el ultimo DWLArbolEx_Nodo visible en el ArbolEx.
				\remarks    Esta funcion devolvera el ultimo nodo visible del arbol si existen nodos. En caso contrario retornara NULL.
				\sa			ArbolEx_NodoInicioPagina()
		*/
		DWLArbolEx_Nodo *DWLArbolEx_Nucleo::ArbolEx_NodoFinPagina(void) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::NodoFinPagina\n"));
			#endif
			if (_ArbolEx_Nodos.size() == 0) return NULL;
			DWLArbolEx_Nodo *NPosicion = _ArbolEx_Nodos[0];

			// Situo NPosicion al primer nodo que se ve en la pagina
			for (int i = 0; i < (_BarraScrollEx_ValorV + _BarraScrollEx_PaginaV) -1; i++) {
				if (NPosicion->_Expandido == true && NPosicion->_Hijos.size() > 0)	{ // Si esta expandido
					NPosicion = NPosicion->_Hijos[0];
				}
				else {
					while (NPosicion->_Siguiente == NULL) {
						if (NPosicion->_Padre == NULL)	{ // Se ha llegado al final
							return NPosicion;
						}
						NPosicion = NPosicion->_Padre;
					}
					NPosicion = NPosicion->_Siguiente;
				}
			}
			return NPosicion;
		}

		//! Función que borra todos los nodos del ArbolEx.
		/*! Esta función borra todos los nodos del ArbolEx.
				\fn			void ArbolEx_EliminarTodosLosNodos(void);
				\return		No devuelve nada.
				\sa			ArbolEx_EliminarNodo(), ArbolEx_EliminarNodosSeleccionados()
		*/
		void DWLArbolEx_Nucleo::ArbolEx_EliminarTodosLosNodos(void) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::EliminarTodosLosNodos\n"));
			#endif
//			for (unsigned int i = static_cast<int>(_ArbolEx_Nodos.size()) -1; i > -1; i--) delete _ArbolEx_Nodos[i];
		    for (size_t i = 0; i < _ArbolEx_Nodos.size(); i++) delete _ArbolEx_Nodos[i];
			_ArbolEx_Nodos.resize(0);
			_BarraScrollEx_PosActualV	= 0;
			_BarraScrollEx_PosActualH	= 0;
			_BarraScrollEx_ValorV		= 0;
			_BarraScrollEx_ValorH		= 0;
			_BarraScrollEx_MaximoV		= 0;
			_BarraScrollEx_MaximoH		= 0;
			_ArbolEx_NodoPresionado		= NULL;
			_ArbolEx_NodoShifteado		= NULL;
			_ArbolEx_NodoMarcado		= NULL;
			_ArbolEx_NodoResaltado		= NULL;
			_ArbolEx_UNodoResaltado		= NULL;
			_ArbolEx_PosUltimoClick		= NULL;
			_ArbolEx_ExpansorPresionado = NULL;
			_ArbolEx_ExpansorResaltado	= NULL;
			_ArbolEx_UExpansorResaltado = NULL;

			BarraScrollEx_CalcularScrollV();
			BarraScrollEx_CalcularScrollH();
		}


		//! Función que agrega un nodo al ArbolEx.
		/*! Esta función agrega un nodo al ArbolEx.
				\fn			DWLArbolEx_Nodo *ArbolEx_AgregarNodo(DWLArbolEx_Nodo *nNodo = NULL, DWLArbolEx_Nodo *nPadre = NULL, const int nIcono = NULL, const TCHAR *nTexto = NULL, const int PosicionNodo = DWL_ARBOLEX_ORDENADO);
				\param[in]	nNodo			: Clase que hereda de DWLArbolEx_Nodo creada anteriormente. Puede ser NULL.
				\param[in]	nPadre			: Nodo padre de este nodo. Puede ser NULL.
				\param[in]	nIcono			: ID del icono para este nodo.
				\param[in]	nTexto			: Texto para el nodo.
				\param[in]	nPosicionNodo	: Posicion para el nodo que puede ser DWL_ARBOLEX_PRINCIPIO, DWL_ARBOLEX_ORDENADO, DWL_ARBOLEX_FIN, o un numero valido de posición.
				\return		Devuelve un puntero al DWLArbolEx_Nodo que se ha creado.
				\remarks	Puedes heredar la clase DWLArbolEx_Nodo y agregarle mas miembros, para luego añadirla al arbol utilizando esta funcion.
							Para ello deberas crear en memoria tu clase heredada, y pasarsela en el parametro nNodo.
							Una vez echo esto ya te puedes olvidar de eliminarla de memoria, ya que el mismo arbol se encargara de ello cuando no la necesite mas.
							Por ultimo cuando no necesites añadir mas nodos deberas llamar a la funcion ArbolEx_ActualizarTodo() para actualizar las listas enlazadas de nodos.
				\sa			ArbolEx_ActualizarTodo();
		*/
		DWLArbolEx_Nodo *DWLArbolEx_Nucleo::ArbolEx_AgregarNodo(DWLArbolEx_Nodo *nNodo, DWLArbolEx_Nodo *nPadre, const int nIcono, const TCHAR *nTexto, const int PosicionNodo) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::AgregarNodo\n"));
			#endif
			DWLArbolEx_Nodo *nAnterior = NULL;
			SIZE Tam;
			GetTextExtentPoint(_ArbolEx_Buffer, nTexto, static_cast<int>(DWLStrLen(nTexto)), &Tam);

			if (nNodo == NULL) {
				nNodo = new DWLArbolEx_Nodo(this, nPadre, nAnterior);
			}
			else {
				nNodo->_Padre = nPadre;
				nNodo->_Anterior = nAnterior;
				nNodo->_Arbol = this;
			}
			nNodo->_Siguiente = NULL;

			// Al final de todo  ///////////////////////////////////////////////////////////////////////////
			if (PosicionNodo == DWL_ARBOLEX_FIN) {
				if (nPadre != NULL) {
					if (nPadre->_Hijos.size() > 0) nAnterior = nPadre->_Hijos[nPadre->_Hijos.size() -1];
				}
				else {
					if (_ArbolEx_Nodos.size() > 0) nAnterior = _ArbolEx_Nodos[_ArbolEx_Nodos.size() -1];
				}
				nNodo->_Siguiente = NULL;
				if (nPadre == NULL) _ArbolEx_Nodos.push_back(nNodo);
				else				nPadre->_Hijos.push_back(nNodo);
			}

			// Por orden Alfabetico ////////////////////////////////////////////////////////////////////////
			else if (PosicionNodo == DWL_ARBOLEX_ORDENADO) {
				unsigned int i;
				if (nPadre == NULL) { // Si no tiene padre
					for (i = 0; i < _ArbolEx_Nodos.size(); i++) {
						if (DWLStrCmpi(nTexto, _ArbolEx_Nodos[i]->_Texto()) < 0) break;
					}

					if (_ArbolEx_Nodos.size() > 0 && i > 0) nAnterior = _ArbolEx_Nodos[i -1];


					if (nAnterior != NULL) {
						nNodo->_Siguiente = nAnterior->_Siguiente;
						nAnterior->_Siguiente = nNodo;
					}
					else {
						if (_ArbolEx_Nodos.size() > 0)	nNodo->_Siguiente = _ArbolEx_Nodos[i];
						else					        nNodo->_Siguiente = NULL;
					}
					if (nNodo->_Siguiente != NULL)	nNodo->_Siguiente->_Anterior = nNodo;

					if (_ArbolEx_Nodos.size() == 0)	_ArbolEx_Nodos.push_back(nNodo);
					else					        _ArbolEx_Nodos.insert(_ArbolEx_Nodos.begin() + i, nNodo);
				}

				else { // Si tiene padre
					for (i = 0; i < nPadre->_Hijos.size(); i++) {
						if (DWLStrCmpi(nTexto, nPadre->_Hijos[i]->_Texto()) < 0) break;
					}
					if (nPadre->_Hijos.size() > 0 && i > 0)		nAnterior = nPadre->_Hijos[i -1];

					if (nAnterior != NULL) {
						nNodo->_Siguiente = nAnterior->_Siguiente;
						nAnterior->_Siguiente = nNodo;
					}
					else {
						if (nPadre->_Hijos.size() > 0) 	nNodo->_Siguiente = nPadre->_Hijos[i];
						else							nNodo->_Siguiente = NULL;
					}
					if (nNodo->_Siguiente != NULL)	nNodo->_Siguiente->_Anterior = nNodo;

					if (nPadre->_Hijos.size() == 0) nPadre->_Hijos.push_back(nNodo);
					else							nPadre->_Hijos.insert(nPadre->_Hijos.begin() + i, nNodo);

				}

			}
			// Insertado en una posicion especifica (Tambien se usa para insertar nodos al principio) ////////
			else {
				int nPosicionNodo = PosicionNodo;
				if (nPadre == NULL) { // Si no tiene padre
					if (nPosicionNodo > static_cast<int>(_ArbolEx_Nodos.size())) nPosicionNodo = static_cast<int>(_ArbolEx_Nodos.size());

					if (static_cast<int>(_ArbolEx_Nodos.size()) > 0 && nPosicionNodo > 0) nAnterior = _ArbolEx_Nodos[nPosicionNodo -1];

					if (nAnterior != NULL) {
						nNodo->_Siguiente = nAnterior->_Siguiente;
						nAnterior->_Siguiente = nNodo;
					}
					else {
						if (_ArbolEx_Nodos.size() > 0)	nNodo->_Siguiente = _ArbolEx_Nodos[nPosicionNodo];
						else					nNodo->_Siguiente = NULL;
					}
					if (nNodo->_Siguiente != NULL)	nNodo->_Siguiente->_Anterior = nNodo;
					if (_ArbolEx_Nodos.size() == 0)	_ArbolEx_Nodos.push_back(nNodo);
					else					_ArbolEx_Nodos.insert(_ArbolEx_Nodos.begin() + nPosicionNodo, nNodo);
				}
				else {	// Si tiene padre
					if (nPosicionNodo > static_cast<int>(nPadre->_Hijos.size())) nPosicionNodo = static_cast<int>(nPadre->_Hijos.size());
					if (nPadre->_Hijos.size() > 0 && nPosicionNodo > 0)	nAnterior = nPadre->_Hijos[nPosicionNodo -1];

					if (nAnterior != NULL) {
						nNodo->_Siguiente = nAnterior->_Siguiente;
						nAnterior->_Siguiente = nNodo;
					}
					else {
						if (nPadre->_Hijos.size() > 0)	nNodo->_Siguiente = nPadre->_Hijos[nPosicionNodo];
						else							nNodo->_Siguiente = NULL;
					}
					if (nNodo->_Siguiente != NULL)	nNodo->_Siguiente->_Anterior = nNodo;
					if (nPadre->_Hijos.size() == 0) nPadre->_Hijos.push_back(nNodo);
					else							nPadre->_Hijos.insert(nPadre->_Hijos.begin() + nPosicionNodo, nNodo);
				}
			}

			nNodo->_Anterior = nAnterior;
			nNodo->_Icono = nIcono;
			nNodo->_Texto = nTexto;
			nNodo->_AnchoTexto = Tam.cx;

			if (nAnterior != NULL) nAnterior->_Siguiente = nNodo;

			if (nPadre == NULL) nNodo->_NumNodosSuperiores = 0;
			else				nNodo->_NumNodosSuperiores = nPadre->_NumNodosSuperiores + 1;
			return nNodo;
		}

		//! Función que recalcula los tamaños de todos los textos del ArbolEx.
		/*! Esta función recaltula los tamaños de todos los textos del ArbolEx.
				\fn			void ArbolEx_ActualizarTamTexto(void);
				\return		No devuelve nada.
		*/
		void DWLArbolEx_Nucleo::ArbolEx_ActualizarTamTexto(void) {
			SIZE Tam;
            _ArbolEx_AltoLinea = 14;
//            SelectObject(_ArbolEx_Buffer, ArbolEx_Estilos.Fuentes.Normal());
			for (size_t i = 0; i < _ArbolEx_NodosLineales.size(); i++) {
                if (_ArbolEx_NodosLineales[i]->_Fuentes != NULL) SelectObject(_ArbolEx_Buffer, _ArbolEx_NodosLineales[i]->_Fuentes->Normal());
				else                                             SelectObject(_ArbolEx_Buffer, ArbolEx_Estilos.Fuentes.Normal());

				GetTextExtentPoint(_ArbolEx_Buffer, _ArbolEx_NodosLineales[i]->Texto(), _ArbolEx_NodosLineales[i]->LongitudTexto(), &Tam);
				_ArbolEx_NodosLineales[i]->_AnchoTexto = Tam.cx;
                if (_ArbolEx_AltoLinea < Tam.cy + 3) _ArbolEx_AltoLinea = Tam.cy + 3;
			}
		}

		//! Función que borra un nodo del ArbolEx.
		/*! Esta función borra el nodo especificado del ArbolEx.
				\fn			void ArbolEx_EliminarNodo(HWND hWndControl, DWLArbolEx_Nodo *bNodo, const bool Actualizar = true);
				\param[in]	hWndControl	: HWND del control que contiene el ArbolEx.
				\param[in]	nNodo		: DWLArbolEx_Nodo que se quiere eliminar.
				\param[in]	Actualizar	: Valor para decidir si se debe actualizar el ArbolEx.
				\return		No devuelve nada.
				\sa			ArbolEx_EliminarNodosSeleccionados(), ArbolEx_EliminarTodosLosNodos()
		*/
		void DWLArbolEx_Nucleo::ArbolEx_EliminarNodo(HWND hWndControl, DWLArbolEx_Nodo *bNodo, const bool Actualizar) {
		#if defined DWL_ARBOLEX_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::EliminarNodo\n"));
		#endif
			size_t i = 0;
			_ArbolEx_NodoMarcado = bNodo->_Siguiente;
			if (bNodo->_Padre != NULL) { // Si tiene padre
                if (bNodo->_Padre->_Hijos.size() > 0) {
    				for (i = static_cast<int>(bNodo->_Padre->_Hijos.size()); i > 0; i--) {
//    				for (i = static_cast<int>(bNodo->_Padre->_Hijos.size()) -1; i < -1; i--) {
					    if (bNodo->_Padre->_Hijos[i - 1] == bNodo) {
						    bNodo->_Padre->_Hijos.erase(bNodo->_Padre->_Hijos.begin() + (i - 1));
						    break;
					    }
				    }
                }
			}
			else { // Si no tiene padre
                if (_ArbolEx_Nodos.size() > 0) {
	//		        for (i = _ArbolEx_Nodos.size() -1; i != 0; i--) {
    				for (i = static_cast<int>(_ArbolEx_Nodos.size()); i > 0; i--) {
//    				for (i = static_cast<int>(_ArbolEx_Nodos.size()) -1; i < -1; i--) {
					    if (_ArbolEx_Nodos[i - 1] == bNodo) {
						    _ArbolEx_Nodos.erase(_ArbolEx_Nodos.begin() + (i - 1));
						    break;
					    }
				    }
                }
			}
			// Elimino el espacio del nodo lineal
            if (_ArbolEx_NodosLineales.size() > 0) {
    //            for (i = _ArbolEx_NodosLineales.size() -1; i != 0; i--) {
   				for (i = static_cast<int>(_ArbolEx_NodosLineales.size()); i > 0; i--) {
//    			for (i = static_cast<int>(_ArbolEx_NodosLineales.size()) -1; i < -1; i--) {
				    if (_ArbolEx_NodosLineales[i - 1] == bNodo) {
					    _ArbolEx_NodosLineales.erase(_ArbolEx_NodosLineales.begin() + (i - 1));
					    break;
				    }
			    }
            }
			// Reasigno los punteros (Siguiente , Anterior, Padre)
			bNodo->_BorrarNodo();
			if (bNodo->_Anterior != NULL) bNodo->_Anterior->_Siguiente = bNodo->_Siguiente;
			if (bNodo->_Siguiente != NULL) bNodo->_Siguiente->_Anterior = bNodo->_Anterior;
			// Borro el nodo de la memoria junto con todos sus hijos
			delete bNodo;

			if (Actualizar == true) {
				ArbolEx_ActualizarVectorLineal(hWndControl);
				_ArbolEx_NodoResaltado = NULL;
				_ArbolEx_UNodoResaltado = NULL;
				_ArbolEx_ExpansorResaltado = NULL;
				_ArbolEx_ExpansorPresionado = NULL;

				if (_BarraScrollEx_MaximoV  > _BarraScrollEx_PaginaV) {
					if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
				}
				else {
					BarraScrollEx_ValorV(0);
				}
				_ArbolEx_UYMouse = !_ArbolEx_AltoLinea;
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
				Repintar(true);
			}
		}


		//! Función que borra todos los nodos selecionados.
		/*! Esta función borra todos los nodos selecionados del ArbolEx.
				\fn			void ArbolEx_EliminarNodosSeleccionados(HWND hWndControl, DWLArbolEx_Nodo *bNodo = NULL);
				\param[in]	hWndControl	: HWND del control que contiene el ArbolEx.
				\param[in]	bNodo		: DWLArbolEx_Nodo del que partira la busqueda de nodos seleccionados. Puede ser NULL.
				\return		No devuelve nada.
				\sa			ArbolEx_EliminarNodo(), ArbolEx_EliminarTodosLosNodos()
		*/
		void DWLArbolEx_Nucleo::ArbolEx_EliminarNodosSeleccionados(HWND hWndControl, DWLArbolEx_Nodo *bNodo) {
		#if defined DWL_ARBOLEX_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::EliminarNodosSeleccionados\n"));
		#endif
			if (_ArbolEx_Nodos.size() == 0) return;
			DWLArbolEx_Nodo *TmpNodo = bNodo;
			DWLArbolEx_Nodo *TmpNodo2 = NULL;
			// Si no hay ninguno marcado selecciono el primero
			if (TmpNodo == NULL) TmpNodo = _ArbolEx_Nodos[0];
			while (TmpNodo != NULL) {
				TmpNodo2 = TmpNodo;
				TmpNodo = TmpNodo->_Siguiente;
				if (TmpNodo2->_Seleccionado == true) {
					ArbolEx_EliminarNodo(hWndControl, TmpNodo2);
				}
				else {
					if (TmpNodo2->_Hijos.size() > 0)	ArbolEx_EliminarNodosSeleccionados(hWndControl, TmpNodo2->_Hijos[0]);
				}
			}
			if (bNodo == NULL) { // Se han borrado todos los nodos selecionados
				_ArbolEx_NodoResaltado = NULL;
				_ArbolEx_UNodoResaltado = NULL;
				_ArbolEx_ExpansorResaltado = NULL;
				_ArbolEx_ExpansorPresionado = NULL;

				ArbolEx_ActualizarVectorLineal(hWndControl);
				if (_BarraScrollEx_MaximoV  > _BarraScrollEx_PaginaV) {
					if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
				}
				else {
					BarraScrollEx_ValorV(0);
				}
				_ArbolEx_UYMouse = !_ArbolEx_AltoLinea;
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
				Repintar(true);
			}
		}

		//! Función que actualiza todos los datos del ArbolEx.
		/*! Esta función actualiza todos los datos del ArbolEx.
				\fn			void ArbolEx_ActualizarTodo(HWND hWndControl, RECT *Espacio);
				\param[in]	hWndControl	  : HWND del control que contiene el ArbolEx.
				\param[in]	Espacio		  : Recta que debe contener el espacio para el ArbolEx.
                \param[in]  ExpandirNodos : Especifica true para que todos los nodos salgan expandidos, en caso contrario se mantendran como estaban.
				\return		No devuelve nada.
				\remarks	Esta función se usa para actualizar todos los estilos y nodos del ArbolEx. Si necesitas actualizar el tamaño de los textos por haber cambiado la fuente, deberas usar tambien ArbolEx_ActualizarTamTexto().
		*/
		void DWLArbolEx_Nucleo::ArbolEx_ActualizarTodo(HWND hWndControl, RECT *Espacio, const bool ExpandirNodos) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::ActualizarTodo\n"));
			#endif

            // Miramos si el borde ha cambiado
            HRGN Region = CreateRectRgn(0,0,0,0);
            int RR = GetWindowRgn(hWndControl, Region);
            // - Si hay que pintar borde y la region no existe
            if (ArbolEx_Estilos.PintarBorde == true && RR == NULLREGION) {
                HRGN Region2 = CreateRoundRectRgn(0, 0, (Espacio->right - Espacio->left) + 1, (Espacio->bottom - Espacio->top) + 1, 2, 2);
                SetWindowRgn(hWndControl, Region2, FALSE);
            }
            // - Si no hay que pintar el borde y la region existe
            if (ArbolEx_Estilos.PintarBorde == false && RR != NULLREGION && RR != ERROR) {
                SetWindowRgn(hWndControl, NULL, FALSE);
            }
            DeleteObject(Region);

            // Actualizo el vector lineal de los nodos
			ArbolEx_ActualizarVectorLineal(hWndControl, ExpandirNodos);

            // Miro que la barra de scroll no se salga de los limites
			if (_BarraScrollEx_MaximoV  > _BarraScrollEx_PaginaV) {
				if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
			}
			else {
				BarraScrollEx_ValorV(0);
			}
			_ArbolEx_UYMouse = !_ArbolEx_AltoLinea;

			// Repinto el fondo en el DC que tenemos en memoria
            ArbolEx_Evento_Pintar_Fondo(_ArbolEx_FondoDC, Espacio);

            // Repinto el control
//			Repintar(true);
		}

		//! Función que borra toda la memoria del ArbolEx.
		/*! Esta función borra toda la memora del ArbolEx, incluidos los nodos y sus fuentes propias.
				\fn			void ArbolEx_BorrarMemoria(void);
				\return		No devuelve nada.
		*/
		void DWLArbolEx_Nucleo::ArbolEx_BorrarMemoria(void) {
			if (_ArbolEx_Buffer != NULL) {
				SelectObject(_ArbolEx_Buffer, _ArbolEx_Viejo);
				SelectObject(_ArbolEx_Buffer, _ArbolEx_VFuente);
				DeleteObject(_ArbolEx_Bmp);
				DeleteDC(_ArbolEx_Buffer);
				_ArbolEx_Buffer = NULL;
				SelectObject(_ArbolEx_FondoDC, _ArbolEx_ViejoFondo);
				DeleteObject(_ArbolEx_BmpFondo);
				DeleteDC(_ArbolEx_FondoDC);
				_ArbolEx_FondoDC = NULL;
			}
		}

		//! Función que retorna el nodo que esta debajo de las coordenadas especificadas.
		/*! Esta función retorna el nodo o la parte del nodo que esta debajo de las coordenadas especificadas.
				\fn			DWLArbolEx_Nodo *ArbolEx_HitTest(const int cX, const int cY, const DWL_Enum_ArbolEx_HitTest Tipo = DWL_Enum_ArbolEx_HitTest_Texto_Icono);
				\param[in]	cX		: Coordenada X.
				\param[in]	cY		: Coordenada Y.
				\param[in]	nTipo	: Tipo de busqueda.
				\return		No devuelve nada.
				\remarks	Hay varios tipos de busqueda : [DWL_Enum_ArbolEx_HitTest_Texto] Solo el texto, [DWL_Enum_ArbolEx_HitTest_Icono] Solo el icono, [DWL_Enum_ArbolEx_HitTest_Expansor] Solo el expansor, [DWL_Enum_ArbolEx_HitTest_Texto_Icono] Texto, icono y expansor.
		*/
		DWLArbolEx_Nodo *DWLArbolEx_Nucleo::ArbolEx_HitTest(const int cX, const int cY, const DWL_Enum_ArbolEx_HitTest Tipo) {
		#if defined DWL_ARBOLEX_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::HitTest(cX %d, cY %d, Tipo %d)  "), cX, cY, Tipo);
		#endif
			int Linea = static_cast<int>(cY / _ArbolEx_AltoLinea);
			if (_ArbolEx_Nodos.size() == 0) return NULL;
			DWLArbolEx_Nodo *NPosicion = _ArbolEx_Nodos[0];
			// Situo NPosicion al nodo que se ve en la pagina en las coordenadas especificadas
			for (int i = 0; i < _BarraScrollEx_ValorV + Linea; i++) {
				if (NPosicion->_Expandido == true && NPosicion->_Hijos.size() > 0)	{ // Si esta expandido
					NPosicion = NPosicion->_Hijos[0];
				}
				else {
					while (NPosicion->_Siguiente == NULL) {
						if (NPosicion->_Padre == NULL)	return NULL; // Se ha llegado al final
						NPosicion = NPosicion->_Padre;
					}
					NPosicion = NPosicion->_Siguiente;
				}
			}
			POINT Pt = { cX, cY };
			RECT  DR;
			DR.top =  Linea * _ArbolEx_AltoLinea;
			DR.bottom = (Linea +1) * _ArbolEx_AltoLinea;
			switch (Tipo) {
				case DWL_Enum_ArbolEx_HitTest_Texto :
					DR.left = ((NPosicion->_NumNodosSuperiores + 1) * 18) - _BarraScrollEx_ValorH;
					DR.right = DR.left + NPosicion->_AnchoTexto;
					break;
				case DWL_Enum_ArbolEx_HitTest_Icono :
					DR.left = ((NPosicion->_NumNodosSuperiores + 1) * 18) - _BarraScrollEx_ValorH;
					DR.right = DR.left + 16;
					break;
				case DWL_Enum_ArbolEx_HitTest_Expansor :
					DR.left = (((NPosicion->_NumNodosSuperiores + 1) * 18) - 17) - _BarraScrollEx_ValorH;
					DR.right = DR.left + 12;
					break;
				case DWL_Enum_ArbolEx_HitTest_Texto_Icono :
					DR.left = ((NPosicion->_NumNodosSuperiores + 1) * 18) - _BarraScrollEx_ValorH;
					DR.right = DR.left + 21 + NPosicion->_AnchoTexto;
					break;
			}
			if (PtInRect(&DR, Pt) == TRUE)	{
				#if defined DWL_ARBOLEX_DEBUG
					DWL::DWLDebug::ImprimirDebug(TEXT("= %s \n"), NPosicion->Texto());
				#endif
				return NPosicion;
			}
			else {
				#if defined DWL_ARBOLEX_DEBUG
					DWL::DWLDebug::ImprimirDebug(TEXT("= NULL\n"));
				#endif
				return NULL;
			}
		}


		//! Función que enlaza todos los nodos lienales entre ellos.
		/*! Esta función enlaza todos los nodos lienales entre ellos.
				\fn			void ArbolEx_ActualizarVectorLineal(HWND hWndControl, const bool ExpandirTodo = false);;
				\param[in]	hWndControl		: HWND del control que contiene el ArbolEx.
				\param[in]	ExpandirTodo	: Parametro en el que especificamos si queremos los nodos expandidos o contraidos.
				\return		No devuelve nada.
		*/
		void DWLArbolEx_Nucleo::ArbolEx_ActualizarVectorLineal(HWND hWndControl, const bool ExpandirTodo) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::ActualizarVectorLineal\n"));
			#endif
			_ArbolEx_NodosLineales.resize(0);
			_BarraScrollEx_MaximoV = static_cast<int>(_ArbolEx_Nodos.size());
			_BarraScrollEx_MaximoH = 1;
			unsigned int TotalNodos = static_cast<unsigned int>(_ArbolEx_Nodos.size());
			for (unsigned int i = 0; i < TotalNodos; i++) {
				_ArbolEx_NodosLineales.push_back(_ArbolEx_Nodos[i]);
				if (_ArbolEx_Nodos[i]->_Hijos.size() > 0)	ArbolEx_MirarHijosVectorLineal(_ArbolEx_Nodos[i], ExpandirTodo);
			}

			RECT R;
			GetClientRect(hWndControl, &R);
			int Borde = 0;
			if (ArbolEx_Estilos.PintarBorde == true) Borde = 4;
			_BarraScrollEx_PaginaV = (static_cast<int>(static_cast<float>(R.bottom - Borde) / static_cast<float>(_ArbolEx_AltoLinea)));
			_BarraScrollEx_PaginaH = R.right - Borde;
			if (BarraScrollEx_VisibleH() == TRUE) _BarraScrollEx_PaginaV -= 1;
			if (BarraScrollEx_VisibleV() == TRUE) _BarraScrollEx_PaginaH -= 21;


			if (_ArbolEx_Buffer != NULL) {
				SelectObject(_ArbolEx_Buffer, _ArbolEx_VFuente);
				SelectObject(_ArbolEx_Buffer, _ArbolEx_ViejoFondo);
				DeleteObject(_ArbolEx_BmpFondo);
				DeleteDC(_ArbolEx_Buffer);
			}
			int AnchoBuffer = _BarraScrollEx_MaximoH;
			if (AnchoBuffer < R.right) AnchoBuffer = R.right;
			HDC hDC = GetDC(hWndControl);
			_ArbolEx_Buffer		= CreateCompatibleDC(NULL);
			_ArbolEx_BmpFondo	= CreateCompatibleBitmap(hDC, AnchoBuffer, _ArbolEx_AltoLinea);
			_ArbolEx_ViejoFondo = static_cast<HBITMAP>(SelectObject(_ArbolEx_Buffer, _ArbolEx_BmpFondo));
			_ArbolEx_VFuente    = static_cast<HFONT>(SelectObject(_ArbolEx_Buffer, ArbolEx_Estilos.Fuentes.Normal()));
			SetBkMode(_ArbolEx_Buffer, TRANSPARENT);
			ReleaseDC(hWndControl, hDC);
			BarraScrollEx_PosicionarScrolls(hWndControl, &R, false, ArbolEx_Estilos.PintarBorde);

			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("_BarraScrollEx_PaginaH %d _BarraScrollEx_MaximoH %d _BarraScrollEx_ValorH %d\n"), _BarraScrollEx_PaginaH, _BarraScrollEx_MaximoH, _BarraScrollEx_ValorH);
			#endif
		}


		//! Función que recorre un nodo para enumerar todos sus nodos hijos y asi agregarlos al vector lineal.
		/*! Esta función recorre un nodo para enumerar todos sus nodos hijos y asi agregarlos al vector lineal.
				\fn			void ArbolEx_MirarHijosVectorLineal(DWLArbolEx_Nodo *nNodo, const bool ExpandirTodo);
				\param[in]	hWndControl		: HWND del control que contiene el ArbolEx.
				\param[in]	ExpandirTodo	: Parametro en el que especificamos si queremos los nodos expandidos o contraidos.
				\return		No devuelve nada.
				\remarks	Funcion de uso interno para ArbolEx_ActualizarVectorLineal().
		*/
		void DWLArbolEx_Nucleo::ArbolEx_MirarHijosVectorLineal(DWLArbolEx_Nodo *nNodo, const bool ExpandirTodo) {
		    #if defined DWL_ARBOLEX_DEBUG
			    DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::MirarHijosVectorLineal\n"));
		    #endif
			unsigned int TotalNodos = static_cast<unsigned int>(nNodo->_Hijos.size());
			int          Retro      = 0;
			DWLArbolEx_Nodo *Tmp	= nNodo;
			for (unsigned int i = 0; i < TotalNodos; i++) {
				Tmp = nNodo->_Hijos[i];
					if (ExpandirTodo == true || nNodo->_Expandido == true) {
					if (nNodo->TotalHijos() > 0) nNodo->_Expandido = true;
				}
				_ArbolEx_NodosLineales.push_back(nNodo->_Hijos[i]);
				if (nNodo->Expandido() == true) {
					Retro = 36;
					while (Tmp->_Padre != NULL) {
						Tmp = Tmp->_Padre;
						Retro += 18;
					}
					if (_BarraScrollEx_MaximoH < (nNodo->_Hijos[i]->_AnchoTexto + Retro + 20)) _BarraScrollEx_MaximoH = nNodo->_Hijos[i]->_AnchoTexto + Retro + 1;
					#if defined DWL_ARBOLEX_DEBUG
						DWL::DWLDebug::ImprimirDebugMS(TEXT("%s = %d + %d\n"), nNodo->_Hijos[i]->Texto(), nNodo->_Hijos[i]->_AnchoTexto, Retro);
					#endif

					_BarraScrollEx_MaximoV ++;
				}
				if (nNodo->_Hijos[i]->_Hijos.size() > 0) ArbolEx_MirarHijosVectorLineal(nNodo->_Hijos[i], ExpandirTodo);
			}
		}

		//! Función que procesa los botones presionados del mouse en el ArbolEx.
		/*! Esta función procesa los botones presionados del mouse en el ArbolEx.
				\fn			BOOL ArbolEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	hWndControl		: HWND del control que contiene el ArbolEx.
				\param[in]	RectaControl	: Recta con el espacio del ArbolEx.
				\param[in]	Boton			: Boton del mouse presionado.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonPresionado del control que vaya a contener el ArbolEx.
				\sa			ArbolEx_Mouse_Movimiento(), ArbolEx_Mouse_BotonSoltado()
		*/
		BOOL DWLArbolEx_Nucleo::ArbolEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Mouse_BotonPresionado\n"));
			#endif
			if (BarraScrollEx_Mouse_BotonPresionado(hWndControl, RectaControl, Boton, cX, cY, Param) == TRUE) return TRUE;

			int nAncho = RectaControl->right - RectaControl->left;
			int nAlto = RectaControl->bottom - RectaControl->top;
			if (BarraScrollEx_VisibleV() == TRUE) nAncho -= 17;
			if (BarraScrollEx_VisibleH() == TRUE) nAlto -= 17;
			if (cX < 0 || cX > nAncho || cY < 0 || cY > nAlto) return TRUE;

			_ArbolEx_ExpansorPresionado = ArbolEx_HitTest(cX, cY, DWL_Enum_ArbolEx_HitTest_Expansor);
			if (_ArbolEx_ExpansorPresionado == NULL) {
				_ArbolEx_NodoPresionado = ArbolEx_HitTest(cX, cY, DWL_Enum_ArbolEx_HitTest_Texto_Icono);
			}

			if (_ArbolEx_Teclado[VK_SHIFT] == false) _ArbolEx_NodoShifteado = _ArbolEx_NodoPresionado;

			HDC hDC = GetDC(hWndControl);
			if (_ArbolEx_NodoPresionado != NULL) {
				ArbolEx_PintarNodo(hDC, RectaControl, _ArbolEx_NodoPresionado, static_cast<int>(cY / _ArbolEx_AltoLinea));
			}
			if (_ArbolEx_ExpansorPresionado != NULL) {
				ArbolEx_PintarNodo(hDC, RectaControl, _ArbolEx_ExpansorPresionado, static_cast<int>(cY / _ArbolEx_AltoLinea));
			}
			ReleaseDC(hWndControl, hDC);
			return TRUE;
		}

	    //! Función que procesa los botones soltados del mouse en el ArbolEx.
	    /*! Esta función procesa los botones soltados del mouse en el ArbolEx.
			    \fn			BOOL ArbolEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
			    \param[in]	hWndControl		: HWND del control que contiene el ArbolEx.
			    \param[in]	RectaControl	: Recta con el espacio del ArbolEx.
			    \param[in]	Boton			: Boton del mouse presionado.
			    \param[in]	cX				: Coordenada X del mouse relativa al control.
			    \param[in]	cX				: Coordenada Y del mouse relativa al control.
			    \param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
			    \return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
			    \remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonSoltado del control que vaya a contener el ArbolEx.
			    \sa			ArbolEx_Mouse_Movimiento(), ArbolEx_Mouse_BotonPresionado()
	    */
		BOOL DWLArbolEx_Nucleo::ArbolEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Mouse_BotonSoltado\n"));
			#endif
			if (_ArbolEx_Editando == true) ArbolEx_CancelarLabelEdit(hWndControl);
			if (BarraScrollEx_Mouse_BotonSoltado(hWndControl, RectaControl, Boton, cX, cY, Param) == TRUE) return TRUE;

			int nAncho = RectaControl->right - RectaControl->left;
			int nAlto  = RectaControl->bottom - RectaControl->top;
			if (BarraScrollEx_VisibleV() == TRUE) nAncho -= 17;
			if (BarraScrollEx_VisibleH() == TRUE) nAlto -= 17;
			if (cX < 0 || cX > nAncho || cY < 0 || cY > nAlto) return TRUE;

			if (_ArbolEx_ExpansorPresionado == NULL) {
				bool			Shift					= (Param & MK_SHIFT)   ? true : false;
				bool			Control					= (Param & MK_CONTROL) ? true : false;
				int				TotalSeleccionados		= 0;
				int				TotalSubSeleccionados	= 0;
				unsigned int	i;
                if (ArbolEx_Estilos.MultiSeleccion == false) {
					Shift = false;
					Control = false;
				}

				for (i = 0; i < _ArbolEx_NodosLineales.size(); i++) {
					if (_ArbolEx_NodosLineales[i]->Seleccionado() == true)		TotalSeleccionados ++;
					if (_ArbolEx_NodosLineales[i]->SubSeleccionado() == true)	TotalSubSeleccionados ++;
				}

				if (Shift == false && Control == false) {
					if (Boton == 1) {
						if (TotalSeleccionados - TotalSubSeleccionados < 2) {
							ArbolEx_DesSeleccionarTodo(false);
							if (_ArbolEx_NodoPresionado != NULL) _ArbolEx_NodoPresionado->Seleccionado(true);
							_ArbolEx_NodoMarcado = _ArbolEx_NodoPresionado;
						}
					}
					else if (Boton == 0 || Boton == 2) { // Los botones X no se incluyen porque no tienen evento presionado
						ArbolEx_DesSeleccionarTodo(false);
						if (_ArbolEx_NodoPresionado != NULL) _ArbolEx_NodoPresionado->Seleccionado(true);
						_ArbolEx_NodoMarcado = _ArbolEx_NodoPresionado;
					}
					else if (Boton == 3) { // Mostrar tooltip
						ArbolEx_DesSeleccionarTodo(false);
						if (_ArbolEx_NodoPresionado != NULL) _ArbolEx_NodoPresionado->Seleccionado(true);
						_ArbolEx_NodoMarcado = _ArbolEx_NodoPresionado;
						_ArbolEx_TT_UltimoNodo = _ArbolEx_NodoPresionado;
						_ArbolEx_NodoResaltado = _ArbolEx_NodoPresionado;
						
						SendMessage(GetParent(hWndControl), DWL_TOOLTIPEX_MOSTRAR, GetWindowLongPtr(hWndControl, GWL_ID), 0);
					}
				}

				if (Control == true) {
					if (_ArbolEx_NodoPresionado != NULL && Boton == 0) _ArbolEx_NodoPresionado->Seleccionado(!_ArbolEx_NodoPresionado->Seleccionado());
				}

				if (Shift == true) {
					if (_ArbolEx_NodoPresionado != _ArbolEx_NodoShifteado && _ArbolEx_NodoPresionado != NULL && _ArbolEx_NodoShifteado != NULL) {
						bool OrdenAscendente;
						for (i = 0; i < _ArbolEx_NodosLineales.size(); i++) {
							if (_ArbolEx_NodoPresionado == _ArbolEx_NodosLineales[i]) {
								OrdenAscendente = false;
								break;
							}
							if (_ArbolEx_NodoShifteado == _ArbolEx_NodosLineales[i]) {
								OrdenAscendente = true;
								break;
							}
						}
						ArbolEx_DesSeleccionarTodo();
						if (OrdenAscendente == true) {
							while (_ArbolEx_NodosLineales[i] != _ArbolEx_NodoPresionado) {
								_ArbolEx_NodosLineales[i]->Seleccionado(true, false);
								i++;
							}
						}
						else {
							while (_ArbolEx_NodosLineales[i] != _ArbolEx_NodoShifteado) {
								_ArbolEx_NodosLineales[i]->Seleccionado(true, false);
								i++;
							}
						}
						_ArbolEx_NodosLineales[i]->Seleccionado(true, false);
					}
				}

				SetFocus(hWndControl);
				// Dobleclick
				if (_ArbolEx_UltimoClick + GetDoubleClickTime() > GetTickCount() && _ArbolEx_UltimoBoton == Boton) {
					_ArbolEx_UltimoClick = 0;
					// PARTE PARA EL DOBLECLICK
					if (_ArbolEx_PosUltimoClick == _ArbolEx_NodoResaltado) {
						// Si ArbolEx_Evento_Mouse_DobleClick no retorna -1 hacemos la parte del expansor
						if (ArbolEx_Evento_Mouse_DobleClick(Boton, cX, cY) != -1) {
							if (_ArbolEx_NodoResaltado != NULL) {
								if (_ArbolEx_NodoResaltado->_Expandido == false) ArbolEx_Evento_Expandir(_ArbolEx_NodoResaltado);
								ArbolEx_Expandir(hWndControl, _ArbolEx_NodoResaltado, !_ArbolEx_NodoResaltado->_Expandido);
								Repintar(true);
							}
						}						
						DWLArbolEx_ParametrosClick ParamFinal(_ArbolEx_NodoPresionado, cX, cY, GetWindowLongPtr(hWndControl, GWL_ID), Boton);
						SendMessage(GetParent(hWndControl), DWL_ARBOLEX_DOBLECLICK, reinterpret_cast<WPARAM>(&ParamFinal), 0);
					}
				}
				else {
					_ArbolEx_UltimoBoton = Boton;
					_ArbolEx_UltimoClick = GetTickCount();
				}
			}
			// Click en el Expansor
			else {
				_ArbolEx_NodoResaltado = _ArbolEx_ExpansorPresionado;
				_ArbolEx_UNodoResaltado = _ArbolEx_NodoResaltado;
				_ArbolEx_UYMouse = nAlto + _ArbolEx_AltoLinea;
				// Llamamos al evento expandir
				if (_ArbolEx_NodoResaltado->_Expandido == false) ArbolEx_Evento_Expandir(_ArbolEx_NodoResaltado);
				ArbolEx_Expandir(hWndControl, _ArbolEx_NodoResaltado, !_ArbolEx_NodoResaltado->_Expandido);
				Repintar(true);
			}

			DWLArbolEx_Nodo *Tmp = _ArbolEx_NodoPresionado;
			_ArbolEx_ExpansorPresionado = NULL;
			_ArbolEx_NodoPresionado = NULL;
			Repintar(true);
			_ArbolEx_PosUltimoClick = _ArbolEx_NodoResaltado;

			if (_ArbolEx_NodoResaltado == Tmp) {
				DWLArbolEx_ParametrosClick ParamFinal(Tmp, cX, cY, GetWindowLongPtr(hWndControl, GWL_ID), Boton);
				SendMessage(GetParent(hWndControl), DWL_ARBOLEX_CLICK, reinterpret_cast<WPARAM>(&ParamFinal), 0);
			}
			return TRUE;
		}

		//! Función para expandir / contraer el nodo especificado.
		/*! Esta función expande / contrae el nodo especificado.
				\fn			void ArbolEx_Expandir(HWND hWndControl, DWLArbolEx_Nodo *vNodo, const bool nExpandir, const bool nRepintar = false);
				\param[in]	hWndControl	: HWND del control que contiene el ArbolEx.
				\param[in]	nNodo		: Nodo que queremos expandir / contraer.
				\param[in]	nExpandir	: Variable en la que especificamos si hay que expandir o contraer.
				\param[in]	nRepintar	: Variable en la que especificamos si hay que repintar.
				\return		No devuelve nada.
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Expandir(HWND hWndControl, DWLArbolEx_Nodo *eNodo, const bool nExpandir, const bool nRepintar) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Expandir\n"));
			#endif
			eNodo->_Expandido = nExpandir;

			ArbolEx_ActualizarVectorLineal(hWndControl);
			if (_BarraScrollEx_MaximoV  > _BarraScrollEx_PaginaV) {
				if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) {
					BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
					_ArbolEx_NodoResaltado = NULL;
					_ArbolEx_UNodoResaltado = NULL;
					_ArbolEx_ExpansorResaltado = NULL;
					_ArbolEx_UExpansorResaltado = NULL;
				}
			}
			else {
				BarraScrollEx_ValorV(0);
			}
			_ArbolEx_UYMouse = !_ArbolEx_AltoLinea;
			if (nRepintar == true) {
				Repintar(true);
			}
		}

		//! Función que des-seleciona todos los nodos.
		/*! Esta función des-selecciona todos los nodos del ArbolEx.
				\fn			void ArbolEx_DesSeleccionarTodo(const bool nRepintar = false);
				\param[in]	nRepintar	: Parametro en el que especificamos si deseamos repintar el ArbolEx.
				\return		No devuelve nada.
		*/
		void DWLArbolEx_Nucleo::ArbolEx_DesSeleccionarTodo(const bool Repintar) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::DesSeleccionarTodo\n"));
			#endif
			for (unsigned int i = 0; i < _ArbolEx_NodosLineales.size(); i++) {
				_ArbolEx_NodosLineales[i]->_Seleccionado = false;
				_ArbolEx_NodosLineales[i]->_ArbolEx_SubSeleccion = false;
			}
		}

		//! Función que procesa el movimiento del mouse en el ArbolEx.
		/*! Esta función procesa el movimiento del mouse en el ArbolEx.
				\fn			BOOL ArbolEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param);
				\param[in]	hWndControl		: HWND del control que contiene el ArbolEx.
				\param[in]	RectaControl	: Recta con el espacio del ArbolEx.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_Movimiento del control que vaya a contener el ArbolEx.
				\sa			ArbolEx_Mouse_BotonPresionado(), ArbolEx_Mouse_BotonSoltado()
		*/
		BOOL DWLArbolEx_Nucleo::ArbolEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Mouse_Movimiento UY %d / AltoLinea %d = %d\n"), _ArbolEx_UYMouse, _ArbolEx_AltoLinea, static_cast<int>(_ArbolEx_UYMouse / _ArbolEx_AltoLinea));
			#endif

			if (BarraScrollEx_Mouse_Movimiento(hWndControl, RectaControl, cX, cY, Param, ArbolEx_Estilos.PintarBorde) == TRUE) {
				if (_ArbolEx_NodoPresionado == NULL && _ArbolEx_NodoResaltado != NULL) {
					_ArbolEx_NodoResaltado = NULL;
					Repintar();
				}
				return TRUE;
			}
			if (_ArbolEx_Editando == true) return TRUE;
			HDC hDC = GetDC(hWndControl);
			_ArbolEx_NodoResaltado = ArbolEx_HitTest(cX, cY);
			// Si no coinciden los nodos reseteamos el tooltip
			if (_ArbolEx_TT_UltimoNodo != _ArbolEx_NodoResaltado) {
				KillTimer(hWndControl, DWL_TIMER_TOOLTIP);
				SetTimer(hWndControl, DWL_TIMER_TOOLTIP, DWL_TIEMPO_TOOLTIP, NULL);
				SendMessage(GetParent(hWndControl), DWL_TOOLTIPEX_OCULTAR, GetWindowLong(hWndControl, GWL_ID), 0);
				_ArbolEx_TT_UltimoNodo = _ArbolEx_NodoResaltado;
			}
			_ArbolEx_ExpansorResaltado = ArbolEx_HitTest(cX, cY, DWL_Enum_ArbolEx_HitTest_Expansor);

			if (_ArbolEx_UYMouse > 0) {
				ArbolEx_PintarNodo(hDC, RectaControl, _ArbolEx_UNodoResaltado, static_cast<int>(_ArbolEx_UYMouse / _ArbolEx_AltoLinea));
				ArbolEx_PintarNodo(hDC, RectaControl, _ArbolEx_UExpansorResaltado, static_cast<int>(_ArbolEx_UYMouse / _ArbolEx_AltoLinea));
			}
			ArbolEx_PintarNodo(hDC, RectaControl, _ArbolEx_ExpansorResaltado, static_cast<int>(cY / _ArbolEx_AltoLinea));
			ArbolEx_PintarNodo(hDC, RectaControl, _ArbolEx_NodoResaltado, static_cast<int>(cY / _ArbolEx_AltoLinea));
			ReleaseDC(hWndControl, hDC);
			_ArbolEx_UYMouse = cY;
			_ArbolEx_UNodoResaltado = _ArbolEx_NodoResaltado;
			_ArbolEx_UExpansorResaltado = _ArbolEx_ExpansorResaltado;
			return TRUE;
		}


		//! Función virtual que monta los datos del tooltip antes de mostrarlo
		/*! Esta función virtual es llamada cuando el ArbolEx quiere mostrar un tooltip de un nodo.
				\fn			virtual void ArbolEx_Evento_MostrarToolTip(DWLArbolEx_Nodo *ttNodo);
				\param[in]	ttNodo : Nodo del que se va a mostrar la informacion.
				\return		No devuelve nada.
				\remarks	Por defecto el tooltip muestra el nombre y icono del nodo, y luego una lista con los 10 hijos siguientes.
							Puedes re-emplazar esta función y mostrar los datos que desees del nodo.
		*/
		/*void DWLArbolEx_Nucleo::ArbolEx_Evento_MostrarToolTip(DWLArbolEx_Nodo *ttNodo) {
			if (ttNodo == NULL) return;
			DWLArbolEx_Nodo *TmpNodo = NULL;
			ArbolEx_ToolTip.BorrarMemoria();
			ArbolEx_ToolTip.AgregarIconoTexto(ttNodo->Icono(), 16, 16, ttNodo->Texto());
			int Hijos = 0;
			TmpNodo = ttNodo->Hijo(0);
			while (TmpNodo != NULL) {
				if (Hijos == 10) {
					ArbolEx_ToolTip.AgregarTexto(TEXT("....."));
					break;
				}
				Hijos ++;
				ArbolEx_ToolTip.AgregarTexto(TmpNodo->Texto());
				TmpNodo = TmpNodo->Siguiente();
			}
			ArbolEx_ToolTip.MostrarToolTipEx();
		}*/


		//! Función que procesa la tecla Inicio.
		/*! Esta función procesa la tecla Inicio.
				\fn			void ArbolEx_Tecla_Inicio(HWND hWndControl, const bool nRepintar = true);
				\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
				\param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
				\return		No devuelve nada.
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Tecla_Inicio(HWND hWndControl, const bool nRepintar) {
		#if defined DWL_ARBOLEX_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Tecla_Inicio\n"));
		#endif
			int i;
			if (_ArbolEx_Teclado[VK_SHIFT] == true && ArbolEx_Estilos.MultiSeleccion == true) {
				for (i = static_cast<int>(_ArbolEx_NodosLineales.size()) -1; i != -1; i--) {
					if (_ArbolEx_NodosLineales[i] == _ArbolEx_NodoMarcado)
						break;
				}
				for (i = i; i != -1; i--) {
					_ArbolEx_NodosLineales[i]->Seleccionado(!_ArbolEx_NodosLineales[i]->_Seleccionado);
				}
			}
			else {
				ArbolEx_DesSeleccionarTodo();
			}
			BarraScrollEx_ValorV(0);
			_ArbolEx_NodoMarcado = _ArbolEx_Nodos[0];
			_ArbolEx_NodoMarcado->Seleccionado(true, nRepintar);
			BarraScrollEx_CalcularScrollV();

			BarraScrollEx_Repintar(hWndControl, true);
		}

		//! Función que procesa la tecla Fin.
		/*! Esta función procesa la tecla Fin.
				\fn			void ArbolEx_Tecla_Fin(HWND hWndControl, const bool nRepintar = true);
				\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
				\param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
				\return		No devuelve nada.
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Tecla_Fin(HWND hWndControl, const bool nRepintar) {
		#if defined DWL_ARBOLEX_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Tecla_Fin\n"));
		#endif
			int i;
			if (_ArbolEx_Teclado[VK_SHIFT] == true && ArbolEx_Estilos.MultiSeleccion == true) {
				for (i = _ArbolEx_NodosLineales.size() -1; i != -1; i--) {
					if (_ArbolEx_NodosLineales[i] == _ArbolEx_NodoMarcado)	break;
				}
				for (i = i; i != static_cast<int>(_ArbolEx_NodosLineales.size()) -1; i++) {
					_ArbolEx_NodosLineales[i]->Seleccionado(!_ArbolEx_NodosLineales[i]->_Seleccionado);
				}
			}
			else {
				ArbolEx_DesSeleccionarTodo();
			}
			BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
			if (_BarraScrollEx_ValorV < 0) BarraScrollEx_ValorV(0);
//			_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;
			_ArbolEx_NodoMarcado = _ArbolEx_Nodos[_ArbolEx_Nodos.size() -1];
			ArbolEx_HacerVisible(hWndControl, _ArbolEx_NodoMarcado);
			_ArbolEx_NodoMarcado->Seleccionado(true, nRepintar);
			BarraScrollEx_CalcularScrollV();

			BarraScrollEx_Repintar(hWndControl, true);
		}

	    //! Función que procesa la tecla cursor Arriba.
	    /*! Esta función procesa la tecla cursor Arriba.
			    \fn			void ArbolEx_Tecla_Arriba(HWND hWndControl, const bool nRepintar = true);
			    \param[in]	hWndControl : HWND del control que contiene el ArbolEx.
			    \param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
			    \return		No devuelve nada.
	    */
		void DWLArbolEx_Nucleo::ArbolEx_Tecla_Arriba(HWND hWndControl, const bool nRepintar) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Tecla_Arriba\n"));
			#endif
			unsigned int i;
			int          zz;
			DWLArbolEx_Nodo *Tmp = NULL;
			if (_ArbolEx_Teclado[VK_SHIFT] == false || ArbolEx_Estilos.MultiSeleccion == false) ArbolEx_DesSeleccionarTodo(false);
			for (i = 0; i < _ArbolEx_NodosLineales.size(); i++) {
				if (_ArbolEx_NodosLineales[i] == _ArbolEx_NodoMarcado) break;
			}
			bool NodoVisible = false;
			while (NodoVisible == false && i != 0) {
				i--;
				if (_ArbolEx_NodosLineales[i]->_Padre == NULL) NodoVisible = true; // no hay mas padres..
				else {
					Tmp = _ArbolEx_NodosLineales[i]->_Padre;
					NodoVisible = true;
					while (Tmp != NULL) {
						if (Tmp->_Expandido == false) {
							NodoVisible = false;
							break;
						}
						Tmp = Tmp->_Padre;
					}
				}
			}
			zz = ArbolEx_PosicionVisibleNodo(_ArbolEx_NodosLineales[i]);
			if (zz < _BarraScrollEx_ValorV) _BarraScrollEx_ValorV --;
			_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;
			if (_ArbolEx_NodosLineales[i]->Seleccionado() == false)	_ArbolEx_NodosLineales[i]->Seleccionado(true, false);
			else											_ArbolEx_NodoMarcado->Seleccionado(false, false);
			_ArbolEx_NodoMarcado = _ArbolEx_NodosLineales[i];
			_ArbolEx_NodoMarcado->Seleccionado(true, nRepintar);
			BarraScrollEx_CalcularScrollV();

			BarraScrollEx_Repintar(hWndControl, true);
		}

		//! Función que procesa la tecla cursor Abajo.
		/*! Esta función procesa la tecla cursor Abajo.
				\fn			void ArbolEx_Tecla_Abajo(HWND hWndControl, const bool nRepintar = true);
				\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
				\param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
				\return		No devuelve nada.
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Tecla_Abajo(HWND hWndControl, const bool nRepintar) {
		#if defined DWL_ARBOLEX_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Tecla_Abajo\n"));
		#endif
			bool NodoVisible = false;
			DWLArbolEx_Nodo *Tmp = _ArbolEx_NodoMarcado;
			if (_ArbolEx_Teclado[VK_SHIFT] == false || ArbolEx_Estilos.MultiSeleccion == false) ArbolEx_DesSeleccionarTodo(false);
			if (_ArbolEx_NodoMarcado->_Hijos.size() > 0 && _ArbolEx_NodoMarcado->_Expandido == true) {
				_ArbolEx_NodoMarcado = _ArbolEx_NodoMarcado->_Hijos[0];
			}
			else {
				if (_ArbolEx_NodoMarcado->_Siguiente != NULL) {
					_ArbolEx_NodoMarcado = _ArbolEx_NodoMarcado->_Siguiente;
				}
				else {
					while (NodoVisible == false) {
						Tmp = Tmp->_Padre;
						if (Tmp == NULL) {
							// Salgo del while y no toco el nodo marcado
							break;
						}
						else {
							// Si esta expandido asigno  y el siguiente existe , lo asigno y salgo
							if (Tmp->_Expandido == true && Tmp->_Siguiente != NULL) {
								_ArbolEx_NodoMarcado = Tmp->_Siguiente;
								break;
							}
						}
					}
				}
			}
			if (ArbolEx_PosicionVisibleNodo(_ArbolEx_NodoMarcado) > (_BarraScrollEx_ValorV + _BarraScrollEx_PaginaV) -1) _BarraScrollEx_ValorV ++;
			if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
			if (_BarraScrollEx_ValorV < 0) BarraScrollEx_ValorV(0);
			_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;
			_ArbolEx_NodoMarcado->Seleccionado(true, false);
			BarraScrollEx_CalcularScrollV();

			BarraScrollEx_Repintar(hWndControl, true);
		}


		//! Función que procesa la tecla AvPag.
		/*! Esta función procesa la tecla AvPag.
				\fn			void ArbolEx_Tecla_AvancePagina(HWND hWndControl, const bool nRepintar = true);
				\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
				\param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
				\return		No devuelve nada.
		*/
		// Deberia posicionarme en el nodo que en el momento este marcado para luego comprobar uno a uno
		// los nodos inmediatamente siguentes a estos, con el fin de comprobar que todos sus padres esten expandidos,
		// en tal caso se sumaria al desplazamiento
		void DWLArbolEx_Nucleo::ArbolEx_Tecla_AvancePagina(HWND hWndControl, const bool nRepintar) {
		#if defined DWL_ARBOLEX_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Tecla_AvancePagina\n"));
		#endif
			if (_ArbolEx_NodoMarcado == ArbolEx_NodoFinPagina()) { // hay que retroceder una pagina
				unsigned int i;
				DWLArbolEx_Nodo *Tmp = NULL;
				ArbolEx_DesSeleccionarTodo(false);
				for (i = 0; i < _ArbolEx_NodosLineales.size(); i++) {
					if (_ArbolEx_NodosLineales[i] == _ArbolEx_NodoMarcado) break;
				}
				bool NodoVisible = false;
				for (int zz = 0; zz < _BarraScrollEx_PaginaV; zz++) {
					NodoVisible = false;
					while (NodoVisible == false && i != _ArbolEx_NodosLineales.size() -1) {
						i++;
						if (_ArbolEx_NodosLineales[i]->_Padre == NULL) NodoVisible = true;
						else {
							Tmp = _ArbolEx_NodosLineales[i]->_Padre;
							NodoVisible = true;
							while (Tmp != NULL) {
								if (Tmp->_Expandido == false) {
									NodoVisible = false;
									break;
								}
								Tmp = Tmp->_Padre;
							}
						}
					}
				}

				_BarraScrollEx_ValorV += _BarraScrollEx_PaginaV;
				if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
				_ArbolEx_NodoMarcado = _ArbolEx_NodosLineales[i];
			}
			else {
				_ArbolEx_NodoMarcado->Seleccionado(false, false);
				_ArbolEx_NodoMarcado = ArbolEx_NodoFinPagina();
			}
			_ArbolEx_NodoMarcado->Seleccionado(true, nRepintar);
			BarraScrollEx_CalcularScrollV();

			BarraScrollEx_Repintar(hWndControl, true);
		}

		//! Función que procesa la tecla RePag.
		/*! Esta función procesa la tecla RePag.
				\fn			void ArbolEx_Tecla_RetrocesoPagina(HWND hWndControl, const bool nRepintar = true);
				\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
				\param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
				\return		No devuelve nada.
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Tecla_RetrocesoPagina(HWND hWndControl, const bool nRepintar) {
		#if defined DWL_ARBOLEX_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Tecla_RetrocesoPagina\n"));
		#endif
			if (_ArbolEx_NodoMarcado == ArbolEx_NodoInicioPagina()) { // hay que retroceder una pagina
				unsigned int i;
				DWLArbolEx_Nodo *Tmp = NULL;
				ArbolEx_DesSeleccionarTodo(false);
				for (i = 0; i < _ArbolEx_NodosLineales.size(); i++) {
					if (_ArbolEx_NodosLineales[i] == _ArbolEx_NodoMarcado) break;
				}
				bool NodoVisible = false;
				for (int zz = 0; zz < _BarraScrollEx_PaginaV; zz++) {
					NodoVisible = false;
					while (NodoVisible == false && i != 0) {
						i--;
						if (_ArbolEx_NodosLineales[i]->_Padre == NULL) NodoVisible = true; // no hay mas padres..
						else {
							Tmp = _ArbolEx_NodosLineales[i]->_Padre;
							NodoVisible = true;
							while (Tmp != NULL) {
								if (Tmp->_Expandido == false) {
									NodoVisible = false;
									break;
								}
								Tmp = Tmp->_Padre;
							}
						}
					}
				}
				_BarraScrollEx_ValorV -= _BarraScrollEx_PaginaV;
				if (_BarraScrollEx_ValorV < 0) BarraScrollEx_ValorV(0);
				_ArbolEx_NodoMarcado = _ArbolEx_NodosLineales[i];
			}
			else {
				_ArbolEx_NodoMarcado->Seleccionado(false, false);
				_ArbolEx_NodoMarcado = ArbolEx_NodoInicioPagina();
			}
			_ArbolEx_NodoMarcado->Seleccionado(true, nRepintar);
			BarraScrollEx_CalcularScrollV();
			BarraScrollEx_Repintar(hWndControl, true);
		}

		//! Función que procesa la tecla cursor Derecha.
		/*! Esta función procesa la tecla cursor Derecha.
				\fn			void ArbolEx_Tecla_Derecha(HWND hWndControl, const bool nRepintar = true);
				\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
				\param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
				\return		No devuelve nada.
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Tecla_Derecha(HWND hWndControl, const bool nRepintar) {
		#if defined DWL_ARBOLEX_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Tecla_Derecha\n"));
		#endif
			if (_ArbolEx_NodoMarcado->_Hijos.size() > 0)  {
				ArbolEx_Expandir(hWndControl, _ArbolEx_NodoMarcado, true, nRepintar);
				ArbolEx_Evento_Expandir(_ArbolEx_NodoMarcado);
			}
			BarraScrollEx_CalcularScrollV();
			BarraScrollEx_CalcularScrollH();
			BarraScrollEx_Repintar(hWndControl, true);
		}

		//! Función que procesa la tecla cursor Izquierda.
		/*! Esta función procesa la tecla cursor Izquierda.
				\fn			void ArbolEx_Tecla_Izquierda(HWND hWndControl, const bool nRepintar = true);
				\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
				\param[in]	nRepintar	: Parametro en el que se indica si debemos repintar o no.
				\return		No devuelve nada.
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Tecla_Izquierda(HWND hWndControl, const bool nRepintar) {
		#if defined DWL_ARBOLEX_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Tecla_Izquierda\n"));
		#endif
			if (_ArbolEx_NodoMarcado->_Hijos.size() > 0) ArbolEx_Expandir(hWndControl, _ArbolEx_NodoMarcado, false, nRepintar);
			BarraScrollEx_CalcularScrollV();
			BarraScrollEx_CalcularScrollH();
			BarraScrollEx_Repintar(hWndControl, true);
		}

		//! Función que procesa las teclas presionadas en el ArbolEx.
		/*! Esta función procesa las teclas presionadas en el ArbolEx.
				\fn			void ArbolEx_Teclado_TeclaPresionada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Param);
				\param[in]	hWndControl	: HWND del control que contiene el ArbolEx.
				\param[in]	Tecla		: Tecla que se ha presionado.
				\param[in]	Repeticion  : Repeticion de la tecla.
				\param[in]	Param		: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		No devuelve nada.
				\remarks    Esta función debe ser enlazada con el Evento_TeclaPresionada del control que vaya a contener el ArbolEx.
				\sa			ArbolEx_Teclado_TeclaPresionada()
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Teclado_TeclaPresionada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params) {
			if (_ArbolEx_Nodos.size() == 0) return;
			if (_ArbolEx_NodoMarcado == NULL) _ArbolEx_NodoMarcado = ArbolEx_NodoInicioPagina();
			_ArbolEx_Teclado[Caracter] = true;

			// Tecla Inicio
			if (_ArbolEx_Teclado[VK_HOME] == true) { // Boton Inicio
				ArbolEx_Tecla_Inicio(hWndControl, false);
			}

			// Tecla Fin
			if (_ArbolEx_Teclado[VK_END] == true) { // Boton Fin
				ArbolEx_Tecla_Fin(hWndControl, false);
			}

			// Tecla cursor arriba
			if (_ArbolEx_Teclado[VK_UP] == true) {
				ArbolEx_Tecla_Arriba(hWndControl, false);
			}

			// Tecla cursor abajo
			if (_ArbolEx_Teclado[VK_DOWN] == true) {
				ArbolEx_Tecla_Abajo(hWndControl, false);
			}

			// Tecla cursor izquierda
			if (_ArbolEx_Teclado[VK_LEFT] == true) {
				ArbolEx_Tecla_Izquierda(hWndControl, false);
			}

			// Tecla cursor derecho
			if (_ArbolEx_Teclado[VK_RIGHT] == true) {
				ArbolEx_Tecla_Derecha(hWndControl, false);
			}

			// Tecla Re-Pág
			if (_ArbolEx_Teclado[VK_PRIOR] == true) {
				ArbolEx_Tecla_RetrocesoPagina(hWndControl, false);
			}

			// Tecla Av-Pág
 			if (_ArbolEx_Teclado[VK_NEXT] == true) {
				ArbolEx_Tecla_AvancePagina(hWndControl, false);
			}

		/*
		 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
		 * 0x40 : unassigned
		 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
		 */
			// Cualquier tecla valida
			if (Caracter >= 0x30 && Caracter <= 0x5A) {
				if (_ArbolEx_UVirtKey != Caracter) _ArbolEx_PosBuscar = 0;
				_ArbolEx_UVirtKey = Caracter;
				for (_ArbolEx_PosBuscar = _ArbolEx_PosBuscar; _ArbolEx_PosBuscar < _ArbolEx_NodosLineales.size(); _ArbolEx_PosBuscar++) {
					if (toupper(_ArbolEx_NodosLineales[_ArbolEx_PosBuscar]->_Texto[0]) == static_cast<int>(Caracter)) {
						if (_ArbolEx_NodosLineales[_ArbolEx_PosBuscar]->_Padre == NULL) {
							ArbolEx_DesSeleccionarTodo();
							_ArbolEx_NodoMarcado = _ArbolEx_NodosLineales[_ArbolEx_PosBuscar];
							_ArbolEx_NodoMarcado->Seleccionado(true);
							ArbolEx_HacerVisible(hWndControl, _ArbolEx_NodoMarcado, true);
//							_ArbolEx_NodoMarcado->HacerVisible();
							break;
						}
						else {
							if (_ArbolEx_NodosLineales[_ArbolEx_PosBuscar]->_Padre->_Expandido == true) {
								ArbolEx_DesSeleccionarTodo();
								_ArbolEx_NodoMarcado = _ArbolEx_NodosLineales[_ArbolEx_PosBuscar];
								_ArbolEx_NodoMarcado->Seleccionado(true);
								ArbolEx_HacerVisible(hWndControl, _ArbolEx_NodoMarcado, true);
								break;
							}
						}
					}
				}
				_ArbolEx_PosBuscar ++;
				if (_ArbolEx_PosBuscar == _ArbolEx_NodosLineales.size() +1) {
					_ArbolEx_PosBuscar = 0;
					MessageBeep(-1);
				}
			}
			// Asi eliminamos el tooltip al tocar una tecla, ademas de que si movemos con cursores o avpag repag ese nodo no es correcto.
			_ArbolEx_NodoResaltado = NULL;

			PostMessage(GetParent(hWndControl), DWL_ARBOLEX_TECLADO_PRESIONADO, static_cast<WPARAM>(Caracter), static_cast<LPARAM>(GetWindowLongPtr(hWndControl, GWL_ID)));

		}

		//! Función que procesa las teclas soltadas en el ArbolEx.
		/*! Esta función procesa las teclas presionadas en el ArbolEx.
				\fn			void ArbolEx_Teclado_TeclaSoltada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Param);
				\param[in]	hWndControl	: HWND del control que contiene el ArbolEx.
				\param[in]	Tecla		: Tecla que se ha soltado.
				\param[in]	Repeticion  : Repeticion de la tecla.
				\param[in]	Param		: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		No devuelve nada.
				\remarks    Esta función debe ser enlazada con el Evento_TeclaSoltada del control que vaya a contener el ArbolEx.
				\sa			ArbolEx_Teclado_TeclaSoltada()
		*/
		void DWLArbolEx_Nucleo::ArbolEx_Teclado_TeclaSoltada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params) {
			_ArbolEx_Teclado[Caracter] = false;
			PostMessage(GetParent(hWndControl), DWL_ARBOLEX_TECLADO_SOLTADO, static_cast<WPARAM>(Caracter), static_cast<LPARAM>(GetWindowLongPtr(hWndControl, GWL_ID)));
			if (Caracter == 13) PostMessage(GetParent(hWndControl), DWL_ARBOLEX_TECLADO_INTRO, static_cast<WPARAM>(Caracter), static_cast<LPARAM>(GetWindowLongPtr(hWndControl, GWL_ID)));
		}

		//! Función que obtiene el espacio que necesita el nodo para ser pintado.
		/*! Esta funcion obtiene el espacio que necesita el nodo para ser pintado.
				\fn			void ArbolEx_ObtenerRectaNodo(DWLArbolEx_Nodo *nNodo, RECT *Rectangulo);
				\param[in]	nNodo		: Nodo del que queremos obtener el espacio.
				\param[out]	Rectangulo	: Recta en la que se asignara el espacio necesario para el nodo.
				\return		No devuelve nada.
		*/
		void DWLArbolEx_Nucleo::ArbolEx_ObtenerRectaNodo(DWLArbolEx_Nodo *nNodo, RECT *Rectangulo) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::ObtenerRectaNodo\n"));
			#endif
			Rectangulo->left  = ((nNodo->_NumNodosSuperiores + 1) * 18) + 18;
			Rectangulo->right = Rectangulo->left + nNodo->_AnchoTexto + 2;
			// Reposiciono el puntero del nodo al siguiente nodo que pueda ser pintado
			DWLArbolEx_Nodo *NPosicion = ArbolEx_NodoInicioPagina();
			// Busco la posicion en la pagina visible del nodo para poder obtener la Y donde empieza este.
			int i = 0;
			if (NPosicion != NULL) {
				for (i = 0; i < _BarraScrollEx_PaginaV; i++) {
					if (NPosicion == nNodo) break;
					if (NPosicion->_Expandido == true && NPosicion->_Hijos.size() > 0)	{ // Si esta expandido
						NPosicion = NPosicion->_Hijos[0];
					}
					else {
						while (NPosicion->_Siguiente == NULL) {
							if (NPosicion->_Padre == NULL)	{ // Se ha llegado al final
								NPosicion = NULL;
								break;
							}
							NPosicion = NPosicion->_Padre;
						}
						if (NPosicion == NULL) {
							i++;
							break;
						}
						NPosicion = NPosicion->_Siguiente;
					}
				}
			}
			Rectangulo->top = i * _ArbolEx_AltoLinea;
			Rectangulo->bottom = Rectangulo->top + _ArbolEx_AltoLinea;
		}

		//! Función para empezar la edicion de un nodo.
		/*! Esta función inicia la edicion de un nodo.
				\fn			HWND ArbolEx_EmpezarLabelEdit(HWND hWndControl, DWLArbolEx_Nodo *nNodo, const bool Numerico);
				\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
				\param[in]	nNodo		: Nodo que se va a editar.
				\param[in]	Numerico	: True para que la edicion solo acepte digitos, false para que acepte todos los caracteres.
				\return		Devuelve el HWND del EditBox creado para editar el nodo.
				\sa			ArbolEx_TerminarLabelEdit(), ArbolEx_CancelarLabelEdit()
		*/
		HWND DWLArbolEx_Nucleo::ArbolEx_EmpezarLabelEdit(HWND hWndControl, DWLArbolEx_Nodo *nNodo, const bool Numerico) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::EmpezarLabelEdit\n"));
			#endif
			ArbolEx_CancelarLabelEdit(hWndControl);
			if (nNodo == NULL) return NULL;
			_ArbolEx_eNodo = nNodo;
			RECT Dim;
			ArbolEx_DesSeleccionarTodo(true);
			_ArbolEx_Editando = true;
			ArbolEx_ObtenerRectaNodo(_ArbolEx_eNodo, &Dim);
			//ListView_GetSubItemRect(_hWnd, eItem, eSubItem, LVIR_LABEL, &Dim);
			long Estilos;
			if (Numerico == false) { Estilos = WS_BORDER | ES_AUTOHSCROLL | WS_CHILD; }
			else                   { Estilos = WS_BORDER | ES_AUTOHSCROLL | WS_CHILD | ES_NUMBER; }
			Dim.top --;
			Dim.right += 30;
			_ArbolEx_hWndEdit = CreateWindow(TEXT("EDIT"), nNodo->_Texto(), Estilos, Dim.left - 5, Dim.top , Dim.right - (Dim.left) + 10, Dim.bottom - (Dim.top), hWndControl, (HMENU)555, GetModuleHandle(NULL), NULL);
			SetWindowLongPtr(_ArbolEx_hWndEdit, GWL_USERDATA, PtrToLong(this));
			_ArbolEx_GestorMensajesOriginalEdit = (WNDPROC)LongToPtr(SetWindowLongPtr(_ArbolEx_hWndEdit, GWL_WNDPROC, PtrToLong(_ArbolEx_GestorMensajesEdit)));
//			_GestorMensajesOriginalEdit = (WNDPROC)SetWindowLongPtr(_hWndEdit, GWL_WNDPROC, (long)_ArbolEx_GestorMensajesEdit);
			SendMessage(_ArbolEx_hWndEdit, EM_SETSEL, 0, nNodo->_Texto.Tam());
			if (nNodo->_Fuentes != NULL)	SendMessage(_ArbolEx_hWndEdit, WM_SETFONT, (WPARAM)nNodo->_Fuentes->Normal(), 0);
			else							SendMessage(_ArbolEx_hWndEdit, WM_SETFONT, (WPARAM)ArbolEx_Estilos.Fuentes.Normal(), 0);
			SendMessage(_ArbolEx_hWndEdit, EM_SETLIMITTEXT, 0, 0);
			if (nNodo->_Colores != NULL)	_ArbolEx_BrochaFondoEdit = CreateSolidBrush(nNodo->_Colores->FondoNormal());
			else							_ArbolEx_BrochaFondoEdit = CreateSolidBrush(ArbolEx_Estilos.Colores.Fondo());
			ShowWindow (_ArbolEx_hWndEdit, SW_SHOWNORMAL);
			UpdateWindow(_ArbolEx_hWndEdit);
			SetFocus(_ArbolEx_hWndEdit);
			PostMessage(GetParent(hWndControl), DWL_ARBOLEX_LABELEDIT_INICIO, (WPARAM)nNodo, (LPARAM)GetWindowLongPtr(hWndControl, GWL_ID));

			return _ArbolEx_hWndEdit;
		}

		//! Función para terminar la edicion de un nodo guardando los datos.
		/*! Esta función termina la edicion de un nodo guardando los datos.
				\fn			HWND ArbolEx_TerminarLabelEdit(HWND hWndControl);
				\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
				\return		No devuelve nada.
				\sa			ArbolEx_EmpezarLabelEdit(), ArbolEx_CancelarLabelEdit()
		*/
		void DWLArbolEx_Nucleo::ArbolEx_TerminarLabelEdit(HWND hWndControl) {
		#if defined DWL_ARBOLEX_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::TerminarLabelEdit\n"));
		#endif
			if (_ArbolEx_hWndEdit != NULL && _ArbolEx_Editando == true) {
				TCHAR Txt[512];
				GetDlgItemText(GetParent(_ArbolEx_hWndEdit), GetWindowLongPtr(_ArbolEx_hWndEdit, GWL_ID), Txt, 512);
				_ArbolEx_Editando = false;
				DWLArbolEx_TerminarLabelEdit Edicion(_ArbolEx_eNodo, Txt);
				SendMessage(GetParent(hWndControl), DWL_ARBOLEX_LABELEDIT_FIN, reinterpret_cast<WPARAM>(&Edicion), static_cast<LPARAM>(GetWindowLongPtr(hWndControl, GWL_ID)));
				if (Edicion.Cancelar == false) _ArbolEx_eNodo->Texto(Edicion.NuevoTexto());
				RECT Dim;
				ArbolEx_ObtenerRectaNodo(_ArbolEx_eNodo, &Dim);
				InvalidateRect(hWndControl, &Dim, false);
				DestroyWindow(_ArbolEx_hWndEdit);
				DeleteObject(_ArbolEx_BrochaFondoEdit);
				_ArbolEx_NodoMarcado = _ArbolEx_eNodo;
				_ArbolEx_eNodo = NULL;
			}
		}

		//! Función para cancelar la edicion de un nodo sin guardar los datos.
		/*! Esta función cancela la edicion de un nodo sin guardar los datos.
				\fn			HWND ArbolEx_CancelarLabelEdit(HWND hWndControl);
				\param[in]	hWndControl : HWND del control que contiene el ArbolEx.
				\return		No devuelve nada.
				\sa			ArbolEx_EmpezarLabelEdit(), ArbolEx_TerminarLabelEdit()
		*/
		void DWLArbolEx_Nucleo::ArbolEx_CancelarLabelEdit(HWND hWndControl) {
		#if defined DWL_ARBOLEX_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::CancelarLabelEdit\n"));
		#endif
			if (_ArbolEx_hWndEdit != NULL && _ArbolEx_Editando == true) {
				_ArbolEx_Editando = false;
				SendMessage(GetParent(hWndControl), DWL_ARBOLEX_LABELEDIT_CANCELADO, (WPARAM)_ArbolEx_NodoMarcado, (LPARAM)GetWindowLongPtr(hWndControl, GWL_ID));
				DestroyWindow(_ArbolEx_hWndEdit);
				DeleteObject(_ArbolEx_BrochaFondoEdit);
				_ArbolEx_eNodo->Seleccionado(true);
				_ArbolEx_NodoMarcado = _ArbolEx_eNodo;
				_ArbolEx_eNodo = NULL;
			}
		}

		//! Función que hace visible en la pantalla el nodo especificado.
		/*! Esta funcion hace visible en la pantalla el nodo especificado.
				\fn			void ArbolEx_HacerVisible(HWND hWndControl, DWLArbolEx_Nodo *vNodo, const bool nRepintar = false);
				\param[in]	hWndControl	: HWND del control que contiene el ArbolEx.
				\param[in]	nNodo		: Nodo que queremos hacer visible.
				\param[in]	nRepintar	: Variable en la que especificamos si hay que repintar.
				\return		No devuelve nada.
		*/
		void DWLArbolEx_Nucleo::ArbolEx_HacerVisible(HWND hWndControl, DWLArbolEx_Nodo *vNodo, const bool nRepintar) {
		#if defined DWL_ARBOLEX_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::HacerVisible\n"));
		#endif
			if (vNodo == NULL) return;
			DWLArbolEx_Nodo *TmpPadre = vNodo;
			int NPosScroll = 0;
			// Posicionamos el nodo al padre de vNodo para expandirlo si es necesario
			while (TmpPadre->_Padre != NULL) {
				if (TmpPadre->_Padre->_Expandido == false) 	ArbolEx_Expandir(hWndControl, TmpPadre->_Padre, true, true);
				TmpPadre = TmpPadre->_Padre;
			}

			//_PosMovimientoScroll = 0;
			DWLArbolEx_Nodo *NPosicion = _ArbolEx_Nodos[0];
			while (NPosicion != vNodo) {
				// Si el nodo tiene hijos obtengo el primer hijo y sigo trabajando con el
				if (NPosicion->_Expandido == true && NPosicion->_Hijos.size() > 0)	{
					NPosicion = NPosicion->_Hijos[0];
					NPosScroll ++;
				}
				// Si no tiene hijos obtengo el nodo inmediatamente inferior, y si no su padre
				else {
					while (NPosicion->_Siguiente == NULL) {
						NPosicion = NPosicion->_Padre;
					}
					NPosScroll ++;
					NPosicion = NPosicion->_Siguiente;
				}
			}
			// Si la posicion del scroll sobrepasa el maximo permitido lo reajusto
			if (NPosScroll > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) NPosScroll = _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV;
			// Si la posicion del scroll sobrepasa el minimo permitido lo reajusto
			if (NPosScroll < 0) NPosScroll = 0;
			// Si la posicion ha cambiado y no sigue dentro de la misma pagina
			if (NPosScroll <= _BarraScrollEx_ValorV || NPosScroll >= _BarraScrollEx_ValorV + _BarraScrollEx_PaginaV) BarraScrollEx_ValorV(NPosScroll);

//			_ArbolEx_UYMouse = Alto() + _ArbolEx_AltoLinea;
			BarraScrollEx_CalcularScrollV();
			BarraScrollEx_CalcularScrollH();
			if (nRepintar == true) Repintar(true);
		}

		//! Función que retorna la fila donde esta posicionado el nodo en la pantalla.
		/*! Esta función retorna la fila donde esta posicionado el nodo en la pantalla.
				\fn			int ArbolEx_PosicionVisibleNodo(DWLArbolEx_Nodo *vNodo);
				\param[in]	vNodo : Nodo del que se quere averiguar su posicion visible.
				\return		Devuelve su posicion visible dentro del ArbolEx.
				\remarks	Esta funcion siempre retornara una posicion positiva, y puede retornar posiciones que quedan fuera del area visible del control.
		*/
		int DWLArbolEx_Nucleo::ArbolEx_PosicionVisibleNodo(DWLArbolEx_Nodo *vNodo) {
		    #if defined DWL_ARBOLEX_DEBUG
			    DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::PosicionVisibleNodo\n"));
		    #endif
			int NPosScroll = 0;
			DWLArbolEx_Nodo *NPosicion = _ArbolEx_Nodos[0];
			while (NPosicion != vNodo) {
				if (NPosicion->_Expandido == true && NPosicion->_Hijos.size() > 0)	{
					NPosicion = NPosicion->_Hijos[0];
					NPosScroll ++;
				}
				else {
					while (NPosicion->_Siguiente == NULL) {
						if (NPosicion->_Padre == NULL)	{ // Se ha llegado al final
							return _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV;
						}
						NPosicion = NPosicion->_Padre;
					}
					NPosScroll ++;
					NPosicion = NPosicion->_Siguiente;
				}
			}
			return NPosScroll;
		}

	    //! WindowProcedure que usara el Editbox en la Función ArbolEx_EmpezarLabelEdit().
	    /*! WindowProcedure que usara el Editbox en la Función ArbolEx_EmpezarLabelEdit().
			    \fn			static LRESULT CALLBACK _ArbolEx_GestorMensajesEdit(HWND dhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			    \param[in]	dhWnd	: HWND del EditBox.
			    \param[in]	uMsg	: Mensaje.
			    \param[in]	wParam	: Parametro1.
			    \param[in]	lParam	: Parametro2.
			    \return		Devuelve un valor acorde al mensaje especificado.
			    \remarks	Funcion de uso interno para ArbolEx_EmpezarLabelEdit().
	    */
		LRESULT CALLBACK DWLArbolEx_Nucleo::_ArbolEx_GestorMensajesEdit(HWND dhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			DWLArbolEx_Nucleo *This = reinterpret_cast<DWLArbolEx_Nucleo *>(LongToPtr(GetWindowLongPtr(dhWnd, GWL_USERDATA)));
			NMHDR T;
			T.hwndFrom = dhWnd;
			T.idFrom = GetWindowLongPtr(dhWnd, GWL_ID);
			switch (uMsg) {
				case WM_LBUTTONUP :
					T.code = NM_CLICK;
					PostMessage(GetParent(dhWnd), WM_NOTIFY, 0, PtrToLong(&T));
					break;
				case WM_RBUTTONUP :
					T.code = NM_RCLICK;
					PostMessage(GetParent(dhWnd), WM_NOTIFY, 0, PtrToLong(&T));
					break;
				case WM_LBUTTONDBLCLK :
					T.code = NM_DBLCLK;
					PostMessage(GetParent(dhWnd), WM_NOTIFY, 0, PtrToLong(&T));
					break;
				case WM_CHAR :
					PostMessage(GetParent(dhWnd), DWL_ARBOLEX_TECLADO_SOLTADO, wParam, 0);
					if (wParam == 13) PostMessage(GetParent(dhWnd), DWL_ARBOLEX_TECLADO_INTRO, 0, 0);
					break;

			}
			return CallWindowProc(This->_ArbolEx_GestorMensajesOriginalEdit, dhWnd, uMsg, wParam, lParam);
		};



    };
};
