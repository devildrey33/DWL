/*! \file		DWLDialogoImpresoras.cpp
	\brief		Archivo que contiene una clase para mostrar un dialogo para seleccionar una directorio del sistema.
	\author		devildrey33
	\date		Creado el [10/06/2004], ultima modificación el [05/10/2010]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es																			\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

*/
 
#ifndef DWL_DIALOGOIMPRESORAS_CPP
#define DWL_DIALOGOIMPRESORAS_CPP

#include "DWLDialogoImpresoras.h"

//#include <shlobj.h>             // Libreria para los objetos Shell

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Ventanas
	namespace Ventanas {

		//! Función que muestra el dialogo del sistema para seleccionar una impresora.
		/*!	Esta función muestra el dialogo del sistema para seleccionar una impresora.
				\fn			BOOL MostrarImpresoras(HWND hWndPadre, PRINTDLG &pDlg, HINSTANCE hInstance = NULL);
				\param[in]	hWndPadre	: Cadena de caracteres con el titulo del dialogo
				\param[in]	pDlg		: Estructura que contiene los datos de la impresora seleccionada.
				\param[in]	hInstance	: Instancua de nuestra aplicacion (Puede ser NULL)
				\return		Devuelve 0 en caso de error, o cualquier otro valor si se realizo la operación correctamente.
		*/
		BOOL DWLDialogoImpresoras::MostrarImpresoras(HWND hWndPadre, PRINTDLG &pDlg, HINSTANCE hInstance) {
			if (hInstance == NULL) hInstance = GetModuleHandle(NULL);
			pDlg.lStructSize = sizeof(PRINTDLG);
			pDlg.hwndOwner = hWndPadre;
			pDlg.hInstance = hInstance;
			pDlg.Flags = PD_USEDEVMODECOPIES | PD_ALLPAGES | PD_RETURNDC | PD_NOSELECTION;
			pDlg.nFromPage = 1;
			pDlg.nToPage = 1;
			pDlg.nMinPage = 1;
			pDlg.nMaxPage = 0xffffU; // We do not know how many pages in the
									// document until the printer is selected and the paper size is known.
			pDlg.nCopies = 1;
			pDlg.hDC = 0;
			pDlg.hDevMode = NULL;
			pDlg.hDevNames = NULL;
			pDlg.lCustData = 0;
			pDlg.lpfnPrintHook = NULL;
			pDlg.lpfnSetupHook = NULL;
			pDlg.lpPrintTemplateName = NULL;
			pDlg.lpSetupTemplateName = NULL;
			pDlg.hPrintTemplate = NULL;
			pDlg.hSetupTemplate = NULL;


			/*_pDlg.lStructSize = sizeof(PRINTDLGEX);
			_pDlg.hwndOwner = hWndPadre;
			_pDlg.hDevMode = NULL;
			_pDlg.hDevNames = NULL;
			_pDlg.hDC = 0;
			_pDlg.Flags = PD_NOPAGENUMS | PD_RETURNDC;
			_pDlg.Flags2 = 0;
			_pDlg.ExclusionFlags = 0;
			_pDlg.nPageRanges = 1;
			_pDlg.nMaxPageRanges = 1;
			_pDlg.lpPageRanges = NULL;
			_pDlg.nMinPage = 1;
			_pDlg.nMaxPage = 1;
			_pDlg.nCopies = 1;
			_pDlg.hInstance = hInstance;
			_pDlg.lpPrintTemplateName = TEXT("Imprimir Control de calidad");
			_pDlg.lpCallback = NULL;
			_pDlg.nPropertyPages = 0;
			_pDlg.lphPropertyPages = NULL;
			_pDlg.nStartPage = START_PAGE_GENERAL;
			_pDlg.dwResultAction = 0;*/

/*
			_pDlg.nFromPage = 1;
			_pDlg.nToPage = 1;
			_pDlg.nMinPage = 1;
			_pDlg.nMaxPage = 0xffffU; // We do not know how many pages in the
			// document until the printer is selected and the paper size is known.
			_pDlg.nCopies = 1;
			_pDlg.hDevMode = NULL;
			_pDlg.hDevNames = NULL;
			_pDlg.lCustData = 0;
			_pDlg.lpfnPrintHook = NULL;
			_pDlg.lpfnSetupHook = NULL;
			_pDlg.lpPrintTemplateName = NULL;
			_pDlg.lpSetupTemplateName = NULL;
			_pDlg.hPrintTemplate = NULL;
			_pDlg.hSetupTemplate = NULL;
			// See if a range has been selected
			_pDlg.Flags |= (_startPos != _endPos)?PD_SELECTION:PD_NOSELECTION;*/
									
			int Error = PrintDlg(&pDlg);
			int SCODE = SCODE_CODE(Error);
			return Error;
		};

	}
}


#endif // DWL_DIALOGODIRECTORIOS_CPP
