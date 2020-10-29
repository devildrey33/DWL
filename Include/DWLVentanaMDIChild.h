#ifndef DWL_VENTANAMDICHILD_H
#define DWL_VENTANAMDICHILD_H

#include "DWLEventosPadre.h"


namespace DWL {
 
	namespace Ventanas {
        class DWLVentanaMDI;

        class DWLVentanaMDIChild : public Base::DWLEventosPadre<LRESULT> {
		   public : ////////////////// -Declaraciones publicas

                                    //
									// Constructor
									DWLVentanaMDIChild(void);

									//
									// Destructor (Vacio)
								   ~DWLVentanaMDIChild(void);

								    //! Funci�n que crea la ventana MDI hija.
								    /*!	Esta funci�n crea la ventana MDI hija.
										    \fn			HWND CrearVentanaMDIChild(DWLVentanaMDI *PadreMDI, const TCHAR *nNombre, UINT nEstilos, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, DWORD nEstiloExtendido, HBRUSH nColorFondo = NULL, const int nIconoRecursos = NULL);
										    \param[in]	nNombre				: Nombre para la clase ventana.
										    \param[in]	nEstilos			: Estilos validos para ventanas MDI.
										    \param[in]	nTexto				: Titulo para la ventana.
										    \param[in]	cX					: Posicion X. Puedes especificar DWL_CENTRADO para que se centre.
										    \param[in]	cY					: Posicion Y. Puedes especificar DWL_CENTRADO para que se centre.
										    \param[in]	cAncho				: Ancho de la ventana.
										    \param[in]	cAlto				: Alto de la ventana.
										    \param[in]	nMenu				: Menu para la ventana.
										    \param[in]	nEstiloExtendido	: Estilos extendidos validos.
										    \param[in]	nColorFondo			: Brocha con el color del fondo de la ventana. Puede ser NULL.
										    \param[in]	nIconoRecursos		: ID del icono de los recursos que se asignara a la ventana. Puede ser 32512 para que se asigne el icono de la aplicaci�n.
										    \return		Devuelve el HWND de la ventana hija. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para ver el error.
								    */
           HWND                     CrearVentanaMDIChild(DWLVentanaMDI *PadreMDI, const TCHAR *nNombre, UINT nEstilos, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, DWORD nEstiloExtendido, HBRUSH nColorFondo = NULL, const int nIconoRecursos = NULL);

									//
									// Funci�n para asignar si la ventana se puede maximizar
									// virtual void Maximizable(const bool nMax);
		   virtual void             Maximizable(const bool nMax);

									//
									// Funci�n que retorna si la ventana se puede maximizar
									// const bool Maximizable(void);
		   virtual bool             Maximizable(void);

									//
									// Funci�n para asignar si la ventana se puede minimizar
									// void Minimizable(const bool nMin);
		   virtual void             Minimizable(const bool nMin);

									//
									// Funci�n que retorna si la ventana se puede minimizar
									// virtual bool Minimizable(void);
		   virtual bool             Minimizable(void);

									//
									// Funci�n que posiciona la ventana siempre delante de todo
									// virtual void SiempreDelante(const bool SD);
		   virtual void				SiempreDelante(const bool SD);


		  protected: ///////////////// -Declaraciones protegidas (Solo podran usarse en la clase heredada no desde fuera)

                                    //! Ventana padre de esta
		   DWLVentanaMDI           *Padre;
								    //! Esqueleto inicial que enlaza esta clase de la ventana MDI hija.
								    /*! Esta funci�n es el esqueleto  inicial que enlaza esta clase de la ventana MDI hija.
										    \fn			static LRESULT CALLBACK _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
										    \param[in]	HandleVentana	: Identificador de ventana.
										    \param[in]	uMsg			: Mensaje.
										    \param[in]	wParam			: Parametro1.
										    \param[in]	lParam			: Parametro2.
										    \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
								    */
		   static LRESULT CALLBACK _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
		};			     			//
		////////////////////////////// Fin DWLVentanaMDIChild

    };
};

#endif
