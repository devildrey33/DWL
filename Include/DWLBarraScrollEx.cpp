//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DWLBarraScrollEx.h																															//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Descripción :																																//
//					Estas clases forman parte del nucleo para crear controles extendidos con scroll. Se pueden crear 2 scrolls (V/H)			//
//					son totalmente configurables en apariencia, y tienen posibilidad de añadir botones extendidos.								//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Este archivo contiene varias clases descritas a continuacion :																				//
// - DWLBarraScrollEx_Colores			:	Clase que enlaza los colores a la configuracion del skin por defecto								//
//											Puedes modificar cualquier color de esta clase, solo deberas repintar el scroll al terminar.		//
//																																				//
// - DWLBarraScrollEx_Boton				:	Clase que contiene los datos para los botones extendidos del scroll.								//
//																																				//
// - DWLBarraScrollEx_ParametrosClick	:	Clase utilizada internamente para pasar los datos de un click a la ventana padre.					//
//																																				//
//																																				//
// - DWLBarraScrollEx_Nucleo			:	Clase que contiene las Funciónes basicas para pintar y controlar los eventos del scroll.			//
//											Esta clase se ha creado de forma que puede compartir un control con otra clase.						//
//																																				//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Archivo creado por devildrey33 el dia 20/05/2007	para http://www.devildrey33.es																//
// Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :		//
//  http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																		//
//  http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)																//
//  http://www.softcatala.cat/wiki/GPL3		 (Catalá, traduccion no oficial)																	//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Version 0.95																																	//
// Ultima modificación : 04/11/2009																												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "DWLBarraScrollEx.h"
#include "DWLListaIconos.h"
#include "DWLGraficos.h"

#define ANCHO_MINIMO_SCROLL 5

namespace DWL {
	namespace ControlesEx {

		//! Constructor.
		/*! Constructor.
			\fn			DWLBarraScrollEx_Nucleo(void);
			\return		No devuelve nada.
		*/
		DWLBarraScrollEx_Nucleo::DWLBarraScrollEx_Nucleo(void) {
		    #if defined DWL_BaseControlExScroll_DEBUG
			    DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::DWLBarraScrollEx\n"));
		    #endif
			_BarraScrollEx_VisibleH			= FALSE;
			_BarraScrollEx_ValorH			= 0;
			_BarraScrollEx_UValorH			= -1;
			_BarraScrollEx_MaximoH			= 10;
			_BarraScrollEx_PaginaH			= 5;
			_BarraScrollEx_PosActualH		= 0;

			_BarraScrollEx_VisibleV			= FALSE;
			_BarraScrollEx_ValorV			= 0;
			_BarraScrollEx_UValorV			= -1;
			_BarraScrollEx_MaximoV			= 10;
			_BarraScrollEx_PaginaV			= 5;
			_BarraScrollEx_PosActualV		= 0;

			_BarraScrollEx_EstadoV			= DWL_Enum_BarraScrollEx_Estado_Normal;
			_BarraScrollEx_EstadoH			= DWL_Enum_BarraScrollEx_Estado_Normal;
			_BarraScrollEx_UEstadoV			= DWL_Enum_BarraScrollEx_Estado_Normal;
			_BarraScrollEx_UEstadoH			= DWL_Enum_BarraScrollEx_Estado_Normal;
			_BarraScrollEx_PresionadoH		= DWL_Enum_BarraScrollEx_ControlPresionado_Ninguno;
			_BarraScrollEx_PresionadoV		= DWL_Enum_BarraScrollEx_ControlPresionado_Ninguno;
			_BarraScrollEx_PosInicio.x		= 0;
			_BarraScrollEx_PosInicio.y		= 0;
			_BarraScrollEx_Capturado		= false;
			_BarraScrollEx_Activado         = true;
		}

		//! Destructor.
		/*! Destructor.
			\fn			~DWLBarraScrollEx_Nucleo(void);
			\return		No devuelve nada.
		*/
		DWLBarraScrollEx_Nucleo::~DWLBarraScrollEx_Nucleo(void) {
		    #if defined DWL_BaseControlExScroll_DEBUG
			    DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::~DWLBarraScrollEx\n"));
		    #endif
			size_t i = 0;
			for (i = 0; i < _BarraScrollEx_BotonesV.size(); i++) delete _BarraScrollEx_BotonesV[i];
			for (i = 0; i < _BarraScrollEx_BotonesH.size(); i++) delete _BarraScrollEx_BotonesH[i];
		}


		//! Función que crea la barra de scroll vertical.
		/*! Esta funcion crea la barra de scroll vertical en nuestro control.
			\fn			void BarraScrollEx_CrearV(const BOOL nVisible = DWL_BARRASCROLLEX_AUTOMATICO, const long nMaximo = 10, const long nPagina = 5, const long nValor = 0);
			\param[in]	nVisible	: TRUE para que sea visible, FALSE para que sea invisible. Tambien puedes especificar el parametro DWL_BARRASCROLLEX_AUTOMATICO.
			\param[in]	nMaximo		: Valor maximo para el scroll.
			\param[in]	nPagina		: Valor de la pagina para el scroll.
			\param[in]	nValor		: Valor actual para el scroll.
			\return		No devuelve nada.
			\remarks	Si nVisible es DWL_BARRASCROLLEX_AUTOMATICO, se mirara si _BarraScrollEx_MaximoV es mas grande que _BarraScrollEx_PaginaV para decidir si el scroll es visible.
						Si el maximo supera la pagina el scroll sera visible, en caso contrario no se vera.
			\sa			BarraScrollEx_CrearH()
		*/
		void DWLBarraScrollEx_Nucleo::BarraScrollEx_CrearV(const BOOL nVisible, const long nMaximo, const long nPagina, const long nValor) {
		#if defined DWL_BaseControlExScroll_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::CrearBarraScrollExV\n"));
		#endif
			_BarraScrollEx_MaximoV = nMaximo;
			_BarraScrollEx_PaginaV = nPagina;
			_BarraScrollEx_ValorV = nValor;

			_BarraScrollEx_VisibleV = nVisible;
		};


		//! Función que crea la barra de scroll horizontal.
		/*! Esta funcion crea la barra de scroll horizontal en nuestro control.
			\fn			void BarraScrollEx_CrearH(const BOOL nVisible = DWL_BARRASCROLLEX_AUTOMATICO, const long nMaximo = 10, const long nPagina = 5, const long nValor = 0);
			\param[in]	nVisible	: TRUE para que sea visible, FALSE para que sea invisible. Tambien puedes especificar el parametro DWL_BARRASCROLLEX_AUTOMATICO.
			\param[in]	nMaximo		: Valor maximo para el scroll.
			\param[in]	nPagina		: Valor de la pagina para el scroll.
			\param[in]	nValor		: Valor actual para el scroll.
			\return		No devuelve nada.
			\remarks	Si nVisible es DWL_BARRASCROLLEX_AUTOMATICO, se mirara si _BarraScrollEx_MaximoH es mas grande que _BarraScrollEx_PaginaH para decidir si el scroll es visible.
						Si el maximo supera la pagina el scroll sera visible, en caso contrario no se vera.
			\sa			BarraScrollEx_CrearV()
		*/
		void DWLBarraScrollEx_Nucleo::BarraScrollEx_CrearH(const BOOL nVisible, const long nMaximo, const long nPagina, const long nValor) {
		#if defined DWL_BaseControlExScroll_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::CrearBarraScrollExH\n"));
		#endif
			_BarraScrollEx_MaximoH = nMaximo;
			_BarraScrollEx_PaginaH = nPagina;
			_BarraScrollEx_ValorH = nValor;
			_BarraScrollEx_VisibleH = nVisible;
		};

		//! Función que agrega un boton extendido a la barra de scroll vertical.
		/*! Esta funcion agrega un boton extendido a la barra de scroll vertical.
			\fn			BOOL BarraScrollEx_AgregarBotonV(const UINT IconoRecursos, const UINT IDBoton);
			\param[in]	IconoRecursos	: ID del icono de los recursos que usara este boton.
			\param[in]	IDBoton			: ID de este boton extendido.
			\return		Devuelve TRUE si se ha creado correctamente, FALSE si la ID del boton ya existe.
			\remarks	Los botones comparten el estado visible de su barra, es decir si la barra vertical es visible los botones verticales tambien.
			\sa			BarraScrollEx_AgregarBotonH(), BarraScrollEx_Evento_BotonExtendido_Click()

		*/
		BOOL DWLBarraScrollEx_Nucleo::BarraScrollEx_AgregarBotonV(const UINT IconoRecursos, const UINT IDBoton) {
            for (size_t i = 0; i < _BarraScrollEx_BotonesV.size(); i++) if (IDBoton == _BarraScrollEx_BotonesV[i]->IDControl) return FALSE;
			DWLBarraScrollEx_Boton *Tmp = new DWLBarraScrollEx_Boton(IconoRecursos, IDBoton);
			_BarraScrollEx_BotonesV.push_back(Tmp);
            return TRUE;
		}

		//! Función que agrega un boton extendido a la barra de scroll horizontal.
		/*! Esta funcion agrega un boton extendido a la barra de scroll horizontal.
			\fn			BOOL BarraScrollEx_AgregarBotonH(const UINT IconoRecursos, const UINT IDBoton);
			\param[in]	IconoRecursos	: ID del icono de los recursos que usara este boton.
			\param[in]	IDBoton			: ID de este boton extendido.
			\return		Devuelve TRUE si se ha creado correctamente, FALSE si la ID del boton ya existe.
			\remarks	Los botones comparten el estado visible de su barra, es decir si la barra horizontal es visible los botones horizontales tambien.
			\sa			BarraScrollEx_AgregarBotonV(), BarraScrollEx_Evento_BotonExtendido_Click()
		*/
		BOOL DWLBarraScrollEx_Nucleo::BarraScrollEx_AgregarBotonH(const UINT IconoRecursos, const UINT IDBoton) {
            for (size_t i = 0; i < _BarraScrollEx_BotonesH.size(); i++) if (IDBoton == _BarraScrollEx_BotonesH[i]->IDControl) return FALSE;
			DWLBarraScrollEx_Boton *Tmp = new DWLBarraScrollEx_Boton(IconoRecursos, IDBoton);
			_BarraScrollEx_BotonesH.push_back(Tmp);
            return TRUE;
		}

        //! Función que elimina un boton extendido a la barra de scroll vertical.
        /*! Esta funcion elimina un boton extendido a la barra de scroll vertical.
            \fn			BOOL BarraScrollEx_EliminarBotonV(const UINT IDBoton);
            \param[in]	IDBoton			: ID de este boton extendido.
            \return		Devuelve TRUE si se ha eliminado correctamente, FALSE si la ID del boton no existe.
            \remarks	Los botones comparten el estado visible de su barra, es decir si la barra horizontal es visible los botones horizontales tambien.
            \sa			BarraScrollEx_AgregarBotonV(), BarraScrollEx_Evento_BotonExtendido_Click()
        */
        BOOL DWLBarraScrollEx_Nucleo::BarraScrollEx_EliminarBotonV(const UINT IDBoton) {
            for (size_t i = 0; i < _BarraScrollEx_BotonesV.size(); i++) {
                if (IDBoton == _BarraScrollEx_BotonesV[i]->IDControl) {
                    delete _BarraScrollEx_BotonesV[i];
                    _BarraScrollEx_BotonesV.erase(_BarraScrollEx_BotonesV.begin() + i);
                    return TRUE;
                }
            }
            return FALSE;
        }

		//! Función que elimina un boton extendido a la barra de scroll horizontal.
		/*! Esta funcion elimina un boton extendido a la barra de scroll horizontal.
			\fn			BOOL BarraScrollEx_EliminarBotonH(const UINT IDBoton);
			\param[in]	IDBoton			: ID de este boton extendido.
			\return		Devuelve TRUE si se ha eliminado correctamente, FALSE si la ID del boton no existe.
			\remarks	Los botones comparten el estado visible de su barra, es decir si la barra horizontal es visible los botones horizontales tambien.
			\sa			BarraScrollEx_AgregarBotonV(), BarraScrollEx_Evento_BotonExtendido_Click()
		*/
        BOOL DWLBarraScrollEx_Nucleo::BarraScrollEx_EliminarBotonH(const UINT IDBoton) {
            for (size_t i = 0; i < _BarraScrollEx_BotonesH.size(); i++) {
                if (IDBoton == _BarraScrollEx_BotonesH[i]->IDControl) {
                    delete _BarraScrollEx_BotonesH[i];
                    _BarraScrollEx_BotonesH.erase(_BarraScrollEx_BotonesH.begin() + i);
                    return TRUE;
                }
            }
            return FALSE;
        }

		//! Función que elimina los botones extendido a la barra de scroll vertical.
		/*! Esta funcion elimina los botones extendido a la barra de scroll vertical.
			\fn			void BarraScrollEx_EliminarBotonesV(void);
			\return		Esta función no devuelve nada.
			\remarks	Los botones comparten el estado visible de su barra, es decir si la barra horizontal es visible los botones horizontales tambien.
			\sa			BarraScrollEx_AgregarBotonV(), BarraScrollEx_Evento_BotonExtendido_Click()
		*/
        void DWLBarraScrollEx_Nucleo::BarraScrollEx_EliminarBotonesV(void) {
            for (size_t i = 0; i < _BarraScrollEx_BotonesV.size(); i++) delete _BarraScrollEx_BotonesV[i];
            _BarraScrollEx_BotonesV.resize(0);
        }

		//! Función que elimina los botones extendido a la barra de scroll horizontal.
		/*! Esta funcion elimina los botones extendido a la barra de scroll horizontal.
			\fn			void BarraScrollEx_EliminarBotonesH(void);
			\return		Esta función no devuelve nada.
			\remarks	Los botones comparten el estado visible de su barra, es decir si la barra horizontal es visible los botones horizontales tambien.
			\sa			BarraScrollEx_AgregarBotonV(), BarraScrollEx_Evento_BotonExtendido_Click()
		*/
        void DWLBarraScrollEx_Nucleo::BarraScrollEx_EliminarBotonesH(void) {
            for (size_t i = 0; i < _BarraScrollEx_BotonesH.size(); i++) delete _BarraScrollEx_BotonesH[i];
            _BarraScrollEx_BotonesH.resize(0);
        }

		//! Función que calcula las posiciones de todos los controles del scroll.
		/*! Esta funcion calcula las posiciones de todos los controles del scroll.
				\fn			void BarraScrollEx_PosicionarScrolls(HWND hWndControl, RECT *EspacioControl, const bool nRepintar = false, const bool TieneBorde = false);
				\param[in]	hWndControl		: HWND de la ventana destino donde se van a repintar los scrolls.
				\param[in]	EspacioControl	: Espacio de todo el control (no solo de la barra de scroll).
				\param[in]  nRepintar		: Valor que especifica si se repintara el control.
				\param[in]  nTieneBorde		: Valor en el que especificamos si el control tiene borde.
				\return		No devuelve nada.
				\remarks	Si en el parametro nTieneBorde especificamos true, el scroll se reducira 2 pixeles de tamaño para no engancharse con el borde del control. Esta funcion deberia ser usada siempre que se cambie el tamaño del control.
		*/
		void DWLBarraScrollEx_Nucleo::BarraScrollEx_PosicionarScrolls(HWND hWndControl, RECT *EspacioControl, const bool nRepintar, const bool TieneBorde) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::BarraScrollEx_PosicionarScrolls\n"));
			#endif
			int AnchoBordeControl = 0;
			if (TieneBorde == true) AnchoBordeControl = 2;
			_BarraScrollEx_EspacioV.left	= EspacioControl->right - (17 + (AnchoBordeControl));
			_BarraScrollEx_EspacioV.top		= EspacioControl->top + AnchoBordeControl;
			_BarraScrollEx_EspacioV.right	= _BarraScrollEx_EspacioV.left + 17; // todas las barras tendran 17 pixeles de ancho

			if (BarraScrollEx_VisibleH() == TRUE)	_BarraScrollEx_EspacioV.bottom = EspacioControl->bottom - (17 + (AnchoBordeControl));
			else									_BarraScrollEx_EspacioV.bottom = EspacioControl->bottom;

			BarraScrollEx_CalcularScrollV(TieneBorde);


			_BarraScrollEx_EspacioH.left	= EspacioControl->left + AnchoBordeControl;
			_BarraScrollEx_EspacioH.top		= EspacioControl->bottom - (17 + (AnchoBordeControl));
			_BarraScrollEx_EspacioH.bottom	= _BarraScrollEx_EspacioH.top + 17;
			if (BarraScrollEx_VisibleV() == TRUE)	_BarraScrollEx_EspacioH.right = EspacioControl->right - (17 + (AnchoBordeControl));
			else									_BarraScrollEx_EspacioH.right = EspacioControl->right;

			BarraScrollEx_CalcularScrollH(TieneBorde);

			if (nRepintar == true) BarraScrollEx_Repintar(hWndControl, true);
		}


		//! Función que pinta el scroll vertical en el DC especificado.
		/*! Esta función pinta el scroll vertical en el DC especificado.
			\fn			void BarraScrollEx_PintarV(HDC hDC);
			\param[in]	hDC : hDC donde se pintara la barra de scroll vertical.
			\return		No devuelve nada.
		*/
		void DWLBarraScrollEx_Nucleo::BarraScrollEx_PintarV(HDC hDC) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::BarraScrollEx_PintarV\n"));
			#endif
			if (_BarraScrollEx_VisibleV == false) return;
			if (_BarraScrollEx_VisibleV == DWL_BARRASCROLLEX_AUTOMATICO) {
				if (_BarraScrollEx_MaximoV <= _BarraScrollEx_PaginaV) return;
			}
			int     An		= (_BarraScrollEx_EspacioV.right - _BarraScrollEx_EspacioV.left) + 1;
			int     Al		= (_BarraScrollEx_EspacioV.bottom - _BarraScrollEx_EspacioV.top) + 1;
			HDC     Buffer	= CreateCompatibleDC(NULL);
			HBITMAP Bmp		= CreateCompatibleBitmap(hDC, An, Al);
			HBITMAP Viejo	= static_cast<HBITMAP>(SelectObject(Buffer, Bmp));
			RECT    TMP;
			// Pinto el fondo
			TMP.left = 0; TMP.top = 0; TMP.right = _BarraScrollEx_EspacioV.right; TMP.bottom = _BarraScrollEx_EspacioV.bottom;
			HBRUSH Brocha = CreateSolidBrush(BarraScrollEx_Colores.FondoNormal());
			FillRect(Buffer, &TMP, Brocha);
			DeleteObject(Brocha);

			TMP.left = 0; TMP.top = _BarraScrollEx_RectaFondoSuperiorV.top; TMP.right = _BarraScrollEx_RectaFondoSuperiorV.right - _BarraScrollEx_RectaFondoSuperiorV.left; TMP.bottom = _BarraScrollEx_RectaFondoSuperiorV.bottom;
			BarraScrollEx_Evento_Pintar_Fondo(Buffer, &TMP, DWL_Enum_BarraScrollEx_TipoScroll_VerticalSuperior);
			TMP.left = 0; TMP.top = _BarraScrollEx_RectaFondoInferiorV.top; TMP.right = _BarraScrollEx_RectaFondoInferiorV.right - _BarraScrollEx_RectaFondoInferiorV.left; TMP.bottom = _BarraScrollEx_RectaFondoInferiorV.bottom;
			BarraScrollEx_Evento_Pintar_Fondo(Buffer, &TMP, DWL_Enum_BarraScrollEx_TipoScroll_VerticalInferior);
			// Pinto el boton superior
			TMP.left = 0; TMP.top = _BarraScrollEx_RectaBotonSuperiorV.top; TMP.right = _BarraScrollEx_RectaBotonSuperiorV.right - _BarraScrollEx_RectaBotonSuperiorV.left; TMP.bottom = _BarraScrollEx_RectaBotonSuperiorV.bottom;
			BarraScrollEx_Evento_Pintar_Boton(Buffer, &TMP, DWL_DIRECCION_FLECHA_ARRIBA);
			// Pinto el boton Inferior
			TMP.left = 0; TMP.top = _BarraScrollEx_RectaBotonInferiorV.top; TMP.right = _BarraScrollEx_RectaBotonInferiorV.right - _BarraScrollEx_RectaBotonInferiorV.left; TMP.bottom = _BarraScrollEx_RectaBotonInferiorV.bottom;
			BarraScrollEx_Evento_Pintar_Boton(Buffer, &TMP, DWL_DIRECCION_FLECHA_ABAJO);
			// Pinto el rectangulo del scroll
			TMP.left = 0; TMP.top = _BarraScrollEx_RectaScrollV.top; TMP.right = _BarraScrollEx_RectaScrollV.right - _BarraScrollEx_RectaScrollV.left; TMP.bottom = _BarraScrollEx_RectaScrollV.bottom;
			BarraScrollEx_Evento_Pintar_Scroll(Buffer, &TMP, DWL_Enum_BarraScrollEx_TipoScroll_Vertical);

			for (size_t i = 0; i < _BarraScrollEx_BotonesV.size(); i++) {
				TMP.left = 0; TMP.top = _BarraScrollEx_BotonesV[i]->Posicion.top; TMP.right = _BarraScrollEx_BotonesV[i]->Posicion.right - _BarraScrollEx_BotonesV[i]->Posicion.left; TMP.bottom = _BarraScrollEx_BotonesV[i]->Posicion.bottom;
				BarraScrollEx_Evento_Pintar_Boton(Buffer, &TMP, DWL_DIRECCION_FLECHA_EXTENDIDA, _BarraScrollEx_BotonesV[i]->IDIcono, _BarraScrollEx_BotonesV[i]->Estado);
			}

			BitBlt(hDC, _BarraScrollEx_EspacioV.left, _BarraScrollEx_EspacioV.top, _BarraScrollEx_EspacioV.right - _BarraScrollEx_EspacioV.left, _BarraScrollEx_EspacioV.bottom - _BarraScrollEx_EspacioV.top, Buffer, 0, _BarraScrollEx_EspacioV.top, SRCCOPY);

			SelectObject(Buffer, Viejo);
			DeleteObject(Bmp);
			DeleteDC(Buffer);
		};


		//! Función que pinta el scroll horizontal en el DC especificado.
		/*! Esta función pinta el scroll horizontal en el DC especificado.
			\fn			void BarraScrollEx_PintarH(HDC hDC);
			\param[in]	hDC : hDC donde se pintara la barra de scroll horizontal.
			\return		No devuelve nada.
		*/
		void DWLBarraScrollEx_Nucleo::BarraScrollEx_PintarH(HDC hDC) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::BarraScrollEx_PintarH\n"));
			#endif
			if (_BarraScrollEx_VisibleH == false) {
				return;
			}
			if (_BarraScrollEx_VisibleH == DWL_BARRASCROLLEX_AUTOMATICO) {
				if (_BarraScrollEx_MaximoH <= _BarraScrollEx_PaginaH) return;
			}

			int     An		= (_BarraScrollEx_EspacioH.right - _BarraScrollEx_EspacioH.left) + 1;
			int     Al		= (_BarraScrollEx_EspacioH.bottom - _BarraScrollEx_EspacioH.top) + 1;
			HDC     Buffer	= CreateCompatibleDC(NULL);
			HBITMAP Bmp		= CreateCompatibleBitmap(hDC, An, Al);
			HBITMAP Viejo	= static_cast<HBITMAP>(SelectObject(Buffer, Bmp));
			RECT    TMP;
			// Pinto el fondo
			TMP.left = 0; TMP.top = 0; TMP.right = _BarraScrollEx_EspacioH.right; TMP.bottom = _BarraScrollEx_EspacioH.bottom;
			HBRUSH Brocha = CreateSolidBrush(BarraScrollEx_Colores.FondoNormal());
			FillRect(Buffer, &TMP, Brocha);
			DeleteObject(Brocha);

			TMP.left = _BarraScrollEx_RectaFondoSuperiorH.left; TMP.top = 0; TMP.right = _BarraScrollEx_RectaFondoSuperiorH.right; TMP.bottom = _BarraScrollEx_RectaFondoSuperiorH.bottom - _BarraScrollEx_RectaFondoSuperiorH.top;
			BarraScrollEx_Evento_Pintar_Fondo(Buffer, &TMP, DWL_Enum_BarraScrollEx_TipoScroll_HorizontalDerecho);
			TMP.left = _BarraScrollEx_RectaFondoInferiorH.left; TMP.top = 0; TMP.right = _BarraScrollEx_RectaFondoInferiorH.right; TMP.bottom = _BarraScrollEx_RectaFondoInferiorH.bottom - _BarraScrollEx_RectaFondoInferiorH.top;
			BarraScrollEx_Evento_Pintar_Fondo(Buffer, &TMP, DWL_Enum_BarraScrollEx_TipoScroll_HorizontalIzquierdo);
			// Pinto el boton Izquierdo
			TMP.left = _BarraScrollEx_RectaBotonIzquierdoH.left; TMP.top = 0; TMP.right = _BarraScrollEx_RectaBotonIzquierdoH.right; TMP.bottom = _BarraScrollEx_RectaBotonIzquierdoH.bottom - _BarraScrollEx_RectaBotonIzquierdoH.top;
			BarraScrollEx_Evento_Pintar_Boton(Buffer, &TMP, DWL_DIRECCION_FLECHA_IZQUIERDA);
			// Pinto el boton Derecho
			TMP.left = _BarraScrollEx_RectaBotonDerechoH.left; TMP.top = 0; TMP.right = _BarraScrollEx_RectaBotonDerechoH.right; TMP.bottom = _BarraScrollEx_RectaBotonDerechoH.bottom - _BarraScrollEx_RectaBotonDerechoH.top;
			BarraScrollEx_Evento_Pintar_Boton(Buffer, &TMP, DWL_DIRECCION_FLECHA_DERECHA);
			// Pinto el rectangulo del scroll
			TMP.left = _BarraScrollEx_RectaScrollH.left; TMP.top = 0; TMP.right = _BarraScrollEx_RectaScrollH.right; TMP.bottom = _BarraScrollEx_RectaScrollH.bottom - _BarraScrollEx_RectaScrollH.top;
			BarraScrollEx_Evento_Pintar_Scroll(Buffer, &TMP, DWL_Enum_BarraScrollEx_TipoScroll_Horizontal);

			for (size_t i = 0; i < _BarraScrollEx_BotonesH.size(); i++) {
				TMP.left = _BarraScrollEx_BotonesH[i]->Posicion.left; TMP.top = 0; TMP.right = _BarraScrollEx_BotonesH[i]->Posicion.right; TMP.bottom = _BarraScrollEx_BotonesH[i]->Posicion.bottom - _BarraScrollEx_BotonesH[i]->Posicion.top;
				BarraScrollEx_Evento_Pintar_Boton(Buffer, &TMP, DWL_DIRECCION_FLECHA_EXTENDIDA, _BarraScrollEx_BotonesH[i]->IDIcono, _BarraScrollEx_BotonesH[i]->Estado);
			}

			BitBlt(hDC, _BarraScrollEx_EspacioH.left, _BarraScrollEx_EspacioH.top, _BarraScrollEx_EspacioH.right - _BarraScrollEx_EspacioH.left, _BarraScrollEx_EspacioH.bottom - _BarraScrollEx_EspacioH.top, Buffer, _BarraScrollEx_EspacioH.left, 0, SRCCOPY);

			SelectObject(Buffer, Viejo);
			DeleteObject(Bmp);
			DeleteDC(Buffer);
		};

		//! Función para repintar las barras de scroll.
		/*! Esta funcion repinta las barras de scroll si es necesario o si se especifica true en Forzar.
				\fn			void BarraScrollEx_Repintar(HWND hWndControl, const bool Forzar = false);
				\param[in]	hWndControl	: HWND de la ventana destino donde se van a repintar los scrolls.
				\param[in]	nForzar		: Valor que determina si se fuerza el repintado.
				\return		No devuelve nada.
		*/
		void DWLBarraScrollEx_Nucleo::BarraScrollEx_Repintar(HWND hWndControl, const bool Forzar) {
			if (hWndControl == NULL) return;
			//			(hWndControl != NULL);
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::BarraScrollEx_Repintar(Forzar %d)\n"), Forzar);
			#endif
			// Parte del scroll vertical
			bool P = Forzar;
			if (P == false) {
				if (_BarraScrollEx_EstadoV != _BarraScrollEx_UEstadoV)	P = true;
				if (_BarraScrollEx_ValorV != _BarraScrollEx_UValorV)	P = true;
			}
			_BarraScrollEx_UEstadoV = _BarraScrollEx_EstadoV;
			_BarraScrollEx_UValorV = _BarraScrollEx_ValorV;
			HDC	hDC	= GetDC(hWndControl);
			if (P == true) {
				BarraScrollEx_PintarV(hDC);
			}
			// Parte del scroll horizontal
			P = Forzar;
			if (P == false) {
				if (_BarraScrollEx_EstadoH != _BarraScrollEx_UEstadoH)	P = true;
				if (_BarraScrollEx_ValorH != _BarraScrollEx_UValorH)	P = true;
			}
			_BarraScrollEx_UEstadoH = _BarraScrollEx_EstadoH;
			_BarraScrollEx_UValorH = _BarraScrollEx_ValorH;
			if (P == true) {
				BarraScrollEx_PintarH(hDC);
			}

			ReleaseDC(hWndControl, hDC);
		};


		//! Función virtual que pinta un boton en cualquier de sus estados.
		/*! Esta funcion virtual que pinta un boton en cualquier de sus estados.
				\fn			void BarraScrollEx_Evento_Pintar_Boton(HDC hDC, RECT *Espacio, const int TipoBoton, const int IDIcono = 0, const int EstadoBotonEx = 0);
				\param[in]	hDC			: hDC donde se pintara el boton.
				\param[in]  Espacio		: Recta que contiene el espacio del boton.
				\param[in]	TipoBoton	: Tipo de boton.
				\return		No devuelve nada.
				\remarks	Si re-escribes esta función, deberas encargarte de pintar el fondo del boton, el borde y su imagen.
		*/
		void DWLBarraScrollEx_Nucleo::BarraScrollEx_Evento_Pintar_Boton(HDC hDC, RECT *Espacio, const int TipoBoton, const int IDIcono, const int EstadoBotonEx) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::BarraScrollEx_Evento_Pintar_Boton\n"));
			#endif
			COLORREF				C1 = 0;
			COLORREF				C2 = 0;
			COLORREF				CT = 0;
			COLORREF				ColorBorde = 0;
			bool                    BotonPresionado = false;

			if (TipoBoton == DWL_DIRECCION_FLECHA_EXTENDIDA) {
				switch (EstadoBotonEx) {
					case 0 : // normal
						C1 = BarraScrollEx_Colores.DegradadoSuperior();
						C2 = BarraScrollEx_Colores.DegradadoInferior();
						ColorBorde = BarraScrollEx_Colores.BordeNormal();
						break;
					case 1 : // resaltado
						C1 = BarraScrollEx_Colores.DegradadoResaltado();
						C2 = BarraScrollEx_Colores.DegradadoInferior();
						ColorBorde = BarraScrollEx_Colores.BordeFocoRaton();
						break;
					case 2 : // presionado
						C1 = BarraScrollEx_Colores.DegradadoInferior();
						C2 = BarraScrollEx_Colores.DegradadoSuperior();
						ColorBorde = BarraScrollEx_Colores.BordeFocoRaton();
						break;
				}
				DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, C1, C2, true);
				if (BotonPresionado == true) {
					Espacio->left ++;
					Espacio->top ++;
					Espacio->right ++;
					Espacio->bottom ++;
				}
				DWL::SO::DWLListaIconos::PintarIcono(hDC, Espacio->left, Espacio->top, 16, 16, IDIcono);
				if (BotonPresionado == true) {
					Espacio->left --;
					Espacio->top --;
					Espacio->right --;
					Espacio->bottom --;
				}
			}
			else {
				DWL_Enum_BarraScrollEx_Estado EstadoScroll = _BarraScrollEx_EstadoV;
				if (TipoBoton == DWL_DIRECCION_FLECHA_DERECHA || TipoBoton == DWL_DIRECCION_FLECHA_IZQUIERDA) EstadoScroll = _BarraScrollEx_EstadoH;
				switch (EstadoScroll) {
					case DWL_Enum_BarraScrollEx_Estado_BotonSuperiorResaltado :
						if (TipoBoton == DWL_DIRECCION_FLECHA_ARRIBA || TipoBoton == DWL_DIRECCION_FLECHA_IZQUIERDA) {
							C1 = BarraScrollEx_Colores.DegradadoResaltado();
							C2 = BarraScrollEx_Colores.DegradadoInferior();
							CT = BarraScrollEx_Colores.FlechitaResaltada();
							ColorBorde = BarraScrollEx_Colores.BordeFocoRaton();
						}
						else {
							C1 = BarraScrollEx_Colores.DegradadoSuperior();
							C2 = BarraScrollEx_Colores.DegradadoInferior();
							CT = BarraScrollEx_Colores.FlechitaNormal();
							ColorBorde = BarraScrollEx_Colores.BordeNormal();
						}
						break;
					case DWL_Enum_BarraScrollEx_Estado_BotonInferiorResaltado :
						if (TipoBoton == DWL_DIRECCION_FLECHA_ABAJO || TipoBoton == DWL_DIRECCION_FLECHA_DERECHA) {
							C1 = BarraScrollEx_Colores.DegradadoResaltado();
							C2 = BarraScrollEx_Colores.DegradadoInferior();
							CT = BarraScrollEx_Colores.FlechitaResaltada();
							ColorBorde = BarraScrollEx_Colores.BordeFocoRaton();
						}
						else {
							C1 = BarraScrollEx_Colores.DegradadoSuperior();
							C2 = BarraScrollEx_Colores.DegradadoInferior();
							CT = BarraScrollEx_Colores.FlechitaNormal();
							ColorBorde = BarraScrollEx_Colores.BordeNormal();
						}

						break;
					case DWL_Enum_BarraScrollEx_Estado_BotonSuperiorPresionado :
						if (TipoBoton == DWL_DIRECCION_FLECHA_ARRIBA || TipoBoton == DWL_DIRECCION_FLECHA_IZQUIERDA) {
							C1 = BarraScrollEx_Colores.DegradadoInferior();
							C2 = BarraScrollEx_Colores.DegradadoSuperior();
							CT = BarraScrollEx_Colores.FlechitaPresionada();
							BotonPresionado = true;
							ColorBorde = BarraScrollEx_Colores.BordeFocoRaton();
						}
						else {
							C1 = BarraScrollEx_Colores.DegradadoSuperior();
							C2 = BarraScrollEx_Colores.DegradadoInferior();
							CT = BarraScrollEx_Colores.FlechitaNormal();
							ColorBorde = BarraScrollEx_Colores.BordeNormal();
						}
						break;
					case DWL_Enum_BarraScrollEx_Estado_BotonInferiorPresionado :
						if (TipoBoton == DWL_DIRECCION_FLECHA_ABAJO || TipoBoton == DWL_DIRECCION_FLECHA_DERECHA) {
							C1 = BarraScrollEx_Colores.DegradadoInferior();
							C2 = BarraScrollEx_Colores.DegradadoSuperior();
							CT = BarraScrollEx_Colores.FlechitaPresionada();
							BotonPresionado = true;
							ColorBorde = BarraScrollEx_Colores.BordeFocoRaton();
						}
						else {
							C1 = BarraScrollEx_Colores.DegradadoSuperior();
							C2 = BarraScrollEx_Colores.DegradadoInferior();
							CT = BarraScrollEx_Colores.FlechitaNormal();
							ColorBorde = BarraScrollEx_Colores.BordeNormal();
						}
						break;
					default : // Estado Normal
						C1 = BarraScrollEx_Colores.DegradadoSuperior();
						C2 = BarraScrollEx_Colores.DegradadoInferior();
						if (_BarraScrollEx_Activado == true) CT = BarraScrollEx_Colores.FlechitaNormal();
						else								 CT = BarraScrollEx_Colores.FlechitaPresionada();
						ColorBorde = BarraScrollEx_Colores.BordeNormal();
						break;
				}
				DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, C1, C2, true);
				if (BotonPresionado == true) {
					Espacio->left ++;
					Espacio->top ++;
					Espacio->right ++;
					Espacio->bottom ++;
				}
				DWL::GDI::PintarFlecha(hDC, Espacio, CT, TipoBoton);
				if (BotonPresionado == true) {
					Espacio->left --;
					Espacio->top --;
					Espacio->right --;
					Espacio->bottom --;
				}
			}
			_BarraScrollEx_EnmarcarRecta(hDC, Espacio, ColorBorde);
		};


		//! Función virtual que pinta el scroll en cualquier de sus estados.
		/*! Esta funcion virtual que pinta el scroll en cualquier de sus estados.
				\fn			void BarraScrollEx_Evento_Pintar_Scroll(HDC hDC, RECT *Espacio, DWL_Enum_BarraScrollEx_TipoScroll TipoScroll);
				\param[in]	hDC			: hDC donde se pintara el boton.
				\param[in]  Espacio		: Recta que contiene el espacio del boton.
				\param[in]	TipoScroll	: Tipo de scroll.
				\return		No devuelve nada.
				\remarks	Si re-escribes esta función, deberas encargarte de pintar el fondo del control y su borde.
		*/
		void DWLBarraScrollEx_Nucleo::BarraScrollEx_Evento_Pintar_Scroll(HDC hDC, RECT *Espacio, DWL_Enum_BarraScrollEx_TipoScroll TipoScroll) {
		#if defined DWL_BaseControlExScroll_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::BarraScrollEx_Evento_Pintar_Scroll\n"));
		#endif
			COLORREF				C1;
			COLORREF				C2;
			COLORREF				ColorBorde;
			DWL_Enum_BarraScrollEx_Estado EstadoScroll = _BarraScrollEx_EstadoV;
			if (TipoScroll == DWL_Enum_BarraScrollEx_TipoScroll_Horizontal) EstadoScroll = _BarraScrollEx_EstadoH;
			switch (EstadoScroll) {
				case DWL_Enum_BarraScrollEx_Estado_ScrollResaltado :
					C1 = BarraScrollEx_Colores.DegradadoResaltado();
					C2 = BarraScrollEx_Colores.DegradadoInferior();
					ColorBorde = BarraScrollEx_Colores.BordeFocoRaton();
					break;
				case DWL_Enum_BarraScrollEx_Estado_ScrollPresionado :
					C1 = BarraScrollEx_Colores.DegradadoInferior();
					C2 = BarraScrollEx_Colores.DegradadoSuperior();
					ColorBorde = BarraScrollEx_Colores.BordeFocoRaton();
					break;
				default : // Estado normal
					C1 = BarraScrollEx_Colores.DegradadoSuperior();
					C2 = BarraScrollEx_Colores.DegradadoInferior();
					ColorBorde = BarraScrollEx_Colores.BordeNormal();
					break;

			}
			bool Modo = false;
			// Si es mas ancho que alto, cambio el modo a vertical
			if ((Espacio->right - Espacio->left) > (Espacio->bottom - Espacio->top)) Modo = true;
			DWL::GDI::PintarGradient(hDC, Espacio->left, Espacio->top, Espacio->right, Espacio->bottom, C1, C2, Modo);
			_BarraScrollEx_EnmarcarRecta(hDC, Espacio, ColorBorde);
		};

		//! Función que procesa el movimiento del mouse en el scoll.
		/*! Esta función procesa el movimiento del mouse en el scroll.
				\fn			BOOL BarraScrollEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param, const bool TieneBorde);
				\param[in]	hWndControl		: HWND del control que contiene el scroll.
				\param[in]	RectaControl	: Recta con el espacio del scroll.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_Movimiento del control que vaya a contener el scrollex.
							Si solo vas a crear un scroll puedes usar las funcion terminada en V o H, de esta forma ahorraras el tener que procesar los mensajes para la otra barra si no va a existir.
				\sa			BarraScrollEx_Mouse_BotonPresionado(), BarraScrollEx_Mouse_BotonSoltado()
		*/
		BOOL DWLBarraScrollEx_Nucleo::BarraScrollEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param, const bool TieneBorde) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::Evento_Mouse_MovimientoScroll\n"));
			#endif
			if (BarraScrollEx_Mouse_MovimientoV(hWndControl, RectaControl, cX, cY, Param, TieneBorde) == TRUE) return TRUE;
			return BarraScrollEx_Mouse_MovimientoH(hWndControl, RectaControl, cX, cY, Param, TieneBorde);
		}

		//! Función que procesa los botones presionados del mouse en el scoll.
		/*! Esta función procesa los botones presionados del mouse en el scoll.
				\fn			BOOL BarraScrollEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param, const bool TieneBorde);
				\param[in]	hWndControl		: HWND del control que contiene el scoll.
				\param[in]	RectaControl	: Recta con el espacio del scoll.
				\param[in]	Boton			: Boton del mouse presionado.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\param[in]	TieneBorde  	: Parametro en el que debemos especificar si el control tiene borde.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonPresionado del control que vaya a contener el scoll.
							Si solo vas a crear un scroll puedes usar las funcion terminada en V o H, de esta forma ahorraras el tener que procesar los mensajes para la otra barra si no va a existir.
				\sa			BarraScrollEx_Mouse_Movimiento(), BarraScrollEx_Mouse_BotonSoltado()
		*/
		BOOL DWLBarraScrollEx_Nucleo::BarraScrollEx_Mouse_MovimientoV(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param, const bool TieneBorde) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::BarraScrollEx_Evento_Mouse_MovimientoV\n"));
			#endif
			if (_BarraScrollEx_Activado == false) return FALSE;
			if (_BarraScrollEx_VisibleV == FALSE)
				return FALSE;
			if (_BarraScrollEx_VisibleV == DWL_BARRASCROLLEX_AUTOMATICO) {
				if (_BarraScrollEx_MaximoV <= _BarraScrollEx_PaginaV) return FALSE;
			}
			POINT Pt;
			Pt.x = cX;
			Pt.y = cY;
			BOOL PTIR = PtInRect(&_BarraScrollEx_EspacioV, Pt);
			BOOL PTIR2 = FALSE;
			size_t BotonEx = 0;
			for (size_t i = 0; i < _BarraScrollEx_BotonesV.size(); i++) {
				if (_BarraScrollEx_BotonesV[i]->Estado != 2 && _BarraScrollEx_PresionadoV != DWL_Enum_BarraScrollEx_ControlPresionado_Scroll) {
					_BarraScrollEx_BotonesV[i]->Estado = 0;
					if (PtInRect(&_BarraScrollEx_BotonesV[i]->Posicion, Pt) == TRUE) {
						PTIR2 = TRUE;
						BotonEx = i;
						_BarraScrollEx_BotonesV[i]->Estado = 1; // estado resaltado
					}
				}
			}
			if (PTIR == FALSE && PTIR2 == FALSE && _BarraScrollEx_PresionadoV == DWL_Enum_BarraScrollEx_ControlPresionado_Ninguno) {
				_BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_Normal;
				BarraScrollEx_Repintar(hWndControl);
				return FALSE;
			}


			if (PTIR2 == TRUE) {
				_BarraScrollEx_BotonesV[BotonEx]->Estado = 1; // resaltado
				_BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_BotonExtendidoResaltado;
				BarraScrollEx_Repintar(hWndControl, true);
				return TRUE;
			}

			if (PTIR == TRUE || _BarraScrollEx_Capturado == true) {
				switch (_BarraScrollEx_PresionadoV) {
					case DWL_Enum_BarraScrollEx_ControlPresionado_Ninguno : // Nada presionado
						if (PtInRect(&_BarraScrollEx_RectaBotonSuperiorV, Pt) == TRUE)  { _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_BotonSuperiorResaltado; }
						if (PtInRect(&_BarraScrollEx_RectaBotonInferiorV, Pt) == TRUE)  { _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_BotonInferiorResaltado; }
						if (PtInRect(&_BarraScrollEx_RectaScrollV, Pt) == TRUE)         { _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_ScrollResaltado; }
						if (PtInRect(&_BarraScrollEx_RectaFondoSuperiorV, Pt) == TRUE)  { _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_FondoSuperiorResaltado; }
						if (PtInRect(&_BarraScrollEx_RectaFondoInferiorV, Pt) == TRUE)  { _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_FondoInferiorResaltado; }
						break;
					case DWL_Enum_BarraScrollEx_ControlPresionado_FondoSuperior : // Fondo superior presionado
						if (PtInRect(&_BarraScrollEx_RectaFondoSuperiorV, Pt) == FALSE) { _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_Normal;					}
						else									    					{ _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_FondoSuperiorPresionado;	}
						break;
					case DWL_Enum_BarraScrollEx_ControlPresionado_FondoInferior : // Fondo inferior presionado
						if (PtInRect(&_BarraScrollEx_RectaFondoInferiorV, Pt) == FALSE) { _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_Normal;					}
						else									    					{ _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_FondoInferioPresionado;	}
						break;
					case DWL_Enum_BarraScrollEx_ControlPresionado_BotonSuperior : // Boton superior presionado
						if (PtInRect(&_BarraScrollEx_RectaBotonSuperiorV, Pt) == FALSE) { _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_Normal;					}
						else									    					{ _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_BotonSuperiorPresionado;	}
						break;
					case DWL_Enum_BarraScrollEx_ControlPresionado_BotonInferior : // Boton inferior presionado
						if (PtInRect(&_BarraScrollEx_RectaBotonInferiorV, Pt) == FALSE) { _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_Normal;					}
						else															{ _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_BotonInferiorPresionado;	}
						break;
					case DWL_Enum_BarraScrollEx_ControlPresionado_Scroll : { // Scroll presionado .....
						int An = _BarraScrollEx_EspacioV.right - _BarraScrollEx_EspacioV.left;
						int Al = (_BarraScrollEx_EspacioV.bottom - _BarraScrollEx_EspacioV.top) - (18 * _BarraScrollEx_BotonesV.size()) - ANCHO_MINIMO_SCROLL;
						int Borde = 0;
                        if (TieneBorde == true) Borde = 2;
						float	Proporcion	= static_cast<float>((Al - (4 + Borde)) - (An * 2)) / static_cast<float>(_BarraScrollEx_MaximoV);
						int		Desp		= static_cast<int>(static_cast<float>(Pt.y - _BarraScrollEx_PosInicio.y) / Proporcion);
						_BarraScrollEx_ValorV = _BarraScrollEx_PosActualV + Desp;
						if (_BarraScrollEx_ValorV > (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV)) _BarraScrollEx_ValorV = (_BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV);

						if (Pt.y < 0) _BarraScrollEx_ValorV = 0;
						_BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_ScrollPresionado;
						BarraScrollEx_CalcularScrollV(TieneBorde);
						if (_BarraScrollEx_ValorV != _BarraScrollEx_UValorV) {
							_BarraScrollEx_UValorV = _BarraScrollEx_ValorV;
							Repintar(true);	// repinto todo el control
							BarraScrollEx_Evento_Scroll_CambioPos();
							return PTIR;
						}
						break;
					}
				}
			}
			BarraScrollEx_Repintar(hWndControl);
			return PTIR;
		};


		//! Función que procesa el movimiento del mouse en el scoll horizontal.
		/*! Esta función procesa el movimiento del mouse en el scroll horizontal.
				\fn			BOOL BarraScrollEx_Mouse_MovimientoH(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param, const bool TieneBorde);
				\param[in]	hWndControl		: HWND del control que contiene el scroll.
				\param[in]	RectaControl	: Recta con el espacio del scroll.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\param[in]	TieneBorde  	: Parametro en el que debemos especificar si el control tiene borde.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta funcion es especifica solo para el scroll horizontal, si vas a usar ambos scrolls utiliza la funcion BarraScrollEx_Mouse_Movimiento() en ve de esta.
				\sa			BarraScrollEx_Mouse_BotonPresionadoH(), BarraScrollEx_Mouse_BotonSoltadoH()
		*/
		BOOL DWLBarraScrollEx_Nucleo::BarraScrollEx_Mouse_MovimientoH(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param, const bool TieneBorde) {
			#if defined DWL_DWLBarraScrollEx_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::BarraScrollEx_Evento_Mouse_MovimientoH\n"));
			#endif
			if (_BarraScrollEx_Activado == false) return FALSE;
			if (_BarraScrollEx_VisibleH == false)
				return FALSE;
			if (_BarraScrollEx_VisibleH == DWL_BARRASCROLLEX_AUTOMATICO) {
				if (_BarraScrollEx_MaximoH <= _BarraScrollEx_PaginaH) return FALSE;
			}
			POINT Pt;
			Pt.x = cX;
			Pt.y = cY;
			BOOL PTIR = PtInRect(&_BarraScrollEx_EspacioH, Pt);
			BOOL PTIR2 = FALSE;
			size_t BotonEx = 0;
			for (size_t i = 0; i < _BarraScrollEx_BotonesH.size(); i++) {
				if (_BarraScrollEx_BotonesH[i]->Estado != 2 && _BarraScrollEx_PresionadoH != DWL_Enum_BarraScrollEx_ControlPresionado_Scroll) {
					_BarraScrollEx_BotonesH[i]->Estado = 0;
					if (PtInRect(&_BarraScrollEx_BotonesH[i]->Posicion, Pt) == TRUE) {
						PTIR2 = TRUE;
						BotonEx = i;
						_BarraScrollEx_BotonesH[i]->Estado = 1; // estado normal
					}
				}
			}
			if (PTIR == FALSE && PTIR2 == FALSE &&_BarraScrollEx_PresionadoH == DWL_Enum_BarraScrollEx_ControlPresionado_Ninguno) {
				_BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_Normal;
				BarraScrollEx_Repintar(hWndControl);
				return FALSE;
			}

			if (PTIR2 == TRUE) {
				_BarraScrollEx_BotonesH[BotonEx]->Estado = 1; // resaltado
				_BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_BotonExtendidoResaltado;
				BarraScrollEx_Repintar(hWndControl, true);
				return TRUE;
			}

			if (PTIR == TRUE || _BarraScrollEx_Capturado == true) {
				switch (_BarraScrollEx_PresionadoH) {
					case DWL_Enum_BarraScrollEx_ControlPresionado_Ninguno : // Nada presionado
						if (PtInRect(&_BarraScrollEx_RectaBotonIzquierdoH, Pt) == TRUE)  { _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_BotonSuperiorResaltado; }
						if (PtInRect(&_BarraScrollEx_RectaBotonDerechoH, Pt) == TRUE)    { _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_BotonInferiorResaltado; }
						if (PtInRect(&_BarraScrollEx_RectaScrollH, Pt) == TRUE)          { _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_ScrollResaltado; }
						if (PtInRect(&_BarraScrollEx_RectaFondoSuperiorH, Pt) == TRUE)   { _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_FondoSuperiorResaltado; }
						if (PtInRect(&_BarraScrollEx_RectaFondoInferiorH, Pt) == TRUE)   { _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_FondoInferiorResaltado; }
						break;
					case DWL_Enum_BarraScrollEx_ControlPresionado_FondoSuperior : // Fondo superior presionado
						if (PtInRect(&_BarraScrollEx_RectaFondoSuperiorH, Pt) == FALSE) { _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_Normal;					}
						else									    					{ _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_FondoSuperiorPresionado;	}
						break;
					case DWL_Enum_BarraScrollEx_ControlPresionado_FondoInferior : // Fondo inferior presionado
						if (PtInRect(&_BarraScrollEx_RectaFondoInferiorH, Pt) == FALSE) { _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_Normal;					}
						else									    					{ _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_FondoInferioPresionado;	}
						break;
					case DWL_Enum_BarraScrollEx_ControlPresionado_BotonSuperior : // Boton superior presionado
						if (PtInRect(&_BarraScrollEx_RectaBotonIzquierdoH, Pt) == FALSE)	{ _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_Normal;					}
						else									    						{ _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_BotonSuperiorPresionado;	}
						break;
					case DWL_Enum_BarraScrollEx_ControlPresionado_BotonInferior : // Boton inferior presionado
						if (PtInRect(&_BarraScrollEx_RectaBotonDerechoH, Pt) == FALSE)  { _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_Normal;					}
						else															{ _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_BotonInferiorPresionado;  }
						break;
					case DWL_Enum_BarraScrollEx_ControlPresionado_Scroll : { // Scroll presionado .....
						int An = (_BarraScrollEx_EspacioH.right - _BarraScrollEx_EspacioH.left) - (18 * _BarraScrollEx_BotonesH.size()) - ANCHO_MINIMO_SCROLL;
						int Al = _BarraScrollEx_EspacioH.bottom - _BarraScrollEx_EspacioH.top;
                        int Borde = 0;
                        if (TieneBorde == true) Borde = 2;
						float	Proporcion	= static_cast<float>((An - (4 + Borde)) - (Al * 2)) / static_cast<float>(_BarraScrollEx_MaximoH);
						int		Desp		= static_cast<int>(static_cast<float>(Pt.x - _BarraScrollEx_PosInicio.x) / Proporcion);
						_BarraScrollEx_ValorH = _BarraScrollEx_PosActualH + Desp;
						if (_BarraScrollEx_ValorH > (_BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH)) _BarraScrollEx_ValorH = (_BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH);
						if (Pt.x < 0) _BarraScrollEx_ValorH = 0;
						_BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_ScrollPresionado;
						BarraScrollEx_CalcularScrollH(TieneBorde);
						if (_BarraScrollEx_ValorH != _BarraScrollEx_UValorH) {
							_BarraScrollEx_UValorH = _BarraScrollEx_ValorH;
							Repintar(true);		// Repinto todo el control
							BarraScrollEx_Evento_Scroll_CambioPos();
							return PTIR;
						}
						break;
					}
				}
			}

			BarraScrollEx_Repintar(hWndControl);
			return PTIR;
		};



	    //! Función que procesa los botones presionados del mouse en el scoll vertical.
	    /*! Esta función procesa los botones presionados del mouse en el scoll vertical.
			    \fn			BOOL BarraScrollEx_Mouse_BotonPresionadoV(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT wParam);
			    \param[in]	hWndControl		: HWND del control que contiene el scoll.
			    \param[in]	RectaControl	: Recta con el espacio del scoll.
			    \param[in]	Boton			: Boton del mouse presionado.
			    \param[in]	cX				: Coordenada X del mouse relativa al control.
			    \param[in]	cX				: Coordenada Y del mouse relativa al control.
			    \param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
			    \return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
			    \remarks    Esta funcion es especifica solo para el scroll vertical, si vas a usar ambos scrolls utiliza la funcion BarraScrollEx_Mouse_BotonPresionado() en ve de esta.
			    \sa			BarraScrollEx_Mouse_MovimientoV(), BarraScrollEx_Mouse_BotonSoltadoV()
	    */
		BOOL DWLBarraScrollEx_Nucleo::BarraScrollEx_Mouse_BotonPresionadoV(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::BarraScrollEx_Mouse_BotonPresionadoV\n"));
			#endif
			if (_BarraScrollEx_Activado == false) return FALSE;
			if (_BarraScrollEx_VisibleV == false) return FALSE;
			if (_BarraScrollEx_VisibleV == DWL_BARRASCROLLEX_AUTOMATICO) {
				if (_BarraScrollEx_MaximoV <= _BarraScrollEx_PaginaV) return FALSE;
			}
			int nPresionado = DWL_BARRASCROLLEX_OBJETO_NINGUNO;
			_BarraScrollEx_PosInicio.x = cX;
			_BarraScrollEx_PosInicio.y = cY;
			bool RepintarControl = false;

			for (size_t i = 0; i < _BarraScrollEx_BotonesV.size(); i++) {
				if (PtInRect(&_BarraScrollEx_BotonesV[i]->Posicion, _BarraScrollEx_PosInicio) == TRUE) {
					_BarraScrollEx_PresionadoV = DWL_Enum_BarraScrollEx_ControlPresionado_BotonExtendido;
					_BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_BotonExtendidoPresionado;
					_BarraScrollEx_BotonesV[i]->Estado = 2; // presionado
					RepintarControl = true;
					nPresionado = DWL_BARRASCROLLEX_OBJETO_BOTON_EXTENDIDO;
                    break;
				}
			}


			if (PtInRect(&_BarraScrollEx_RectaFondoSuperiorV, _BarraScrollEx_PosInicio) == TRUE) {
				_BarraScrollEx_PresionadoV = DWL_Enum_BarraScrollEx_ControlPresionado_FondoSuperior;
				_BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_FondoSuperiorPresionado;
				SetTimer(hWndControl, 10002, 35, NULL);
				RepintarControl = true;
				nPresionado = DWL_BARRASCROLLEX_OBJETO_FONDO_SUPERIOR;
			}

			if (PtInRect(&_BarraScrollEx_RectaFondoInferiorV, _BarraScrollEx_PosInicio) == TRUE) {
				_BarraScrollEx_PresionadoV = DWL_Enum_BarraScrollEx_ControlPresionado_FondoInferior;
				_BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_FondoInferioPresionado;
				SetTimer(hWndControl, 10003, 35, NULL);
				RepintarControl = true;
				nPresionado = DWL_BARRASCROLLEX_OBJETO_FONDO_INFERIOR;
			}

			if (PtInRect(&_BarraScrollEx_RectaBotonSuperiorV, _BarraScrollEx_PosInicio) == TRUE) {
				_BarraScrollEx_PresionadoV = DWL_Enum_BarraScrollEx_ControlPresionado_BotonSuperior;
				_BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_BotonSuperiorPresionado;
				SetTimer(hWndControl, 10000, 35, NULL);
				RepintarControl = true;
				nPresionado = DWL_BARRASCROLLEX_OBJETO_BOTON_SUPERIOR;
			}

			if (PtInRect(&_BarraScrollEx_RectaBotonInferiorV, _BarraScrollEx_PosInicio) == TRUE) {
				_BarraScrollEx_PresionadoV = DWL_Enum_BarraScrollEx_ControlPresionado_BotonInferior;
				_BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_BotonInferiorPresionado;
				SetTimer(hWndControl, 10001, 35, NULL);
				RepintarControl = true;
				nPresionado = DWL_BARRASCROLLEX_OBJETO_BOTON_INFERIOR;
//				DWL::DWLDebug::ImprimirDebug(TEXT("TimerON\n"));
			}

			if (PtInRect(&_BarraScrollEx_RectaScrollV, _BarraScrollEx_PosInicio) == TRUE) {
				_BarraScrollEx_PresionadoV = DWL_Enum_BarraScrollEx_ControlPresionado_Scroll;
				_BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_ScrollPresionado;
				RepintarControl = true;
				nPresionado = DWL_BARRASCROLLEX_OBJETO_SCROLL;
			}

			if (RepintarControl == true) {
				SetCapture(hWndControl);
				_BarraScrollEx_Capturado = true;
				BarraScrollEx_Repintar(hWndControl, true);
			}


			return PtInRect(&_BarraScrollEx_EspacioV, _BarraScrollEx_PosInicio);
		};



		//! Función que procesa los botones presionados del mouse en el scoll horizontal.
		/*! Esta función procesa los botones presionados del mouse en el scoll horizontal.
				\fn			BOOL BarraScrollEx_Mouse_BotonPresionadoH(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT wParam);
				\param[in]	hWndControl		: HWND del control que contiene el scoll.
				\param[in]	RectaControl	: Recta con el espacio del scoll.
				\param[in]	Boton			: Boton del mouse presionado.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta funcion es especifica solo para el scroll horizontal, si vas a usar ambos scrolls utiliza la funcion BarraScrollEx_Mouse_BotonPresionado() en ve de esta.
				\sa			BarraScrollEx_Mouse_MovimientoH(), BarraScrollEx_Mouse_BotonSoltadoH()
		*/
		BOOL DWLBarraScrollEx_Nucleo::BarraScrollEx_Mouse_BotonPresionadoH(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::BarraScrollEx_Mouse_BotonPresionadoH\n"));
			#endif
			if (_BarraScrollEx_Activado == false) return FALSE;
			if (_BarraScrollEx_VisibleH == false) return FALSE;
			if (_BarraScrollEx_VisibleH == DWL_BARRASCROLLEX_AUTOMATICO) {
				if (_BarraScrollEx_MaximoH <= _BarraScrollEx_PaginaH) return FALSE;
			}
			int nPresionado = DWL_BARRASCROLLEX_OBJETO_NINGUNO;
			_BarraScrollEx_PosInicio.x = cX;
			_BarraScrollEx_PosInicio.y = cY;
			bool RepintarControl = false;

//			if (_BarraScrollEx_PresionadoH != Control_Ninguno) return TRUE;

			for (size_t i = 0; i < _BarraScrollEx_BotonesH.size(); i++) {
				if (PtInRect(&_BarraScrollEx_BotonesH[i]->Posicion, _BarraScrollEx_PosInicio) == TRUE) {
					_BarraScrollEx_PresionadoH = DWL_Enum_BarraScrollEx_ControlPresionado_BotonExtendido;
					_BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_BotonExtendidoPresionado;
					_BarraScrollEx_BotonesH[i]->Estado = 2; // presionado
					RepintarControl = true;
					nPresionado = DWL_BARRASCROLLEX_OBJETO_BOTON_EXTENDIDO;
				}
			}

			if (PtInRect(&_BarraScrollEx_RectaFondoSuperiorH, _BarraScrollEx_PosInicio) == TRUE) {
				_BarraScrollEx_PresionadoH = DWL_Enum_BarraScrollEx_ControlPresionado_FondoSuperior;
				_BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_FondoSuperiorPresionado;
				SetTimer(hWndControl, 10012, 35, NULL);
				RepintarControl = true;
				nPresionado = DWL_BARRASCROLLEX_OBJETO_FONDO_SUPERIOR;
			}

			if (PtInRect(&_BarraScrollEx_RectaFondoInferiorH, _BarraScrollEx_PosInicio) == TRUE) {
				_BarraScrollEx_PresionadoH = DWL_Enum_BarraScrollEx_ControlPresionado_FondoInferior;
				_BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_FondoInferioPresionado;
				SetTimer(hWndControl, 10013, 35, NULL);
				RepintarControl = true;
				nPresionado = DWL_BARRASCROLLEX_OBJETO_FONDO_INFERIOR;
			}

			if (PtInRect(&_BarraScrollEx_RectaBotonIzquierdoH, _BarraScrollEx_PosInicio) == TRUE) {
				_BarraScrollEx_PresionadoH = DWL_Enum_BarraScrollEx_ControlPresionado_BotonSuperior;
				_BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_BotonSuperiorPresionado;
				SetTimer(hWndControl, 10010, 35, NULL);
				RepintarControl = true;
				nPresionado = DWL_BARRASCROLLEX_OBJETO_BOTON_SUPERIOR;
			}

			if (PtInRect(&_BarraScrollEx_RectaBotonDerechoH, _BarraScrollEx_PosInicio) == TRUE) {
				_BarraScrollEx_PresionadoH = DWL_Enum_BarraScrollEx_ControlPresionado_BotonInferior;
				_BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_BotonInferiorPresionado;
				SetTimer(hWndControl, 10011, 35, NULL);
				RepintarControl = true;
				nPresionado = DWL_BARRASCROLLEX_OBJETO_BOTON_INFERIOR;
			}

			if (PtInRect(&_BarraScrollEx_RectaScrollH, _BarraScrollEx_PosInicio) == TRUE) {
				_BarraScrollEx_PresionadoH = DWL_Enum_BarraScrollEx_ControlPresionado_Scroll;
				_BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_ScrollPresionado;
				RepintarControl = true;
				nPresionado = DWL_BARRASCROLLEX_OBJETO_SCROLL;
			}

			if (RepintarControl == true) {
				SetCapture(hWndControl);
				_BarraScrollEx_Capturado = true;
				BarraScrollEx_Repintar(hWndControl, true);
			}

			return PtInRect(&_BarraScrollEx_EspacioH, _BarraScrollEx_PosInicio);
		};


		//! Función que debe ser usada cuando el control reciba un mensaje WM_TIMER.
		/*!	Esta función debe ser usada cuando el control reciba un mensaje WM_TIMER.
				\fn			virtual void BarraScrollEx_Evento_Temporizador(HWND hWndControl, const UINT cID, const bool TieneBorde);
				\param[in]	hWndControl : HWND de la ventana que contiene el scrollbar.
				\param[in]	cID			: ID del temporizador.
                \param[in]  TieneBorde  : Parametro en el que debemos especificar si el control tiene borde.
				\return		No devuelve nada.
				\remarks	Si no se llama a esta funcion cuando se recibe un mensaje WM_TIMER, no funcionaran las pulsaciones sobre los fondos y botones del scroll.
		*/
		void DWLBarraScrollEx_Nucleo::BarraScrollEx_Evento_Temporizador(HWND hWndControl, const UINT cID, const bool TieneBorde) {
		#if defined DWL_BaseControlExScroll_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::Evento_Temporizador(cID %d)\n"), cID);
		#endif
			int Calculo = 0;
			switch (cID) {
				case 10000 : // Boton Superior
					if (_BarraScrollEx_EstadoV == DWL_Enum_BarraScrollEx_Estado_BotonSuperiorPresionado) {
						if (_BarraScrollEx_ValorV != 0) {
							_BarraScrollEx_ValorV --;
							BarraScrollEx_CalcularScrollV(TieneBorde);
							BarraScrollEx_Repintar(hWndControl, true);
							Repintar(true);
							BarraScrollEx_Evento_Scroll_CambioPos();
						}
					}
					break;
				case 10001 : // Boton Inferior
					if (_BarraScrollEx_EstadoV == DWL_Enum_BarraScrollEx_Estado_BotonInferiorPresionado) {
						if (_BarraScrollEx_ValorV < _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) {
							_BarraScrollEx_ValorV ++;
							BarraScrollEx_CalcularScrollV(TieneBorde);
							BarraScrollEx_Repintar(hWndControl, true);
							Repintar(true);
							BarraScrollEx_Evento_Scroll_CambioPos();
						}
					}
					break;
				case 10002 : // Fondo Superior
					if (_BarraScrollEx_EstadoV == DWL_Enum_BarraScrollEx_Estado_FondoSuperiorPresionado) {
						if (PtInRect(&_BarraScrollEx_RectaFondoSuperiorV, _BarraScrollEx_PosInicio) == TRUE && _BarraScrollEx_ValorV != 0) {
							_BarraScrollEx_ValorV -= _BarraScrollEx_PaginaV;
							if (_BarraScrollEx_ValorV < 0) _BarraScrollEx_ValorV = 0;
							BarraScrollEx_CalcularScrollV(TieneBorde);
							BarraScrollEx_Repintar(hWndControl, true);
							Repintar(true);
							BarraScrollEx_Evento_Scroll_CambioPos();
						}
					}
					break;
				case 10003 : // Fondo Inferior
					if (_BarraScrollEx_EstadoV == DWL_Enum_BarraScrollEx_Estado_FondoInferioPresionado) {
						if (PtInRect(&_BarraScrollEx_RectaFondoInferiorV, _BarraScrollEx_PosInicio) == TRUE && _BarraScrollEx_ValorV != _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) {
							_BarraScrollEx_ValorV += _BarraScrollEx_PaginaV;
							if (_BarraScrollEx_ValorV > _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV) _BarraScrollEx_ValorV = _BarraScrollEx_MaximoV - _BarraScrollEx_PaginaV;
							BarraScrollEx_CalcularScrollV(TieneBorde);
							BarraScrollEx_Repintar(hWndControl, true);
							Repintar(true);
							BarraScrollEx_Evento_Scroll_CambioPos();
						}
					}
					break;
				case 10010 : // Boton Izquierdo
					if (_BarraScrollEx_EstadoH == DWL_Enum_BarraScrollEx_Estado_BotonSuperiorPresionado) {
						if (_BarraScrollEx_ValorH != 0) {
							_BarraScrollEx_ValorH --;
							BarraScrollEx_CalcularScrollH(TieneBorde);
							BarraScrollEx_Repintar(hWndControl, true);
							Repintar(true);
							BarraScrollEx_Evento_Scroll_CambioPos();
						}
					}
					break;
				case 10011 : // Boton Derecho
					if (_BarraScrollEx_EstadoH == DWL_Enum_BarraScrollEx_Estado_BotonInferiorPresionado) {
						if (_BarraScrollEx_ValorH != _BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH) {
							_BarraScrollEx_ValorH ++;
							if (_BarraScrollEx_ValorH > _BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH) _BarraScrollEx_ValorH = _BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH;
							BarraScrollEx_CalcularScrollH(TieneBorde);
							BarraScrollEx_Repintar(hWndControl, true);
							Repintar(true);
							BarraScrollEx_Evento_Scroll_CambioPos();
						}
					}
					break;
				case 10012 : // Fondo Izquierdo
					if (_BarraScrollEx_EstadoH == DWL_Enum_BarraScrollEx_Estado_FondoSuperiorPresionado) {
						if (PtInRect(&_BarraScrollEx_RectaFondoSuperiorH, _BarraScrollEx_PosInicio) == TRUE && _BarraScrollEx_ValorH != 0) {
							_BarraScrollEx_ValorH -= _BarraScrollEx_PaginaH;
							if (_BarraScrollEx_ValorH < 0) _BarraScrollEx_ValorH = 0;
							BarraScrollEx_CalcularScrollH(TieneBorde);
							BarraScrollEx_Repintar(hWndControl, true);
							Repintar(true);
							BarraScrollEx_Evento_Scroll_CambioPos();
						}
					}
					break;
				case 10013 : // Fondo Derecho
					if (_BarraScrollEx_EstadoH == DWL_Enum_BarraScrollEx_Estado_FondoInferioPresionado) {
						if (PtInRect(&_BarraScrollEx_RectaFondoInferiorH, _BarraScrollEx_PosInicio) == TRUE && _BarraScrollEx_ValorH != _BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH) {
							_BarraScrollEx_ValorH += _BarraScrollEx_PaginaH;
							if (_BarraScrollEx_ValorH > _BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH) _BarraScrollEx_ValorH = _BarraScrollEx_MaximoH - _BarraScrollEx_PaginaH;
							BarraScrollEx_CalcularScrollH(TieneBorde);
							BarraScrollEx_Repintar(hWndControl, true);
							Repintar(true);
							BarraScrollEx_Evento_Scroll_CambioPos();
						}
					}
					break;
			}
		}


		//! Función que procesa los botones presionados del mouse en el scoll.
		/*! Esta función procesa los botones presionados del mouse en el scoll.
				\fn			BOOL BarraScrollEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	hWndControl		: HWND del control que contiene el scoll.
				\param[in]	RectaControl	: Recta con el espacio del scoll.
				\param[in]	Boton			: Boton del mouse presionado.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonPresionado del control que vaya a contener el scoll.
							Si solo vas a crear un scroll puedes usar las funcion terminada en V o H, de esta forma ahorraras el tener que procesar los mensajes para la otra barra si no va a existir.
				\sa			BarraScrollEx_Mouse_Movimiento(), BarraScrollEx_Mouse_BotonSoltado()
		*/
		BOOL DWLBarraScrollEx_Nucleo::BarraScrollEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::Evento_Mouse_BotonPresionadoScroll\n"));
			#endif
			if (BarraScrollEx_Mouse_BotonPresionadoV(hWndControl, RectaControl, Boton, cX, cY, Param) == TRUE) return TRUE;
			return BarraScrollEx_Mouse_BotonPresionadoH(hWndControl, RectaControl, Boton, cX, cY, Param);
		}


		//! Función que procesa los botones soltados del mouse en el scroll
		/*! Esta función procesa los botones soltados del mouse en el scroll.
				\fn			BOOL BarraScrollEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT wParam);
				\param[in]	hWndControl		: HWND del control que contiene el scroll.
				\param[in]	RectaControl	: Recta con el espacio del scroll.
				\param[in]	Boton			: Boton del mouse presionado.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonSoltado del control que vaya a contener el ArbolEx.
							Si solo vas a crear un scroll puedes usar las funcion terminada en V o H, de esta forma ahorraras el tener que procesar los mensajes para la otra barra si no va a existir.
				\sa			BarraScrollEx_Mouse_Movimiento(), BarraScrollEx_Mouse_BotonPresionado()
		*/
		BOOL DWLBarraScrollEx_Nucleo::BarraScrollEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::Evento_Mouse_BotonSoltadoScroll\n"));
			#endif
			if (BarraScrollEx_Mouse_BotonSoltadoV(hWndControl, RectaControl,  Boton, cX, cY, Param) == TRUE) return TRUE;
			return BarraScrollEx_Mouse_BotonSoltadoH(hWndControl, RectaControl, Boton, cX, cY, Param);
		}


		//! Función que procesa los botones soltados del mouse en el scroll vertical.
		/*! Esta función procesa los botones soltados del mouse en el scroll vertical.
				\fn			BOOL BarraScrollEx_Mouse_BotonSoltadoV(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	hWndControl		: HWND del control que contiene el scroll.
				\param[in]	RectaControl	: Recta con el espacio del scroll.
				\param[in]	Boton			: Boton del mouse presionado.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
                \param[in]	TieneBorde  	: Parametro en el que debemos especificar si el control tiene borde.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta funcion es especifica solo para el scroll vertical, si vas a usar ambos scrolls utiliza la funcion BarraScrollEx_Mouse_BotonSoltado() en ve de esta.
				\sa			BarraScrollEx_Mouse_MovimientoV(), BarraScrollEx_Mouse_BotonPresionadoV()
		*/
		BOOL DWLBarraScrollEx_Nucleo::BarraScrollEx_Mouse_BotonSoltadoV(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::BarraScrollEx_Mouse_BotonSoltadoV\n"));
			#endif
			if (_BarraScrollEx_Activado == false) return FALSE;
			if (_BarraScrollEx_VisibleV == false) return FALSE;
			if (_BarraScrollEx_VisibleV == DWL_BARRASCROLLEX_AUTOMATICO) {
				if (_BarraScrollEx_MaximoV <= _BarraScrollEx_PaginaV) return FALSE;
			}

			ReleaseCapture();
			_BarraScrollEx_Capturado = false;

			bool RepintarControl = false;
			int nPresionado = DWL_BARRASCROLLEX_OBJETO_NINGUNO;
			POINT Pt;
			Pt.x = cX;
			Pt.y = cY;
			int BotonEx = -1;
			_BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_Normal;
			KillTimer(hWndControl, 10000);
			KillTimer(hWndControl, 10001);
			KillTimer(hWndControl, 10002);
			KillTimer(hWndControl, 10003);
			switch (_BarraScrollEx_PresionadoV) {
				case DWL_Enum_BarraScrollEx_ControlPresionado_BotonSuperior : // Boton superior soltado
					if (PtInRect(&_BarraScrollEx_RectaBotonSuperiorV, Pt) == TRUE) _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_BotonSuperiorResaltado;
					_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;
					RepintarControl = true;
					nPresionado = DWL_BARRASCROLLEX_OBJETO_BOTON_SUPERIOR;
					break;
				case DWL_Enum_BarraScrollEx_ControlPresionado_BotonInferior : // Boton inferior soltado
					if (PtInRect(&_BarraScrollEx_RectaBotonInferiorV, Pt) == TRUE) _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_BotonInferiorResaltado;
					_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;
					RepintarControl = true;
					nPresionado = DWL_BARRASCROLLEX_OBJETO_BOTON_INFERIOR;
					break;
				case DWL_Enum_BarraScrollEx_ControlPresionado_Scroll : // Scroll soltado
					if (PtInRect(&_BarraScrollEx_RectaScrollV, Pt) == TRUE)		_BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_ScrollResaltado;
					RepintarControl = true;
					_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;
					nPresionado = DWL_BARRASCROLLEX_OBJETO_SCROLL;
					break;
				case DWL_Enum_BarraScrollEx_ControlPresionado_FondoSuperior : // Fondo superior presionado
					if (PtInRect(&_BarraScrollEx_RectaFondoSuperiorV, Pt) == TRUE) _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_FondoSuperiorResaltado;
					_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;
					RepintarControl = true;
					nPresionado = DWL_BARRASCROLLEX_OBJETO_FONDO_SUPERIOR;
					break;
				case DWL_Enum_BarraScrollEx_ControlPresionado_FondoInferior : // Fondo inferior presionado
					if (PtInRect(&_BarraScrollEx_RectaFondoInferiorV, Pt) == TRUE) _BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_FondoInferiorResaltado;
					_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;
					RepintarControl = true;
					nPresionado = DWL_BARRASCROLLEX_OBJETO_FONDO_INFERIOR;
					break;
				case DWL_Enum_BarraScrollEx_ControlPresionado_BotonExtendido :
					for (size_t i = 0; i < _BarraScrollEx_BotonesV.size(); i++) {
						if (PtInRect(&_BarraScrollEx_BotonesV[i]->Posicion, Pt) == TRUE) {
							BotonEx = i;
							_BarraScrollEx_BotonesV[i]->Estado = 1; // resaltado
							RepintarControl = true;
							nPresionado = DWL_BARRASCROLLEX_OBJETO_BOTON_EXTENDIDO;
//							break;
						}
						else {
							_BarraScrollEx_BotonesV[i]->Estado = 0; // normal
						}
					}
					break;
			}
			if (RepintarControl == true) {
				//BarraScrollEx_Repintar(hWndControl, true);
				Repintar(true);
			}

			_BarraScrollEx_PresionadoV = DWL_Enum_BarraScrollEx_ControlPresionado_Ninguno;

			if (nPresionado == DWL_BARRASCROLLEX_OBJETO_BOTON_EXTENDIDO) {
				BarraScrollEx_Evento_BotonExtendido_Click(_BarraScrollEx_BotonesV[BotonEx]);
   				PostMessage(GetParent(hWndControl), DWL_BARRASCROLLEX_BOTONEX_CLICK, static_cast<WPARAM>(_BarraScrollEx_BotonesV[BotonEx]->IDControl), static_cast<LPARAM>(Boton));
			}


			return PtInRect(&_BarraScrollEx_EspacioV, Pt);
		};



		//! Función que procesa los botones soltados del mouse en el scroll horizontal.
		/*! Esta función procesa los botones soltados del mouse en el scroll horizontal.
				\fn			BOOL BarraScrollEx_Mouse_BotonSoltadoH(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT wParam);
				\param[in]	hWndControl		: HWND del control que contiene el scroll.
				\param[in]	RectaControl	: Recta con el espacio del scroll.
				\param[in]	Boton			: Boton del mouse presionado.
				\param[in]	cX				: Coordenada X del mouse relativa al control.
				\param[in]	cX				: Coordenada Y del mouse relativa al control.
				\param[in]	Param			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
				\return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
				\remarks    Esta funcion es especifica solo para el scroll horizontal, si vas a usar ambos scrolls utiliza la funcion BarraScrollEx_Mouse_BotonSoltado() en ve de esta.
				\sa			BarraScrollEx_Mouse_MovimientoH(), BarraScrollEx_Mouse_BotonPresionadoH()
		*/
		BOOL DWLBarraScrollEx_Nucleo::BarraScrollEx_Mouse_BotonSoltadoH(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::BarraScrollEx_Evento_Mouse_BotonSoltadoH\n"));
			#endif
			if (_BarraScrollEx_Activado == false) return FALSE;
			if (_BarraScrollEx_VisibleH == false) return FALSE;
			if (_BarraScrollEx_VisibleH == DWL_BARRASCROLLEX_AUTOMATICO) {
				if (_BarraScrollEx_MaximoH <= _BarraScrollEx_PaginaH) return FALSE;
			}

			ReleaseCapture();
			_BarraScrollEx_Capturado = false;

			bool RepintarControl = false;
			POINT Pt;
			Pt.x = cX;
			Pt.y = cY;
			int BotonEx = -1;
			_BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_Normal;
			KillTimer(hWndControl, 10010);
			KillTimer(hWndControl, 10011);
			KillTimer(hWndControl, 10012);
			KillTimer(hWndControl, 10013);
			int nPresionado = DWL_BARRASCROLLEX_OBJETO_NINGUNO;
			switch (_BarraScrollEx_PresionadoH) {
				case DWL_Enum_BarraScrollEx_ControlPresionado_BotonSuperior : // Boton superior soltado
					if (PtInRect(&_BarraScrollEx_RectaBotonIzquierdoH, Pt) == TRUE) _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_BotonSuperiorResaltado;
					_BarraScrollEx_PosActualH = _BarraScrollEx_ValorH;
					RepintarControl = true;
					nPresionado = DWL_BARRASCROLLEX_OBJETO_BOTON_SUPERIOR;
					break;
				case DWL_Enum_BarraScrollEx_ControlPresionado_BotonInferior : // Boton inferior soltado
					if (PtInRect(&_BarraScrollEx_RectaBotonDerechoH, Pt) == TRUE) _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_BotonInferiorResaltado;
					_BarraScrollEx_PosActualH = _BarraScrollEx_ValorH;
					RepintarControl = true;
					nPresionado = DWL_BARRASCROLLEX_OBJETO_BOTON_INFERIOR;
					break;
				case DWL_Enum_BarraScrollEx_ControlPresionado_Scroll : // Scroll soltado
					if (PtInRect(&_BarraScrollEx_RectaScrollH, Pt) == TRUE)		_BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_ScrollResaltado;
					RepintarControl = true;
					_BarraScrollEx_PosActualH = _BarraScrollEx_ValorH;
					nPresionado = DWL_BARRASCROLLEX_OBJETO_SCROLL;
					break;
				case DWL_Enum_BarraScrollEx_ControlPresionado_FondoSuperior : // Fondo superior presionado
					if (PtInRect(&_BarraScrollEx_RectaFondoSuperiorH, Pt) == TRUE) _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_FondoSuperiorResaltado;
					_BarraScrollEx_PosActualH = _BarraScrollEx_ValorH;
					RepintarControl = true;
					nPresionado = DWL_BARRASCROLLEX_OBJETO_FONDO_SUPERIOR;
					break;
				case DWL_Enum_BarraScrollEx_ControlPresionado_FondoInferior : // Fondo inferior presionado
					if (PtInRect(&_BarraScrollEx_RectaFondoInferiorH, Pt) == TRUE) _BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_FondoInferiorResaltado;
					_BarraScrollEx_PosActualH = _BarraScrollEx_ValorH;
					RepintarControl = true;
					nPresionado = DWL_BARRASCROLLEX_OBJETO_FONDO_INFERIOR;
					break;
				case DWL_Enum_BarraScrollEx_ControlPresionado_BotonExtendido :
					for (size_t i = 0; i < _BarraScrollEx_BotonesH.size(); i++) {
						if (PtInRect(&_BarraScrollEx_BotonesH[i]->Posicion, Pt) == TRUE) {
							BotonEx = i;
							_BarraScrollEx_BotonesH[i]->Estado = 1; // resaltado
							RepintarControl = true;
							nPresionado = DWL_BARRASCROLLEX_OBJETO_BOTON_EXTENDIDO;
//							break;
						}
						else {
							_BarraScrollEx_BotonesH[i]->Estado = 0; // normal
						}
					}
					break;
			}
			if (RepintarControl == true) {
				Repintar(true);
			}
			_BarraScrollEx_PresionadoH = DWL_Enum_BarraScrollEx_ControlPresionado_Ninguno;

			if (nPresionado == DWL_BARRASCROLLEX_OBJETO_BOTON_EXTENDIDO) {
				BarraScrollEx_Evento_BotonExtendido_Click(_BarraScrollEx_BotonesH[BotonEx]);
   				PostMessage(GetParent(hWndControl), DWL_BARRASCROLLEX_BOTONEX_CLICK, static_cast<WPARAM>(_BarraScrollEx_BotonesH[BotonEx]->IDControl), static_cast<LPARAM>(Boton));
			}

			return PtInRect(&_BarraScrollEx_EspacioH, Pt);
		};


		void DWLBarraScrollEx_Nucleo::BarraScrollEx_Mouse_Saliendo(HWND hWndControl) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::Evento_Mouse_Saliendo\n"));
			#endif
			if (_BarraScrollEx_PresionadoH == DWL_Enum_BarraScrollEx_ControlPresionado_Ninguno && _BarraScrollEx_PresionadoV == DWL_Enum_BarraScrollEx_ControlPresionado_Ninguno) {
				_BarraScrollEx_EstadoV = DWL_Enum_BarraScrollEx_Estado_Normal;
				_BarraScrollEx_EstadoH = DWL_Enum_BarraScrollEx_Estado_Normal;
				size_t i = 0;
				for (i = 0; i < _BarraScrollEx_BotonesV.size(); i++)  _BarraScrollEx_BotonesV[i]->Estado = 0;
				for (i = 0; i < _BarraScrollEx_BotonesH.size(); i++)  _BarraScrollEx_BotonesH[i]->Estado = 0;

				BarraScrollEx_Repintar(hWndControl, true);
				Repintar(false);
			}
		};



	    //! Función virtual destinada a pintar el fondo del scroll.
	    /*!	Esta función se encarga de pintar el fondo del scroll.
			    \fn			virtual void BarraScrollEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio, DWL_Enum_BarraScrollEx_TipoScroll TipoScroll);
			    \param[in]	hDC			: HDC del control donde se pintara el scroll.
			    \param[in]	Espacio		: Recta con el espacio del fondo del scroll.
			    \param[in]	TipoScroll	: Tipo de scroll.
			    \return		No devuelve nada.
	    */
		void DWLBarraScrollEx_Nucleo::BarraScrollEx_Evento_Pintar_Fondo(HDC hDC, RECT *Espacio, DWL_Enum_BarraScrollEx_TipoScroll TipoScroll) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::BarraScrollEx_Evento_Pintar_Fondo\n"));
			#endif
			HBRUSH Brocha = NULL;
			DWL_Enum_BarraScrollEx_Estado EstadoScroll = _BarraScrollEx_EstadoV;

			if (TipoScroll == DWL_Enum_BarraScrollEx_TipoScroll_HorizontalDerecho || TipoScroll == DWL_Enum_BarraScrollEx_TipoScroll_HorizontalIzquierdo) EstadoScroll = _BarraScrollEx_EstadoH;

			switch (EstadoScroll) {
				case DWL_Enum_BarraScrollEx_Estado_FondoSuperiorResaltado :
					if (TipoScroll == DWL_Enum_BarraScrollEx_TipoScroll_HorizontalDerecho || TipoScroll == DWL_Enum_BarraScrollEx_TipoScroll_VerticalSuperior)   Brocha = CreateSolidBrush(BarraScrollEx_Colores.FondoResaltado());
					break;
				case DWL_Enum_BarraScrollEx_Estado_FondoInferiorResaltado :
					if (TipoScroll == DWL_Enum_BarraScrollEx_TipoScroll_HorizontalIzquierdo || TipoScroll == DWL_Enum_BarraScrollEx_TipoScroll_VerticalInferior) Brocha = CreateSolidBrush(BarraScrollEx_Colores.FondoResaltado());
					break;
				case DWL_Enum_BarraScrollEx_Estado_FondoSuperiorPresionado :
					if (TipoScroll == DWL_Enum_BarraScrollEx_TipoScroll_HorizontalDerecho || TipoScroll == DWL_Enum_BarraScrollEx_TipoScroll_VerticalSuperior)   Brocha = CreateSolidBrush(BarraScrollEx_Colores.FondoPresionado());
					break;
				case DWL_Enum_BarraScrollEx_Estado_FondoInferioPresionado :
					if (TipoScroll == DWL_Enum_BarraScrollEx_TipoScroll_HorizontalIzquierdo || TipoScroll == DWL_Enum_BarraScrollEx_TipoScroll_VerticalInferior) Brocha = CreateSolidBrush(BarraScrollEx_Colores.FondoPresionado());
					break;
			}
			if (Brocha == NULL) { // Estado Normal
				Brocha = CreateSolidBrush(BarraScrollEx_Colores.FondoNormal());
			}

			FillRect(hDC, Espacio, Brocha);
			DeleteObject(Brocha);
		};




		//! Función para calcular los tamaños del scroll vertical.
		/*!	Esta función calcula todos los tamaños de los controles que se usan en el scroll vertical, incluyendo botones extendidos.
				\fn			void BarraScrollEx_CalcularScrollV(const bool TieneBorde);
                \param[in]  TieneBorde : Parametro en el que debemos especificar si el control tiene borde
				\return		No devuelve nada.
				\remarks	Función de uso interno.
		*/
		void DWLBarraScrollEx_Nucleo::BarraScrollEx_CalcularScrollV(const bool TieneBorde) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::BarraScrollEx_CalcularScrollV\n"));
			#endif

            int Borde = 0;
            if (TieneBorde == true) Borde = 2;

			if (_BarraScrollEx_ValorV < 0) _BarraScrollEx_ValorV = 0;

			int An = _BarraScrollEx_EspacioV.right - _BarraScrollEx_EspacioV.left;
			int Al = _BarraScrollEx_EspacioV.bottom - _BarraScrollEx_EspacioV.top;

			for (size_t i = 0; i < _BarraScrollEx_BotonesV.size(); i++) {
				Al -= 17;
				_BarraScrollEx_BotonesV[i]->Posicion.left	= _BarraScrollEx_EspacioV.left;
				_BarraScrollEx_BotonesV[i]->Posicion.top	= Al + 1;
				_BarraScrollEx_BotonesV[i]->Posicion.right	= _BarraScrollEx_EspacioV.left + An;
				_BarraScrollEx_BotonesV[i]->Posicion.bottom	= Al + 17;
			}

			float Proporcion = static_cast<float>((Al - (4 + Borde)) - (An * 2)) / static_cast<float>(_BarraScrollEx_MaximoV);
			_BarraScrollEx_RectaBotonSuperiorV.left		= _BarraScrollEx_EspacioV.left;
			_BarraScrollEx_RectaBotonSuperiorV.top		= _BarraScrollEx_EspacioV.top;
			_BarraScrollEx_RectaBotonSuperiorV.bottom	= _BarraScrollEx_EspacioV.top + An;
			_BarraScrollEx_RectaBotonSuperiorV.right	= _BarraScrollEx_EspacioV.left + An;


			_BarraScrollEx_RectaBotonInferiorV.left		= _BarraScrollEx_EspacioV.left;
//			_BarraScrollEx_RectaBotonInferiorV.top		= _BarraScrollEx_EspacioV.bottom - 16;
			_BarraScrollEx_RectaBotonInferiorV.top		= Al - 16;
			_BarraScrollEx_RectaBotonInferiorV.right	= _BarraScrollEx_EspacioV.right;
//			_BarraScrollEx_RectaBotonInferiorV.bottom	= _BarraScrollEx_EspacioV.bottom;
			_BarraScrollEx_RectaBotonInferiorV.bottom	= Al;


			if (_BarraScrollEx_PaginaV > _BarraScrollEx_MaximoV) {
				_BarraScrollEx_RectaScrollV.left	= _BarraScrollEx_EspacioV.left;
				_BarraScrollEx_RectaScrollV.right	= _BarraScrollEx_EspacioV.right;
				_BarraScrollEx_RectaScrollV.top		= _BarraScrollEx_EspacioV.top + An + 1;
				_BarraScrollEx_RectaScrollV.bottom	= Al - An;
			}
			else {
				_BarraScrollEx_RectaScrollV.left	= _BarraScrollEx_EspacioV.left;
				_BarraScrollEx_RectaScrollV.right	= _BarraScrollEx_EspacioV.right;
				_BarraScrollEx_RectaScrollV.top		= _BarraScrollEx_EspacioV.top + An + 1 + static_cast<int>((Proporcion * static_cast<float>(_BarraScrollEx_ValorV)));
				if (_BarraScrollEx_RectaScrollV.top >= (Al - An) - ANCHO_MINIMO_SCROLL)    _BarraScrollEx_RectaScrollV.top = (Al - An) - ANCHO_MINIMO_SCROLL;
				_BarraScrollEx_RectaScrollV.bottom	= _BarraScrollEx_EspacioV.top + An + ANCHO_MINIMO_SCROLL + static_cast<int>((Proporcion * static_cast<float>(_BarraScrollEx_ValorV))) + static_cast<int>((static_cast<float>(_BarraScrollEx_PaginaV) * Proporcion));
				if (_BarraScrollEx_RectaScrollV.bottom >= (Al - An) + Borde) _BarraScrollEx_RectaScrollV.bottom = (Al - An) + Borde;
			}
			_BarraScrollEx_RectaFondoSuperiorV.left		= _BarraScrollEx_EspacioV.left;
			_BarraScrollEx_RectaFondoSuperiorV.right	= _BarraScrollEx_EspacioV.right;
			_BarraScrollEx_RectaFondoSuperiorV.top		= _BarraScrollEx_RectaBotonSuperiorV.bottom;
			_BarraScrollEx_RectaFondoSuperiorV.bottom	= _BarraScrollEx_RectaScrollV.top;

			_BarraScrollEx_RectaFondoInferiorV.left		= _BarraScrollEx_EspacioV.left;
			_BarraScrollEx_RectaFondoInferiorV.right	= _BarraScrollEx_EspacioV.right;
			_BarraScrollEx_RectaFondoInferiorV.top		= _BarraScrollEx_RectaScrollV.bottom;
			_BarraScrollEx_RectaFondoInferiorV.bottom	= _BarraScrollEx_RectaBotonInferiorV.top;
//			_BarraScrollEx_PosActualV = _BarraScrollEx_ValorV;
		};



		//! Función para calcular los tamaños del scroll horizontal.
		/*!	Esta función calcula todos los tamaños de los controles que se usan en el scroll horizontal, incluyendo botones extendidos.
				\fn			void BarraScrollEx_CalcularScrollH(const bool TieneBorde);
                \param[in]  TieneBorde : Parametro en el que debemos especificar si el control tiene borde
				\return		No devuelve nada.
				\remarks	Función de uso interno.
		*/
		void DWLBarraScrollEx_Nucleo::BarraScrollEx_CalcularScrollH(const bool TieneBorde) {
		#if defined DWL_BaseControlExScroll_DEBUG
			DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::BarraScrollEx_CalcularScrollH\n"));
		#endif
            int Borde = 0;
            if (TieneBorde == true) Borde = 2;

            if (_BarraScrollEx_ValorH < 0) _BarraScrollEx_ValorH = 0;

			int An = _BarraScrollEx_EspacioH.right - _BarraScrollEx_EspacioH.left;
			int Al = _BarraScrollEx_EspacioH.bottom - _BarraScrollEx_EspacioH.top;

			for (size_t i = 0; i < _BarraScrollEx_BotonesH.size(); i++) {
				An -= 17;
				_BarraScrollEx_BotonesH[i]->Posicion.left	= An + 1;
				_BarraScrollEx_BotonesH[i]->Posicion.top	= _BarraScrollEx_EspacioH.top;
				_BarraScrollEx_BotonesH[i]->Posicion.right	= An + 17;
				_BarraScrollEx_BotonesH[i]->Posicion.bottom	= _BarraScrollEx_EspacioH.top + Al;
			}

			float Proporcion = static_cast<float>((An - (4 + Borde)) - (Al * 2)) / static_cast<float>(_BarraScrollEx_MaximoH);
			_BarraScrollEx_RectaBotonIzquierdoH.left	= _BarraScrollEx_EspacioH.left;
			_BarraScrollEx_RectaBotonIzquierdoH.top		= _BarraScrollEx_EspacioH.top;
			_BarraScrollEx_RectaBotonIzquierdoH.bottom	= _BarraScrollEx_EspacioH.bottom;
			_BarraScrollEx_RectaBotonIzquierdoH.right	= _BarraScrollEx_EspacioH.left + Al;

			_BarraScrollEx_RectaBotonDerechoH.left		= An - 16;
			_BarraScrollEx_RectaBotonDerechoH.top		= _BarraScrollEx_EspacioH.top;
			_BarraScrollEx_RectaBotonDerechoH.right		= An;
			_BarraScrollEx_RectaBotonDerechoH.bottom	= _BarraScrollEx_EspacioH.bottom;

			if (_BarraScrollEx_PaginaH > _BarraScrollEx_MaximoH) {
                _BarraScrollEx_RectaScrollH.left	= _BarraScrollEx_EspacioH.left + Al + 1;
				_BarraScrollEx_RectaScrollH.right	= (An - Al);
				_BarraScrollEx_RectaScrollH.top		= _BarraScrollEx_EspacioH.top;
				_BarraScrollEx_RectaScrollH.bottom	= _BarraScrollEx_EspacioH.bottom;
			}
			else {
				_BarraScrollEx_RectaScrollH.top		= _BarraScrollEx_EspacioH.top;
				_BarraScrollEx_RectaScrollH.bottom	= _BarraScrollEx_EspacioH.bottom;
				_BarraScrollEx_RectaScrollH.left	= _BarraScrollEx_EspacioH.left + Al + 1 + static_cast<int>((Proporcion * static_cast<float>(_BarraScrollEx_ValorH)));
				if (_BarraScrollEx_RectaScrollH.left >= (An - Al) - ANCHO_MINIMO_SCROLL)    _BarraScrollEx_RectaScrollH.left = (An - Al) - ANCHO_MINIMO_SCROLL;
				_BarraScrollEx_RectaScrollH.right	= _BarraScrollEx_EspacioH.left + Al + ANCHO_MINIMO_SCROLL + static_cast<int>((Proporcion * static_cast<float>(_BarraScrollEx_ValorH))) + static_cast<int>((static_cast<float>(_BarraScrollEx_PaginaH) * Proporcion));
				if (_BarraScrollEx_RectaScrollH.right >= (An - Al) + Borde) _BarraScrollEx_RectaScrollH.right = (An - Al) + Borde;
			}
			_BarraScrollEx_RectaFondoSuperiorH.left		= _BarraScrollEx_RectaBotonIzquierdoH.right;
			_BarraScrollEx_RectaFondoSuperiorH.right	= _BarraScrollEx_RectaScrollH.left;
			_BarraScrollEx_RectaFondoSuperiorH.top		= _BarraScrollEx_EspacioH.top;
			_BarraScrollEx_RectaFondoSuperiorH.bottom	= _BarraScrollEx_EspacioH.bottom;

			_BarraScrollEx_RectaFondoInferiorH.left		= _BarraScrollEx_RectaScrollH.right;
			_BarraScrollEx_RectaFondoInferiorH.right	= _BarraScrollEx_RectaBotonDerechoH.left;
			_BarraScrollEx_RectaFondoInferiorH.top		= _BarraScrollEx_EspacioH.top;
			_BarraScrollEx_RectaFondoInferiorH.bottom	= _BarraScrollEx_EspacioH.bottom;
//			_BarraScrollEx_PosActualH = _BarraScrollEx_ValorH;
		};

		//! Función que pinta el borde de varios controles del scroll.
		/*! Esta función pinta el borde de varios controles del scroll.
				\fn			inline void _BarraScrollEx_EnmarcarRecta(HDC hDC, RECT *Espacio, COLORREF ColorBorde);
				\param[in]	hDC			: HDC donde se esta pintado el ArbolEx.
				\param[in]	Espacio		: Recta que contiene el espacio para el borde de la marca.
				\param[in]	ColorBorde	: Color que se usara para pintar el borde.
				\return		No devuelve nada.
		*/
		void DWLBarraScrollEx_Nucleo::_BarraScrollEx_EnmarcarRecta(HDC hDC, RECT *Espacio, COLORREF ColorBorde) {
			#if defined DWL_BaseControlExScroll_DEBUG
				DWL::DWLDebug::ImprimirDebugMS(TEXT("DWLBarraScrollEx::_BarraScrollEx_EnmarcarRecta\n"));
			#endif
			HBRUSH Brocha = CreateSolidBrush(ColorBorde);
			FrameRect(hDC, Espacio, Brocha);
			BOOL Z = DeleteObject(Brocha);
			SetPixel(hDC, Espacio->left, Espacio->top, BarraScrollEx_Colores.FondoNormal());
			SetPixel(hDC, Espacio->left, Espacio->bottom -1, BarraScrollEx_Colores.FondoNormal());
			SetPixel(hDC, Espacio->right -1, Espacio->top, BarraScrollEx_Colores.FondoNormal());
			SetPixel(hDC, Espacio->right -1, Espacio->bottom -1, BarraScrollEx_Colores.FondoNormal());
		};

	}
}
