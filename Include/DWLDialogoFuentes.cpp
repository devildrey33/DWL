/*! \file		DWLDialogoFuentes.cpp
	\brief		Archivo que contiene una clase para mostrar un dialogo para seleccionar una fuente del sistema.
	\author		devildrey33
	\date		Creado el [10/06/2004], ultima modificación el [05/10/2010]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es																			\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

*/ 


#ifndef DWL_DIALOGOFUENTES_CPP
#define DWL_DIALOGOFUENTES_CPP

#include "DWLDialogoFuentes.h"
#include <commdlg.h>
//#include <shlobj.h>             // Libreria para los objetos Shell

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Ventanas
	namespace Ventanas {

			//! Función que muestra el diálogo seleccionar una fuente.
			/*!	Función que muestra el diálogo seleccionar una fuente.
					\fn			LOGFONT MostrarFuentes(void);
					\return		Devuelve la fuente selecionada.
			*/
			LOGFONT	DWLDialogoFuentes::MostrarFuentes(void) {
				CHOOSEFONT     cf;
				DWORD          rgbCurrent = RGB(0, 0, 0);
				ZeroMemory(&cf, sizeof(cf));
				cf.lStructSize = sizeof (cf);
				cf.hwndOwner = NULL;
				cf.lpLogFont = &_Fuente;
				cf.rgbColors = rgbCurrent;
				cf.Flags = CF_SCREENFONTS | CF_EFFECTS;
				ChooseFont(&cf);
				return _Fuente; 
			};


	}
}


#endif // DWL_DIALOGOSCOMUNES_CPP
