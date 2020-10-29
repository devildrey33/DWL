#pragma once
#include "..\..\Include\DWLVentana.h"
#include "..\..\Include\DWLComboBox.h"
#include "..\..\Include\DWLBotonEx.h"
#include "..\..\Include\DWLArbolEx.h"
#include "..\..\Include\DWLListaEx.h"
#include "..\..\Include\DWLBarraEx.h"
#include "..\..\Include\DWLMarcaEx.h"
#include "..\..\Include\DWLEdicionEx.h"
//#include "..\..\Include\DWLEdicionEx2.h"
#include "..\..\Include\DWLEdicionDesplegableEx.h"
#include "..\..\Include\DWLExplorarDirectorios.h"



enum Controles {
	Control_NoDefinido					= -1,
	Control_ArbolEx						= 0,
	Control_ListaEx						= 1,
	Control_BotonEx						= 2,
	Control_BarraEx						= 3,
	Control_MarcaEx						= 4,
	Control_EdicionTextoEx				= 5,
	Control_EdicionTextoExpandibleEx	= 6,
	Control_ExplorarDirectorios			= 7
};

class VentanaMain :	public DWL::Ventanas::DWLVentana {
public:
							    	VentanaMain(void);
	                               ~VentanaMain(void);
 void						    	Crear(void);
 void						    	CrearControl(void);
 void						    	DestruirControl(void);
 void						    	RepintarControl(void);
 LRESULT					    	Evento_Cerrar(void);
 LRESULT					    	Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);
 LRESULT					    	Evento_Temporizador(const UINT cID);
 LRESULT						    Evento_CambiandoTam(const UINT Lado, RECT *Rectangulo);
 void						    	PintarDatos(HDC hDC = NULL);
 LRESULT					    	Evento_BotonEx_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT IDBotonEx, const UINT Param);;
// LRESULT CALLBACK				    GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
 const DWORD				    	MirarObjetosGDI(void);
 const DWORD					    MirarObjetosUsuario(void);
 DWL::Controles::DWLComboBox	    ComboControles;
 DWL::ControlesEx::DWLBotonEx	    BotonCrear;
 DWL::ControlesEx::DWLBotonEx	    BotonDestruir;
 DWL::ControlesEx::DWLBotonEx	    BotonRepintar;
 DWL::Ventanas::Base::DWLBaseWnd   *ControlActual;
// DWL::ControlesEx::DWLEdicionEx2_Nucleo EditP;
// DWORD							ObjetosGDI;
// DWORD							ObjetosUsuario;
 Controles						    TipoControlActual;
};
