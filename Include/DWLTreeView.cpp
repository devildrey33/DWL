/*! \file DWLTreeView.cpp
	\brief		Archivo que contiene funciones para la utilización de un treeview en windows.


	\details	Clase diseñada para poder controlar un treeview de windows.																		\n
				Esta clase en breve no formara parte del proyecto y por lo tanto no recibira actualizaciones.											\n
				Si quieres utilizar un control del estilo del edit box con la DWL se recomienda usar DWLArbolEx.										\n
				Para la version 1.0 de la DWL esta clase probablemente desaparecera.																	\n

																																						\n
	\author		devildrey33
	\version	0.95
	\date		24/07/2005

	\remarks
				Archivo creado por devildrey33 el dia [29/03/2004] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n	
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n	
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n	

*/ 
#include "DWLTreeView.h"
#include <WinUser.h>

namespace DWL {
	namespace Controles {

		// Constructor.
		DWLTreeView::DWLTreeView(void) {
			INITCOMMONCONTROLSEX Comm;
			Comm.dwSize = sizeof(INITCOMMONCONTROLSEX);
			Comm.dwICC = ICC_TREEVIEW_CLASSES;
			InitCommonControlsEx(&Comm);
			_ColorSeleccion = GetSysColor(COLOR_HIGHLIGHT); 
			_ColorSeleccionTexto = GetSysColor(COLOR_HIGHLIGHTTEXT); 
		}



		// Destructor.
		DWLTreeView::~DWLTreeView(void) {
			for (unsigned int i = 0; i < _Nodos.size(); i++) { 
				delete _Nodos[i]; 
			} 
		};



		// Función para crear el TreeView.
		void DWLTreeView::Crear(DWORD Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, DWORD EstilosExtendidos) {
			int NX = cX; 
			int NY = cY; 
			if (cX == DWL_CENTRADO) NX = _CalcularCentrado(hWndParent, true, cAncho); 
			if (cY == DWL_CENTRADO) NY = _CalcularCentrado(hWndParent, false, cAlto); 
			_hWnd = CreateWindowEx(EstilosExtendidos, WC_TREEVIEW, NULL, Estilos, NX, NY, cAncho, cAlto, hWndParent, reinterpret_cast<HMENU>(IntToPtr(cID)), GetModuleHandle(NULL), NULL);
			ConectarControl(); 
			_Fuente = (HFONT)SendMessage(_hWnd, WM_GETFONT, 0, 0); 
			ColorFondo(GetSysColor(COLOR_WINDOW)); 
			ColorTexto(GetSysColor(COLOR_WINDOWTEXT)); 
		};




		// Función para asignar esta clase a un TreeView creado anteriormente en el editor de recursos.
		void DWLTreeView::Asignar(HWND hWndParent, const int cID) { 
			_hWnd = GetDlgItem(hWndParent, cID); 
			ConectarControl(); 
			_Fuente = (HFONT)SendMessage(_hWnd, WM_GETFONT, 0, 0); 
		};




		// Funciónes para Agregar un Nodo partiendo de una clase derivada de DWLTreeView_Nodo.
		HTREEITEM DWLTreeView::AgregarNodo(DWLTreeView_Nodo *nNodo, HTREEITEM Parent, const TCHAR *cTexto, const int cIko, HTREEITEM InsertarDespuesDe) {
			TVINSERTSTRUCT ITS; 
			TVITEM         Item;
			TCHAR          Tmp[128];
			DWLStrCopy(Tmp, 128, cTexto);
			Item.pszText = Tmp;
			Item.cchTextMax = static_cast<int>(DWLStrLen(Tmp));
			Item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN;
			Item.state = TVIS_SELECTED;
			Item.stateMask = TVIS_SELECTED; 
			Item.iImage = cIko; Item.iSelectedImage = cIko; 
			Item.cChildren = 0; 
			ITS.hInsertAfter = InsertarDespuesDe;
			ITS.item = Item; 
			ITS.hParent = Parent;
			nNodo->_AsignarBase(this, TreeView_InsertItem(_hWnd, &ITS));
			_Nodos.push_back(nNodo);
			if (Parent != NULL) {
				_SetChildren(Parent, true);
			}
			return nNodo->hTreeItem(); 
		};




		HTREEITEM DWLTreeView::AgregarNodo(DWLTreeView_Nodo *nNodo, HTREEITEM Parent, const TCHAR *cTexto, const int cIko, COLORREF nColorTexto, COLORREF nColorFondo, HTREEITEM InsertarDespuesDe) {
			TVINSERTSTRUCT ITS; 
			TVITEM         Item; 
			TCHAR          Tmp[128];
			DWLStrCopy(Tmp, 128, cTexto); 
			Item.pszText = Tmp; 
			Item.cchTextMax = static_cast<int>(DWLStrLen(Tmp));
			Item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN; 
			Item.state = TVIS_SELECTED; 
			Item.stateMask = TVIS_SELECTED; 
			Item.iImage = cIko;
			Item.iSelectedImage = cIko;
			Item.cChildren = 0;
			ITS.hInsertAfter = InsertarDespuesDe; 
			ITS.item = Item; 
			ITS.hParent = Parent; 
			nNodo->_AsignarBase(this, TreeView_InsertItem(_hWnd, &ITS), nColorFondo, nColorTexto); 
			_Nodos.push_back(nNodo); 
			if (Parent != NULL) { 
				_SetChildren(Parent, true);
			} 
			return nNodo->hTreeItem(); 
		};



		// Funciónes para Agregar un Nodo normal.
		HTREEITEM DWLTreeView::AgregarNodo(HTREEITEM Parent, const TCHAR *cTexto, const int cIko, HTREEITEM InsertarDespuesDe) {
			TVINSERTSTRUCT ITS; 
			TVITEM         Item;
			TCHAR          Tmp[128];
			DWLStrCopy(Tmp, 128, cTexto); 
			Item.pszText = Tmp; 
			Item.cchTextMax = static_cast<int>(DWLStrLen(Tmp));
			Item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN; 
			Item.state = TVIS_SELECTED;
			Item.stateMask = TVIS_SELECTED; 
			Item.iImage = cIko; 
			Item.iSelectedImage = cIko; 
			Item.cChildren = 0; 
			ITS.hInsertAfter = InsertarDespuesDe; 
			ITS.item = Item; 
			ITS.hParent = Parent; 
			DWLTreeView_Nodo *nNodo = new DWLTreeView_Nodo(this, TreeView_InsertItem(_hWnd, &ITS));
			_Nodos.push_back(nNodo); 
			if (Parent != NULL) {
				_SetChildren(Parent, true); 
			} 
			return nNodo->hTreeItem(); 
		};




		HTREEITEM DWLTreeView::AgregarNodo(HTREEITEM Parent, const TCHAR *cTexto, const int cIko, COLORREF nColorTexto, COLORREF nColorFondo, HTREEITEM InsertarDespuesDe) { 
			TVINSERTSTRUCT ITS; 
			TVITEM         Item;
			TCHAR          Tmp[128];
			DWLStrCopy(Tmp, 128, cTexto); 
			Item.pszText = Tmp;
			Item.cchTextMax = static_cast<int>(DWLStrLen(Tmp)); 
			Item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN; 
			Item.state = TVIS_SELECTED; Item.stateMask = TVIS_SELECTED; 
			Item.iImage = cIko;
			Item.iSelectedImage = cIko; 
			Item.cChildren = 0;
			ITS.hInsertAfter = InsertarDespuesDe; 
			ITS.item = Item; 
			ITS.hParent = Parent; 
			DWLTreeView_Nodo *nNodo = new DWLTreeView_Nodo(this, TreeView_InsertItem(_hWnd, &ITS), nColorFondo, nColorTexto);
			_Nodos.push_back(nNodo); 
			if (Parent != NULL) { 
				_SetChildren(Parent, true); 
			} 
			return nNodo->hTreeItem(); 
		};



		// Funciónes para Borrar Nodos.
		void DWLTreeView::BorrarNodo(HTREEITEM BNodo) {
			if (BNodo == NULL) {
				return;
			} 
			for (unsigned int i = 0; i < _Nodos.size(); i++) {
				if (_Nodos[i]->_Nodo == BNodo) {
					BorrarNodo(i);
					break;
				}
			}
		};




		void DWLTreeView::BorrarNodo(const unsigned int Pos) {
			HTREEITEM		NB   = _Nodos[Pos]->_Nodo;
			HTREEITEM		Hijo = TreeView_GetChild(_hWnd, NB);
			unsigned int	j;
			unsigned int	i;
			while (Hijo != NULL) { 
				for (j = 0; j < _Nodos.size(); j++) { 
					if (_Nodos[j]->_Nodo == Hijo) {
						break;
					}
				}  
				BorrarNodo(j);  
				Hijo = TreeView_GetChild(_hWnd, NB);
			}
			for (i = 0; i < _Nodos.size(); i++) { 
				if (_Nodos[i]->_Nodo == NB) {
					break;
				}
			}
			TreeView_DeleteItem(_hWnd, _Nodos[i]->_Nodo);
			delete _Nodos[i]; 
			_Nodos.erase(_Nodos.begin() + i); 
		};





		void DWLTreeView::BorrarTodo(void) {
			TreeView_DeleteAllItems(_hWnd);
			for (unsigned int i = 0; i < _Nodos.size(); i++) {
				delete _Nodos[i];
			}
			_Nodos.clear(); 
		};




		// Función que retorna un puntero DWLTreeView_Nodo partiendo de la ID Unica especificada.
		DWLTreeView_Nodo *DWLTreeView::BuscarNodo(HTREEITEM BNodo) {
			 for (unsigned int i = 0; i < _Nodos.size(); i ++) {
				 if (_Nodos[i]->_Nodo == BNodo) {
					 return _Nodos[i];  
				 }
			 } 
			 return NULL; 
		};





		 // Función para obtener la ID Unica del Nodo que esta en las coordenadas especificadas.
		HTREEITEM DWLTreeView::HitTest(const int cX, const int cY) {
			 TVHITTESTINFO ht; 
			 POINT         hitPt = { cX, cY };
			 ht.pt = hitPt; 
			 SendMessage(_hWnd, TVM_HITTEST, 0, (LPARAM)(LPTVHITTESTINFO) &ht); 
			 return ht.hItem; 
		};





		HTREEITEM DWLTreeView::HitTest(void) {
			 TVHITTESTINFO ht; 
			 RECT          Rect; 
			 POINT         hitPt; 
			 GetCursorPos(&hitPt);
			 RECT RV;
			 GetWindowRect(_hWnd, &RV);
			 hitPt.x -= RV.left;
			 hitPt.y -= RV.top; 
			 ht.pt = hitPt;
			 SendMessage(_hWnd, TVM_HITTEST, 0, (LPARAM)(LPTVHITTESTINFO) &ht); 
			 TreeView_GetItemRect(_hWnd, ht.hItem, &Rect, TRUE);
			 if (PtInRect(&Rect, hitPt) != 0) { 
				 return ht.hItem;
			 }
			 return NULL;
		};




		 // Esta Función usa las coordenadas en que esta situado el mouse
		 // Función que retorna el Nodo especificado en forma de Clase DWLTreeView_Nodo. 
		DWLTreeView_Nodo *DWLTreeView::Nodo(const unsigned int Pos) {
			return _Nodos[Pos];
		};


		/*
		// Función para convertir los scrollbars en flatscrollbars
		void DWLTreeView::FlatScrollBar(const bool FSB) { 
			 if (FSB == true) {	 ListView_SetExtendedListViewStyleEx(_hWnd, LVS_EX_FLATSB, LVS_EX_FLATSB); } 
			 else             { ListView_SetExtendedListViewStyleEx(_hWnd, LVS_EX_FLATSB, 0); } 
		};*/
		 



		LRESULT CALLBACK DWLTreeView::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
			switch (uMsg) {  
				case DWL_CUSTOM_DRAW : 
					return _CustomDraw(lParam);
					break;  
				case WM_LBUTTONUP : 
					PostMessage(GetParent(_hWnd), DWL_TREEVIEW_CLICK_IZQUIERDO, ID(), lParam);
					break; 
				case WM_RBUTTONDOWN : 
					PostMessage(GetParent(_hWnd), DWL_TREEVIEW_CLICK_DERECHO, ID(), lParam);
					break; 
				case WM_MBUTTONUP : 
					PostMessage(GetParent(_hWnd), DWL_TREEVIEW_CLICK_MEDIO, ID(), lParam);
					break; 
				case WM_LBUTTONDBLCLK : 
					PostMessage(GetParent(_hWnd), DWL_TREEVIEW_DOBLECLICK_IZQUIERDO, ID(), lParam);
					break; 
				case WM_RBUTTONDBLCLK : 
					PostMessage(GetParent(_hWnd), DWL_TREEVIEW_DOBLECLICK_DERECHO, ID(), lParam);
					break; 
				case WM_MBUTTONDBLCLK : 
					PostMessage(GetParent(_hWnd), DWL_TREEVIEW_DOBLECLICK_MEDIO, ID(), lParam);
					break; 
				case WM_KEYDOWN :
					PostMessage(GetParent(_hWnd), DWL_TREEVIEW_TECLADO_PRESIONADO, wParam, (LPARAM)ID()); 
					break; 
				case WM_KEYUP :
					PostMessage(GetParent(_hWnd), DWL_TREEVIEW_TECLADO_SOLTADO, wParam, (LPARAM)ID()); 
					if (wParam == 13) PostMessage(GetParent(_hWnd), DWL_TREEVIEW_TECLADO_INTRO, wParam, (LPARAM)ID());  
					break; 
				case WM_SETFOCUS :
					CancelarLabelEdit();  
					PostMessage(GetParent(_hWnd), DWL_TREEVIEW_FOCO_OBTENIDO, ID(), 0); 
					break;
				case WM_KILLFOCUS :
					PostMessage(GetParent(_hWnd), DWL_TREEVIEW_FOCO_PERDIDO, ID(), 0); 
					break;
				case TVM_EDITLABEL :
					return (LRESULT)EmpezarLabelEdit(BuscarNodo((HTREEITEM)lParam), false); 
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




		// Función que se encarga de especificar los colores y la Fuente del TreeView para cada nodo
		LRESULT DWLTreeView::_CustomDraw(LPARAM Datos) { 
			LPNMTVCUSTOMDRAW  lplvcd       = (LPNMTVCUSTOMDRAW)Datos;
			switch(lplvcd->nmcd.dwDrawStage) { 
				 case CDDS_PREPAINT :   
					 return CDRF_NOTIFYITEMDRAW; 
					 break;  
				 case CDDS_ITEMPREPAINT : 
					 for (unsigned int i = 0; i < _Nodos.size(); i++) {
						 if ((HTREEITEM)lplvcd->nmcd.dwItemSpec == _Nodos[i]->_Nodo) { 
								
							#if defined _DEBUG
								DWL::DWLDebug::ImprimirDebug(TEXT("DWLTreeView::_CustomDraw NodoSel %d , NodoActual %d\n"), lplvcd->nmcd.dwItemSpec, _Nodos[i]->_Nodo);
							#endif
							if (_Nodos[i]->_Nodo != (HTREEITEM)TreeView_GetSelection(_hWnd)) { 
								lplvcd->clrTextBk = _Nodos[i]->_ColorFondo; 
								lplvcd->clrText = _Nodos[i]->_ColorTexto;    
							}    
							else { 
								lplvcd->clrTextBk = _ColorSeleccion;  
								lplvcd->clrText = _ColorSeleccionTexto;  
							}	
							if (_Nodos[i]->_Fuente != NULL) { 
								SelectObject(lplvcd->nmcd.hdc, _Nodos[i]->_Fuente);  
							}	
							else {	 
								SelectObject(lplvcd->nmcd.hdc, _Fuente);	
							}     
						}
					}
					return CDRF_NEWFONT; 
					break;
			} 
			return 0;
		};



		                          
		// Función para asignar si el nodo tiene hijos o no..
		void DWLTreeView::_SetChildren(HTREEITEM IC, const bool TieneHijos) { 
			TVITEM TvItem;
			TvItem.mask = TVIF_HANDLE | TVIF_CHILDREN; 
			TvItem.cChildren = static_cast<int>(TieneHijos); 
			TvItem.hItem = IC; 
			TreeView_SetItem(_hWnd, &TvItem);
		};
		                          
			



		HWND DWLTreeView::EmpezarLabelEdit(DWLTreeView_Nodo *nNodo, const bool Numerico) {
			CancelarLabelEdit();
			if (nNodo == NULL) return NULL; 
			_eNodo = nNodo; 
			RECT Dim;  
			_Editando = true;
			TreeView_GetItemRect(_hWnd, nNodo->_Nodo, &Dim, TRUE);
			long Estilos;  
			if (Numerico == false) { Estilos = WS_BORDER | ES_AUTOHSCROLL | WS_CHILD; }  
			else                   { Estilos = WS_BORDER | ES_AUTOHSCROLL | WS_CHILD | ES_NUMBER; } 
			Dim.right += 30;
			_hWndEdit = CreateWindow(TEXT("EDIT"), nNodo->Texto(), Estilos, Dim.left - 5, Dim.top , Dim.right - (Dim.left) + 10, Dim.bottom - (Dim.top), _hWnd, (HMENU)555, GetModuleHandle(NULL), NULL);
			SetWindowLongPtr(_hWndEdit, GWL_USERDATA, PtrToLong(this));
//			_GestorMensajesOriginalEdit = (WNDPROC)SetWindowLongPtr(_hWndEdit, GWL_WNDPROC, (long)_GestorMensajesEdit); 
			_GestorMensajesOriginalEdit = (WNDPROC)LongToPtr(SetWindowLongPtr(_hWndEdit, GWL_WNDPROC, PtrToLong(_GestorMensajesEdit))); 


			SendMessage(_hWndEdit, EM_SETSEL, 0, DWLStrLen(nNodo->Texto()));
			SendMessage(_hWndEdit, WM_SETFONT, (WPARAM)nNodo->_Fuente, 0); 
			SendMessage(_hWndEdit, EM_SETLIMITTEXT, 0, 0);
			_BrochaFondoEdit = CreateSolidBrush(nNodo->_ColorFondo); 
			ShowWindow (_hWndEdit, SW_SHOWNORMAL); 
			UpdateWindow(_hWndEdit);  
			SetFocus(_hWndEdit); 
			PostMessage(GetParent(_hWnd), DWL_TREEVIEW_LABELEDIT_INICIO, (WPARAM)_eNodo, static_cast<int>(ID()));
			return _hWndEdit; 
		}


		void DWLTreeView::TerminarLabelEdit(void) {
			if (_hWndEdit != NULL && _Editando == true) { 
				TCHAR Txt[512];
				GetDlgItemText(GetParent(_hWndEdit), GetWindowLongPtr(_hWndEdit, GWL_ID), Txt, 512);
				DestroyWindow(_hWndEdit);	
				DeleteObject(_BrochaFondoEdit);	
				
				DWLTreeView_TerminarLabelEdit Edicion(_eNodo, Txt);
				SendMessage(GetParent(_hWnd), DWL_TREEVIEW_LABELEDIT_FIN, reinterpret_cast<WPARAM>(&Edicion), static_cast<int>(ID()));
				if (Edicion.Cancelar == false) _eNodo->Texto(Edicion.NuevoTexto()); 	 
				_Editando = false; 
				RECT Dim; 
				TreeView_GetItemRect(_hWnd, _eNodo->_Nodo, &Dim, TRUE);
				InvalidateRect(_hWnd, &Dim, false);  
				_eNodo = NULL;
			} 
		}

		// Función que cancela la edicion de un item/subitem
		void DWLTreeView::CancelarLabelEdit(void) { 
			if (_hWndEdit != NULL && _Editando == true) {
				_Editando = false;  
				DestroyWindow(_hWndEdit);
				DeleteObject(_BrochaFondoEdit);	
				_eNodo->Seleccionar();
				PostMessage(GetParent(_hWnd), DWL_TREEVIEW_LABELEDIT_CANCELADO, (WPARAM)_eNodo, static_cast<int>(ID()));
				_eNodo = NULL;
			} 
		}




		 // WindowProcedure que usara el Editbox en la Función editlabel
		LRESULT CALLBACK DWLTreeView::_GestorMensajesEdit(HWND dhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { 
			DWLTreeView *This = reinterpret_cast<DWLTreeView *>(LongToPtr(GetWindowLongPtr(dhWnd, GWL_USERDATA)));  
			NMHDR T; 
			T.hwndFrom = dhWnd;
			T.idFrom = GetWindowLongPtr(dhWnd, GWL_ID); 
			switch (uMsg) {  
				case WM_CTLCOLOREDIT : 
				case WM_CTLCOLORSTATIC : 
					//This->Item(This->_eItem)->ColorFondo(This->_eSubItem);
					SetTextColor((HDC)wParam, This->_eNodo->_ColorTexto);
					SetBkColor((HDC)wParam, This->_eNodo->_ColorFondo);
		//			SetBkMode((HDC)wParam, TRANSPARENT);	
					return (LRESULT)This->_BrochaFondoEdit; 
				case WM_LBUTTONUP : 	 
					T.code = NM_CLICK; 	
		//			PostMessage(GetParent(dhWnd), WM_NOTIFY, 0, (long)&T);  
					This->GestorMensajes(WM_NOTIFY, 0, reinterpret_cast<WPARAM>(&T));
					break;   
				case WM_RBUTTONUP : 
					T.code = NM_RCLICK; 	
					This->GestorMensajes(WM_NOTIFY, 0, reinterpret_cast<WPARAM>(&T));
		//			PostMessage(GetParent(dhWnd), WM_NOTIFY, 0, (long)&T);
					break; 		
				case WM_LBUTTONDBLCLK : 
					T.code = NM_DBLCLK; 
		//			PostMessage(GetParent(dhWnd), WM_NOTIFY, 0, (long)&T); 	
					This->GestorMensajes(WM_NOTIFY, 0, reinterpret_cast<WPARAM>(&T));
					break; 
				case WM_CHAR : 
					NMKEY Key;	
					T.code = NM_KEYDOWN;
					Key.hdr = T;	
					Key.nVKey = (unsigned int)wParam;
					Key.uFlags = (unsigned int)lParam; 
					This->GestorMensajes(WM_NOTIFY, 0, reinterpret_cast<WPARAM>(&Key));
		/*			if (wParam == 13) {   		
						T.code = NM_RETURN;  	
						PostMessage(GetParent(dhWnd), WM_NOTIFY, 0, (long)&T);  
					}	 */
					break;
									
			} 
			return CallWindowProc(This->_GestorMensajesOriginalEdit, dhWnd, uMsg, wParam, lParam);
		};



















		DWLTreeView_Nodo::DWLTreeView_Nodo(DWLTreeView *TV, HTREEITEM nNodo) { 
			_TV = TV; 
			_Nodo = nNodo;
			_ColorFondo = _TV->ColorFondo();
			_ColorTexto = _TV->ColorTexto();
			_Fuente = TV->_Fuente;
		};


		DWLTreeView_Nodo::DWLTreeView_Nodo(DWLTreeView *TV, HTREEITEM nNodo, COLORREF nColorFondo, COLORREF nColorTexto) { 
			_TV = TV;
			_Nodo = nNodo; 
			_ColorFondo = nColorFondo; 
			_ColorTexto = nColorTexto; 
			_Fuente = TV->_Fuente;
		};



		void DWLTreeView_Nodo::HacerVisible(void) { 
			TreeView_EnsureVisible(_TV->_hWnd, _Nodo);
		};


		void DWLTreeView_Nodo::Texto(const TCHAR *Txt) {
			TCHAR Tmp[256];
			DWLStrCopy(Tmp, 256, Txt);
			TVITEM TvItem;
			TvItem.mask = TVIF_HANDLE | TVIF_TEXT; 
			TvItem.pszText = Tmp;
			TvItem.cchTextMax = static_cast<int>(DWLStrLen(Tmp));
			TvItem.hItem = _Nodo;
			TreeView_SetItem(_TV->_hWnd, &TvItem);
		};


		const TCHAR *DWLTreeView_Nodo::Texto(void) { 
			TCHAR Tmp[256];
			TVITEM TvItem;
			TvItem.mask = TVIF_HANDLE | TVIF_TEXT; 
			TvItem.pszText = Tmp;
			TvItem.cchTextMax = 256;
			TvItem.hItem = _Nodo;
			TreeView_GetItem(_TV->_hWnd, &TvItem);
			_TV->_TmpStr = Tmp;
			return _TV->_TmpStr(); 
		};


		void DWLTreeView_Nodo::Icono(const int nIcono) {
			TVITEM TvItem;
			TvItem.mask = TVIF_HANDLE | TVIF_IMAGE; 
			TvItem.iImage = nIcono;
			TvItem.hItem = _Nodo; 
			TreeView_SetItem(_TV->_hWnd, &TvItem); 
		};


		const int DWLTreeView_Nodo::Icono(void) { 
			TVITEM TvItem; 
			TvItem.mask = TVIF_HANDLE | TVIF_IMAGE ; 
			TvItem.hItem = _Nodo; 
			TreeView_GetItem(_TV->_hWnd, &TvItem); 
			return TvItem.iImage; 
		};


		void DWLTreeView_Nodo::IconoSeleccionado(const int nIcono) { 
			TVITEM TvItem; 
			TvItem.mask = TVIF_HANDLE | TVIF_SELECTEDIMAGE;
			TvItem.iSelectedImage = nIcono;
			TvItem.hItem = _Nodo;
			TreeView_SetItem(_TV->_hWnd, &TvItem); 
		};


		const int DWLTreeView_Nodo::IconoSeleccionado(void) { 
			TVITEM TvItem; 
			TvItem.mask = TVIF_HANDLE | TVIF_SELECTEDIMAGE;
			TvItem.hItem = _Nodo;
			TreeView_GetItem(_TV->_hWnd, &TvItem);
			return TvItem.iSelectedImage;
		};


		DWLTreeView_Nodo *DWLTreeView_Nodo::NodoHijo(void) {
			return _TV->BuscarNodo(TreeView_GetChild(_TV->_hWnd, _Nodo));
		};


		DWLTreeView_Nodo *DWLTreeView_Nodo::NodoPadre(void) { 
			return _TV->BuscarNodo(TreeView_GetParent(_TV->_hWnd, _Nodo));
		};

		DWLTreeView_Nodo *DWLTreeView_Nodo::NodoSiguiente(void) { 
			return _TV->BuscarNodo(TreeView_GetNextItem(_TV->_hWnd, _Nodo, TVGN_NEXT)); 
		};


		DWLTreeView_Nodo *DWLTreeView_Nodo::NodoAnterior(void) {
			return _TV->BuscarNodo(TreeView_GetNextItem(_TV->_hWnd, _Nodo, TVGN_PREVIOUS)); 
		};


		HTREEITEM DWLTreeView_Nodo::Hijo(void) { 
			return TreeView_GetChild(_TV->_hWnd, _Nodo); 
		};


		HTREEITEM DWLTreeView_Nodo::Padre(void) { 
			return TreeView_GetParent(_TV->_hWnd, _Nodo); 
		};


		HTREEITEM DWLTreeView_Nodo::Siguiente(void) { 
			return TreeView_GetNextItem(_TV->_hWnd, _Nodo, TVGN_NEXT); 
		};


		HTREEITEM DWLTreeView_Nodo::Anterior(void) {
			return TreeView_GetNextItem(_TV->_hWnd, _Nodo, TVGN_PREVIOUS); 
		};


		void DWLTreeView_Nodo::Seleccionar(void) { 
			TreeView_SelectItem(_TV->_hWnd, _Nodo);
		};


		void DWLTreeView_Nodo::_AsignarBase(DWLTreeView *TV, HTREEITEM nNodo, COLORREF nColorFondo, COLORREF nColorTexto) { 
			_TV = TV; 
			_Nodo = nNodo;
			_ColorFondo = nColorFondo; 
			_ColorTexto = nColorTexto;
			_Fuente = TV->_Fuente; 
		};


		void DWLTreeView_Nodo::_AsignarBase(DWLTreeView *TV, HTREEITEM nNodo) { 
			_TV = TV; 
			_Nodo = nNodo; 
			_ColorFondo = _TV->ColorFondo();
			_ColorTexto = _TV->ColorTexto();
			_Fuente = TV->_Fuente; 
		};


	}

}

