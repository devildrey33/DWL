#pragma once
#include "..\..\Include\DWLVentana.h"
#include "..\..\Include\DWLBotonEx.h"
#include "..\..\Include\DWLEdicionDesplegableEx.h"
#include "..\..\Include\DWLMarcaEx.h"
#include "..\..\include\DWLEstilos.h"
#include "MiArbolEx.h"

using namespace DWL;
using namespace DWL::SO; 
using namespace DWL::ControlesEx;

class VentanaMain :	public DWL::Ventanas::DWLVentana {
public:
								VentanaMain(void);
	                           ~VentanaMain(void);
 void							Crear(void);
 LRESULT						Evento_Cerrar(void);
 LRESULT                        Evento_BotonEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDBotonEx, const UINT Param);
 LRESULT                        Evento_MarcaEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDMarcaEx);
 LRESULT						Evento_EdicionDesplegableEx_CambioSeleccion(const TCHAR *NuevoTexto, const UINT IDEdicionTexto);
 MiArbolEx						Arbol;
 DWLArbolEx_Nodo               *TmpNodo;
 DWLBotonEx                     Boton_BorrarNodos;
 DWLBotonEx                     Boton_Mas20Nodos;
 DWLBotonEx                     Boton_Mas20Hijos;
 DWLBotonEx                     Boton_BorrarBotonScroll;
 DWLBotonEx                     Boton_AgregarBoton;
 DWLBotonEx                     Boton_EliminarBoton;
 DWLBotonEx                     Boton_ColoresAleatorios;

 DWLMarcaEx                     Marca_Borde;
 DWLMarcaEx                     Marca_Iconos;
 DWLMarcaEx                     Marca_Lineas;
 DWLMarcaEx                     Marca_MultiSeleccion;
 DWLMarcaEx                     Marca_SubSeleccion;
 DWLMarcaEx                     Marca_Transparencias;

 DWLEdicionDesplegableEx        Combo_ScrollV;  
 DWLEdicionDesplegableEx        Combo_ScrollH;
 DWLEdicionDesplegableEx        Combo_Fuentes;

 DWLEstilos_Fuente              Tahoma13;
 DWLEstilos_Fuente              Comic21;
 DWLEstilos_Fuente              Courier16;

 UINT                           IDBotonesScroll;
};
