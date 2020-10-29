/*! \file		DWLDialogoColores.cpp
	\brief		Archivo que contiene una clase para mostrar un dialogo para seleccionar un color del sistema.
	\author		devildrey33
	\date		Creado el [10/06/2004], ultima modificación el [05/10/2010]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es																			\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

*/ 
#ifndef DWL_DIALOGOCOLORES_CPP
#define DWL_DIALOGOCOLORES_CPP

#include "DWLDialogoColores.h"
#include <commdlg.h>
//#include <shlobj.h>             // Libreria para los objetos Shell

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Ventanas
	namespace Ventanas {

			//! Función que muestra el diálogo seleccionar un color.
			/*!	Función que muestra el diálogo seleccionar un color.
					\fn			COLORREF MostrarColores(void);
					\return		Devuelve el cololr selecionado.
			*/
			COLORREF DWLDialogoColores::MostrarColores(void) { 
				CHOOSECOLOR     cc;
				static COLORREF acrCustClr[16];
				static DWORD    rgbCurrent;
				ZeroMemory(&cc, sizeof(cc));
				cc.lStructSize = sizeof(cc);
				cc.hwndOwner = NULL; 
				cc.lpCustColors = (LPDWORD)acrCustClr;
				cc.rgbResult = rgbCurrent;
				cc.Flags = CC_FULLOPEN | CC_RGBINIT;
				if (ChooseColor(&cc)==TRUE) { 
					_Color = cc.rgbResult;   
					return cc.rgbResult;  
				} 
				return 0;
			};  


	}
}


#endif // DWL_DIALOGOSCOMUNES_CPP
