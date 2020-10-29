/////////////////////////////////////////////////////////////////////////////////////////////////
// Esta clase han sido creada por [\DReY\] el dia 08/04/2006 y es uno de los ejemplos de       //
// http://www.webpersonal.net/devildrey33 (DReY Visual C++ page)                               //
// Puedes modificar esta clase a tu gusto. Si realizas alguna modificacion que creas que es    //
// mejor para esta clase porfavor mandamela por e-mail para que pueda verla :)                 // 
// E-Mail & MSN Messenger : devildrey33@hotmail.com                                            //
//                                                                                             //
// Version 0.3                                                                                 //
// Ultima modificación : 18/04/2006                                                            //
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "DWLEdicionDesplegableEx.h"
#include "DWLGraficos.h"
#include "DWLListaIconos.h"

#define DWL_NOMBRE_CLASE_DWLEDICIONDESPLEGABLEEX    TEXT("DWL::ControlesEx::DWLEdicionDesplegableEx")

namespace DWL {
	namespace ControlesEx {



        DWLEdicionDesplegableEx::DWLEdicionDesplegableEx(void) : DWLControlEx(), DWLEdicionDesplegableEx_Nucleo() {
            RegistrarClase(DWL_NOMBRE_CLASE_DWLEDICIONDESPLEGABLEEX, 0, 0, _GestorMensajes);
        }

        DWLEdicionDesplegableEx::~DWLEdicionDesplegableEx(void) {
            Destruir();
        }

		void DWLEdicionDesplegableEx::Activado(const bool nActivar) {
			_EdicionEx_Activado = nActivar;
			Repintar();
		}

		LRESULT CALLBACK DWLEdicionDesplegableEx::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
			switch (uMsg) {
				case DWL_EDICIONDESPLEGABLEEX_LISTA_OCULTADA :
					_EdicionDesplegableEx_EstadoBotonEx = 0;
					ReleaseCapture();
					Repintar();
					break;
				case DWL_EDICIONDESPLEGABLEEX_CAMBIO_SELECCION_LISTA : {
					DWL::ControlesEx::DWLListaEx_Item *nItem = reinterpret_cast<DWL::ControlesEx::DWLListaEx_Item *>(LongToPtr(wParam));
					if (nItem != NULL) Texto(nItem->Texto(0), nItem->Icono());
					_EdicionDesplegableEx_EstadoBotonEx = 0;
					Repintar();
					PostMessage(GetParent(_hWnd), DWL_EDICIONDESPLEGABLEEX_CAMBIO_SELECCION, PtrToLong(EdicionEx_ObtenerTexto()), ID());
					SetFocus(_hWnd);
					break;
				}
				case DWL_EDICIONDESPLEGABLEEX_CAMBIO_SELECCION_ARBOL : {
					DWL::ControlesEx::DWLArbolEx_Nodo *nNodo = reinterpret_cast<DWL::ControlesEx::DWLArbolEx_Nodo *>(LongToPtr(wParam));
					DWLString Str;
					_EdicionDesplegableEx_ContenedorExplorarDirectorios.ObtenerPath(static_cast<DWLExplorarDirectorios_Nodo *>(nNodo), Str);
					if (nNodo != NULL) Texto(Str(), nNodo->Icono());
					_EdicionDesplegableEx_EstadoBotonEx = 0;
					Repintar();
					PostMessage(GetParent(_hWnd), DWL_EDICIONDESPLEGABLEEX_CAMBIO_SELECCION, PtrToLong(EdicionEx_ObtenerTexto()), ID());
					SetFocus(_hWnd);
					break;
				}
				/*case WM_LBUTTONDOWN :																				
					this->Evento_Mouse_BotonPresionado(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);	
					return 0;																						
				case WM_RBUTTONDOWN :																				
					this->Evento_Mouse_BotonPresionado(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);	
					return 0;																						
				case WM_MBUTTONDOWN :																				
					this->Evento_Mouse_BotonPresionado(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);	
					return 0;

				case WM_LBUTTONUP :																				
					this->Evento_Mouse_BotonSoltado(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);	
					return 0;																					
				case WM_RBUTTONUP :																				
					this->Evento_Mouse_BotonSoltado(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);	
					return 0;																					
				case WM_MBUTTONUP :																				
					this->Evento_Mouse_BotonSoltado(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);	
					return 0;

				case WM_MOUSEMOVE :		
					this->Evento_Mouse_Movimiento(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);	
					return 0;

				case WM_KEYDOWN :		
					this->Evento_Teclado_TeclaPresionada(static_cast<int>(wParam), lParam);
					return 0;
				case WM_KEYUP :			
					this->Evento_Teclado_TeclaSoltada(static_cast<int>(wParam), lParam);
					return 0;
				case WM_CHAR :	
					this->Evento_Teclado_Caracter(static_cast<int>(wParam), lParam);
					return 0;

				case WM_SETFOCUS :
					this->Evento_Foco_Obtenido(reinterpret_cast<HWND>(wParam));	
					return 0;
				case WM_KILLFOCUS :
					this->Evento_Foco_Perdido(reinterpret_cast<HWND>(wParam));
					return 0;
				
				case WM_TIMER :			
					this->Evento_Temporizador(static_cast<int>(wParam));	
					return 0;

				case WM_PAINT :			
					HDC DC;	
					PAINTSTRUCT ps;	
					DC = BeginPaint(_hWnd, &ps);	
					this->Evento_Pintar(DC);	
					EndPaint(_hWnd, &ps);	
					return 0;*/
			}

			#if _MSC_VER > 1200
                return DWL::ControlesEx::Base::DWLControlEx::GestorMensajes(uMsg, wParam, lParam);
			#else
				return DWLControlEx::GestorMensajes(uMsg, wParam, lParam);
			#endif
		};


		LRESULT DWLEdicionDesplegableEx::Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			if (_EdicionEx_Activado == true) {
				RECT RC;
				GetClientRect(_hWnd, &RC);
				if (cX < (RC.right - RC.bottom) && EdicionEx_Estilos.TextoModificable == true) { // parte del edit
					RC.right -= RC.bottom;
					if (_EdicionDesplegableEx_IconoEdicionTexto != 0) RC.left += 16;
					EdicionEx_Mouse_BotonPresionado(_hWnd, &RC, Boton, cX - 20, cY, Param);
				}
			}
            return 0;
		}


		LRESULT DWLEdicionDesplegableEx::Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			if (_EdicionEx_Activado == true) {
				RECT RC;
				GetClientRect(_hWnd, &RC);
				bool ParteBoton = false;
				if (cX < (RC.right - RC.bottom)) { // parte del edit
					if (EdicionEx_Estilos.TextoModificable == false) {
						ParteBoton = true;
					}
					else { 
						RC.right -= RC.bottom;
						if (_EdicionDesplegableEx_IconoEdicionTexto != 0) RC.left += 16;
						EdicionEx_Mouse_BotonSoltado(_hWnd, &RC, Boton, cX - 20, cY, Param);

						if (_EdicionDesplegableEx_EstadoBotonEx != 2) 
							_EdicionDesplegableEx_EstadoBotonEx = 0;
						Repintar();
					}
				}
				else {
					ParteBoton = true;
				}
				if (ParteBoton == true) {
					if (_EdicionDesplegableEx_EstadoBotonEx == 2) {
						if (_EdicionDesplegableEx_TipoEdicion == DWL_Enum_EdicionDesplegableEx_Tipo_ListaDesplegable)	_EdicionDesplegableEx_ContenedorLista.Visible(false);
						else																							_EdicionDesplegableEx_ContenedorExplorarDirectorios.Visible(false);
						_EdicionDesplegableEx_EstadoBotonEx = 1;
					}
					else {
						if (_EdicionDesplegableEx_TipoEdicion == DWL_Enum_EdicionDesplegableEx_Tipo_ListaDesplegable)	_EdicionDesplegableEx_ContenedorLista.Mostrar(_hWnd, _EdicionDesplegableEx_AltoLista);
						else																							_EdicionDesplegableEx_ContenedorExplorarDirectorios.Mostrar(_hWnd, _EdicionDesplegableEx_AltoLista);
						_EdicionDesplegableEx_EstadoBotonEx = 2;
					}
					Repintar();
				}
			}
            return 0;
		}


		LRESULT DWLEdicionDesplegableEx::Evento_Mouse_Saliendo(void) {
			if (_EdicionDesplegableEx_EstadoBotonEx != 2) 
				_EdicionDesplegableEx_EstadoBotonEx = 0;
			Repintar();
            return 0;
		}


		LRESULT DWLEdicionDesplegableEx::Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			if (cX > (RC.right - RC.bottom)) {
				if (_EdicionEx_Activado == true && _EdicionDesplegableEx_EstadoBotonEx != 2) {
					_EdicionDesplegableEx_EstadoBotonEx = 1;
				}
			}
			else {
				if (_EdicionDesplegableEx_EstadoBotonEx != 2) 
					_EdicionDesplegableEx_EstadoBotonEx = 0;
				RC.right -= RC.bottom;
				if (_EdicionDesplegableEx_IconoEdicionTexto != 0) RC.left += 16;
				EdicionEx_Mouse_Movimiento(_hWnd, &RC, cX - 20, cY, Param);
			}
			Repintar();
            return 0;
		}


		void DWLEdicionDesplegableEx::AgregarItem(const TCHAR *nTxt, const int nIcono) {
			_EdicionDesplegableEx_ContenedorLista.AgregarItem(NULL, nIcono, DWL_LISTAEX_FIN, nTxt);
		}


		void DWLEdicionDesplegableEx::FinAgregarItems(void) {
			_EdicionDesplegableEx_ContenedorLista.ActualizarTodo();
		}


		LRESULT DWLEdicionDesplegableEx::Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Param) {
			EdicionEx_Teclado_TeclaSoltada(_hWnd, Caracter, Repeticion, Param);
			Repintar();
            return 0;
		}


		LRESULT DWLEdicionDesplegableEx::Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Param) {
			EdicionEx_Teclado_TeclaPresionada(_hWnd, Caracter, Repeticion, Param);
			Repintar();
            return 0;
		}


		LRESULT DWLEdicionDesplegableEx::Evento_Teclado_Caracter(const UINT Caracter, const UINT Repeticion, const UINT Param) {
			EdicionEx_Teclado_Caracter(_hWnd, Caracter, Repeticion, Param);
			Repintar();
            return 0;
		}

		LRESULT DWLEdicionDesplegableEx::Evento_Temporizador(const UINT tID) {
			if (tID == DWL_EDICIONEX_TEMPORIZADOR_CURSOR) {
				_EdicionEx_CursorVisible = !_EdicionEx_CursorVisible;
				Repintar();
			}
            return 0;
		}

		LRESULT DWLEdicionDesplegableEx::Evento_Foco_Obtenido(HWND FocoAnterior) {
			CrearTemporizador(DWL_EDICIONEX_TEMPORIZADOR_CURSOR, 500);
			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("DWLEdicionEx::Evento_Foco_Obtenido\n")));
            return 0;
		}


		LRESULT DWLEdicionDesplegableEx::Evento_Foco_Perdido(HWND NuevoFoco) {
			EliminarTemporizador(DWL_EDICIONEX_TEMPORIZADOR_CURSOR);
			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("DWLEdicionEx::Evento_Foco_Perdido\n")));
			_EdicionEx_CursorVisible = false;
			_EdicionEx_TeclaControlPresionada = false;
			_EdicionEx_TeclaShiftPresionada = false;
			Repintar();
            return 0;
		}


		void DWLEdicionDesplegableEx::Repintar(void) {
			HDC hDC = GetDC(_hWnd);
            PAINTSTRUCT PS;
			Evento_Pintar(hDC, PS);
			ReleaseDC(_hWnd, hDC);
		}




 

		HWND DWLEdicionDesplegableEx::CrearEdicionDesplegableEx(const long Estilos, HWND hWndParent, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, const int nAltoLista, const int cID, const bool nTextoModificable, const int nIcono, const DWL_Enum_EdicionDesplegableEx_Tipo TipoEdicion) {
			EdicionEx_Estilos.TextoModificable = nTextoModificable;
			_EdicionDesplegableEx_TipoEdicion = TipoEdicion;
			_EdicionDesplegableEx_AltoLista = nAltoLista;
			if (_EdicionDesplegableEx_TipoEdicion == DWL_Enum_EdicionDesplegableEx_Tipo_BuscarDirectorio) {
                _EdicionDesplegableEx_IconoEdicionTexto = DWL::SO::DWLListaIconos::CargarIcono(nTexto);
			}
			else {
				_EdicionDesplegableEx_IconoEdicionTexto = nIcono;
			}
			
//			_EdicionEx_CursorX = 0; // Al primer caracter
//			_EdicionEx_CursorX = _EdicionEx_Texto.Tam();
			CrearControl(hWndParent, DWL_NOMBRE_CLASE_DWLEDICIONDESPLEGABLEEX, Estilos, 0, cX, cY, cAncho, cAlto, cID);
			HRGN Rgn = CreateRoundRectRgn(0, 0, cAncho + 1, cAlto + 1, 2, 2);
			SetWindowRgn(_hWnd, Rgn, false);
			EdicionEx_Estilos.MultiLinea = false;
			EdicionEx_Estilos.PintarBorde = false;
			_EdicionEx_Activado = true;
			EdicionEx_AgregarTexto(_hWnd, nTexto);
			RECT RC = { 0, 0, cAncho, cAlto };
			SetFocus(_hWnd);

			if (_EdicionDesplegableEx_ContenedorLista.TotalColumnas() == 0)	_EdicionDesplegableEx_ContenedorLista.AgregarColumna(cAncho - 18);
			return _hWnd;
		};

        //! Función que conecta el EdicionDesplegableEx de un dialogo.
        /*!	Esta función conecta la EdicionDesplegableEx de un dialogo.
                \fn			HWND ConectarEdicionDesplegableEx(HWND hWndParent, const TCHAR *nTexto, const int nAltoLista, const int cID, const bool nTextoModificable, const int nIcono, const DWL_Enum_EdicionDesplegableEx_Tipo TipoEdicion);
                \param[in]	hWndParent	      : HWND del control que sera el padre de la MarcaEx.
                \param[in]  nTexto            : Texto para el control
                \param[in]	nAltoLista	      : Altura de la lista desplegable.
                \param[in]	cID			      : ID de la MarcaEx.
                \param[in]  nTextoModificable : El texto sera modificable true/false.
                \param[in]	nIcono            : Icono para mostrar, 0 para no mostrar ninguno.
                \param[in]  TipoEdicion       : Tipo_ListaDesplegable o Tipo_BuscarDirectorio.
                \return		Devuelve el HWND de la EdicionDesplegableEx. En caso de error devolvera NULL.
                \remarks    Esta función solo debe usarse con controles que se creen durante la creación del dialogo, si esta clase no pertenece a un dialogo, o se va a crear dinamicamente, no debes usar esta función.
        */
        HWND DWLEdicionDesplegableEx::ConectarEdicionDesplegableEx(HWND hWndParent, const TCHAR *nTexto, const int nAltoLista, const int cID, const bool nTextoModificable, const int nIcono, const DWL_Enum_EdicionDesplegableEx_Tipo TipoEdicion) {
			EdicionEx_Estilos.TextoModificable = nTextoModificable;
			_EdicionDesplegableEx_TipoEdicion = TipoEdicion;
			_EdicionDesplegableEx_AltoLista = nAltoLista;
			if (_EdicionDesplegableEx_TipoEdicion == DWL_Enum_EdicionDesplegableEx_Tipo_BuscarDirectorio) {
				_EdicionDesplegableEx_IconoEdicionTexto = DWL::SO::DWLListaIconos::CargarIcono(nTexto);
			}
			else {
				_EdicionDesplegableEx_IconoEdicionTexto = nIcono;
			}
			
//			_EdicionEx_CursorX = 0; // Al primer caracter
//			_EdicionEx_CursorX = _EdicionEx_Texto.Tam();
//			CrearControl(hWndParent, DWL_NOMBRE_CLASE_DWLEDICIONDESPLEGABLEEX, Estilos, 0, cX, cY, cAncho, cAlto, cID);
            _ConectarControl(cID, hWndParent);
            RECT RC;
            GetClientRect(_hWnd, &RC);
            HRGN Rgn = CreateRoundRectRgn(0, 0, RC.right + 1, RC.bottom + 1, 2, 2);
			SetWindowRgn(_hWnd, Rgn, false);
			EdicionEx_AgregarTexto(_hWnd, nTexto);
			EdicionEx_Estilos.MultiLinea = false;
			EdicionEx_Estilos.PintarBorde = false;
//			RECT RC = { 0, 0, cAncho, cAlto };
			SetFocus(_hWnd);

            if (_EdicionDesplegableEx_ContenedorLista.TotalColumnas() == 0)	_EdicionDesplegableEx_ContenedorLista.AgregarColumna(RC.right -20);
			return _hWnd;
        }


		LRESULT DWLEdicionDesplegableEx::Evento_Pintar(HDC hDC, PAINTSTRUCT &PS) {
			RECT Espacio;
			GetClientRect(_hWnd, &Espacio);
			EdicionDesplegableEx_Pintar(hDC, &Espacio, Foco(), false);
            return 0;
		}


		void DWLEdicionDesplegableEx::SeleccionarItem(const UINT Pos) {
			if (_EdicionDesplegableEx_TipoEdicion != DWL_Enum_EdicionDesplegableEx_Tipo_BuscarDirectorio) {
				if (_EdicionDesplegableEx_ContenedorLista.TotalItems() > Pos) Texto(_EdicionDesplegableEx_ContenedorLista.Item(Pos)->Texto(), _EdicionDesplegableEx_ContenedorLista.Item(Pos)->Icono());
			}
		}

		const int DWLEdicionDesplegableEx::ItemSeleccionado(void) {
			int Ret = -1;
			if (_EdicionDesplegableEx_TipoEdicion != DWL_Enum_EdicionDesplegableEx_Tipo_BuscarDirectorio) {
				for (size_t i = 0; i < _EdicionDesplegableEx_ContenedorLista.TotalItems(); i++) {
					if (DWLStrCmpi(EdicionEx_ObtenerTexto() ,_EdicionDesplegableEx_ContenedorLista.Item(i)->Texto()) == 0) {
						Ret = i;
						break;
					}
				}
			}
			else {
			}
			return Ret;
		}

















		DWLEdicionDesplegableEx_Nucleo::DWLEdicionDesplegableEx_Nucleo(void) {
			_EdicionDesplegableEx_EstadoBotonEx	= 0;
//			_EdicionDesplegableEx_Activado = true;
		}
		
		void DWLEdicionDesplegableEx_Nucleo::EdicionDesplegableEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco) { 
			HBRUSH Brocha;
			if (TieneFoco == true)	Brocha = CreateSolidBrush(EdicionDesplegableEx_ColoresBoton.BordeSeleccionado());
			else					Brocha = CreateSolidBrush(EdicionDesplegableEx_ColoresBoton.Borde());
			FrameRgn(hDC, Region, Brocha, 1, 1);
			DeleteObject(Brocha);
		};

		void DWLEdicionDesplegableEx_Nucleo::EdicionDesplegableEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco, const bool PintarConMascara) {
			RECT	RC				= { 0, 0, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top };
			HDC		hDCCompatible	= CreateCompatibleDC(hDC);
			HBITMAP BMPCompatible	= CreateCompatibleBitmap(hDC, RC.right, RC.bottom);
			HBITMAP BMPViejo		= static_cast<HBITMAP>(SelectObject(hDCCompatible, BMPCompatible));
			HRGN	Region			= CreateRoundRectRgn(0, 0, RC.right + 1, RC.bottom + 1, 2, 2);

			// Pinto la mascara del control si se requiere
			if (PintarConMascara == true) {
				FillRect(hDCCompatible, &RC, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));
				FillRgn(hDCCompatible, Region, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
				BitBlt(hDC, Espacio->left, Espacio->top, RC.right, RC.bottom, hDCCompatible, 0, 0, SRCAND);
			}

			RECT EspacioEdicion = { 2, 2, RC.right - (RC.bottom + 1), RC.bottom };

			HBRUSH Brocha = CreateSolidBrush(EdicionEx_Estilos.Colores.Fondo());
			FillRect(hDCCompatible, &RC, Brocha);
			DeleteObject(Brocha);

			//			EspacioEdicion.right -= (Espacio->bottom + 1); // resto el tamaño del boton
			// Pinto el icono si hay alguno asignado
			if (_EdicionDesplegableEx_IconoEdicionTexto != 0) {
				RECT EspacioIcono = { 0, 0, 18, RC.bottom };
				EspacioEdicion.left += 18;
				SO::DWLListaIconos::PintarIcono(hDCCompatible, 3, 1, 16, 16, _EdicionDesplegableEx_IconoEdicionTexto);
			}
		
			EdicionEx_Pintar(hDCCompatible, &EspacioEdicion, TieneFoco, false);

			RECT EspacioBoton = { RC.right - RC.bottom, 0, RC.right, RC.bottom };

//			RECT EspacioBoton = { Espacio->left, Espacio->top, RC.right, Espacio->bottom };
//			EspacioBoton.left = (EspacioBoton.right - EspacioBoton.left) - EspacioBoton.bottom;
			//EspacioBoton.right += (EspacioBoton.bottom);
			// Pinto el boton y la flecha
			bool TF = TieneFoco;
			if (_EdicionEx_Activado == false) TF = false;
			EdicionDesplegableEx_PintarBotonEx(hDCCompatible, &EspacioBoton, TF);

			EspacioBoton.left ++; EspacioBoton.right ++; EspacioBoton.top ++; EspacioBoton.bottom ++;
			switch (_EdicionDesplegableEx_EstadoBotonEx) {
				case 0 : 
					if (_EdicionEx_Activado == true) DWL::GDI::PintarFlecha(hDCCompatible, EspacioBoton.left -1, EspacioBoton.top, EdicionDesplegableEx_ColoresBoton.TextoNormal(), DWL_DIRECCION_FLECHA_ABAJO);
					else						     DWL::GDI::PintarFlecha(hDCCompatible, EspacioBoton.left -1, EspacioBoton.top, EdicionDesplegableEx_ColoresBoton.TextoDesactivado(), DWL_DIRECCION_FLECHA_ABAJO);
					break;
				case 1 : 
					DWL::GDI::PintarFlecha(hDCCompatible, EspacioBoton.left -1, EspacioBoton.top, EdicionDesplegableEx_ColoresBoton.TextoResaltado(), DWL_DIRECCION_FLECHA_ABAJO);
					break;
				case 2 : 
					EspacioBoton.left ++; EspacioBoton.right ++; EspacioBoton.top ++; EspacioBoton.bottom ++;
					DWL::GDI::PintarFlecha(hDCCompatible, EspacioBoton.left -1, EspacioBoton.top, EdicionDesplegableEx_ColoresBoton.TextoDesactivado(), DWL_DIRECCION_FLECHA_ABAJO);
					break;
			}
			EdicionDesplegableEx_Evento_Pintar_Borde(hDCCompatible, Region, TF);
			DeleteObject(Region);

			// Pinto el control en el hDC especificado
			if (PintarConMascara == false)	BitBlt(hDC, Espacio->left, Espacio->top, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top, hDCCompatible, 0, 0, SRCCOPY);
			else							BitBlt(hDC, Espacio->left, Espacio->top, Espacio->right - Espacio->left, Espacio->bottom - Espacio->top, hDCCompatible, 0, 0, SRCPAINT);

			SelectObject(hDCCompatible, BMPViejo);
			DeleteObject(BMPCompatible);
			DeleteDC(hDCCompatible);
		}


		void DWLEdicionDesplegableEx_Nucleo::EdicionDesplegableEx_PintarBotonEx(HDC hDC, RECT *Espacio, const bool TieneFoco) {
			switch (_EdicionDesplegableEx_EstadoBotonEx) {
				case 0 : // normal
					DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom - Espacio->top, EdicionDesplegableEx_ColoresBoton.DegradadoSuperior(), EdicionDesplegableEx_ColoresBoton.DegradadoInferior(), true);
					break;
				case 1 : // resaltado
					DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom - Espacio->top, EdicionDesplegableEx_ColoresBoton.DegradadoResaltado(), EdicionDesplegableEx_ColoresBoton.DegradadoInferior(), true);
					break;
				case 2 : // presionado
					DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom - Espacio->top, EdicionDesplegableEx_ColoresBoton.DegradadoInferior(), EdicionDesplegableEx_ColoresBoton.DegradadoSuperior(), true);
					break;
			}
			HPEN Borde;
			if (TieneFoco == false) Borde = CreatePen(PS_SOLID, 1, EdicionDesplegableEx_ColoresBoton.Borde());
			else					Borde = CreatePen(PS_SOLID, 1, EdicionDesplegableEx_ColoresBoton.BordeSeleccionado());
			HPEN Viejo = static_cast<HPEN>(SelectObject(hDC, Borde));
			MoveToEx(hDC, Espacio->left - 1, 1, NULL);
			LineTo(hDC, Espacio->left -1, Espacio->bottom -1);
			SelectObject(hDC, Viejo);
			DeleteObject(Borde);
		}

	}
}

