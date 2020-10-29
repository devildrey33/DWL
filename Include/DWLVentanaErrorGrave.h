/*! \file DWLVentanaErrorGrave.h
	\brief Archivo que contiene una clase base para mostrar errores fatales en una ventana
*/
#ifndef DWL_VENTANAERRORGRAVE_H
#define DWL_VENTANAERRORGRAVE_H

//#include "DWLDebug.h"
#include "DWLVentana.h"
#include "DWLBotonEx.h"
#include "DWLVentana.h"
#include "DWLEdicionEx.h"

//! Espacio de nombres DWL
namespace DWL { 
    //! Espacio de nombres Ventanas
    namespace Ventanas {
        //! Clase que gestiona los errores graves, y guarda dumps
	    class DWLVentanaErrorGrave : public DWL::Ventanas::DWLVentana {
	      public :
										    DWLVentanaErrorGrave(void);
								           ~DWLVentanaErrorGrave(void);
										    // Eliminar PathDump y que lo calcule desde dentro 
										    // (chungo porque DirectoriosWindows se tiene que iniciar, y no podemos acceder a la instancia iniciada)
     	   virtual const BOOL		    	Crear(const TCHAR *PathDump);

     	   virtual const BOOL		    	Mostrar(struct _EXCEPTION_POINTERS* ExceptionInfo);

           virtual LRESULT			    	Evento_Cerrar(void);

    	   virtual LRESULT 	    			Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);

           virtual LRESULT					Evento_BotonEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDBotonEx, const UINT Param);

	       virtual const BOOL				CrearDump(struct _EXCEPTION_POINTERS* ExceptionInfo, const TCHAR *PathDump);

	      protected :

    //		DWL::DWLString				   _PathDump;
	       struct _EXCEPTION_POINTERS	  *_ExceptionInfo;
	       DWL::ControlesEx::DWLBotonEx	   _BotonTerminar;
	       DWL::ControlesEx::DWLBotonEx	   _BotonGuardar;
	       DWL::ControlesEx::DWLEdicionEx  _EditPathDump;
	    };
    };


};

#endif
