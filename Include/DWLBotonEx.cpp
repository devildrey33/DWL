//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DWLBotonEx.h																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Descripción :																																//
//					Este control se puede usar como boton estandard, o como un boton marca (se queda presionado, y luego se des-presiona).		//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Este archivo contiene varias clases descritas a continuacion :																				//
// - DWLBotonEx_Colores			:	Clase que enlaza los colores a la configuracion del skin por defecto										//
//									Puedes modificar cualquier color de esta clase, solo deberas repintar el boton al terminar.					//
//																																				//
// - DWLBotonEx_ParametrosClick :	Clase utilizada internamente para pasar los datos de un click a la ventana padre.							//
//																																				//
// - DWLBotonEx_Nucleo			:	Clase que contiene las Funciónes basicas para pintar y controlar los eventos del boton.						//
//									Esta clase se ha creado de forma que puede compartir un control con otra clase, asi podemos hacer controles	//
//									tipo ComboBox y de una forma mucho mas limpia.																//
//																																				//
// - DWLBotonEx					:	Clase que hereda de DWLBotonEx_Nucleo y lo enlaza a un control para el solo.								//
//									Esta clase es la que deberiamos usar para crear un boton estandar sin complicaciones.						//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Archivo creado por devildrey33 el dia 05/12/2004	para http://www.devildrey33.es																//
// Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :		//
//  http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																		//
//  http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)																//
//  http://www.softcatala.cat/wiki/GPL3		 (Catalá, traduccion no oficial)																	//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Version 0.95																																	//
// Ultima modificación : 02/11/2009																												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "DWLBotonEx.h"

#define DWL_NOMBRE_CLASE_DWLBOTONEX     TEXT("DWL::ControlesEx::DWLBotonEx")

namespace DWL {
	namespace ControlesEx {

		//! Constructor.
		/*!	Constructor por defecto.
				\fn		DWLBotonEx(void);
				\return	No devuelve nada.
		*/
        DWLBotonEx::DWLBotonEx(void) : DWLControlEx(), DWLBotonEx_Nucleo() {
            RegistrarClase(DWL_NOMBRE_CLASE_DWLBOTONEX, 0, 0, _GestorMensajes);
		}

		//! Destructor.
		/*!	Destructor.
				\fn	   ~DWLBotonEx(void);
				\return	No devuelve nada.
		*/
		DWLBotonEx::~DWLBotonEx(void) {
            Destruir();
		}

	    //! Función que crea el BotonEx
	    /*!	Esta funcion crea el BotonEx.
			    \fn			HWND CrearBotonEx(const long Estilos, HWND hWndParent, const TCHAR *nTxt, const int cX, const int cY, const int cAncho, const int cAlto, const UINT ID);
			    \param[in]	Estilos			: Estilos para el BotonEx (WS_CHILD | WS_VISIBLE).
			    \param[in]	hWndParent		: HWND del control que sera el padre del BotonEx.
			    \param[in]	nTxt			: Texto para el BotonEx.
			    \param[in]	cX				: Posicion X.
			    \param[in]	cY				: Posicion Y.
			    \param[in]	cAncho			: Ancho del BotonEx.
			    \param[in]	cAlto			: Alto del BotonEx.
			    \param[in]	cID				: ID del BotonEx.
			    \return		Devuelve el HWND del BotonEx. En caso de error devolvera NULL.
	    */ 
		HWND DWLBotonEx::CrearBotonEx(const long Estilos, HWND hWndParent, const TCHAR *nTxt, const int cX, const int cY, const int cAncho, const int cAlto, const UINT cID) {
			CrearControl(hWndParent, DWL_NOMBRE_CLASE_DWLBOTONEX, Estilos, nTxt, cX, cY, cAncho, cAlto, cID);
			if (nTxt != NULL) _BotonEx_Texto = nTxt;
			_ID = cID;
			_BotonEx_Estado = 0;
			_BotonEx_PEstado = -1;
			_BotonEx_Presionado = false;
			_BotonEx_Marcado = false;
			// Creo y asigno una region al boton
			HRGN Rgn = CreateRoundRectRgn(0, 0, cAncho + 1, cAlto + 1, 2, 2);
			SetWindowRgn(_hWnd, Rgn, false);
			_BotonEx_Activado = true;

			_MouseDentro = false;
			return _hWnd;
		}


	    //! Función que crea el BotonEx
	    /*!	Esta funcion crea el BotonEx.
			    \fn			HWND ConectarBotonEx(HWND hWndParent, const TCHAR *nTxt, const UINT ID);
			    \param[in]	hWndParent		: HWND del control que sera el padre del BotonEx.
			    \param[in]	nTxt			: Texto para el BotonEx.
			    \param[in]	cID				: ID del BotonEx.
			    \return		Devuelve el HWND del BotonEx. En caso de error devolvera NULL.
                \remarks    Esta función solo debe usarse con controles que se creen durante la creación del dialogo, si esta clase no pertenece a un dialogo, o se va a crear dinamicamente, no debes usar esta función.
	    */
        HWND DWLBotonEx::ConectarBotonEx(HWND hWndParent, const TCHAR *nTxt, const UINT cID) {
            _ConectarControl(cID, hWndParent);
			if (nTxt != NULL) _BotonEx_Texto = nTxt;
			_ID = cID;
			_BotonEx_Estado = 0;
			_BotonEx_PEstado = -1;
			_BotonEx_Presionado = false;
			_BotonEx_Marcado = false;
            RECT RC;
            GetClientRect(_hWnd, &RC);
			// Creo y asigno una region al boton
			HRGN Rgn = CreateRoundRectRgn(0, 0, RC.right + 1, RC.bottom + 1, 2, 2);
			SetWindowRgn(_hWnd, Rgn, false);
			_BotonEx_Activado = true;

			_MouseDentro = false;
			return _hWnd;
        }

		//! Función para activar / desactivar el BotonEx.
		/*!	Esta funcion activa / desactiva el BotonEx.
				\fn			void Activado(const bool nActivar);
				\param[in]	nActivar	: Parametro en el que especificaremos si queremos activar o desactivar el BotonEx.
				\param[in]	nRepintar	: Parametro en el que especificaremos si queremos repintar el BotonEx.
				\return		No devuelve nada.
		*/
		void DWLBotonEx::Activado(const bool Activar) {
			if (_hWnd == NULL) return;
			if (Activar == false) _BotonEx_Estado = 3;
			else                  _BotonEx_Estado = 0;
			_BotonEx_PEstado = -1;
			_BotonEx_Presionado = false;
			_BotonEx_Activado = Activar;
			Repintar();
		}

		//! Función predefinida del mensaje WM_*BUTTONDOWN (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONDOWN.
				\fn			virtual LRESULT Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param)
				\param[in]	Boton	: Boton presionado.
				\param[in]	cX		: Coordenada X del mouse.
				\param[in]	cY		: Coordenada Y del mouse.
				\param[in]	Param	: Teclas extendidas presionadas.
				\return		No devuelve nada.
				\return		Si re-emplazas esta funcion debes retornar 0.
        */
		LRESULT DWLBotonEx::Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			BotonEx_Mouse_BotonPresionado(_hWnd, &RC, Boton, cX, cY, Param);
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
		LRESULT DWLBotonEx::Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			BotonEx_Mouse_BotonSoltado(_hWnd, &RC, Boton, cX, cY, Param);
            return 0;
		}


		//! Función que recibe cuando el mouse se va del control.
		/*!	Esta función es la encargada de procesar los mensajes WN_MOUSELEAVE.
				\fn			virtual LRESULT Evento_Mouse_Saliendo(void);
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLBotonEx::Evento_Mouse_Saliendo(void) {
			if (_BotonEx_Estado != 3) _BotonEx_Estado = 0;
			Repintar();
            return 0;
		}

	    //! Función predefinida del mensaje WM_MOUSEMOVE.
	    /*!	Esta función es la encargada de procesar los mensajes WN_MOUSEMOVE.
			    \fn			virtual LRESULT Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);
			    \param[in]	cX		: Coordenada X del mouse.
			    \param[in]	cY		: Coordenada Y del mouse.
			    \param[in]	wParam	: Teclas extendidas presionadas.
			    \return		Si re-emplazas esta funcion debes retornar 0.
        */
		LRESULT DWLBotonEx::Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			if (BotonEx_Mouse_Movimiento(_hWnd, &RC, cX, cY, Param) == TRUE) Repintar();
            return 0;
		}

		//! Función para mostrar / ocultar el boton.
		/*! Esta función muestra / oculta el BotonEx.
				\fn			void Visible(const bool nMostrar);
				\param[in]	nMostrar : True para mostrar el control, false para ocultarlo.
				\return		No devuelve nada.
		*/
		void DWLBotonEx::Visible(const bool Mostrar) {
			if (Mostrar == true) {
				ShowWindow(_hWnd, SW_SHOW);
				if (_BotonEx_Activado == true) _BotonEx_Estado = 0;
				else                           _BotonEx_Estado = 3;
				_BotonEx_PEstado = -1;
				Repintar();
			}
			else {
				 ShowWindow(_hWnd, SW_HIDE);
				_BotonEx_Estado = -1;
			}
		}

		//! Función que repinta todo el BotonEx.
		/*!	Esta función repinta todo el BotonEx incluyendo barras de scroll y botones extra.
				\fn			void Repintar(const bool Forzar = false);
				\param[in]	Forzar : True para forzar el repintado, false para que la funcion decida si repintar.
				\return		No devuelve nada.
				\remarks	Cuando Forzar es false, esta función mira si ha cambiado algun estado interno,
							y de ser asi repinta el control, en caso contrario no hace nada.
		*/
		void DWLBotonEx::Repintar(const bool Forzar) {
			if (_hWnd == NULL) return;
			if (Forzar == false) {
				if (_BotonEx_PEstado == _BotonEx_Estado) return;
			}
			_BotonEx_PEstado = _BotonEx_Estado;
			HDC hDC = GetDC(_hWnd);
            PAINTSTRUCT PS;
			Evento_Pintar(hDC, PS);
			ReleaseDC(_hWnd, hDC);
		}

		//! Función que pinta todo el BotonEx cuado se recibe un mensaje WM_PAINT.
		/*!	Esta función pinta el BotonEx cuando se recibe un mensaje WM_PAINT.
				\fn			virtual void Evento_Pintar(HDC hDC);
				\param[in]	hDC	: hDC donde se pintara todo el BotonEx.
                \param[in]  PS  : Estructura que contiene datos del pintado.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLBotonEx::Evento_Pintar(HDC hDC, PAINTSTRUCT &PS) {
			if (_hWnd == NULL) return 0;
			RECT R;
			GetClientRect(_hWnd, &R);
			BotonEx_Pintar(hDC, &R, Foco());
            return 0;
		}

		//! Función predefinida del mensaje WM_KEYDOWN (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WM_KEYDOWN.
				\fn			virtual LRESULT Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Param);
				\param[in]	Caracter   : Tecla virtual presionada.
                \param[in]  Repeticion : Repeticion de la tecla.
				\param[in]	Param	   : Teclas extendidas presionadas.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLBotonEx::Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Param) {
			BotonEx_Teclado_TeclaPresionada(_hWnd, Caracter, Repeticion, Param);
			Repintar();
            return 0;
		}

		//! Función predefinida del mensaje WM_KEYUP (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WM_KEYUP.
				\fn			virtual void Evento_Teclado_TeclaSoltada(const int VirtKey, LPARAM lParam);
				\param[in]	Caracter   : Tecla virtual soltada.
                \param[in]  Repeticion : Repeticion de la tecla.
				\param[in]	Param	   : Teclas extendidas soltadas.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLBotonEx::Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Param) {
			BotonEx_Teclado_TeclaSoltada(_hWnd, Caracter, Repeticion, Param);
			Repintar();
            return 0;
		}

		//! Función que retorna si esta ventana tiene el raton encima.
		/*!	Esta funcion devuelve si esta ventana tiene el raton encima.
				\fn			virtual bool Foco(void);
				\return		Devuelve true si el raton esta encima del control, false en caso contrario.
		*/
        bool DWLBotonEx::Foco(void) {
			bool TieneFoco = false;
			if (_BotonEx_Estado == 2) return true;
			POINT Pt;
			GetCursorPos(&Pt);
			if (_hWnd == WindowFromPoint(Pt)) { // Tiene el foco del raton
				TieneFoco = true;
			}
			return TieneFoco;
		};


	}
}
