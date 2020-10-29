#ifndef DWL_BARRASCROLLEX_PARAMETROSCLICK_H
#define DWL_BARRASCROLLEX_PARAMETROSCLICK_H
 


namespace DWL {
	namespace ControlesEx {

		//! Clase destinada a contener los parametros de un click en el scroll
		class DWLBarraScrollEx_ParametrosClick {
		 public : //////////////////////////////////////// Miembros publicos

														//! Constructor.
														/*! Constructor.
															\fn			DWLBarraScrollEx_ParametrosClick(void);
															\return		No devuelve nada.
														*/
														DWLBarraScrollEx_ParametrosClick(void) : _X(0), _Y(0),	_IDControlEx(0), _Boton(0), _Param(0), _Objeto(0) {
														};

			 											//! Constructor asignador defecto.
														/*! Este constructor asigna todos los datos necesarios para un parametro de click.
																\fn			DWLBarraScrollEx_ParametrosClick(const int cX, const int cY, const UINT cID, const UINT nBoton, const int nObjeto, const UINT nParam);
																\param[in]	cX		: Coordenada X.
																\param[in]	cY		: Coordenada Y.
																\param[in]	cID		: ID de la BarraScrollEx.
																\param[in]	nBoton	: Boton que se ha presionado del mouse.
																\param[in]	nObjeto	: Tipo de objeto que se ha presionado.
																\param[in]	wParam	: wParam para saber si se han presionado teclas extendidas.
																\return		No devuelve nada.
																\remarks	Los tipos de objeto posibles son :
																				DWL_BARRASCROLLEX_OBJETO_NINGUNO,
																				DWL_BARRASCROLLEX_OBJETO_BOTON_SUPERIOR,
																				DWL_BARRASCROLLEX_OBJETO_BOTON_INFERIOR,
																				DWL_BARRASCROLLEX_OBJETO_SCROLL,
																				DWL_BARRASCROLLEX_OBJETO_FONDO_SUPERIOR,
																				DWL_BARRASCROLLEX_OBJETO_FONDO_INFERIOR,
																				DWL_BARRASCROLLEX_OBJETO_BOTON_EXTENDIDO
														*/
														DWLBarraScrollEx_ParametrosClick(const int cX, const int cY, const UINT cID, const UINT nBoton, const int nObjeto, const UINT nParam) :
                                                            _X(cX), _Y(cY),	_IDControlEx(cID), _Boton(nBoton), _Param(nParam), _Objeto(nObjeto) {
														};

														//! Destructor.
														/*! Destructor.
																\fn			~DWLBarraScrollEx_ParametrosClick(void);
																\return		No devuelve nada.
														*/
													   ~DWLBarraScrollEx_ParametrosClick(void) {
														};
														//! Función para asignar todos los valores de la clase.
														/*! Esta función asigna todos los datos necesarios para un parametro de click.
																\fn			inline void Asignar(const int cX, const int cY, const UINT cID, const UINT nBoton, const int nObjeto, const UINT nParam);
																\param[in]	cX		: Coordenada X.
																\param[in]	cY		: Coordenada Y.
																\param[in]	cID		: ID del control que hereda la BarraScrolLEx.
																\param[in]	nBoton	: Boton que se ha presionado del mouse.
																\param[in]	nObjeto	: Tipo de objeto que se ha presionado.
																\param[in]	wParam	: wParam para saber si se han presionado teclas extendidas.
																\return		No devuelve nada.
																\remarks	Los tipos de objeto posibles son :
																				DWL_BARRASCROLLEX_OBJETO_NINGUNO,
																				DWL_BARRASCROLLEX_OBJETO_BOTON_SUPERIOR,
																				DWL_BARRASCROLLEX_OBJETO_BOTON_INFERIOR,
																				DWL_BARRASCROLLEX_OBJETO_SCROLL,
																				DWL_BARRASCROLLEX_OBJETO_FONDO_SUPERIOR,
																				DWL_BARRASCROLLEX_OBJETO_FONDO_INFERIOR,
																				DWL_BARRASCROLLEX_OBJETO_BOTON_EXTENDIDO
														*/
	     inline void									Asignar(const int cX, const int cY, const UINT cID, const UINT nBoton, const int nObjeto, const UINT nParam) {
															_X				= cX;
															_Y				= cY;
															_IDControlEx	= cID;
															_Boton			= nBoton;
															_Param			= nParam;
															_Objeto			= nObjeto;
														};

														//! Función que retorna la coordenada X del mouse.
														/*!	Esta funcion devuelve la coordenada X del mouse.
																\fn			inline int X(void);
																\return		Devuelve la coordenada X del mouse.
														*/
		 inline int								        X(void) {
															return _X;
														};

														//! Función que retorna la coordenada Y del mouse.
														/*!	Esta funcion devuelve la coordenada Y del mouse.
																\fn			inline int Y(void);
																\return		Devuelve la coordenada Y del mouse.
														*/
		 inline int								        Y(void) {
															return _Y;
														};

														//! Función que retorna la ID del control extendido.
														/*!	Esta funcion devuelve la ID del control extendido.
																\fn			inline int IDControlEx(void);
																\return		Devuelve la ID del control extendido.
														*/
		 inline int								        IDControlEx(void) {
															return _IDControlEx;
														};

														//! Función que retorna el boton presionado / soltado.
														/*!	Esta funcion devuelve el boton del mouse presionado / soltado.
																\fn			inline UINT Boton(void);
																\return		Devuelve el boton presionado / soltado.
														*/
		 inline UINT								    Boton(void) {
															return _Boton;
														};

														//! Función que retorna el tipo de objeto presionado / soltado.
														/*!	Esta funcion devuelve el tipo de objeto presionado / soltado.
																\fn			inline const int Objeto(void);
																\return		Devuelve el tipo de objeto.
																\remarks	Los tipos de objeto posibles son :
																				DWL_BARRASCROLLEX_OBJETO_NINGUNO,
																				DWL_BARRASCROLLEX_OBJETO_BOTON_SUPERIOR,
																				DWL_BARRASCROLLEX_OBJETO_BOTON_INFERIOR,
																				DWL_BARRASCROLLEX_OBJETO_SCROLL,
																				DWL_BARRASCROLLEX_OBJETO_FONDO_SUPERIOR,
																				DWL_BARRASCROLLEX_OBJETO_FONDO_INFERIOR,
																				DWL_BARRASCROLLEX_OBJETO_BOTON_EXTENDIDO
														*/
		 inline int								        Objeto(void) {
															return _Objeto;
														};

														//! Función que retorna el Param.
														/*!	Esta funcion devuelve el wParam que especifica si hay teclas extendidas presionadas.
																\fn			inline const UINT Param(void);
																\return		Devuelve el wParam que especifica si hay teclas extendidas presionadas.
														*/
		 inline UINT      						        Param(void) {
															return _Param;
														};
		 private : /////////////////////////////////////// Miembros privados

														//! Coordenada X del mouse relativo al control.
		  int								           _X;

														//! Coordenada Y del mouse relativo al control.
		  int										   _Y;

														//! ID del control.
		  int							               _IDControlEx;

														//! Boton presionado.
		  UINT								           _Boton;

														//! Objeto Presionado.
		  int										   _Objeto;

														// Param del mensaje.
		  UINT  									   _Param;
		};												//
		////////////////////////////////////////////////// Fin DWLBarraScrollEx_ParametrosClick

    };
};

#endif
