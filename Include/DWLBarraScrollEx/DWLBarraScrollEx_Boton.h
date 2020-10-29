#ifndef DWL_BARRASCROLLEX_BOTON_H
#define DWL_BARRASCROLLEX_BOTON_H
 
#include "..\DWLEstilos.h"

namespace DWL {
	namespace ControlesEx {

		//! Clase que controla los botones extras añadidos a la barra de scroll
		class DWLBarraScrollEx_Boton {
		 public: ///// Miembros publicos

					//! Constructor.
					/*! Constructor por defecto.
						\fn			DWLBarraScrollEx_Boton(void);
						\return		No devuelve nada.
					*/
					DWLBarraScrollEx_Boton(void) : IDIcono(0), IDControl(0), Estado(0) ,Posicion() {
					};

					//! Constructor asignador.
					/*! Constructor que asigna los valores especificados.
						\fn			DWLBarraScrollEx_Boton(const UINT nIDIcono, const UINT nIDControl);
						\return		No devuelve nada.
					*/
					DWLBarraScrollEx_Boton(const UINT nIDIcono, const UINT nIDControl)  : IDIcono(nIDIcono), IDControl(nIDControl), Estado(0), Posicion() {
					};

					//! Destructor.
					/*! Destructor.
							\fn			~DWLBarraScrollEx_ParametrosClick(void);
							\return		No devuelve nada.
					*/
				   ~DWLBarraScrollEx_Boton(void) {
					};

					//! Recta con la posicion del boton
		 RECT		Posicion;

					//! ID del icono
		 UINT		IDIcono;

					//! ID para el boton
		 UINT		IDControl;

					//! Estado del boton
		 int		Estado;
		};			//
		////////////// Fin DWLBarraScrollEx_Boton


    };
};

#endif
