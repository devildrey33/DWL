#pragma once
#include "..\..\Include\DWLVentana.h"
#include "..\..\Include\DWLBotonEx.h"

class VentanaMain :	public DWL::Ventanas::DWLVentana {
public:
								VentanaMain(void);
	                           ~VentanaMain(void);
 void							Crear(void);
 LRESULT						Evento_Cerrar(void);
 LRESULT						Evento_BotonEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDBotonEx, const UINT Param);
// LRESULT CALLBACK				GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
 DWL::ControlesEx::DWLBotonEx	Boton1;
 DWL::ControlesEx::DWLBotonEx	Boton2;
};