// Control que tiene como base un EdicionTexto, y un boton a la derecha.
// Este control puede actuar como una lista desplegable / combobox, o puede ser un control para buscar directorios.
#ifndef DWL_DWLEdicionDesplegableEx_H
#define DWL_DWLEdicionDesplegableEx_H

#include "DWLEdicionEx.h"
#include "DWLListaEx.h"
#include "DWLBotonEx.h"
#include "DWLExplorarDirectorios.h"

#define DWL_EDICIONDESPLEGABLEEX_TIMER_FOCO		1432

#define DWL_EDICIONDESPLEGABLEEX_OPACIDAD_LISTA 230

enum DWL_Enum_EdicionDesplegableEx_Tipo {
	DWL_Enum_EdicionDesplegableEx_Tipo_ListaDesplegable	= 0,
	DWL_Enum_EdicionDesplegableEx_Tipo_BuscarDirectorio	= 1
};
 
namespace DWL {

	namespace ControlesEx {

		class DWLEdicionDesplegableEx_ContenedorExplorarDirectorios : public DWL::ControlesEx::DWLExplorarDirectorios {
		 public :
											DWLEdicionDesplegableEx_ContenedorExplorarDirectorios(void) {
//												_SeleccionFinal = NULL;
											};

										   ~DWLEdicionDesplegableEx_ContenedorExplorarDirectorios(void) {
//												Destruir();
											};


		 void								Mostrar(HWND hWndParent, const int Altura) {
												RECT Recta;
												GetWindowRect(hWndParent, &Recta);
												ArbolEx_DesSeleccionarTodo(false);
												if (_hWnd != NULL) {
													SetFocus(_hWnd);
													SetWindowPos(_hWnd, HWND_TOPMOST, Recta.left - 2, Recta.bottom + 1, (Recta.right - Recta.left) + 4, Altura, SWP_NOACTIVATE | SWP_SHOWWINDOW);
                                                    ArbolEx_ActualizarVectorLineal(_hWnd, false);
													Visible(true);
													SetCapture(_hWnd);
													return;
												}


												ArbolEx_Estilos.Colores.ColoresNodo.TextoResaltado.Enlazar(&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_SeleccionadoResaltado);
												ArbolEx_Estilos.Colores.ColoresNodo.FondoResaltado.Enlazar(&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_SeleccionadoResaltado);
												ArbolEx_Estilos.Colores.ColoresNodo.FondoNormal.Enlazar(&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Claro);
												ArbolEx_Estilos.Colores.Fondo.Enlazar(&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Claro);

												CrearExplorarDirectorios(WS_POPUP, 0, Recta.left - 2, Recta.bottom + 1, (Recta.right - Recta.left) + 4, Altura, 0, true);

//												SetWindowLongPtr(_hWnd, GWL_EXSTYLE, 0x00080000 | WS_EX_TOPMOST | WS_EX_TOOLWINDOW);
//												Opacidad(DWL_EDICIONDESPLEGABLEEX_OPACIDAD_LISTA);
//												SetFocus(_hWnd);
//												FinAgregarItems();
												Visible(true);
												_hWndParent = hWndParent;
												SetCapture(_hWnd);
												SetTimer(_hWnd, DWL_EDICIONDESPLEGABLEEX_TIMER_FOCO, 500, NULL);
											};

		 LRESULT                            Evento_Temporizador(const UINT cID) {
												if (cID == DWL_EDICIONDESPLEGABLEEX_TIMER_FOCO) {
													if (GetFocus() != _hWnd) {
														Visible(false);
														SendMessage(_hWndParent, DWL_EDICIONDESPLEGABLEEX_LISTA_OCULTADA, 0, 0);
														KillTimer(_hWnd, DWL_EDICIONDESPLEGABLEEX_TIMER_FOCO);
													}
												}
												return DWLExplorarDirectorios::Evento_Temporizador(cID);
											};

		 LRESULT							Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param) {
												RECT RC;
												GetClientRect(_hWnd, &RC);
												POINT Pt = { cX, cY };

												if (PtInRect(&RC, Pt) == FALSE) {
													ReleaseCapture();
													Visible(false);
													SendMessage(_hWndParent, DWL_EDICIONDESPLEGABLEEX_LISTA_OCULTADA, 0, 0);
													KillTimer(_hWnd, DWL_EDICIONDESPLEGABLEEX_TIMER_FOCO);
													return 0;
												}
												LRESULT Ret = ArbolEx_Mouse_BotonSoltado(_hWnd, &RC, Boton, cX, cY, Param);
												if (_ArbolEx_NodoMarcado != NULL) {
													if (static_cast<DWLExplorarDirectorios_Nodo *>(_ArbolEx_NodoMarcado)->Activado == true) {
														_SeleccionFinal = _ArbolEx_NodoMarcado;
														SendMessage(_hWndParent, DWL_EDICIONDESPLEGABLEEX_CAMBIO_SELECCION_ARBOL, PtrToLong(_SeleccionFinal), 0);
														DWLString Str;
														ReleaseCapture();
														ObtenerPath(static_cast<DWLExplorarDirectorios_Nodo *>(_ArbolEx_NodoMarcado), Str);
														if (Str.Tam() > 0) { // Si el path de la seleccion final es valido
															SendMessage(_hWndParent, DWL_EDICIONDESPLEGABLEEX_CAMBIO_SELECCION_ARBOL, PtrToLong(_ArbolEx_NodoMarcado), 0);
															Visible(false);
														}
													}
												}
												Repintar();
												return Ret;
											};


		 LRESULT							Evento_Foco_Perdido(HWND NuevoFoco) {
												#if _MSC_VER > 1200
													DWL::ControlesEx::DWLExplorarDirectorios::Evento_Foco_Perdido(NuevoFoco);
												#else
													DWLExplorarDirectorios::Evento_Foco_Perdido(NuevoFoco);
												#endif
//												Visible(false);
//												SendMessage(_hWndParent, DWL_EDICIONDESPLEGABLEEX_LISTA_OCULTADA, 0, 0);
                                                return 0;
											};

 		 LRESULT                            Evento_Mouse_Entrando(const int cX, const int cY, const UINT Param) {
//												Opacidad(255);
												return 0;
											};

		 LRESULT                            Evento_Mouse_Saliendo(void) {
//												Opacidad(DWL_EDICIONDESPLEGABLEEX_OPACIDAD_LISTA);
												return DWLExplorarDirectorios::Evento_Mouse_Saliendo();
											};

		protected : //////////////////////////

		 HWND				                _hWndParent;
		 DWL::ControlesEx::DWLArbolEx_Nodo *_SeleccionFinal;
		};




		class DWLEdicionDesplegableEx_ContenedorListaEx : public DWL::ControlesEx::DWLListaEx {
		 public :
											DWLEdicionDesplegableEx_ContenedorListaEx(void) : DWL::ControlesEx::DWLListaEx() {
												_SeleccionFinal = NULL;
											};

										   ~DWLEdicionDesplegableEx_ContenedorListaEx(void) {
//												Destruir();
											};


		 void								Mostrar(HWND hWndParent, const int Altura) {
												RECT Recta;
												GetWindowRect(hWndParent, &Recta);
												DesSeleccionarTodo(false);
												_SeleccionFinal = NULL;
												if (_hWnd != NULL) {
												//	MirarScrollVisible();
													SetFocus(_hWnd);
													SetWindowPos(_hWnd, HWND_TOPMOST, Recta.left - 2, Recta.bottom + 1, (Recta.right - Recta.left) + 4, Altura, SWP_NOACTIVATE | SWP_SHOWWINDOW);
													ActualizarTodo();
													Visible(true);
													SetCapture(_hWnd);
													return;
												}
												else {
													Visible(true);
												}
												bool BIconos = false;
												for (size_t i = 0; i < _ListaEx_Items.size(); i++) {
													if (_ListaEx_Items[i]->Icono() != 0) {
														BIconos = true;
														break;
													}
												}
												MostrarIconos(BIconos);
												ListaEx_Estilos.Colores.ColoresItem.TextoResaltado.Enlazar(&DWL::SO::DWLEstilos::Colores.ContenedorEx_Texto_SeleccionadoResaltado);
												ListaEx_Estilos.Colores.ColoresItem.FondoResaltado.Enlazar(&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_SeleccionadoResaltado);
												ListaEx_Estilos.Colores.ColoresItem.FondoNormal.Enlazar(&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Claro);
												ListaEx_Estilos.Colores.Fondo.Enlazar(&DWL::SO::DWLEstilos::Colores.ContenedorEx_Fondo_Claro);
												CrearListaEx(WS_POPUP, 0, Recta.left - 2, Recta.bottom + 1, (Recta.right - Recta.left) + 4, Altura, 0, true);
												//Colores.TextoResaltado					= DWL_COLORESEX_CONTENEDOR_TEXTO_SELECCIONADO_RESALTADO;

//												int nAncho = 15;
//												int Diferencia = _ListaEx_AltoLinea - nAncho;
												//_ScrollV->Mover(_ScrollV->X() + Diferencia, _ScrollV->Y(), nAncho, _ScrollV->Alto() + 1);
												//MirarScrollVisible();
//												SetWindowLongPtr(_hWnd, GWL_EXSTYLE, 0x00080000 | WS_EX_TOPMOST | WS_EX_TOOLWINDOW);
												//Opacidad(DWL_EDICIONDESPLEGABLEEX_OPACIDAD_LISTA);
//												SetWindowPos(_hWnd, HWND_TOPMOST, Recta.left, Recta.bottom +1, Recta.right - Recta.left, Alto() + 1, SWP_NOACTIVATE);
												SetFocus(_hWnd);
												ActualizarTodo();
												Visible(true);
//												Repintar(true);
												_hWndParent = hWndParent;
												SetCapture(_hWnd);
												SetTimer(_hWnd, DWL_EDICIONDESPLEGABLEEX_TIMER_FOCO, 500, NULL);
											};

		 LRESULT                            Evento_Temporizador(const UINT cID) {
												if (cID == DWL_EDICIONDESPLEGABLEEX_TIMER_FOCO) {
													if (GetFocus() != _hWnd) {
														Visible(false);
														SendMessage(_hWndParent, DWL_EDICIONDESPLEGABLEEX_LISTA_OCULTADA, 0, 0);
													KillTimer(_hWnd, DWL_EDICIONDESPLEGABLEEX_TIMER_FOCO);
													}
												}
												return DWLListaEx::Evento_Temporizador(cID);
											};

		 LRESULT							Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param) {
												_SeleccionFinal = _ListaEx_ItemPresionado;
												RECT RC;
												GetClientRect(_hWnd, &RC);
												POINT Pt = { cX, cY };

												if (PtInRect(&RC, Pt) == FALSE) {
													ReleaseCapture();
													Visible(false);
													SendMessage(_hWndParent, DWL_EDICIONDESPLEGABLEEX_LISTA_OCULTADA, 0, 0);
													KillTimer(_hWnd, DWL_EDICIONDESPLEGABLEEX_TIMER_FOCO);
													return 0;
												}

												ListaEx_Mouse_BotonSoltado(_hWnd, &RC, Boton, cX, cY, Param);
												if (_SeleccionFinal != NULL) {
													ReleaseCapture();
													SendMessage(_hWndParent, DWL_EDICIONDESPLEGABLEEX_CAMBIO_SELECCION_LISTA, PtrToLong(_SeleccionFinal), 0);
													Visible(false);
												}
												else {
													Repintar();
												}
                                                return 0;
											};

 		 LRESULT                            Evento_Mouse_Entrando(const int cX, const int cY, const UINT Param) {
												//Opacidad(255);
												return 0;
											};

		 LRESULT                            Evento_Mouse_Saliendo(void) {
												//Opacidad(DWL_EDICIONDESPLEGABLEEX_OPACIDAD_LISTA);
												return DWLListaEx::Evento_Mouse_Saliendo();
											};


		 LRESULT							Evento_Foco_Perdido(HWND NuevoFoco) {
												#if _MSC_VER > 1200
													DWL::ControlesEx::DWLListaEx::Evento_Foco_Perdido(NuevoFoco);
												#else
													DWLListaEx::Evento_Foco_Perdido(NuevoFoco);
												#endif
//												SendMessage(_hWndParent, DWL_EDICIONDESPLEGABLEEX_LISTA_OCULTADA, 0, 0);
//												Visible(false);
                                                return 0;
											};
		protected : //////////////////////////

		 HWND				                _hWndParent;
		 DWL::ControlesEx::DWLListaEx_Item *_SeleccionFinal;
		};




		class DWLEdicionDesplegableEx_Nucleo : public DWLEdicionEx_Nucleo {
		public:
																	DWLEdicionDesplegableEx_Nucleo(void);
																   ~DWLEdicionDesplegableEx_Nucleo(void) { };
		 void														EdicionDesplegableEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true, const bool PintarConMascara = false);
		 DWL::ControlesEx::DWLBotonEx_Colores						EdicionDesplegableEx_ColoresBoton;
 		protected :
		 virtual void												EdicionDesplegableEx_Evento_Pintar_Borde(HDC hDC, HRGN Region, const bool TieneFoco);
		 void														EdicionDesplegableEx_PintarBotonEx(HDC hDC, RECT *Espacio, const bool TieneFoco);
		 int													   _EdicionDesplegableEx_EstadoBotonEx;
		 int													   _EdicionDesplegableEx_AltoLista;
		 int													   _EdicionDesplegableEx_IconoEdicionTexto;
		 DWLEdicionDesplegableEx_ContenedorListaEx				   _EdicionDesplegableEx_ContenedorLista;
		 DWLEdicionDesplegableEx_ContenedorExplorarDirectorios	   _EdicionDesplegableEx_ContenedorExplorarDirectorios;
		 DWL_Enum_EdicionDesplegableEx_Tipo						   _EdicionDesplegableEx_TipoEdicion;
		 bool                                                      _EdicionDesplegableEx_Activado;

		};




        class DWLEdicionDesplegableEx : public DWLEdicionDesplegableEx_Nucleo, public DWL::ControlesEx::Base::DWLControlEx {
		public:
																	DWLEdicionDesplegableEx(void);
																   ~DWLEdicionDesplegableEx(void);
		 HWND														CrearEdicionDesplegableEx(const long Estilos, HWND hWndParent, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, const int nAltoLista, const int cID, const bool nTextoModificable = true, const int nIcono = 0, const DWL_Enum_EdicionDesplegableEx_Tipo TipoEdicion = DWL_Enum_EdicionDesplegableEx_Tipo_ListaDesplegable);

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
         HWND														ConectarEdicionDesplegableEx(HWND hWndParent, const TCHAR *nTexto, const int nAltoLista, const int cID, const bool nTextoModificable = true, const int nIcono = 0, const DWL_Enum_EdicionDesplegableEx_Tipo TipoEdicion = DWL_Enum_EdicionDesplegableEx_Tipo_ListaDesplegable);

		 DWLExplorarDirectorios_Nodo                               *BuscarDirectorio_AgregarSugerencia(const TCHAR *nNombre, const bool EsDirectorio = true, DWLExplorarDirectorios_Nodo *nPadre = NULL, const UINT nIcono = 0, const bool nNegrita = false) {
																		return _EdicionDesplegableEx_ContenedorExplorarDirectorios.AgregarSugerencia(nNombre, EsDirectorio, nPadre, nIcono, nNegrita);
																	}
		 void                                                       BuscarDirectorio_EliminarSugerencias(void) {
																		_EdicionDesplegableEx_ContenedorExplorarDirectorios.EliminarSugerencias();
																	};

		 inline int											        Icono(void) const {
																		return _EdicionDesplegableEx_IconoEdicionTexto;
																	}

		 void                                                       Activado(const bool nActivar);

		 inline BOOL                                                Activado(void) { return static_cast<BOOL>(_EdicionDesplegableEx_Activado); };

/*		 virtual const bool											Foco(void) {
																		bool TieneFoco = false;

																		POINT Pt;
																		GetCursorPos(&Pt);
																		if (_hWnd == WindowFromPoint(Pt)) { // Tiene el foco del raton
																			TieneFoco = true;
																		}
																		return TieneFoco;
																	};*/

		 virtual BOOL								                Destruir(void) {
																		_EdicionDesplegableEx_ContenedorLista.Destruir();
																		_EdicionDesplegableEx_ContenedorExplorarDirectorios.Destruir();
																		#if _MSC_VER > 1200
                                                                            return DWL::ControlesEx::Base::DWLControlEx::Destruir();
																		#else
																			return DWLControlEx::Destruir();
																		#endif
																	};

 		 void														Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool Repintar = false) {
																		if (_EdicionDesplegableEx_ContenedorLista.ListaEx_Columna(0) != NULL) _EdicionDesplegableEx_ContenedorLista.ListaEx_Columna(0)->Ancho(cAncho -20, false);
																		SetWindowRgn(_hWnd, CreateRoundRectRgn(0, 0, cAncho + 1, cAlto + 1, 2, 2), FALSE);
																		MoveWindow(_hWnd, cX, cY, cAncho, cAlto, Repintar);
																	};


		 inline DWLListaEx_Item									   *Item(const unsigned int Pos) {
																		return _EdicionDesplegableEx_ContenedorLista.Item(Pos);
																	};

		 void														AgregarItem(const TCHAR *nTxt, const int Icono = 0);

		 void                                                       SeleccionarItem(const UINT Pos);
		 const int                                                  ItemSeleccionado(void);

		 void														FinAgregarItems(void);

		 inline void												EliminarItem(const unsigned int Pos) {
																		_EdicionDesplegableEx_ContenedorLista.EliminarItem(Pos);
																	};

		 inline const TCHAR						                   *ObtenerTextoItem(const unsigned int Pos) {
																		return _EdicionDesplegableEx_ContenedorLista.Item(Pos)->Texto(0);
																	};

		 inline UINT               									TotalItems(void) const {
																		return _EdicionDesplegableEx_ContenedorLista.TotalItems();
																	};

		 inline void						                        Texto(const TCHAR *nTexto, const int nIcono = 0, const bool nRepintar = true) {
//																		if (_EdicionDesplegableEx_TipoEdicion == DWL::Enums::Tipo_BuscarDirectorio && nIcono == 0) {
//																			_EdicionDesplegableEx_IconoEdicionTexto = _EdicionDesplegableEx_ContenedorExplorarDirectorios.CargarIcono(nTexto);
//																		}
//																		else {
																		_EdicionDesplegableEx_IconoEdicionTexto = nIcono;
//																		}
																		EdicionEx_BorrarTexto();
																		EdicionEx_AgregarTexto(_hWnd, nTexto);
																		Repintar();
																	};

		 inline const TCHAR										   *Texto(void) {
																		return EdicionEx_ObtenerTexto();
																	};

		 inline UINT            									LongitudTexto(void) const {
																		return EdicionEx_LongitudTexto();
																	};

		 inline void												MostrarLista(const int Altura) {
 																		_EdicionDesplegableEx_ContenedorLista.Mostrar(_hWnd, Altura);
																	};

		 void														BorrarTodo(const bool nRepintar = false) {
																		_EdicionDesplegableEx_ContenedorLista.EliminarTodosLosItems();
																		if (nRepintar == true) Repintar();
																	};

		 LRESULT    												Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);

		 DWL::ControlesEx::DWLListaEx_Colores				       *ColoresContenedorListaEx(void) {
																		return &_EdicionDesplegableEx_ContenedorLista.ListaEx_Estilos.Colores;
																	}

		 DWL::ControlesEx::DWLListaEx_Fuentes			           *FuentesContenedorListaEx(void) {
																		return &_EdicionDesplegableEx_ContenedorLista.ListaEx_Estilos.Fuentes;
																	}

		 DWL::ControlesEx::DWLBarraScrollEx_Colores				   *ColoresContenedorBarraScrollEx(void) {
																		return &_EdicionDesplegableEx_ContenedorLista.BarraScrollEx_Colores;
																	}

//		 DWL::ControlesEx::DWLBotonEx_Colores						ColoresBoton;
		 virtual LRESULT											Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Params);
		 virtual LRESULT											Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Params);
		 virtual LRESULT											Evento_Teclado_Caracter(const UINT Caracter, const UINT Repeticion, const UINT Params);
		 virtual LRESULT											Evento_Temporizador(const UINT tID);
		 virtual LRESULT											Evento_Foco_Obtenido(HWND FocoAnterior);
		 virtual LRESULT											Evento_Foco_Perdido(HWND NuevoFoco);
		 void														Repintar(void);
		protected :
		 virtual LRESULT											Evento_Mouse_Saliendo(void);
		 virtual LRESULT											Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param);
		 virtual LRESULT											Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
		 virtual LRESULT											Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);
//		 void														BorrarMemoriaEx(void);
/*		 void														PintarBotonEx(HDC hDC, RECT *Espacio);
		 int													   _EstadoBotonEx;
		 int													   _AltoLista;
		 int													   _IconoEdicionTexto;
		 DWLEdicionDesplegableEx_ContenedorListaEx				   _ContenedorLista;
		 DWLEdicionDesplegableEx_ContenedorExplorarDirectorios	   _ContenedorExplorarDirectorios;
		 DWL_Enum_EdicionDesplegableEx_Tipo					   _TipoEdicion;*/

		 virtual LRESULT CALLBACK									GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
		};
	}

}

#endif // DWL_DWLEdicionDesplegableEx_H

