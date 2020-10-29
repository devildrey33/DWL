#ifndef DWL_BASEWND
#define DWL_BASEWND

#include "DWL.h"
#include <vector>

//! Definicion para centrar la ventana
#define DWL_CENTRADO				-99
//! Macro para obtener la coordenada X de un LPARAM
#ifndef GET_X_LPARAM
	#define GET_X_LPARAM(lp)			((int)(short)LOWORD(lp))
#endif
//! Macro para obtener la coordenada Y de un LPARAM 
#ifndef GET_Y_LPARAM
	#define GET_Y_LPARAM(lp)			((int)(short)HIWORD(lp))
#endif





//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres Ventanas
    namespace Ventanas {
        //! Espacio de nombres Base
        namespace Base {
		    //! Clase superbase de todas las ventanas dialogos y controles.
		    class DWLBaseWnd {
		     public : //////////////////////////////// Miembros publicos

												    //! Constructor.
												    /*! Constructor.
														    \fn			DWLBaseWnd(void);
														    \return		No devuelve nada.
												    */
												    DWLBaseWnd(void);

												    //! Destructor.
												    /*! Destructor.
														    \fn		   ~DWLBaseWnd(void);
														    \return		No devuelve nada.
												    */
			 virtual		    			       ~DWLBaseWnd(void);

												    //! Función para mostrar / ocultar la ventana / control.
												    /*! Esta función muestra / oculta la ventana / control.
														    \fn			virtual void Visible(const bool nMostrar);
														    \param[in]	nMostrar : True para mostrar la ventana / control, false para ocultarlo.
														    \return		No devuelve nada.
												    */
		     virtual void					        Visible(const bool nMostrar);

												    //! Función que retorna si la ventana / control es visible.
												    /*!	Esta funcion devuelve si la ventana / control es visible.
														    \fn			BOOL Visible(void);
														    \return		Devuelve TRUE si la ventana / control es visible, FALSE en caso contrario.
												    */
		     BOOL					        	    Visible(void);

												    //! Función para activar / desactivar la ventana / control.
												    /*!	Esta función activa / desactiva la ventana / control.
														    \fn			void Activado(const bool nActivar);
														    \param[in]	nActivar	: Parametro en el que especificaremos si queremos activar o desactivar la ventana / control.
														    \return		No devuelve nada.
												    */
		     virtual void					        Activado(const bool nActivar);

												    //! Función que retorna si la ventana / control esta activado.
												    /*!	Esta funcion devuelve si la ventana / control esta activado.
														    \fn			virtual BOOL Activado(void);
														    \return		Devuelve TRUE si la ventana / control esta activado, FALSE en caso contrario.
												    */
		     virtual BOOL				            Activado(void);

												    //! Función que asigna el foco a esta ventana / control.
												    /*!	Esta funcion asigna el foco a esta ventana / control.
														    \fn			virtual void AsignarFoco(void);
														    \return		No devuelve nada.
												    */
		     virtual void					        AsignarFoco(void);

												    //! Función que retorna si esta ventana /control tiene el raton encima.
												    /*!	Esta funcion devuelve si esta ventana /control tiene el raton encima.
														    \fn			virtual bool Foco(void);
														    \return		Devuelve true si el raton esta encima del control / ventana, false en caso contrario.
												    */
		     virtual bool					    	Foco(void);

												    //! Función que asigna una region a esta ventana / control.
												    /*!	Esta funcion asigna una region a esta ventana / control.
														    \fn			virtual int AsignarRegion(HRGN nRegion, const BOOL nRepintar = true);
														    \param[in]	nRegion		: Region que queremos asignar a esta ventana / control.
														    \param[in]	nRepintar	: Valor en el que especificamos si se debe repintar la ventana / control.
														    \return		Devuelve 0 si la funcion ha fallado, cualquier otro numero para advertir que se ha asignado la region correctamente.
												    */
		     virtual int						    AsignarRegion(HRGN nRegion, const BOOL nRepintar = true);

												    //! Función que retorna el identificador de ventana HWND.
												    /*!	Esta funcion devuelve el identificador de ventana HWND.
														    \fn			HWND hWnd(void);
														    \return		Devuelve el HWND para esta ventana / control.
												    */
		     HWND							        hWnd(void);

												    //! Función para mover la ventana / control a la posicion y el tamaño especificados.
												    /*!	Esta función mueve la ventana / control a la posicion y tamaño especificados.
														    \fn			virtual void Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = true);
														    \param[in]	cX			: Nueva posicion X para la ventana / control.
														    \param[in]	cY			: Nueva posicion Y para la ventana / control.
														    \param[in]	cAncho		: Nuevo ancho para la ventana / control.
														    \param[in]	cAlto		: Nueva altura para la ventana / control.
														    \param[in]	cRepintar	: True para repintar la ventana / control, false para dejarlo sin repintar.
														    \return		No devuelve nada.
												    */
		     virtual void							Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = false);

												    //! Función para crear un temporizador en esta ventana / control.
												    /*!	Esta función crea un temporizador en esta ventana / control.
														    \fn			void CrearTemporizador(const UINT nID, const UINT nMiliSegundos);
														    \param[in]	nID				: ID para el temporizador.
														    \param[in]	nMiliSegundos	: Tiempo en milisegundos que pasara hasta que salte el temporizador.
														    \return		No devuelve nada.
														    \remarks	Para obtener cuando salta un temporizador debemos usaar la funcion Evento_Temporizador()
												    */
		     void					        		CrearTemporizador(const UINT nID, const UINT nMiliSegundos);

												    //! Función para eliminar un temporizador en esta ventana / control.
												    /*!	Esta función elimina un temporizador en esta ventana / control.
														    \fn			void EliminarTemporizador(const UINT nID);
														    \param[in]	nID				: ID del temporizador a eliminar.
														    \return		No devuelve nada.
												    */
		     void				        			EliminarTemporizador(const UINT nID);

												    //! Función que destruye esta ventana / control.
												    /*!	Esta funcion destruye esta ventana / control.
														    \fn			virtual BOOL Destruir(void);
														    \return		Devuelve TRUE si la operación se completo, FALSE en caso contrario.
												    */
		     virtual BOOL						    Destruir(void);

												    //! Función que asigna la opacidad para la ventana / control.
												    /*!	Esta funcion asigna la opacidad para la ventana / control.
														    \fn			void Opacidad(const BYTE nNivel);
														    \param[in]	nNivel : Nivel de opacidad (0-255)
														    \return		No devuelve nada.
														    \remarks	Función no soportada en VC6.
												    */
		     void	        						Opacidad(const BYTE nNivel);

												    //! Función que retorna la ID esta ventana / control.
												    /*!	Esta funcion devuelve la ID de esta ventana / control.
														    \fn			const int ID(void);
														    \return		Devuelve la ID de esta ventana / control.
												    */
		     virtual UINT					        ID(void);
		    protected : ////////////////////////////// Miembros protegidos

		                                            //! Función que registra la clase ventana.
		                                            /*!	Esta funcion registra la clase ventana.
				                                            \fn			ATOM RegistrarClase(const TCHAR *nNombre, HBRUSH nColorFondo, const int nIconoRecursos, WNDPROC WindowProcedureInicial);
				                                            \param[in]	nNombre					: Nombre para la clase ventana.
				                                            \param[in]	nColorFondo				: Brocha con el color del fondo de la ventana. Puede ser NULL.
				                                            \param[in]	nIconoRecursos			: ID del icono de los recursos que se asignara a la ventana. Puede ser 32512 para que se asigne el icono de la aplicación.
                                                            \param[in]  WindowProcedureInicial	: WindowProcedure estatico que enlazara con el GestorMensajes virtual
				                                            \return		Devuelve el ATOM creado con RegisterClassEx, NULL en caso de error.
		                                            */
             ATOM                                   RegistrarClase(const TCHAR *nNombre, HBRUSH nColorFondo, const int nIconoRecursos, WNDPROC WindowProcedureInicial);

												    //! Identificador para la ventana / control.
		     HWND				                   _hWnd;

												    //! Función para calcular la X o la Y de la ventana quando esta necesita ser centrada.
												    /*!	Esta funcion sirve para para calcular la X o la Y de la ventana quando esta necesita ser centrada.
														    \fn			int _CalcularCentrado(HWND chWndParent, const bool cAncho, const int cValor);
														    \param[in]	chWndParent	: HWND de la ventana que contiene esta ventana / control.
														    \param[in]	cAncho		: True para obtener el ancho centrado, false para obtener el alto centrado.
														    \param[in]	cValor		: Valor a centrar.
														    \return		Devuelve la posición centrada.
														    \remarks	Función de uso interno.
												    */
              int				        	       _CalcularCentrado(HWND chWndParent, const bool cAncho, const int cValor);
             private: //////////////////////////////// Miembros privados
                                                    // Constructor copia des-habilitado
                                                    DWLBaseWnd(const DWLBaseWnd &) : _hWnd(NULL) { };
                                                    // Operador = des-habilitado
              inline DWLBaseWnd                    &operator=(const DWLBaseWnd &) { return *this; };


		    };										//
		    ////////////////////////////////////////// Fin BaseWnd

			





		    // Desmarcar sta linea para activar el modo debug que imprime datos por el output
		    // #define DWL_LISTATABULADORES_DEBUG

		    //! Clase que controla las tabulaciones dentro de una ventana / control.
		    class DWLListaTabuladores {
		    public: ////////////////////////// Miembros Publicos

										    //! Constructor.
										    /*! Constructor.
											    \fn			DWLListaTabuladores(void);
											    \return		No devuelve nada.
										    */
										    DWLListaTabuladores(void);

										    //! Destructor.
										    /*! Destructor.
											    \fn			~DWLListaTabuladores(void);
											    \return		No devuelve nada.
										    */
									       ~DWLListaTabuladores(void);

										    //! Función que agrega un control a la lista.
										    /*!	Esta funcion agrega un control a la lista.
												    \fn			void AgregarControl(DWLBaseWnd *nControl);
												    \param[in]	nControl : Clase DWLBaseWnd que queremos agregar a la lista de tabulaciones.
												    \return		No devuelve nada.
										    */
		     void							AgregarControl(DWLBaseWnd *nControl);

                                            //! Función que asigna el foco al siguiente control de la lista.
										    /*!	Esta funcion asigna el foco al siguiente control de la lista.
												    \fn			void Siguiente(void);
												    \return		No devuelve nada.
										    */
		     void							Siguiente(void);

                                            //! Función que asigna el foco al anterior control de la lista.
										    /*!	Esta funcion asigna el foco al anterior control de la lista.
												    \fn			void Anterior(void);
												    \return		No devuelve nada.
										    */
		     void							Anterior(void);

										    //! Función que devuelve la posicion del control especificado dentro de la lista.
										    /*!	Esta funcion devuelve la posicion del control especificado dentro de la lista.
												    \fn			int ObtenerPosicion(DWLBaseWnd *bControl);
												    \param[in]	bControl : Clase DWLBaseWnd de la que queremos saber la posicion dentro de la lista
												    \return		Devuelve la posicion de la lista. En caso de no existir devuelve -1.
										    */
		     int						    ObtenerPosicion(DWLBaseWnd *bControl);

										    //! Función que cambia la posicion del control especificado dentro de la lista.
										    /*!	Esta funcion cambia la posicion del control especificado dentro de la lista.
												    \fn			void CambiarPosicion(DWLBaseWnd *bControl, const size_t nPos)
												    \param[in]	bControl	: Clase DWLBaseWnd de la que queremos mover dentro de la lista
												    \param[in]	nPos		: Nueva posicion dentro de la lista
												    \return		No devuelve nada.
												    \remarks	FUNCIÓN PENDIENTE POR PROGRAMAR.
										    */
		     void							CambiarPosicion(DWLBaseWnd *bControl, const size_t nPos);

										    //! Función que borra la lista de tabulaciones.
										    /*!	Esta funcion borra la lista de tabulaciones.
												    \fn			void BorrarLista(void);
												    \return		No devuelve nada.
										    */
		     void							BorrarLista(void);

										    //! Función que borra un control de la lista de tabulaciones.
										    /*!	Esta funcion borra un control de la lista de tabulaciones.
												    \fn			void BorrarControl(DWLBaseWnd *bControl);
												    \param[in]	bControl : Clase DWLBaseWnd que queremos eliminar de la lista de tabulaciones.
												    \return		No devuelve nada.
										    */
		     void							BorrarControl(DWLBaseWnd *bControl);

										    //! Función que asigna el indice de la tabulacion.
										    /*!	Esta funcion asigna el indice de la tabulacion.
												    \fn			void AsignarNuevaPosicion(DWLBaseWnd *bControl);
												    \param[in]	bControl : Clase DWLBaseWnd que queremos establecer como actual.
												    \return		No devuelve nada.
										    */
		     void							AsignarNuevaPosicion(DWLBaseWnd *bControl);
		    private: ///////////////////////// Miembros privados

										    //! Vector que contiene todos los controles que se pueden tabular
		     std::vector<DWLBaseWnd *>	   _ListaControles;

										    //! Posicion actual del foco en la lista
		     size_t						   _Posicion;
		    };								//
		    //////////////////////////////////

        };
    };
};





#endif
