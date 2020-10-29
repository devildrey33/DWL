#include "DWLBrocha.h"
#include "DWLRecta.h"
#include "DWLhDC.h"
#include "DWLRegion.h"

//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres GDI
	namespace GDI {

	    //! Función para pintar una clase DWLRecta en una clase DWLhDC.
	    /*!	Esta función pinta una clase DWLRecta en una clase DWLhDC.
			    \fn		   inline void PintarRecta(DWLhDC &hDC, DWLRecta &R);
                \param[in] hDC : clase DWLhDC donde se va a pintar.
                \param[in] R   : clase DWLRecta que contiene el espacio a pintar.
			    \return    No devuelve nada.
	    */
		void DWLBrocha::PintarRecta(DWLhDC &hDC, DWLRecta &R) { 
			FillRect(hDC.hDC(), R.Recta(), _Brocha);
		};

	    //! Función para pintar una clase DWLRegion en una clase DWLhDC.
	    /*!	Esta función pinta una clase DWLRegion en una clase DWLhDC.
			    \fn		   inline void PintarRegion(DWLhDC &hDC, DWLRegion &R);
                \param[in] hDC : clase DWLhDC donde se va a pintar.
                \param[in] R   : clase DWLRecta que contiene el espacio a pintar.
			    \return    No devuelve nada.
	    */ 
		void DWLBrocha::PintarRegion(DWLhDC &hDC, DWLRegion &R) { 
			FillRgn(hDC.hDC(), R.Region(), _Brocha); 
		};

	    //! Función para enmarcar una clase DWLRecta en una clase DWLhDC.
	    /*!	Esta función enmarca una clase DWLRecta en una clase DWLhDC.
			    \fn		   inline void PintarRegion(DWLhDC &hDC, DWLRegion &R);
                \param[in] hDC : clase DWLhDC donde se va a pintar.
                \param[in] R   : clase DWLRecta que contiene el espacio a enmarcar.
			    \return    No devuelve nada.
	    */
		void DWLBrocha::EnmarcarRecta(DWLhDC &hDC, DWLRecta &R) { 
			FrameRect(hDC.hDC(), R.Recta(), _Brocha); 
		};

		//! Función para enmarcar una clase DWLRegion en una clase DWLhDC.
		/*!	Esta función enmarca una clase DWLRegion en una clase DWLhDC.
				\fn		   inline void EnmarcarRegion(DWLhDC &hDC, DWLRegion &R, const int cAncho = 1, const int cAlto = 1)
                \param[in] hDC    : clase DWLhDC donde se va a pintar.
                \param[in] R      : clase DWLRegion que contiene el espacio a enmarcar.
                \param[in] cAncho : Ancho en pixeles (1 por defecto).
                \param[in] cAlto  : Altura en pixeles (1 por defecto).
				\return    No devuelve nada.
		*/
		void DWLBrocha::EnmarcarRegion(DWLhDC &hDC, DWLRegion &R, const int cAncho, const int cAlto) {
			FrameRgn(hDC.hDC(), R.Region(), _Brocha, cAncho, cAlto); 
		};


	};
};
