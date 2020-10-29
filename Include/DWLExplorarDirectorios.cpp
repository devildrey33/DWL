#include "DWLExplorarDirectorios.h"
#include "DWLMouse.h"
#include "DWLListaIconos.h"
#include "DWLDirectoriosWindows.h"
#include <shlobj.h>
#include <dbt.h>		// Device Management Events

#define ID_ESCRITORIO		-1
#define ID_MIPC				-2
#define ID_DISQUETERA		-3
#define ID_DISCODURO		-4
#define ID_DISCODURORED		-5
#define ID_CDROM			-6
#define ID_DISCORAM			-7
#define ID_DIRECTORIO		-8
#define ID_MISDOCUMENTOS	-9
#define ID_MISSITIOSRED		-10
#define ID_REDMICROSOFT		-11
#define ID_GRUPOTRABAJO		-12
#define ID_SERVIDOR			-13
//#define IDI_IMPRESORAS		-14

#define DWL_NOMBRE_CLASE_DWLEXPLORARDIRECTORIOS    TEXT("DWL::ControlesEx::DWLExplorarDirectorios")


namespace DWL {
	namespace ControlesEx {

		//! ID actual
        int DWLExplorarDirectorios::_IDActual = -1;

		//! Constructor.
		/*!	Constructor por defecto.
				\fn		DWLExplorarDirectorios(void);
				\return	No devuelve nada.
		*/
        DWLExplorarDirectorios::DWLExplorarDirectorios(void) : DWLControlEx(), DWLArbolEx_Nucleo() {
			RegistrarClase(DWL_NOMBRE_CLASE_DWLEXPLORARDIRECTORIOS, 0, 0, _GestorMensajes);
		}

		//! Destructor.
		/*!	Destructor.
				\fn		~DWLExplorarDirectorios(void);
				\return	No devuelve nada.
		*/
		DWLExplorarDirectorios::~DWLExplorarDirectorios(void) {
			Destruir();
		}


	    //! Función que crea un objeto DWLExplorarDirectorios.
	    /*!	Esta funcion crea un objeto DWLExplorarDirectorios.
			    \fn			HWND CrearExplorarDirectorios(UINT Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const bool cPintarBorde);
                \param[in]  Estilos      : Estilos para el control.
                \param[in]  hWndParent   : hWnd de la ventana padre.
                \param[in]  cX           : Coordenada X.
                \param[in]  cY           : Coordenada Y.
                \param[in]  cAncho       : Ancho del control.
                \param[in]  cAlto        : Altura del control.
                \param[in]  cID          : ID del control.
                \param[in]  cPintarBorde : Pintar borde redondeado al control
			    \return		Devuelve el HWND del control DWLExplorarDirectorios, o NULL si ha sucedido un error.
	    */
		HWND DWLExplorarDirectorios::CrearExplorarDirectorios(UINT Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const bool cPintarBorde) {
			_ArbolEx_Editando = false;
			int TotalLineas = (static_cast<int>(static_cast<float>(cAlto) / static_cast<float>(_ArbolEx_AltoLinea)));
			CrearControl(hWndParent, TEXT("DWL::ControlesEx::DWLExplorarDirectorios"), Estilos, 0, cX, cY, cAncho, cAlto, cID);
			_BarraScrollEx_PosActualV	= 0;
			ArbolEx_Estilos.PintarBorde	= cPintarBorde;
			ArbolEx_Estilos.SubSeleccion = false;
			_ArbolEx_NodoResaltado		= NULL;
			_ArbolEx_UNodoResaltado		= NULL;

			RECT RC = { 0, 0, cAncho, cAlto };
			if (ArbolEx_Estilos.PintarBorde == true) {
				HRGN Region = CreateRoundRectRgn(0, 0, cAncho + 1, cAlto + 1, 2, 2);
				AsignarRegion(Region, false);
			}

			ArbolEx_Estilos.MultiSeleccion = false;

			BarraScrollEx_CrearV(DWL_BARRASCROLLEX_AUTOMATICO, 0, 0, 0);
			BarraScrollEx_CrearH(DWL_BARRASCROLLEX_AUTOMATICO, 0, 0, 0);
			BarraScrollEx_PosicionarScrolls(_hWnd, &RC, false, ArbolEx_Estilos.PintarBorde);

			HDC hDC		= GetDC(NULL);
			_ArbolEx_Buffer		= CreateCompatibleDC(NULL);
			_ArbolEx_Bmp		= CreateCompatibleBitmap(hDC, cAncho, _ArbolEx_AltoLinea);
			_ArbolEx_Viejo		= static_cast<HBITMAP>(SelectObject(_ArbolEx_Buffer, _ArbolEx_Bmp));
			_ArbolEx_VFuente	= static_cast<HFONT>(SelectObject(_ArbolEx_Buffer, ArbolEx_Estilos.Fuentes.Normal()));
			_ArbolEx_FondoDC    = CreateCompatibleDC(NULL);
			_ArbolEx_BmpFondo   = CreateCompatibleBitmap(hDC, cAncho, cAlto + _ArbolEx_AltoLinea);
			_ArbolEx_ViejoFondo = static_cast<HBITMAP>(SelectObject(_ArbolEx_FondoDC, _ArbolEx_BmpFondo));
			SetBkMode(_ArbolEx_Buffer, TRANSPARENT);
			ReleaseDC(_hWnd, hDC);
			ArbolEx_Evento_Pintar_Fondo(_ArbolEx_FondoDC, &RC);
			ActualizarDirectorios();
			return _hWnd;

		}

	    //! Función que conecta un objeto DWLExplorarDirectorios de un dialogo.
	    /*!	Esta funcion conecta un objeto DWLExplorarDirectorios de un dialogo.
			    \fn			HWND ConectarExplorarDirectorios(HWND hWndParent, const int cID, const bool cPintarBorde);
                \param[in]  hWndParent   : hWnd de la ventana padre.
                \param[in]  cID          : ID del control.
                \param[in]  cPintarBorde : Pintar borde redondeado al control
			    \return		Devuelve el HWND del control DWLExplorarDirectorios, o NULL si ha sucedido un error.
                \remarks    Esta función solo debe usarse con controles que se creen durante la creación del dialogo, si esta clase no pertenece a un dialogo, o se va a crear dinamicamente, no debes usar esta función.
	    */
        HWND DWLExplorarDirectorios::ConectarExplorarDirectorios(HWND hWndParent, const int cID, const bool cPintarBorde) {
//			CrearControl(hWndParent, TEXT("DWL::ControlesEx::DWLExplorarDirectorios"), Estilos, TEXT(""), cX, cY, cAncho, cAlto, cID);
            _ConectarControl(cID, hWndParent);
            RECT RC;
            GetClientRect(_hWnd, &RC);
			_ArbolEx_Editando = false;
            int TotalLineas = (static_cast<int>(static_cast<float>(RC.bottom) / static_cast<float>(_ArbolEx_AltoLinea)));
			_BarraScrollEx_PosActualV	= 0;
			ArbolEx_Estilos.SubSeleccion = false;
			ArbolEx_Estilos.PintarBorde	= cPintarBorde;
			_ArbolEx_NodoResaltado		= NULL;
			_ArbolEx_UNodoResaltado		= NULL;

//			RECT RC = { 0, 0, cAncho, cAlto };
			if (ArbolEx_Estilos.PintarBorde == true) {
                HRGN Region = CreateRoundRectRgn(0, 0, RC.right + 1, RC.bottom + 1, 2, 2);
				AsignarRegion(Region, false);
			}

			ArbolEx_Estilos.MultiSeleccion = false;

			BarraScrollEx_CrearV(DWL_BARRASCROLLEX_AUTOMATICO, 0, 0, 0);
			BarraScrollEx_CrearH(DWL_BARRASCROLLEX_AUTOMATICO, 0, 0, 0);
			BarraScrollEx_PosicionarScrolls(_hWnd, &RC, false, ArbolEx_Estilos.PintarBorde);

			HDC hDC		        = GetDC(NULL);
			_ArbolEx_Buffer		= CreateCompatibleDC(NULL);
            _ArbolEx_Bmp		= CreateCompatibleBitmap(hDC, RC.right, _ArbolEx_AltoLinea);
			_ArbolEx_Viejo		= static_cast<HBITMAP>(SelectObject(_ArbolEx_Buffer, _ArbolEx_Bmp));
			_ArbolEx_VFuente	= static_cast<HFONT>(SelectObject(_ArbolEx_Buffer, ArbolEx_Estilos.Fuentes.Normal()));
			_ArbolEx_FondoDC    = CreateCompatibleDC(NULL);
			_ArbolEx_BmpFondo   = CreateCompatibleBitmap(hDC, RC.right, RC.bottom + _ArbolEx_AltoLinea);
			_ArbolEx_ViejoFondo = static_cast<HBITMAP>(SelectObject(_ArbolEx_FondoDC, _ArbolEx_BmpFondo));
			SetBkMode(_ArbolEx_Buffer, TRANSPARENT);
			ReleaseDC(_hWnd, hDC);
			ArbolEx_Evento_Pintar_Fondo(_ArbolEx_FondoDC, &RC);
			ActualizarDirectorios();
			return _hWnd;

        }



		//! Función que destruye este DWLExplorarDirectorios.
		/*!	Esta funcion destruye el DWLExplorarDirectorios.
				\fn			BOOL Destruir(void);
				\return		Devuelve TRUE si la operacion se completo, FALSE en caso contrario.
		*/
		BOOL DWLExplorarDirectorios::Destruir(void) {
			ArbolEx_BorrarMemoria();
			return DWLControlEx::Destruir();
		}

		//! Función que enumera todos los dispositivos de la red.
		/*! Esta funcion enumera todos los dispositivos de la red.
				\fn			BOOL EnumerarRed(LPNETRESOURCE lpnrLocal, DWLArbolEx_Nodo *nNodo);
				\param[in]	lpnrLocal : Puntero a estructuras enumeradas.
				\param[in]	nNodo     : Nodo en el que se añadiran las enumeraciones.
		        \return		Devuelve TRUE si todo va bioen, FALSE en caso de error.
		*/
		BOOL DWLExplorarDirectorios::EnumerarRed(LPNETRESOURCE lpnr, DWLArbolEx_Nodo *nNodo) {
			DWORD dwResult, dwResultEnum;
			HANDLE hEnum;
			DWORD cbBuffer = 16384;     // 16K is a good size
			DWORD cEntries = -1;        // enumerate all possible entries
			LPNETRESOURCE lpnrLocal;    // pointer to enumerated structures
			DWORD i;
			DWLArbolEx_Nodo *TmpNodo = NULL;
			size_t	Separador = 0;
			size_t	Contador;
			size_t	TamStr;
			int		IconoNodo = 0;
			int		Tipo = 0;
			DWLString NombreStr;

			dwResult = WNetOpenEnum(RESOURCE_GLOBALNET,	RESOURCETYPE_ANY, 0, lpnr, &hEnum);
			if (dwResult != NO_ERROR) {
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("WnetOpenEnum failed with error %d\n"), dwResult));
				return FALSE;
			}

			lpnrLocal = (LPNETRESOURCE) GlobalAlloc(GPTR, cbBuffer + 1);
			if (lpnrLocal == NULL) {
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("WnetOpenEnum failed with error %d\n"), dwResult));
				return FALSE;
			}

			do {
				if (lpnrLocal) ZeroMemory(lpnrLocal, cbBuffer);
				dwResultEnum = WNetEnumResource(hEnum, &cEntries, lpnrLocal, &cbBuffer);

				if (dwResultEnum == NO_ERROR) {
					for (i = 0; i < cEntries; i++) {
						SOLO_DEBUG(DisplayStruct(i, &lpnrLocal[i]));

						TamStr = DWLStrLen(lpnrLocal[i].lpRemoteName);
						Separador = 0;
//						for (Contador = TamStr; Contador < -1; Contador --) {
//							if (lpnrLocal[i].lpRemoteName[Contador] == TEXT('\\')) {
//								Separador = Contador + 1;
						for (Contador = TamStr; Contador > 0; Contador --) {
							if (lpnrLocal[i].lpRemoteName[Contador - 1] == TEXT('\\')) {
								Separador = Contador;
								break;
							}
						}
						bool nActivado = false;
						switch (lpnrLocal[i].dwDisplayType) {
							case RESOURCEDISPLAYTYPE_NETWORK	:
								IconoNodo = CSIDL_CONNECTIONS;
								Tipo = ID_MISSITIOSRED;

								break;
							case RESOURCEDISPLAYTYPE_DOMAIN		:
								IconoNodo = CSIDL_COMPUTERSNEARME;
								Tipo = ID_REDMICROSOFT;
								break;
							case RESOURCEDISPLAYTYPE_SERVER		:
								Tipo = ID_SERVIDOR;
								IconoNodo = CSIDL_DRIVES;
								break;
							case RESOURCEDISPLAYTYPE_SHARE		:
								Tipo = ID_DIRECTORIO;
								IconoNodo = CSIDL_NETHOOD;
								nActivado = true;
								if (lpnrLocal[i].dwType == RESOURCETYPE_PRINT)	IconoNodo = -1;
								break;
							default								: 
								IconoNodo = 0; 
								Tipo = 0;				
								break;
						}
						/*if (lpnrLocal[i].lpComment != NULL) {
							if (lpnrLocal[i].lpComment[0] != 0)	NombreStr.sprintf(TEXT("%s (%s)"), lpnrLocal[i].lpComment, &lpnrLocal[i].lpRemoteName[Separador]);
							else								NombreStr = &lpnrLocal[i].lpRemoteName[Separador];
						}
						else								NombreStr = &lpnrLocal[i].lpRemoteName[Separador];*/
						NombreStr = &lpnrLocal[i].lpRemoteName[Separador];

						if (IconoNodo != -1) {
                            TmpNodo = AgregarNodo(Tipo, nNodo, DWL::SO::DWLListaIconos::CargarIcono(IconoNodo), NombreStr(), -1, nActivado);
							if (IconoNodo == CSIDL_NETHOOD && lpnrLocal[i].dwType == RESOURCETYPE_DISK) {
								AgregarNodo(0, TmpNodo, 0, TEXT("+"));
							}

							if (RESOURCEUSAGE_CONTAINER == (lpnrLocal[i].dwUsage & RESOURCEUSAGE_CONTAINER))
								if (!EnumerarRed(&lpnrLocal[i], TmpNodo))
									SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("EnumerateFunc returned FALSE\n")));
						}
					}
				}
				// Process errors.
				//
				else if (dwResultEnum != ERROR_NO_MORE_ITEMS) {
					SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("WNetEnumResource failed with error %d\n"), dwResultEnum));
					break;
				}
			} while (dwResultEnum != ERROR_NO_MORE_ITEMS);

			GlobalFree((HGLOBAL) lpnrLocal);
			dwResult = WNetCloseEnum(hEnum);

			if (dwResult != NO_ERROR) {
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("WNetCloseEnum failed with error %d\n"), dwResult));
				return FALSE;
			}
			return TRUE;
		}


		//! Función que agrega un nodo al DWLExplorarDirectorios_Nodo.
		/*! Esta función agrega un nodo al DWLExplorarDirectorios_Nodo.
				\fn			DWLExplorarDirectorios_Nodo *AgregarNodo(const int nTipo, DWLArbolEx_Nodo *nPadre, const int nIcono, const TCHAR *nTexto, const int PosicionNodo = -1);
				\param[in]	nTipo			: Tipo de nodo.
				\param[in]	nPadre			: Nodo padre de este nodo. Puede ser NULL.
				\param[in]	nIcono			: ID del icono para este nodo.
				\param[in]	nTexto			: Texto para el nodo.
				\param[in]	nPosicionNodo	: Posicion para el nodo que puede ser DWL_ARBOLEX_PRINCIPIO, DWL_ARBOLEX_ORDENADO, DWL_ARBOLEX_FIN, o un numero valido de posición.
				\param[in]  nActivado       : Para activar / desactivar la selección de este nodo en el EdicionTextoEx
				\return		Devuelve un puntero al DWLExplorarDirectorios_Nodo que se ha creado.
		*/
		DWLExplorarDirectorios_Nodo *DWLExplorarDirectorios::AgregarNodo(const int nTipo, DWLArbolEx_Nodo *nPadre, const int nIcono, const TCHAR *nTexto, const int PosicionNodo, const bool nActivado) {
			DWLExplorarDirectorios_Nodo *nNodo = new DWLExplorarDirectorios_Nodo;
			nNodo->Tipo = nTipo;
			nNodo->Activado = nActivado;
			ArbolEx_AgregarNodo(nNodo, nPadre, nIcono, nTexto, PosicionNodo);
			if (nActivado == false) {
				nNodo->Colores()->TextoNormal = DWL::SO::DWLEstilos::Colores.ContenedorEx_Borde_Normal;
				nNodo->Colores()->TextoResaltado = DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Normal;
				nNodo->Colores()->TextoSeleccionadoResaltado = DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Normal;
				nNodo->Colores()->FondoSeleccionado = DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Normal;
				nNodo->Colores()->TextoSeleccionado = DWL::SO::DWLEstilos::Colores.ContenedorEx_Borde_Normal;
				nNodo->Fuentes()->Normal = DWL::SO::DWLEstilos::Fuentes.Tahoma13_Cursiva;
///				nNodo->Fuentes()->SubRayada = DWL::SO::DWLEstilos::Fuentes.Tahoma13_Cursiva_SubRayada;
				nNodo->Fuentes()->SubRayada = DWL::SO::DWLEstilos::Fuentes.Tahoma13_Cursiva_SubRayada;
			}
//			nNodo->Fuentes()->
			return nNodo;
		}

		//! Función que actualiza la lista de directorios.
		/*!	Esta funcion actualiza la lista de directorios.
				\fn			void ActualizarDirectorios(void);
				\return		No devuelve nada.
		*/
		void DWLExplorarDirectorios::ActualizarDirectorios(void) {
			ArbolEx_EliminarTodosLosNodos();

			TCHAR PathTmp[MAX_PATH + 1] = TEXT("");

			SHGetSpecialFolderPath(NULL, PathTmp, CSIDL_DESKTOPDIRECTORY, 0);
			PathEscritorio = PathTmp;
//			SHGetSpecialFolderPath(NULL, PathTmp, CSIDL_NETHOOD, 0);
//			PathMisSitiosDeRed = PathTmp;
			SHGetSpecialFolderPath(NULL, PathTmp, CSIDL_PERSONAL, 0);
			PathMisDocumentos = PathTmp;



//			HRESULT hr;
//			LPITEMIDLIST pidl = NULL;
//			SHFILEINFOW sfi = {0};

			DWLArbolEx_Nodo *Escritorio		= AgregarNodo(ID_ESCRITORIO, 0, DWL::SO::DWLListaIconos::CargarIcono(CSIDL_DESKTOP), TEXT("Escritorio"));
			if (TieneDirectorios(PathEscritorio()) == true) AgregarNodo(0, Escritorio, 0, TEXT("+"));
			DWLArbolEx_Nodo *MiPC			= AgregarNodo(ID_MIPC, 0, DWL::SO::DWLListaIconos::CargarIcono(CSIDL_DRIVES), TEXT("Mi PC"), -1, false);
			DWLArbolEx_Nodo *MisDocumentos	= AgregarNodo(ID_MISDOCUMENTOS, 0, DWL::SO::DWLListaIconos::CargarIcono(CSIDL_PERSONAL), TEXT("Mis Documentos"));
			if (TieneDirectorios(PathMisDocumentos()) == true) AgregarNodo(0, MisDocumentos, 0, TEXT("+"));
			DWLArbolEx_Nodo *MisSitiosDeRed = AgregarNodo(ID_MISSITIOSRED, 0, DWL::SO::DWLListaIconos::CargarIcono(CSIDL_NETWORK), TEXT("Mis Sitios de Red"), -1, false);
			AgregarNodo(0, MisSitiosDeRed, 0, TEXT("-"));
			//EnumerarRed(NULL, MisSitiosDeRed);


			//if (TieneDirectorios(PathMisSitiosDeRed()) == true) ArbolEx_AgregarNodo(NULL, MisSitiosDeRed, IDI_MISSITIOSRED, TEXT("+"));
			DWLArbolEx_Nodo *TmpNodo = NULL;
			DWLString TextoNodo;
			TCHAR Unidad[5] = TEXT("?:\\");
			TCHAR NombreDisco[256] = TEXT("");
			DWORD Component;
			DWORD Flags;
			TCHAR NombreSistema[128] = TEXT("");
			UINT  TipoUnidad = 0;
			BOOL  Ret = 0;
			int   IDIcono;
			// enumero unidades y cargo los iconos necesarios
			DWORD MascaraBitsUnidades = GetLogicalDrives();
			int Posicion = 0;
			//SetErrorMode(SEM_FAILCRITICALERRORS);
			for (TCHAR i = 0; i < 32; i++) {
				if (MascaraBitsUnidades & (1 << i)) {
					Unidad[0] = i + 'A';
					TipoUnidad = GetDriveType(Unidad);
//					IDIcono = CargarIcono(Unidad);
					switch (TipoUnidad) {
						case DRIVE_REMOVABLE	:
							IDIcono = ID_DISQUETERA;
//							TextoNodo.Parsear(TEXT("Disquetera ("), static_cast<TCHAR>(i + 'A'), TEXT(":)"));
							TextoNodo.sprintf(TEXT("Disquetera (%c:)"), i + 'A');
							break;
						case DRIVE_FIXED		:
							IDIcono = ID_DISCODURO;
//							TextoNodo.Parsear(TEXT("Disco Duro ("), static_cast<TCHAR>(i + 'A'), TEXT(":)"));
							TextoNodo.sprintf(TEXT("Disco Duro (%c:)"), i + 'A');
							break;
						case DRIVE_REMOTE		:
							IDIcono = ID_DISCODURORED;
//							TextoNodo.Parsear(TEXT("Disco de Red ("), static_cast<TCHAR>(i + 'A'), TEXT(":)"));
							TextoNodo.sprintf(TEXT("Disco de Red (%c:)"), i + 'A');
							break;
						case DRIVE_CDROM		:
							IDIcono = ID_CDROM;
//							TextoNodo.Parsear(TEXT("Unidad CD/DVD ("), static_cast<TCHAR>(i + 'A'), TEXT(":)"));
							TextoNodo.sprintf(TEXT("Unidad CD/DVD (%c:)"), i + 'A');
							break;
						case DRIVE_RAMDISK		:
							IDIcono = ID_DISCORAM;
							//TextoNodo.Parsear(TEXT("Unidad RAM ("), static_cast<TCHAR>(i + 'A'), TEXT(":)"));
							TextoNodo.sprintf(TEXT("Unidad RAM (%c:)"), i + 'A');
							break;
						default					:
							IDIcono = 0;
//							TextoNodo.Parsear(TEXT("DESCONOCIDO ("), static_cast<TCHAR>(i + 'A'), TEXT(":)"));
							TextoNodo.sprintf(TEXT("DESCONOCIDO (%c:)"), i + 'A');
							break;
					}

					// Desactivamos la raíz donde se encuentra windows
					bool nActivado = true;
					if (Estilos.DesactivarDirectoriosWindows == true) {
						if (toupper(PathEscritorio[0]) == i + 'A') nActivado = false;
					}

					if (Unidad[0] != TEXT('A') && Unidad[0] != TEXT('B'))	Ret = GetVolumeInformation(Unidad, NombreDisco, 256, NULL, &Component, &Flags, NombreSistema, 128);
					else													Ret = 1;
					if (Ret != 0) {
						if (NombreDisco[0] != 0) TextoNodo.sprintf(TEXT("%s (%c:)"), NombreDisco, i + 'A'); //TextoNodo.Parsear(NombreDisco, TEXT(" ("), static_cast<TCHAR>(i + 'A'), TEXT(":)"));
					}
					TmpNodo = AgregarNodo(IDIcono, MiPC, DWL::SO::DWLListaIconos::CargarIcono(Unidad), TextoNodo(), Posicion, nActivado);
					if (Ret != 0)	AgregarNodo(0, TmpNodo, 0, TEXT("+"));
					Posicion ++;

				}
			}
			SetErrorMode(0);


			DWLExplorarDirectorios_Nodo *PadreSugerencia = NULL; 
			DWLExplorarDirectorios_Nodo *NodoSugerencia = NULL; 
			// Agregamos las sugerencias
			size_t n = 0, z = 0;
			for (n = 0; n < _Sugerencias.size(); n++) {
				// Tiene padre, hay que buscar su nodo (no podemos buscar en NodosLineales porque aun no se ha creado...)
				if (_Sugerencias[n].Padre.Tam() > 0) {
					for (z = 0; z < _ArbolEx_Nodos.size(); z++) {
						if (_Sugerencias[n].Padre == _ArbolEx_Nodos[z]->Texto()) {
							PadreSugerencia = static_cast<DWLExplorarDirectorios_Nodo *>(_ArbolEx_Nodos[z]);
							PadreSugerencia->_Expandido = true;
							break;
						}
					}
					// Tenemos el nodo padre, agregamos el hijo
					NodoSugerencia = AgregarNodo(ID_DIRECTORIO, PadreSugerencia, _Sugerencias[n].Icono, _Sugerencias[n].Nombre(), DWL_ARBOLEX_ORDENADO, true);
				}
				// No tiene padre
				else {
					if (_Sugerencias[n].EsDirectorio == true)	{
						NodoSugerencia = AgregarNodo(ID_DIRECTORIO, NULL, _Sugerencias[n].Icono, _Sugerencias[n].Nombre(), DWL_ARBOLEX_PRINCIPIO, true);
					}
					else {
						NodoSugerencia = AgregarNodo(0, NULL, _Sugerencias[n].Icono, _Sugerencias[n].Nombre(), DWL_ARBOLEX_PRINCIPIO, false);
					}
				}
				if (_Sugerencias[n].Negrita == true) {
					NodoSugerencia->Fuentes()->Normal = DWL::SO::DWLEstilos::Fuentes.Tahoma13_Negrita_Cursiva;
					NodoSugerencia->Fuentes()->SubRayada = DWL::SO::DWLEstilos::Fuentes.Tahoma13_Negrita_Cursiva_SubRayada;
				}
			}

            RECT RC;
            GetClientRect(_hWnd, &RC);
			ArbolEx_ActualizarTodo(_hWnd, &RC);

//			ArbolEx_Expandir(_hWnd, Escritorio, true, false);

			ArbolEx_ActualizarTamTexto();
            ArbolEx_Expandir(_hWnd, MiPC, true, false);
		}



		//! Función que añade una sugerencia al principio.
		/*!	Esta funcion añade una sugerencia al principio.
				\fn			DWLExplorarDirectorios_Nodo *AgregarSugerencia(const TCHAR *Path, const TCHAR *TituloRoot);
				\paran[in]  Path       : Directorio válido
				\param[in]  TituloRoot : Nombre del nodo root de la sugerencia (Si es NULL la sugerencia no tendrá padre)
				\return		Devuelve la clase DWLExplorarDirectorios_Nodo creada.
				\remarks    Necesitaras actualizar el arbol
		*/
		DWLExplorarDirectorios_Nodo *DWLExplorarDirectorios::AgregarSugerencia(const TCHAR *nNombre, const bool EsDirectorio, DWLExplorarDirectorios_Nodo *nPadre, const UINT nIcono, const bool nNegrita) {
			DWLExplorarDirectorios_Nodo *nNodo = NULL; 
			for (size_t i = 0; i < _Sugerencias.size(); i++) {
				// Se ha encontrado la sugerencia, buscamos el nodo
				if (_Sugerencias[i].Nombre == nNombre) {
					for (size_t z = 0; z < _ArbolEx_NodosLineales.size(); z++) {
						if (_Sugerencias[i].Nombre == _ArbolEx_NodosLineales[z]->Texto()) 	return static_cast<DWLExplorarDirectorios_Nodo *>(_ArbolEx_NodosLineales[z]);
					}
					SOLO_DEBUG(_ASSERT(0));
				}
			}
			// Si llegamos aqui es que no se ha encontrado el nodo, lo agregamos
//			DWL::DWLString Nombre = nNombre;
			DWLExplorarDirectorios_Sugerencia Sugerencia;
			Sugerencia.Nombre = nNombre;
			Sugerencia.EsDirectorio = EsDirectorio;
			if (nPadre != NULL) Sugerencia.Padre = nPadre->Texto();
			nNodo = new DWLExplorarDirectorios_Nodo;
			if (EsDirectorio == true) {
				Sugerencia.Icono = DWL::SO::DWLListaIconos::CargarIcono(nNombre);
				nNodo = AgregarNodo(ID_DIRECTORIO, nPadre, Sugerencia.Icono, nNombre, DWL_ARBOLEX_ORDENADO, true);
			}
			else {
				Sugerencia.Icono = nIcono;
				nNodo = AgregarNodo(0, nPadre, nIcono, nNombre, DWL_ARBOLEX_PRINCIPIO, false);
			}
			Sugerencia.Negrita = nNegrita;
			_Sugerencias.push_back(Sugerencia);

			if (nNegrita == true) {
				nNodo->Fuentes()->Normal = DWL::SO::DWLEstilos::Fuentes.Tahoma13_Negrita;
				nNodo->Fuentes()->SubRayada = DWL::SO::DWLEstilos::Fuentes.Tahoma13_Negrita_SubRayada;
			}
			return nNodo;
		}

		void DWLExplorarDirectorios::EliminarSugerencias(void) {
			_Sugerencias.resize(0);
		}

		
		//! Función que agrega un directorio al arbol.
		/*! Esta funcion agrega un directorio al arbol.
				\fn			void AgregarDirectorio(DWLExplorarDirectorios_Nodo *nNodoExpandido, const TCHAR *PathBusqueda);
				\param[in]	nNodoExpandido : Nodo en el que se añadiran las nuevas entradas.
				\param[in]	PathBusqueda   : Path final de la ruta a explorar.
		        \return		No devuelve nada.
		*/
		void DWLExplorarDirectorios::ArbolEx_Evento_Expandir(DWLArbolEx_Nodo *nNodoExpandido) {
			const TCHAR *TmpTxt;
			DWLString PathBusqueda;
			if (nNodoExpandido->TotalHijos() == 1) {
				TmpTxt = nNodoExpandido->Hijo(0)->Texto();
				if (TmpTxt[0] == TEXT('+')) {
					ObtenerPath(static_cast<DWLExplorarDirectorios_Nodo *>(nNodoExpandido), PathBusqueda);
					ArbolEx_EliminarNodo(_hWnd, nNodoExpandido->Hijo(0), false);
					SO::DWLMouse::CambiarCursorEstandard(DWL_Enum_Mouse_Cursor_Procesando);
					AgregarDirectorio(static_cast<DWLExplorarDirectorios_Nodo *>(nNodoExpandido), PathBusqueda());
					SO::DWLMouse::CambiarCursorEstandard();
                    ArbolEx_ActualizarVectorLineal(_hWnd, false);
					ArbolEx_ActualizarTamTexto();
//					ArbolEx_FinAgregarNodos(_hWnd);
				}

				if (TmpTxt[0] == TEXT('-')) {
					SO::DWLMouse::CambiarCursorEstandard(DWL_Enum_Mouse_Cursor_Procesando);
					EnumerarRed(NULL, static_cast<DWLExplorarDirectorios_Nodo *>(nNodoExpandido));
					SO::DWLMouse::CambiarCursorEstandard();
					// Elimino nodos que no contengan mas hijos en la raiz de la red (que son el terminalserver, etc..)
					for (size_t z = nNodoExpandido->TotalHijos(); z > 0; z--) {
						if (nNodoExpandido->Hijo(z - 1)->TotalHijos() == 0) ArbolEx_EliminarNodo(_hWnd, nNodoExpandido->Hijo(z - 1), false);
					}
				}
			}
			SetErrorMode(0);
		}

		//! Función que agrega un directorio al arbol.
		/*! Esta funcion agrega un directorio al arbol.
				\fn			void AgregarDirectorio(DWLExplorarDirectorios_Nodo *nNodoExpandido, const TCHAR *PathBusqueda);
				\param[in]	nNodoExpandido : Nodo en el que se añadiran las nuevas entradas.
				\param[in]	PathBusqueda   : Path final de la ruta a explorar.
		        \return		No devuelve nada.
		*/
		void DWLExplorarDirectorios::AgregarDirectorio(DWLExplorarDirectorios_Nodo *nNodoExpandido, const TCHAR *PathBusqueda) {
			WIN32_FIND_DATA		FindInfoPoint;
			HANDLE				hFind = NULL;
			DWLArbolEx_Nodo    *TmpNodo = NULL;
			DWLString Path;
			Path = PathBusqueda; Path += TEXT("*.*");
			DWLString PathBusqueda2;
			PathBusqueda2 = PathBusqueda;
			//PathBusqueda += TEXT("*.*");
			SetErrorMode(SEM_FAILCRITICALERRORS);
			hFind = FindFirstFile(Path(), &FindInfoPoint);
			if (hFind == INVALID_HANDLE_VALUE) {
				return;
			}
			TCHAR DirWindows[MAX_PATH];
			GetWindowsDirectory(DirWindows, MAX_PATH);
			size_t TamWP = DWLStrLen(DirWindows);
			if (DirWindows[TamWP] != TEXT('\\')) {
				DirWindows[TamWP] = TEXT('\\');
				DirWindows[TamWP + 1] = TEXT('\0');
			}
			bool NodoActivado = true;;

			while (FindNextFile(hFind, &FindInfoPoint) != 0) {
				NodoActivado = true;
				if (FindInfoPoint.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && FindInfoPoint.cFileName[0] != TEXT('.')) {
					if (FindInfoPoint.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) { // oculto
						if (Estilos.MostrarDirectoriosOcultos == true) {
							PathBusqueda2.sprintf(TEXT("%s%s\\"), PathBusqueda, FindInfoPoint.cFileName);
							TmpNodo = AgregarNodo(ID_DIRECTORIO, nNodoExpandido, DWL::SO::DWLListaIconos::CargarIcono(PathBusqueda2()), FindInfoPoint.cFileName, -1, !Estilos.DesactivarDirectoriosWindows);
							if (TieneDirectorios(PathBusqueda2())) AgregarNodo(0, TmpNodo, 0, TEXT("+"));
						}
					}
					else { // normal
						PathBusqueda2.sprintf(TEXT("%s%s\\"), PathBusqueda, FindInfoPoint.cFileName);
						if (Estilos.DesactivarDirectoriosWindows == true) {
							if (PathBusqueda2 == DirWindows) NodoActivado = false;
						}
						TmpNodo = AgregarNodo(ID_DIRECTORIO, nNodoExpandido, DWL::SO::DWLListaIconos::CargarIcono(PathBusqueda2()), FindInfoPoint.cFileName, -1, NodoActivado);
						if (NodoActivado) if (TieneDirectorios(PathBusqueda2())) AgregarNodo(0, TmpNodo, 0, TEXT("+"));
					}
				}
			}
			FindClose(hFind);
		}


		//! Función que hace una pre-exploracion para determinar si el directorio tiene mas directorios dentro.
		/*! Esta funcion hace una pre-exploracion para determinar si el directorio tiene mas directorios dentro.
				\fn			bool TieneDirectorios(const TCHAR *Path);
				\param[in]	Path : Path a explorar.
		        \return		Devuelve true si hay directorios dentro, false en caso contrario.
		*/
		bool DWLExplorarDirectorios::TieneDirectorios(const TCHAR *Path) {
			WIN32_FIND_DATA		FindInfoPoint;
			HANDLE				hFind = NULL;
			DWLString PathBusqueda;
			PathBusqueda = Path;
			if (PathBusqueda[PathBusqueda.Tam()] != '\\')	PathBusqueda += TEXT("\\*.*");
			else											PathBusqueda += TEXT("*.*");
			SetErrorMode(SEM_FAILCRITICALERRORS);
			hFind = FindFirstFile(PathBusqueda(), &FindInfoPoint);
			if (hFind == INVALID_HANDLE_VALUE) return false;
			while (FindNextFile(hFind, &FindInfoPoint) != 0) {
				if (FindInfoPoint.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && FindInfoPoint.cFileName[0] != TEXT('.')) {
					FindClose(hFind);
					return true;
				}
			}
			FindClose(hFind);
			return false;
		}


		//! Función que explora un directorio.
		/*! Esta funcion explora un directorio.
				\fn			void ObtenerPath(DWLExplorarDirectorios_Nodo *NodoPath, DWLString &PathFinal);
				\param[in]	NodoPath  : Nodo en el que se añadiran las nuevas entradas.
				\param[in]	PathFinal : Path final de la ruta a explorar.
		        \return		No devuelve nada.
		*/
		void DWLExplorarDirectorios::ObtenerPath(DWLExplorarDirectorios_Nodo *NodoPath, DWLString &PathFinal) {
			DWLExplorarDirectorios_Nodo *TmpNodo = NodoPath;
			DWLString		 TmpStr;
			const TCHAR *TmpTexto = NodoPath->Texto();

			TmpNodo = NodoPath;
			if (TmpNodo->Tipo == ID_DIRECTORIO) {
				PathFinal.sprintf(TEXT("%s\\"), TmpNodo->Texto());
				if (TmpNodo->Padre() != NULL) TmpNodo = static_cast<DWLExplorarDirectorios_Nodo *>(TmpNodo->Padre());
			}

			while (TmpNodo->Tipo == ID_DIRECTORIO) { // Mientras el icono sea de un directorio, no estaremos en la raiz
				TmpStr = PathFinal;
				PathFinal.sprintf(TEXT("%s\\%s"), TmpNodo->Texto(), TmpStr());
				TmpNodo = static_cast<DWLExplorarDirectorios_Nodo *>(TmpNodo->Padre());
			}

			switch (TmpNodo->Tipo) {
				case ID_ESCRITORIO :
					TmpStr = PathFinal;
					if (TmpStr.Tam() > 0)	PathFinal.sprintf(TEXT("%s\\%s"), PathEscritorio(), TmpStr());
					else					PathFinal.sprintf(TEXT("%s\\"), PathEscritorio());
//					TmpNodo = TmpNodo->Padre();
					break;
				case ID_MISDOCUMENTOS :
					TmpStr = PathFinal;
					if (TmpStr.Tam() > 0)	PathFinal.sprintf(TEXT("%s\\%s"), PathMisDocumentos(), TmpStr());
					else					PathFinal.sprintf(TEXT("%s\\"), PathMisDocumentos());
					break;
				case ID_SERVIDOR :
					if (PathFinal.Tam() > 0) {
						TmpStr = PathFinal;
						PathFinal.sprintf(TEXT("\\\\%s\\%s"), TmpNodo->Texto(), TmpStr());
					}
					break;
				case ID_DISCODURO :
				case ID_CDROM :
				case ID_DISQUETERA :
				case ID_DISCORAM :
				case ID_DISCODURORED :
					TmpTexto = TmpNodo->Texto();
					TmpStr = PathFinal;
					if (TmpStr.Tam() > 0)	PathFinal.sprintf(TEXT("%c:\\%s"), TmpTexto[DWLStrLen(TmpTexto) - 3], TmpStr());
					else					PathFinal.sprintf(TEXT("%c:\\"), TmpTexto[DWLStrLen(TmpTexto) - 3]);
					break;


				case ID_DIRECTORIO :
					TmpNodo = NodoPath;
					PathFinal.sprintf(TEXT("%s\\"), TmpNodo->Texto());
					TmpNodo = static_cast<DWLExplorarDirectorios_Nodo *>(TmpNodo->Padre());
					while (TmpNodo->Tipo == ID_DIRECTORIO) {
						TmpStr = PathFinal;
						PathFinal.sprintf(TEXT("%s\\%s"), TmpNodo->Texto(), TmpStr());
						TmpNodo = static_cast<DWLExplorarDirectorios_Nodo *>(TmpNodo->Padre());
					}
					TmpTexto = TmpNodo->Texto();
					TmpStr = PathFinal;
					PathFinal.sprintf(TEXT("%c:\\%s"), TmpTexto[DWLStrLen(TmpTexto) - 3], TmpStr());
					break;
				default :
					break;
			}
		}




		/*void DWLExplorarDirectorios::ObtenerPath(DWLArbolEx_Nodo *NodoPath, DWLString &PathFinal) {
			DWLArbolEx_Nodo *TmpNodo = NULL;
			DWLString		 TmpStr;
			const TCHAR *TmpTexto = NodoPath->Texto();
			switch (NodoPath->Icono()) {
				case IDI_ESCRITORIO :
					break;
				case IDI_MISDOCUMENTOS :
					break;
				case IDI_MISSITIOSRED :
					break;


				case IDI_DISCODURO :
				case IDI_CDROM :
				case IDI_DISQUETERA :
				case IDI_DISCORAM :
				case IDI_DISCODURORED :
					PathFinal = TmpTexto[DWLStrLen(TmpTexto) - 3];
					PathFinal += TEXT(":\\");
					break;
				case IDI_DIRECTORIO :
					TmpNodo = NodoPath;
					PathFinal.sprintf(TEXT("%s\\"), TmpNodo->Texto());
					TmpNodo = TmpNodo->Padre();
					while (TmpNodo->Icono() == IDI_DIRECTORIO) {
						TmpStr = PathFinal;
						PathFinal.sprintf(TEXT("%s\\%s"), TmpNodo->Texto(), TmpStr());
						TmpNodo = TmpNodo->Padre();
					}
					TmpTexto = TmpNodo->Texto();
					TmpStr = PathFinal;
					PathFinal.sprintf(TEXT("%c:\\%s"), TmpTexto[DWLStrLen(TmpTexto) - 3], TmpStr);
					break;
				default :
					break;
			}
		}*/


		//! Función predefinida del mensaje WM_*BUTTONDOWN (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONDOWN.
				\fn			virtual LRESULT Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param)
				\param[in]	Boton	: Boton presionado.
				\param[in]	cX		: Coordenada X del mouse.
				\param[in]	cY		: Coordenada Y del mouse.
				\param[in]	wParam	: Teclas extendidas presionadas.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLExplorarDirectorios::Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			ArbolEx_Mouse_BotonPresionado(_hWnd, &RC, Boton, cX, cY, Param);
			Repintar();
            return 0;
		}


		//! Función predefinida del mensaje WM_*BUTTONUP (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONUP.
				\fn			virtual LRESULT Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	Boton	: Boton presionado.
				\param[in]	cX		: Coordenada X del mouse.
				\param[in]	cY		: Coordenada Y del mouse.
				\param[in]	Param	: Teclas extendidas presionadas.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLExplorarDirectorios::Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			ArbolEx_Mouse_BotonSoltado(_hWnd, &RC, Boton, cX, cY, Param);
			Repintar();
            return 0;
		}


		//! Función predefinida del mensaje WM_MOUSEMOVE.
		/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEMOVE.
				\fn			virtual LRESULT Evento_Mouse_Movimiento(const int cX, const int cY, const UINT wParam);
				\param[in]	cX		: Coordenada X del mouse.
				\param[in]	cY		: Coordenada Y del mouse.
				\param[in]	Param	: Teclas extendidas presionadas.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLExplorarDirectorios::Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			ArbolEx_Mouse_Movimiento(_hWnd, &RC, cX, cY, Param);
			Repintar();
            return 0;
		}

		//! Función que recibe cuando el mouse se va del control
		/*!	Esta función es la encargada de procesar los mensajes WN_MOUSELEAVE.
				\fn			virtual LRESULT Evento_Mouse_Saliendo(void);
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
    	LRESULT DWLExplorarDirectorios::Evento_Mouse_Saliendo(void) {
			#if defined DWL_ARBOLEX_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLArbolEx::Evento_Mouse_Saliendo\n"));
			#endif
			_ArbolEx_NodoResaltado = NULL;
			_ArbolEx_ExpansorResaltado = NULL;
			BarraScrollEx_Mouse_Saliendo(_hWnd);
			Repintar(true);
            return 0;
		}

		//! Función que enlaza el mensaje WM_TIMER con el control.
	    /*! Esta función enlaza el mensaje WM_TIMER con el control.
			    \fn			void Evento_Temporizador(const int cID);
			    \param[in]	cID : ID del temporizador.
			    \return		No devuelve nada.
			    \remarks	Si re-emplazas esta funcion debes retornar 0.
	    */
		LRESULT DWLExplorarDirectorios::Evento_Temporizador(const UINT cID) {
			DWLBarraScrollEx_Nucleo::BarraScrollEx_Evento_Temporizador(_hWnd, cID, true);
/*			if (cID == DWL_TIMER_TOOLTIP) {
				if (Visible() == FALSE) return 0;
				if (_ArbolEx_TT_UltimoNodo == _ArbolEx_NodoResaltado) {
					if (GetTickCount() - _ArbolEx_TT_TiempoMS > DWL_TIEMPO_TOOLTIP && _ArbolEx_TT_UltimoNodo != NULL) {
						if (ArbolEx_ToolTip.hWnd() == NULL) ArbolEx_Evento_MostrarToolTip(_ArbolEx_TT_UltimoNodo);
					}
				}
				else {
					ArbolEx_ToolTip.Destruir();
					_ArbolEx_TT_UltimoNodo = _ArbolEx_NodoResaltado;
					_ArbolEx_TT_TiempoMS = GetTickCount();
				}
			}*/
            return 0;
		}


		//! Función que pinta todo el control cuado se recibe un mensaje WM_PAINT.
		/*!	Esta función pinta el control cuando se recibe un mensaje WM_PAINT.
				\fn			LRESULT Evento_Pintar(HDC hDC);
				\param[in]	hDC	: hDC donde se pintara todo el control.
                \param[in]  PS  : Estructura que contiene los datos del pintado.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLExplorarDirectorios::Evento_Pintar(HDC hDC, PAINTSTRUCT &PS) {
			if (_hWnd == NULL) return 0;
			RECT R;
			GetClientRect(_hWnd, &R);
			ArbolEx_Pintar(hDC, &R, Foco());
            return 0;
		}

		//! Función predefinida del mensaje WM_KEYDOWN (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WM_KEYDOWN.
				\fn			virtual LRESULT Evento_Teclado_TeclaPresionada(const UINT Tecla, const UINT Repeticion, const UINT Param);
				\param[in]	Caracter   : Tecla virtual soltada.
				\param[in]	Repeticion : Repeticiones de la tecla
				\param[in]	Param	   : Teclas extendidas soltadas.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLExplorarDirectorios::Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Param) {
			ArbolEx_Teclado_TeclaPresionada(_hWnd, Caracter, Repeticion, Param);
			Repintar(true);
            return 0;
		}


		//! Función predefinida del mensaje WM_KEYUP (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WM_KEYUP.
				\fn			virtual LRESULT Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Param);
				\param[in]	Caracter   : Tecla virtual soltada.
				\param[in]	Repeticion : Repeticiones de la tecla
				\param[in]	Param	   : Teclas extendidas soltadas.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLExplorarDirectorios::Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Param) {
			ArbolEx_Teclado_TeclaSoltada(_hWnd, Caracter, Repeticion, Param);
            return 0;
		}

		//! Función para mover el control a la posicion y el tamaño especificados.
		/*!	Esta función mueve el control a la posicion y tamaño especificados.
				\fn			void Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = true);
				\param[in]	cX			: Nueva posicion X para el control.
				\param[in]	cY			: Nueva posicion Y para el control.
				\param[in]	cAncho		: Nuevo ancho para el control.
				\param[in]	cAlto		: Nueva altura para el control.
				\param[in]	cRepintar	: True para repintar el control, false para dejarlo sin repintar.
				\return		No devuelve nada.
		*/
		void DWLExplorarDirectorios::Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar) {
			RECT RectaFondo = { 0, 0, cAncho, cAlto };
			MoveWindow(_hWnd, cX, cY, cAncho, cAlto, false);
			long UPaginaV = _BarraScrollEx_PaginaV;
			long UPaginaH = _BarraScrollEx_PaginaH;
			_BarraScrollEx_PaginaV = (static_cast<int>(static_cast<float>(cAlto) / static_cast<float>(_ArbolEx_AltoLinea)));
			_BarraScrollEx_PaginaH = cAncho;

			if (BarraScrollEx_VisibleH() == TRUE) _BarraScrollEx_PaginaV -= 1;
			if (BarraScrollEx_VisibleV() == TRUE) _BarraScrollEx_PaginaH -= 17;
			if (UPaginaV < _BarraScrollEx_PaginaV && _BarraScrollEx_ValorV > _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) BarraScrollEx_ValorV( _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
			if (UPaginaH < _BarraScrollEx_PaginaH && _BarraScrollEx_ValorH > _BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH) BarraScrollEx_ValorH(_BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH);

			BarraScrollEx_PosicionarScrolls(_hWnd, &RectaFondo, true, ArbolEx_Estilos.PintarBorde);

			if (_ArbolEx_FondoDC != NULL) {
				SelectObject(_ArbolEx_FondoDC, _ArbolEx_VFuente);
				SelectObject(_ArbolEx_FondoDC, _ArbolEx_Viejo);
				DeleteObject(_ArbolEx_Bmp);
				DeleteDC(_ArbolEx_FondoDC);
				_ArbolEx_FondoDC = NULL;
				SelectObject(_ArbolEx_Buffer, _ArbolEx_VFuente);
				SelectObject(_ArbolEx_Buffer, _ArbolEx_ViejoFondo);
				DeleteObject(_ArbolEx_BmpFondo);
				DeleteDC(_ArbolEx_Buffer);
			}

			HDC	hDC		= GetDC(NULL);
			_ArbolEx_FondoDC    = CreateCompatibleDC(hDC);
			_ArbolEx_Bmp        = CreateCompatibleBitmap(hDC, cAncho, cAlto + _ArbolEx_AltoLinea);
			_ArbolEx_Viejo      = static_cast<HBITMAP>(SelectObject(_ArbolEx_FondoDC, _ArbolEx_Bmp));
			_ArbolEx_VFuente    = static_cast<HFONT>(SelectObject(_ArbolEx_FondoDC, ArbolEx_Estilos.Fuentes.Normal()));
			int AnchoBuffer = _BarraScrollEx_MaximoH;
			if (AnchoBuffer < cAncho) AnchoBuffer = cAncho;
			_ArbolEx_Buffer		= CreateCompatibleDC(hDC);
			_ArbolEx_BmpFondo	= CreateCompatibleBitmap(hDC, AnchoBuffer, _ArbolEx_AltoLinea);
			_ArbolEx_ViejoFondo = static_cast<HBITMAP>(SelectObject(_ArbolEx_Buffer, _ArbolEx_BmpFondo));
			_ArbolEx_VFuente    = static_cast<HFONT>(SelectObject(_ArbolEx_Buffer, ArbolEx_Estilos.Fuentes.Normal()));
			ReleaseDC(NULL, hDC);
			SetBkMode(_ArbolEx_FondoDC, TRANSPARENT);
			SetBkMode(_ArbolEx_Buffer, TRANSPARENT);
			ArbolEx_Evento_Pintar_Fondo(_ArbolEx_FondoDC, &RectaFondo);
			if (cRepintar == true) Repintar(true);
		}


		//! Función predefinida del mensaje WM_MOUSEWHEEL.
		/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEWHEEL.
				\fn			virtual LRESULT Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey);
				\param[in]	Delta	: Valor de desplazamiento del mouse.
				\param[in]	cX		: Coordenada X.
				\param[in]	cY		: Coordenada Y.
				\param[in]	VirtKey	: Tecla virtual presionada.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLExplorarDirectorios::Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey) {
			if ((_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) > 0 && _BarraScrollEx_ValorV < (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) +1) {
				if (Delta > 0) { // Hacia arriba
					_BarraScrollEx_ValorV -= 3;
					if (_BarraScrollEx_ValorV < 0) BarraScrollEx_ValorV(0);

				}
				else { // Hacia abajo
					_BarraScrollEx_ValorV += 3;
					if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) BarraScrollEx_ValorV(_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);
				}
				_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;
				_ArbolEx_NodoResaltado = NULL;
				_ArbolEx_ExpansorResaltado = NULL;
				BarraScrollEx_CalcularScrollV();
				BarraScrollEx_CalcularScrollH();
				BarraScrollEx_Repintar(_hWnd, true);
				Repintar(true);
			}
            RECT RC;
            GetClientRect(_hWnd, &RC);
            _ArbolEx_UYMouse = RC.bottom + _ArbolEx_AltoLinea;
            return 0;
		}


		//! Función que repinta todo el control DWLExplorarDirectorios.
		/*!	Esta función repinta todo el control incluyendo barras de scroll y botones extra.
				\fn			void Repintar(const bool Forzar = false);
				\param[in]	Forzar : True para forzar el repintado, false para que la funcion decida si repintar.
				\return		No devuelve nada.
				\remarks	Cuando Forzar es false, esta función mira si ha cambiado algun estado interno,
							y de ser asi repinta el control, en caso contrario no hace nada.
		*/
		void DWLExplorarDirectorios::Repintar(const bool Forzar) {
			if (_ArbolEx_Editando == true) return;
			bool P = Forzar;
			if (P == false) {
				if (_BarraScrollEx_UValorV != _BarraScrollEx_ValorV)	P = true;
				if (_ArbolEx_UNodoResaltado != _ArbolEx_NodoResaltado)	P = true;
				bool FocoActual = Foco();
				if (_ArbolEx_FocoRaton != FocoActual) {
					_ArbolEx_FocoRaton = FocoActual;
					P = true;
				}
			}
			_BarraScrollEx_UValorV = _BarraScrollEx_ValorV;
			_ArbolEx_UNodoResaltado = _ArbolEx_NodoResaltado;
			if (P == true) {
				RECT RC;
                GetClientRect(_hWnd, &RC);
				ArbolEx_Evento_Pintar_Fondo(_ArbolEx_FondoDC, &RC);

				HDC hDC = GetDC(_hWnd);
		//		_ScrollV->ReAjustarMedidas();
		//		_ScrollV->Repintar(true);
                PAINTSTRUCT PS;
				Evento_Pintar(hDC, PS);
				ReleaseDC(_hWnd, hDC);
			}
		}


		//! Esqueleto para los mensajes del control.
		/*! Esta función es el esqueleto para los mensajes del control.
				\fn			LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
				\param[in]	uMsg	: Mensaje.
				\param[in]	wParam	: Parametro1.
				\param[in]	lParam	: Parametro2.
				\return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
				\remarks	Esta función es el esqueleto del control por donde pasaran todos sus mensajes.
		*/
		LRESULT CALLBACK DWLExplorarDirectorios::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
			switch (uMsg) {
				case DWL_ARBOLEX_TECLADO_INTRO :
					ArbolEx_TerminarLabelEdit(_hWnd);
					break;
				case DWL_ARBOLEX_TECLADO_SOLTADO :
					if (wParam == VK_ESCAPE) ArbolEx_CancelarLabelEdit(_hWnd);
					break;

				case WM_NOTIFY			: // LabelEdit
					switch (((LPNMHDR)lParam)->code) {
						case NM_KILLFOCUS :
							ArbolEx_CancelarLabelEdit(_hWnd);
							break;
					}
					break;
				case WM_CTLCOLOREDIT :
				case WM_CTLCOLORSTATIC :
					DWLArbolEx_ColoresNodo *Col;
					if (_ArbolEx_eNodo->Colores() != NULL)   Col = _ArbolEx_eNodo->Colores();
					else									 Col = &ArbolEx_Estilos.Colores.ColoresNodo;
					SetTextColor((HDC)wParam, Col->TextoNormal());
					SetBkColor((HDC)wParam, Col->FondoNormal());
					return (LRESULT)_ArbolEx_BrochaFondoEdit;
				case WM_DEVICECHANGE :
					PDEV_BROADCAST_HDR *lpdb;
					lpdb = (PDEV_BROADCAST_HDR *)lParam;
					if (wParam == DBT_DEVICEARRIVAL || wParam == DBT_DEVICEREMOVECOMPLETE) {
						ActualizarDirectorios();
					}
					break;

			}
			return DWLControlEx::GestorMensajes(uMsg, wParam, lParam);
		}

		//! Función que procesa el mensaje WM_KILLFOCUS
		/*! Esta funcion es la encargada de procesar el mensaje WM_KILLFOCUS
				\fn			virtual LRESULT Evento_Foco_Perdido(HWND NuevoFoco);
				\param[in]	NuevoFoco	: HWND de la ventana que recibira el foco despues de esta.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/ 
		LRESULT DWLExplorarDirectorios::Evento_Foco_Perdido(HWND NuevoFoco) {
			int i;
			for (i = 0; i < 256; i++) _ArbolEx_Teclado[i] = false;
			_ArbolEx_NodoPresionado = NULL;
			PostMessage(GetParent(_hWnd), DWL_ARBOLEX_FOCO_PERDIDO, ID(), 0);
            return 0;
		}

		//! Función que procesa el mensaje WM_SETFOCUS
		/*! Esta funcion es la encargada de procesar el mensaje WM_SETFOCUS
				\fn			virtual LRESULT Evento_Foco_Obtenido(HWND FocoAnterior);
				\param[in]	FocoAnterior	: HWND de la ventana que tenia el foco antes que esta.
		        \return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLExplorarDirectorios::Evento_Foco_Obtenido(HWND FocoAnterior) {
			ArbolEx_CancelarLabelEdit(_hWnd);
			PostMessage(GetParent(_hWnd), DWL_ARBOLEX_FOCO_OBTENIDO, ID(), 0);
            return 0;
		}


		//! Función para la depuración en la obtención de directorios.
		/*! Esta funcion es para la depuración en la obtención de directorios.
				\fn			void DisplayStruct(int i, LPNETRESOURCE lpnrLocal);
				\param[in]	i         : Numero de entrada.
				\param[in]	lpnrLocal : Puntero a estructuras enumeradas.
		        \return		No devuelve nada.
		*/
		void DWLExplorarDirectorios::DisplayStruct(int i, LPNETRESOURCE lpnrLocal)	{
			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("NETRESOURCE[%d] Scope: "), i));
			switch (lpnrLocal->dwScope) {
			case (RESOURCE_CONNECTED):
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("connected\n")));
				break;
			case (RESOURCE_GLOBALNET):
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("all resources\n")));
				break;
			case (RESOURCE_REMEMBERED):
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("remembered\n")));
				break;
			default:
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("unknown scope %d\n"), lpnrLocal->dwScope));
				break;
			}

			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("NETRESOURCE[%d] Type: "), i));
			switch (lpnrLocal->dwType) {
			case (RESOURCETYPE_ANY):
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("any\n")));
				break;
			case (RESOURCETYPE_DISK):
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("disk\n")));
				break;
			case (RESOURCETYPE_PRINT):
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("print\n")));
				break;
			default:
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("unknown type %d\n"), lpnrLocal->dwType));
				break;
			}

			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("NETRESOURCE[%d] DisplayType: "), i));
			switch (lpnrLocal->dwDisplayType) {
			case (RESOURCEDISPLAYTYPE_GENERIC):
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("generic\n")));
				break;
			case (RESOURCEDISPLAYTYPE_DOMAIN):
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("domain\n")));
				break;
			case (RESOURCEDISPLAYTYPE_SERVER):
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("server\n")));
				break;
			case (RESOURCEDISPLAYTYPE_SHARE):
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("share\n")));
				break;
			case (RESOURCEDISPLAYTYPE_FILE):
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("file\n")));
				break;
			case (RESOURCEDISPLAYTYPE_GROUP):
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("group\n")));
				break;
			case (RESOURCEDISPLAYTYPE_NETWORK):
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("network\n")));
				break;
			default:
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("unknown display type %d\n"), lpnrLocal->dwDisplayType));
				break;
			}

			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("NETRESOURCE[%d] Usage: 0x%x = "), i, lpnrLocal->dwUsage));
			if (lpnrLocal->dwUsage & RESOURCEUSAGE_CONNECTABLE)
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("connectable ")));
			if (lpnrLocal->dwUsage & RESOURCEUSAGE_CONTAINER)
				SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("container ")));
			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("\n")));

			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("NETRESOURCE[%d] Localname: %s\n"), i, lpnrLocal->lpLocalName));
			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("NETRESOURCE[%d] Remotename: %s\n"), i, lpnrLocal->lpRemoteName));
			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("NETRESOURCE[%d] Comment: %s\n"), i, lpnrLocal->lpComment));
			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("NETRESOURCE[%d] Provider: %s\n"), i, lpnrLocal->lpProvider));
			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("\n")));
		}
	};
};
