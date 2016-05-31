// Ventana.cpp: define el punto de entrada de la aplicación.
//

#include "stdafx.h"
#include "Ventana.h"






const int AppVentana::Evento_Empezar(void) {
	V.Crear();
	return 0;
}

void Ventana::Crear(void) {
	DVentana::Crear(NULL, TEXT("VentanaDWL"), TEXT("Ventana"), 100, 100, 300, 300, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
}

LRESULT Ventana::Evento_Cerrar(void) {
	App.Terminar();
	return 0;
}