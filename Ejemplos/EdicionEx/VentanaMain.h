#pragma once
#include "..\..\Include\DWLVentana.h"
//#include "..\..\Include\DWLEdicionEx.h"
#include "..\..\Include\DWLEdicionEx.h"

class VentanaMain :	public DWL::Ventanas::DWLVentana {
public:
								VentanaMain(void);
							   ~VentanaMain(void);
 void							Crear(void);
 LRESULT						Evento_Cerrar(void);
// LRESULT CALLBACK				GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
 DWL::ControlesEx::DWLEdicionEx	Edit1;
 DWL::ControlesEx::DWLEdicionEx	Edit2;
};
