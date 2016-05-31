#ifndef DObjeto_H
#define DObjeto_H

#include <windows.h>
//#include "DDebug.h"

namespace DWL {

	enum DEnum_Objeto {
		DEnum_Objeto_Indefinido = 0,
		DEnum_Objeto_Aplicacion,
		DEnum_Objeto_BaseWnd,
		DEnum_Objeto_Debug,
		DEnum_Objeto_EventosBase,
		DEnum_Objeto_EventosPadre,
		DEnum_Objeto_String,
		DEnum_Objeto_Ventana,
		DEnum_Objeto_Button,
		DEnum_Objeto_ComboBox,
		DEnum_Objeto_ListView,
		DEnum_Objeto_ListView_Item,
		DEnum_Objeto_ListView_Columna,
		DEnum_Objeto_ListView_SubItem,
		DEnum_Objeto_ListView_DatosClick,
		DEnum_Objeto_ListView_DatosEdicion,
		DEnum_Objeto_TreeView,
		DEnum_Objeto_TreeView_Nodo,
		DEnum_Objeto_TreeView_DatosClick,
		DEnum_Objeto_ImageList,
		DEnum_Objeto_Split,
		DEnum_Objeto_Mouse,
		DEnum_Objeto_UnidadDisco,
		DEnum_Objeto_UnidadesDisco,
		DEnum_Objeto_DirectoriosWindows,
		DEnum_Objeto_Menu
	};

	/*
	template <const DEnum_Objeto OBJETO = DEnum_Objeto::Objeto_Indefinido> class DObjeto {
		public :

		virtual const DEnum_Objeto		Objeto_Tipo(void) { return OBJETO; };
	};*/
};

#endif