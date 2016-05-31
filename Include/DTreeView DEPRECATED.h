#pragma once

#include "DControl.h"
#include <string>
#include "DDebug.h"
#include <vector>
#include "DImageList.h"

namespace DWL {


	
	// Siempre hay que iniciarla con un objeto que herede de DTreeView<MIOBJETO>::DTreeView_Nodo (cosa que no me convence)
	template <class TIPO_NODO> class DTreeView : public DControl {
		public:
			////////////////////////////////////////////////////////////////////////////////////
			// DTreeView_Nodo																  //
			////////////////////////////////////////////////////////////////////////////////////
			class DTreeView_Nodo {
			  public:
				virtual const DEnum_Objeto Objeto_Tipo(void) {
					return DEnum_Objeto_TreeView_Nodo;
				};

				DTreeView_Nodo(void) : _ID(NULL), _TV(NULL) {
				}

				~DTreeView_Nodo(void) {
				}

				const BOOL AsignarTexto(std::wstring nTexto) {
					return AsignarTexto(nTexto.c_str(), nTexto.size());
				};

				const BOOL AsignarTexto(const wchar_t *nTexto, size_t nTotalCaracteres = 0) {
					if (nTotalCaracteres == 0) nTotalCaracteres = wcslen(nTexto);
					TCHAR *Tmp = new TCHAR[nTotalCaracteres + 1];
					wcscpy_s(Tmp, nTotalCaracteres + 1, nTexto);
					TVITEMEX Nodo;
					Nodo.mask = TVIF_HANDLE | TVIF_TEXT;
					Nodo.pszText = Tmp;
					Nodo.cchTextMax = static_cast<int>(nTotalCaracteres);
					Nodo.hItem = this->_ID;
					BOOL R = TreeView_SetItem(_TV->hWnd(), &Nodo);
					delete[] Tmp;
					return R;
				};

				const BOOL ObtenerTexto(std::wstring &nTexto) {
					static TCHAR	Tmp[256];
					TVITEMEX		TvItem;
					TvItem.mask = TVIF_HANDLE | TVIF_TEXT;
					TvItem.pszText = Tmp;
					TvItem.cchTextMax = 256;
					TvItem.hItem = _ID;
					BOOL R = TreeView_GetItem(_TV->hWnd(), &TvItem);
					nTexto = Tmp;
					return R;
				}

				TIPO_NODO *Padre(void) {
					HTREEITEM Padre = TreeView_GetParent(_TV->hWnd(), _ID);
					return _ObtenerLPARAM(Padre);
				}

				TIPO_NODO *Hijo(void) {
					HTREEITEM Hijo = TreeView_GetChild(_TV->hWnd(), _ID);
					return _ObtenerLPARAM(Hijo);
				};

				TIPO_NODO *Siguiente(void) {
					HTREEITEM Siguiente = TreeView_GetNextItem(_TV->hWnd(), _ID, TVGN_NEXT);
					return _ObtenerLPARAM(Siguiente);
				};

				TIPO_NODO *Anterior(void) {
					HTREEITEM Anterior = TreeView_GetNextItem(_TV->hWnd(), _ID, TVGN_PREVIOUS);
					return _ObtenerLPARAM(Anterior);
				};
			protected:
				HTREEITEM					   _ID;
				DControl        	          *_TV;

				TIPO_NODO *_ObtenerLPARAM(HTREEITEM nItem) {
					if (nItem == NULL) return NULL;
					TVITEMEX Nodo;
					Nodo.mask = TVIF_HANDLE | TVIF_PARAM;
					Nodo.hItem = nItem;
					if (TreeView_GetItem(_TV->hWnd(), &Nodo) == FALSE) return NULL;
					return static_cast<TIPO_NODO *>(reinterpret_cast<void *>(Nodo.lParam));
				}


/*				template <class TIPO_NODO> TIPO_NODO *_ObtenerTipoNodo(LPARAM lParam) {
					return static_cast<TIPO_NODO *>(reinterpret_cast<void *>(Nodo.lParam));
				};*/

				template <class TIPO_NODO> friend class DTreeView;
			};

			////////////////////////////////////////////////////////////////////////////////////
			// FIN DTreeView_Nodo															  //
			////////////////////////////////////////////////////////////////////////////////////











		virtual const DEnum_Objeto Objeto_Tipo(void) { return DEnum_Objeto::DEnum_Objeto_TreeView; };

		DTreeView(void) { 
		};

		~DTreeView(void) { 
		};

		//! Función para crear el TreeView (CreateWindowEx).
		/*! Esta función se usa para crear un TreeView dinamicamente.
				\fn         HWND Crear(DBaseWnd *nPadre, const int cX, const int cY, const int cAncho, const int cAlto, const UINT cID, DWORD nEstilos, DWORD nEstilosExtendidos = NULL);
				\param[in]  nPadre               Clase DBaseWnd que va a hacer de padre para el TreeView
				\param[in]  cX                   Coordenada X relativa a la ventana padre.
				\param[in]  cY                   Coordenada Y relativa a la ventana padre.
				\param[in]  cAncho               Ancho del TreeView en pixeles.
				\param[in]  cAlto                Altura del TreeView en pixeles
				\param[in]  cID                  ID para poder identificar el TreeView en sus eventos.
				\param[in]  nEstilos             Estilos estandar para el TreeView.
				\param[in]  nEstilosExtendidos   Estilos extendidos para el TreeView.
				\return     Devuelve el HWND del TreeView o NULL en caso de error.
		*/
		HWND Crear(DBaseWnd *nPadre, const int cX, const int cY, const int cAncho, const int cAlto, const UINT cID, DWORD nEstilos, DWORD nEstilosExtendidos = NULL) {
			_hWnd = CreateWindowEx(nEstilosExtendidos, WC_TREEVIEW, NULL, nEstilos, cX, cY, cAncho, cAlto, nPadre->hWnd(), reinterpret_cast<HMENU>(IntToPtr(cID)), GetModuleHandle(NULL), NULL);
			_ConectarControl(cID, nPadre);
			return _hWnd;
		}


		//! Función para asignar esta clase a un TreeView de un dialogo.
		/*! Esta función se usa para asignar esta clase a un TreeView de un dialogo.
				\fn         HWND Asignar(DBaseWnd *Padre, const UINT cID);
				\param[in]  nPadre      Clase DBaseWnd que va a hacer de padre para el TreeView
				\param[in]  cID         ID para poder identificar el TreeView en sus eventos.
				\return     Devuelve el HWND del TreeView o NULL en caso de error.
				\remarks    Esta función solo debe utilizarse si tenemos un TreeView en un dialogo de los recursos.
		*/
		HWND Asignar(DBaseWnd *nPadre, const UINT cID) {
			_hWnd = GetDlgItem(nPadre->hWnd(), cID);
			_ConectarControl(cID, nPadre);
			return _hWnd;
		}



		TIPO_NODO *AgregarNodo(TIPO_NODO *nPadre, const TCHAR *cTexto, const int cIko, TIPO_NODO *InsertarDespuesDe = NULL, const UINT Estado = NULL, const UINT MascaraEstado = NULL) {
			TVINSERTSTRUCT ITS;
			TVITEMEX       Item;
			static TCHAR   Tmp[512];
			TIPO_NODO *nNodo = new TIPO_NODO;
			nNodo->_TV = this;
			wcscpy_s(Tmp, 512, cTexto);
			Item.pszText		= Tmp;
			Item.cchTextMax		= static_cast<int>(wcslen(Tmp));
			Item.mask			= TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_STATE | TVIF_CHILDREN;
			Item.iImage			= cIko; 
			Item.iSelectedImage = cIko;
			Item.state			= Estado;
			Item.stateMask		= MascaraEstado;
		//												Item.cChildren		= 0;
			Item.lParam			= static_cast<LPARAM>(PtrToLong(nNodo));
		//												Item.lParam			= (LPARAM)this;
			ITS.hInsertAfter	= (InsertarDespuesDe) ? InsertarDespuesDe->_ID : TVI_LAST;
			ITS.itemex			= Item;
			ITS.hParent			= (nPadre) ? nPadre->_ID : TVI_ROOT;

		//												HTREEITEM nID = TreeView_InsertItem(_hWnd, &ITS);
			static_cast<DTreeView_Nodo *>(nNodo)->_ID = TreeView_InsertItem(_hWnd, &ITS);
			_Nodos.push_back(nNodo);
			return nNodo;
		}

		void BorrarNodo(TIPO_NODO *eNodo) { 
			TreeView_DeleteItem(_hWnd, eNodo->_ID);
		}


		//
		//! Evento que es llamado cuando se expande / contrae un nodo del treeview
		//  virtual void TreeView_Evento_Nodo_Expandiendo(DTreeView_Nodo *nNodo);
		virtual const BOOL TreeView_Evento_Nodo_Expandiendo(TIPO_NODO *nNodo) { return FALSE; };

		void AsignarImageList(DImageList *nListaImagenes) {
			HIMAGELIST nImg = NULL;
			if (nListaImagenes != NULL) nImg = nListaImagenes->operator ()();
			TreeView_SetImageList(_hWnd, nImg, TVSIL_NORMAL);
		}

		//! Nuevo WindowProcedure que se sobrepondra al WindowProcedure original del ListView.
		/*! Esta función es la que re-emplaza el WindowProcedure del ListView para poder hacer cosas como la edicion, y el pintado personalizado.
				\fn         virtual LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam)
				\param[in]  uMsg        Mensaje
				\param[in]  wParam      Parametro wide
				\param[in]  lParam      Parametro long
				\return     Dependiendo del mensaje procesado devolvera una cosa u otra...
				\remarks    Hacer un SendMessage al HWND de este ListView o utilizar esta función es exactamente lo mismo.
		*/
		virtual LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
			HTREEITEM hID;
			TIPO_NODO *NodoTmp = NULL;
			switch (uMsg) {
				case DWL_NOTIFICACION:
					switch (((LPNMHDR)lParam)->code) {
/*						case NM_CLICK: // nItem, nSubItem, ptAction
						case NM_DBLCLK: // nItem, nSubItem, ptAction
						case NM_RCLICK: // nItem, nSubItem, ptAction
						case NM_RDBLCLK: // nItem, nSubItem, ptAction
							return _NotificacionClick(lParam);*/
							//                    case NM_HOVER : // (devolver 0 para normal, 1 para cancelar)
							//                        return SendMessage(GetParent(_hWnd), DWL_LISTVIEW_RESALTAR_ITEM, static_cast<WPARAM>(ID()), 0);
						case NM_KILLFOCUS: // nada
							return SendMessage(GetParent(_hWnd), DWL_TREEVIEW_FOCO_PERDIDO, static_cast<WPARAM>(ID()), 0);
						case NM_RELEASEDCAPTURE: // nada
							return SendMessage(GetParent(_hWnd), DWL_TREEVIEW_TERMINAR_CAPTURA, static_cast<WPARAM>(ID()), 0);
						case NM_RETURN: // nada
							return SendMessage(GetParent(_hWnd), DWL_TREEVIEW_TECLADO_INTRO, static_cast<WPARAM>(ID()), 0);
						case NM_SETFOCUS: // nada
							return SendMessage(GetParent(_hWnd), DWL_TREEVIEW_FOCO_OBTENIDO, static_cast<WPARAM>(ID()), 0);
					}
					break;
				case DWL_TREEVIEW_NODO_EXPANDIENDO:
					hID = ((LPNMTREEVIEW)lParam)->itemNew.hItem;
					for (size_t i2 = 0; i2 < _Nodos.size(); i2++) {
						if (_Nodos[i2]->_ID == hID) {
							NodoTmp = _Nodos[i2];
							break;
						}
					}
					if (this->TreeView_Evento_Nodo_Expandiendo(NodoTmp) == TRUE) return TRUE;
					return SendMessage(GetParent(_hWnd), DWL_TREEVIEW_NODO_EXPANDIENDO, (WPARAM)NodoTmp, (LPARAM)ID());

				// Este mensaje se recibe una vez borrado el item y se usa para borrar la clase con el nodo de la memoria.
				// El LPARAM es un puntero a la clase TIPO_NODO que contiene la información adicional para el nodo, y que debe ser eliminada tanto del vector de nodos como de memória.
				case DWL_TREEVIEW_BORRARNODO:
					NodoTmp = static_cast<TIPO_NODO *>(reinterpret_cast<void *>(lParam));
					for (size_t i = 0; i < _Nodos.size(); i++) {
						if (_Nodos[i] == NodoTmp) {
							_Nodos.erase(_Nodos.begin() + i);
							break;
						}
					}
					delete NodoTmp;
					return 0;
			}
			return DControl::GestorMensajes(uMsg, wParam, lParam);
		}
		



		inline const size_t TotalNodos(void) {
			return _Nodos.size();
		}

		inline TIPO_NODO *Nodo(size_t Pos) {
			return _Nodos[Pos];
		}
		
		inline TIPO_NODO *PrimerNodo(void) {
			HTREEITEM TvRoot = TreeView_GetRoot(_hWnd);
			if (TvRoot == NULL) return NULL;
			TVITEMEX tvItem;
			tvItem.mask = TVIF_HANDLE | TVIF_PARAM;
			tvItem.hItem =TvRoot;
			TreeView_GetItem(_hWnd, &tvItem);
			TIPO_NODO *NodoPadre = static_cast<TIPO_NODO *>(reinterpret_cast<void *>(tvItem.lParam));
			return NodoPadre;
		}

		/* Función que devuelve el primer texto encontrado en el arbol igual que el parámetro buscar, o null si no lo encuentra 
			NOTA : la comparación se hace INSENSITIVE
			Parámetros :
				- Buscar    : Cadena a buscar
				- Padre     : Nodo padre por donde empieza la busqueda, NULL si se busca desde la raíz (valor por defecto).
				- Recursivo : Busqueda recursiva por los hijos (por defecto desactivada)
		*/

		TIPO_NODO *BuscarTexto(std::wstring Buscar, TIPO_NODO *Padre = NULL, const BOOL Recursivo = FALSE) {
			TIPO_NODO *Ret = NULL;
//			HTREEITEM		Hijo;
			TVITEMEX		TvItem, TvItemH;
			TCHAR			Tmp[256];
			BOOL			R = FALSE;
//			if (bNodo != NULL) BuscarDesde = bNodo->_ID;
			TvItem.mask			= TVIF_HANDLE | TVIF_TEXT | TVIF_PARAM | TVIF_CHILDREN;
			TvItem.pszText		= Tmp;
			TvItem.cchTextMax	= 256;
			TvItem.hItem		= (Padre) ? TreeView_GetChild(_hWnd, Padre->_ID)  : TreeView_GetRoot(_hWnd);
			TvItemH.mask		= TVIF_HANDLE | TVIF_PARAM;
			TvItemH.hItem		= TVI_ROOT;
			R = TreeView_GetItem(_hWnd, &TvItem);
			if (R == FALSE) return NULL;

			do {
				// Tiene el mismo texto
				if (_wcsicmp(Buscar.c_str(), TvItem.pszText) == 0) {
					return static_cast<TIPO_NODO *>(reinterpret_cast<void *>(TvItem.lParam));
				}
				// Si tiene hijos busco en ellos
				if (TvItem.cChildren && Recursivo == TRUE) {
					TvItemH.hItem = TreeView_GetChild(_hWnd, TvItem.hItem);
					R = TreeView_GetItem(_hWnd, &TvItemH);
					Ret = BuscarTexto(Buscar, static_cast<TIPO_NODO *>(reinterpret_cast<void *>(TvItemH.lParam)));
					if (Ret) return Ret;
				}
				// Obtengo el sigiente nodo
				TvItem.hItem = TreeView_GetNextItem(_hWnd, TvItem.hItem, TVGN_NEXT);
				R = TreeView_GetItem(_hWnd, &TvItem);
			} while (TvItem.hItem != NULL);

			return NULL;
		};


/////////////////	
	protected: //
/////////////////

		// vector de nodos para hacer busquedas lineales mucho más rápido.
		// Los nodos se guardan en el LPARAM de cada HTREEITEM y tambien en este vector.
		// Unicamente guardo el puntero del Nodo por lo que hay que borrarlos al finalizar.
		std::vector<TIPO_NODO *> _Nodos;

        friend class DTreeView_Nodo;
	};
};

