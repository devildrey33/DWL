/*! \file		DWLDialogoImpresoras.h
	\brief		Archivo que contiene una clase para mostrar un dialogo del sistema para seleccionar una impresora.
	\author		devildrey33
	\date		Creado el [10/06/2004], ultima modificación el [05/10/2010]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es																			\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

*/ 

#ifndef DWL_DIALOGOIMPRESORAS_H
#define DWL_DIALOGOIMPRESORAS_H

//#pragma warning( disable : 4786 )
//#include <vector>
#include "DWLString.h"
#include <commdlg.h>


//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Ventanas
	namespace Ventanas {
		//! Clase para mostrar el dialogo del sistema para seleccionar una impresora
		class DWLDialogoImpresoras {
		  public : /////////// Miembros publicos

							//! Constructor.
							/*!	Constructor por defecto.
									\fn		DWLDialogoImpresoras(void);
									\return	No devuelve nada.
							*/
							DWLDialogoImpresoras(void) {
							};

							//! Función que muestra el dialogo del sistema para seleccionar una impresora.
							/*!	Esta función muestra el dialogo del sistema para seleccionar una impresora.
									\fn			BOOL MostrarImpresoras(HWND hWndPadre, PRINTDLG &pDlg, HINSTANCE hInstance = NULL);
									\param[in]	hWndPadre	: Cadena de caracteres con el titulo del dialogo
									\param[in]	pDlg		: Estructura que contiene los datos de la impresora seleccionada.
									\param[in]	hInstance	: Instancua de nuestra aplicacion (Puede ser NULL)
									\return		Devuelve 0 en caso de error, o cualquier otro valor si se realizo la operación correctamente.
							*/
			BOOL			MostrarImpresoras(HWND hWndPadre, PRINTDLG &pDlg, HINSTANCE hInstance = NULL);
		};
	}
}


#endif // DWL_DIALOGOCOLORES_H


// Version 0.53 [15/08/2007]
// - Se ha solucionado un fallo en la clase DlgDirectorio que creaba una excepcion no valida al seleccionar "MI PC" como directorio

// Version 0.6  [01/10/2009]
// - Se ha añadido la opcion para que el dialogo abrir no tenga multiseleccion