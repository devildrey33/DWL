/*! \file DWLDirectoriosWindows.cpp
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

#include "DWLDirectoriosWindows.h"
#include "DWLString.h"
#include <shlobj.h>


// Se conserva el soporte a funciones de windows xp y anteriores, pero si el SO es vista o superior se usaran las nuevas funciones SHGetKnownFolderPath
// Para visualC6 y DevC++ solo se soportan las funciones de windows xp y anteriores.


#if DWL_DIRECTORIOSWINDOWS_COMPATIBILIDAD
    // Macro para obtener el directorio ////////////////////////////////////
    #define DWL_OBTENER_DIRECTORIO(CSLID_V5, FOLDERID_V6, DWLSTR)          \
        BOOL Ret = _ObtenerDirectorioV6(FOLDERID_V6, DWLSTR);              \
        if (Ret == FALSE) Ret = _ObtenerDirectorioV5(CSLID_V5, DWLSTR);    \
        return Ret;                                                        \
    ////////////////////////////////////////////////////////////////////////
#else
    // Macro para obtener el directorio ///////////////////////////
    #define DWL_OBTENER_DIRECTORIO(CSLID_V5, FOLDERID_V6, DWLSTR) \
        return _ObtenerDirectorioV5(CSLID_V5, DWLSTR);            \
    ///////////////////////////////////////////////////////////////
#endif


namespace DWL {
    namespace SO {

	    //! Constructor.
	    /*! Constructor.
			    \fn			DWLDirectoriosWindows(void);
			    \return		No devuelve nada.
	    */
    #if DWL_DIRECTORIOSWINDOWS_COMPATIBILIDAD
	    DWLDirectoriosWindows::DWLDirectoriosWindows(void) : _Shell32(NULL), _VersionMayor(0), _SHGetKnownFolderPath(NULL)  {
	#else
	    DWLDirectoriosWindows::DWLDirectoriosWindows(void) : _Shell32(NULL), _VersionMayor(0), _SHGetFolderPath(NULL) {
    #endif
        }

        //! Destructor.
        /*! Destructor.
		        \fn			~DWLDirectoriosWindows(void);
		        \return		No devuelve nada.
        */
	    DWLDirectoriosWindows::~DWLDirectoriosWindows(void) {
		    if (_Shell32 != NULL) FreeLibrary(_Shell32);
	    }

	    //! Función que llamara a SHGetFolderPath si es posible.
	    /*! Esta función llamara a SHGetFolderPath si es posible.
			    \fn			BOOL _ObtenerDirectorioV5(int CSLID, DWL::DWLString &StrOut);
                \param[in]  CSLID  : ID en formato CSLID del directorio a obtener.
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE en caso de exito, FALSE en caso de error.
			    \remarks    Función de uso interno para la DWL.
	    */
	    BOOL DWLDirectoriosWindows::_ObtenerDirectorioV5(int CSLID, DWL::DWLString &StrOut) {
		    TCHAR TmpStr[MAX_PATH] = TEXT("");
		    if (SUCCEEDED(SHGetFolderPath(NULL, CSLID, NULL, 0, TmpStr))) {
			    StrOut = TmpStr;
			    return TRUE;
		    }
		    return FALSE;
	    }

    #if DWL_DIRECTORIOSWINDOWS_COMPATIBILIDAD
	    //! Función que llamara a SHGetKnownFolderPath si es posible.
	    /*! Esta función llamara a SHGetKnownFolderPath si es posible.
			    \fn			BOOL _ObtenerDirectorioV5(int CSLID, DWL::DWLString &StrOut);
                \param[in]  rfid   : ID en formato GUID del directorio a obtener.
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE en caso de exito, FALSE en caso de error.
			    \remarks    Función de uso interno para la DWL.
	    */
	    BOOL DWLDirectoriosWindows::_ObtenerDirectorioV6(const GUID& rfid, DWL::DWLString &StrOut) {
		    if (_VersionMayor > 5 && _SHGetKnownFolderPath != NULL) { // Vista o superior
			    PWSTR Tmp = NULL;
			    if (S_OK == _SHGetKnownFolderPath(rfid, NULL, 0, &Tmp)) {
				    StrOut = Tmp;
				    CoTaskMemFree(Tmp);
				    return TRUE;
			    }
		    }
		    return FALSE;
	    }
    #endif


	    //! Función que inicia esta clase.
	    /*! Esta función inicia la clase de forma que carga la libreria Shell32 y la funcion SHGetKnownFolderPath.
			    \fn			void _Iniciar(void);
			    \return		No devuelve nada.
			    \remarks    Función de uso interno para la DWL.
	    */
	    void DWLDirectoriosWindows::_Iniciar(void) {
            OSVERSIONINFOEX osvi;
		    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
		    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
		    GetVersionEx((OSVERSIONINFO *)&osvi);
			this->_VersionMayor = osvi.dwMajorVersion;
		    _Shell32 = NULL;
		    // Hay que pasar la ruta completa de shell32.dll para evitar la vulnerabilidad de la dll injection
			_Shell32 = LoadLibrary(TEXT("shell32.dll"));
		    #if DWL_DIRECTORIOSWINDOWS_COMPATIBILIDAD
			    _SHGetKnownFolderPath = NULL;
			    #if defined UNICODE // No hay version ansi de SHGetKnownFolderPath xd
				    if (_Shell32 != NULL) _SHGetKnownFolderPath = reinterpret_cast<TpSHGetKnownFolderPath>(GetProcAddress(_Shell32, "SHGetKnownFolderPath"));
			    #endif
		    #else // VC6 - DEVC++
			    _SHGetFolderPath = NULL;
			    #if defined UNICODE
				    if (_Shell32 != NULL)	_SHGetFolderPath = reinterpret_cast<TpSHGetFolderPath>(GetProcAddress(_Shell32, "SHGetFolderPathW"));
			    #else
				    if (_Shell32 != NULL)	_SHGetFolderPath = reinterpret_cast<TpSHGetFolderPath>(GetProcAddress(_Shell32, "SHGetFolderPathA"));
			    #endif
		    #endif
	    }


	    //! Función que retorna el directorio AppData para todos los usuarios del sistema.
	    /*! Esta función devuelve el directorio AppData para todos los usuarios del sistema en la clase DWLString proporcionada.
			    \fn			BOOL AppData(DWL::DWLString &StrOut);
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
			    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\All Users\Application Data",
						    si queremos obtener la ruta para el usuario actual debemos usar la función AppData_UsuarioActual.
	    */
	    BOOL DWLDirectoriosWindows::AppData(DWL::DWLString &StrOut) {
            DWL_OBTENER_DIRECTORIO(CSIDL_COMMON_APPDATA, FOLDERID_ProgramData, StrOut);
	    }

	    //! Función que retorna el directorio AppData del usuario actual.
	    /*! Esta función devuelve el directorio AppData común del usuario actual en la clase DWLString proporcionada.
			    \fn			BOOL AppData_UsuarioActual(DWL::DWLString &StrOut);
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
			    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\USUARIO ACTUAL\Application Data",
						    si queremos obtener la ruta para todos los usuarios debemos usar la función AppData.
	    */
	    BOOL DWLDirectoriosWindows::AppData_UsuarioActual(DWL::DWLString &StrOut) {
            DWL_OBTENER_DIRECTORIO(CSIDL_APPDATA, FOLDERID_RoamingAppData, StrOut);
	    }

	    //! Función que retorna el directorio usado como escritorio común.
	    /*! Esta función devuelve el directorio usado como escritorio común en la clase DWLString proporcionada.
			    \fn			BOOL Escritorio(DWL::DWLString &StrOut);
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
			    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\All Users\Desktop",
						    si queremos obtener la ruta para el usuario actual debemos usar la función Escritorio_UsuarioActual.
	    */
	    BOOL DWLDirectoriosWindows::Escritorio(DWL::DWLString &StrOut) {
            DWL_OBTENER_DIRECTORIO(CSIDL_COMMON_DESKTOPDIRECTORY, FOLDERID_PublicDesktop, StrOut);
	    }

	    //! Función que retorna el directorio usado como escritorio del usuario actual.
	    /*! Esta función devuelve el directorio usado como escritorio del usuario actual en la clase DWLString proporcionada.
			    \fn			BOOL Escritorio_UsuarioActual(DWL::DWLString &StrOut);
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
			    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\USUARIO ACTUAL\Desktop",
						    si queremos obtener la ruta para todos los usuarios debemos usar la función Escritorio.
	    */
        BOOL DWLDirectoriosWindows::Escritorio_UsuarioActual(DWL::DWLString &StrOut) {
            DWL_OBTENER_DIRECTORIO(CSIDL_DESKTOPDIRECTORY, FOLDERID_Desktop, StrOut);
	    }

	    //! Función que retorna el directorio usado como Menú inicio -> Programas.
	    /*! Esta función devuelve el directorio usado como Menú inicio -> Programas en la clase DWLString proporcionada.
			    \fn			BOOL Escritorio_UsuarioActual(DWL::DWLString &StrOut);
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
			    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\All Users\Programs".
	    */
        BOOL DWLDirectoriosWindows::MenuInicio_Programas(DWL::DWLString &StrOut) {
            DWL_OBTENER_DIRECTORIO(CSIDL_COMMON_PROGRAMS, FOLDERID_CommonPrograms, StrOut);
        }

	    //! Función que retorna el directorio usado como Menú inicio -> Programas del usuario actual.
	    /*! Esta función devuelve el directorio usado como Menú inicio -> Programas del usuario actual en la clase DWLString proporcionada.
			    \fn			BOOL MenuInicio_Programas_UsuarioActual(DWL::DWLString &StrOut);
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
			    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\USUARIO ACTUAL\Programs".
	    */
        BOOL DWLDirectoriosWindows::MenuInicio_Programas_UsuarioActual(DWL::DWLString &StrOut) {
            DWL_OBTENER_DIRECTORIO(CSIDL_PROGRAMS , FOLDERID_Programs, StrOut);

		    return _ObtenerDirectorioV5(CSIDL_PROGRAMS, StrOut);
        }

	    //! Función que retorna el directorio usado como Mis Documentos.
	    /*! Esta función devuelve el directorio usado como Mis Documentos en la clase DWLString proporcionada.
			    \fn			BOOL MisDocumentos(DWL::DWLString &StrOut);
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
			    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\All Users\Documentos".
	    */
        BOOL DWLDirectoriosWindows::MisDocumentos(DWL::DWLString &StrOut) {
            DWL_OBTENER_DIRECTORIO(CSIDL_COMMON_DOCUMENTS , FOLDERID_PublicDocuments, StrOut);
        }

	    //! Función que retorna el directorio usado como Mis Documentos para el usuario actual.
	    /*! Esta función devuelve el directorio usado como Mis Documentos para el usuario actual en la clase DWLString proporcionada.
			    \fn			BOOL MisDocumentos_UsuarioActual(DWL::DWLString &StrOut);
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
			    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\USUARIO ACTUAL\Documents".
	    */
        BOOL DWLDirectoriosWindows::MisDocumentos_UsuarioActual(DWL::DWLString &StrOut) {
            DWL_OBTENER_DIRECTORIO(CSIDL_MYDOCUMENTS , FOLDERID_Documents, StrOut);
        }

	    //! Función que retorna el directorio usado como Mis Imagenes.
	    /*! Esta función devuelve el directorio usado como Mis Imagenes en la clase DWLString proporcionada.
			    \fn			BOOL MisImagenes(DWL::DWLString &StrOut);
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
			    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\All Users\Documents\My Pictures".
	    */
        BOOL DWLDirectoriosWindows::MisImagenes(DWL::DWLString &StrOut) {
            DWL_OBTENER_DIRECTORIO(CSIDL_COMMON_PICTURES , FOLDERID_PublicPictures, StrOut);
        }

	    //! Función que retorna el directorio usado como Mis Imagenes para el usuario actual.
	    /*! Esta función devuelve el directorio usado como Mis Imagenes para el usuario actual en la clase DWLString proporcionada.
			    \fn			BOOL MisImagenes_UsuarioActual(DWL::DWLString &StrOut);
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
			    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\USUARIO ACTUAL\Documents\My Pictures".
	    */
        BOOL DWLDirectoriosWindows::MisImagenes_UsuarioActual(DWL::DWLString &StrOut) {
            DWL_OBTENER_DIRECTORIO(CSIDL_MYPICTURES , FOLDERID_Pictures, StrOut);
        }

	    //! Función que retorna el directorio usado como Mi Música.
	    /*! Esta función devuelve el directorio usado como Mi Música en la clase DWLString proporcionada.
			    \fn			BOOL MiMusica(DWL::DWLString &StrOut);
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
			    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\All Users\Documents\My Music".
	    */
        BOOL DWLDirectoriosWindows::MiMusica(DWL::DWLString &StrOut) {
            DWL_OBTENER_DIRECTORIO(CSIDL_COMMON_MUSIC, FOLDERID_PublicMusic, StrOut);
        }

	    //! Función que retorna el directorio usado como Mi Música para el usuario actual.
	    /*! Esta función devuelve el directorio usado como Mi Música para el usuario actual en la clase DWLString proporcionada.
			    \fn			BOOL MiMusica_UsuarioActual(DWL::DWLString &StrOut);
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
			    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\USUARIO ACTUAL\Documents\My Music".
	    */
        BOOL DWLDirectoriosWindows::MiMusica_UsuarioActual(DWL::DWLString &StrOut) {
            DWL_OBTENER_DIRECTORIO(CSIDL_MYMUSIC, FOLDERID_Music, StrOut);
        }

	    //! Función que retorna el directorio usado como Mis Videos.
	    /*! Esta función devuelve el directorio usado como Mis Videos en la clase DWLString proporcionada.
			    \fn			BOOL MisVideos(DWL::DWLString &StrOut);
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
			    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\All Users\Documents\My Videos".
	    */
        BOOL DWLDirectoriosWindows::MisVideos(DWL::DWLString &StrOut) {
            DWL_OBTENER_DIRECTORIO(CSIDL_COMMON_VIDEO, FOLDERID_PublicVideos, StrOut);
        }

	    //! Función que retorna el directorio usado como Mis Videos para el usuario actual.
	    /*! Esta función devuelve el directorio usado como Mi Música para el usuario actual en la clase DWLString proporcionada.
			    \fn			BOOL MisVideos_UsuarioActual(DWL::DWLString &StrOut);
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
			    \remarks    Esta función devuelve una ruta tipo : "C:\Documents and Settings\USUARIO ACTUAL\Documents\My Videos".
	    */
        BOOL DWLDirectoriosWindows::MisVideos_UsuarioActual(DWL::DWLString &StrOut) {
            DWL_OBTENER_DIRECTORIO(CSIDL_MYVIDEO, FOLDERID_Videos, StrOut);
        }

        //! Función que retorna el directorio que contiene Windows.
	    /*! Esta función devuelve el directorio usado directorio  raíz de windows en la clase DWLString proporcionada.
			    \fn			BOOL Windows(DWL::DWLString &StrOut);
			    \param[out] StrOut : Clase DWLString en la que se guardara la ruta del directorio.
			    \return		Devuelve TRUE si la operación se completo con exito, FALSE en caso contrario.
			    \remarks    Esta función devuelve una ruta tipo : "C:\Windows".
	    */
        BOOL DWLDirectoriosWindows::Windows(DWL::DWLString &StrOut) {
            DWL_OBTENER_DIRECTORIO(CSIDL_WINDOWS, FOLDERID_Windows, StrOut);
        }


    };

};
