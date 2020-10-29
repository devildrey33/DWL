#ifndef DWL_CLASEMEDIDASSISTEMA_H
#define DWL_CLASEMEDIDASSISTEMA_H

//! Espacio de nombres DWL
namespace DWL {
    namespace SO {

	    // Clase que retornara los tamaños del sistema (bordes, titulo, etc...)
	    // Se basa en la API GetSystemMetrics
	    class DWLMedidasSistema {
	     public:
				    DWLMedidasSistema(void)		{ };
			       ~DWLMedidasSistema(void)		{ };

	     int	    Alto_BarraTitulo(void);

	     int	    Ancho_Borde(void);
	     int	    Alto_Borde(void);

	     int	    Ancho_Cursor(void);
	     int	    Alto_Cursor(void);

	     int        Alto_Escritorio(void);
	     int        Ancho_Escritorio(void);

	     int        Alto_ScrollBar(void);
	     int        Ancho_ScrollBar(void);

	    };

    };
 
}


#endif
