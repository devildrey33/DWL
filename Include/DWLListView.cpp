/*! \file DWLListView.cpp
	\brief		Archivo que contiene funciones para la utilización de un listview en windows.


	\details	Clase diseñada para poder controlar un listview de windows.																				\n
				Esta clase en breve no formara parte del proyecto y por lo tanto no recibira actualizaciones.											\n
				Si quieres utilizar un control del estilo del edit box con la DWL se recomienda usar DWLListaEx.									\n
				Para la version 1.0 de la DWL esta clase probablemente desaparecera.																	\n

				 																																		\n
	\author		devildrey33
	\version	0.95
	\date		07/12/2005

	\remarks
				Archivo creado por devildrey33 el dia [16/03/2004] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n	
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n	
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n	

*/

//! Cabecera DWLListView.h
#include "DWLListView.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Controles
	namespace Controles {

		// Constructor que inicia las clases del ListView en los common controls
		DWLListView::DWLListView(void) {
			INITCOMMONCONTROLSEX Comm;
			Comm.dwSize = sizeof(INITCOMMONCONTROLSEX);
			Comm.dwICC = ICC_LISTVIEW_CLASSES;
			InitCommonControlsEx(&Comm);
			_ColorSeleccion = GetSysColor(COLOR_HIGHLIGHT);
			_ColorSeleccionTexto = GetSysColor(COLOR_HIGHLIGHTTEXT); 
			_Editando = false;
		};



		// Destructor
		DWLListView::~DWLListView(void) {
			unsigned int i;
			Destruir();
			for (i = 0; i < _Cols.size(); i++) {
				delete _Cols[i];
			}
			for (i = 0; i < _Items.size(); i++) {
				delete _Items[i];
			}
		};



		// Función para crear el ListView
		void DWLListView::Crear(DWORD Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, DWORD EstilosExtendidos) {
			int NX = cX;
			int NY = cY; 
			if (cX == DWL_CENTRADO) { NX = _CalcularCentrado(hWndParent, true, cAncho); } 
			if (cY == DWL_CENTRADO) { NY = _CalcularCentrado(hWndParent, false, cAlto); }
			_hWnd = CreateWindowEx(EstilosExtendidos, WC_LISTVIEW, NULL, Estilos, NX, NY, cAncho, cAlto, hWndParent, reinterpret_cast<HMENU>(IntToPtr(cID)), GetModuleHandle(NULL), NULL); 
			ConectarControl();
			_Fuente = (HFONT)SendMessage(_hWnd, WM_GETFONT, 0, 0); 
		};


		                          
		// Función para asignar esta clase a un ListView creado anteriormente en el editor de recursos
		HWND DWLListView::Asignar(HWND hWndParent, const int cID) { 
			_hWnd = GetDlgItem(hWndParent, cID);
			ConectarControl(); 
			_Fuente = (HFONT)SendMessage(_hWnd, WM_GETFONT, 0, 0);
			return _hWnd;
		};
		                          

		// Función para agregar un Item Debes poner tantos subitems como columnas tengas creadas menos una (la que debes crear para que se muestre el texto en report)
		void DWLListView::AgregarItem(const int Iko, const TCHAR *Txt, ...) { 
			DWLListView_Item *NDItem = new DWLListView_Item(this);
			_Items.push_back(NDItem);
			LV_ITEM LVItem;
			int     i = 0; 
			TCHAR   Text[256]; 
			va_list Marker; 
			DWLStrCopy(Text, 256, Txt); 
			LVItem.mask = LVIF_TEXT | LVIF_IMAGE; 
			LVItem.pszText = Text; 
			LVItem.cchTextMax =  static_cast<int>(DWLStrLen(Text)); 
			LVItem.iSubItem = 0; 
			LVItem.iImage = Iko; 
			LVItem.iItem = static_cast<int>(_Items.size());
			i = ListView_InsertItem(_hWnd, &LVItem); 
			va_start(Marker, Txt);
			for (unsigned int n = 0; n < _Cols.size() -1; n++) {
				DWLStrCopy(Text, 256, va_arg(Marker, const TCHAR *)); 
				ListView_SetItemText(_hWnd, i, n +1, Text); 
			} 
			va_end(Marker); 
		};
		                          

		// Función para agregar un Item Debes poner tantos subitems como columnas tengas creadas menos una (la que debes crear para que se muestre el texto en report)
		void DWLListView::AgregarItem(const int Pos, const int Iko, const TCHAR *Txt, ...) { 
			DWLListView_Item *NDItem = new DWLListView_Item(this);
			_Items.push_back(NDItem);
			LV_ITEM LVItem;
			int     i = 0; 
			TCHAR   Text[256];
			va_list Marker;
			DWLStrCopy(Text, 256, Txt); 
			LVItem.mask = LVIF_TEXT | LVIF_IMAGE; 
			LVItem.pszText = Text; 
			LVItem.cchTextMax = static_cast<int>(DWLStrLen(Text)); 
			LVItem.iSubItem = 0; 
			LVItem.iImage = Iko; 
			LVItem.iItem = Pos; 
			i = ListView_InsertItem(_hWnd, &LVItem);
			va_start(Marker, Txt); 
			for (unsigned int n = 0; n < _Cols.size(); n++) {  
				DWLStrCopy(Text, 256,va_arg(Marker, const TCHAR *));  
				ListView_SetItemText(_hWnd, i, n +1, Text); 
			} 
			va_end(Marker);
		};
		                           


		// Función para agregar un Item Debes poner tantos subitems como columnas tengas creadas menos una (la que debes crear para que se muestre el texto en report)
		void DWLListView::AgregarItem(DWLListView_Item *Itm, const int Iko, const TCHAR *Txt, ...) { 
			Itm->_AsignarNuevo(this); 
			_Items.push_back(Itm);
			LV_ITEM LVItem;
			int     i = 0; 
			TCHAR   Text[2048];
			va_list Marker;
			DWLStrCopy(Text, 2048, Txt);
			LVItem.mask = LVIF_TEXT | LVIF_IMAGE;
			LVItem.pszText = Text;
			LVItem.cchTextMax =  static_cast<int>(DWLStrLen(Text)); 
			LVItem.iSubItem = 0; 
			LVItem.iImage = Iko;
			LVItem.iItem = static_cast<int>(_Items.size());
			i = ListView_InsertItem(_hWnd, &LVItem); 
			va_start(Marker, Txt);
			for (unsigned int n = 0; n < _Cols.size() -1; n++) { 
				DWLStrCopy(Text, 2048, va_arg(Marker, const TCHAR *)); 
				ListView_SetItemText(_hWnd, i, n +1, Text);
			} 
			va_end(Marker);
		};
		                          


		// Función para agregar un Item Debes poner tantos subitems como columnas tengas creadas menos una (la que debes crear para que se muestre el texto en report)
		void DWLListView::AgregarItem(DWLListView_Item *Itm, const int Pos, const int Iko, const TCHAR *Txt, ...) { 
			Itm->_AsignarNuevo(this); 
			_Items.push_back(Itm); 
			LV_ITEM LVItem; 
			int     i = 0; 
			TCHAR   Text[256]; 
			va_list Marker; 
			DWLStrCopy(Text, 256, Txt);
			LVItem.mask = LVIF_TEXT | LVIF_IMAGE; 
			LVItem.pszText = Text;
			LVItem.cchTextMax = static_cast<int>(DWLStrLen(Text)); 
			LVItem.iSubItem = 0; 
			LVItem.iImage = Iko;
			LVItem.iItem = Pos;
			i = ListView_InsertItem(_hWnd, &LVItem);
			va_start(Marker, Txt);
			for (unsigned int n = 0; n < _Cols.size(); n++) { 
				DWLStrCopy(Text, 256, va_arg(Marker, const TCHAR *)); 
				ListView_SetItemText(_hWnd, i, n +1, Text);
			} 
			va_end(Marker); 
		};
		                          


		// Función para borrar un Item
		void DWLListView::BorrarItem(const int nItem) { 
			SendMessage(_hWnd, LVM_DELETEITEM , nItem, 0); 
			delete _Items[nItem]; 
			_Items.erase(_Items.begin() + nItem);
		};
		                          

		// Función para borrar todos los items
		void DWLListView::BorrarTodosLosItems(void) { 
			SendMessage(_hWnd, LVM_DELETEALLITEMS, 0, 0);
			for (unsigned int i = 0; i < _Items.size(); i++) {
				delete _Items[i]; 
			} 
			_Items.resize(0); 
		};
		                          


		// Función para agregar una columna
		void DWLListView::AgregarColumna(const TCHAR *Txt, const int cAncho) { 
			TCHAR    Tmp[256];
			LVCOLUMN Columna; 
			DWLStrCopy(Tmp, 256, Txt); 
			Columna.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM; 
			Columna.cx = cAncho; 
			Columna.pszText = Tmp;
			Columna.cchTextMax = static_cast<int>(DWLStrLen(Tmp));
			SendMessage(_hWnd ,LVM_INSERTCOLUMN ,0 ,(LPARAM)&Columna); 
			DWLListView_Columna *Col = new DWLListView_Columna(this); 
			_Cols.push_back(Col);
		};



		// Función para borrar una columna
		void DWLListView::BorrarColumna(const int Col) { 
			SendMessage(_hWnd, LVM_DELETECOLUMN , Col, 0);
			delete _Cols[Col]; 
			_Cols.erase(_Cols.begin() + Col); 
			for (unsigned int i = 0; i < _Items.size(); i++) { 
				_Items[i]->_ColorFondo.erase(_Items[i]->_ColorFondo.begin() + Col); 
				_Items[i]->_ColorTexto.erase(_Items[i]->_ColorTexto.begin() + Col);
				_Items[i]->_Fuente.erase(_Items[i]->_Fuente.begin() + Col);
			} 
		};


		// Función para obtener la selecion actual del listview
		const int DWLListView::Seleccion(void) {
			unsigned int S = 0; 
			for (S = 0; S < _Items.size(); S++) { 
				if (ListView_GetItemState(_hWnd, S, LVIS_SELECTED) == LVIS_SELECTED) {
					return ListView_GetSelectionMark(_hWnd); 
				} 
			}
			return -1;
		};
		                         

		                         

		// Función que deseleciona todos los items
		void DWLListView::DesSeleccionarTodo(void) { 
			for (unsigned int i = 0; i < _Items.size(); i++) {  
				ListView_SetItemState(_hWnd, i, LVIS_SELECTED, 0);
			} 
		};
		                          

		// Función que retorna un puntero a una clase DWLListView_Item
		DWLListView_Item *DWLListView::Item(const int Num) { 
			return _Items[Num];
		};
		                          

		// Función que retorna la columna especificada
		DWLListView_Columna *DWLListView::Columna(const int Num) { 
			return _Cols[Num];
		};


		// Función que retorna el numero total de items
		const int DWLListView::TotalItems(void) { 
			return static_cast<int>(_Items.size());
		};


		// Función que retorna el numero total de columnas
		const int DWLListView::TotalColumnas(void) { 
			return static_cast<int>(_Cols.size()); 
		};
		                          


		// Función que empieza la edicion de un item/subitem
		HWND DWLListView::EmpezarLabelEdit(const unsigned int eItem, const unsigned int eSubItem, const bool Numerico) {
			CancelarLabelEdit();
			_Editando = true;
			if (eItem > _Items.size() || eItem < 0 || eSubItem > _Cols.size() || eSubItem < 0) {
				return NULL; 
			}
			ListView_SetItemState(_hWnd, -1, 0, LVIS_SELECTED); 
			_eItem = eItem; 
			_eSubItem = eSubItem; 
			RECT Dim;  
			memset(&Dim, 0, sizeof(Dim)); 
			ListView_GetSubItemRect(_hWnd, eItem, eSubItem, LVIR_LABEL, &Dim); 
			long Estilos;  
			if (Numerico == false) { Estilos = WS_CHILD | ES_AUTOHSCROLL; }  
			else                   { Estilos = WS_CHILD | ES_AUTOHSCROLL | ES_NUMBER; } 
			_hWndEdit = CreateWindow(TEXT("EDIT"), _Items[eItem]->Texto(eSubItem), Estilos, Dim.left + 2, Dim.top + 2, Dim.right - (Dim.left + 2), Dim.bottom - (Dim.top + 2), _hWnd, (HMENU)555, GetModuleHandle(NULL), NULL);
			SendMessage(_hWndEdit, EM_LIMITTEXT, 0, 0); // Buffer al maximo para el texto
			SetWindowLongPtr(_hWndEdit, GWL_USERDATA, PtrToLong(this));
			SendMessage(_hWndEdit, EM_SETSEL, 0, DWLStrLen(_Items[eItem]->Texto(eSubItem)));
			_Items[eItem]->Fuente(eSubItem);
			SendMessage(_hWndEdit, WM_SETFONT, (WPARAM)_Items[eItem]->Fuente(eSubItem), 0); 

//			_GestorMensajesOriginal = reinterpret_cast<WNDPROC>(LongToPtr(SetWindowLongPtr(_hWnd, GWLP_WNDPROC, PtrToLong(_GestorMensajes))));

			_GestorMensajesOriginalEdit = (WNDPROC)LongToPtr(SetWindowLongPtr(_hWndEdit, GWL_WNDPROC, PtrToLong(_GestorMensajesEdit))); 
			_BrochaFondoEdit = CreateSolidBrush(Item(_eItem)->ColorFondo(_eSubItem)); 
			ShowWindow (_hWndEdit, SW_SHOWNORMAL); 
			UpdateWindow(_hWndEdit);  
			SetFocus(_hWndEdit); 

			PostMessage(GetParent(_hWnd), DWL_LISTVIEW_LABELEDIT_INICIO, MAKEWPARAM(eItem, eSubItem), (LPARAM)ID());

			
			return _hWndEdit; 
		}
		                          


		// Función que termina la edicion de un item/subitem
		void DWLListView::TerminarLabelEdit(void) { 
			if (_hWndEdit != NULL && _Editando == true) { 
				TCHAR Txt[512];
				GetDlgItemText(GetParent(_hWndEdit), GetWindowLongPtr(_hWndEdit, GWL_ID), Txt, 512);
		/*		LVITEM T;  
				T.iItem = _eItem; 
				T.iSubItem = _eSubItem; 
				T.mask = LVIF_INDENT | LVIF_STATE; 
				ListView_GetItem(_hWnd, &T); 
				NMLVDISPINFO Nfo;  	
				Nfo.hdr.code = LVN_ENDLABELEDIT; 
				Nfo.hdr.idFrom = ID(); 	
				Nfo.hdr.hwndFrom = _hWnd;
				Nfo.item = T;*/

				//SendMessage(GetParent(_hWnd), WM_NOTIFY, 0, (LPARAM)&Nfo);
				DWLListView_TerminarLabelEdit LabelEditP(_Items[_eItem], _eItem, _eSubItem, Txt);

		//		SendMessage(GetParent(_hWnd), DWL_LISTVIEW_LABELEDIT_FIN, MAKEWPARAM(_eItem, _eSubItem), static_cast<int>(ID()));
				SendMessage(GetParent(_hWnd), DWL_LISTVIEW_LABELEDIT_FIN, reinterpret_cast<WPARAM>(&LabelEditP), static_cast<int>(ID()));
				RECT Dim = { 0, 0, 0, 0 }; 
				ListView_GetSubItemRect(_hWnd, _eItem, _eSubItem, LVIR_LABEL, &Dim); 
				InvalidateRect(_hWnd, &Dim, false);  
				ListView_SetItemState(_hWnd, _eItem, 0, LVIS_SELECTED);
				// Si no se cancela cambio el texto
				if (LabelEditP.Cancelar == false) _Items[_eItem]->Texto(_eSubItem, LabelEditP.NuevoTexto()); 	 
				
				_Editando = false; 
					
				DestroyWindow(_hWndEdit);	
				DeleteObject(_BrochaFondoEdit);	

			} 
		};
		                          


		// Función que cancela la edicion de un item/subitem
		void DWLListView::CancelarLabelEdit(void) { 
			if (_hWndEdit != NULL && _Editando == true) {
				_Editando = false;  
				ListView_SetItemState(_hWnd, _eItem, 0, LVIS_SELECTED);
		/*		LVITEM T;  
				T.iItem = _eItem; 
				T.iSubItem = _eSubItem;  
				T.mask = LVIF_INDENT | LVIF_STATE;
				ListView_GetItem(_hWnd, &T);   
				NMLVDISPINFO Nfo;  
				Nfo.hdr.code = LVN_ENDLABELEDIT;  
				Nfo.hdr.idFrom = ID(); 
				Nfo.hdr.hwndFrom = _hWnd;  Nfo.item = T; */

				PostMessage(GetParent(_hWnd), DWL_LISTVIEW_LABELEDIT_CANCELADO, MAKEWPARAM(_eItem, _eSubItem), static_cast<int>(ID()));
				DestroyWindow(_hWndEdit);
				DeleteObject(_BrochaFondoEdit);	

			} 
		};
		                          




		// Función que retorna el item que hay debajo del mouse
		const int DWLListView::ItemHitTest(void) {
			int   HT = -1;
			RECT  R;
			POINT Pt;
			GetCursorPos(&Pt);
			RECT RV;
			GetWindowRect(_hWnd, &RV); 
			Pt.x -= RV.left;
			Pt.y -= RV.top;
			LVHITTESTINFO   LInfo;
			LInfo.pt = Pt;
			LInfo.flags = LVHT_ABOVE | LVHT_TOLEFT;
		//	LInfo.iSubItem = 0;
			HT = ListView_HitTest(_hWnd, &LInfo);
			ListView_GetItemRect(_hWnd, HT, &R, LVIR_BOUNDS);
			if (PtInRect(&R, Pt) != 0) { return HT; }
			else                       { return -1; } 
		};


		// Función que retorna el item que hay debajo del mouse
		const int DWLListView::ItemHitTest(const int cX, const int cY) {
			int				HT = -1;
			RECT			R;
			POINT			Pt;
			LVHITTESTINFO   LInfo;
			Pt.x = cX;
			Pt.y = cY;
			LInfo.pt = Pt;
			LInfo.flags = LVHT_ABOVE | LVHT_TOLEFT;
		//	LInfo.iSubItem = 0;
			HT = ListView_HitTest(_hWnd, &LInfo);
			ListView_GetItemRect(_hWnd, HT, &R, LVIR_BOUNDS);
			if (PtInRect(&R, Pt) != 0) { return HT; }
			else                       { return -1; } 
		};

		// Función que retorna el item que hay debajo del mouse
		const int DWLListView::SubItemHitTest(void) {
			int				HT = -1;
			RECT			R;
			POINT			Pt;
			LVHITTESTINFO   LInfo;
			GetCursorPos(&Pt);
			RECT RV;
			GetWindowRect(_hWnd, &RV); 
			Pt.x -= RV.left;
			Pt.y -= RV.top;
			LInfo.pt = Pt;
			LInfo.flags = LVHT_ABOVE | LVHT_TOLEFT;
			LInfo.iSubItem = 0;
			HT = ListView_SubItemHitTest(_hWnd, &LInfo);
			ListView_GetSubItemRect(_hWnd, HT, LInfo.iSubItem, LVIR_BOUNDS, &R);
			if (PtInRect(&R, Pt) != 0) { return LInfo.iSubItem; }
			else                       { return -1; } 
		};


		// Función que retorna el item que hay debajo del mouse
		const int DWLListView::SubItemHitTest(const int cX, const int cY) {
			int				HT = -1;
			RECT			R;
			POINT			Pt;
			LVHITTESTINFO   LInfo;
			Pt.x = cX;
			Pt.y = cY;
			LInfo.pt = Pt;
			LInfo.flags = LVHT_ABOVE | LVHT_TOLEFT;
		//	LInfo.iSubItem = 0;
			HT = ListView_SubItemHitTest(_hWnd, &LInfo);
			ListView_GetSubItemRect(_hWnd, HT, LInfo.iSubItem, LVIR_BOUNDS, &R);
			if (PtInRect(&R, Pt) != 0) { return LInfo.iSubItem; }
			else                       { return -1; } 
		};


		// Notificaciones de pintado
		LRESULT DWLListView::Evento_Pintar_InicioItem(LPNMLVCUSTOMDRAW lplvcd) {
		//	SetBkMode(lplvcd->nmcd.hdc, TRANSPARENT);
			lplvcd->clrTextBk = _Items[lplvcd->nmcd.dwItemSpec]->_ColorFondo[lplvcd->iSubItem];
			lplvcd->clrText   = _Items[lplvcd->nmcd.dwItemSpec]->_ColorTexto[lplvcd->iSubItem]; 
			return CDRF_NEWFONT; 
		};


		LRESULT DWLListView::Evento_Pintar_InicioItemSeleccionado(LPNMLVCUSTOMDRAW lplvcd) { 
		//	SetBkMode(lplvcd->nmcd.hdc, TRANSPARENT);
		//	lplvcd->clrTextBk = _Items[lplvcd->nmcd.dwItemSpec]->_ColorFondo[lplvcd->iSubItem];
		//	lplvcd->clrText   = _Items[lplvcd->nmcd.dwItemSpec]->_ColorTexto[lplvcd->iSubItem]; 
			lplvcd->clrTextBk = _ColorSeleccion;
			lplvcd->clrText   = _ColorSeleccionTexto;
			return CDRF_NEWFONT; 
		};


		LRESULT DWLListView::Evento_Pintar_FinItem(LPNMLVCUSTOMDRAW lplvcd)  { 
			return CDRF_DODEFAULT; 
		};


		LRESULT DWLListView::Evento_Pintar_FinItemSeleccionado(LPNMLVCUSTOMDRAW lplvcd) {
			return CDRF_DODEFAULT; 
		};



		// Nuevo WindowProcedure para el ListView
		LRESULT CALLBACK DWLListView::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
			switch (uMsg) {
				case WM_LBUTTONDOWN : // Se pilla cuando se presiona porque al estar soltado no se capta bien el mensaje WM_LBUTTONUP por alguna razon ajena a mi.... grrrr
					PostMessage(GetParent(_hWnd), DWL_LISTVIEW_CLICK_IZQUIERDO, (WPARAM)ID(), lParam);
					break; 
				case WM_RBUTTONDOWN : 
					PostMessage(GetParent(_hWnd), DWL_LISTVIEW_CLICK_DERECHO, (WPARAM)ID(), lParam);
					break; 
				case WM_MBUTTONDOWN : 
					PostMessage(GetParent(_hWnd), DWL_LISTVIEW_CLICK_MEDIO, (WPARAM)ID(), lParam);
					break; 
				case WM_LBUTTONDBLCLK : 
					PostMessage(GetParent(_hWnd), DWL_LISTVIEW_DOBLECLICK_IZQUIERDO, (WPARAM)ID(), lParam);
					break; 
				case WM_RBUTTONDBLCLK : 
					PostMessage(GetParent(_hWnd), DWL_LISTVIEW_DOBLECLICK_DERECHO, (WPARAM)ID(), lParam);
					break; 
				case WM_MBUTTONDBLCLK : 
					PostMessage(GetParent(_hWnd), DWL_LISTVIEW_DOBLECLICK_MEDIO, (WPARAM)ID(), lParam);
					break; 
				case WM_KEYDOWN :
					PostMessage(GetParent(_hWnd), DWL_LISTVIEW_TECLADO_PRESIONADO, wParam, (LPARAM)ID());
					break; 
				case WM_KEYUP :
					PostMessage(GetParent(_hWnd), DWL_LISTVIEW_TECLADO_SOLTADO, wParam, (LPARAM)ID());
					if (wParam == 13) PostMessage(GetParent(_hWnd), DWL_LISTVIEW_TECLADO_INTRO, wParam, (LPARAM)ID());  
					break; 
				case WM_SETFOCUS :
					CancelarLabelEdit();  
					PostMessage(GetParent(_hWnd), DWL_LISTVIEW_FOCO_OBTENIDO, ID(), 0); 
					break;
				case WM_KILLFOCUS :
					PostMessage(GetParent(_hWnd), DWL_LISTVIEW_FOCO_PERDIDO, ID(), 0); 
					break;
				case DWL_CUSTOM_DRAW : 
					return _CustomDraw(lParam); 
					break; 
				case WM_CTLCOLOREDIT : 
					return SendMessage((HWND)lParam, uMsg, wParam, 0);  
					break; 
				case LVM_EDITLABEL :
					return (LRESULT)EmpezarLabelEdit((int)wParam, (int)lParam); 
					break;
				case WM_NOTIFY : 
					switch (((LPNMHDR)lParam)->code) { 
						case NM_KEYDOWN : 
							switch(((LPNMKEY)lParam)->nVKey) { 
								case VK_RETURN : 
									TerminarLabelEdit();	
									break; 
								case VK_ESCAPE : 
									CancelarLabelEdit();	
									break; 
							}	
							break;
						case NM_KILLFOCUS : 
							CancelarLabelEdit();
							break; 
					}  
					break;
			} 
			return DWLControl::GestorMensajes(uMsg, wParam, lParam);
		};




		// Función que se encarga de especificar los colores y la Fuente del ListView para cada item
		LRESULT DWLListView::_CustomDraw(LPARAM Datos) { 
			LPNMLVCUSTOMDRAW  lplvcd = (LPNMLVCUSTOMDRAW)Datos; 
			switch(lplvcd->nmcd.dwDrawStage) { 
				 case CDDS_PREPAINT :  
				 case CDDS_POSTPAINT : 
					 return (CDRF_NOTIFYPOSTPAINT | CDRF_NOTIFYITEMDRAW | CDRF_NOTIFYSUBITEMDRAW); 
				 case CDDS_ITEMPREPAINT : 
					 return (CDRF_NOTIFYPOSTPAINT | CDRF_NOTIFYITEMDRAW | CDRF_NOTIFYSUBITEMDRAW); 
				 case (CDDS_SUBITEM | CDDS_ITEMPREPAINT) :
					 if (_Items[lplvcd->nmcd.dwItemSpec]->Fuente(lplvcd->iSubItem) != NULL) { 
						 SelectObject(lplvcd->nmcd.hdc, _Items[lplvcd->nmcd.dwItemSpec]->_Fuente[lplvcd->iSubItem]);
					 }  
					 else {
						 SelectObject(lplvcd->nmcd.hdc, _Fuente); 
					 }  
					 if ((LVIS_SELECTED ^ ListView_GetItemState(_hWnd, lplvcd->nmcd.dwItemSpec, LVIS_SELECTED)) != false) { 
						 return Evento_Pintar_InicioItem(lplvcd);  
					 }   
					 else {  
						 return Evento_Pintar_InicioItemSeleccionado(lplvcd); 
					 }   break; 
				 case CDDS_ITEMPOSTPAINT :
					 if ((LVIS_SELECTED ^ ListView_GetItemState(_hWnd, lplvcd->nmcd.dwItemSpec, LVIS_SELECTED)) != false) { 
						 return Evento_Pintar_FinItem(lplvcd);  
					 } 
					 else {   
						 return Evento_Pintar_FinItemSeleccionado(lplvcd);   
					 }   break;
			} 
			return 0;
		}; 




		// WindowProcedure que usara el Editbox en lka Función editlabel
		LRESULT CALLBACK DWLListView::_GestorMensajesEdit(HWND dhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { 
			DWLListView *This = reinterpret_cast<DWLListView *>(LongToPtr(GetWindowLongPtr(dhWnd, GWL_USERDATA)));  
			NMHDR T; 
			T.hwndFrom = dhWnd;
			T.idFrom = GetWindowLongPtr(dhWnd, GWL_ID); 
			switch (uMsg) {  
				case WM_CTLCOLOREDIT : 
				case WM_CTLCOLORSTATIC : 
					//This->Item(This->_eItem)->ColorFondo(This->_eSubItem);
					SetTextColor((HDC)wParam, This->Item(This->_eItem)->ColorTexto(This->_eSubItem));
					SetBkColor((HDC)wParam, This->Item(This->_eItem)->ColorFondo(This->_eSubItem));
					SetBkMode((HDC)wParam, TRANSPARENT);	
					return (LRESULT)This->_BrochaFondoEdit; 
				case WM_LBUTTONUP : 	 
					T.code = NM_CLICK; 	
					This->GestorMensajes(WM_NOTIFY, 0, reinterpret_cast<WPARAM>(&T));
		//			PostMessage(GetParent(dhWnd), WM_NOTIFY, 0, reinterpret_cast<WPARAM>(&T));  
					break;   
				case WM_RBUTTONUP : 
					T.code = NM_RCLICK; 	
					This->GestorMensajes(WM_NOTIFY, 0, reinterpret_cast<WPARAM>(&T));
		//			PostMessage(GetParent(dhWnd), WM_NOTIFY, 0, reinterpret_cast<WPARAM>(&T));
					break; 		
				case WM_LBUTTONDBLCLK : 
					T.code = NM_DBLCLK; 
					This->GestorMensajes(WM_NOTIFY, 0, reinterpret_cast<WPARAM>(&T));
		//			PostMessage(GetParent(dhWnd), WM_NOTIFY, 0, reinterpret_cast<WPARAM>(&T)); 	
					break; 
				case WM_CHAR : 
					NMKEY Key;	
					T.code = NM_KEYDOWN;
					Key.hdr = T;	
					Key.nVKey = (unsigned int)wParam;
					Key.uFlags = (unsigned int)lParam; 
		//			SendMessage(GetParent(dhWnd), WM_NOTIFY, 0, reinterpret_cast<WPARAM>(&Key));
					This->GestorMensajes(WM_NOTIFY, 0, reinterpret_cast<WPARAM>(&Key));
		/*			if (wParam == 13) {   		
						T.code = NM_RETURN;  	
		//				SendMessage(GetParent(dhWnd), WM_NOTIFY, 0, reinterpret_cast<WPARAM>(&T));  
						This->GestorMensajes(WM_NOTIFY, 0, reinterpret_cast<WPARAM>(&T));
					}	 */
					break;
									
			} 
			return CallWindowProc(This->_GestorMensajesOriginalEdit, dhWnd, uMsg, wParam, lParam);
		};






























		DWLListView_Item::DWLListView_Item(void) { 
			_LV = NULL;
		}


		DWLListView_Item::DWLListView_Item(DWLListView *LV) {
			_LV = LV; 
			for (unsigned int i = 0; i <= _LV->_Cols.size(); i++) { 
				_Fuente.push_back(_LV->Fuente());  
				_ColorFondo.push_back(_LV->ColorFondo());
				_ColorTexto.push_back(_LV->ColorTexto());
			}
		}



		void DWLListView_Item::_AsignarNuevo(DWLListView *LV) {
			_LV = LV;
			for (unsigned int i = 0; i <= _LV->_Cols.size(); i++) {
				_Fuente.push_back(_LV->Fuente());
				_ColorFondo.push_back(_LV->ColorFondo());
				_ColorTexto.push_back(_LV->ColorTexto()); 
			}
		}


		void DWLListView_Item::Texto(const int SubItem, const TCHAR *Txt) {
			TCHAR   Text[256]; 
			LV_ITEM LVItem; 
			unsigned int i;
			DWLStrCopy(Text, 256, Txt);
			LVItem.mask = LVIF_TEXT;
			LVItem.pszText = Text;
			LVItem.cchTextMax = static_cast<int>(DWLStrLen(Text)); 
			LVItem.iSubItem = SubItem; 
			for (i = 0; i < _LV->_Items.size(); i++) { 
				if (_LV->_Items[i] == this) {
					break; 
				} 
			}
			LVItem.iItem = static_cast<int>(i);
			SendMessage(_LV->_hWnd, LVM_SETITEM, 0, (LPARAM)&LVItem);
		}


		const TCHAR *DWLListView_Item::Texto(const int SubItem) {
			TCHAR    Text[256];
			unsigned int i;
			LV_ITEM LVItem; 
			LVItem.mask = LVIF_TEXT;
			LVItem.pszText = Text; 
			LVItem.cchTextMax = 256; 
			LVItem.iSubItem = SubItem;
			for (i = 0; i < _LV->_Items.size(); i++) {
				if (_LV->_Items[i] == this) { 
					break; 
				} 
			}
			LVItem.iItem = static_cast<int>(i);
			SendMessage(_LV->_hWnd, LVM_GETITEM, 0, (LPARAM)&LVItem); 
			_LV->_TmpStr = Text;
			return _LV->_TmpStr();
		}


		void DWLListView_Item::Icono(const int nIko) { 
			LVITEM LVItem; 
			LVItem.mask = LVIF_IMAGE;
			unsigned int i;
			for (i = 0; i < _LV->_Items.size(); i++) {
				if (_LV->_Items[i] == this) { break; } 
			} 
			LVItem.iSubItem = 0; 
			LVItem.iItem = static_cast<int>(i);
			LVItem.iImage = nIko;
			ListView_SetItem(_LV->_hWnd, &LVItem);
		}


		const int DWLListView_Item::Icono(void) { 
			LV_ITEM LVItem; 
			unsigned int i;
			LVItem.mask = LVIF_IMAGE;
			for (i = 0; i < _LV->_Items.size(); i++) {
				if (_LV->_Items[i] == this) { break; } 
			} 
			LVItem.iItem = static_cast<int>(i);
			ListView_GetItem(_LV->_hWnd, &LVItem);
			return LVItem.iImage; 
		}


		HFONT DWLListView_Item::Fuente(const unsigned int SubItem) { 
			return _Fuente[SubItem];
		}


		void DWLListView_Item::Fuente(const unsigned int SubItem, HFONT nFuente) { 
			_Fuente[SubItem] = nFuente; 
		}


		void DWLListView_Item::ColorTexto(const int SubItem, COLORREF nColor) {
			_ColorTexto[SubItem] = nColor; 
		}


		COLORREF DWLListView_Item::ColorTexto(const int SubItem) { 
			return _ColorTexto[SubItem];
		}


		void DWLListView_Item::ColorFondo(const int SubItem, COLORREF nColor) {
			_ColorFondo[SubItem] = nColor; 
		}


		COLORREF DWLListView_Item::ColorFondo(const int SubItem) { 
			return _ColorFondo[SubItem];
		}


		void DWLListView_Item::Seleccionado(const bool Sel) { 
			unsigned int i;
			for (i = 0; i < _LV->_Items.size(); i++) {
				if (_LV->_Items[i] == this) {   break;  } 
			} 
			if (Sel == true) { ListView_SetItemState(_LV->_hWnd, i, LVIS_SELECTED, LVIS_SELECTED); } 
			else             { ListView_SetItemState(_LV->_hWnd, i, LVIS_SELECTED, 0); } 
		}


		const bool DWLListView_Item::Seleccionado(void) { 
			unsigned int i;
			for (i = 0; i < _LV->_Items.size(); i++) { 
				if (_LV->_Items[i] == this) {   break;  } 
			} 
			if ((ListView_GetItemState(_LV->_hWnd, i, LVIS_SELECTED) == LVIS_SELECTED)) { return true; } 
			else                                                                        { return false; }
		}


		void DWLListView_Item::HacerVisible(void) { 
			unsigned int i;
			for (i = 0; i < _LV->_Items.size(); i++) {
				if (_LV->_Items[i] == this) {   break;  } 
			} 
			ListView_EnsureVisible(_LV->_hWnd, i, false); 
		}

















		DWLListView_Columna::DWLListView_Columna(DWLListView *LV) {
			_LV = LV;
		}


		void DWLListView_Columna::Texto(const TCHAR *Txt) {
			LVCOLUMN Columna;
			TCHAR    Tmp[256];
			DWLStrCopy(Tmp, 256, Txt); 
			Columna.mask = LVCF_TEXT;
			Columna.pszText = Tmp; 
			Columna.cchTextMax = 256; 
			unsigned int i;
			for (i = 0; i < _LV->_Cols.size(); i++) { 
				if (_LV->_Cols[i] == this) {   break;  }
			} 
			Columna.iSubItem = i; 
			SendMessage(_LV->_hWnd ,LVM_SETCOLUMN ,0 ,(LPARAM)&Columna); 
		}


		const TCHAR *DWLListView_Columna::Texto(void) { 
			LVCOLUMN Columna; 
			TCHAR    Tmp[256]; 
			Columna.mask = LVCF_TEXT;
			Columna.pszText = Tmp;
			Columna.cchTextMax = 256;
			unsigned int i;
			for (i = 0; i < _LV->_Cols.size(); i++) { 
				if (_LV->_Cols[i] == this) {   break;  }
			} 
			Columna.iSubItem = i; 
			SendMessage(_LV->_hWnd, LVM_GETCOLUMN, 0, (LPARAM)&Columna); 
			_LV->_TmpStr = Columna.pszText; 
			return _LV->_TmpStr(); 
		}


		void DWLListView_Columna::Ancho(const int nAncho) {
			LVCOLUMN Columna; 
			Columna.mask = LVCF_WIDTH; 
			unsigned int i;
			for (i = 0; i < _LV->_Cols.size(); i++) {
				if (_LV->_Cols[i] == this) {   break;  } 
			} 
			Columna.iSubItem = i; 
			Columna.cx = nAncho; 
			SendMessage(_LV->_hWnd ,LVM_SETCOLUMN ,0 ,(LPARAM)&Columna);
		}


		const int DWLListView_Columna::Ancho(void) { 
			LVCOLUMN Columna; 
			Columna.mask = LVCF_WIDTH; 
			unsigned int i;
			for (i = 0; i < _LV->_Cols.size(); i++) { 
				if (_LV->_Cols[i] == this) {   break;  }
			} 
			Columna.iSubItem = i;
			SendMessage(_LV->_hWnd ,LVM_GETCOLUMN ,0 ,(LPARAM)&Columna); 
			return Columna.cx; 
		}



	}
}
