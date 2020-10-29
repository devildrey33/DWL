/*! \file DWLEnumsGDI.h
	\brief		  Modulo de definiciones y enumeraciones basicas para las clases graficas de la DWL
*/

#ifndef DWL_ENUMS_GDI_H
#define DWL_ENUMS_GDI_H

#include "DWL.h"
 
//! Enumeración de los colores del sistema
enum DWL_Enum_ColoresSistema {
	DWL_Enum_ColoresSistema_ScrollBar						= COLOR_SCROLLBAR,
	DWL_Enum_ColoresSistema_Fondo							= COLOR_BACKGROUND,
	DWL_Enum_ColoresSistema_CaptionActivo					= COLOR_ACTIVECAPTION,
	DWL_Enum_ColoresSistema_CaptionInactivo					= COLOR_INACTIVECAPTION,
	DWL_Enum_ColoresSistema_Menu							= COLOR_MENU,
	DWL_Enum_ColoresSistema_Ventana							= COLOR_WINDOW,
	DWL_Enum_ColoresSistema_MarcoVentana					= COLOR_WINDOWFRAME,
	DWL_Enum_ColoresSistema_TextoMenu						= COLOR_MENUTEXT,
	DWL_Enum_ColoresSistema_TextoVentana					= COLOR_WINDOWTEXT,
	DWL_Enum_ColoresSistema_TextoCaption					= COLOR_CAPTIONTEXT,
	DWL_Enum_ColoresSistema_BordeActivo						= COLOR_ACTIVEBORDER,
	DWL_Enum_ColoresSistema_BordeInactivo					= COLOR_INACTIVEBORDER,
	DWL_Enum_ColoresSistema_EspacioAplicaion				= COLOR_APPWORKSPACE,
	DWL_Enum_ColoresSistema_HighLight						= COLOR_HIGHLIGHT,
	DWL_Enum_ColoresSistema_HighLightText					= COLOR_HIGHLIGHTTEXT,
	DWL_Enum_ColoresSistema_CaraBoton						= COLOR_BTNFACE,
	DWL_Enum_ColoresSistema_SombraBoton						= COLOR_BTNSHADOW,
	DWL_Enum_ColoresSistema_TextoDesactivado				= COLOR_GRAYTEXT,
	DWL_Enum_ColoresSistema_TextoBoton						= COLOR_BTNTEXT,
	DWL_Enum_ColoresSistema_TextoCaptionInactivo			= COLOR_INACTIVECAPTIONTEXT,
	DWL_Enum_ColoresSistema_HighLightBoton					= COLOR_BTNHIGHLIGHT,
	DWL_Enum_ColoresSistema_3DSombraOscura					= COLOR_3DDKSHADOW,
	DWL_Enum_ColoresSistema_3DLuz							= COLOR_3DLIGHT,
	DWL_Enum_ColoresSistema_TextoInformacion				= COLOR_INFOTEXT, 
	DWL_Enum_ColoresSistema_FondoInformacion				= COLOR_INFOBK,
	#if (WINVER >= 0x0500)
		DWL_Enum_ColoresSistema_LuzCaliente					= COLOR_HOTLIGHT,
		DWL_Enum_ColoresSistema_GradientCaptionActivo		= COLOR_GRADIENTACTIVECAPTION,
		DWL_Enum_ColoresSistema_GradientCaptionInactivo		= COLOR_GRADIENTINACTIVECAPTION,
		#if (WINVER >= 0x0501)
			#if (COMPILADOR == COMPILADOR_VC9 || COMPILADOR == COMPILADOR_VC10)
				DWL_Enum_ColoresSistema_MenuHighLight		= COLOR_MENUHILIGHT,
				DWL_Enum_ColoresSistema_MenuBar				= COLOR_MENUBAR
			#endif
		#endif /* WINVER >= 0x0501 */
	#endif /* WINVER >= 0x0500 */
};

//! Enumeración de las brochas en stock
enum DWL_Enum_BrochasStock {
	DWL_Enum_BrochasStock_Blanca     = WHITE_BRUSH,
	DWL_Enum_BrochasStock_GrisClaro  = LTGRAY_BRUSH,
	DWL_Enum_BrochasStock_Gris       = GRAY_BRUSH,
	DWL_Enum_BrochasStock_GrisOscuro = DKGRAY_BRUSH,
	DWL_Enum_BrochasStock_Negra      = BLACK_BRUSH,
	DWL_Enum_BrochasStock_Nula       = NULL_BRUSH
};

//! Enumeración de las plumas en stock
enum DWL_Enum_PlumasStock {
	DWL_Enum_PlumasStock_Blanca		= WHITE_PEN,
	DWL_Enum_PlumasStock_Negra		= BLACK_PEN,
	DWL_Enum_PlumasStock_Nula		= NULL_PEN,
	DWL_Enum_PlumasStock_GrisClaro	= LTGRAY_BRUSH,
	DWL_Enum_PlumasStock_Gris		= GRAY_BRUSH,
	DWL_Enum_PlumasStock_GrisOscuro	= DKGRAY_BRUSH 
};


//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres GDI
	namespace GDI {
        //! Tipo definido DWLColoresSistema
		typedef long DWLColoresSistema;

        //! Tipo definido DWLBrochasStock
		typedef int  DWLBrochasStock;

        //! Tipo definido DWLPlumasStock
		typedef int  DWLPlumasStock;
	};
};

//! Macro para obtener el valor R de un COLORREF
#define DWL_RGB_OBTENER_R(ValorRGB)	static_cast<unsigned short>((ValorRGB & 0xFF) * 0x100)
//! Macro para obtener el valor G de un COLORREF
#define DWL_RGB_OBTENER_G(ValorRGB)	static_cast<unsigned short>(ValorRGB & 0xFF00)
//! Macro para obtener el valor B de un COLORREF
#define DWL_RGB_OBTENER_B(ValorRGB)	static_cast<unsigned short>((ValorRGB & 0xFF0000) / 0x100)


#endif
