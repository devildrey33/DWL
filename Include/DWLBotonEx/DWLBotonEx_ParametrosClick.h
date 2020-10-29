#ifndef DWL_BOTONEX_PARAMETROSCLICK_H
#define DWL_BOTONEX_PARAMETROSCLICK_H

 
namespace DWL {
	namespace ControlesEx {

		//! Clase destinada a contener los parametros de un click en el boton
		class DWLBotonEx_ParametrosClick {
		 public : //////////////// Miembros publicos

								//! Constructor.
								/*! Constructor.
									\fn			DWLBotonEx_ParametrosClick(void);
									\return		No devuelve nada.
								*/
								DWLBotonEx_ParametrosClick(void) : _X(0), _Y(0), _IDBotonEx(0), _Boton(0), _Param(0) {
								};

			 					//! Constructor asignador defecto.
								/*! Este constructor asigna todos los datos necesarios para un parametro de click.
										\fn			DWLBotonEx_ParametrosClick(const int cX, const int cY, const UINT cID, const UINT nBoton, const UINT nParam);
										\param[in]	cX		: Coordenada X.
										\param[in]	cY		: Coordenada Y.
										\param[in]	cID		: ID del BotonEx.
										\param[in]	nBoton	: Boton que se ha presionado del mouse.
										\param[in]	Param	: wParam para saber si se han presionado teclas extendidas.
										\return		No devuelve nada.
								*/
								DWLBotonEx_ParametrosClick(const int cX, const int cY, const UINT cID, const UINT nBoton, const UINT nParam) : _X(cX), _Y(cY), _IDBotonEx(cID), _Boton(nBoton), _Param(nParam) {
								};

								//! Destructor.
								/*! Destructor.
										\fn			~DWLBotonEx_ParametrosClick(void);
										\return		No devuelve nada.
								*/
							   ~DWLBotonEx_ParametrosClick(void) {
								};

			 					//! Función que asigna todos los parametros del click.
								/*! Esta función asigna todos los datos necesarios para un parametro de click.
										\fn			inline void Asignar(const int cX, const int cY, const UINT cID, const UINT nBoton, const UINT nParam);
										\param[in]	cX		: Coordenada X.
										\param[in]	cY		: Coordenada Y.
										\param[in]	cID		: ID del BotonEx.
										\param[in]	nBoton	: Boton que se ha presionado del mouse.
										\param[in]	nParam	: wParam para saber si se han presionado teclas extendidas.
										\return		No devuelve nada.
								*/
		 inline void			Asignar(const int cX, const int cY, const UINT cID, const UINT nBoton, const UINT nParam) {
									_X			= cX;
									_Y			= cY;
									_IDBotonEx	= cID;
									_Boton		= nBoton;
									_Param		= nParam;
								};

								//! Función que retorna la coordenada X del mouse.
								/*!	Esta funcion devuelve la coordenada X del mouse.
										\fn			inline int X(void) const;
										\return		Devuelve la coordenada X del mouse.
								*/
		 inline int		        X(void) const {
									return _X;
								};

								//! Función que retorna la coordenada Y del mouse.
								/*!	Esta funcion devuelve la coordenada Y del mouse.
										\fn			inline int Y(void) const;
										\return		Devuelve la coordenada Y del mouse.
								*/
		 inline int		        Y(void) const {
									return _Y;
								};

								//! Función que retorna la ID del BotonEx.
								/*!	Esta funcion devuelve la ID del BotonEx.
										\fn			inline UINT IDBotonEx(void) const;
										\return		Devuelve la ID del BotonEx.
								*/
		 inline UINT		    IDBotonEx(void) const {
									return _IDBotonEx;
								};

								//! Función que retorna el boton presionado / soltado.
								/*!	Esta funcion devuelve el boton del mouse presionado / soltado.
										\fn			inline UINT Boton(void) const;
										\return		Devuelve el boton presionado / soltado.
								*/
		 inline UINT		    Boton(void) const {
									return _Boton;
								};

								//! Función que retorna el wParam.
								/*!	Esta funcion devuelve el wParam que especifica si hay teclas extendidas presionadas.
										\fn			inline const UINT Param(void);
										\return		Devuelve el wParam que especifica si hay teclas extendidas presionadas.
								*/
		 inline UINT            Param(void) const {
									return _Param;
								};
		 private : /////////////// Miembros privados

								//! Coordenada X del mouse relativo al control
		  int                  _X;

								//! Coordenada Y del mouse relativo al control
		  int				   _Y;

								//! ID del control
		  UINT                 _IDBotonEx;

								//! Boton presionado
		  UINT                 _Boton;

								//! Param del mensaje
		  UINT  			   _Param;
		};						//
		////////////////////////// Fin DWLBotonEx_ParametrosClick

    };
};

#endif
