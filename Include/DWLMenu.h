/*! \file DWLMenu.h
	\brief		Archivo que contiene funciones para la utilización de menús desplegables en windows.


	\details	Clase diseñada para poder controlar menús desplegables en windows.																				\n
				Esta clase en breve no formara parte del proyecto y por lo tanto no recibira actualizaciones.											\n
				Si quieres utilizar un control del estilo del edit box con la DWL se recomienda usar DWLMenuEx.									\n
				Para la version 1.0 de la DWL esta clase probablemente desaparecera.																	\n

																																						\n
	\author		devildrey33
	\version	0.95
	\date		30/01/2005
 
	\remarks
				Archivo creado por devildrey33 el dia [01/02/2004] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n	
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n	
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n	

*/
#ifndef DWL_MENU_H
#define DWL_MENU_H

#include "DWL.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Controles
	namespace Controles {
		//! Clase para controlar un menu desplegable de windows
		class DWLMenu {				
		 public : //////////////////// Miembros publicos
									//
									//! Constructor
									// DWLMenu(void);
									DWLMenu(void) {
										_ID = -1;
										_hMenu = NULL;
										Padre = false;
										_Check = NULL;
										_UnCheck = NULL; 
									};
									//
									//! Constructor para obtener el Menu del sistema de una Ventana
									// DWLMenu(HWND hWndSysMenu);
									DWLMenu(HWND hWndSysMenu) {
										_ID = -1;
										_hMenu = NULL; 
										Padre = false;
										_Check = NULL;
										_UnCheck = NULL;
										ObtenerMenuSistema(hWndSysMenu); 
									};
									//
									//! Destructor
									// ~DWLMenu(void);
								   ~DWLMenu(void) {
										if (Padre == true)                               { DestroyMenu(_hMenu); }
										for (unsigned int i = 0; i < _Items.size(); i++) { delete _Items[i]; } 
										if (_Check != NULL)                              { DeleteObject(_Check); }
										if (_UnCheck != NULL)                            { DeleteObject(_UnCheck); } 
									};
									//
									//! Función para crear el Menu Padre principal.  
									// void inline CrearMenu(void);
		 inline void                CrearMenu(void) {
										if (_hMenu != NULL) BorrarTodo();
										_hMenu = CreatePopupMenu();
										Padre = true; 
									};
									//
									//! Función para crear un MenuItem
									// const int CrearMenuItem(const int IDM, const TCHAR *Txt, const int IconoMarcado = -1, const int IconoDesMarcado = -1, const int nPos = -1);
		 const int                  CrearMenuItem(const int IDM, const TCHAR *Txt, const int IconoMarcado = -1, const int IconoDesMarcado = -1, const int nPos = -1) {
										int           Posicion = nPos;
										TCHAR         NTexto[256]; 
										DWLMenu    *MenuItem = new DWLMenu; 
										MENUITEMINFO  MenuInfo; 
										DWLStrCopy(NTexto, 256, Txt); 
										if (Posicion == -1 || Posicion > static_cast<int>(_Items.size()) -1) Posicion = static_cast<int>(_Items.size()); 
										MenuItem->_ID = IDM; 
										MenuItem->_Parent = _hMenu; 
										MenuItem->_Pos = Posicion; 
										for (unsigned int i = Posicion; i < _Items.size(); i++) { _Items[i]->_Pos ++; }  
										MenuInfo.cbSize = sizeof(MENUITEMINFO); 
										MenuInfo.fMask = MIIM_DATA | MIIM_ID | MIIM_SUBMENU | MIIM_TYPE; 
										MenuInfo.wID = IDM; 
										MenuInfo.hSubMenu = NULL; 
										MenuInfo.fType = MFT_STRING; 
										MenuInfo.cch = static_cast<UINT>(DWLStrLen(Txt));
										MenuInfo.dwTypeData = NTexto; 
										BOOL R = InsertMenuItem(_hMenu, Posicion, TRUE, &MenuInfo);
										if (IconoMarcado != -1)   { _Check = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IconoMarcado)); }
										if (IconoDesMarcado != -1) { _UnCheck = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IconoDesMarcado)); } 
										SetMenuItemBitmaps(MenuItem->_Parent, Posicion, MF_BYPOSITION, _Check, _UnCheck);
										_Items.insert(_Items.begin() + Posicion, MenuItem); 
										if (R == 0) return -1;
										else 		return Posicion;
									};
									//
									//! Función para crear un SubMenu 
									// const int CrearSubMenu(const int IDM, const TCHAR *Txt, const int IkoCheck = -1, const int IkoUncheck = -1, const int nPos = -1);
		 const int                  CrearSubMenu(const int IDM, const TCHAR *Txt, const int IkoCheck = -1, const int IkoUncheck = -1, const int nPos = -1) {
										int           Posicion = nPos;
										TCHAR         NTexto[256]; 
										DWLMenu      *SubMenu = new DWLMenu;
										MENUITEMINFO  MenuInfo; 
										DWLStrCopy(NTexto, 256, Txt); 
										if (Posicion == -1 || Posicion > static_cast<int>(_Items.size()) -1) { Posicion = static_cast<int>(_Items.size()); } 
										SubMenu->_ID = IDM; 
										SubMenu->_hMenu = CreateMenu(); 
										SubMenu->_Parent = _hMenu;
										SubMenu->_Pos = Posicion; 
										for (unsigned int i = static_cast<int>(Posicion); i < _Items.size(); i++) { _Items[i]->_Pos ++; }
										MenuInfo.cbSize = sizeof(MENUITEMINFO);
										MenuInfo.fMask = MIIM_DATA | MIIM_ID | MIIM_SUBMENU | MIIM_TYPE; 
										MenuInfo.wID = IDM;
										MenuInfo.hSubMenu = SubMenu->_hMenu; 
										MenuInfo.fType = MFT_STRING; 
										MenuInfo.cch = static_cast<UINT>(DWLStrLen(Txt)); 
										MenuInfo.dwTypeData = NTexto; 
										BOOL R = InsertMenuItem(_hMenu, Posicion, TRUE, &MenuInfo);
										if (IkoCheck != -1)   { _Check = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IkoCheck)); } 
										if (IkoUncheck != -1) { _UnCheck = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IkoUncheck)); } 
										SetMenuItemBitmaps(SubMenu->_Parent, Posicion, MF_BYPOSITION, _Check, _UnCheck);
										_Items.insert(_Items.begin() + Posicion, SubMenu); 
										if (R == 0) return -1;
										else 		return Posicion;
									};
									//
									//! Función para crear un Separador de menus
									// const int CrearSeparador(const int nPos = -1);
		 const int                  CrearSeparador(const int nPos = -1) {
										DWLMenu      *Separador = new DWLMenu;
										int           Posicion  = nPos; 
										MENUITEMINFO  MenuInfo; 
										if (Posicion == -1 || Posicion > static_cast<int>(_Items.size()) -1) { Posicion = static_cast<int>(_Items.size()); } 
										for (unsigned int i = static_cast<int>(Posicion); i < _Items.size(); i++) { _Items[i]->_Pos ++; } 
										MenuInfo.cbSize = sizeof(MENUITEMINFO);
										MenuInfo.fMask = MIIM_ID | MIIM_SUBMENU | MIIM_TYPE; 
										MenuInfo.wID = 99999; 
										MenuInfo.hSubMenu = NULL;
										MenuInfo.fType = MFT_SEPARATOR;
										Separador->_ID = 0; 
										Separador->_Parent = _hMenu; 
										Separador->_Pos = Posicion;
										BOOL R = InsertMenuItem(_hMenu, Posicion, MF_BYPOSITION, &MenuInfo);
										_Items.insert(_Items.begin() + Posicion, Separador);
										if (R == 0) return -1;
										else 		return Posicion;
									};
									//
									//! Función para Marcar / Desmarcar el menu
									// inline void Marcado(const bool Marcar);
		 inline void                Marcado(const bool Marcar) {
										CheckMenuItem(_Parent, _Pos, MF_BYPOSITION | ((Marcar == true) ? MF_CHECKED : MF_UNCHECKED)); 
									};
									//
									//! Función para Activar / Desactivar el menu
									// inline void Activado(const bool Activar);
		 inline void                Activado(const bool Activar)  {
										EnableMenuItem(_Parent, _Pos, MF_BYPOSITION | ((Activar == true) ? MF_ENABLED : MF_GRAYED)); 
									};
									//
									//! Función para mostrar el Menu por pantalla en las coordenadas actuales del mouse
									// inline void Mostrar(HWND hWndDest);
		 inline void                Mostrar(HWND hWndDest) {
										POINT Point;
										GetCursorPos(&Point);
										TrackPopupMenu(_hMenu, TPM_LEFTALIGN, Point.x, Point.y, NULL, hWndDest, NULL);
									};
									//
									//! Función que retorna el Handle del menu
									// inline HMENU hMenu(void);
		 inline HMENU               hMenu(void) {
										return _hMenu; 
									};
									//
									//! Función que retorna la ID del menu
									// inline const int ID(void);
		 inline const int           ID(void) {
										return _ID; 
									};
									//
									//! Función que retorna la posicion del menu
									// inline const int Posicion(void);
		 inline const int           Posicion(void) {
										return _Pos; 
									};
									//
									//! Esta función devuelve el handle del Menu inmediatamente superior al especificado
									// inline HMENU MenuPadre(void);
		 inline HMENU               MenuPadre(void) {
										return _Parent; 
									};
									//
									//! Esta función se usa para Obtener el texto de este menu
									// void ObtenerTexto(TCHAR *Txt, const int TamTxt);
		 void						ObtenerTexto(TCHAR *Txt, const int TamTxt) {
//										TCHAR T[256];
										MENUITEMINFO MenuInfo;
										MenuInfo.cbSize = sizeof(MENUITEMINFO);
										MenuInfo.fMask = MIIM_TYPE;
										MenuInfo.dwTypeData = Txt;
										MenuInfo.cch = TamTxt;
										GetMenuItemInfo(_Parent, _Pos, true, &MenuInfo);
									};
									//
									//! Esta función se usa para asignar el texto de este menu
									// void AsignarTexto(const TCHAR *Txt);
		 void                       AsignarTexto(const TCHAR *Txt) { 
										TCHAR T[256];
										MENUITEMINFO MenuInfo; 
										MenuInfo.cbSize = sizeof(MENUITEMINFO);
										MenuInfo.fMask = MIIM_TYPE; 
										MenuInfo.dwTypeData = T; 
										MenuInfo.cch = 256;
										GetMenuItemInfo(_Parent, _Pos, true, &MenuInfo);
										DWLStrCopy(T, 256, Txt); 
										SetMenuItemInfo(_Parent, _Pos, true, &MenuInfo);
									};
									//
									//! Función para buscar recursivamente un Item o SubItem de este menu
									// DWLMenu *BuscarID(const int bID);
		 DWLMenu                   *BuscarID(const int bID) { 
										DWLMenu *R = NULL; 
										for (unsigned int i = 0; i < _Items.size(); i++) { 
											if (_Items[i]->ID() == bID) return _Items[i];
											if (_Items[i]->TotalMenus() > 0) {   
												R = _Items[i]->BuscarID(bID);   
												if (R != NULL) return R;
											} 
										} 
										return NULL; 
									};
									//
									//! Función para asignar los iconos del menu
									// void AsignarIcono(const int IconoMarcado = -1, const int IconoDesMarcado = -1);
		 void                       AsignarIcono(const int IconoMarcado = -1, const int IconoDesMarcado = -1) {
										if (IconoMarcado != -1) {  
											if (_Check != NULL)   DeleteObject(_Check);
											_Check = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IconoMarcado)); 
										} 
										if (IconoDesMarcado != -1) { 
											if (_UnCheck != NULL) DeleteObject(_UnCheck);
											_UnCheck = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IconoDesMarcado)); 
										}
										SetMenuItemBitmaps(_Parent, _Pos, MF_BYPOSITION, _Check, _UnCheck); 
									};
									//
									//! Función para borrar todos los menus de este menu (El menu padre no sera eliminado)
									// void BorrarTodo(void);
		 void                       BorrarTodo(void) {
										DWLMenu *T;
										for (unsigned int i = 0; i < _Items.size(); i++) { 
											T = _Items[i];  
											DeleteMenu(_Items[i]->MenuPadre(), _Items[i]->ID(), MF_BYCOMMAND);
											if (_Items[i]->_Check != NULL)   { DeleteObject(_Items[i]->_Check); } 
											if (_Items[i]->_UnCheck != NULL) { DeleteObject(_Items[i]->_UnCheck); }
											delete _Items[i]; 
										} 
										_Items.resize(0); 
										if (Padre == true)    { DestroyMenu(_hMenu); _hMenu = NULL; Padre = false; } 
										if (_Check != NULL)   { DeleteObject(_Check); }
										if (_UnCheck != NULL) { DeleteObject(_UnCheck); }
										_Check = NULL;
										_UnCheck = NULL; 
										_ID = -1; 
										Padre = false; 
									};
									//
									//! Función para borrar un Menu
									// void BorrarMenu(const unsigned int Pos);
		 void                       BorrarMenu(const unsigned int Pos) {
										DeleteMenu(_Items[Pos]->MenuPadre(), _Items[Pos]->ID(), MF_BYCOMMAND); 
										if (_Items[Pos]->_Check != NULL)   { DeleteObject(_Check); } 
										if (_Items[Pos]->_UnCheck != NULL) { DeleteObject(_UnCheck); } 
										delete _Items[Pos];
										_Items.erase(_Items.begin() + Pos);
									};
									//
									//! Función para leer el menu del sistema y almacenarlo en esta Función
									// void ObtenerMenuSistema(HWND hWndSysMenu);
		 void                       ObtenerMenuSistema(HWND hWndSysMenu) {
										int           Contador = 0; 
										DWLMenu      *MenuItem = NULL; 
										MENUITEMINFO  InfoMenu;
										BorrarTodo();
										_hMenu = GetSystemMenu(hWndSysMenu, false); 
										Padre = false; 
										InfoMenu.cbSize = sizeof(MENUITEMINFO);
										InfoMenu.fMask = MIIM_ID; 
										while (GetMenuItemInfo(_hMenu, Contador, TRUE, &InfoMenu) != FALSE) { 
											MenuItem = new DWLMenu; 
											MenuItem->_ID = InfoMenu.wID;
											MenuItem->_Parent = _hMenu;
											MenuItem->_Pos = Contador;
											MenuItem->_hMenu = NULL;
											Contador ++; 
											_Items.push_back(MenuItem);
										}
									};
									//
									//! Función que retorna el numero total de menus
									// inline const unsigned int TotalMenus(void);
		 inline const unsigned int  TotalMenus(void) {
										return static_cast<unsigned int>(_Items.size()); 
									};
									//
									//! Función que retorna el menu especificado
									// inline DWLMenu *Menu(const unsigned int Pos);
		 inline DWLMenu            *Menu(const unsigned int Pos) { 
										return _Items[Pos]; 
									};
									//
									//! Operador que retorna el menu especificado
									// inline DWLMenu *operator[] (const unsigned int Pos);
		 inline DWLMenu            *operator[] (const unsigned int Pos) { 
										return _Items[Pos]; 
									};
									//
									//! Operador que retorna el handle de este menu
									// inline HMENU operator() (void);
		 inline HMENU               operator() (void) { 
										return _hMenu; 
									};
		private: ///////////////////// Metodos y atributos privados
									//
									//! Handle de este menu
		 HMENU                     _hMenu;
									//
									//! ID de este menu
		 int                       _ID;
									//
									//! Menu padre de este menu 
		 HMENU                     _Parent;
									//
									//! Posicion de este menu
		 int                       _Pos;
									//
									//! Valor para saber si es el ,menu principal o no
		 bool                       Padre;
									//
									//! Este vector contiene todos los MenuItems y SubMenus de este menu
		 std::vector<DWLMenu *>    _Items;
									//
									//! Este bitmap contiene el dibujo del estado check de este menu
		 HBITMAP                   _Check;
									//
									//! Este bitmap contiene el dibujo del estado uncheck de este menu
		 HBITMAP                   _UnCheck;
									//
									//! Creo una amistad entre esta misma clase para poder acceder a las variables privadas
		 friend class               DWLMenu;
		};							//
		////////////////////////////// Final DWLMenu

	}
}

#endif // DWL_MENU_H















