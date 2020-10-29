#include "DWLMedidasSistema.h"
#include "DWL.h"

namespace DWL {
    namespace SO {

	    int DWLMedidasSistema::Alto_BarraTitulo(void) {
		    return GetSystemMetrics(SM_CYCAPTION);
	    }

	    int DWLMedidasSistema::Ancho_Borde(void) {
		    return GetSystemMetrics(SM_CXSIZEFRAME);
	    }

	    int DWLMedidasSistema::Alto_Borde(void) {
		    return GetSystemMetrics(SM_CYSIZEFRAME); // SM_CYBORDER
	    }

	    int DWLMedidasSistema::Ancho_Cursor(void) {
		    return GetSystemMetrics(SM_CXCURSOR);
	    }

	    int DWLMedidasSistema::Alto_Cursor(void) {
		    return GetSystemMetrics(SM_CYCURSOR);
	    }

	    int DWLMedidasSistema::Ancho_Escritorio(void) {
		    return GetSystemMetrics(SM_CXFULLSCREEN);
	    }

	    int DWLMedidasSistema::Alto_Escritorio(void) {
		    return GetSystemMetrics(SM_CYFULLSCREEN);
	    }

	    int DWLMedidasSistema::Ancho_ScrollBar(void) {
		    return GetSystemMetrics(SM_CXVSCROLL);
	    }

	    int DWLMedidasSistema::Alto_ScrollBar(void) {
		    return GetSystemMetrics(SM_CYVSCROLL);
	    }
    };
};
 