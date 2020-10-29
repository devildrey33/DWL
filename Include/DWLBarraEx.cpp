/*! \file DWLBarraEx.cpp
	\brief		 Archivo que contiene las definiciones de las clases de la BarraEx.


	\details	Este control se puede usar como una barra de desplazamiento, o como una barra de progreso y admite tanto alineaciones verticales como horizontales.																								\n
				<table border = 0 align ='right'><tr><td> \image html BarraEx.jpg </td></tr></table>
																																												\n
				\section Clases_Sec		Este archivo contiene varias clases descritas a continuación  :
				 - DWL::ControlesEx::DWLBarraEx_Colores :																														\n
					Clase que enlaza los colores a la configuración del skin por defecto	.																					\n
					Puedes modificar cualquier color de esta clase, solo deberas repintar la barra al terminar.																	\n
																																												\n
				 - DWL::ControlesEx::DWLBarraEx_Nucleo :																														\n
					Clase que contiene las funciónes basicas para pintar y controlar los eventos de la barra.																	\n
					Esta clase se ha creado de forma que puede compartir un control con otra clase, asi podemos hacer controles	tipo ComboBox y de una forma mucho mas limpia.	\n
																																												\n
				 - DWL::ControlesEx::DWLBarraEx :																																\n
					Clase que hereda de DWLBarraEx_Nucleo y lo enlaza a un control para el solo.																				\n
					Esta clase es la que deberiamos usar para crear una barra estandar sin complicaciones.																		\n

																																																																\n
	\author		devildrey33
	\version	0.95
	\date		02/11/2009

	\remarks
				Archivo creado por devildrey33 el dia [10/02/2005] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

	\todo		Implementar tooltips informativos al desplazar la barra.
*/


#include "DWLBarraEx.h"


#define DWL_NOMBRE_CLASE_DWLBARRAEX TEXT("DWL::ControlesEx::DWLBarraEx")

namespace DWL {
	namespace ControlesEx {

		//! Constructor por defecto.
		/*! Constructor por defecto.
				\fn			DWLBarraEx(void);
				\return		No devuelve nada.
		*/
        DWLBarraEx::DWLBarraEx(void) {
		    RegistrarClase(DWL_NOMBRE_CLASE_DWLBARRAEX, NULL, 0, _GestorMensajes);
		};

		//! Destructor.
		/*! Destructor.
				\fn			~DWLBarraEx(void);
				\return		No devuelve nada.
		*/
        DWLBarraEx::~DWLBarraEx(void) {
		};

		//! Función que retorna si esta ventana tiene el raton encima.
		/*!	Esta funcion devuelve si esta ventana tiene el raton encima.
				\fn			virtual bool Foco(void);
				\return		Devuelve true si el raton esta encima del control, false en caso contrario.
		*/
        bool DWLBarraEx::Foco(void) {
			bool TieneFoco = false;
			if (_BarraEx_Estado == DWL_Enum_BarraEx_Estados_Presionado) return true;
			POINT Pt;
			GetCursorPos(&Pt);
			if (_hWnd == WindowFromPoint(Pt)) { // Tiene el foco del raton
				TieneFoco = true;
			}
			return TieneFoco;
		};

		//! Función que crea la BarraEx
		/*!	Esta funcion crea la BarraEx.
				\fn			HWND CrearBarraEx(const long Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const int Tipo = DWL_BARRAEX_PROGRESO_HORIZONTAL, const long nMinimo = 0, const long nMaximo = 1000, const int nPixelesBorde = 2);
				\param[in]	Estilos				: Estilos para el ArbolEx (WS_CHILD | WS_VISIBLE).
				\param[in]	hWndParent			: HWND del control que sera el padre de la BarraEx.
				\param[in]	cX					: Posicion X.
				\param[in]	cY					: Posicion Y.
				\param[in]	cAncho				: Ancho de la BarraEx.
				\param[in]	cAlto				: Alto de la BarraEx.
				\param[in]	cID					: ID de la BarraEx.
				\param[in]	int					: Tipo de barra [DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL, DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL, DWL_BARRAEX_PROGRESO_HORIZONTAL, DWL_BARRAEX_PROGRESO_VERTICAL].
				\param[in]	nMinimo				: Valor minimo inicial (0 por defecto).
				\param[in]	nMaximo				: Valor maximo inicial (1000 por defecto).
				\return		Devuelve el HWND de la BarraEx. En caso de error devolvera NULL.
		*/
		HWND DWLBarraEx::CrearBarraEx(const long Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const int nTipo, const long nMinimo, const long nMaximo) {
			CrearControl(hWndParent, DWL_NOMBRE_CLASE_DWLBARRAEX, Estilos, 0, cX, cY, cAncho, cAlto, cID);
			SetWindowRgn(_hWnd, CreateRoundRectRgn(0, 0, cAncho, cAlto, 5, 5), false);
			_ID = cID;
			_BarraEx_Estado = DWL_Enum_BarraEx_Estados_Normal;
			_BarraEx_PEstado = DWL_Enum_BarraEx_Estados_NoDefinido;
			_BarraEx_Presionado = false;
			_BarraEx_Maximo = nMaximo;
			_BarraEx_Minimo = nMinimo;
			_BarraEx_Valor = 0;
			BarraEx_Estilos.Orientacion = nTipo;
			return _hWnd;
		}

		//! Función que conecta la BarraEx de un dialogo.
		/*!	Esta funcion conecta la BarraEx de un dialogo.
				\fn			HWND ConectarBarraEx(HWND hWndParent, const int cID, const int Tipo = DWL_BARRAEX_PROGRESO_HORIZONTAL, const long nMinimo = 0, const long nMaximo = 1000, const int nPixelesBorde = 2);
				\param[in]	hWndParent			: HWND del control que sera el padre de la BarraEx.
				\param[in]	cID					: ID de la BarraEx.
				\param[in]	nTipo				: Tipo de barra [DWL_BARRAEX_DESPLAZAMIENTO_HORIZONTAL, DWL_BARRAEX_DESPLAZAMIENTO_VERTICAL, DWL_BARRAEX_PROGRESO_HORIZONTAL, DWL_BARRAEX_PROGRESO_VERTICAL].
				\param[in]	nMinimo				: Valor minimo inicial (0 por defecto).
				\param[in]	nMaximo				: Valor maximo inicial (1000 por defecto).
				\return		Devuelve el HWND de la BarraEx. En caso de error devolvera NULL.
                \remarks    Esta función solo debe usarse con controles que se creen durante la creación del dialogo, si esta clase no pertenece a un dialogo, o se va a crear dinamicamente, no debes usar esta función.
		*/
        HWND DWLBarraEx::ConectarBarraEx(HWND hWndParent, const int cID, const int nTipo, const long nMinimo, const long nMaximo) {
            _ConectarControl(cID, hWndParent);
            RECT RC;
            GetClientRect(_hWnd, &RC);
			SetWindowRgn(_hWnd, CreateRoundRectRgn(0, 0, RC.right, RC.bottom, 5, 5), false);
			_ID = cID;
			_BarraEx_Estado = DWL_Enum_BarraEx_Estados_Normal;
			_BarraEx_PEstado = DWL_Enum_BarraEx_Estados_NoDefinido;
			_BarraEx_Presionado = false;
			_BarraEx_Maximo = nMaximo;
			_BarraEx_Minimo = nMinimo;
			_BarraEx_Valor = 0;
			BarraEx_Estilos.Orientacion = nTipo;
			return _hWnd;
		}

		//! Función que pinta todo la BarraEx cuado se recibe un mensaje WM_PAINT.
		/*!	Esta función pinta la BarraEx cuando se recibe un mensaje WM_PAINT.
				\fn			LRESULT Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);
				\param[in]	hDC	: hDC donde se pintara todo la BarraEx.
                \param[in]  PS  : Estructura con los datos de pintado.
				\return		No devuelve nada.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLBarraEx::Evento_Pintar(HDC hDC, PAINTSTRUCT &PS) {
			RECT Espacio;
			GetClientRect(_hWnd, &Espacio);
			BarraEx_Pintar(hDC, &Espacio, Foco(), false);
            return 0;
		}

		//! Función que repinta todo la BarraEx.
		/*!	Esta función repinta todo la BarraEx.
				\fn			void Repintar(const bool Forzar = false);
				\param[in]	Forzar : True para forzar el repintado, false para que la funcion decida si repintar.
				\return		No devuelve nada.
				\remarks	Cuando Forzar es false, esta función mira si ha cambiado algun estado interno,
							y de ser asi repinta el control, en caso contrario no hace nada.
		*/
		void DWLBarraEx::Repintar(const bool Forzar) {
			if (Forzar == false) {
				if (_BarraEx_PEstado == _BarraEx_Estado) return;
			}
			_BarraEx_PEstado = _BarraEx_Estado;
			HDC hDC = GetDC(_hWnd);
            PAINTSTRUCT PS;
			Evento_Pintar(hDC, PS);
			ReleaseDC(_hWnd, hDC);
        }

	    //! Función predefinida del mensaje WM_MOUSEMOVE.
	    /*!	Esta función es la encargada de procesar los mensajes WN_MOUSEMOVE.
			    \fn			virtual LRESULT Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);
			    \param[in]	cX		: Coordenada X del mouse.
			    \param[in]	cY		: Coordenada Y del mouse.
			    \param[in]	Param	: Teclas extendidas presionadas.
			    \return		No devuelve nada.
	    */
		LRESULT DWLBarraEx::Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			BarraEx_Mouse_Movimiento(_hWnd, &RC, cX, cY, Param);
			Repintar(true);
            return 0;
		}

	    //! Función predefinida del mensaje WM_*BUTTONDOWN (Virtual)
	    /*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONDOWN.
			    \fn			virtual LRESULT Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param)
			    \param[in]	Boton	: Boton presionado.
			    \param[in]	cX		: Coordenada X del mouse.
			    \param[in]	cY		: Coordenada Y del mouse.
			    \param[in]	Param	: Teclas extendidas presionadas.
			    \return		No devuelve nada.
	    */
		LRESULT DWLBarraEx::Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			BarraEx_Mouse_BotonPresionado(_hWnd, &RC, Boton, cX, cY, Param);
			Repintar(true);
            return 0;
		}

		//! Función predefinida del mensaje WM_*BUTTONUP (Virtual)
		/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONUP.
				\fn			virtual LRESULT Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
				\param[in]	Boton	: Boton presionado.
				\param[in]	cX		: Coordenada X del mouse.
				\param[in]	cY		: Coordenada Y del mouse.
				\param[in]	Param	: Teclas extendidas presionadas.
				\return		No devuelve nada.
		*/
		LRESULT DWLBarraEx::Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param) {
			RECT RC;
			GetClientRect(_hWnd, &RC);
			BarraEx_Mouse_BotonSoltado(_hWnd, &RC, Boton, cX, cY, Param);
			Repintar(true);
            return 0;
		}

		//! Función que recibe cuando el mouse se va del control
		/*!	Esta función es la encargada de procesar los mensajes WN_MOUSELEAVE.
				\fn			virtual LRESULT Evento_Mouse_Saliendo(void);
				\return		No devuelve nada.
				\return		Si re-emplazas esta funcion debes retornar 0.
		*/
		LRESULT DWLBarraEx::Evento_Mouse_Saliendo(void) {
			_BarraEx_Estado = DWL_Enum_BarraEx_Estados_Normal;
			Repintar(true);
            return 0;
		}


	}
}
