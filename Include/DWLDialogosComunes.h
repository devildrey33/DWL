/*! \file		DWLDialogosComunes.h
	\brief		Archivo enlaza a todas las cabeceras de los dialogos comunes.
	\author		devildrey33
	\date		Creado el [10/06/2004], ultima modificación el [05/10/2010]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es																			\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

*/ 
#ifndef DWL_DIALOGOSCOMUNES_H
#define DWL_DIALOGOSCOMUNES_H


#include "DWLDialogoAbrir.h"
#include "DWLDialogoGuardar.h"
#include "DWLDialogoColores.h"
#include "DWLDialogoFuentes.h"
#include "DWLDialogoImpresoras.h"
#include "DWLDialogoDirectorios.h"

#endif // DWL_DIALOGOSCOMUNES_H


// Version 0.53 [15/08/2007]
// - Se ha solucionado un fallo en la clase DlgDirectorio que creaba una excepcion no valida al seleccionar "MI PC" como directorio

// Version 0.6  [01/10/2009]
// - Se ha añadido la opcion para que el dialogo abrir no tenga multiseleccion