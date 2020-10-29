#pragma once

#include "..\..\Include\DWLAplicacion.h"



class ListaExApp : public DWL::DWLAplicacion {
  public :
				ListaExApp(void) { };
	           ~ListaExApp(void) { };
	const BOOL  Inicio(void) {
					Ventana.Crear();
					return TRUE;
				};
  protected :
	VentanaMain Ventana;
};

//DWL::DWLSistema<ListaExApp> &Sistema = DWL::DWL_Iniciar2<ListaExApp>::Sistema;
DWL_Enlazar_Sistema(ListaExApp);
