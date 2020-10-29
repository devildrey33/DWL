//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DWLMarcaEx.h																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Descripción :																																//
//					Este control simula un checkbox de windows.																					//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Este archivo contiene varias clases descritas a continuacion :																				//
// - DWLMarcaEx_Colores			:	Clase que enlaza los colores a la configuracion del skin por defecto										//
//									Puedes modificar cualquier color de esta clase, solo deberas repintar el control al terminar.				//
//																																				//
// - DWLMarcaEx_Nucleo			:	Clase que contiene las Funciónes basicas para pintar y controlar los eventos del control.						//
//									Esta clase se ha creado de forma que puede compartir un control con otra clase, asi podemos hacer controles	//
//									tipo ComboBox y de una forma mucho mas limpia.																//
//																																				//
// - DWLMarcaEx					:	Clase que hereda de DWLMarcaEx_Nucleo y lo enlaza a un control para el solo.								//
//									Esta clase es la que deberiamos usar para crear un boton estandar sin complicaciones.						//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Archivo creado por devildrey33 el dia 01/12/2004	para http://www.devildrey33.es																//
// Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :		//
//  http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																		//
//  http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)																//
//  http://www.softcatala.cat/wiki/GPL3		 (Catalá, traduccion no oficial)																	//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Version 0.95																																	//
// Ultima modificación : 05/11/2009																												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "DWLMarcaEx.h"
 
#define DWL_NOMBRE_CLASE_DWLMARCAEX    TEXT("DWL::ControlesEx::DWLMarcaEx")

namespace DWL {
	namespace ControlesEx {

		//! Constructor.
		/*!	Constructor por defecto.
				\fn		DWLMarcaEx(void);
				\return	No devuelve nada.
		*/
        DWLMarcaEx::DWLMarcaEx(void) : DWLControlEx(), DWLMarcaEx_Nucleo() {
            RegistrarClase(DWL_NOMBRE_CLASE_DWLMARCAEX, NULL, NULL, _GestorMensajes);
        };

		//! Destructor.
		/*!	Destructor.
				\fn		~DWLMarcaEx(void);
				\return	No devuelve nada.
		*/
        DWLMarcaEx::~DWLMarcaEx(void) {
            Destruir();
        };

		//! Función que retorna si esta ventana tiene el raton encima.
		/*!	Esta funcion devuelve si esta ventana tiene el raton encima.
				\fn			virtual bool Foco(void);
				\return		Devuelve true si el raton esta encima del control, false en caso contrario.
		*/
        bool DWLMarcaEx::Foco(void) {
			bool TieneFoco = false;
			if (_MarcaEx_Estado == 2) return true;
			POINT Pt;
			GetCursorPos(&Pt);
			if (_hWnd == WindowFromPoint(Pt)) { // Tiene el foco del raton
				TieneFoco = true;
			}
			return TieneFoco;
		};

		//! Función que crea la MarcaEx.
		/*!	Esta funcion crea la MarcaEx.
				\fn			HWND CrearMarcaEx(const long Estilos, HWND hWndParent, const TCHAR *Txt, const int cX, const int cY, const int cID, const bool cMarcado = false);
				\param[in]	Estilos		: Estilos para el ArbolEx (WS_CHILD | WS_VISIBLE).
				\param[in]	hWndParent	: HWND del control que sera el padre de la MarcaEx.
                \param[in]  Txt         : Texto para el control
				\param[in]	cX			: Posicion X.
				\param[in]	cY			: Posicion Y.
				\param[in]	cID			: ID de la MarcaEx.
				\param[in]	cMarcado	: Parametro si el control esta marcado o no inicialmente.
				\return		Devuelve el HWND de la MarcaEx. En caso de error devolvera NULL.
		*/
		HWND DWLMarcaEx::CrearMarcaEx(const long Estilos, HWND hWndParent, const TCHAR *Txt, const int cX, const int cY, const int cID, const bool cMarcado) {
			_MarcaEx_Marcado = cMarcado;

//			int nX = 0;
//			if (cX != DWL_CENTRADO) nX = cX;

			CrearControl(hWndParent, DWL_NOMBRE_CLASE_DWLMARCAEX, Estilos, TEXT(""), cX, cY, 20, 18, cID);

			HDC hDC = GetDC(NULL);
			HFONT VFuente = static_cast<HFONT>(SelectObject(hDC, MarcaEx_Estilos.Fuentes.Normal()));
			SIZE Tam;
			_MarcaEx_Texto = Txt;
			GetTextExtentPoint32(hDC, _MarcaEx_Texto(), static_cast<int>(_MarcaEx_Texto.Tam()), &Tam);
			SelectObject(hDC, VFuente);
			ReleaseDC(_hWnd, hDC);

/*			if (cX == DWL_CENTRADO) {
				RECT RP;
				GetClientRect(hWndParent, &RP);
				nX = (RP.right - (Tam.cx + 22)) / 2;
			}*/
			Mover(cX, cY, Tam.cx + 22, 18);
			_MarcaEx_Presionado = false;
			_MarcaEx_Estado = 0;
			_MarcaEx_PEstado = -1;
			return _hWnd;
		}

		//! Función que conecta la MarcaEx de un dialogo.
		/*!	Esta función conecta la MarcaEx de un dialogo.
				\fn			HWND ConectarMarcaEx(HWND hWndParent, const TCHAR *Txt,const int cID, const bool cMarcado = false);
				\param[in]	hWndParent	: HWND del control que sera el padre de la MarcaEx.
                \param[in]  Txt         : Texto para el control
				\param[in]	cID			: ID de la MarcaEx.
				\param[in]	cMarcado	: Parametro si el control esta marcado o no inicialmente.
				\return		Devuelve el HWND de la MarcaEx. En caso de error devolvera NULL.
                \remarks    Esta función solo debe usarse con controles que se creen durante la creación del dialogo, si esta clase no pertenece a un dialogo, o se va a crear dinamicamente, no debes usar esta función.
		*/
        HWND DWLMarcaEx::ConectarMarcaEx(HWND hWndParent, const TCHAR *Txt, const int cID, const bool cMarcado) {
			_MarcaEx_Marcado = cMarcado;
            RECT RW;
//			if (cX != DWL_CENTRADO) nX = cX;

			//CrearControl(hWndParent, TEXT("DWL::ControlesEx::DWLMarcaEx"), Estilos, TEXT(""), nX, cY, 20, 18, cID);
            _ConectarControl(cID, hWndParent);
            GetWindowRect(_hWnd, &RW);
//            int nX = RW.left;

			HDC hDC = GetDC(NULL);
			HFONT VFuente = static_cast<HFONT>(SelectObject(hDC, MarcaEx_Estilos.Fuentes.Normal()));
			SIZE Tam;
			_MarcaEx_Texto = Txt;
			GetTextExtentPoint32(hDC, _MarcaEx_Texto(), static_cast<int>(_MarcaEx_Texto.Tam()), &Tam);
			SelectObject(hDC, VFuente);
			ReleaseDC(_hWnd, hDC);

/*			if (cX == DWL_CENTRADO) {
				RECT RP;
				GetClientRect(hWndParent, &RP);
				nX = (RP.right - (Tam.cx + 22)) / 2;
			}*/
			Mover(RW.left, RW.top, Tam.cx + 22, 18);
			_MarcaEx_Presionado = false;
			_MarcaEx_Estado = 0;
			_MarcaEx_PEstado = -1;
			return _hWnd;
        }

		//! Función para asignar el texto del control.
		/*! Esta función se usa para asignar el texto del control.
				\fn			void Texto(const TCHAR *nTxt);
				\param[in]	nTxt : Cadena de caracteres que sera el nuevo texto del control.
				\return		No devuelve nada.
		*/
		void DWLMarcaEx::Texto(const TCHAR *Txt) {
			_MarcaEx_Texto = Txt;

			HDC hDC = GetDC(NULL);
			HFONT VFuente = static_cast<HFONT>(SelectObject(hDC, MarcaEx_Estilos.Fuentes.Normal()));
			SIZE Tam;
			GetTextExtentPoint32(hDC, _MarcaEx_Texto(), static_cast<int>(_MarcaEx_Texto.Tam()), &Tam);
			SelectObject(hDC, VFuente);
			ReleaseDC(_hWnd, hDC);

            WINDOWPLACEMENT WP;
			WP.length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(_hWnd, &WP);

			Mover(WP.rcNormalPosition.left, WP.rcNormalPosition.top, Tam.cx + 22, 18);
		}

		//! Función para activar / desactivar la MarcaEx.
		/*!	Esta funcion activa / desactiva la MarcaEx.
				\fn			void Activado(const bool nActivar);
				\param[in]	nActivar	: Parametro en el que especificaremos si queremos activar o desactivar la MarcaEx.
				\return		No devuelve nada.
		*/
		void DWLMarcaEx::Activado(const bool Activar) {
			if (Activar == false)	_MarcaEx_Estado = 3;
			else					_MarcaEx_Estado = 0;
			Repintar(true);
		}

		//! Función que repinta toda la MarcaEx.
		/*!	Esta función repinta toda la MarcaEx.
				\fn			void Repintar(const bool Forzar = false);
				\param[in]	Forzar : True para forzar el repintado, false para que la función decida si repintar.
				\return		No devuelve nada.
				\remarks	Cuando Forzar es false, esta función mira si ha cambiado algun estado interno,
							y de ser asi repinta el control, en caso contrario no hace nada.
		*/
		void DWLMarcaEx::Repintar(const bool Forzar) {
			if (Forzar == false && _MarcaEx_PEstado == _MarcaEx_Estado) return;
			_MarcaEx_PEstado = _MarcaEx_Estado;
			HDC hDC = GetDC(_hWnd);
            PAINTSTRUCT PS;
			Evento_Pintar(hDC, PS);
			ReleaseDC(_hWnd, hDC);
		}

		//! Función que pinta toda la MarcaEx cuado se recibe un mensaje WM_PAINT.
		/*!	Esta función pinta la MarcaEx cuando se recibe un mensaje WM_PAINT.
				\fn			LRESULT Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);
				\param[in]	hDC	: hDC donde se pintara toda la MarcaEx.
                \param[in]  PS  : Estructura que contiene los datos del pintado
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLMarcaEx::Evento_Pintar(HDC hDC, PAINTSTRUCT &PS) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			MarcaEx_Pintar(hDC, &RC, Foco());
            return 0;
		}

		//! Función predefinida del mensaje WM_*BUTTONDOWN (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONDOWN.
				\fn			virtual LRESULT Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param)
				\param[in]	Boton	: Boton presionado.
				\param[in]	cX		: Coordenada X del mouse.
				\param[in]	cY		: Coordenada Y del mouse.
				\param[in]	wParam	: Teclas extendidas presionadas.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLMarcaEx::Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			MarcaEx_Mouse_BotonPresionado(_hWnd, &RC, Boton, cX, cY, Param);
//			_MarcaEx_Estado = 2;
//			_MarcaEx_Presionado = true;
			Repintar();
            return 0;
		}

		//! Función predefinida del mensaje WM_*BUTTONUP (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONUP.
				\fn			virtual LRESULT Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	Boton	: Boton presionado.
				\param[in]	cX		: Coordenada X del mouse.
				\param[in]	cY		: Coordenada Y del mouse.
				\param[in]	wParam	: Teclas extendidas presionadas.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLMarcaEx::Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			MarcaEx_Mouse_BotonSoltado(_hWnd, &RC, Boton, cX, cY, Param);

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
		LRESULT DWLMarcaEx::Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			MarcaEx_Mouse_Movimiento(_hWnd, &RC, cX, cY, Param);

			Repintar();
            return 0;
		}

		//! Función que recibe cuando el mouse se va del control
		/*!	Esta función es la encargada de procesar los mensajes WN_MOUSELEAVE.
				\fn			virtual LRESULT Evento_Mouse_Saliendo(void);
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLMarcaEx::Evento_Mouse_Saliendo(void) {
			if (_MarcaEx_Estado != 3) _MarcaEx_Estado = 0;
			Repintar();
            return 0;
		}

		//! Esqueleto para los mensajes de la MarcaEx.
		/*! Esta función es el esqueleto para los mensajes de la MarcaEx.
				\fn			LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
				\param[in]	uMsg	: Mensaje.
				\param[in]	wParam	: Parametro1.
				\param[in]	lParam	: Parametro2.
				\return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
				\remarks	Esta función es el esqueleto del ArbolEx por donde pasaran todos sus mensajes.
		*/
		LRESULT CALLBACK DWLMarcaEx::GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
			switch (uMsg) {
				case WM_SETFOCUS	:  Repintar(true);																																						return 0;
				case WM_KILLFOCUS	:  _MarcaEx_Estado = 0;		Repintar(true);																																return 0;
				case WM_KEYDOWN		:  if (wParam == VK_SPACE || wParam == VK_RETURN) this->Evento_Mouse_BotonPresionado(0, 1, 1, NULL);																	break;
				case WM_KEYUP		:  if (wParam == VK_SPACE || wParam == VK_RETURN) this->Evento_Mouse_BotonSoltado(0, 1, 1, NULL);																		break;
			}
            return DWLControlEx::GestorMensajes(uMsg, wParam, lParam);
		}



	}
}
