#pragma once

#include "..\..\DWL\DAplicacion.h"
#include "..\..\DWL\DVentana.h"


using namespace DWL;


class Ventana : public DVentana {
  public:
	void	Crear();
	LRESULT Evento_Cerrar();
};

class AppVentana : public DAplicacion {
  public:
	                        AppVentana(void) {};
	                       ~AppVentana(void) {};
	const int				Evento_Empezar(void);

	Ventana					V;
};

DWL_INICIAR(AppVentana);

// Creo la macro App que sera una referencia publica a la clase AppListView
#define App DWL_APP(AppVentana)