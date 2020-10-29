#pragma once
#include "..\..\Include\DWLVentana.h"
#include "..\..\Include\DWLMarcaEx.h"

class VentanaMain :	public DWL::Ventanas::DWLVentana {
public:
								VentanaMain(void);
	                           ~VentanaMain(void);
 void							Crear(void);
 LRESULT						Evento_Cerrar(void);
 LRESULT						Evento_MarcaEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDMarcaEx);
// LRESULT CALLBACK				GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
 DWL::ControlesEx::DWLMarcaEx	Marca1;
 DWL::ControlesEx::DWLMarcaEx	Marca2;
};
