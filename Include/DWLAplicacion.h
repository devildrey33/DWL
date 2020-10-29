//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DWLAplicacion.h																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Descripción :																																//
//					Este control simula un checkbox de windows.																					//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Este archivo contiene varias clases descritas a continuacion :																				//
// - DWLAplicacion			:	Clase base para nuestras aplicaciones la cual heredaremos al crear una aplicación.								//
//								Debes re-escribir la funcion "const BOOL DWLAplicacion::Inicio(void)" que sera el nuevo main de la aplicación.	//																																				//
//								La funcion Inicio debe retornar TRUE si quieres pasar al bucle de mensajes para ventanas, FALSE para terminar.	//
//																																				//
// - _DWLApp				:	Clase plantilla de uso interno que contiene y inicia la aplicación y la DWL.									//
//								No debes usar esta clase bajo ningún concepto.																    //
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Este archivo ademas de contener clases contiene funciones y macros para iniciar la DWL y facilitarnos su uso :								//
// - DWL_Iniciar			:	Función plantilla que inicia la DWL. Uso : DWL_Iniciar<MiAppHeredada>();										//
// - DWL_ObtenerApp			:	Función plantilla que devuelve una referencia a nuestra clase MiAppHeredada.									//
//								Uso : MiAppHeredada &App = DWL_ObtenerApp<MiAppHeredada>();														//
//									  HINSTANCE      I   = App.Instancia();																		//
// - DWLAPP					:	Macro que crea una referencia a nuestra clase MiAppHeredada en el objeto App.									//
//								Uso : DWLAPP(MiAppHeredada); // Seria como hacer "MiAppHeredada &App = DWL_ObtenerApp<MiAppHeredada>();"		//
//								      HINSTANCE I = App.Instancia();																			//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Archivo creado por devildrey33 el dia 30/11/2009	para http://www.devildrey33.es																//
// Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :		//
//  http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																		//
//  http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)																//
//  http://www.softcatala.cat/wiki/GPL3		 (Catalá, traduccion no oficial)																	//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Version 0.95																																	//
// Ultima modificación : 02/12/2009																												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file DWLAplicacion.h
	\brief Archivo que contiene las clases que inician una instancia de la DWL
*/
#ifndef DWL_APLICACION_H
#define DWL_APLICACION_H

//#include "DWLDebug.h"
#include "DWLString.h"
#include "DWLMedidasSistema.h"
#include "DWLDirectoriosWindows.h"
#include "DWLPortaPapeles.h"
#include "DWLRegistro.h"
#include "DWLVentanaErrorGrave.h"
//#include "DWLToolTipEx.h"

//! Espacio de nombres DWL
namespace DWL {

	//! Clase base para las aplicaciones DWL
	class DWLAplicacion {
	 public: ///////////////////////////////// Miembros publicos

										    //! Constructor.
										    /*! Constructor.
												    \fn			DWLAplicacion(void);
												    \return		No devuelve nada.
										    */
										    DWLAplicacion(void);

										    //! Destructor.
										    /*! Destructor .
												    \fn			~DWLAplicacion(void);
												    \return		No devuelve nada.
										    */
							               ~DWLAplicacion(void);

										    //! Función que obtiene el directorio donde esta situada nuestra aplicación.
										    /*! Esta función obtiene el directorio donde esta situada nuestra aplicación.
												    \fn			void Directorio(DWL::DWLString &Str);
												    \param[out] Str : Referencia a la clase DWLString donde se va a guardar el path de nuestra aplicacion.
												    \return		No devuelve nada.
										    */											
	    void				    			Directorio(DWL::DWLString &Str);

										    //! Función que obtiene la ruta completa de nuestra aplicación.
										    /*! Esta función obtiene la ruta completa de nuestra aplicación, incluyendo el nombre del ejecutable.
												    \fn			void Ejecutable(DWL::DWLString &Str);
												    \param[out] Str : Referencia a la clase DWLString donde se va a guardar la ruta de nuestra aplicacion.
												    \return		No devuelve nada.
										    */											
        void		    					Ejecutable(DWL::DWLString &Str);

										    //! Función virtual que es llamada al iniciar la aplicacion.
										    /*! Esta función virtual es llamada al iniciar la aplicacion.
												    \fn			virtual const BOOL Inicio(void);
												    \return		Devuelve TRUE si quieres continuar con el BucleMensajes, FALSE para abortar la ejecución.
												    \remarks	Esta funcion vendria a ser nuestro WinMain, si no quieres que luego se usen las funciones
															    BucleMensajes() y Fin() devuelve FALSE.
										    */											
	    virtual const BOOL	    			Inicio(void) { return TRUE; };

										    //! Función virtual que es llamada al terminar la aplicacion.
										    /*! Esta función virtual es llamada al terminar la aplicacion.
												    \fn			virtual void Fin(void);
												    \return		No devuelve nada.
												    \remarks	Esta funcion es llamada cuando se ha terminado el BucleMensajes.
										    */											
	    virtual void		    			Fin(void) {	};

										    //! Función virtual que contiene un bucle de mensajes estandar.
										    /*! Esta función virtual contiene un bucle de mensajes estandar.
												    \fn			virtual int BucleMensajes(void);
												    \return		Devuelve el ultimo mensaje.
										    */											
	    virtual int 			    		BucleMensajes(void);

										    //! Función que devuelve el HINSTANCE de nuestra aplicación.
										    /*! Esta función devuelve el HINSTANCE de nuestra aplicación.
												    \fn			inline HINSTANCE Instancia(void);
												    \return		Devuelve el HINSTANCE de nuestra aplicación.
										    */											
		inline HINSTANCE				    Instancia(void) { return GetModuleHandle(NULL);	};

	 protected : ///////////////////////// Miembros protegidos


//      friend class					        DWLSO;
	};									//
	////////////////////////////////////// Fin DWLAplicacion


    template <class DWL_TIPO_APP> class DWL_Iniciar;

	//! Plantilla que contiene la clase Sistema, y dentro tiene la clase aplicación. (POR COMENTAR)
    template <class DWL_TIPO_APP> class DWLSO {
       public :
                                            DWLSO(void) { };
                                           ~DWLSO(void) { };
        DWL_TIPO_APP                        App;
        SO::DWLMedidasSistema			    Medidas;
        SO::DWLDirectoriosWindows           Directorio;
        SO::DWLPortaPapeles                 PortaPapeles;
        SO::DWLRegistro                     Registro;
	    inline const DWORD					VersionMayor(void) { return _VersionMayor; };
	    inline const DWORD 					VersionMenor(void) { return _VersionMenor; };
	    inline const DWORD					VersionServicePackMayor(void) { return _VersionServicePackMayor; };
	    inline const DWORD 					VersionServicePackMenor(void) { return _VersionServicePackMenor; };
	#if (COMPILADOR != COMPILADOR_VC6)
       protected :
	#endif
        void			                   _Iniciar(void) { 
                                                OSVERSIONINFOEX osvi;
                                                srand(GetTickCount()); // Inicio semilla para numeros aleatorios
		                                        ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
		                                        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
		                                        GetVersionEx((OSVERSIONINFO *)&osvi);
		                                        _VersionMayor = osvi.dwMajorVersion;
		                                        _VersionMenor = osvi.dwMinorVersion;
												_VersionServicePackMayor = osvi.wServicePackMajor;
												_VersionServicePackMenor = osvi.wServicePackMinor;
		                                        Directorio._Iniciar();
												HRESULT R = CoInitializeEx(NULL, COINIT_MULTITHREADED);
                                            };
	#if (COMPILADOR == COMPILADOR_VC6)
       protected :
	#endif

	    DWORD				               _VersionMayor;
	    DWORD				               _VersionMenor;
	    DWORD				               _VersionServicePackMayor;
	    DWORD				               _VersionServicePackMenor;

        #if (COMPILADOR == COMPILADOR_VC9 || COMPILADOR == COMPILADOR_VC10)
            template <class DWL_TIPO_APP> friend class DWL::DWL_Iniciar; // VC 2008+
        #elif (COMPILADOR == COMPILADOR_MINGW)
            friend class DWL::DWL_Iniciar<DWL_TIPO_APP>;
        #elif (COMPILADOR == COMPILADOR_VC6)
			friend class DWL_Iniciar;
        #endif
    };





	//! Clase plantilla para iniciar la DWL y nuestra clase aplicación (POR COMENTAR)
    template <class DWL_TIPO_APP> class DWL_Iniciar {
      public : /////////////////////////////////////////// Miembros publicos
														//! Constructor vacio
                                                        DWL_Iniciar(void) { };
														//! Destructor vacio
                                                       ~DWL_Iniciar(void) { };

													    //! Función que ejecuta la instancia de nuestra aplicacion (POR RETOCAR)
        int                                             Ejecutar(DWL::SO::DWLEstilos *Estilos = NULL) { 
                                                            if (Estilos == NULL){
                                                                DWL::SO::DWLEstilos::Restaurar_Colores_Por_Defecto();
                                                                DWL::SO::DWLEstilos::IniciarFuentes();
                                                            }
                                                            else {
                                                                DWL::SO::DWLEstilos::Colores = Estilos->Colores;
                                                                DWL::SO::DWLEstilos::Fuentes = Estilos->Fuentes;
                                                            }
							                                int Ret = 0;
							                                Sistema._Iniciar();
                                                            if (Sistema.App.Inicio() == TRUE){
								                                Ret = Sistema.App.BucleMensajes();
								                                Sistema.App.Fin();
							                                }
							                                return Ret;
                                                        };

														//! Plantilla que contiene la variable Sistema
        static DWLSO<DWL_TIPO_APP>                      Sistema;
    };

	//! Definición para el miembro estatico Sistema de la plantilla DWL_Iniciar
    template <class DWL_TIPO_APP> DWLSO<DWL_TIPO_APP> DWL_Iniciar<DWL_TIPO_APP>::Sistema;

	//! Definición del filtro por defecto para los errores graves
//	template <class DWL_TIPO_APP> LPTOP_LEVEL_EXCEPTION_FILTER DWL_Iniciar<DWL_TIPO_APP>::_FiltroPorDefecto = NULL;


    //! Macro que enlaza el sistema en el objeto por referencia SO
    #define DWL_Enlazar_Sistema(DWL_TIPO_APP) static DWL::DWLSO<DWL_TIPO_APP> &Sistema = DWL::DWL_Iniciar<DWL_TIPO_APP>::Sistema;
};  

#endif
