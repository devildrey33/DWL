// Clase para controlar aspectos basicos del raton

#ifndef DWL_MOUSE_H
#define DWL_MOUSE_H

enum DWL_Enum_Mouse_Cursor {
	DWL_Enum_Mouse_Cursor_FlechaReloj		= 32650,	// IDC_APPSTARTING
	DWL_Enum_Mouse_Cursor_FlechaVertical	= 32516,	// IDC_UPARROW
	DWL_Enum_Mouse_Cursor_Flecha			= 32512,	// IDC_ARROW
	DWL_Enum_Mouse_Cursor_Cruz				= 32515,    // IDC_CROSS
	DWL_Enum_Mouse_Cursor_Mano				= 32649,	// IDC_HAND
	DWL_Enum_Mouse_Cursor_Ayuda				= 32651,	// IDC_HELP
	DWL_Enum_Mouse_Cursor_IBeam				= 32513,	// IDC_IBEAM
	DWL_Enum_Mouse_Cursor_Cancelar			= 32648,	// IDC_NO
	DWL_Enum_Mouse_Cursor_Tam				= 32646,	// IDC_SIZEALL
	DWL_Enum_Mouse_Cursor_TamNESO			= 32643,	// IDC_SIZENESW
	DWL_Enum_Mouse_Cursor_TamNS				= 32645,	// IDC_SIZENS
	DWL_Enum_Mouse_Cursor_TamNOSE			= 32642,	// IDC_SIZENWSE
	DWL_Enum_Mouse_Cursor_TamEO				= 32644,	// IDC_SIZEWE
	DWL_Enum_Mouse_Cursor_Procesando		= 32514     // IDC_WAIT
}; 

namespace DWL {
	namespace SO {
		class DWLMouse {
		 public: ///////////////// Miembros publicos
								DWLMouse(void) {
								};


		 static HCURSOR			CambiarCursorEstandard(const DWL_Enum_Mouse_Cursor nCursor = DWL_Enum_Mouse_Cursor_Flecha) {
									HCURSOR Cur = LoadCursor(NULL, MAKEINTRESOURCE(nCursor));
									return SetCursor(Cur);
								};

		 static HCURSOR			CambiarCursor(HCURSOR nCursor) {
									return SetCursor(nCursor);
								};

		 static int				Visible(const BOOL nVisible) {
									int MRet = 0;
									if (nVisible == false) {
										MRet = ShowCursor(nVisible);
										while (MRet > -1) MRet = ShowCursor(nVisible);
									}
									else {
										MRet = ShowCursor(nVisible);
										while (MRet < 0) MRet = ShowCursor(nVisible);
									}
									return MRet;			
								};

		 static BOOL	        ObtenerPosicion(POINT *Pos) {
									return GetCursorPos(Pos);
								};

		 static BOOL			AsignarPosicion(const int cX, const int cY) {
									return SetCursorPos(cX, cY);
								};

		 static BOOL			AsignarPosicion(const POINT *nPos) {
									return SetCursorPos(nPos->x, nPos->y);
								};

		 static BOOL			AreaRaton(const RECT *nArea) {
									return ClipCursor(nArea);
								};
		};
	}
} 

#endif
// 20/03/2007
