//#pragma once
#ifndef MIARBOLEX
#define MIARBOLEX
#include "..\..\Include\DWLArbolEx.h"

//using namespace DWL;

class MiArbolEx : public DWL::ControlesEx::DWLArbolEx {
public:
				MiArbolEx(void) {};
		       ~MiArbolEx(void) {};
 void			BarraScrollEx_Evento_BotonExtendido_Click(DWL::ControlesEx::DWLBarraScrollEx_Boton *BotonExtendido);
};

#endif