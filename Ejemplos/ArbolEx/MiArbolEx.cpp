#include "StdAfx.h"
#include "MiArbolEx.h"


void MiArbolEx::BarraScrollEx_Evento_BotonExtendido_Click(DWL::ControlesEx::DWLBarraScrollEx_Boton *BotonExtendido) {
	if (BotonExtendido->IDControl == 100) MessageBox(_hWnd, TEXT("BotonExtendido presionado"), TEXT("Msg"), MB_OK);
}
