#pragma once
#include "..\..\Include\DWLDialogo.h"
#include "..\..\Include\DWLBarraEx.h"

class VentanaMain :	public DWL::Ventanas::DWLDialogo {
public:
								VentanaMain(void);
	                           ~VentanaMain(void);
 void							Crear(void);
 BOOL    						Evento_Cerrar(void);
// LRESULT CALLBACK				GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
 DWL::ControlesEx::DWLBarraEx	Barra1;
 DWL::ControlesEx::DWLBarraEx	Barra2;
};
