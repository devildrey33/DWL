#ifndef DWL_MARCAEX_COLORES_H
#define DWL_MARCAEX_COLORES_H
 
#include "..\DWLEstilos.h"

namespace DWL {
	namespace ControlesEx {

		//! Clase que contiene los colores para el control DWLMarcaEx
		class DWLMarcaEx_Colores {
		public : ///////////////////////////// Miembros publicos

										    //! Constructor por defecto.
										    /*! Este constructor enlaza todos los colores a la clase DWLEstilos.
												    \fn			DWLMarcaEx_Colores(void);
												    \return		No devuelve nada.
										    */
										    DWLMarcaEx_Colores(void) :
											    BordeRectangulo(			&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_Normal),
											    BordeRectanguloFoco(		&DWL::SO::DWLEstilos::Colores.ControlEx_Borde_FocoRaton),
											    Fondo(						&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Normal),
											    FondoRectanguloResaltado(	&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Claro),
											    TextoNormal(				&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_Normal),
											    TextoPresionado(			&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_Presionado),
											    FondoRectanguloNormal(),
											    FondoRectanguloPresionado(),
											    TextoResaltado() {
                                                    FondoRectanguloNormal = RGB(220, 220, 220);
                                                    FondoRectanguloPresionado = RGB(200, 200, 200);
                                                    TextoResaltado = RGB(100, 100, 210);
										    };

										    //! Color del fondo
         DWL::SO::DWLEstilos_Color			Fondo;

										    //! Color del fondo del rectangulo que tiene la marca (normal)
		 DWL::SO::DWLEstilos_Color			FondoRectanguloNormal;

										    //! Color del fondo del rectangulo que tiene la marca (resaltado)
		 DWL::SO::DWLEstilos_Color			FondoRectanguloResaltado;

										    //! Color del fondo del rectangulo que tiene la marca (presionado)
		 DWL::SO::DWLEstilos_Color			FondoRectanguloPresionado;

										    //! Color del borde del rectangulo
		 DWL::SO::DWLEstilos_Color			BordeRectangulo;

										    //! Color del borde del rectangulo cuando el control tiene el foco
		 DWL::SO::DWLEstilos_Color			BordeRectanguloFoco;

										    //! Color del texto normal
		 DWL::SO::DWLEstilos_Color			TextoNormal;
			
										    //! Color del texto hilight
		 DWL::SO::DWLEstilos_Color			TextoResaltado;

										    //! Color del texto presionado
		 DWL::SO::DWLEstilos_Color			TextoPresionado;
		};								    //
		////////////////////////////////////// Final ColoresClaseMarcaEx

    };
};

#endif
