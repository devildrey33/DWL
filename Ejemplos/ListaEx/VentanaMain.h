#pragma once
#include "..\..\Include\DWLVentana.h"
#include "..\..\Include\DWLListaEx.h"
#include "..\..\Include\DWLBotonEx.h"
#include "..\..\Include\DWLEdicionDesplegableEx.h"
#include "..\..\Include\DWLMarcaEx.h"
#include "..\..\include\DWLEstilos.h"

using namespace DWL;
using namespace DWL::ControlesEx;
//using namespace DWL::Estilos;

class VentanaMain :	public DWL::Ventanas::DWLVentana {
public:
								VentanaMain(void);
	                           ~VentanaMain(void);
 void							Crear(void);
 LRESULT						Evento_Cerrar(void);
 LRESULT						Evento_CambiandoTam(const UINT Lado, RECT *Rectangulo);
 LRESULT						Evento_ListaEx_Mouse_Click(const UINT Boton, const int cX, const int cY, DWL::ControlesEx::DWLListaEx_Item *nItem, const UINT IDListaEx);
 LRESULT                        Evento_ListaEx_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDListaEx);
 LRESULT                        Evento_BotonEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDBotonEx, const UINT Param);
 LRESULT                        Evento_MarcaEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDMarcaEx);
 LRESULT						Evento_EdicionDesplegableEx_CambioSeleccion(const TCHAR *NuevoTexto, const UINT IDEdicionTexto);

 DWLListaEx						Lista;

 DWLBotonEx                     Boton_BorrarItems;
 DWLBotonEx                     Boton_Mas20Items;
 DWLBotonEx                     Boton_AgregarColumna;
 DWLBotonEx                     Boton_BorrarColumna;

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

 DWL::SO::DWLEstilos_Fuente     Tahoma13;
 DWL::SO::DWLEstilos_Fuente     Comic21;
 DWL::SO::DWLEstilos_Fuente     Courier16;

 UINT                           IDBotonesScroll;
};