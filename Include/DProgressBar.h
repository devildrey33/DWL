#ifndef DIMAGELIST_H
	#define DIMAGELIST_H

	#include "DControlEstandard.h"

	namespace DWL {
		class DProgressBar : public DControlEstandard {
		public :
						    DProgressBar(void);
				           ~DProgressBar(void) { };
			HWND            CrearProgressBar(DBaseWnd *Padre, const UINT nEstilos, const int cX, const int cY, const int cAncho, const int cAlto, const UINT nID, const int nMin = 0, const int nMax = 100, const int nValor = 0);
							// -Función para asignar el minimo y el maximo para la progressbar 
							//  (PBM_SETRANGE)
			void            AsignarRango(const int Minimo, const int nMaximo);
							// -Función para obtener el minimo y el maximo de la progressbar 
							//  (PBM_GETRANGE)
			void            ObtenerRango(int &nMinimo, int &nMaximo);
							// -Función para obtener el minimo de la progressbar 
							//  (PBM_GETRANGE)
			const int       Minimo(void);
							// -Función para obtener el maximo de la progressbar 
							//  (PBM_GETRANGE)
			const int		Maximo(void);

							// -Función para asignar el valor de la progressbar (PBM_GETPOS)
			void			Valor(const int nValor);
							// -Función para obtener el valor de la progressbar (PBM_SETPOS) 
							//  (ojo que devuelve UINT)
			const UINT		Valor(void);
		};
	};

#endif