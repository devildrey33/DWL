#include "DWLListaEx_Nucleo.h"
#include "..\DWLListaIconos.h"
#include "..\DWLGraficos.h"
//#include "DWL.h"
 
#define DWL_VALOR_ALPHA    110

namespace DWL {
	namespace ControlesEx {

		//! Constructor por defecto.
		/*! Constructor por defecto.
				\fn			DWLListaEx_Nucleo(void);
				\return		No devuelve nada.
		*/
		DWLListaEx_Nucleo::DWLListaEx_Nucleo(void) :
            _ListaEx_Columnas(),
            _ListaEx_Items(),
            _ListaEx_Presionado(false),
//            _ListaEx_VentanaActivada(TRUE),
            _ListaEx_ItemPresionado(NULL),
            _ListaEx_PosUltimoClick(-1),
            _ListaEx_UltimoBoton(-1),
            _ListaEx_SubItemPresionado(-1),
            _ListaEx_ItemResaltado(NULL),
            _ListaEx_UItemResaltado(NULL),
            _ListaEx_SubItemResaltado(-1),
            _ListaEx_ItemMarcado(NULL),
            _ListaEx_ItemShifteado(NULL),
    //		_ListaEx_Teclado(),
            _ListaEx_FondoDC(NULL),
            _ListaEx_Bmp(NULL),
            _ListaEx_Viejo(NULL),
            _ListaEx_VFuente(NULL),
            _ListaEx_UltimoClick(0),
            _ListaEx_AltoLinea(17),
            _ListaEx_FocoRaton(false),
            _ListaEx_TT_UltimoItem(NULL),
            _ListaEx_GestorMensajesOriginalEdit(NULL),
            _ListaEx_BrochaFondoEdit(NULL),
            _ListaEx_eItem(NULL),
            _ListaEx_eSubItem(-1),
            _ListaEx_Editando(false),
            _ListaEx_hWndEdit(NULL),
            _ListaEx_UltimoIntX(-1),
            _ListaEx_UltimoIntY(-1),
            _ListaEx_ID(0) {
/*
            _ListaEx_FondoDC = NULL;
			_BarraScrollEx_PosActualV = 0;
			_ListaEx_AltoLinea = 17;
			_ListaEx_Editando = false;
			_ListaEx_DesactivarBlend = false;
			_ListaEx_VentanaActivada = true;
			_ListaEx_UltimoBoton = -1;
			_ListaEx_MultiSeleccion = true;
			_ListaEx_PintarIconos = true;

			_ListaEx_ItemResaltado = NULL;
			_ListaEx_ItemMarcado = NULL;
			_ListaEx_UItemResaltado = NULL;
			_ListaEx_ItemShifteado = NULL;
			_ListaEx_ItemPresionado = NULL;

			_ListaEx_TT_Mostrar = false;
			_ListaEx_TT_TiempoMS = 0;
			_ListaEx_TT_UltimoItem = NULL;
			_ListaEx_MostrarEncabezadosColumnas = false;
			_ListaEx_UltimoIntX = 0;
			_ListaEx_UltimoIntY = 0;
			_ListaEx_PintarBorde = false;
			_ListaEx_FocoRaton = false;*/

			for (unsigned short i = 0; i != 255; i++) _ListaEx_Teclado[i] = FALSE;
//			ListaEx_Estilos.Fuentes.Enlazar(DWL::SO::DWLEstilos::Fuentes);
		}

	    //! Destructor.
	    /*! Destructor.
			    \fn			~DWLListaEx_Nucleo(void);
			    \return		No devuelve nada.
	    */
		DWLListaEx_Nucleo::~DWLListaEx_Nucleo(void) {
			unsigned int i = 0;
			for (i = 0; i < _ListaEx_Items.size(); i++) delete _ListaEx_Items[i];
			_ListaEx_Items.resize(0);
			for (i = 0; i < _ListaEx_Columnas.size(); i++) delete _ListaEx_Columnas[i];
			_ListaEx_Columnas.resize(0);
		}

		//! Función para agregar un item (INTERNA).
		/*! Esta función es de uso interno para la clase DWLListaEx de forma que pueda pasar los parametros opcionales a esta.
				\fn			DWLListaEx_Item *ListaEx_AgregarItem(DWLListaEx_Item *nItem, const int nIcono, const int Posicion, const TCHAR *Txt, va_list Marker);
				\param[in]	nItem		: Item heredado, en caso de ser un DWLListaEx_Item puedes especificar NULL.
				\param[in]	nIcono		: Icono para el item.
				\param[in]	nPosicion	: Posicion en la que se agregara el item. Puede ser (DWL_LISTAEX_FIN, DWL_LISTAEX_INICIO, y DWL_LISTAEX_ORDENADO)
				\param[in]	nTexto		: Texto para el item.
				\param[in]	Marker		: Parametro que contiene una lista de parametros opcionales.
				\return		Devuelve un puntero a la clase DWLListaEx_Item que acabamos de crear / añadir.
				\remarks	Se deben añadir tantos textos en los parametros opcionales como columnas -1 tenga la lista.
		*/
		DWLListaEx_Item *DWLListaEx_Nucleo::ListaEx_AgregarItem(DWLListaEx_Item *nItem, const int Iko, const int Posicion, const TCHAR *Txt, va_list Marker) {
			size_t	i;
			if (nItem == NULL) nItem = new DWLListaEx_Item(this);
			else               nItem->_ListaEx = this;

			DWLListaEx_DatosSubItem *DtSI = NULL;
			nItem->_Seleccionado = false;
			nItem->_Icono = Iko;
			nItem->_Siguiente = NULL;
			nItem->_Anterior = NULL;

			DtSI = new DWLListaEx_DatosSubItem(Txt);
			nItem->_SubItems.push_back(DtSI);
			for (unsigned int n = 1; n < _ListaEx_Columnas.size(); n++) {
				DtSI = new DWLListaEx_DatosSubItem(static_cast<const TCHAR *>(va_arg(Marker, const TCHAR *)));
				nItem->_SubItems.push_back(DtSI);
			}

			// Insertar el item al final
			if (Posicion == DWL_LISTAEX_FIN) {
/*				if (_ListaEx_Items.size() > 0) {
					nItem->_Anterior = _ListaEx_Items[_ListaEx_Items.size() -1];
					_ListaEx_Items[_ListaEx_Items.size() -1]->_Siguiente = nItem;
				}*/
				_ListaEx_Items.push_back(nItem);
			}

			// Insertar el item ordenado por orden alfabetico mirando la primera columna
			else if (Posicion == DWL_LISTAEX_ORDENADO) {
				if (_ListaEx_Items.size() != 0) {
					for (i = 0; i < _ListaEx_Items.size(); i++) {
						if (DWLStrCmpi(Txt, _ListaEx_Items[i]->Texto(0)) < 0)
                            break;
					}
                    if (i < _ListaEx_Items.size()) {
                        _ListaEx_Items.insert(_ListaEx_Items.begin() + i, nItem);
                        /*nItem->_Siguiente = _ListaEx_Items[i + 1];
                        nItem->_Siguiente->_Anterior = nItem;
                        if (i > 0) {
                            nItem->_Anterior = _ListaEx_Items[i - 1];
                            nItem->_Anterior->_Siguiente = nItem;
                        }
						else {
							nItem->_Anterior = NULL;
						}*/
                    }
                    else {
                        _ListaEx_Items.push_back(nItem);
                    }
				}
				else {
					_ListaEx_Items.push_back(nItem);
				}
			}
			// Insertar el item en una posición especifica (tambien válido para DWL_LISTAEX_PRINCIPIO)
			else {
                if (static_cast<UINT>(Posicion) < _ListaEx_Items.size()) {
				    _ListaEx_Items.insert(_ListaEx_Items.begin() + Posicion, nItem);
/*                    nItem->_Siguiente = _ListaEx_Items[Posicion + 1];
                    nItem->_Siguiente->_Anterior = nItem;
                    if (Posicion > 0) {
                        nItem->_Anterior = _ListaEx_Items[Posicion - 1];
                        nItem->_Anterior->_Siguiente = nItem;
                    }*/
                }
                else {
					_ListaEx_Items.push_back(nItem);
                }
			}

			return nItem;
		}


		//! Función para agregar un item.
		/*! Esta función se usa para agregar un item a la ListaEx.
				\fn			DWLListaEx_Item *ListaEx_AgregarItem(DWLListaEx_Item *nItem = NULL, const int nIcono = NULL, const int Posicion = DWL_LISTAEX_FIN, const TCHAR *Txt = NULL, ...);
				\param[in]	nItem		: Item heredado, en caso de ser un DWLListaEx_Item puedes especificar NULL.
				\param[in]	nIcono		: Icono para el item.
				\param[in]	nPosicion	: Posicion en la que se agregara el item. Puede ser (DWL_LISTAEX_FIN, DWL_LISTAEX_INICIO, y DWL_LISTAEX_ORDENADO)
				\param[in]	nTexto		: Texto para el item.
				\param[in]	...			: Parametros opcionales en los que debemos especificar los textos para los subitems.
				\return		Devuelve un puntero a la clase DWLListaEx_Item que acabamos de crear / añadir.
				\remarks	Se deben añadir tantos textos en los parametros opcionales como columnas -1 tenga la lista.
		*/
		DWLListaEx_Item *DWLListaEx_Nucleo::ListaEx_AgregarItem(DWLListaEx_Item *nItem, const int Iko, const int Posicion, const TCHAR *Txt, ...) {
			va_list Marker;
			va_start(Marker, Txt);
			DWLListaEx_Item *ItemNuevo = ListaEx_AgregarItem(nItem, Iko, Posicion, Txt, Marker);
			va_end(Marker);
			return ItemNuevo;

		}

		//! Función que pinta la listaex en el DC y espacio especificados.
		/*! Esta funcion pinta la ListaEx en las coordenadas y DC especificados.
				\fn			void ListaEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true, const bool PintarConMascara = false);;
				\param[in]	hDC					: DC en el que se va a pintar la ListaEx.
				\param[in]	Espacio				: Recta que delimita el espacio donde se puede pintar la ListaEx.
				\param[in]	TieneFoco			: Valor que determina si la lista tiene el foco del raton (por defecto se usara la funcion Foco()).
				\param[in]	PintarConMascara	: Valor que determina si se va a pintar el contorno del control con SRCAND antes de pintar el control.
				\return		No devuelve nada.
				\remarks	Esta función esta preparada para pintar la ListaEx en un DC que no sea el suyo, o que sea compartido.
							Por ello debemos especificar las coordenadas donde se va a pintar, si tiene el foco del raton o no, y por ultimo si debemos
							pintar la mascara.
							El parametro PintarMascara solo es necesario si vamos a pintar la ListaEx en un DC que no es el suyo y requerimos el pintado
							del borde del control. Entonces la función de pintado pintara el contorno de la ListaEx con SRCAND, y luego pintara el control
							con SRC_PAINT para que no se vean graficos desfasados en el borde.
				\sa			ListaEx_PintarItem_Filas_y_Columnas_Vertical(), ListaEx_PintarItem_Filas_Horizontal().
		*/
		void DWLListaEx_Nucleo::ListaEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco, const bool PintarConMascara) {
			RECT	RC		= { 0, 0, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top };
			HDC		Buffer	= CreateCompatibleDC(hDC);
			HBITMAP Bmp		= CreateCompatibleBitmap(hDC, RC.right, RC.bottom);
			HBITMAP Viejo	= static_cast<HBITMAP>(SelectObject(Buffer, Bmp));
			HRGN	Region	= NULL;

            if (ListaEx_Estilos.PintarBorde == true || PintarConMascara == true) Region = CreateRoundRectRgn(0, 0, RC.right +1, RC.bottom +1, 2, 2);
			// Pinto la mascara del control si se requiere
			if (PintarConMascara == true) {
				FillRect(Buffer, &RC, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));
				FillRgn(Buffer, Region, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
				BitBlt(hDC, Espacio->left, Espacio->top, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top, Buffer, 0, 0, SRCAND);
			}
			int      NLeft      = 0;
			int      An         = Espacio->right;
			int      Al         = Espacio->bottom;
			if (BarraScrollEx_VisibleV() == TRUE)	An -= 17;
			if (BarraScrollEx_VisibleH() == TRUE)	Al -= 17;

			// Pinto el fondo
			HBRUSH	Brocha = CreateSolidBrush(ListaEx_Estilos.Colores.Fondo());
			FillRect(Buffer, &RC, Brocha);
			DeleteObject(Brocha);

			#if defined DWL_LISTAEX_DEBUG
				DWL::DWLDebug::ImprimirDebug(TEXT("DWLListaEx::Evento_Pintar(hDC = %d, Ancho = %d)\n"), hDC, An);
			#endif
			int EstadoActual = 0;
			int i;

			// DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL
			// Este modo pinta la lista de forma vertical, con columnas
			if (ListaEx_Estilos.ModoVisionado == DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL) {
				ListaEx_PintarColumnas(Buffer, Espacio);
				for (i = _BarraScrollEx_ValorV; i < _BarraScrollEx_ValorV + _BarraScrollEx_PaginaV + 1; i++) {
					if (i >= static_cast<int>(_ListaEx_Items.size())) break;
					ListaEx_PintarItem_Filas_y_Columnas_Vertical(Buffer, Espacio, _ListaEx_Items[i]);
				}
				// Pinto el resto del fondo (si no se ha pintado todo)
				if (i < _BarraScrollEx_ValorV + _BarraScrollEx_PaginaV  + 1 || _BarraScrollEx_PaginaV == 0) {
					if (ListaEx_Estilos.Transparencias == true) {
						BLENDFUNCTION BF;
						BF.AlphaFormat = 0;
						BF.BlendOp = 0;
						BF.BlendFlags = 0;
						BF.SourceConstantAlpha = DWL_VALOR_ALPHA;
						AlphaBlend(Buffer, 0, (i * _ListaEx_AltoLinea), An, Al  - (i * _ListaEx_AltoLinea), _ListaEx_FondoDC, 0, i * _ListaEx_AltoLinea, An, Al  - (i * _ListaEx_AltoLinea), BF);
					}
				}
			}

			// DWL_LISTAEX_FILAS_HORIZONTAL
			// Este modo pinta la lista de forma horizontal, y omite las columnas
			if (ListaEx_Estilos.ModoVisionado == DWL_LISTAEX_FILAS_HORIZONTAL) {
				HDC         TmpDC2          = GetDC(NULL);
				HDC			TercerBuffer2	= CreateCompatibleDC(TmpDC2);
				HBITMAP		TBmp2			= CreateCompatibleBitmap(TmpDC2, An, Al);
				HBITMAP		TViejo2			= static_cast<HBITMAP>(SelectObject(TercerBuffer2, TBmp2));
				HBRUSH      BF2				= CreateSolidBrush(ListaEx_Estilos.Colores.Fondo());
				RECT		TB2				= { 0, 0, An, Al };
				ReleaseDC(NULL, TmpDC2);
				FillRect(TercerBuffer2, &TB2, BF2);
				DeleteObject(BF2);

				if (ListaEx_Estilos.Transparencias == true) {
					BLENDFUNCTION BF;
					BF.AlphaFormat = 0;
					BF.BlendOp = 0;
					BF.BlendFlags = 0;
					BF.SourceConstantAlpha = DWL_VALOR_ALPHA;
					AlphaBlend(TercerBuffer2, 0, 0, An, Al, _ListaEx_FondoDC, 0, 0, An, Al, BF);
				}

				int PosX = 0;
				int PosY = 0;
				for (int i2 = _BarraScrollEx_ValorH * _BarraScrollEx_PaginaV; i2 < (_BarraScrollEx_ValorH * _BarraScrollEx_PaginaV) + (((An / ListaEx_Estilos.AnchoMaximoItem) + 1) * _BarraScrollEx_PaginaV); i2++) {
					if (i2 >= static_cast<int>(_ListaEx_Items.size())) break;
					if (PosY == _BarraScrollEx_PaginaV) {
						PosY = 0;
						PosX ++;
					}
					ListaEx_PintarItem_Filas_Horizontal(TercerBuffer2, Espacio, _ListaEx_Items[i2], PosX, PosY);
					PosY ++;
				}

				BitBlt(Buffer, 0, 0, An, Al, TercerBuffer2, 0, 0, SRCCOPY);
				SelectObject(TercerBuffer2, TViejo2);
				DeleteObject(TBmp2);
				DeleteDC(TercerBuffer2);
			}

			BarraScrollEx_PintarV(Buffer);
			BarraScrollEx_PintarH(Buffer);

            // Pinto el borde
			bool TF = TieneFoco;
			if (_BarraScrollEx_Activado == false)   TF = false;
            if (ListaEx_Estilos.PintarBorde == true) ListaEx_Evento_Pintar_Borde(Buffer, Region, TF);
    		if (Region != NULL) DeleteObject(Region);

			if (PintarConMascara == false)	BitBlt(hDC, Espacio->left, Espacio->top, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top, Buffer, 0, 0, SRCCOPY);
			else							BitBlt(hDC, Espacio->left, Espacio->top, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top, Buffer, 0, 0, SRCPAINT);

			// Elimino objetos gdi de la memoria
			SelectObject(Buffer, Viejo);
			DeleteObject(Bmp);
			DeleteDC(Buffer);

		}

		//! Función para eliminar un item y sus subitems.
		/*! Esta funcion elimina el item especificado.
				\fn			void ListaEx_EliminarItem(HWND hWndControl, DWLListaEx_Item *nItem, const bool nRepintar = false);
				\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
				\param[in]	nItem		: Clase DWLListaEx_Item que se va a eliminar.
				\param[in]	nRepintar	: Parametro en el que especificamos si la ListaEx debe ser repintada.
				\return		No devuelve nada.
				\remarks	Cuando eliminamos un item se borra toda su memoria, incluso si ese item es heredado lo eliminamos por completo. Asegurate de tener un destructor que elimine los datos de tus items heredados.
		*/
		void DWLListaEx_Nucleo::ListaEx_EliminarItem(HWND hWndControl, DWLListaEx_Item *eItem, const bool nRepintar) {
			ListaEx_CancelarLabelEdit(hWndControl);
			unsigned int i = 0;
			for (i = 0; i < _ListaEx_Items.size(); i++) {
				if (_ListaEx_Items[i] == eItem) {
					ListaEx_EliminarItem(hWndControl, i, nRepintar);
					break;
				}
			}
		}

	    //! Función para eliminar un item y sus subitems.
	    /*! Esta funcion elimina el item especificado.
			    \fn			void ListaEx_EliminarItem(HWND hWndControl, const unsigned int nPos, const bool nRepintar = false);
			    \param[in]	hWndControl	: HWND del control que contiene la ListaEx.
			    \param[in]	nPos		: Posicion del item que se va a eliminar.
			    \param[in]	nRepintar	: Parametro en el que especificamos si la ListaEx debe ser repintada.
			    \return		No devuelve nada.
			    \remarks	Cuando eliminamos un item se borra toda su memoria, incluso si ese item es heredado lo eliminamos por completo. Asegurate de tener un destructor que elimine los datos de tus items heredados.
	    */
		void DWLListaEx_Nucleo::ListaEx_EliminarItem(HWND hWndControl, const unsigned int Pos, const bool nRepintar) {
			ListaEx_CancelarLabelEdit(hWndControl);
			if (_ListaEx_Items[Pos]->_Anterior != NULL) _ListaEx_Items[Pos]->_Anterior->_Siguiente = _ListaEx_Items[Pos]->_Siguiente;
			if (_ListaEx_Items[Pos]->_Siguiente != NULL) _ListaEx_Items[Pos]->_Siguiente->_Anterior = _ListaEx_Items[Pos]->_Anterior;
			delete _ListaEx_Items[Pos];
			_ListaEx_Items.erase(_ListaEx_Items.begin() + Pos);
			_BarraScrollEx_MaximoV = static_cast<int>(_ListaEx_Items.size());
			_ListaEx_UItemResaltado = NULL;
			_ListaEx_ItemResaltado = NULL;
			if ((_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) > 0) {
				if (_BarraScrollEx_ValorV > _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
				_ListaEx_ItemMarcado = NULL;
				_ListaEx_ItemShifteado = NULL;
			}
			else {
				BarraScrollEx_ValorV(0);
				_ListaEx_ItemMarcado = NULL;
				_ListaEx_ItemShifteado = NULL;
			}
			if (nRepintar == true) {
				ListaEx_FinAgregarItems(hWndControl);
				Repintar(true);
			}
		}


		//! Función para eliminar los items seleccionados.
		/*! Esta función elimina todos los items seleccionados de la ListaEx.
				\fn			UINT ListaEx_EliminarItemsSeleccionados(HWND hWndControl, const bool nRepintar = true);
				\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
				\param[in]	nRepintar	: Parametro en el que especificamos si la ListaEx debe ser repintada.
				\return		Devuelve el total de items eliminados.
				\remarks	Cuando eliminamos un item se borra toda su memoria, incluso si ese item es heredado lo eliminamos por completo. Asegurate de tener un destructor que elimine los datos de tus items heredados.
		*/
		UINT DWLListaEx_Nucleo::ListaEx_EliminarItemsSeleccionados(HWND hWndControl, const bool nRepintar) {
			ListaEx_CancelarLabelEdit(hWndControl);
            size_t TotalEliminados = 0;
			for (size_t i = _ListaEx_Items.size(); i > 0; i--) {
				if (_ListaEx_Items[i - 1]->_Seleccionado == true) {
					if (_ListaEx_Items[i -1]->_Anterior != NULL) _ListaEx_Items[i -1]->_Anterior->_Siguiente = _ListaEx_Items[i -1]->_Siguiente;
					if (_ListaEx_Items[i -1]->_Siguiente != NULL) _ListaEx_Items[i -1]->_Siguiente->_Anterior = _ListaEx_Items[i -1]->_Anterior;
//                    DWLDebug::ImprimirDebug(TEXT("Pos %d, Item %d, Item->Anterior %d, Item->Siguiente %d\n"), i, _ListaEx_Items[i -1], _ListaEx_Items[i -1]->_Anterior, _ListaEx_Items[i -1]->_Siguiente);
					delete _ListaEx_Items[i -1];
                    _ListaEx_Items[i - 1] = NULL;
					_ListaEx_Items.erase(_ListaEx_Items.begin() + (i -1));
                    TotalEliminados ++;
				}
			}
			_ListaEx_ItemResaltado = NULL;
			_ListaEx_UItemResaltado = NULL;
			_BarraScrollEx_MaximoV = static_cast<long>(_ListaEx_Items.size());
			if ((_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) > 0) {
				if (_BarraScrollEx_ValorV > _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
				_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;
				_ListaEx_ItemMarcado = NULL;
				_ListaEx_ItemShifteado = NULL;
			}
			else {
				BarraScrollEx_ValorV(0);
				_BarraScrollEx_PosActualV = 0;
				_ListaEx_ItemMarcado = NULL;
				_ListaEx_ItemShifteado = NULL;
			}
			ListaEx_FinAgregarItems(hWndControl);
			if (nRepintar == true) {
				Repintar(true);
			}
            return TotalEliminados;
		}


		//! Función para eliminar todos los items.
		/*! Esta función elimina todos los items de la ListaEx.
				\fn			void ListaEx_EliminarTodosLosItems(HWND hWndControl, const bool nRepintar = true);
				\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
				\param[in]	nRepintar	: Parametro en el que especificamos si la ListaEx debe ser repintada.
				\return		No devuelve nada.
				\remarks	Cuando eliminamos un item se borra toda su memoria, incluso si ese item es heredado lo eliminamos por completo. Asegurate de tener un destructor que elimine los datos de tus items heredados.
		*/
		void DWLListaEx_Nucleo::ListaEx_EliminarTodosLosItems(HWND hWndControl, const bool nRepintar) {
			ListaEx_CancelarLabelEdit(hWndControl);
			for (unsigned int i = 0; i < _ListaEx_Items.size(); i++) delete _ListaEx_Items[i];
			_ListaEx_Items.resize(0);
			_BarraScrollEx_PosActualV	= 0;
			_BarraScrollEx_PosActualH	= 0;
			_BarraScrollEx_ValorV				= 0;
			_BarraScrollEx_ValorH				= 0;
			_BarraScrollEx_MaximoV			= 0;
			_BarraScrollEx_MaximoH			= 0;
			_ListaEx_ItemResaltado		= NULL;
			_ListaEx_ItemMarcado		= NULL;
			_ListaEx_UItemResaltado		= NULL;
			_ListaEx_ItemShifteado		= NULL;
			_ListaEx_ItemPresionado		= NULL;
			ListaEx_DesSeleccionarTodo(false);
			ListaEx_FinAgregarItems(hWndControl);
			if (nRepintar == true) {
				Repintar(true);
			}
		}

		//! Función que agrega una columna a la ListaEx.
		/*! Esta función agrega una columna a la ListaEx.
				\fn			void ListaEx_AgregarColumna(const int nAncho = DWL_LISTAEX_ANCHO_AUTOMATICO, const int nAlineacion = DWL_LISTAEX_TEXTO_IZQUIERDA, const TCHAR *NombreColumna = NULL);
				\param[in]	nAncho			: Ancho en pixeles para la columna (puede ser DWL_LISTAEX_ANCHO_AUTOMATICO).
				\param[in]	nAlineacion		: Alineacion del texto de la columna (puede ser DWL_LISTAEX_TEXTO_IZQUIERDA, DWL_LISTAEX_TEXTO_CENTRADO, DWL_LISTAEX_TEXTO_DERECHA).
				\param[in]	NombreColumna	: Nombre para la columna (NULL por defecto).
				\return		No devuelve nada.
				\remarks	Si vas a usar la lista en modo DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL debes crear como minimo una columna, en caso de usar el modo DWL_LISTAEX_FILAS_HORIZONTAL las columnas no se tienen en cuenta.
		*/
		void DWLListaEx_Nucleo::ListaEx_AgregarColumna(const int nAncho, const int nAlineacion, const TCHAR *NombreColumna) {
			DWLListaEx_Columna *Col = new DWLListaEx_Columna(this);
			Col->_Ancho			= nAncho;
			Col->_Alineacion	= nAlineacion;
			Col->_Nombre		= NombreColumna;
			_ListaEx_Columnas.push_back(Col);
		}

		//! Función para eliminar la columna especificada.
		/*! Esta función elimina la columna especificada.
				\fn			void ListaEx_EliminarColumna(HWND hWndControl, const int Pos);
				\param[in]	hWndControl : HWND del control que contiene la ListaEx.
				\param[in]	nPos		: Posicion de la columna a eliminar.
				\return		No devuelve nada.
				\remarks	Cuando eliminamos una columna, NO SE ELIMINAN los datos de los items referentes a esa posicion de la columna.
		*/
		void DWLListaEx_Nucleo::ListaEx_EliminarColumna(HWND hWndControl, const int Pos) {
			ListaEx_CancelarLabelEdit(hWndControl);
			_ListaEx_Columnas.erase(_ListaEx_Columnas.begin() + Pos);
			if (ListaEx_Estilos.PintarIconos == true)   _BarraScrollEx_MaximoH = 18;
			else										_BarraScrollEx_MaximoH = 0;
			for (unsigned int i = 0; i < _ListaEx_Columnas.size(); i++) _BarraScrollEx_MaximoH += _ListaEx_Columnas[i]->Ancho();
		}

		//! Función para eliminar todas las columnas.
		/*! Esta funcion elimina todas las columnas de la ListaEx.
				\fn			void ListaEx_EliminarTodasLasColumnas(HWND hWndControl);
				\param[in]	hWndControl : HWND del control que contiene la ListaEx.
				\return		No devuelve nada.
				\remarks	Cuando eliminamos todas las columnas, NO SE ELIMINAN los datos de los items para las posiciones de las columnas.
		*/
		void DWLListaEx_Nucleo::ListaEx_EliminarTodasLasColumnas(HWND hWndControl) {
			ListaEx_CancelarLabelEdit(hWndControl);
			for (unsigned int i = 0; i < _ListaEx_Columnas.size(); i++) delete _ListaEx_Columnas[i];
			_ListaEx_Columnas.resize(0);
			if (ListaEx_Estilos.PintarIconos == true)   _BarraScrollEx_MaximoH = 18;
			else										_BarraScrollEx_MaximoH = 0;
			_BarraScrollEx_PosActualV = 0;
			BarraScrollEx_ValorV(0);
			_BarraScrollEx_MaximoV = 0;
			_ListaEx_UItemResaltado = NULL;
			_ListaEx_ItemResaltado = NULL;
			ListaEx_DesSeleccionarTodo(false);
			ListaEx_FinAgregarItems(hWndControl);
		}

		//! Función virtual que pinta el borde de la ListaEx.
		/*! Esta función virtual pinta el borde de la ListaEx.
				\fn			virtual void ListaEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco);
				\param[in]	hDC			: hDC donde se va a pintar el borde de la ListaEx.
				\param[in]	Region		: Region donde se pintara borde de la ListaEx.
				\param[in]	TieneFoco	: Valor en el que determinamos si pintamos el borde con foco o sin foco.
				\return		No devuelve nada.
				\remarks	Si _ListaEx_PintarBorde es false, esta función no se usara.
				\sa			ListaEx_Pintar()
		*/
		void DWLListaEx_Nucleo::ListaEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco) {
			HBRUSH Brocha;
			if (TieneFoco == true)	Brocha = CreateSolidBrush(ListaEx_Estilos.Colores.BordeFocoRaton());
			else					Brocha = CreateSolidBrush(ListaEx_Estilos.Colores.Borde());
			FrameRgn(hDC, Region, Brocha, 1, 1);
			DeleteObject(Brocha);
		}

		//! Función que retorna el item que esta debajo de las coordenadas especificadas.
		/*! Esta función retorna el item o la parte del nodo que esta debajo de las coordenadas especificadas.
				\fn			DWLListaEx_Item *ListaEx_HitTest(HWND hWndControl, const int cX, const int cY, const DWL_Enum_ListaEx_HitTest Tipo = HitTest_Texto_Icono);
				\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
				\param[in]	cX			: Coordenada X.
				\param[in]	cY			: Coordenada Y.
				\param[in]	nTipo		: Tipo de busqueda.
				\return		No devuelve nada.
				\remarks	Hay varios tipos de busqueda : [HitTest_Texto] Solo el texto, [HitTest_Icono] Solo el icono, [HitTest_Texto_Icono] Texto y icono.
		*/
		DWLListaEx_Item *DWLListaEx_Nucleo::ListaEx_HitTest(HWND hWndControl, const int cX, const int cY, const DWL_Enum_ListaEx_HitTest Tipo) {
			RECT RC;
			GetClientRect(hWndControl, &RC);
			if (ListaEx_Estilos.ModoVisionado == DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL) {
				int IntItemResaltado = (cY / _ListaEx_AltoLinea) + _BarraScrollEx_PosActualV;
				if (ListaEx_Estilos.MostrarEncabezadosColumnas == true) IntItemResaltado --;
				if (cX >  RC.right - 17 &&  BarraScrollEx_VisibleV() == TRUE)	return NULL; // Esta en la parte del scrollbar
				if (IntItemResaltado > _BarraScrollEx_MaximoV -1)				return NULL; // Esta en una posicion que no hay items porque se ha superado el maximo
				switch (Tipo) {
					case DWL_Enum_ListaEx_HitTest_Texto_Icono :
						return _ListaEx_Items[IntItemResaltado];
					case DWL_Enum_ListaEx_HitTest_Texto :
						if (cX < 18) return NULL;
						return _ListaEx_Items[IntItemResaltado];
					case DWL_Enum_ListaEx_HitTest_Icono :
						if (cX > 18) return NULL;
						return _ListaEx_Items[IntItemResaltado];
				}
			}

			if (ListaEx_Estilos.ModoVisionado == DWL_LISTAEX_FILAS_HORIZONTAL) {
				int IntY = (cY / _ListaEx_AltoLinea);
				int IntX = _BarraScrollEx_PosActualH + (cX / ListaEx_Estilos.AnchoMaximoItem);
				int ItemFinal = (IntX * _BarraScrollEx_PaginaV) + IntY;
				int AnchoIconos = 0;
				if (ListaEx_Estilos.PintarIconos == true) AnchoIconos = 18;
				if (ItemFinal >= static_cast<int>(_ListaEx_Items.size()))	return NULL;
				if (IntY >= _BarraScrollEx_PaginaV)								return NULL;
				RECT RectaItem = { IntX * ListaEx_Estilos.AnchoMaximoItem, IntY * _ListaEx_AltoLinea, (IntX * ListaEx_Estilos.AnchoMaximoItem) + _ListaEx_Items[ItemFinal]->_Ancho + AnchoIconos, (IntY * _ListaEx_AltoLinea) + _ListaEx_AltoLinea };
				POINT Pt = { cX, cY };
				switch (Tipo) {
					case DWL_Enum_ListaEx_HitTest_Texto_Icono :
						// No se modifica la recta
						break;
					case DWL_Enum_ListaEx_HitTest_Texto :
						// sumamos el ancho del icono al left
						RectaItem.left += 17;
						break;
					case DWL_Enum_ListaEx_HitTest_Icono :
						// dejamos solo 18 pixeles de ancho
						RectaItem.right = RectaItem.left + 18;
						break;
				}
				if (PtInRect(&RectaItem, Pt) == TRUE)	return _ListaEx_Items[ItemFinal];
				else									return NULL;
			}
			return NULL;
		}

		//! Función para pintar un item de la lista en modo DWL_LISTAEX_FILAS_HORIZONTAL.
		/*! Esta funcion se usa para pintar un item de la lista en modo DWL_LISTAEX_FILAS_HORIZONTAL.
				\fn			void ListaEx_PintarItem_Filas_Horizontal(HDC hDC, RECT *EspacioControl, DWLListaEx_Item *pItem, const int PosX, const int PosY);
				\param[in]	hDC				: HDC donde se pintara la ListaEx.
				\param[in]	EspacioControl	: Espacio de todo el control de la ListaEx.
				\param[in]	pItem			: Puntero a la clase DWLListaEx_Item que se va a pintar.
				\param[in]	PosX			: Posicion X del item.
				\param[in]	PosY			: Posicion Y del item.
				\return		No devuelve nada.
				\remarks	Función de uso interno para ListaEx_Pintar().
		*/
		void DWLListaEx_Nucleo::ListaEx_PintarItem_Filas_Horizontal(HDC hDC, RECT *EspacioControl, DWLListaEx_Item *pItem, const int PosX, const int PosY) {
			DWLListaEx_ColoresItem						   *ColoresTmp		= NULL;
			DWLListaEx_Fuentes				 	           *FuentesTmp		= NULL;
			int												EstadoActual	= DWL_LISTAEX_ESTADO_INDEFINIDO;
			if (pItem->_SubItems[0]->_Colores != NULL)		ColoresTmp		= pItem->_SubItems[0]->_Colores;
			else											ColoresTmp		= &ListaEx_Estilos.Colores.ColoresItem;
			if (pItem->_SubItems[0]->_Fuentes != NULL)		FuentesTmp		= pItem->_SubItems[0]->_Fuentes;
			else											FuentesTmp		= &ListaEx_Estilos.Fuentes;
			HDC												TmpDC			= GetDC(NULL);
			HDC												Buffer			= CreateCompatibleDC(TmpDC);
			HBITMAP											TBmp			= CreateCompatibleBitmap(TmpDC, pItem->_Ancho + 20, _ListaEx_AltoLinea);
			HBITMAP											TViejo			= static_cast<HBITMAP>(SelectObject(Buffer, TBmp));
			HBRUSH											Brocha			= NULL;
			HFONT											VFont			= NULL;
			SetBkMode(Buffer, TRANSPARENT);
			ReleaseDC(NULL, TmpDC);


			// Eleccion de la brocha para el fondo, y del estado actual del item
			if (pItem == _ListaEx_ItemResaltado && pItem == _ListaEx_ItemPresionado) {
				EstadoActual = DWL_LISTAEX_ESTADO_PRESIONADO;
				Brocha = CreateSolidBrush(ColoresTmp->FondoPresionado());
				SetTextColor(Buffer, ColoresTmp->TextoPresionado());
				VFont = static_cast<HFONT>(SelectObject(Buffer, FuentesTmp->SubRayada()));
			}
			else if (pItem == _ListaEx_ItemResaltado && pItem != _ListaEx_ItemPresionado)  {
				if (pItem->_Seleccionado == false) {
					Brocha = CreateSolidBrush(ColoresTmp->FondoResaltado());
					EstadoActual = DWL_LISTAEX_ESTADO_RESALTADO;
					SetTextColor(Buffer, ColoresTmp->TextoResaltado());
					VFont = static_cast<HFONT>(SelectObject(Buffer, FuentesTmp->SubRayada()));
				}
				else {
					Brocha = CreateSolidBrush(ColoresTmp->FondoSeleccionadoResaltado());
					EstadoActual = DWL_LISTAEX_ESTADO_SELECCIONADO_RESALTADO;
					SetTextColor(Buffer, ColoresTmp->TextoSeleccionadoResaltado());
					VFont = static_cast<HFONT>(SelectObject(Buffer, FuentesTmp->SubRayada()));
				}
			}
			else {
				if (pItem->_Seleccionado == false) {
					Brocha = CreateSolidBrush(ColoresTmp->FondoNormal());
					EstadoActual = DWL_LISTAEX_ESTADO_NORMAL;
					SetTextColor(Buffer, ColoresTmp->TextoNormal());
					VFont = static_cast<HFONT>(SelectObject(Buffer, FuentesTmp->Normal()));
				}
				else {
					Brocha = CreateSolidBrush(ColoresTmp->FondoSeleccionado());
					EstadoActual = DWL_LISTAEX_ESTADO_SELECCIONADO;
					SetTextColor(Buffer, ColoresTmp->TextoSeleccionado());
					VFont = static_cast<HFONT>(SelectObject(Buffer, FuentesTmp->Normal()));
				}
			}


			RECT FondoItem = { 0, 0, pItem->_Ancho + 20, _ListaEx_AltoLinea };
			FillRect(Buffer, &FondoItem, Brocha);

			if (ListaEx_Estilos.Transparencias == true) {
				BLENDFUNCTION BF;
				BF.AlphaFormat = 0;
				BF.BlendOp = 0;
				BF.BlendFlags = 0;
				BF.SourceConstantAlpha = DWL_VALOR_ALPHA;
				int CorreccionAncho = 0;
				if ((PosX * ListaEx_Estilos.AnchoMaximoItem) + (pItem->_Ancho + 20) > EspacioControl->right)	CorreccionAncho = EspacioControl->right - (PosX * ListaEx_Estilos.AnchoMaximoItem);
				else																					CorreccionAncho = (pItem->_Ancho + 20);
				BOOL A = AlphaBlend(Buffer, 0, 0, pItem->_Ancho + 20, _ListaEx_AltoLinea, _ListaEx_FondoDC, PosX * ListaEx_Estilos.AnchoMaximoItem, PosY * _ListaEx_AltoLinea, CorreccionAncho, _ListaEx_AltoLinea, BF);
//				SOLO_DEBUG(_ASSERT(A));
			}


			FondoItem.left = 19;
			DrawText(Buffer, pItem->Texto(0), pItem->LongitudTexto(0), &FondoItem, DT_NOPREFIX);
			DeleteObject(Brocha);
			FondoItem.left = 0;


			if (_ListaEx_ItemMarcado == pItem) {
				HBRUSH Brocha2;
				Brocha2 = CreateSolidBrush(ListaEx_Estilos.Colores.BordeSeleccion());
				FrameRect(Buffer, &FondoItem, Brocha2);
				DeleteObject(Brocha2);
			}
			if (ListaEx_Estilos.PintarIconos == true) {
				FondoItem.right = 20;
				FondoItem.left = 1;
				ListaEx_Evento_Pintar_Icono(Buffer, pItem, &FondoItem);
			}

			BitBlt(hDC, PosX * ListaEx_Estilos.AnchoMaximoItem, PosY * _ListaEx_AltoLinea, pItem->_Ancho + 20, _ListaEx_AltoLinea, Buffer, 0, 0, SRCCOPY);

			SelectObject(Buffer, VFont);
			SelectObject(Buffer, TViejo);
			DeleteObject(TBmp);
			DeleteDC(Buffer);
		}


		//! Función virtual que pinta el fondo de la ListaEx con AlphaBlend.
		/*! Esta función virtual pinta el fondo de la ListaEx con AlphaBlend.
				\fn			virtual void ListaEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio);
				\param[in]	hDC		: hDC donde se va a pintar la ListaEx.
				\param[in]	Espacio	: Espacio donde se pintara.
				\return		No devuelve nada.
				\remarks	Si _ListaEx_DesactivarBlend es false, esta función no se usara.
		*/
		void DWLListaEx_Nucleo::ListaEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio) {
			HBRUSH Brocha = CreateSolidBrush(ListaEx_Estilos.Colores.Fondo());
			FillRect(hDC, Espacio, Brocha);
			DeleteObject(Brocha);
		}


		//! Función virtual que pinta el encabezado de una columna de la ListaEx.
		/*! Esta función virtual pinta el encabezado de una columna de la ListaEx.
				\fn			virtual void ListaEx_Evento_Pintar_Columna(HDC hDC, RECT *Espacio, DWLListaEx_Columna *pColumna);
				\param[in]	hDC			: hDC donde se va a pintar la ListaEx.
				\param[in]	Espacio		: Espacio donde se pintara.
				\param[in]	pColumna	: Puntero a la clase DWLListaEx_Columna que se va a pintar.
				\return		No devuelve nada.
				\remarks	Si _ListaEx_MostrarEncabezadosColumnas es false, esta función no se usara.
		*/
		void DWLListaEx_Nucleo::ListaEx_Evento_Pintar_Columna(HDC hDC, RECT *Espacio, DWLListaEx_Columna *pColumna) {
			HFONT VFuente = NULL;
			DWLListaEx_ColoresColumna	*Col;
			DWLListaEx_Fuentes			*ColF;
			if (pColumna->_Colores != NULL) Col = pColumna->_Colores;
			else							Col = &ListaEx_Estilos.Colores.ColoresColumna;
			if (pColumna->_Fuentes != NULL) ColF = pColumna->_Fuentes;
			else							ColF = &ListaEx_Estilos.Fuentes;
			COLORREF ColorBorde;
			switch (pColumna->_Estado) {
				default :
				case DWL_LISTAEX_ESTADO_NORMAL :
					DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, Col->Columna_DegradadoSuperior(), Col->Columna_DegradadoInferior(), true);
					SetTextColor(hDC, Col->Columna_TextoNormal());
					VFuente = static_cast<HFONT>(SelectObject(hDC, ColF->Normal()));
					ColorBorde = ListaEx_Estilos.Colores.Borde();
					break;
				case DWL_LISTAEX_ESTADO_RESALTADO :
					DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, Col->Columna_DegradadoResaltado(), Col->Columna_DegradadoInferior(), true);
					SetTextColor(hDC, Col->Columna_TextoResaltado());
					VFuente = static_cast<HFONT>(SelectObject(hDC, ColF->SubRayada()));
					ColorBorde = ListaEx_Estilos.Colores.BordeFocoRaton();
					break;
				case DWL_LISTAEX_ESTADO_PRESIONADO :
					DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, Col->Columna_DegradadoInferior(), Col->Columna_DegradadoSuperior(), true);
					SetTextColor(hDC, Col->Columna_TextoPresionado());
					VFuente = static_cast<HFONT>(SelectObject(hDC, ColF->SubRayada()));
					ColorBorde = ListaEx_Estilos.Colores.BordeFocoRaton();
					break;
			}
			DrawText(hDC, pColumna->_Nombre(), static_cast<int>(pColumna->_Nombre.Tam()), Espacio, DT_CENTER | DT_NOPREFIX);
			_BarraScrollEx_EnmarcarRecta(hDC, Espacio, ColorBorde);
			SelectObject(hDC, VFuente);
		}


		//! Función que se usa para pintar los encabezados de las columnas.
		/*! Esta función se usa para pintar los encabezados de las columnas.
				\fn			void ListaEx_PintarColumnas(HDC hDC, RECT *EspacioControl);
				\param[in]	hDC				: HDC donde se va a pintar los encabezados de las columnas.
				\param[in]  EspacioControl	: Espacio de todo el control ListaEx.
				\return		No devuelve nada.
		*/
		void DWLListaEx_Nucleo::ListaEx_PintarColumnas(HDC hDC, RECT *EspacioControl) {
			if (ListaEx_Estilos.MostrarEncabezadosColumnas == false) return;
			int											AnchoBuffer		= _BarraScrollEx_MaximoH;
			if (EspacioControl->right > AnchoBuffer)	AnchoBuffer		= EspacioControl->right;
			HDC									       _Buffer2			= CreateCompatibleDC(hDC);
			HBITMAP							           _Bmp2			= CreateCompatibleBitmap(hDC, AnchoBuffer, _ListaEx_AltoLinea);
			HBITMAP							           _Viejo2			= static_cast<HBITMAP>(SelectObject(_Buffer2, _Bmp2));
			RECT										Espacio = { 0, 0, AnchoBuffer, _ListaEx_AltoLinea };
			HBRUSH										ColorFondo = CreateSolidBrush(ListaEx_Estilos.Colores.Fondo());
			FillRect(_Buffer2, &Espacio, ColorFondo);
			DeleteObject(ColorFondo);
			Espacio.top ++;
			Espacio.bottom --;
			int Cuenta = 0;
			if (ListaEx_Estilos.PintarIconos == true) Cuenta = 18;
			for (size_t i = 0; i < _ListaEx_Columnas.size(); i++)  {
				if (i == 0) Espacio.left = 1;
				else		Espacio.left = Cuenta;
				if (ListaEx_Estilos.PintarBorde == true) {
					Espacio.left ++;
					Espacio.top = 2;
				}
				Cuenta += _ListaEx_Columnas[i]->Ancho();
				Espacio.right = Cuenta - 1;
				ListaEx_Evento_Pintar_Columna(_Buffer2, &Espacio, _ListaEx_Columnas[i]);
			}
			int An2;
			if (BarraScrollEx_VisibleV() == TRUE)	An2 = EspacioControl->right - 17;
			else									An2 = EspacioControl->right;
			BitBlt(hDC, 0, 0, An2, _ListaEx_AltoLinea, _Buffer2, _BarraScrollEx_ValorH, 0, SRCCOPY);
			SelectObject(_Buffer2, _Viejo2);
			DeleteObject(_Bmp2);
			DeleteDC(_Buffer2);
		}


		//! Función para pintar un item de la lista en modo DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL.
		/*! Esta funcion se usa para pintar un item de la lista en modo DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL.
				\fn			void ListaEx_PintarItem_Filas_y_Columnas_Vertical(HDC hDC, RECT *EspacioControl, DWLListaEx_Item *pItem);
				\param[in]	hDC				: HDC donde se pintara la ListaEx.
				\param[in]	EspacioControl	: Espacio de todo el control de la ListaEx.
				\param[in]	pItem			: Puntero a la clase DWLListaEx_Item que se va a pintar.
				\return		No devuelve nada.
				\remarks	Función de uso interno para ListaEx_Pintar().
		*/
		void DWLListaEx_Nucleo::ListaEx_PintarItem_Filas_y_Columnas_Vertical(HDC hDC, RECT *EspacioControl, DWLListaEx_Item *pItem) {
			int											AnchoBuffer		= _BarraScrollEx_MaximoH;
			if (EspacioControl->right > AnchoBuffer)	AnchoBuffer		= EspacioControl->right;
			int											NLeft			= 0;
			int											An2				= 0;
			int											Al				= EspacioControl->bottom;
			int											l				= 0;
			HDC								           _Buffer2			= CreateCompatibleDC(hDC);
			HBITMAP							           _Bmp2			= CreateCompatibleBitmap(hDC, AnchoBuffer, _ListaEx_AltoLinea);
			HBITMAP							           _Viejo2			= static_cast<HBITMAP>(SelectObject(_Buffer2, _Bmp2));
			int											EstadoActual	= DWL_LISTAEX_ESTADO_INDEFINIDO;
			HBRUSH										Brocha			= NULL;
			COLORREF									ColorFondo		= 0;
			DWLListaEx_ColoresItem					   *ColoresTmp		= NULL;
			DWLListaEx_Fuentes					       *FuentesTmp		= NULL;
			if (pItem->_SubItems[0]->_Colores != NULL)	ColoresTmp		= pItem->_SubItems[0]->_Colores;
			else										ColoresTmp		= &ListaEx_Estilos.Colores.ColoresItem;
			if (pItem->_SubItems[0]->_Fuentes != NULL)	FuentesTmp		= pItem->_SubItems[0]->_Fuentes;
			else										FuentesTmp		= &ListaEx_Estilos.Fuentes;
			HFONT									   _VFuente2		= static_cast<HFONT>(SelectObject(_Buffer2, FuentesTmp->Normal()));
			RECT										RectaItem;
			SetBkMode(_Buffer2, TRANSPARENT);

			if (BarraScrollEx_VisibleV() == TRUE)	An2 = EspacioControl->right - 18;
			else									An2 = EspacioControl->right;

			if (BarraScrollEx_VisibleH() == TRUE) Al -= 18;

//            if (ListaEx_Estilos.PintarBorde == true) An2 -= 3;

			#if defined DWL_LISTAEX_DEBUG
				DWL::DWLDebug::ImprimirDebug(TEXT("DWLListaEx::PintarItem(Item = %.08x, Ancho = %d)\n"), pItem, An2);
			#endif
			RectaItem.left = 0;
//			if (ListaEx_Estilos.PintarBorde == true)	RectaItem.right = An2 - 4;
//			else										RectaItem.right = An2;
			RectaItem.right = AnchoBuffer;
			RectaItem.top = 0;
			RectaItem.bottom = _ListaEx_AltoLinea + 1;
			// Eleccion de la brocha para el fondo, y del estado actual del item
			if (pItem == _ListaEx_ItemResaltado && pItem == _ListaEx_ItemPresionado) {
				EstadoActual = DWL_LISTAEX_ESTADO_PRESIONADO;
				Brocha = CreateSolidBrush(ColoresTmp->FondoPresionado());
			}

			else if (pItem == _ListaEx_ItemResaltado && pItem != _ListaEx_ItemPresionado && _BarraScrollEx_Activado == TRUE)  {
				if (pItem->_Seleccionado == false) {
					Brocha = CreateSolidBrush(ColoresTmp->FondoResaltado());
					EstadoActual = DWL_LISTAEX_ESTADO_RESALTADO;
				}
				else {
					Brocha = CreateSolidBrush(ColoresTmp->FondoSeleccionadoResaltado());
					EstadoActual = DWL_LISTAEX_ESTADO_SELECCIONADO_RESALTADO;
				}
			}
			else {
				if (pItem->_Seleccionado == false) {
					Brocha = CreateSolidBrush(ColoresTmp->FondoNormal());
					EstadoActual = DWL_LISTAEX_ESTADO_NORMAL;
				}
				else {
					Brocha = CreateSolidBrush(ColoresTmp->FondoSeleccionado());
					EstadoActual = DWL_LISTAEX_ESTADO_SELECCIONADO;
				}
			}
			// Pinto el fondo
			int PosicionItem = pItem->Posicion();
			if (ListaEx_Estilos.MostrarEncabezadosColumnas == true) PosicionItem ++;
			FillRect(_Buffer2, &RectaItem, Brocha);
			DeleteObject(Brocha);

			if (ListaEx_Estilos.Transparencias == true) {
				BLENDFUNCTION BF;
				BF.AlphaFormat = 0;
				BF.BlendOp = 0;
				BF.BlendFlags = 0;
				BF.SourceConstantAlpha = DWL_VALOR_ALPHA;
				BOOL A = AlphaBlend(_Buffer2, _BarraScrollEx_ValorH, 0, An2, _ListaEx_AltoLinea, _ListaEx_FondoDC, 0, (PosicionItem - _BarraScrollEx_ValorV) * _ListaEx_AltoLinea, An2, _ListaEx_AltoLinea, BF);
			}
			// Pinto los textos del item
			for (int z = 0; z < static_cast<int>(_ListaEx_Columnas.size()); z++) {
				if (ListaEx_Estilos.PintarIconos == true)	NLeft = 18; // 18 pixeles desde el inicio (asi reservamos espacio para el icono)
				else										NLeft = 2;  // 2 pixeles desde el inicio (sin reservar espacio para el icono)
				if (_ListaEx_Columnas.size() > 1) {
					for (l = 0; l < z; l++) NLeft += _ListaEx_Columnas[l]->_Ancho;
					RectaItem.right = NLeft + _ListaEx_Columnas[l]->_Ancho;
				}
				else if (_ListaEx_Columnas.size() == 1) {
					RectaItem.right = An2 - NLeft;
				}
				RectaItem.left = NLeft;
				ListaEx_Evento_Pintar_Item(_Buffer2, pItem, z, &RectaItem, EstadoActual);
			}
			// Si hay que pintar iconos
			if (ListaEx_Estilos.PintarIconos == true) {
				RectaItem.left = 0;
				RectaItem.right = 18;
				ListaEx_Evento_Pintar_Icono(_Buffer2, pItem, &RectaItem);
			}
			// Pinto la marca
			if (_ListaEx_ItemMarcado == pItem) {
				RectaItem.left = 0;
				RectaItem.right = An2;
				RectaItem.bottom = _ListaEx_AltoLinea;
				HBRUSH Brocha2 = CreateSolidBrush(ListaEx_Estilos.Colores.BordeSeleccion());

				FrameRect(_Buffer2, &RectaItem, Brocha2);
				DeleteObject(Brocha2);
			}
			// Calculo el arreglo del scroll
			int ArregloScroll = _ListaEx_AltoLinea;
			if (BarraScrollEx_VisibleH() == TRUE && ((PosicionItem - _BarraScrollEx_ValorV) +1) * static_cast<int>(_ListaEx_AltoLinea) > EspacioControl->bottom - 20) {
				if (ListaEx_Estilos.PintarBorde == true)	ArregloScroll = (EspacioControl->bottom - 23) - ((PosicionItem - _BarraScrollEx_ValorV) * _ListaEx_AltoLinea);
				else										ArregloScroll = (EspacioControl->bottom - 19) - ((PosicionItem - _BarraScrollEx_ValorV) * _ListaEx_AltoLinea);
			}
			else if (BarraScrollEx_VisibleH() == FALSE && ((PosicionItem - _BarraScrollEx_ValorV) +1) * static_cast<int>(_ListaEx_AltoLinea) > EspacioControl->bottom - 4 && ListaEx_Estilos.PintarBorde == true) {
				ArregloScroll = (EspacioControl->bottom - 4) - ((PosicionItem - _BarraScrollEx_ValorV) * static_cast<int>(_ListaEx_AltoLinea));
			}

			int Borde = 0;
			if (ListaEx_Estilos.PintarBorde == true) {
				Borde = 2;
			}
			BitBlt(hDC, Borde, ((PosicionItem - _BarraScrollEx_ValorV) * static_cast<int>(_ListaEx_AltoLinea)) + Borde, An2 - (Borde * 2), ArregloScroll, _Buffer2, _BarraScrollEx_ValorH, 0, SRCCOPY);
			SelectObject(_Buffer2, _VFuente2);
			SelectObject(_Buffer2, _Viejo2);
			DeleteObject(_Bmp2);
			DeleteDC(_Buffer2);
		}


		//! Función virtual que pinta el icono de un item de la ListaEx.
		/*! Esta función virtual ppinta el icono de un item de la ListaEx.
				\fn			virtual void ListaEx_Evento_Pintar_Icono(HDC hDC, DWLListaEx_Item *nItem, RECT *Espacio);
				\param[in]	hDC			: hDC donde se va a pintar la ListaEx.
				\param[in]	nItem		: Puntero a la clase DWLListaEx_Item que contiene el icono que se va a pintar.
				\param[in]	Espacio		: Espacio donde se pintara.
				\return		No devuelve nada.
				\remarks	Si _ListaEx_MostrarEncabezadosColumnas es false, esta función no se usara.
		*/
		void DWLListaEx_Nucleo::ListaEx_Evento_Pintar_Icono(HDC hDC, DWLListaEx_Item *nItem, RECT *Espacio) {
			if (_ListaEx_ItemPresionado == nItem)	DWL::SO::DWLListaIconos::PintarIcono(hDC, Espacio->left + 2, Espacio->top + 2, 16, 16, nItem->_Icono);
			else									DWL::SO::DWLListaIconos::PintarIcono(hDC, Espacio->left + 1, Espacio->top + 1, 16, 16, nItem->_Icono);
		}


		//! Función virtual que pinta el texto normal de un item de la ListaEx.
		/*! Esta función virtual ppinta el texto normal de un item de la ListaEx.
				\fn			virtual void ListaEx_Evento_Pintar_Item(HDC hDC, DWLListaEx_Item *nItem, const int nSubItem, RECT *Espacio, const int EstadoItem);
				\param[in]	hDC			: hDC donde se va a pintar la ListaEx.
				\param[in]	nItem		: Puntero a la clase DWLListaEx_Item que contiene el icono que se va a pintar.
				\param[in]	nSubItem	: Posicion del subitem del que se va a pintar el texto.
				\param[in]	Espacio		: Espacio donde se pintara.
				\param[in]	EstadoItem	: Estado del item, puede ser : DWL_LISTAEX_ESTADO_NORMAL, DWL_LISTAEX_ESTADO_RESALTADO, DWL_LISTAEX_ESTADO_PRESIONADO, DWL_LISTAEX_ESTADO_SELECCIONADO, DWL_LISTAEX_ESTADO_SELECCIONADO_RESALTADO.
				\return		No devuelve nada.
		*/
		void DWLListaEx_Nucleo::ListaEx_Evento_Pintar_Item(HDC hDC, DWLListaEx_Item *nItem, const int nSubItem, RECT *Espacio, const int EstadoItem) {
			DWLListaEx_ColoresItem			*Col;
			DWLListaEx_Fuentes           	*Fue;
			if (nItem->_SubItems[nSubItem]->_Colores == NULL) Col = &ListaEx_Estilos.Colores.ColoresItem;
			else											  Col = nItem->_SubItems[nSubItem]->_Colores;
			if (nItem->_SubItems[nSubItem]->_Fuentes == NULL) Fue = &ListaEx_Estilos.Fuentes;
			else											  Fue = nItem->_SubItems[nSubItem]->_Fuentes;

			// Correcion para que los textos alineados a la derecha no se peguen con otros que pueden estar alineados a la izquierda
			if (_ListaEx_Columnas[nSubItem]->Alineacion() == DWL_LISTAEX_TEXTO_DERECHA)  Espacio->right -= 2;

			switch (EstadoItem) {
				case DWL_LISTAEX_ESTADO_NORMAL :
					SelectObject(hDC, Fue->Normal());
					if (_BarraScrollEx_Activado == TRUE) SetTextColor(hDC, Col->TextoNormal());
					else								  SetTextColor(hDC, Col->TextoPresionado());
					Espacio->top +=2;
					DrawText(hDC, nItem->Texto(nSubItem), static_cast<int>(nItem->LongitudTexto(nSubItem)), Espacio, static_cast<UINT>(_ListaEx_Columnas[nSubItem]->Alineacion()) | DT_NOPREFIX);
					Espacio->top -=2;
					break;
				case DWL_LISTAEX_ESTADO_RESALTADO :
					if (_BarraScrollEx_Activado == TRUE) {
						SelectObject(hDC, Fue->SubRayada());
						SetTextColor(hDC, Col->TextoResaltado());
					}
					else {
						SelectObject(hDC, Fue->Normal());
						SetTextColor(hDC, Col->TextoPresionado());
					}
					Espacio->top +=2;
					DrawText(hDC, nItem->Texto(nSubItem), static_cast<int>(nItem->LongitudTexto(nSubItem)), Espacio, static_cast<UINT>(_ListaEx_Columnas[nSubItem]->Alineacion()) | DT_NOPREFIX);
					Espacio->top -=2;
					break;
				case DWL_LISTAEX_ESTADO_PRESIONADO :
					SelectObject(hDC, Fue->SubRayada());
					SetTextColor(hDC, Col->TextoPresionado());
					Espacio->left ++;	Espacio->top +=3;
					DrawText(hDC, nItem->Texto(nSubItem), static_cast<int>(nItem->LongitudTexto(nSubItem)), Espacio, static_cast<UINT>(_ListaEx_Columnas[nSubItem]->Alineacion()) | DT_NOPREFIX);
					Espacio->left --;	Espacio->top -=3;
					break;
				case DWL_LISTAEX_ESTADO_SELECCIONADO :
					SelectObject(hDC, Fue->Normal());
					if (_BarraScrollEx_Activado == TRUE) SetTextColor(hDC, Col->TextoSeleccionado());
					else								  SetTextColor(hDC, Col->TextoPresionado());
					Espacio->top +=2;
					DrawText(hDC, nItem->Texto(nSubItem), static_cast<int>(nItem->LongitudTexto(nSubItem)), Espacio, static_cast<UINT>(_ListaEx_Columnas[nSubItem]->Alineacion()) | DT_NOPREFIX);
					Espacio->top -=2;
					break;
				case DWL_LISTAEX_ESTADO_SELECCIONADO_RESALTADO :
					if (_BarraScrollEx_Activado == TRUE) {
						SelectObject(hDC, Fue->SubRayada());
						SetTextColor(hDC, Col->TextoSeleccionadoResaltado());
					}
					else {
						SelectObject(hDC, Fue->Normal());
						SetTextColor(hDC, Col->TextoPresionado());
					}
					Espacio->top +=2;
					DrawText(hDC, nItem->Texto(nSubItem), static_cast<int>(nItem->LongitudTexto(nSubItem)), Espacio, static_cast<UINT>(_ListaEx_Columnas[nSubItem]->Alineacion()) | DT_NOPREFIX);
					Espacio->top -=2;
					break;
			}

			// Restauro la correccion del texto hacia la derecha
			if (_ListaEx_Columnas[nSubItem]->Alineacion() == DWL_LISTAEX_TEXTO_DERECHA)  Espacio->right += 2;
		}


		//! Función que muestra en pantalla el item especificado.
		/*! Esta función muestra en pantalla el item especificado.
				\fn			void ListaEx_MostrarItem(DWLListaEx_Item *vItem);
				\param[in]	vItem	: Clase DWLListaEx_Item que queremos mostrar.
				\return		No devuelve nada.
		*/
		void DWLListaEx_Nucleo::ListaEx_MostrarItem(DWLListaEx_Item *vItem) {
			for (unsigned int i = 0; i < _ListaEx_Items.size(); i++) {
				if (_ListaEx_Items[i] == vItem) {
					ListaEx_MostrarItem(i);
					break;
				}
			}
		}

		//! Función que muestra en pantalla el item especificado.
		/*! Esta función muestra en pantalla el item especificado.
				\fn			void ListaEx_MostrarItem(const int nPos);
				\param[in]	nPos	: Posición del item que queremos mostrar.
				\return		No devuelve nada.
		*/
		void DWLListaEx_Nucleo::ListaEx_MostrarItem(const int nPos) {
			if (ListaEx_Estilos.ModoVisionado == DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL) {
				if (nPos < _BarraScrollEx_ValorV) { // por encima de la pagina
					BarraScrollEx_ValorV(nPos);
				}
				else if (nPos > (_BarraScrollEx_ValorV + _BarraScrollEx_PaginaV) -1) { // por debajo
					BarraScrollEx_ValorV(((nPos - _BarraScrollEx_PaginaV) +1));
					if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
				}
				_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;
			}

			if (ListaEx_Estilos.ModoVisionado == DWL_LISTAEX_FILAS_HORIZONTAL) {
				int ValorHFinal = nPos / _BarraScrollEx_PaginaV;
				if (_BarraScrollEx_ValorH + _BarraScrollEx_PaginaH < ValorHFinal) _BarraScrollEx_ValorH = ValorHFinal;
				if (_BarraScrollEx_ValorH > ValorHFinal)	_BarraScrollEx_ValorH = ValorHFinal;
				_BarraScrollEx_PosActualH = _BarraScrollEx_ValorH;
			}
			BarraScrollEx_CalcularScrollV(ListaEx_Estilos.PintarBorde);
			BarraScrollEx_CalcularScrollH(ListaEx_Estilos.PintarBorde);
			Repintar(true);
		}


		//! Función que elimina el estado de selección en todos los items.
		/*! Esta función elimina el estado de selección en todos los items.
				\fn			void ListaEx_DesSeleccionarTodo(const bool bRepintar = true);
				\param[in]	bRepintar	: Valor en el que especificamos si debemos repintar la ListaEx.
				\return		No devuelve nada.
		*/
		void DWLListaEx_Nucleo::ListaEx_DesSeleccionarTodo(const bool bRepintar) {
			for (unsigned int i = 0; i < _ListaEx_Items.size(); i++) {
				_ListaEx_Items[i]->_Seleccionado = false;
			}
			_ListaEx_ItemMarcado = NULL;
			if (bRepintar == true) Repintar(true);
		}



		//! Función que recalcula los tamaños de todos los textos de la ListaEx.
		/*! Esta función recaltula los tamaños de todos los textos de la ListaEx.
				\fn			void ListaEx_ActualizarTamTexto(void);
				\return		No devuelve nada.
		*/
		void DWLListaEx_Nucleo::ListaEx_ActualizarTamTexto(void) {
			SIZE Tam;
            _ListaEx_AltoLinea = 14;

			for (size_t i = 0; i < _ListaEx_Items.size(); i++) {
				for (size_t r = 0; r < _ListaEx_Columnas.size();) {
					if (_ListaEx_Items[i]->SubItem(r)->_Fuentes != NULL) SelectObject(_ListaEx_FondoDC, _ListaEx_Items[i]->SubItem(r)->_Fuentes->Normal());
					else                                                 SelectObject(_ListaEx_FondoDC, ListaEx_Estilos.Fuentes.Normal());

					GetTextExtentPoint(_ListaEx_FondoDC, _ListaEx_Items[i]->Texto(r), _ListaEx_Items[i]->LongitudTexto(r), &Tam);
					if (_ListaEx_AltoLinea < Tam.cy + 3) _ListaEx_AltoLinea = Tam.cy + 3;
				}
			}
		}

		//! Función que actualiza todos los datos de la ListaEx.
		/*! Esta función actualiza todos los datos de la ListaEx.
				\fn			void ListaEx_ActualizarTodo(HWND hWndControl, RECT *Espacio);
				\param[in]	hWndControl	  : HWND del control que contiene la ListaEx.
				\param[in]	Espacio		  : Recta que debe contener el espacio para la ListaEx.
				\return		No devuelve nada.
				\remarks	Esta función se usa para actualizar todos los estilos y nodos del ListaEx. Si necesitas actualizar el tamaño de los textos por haber cambiado la fuente, deberas usar tambien ListaEx_ActualizarTamTexto().
		*/
		void DWLListaEx_Nucleo::ListaEx_ActualizarTodo(HWND hWndControl, RECT *Espacio) {
			#if defined DWL_LISTAEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLListaEx::ActualizarTodo\n"));
			#endif
            // Miramos si el borde ha cambiado
            HRGN Region = CreateRectRgn(0,0,0,0);
            int RR = GetWindowRgn(hWndControl, Region);
            // - Si hay que pintar borde y la region no existe
            if (ListaEx_Estilos.PintarBorde == true && RR == NULLREGION) {
                HRGN Region2 = CreateRoundRectRgn(0, 0, (Espacio->right - Espacio->left) + 1, (Espacio->bottom - Espacio->top) + 1, 2, 2);
                SetWindowRgn(hWndControl, Region2, FALSE);
            }
            // - Si no hay que pintar el borde y la region existe
            if (ListaEx_Estilos.PintarBorde == false && RR != NULLREGION && RR != ERROR) {
                SetWindowRgn(hWndControl, NULL, FALSE);
            }
            DeleteObject(Region);

			// Actualizamos los datos de los items para que se muestren correctamente
			ListaEx_FinAgregarItems(hWndControl);

            // Miro que la barra de scroll no se salga de los limites
			if (_BarraScrollEx_MaximoV  > _BarraScrollEx_PaginaV) {
				if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
			}
			else {
				BarraScrollEx_ValorV(0);
			}
//			_ListaEx_UYMouse = !_ListaEx_AltoLinea;
			// Repinto el fondo en el DC que tenemos en memoria
            ListaEx_Evento_Pintar_Fondo(_ListaEx_FondoDC, Espacio);
		}

		//! Función que enlaza todos los items entre ellos y calcula los valores del scroll.
		/*!	Esta función es la encargada de enlazar todos los items entre ellos y calcular las posiciones para los scrolls.
				\fn			void ListaEx_FinAgregarItems(HWND hWndControl);
				\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
				\return		No devuelve nada.
				\remarks	Esta función debe ser llamada cuando terminemos de agregar el ultimo item a la lista.
		*/
		void DWLListaEx_Nucleo::ListaEx_FinAgregarItems(HWND hWndControl) {
			RECT R;
			GetClientRect(hWndControl, &R);
			int  Al = R.bottom;
			int  An = R.right;
			int  Borde = 0;
			size_t i = 0;
			if (ListaEx_Estilos.PintarBorde == true) Borde = 4;
			if (ListaEx_Estilos.ModoVisionado == DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL) {
				if (ListaEx_Estilos.PintarIconos == true)  _BarraScrollEx_MaximoH = 18; // Ancho del icono
				else								_BarraScrollEx_MaximoH = 2;
				for (unsigned int i = 0; i < _ListaEx_Columnas.size(); i++) _BarraScrollEx_MaximoH += _ListaEx_Columnas[i]->Ancho(); // Ancho total en pixeles
				_BarraScrollEx_MaximoV = static_cast<int>(_ListaEx_Items.size()); // numero total de items
				_BarraScrollEx_PaginaV = (static_cast<int>(static_cast<float>(Al - Borde) / static_cast<float>(_ListaEx_AltoLinea)));
				_BarraScrollEx_PaginaH = R.right - Borde;
				if (_BarraScrollEx_PaginaV > _BarraScrollEx_MaximoV) BarraScrollEx_ValorV(0);
				else {
					if (_BarraScrollEx_PosActualV > _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) _BarraScrollEx_PosActualV = _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV;
				}
				if (ListaEx_Estilos.MostrarEncabezadosColumnas == true) _BarraScrollEx_PaginaV -= 1;
				if (BarraScrollEx_VisibleH() == TRUE) _BarraScrollEx_PaginaV -= 1;
				if (BarraScrollEx_VisibleV() == TRUE) _BarraScrollEx_PaginaH -= 17;
			}
			// Modo DWL_LISTAEX_FILAS_HORIZONTAL
			// para este modo necesitamos calcular los anchos de cada item para establecer los calculos del scroll horizontal
			if (ListaEx_Estilos.ModoVisionado == DWL_LISTAEX_FILAS_HORIZONTAL) {
				HDC hDC = GetDC(hWndControl);
				HFONT Viejo = static_cast<HFONT>(SelectObject(hDC, ListaEx_Estilos.Fuentes.Normal()));
				bool OtraFuente = false;
				SIZE Tam;
				ListaEx_Estilos.AnchoMaximoItem = 0;
				// Calculo todos los anchos, y miro cual sera el mas grande
				for (i = 0; i < _ListaEx_Items.size(); i++) {
					if (OtraFuente == true) {
						SelectObject(hDC, ListaEx_Estilos.Fuentes.Normal());
						OtraFuente = false;
					}
					if (_ListaEx_Items[i]->_SubItems[0]->_Fuentes != NULL) { //
						SelectObject(hDC, _ListaEx_Items[i]->_SubItems[0]->_Fuentes->Normal());
						OtraFuente = true;
					}
					GetTextExtentPoint32(hDC, _ListaEx_Items[i]->Texto(0), _ListaEx_Items[i]->LongitudTexto(0), &Tam);
					if (ListaEx_Estilos.AnchoMaximoItem < Tam.cx) ListaEx_Estilos.AnchoMaximoItem = Tam.cx;
					_ListaEx_Items[i]->_Ancho = Tam.cx;
				}
				// Correcciones de tamaño finales
				if (ListaEx_Estilos.PintarIconos == true) ListaEx_Estilos.AnchoMaximoItem += 18; // Sumo el ancho del icono
				ListaEx_Estilos.AnchoMaximoItem += 20; // espacio delimitador entre columnas
				ReleaseDC(hWndControl, hDC);
				// Calculo los tamaños para el scroll
				if (_ListaEx_AltoLinea < Al) {
					_BarraScrollEx_PaginaV = (static_cast<int>(static_cast<float>(Al) / static_cast<float>(_ListaEx_AltoLinea)));
					_BarraScrollEx_PaginaH = An / ListaEx_Estilos.AnchoMaximoItem;
					if (_BarraScrollEx_PaginaH < (static_cast<int>(_ListaEx_Items.size()) / _BarraScrollEx_PaginaV))
						_BarraScrollEx_PaginaV --; // Habra scroll asi que quito un espacio a la pagina vertical
					if (_BarraScrollEx_PaginaV <= 0) _BarraScrollEx_PaginaV = 1;
					_BarraScrollEx_MaximoV = _BarraScrollEx_PaginaV; // numero total de items
					_BarraScrollEx_MaximoH = (_ListaEx_Items.size() / _BarraScrollEx_PaginaV) + 1;
				}
				else {
					_BarraScrollEx_MaximoV = 1;
					_BarraScrollEx_MaximoH = 1;
					_BarraScrollEx_PaginaV = 1;
					_BarraScrollEx_PaginaH = 1;
				}
				BarraScrollEx_ValorV(0);
				if (_BarraScrollEx_PaginaH > _BarraScrollEx_MaximoH) {
					BarraScrollEx_ValorH(0);
				}
				else {
					if (_BarraScrollEx_PosActualH > _BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH) _BarraScrollEx_PosActualH = _BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH;
				}
			}
			// Por último enlazamos todos los items entre ellos
			if (_ListaEx_Items.size() > 1) {
				_ListaEx_Items[0]->_Anterior = NULL;
				_ListaEx_Items[0]->_Siguiente = _ListaEx_Items[1];
				for (i = 1; i < _ListaEx_Items.size(); i++) {
					_ListaEx_Items[i]->_Anterior = _ListaEx_Items[i - 1];
					if (_ListaEx_Items.size() > i + 1)	_ListaEx_Items[i]->_Siguiente = _ListaEx_Items[i + 1];
					else								_ListaEx_Items[i]->_Siguiente = NULL;
				}
			}
			BarraScrollEx_PosicionarScrolls(hWndControl, &R, true, ListaEx_Estilos.PintarBorde);
		}



		//! Función que asigna la altura de un item en pixeles.
		/*! Esta función asigna la altura de un item en pixeles.
				\fn			void ListaEx_AltoLinea(HWND hWndControl, const unsigned int nAlto);
				\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
				\param[in]	nAlto		: Nueva altura en pixeles para los items.
				\return		No devuelve nada.
		*/
		void DWLListaEx_Nucleo::ListaEx_AltoLinea(HWND hWndControl, const unsigned int nAlto) {
			RECT RC;
			GetClientRect(hWndControl, &RC);
			int An = RC.right;
			if (BarraScrollEx_VisibleV() == TRUE) An -= 17;
			_ListaEx_AltoLinea = nAlto;
			BarraScrollEx_PosicionarScrolls(hWndControl, &RC, false, ListaEx_Estilos.PintarBorde);
			ListaEx_FinAgregarItems(hWndControl);
		}


		//! Función para empezar la edicion de un item.
		/*! Esta función inicia la edicion de un item.
				\fn			HWND ListaEx_EmpezarLabelEdit(HWND hWndControl, DWLListaEx_Item *eItem, const unsigned int eSubItem = 0, const bool Numerico);
				\param[in]	hWndControl : HWND del control que contiene la ListaEx.
				\param[in]	eItem		: Clase DWLListaEx_Item que se va a editar.
				\param[in]	eSubItem	: Posicion del subitem que se va a editar.
				\param[in]	Numerico	: True para que la edicion solo acepte digitos, false para que acepte todos los caracteres.
				\return		Devuelve el HWND del EditBox creado para editar el nodo.
				\sa			ListaEx_TerminarLabelEdit(), ListaEx_CancelarLabelEdit()
		*/
		HWND DWLListaEx_Nucleo::ListaEx_EmpezarLabelEdit(HWND hWndControl, DWLListaEx_Item *eItem, const unsigned int eSubItem, const bool Numerico) {
			ListaEx_CancelarLabelEdit(hWndControl);
			if (eItem == NULL || eSubItem > _ListaEx_Columnas.size()) {
				return NULL;
			}
			_ListaEx_eItem = eItem;
			_ListaEx_eSubItem = eSubItem;
			RECT Dim;
			ListaEx_DesSeleccionarTodo(true);
			_ListaEx_Editando = true;
			ListaEx_ObtenerRectaItem(eItem->Posicion(), eSubItem, &Dim);
			long Estilos;
			if (Numerico == false) { Estilos = static_cast<long>(_ListaEx_Columnas[eSubItem]->Alineacion()) | ES_AUTOHSCROLL | WS_CHILD; }
			else                   { Estilos = static_cast<long>(_ListaEx_Columnas[eSubItem]->Alineacion()) | ES_AUTOHSCROLL | WS_CHILD | ES_NUMBER; }
			_ListaEx_hWndEdit = CreateWindow(TEXT("EDIT"), _ListaEx_eItem->Texto(eSubItem), Estilos, Dim.left, Dim.top + 2, Dim.right - (Dim.left), Dim.bottom - (Dim.top), hWndControl, (HMENU)555, GetModuleHandle(NULL), NULL);
			SetWindowLongPtr(_ListaEx_hWndEdit, GWL_USERDATA, PtrToLong(this));
			_ListaEx_GestorMensajesOriginalEdit = (WNDPROC)LongToPtr(SetWindowLongPtr(_ListaEx_hWndEdit, GWL_WNDPROC, PtrToLong(_ListaEx_GestorMensajesEdit)));
			SendMessage(_ListaEx_hWndEdit, EM_SETLIMITTEXT, 0, 0);
			SendMessage(_ListaEx_hWndEdit, EM_SETSEL, 0, eItem->LongitudTexto(eSubItem));

			if (eItem->_SubItems[eSubItem]->_Fuentes != NULL)	SendMessage(_ListaEx_hWndEdit, WM_SETFONT, (WPARAM)eItem->_SubItems[eSubItem]->_Fuentes->Normal(), 0);
			else												SendMessage(_ListaEx_hWndEdit, WM_SETFONT, (WPARAM)ListaEx_Estilos.Fuentes.Normal(), 0);
			if (eItem->_SubItems[eSubItem]->_Colores != NULL)	_ListaEx_BrochaFondoEdit = CreateSolidBrush(eItem->_SubItems[eSubItem]->Colores()->FondoNormal());
			else												_ListaEx_BrochaFondoEdit = CreateSolidBrush(ListaEx_Estilos.Colores.ColoresItem.FondoNormal());
			ShowWindow (_ListaEx_hWndEdit, SW_SHOWNORMAL);
			UpdateWindow(_ListaEx_hWndEdit);
			SetFocus(_ListaEx_hWndEdit);
            DWLListaEx_ParametrosLabelEdit ParamsLE(_ListaEx_eItem, _ListaEx_eItem->Posicion(), _ListaEx_eSubItem,_ListaEx_eItem->Texto(eSubItem));
			SendMessage(GetParent(hWndControl), DWL_LISTAEX_LABELEDIT_INICIO, reinterpret_cast<WPARAM>(&ParamsLE), _ListaEx_ID);
            if (ParamsLE.Cancelar == false) _ListaEx_eItem->Texto(_ListaEx_eSubItem, ParamsLE.NuevoTexto());
            else                            ListaEx_CancelarLabelEdit(hWndControl);

			return _ListaEx_hWndEdit;
		}


		//! Función para terminar la edicion de un item guardando los datos.
		/*! Esta función termina la edicion de un item guardando los datos.
				\fn			HWND ListaEx_TerminarLabelEdit(HWND hWndControl);
				\param[in]	hWndControl : HWND del control que contiene la ListaEx.
				\return		No devuelve nada.
				\sa			ListaEx_EmpezarLabelEdit(), ListaEx_CancelarLabelEdit()
		*/
		void DWLListaEx_Nucleo::ListaEx_TerminarLabelEdit(HWND hWndControl) {
			if (_ListaEx_hWndEdit != NULL && _ListaEx_Editando == true) {
				TCHAR Txt[512];
				GetDlgItemText(GetParent(_ListaEx_hWndEdit), GetWindowLongPtr(_ListaEx_hWndEdit, GWL_ID), Txt, 512);
				_ListaEx_Editando = false;
				int Pos = _ListaEx_eItem->Posicion();
				DWLListaEx_ParametrosLabelEdit Edicion(_ListaEx_eItem, Pos, _ListaEx_eSubItem, Txt);
				SendMessage(GetParent(hWndControl), DWL_LISTAEX_LABELEDIT_FIN, reinterpret_cast<WPARAM>(&Edicion), _ListaEx_ID);
				if (Edicion.Cancelar == false) _ListaEx_eItem->Texto(_ListaEx_eSubItem, Edicion.NuevoTexto());
				RECT Dim;
				ListaEx_ObtenerRectaItem(Pos, _ListaEx_eSubItem, &Dim);
				InvalidateRect(hWndControl, &Dim, false);
				DestroyWindow(_ListaEx_hWndEdit);
				DeleteObject(_ListaEx_BrochaFondoEdit);
			}
		}

		//! Función para cancelar la edicion de un item sin guardar los datos.
		/*! Esta función cancela la edicion de un item sin guardar los datos.
				\fn			HWND ListaEx_CancelarLabelEdit(HWND hWndControl);
				\param[in]	hWndControl : HWND del control que contiene la ListaEx.
				\return		No devuelve nada.
				\sa			ListaEx_EmpezarLabelEdit(), ListaEx_TerminarLabelEdit()
		*/
		void DWLListaEx_Nucleo::ListaEx_CancelarLabelEdit(HWND hWndControl) {
			if (_ListaEx_hWndEdit != NULL && _ListaEx_Editando == true) {
				_ListaEx_Editando = false;
				_ListaEx_eItem->Seleccionado(true, false);
				SendMessage(GetParent(hWndControl), DWL_LISTAEX_LABELEDIT_CANCELADO, MAKEWPARAM(_ListaEx_eItem->Posicion(), _ListaEx_eSubItem), (LPARAM)GetWindowLongPtr(hWndControl, GWL_ID));
				DestroyWindow(_ListaEx_hWndEdit);
				DeleteObject(_ListaEx_BrochaFondoEdit);
				_ListaEx_hWndEdit = NULL;
				Repintar(true);
			}
		}

		//! Función que obtiene el espacio que necesita el subitem para ser pintado.
		/*! Esta funcion obtiene el espacio que necesita el subitem para ser pintado.
				\fn			RECT *ListaEx_ObtenerRectaItem(const int nItem, const int nSubItem, RECT *Ret);
				\param[in]	nItem		: Numero de Item del que queremos obtener el espacio.
				\param[in]	nSubItem	: Numero de SubItem del que queremos obtener el espacio.
				\param[out]	Ret			: Recta en la que se asignara el espacio necesario para el subitem.
				\return		Devuelve un puntero al parametro Ret.
		*/
		RECT *DWLListaEx_Nucleo::ListaEx_ObtenerRectaItem(const int nItem, const int nSubItem, RECT *Ret) {
			Ret->top = (nItem - _BarraScrollEx_ValorV) * _ListaEx_AltoLinea;
			Ret->bottom = (Ret->top + _ListaEx_AltoLinea);
			if (ListaEx_Estilos.PintarIconos == true)	Ret->left = 13;
			else										Ret->left = 0;
			int n;
			for (n = 0; n < nSubItem; n++) Ret->left += _ListaEx_Columnas[n]->_Ancho;
			Ret->right = Ret->left +  _ListaEx_Columnas[n]->_Ancho;
			return Ret;
		}

		//! Función que obtiene el espacio que necesita el subitem para ser pintado.
		/*! Esta funcion obtiene el espacio que necesita el subitem para ser pintado.
				\fn			RECT *ListaEx_ObtenerRectaItem(DWLListaEx_Item *nItem, const int nSubItem, RECT *Ret);
				\param[in]	nItem		: Clase DWLListaEx_Item de la que queremos obtener el espacio.
				\param[in]	nSubItem	: Numero de SubItem del que queremos obtener el espacio.
				\param[out]	Ret			: Recta en la que se asignara el espacio necesario para el subitem.
				\return		Devuelve un puntero al parametro Ret.
		*/
		RECT *DWLListaEx_Nucleo::ListaEx_ObtenerRectaItem(DWLListaEx_Item *nItem, const int nSubItem, RECT *Ret) {
			int Posicion = nItem->Posicion();
			Ret->top = (Posicion - _BarraScrollEx_ValorV) * _ListaEx_AltoLinea;
			Ret->bottom = (Ret->top + _ListaEx_AltoLinea);
			if (ListaEx_Estilos.PintarIconos == true)	Ret->left = 13;
			else						Ret->left = 0;
			int n;
			for (n = 0; n < nSubItem; n++) Ret->left += _ListaEx_Columnas[n]->_Ancho;
			Ret->right = Ret->left +  _ListaEx_Columnas[n]->_Ancho;
			return Ret;
		}


		//! Función que procesa las teclas soltadas en la ListaEx.
		/*! Esta función procesa las teclas presionadas en la ListaEx.
				\fn			void ListaEx_Teclado_TeclaSoltada(HWND hWndControl, const int Tecla, LPARAM lParam);
				\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
				\param[in]	Tecla		: Tecla que se ha soltado.
				\param[in]	Repeticion	: Repeticion de la tecla.
				\param[in]	Param		: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		No devuelve nada.
				\remarks    Esta función debe ser enlazada con el Evento_TeclaSoltada del control que vaya a contener la ListaEx.
				\sa			ListaEx_Teclado_TeclaSoltada()
		*/
		void DWLListaEx_Nucleo::ListaEx_Teclado_TeclaSoltada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params) {
			if (_BarraScrollEx_Activado == FALSE) return;
			_ListaEx_Teclado[Caracter] = false;
			#if defined DWL_LISTAEX_DEBUG
				DWL::DWLDebug::ImprimirDebug(TEXT("DWLListaEx_Nucleo::ListaEx_Teclado_TeclaSoltada %d\n"), VirtKey);
			#endif
			if (Caracter == VK_SHIFT) _ListaEx_ItemShifteado = NULL;
			PostMessage(GetParent(hWndControl), DWL_LISTAEX_TECLADO_SOLTADO, (WPARAM)Caracter, (LPARAM)GetWindowLongPtr(hWndControl, GWL_ID));
			if (Caracter == 13) PostMessage(GetParent(hWndControl), DWL_LISTAEX_TECLADO_INTRO, (WPARAM)Caracter, (LPARAM)GetWindowLongPtr(hWndControl, GWL_ID));
		}


		//! Función que procesa las teclas presionadas en la ListaEx.
		/*! Esta función procesa las teclas presionadas en la ListaEx.
				\fn			void ListaEx_Teclado_TeclaPresionada(HWND hWndControl, const int Tecla, LPARAM lParam);
				\param[in]	hWndControl	: HWND del control que contiene la ListaEx.
				\param[in]	Tecla		: Tecla que se ha presionado.
				\param[in]	Repeticion	: Repeticion de la tecla.
				\param[in]	Param		: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		No devuelve nada.
				\remarks    Esta función debe ser enlazada con el Evento_TeclaPresionada del control que vaya a contener la ListaEx.
				\sa			ListaEx_Teclado_TeclaPresionada()
		*/
		void DWLListaEx_Nucleo::ListaEx_Teclado_TeclaPresionada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params) {
			if (_BarraScrollEx_Activado == FALSE) return;
			if (_ListaEx_Items.size() == 0) return;
			_ListaEx_Teclado[Caracter] = true;
			int i = 0;
			int f = 0;
			// Asi eliminamos el tooltip al tocar una tecla, ademas de que si movemos con cursores o avpag repag ese nodo no es correcto.
			_ListaEx_ItemResaltado = NULL;

			bool Shift = false;
			if (_ListaEx_Teclado[VK_SHIFT] == true && ListaEx_Estilos.MultiSeleccion == true) Shift = true;
			if (_ListaEx_ItemMarcado == NULL) {
				if (_ListaEx_ItemResaltado == NULL)	_ListaEx_ItemMarcado = _ListaEx_Items[0];
				else								_ListaEx_ItemMarcado = _ListaEx_ItemResaltado;
			}
			DWLListaEx_Item *IM = _ListaEx_ItemMarcado;
			DWLListaEx_Item *TmpItem = NULL;

			if (Caracter == VK_SHIFT && _ListaEx_ItemShifteado == NULL) {
				_ListaEx_ItemShifteado = _ListaEx_ItemMarcado;
			}
			if (_ListaEx_Items.size() == 0) return;
			// Tecla Inicio
			if (_ListaEx_Teclado[VK_HOME] == true && Shift == false) { // Boton Inicio
				if (_ListaEx_ItemMarcado != _ListaEx_Items[0]) _ListaEx_ItemMarcado->_Seleccionado = false;
				BarraScrollEx_ValorV(0);
				_ListaEx_ItemMarcado = _ListaEx_Items[0];
				_ListaEx_ItemMarcado->_Seleccionado = true;
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
				Repintar(true);
			}
			// Tecla Inicio + Shift
			else if (_ListaEx_Teclado[VK_HOME] == true && Shift == true) { // Shift + Inicio
				if (_ListaEx_ItemMarcado != _ListaEx_Items[0]) {
					for (i = _ListaEx_ItemMarcado->Posicion() -1; i > 0; i--) _ListaEx_Items[i]->_Seleccionado = !_ListaEx_Items[i]->_Seleccionado;
					if (_ListaEx_ItemShifteado < _ListaEx_ItemMarcado)	_ListaEx_ItemMarcado->_Seleccionado = !_ListaEx_ItemMarcado->_Seleccionado;
					BarraScrollEx_ValorV(0);
					_ListaEx_ItemMarcado = _ListaEx_Items[0];
					_ListaEx_ItemMarcado->_Seleccionado = true;
					BarraScrollEx_CalcularScrollV();
					BarraScrollEx_CalcularScrollH();
					Repintar(true);
				}
			}

			// Tecla Fin
			if (_ListaEx_Teclado[VK_END] == true && Shift == false) { // Boton Fin
				_ListaEx_ItemMarcado->_Seleccionado = false;
				if ((_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) > 0) {
					BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
				}
				_ListaEx_ItemMarcado = _ListaEx_Items[_ListaEx_Items.size() -1];
				_ListaEx_ItemMarcado->_Seleccionado = true;
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
				Repintar(true);
			}

			// Tecla Fin + Shift
			else if (_ListaEx_Teclado[VK_END] == true && Shift == true) { // Shift + Fin;
				for (i = _ListaEx_ItemMarcado->Posicion() +1; i <  static_cast<int>(_ListaEx_Items.size()) -1; i++) _ListaEx_Items[i]->_Seleccionado = !_ListaEx_Items[i]->_Seleccionado;
				if ((_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) > 0) {
					BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
				}
				if (_ListaEx_ItemShifteado->Posicion() < _ListaEx_ItemMarcado->Posicion())	_ListaEx_ItemMarcado->_Seleccionado = !_ListaEx_ItemMarcado->_Seleccionado;
				_ListaEx_ItemMarcado = _ListaEx_Items[_ListaEx_Items.size() -1];
				_ListaEx_ItemMarcado->_Seleccionado = true;
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
				Repintar(true);
			}

			if (ListaEx_Estilos.ModoVisionado == DWL_LISTAEX_FILAS_HORIZONTAL) {
				// Tecla cursor derecha
				if (_ListaEx_Teclado[VK_RIGHT] == true && Shift == false) {
					ListaEx_DesSeleccionarTodo(false);
					_ListaEx_ItemMarcado = IM;
					i = _ListaEx_ItemMarcado->Posicion();
					if ((i + _BarraScrollEx_PaginaV) <= static_cast<int>(_ListaEx_Items.size() -1)) _ListaEx_ItemMarcado = _ListaEx_Items[i + _BarraScrollEx_PaginaV];
					_ListaEx_ItemMarcado->_Seleccionado = true;
					ListaEx_MostrarItem(_ListaEx_ItemMarcado);
					BarraScrollEx_CalcularScrollV();
					BarraScrollEx_CalcularScrollH();
					Repintar(true);
				}
				// Tecla cursor derecha + Shift
				else if (_ListaEx_Teclado[VK_RIGHT] == true && Shift == true) {
					if ((IM->Posicion() + _BarraScrollEx_PaginaV) > static_cast<int>(_ListaEx_Items.size() -1)) return;
					TmpItem = _ListaEx_Items[IM->Posicion() + _BarraScrollEx_PaginaV];
					_ListaEx_ItemMarcado = IM;
					while (_ListaEx_ItemMarcado != TmpItem) {
						_ListaEx_ItemMarcado->_Seleccionado = !_ListaEx_ItemMarcado->_Seleccionado;
						_ListaEx_ItemMarcado = _ListaEx_ItemMarcado->_Siguiente;
					}
					if (IM->_Siguiente->_Seleccionado == true) IM->_Seleccionado = true;
					_ListaEx_ItemMarcado->_Seleccionado = true;
					ListaEx_MostrarItem(_ListaEx_ItemMarcado);
					BarraScrollEx_CalcularScrollV();
					BarraScrollEx_CalcularScrollH();
					Repintar(true);
				}

				// Tecla cursor izquierda
				if (_ListaEx_Teclado[VK_LEFT] == true && Shift == false) {
					ListaEx_DesSeleccionarTodo(false);
					_ListaEx_ItemMarcado = IM;
					i = _ListaEx_ItemMarcado->Posicion();
					if (i >= _BarraScrollEx_PaginaV) _ListaEx_ItemMarcado = _ListaEx_Items[i - _BarraScrollEx_PaginaV];
					_ListaEx_ItemMarcado->_Seleccionado = true;
					ListaEx_MostrarItem(_ListaEx_ItemMarcado);
					BarraScrollEx_CalcularScrollV();
					BarraScrollEx_CalcularScrollH();
					Repintar(true);
				}
				// Tecla cursor izquierda + Shift
				else if (_ListaEx_Teclado[VK_LEFT] == true && Shift == true) {
					if (IM->Posicion() < _BarraScrollEx_PaginaV) return;
					TmpItem = _ListaEx_Items[IM->Posicion() - _BarraScrollEx_PaginaV];
					_ListaEx_ItemMarcado = IM;

					while (_ListaEx_ItemMarcado != TmpItem) {
						_ListaEx_ItemMarcado->_Seleccionado = !_ListaEx_ItemMarcado->_Seleccionado;
						_ListaEx_ItemMarcado = _ListaEx_ItemMarcado->_Anterior;
					}
					if (IM->_Anterior->_Seleccionado == true) IM->_Seleccionado = true;
					_ListaEx_ItemMarcado->_Seleccionado = true;
					ListaEx_MostrarItem(_ListaEx_ItemMarcado);
					BarraScrollEx_CalcularScrollV();
					BarraScrollEx_CalcularScrollH();
					Repintar(true);
				}

			}

			// Tecla cursor arriba
			if (_ListaEx_Teclado[VK_UP] == true && Shift == false) {
				ListaEx_DesSeleccionarTodo(false);
				_ListaEx_ItemMarcado = IM;
				if (_ListaEx_ItemMarcado->_Anterior != NULL) _ListaEx_ItemMarcado = _ListaEx_ItemMarcado->_Anterior;
				_ListaEx_ItemMarcado->_Seleccionado = true;
				ListaEx_MostrarItem(_ListaEx_ItemMarcado);
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
				Repintar(true);
			}

			// Tecla cursor arriba + Shift
			else if (_ListaEx_Teclado[VK_UP] == true && Shift == true) {
				if (_ListaEx_ItemShifteado->Posicion() < _ListaEx_ItemMarcado->Posicion())	_ListaEx_ItemMarcado->_Seleccionado = !_ListaEx_ItemMarcado->_Seleccionado;
				if (_ListaEx_ItemMarcado->_Anterior != NULL) _ListaEx_ItemMarcado = _ListaEx_ItemMarcado->_Anterior;
				_ListaEx_ItemMarcado->_Seleccionado = true;
				ListaEx_MostrarItem(_ListaEx_ItemMarcado);
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
				Repintar(true);
			}

			// Tecla Cursor abajo
			if (_ListaEx_Teclado[VK_DOWN] == true && Shift == false) {
				ListaEx_DesSeleccionarTodo(false);
				_ListaEx_ItemMarcado = IM;
				if (_ListaEx_ItemMarcado->_Siguiente != NULL) _ListaEx_ItemMarcado = _ListaEx_ItemMarcado->_Siguiente;
				_ListaEx_ItemMarcado->_Seleccionado = true;
				ListaEx_MostrarItem(_ListaEx_ItemMarcado);
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
				Repintar(true);
			}

			// Tecla Cursor abajo + Shift
			else if (_ListaEx_Teclado[VK_DOWN] == true && Shift == true) {
				if (_ListaEx_ItemShifteado->Posicion() > _ListaEx_ItemMarcado->Posicion())	_ListaEx_ItemMarcado->_Seleccionado = !_ListaEx_ItemMarcado->_Seleccionado;
				if (_ListaEx_ItemMarcado->_Siguiente != NULL) _ListaEx_ItemMarcado = _ListaEx_ItemMarcado->_Siguiente;
				_ListaEx_ItemMarcado->_Seleccionado = true;
				ListaEx_MostrarItem(_ListaEx_ItemMarcado);
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
				Repintar(true);
			}

			// Tecla RePag
			if (_ListaEx_Teclado[VK_PRIOR] == true && Shift == false) {
				ListaEx_DesSeleccionarTodo(false);
				_ListaEx_ItemMarcado = IM;
				_ListaEx_ItemMarcado->_Seleccionado = false;
				if (_ListaEx_ItemMarcado->Posicion() == _BarraScrollEx_ValorV) {
					_BarraScrollEx_ValorV -= _BarraScrollEx_PaginaV;
					if (_BarraScrollEx_ValorV < 0) _BarraScrollEx_ValorV = 0;
					_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;
				}
				_ListaEx_ItemMarcado = _ListaEx_Items[_BarraScrollEx_ValorV];
				_ListaEx_ItemMarcado->_Seleccionado = true;
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
				Repintar(true);
			}

			// Tecla RePag + Shift
			else if (_ListaEx_Teclado[VK_PRIOR] == true && Shift == true) {
			/*	ListaEx_DesSeleccionarTodo(false);
				_ListaEx_ItemMarcado = IM;
				ISPosicion = _ListaEx_ItemShifteado->Posicion();
				if (ISPosicion == _BarraScrollEx_ValorV) {
					_BarraScrollEx_ValorV -= _BarraScrollEx_PaginaV;
					if (_BarraScrollEx_ValorV < 0) _BarraScrollEx_ValorV = 0;
				}
				_ListaEx_ItemMarcado = _ListaEx_Items[_BarraScrollEx_ValorV];
				_ListaEx_ItemMarcado->_Seleccionado = true;
				IMPosicion = _ListaEx_ItemMarcado->Posicion();
				if (ISPosicion > IMPosicion) {
					for (i = ISPosicion; i > IMPosicion; i--) _ListaEx_Items[i]->Seleccionado(true ,false);
				}
				else {
					for (i = ISPosicion; i < IMPosicion; i++) _ListaEx_Items[i]->Seleccionado(true ,false);
				}
				Repintar(true);
				_ScrollV->ReAjustarMedidas();
				_ScrollV->Repintar(true);
		/*		ISPosicion = _ItemShifteado->Posicion();
				if (ISPosicion - (_BarraScrollEx_PaginaV -1) == _BarraScrollEx_ValorV) {
					if ((_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) > 0) {
						_BarraScrollEx_ValorV += _BarraScrollEx_PaginaV;
						if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) _BarraScrollEx_ValorV = (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
					}
				}
				_ListaEx_ItemMarcado = _ListaEx_Items[_BarraScrollEx_ValorV];
				IMPosicion = _ListaEx_ItemMarcado->Posicion();
				if (ISPosicion > IMPosicion) {
					for (i = ISPosicion; i > IMPosicion; i--) _ListaEx_Items[i]->Seleccionado(true ,false);
				}
				else {
					for (i = ISPosicion; i < IMPosicion; i++) _ListaEx_Items[i]->Seleccionado(true ,false);
				}
				_ListaEx_ItemMarcado->_Seleccionado = true;
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
				Repintar(true);
		*/
			}

			// Tecla Av Pag
 			if (_ListaEx_Teclado[VK_NEXT] == true && Shift == false) {
				ListaEx_DesSeleccionarTodo(false);
				_ListaEx_ItemMarcado = IM;
				_ListaEx_ItemMarcado->_Seleccionado = false;
				if (_ListaEx_ItemMarcado->Posicion() - (_BarraScrollEx_PaginaV -1) == _BarraScrollEx_ValorV) {
					if ((_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) > 0) {
						_BarraScrollEx_ValorV += _BarraScrollEx_PaginaV;
						if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) _BarraScrollEx_ValorV = (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
						_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;
					}
				}
				if (_BarraScrollEx_ValorV + (_BarraScrollEx_PaginaV -1) > static_cast<int>(_ListaEx_Items.size() -1))	_ListaEx_ItemMarcado = _ListaEx_Items[_ListaEx_Items.size() -1];
				else																									_ListaEx_ItemMarcado = _ListaEx_Items[_BarraScrollEx_ValorV + (_BarraScrollEx_PaginaV -1)];
				if (_ListaEx_ItemMarcado->Posicion() > _BarraScrollEx_MaximoV -1) _ListaEx_ItemMarcado = _ListaEx_Items[_ListaEx_Items.size() -1];
				_ListaEx_ItemMarcado->_Seleccionado = true;
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
				Repintar(true);
			}

			// Tecla Av Pag + Shift
			else if (_ListaEx_Teclado[VK_NEXT] == true && Shift == true) {
		/*		ISPosicion = _ItemShifteado->Posicion();
				if (ISPosicion - (_BarraScrollEx_PaginaV -1) == _BarraScrollEx_ValorV) {
					if ((_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) > 0) {
						_BarraScrollEx_ValorV += _BarraScrollEx_PaginaV;
						if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) _BarraScrollEx_ValorV = (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
					}
				}
				if (_BarraScrollEx_ValorV + (_BarraScrollEx_PaginaV -1) > static_cast<int>(_Items.size() -1))	_ItemMarcado = _Items[_Items.size() -1];
				else																			_ItemMarcado = _Items[_BarraScrollEx_ValorV + (_BarraScrollEx_PaginaV -1)];
				_ItemMarcado = _Items[_BarraScrollEx_ValorV];
				IMPosicion = _ItemMarcado->Posicion();
				// si el item shiftejat es mes gran k el marcat haig de fer el bucle
				if (ISPosicion > IMPosicion) {
					for (i = ISPosicion; i > IMPosicion; i--)
						_Items[i]->_Seleccionado = !_Items[i]->_Seleccionado;
				}
				else {
					for (i = ISPosicion; i < IMPosicion; i++)
						_Items[i]->_Seleccionado = !_Items[i]->_Seleccionado;
				}
				_ItemMarcado->_Seleccionado = true;
				Repintar(true);
				_ScrollV->ReAjustarMedidas();
				_ScrollV->Repintar(true);
		/*		_ItemMarcado = IM;
				IMPosicion = IM->Posicion();
				if (IMPosicion - (_BarraScrollEx_PaginaV -1) == _BarraScrollEx_ValorV) {
					if ((_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) > 0) {
						_BarraScrollEx_ValorV += _BarraScrollEx_PaginaV;
						if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) _BarraScrollEx_ValorV = (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
					}
				}
				if ((_BarraScrollEx_ValorV + (_BarraScrollEx_PaginaV -1)) > static_cast<int>(_Items.size()) -1)
					_ItemMarcado = _Items[_Items.size() -1];
				else
					_ItemMarcado = _Items[_BarraScrollEx_ValorV + (_BarraScrollEx_PaginaV -1)];
				ItemMarcadoPosicion = _ItemMarcado->Posicion();
				if (IMPosicion > ItemMarcadoPosicion) {
					for (i = IMPosicion - 1; i > ItemMarcadoPosicion; i--) _Items[i]->_Seleccionado = !_Items[i]->_Seleccionado;
				}
				else {
					for (i = IMPosicion + 1; i < ItemMarcadoPosicion; i++) _Items[i]->_Seleccionado = !_Items[i]->_Seleccionado;
				}
				if (ItemMarcadoPosicion > _BarraScrollEx_MaximoV -1) _ItemMarcado = _Items[_BarraScrollEx_MaximoV -1];
		//		IM->_Seleccionado = !IM->_Seleccionado;
				_ItemMarcado->_Seleccionado = true;
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
 				Repintar(true);
		*/
			}

			if (_ListaEx_Teclado[VK_ESCAPE] == true) {
				ListaEx_DesSeleccionarTodo(false);
				_ListaEx_ItemMarcado = IM;
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
				Repintar(true);
			}
			// VK_HOME
			// VK_END
			// VK_UP
			// VK_DOWN
			// VK_PRIOR
			// VK_NEXT
			// VK_A to VK_Z
			// VK_ESCAPE
			// VK_CONTROL
			// VK_SHIFT
			PostMessage(GetParent(hWndControl), DWL_LISTAEX_TECLADO_PRESIONADO, (WPARAM)Caracter, (LPARAM)GetWindowLong(hWndControl, GWL_ID));

		}

		//! Función virtual que monta los datos del tooltip antes de mostrarlo
		/*! Esta función virtual es llamada cuando la ListaEx quiere mostrar un tooltip de un Item.
				\fn			virtual void ListaEx_Evento_MostrarToolTip(DWLListaEx_Item *ttItem);
				\param[in]	ttItem : Item del que se va a mostrar la informacion.
				\return		No devuelve nada.
				\remarks	Por defecto el tooltip muestra el texto del primer subitem y icono del item.
							Puedes re-emplazar esta función y mostrar los datos que desees del item.
		*/
		/*void DWLListaEx_Nucleo::ListaEx_Evento_MostrarToolTip(DWLListaEx_Item *ttItem) {
			if (ttItem == NULL) return;
			ListaEx_ToolTip.BorrarMemoria();
			ListaEx_ToolTip.AgregarIconoTexto(ttItem->Icono(), 16, 16, ttItem->Texto(0));
			for (size_t i = 1; i < _ListaEx_Columnas.size(); i++) {
				ListaEx_ToolTip.AgregarTexto(ttItem->Texto(i));
			}
			ListaEx_ToolTip.MostrarToolTipEx();
		}*/


	    //! WindowProcedure que usara el Editbox en la Función ListaEx_EmpezarLabelEdit().
	    /*! WindowProcedure que usara el Editbox en la Función ListaEx_EmpezarLabelEdit().
			    \fn			static LRESULT CALLBACK _ListaEx_GestorMensajesEdit(HWND dhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			    \param[in]	dhWnd	: HWND del EditBox.
			    \param[in]	uMsg	: Mensaje.
			    \param[in]	wParam	: Parametro1.
			    \param[in]	lParam	: Parametro2.
			    \return		Devuelve un valor acorde al mensaje especificado.
			    \remarks	Funcion de uso interno para ListaEx_EmpezarLabelEdit().
	    */
		LRESULT CALLBACK DWLListaEx_Nucleo::_ListaEx_GestorMensajesEdit(HWND dhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			DWLListaEx_Nucleo *This = reinterpret_cast<DWLListaEx_Nucleo *>(LongToPtr(GetWindowLongPtr(dhWnd, GWL_USERDATA)));
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
					PostMessage(GetParent(dhWnd), DWL_LISTAEX_TECLADO_SOLTADO, wParam, 0);
					if (wParam == 13) PostMessage(GetParent(dhWnd), DWL_LISTAEX_TECLADO_INTRO, 0, 0);
					break;
			}
			return CallWindowProc(This->_ListaEx_GestorMensajesOriginalEdit, dhWnd, uMsg, wParam, lParam);
		};

		//! Función que procesa el movimiento del mouse en la ListaEx.
		/*! Esta función procesa el movimiento del mouse en la ListaEx.
				\fn			BOOL ListaEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT wParam);
				\param[in]	hWndControl		: HWND del control que contiene la ListaEx.
				\param[in]	RectaControl	: Recta con el espacio de la ListaEx.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_Movimiento del control que vaya a contener la ListaEx.
				\sa			ListaEx_Mouse_BotonPresionado(), ListaEx_Mouse_BotonSoltado()
		*/
		BOOL DWLListaEx_Nucleo::ListaEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param) {
			if (BarraScrollEx_Mouse_Movimiento(hWndControl, RectaControl, cX, cY, Param, ListaEx_Estilos.PintarBorde) == TRUE) return TRUE;
			if (_ListaEx_Editando == true) return TRUE;
			#if defined DWL_LISTAEX_DEBUG
				DWL::DWLDebug::ImprimirDebug(TEXT("DWLListaEx::Evento_Mouse_Movimiento (Item %.08x | SubItem %d | ItemShifteado %.08x | TotalItems %d)\n"), _ItemResaltado, _SubItemResaltado, _ItemShifteado, _Items.size());
			#endif
			if (cX < 0 || cY < 0) return TRUE;
			if (ListaEx_Estilos.ModoVisionado == DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL) {
				int IntItemResaltado = (cY / _ListaEx_AltoLinea) + _BarraScrollEx_PosActualV;
				if (ListaEx_Estilos.MostrarEncabezadosColumnas == true) IntItemResaltado --;
				if (cX >  RectaControl->right - 17 &&  BarraScrollEx_VisibleV() == TRUE)	IntItemResaltado = -1; // Esta en la parte del scrollbar
				if (IntItemResaltado > _BarraScrollEx_MaximoV -1)		IntItemResaltado = -1; // Esta en una posicion que no hay items porque se ha superado el maximo
				if (IntItemResaltado == -1) _ListaEx_ItemResaltado = NULL;
				else						_ListaEx_ItemResaltado = _ListaEx_Items[IntItemResaltado];
				// Si no coinciden los items reseteamos el tooltip
				if (_ListaEx_TT_UltimoItem != _ListaEx_ItemResaltado) {
					KillTimer(hWndControl, DWL_TIMER_TOOLTIP);
					SetTimer(hWndControl, DWL_TIMER_TOOLTIP, DWL_TIEMPO_TOOLTIP, NULL);
					SendMessage(GetParent(hWndControl), DWL_TOOLTIPEX_OCULTAR, GetWindowLong(hWndControl, GWL_ID), 0);
					_ListaEx_TT_UltimoItem = _ListaEx_ItemResaltado;
				}

				int RC = 0;
				int TAncho = 0;
				if (ListaEx_Estilos.PintarIconos == true) TAncho += 18;
				_ListaEx_SubItemResaltado = -1;
				while (TAncho < cX) {
					_ListaEx_SubItemResaltado ++;
					if (_ListaEx_SubItemResaltado < static_cast<int>(_ListaEx_Columnas.size())) TAncho += _ListaEx_Columnas[_ListaEx_SubItemResaltado]->_Ancho;
					else																		break;
				}
				if (IntItemResaltado == -1) {
					for (size_t i = 0; i < _ListaEx_Columnas.size(); i++) {
						if (_ListaEx_Columnas[i]->_Estado != DWL_LISTAEX_ESTADO_PRESIONADO) _ListaEx_Columnas[i]->_Estado = DWL_LISTAEX_ESTADO_NORMAL;
					}
				}
				if (ListaEx_Estilos.MostrarEncabezadosColumnas == true) {
					RECT RCC = { 0, 0, _ListaEx_Columnas[0]->_Ancho, _ListaEx_AltoLinea };
					POINT Pt = { cX, cY };
					int Suma = 0;
					if (BarraScrollEx_VisibleV() == TRUE) Suma += 17;
					for (size_t i = 0; i < _ListaEx_Columnas.size(); i++) {
						if (i == 0) RCC.left = 0;
						else		RCC.left = Suma;
						Suma += _ListaEx_Columnas[i]->_Ancho;
						RCC.right = Suma;
						if (_ListaEx_Columnas[i]->_Estado != DWL_LISTAEX_ESTADO_PRESIONADO) {
							if (PtInRect(&RCC, Pt) == TRUE) _ListaEx_Columnas[i]->_Estado = DWL_LISTAEX_ESTADO_RESALTADO;
							else							_ListaEx_Columnas[i]->_Estado = DWL_LISTAEX_ESTADO_NORMAL;
						}
					}
				}

				if (_ListaEx_SubItemResaltado == -1) _ListaEx_SubItemResaltado = 0;
				if (cX > RectaControl->right - 17 && BarraScrollEx_VisibleV() == TRUE) _ListaEx_ItemResaltado = NULL;

				if (_ListaEx_ItemResaltado != _ListaEx_UItemResaltado) {
					HDC hDC = GetDC(hWndControl);
					if (_ListaEx_ItemResaltado != NULL)	  ListaEx_PintarItem_Filas_y_Columnas_Vertical(hDC, RectaControl, _ListaEx_ItemResaltado);
					if (_ListaEx_UItemResaltado != NULL)  ListaEx_PintarItem_Filas_y_Columnas_Vertical(hDC, RectaControl, _ListaEx_UItemResaltado);
					ReleaseDC(hWndControl, hDC);
					_ListaEx_UItemResaltado = _ListaEx_ItemResaltado;
				}
			}

			if (ListaEx_Estilos.ModoVisionado == DWL_LISTAEX_FILAS_HORIZONTAL) {
				int IntY = (cY / _ListaEx_AltoLinea);
				int IntX = _BarraScrollEx_PosActualH + (cX / ListaEx_Estilos.AnchoMaximoItem);
				int ItemFinal = (IntX * _BarraScrollEx_PaginaV) + IntY;
				int AnchoIconos = 0;
				if (ListaEx_Estilos.PintarIconos == true) AnchoIconos = 18;
				if (ItemFinal >= static_cast<int>(_ListaEx_Items.size())) {
					_ListaEx_ItemResaltado = NULL;
				}
				else {
					POINT Pt = { cX, cY };
					RECT RectaItem = { (IntX - _BarraScrollEx_PosActualH) * ListaEx_Estilos.AnchoMaximoItem, IntY * _ListaEx_AltoLinea, ((IntX - _BarraScrollEx_PosActualH) * ListaEx_Estilos.AnchoMaximoItem) + (_ListaEx_Items[ItemFinal]->_Ancho + AnchoIconos), (IntY * _ListaEx_AltoLinea) + _ListaEx_AltoLinea };
					if (PtInRect(&RectaItem, Pt) == TRUE)	_ListaEx_ItemResaltado = _ListaEx_Items[ItemFinal];
					else									_ListaEx_ItemResaltado = NULL;
				}
				// Si no coinciden los items reseteamos el tooltip
				if (_ListaEx_TT_UltimoItem != _ListaEx_ItemResaltado) {
					KillTimer(hWndControl, DWL_TIMER_TOOLTIP);
					SetTimer(hWndControl, DWL_TIMER_TOOLTIP, DWL_TIEMPO_TOOLTIP, NULL);
					_ListaEx_TT_UltimoItem = _ListaEx_ItemResaltado;
				}

				if (IntY >= _BarraScrollEx_PaginaV) _ListaEx_ItemResaltado = NULL;
				if (_ListaEx_ItemResaltado != _ListaEx_UItemResaltado) {
					HDC hDC = GetDC(hWndControl);
					if (_ListaEx_ItemResaltado != NULL)	  ListaEx_PintarItem_Filas_Horizontal(hDC, RectaControl, _ListaEx_ItemResaltado, (IntX - _BarraScrollEx_PosActualH), IntY);
					if (_ListaEx_UItemResaltado != NULL)  ListaEx_PintarItem_Filas_Horizontal(hDC, RectaControl, _ListaEx_UItemResaltado, _ListaEx_UltimoIntX, _ListaEx_UltimoIntY);
					ReleaseDC(hWndControl, hDC);
					_ListaEx_UItemResaltado = _ListaEx_ItemResaltado;
					_ListaEx_UltimoIntX = (IntX - _BarraScrollEx_PosActualH);
					_ListaEx_UltimoIntY = IntY;
				}
			}
			return TRUE;
		}

		//! Función que procesa los botones soltados del mouse en la ListaEx.
		/*! Esta función procesa los botones soltados del mouse en la ListaEx.
				\fn			BOOL ListaEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	hWndControl		: HWND del control que contiene la ListaEx.
				\param[in]	RectaControl	: Recta con el espacio de la ListaEx.
				\param[in]	Boton			: Boton del mouse presionado.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonSoltado del control que vaya a contener la ListaEx.
				\sa			ListaEx_Mouse_Movimiento(), ListaEx_Mouse_BotonPresionado()
		*/
		BOOL DWLListaEx_Nucleo::ListaEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			if (_BarraScrollEx_Activado == FALSE) return FALSE;
			if (BarraScrollEx_Mouse_BotonSoltado(hWndControl, RectaControl, Boton, cX, cY, Param) == TRUE) return TRUE;
			bool ColumnaPresionada = false;
			int nAncho = RectaControl->right;
			bool Shift   = (Param & MK_SHIFT)   ? true : false;
			bool Control = (Param & MK_CONTROL) ? true : false;

			if (_ListaEx_Editando == true) ListaEx_CancelarLabelEdit(hWndControl);
			if (ListaEx_Estilos.MultiSeleccion == false) {
				Shift = false;
				Control = false;
			}


			if (BarraScrollEx_VisibleV() == TRUE) nAncho -= 17;
			if (cX < 0 || cX > nAncho || cY < 0 || cY > RectaControl->bottom) return FALSE;

			if (_ListaEx_ItemPresionado != NULL) {
				if (Control == true) {
					_ListaEx_ItemPresionado->_Seleccionado = !_ListaEx_ItemPresionado->_Seleccionado;
				}

				int ItemMarcadoPos		= _ListaEx_ItemMarcado->Posicion();
				int ItemPresionadoPos	= _ListaEx_ItemPresionado->Posicion();

				if (ListaEx_Estilos.MostrarEncabezadosColumnas == true) {
					ItemMarcadoPos --;
					ItemPresionadoPos --;
				}

				if (Shift == true) {
					int i;
					if (_ListaEx_ItemMarcado != NULL) {
						if (ItemMarcadoPos > ItemPresionadoPos) { // De abajo a arriba
							for (i = ItemPresionadoPos; i < ItemMarcadoPos; i++) {
								_ListaEx_Items[i]->_Seleccionado = !_ListaEx_Items[i]->_Seleccionado;
							}
							if (ItemMarcadoPos > ItemPresionadoPos) _ListaEx_Items[ItemMarcadoPos]->_Seleccionado = _ListaEx_Items[ItemMarcadoPos - 1]->_Seleccionado;
						}
						if (ItemMarcadoPos < ItemPresionadoPos) { // De arriba a abajo
							for (i = ItemMarcadoPos; i < ItemPresionadoPos +1; i++) {
								_ListaEx_Items[i]->_Seleccionado = !_ListaEx_Items[i]->_Seleccionado;
							}
							if (ItemMarcadoPos < ItemPresionadoPos) _ListaEx_Items[ItemMarcadoPos]->_Seleccionado = _ListaEx_Items[ItemMarcadoPos + 1]->_Seleccionado;
						}
						_ListaEx_ItemMarcado = _ListaEx_ItemPresionado;
						_ListaEx_ItemMarcado->_Seleccionado = true;
					}
				}

				if (Control == false && Shift == false) {
					if (Boton == 0) {
						ListaEx_DesSeleccionarTodo(false);
						if (_ListaEx_ItemPresionado == _ListaEx_ItemResaltado) _ListaEx_ItemPresionado->_Seleccionado = true;
						_ListaEx_ItemMarcado = _ListaEx_ItemPresionado;
					}
					else if (Boton == 1) {
						if (_ListaEx_ItemPresionado->_Seleccionado == false) {
							ListaEx_DesSeleccionarTodo(false);
							_ListaEx_ItemPresionado->_Seleccionado = true;
						}
						_ListaEx_ItemMarcado = _ListaEx_ItemPresionado;
					}
					else if (Boton == 3) { // Mostrar tooltip
						ListaEx_DesSeleccionarTodo(false);
						if (_ListaEx_ItemPresionado == _ListaEx_ItemResaltado) _ListaEx_ItemPresionado->_Seleccionado = true;
						_ListaEx_ItemMarcado = _ListaEx_ItemPresionado;
						_ListaEx_TT_UltimoItem = _ListaEx_ItemPresionado;
/*						if (_ListaEx_TT_Mostrar == true) {
							ListaEx_ToolTip.Destruir();
							ListaEx_Evento_MostrarToolTip(_ListaEx_ItemResaltado);
						}*/
						SendMessage(GetParent(hWndControl), DWL_TOOLTIPEX_MOSTRAR, GetWindowLong(hWndControl, GWL_ID), 0);
					}
					else {
						if (_ListaEx_ItemPresionado == _ListaEx_ItemResaltado) _ListaEx_ItemPresionado->_Seleccionado = true;
						_ListaEx_ItemMarcado = _ListaEx_ItemPresionado;
					}
				}
				// Dobleclick
				if (_ListaEx_UltimoClick + GetDoubleClickTime() > GetTickCount() && _ListaEx_UltimoBoton == Boton) {
					_ListaEx_UltimoClick = 0;
					if (_ListaEx_ItemResaltado != NULL) {
						if (_ListaEx_PosUltimoClick == _ListaEx_ItemResaltado->Posicion()) {
							ListaEx_Evento_Mouse_DobleClick(Boton, cX, cY);
							DWLListaEx_ParametrosClick ParamFinal(_ListaEx_ItemPresionado, cX, cY, GetWindowLongPtr(hWndControl, GWL_ID), Boton);
							SendMessage(GetParent(hWndControl), DWL_LISTAEX_DOBLECLICK, reinterpret_cast<WPARAM>(&ParamFinal) , 0);
						}
					}
				}
				else {
					_ListaEx_UltimoBoton = Boton;
					_ListaEx_UltimoClick = GetTickCount();
				}
				_ListaEx_ItemPresionado = NULL;
				_ListaEx_SubItemPresionado = -1;
				if (_ListaEx_ItemResaltado != NULL) _ListaEx_PosUltimoClick = _ListaEx_ItemResaltado->Posicion();
				else								_ListaEx_PosUltimoClick = -1;
			}
			else {
				ListaEx_DesSeleccionarTodo();
			}
			if (ListaEx_Estilos.MostrarEncabezadosColumnas == true) {
				RECT RCC = { 0, 0, _ListaEx_Columnas[0]->_Ancho, _ListaEx_AltoLinea };
				POINT Pt = { cX, cY };
				int Suma = 0;
				if (BarraScrollEx_VisibleV() == TRUE) Suma += 17;
				for (size_t i = 0; i < _ListaEx_Columnas.size(); i++) {
					if (i == 0) RCC.left = 0;
					else		RCC.left = Suma;
					Suma += _ListaEx_Columnas[i]->_Ancho;
					RCC.right = Suma;
					if (PtInRect(&RCC, Pt) == TRUE) {
						if (_ListaEx_Columnas[i]->_Estado == DWL_LISTAEX_ESTADO_PRESIONADO) {
							ColumnaPresionada = true;
							ListaEx_Evento_ColumnaPresionada(_ListaEx_Columnas[i], Boton, Param);
						}
						_ListaEx_Columnas[i]->_Estado = DWL_LISTAEX_ESTADO_RESALTADO;
					}
					else {
						_ListaEx_Columnas[i]->_Estado = DWL_LISTAEX_ESTADO_NORMAL;
					}
				}
			}

			SetFocus(hWndControl);

			if (ColumnaPresionada == false) {
				DWLListaEx_ParametrosClick ParamFinal(_ListaEx_ItemPresionado, cX, cY, GetWindowLongPtr(hWndControl, GWL_ID), Boton);
				SendMessage(GetParent(hWndControl), DWL_LISTAEX_CLICK, reinterpret_cast<WPARAM>(&ParamFinal) , 0);
			}
			return TRUE;
		}

		//! Función que procesa los botones presionados del mouse en la ListaEx.
		/*! Esta función procesa los botones presionados del mouse en la ListaEx.
				\fn			BOOL ListaEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	hWndControl		: HWND del control que contiene la ListaEx.
				\param[in]	RectaControl	: Recta con el espacio de la ListaEx.
				\param[in]	Boton			: Boton del mouse presionado.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonPresionado del control que vaya a contener la ListaEx.
				\sa			ListaEx_Mouse_Movimiento(), ListaEx_Mouse_BotonSoltado()
		*/
		BOOL DWLListaEx_Nucleo::ListaEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			if (_BarraScrollEx_Activado == FALSE) return FALSE;
			if (BarraScrollEx_Mouse_BotonPresionado(hWndControl, RectaControl, Boton, cX, cY, Param) == TRUE) return TRUE;
			int nAncho = RectaControl->right;

			if (ListaEx_Estilos.ModoVisionado == DWL_LISTAEX_FILAS_Y_COLUMNAS_VERTICAL) {
				if (BarraScrollEx_VisibleV() == TRUE) nAncho -= 17;
				if (cX < 0 || cX > nAncho || cY < 0 || cY > RectaControl->bottom) return FALSE;
				int IntItemResaltado = (cY / _ListaEx_AltoLinea) + _BarraScrollEx_PosActualV;
				if (ListaEx_Estilos.MostrarEncabezadosColumnas == true) IntItemResaltado --;
				if (IntItemResaltado != -1) { // Si es -1 es que esta clicando una columna
					if (IntItemResaltado > _BarraScrollEx_MaximoV -1)	_ListaEx_ItemResaltado = NULL;
					else												_ListaEx_ItemResaltado = _ListaEx_Items[IntItemResaltado];
				}
				else { // Click en una columna
					_ListaEx_ItemResaltado = NULL;
					if (ListaEx_Estilos.MostrarEncabezadosColumnas == true) {
						RECT RCC = { 0, 0, _ListaEx_Columnas[0]->_Ancho, _ListaEx_AltoLinea };
						POINT Pt = { cX, cY };
						int Suma = 0;
						if (BarraScrollEx_VisibleV() == TRUE) Suma += 17;
						for (size_t i = 0; i < _ListaEx_Columnas.size(); i++) {
							if (i == 0) RCC.left = 0;
							else		RCC.left = Suma;
							Suma += _ListaEx_Columnas[i]->_Ancho;
							RCC.right = Suma;
							if (PtInRect(&RCC, Pt) == TRUE) _ListaEx_Columnas[i]->_Estado = DWL_LISTAEX_ESTADO_PRESIONADO;
							else							_ListaEx_Columnas[i]->_Estado = DWL_LISTAEX_ESTADO_NORMAL;
						}
					}
				}
			}

			if (ListaEx_Estilos.ModoVisionado == DWL_LISTAEX_FILAS_HORIZONTAL) {
				int IntY = (cY / _ListaEx_AltoLinea);
				int IntX = _BarraScrollEx_PosActualH + (cX / ListaEx_Estilos.AnchoMaximoItem);
				int ItemFinal = (IntX * _BarraScrollEx_PaginaV) + IntY;
				int AnchoIconos = 0;
				if (ListaEx_Estilos.PintarIconos == true) AnchoIconos = 18;
				if (ItemFinal >= static_cast<int>(_ListaEx_Items.size())) {
					_ListaEx_ItemResaltado = NULL;
				}
				else {
					POINT Pt = { cX, cY };
					RECT RectaItem = { (IntX - _BarraScrollEx_PosActualH) * ListaEx_Estilos.AnchoMaximoItem, IntY * _ListaEx_AltoLinea, ((IntX - _BarraScrollEx_PosActualH) * ListaEx_Estilos.AnchoMaximoItem) + (_ListaEx_Items[ItemFinal]->_Ancho + AnchoIconos), (IntY * _ListaEx_AltoLinea) + _ListaEx_AltoLinea };
					if (PtInRect(&RectaItem, Pt) == TRUE)	_ListaEx_ItemResaltado = _ListaEx_Items[ItemFinal];
					else									_ListaEx_ItemResaltado = NULL;
				}
				if (IntY >= _BarraScrollEx_PaginaV) _ListaEx_ItemResaltado = NULL;
			}


			_ListaEx_ItemPresionado = _ListaEx_ItemResaltado;
			_ListaEx_SubItemPresionado = _ListaEx_SubItemResaltado;
			if (_ListaEx_Teclado[VK_SHIFT] == false) _ListaEx_ItemMarcado = _ListaEx_ItemResaltado;
			Repintar(true);
			return TRUE;
		}

		//! Función que procesa la rueda del raton dentro de la ListaEx.
		/*!	Esta función es la encargada de procesar la rueda del raton dentro de la ListaEx.
				\fn			virtual LRESULT ListaEx_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey);
				\param[in]	Delta	: Valor de desplazamiento del mouse.
				\param[in]	cX		: Coordenada X.
				\param[in]	cY		: Coordenada Y.
				\param[in]	VirtKey	: Tecla virtual presionada.
				\return		Devuelve TRUE.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_Rueda del control que vaya a contener la ListaEx.
		*/
		BOOL DWLListaEx_Nucleo::ListaEx_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey) {
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
            return TRUE;
		}

		//! Función para habilitar / deshabilitar los tooltips.
		/*! Esta función habilita / deshabilita los tooltips.
				\fn			void ListaEx_MostrarToolTip(HWND hWndControl, const bool nMostrar);
				\param[in]	hWndControl : HWND del control que contiene la ListaEx.
				\param[in]	nMostrar : True para mostrar los tooltips cuando sea necesario, false para no mostrar nunca los tooltips.
				\return		No devuelve nada.
		*/
/*		void DWLListaEx_Nucleo::ListaEx_MostrarToolTip(HWND hWndControl, const bool nMostrar) {
			_ListaEx_TT_Mostrar = nMostrar;
			if (nMostrar == true)	SetTimer(hWndControl, DWL_TIMER_TOOLTIP, 500, NULL);
			else					KillTimer(hWndControl, DWL_TIMER_TOOLTIP);
		}*/


    };
};

