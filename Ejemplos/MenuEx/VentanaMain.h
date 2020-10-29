#pragma once
#include "..\..\Include\DWLVentana.h"
#include "..\..\Include\DWLMenuEx.h"

class VentanaMain :	public DWL::Ventanas::DWLVentana {
public:
								VentanaMain(void);
	                           ~VentanaMain(void);
 void							Crear(void);
 LRESULT						Evento_Cerrar(void);
 LRESULT						Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT wParam);
 LRESULT						Evento_MenuEx_Menu_Pulsado(DWL::ControlesEx::DWLMenuEx *MenuPulsado, const UINT IDMenuExPadre);
// LRESULT CALLBACK				GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
 DWL::ControlesEx::DWLMenuEx	Menu;
};
