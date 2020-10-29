#ifndef DWL_MARCAEX_NUCLEO_H
#define DWL_MARCAEX_NUCLEO_H

#include "DWLMarcaEx_Estilos.h"
#include "..\DWLString.h"
 

namespace DWL {
	namespace ControlesEx {

		//! Clase Nucleo de la MarcaEx
		/*! Esta clase contiene las funciones de pintado, funciones de control para el teclado y el raton, y algunos eventos que podemos sobre-escribir.		*/
		class DWLMarcaEx_Nucleo {
		 public : //////////////////////////// Miembros publicos

                                            //! Constructor por defecto.
                                            /*! Constructor por defecto.
                                                    \fn			DWLMarcaEx_Nucleo(void);
                                                    \return		No devuelve nada.
                                            */
                                            DWLMarcaEx_Nucleo(void);

                                            //! Destructor.
                                            /*! Destructor.
                                                    \fn			~DWLMarcaEx_Nucleo(void);
                                                    \return		No devuelve nada.
                                            */
         virtual                           ~DWLMarcaEx_Nucleo(void);

                                            //! Función que pinta la MarcaEx en el DC y espacio especificados.
                                            /*! Esta funcion pinta la MarcaEx en las coordenadas y DC especificados.
                                                    \fn			void MarcaEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true);
                                                    \param[in]	hDC					: DC en el que se va a pintar la ListaEx.
                                                    \param[in]	Espacio				: Recta que delimita el espacio donde se puede pintar la ListaEx.
                                                    \param[in]	TieneFoco			: Valor que determina si la lista tiene el foco del raton (por defecto se usara la funcion Foco()).
                                                    \return		No devuelve nada.
                                                    \remarks	Esta función esta preparada para pintar la MarcaEx en un DC que no sea el suyo, o que sea compartido.
                                            */
		 void							    MarcaEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco = true);

                                            //! Función que retorna si el control esta marcado.
                                            /*! Esta función develve si el control esta marcado.
                                                    \fn			inline bool MarcaEx_Marcado(void) const;
                                                    \return		Devuelve true el control esta marcado, false en caso contrario.
                                            */
		 inline bool                        MarcaEx_Marcado(void) const {
                                                return _MarcaEx_Marcado;
                                            };

                                            //! Función para marcar / desmarcar el control.
                                            /*! Esta función marca / desmarca el control.
                                                    \fn			inline void MarcaEx_Marcar(const bool nMarca);
                                                    \param[in]	nMarca : True para marcar el control, false para desmarcarlo.
                                                    \return		No devuelve nada.
                                            */
		 inline void                        MarcaEx_Marcar(const bool nMarca) {
                                                _MarcaEx_Marcado = nMarca;
                                            };

                                            //! Función para asignar un texto al control.
                                            /*! Esta función asigna el texto especificado al control.
                                                    \fn			void MarcaEx_Texto(const TCHAR *nTxt);
                                                    \param[in]	nTxt : Cadena de texto que queremos asignar al control.
                                                    \return		No devuelve nada.
                                            */
		 void                               MarcaEx_Texto(const TCHAR *nTxt) {
                                                _MarcaEx_Texto = nTxt;
                                            };

                                            //! Función que retorna el texto del control.
                                            /*! Esta función develve el texto del control.
                                                    \fn			inline const TCHAR *MarcaEx_Texto(void);
                                                    \return		Devuelve un puntero a una cadena de texto correspondiente al texto del control.
                                            */
		 inline const TCHAR                *MarcaEx_Texto(void) {
                                                return _MarcaEx_Texto();
                                            };

                                            //! Función virtual que pinta la marca del control.
                                            /*! Esta función virtual pinta la marca del control.
                                                    \fn			virtual void MarcaEx_Evento_PintarMarca(HDC hDC, RECT *Espacio, const int nEstado);
                                                    \param[in]	hDC		: hDC donde se va a pintar la MarcaEx.
                                                    \param[in]	Espacio	: Espacio donde se pintara.
                                                    \param[in]	nEstado	: Estado del control : 0 = normal, 1 = resaltado, 2 = presionado.
                                                    \return		No devuelve nada.
                                            */
		 virtual void					    MarcaEx_Evento_PintarMarca(HDC hDC, RECT *Espacio, const int nEstado);

                                            //! Función virtual que pinta el fondo del control.
                                            /*! Esta función virtual pinta el fondo del control.
                                                    \fn			virtual void MarcaEx_Evento_PintarFondo(HDC hDC, RECT *Espacio);
                                                    \param[in]	hDC		: hDC donde se va a pintar la MarcaEx.
                                                    \param[in]	Espacio	: Espacio donde se pintara.
                                                    \return		No devuelve nada.
                                            */
		 virtual void					    MarcaEx_Evento_PintarFondo(HDC hDC, RECT *Espacio);

                                            //! Función que procesa las teclas presionadas en la MarcaEx.
                                            /*! Esta función procesa las teclas presionadas en la MarcaEx.
                                                    \fn			void MarcaEx_Teclado_TeclaPresionada(HWND hWndControl, const int Tecla, LPARAM lParam);
                                                    \param[in]	hWndControl	: HWND del control que contiene la MarcaEx.
                                                    \param[in]	Tecla		: Tecla que se ha presionado.
                                                    \param[in]	lParam		: lParam que contiene si se ha pulsado shift / control y otras teclas extendidas.
                                                    \return		No devuelve nada.
                                                    \remarks    Esta función debe ser enlazada con el Evento_TeclaPresionada del control que vaya a contener la MarcaEx.
                                                    \sa			MarcaEx_Teclado_TeclaPresionada()
                                            */
		 void							    MarcaEx_Teclado_TeclaPresionada(HWND hWndControl, const int Tecla, LPARAM lParam);

                                            //! Función que procesa las teclas soltadas en la MarcaEx.
                                            /*! Esta función procesa las teclas presionadas en la MarcaEx.
                                                    \fn			void MarcaEx_Teclado_TeclaSoltada(HWND hWndControl, const int Tecla, LPARAM lParam);
                                                    \param[in]	hWndControl	: HWND del control que contiene la MarcaEx.
                                                    \param[in]	Tecla		: Tecla que se ha soltado.
                                                    \param[in]	lParam		: lParam que contiene si se ha pulsado shift / control y otras teclas extendidas.
                                                    \return		No devuelve nada.
                                                    \remarks    Esta función debe ser enlazada con el Evento_TeclaSoltada del control que vaya a contener la MarcaEx.
                                                    \sa			MarcaEx_Teclado_TeclaSoltada()
                                            */
		 void							    MarcaEx_Teclado_TeclaSoltada(HWND hWndControl, const int Tecla, LPARAM lParam);

                                            //! Función que procesa el movimiento del mouse en la MarcaEx.
                                            /*! Esta función procesa el movimiento del mouse en la MarcaEx.
                                                    \fn			BOOL MarcaEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param);
                                                    \param[in]	hWndControl		: HWND del control que contiene la MarcaEx.
                                                    \param[in]	RectaControl	: Recta con el espacio de la MarcaEx.
                                                    \param[in]	cX				: Coordenada X del mouse relativa al control.
                                                    \param[in]	cX				: Coordenada Y del mouse relativa al control.
                                                    \param[in]	wParam			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
                                                    \return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
                                                    \remarks    Esta función debe ser enlazada con el Evento_Mouse_Movimiento del control que vaya a contener la MarcaEx.
                                                    \sa			MarcaEx_Mouse_BotonPresionado(), MarcaEx_Mouse_BotonSoltado()
                                            */
		 BOOL					    	    MarcaEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT Param);

                                            //! Función que procesa los botones presionados del mouse en la MarcaEx.
                                            /*! Esta función procesa los botones presionados del mouse en la MarcaEx.
                                                    \fn			BOOL MarcaEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
                                                    \param[in]	hWndControl		: HWND del control que contiene la MarcaEx.
                                                    \param[in]	RectaControl	: Recta con el espacio de la MarcaEx.
                                                    \param[in]	Boton			: Boton del mouse presionado.
                                                    \param[in]	cX				: Coordenada X del mouse relativa al control.
                                                    \param[in]	cX				: Coordenada Y del mouse relativa al control.
                                                    \param[in]	wParam			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
                                                    \return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
                                                    \remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonPresionado del control que vaya a contener la MarcaEx.
                                                    \sa			MarcaEx_Mouse_Movimiento(), MarcaEx_Mouse_BotonSoltado()
                                            */
		 BOOL				    		    MarcaEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);

                                            //! Función que procesa los botones soltados del mouse en la MarcaEx.
                                            /*! Esta función procesa los botones soltados del mouse en la MarcaEx.
                                                    \fn			BOOL MarcaEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
                                                    \param[in]	hWndControl		: HWND del control que contiene la MarcaEx.
                                                    \param[in]	RectaControl	: Recta con el espacio de la MarcaEx.
                                                    \param[in]	Boton			: Boton del mouse presionado.
                                                    \param[in]	cX				: Coordenada X del mouse relativa al control.
                                                    \param[in]	cX				: Coordenada Y del mouse relativa al control.
                                                    \param[in]	wParam			: Param que contiene si se ha pulsado shift / control y otras teclas extendidas.
                                                    \return		Devuelve true si el mensaje se ha procesado, false en caso contrario.
                                                    \remarks    Esta función debe ser enlazada con el Evento_Mouse_BotonSoltado del control que vaya a contener la MarcaEx.
                                                    \sa			MarcaEx_Mouse_Movimiento(), MarcaEx_Mouse_BotonPresionado()
                                            */
		 BOOL   						    MarcaEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);

											//! Clase que contiene los estilos del control
		 DWLMarcaEx_Estilos					MarcaEx_Estilos;
		protected: /////////////////////////// Miembros protegidos

                                            //! El control esta marcado o no
		 bool                              _MarcaEx_Marcado;

                                            //! Estado del control (0 normal, 1 hilight, 2 desactivado / presionado)
		 char                              _MarcaEx_Estado;

                                            //! Ultimo estado
		 char                              _MarcaEx_PEstado;

                                            //! El control esta presionado
		 bool                              _MarcaEx_Presionado;

                                            //! Texto del control
		 DWLString                         _MarcaEx_Texto;
		};							    	//
		////////////////////////////////////// Fin DWLMarcaEx_Nucleo


    };
};

#endif
