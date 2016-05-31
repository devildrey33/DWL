#ifndef DVENTANA_H
    #define DVENTANA_H

    #include "DEventosPadre.h"
     
    namespace DWL {


        class DVentana : public DEventosPadre<LRESULT> {
		    public : ///////////////////////////// -Declaraciones publicas
			  virtual const DEnum_Objeto		Objeto_Tipo(void) { return DEnum_Objeto::DEnum_Objeto_Ventana; };

								                //! Constructor  
                                                /*! Constructor por defecto.
									                    \fn			DVentana(void);
                                                        \return     No devuelve nada
                                                */
                                                DVentana(void) : DEventosPadre<LRESULT>() { };

								                //! Destructor  
                                                /*! Destructor por defecto.
									                    \fn		   ~DVentana(void);
                                                        \return     No devuelve nada
                                                */
								               ~DVentana(void);

								                //! Función que crea la ventana.
								                /*!	Esta función crea la ventana.
										                \fn			HWND Crear(const TCHAR *nNombre, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, DWORD nEstilos, DWORD nEstilosExtendidos = NULL, HMENU nMenu= NULL, HBRUSH nColorFondo = NULL, const int nIconoRecursos = 32512);
										                \param[in]	nNombre				: Nombre para la clase ventana.
										                \param[in]	nTexto				: Titulo para la ventana.
										                \param[in]	cX					: Posicion X. Puedes especificar DWL_CENTRADO para que se centre.
										                \param[in]	cY					: Posicion Y. Puedes especificar DWL_CENTRADO para que se centre.
										                \param[in]	cAncho				: Ancho de la ventana.
										                \param[in]	cAlto				: Alto del la ventana.
										                \param[in]	nEstilos			: Estilos validos para ventanas (WS_OVERLAPPED | WS_VISIBLE | etc..)
										                \param[in]	nEstilosExtendidos	: Estilos extendidos validos.
										                \param[in]	nColorFondo			: Brocha con el color del fondo de la ventana. Puede ser NULL.
										                \param[in]	nMenu				: Menu para la ventana, NULL si no hay menu. NOTA a diferencia de los controles creados con CreateWindow este parametro NO DEBE UTILIZARSE para especificar la ID de la ventana.
										                \param[in]	nIconoRecursos		: ID del icono de los recursos que se asignara a la ventana. Puede ser 32512 para que se asigne el icono de la aplicación.
										                \return		Devuelve el HWND de la ventana. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para ver el error.
								                */
            HWND			                    Crear(const TCHAR *nNombre, const TCHAR *nTexto, const int cX, const int cY, const int cAncho, const int cAlto, DWORD nEstilos, DWORD nEstilosExtendidos = NULL, HMENU nMenu = NULL, HBRUSH nColorFondo = NULL, const int nIconoRecursos = 32512);

							                    //! Función virtual para determinar si la ventana es maximizable.
							                    /*! Esta función virtual determina si la ventana es maximizable.
									                    \fn			virtual void Maximizable(const bool nMax);
									                    \param[in]	nMax : Especifica true para que la ventana sea maximizable, false para lo contrario.
									                    \return		Esta función no devuelve nada.
							                    */
		    virtual void                        Maximizable(const bool nMax);

							                    //! Función virtual que nos dice si la ventana es maximizable.
							                    /*! Esta función virtual nos dice si la ventana es maximizable.
									                    \fn			virtual const bool Maximizable(void);
									                    \return		Devuelve true si la ventana es maximizable, false en caso contrario.
							                    */
		    virtual const bool                  Maximizable(void);

							                    //! Función que nos dice si la ventana esta maximizada en este momento.
							                    /*! Esta función nos dice si la ventana esta maximizada en este momento.
									                    \fn			const bool Maximizada(void);
									                    \return		Devuelve true si la ventana esta maximizada, false en caso contrario.
							                    */
            const bool				            Maximizada(void);

							                    //! Función virtual para determinar si la ventana es minimizable.
							                    /*! Esta función virtual determina si la ventana es minimizable.
									                    \fn			virtual void Minimizable(const bool nMin);
									                    \param[in]	nMin : Especifica true para que la ventana sea minimizable, false para lo contrario.
									                    \return		Esta función no devuelve nada.
							                    */
		    virtual void                        Minimizable(const bool nMin);

							                    //! Función virtual que nos dice si la ventana es minimizable.
							                    /*! Esta función virtual nos dice si la ventana es minimizable.
									                    \fn			virtual const bool Minimizable(void);
									                    \return		Devuelve true si la ventana es minimizable, false en caso contrario.
							                    */
		    virtual const bool                  Minimizable(void);

							                    //! Función que nos dice si la ventana esta minimizada en este momento.
							                    /*! Esta función nos dice si la ventana esta minimizada en este momento.
									                    \fn			const bool Minimizada(void);
									                    \return		Devuelve true si la ventana esta minimizada, false en caso contrario.
							                    */
		    const bool				            Minimizada(void);

							                    //! Función para posicionar la ventana siempre delante de todas las otras ventanas.
							                    /*! Esta función posiciona la ventana siempre delante de todas las otras ventanas.
									                    \fn			virtual void SiempreDelante(const bool SD);
									                    \param[in]	SD : Especifica true para que la ventana quede siempre por delante, false para que tenga un comportamiento normal segun su coordenada Z.
									                    \return		Esta función no devuelve nada.
                                                        \remarks    Por norma las ventanas se posicionan utilizando el OrdenZ, que es un indice para determinar en que posición estan las ventanas. 
                                                                    Si por ejemplo creas dos ventanas la primera se pondra en el orden 1, y la segunda en el orden 0, 
                                                                    de forma que si se crean en cascada deberias ver la segunda ventana por delante de todo.
							                    */
		    virtual void				        SiempreDelante(const bool SD);

							                    //! Función para asignar el titulo de la ventana.
							                    /*! Esta función asigna el titulo de la ventana.
									                    \fn			virtual void Titulo(const TCHAR *Txt);
									                    \param[in]	Txt : Nuevo texto para el titulo de la ventana.
									                    \return		Esta función no devuelve nada.
							                    */
		    virtual void		   		        Titulo(const TCHAR *Txt);

							                    //! Función para obtener el titulo de la ventana.
							                    /*! Esta función obtiene el titulo de la ventana en el buffer especificado.
									                    \fn			int Titulo(TCHAR *Txt, const int TamTxt);
									                    \param[in]	Txt    : Buffer de texto para obtener el titulo.
                                                        \param[in]  TamTxt : Tamaño del buffer para el titulo.
									                    \return		Esta función devuelve 0 en caso de error. En caso de exito devuelve el numero de caracteres que contiene el titulo sin incluir el terminador NULL.
							                    */
		    int						            Titulo(TCHAR *Txt, const int TamTxt);


            virtual LRESULT                     Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);


          protected: ///////////////////////////// -Declaraciones protegidas (Solo podran usarse en la clase heredada no desde fuera)

								                //! Esqueleto inicial que enlaza esta clase con la ventana.
								                /*! Esta función es el esqueleto inicial que enlaza esta clase con la ventana.
										                \fn			static LRESULT CALLBACK _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
										                \param[in]	HandleVentana	: Identificador de ventana.
										                \param[in]	uMsg			: Mensaje.
										                \param[in]	wParam			: Parametro1.
										                \param[in]	lParam			: Parametro2.
										                \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
								                */
            static LRESULT CALLBACK            _GestorMensajes(HWND HandleVentana, UINT uMsg, WPARAM wParam, LPARAM lParam);
	    };			     			            //
	    ////////////////////////////////////////// Fin DVentana


    /*
    enum DVentana_TipoVentana {
        DEnum_TipoVentana_Popup,                // WS_POPUP
        DEnum_TipoVentana_PopupWindow,          // WS_POPUPWINDOW (WS_POPUP | WS_BORDER | WS_SYSMENU)
        DEnum_TipoVentana_Overlapped,           // WS_OVERLAPPED
        DEnum_TipoVentana_OverlappedWindow      // WS_OVERLAPPEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
    };


    class DVentana_Estilos {
      public :
        DVentana_Estilos() {
            _Visible = true;
            _Desactivada = false;
            Tipo(DEnum_TipoVentana_Popup);
        }

        void Tipo(const DVentana_TipoVentana nTipo) {
            switch (nTipo) {
                case DEnum_TipoVentana_Popup :
                    _BarraTitulo        = false;
                    _Boton_Maximizar    = false;
                    _Boton_Minimizar    = false;
                    _Boton_Cerrar       = false;
                    _Redimensionable    = false; // Modificable
                    _Borde              = false; // Modificable
                    _MenuSistema        = false; // Modificable
                    break;
                case DEnum_TipoVentana_PopupWindow :
                    _BarraTitulo        = false;
                    _Boton_Maximizar    = false;
                    _Boton_Minimizar    = false;
                    _Boton_Cerrar       = false;
                    _Redimensionable    = false; // Modificable
                    _Borde              = true;
                    _MenuSistema        = true;
                    break;
                case DEnum_TipoVentana_Overlapped :
                    _BarraTitulo        = false; // Modificable
                    _Boton_Maximizar    = false; // Modificable
                    _Boton_Minimizar    = false; // Modificable
                    _Boton_Cerrar       = false; // Modificable
                    _Redimensionable    = false; // Modificable
                    _Borde              = true;
                    _MenuSistema        = false; // Modificable
                    break;
                case DEnum_TipoVentana_OverlappedWindow :
                    _BarraTitulo        = true;
                    _Boton_Maximizar    = true;
                    _Boton_Minimizar    = true;
                    _Boton_Cerrar       = true;
                    _Redimensionable    = true;
                    _Borde              = true;
                    _MenuSistema        = true;
                    break;
            }
        }

        void BarraTitulo(const bool nBarraTitulo) {
            if (_Tipo == DEnum_TipoVentana_Overlapped) _BarraTitulo = nBarraTitulo;
        }

        void Boton_Maximizar(const bool nBoton_Maximizar) {
            if (_Tipo == DEnum_TipoVentana_Overlapped) _Boton_Maximizar = nBoton_Maximizar;
        }

        void Boton_Minimizar(const bool nBoton_Minimizar) {
            if (_Tipo == DEnum_TipoVentana_Overlapped) _Boton_Minimizar = nBoton_Minimizar;
        }

        void Boton_Cerrar(const bool nBoton_Cerrar) {
            if (_Tipo == DEnum_TipoVentana_Overlapped) _Boton_Cerrar = nBoton_Cerrar;
        }

        void Redimensionable(const bool nRedimensionable) {
            if (_Tipo != DEnum_TipoVentana_OverlappedWindow) _Redimensionable = nRedimensionable;
        }

        void Borde(const bool nBorde) {
            if (_Tipo == DEnum_TipoVentana_Popup) _Borde = nBorde;
        }

        void MenuSistema(const bool nMenuSistema) {
            if (_Tipo == DEnum_TipoVentana_Popup || _Tipo == DEnum_TipoVentana_Overlapped) _MenuSistema = nMenuSistema;
        }

        void Visible(const bool nVisible) {
            _Visible = nVisible;
        }

        void Desactivada(const bool nDesactivada) {
            _Desactivada = nDesactivada;
        }

        DWORD ObtenerEstilo(void) {
            DWORD nEstilo = 0;
            if (_Visible == true)       nEstilo = nEstilo | WS_VISIBLE;
            if (_Desactivada == true)   nEstilo = nEstilo | WS_DISABLED;
            switch (_Tipo) {
                case DEnum_TipoVentana_Popup :
                    nEstilo = nEstilo | WS_POPUP;
                    if (_Redimensionable == true)   nEstilo = nEstilo | WS_SIZEBOX;
                    if (_Borde == true)             nEstilo = nEstilo | WS_BORDER;
                    if (_MenuSistema == true)       nEstilo = nEstilo | WS_SYSMENU;
                    break;
                case DEnum_TipoVentana_PopupWindow :
                    nEstilo = nEstilo | WS_POPUPWINDOW;
                    if (_Redimensionable == true)   nEstilo = nEstilo | WS_SIZEBOX;
                    break;
                case DEnum_TipoVentana_Overlapped :
                    nEstilo = nEstilo | WS_OVERLAPPED;
                    if (_BarraTitulo == true)       nEstilo = nEstilo | WS_CAPTION;
                    if (_Boton_Maximizar == true)   nEstilo = nEstilo | WS_MAXIMIZEBOX;
                    if (_Boton_Minimizar == true)   nEstilo = nEstilo | WS_MINIMIZEBOX;
                    // boton cerrar.....
                    if (_Redimensionable == true)   nEstilo = nEstilo | WS_SIZEBOX;
                    if (_MenuSistema == true)       nEstilo = nEstilo | WS_SYSMENU;
                    break;
                case DEnum_TipoVentana_OverlappedWindow :
                    nEstilo = nEstilo | WS_OVERLAPPEDWINDOW;
                    break;
            }
            return nEstilo;
        }

      protected :

        bool _BarraTitulo;           // Si no hay barra de titulo no hay botones max, min, cerrar. Si se añade barra de titulo el borde viene incluido
        bool _Boton_Maximizar;
        bool _Boton_Minimizar;
        bool _Boton_Cerrar;
        bool _Redimensionable;       // Si es redimensionable tiene borde por cojones
        bool _Borde;                 // Solo funciona con el titpo Popup, el overlapped ya lo tiene por defecto
        bool _MenuSistema;

        bool _Visible;
        bool _Desactivada;
        DVentana_TipoVentana _Tipo;  // Dependiendo del tipo algunos valores son omitidos
    };*/

};

#endif // DVENTANA_H
