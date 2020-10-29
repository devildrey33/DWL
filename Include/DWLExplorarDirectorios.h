//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DWLExplorarDirectorios.h																														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Descripción :																																//
//					Este control se utiliza para buscar un directorio en el ordenador o en red													//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Este archivo contiene varias clases descritas a continuacion :																				//
// - DWLExplorarDirectorios			:	Clase que hereda de DWLArbolEx_Nucleo y DWLControlEx para crear un control destinado a buscar 		//
//										directorios.																							//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
// Archivo creado por devildrey33 el dia 10/11/2009	para http://www.devildrey33.es																//
// Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :		//
//  http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																		//
//  http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)																//
//  http://www.softcatala.cat/wiki/GPL3		 (Catalá, traduccion no oficial)																	//
//																																				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Version 0.25	 (FASE ALPHA)																													//
// Ultima modificación : 02/11/2009																												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// POR HACER : 
// -Sacar los textos de las unidades de windows, como por ejemplo el de la disquetera.
// -Mirar porque cada icono cargado me consume 3 objetos gdi.
// -Testear el control, y utilizarlo en proyectos para ver que metodos utiles incluir.


#ifndef DWL_EXPLORARDIRECTORIOS_H
#define DWL_EXPLORARDIRECTORIOS_H

#include ".\DWLArbolEx\DWLArbolEx_Nucleo.h"
#include "DWLControlEx.h"

// 10/11/2009

//Mpr.lib
//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres ControlesEx
	namespace ControlesEx {

		class DWLExplorarDirectorios_Estilos {
		  public:
							DWLExplorarDirectorios_Estilos(void) : MostrarDirectoriosOcultos(false), DesactivarDirectoriosWindows(true) { };
			bool			MostrarDirectoriosOcultos;
			bool            DesactivarDirectoriosWindows;
		};

        //! Clase para los nodos de DWLExplorarDirectorios
		class DWLExplorarDirectorios_Nodo : public DWLArbolEx_Nodo {
			public: // Miembros publicos

					//! Constructor.
					/*!	Constructor por defecto.
							\fn		DWLExplorarDirectorios_Nodo(void);
							\return	No devuelve nada.
					*/
					DWLExplorarDirectorios_Nodo(void) { };

					//! Destructor.
					/*!	Destructor.
							\fn		~DWLExplorarDirectorios_Nodo(void);
							\return	No devuelve nada.
					*/
			       ~DWLExplorarDirectorios_Nodo(void) { };

                    //! Tipo de nodo
			int		Tipo;
			bool    Activado;
		};          //
        ////////////// FIN DWLExplorarDirectorios_Nodo

		class DWLExplorarDirectorios_Sugerencia {
		  public :
							DWLExplorarDirectorios_Sugerencia(void) : Icono(0), EsDirectorio(false), Negrita(true) { };
			DWL::DWLString	Nombre;
			DWL::DWLString	Padre;
			UINT            Icono;
			bool            EsDirectorio;
			bool            Negrita;
		};

        //! Clase que hereda de ArbolEx_Nucleo para formar un control para explorar directorios
        class DWLExplorarDirectorios : public DWL::ControlesEx::Base::DWLControlEx, public DWLArbolEx_Nucleo {
		 public : //////////////////////////// Mimebros publicos

											//! Constructor.
											/*!	Constructor por defecto.
													\fn		DWLExplorarDirectorios(void);
													\return	No devuelve nada.
											*/
											DWLExplorarDirectorios(void);

											//! Destructor.
											/*!	Destructor.
													\fn		~DWLArbolEx(void);
													\return	No devuelve nada.
											*/
								           ~DWLExplorarDirectorios(void);

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
		  HWND								CrearExplorarDirectorios(UINT Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const bool cPintarBorde);

											//! Función que conecta un objeto DWLExplorarDirectorios de un dialogo.
											/*!	Esta funcion conecta un objeto DWLExplorarDirectorios de un dialogo.
													\fn			HWND ConectarExplorarDirectorios(HWND hWndParent, const int cID, const bool cPintarBorde);
                                                    \param[in]  hWndParent   : hWnd de la ventana padre.
                                                    \param[in]  cID          : ID del control.
                                                    \param[in]  cPintarBorde : Pintar borde redondeado al control
													\return		Devuelve el HWND del control DWLExplorarDirectorios, o NULL si ha sucedido un error.
                                                    \remarks    Esta función solo debe usarse con controles que se creen durante la creación del dialogo, si esta clase no pertenece a un dialogo, o se va a crear dinamicamente, no debes usar esta función.
											*/
		  HWND								ConectarExplorarDirectorios(HWND hWndParent, const int cID, const bool cPintarBorde);

											//! Función que destruye este DWLExplorarDirectorios.
											/*!	Esta funcion destruye el DWLExplorarDirectorios.
													\fn			const BOOL Destruir(void);
													\return		Devuelve TRUE si la operacion se completo, FALSE en caso contrario.
											*/
		  BOOL						        Destruir(void);

											//! Función que actualiza la lista de directorios.
											/*!	Esta funcion actualiza la lista de directorios.
													\fn			void ActualizarDirectorios(void);
													\return		No devuelve nada.
											*/
		  void								ActualizarDirectorios(void);

											//! Función que añade una sugerencia al principio.
											/*!	Esta funcion añade una sugerencia al principio.
													\fn			DWLExplorarDirectorios_Nodo *AgregarSugerencia(const TCHAR *nNombre, const bool EsDirectorio, const UINT nIcono = 0, DWLExplorarDirectorios_Nodo *Padre = NULL, const bool nNegrita = false);
													\paran[in]  nNombre    : Directorio válido
													\param[in]  TituloRoot : Nombre del nodo root de la sugerencia (Si es NULL la sugerencia no tendrá padre)
													\param[in]  IconoRoot  : Icono para el nodo del titulo.
													\return		Devuelve la clase DWLExplorarDirectorios_Nodo creada.
											*/
//		 DWLExplorarDirectorios_Nodo       *AgregarSugerencia(const TCHAR *Path, const TCHAR *TituloRoot, const UINT IconoRoot);
		 DWLExplorarDirectorios_Nodo       *AgregarSugerencia(const TCHAR *nNombre, const bool EsDirectorio = true, DWLExplorarDirectorios_Nodo *Padre = NULL, const UINT nIcono = 0, const bool nNegrita = false);
		 void								EliminarSugerencias(void);

											//! Función para activar / desactivar el control DWLExplorarDirectorios.
											/*!	Esta funcion activa / desactiva el control DWLExplorarDirectorios.
													\fn			inline virtual void Activado(const bool nActivar, const bool nRepintar = true);
													\param[in]	nActivar	: Parametro en el que especificaremos si queremos activar o desactivar el control.
													\param[in]	nRepintar	: Parametro en el que especificaremos si queremos repintar el control.
													\return		No devuelve nada.
											*/
		 inline virtual void				Activado(const bool Activar, const bool nRepintar = true) {
												_BarraScrollEx_Activado = Activar;
												EnableWindow(_hWnd, Activar);
												if (nRepintar == true) Repintar(true);
											};

											//! Función que retorna si el control esta activado.
											/*!	Esta funcion devuelve si el control esta activado.
													\fn			inline virtual BOOL Activado(void);
													\return		Devuelve TRUE si el control esta activado, FALSE en caso contrario.
											*/
		 inline virtual BOOL			    Activado(void) {
												return _BarraScrollEx_Activado;
											};

											//! Función que retorna el alto para los nodos del control DWLExplorarDirectorios en pixeles.
											/*!	Esta funcion devuelve el alto para los nodos del control DWLExplorarDirectorios en pixeles.
													\fn			inline const int AltoLinea(void);
													\return		Devuelve la altura de los nodos en pixeles.
											*/
		 inline const int				    AltoLinea(void) {
												return _ArbolEx_AltoLinea;
											};

											//! Función para asignar los pixeles que tendra de alto cada nodo.
											/*!	Esta funcion asigna los pixeles que tendra de alto cada nodo.
													\fn			void AltoLinea(const int nAlto);
													\param[in]	nAlto	: Nueva altura en pixeles para los nodos.
													\return		No devuelve nada.
											*/
		 void				                AltoLinea(const int nAlto);

											//! Función que repinta todo el control DWLExplorarDirectorios.
											/*!	Esta función repinta todo el control incluyendo barras de scroll y botones extra.
													\fn			void Repintar(const bool Forzar = false);
													\param[in]	Forzar : True para forzar el repintado, false para que la funcion decida si repintar.
													\return		No devuelve nada.
													\remarks	Cuando Forzar es false, esta función mira si ha cambiado algun estado interno,
																y de ser asi repinta el control, en caso contrario no hace nada.
											*/
		 void                               Repintar(const bool Forzar = false);

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
		 void								Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = true);

											//! Función que pinta todo el control cuado se recibe un mensaje WM_PAINT.
											/*!	Esta función pinta el control cuando se recibe un mensaje WM_PAINT.
													\fn			LRESULT Evento_Pintar(HDC hDC);
													\param[in]	hDC	: hDC donde se pintara todo el control.
                                                    \param[in]  PS  : Estructura que contiene los datos del pintado.
											        \return		Si re-emplazas esta funcion debes retornar 0.
											*/
		 LRESULT                            Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);

											//! Función predefinida del mensaje WM_MOUSEWHEEL.
											/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEWHEEL.
													\fn			virtual LRESULT Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey);
													\param[in]	Delta	: Valor de desplazamiento del mouse.
													\param[in]	cX		: Coordenada X.
													\param[in]	cY		: Coordenada Y.
													\param[in]	VirtKey	: Tecla virtual presionada.
											        \return		Si re-emplazas esta funcion debes retornar 0.
											*/
		 virtual LRESULT                    Evento_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey);

											//! Función predefinida del mensaje WM_MOUSEMOVE.
											/*!	Esta función es la encargada de procesar los mensajes WN_MOUSEMOVE.
													\fn			virtual LRESULT Evento_Mouse_Movimiento(const int cX, const int cY, const UINT wParam);
													\param[in]	cX		: Coordenada X del mouse.
													\param[in]	cY		: Coordenada Y del mouse.
													\param[in]	Param	: Teclas extendidas presionadas.
											        \return		Si re-emplazas esta funcion debes retornar 0.
											*/
		 virtual LRESULT                    Evento_Mouse_Movimiento(const int cX, const int cY, const UINT Param);

											//! Función predefinida del mensaje WM_*BUTTONDOWN (Virtual)
											/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONDOWN.
													\fn			virtual LRESULT Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param)
													\param[in]	Boton	: Boton presionado.
													\param[in]	cX		: Coordenada X del mouse.
													\param[in]	cY		: Coordenada Y del mouse.
													\param[in]	wParam	: Teclas extendidas presionadas.
											        \return		Si re-emplazas esta funcion debes retornar 0.
											*/
		 virtual LRESULT                    Evento_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT Param);

											//! Función predefinida del mensaje WM_*BUTTONUP (Virtual)
											/*!	Esta función es la encargada de procesar los mensajes WN_*BUTTONUP.
													\fn			virtual LRESULT Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);
													\param[in]	Boton	: Boton presionado.
													\param[in]	cX		: Coordenada X del mouse.
													\param[in]	cY		: Coordenada Y del mouse.
													\param[in]	Param	: Teclas extendidas presionadas.
											        \return		Si re-emplazas esta funcion debes retornar 0.
											*/
		 virtual LRESULT                    Evento_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT Param);

											//! Función que recibe cuando el mouse se va del control
											/*!	Esta función es la encargada de procesar los mensajes WN_MOUSELEAVE.
													\fn			virtual LRESULT Evento_Mouse_Saliendo(void);
											        \return		Si re-emplazas esta funcion debes retornar 0.
											*/
		 virtual LRESULT			        Evento_Mouse_Saliendo(void);

											//! Función predefinida del mensaje WM_KEYDOWN (Virtual)
											/*!	Esta función es la encargada de procesar los mensajes WM_KEYDOWN.
													\fn			virtual LRESULT Evento_Teclado_TeclaPresionada(const UINT Tecla, const UINT Repeticion, const UINT Param);
													\param[in]	Caracter   : Tecla virtual soltada.
													\param[in]	Repeticion : Repeticiones de la tecla
													\param[in]	Param	   : Teclas extendidas soltadas.
											        \return		Si re-emplazas esta funcion debes retornar 0.
											*/
		 virtual LRESULT                    Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Params);

											//! Función predefinida del mensaje WM_KEYUP (Virtual)
											/*!	Esta función es la encargada de procesar los mensajes WM_KEYUP.
													\fn			virtual LRESULT Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Param);
													\param[in]	Caracter   : Tecla virtual soltada.
													\param[in]	Repeticion : Repeticiones de la tecla
													\param[in]	Param	   : Teclas extendidas soltadas.
											        \return		Si re-emplazas esta funcion debes retornar 0.
											*/
		 virtual LRESULT                    Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Params);

											//! Función que enlaza el mensaje WM_TIMER con el control.
											/*! Esta función enlaza el mensaje WM_TIMER con el control.
													\fn			void Evento_Temporizador(const int cID);
													\param[in]	cID : ID del temporizador.
													\return		No devuelve nada.
													\remarks	Si re-emplazas esta funcion debes retornar 0.
											*/
		 LRESULT							Evento_Temporizador(const UINT cID);

											//! Función que procesa el mensaje WM_SETFOCUS
											/*! Esta funcion es la encargada de procesar el mensaje WM_SETFOCUS
													\fn			virtual LRESULT Evento_Foco_Obtenido(HWND FocoAnterior);
													\param[in]	FocoAnterior	: HWND de la ventana que tenia el foco antes que esta.
											        \return		Si re-emplazas esta funcion debes retornar 0.
											*/
		 virtual LRESULT					Evento_Foco_Obtenido(HWND FocoAnterior);

											//! Función que procesa el mensaje WM_KILLFOCUS
											/*! Esta funcion es la encargada de procesar el mensaje WM_KILLFOCUS
													\fn			virtual LRESULT Evento_Foco_Perdido(HWND NuevoFoco);
													\param[in]	NuevoFoco	: HWND de la ventana que recibira el foco despues de esta.
											        \return		Si re-emplazas esta funcion debes retornar 0.
											*/
		 virtual LRESULT					Evento_Foco_Perdido(HWND NuevoFoco);

											//! Función que explora un directorio.
											/*! Esta funcion explora un directorio.
													\fn			void ObtenerPath(DWLExplorarDirectorios_Nodo *NodoPath, DWLString &PathFinal);
													\param[in]	NodoPath  : Nodo en el que se añadiran las nuevas entradas.
													\param[in]	PathFinal : Path final de la ruta a explorar.
											        \return		No devuelve nada.
											*/
		 void								ObtenerPath(DWLExplorarDirectorios_Nodo *NodoPath, DWLString &PathFinal);

										    //! Función que carga un icono de un ejecutable.
										    /*! Esta funcion carga un icono de un ejecutable.
												    \fn			int CargarIcono(const TCHAR *Path);
												    \param[in]	Path : HWND de la ventana que recibira el foco despues de esta.
										            \return		Devuelve el indice del icono en la lista de iconos.
										    */
		 int							    CargarIcono(const TCHAR *Path);

		 DWLExplorarDirectorios_Estilos		Estilos;

		protected :	////////////////////////// Miebros protegidos

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
		 DWLExplorarDirectorios_Nodo       *AgregarNodo(const int nTipo, DWLArbolEx_Nodo *nPadre, const int nIcono, const TCHAR *nTexto, const int PosicionNodo = -1, const bool nActivado = true);

											//! Función que enumera todos los dispositivos de la red.
											/*! Esta funcion enumera todos los dispositivos de la red.
													\fn			const BOOL EnumerarRed(LPNETRESOURCE lpnrLocal, DWLArbolEx_Nodo *nNodo);
													\param[in]	lpnrLocal : Puntero a estructuras enumeradas.
													\param[in]	nNodo     : Nodo en el que se añadiran las enumeraciones.
											        \return		Devuelve TRUE si todo va bioen, FALSE en caso de error.
											*/
		 BOOL							    EnumerarRed(LPNETRESOURCE lpnrLocal, DWLArbolEx_Nodo *nNodo);

											//! Función para la depuración en la obtención de directorios.
											/*! Esta funcion es para la depuración en la obtención de directorios.
													\fn			void DisplayStruct(int i, LPNETRESOURCE lpnrLocal);
													\param[in]	i         : Numero de entrada.
													\param[in]	lpnrLocal : Puntero a estructuras enumeradas.
											        \return		No devuelve nada.
											*/
		 void								DisplayStruct(int i, LPNETRESOURCE lpnrLocal);

											//! Función virtual que es llamada cuando se expande un DWLArbolEx_Nodo.
											/*! Esta función virtual es llamada cuando se expande un DWLArbolEx_Nodo.
													\fn			virtual void ArbolEx_Evento_Expandir(DWLArbolEx_Nodo *nNodoExpandido);
													\param[in]	nNodo	: DWLArbolEx_Nodo que se va a expandir.
													\return		No devuelve nada.
													\remarks    Esta función se usa principalmente si estamos creando el arbol al vuelo.
																Por ejemplo con una lista de directorios que se va rellenando cuando abres un directorio.
													\sa			ArbolEx_PintarNodo()
											*/
		 void								ArbolEx_Evento_Expandir(DWLArbolEx_Nodo *nNodoExpandido);

											//! Función que agrega un directorio al arbol.
											/*! Esta funcion agrega un directorio al arbol.
													\fn			void AgregarDirectorio(DWLExplorarDirectorios_Nodo *nNodoExpandido, const TCHAR *PathBusqueda);
													\param[in]	nNodoExpandido : Nodo en el que se añadiran las nuevas entradas.
													\param[in]	PathBusqueda   : Path final de la ruta a explorar.
											        \return		No devuelve nada.
											*/
		 void								AgregarDirectorio(DWLExplorarDirectorios_Nodo *nNodoExpandido, const TCHAR *PathBusqueda);

											//! Función que hace una pre-exploracion para determinar si el directorio tiene mas directorios dentro.
											/*! Esta funcion hace una pre-exploracion para determinar si el directorio tiene mas directorios dentro.
													\fn			const bool TieneDirectorios(const TCHAR *Path);
													\param[in]	Path : Path a explorar.
											        \return		Devuelve true si hay directorios dentro, false en caso contrario.
											*/
		 bool							    TieneDirectorios(const TCHAR *Path);

											//! Función que carga un icono de un CSIDL.
											/*! Esta funcion carga un icono de un CSIDL.
													\fn			int CargarIcono(const int CSIDL);
													\param[in]	CSIDL : ID del icono correspondiente.
											        \return		Devuelve el indice del icono en la lista de iconos.
											*/
		 int							    CargarIcono(const int CSIDL);

                                            //! Path del escritorio
		 DWLString							PathEscritorio;

                                            //! Path de mis documentos
		 DWLString							PathMisDocumentos;

                                            //! ID actual
		 static int						   _IDActual;

		 std::vector<DWLExplorarDirectorios_Sugerencia>       _Sugerencias;

											//! Esqueleto para los mensajes del control.
											/*! Esta función es el esqueleto para los mensajes del control.
													\fn			LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
													\param[in]	uMsg	: Mensaje.
													\param[in]	wParam	: Parametro1.
													\param[in]	lParam	: Parametro2.
													\return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
													\remarks	Esta función es el esqueleto del control por donde pasaran todos sus mensajes.
											*/
		 LRESULT CALLBACK					GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
		};
        ////////////////////////////////////// FIN DWLExplorarDirectorios
	};
};

#endif
