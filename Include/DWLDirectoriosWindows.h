/*! \file DWLDirectoriosWindows.h
	\brief      Archivo que contiene funciones para obtener varios directorios de windows.
	\details	La clase DWLDirectoriosWindows es una clase para obtener directorios especiales de windows con relativa facilidad.		\n

    \author		devildrey33
	\version	0.96
	\date		07/07/2010

	\remarks
				Archivo creado por devildrey33 el dia [14/02/2009] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)															\n

*/
 
#ifndef DWL_DIRECTORIOSWINDOWS
#define DWL_DIRECTORIOSWINDOWS

// Macro que define las compatibilidades para esta clase, asignada a VC9 SOLO.
#define DWL_DIRECTORIOSWINDOWS_COMPATIBILIDAD   (COMPILADOR == COMPILADOR_VC9 || COMPILADOR == COMPILADOR_VC10)

//#include "DWL.h"
#include "DWLString.h"

#if DWL_DIRECTORIOSWINDOWS_COMPATIBILIDAD
	#include <KnownFolders.h>
	typedef HRESULT (WINAPI* TpSHGetKnownFolderPath)(const GUID& rfid, DWORD dwFlags, HANDLE hToken, PWSTR *path);
#else
	#if defined UNICODE
		typedef HRESULT (WINAPI* TpSHGetFolderPath)(HWND hwnd, int csidl, HANDLE hToken, DWORD dwFlags, LPWSTR pszPath);
	#else
		typedef HRESULT (WINAPI* TpSHGetFolderPath)(HWND hwnd, int csidl, HANDLE hToken, DWORD dwFlags, LPSTR pszPath);
	#endif
#endif


//! Espacio de nombres DWL
namespace DWL {

//	class DWLString;
	template <class DWL_TIPO_APP> class DWLSO;


    //! Espacio de nombres DWL
    namespace SO {
	    //! Clase para obtener rutas especiales de windows
	    class DWLDirectoriosWindows {
	     public: ///////////////////////// Miembros publicos

									    //! Constructor.
									    /*! Constructor.
											    \fn			DWLDirectoriosWindows(void);
											    \return		No devuelve nada.
									    */
									    DWLDirectoriosWindows(void);

									    //! Destructor.
									    /*! Destructor.
											    \fn			~DWLDirectoriosWindows(void);
											    \return		No devuelve nada.
									    */
								       ~DWLDirectoriosWindows(void);


									    //! Función que retorna el directorio AppData para todos los usuarios del sistema.
									    /*! Esta función devuelve el directorio AppData para todos los usuarios del sistema en la clase DWLString proporcionada.
											    \fn			BOOL AppData(DWL::DWLString &StrOut);
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
											    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\All Users\Application Data",
														    si queremos obtener la ruta para el usuario actual debemos usar la función AppData_UsuarioActual.
									    */
		    BOOL					    AppData(DWL::DWLString &StrOut);

									    //! Función que retorna el directorio AppData del usuario actual.
									    /*! Esta función devuelve el directorio AppData común del usuario actual en la clase DWLString proporcionada.
											    \fn			BOOL AppData_UsuarioActual(DWL::DWLString &StrOut);
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
											    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\USUARIO ACTUAL\Application Data",
														    si queremos obtener la ruta para todos los usuarios debemos usar la función AppData.
									    */
		    BOOL					    AppData_UsuarioActual(DWL::DWLString &StrOut);

									    //! Función que retorna el directorio usado como escritorio común.
									    /*! Esta función devuelve el directorio usado como escritorio común en la clase DWLString proporcionada.
											    \fn			BOOL Escritorio(DWL::DWLString &StrOut);
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
											    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\All Users\Desktop",
														    si queremos obtener la ruta para el usuario actual debemos usar la función Escritorio_UsuarioActual.
									    */
		    BOOL					    Escritorio(DWL::DWLString &StrOut);

									    //! Función que retorna el directorio usado como escritorio del usuario actual.
									    /*! Esta función devuelve el directorio usado como escritorio del usuario actual en la clase DWLString proporcionada.
											    \fn			BOOL Escritorio_UsuarioActual(DWL::DWLString &StrOut);
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
											    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\USUARIO ACTUAL\Desktop",
														    si queremos obtener la ruta para todos los usuarios debemos usar la función Escritorio.
									    */
		    BOOL					    Escritorio_UsuarioActual(DWL::DWLString &StrOut);

									    //! Función que retorna el directorio usado como Menú inicio -> Programas.
									    /*! Esta función devuelve el directorio usado como Menú inicio -> Programas en la clase DWLString proporcionada.
											    \fn			BOOL MenuInicio_Programas(DWL::DWLString &StrOut);
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
											    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\All Users\Programs".
									    */
		    BOOL					    MenuInicio_Programas(DWL::DWLString &StrOut);

									    //! Función que retorna el directorio usado como Menú inicio -> Programas del usuario actual.
									    /*! Esta función devuelve el directorio usado como Menú inicio -> Programas del usuario actual en la clase DWLString proporcionada.
											    \fn			BOOL MenuInicio_Programas_UsuarioActual(DWL::DWLString &StrOut);
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
											    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\USUARIO ACTUAL\Programs".
									    */
		    BOOL					    MenuInicio_Programas_UsuarioActual(DWL::DWLString &StrOut);

									    //! Función que retorna el directorio usado como Mis Documentos.
									    /*! Esta función devuelve el directorio usado como Mis Documentos en la clase DWLString proporcionada.
											    \fn			BOOL MisDocumentos(DWL::DWLString &StrOut);
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
											    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\All Users\Documents".
									    */
		     BOOL					    MisDocumentos(DWL::DWLString &StrOut);

									    //! Función que retorna el directorio usado como Mis Documentos para el usuario actual.
									    /*! Esta función devuelve el directorio usado como Mis Documentos para el usuario actual en la clase DWLString proporcionada.
											    \fn			BOOL MisDocumentos_UsuarioActual(DWL::DWLString &StrOut);
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
											    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\USUARIO ACTUAL\Documents".
									    */
		    BOOL	    				MisDocumentos_UsuarioActual(DWL::DWLString &StrOut);

									    //! Función que retorna el directorio usado como Mis Imagenes.
									    /*! Esta función devuelve el directorio usado como Mis Imagenes en la clase DWLString proporcionada.
											    \fn			BOOL MisImagenes(DWL::DWLString &StrOut);
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
											    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\All Users\Documents\My Pictures".
									    */
		    BOOL					    MisImagenes(DWL::DWLString &StrOut);

									    //! Función que retorna el directorio usado como Mis Imagenes para el usuario actual.
									    /*! Esta función devuelve el directorio usado como Mis Imagenes para el usuario actual en la clase DWLString proporcionada.
											    \fn			BOOL MisImagenes_UsuarioActual(DWL::DWLString &StrOut);
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
											    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\USUARIO ACTUAL\Documents\My Pictures".
									    */
		    BOOL					    MisImagenes_UsuarioActual(DWL::DWLString &StrOut);

									    //! Función que retorna el directorio usado como Mi Música.
									    /*! Esta función devuelve el directorio usado como Mi Música en la clase DWLString proporcionada.
											    \fn			BOOL MiMusica(DWL::DWLString &StrOut);
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
											    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\All Users\Documents\My Music".
									    */
		    BOOL					    MiMusica(DWL::DWLString &StrOut);

									    //! Función que retorna el directorio usado como Mi Música para el usuario actual.
									    /*! Esta función devuelve el directorio usado como Mi Música para el usuario actual en la clase DWLString proporcionada.
											    \fn			BOOL MiMusica_UsuarioActual(DWL::DWLString &StrOut);
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
											    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\USUARIO ACTUAL\Documents\My Music".
									    */
		     BOOL					    MiMusica_UsuarioActual(DWL::DWLString &StrOut);

									    //! Función que retorna el directorio usado como Mis Videos.
									    /*! Esta función devuelve el directorio usado como Mis Videos en la clase DWLString proporcionada.
											    \fn			BOOL MisVideos(DWL::DWLString &StrOut);
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
											    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\All Users\Documents\My Videos".
									    */
		     BOOL					    MisVideos(DWL::DWLString &StrOut);

									    //! Función que retorna el directorio usado como Mis Videos para el usuario actual.
									    /*! Esta función devuelve el directorio usado como Mi Música para el usuario actual en la clase DWLString proporcionada.
											    \fn			const BOOL	MisVideos_UsuarioActual(DWL::DWLString &StrOut);
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
											    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\USUARIO ACTUAL\Documents\My Videos".
									    */
		     BOOL					    MisVideos_UsuarioActual(DWL::DWLString &StrOut);


									    //! Función que retorna el directorio que contiene Windows.
									    /*! Esta función devuelve el directorio usado directorio  raíz de windows en la clase DWLString proporcionada.
											    \fn			BOOL Windows(DWL::DWLString &StrOut);
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
											    \remarks    Esta función devuelve una ruta tipo : "C:\Windows".
									    */
              BOOL					    Windows(DWL::DWLString &StrOut);

	#if (COMPILADOR != COMPILADOR_VC6)
	     protected : ///////////////////// Miembros protegidos
	#endif
									    //! Función que inicia esta clase.
									    /*! Esta función inicia la clase de forma que carga la libreria Shell32 y la funcion SHGetKnownFolderPath.
											    \fn			void _Iniciar(void);
											    \return		No devuelve nada.
											    \remarks    Función de uso interno para la DWL.
									    */
	        void	                   _Iniciar(void);

									    //! Función que llamara a SHGetFolderPath si es posible.
									    /*! Esta función llamara a SHGetFolderPath si es posible.
											    \fn			BOOL _ObtenerDirectorioV5(int CSLID, DWL::DWLString &StrOut);
                                                \param[in]  CSLID  : ID en formato CSLID del directorio a obtener.
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE en caso de exito, FALSE en caso de error.
											    \remarks    Función de uso interno para la DWL.
									    */
            BOOL				       _ObtenerDirectorioV5(int CSLID, DWL::DWLString &StrOut);

									    //! Modulo shell32.
		    HMODULE	                   _Shell32;

                                        //! Version mayor de windows
            unsigned long              _VersionMayor;
          private: /////////////////////// Miembros privados
                                        //! Operador = des-habilitado
            inline HFONT                operator=(const DWL::SO::DWLDirectoriosWindows &) { };
    #if DWL_DIRECTORIOSWINDOWS_COMPATIBILIDAD
                                        //! Constructor copia des-habilitado
                                        DWLDirectoriosWindows(const DWL::SO::DWLDirectoriosWindows &) : _Shell32(NULL), _VersionMayor(0), _SHGetKnownFolderPath(NULL) { };
									    //! Función que llamara a SHGetKnownFolderPath si es posible.
									    /*! Esta función llamara a SHGetKnownFolderPath si es posible.
											    \fn			BOOL _ObtenerDirectorioV5(int CSLID, DWL::DWLString &StrOut);
                                                \param[in]  rfid   : ID en formato GUID del directorio a obtener.
											    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
											    \return		Devuelve TRUE en caso de exito, FALSE en caso de error.
											    \remarks    Función de uso interno para la DWL.
									    */
            BOOL				       _ObtenerDirectorioV6(const GUID& rfid, DWL::DWLString &StrOut);

									    //! Función SHGetKnownFolderPath (Funciona a partir de Windows 6.x y no se puede usar bajo VC6 y DevC++).
		    TpSHGetKnownFolderPath	   _SHGetKnownFolderPath;
    #else
                                        //! Constructor copia des-habilitado
                                        DWLDirectoriosWindows(const DWL::SO::DWLDirectoriosWindows &) : _Shell32(NULL), _VersionMayor(0), _SHGetFolderPath(NULL)  { };

                                        //! Función SHGetFolderPath (para VC6 y DevC++)
		    TpSHGetFolderPath		   _SHGetFolderPath;
    #endif
									    //! Clase amiga DWLSO.
	#if (COMPILADOR == COMPILADOR_VC6)
		    friend class DWL::DWLSO;
	#else
		    template <class DWL_TIPO_APP> friend class DWL::DWLSO;
	#endif
	    };
    };
};

#endif
