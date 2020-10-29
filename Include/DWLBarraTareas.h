/*! \file DWLBarraTareas.h
	\brief		 Archivo que contiene las definiciones para modificar la barra de tareas de windows 7.
    */ 
#ifndef DWL_BARRATAREAS_H
#define DWL_BARRATAREAS_H

#include <vector>
#include "DWLString.h"

#if COMPILADOR == COMPILADOR_VC10
	#include "Shobjidl.h"
#else
	#include "Compiladores\DWL_ITaskBar.h"
#endif


//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Ventanas
    namespace Ventanas {
        //! Espacio de nombres Base
        namespace Base {
			template <typename TIPO_DEVUELTO, const long VALOR_DEVUELTO> class DWLEventosPadre;

			//! Clase que contiene un botón de la TaskBar antes de su creación
			class DWLBarraTareas_Boton {
			  public :
							DWLBarraTareas_Boton(void) : IDIcono(0), ID(0) { };
							DWLBarraTareas_Boton(const UINT nIDIcono, const TCHAR *nTextoToolTip, const UINT nID) : IDIcono(nIDIcono), TextoToolTip(nTextoToolTip), ID(nID) { };
							DWLBarraTareas_Boton(const DWLBarraTareas_Boton &nBoton) : IDIcono(nBoton.IDIcono), TextoToolTip(nBoton.TextoToolTip), ID(nBoton.ID) { };
				UINT		IDIcono;
				DWLString	TextoToolTip;
				UINT        ID;
			};

			class DWLBarraTareas {
			  public :
													DWLBarraTareas(void);
				void								Resaltar(void);
				void								BarraProgreso_Estado_Normal(void);
				void								BarraProgreso_Estado_Pausa(void);
				void								BarraProgreso_Estado_Error(void);
				void								BarraProgreso_Valor(const UINT nValor, const UINT nMaximo);
				void								BarraProgreso_Ocultar(void);
				void								Boton_Agregar(UINT nIDIcono, const TCHAR *nTextoToolTip, const UINT nID);
				void								Boton_Activado(const UINT nID, const bool nActivado);
				void								Boton_Visible(const UINT nID, const bool nVisible);
				void								Boton_Icono(const UINT nID, const UINT IDIcono);
			#if COMPILADOR != COMPILADOR_VC6
			  private :
			#endif
				void		                       _CrearBotones(void);
				void                               _Enlazar(HWND *hWnd);
				void                               _ObtenerTaskBarList3(void);
				ITaskbarList3                     *_BarraTareas;
				HWND							  *_hWnd;
				std::vector<DWLBarraTareas_Boton>  _Botones;

			#if COMPILADOR != COMPILADOR_VC6
				template <typename TIPO_DEVUELTO, const long VALOR_DEVUELTO> friend class DWL::Ventanas::Base::DWLEventosPadre; // VC 2008+
			#endif
			};
		};
	};
};

#endif
