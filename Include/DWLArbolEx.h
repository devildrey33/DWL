/*! \file DWLArbolEx.h
	\brief		Archivo que contiene las definiciones para las clases del ArbolEx.


	\details	Este control simula un TreeView de windows, con algunas innovaciones como pueden ser la sub-seleccion, tooltips propios facilmente configurables, scrolls que pueden contener botones extra, y ademas tiene una apariencia totalmente configurable.																												\n
				<table border = 0 align ='right'><tr><td> \image html ArbolEx.jpg </td></tr></table>
																																											\n
				\section Clases_Sec		Este archivo requiere varias clases descritas a continuación  :
				 - DWL::ControlesEx::DWLArbolEx_Estilos	:																																																		\n
				   Clase que contiene todos los estilos necesarios para el ArbolEx.																																										        \n
				   Puedes modificar cualquier estilo, una vez modificado deberas llamar a ArbolEx_ActualizarTodo para que los cambios sean procesados. Hay que remarcar que si cambias la fuente tendras que usar tambien ActualizarAnchosTexto().	            \n
                                                                                                                                                                                                                                                                \n
				 - DWL::ControlesEx::DWLArbolEx_Colores	:																																																		\n
				   Clase que enlaza los colores a la configuracion del skin por defecto.																																										\n
				   Puedes modificar cualquier color de esta clase, solo deberas repintar el arbol al terminar.																																					\n
																																																																\n
				 - DWL::ControlesEx::DWLArbolEx_ColoresNodo	:																																																	\n
				   Clase que enlaza los colores del nodo a la configuracion skin por defecto.																																									\n
																																																																\n
				 - DWL::ControlesEx::DWLArbolEx_ParametrosClick	:																																																\n
				   Clase utilizada internamente para pasar los datos de un click a la ventana padre.																																							\n
																																																																\n
				 - DWL::ControlesEx::DWLArbolEx_TerminarLabelEdit :																																																\n
				   Clase utilizada internamente para pasar los datos de una edicion a la ventana padre.																																							\n
																																																																\n
				 - DWL::ControlesEx::DWLArbolEx_Nodo :																																																			\n
				   Clase que contiene los datos de un nodo (Puede ser heredada).																																												\n
																																																																\n
				 - DWL::ControlesEx::DWLArbolEx_Nucleo :																																																		\n
				   Clase que contiene las funciónes basicas para pintar y controlar los eventos del arbol.																																						\n
				   Esta clase se ha creado de forma que puede compartir un control con otra clase, aunque es poco probable que se requiera compartir un arbol con otro control, es muy interesante la posibilidad de poder pintar el control en cualquier hDC.  \n
																																																															    \n
				 - DWL::ControlesEx::DWLArbolEx :																																																				\n
				   Clase que hereda de DWLArbolEx_Nucleo y lo enlaza a un control para el solo.																																									\n
				   Esta clase es la que deberiamos usar para crear un arbol estandar sin complicaciones.																																						\n

																																																																\n
	\author		devildrey33
	\date		Creado el [20/02/2005], ultima modificación el [29/05/2010]

	\remarks
				Archivo creado por devildrey33 para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

	\todo		Revisar implementación del teclado, en especial teclas con control o shift.

*/




#ifndef DWL_ARBOLEX_H
#define DWL_ARBOLEX_H

//#define DWL_ARBOLEX_DEBUG // Descomenta esta linea para que se muestren mensajes de debug para este control

#include ".\DWLArbolEx\DWLArbolEx_Nucleo.h"
#include "DWLControlEx.h"


//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres ControlesEx
	namespace ControlesEx {

		//! Clase que une DWLControlEx con DWLArbolEx_Nucleo, para formar un control ArbolEx
        class DWLArbolEx : public DWL::ControlesEx::Base::DWLControlEx, public DWLArbolEx_Nucleo {
		public: ////////////////////////////// Miembros publicos

											//! Constructor.
											/*!	Constructor por defecto.
													\fn		DWLArbolEx(void);
													\return	No devuelve nada.
											*/
											DWLArbolEx(void);

											//! Destructor.
											/*!	Destructor.
													\fn		~DWLArbolEx(void);
													\return	No devuelve nada.
											*/
										   ~DWLArbolEx(void);

											//! Función que retorna si esta ventana tiene el raton encima.
											/*!	Esta funcion devuelve si esta ventana tiene el raton encima.
													\fn			virtual bool Foco(void);
													\return		Devuelve true si el raton esta encima del control, false en caso contrario.
											*/
		 virtual bool					    Foco(void);

											//! Función para activar / desactivar el ArbolEx.
											/*!	Esta funcion activa / desactiva el ArbolEx.
													\fn			inline virtual void Activado(const bool nActivar, const bool nRepintar = true);
													\param[in]	nActivar	: Parametro en el que especificaremos si queremos activar o desactivar el ArbolEx.
													\param[in]	nRepintar	: Parametro en el que especificaremos si queremos repintar el ArbolEx.
													\return		No devuelve nada.
											*/
		 inline virtual void				Activado(const bool nActivar, const bool nRepintar = true) {
												_BarraScrollEx_Activado = nActivar;
												EnableWindow(_hWnd, nActivar);
												if (nRepintar == true) Repintar(true);
											};

											//! Función que retorna si el ArbolEx esta activado.
											/*!	Esta funcion devuelve si el ArbolEx esta activado.
													\fn			inline virtual BOOL Activado(void);
													\return		Devuelve TRUE si el ArbolEx esta activado, FALSE en caso contrario.
											*/
		 inline virtual BOOL			    Activado(void) {
												return _BarraScrollEx_Activado;
											};

											//! Función que retorna el alto para los nodos del ArbolEx en pixeles.
											/*!	Esta funcion devuelve el alto para los nodos del ArbolEx en pixeles.
													\fn			inline int AltoLinea(void) const;
													\return		Devuelve la altura de los nodos en pixeles.
											*/
		 inline int				            AltoLinea(void) const {
												return _ArbolEx_AltoLinea;
											};

											//! Función para asignar los pixeles que tendra de alto cada nodo del ArbolEx.
											/*!	Esta funcion asigna los pixeles que tendra de alto cada nodo del ArbolEx.
													\fn			void AltoLinea(const int nAlto);
													\param[in]	nAlto	: Nueva altura en pixeles para los nodos del ArbolEx.
													\return		No devuelve nada.
											*/
		 void				                AltoLinea(const int nAlto);

											//! Función que crea el ArbolEx.
											/*!	Esta funcion crea el ArbolEx.
													\fn			HWND CrearArbolEx(const long Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const bool cPintarBorde = true);
													\param[in]	Estilos			: Estilos para el ArbolEx (WS_CHILD | WS_VISIBLE).
													\param[in]	hWndParent		: HWND del control que sera el padre del ArbolEx.
													\param[in]	cX				: Posicion X.
													\param[in]	cY				: Posicion Y.
													\param[in]	cAncho			: Ancho del ArbolEx.
													\param[in]	cAlto			: Alto del ArbolEx.
													\param[in]	cID				: ID del ArbolEx.
													\param[in]	cPintarBorde	: Parametro que indica si se tiene que pintar el borde del ArbolEx.
													\return		Devuelve el HWND del ArbolEx. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para mas información del error.
											*/
		 HWND								CrearArbolEx(const long Estilos, HWND hWndParent, const int cX, const int cY, const int cAncho, const int cAlto, const int cID, const bool cPintarBorde = true);

											//! Función que conecta el ArbolEx de un dialogo.
											/*!	Esta funcion conecta el ArbolEx de un dialogo.
													\fn			HWND ConectarArbolEx(HWND hWndParent, const int cID, const bool cPintarBorde = true);
													\param[in]	hWndParent		: HWND del control que sera el padre del ArbolEx.
													\param[in]	cID				: ID del ArbolEx.
													\param[in]	cPintarBorde	: Parametro que indica si se tiene que pintar el borde del ArbolEx.
													\return		Devuelve el HWND del ArbolEx. En caso de error devolvera NULL, utiliza DWLDebug::MostrarUltimoError() para mas información del error.
                                                    \remarks    Esta función solo debe usarse con controles que se creen durante la creación del dialogo, si esta clase no pertenece a un dialogo, o se va a crear dinamicamente, no debes usar esta función.
											*/
		 HWND								ConectarArbolEx(HWND hWndParent, const int cID, const bool cPintarBorde = true);

											//! Función que destruye este ArbolEx.
											/*!	Esta funcion destruye el ArbolEx.
													\fn			BOOL Destruir(void);
													\return		Devuelve TRUE si la operacion se completo, FALSE en caso contrario.
											*/
		 BOOL                               Destruir(void);

											//! Función que repinta todo el ArbolEx.
											/*!	Esta función repinta todo el ArbolEx incluyendo barras de scroll y botones extra.
													\fn			void Repintar(const bool Forzar = false);
													\param[in]	Forzar : True para forzar el repintado, false para que la funcion decida si repintar.
													\return		No devuelve nada.
													\remarks	Cuando Forzar es false, esta función mira si ha cambiado algun estado interno,
																y de ser asi repinta el control, en caso contrario no hace nada.
											*/
		 void                               Repintar(const bool Forzar = false);

											//! Función para empezar la edicion de un nodo del ArbolEx.
											/*!	Esta función empieza la edicion de un nodo del ArbolEx.
													\fn			inline HWND EmpezarLabelEdit(DWLArbolEx_Nodo *nNodo, const bool Numerico = false);
													\param[in]	nNodo		:
													\param[in]	Numerico	: True para que la edicion solo acepte digitos, false para que acepte todos los caracteres.
													\return		Devuelve el HWND del Editbox creado para la edicion del Nodo.
													\sa			TerminarLabelEdit(), CancelarLabelEdit()
											*/
		 inline HWND		                EmpezarLabelEdit(DWLArbolEx_Nodo *nNodo, const bool Numerico = false) {
												return ArbolEx_EmpezarLabelEdit(_hWnd, nNodo, Numerico);
											};

											//! Función que termina la edicion de un nodo guardando los datos.
											/*!	Esta función termina la edicion de un nodo del ArbolEx guardando los datos.
													\fn			inline void TerminarLabelEdit(void);
													\return		No devuelve nada.
													\sa			EmpezarLabelEdit(), CancelarLabelEdit()
											*/
		 inline void				        TerminarLabelEdit(void) {
												ArbolEx_TerminarLabelEdit(_hWnd);
											};

											//! Función que cancela la edicion de un nodo sin guardar los datos.
											/*!	Esta función cancela la edicion de un nodo del ArbolEx sin guardar los datos.
													\fn			inline void CancelarLabelEdit(void);
													\return		No devuelve nada.
													\sa			EmpezarLabelEdit(), TerminarLabelEdit()
											*/
		 inline void		                CancelarLabelEdit(void) {
												ArbolEx_CancelarLabelEdit(_hWnd);
											};

											//! Función para mover el ArbolEx a la posicion y el tamaño especificados.
											/*!	Esta función mueve el ArbolEx a la posicion y tamaño especificados.
													\fn			void Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = true);
													\param[in]	cX			: Nueva posicion X para el ArbolEx.
													\param[in]	cY			: Nueva posicion Y para el ArbolEx.
													\param[in]	cAncho		: Nuevo ancho para el ArbolEx.
													\param[in]	cAlto		: Nueva altura para el ArbolEx.
													\param[in]	cRepintar	: True para repintar el control, false para dejarlo sin repintar.
													\return		No devuelve nada.
											*/
		 void								Mover(const int cX, const int cY, const int cAncho, const int cAlto, const bool cRepintar = true);

											//! Función que pinta todo el ArbolEx cuado se recibe un mensaje WM_PAINT.
											/*!	Esta función pinta el ArbolEx cuando se recibe un mensaje WM_PAINT.
													\fn			LRESULT Evento_Pintar(HDC hDC, PAINTSTRUCT &PS);
													\param[in]	hDC	: hDC donde se pintara todo el ArbolEx.
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
		 virtual LRESULT		            Evento_Mouse_Saliendo(void);

											//! Función predefinida del mensaje WM_KEYDOWN (Virtual)
											/*!	Esta función es la encargada de procesar los mensajes WM_KEYDOWN.
													\fn			virtual LRESULT Evento_Teclado_TeclaPresionada(const UINT Tecla, const UINT Repeticion, const UINT Param);
													\param[in]	Caracter   : Tecla virtual soltada.
													\param[in]	Repeticion : Repeticiones de la tecla
													\param[in]	Param	   : Teclas extendidas soltadas.
											        \return		Si re-emplazas esta funcion debes retornar 0.
											*/
		 virtual LRESULT                    Evento_Teclado_TeclaPresionada(const UINT Caracter, const UINT Repeticion, const UINT Param);

											//! Función predefinida del mensaje WM_KEYUP (Virtual)
											/*!	Esta función es la encargada de procesar los mensajes WM_KEYUP.
													\fn			virtual LRESULT Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Param);
													\param[in]	Caracter   : Tecla virtual soltada.
													\param[in]	Repeticion : Repeticiones de la tecla
													\param[in]	Param	   : Teclas extendidas soltadas.
											        \return		Si re-emplazas esta funcion debes retornar 0.
											*/
		 virtual LRESULT                    Evento_Teclado_TeclaSoltada(const UINT Caracter, const UINT Repeticion, const UINT Param);

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

											//! Función que agrega un nodo al ArbolEx.
											/*! Esta función agrega un nodo al ArbolEx.
													\fn			DWLArbolEx_Nodo *AgregarNodo(DWLArbolEx_Nodo *nPadre = NULL, const int nIcono = NULL, const TCHAR *nTexto = NULL, const int PosicionNodo = DWL_ARBOLEX_ORDENADO);
													\param[in]	nPadre			: Nodo padre de este nodo. Puede ser NULL.
													\param[in]	nIcono			: ID del icono para este nodo.
													\param[in]	nTexto			: Texto para el nodo.
													\param[in]	nPosicionNodo	: Posicion para el nodo que puede ser DWL_ARBOLEX_PRINCIPIO, DWL_ARBOLEX_ORDENADO, DWL_ARBOLEX_FIN, o un numero valido de posición.
													\return		Devuelve un puntero al DWLArbolEx_Nodo que se ha creado.
													\remarks	Cuando no necesites añadir mas nodos deberas llamar a la funcion FinAgregarNodos() para actualizar las listas enlazadas.
													\sa			ActualizarTodo();
											*/
		 inline DWLArbolEx_Nodo			   *AgregarNodo(DWLArbolEx_Nodo *nPadre = NULL, const int nIcono = NULL, const TCHAR *nTexto = NULL, const int PosicionNodo = DWL_ARBOLEX_ORDENADO) {
												return ArbolEx_AgregarNodo(NULL, nPadre, nIcono, nTexto, PosicionNodo);
											};

											//! Función que agrega un nodo al ArbolEx.
											/*! Esta función agrega un nodo al ArbolEx.
													\fn			DWLArbolEx_Nodo *AgregarNodo(DWLArbolEx_Nodo *nNodo = NULL, DWLArbolEx_Nodo *nPadre = NULL, const int nIcono = NULL, const TCHAR *nTexto = NULL, const int PosicionNodo = DWL_ARBOLEX_ORDENADO);
													\param[in]	nNodo			: Clase que hereda de DWLArbolEx_Nodo creada anteriormente. Puede ser NULL.
													\param[in]	nPadre			: Nodo padre de este nodo. Puede ser NULL.
													\param[in]	nIcono			: ID del icono para este nodo.
													\param[in]	nTexto			: Texto para el nodo.
													\param[in]	nPosicionNodo	: Posicion para el nodo que puede ser DWL_ARBOLEX_PRINCIPIO, DWL_ARBOLEX_ORDENADO, DWL_ARBOLEX_FIN, o un numero valido de posición.
													\return		Devuelve un puntero al DWLArbolEx_Nodo que se ha creado.
													\remarks	Puedes heredar la clase DWLArbolEx_Nodo y agregarle mas miembros, para luego añadirla al arbol utilizando esta funcion.
																Para ello deberas crear en memoria tu clase heredada, y pasarsela en el parametro nNodo.
																Una vez echo esto ya te puedes olvidar de eliminarla de memoria, ya que el mismo arbol se encargara de ello cuando no la necesite mas.
																Por ultimo cuando no necesites añadir mas nodos deberas llamar a la funcion FinAgregarNodos() para actualizar las listas enlazadas.
													\sa			ActualizarTodo();
											*/
		 inline DWLArbolEx_Nodo			   *AgregarNodo(DWLArbolEx_Nodo *nNodo = NULL, DWLArbolEx_Nodo *nPadre = NULL, const int nIcono = NULL, const TCHAR *nTexto = NULL, const int PosicionNodo = DWL_ARBOLEX_ORDENADO) {
												return ArbolEx_AgregarNodo(nNodo, nPadre, nIcono, nTexto, PosicionNodo);
											};

											//! Función que borra un nodo del ArbolEx.
											/*! Esta función borra el nodo especificado del ArbolEx.
													\fn			void EliminarNodo(DWLArbolEx_Nodo *bNodo, const bool nActualizar = true);
													\param[in]	nNodo		: DWLArbolEx_Nodo que se quiere eliminar.
													\param[in]	Actualizar	: Valor para decidir si se debe actualizar el ArbolEx.
													\return		No devuelve nada.
													\sa			EliminarNodosSeleccionados(), EliminarTodosLosNodos()
											*/
		 inline void						EliminarNodo(DWLArbolEx_Nodo *bNodo, const bool nActualizar = true) {
												ArbolEx_EliminarNodo(_hWnd, bNodo, nActualizar);
											};

											//! Función que borra todos los nodos selecionados.
											/*! Esta función borra todos los nodos selecionados del ArbolEx.
													\fn			void EliminarNodosSeleccionados(DWLArbolEx_Nodo *bNodo = NULL);
													\param[in]	bNodo		: DWLArbolEx_Nodo del que partira la busqueda de nodos seleccionados. Puede ser NULL.
													\return		No devuelve nada.
													\sa			EliminarNodo(), EliminarTodosLosNodos()
											*/
		 inline void						EliminarNodosSeleccionados(DWLArbolEx_Nodo *bNodo = NULL) {
												ArbolEx_EliminarNodosSeleccionados(_hWnd, bNodo);
											};

											//! Función que borra todos los nodos del ArbolEx.
											/*! Esta función borra todos los nodos del ArbolEx.
													\fn			void EliminarTodosLosNodos(void);
													\return		No devuelve nada.
													\sa			EliminarNodo(), EliminarNodosSeleccionados()
											*/
		 inline void                        EliminarTodosLosNodos(void) {
												ArbolEx_EliminarTodosLosNodos();
											};

											//! Función a la que se debe llamar una vez se ha terminado de añadir todos los nodos al ArbolEx.
											/*! Esta función es la encargada de alinear y enlazar todos los nodos del ArbolEx entre ellos.
													\fn			void FinAgregarNodos(const bool ExpandirTodo = false);
													\param[in]	ExpandirTodo	: Valor que determina si los nodos inicialmente estan expandidos.
													\return		No devuelve nada.
													\remarks	Es imperativo que se llame a esta funcion una vez se ha terminado de añadir los nodos para que se actualizen todas las listas de punteros a sus respectivos nodos.
																Si no se llama a esta funcion al terminar de añadir los nodos los resultados pueden ser imprevisibles.
													\sa			AgregarNodo()
											*/
/*		 inline void                        FinAgregarNodos(const bool ExpandirTodo = false) {
												ArbolEx_FinAgregarNodos(_hWnd, ExpandirTodo);
											};	*/

											//! Función que des-seleciona todos los nodos.
											/*! Esta función des-selecciona todos los nodos del ArbolEx.
													\fn			void DesSeleccionarTodo(const bool nRepintar = false);
													\param[in]	nRepintar	: Parametro en el que especificamos si deseamos repintar el ArbolEx.
													\return		No devuelve nada.
											*/
		 inline void                        DesSeleccionarTodo(const bool nRepintar = false) {
												ArbolEx_DesSeleccionarTodo(nRepintar);
											};

											//! Función que retorna el nodo que esta debajo de las coordenadas especificadas.
											/*! Esta función retorna el nodo o la parte del nodo que esta debajo de las coordenadas especificadas.
													\fn			DWLArbolEx_Nodo *HitTest(const int cX, const int cY, const DWL_Enum_ArbolEx_HitTest Tipo = DWL_Enum_ArbolEx_HitTest_Texto_Icono);
													\param[in]	cX		: Coordenada X.
													\param[in]	cY		: Coordenada Y.
													\param[in]	nTipo	: Tipo de busqueda.
													\return		No devuelve nada.
													\remarks	Hay varios tipos de busqueda : [DWL_Enum_ArbolEx_HitTest_Texto] Solo el texto, [DWL_Enum_ArbolEx_HitTest_Icono] Solo el icono, [DWL_Enum_ArbolEx_HitTest_Expansor] Solo el expansor, [DWL_Enum_ArbolEx_HitTest_Texto_Icono] Texto, icono y expansor.
											*/
		 inline DWLArbolEx_Nodo			   *HitTest(const int cX, const int cY, const DWL_Enum_ArbolEx_HitTest nTipo = DWL_Enum_ArbolEx_HitTest_Texto_Icono) {
												return ArbolEx_HitTest(cX, cY, nTipo);
											};

											//! Función que retorna el nodo padre de la posicion especificada.
											/*! Esta funcion retorna el nodo padre de la posicion especificada.
													\fn			inline DWLArbolEx_Nodo *Nodo(const size_t Pos);
													\param[in]	Pos : Posicion del DWLArbolEx_Nodo padre.
													\return		Devuelve el nodo especificado.
													\remarks	Esta funcion te da acceso solo a los nodos padre, si quieres acceso a todos los nodos del ArbolEx en una lista utiliza ArbolEx_NodoLineal()
													\sa			TotalNodos(), NodoLineal(), NodoResaltado(), NodoPresionado(), NodoMarcado()
											*/
		 inline DWLArbolEx_Nodo		       *Nodo(const size_t Pos) {
												return ArbolEx_Nodo(Pos);
											};

											//! Función que retorna el nodo lineal de la posicion especificada
											/*! Esta funcion retorna el nodo lineal de la posicion especificada.
													\fn			inline DWLArbolEx_Nodo *NodoLineal(const size_t Pos);
													\param[in]	Pos : Posicion del DWLArbolEx_Nodo lineal.
													\return		Devuelve el nodo especificado.
													\remarks	Esta funcion te da acceso a todos los nodos, si quieres acceso a solo a los nodos padre en una lista utiliza ArbolEx_Nodo().
													\sa			TotalNodosLineales(), Nodo(), NodoResaltado(), NodoPresionado(), NodoMarcado()
											*/
		 inline DWLArbolEx_Nodo		       *NodoLineal(const size_t Pos) {
												return ArbolEx_NodoLineal(Pos);
											};

											//! Función que retorna el nodo resaltado.
											/*! Esta funcion retorna el nodo resaltado.
													\fn			inline DWLArbolEx_Nodo *NodoResaltado(void);
													\return		Devuelve el nodo resaltado, o NULL si no hay nodo resaltado.
													\sa			Nodo(), NodoLineal(), NodoPresionado(), NodoMarcado()
											*/
		 inline DWLArbolEx_Nodo            *NodoResaltado(void) {
												return _ArbolEx_NodoResaltado;
											};

											//! Función que retorna el nodo presionado.
											/*! Esta funcion retorna el nodo presionado.
													\fn			inline DWLArbolEx_Nodo *NodoPresionado(void);
													\return		Devuelve el nodo presionado, o NULL si no hay nodo presionado.
													\sa			Nodo(), NodoLineal(), NodoResaltado(), NodoMarcado()
											*/
		 inline DWLArbolEx_Nodo            *NodoPresionado(void) {
												return _ArbolEx_NodoPresionado;
											};

											//! Función que retorna el nodo marcado.
											/*! Esta funcion retorna el nodo marcado.
													\fn			inline DWLArbolEx_Nodo *NodoMarcado(void);
													\return		Devuelve el nodo marcado, o NULL si no hay nodo marcado.
													\sa			Nodo(), NodoLineal(), NodoResaltado(), NodoPresionado()
													\remarks	El nodo marcado es el nodo que tiene un borde distinto, y es por decirlo de una manera el cursor del teclado.
											*/
		 inline DWLArbolEx_Nodo            *NodoMarcado(void) {
												return _ArbolEx_NodoMarcado;
											};

											//! Función que retorna el total de nodos en el ArbolEx.
											/*! Esta funcion retorna el total de nodos padre en el ArbolEx.
													\fn			inline UINT TotalNodos(void) const;
													\return		Devuelve el total de nodos padre.
													\sa			Nodo(), NodoLineal(),  TotalNodosLineales()
											*/
		 inline UINT      			        TotalNodos(void) const {
												return static_cast<UINT>(_ArbolEx_Nodos.size());
											};

											//! Función que retorna el total de nodos lineales en el ArbolEx.
											/*! Esta funcion retorna el total de nodos lineales en el ArbolEx.
													\fn			inline UINT TotalNodosLineales(void) const;
													\return		Devuelve el total de nodos lineales.
													\sa			Nodo(), NodoLineal(), TotalNodos()
											*/
		 inline UINT      			        TotalNodosLineales(void) const {
												return static_cast<unsigned int>(_ArbolEx_NodosLineales.size());
											};

											//! Función que obtiene el espacio que necesita el nodo para ser pintado.
											/*! Esta funcion obtiene el espacio que necesita el nodo para ser pintado.
													\fn			void ObtenerRectaNodo(DWLArbolEx_Nodo *nNodo, RECT *Rectangulo);
													\param[in]	nNodo		: Nodo del que queremos obtener el espacio.
													\param[out]	Rectangulo	: Recta en la que se asignara el espacio necesario para el nodo.
													\return		No devuelve nada.
											*/
		 inline void                        ObtenerRectaNodo(DWLArbolEx_Nodo *nNodo, RECT *Rectangulo) {
												ArbolEx_ObtenerRectaNodo(nNodo, Rectangulo);
											};

											//! Función que hace visible en la pantalla el nodo especificado.
											/*! Esta funcion hace visible en la pantalla el nodo especificado.
													\fn			void HacerVisible(DWLArbolEx_Nodo *vNodo, const bool nRepintar = false);
													\param[in]	nNodo		: Nodo que queremos hacer visible.
													\param[in]	nRepintar	: Variable en la que especificamos si hay que repintar.
													\return		No devuelve nada.
											*/
		 inline void                        HacerVisible(DWLArbolEx_Nodo *vNodo, const bool nRepintar = false) {
												ArbolEx_HacerVisible(_hWnd, vNodo, nRepintar);
											};

											//! Función para expandir / contraer el nodo especificado.
											/*! Esta función expande / contrae el nodo especificado.
													\fn			void Expandir(DWLArbolEx_Nodo *vNodo, const bool nExpandir, const bool nRepintar = false);
													\param[in]	nNodo		: Nodo que queremos expandir / contraer.
													\param[in]	nExpandir	: Variable en la que especificamos si hay que expandir o contraer.
													\param[in]	nRepintar	: Variable en la que especificamos si hay que repintar.
													\return		No devuelve nada.
											*/
		 inline void                        Expandir(DWLArbolEx_Nodo *vNodo, const bool nExpandir, const bool nRepintar = false) {
												ArbolEx_Expandir(_hWnd, vNodo, nExpandir, nRepintar);
											}

											//! Función que actualiza todos los datos del ArbolEx.
											/*! Esta función actualiza todos los datos del ArbolEx.
													\fn			virtual void ActualizarTodo(const bool nRepintar = false, const bool nExpandirTodo = false);
                                                    \param[in]  nRepintar     : true para repintar el control, false para mantenerlo sin repintar.
                                                    \param[in]  nExpandirTodo : true para expandir todos los nodos, false para mantenerlos como estan.
													\return		No devuelve nada.
													\remarks	Esta función se usa para actualizar todos los estilos y nodos del ArbolEx. Si necesitas actualizar el tamaño de los textos por haber cambiado la fuente, deberas usar tambien ArbolEx_ActualizarTamTexto().
											*/
		 virtual void                       ActualizarTodo(const bool nRepintar = false, const bool nExpandirTodo = false) {
												RECT RC;
												GetClientRect(_hWnd, &RC);
												ArbolEx_ActualizarTodo(_hWnd, &RC, nExpandirTodo);
                                                if (nRepintar == true) Repintar(true);
											};

											//! Función para desactivar / activar las transparencias en el ArbolEx.
											/*! Esta función desactiva / activa las transparencias en el ArbolEx.
													\fn			void DesactivarAlphaBlend(const bool nDesactivar);
													\param[in]	nDesactivar : True para desactivar transparencias, False para activarlas.
													\return		No devuelve nada.
													\remarks	Por defecto las transparecinas estan habilitadas.
											*/
/*		 void				                DesactivarAlphaBlend(const bool Desactivar) {
												_ArbolEx_DesactivarBlend = Desactivar;
											};*/

											//! Función que retorna si este control tiene habilitada la multiseleccion.
											/*! Esta función retorna si este control tiene habilitada la multiseleccion.
													\fn			void inline const bool MultiSeleccion(void);
													\return		Devuelve true si la multiseleccion esta habilitada, false en caso contrario.
											*/
/*		 inline const bool					MultiSeleccion(void) {
												return _ArbolEx_MultiSeleccion;
											};*/

											//! Función para habilitar / deshabilitar la multiseleccion.
											/*! Esta función habilita / deshabilita la multiseleccion.
													\fn			inline void MultiSeleccion(const bool nMultiSeleccion);
													\param[in]	nMultiSeleccion : True para habilitar la multiseleccion, false para deshabilitarla.
													\return		No devuelve nada.
											*/
/*		 inline void						MultiSeleccion(const bool nSubSeleccion) {
												_ArbolEx_MultiSeleccion = nSubSeleccion;
											};*/

											//! Función que retorna si este control tiene habilitada la subseleccion.
											/*! Esta función retorna si este control tiene habilitada la subseleccion.
													\fn			void inline const bool SubSeleccion(void);
													\return		Devuelve true si la subseleccion esta habilitada, false en caso contrario.
											*/
/*		 inline const bool					SubSeleccion(void) {
												return _ArbolEx_SubSeleccion;
											};*/

											//! Función para habilitar / deshabilitar la subseleccion
											/*! Esta función habilita / deshabilita la subseleccion.
													\fn			inline void SubSeleccion(const bool nSubSeleccion);
													\param[in]	nSubSeleccion : True para habilitar la subseleccion, false para deshabilitarla.
													\return		No devuelve nada.
											*/
/*		 inline void						SubSeleccion(const bool nSubSeleccion) {
												_ArbolEx_SubSeleccion = nSubSeleccion;
											};*/

											
											//! Función que enlaza el mensaje WM_TIMER con el ArbolEx.
											/*! Esta función enlaza el mensaje WM_TIMER con el ArbolEx.
													\fn			LRESULT Evento_Temporizador(const UINT cID);
													\param[in]	cID : ID del temporizador.
													\return		No devuelve nada.
													\remarks	Si re-emplazas esta funcion debes retornar 0.
											*/
		 LRESULT							Evento_Temporizador(const UINT cID);

											//! Función que retorna el hWnd del EditBox cuando se esta haciendo un LabelEdit.
											/*! Esta función retorna el HWND del EditBox cuando se esta haciendo un LabelEdit.
													\fn			inline HWND hWndEditBox(void);
													\return		Devuelve el HWND del EditBox que se esta usando para la edición.
													\sa			EmpezarLabelEdit()
											*/
		 inline HWND                        hWndEditBox(void) {
												 return _ArbolEx_hWndEdit;
											};
		protected : ////////////////////////// Miembros Protegidos

											//! Esqueleto para los mensajes del ArbolEx.
											/*! Esta función es el esqueleto para los mensajes del ArbolEx.
													\fn			LRESULT CALLBACK GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
													\param[in]	uMsg	: Mensaje.
													\param[in]	wParam	: Parametro1.
													\param[in]	lParam	: Parametro2.
													\return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
													\remarks	Esta función es el esqueleto del ArbolEx por donde pasaran todos sus mensajes.
											*/
		 LRESULT CALLBACK					GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);

		 friend class DWLArbolEx_Nodo;		//
		}; /////////////////////////////////// Fin DWLArbolEx



	}
}

#endif // DWL_ARBOLEX_H


/*! \file DWLArbolEx.h
\version
  [31/05/2010] <b>0.95c</b> \n
  Se ha creado una clase que contiene los estilos del arbol, dentro de ella se encontraran los colores, las fuentes, y las otras propiedades disponibles para la apariencia.\n
  Si se cambia cualquier estilo se debera usar la funcion ArbolEx_ActualizarTodo(), ademas si cambiamos la fuente tambien deberemos usar ArbolEx_ActualizarTamTexto().\n
  Se ha retocado la función ArbolEx_ActualizarTamTexto de forma que calcule el texto de cada nodo usando su fuente, y no la fuente por defecto, ademas tambien se calcula el _ArbolEx_AltoLinea de forma que siempre sea el valor mas alto que se encontro calculando los textos.\n\n
  Eliminada la función ArbolEx_FinAgregarNodos, ahora se usara ArbolEx_ActualizarTodo.\n\n
  [29/05/2010] <b>0.95b</b> \n
  Solucionado bug con el mouse que cuando la barra de scroll horizontal no tenia el valor a 0, el mouse no funcionaba bien para detectar los nodos.\n\n
  [04/11/2009] <b>0.95</b> \n
  Creada clase DWL::ControlesEx::DWLArbolEx_Nucleo, que sera la encargada de realizar todas las operaciones del arbol, la clase DWL::ControlesEx::DWLArbolEx pasa a ser un contenedor de la clase nucleo. Con estos cambios tenemos la ventaja de que podemos pintar el arbol en hdcs que no sean el suyo.
  Se han retocado los colores y las fuentes para que sean mucho mas faciles de editar.\n\n
  [17/06/2009] <b>0.94</b> \n
  Solucionado problema con el repintado, este problema sucedia al arrastrar ventanas por encima, y hacia que no se repintara correctamente el control.\n\n
  [25/02/2009] <b>0.93</b> \n
  Simplificados mensajes de click, y se ha añadido soporte para botones X. \n
  Los mensjaes DWL_ARBOLEX_CLICK_DERECHO, DWL_ARBOLEX_CLICK_IZQUIERDO, DWL_ARBOLEX_CLICK_MEDIO y DWL_ARBOLEX_CLICK_X Se han remplazado por DWL_ARBOLEX_CLICK. \n
  Resuleto problema con los scolls al borrar todos los nodos, que no se actualizaban correctamente. \n
  Añadido soporte para tooltips. \n
  Para empezar se ha añadido la función DWLArbolEx::MostrarTooltip, la cual nos permite activar el uso de estos. \n
  Despues tenemos el DWLArbolEx::Evento_MostrarToolTip virtual, en el cual podemos personalizar el tooltip al maximo. \n
  Y por ultimo el objeto ToolTip que consiste en una clase DWL::ControlesEx::DWLToolTip, el cual es de uso interno. \n\n
  [20/02/2009] <b>0.92</b> \n
  Solucionado crash con unas variables que no tenian valor inicial establecido. \n
  Agregado estado desactivado, para pintarse distinto si el arbol se desactiva. \n\n
  [05/02/2009] <b>0.91</b> \n
  Solucionados algunos fallos con el scroll que no se actualizaba correctamente al mover el scroll con la rueda y con el teclado. \n\n
  [08/06/2007] <b>0.9</b> \n
  El scroll vertical que se usaba antes se ha eliminado (ClaseBarraScrolEx), y actualmente el mismo control tiene los scrolls incorporados tanto horizontales, como verticales!! (BaseControlExScroll) \n
  Ademas la clase BaseControlExScroll tiene funciones para realizar cambios en su tamaño, y para poder mostrar y ocultar los scrolls tanto manualmente como de forma automatica. \n\n
  [27/03/2007] <b>0.8</b> \n
  Este control ahora puede ser redimensionado a cualquier tamaño durante la ejecución, por ello tambien puede mostrar y tratar nodos que no se ven completamente en la pantalla. \n
  AVPAG y REPAG ya pueden usarse con SHIFT! \n\n
  [01/04/2006] <b>0.73</b> \n
  Se ha añadido la posibilidad de activar / desactivar la multiseleccion. Hasta el momento estaba activada por defecto. \n\n
  [07/12/2005] <b>0.72</b> \n
  Se ha retocado el estilo del LabelEdit para satisfacer la linea de esta libreria, haora incluye su clase para cancelarlo si es necesario. \n
  Porfiiin se han terminado las teclas AVPAG y REPAG eso si.. sin SHIFT. \n
  Ademas se han añadido algunas funciones nuevas como son NodoFinPagina y todas las funciones independientes para cada tecla especial (UP, DOWN, LEFT, RIGHT, Etc...). \n\n
  [24/04/2005] <b>0.71</b> \n
  Se han reemplazado varios nombres de funciones medio en ingles medio en castellano para que pasen a ser totalmente en castellano. \n
  Se han eliminado todas las macros que empezaban por On. \n
  Ahora existen nuevas macros que empiezan por ENLACE_ \n
  Se han eliminado las notificaciones estandard que retornaba este control, y ahora retorna sus propios mensajes. \n
  DWL_ARBOLEX_CLICK_DERECHO	       <b>-></b> ENLACE_ArbolEx_Evento_Mouse_Click				<b>-></b> (const UINT Boton, const int cX, const int cY, const int ID) \n
  DWL_ARBOLEX_CLICK_IZQUIERDO      <b>-></b> ENLACE_ArbolEx_Evento_Mouse_Click				<b>-></b> (const UINT Boton, const int cX, const int cY, const int ID) \n
  DWL_ARBOLEX_CLICK_MEDIO		   <b>-></b> ENLACE_ArbolEx_Evento_Mouse_Click				<b>-></b> (const UINT Boton, const int cX, const int cY, const int ID) \n
  DWL_ARBOLEX_DOBLECLICK_DERECHO   <b>-></b> ENLACE_ArbolEx_Evento_Mouse_DobleClick			<b>-></b> (const UINT Boton, const int cX, const int cY, const int ID) \n
  DWL_ARBOLEX_DOBLECLICK_IZQUIERDO <b>-></b> ENLACE_ArbolEx_Evento_Mouse_DobleClick			<b>-></b> (const UINT Boton, const int cX, const int cY, const int ID) \n
  DWL_ARBOLEX_DOBLECLICK_MEDIO	   <b>-></b> ENLACE_ArbolEx_Evento_Mouse_DobleClick			<b>-></b> (const UINT Boton, const int cX, const int cY, const int ID) \n
  DWL_ARBOLEX_TECLADO_PRESIONADO   <b>-></b> ENLACE_ArbolEx_Evento_Teclado_TeclaPresionada	<b>-></b> (const int TeclaVirtual, const int ID) \n
  DWL_ARBOLEX_TECLADO_SOLTADO	   <b>-></b> ENLACE_ArbolEx_Evento_Teclado_TeclaSoltada		<b>-></b> (const int TeclaVirtual, const int ID) \n
  DWL_ARBOLEX_TECLADO_INTRO		   <b>-></b> ENLACE_ArbolEx_Evento_Teclado_Intro			<b>-></b> (const int ID) \n
  DWL_ARBOLEX_FOCO_OBTENIDO		   <b>-></b> ENLACE_ArbolEx_Evento_Foco_Obtenido			<b>-></b> (const int ID) \n
  DWL_ARBOLEX_FOCO_PERDIDO		   <b>-></b> ENLACE_ArbolEx_Evento_Foco_Perdido				<b>-></b> (const int ID) \n\n
  [10/03/2005] <b>0.7</b> \n
  El scrollbar ya no tiene el codigo en este archivo. Por ello haora ademas se necesita el archivo ClaseBarraScrollEx.h \n\n
  [22/02/2005] <b>0.66</b> \n
  La función crear ahora retorna el hWnd del control, NULL si este no se crea correctamente. \n\n
  [20/02/2005] <b>0.65</b> \n
  Primera versión de este control con practicamente todas las cualidades basicas de un treeview. Ademas tiene 23 colores configurables por nodo y 5 fuentes, dispone de multiselecion (comentada mas abajo), posibilidad de incorporar dibujo en el fondo, y todas las funcionabilidades habituales a la hora cambiar colores a los nodos y a la hora de reemplazar funciones de pintado de este control. \n
  La multiselecion es un tanto diferente a lo habitual, ya que he implementado un nuevo tipo de selecion 'SubSeleccion' y este se aplica a todos los hijos del nodo selecionado. con esto es mas facil recorrer todo el arbol y simplemente mirar los nodos selecionados, para asi efectuar operaciones sobre ellos. \n
  Al tener la subselecion se hace algo raro hacer multiselecion, pero funciona bastante bien. En el futuro se vera si trae problemas o no.... \n
  <b>NOTA</b> Este control en su primera version ha llevado practicamente 2 meses de trabajo.... pero me he quedado muy satisfecho de el. :) \n
  */

