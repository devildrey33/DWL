#ifndef DAPLICACION_H
#define DAPLICACION_H

#include <vector>
#include <string>
#include "DObjeto.h"
#include <TCHAR.h> // Dejar esta cabecera ya que en ciertas ocasiones hay problemas con WinMain y _tWinMain

namespace DWL {

	template <typename TIPO_DEVUELTO> class DEventosPadre;

	// Clase base DAplicacion
	class DAplicacion {
	  public:
		virtual const DEnum_Objeto				Objeto_Tipo(void) { return DEnum_Objeto_Aplicacion; };
												DAplicacion(void);
		                                       ~DAplicacion(void);
		virtual const int                       Evento_Empezar(void)        { return 0; };
		virtual const int                       Evento_BuclePrincipal(void) { int Ret = 0; while (_Terminar == false) { Ret = EsperarEvento(); } return Ret; };
		virtual const int                       Evento_Terminar(void)       { return 0; };
		void                                    Terminar(void)              { _Terminar = true; };
		const int                               Ejecutar(void);
		const int                               EsperarEvento(void);
		void                                    MirarEvento(void);
		void                                    ObtenerPathApp(std::wstring &AppPath);
	  protected:
		bool								   _Terminar;
	};

	extern DAplicacion *_APLICACION;

	//#define DWL_APP(NOMBRE_CLASE_APP) NOMBRE_CLASE_APP App = (*static_cast<NOMBRE_CLASE_APP *>(_APLICACION));
	// Esta macro se utiliza para definir un acceso global a la clase aplicacion final
	// Ejemplo : #define App DWL_APP(MiClaseAplicacion)
#define DWL_APP(DAPLICACION) (*static_cast<DAPLICACION *>(_APLICACION)) 

	/*        // Funcion plantilla que devuelve la dirección de la clase aplicación
	template <typename TipoAplicacion> TipoAplicacion &DWLApp(void) {
	return *static_cast<TipoAplicacion *>(_APLICACION);
	}*/


	// Macro que crea la función WinMain 
	// Esta macro debe utilizarse el archivo de definiciones (.cpp) de nuestra clase aplicacion.
	// WinMain UNICODE
#define DWL_INICIAR(DAPLICACION)                                                                            \
	int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {	\
	return DWLIniciar<DAPLICACION>();                                                                   \
	};

	// Macro que crea la función WinMain que muestra una consola
	// Esta macro debe utilizarse el archivo de definiciones (.cpp) de nuestra clase aplicacion.
	// WinMain UNICODE
	#define DWL_INICIAR_CONSOLA(DAPLICACION)    \
		int _tmain(int argc, _TCHAR* argv[]) {	\
			return DWLIniciar<DAPLICACION>();   \
		};


	// Función plantilla que inicia la clase DAplicacion derivada
	template <typename TipoAplicacion> int DWLIniciar(void) {
		_APLICACION = new TipoAplicacion;
		int Ret = _APLICACION->Ejecutar();
		delete _APLICACION;
		return Ret;
/*#else
		TCHAR MensajeError[2048];
		try {
			_APLICACION = new TipoAplicacion;
			int Ret = _APLICACION->Ejecutar();
			delete _APLICACION;
			return Ret;
		}
		catch (DError &ErrorAplicacion) {
			wsprintf(MensajeError, TEXT("%s\n%s"), ErrorAplicacion.FuncionError(), ErrorAplicacion.MensajeError());
			//                wsprintf(MensajeError, TEXT("%s\n%s"), ErrorAplicacion.Objeto()->Objeto_Nombre(), ErrorAplicacion.MensajeError());
			MessageBox(NULL, MensajeError, TEXT("Error"), MB_ICONEXCLAMATION);
			// Si hay un error en GetLastError lo mostrara (parece que no....)
			//                DDebug::MostrarUltimoError(TEXT("GetLastError en formato texto :\n"), MensajeError);
			return -1;
		}
		catch (...) {
			return -1;
		}
#endif*/
	}

};

#endif