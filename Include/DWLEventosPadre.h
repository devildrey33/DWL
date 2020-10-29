/*! \file DWLEventosPadre.h
	\brief Archivo que contiene los eventos basicos para cualquier ventana padre.
*/
#ifndef DWL_EVENTOSPADRE_H
#define DWL_EVENTOSPADRE_H

//#include "DWLDebug.h"
#include "DWLEventosBase.h"

#include "DWLBotonEx.h"
#include "DWLArbolEx.h"
#include "DWLListaEx.h"
#include "DWLBarraEx.h"
#include "DWLMarcaEx.h"
#include "DWLMenuEx.h"
#include "DWLComboBox.h"
#include "DWLEditBox.h"
#include "DWLListBox.h"
#include "DWLListView.h"
#include "DWLTreeView.h" 

#include "DWLEdicionDesplegableEx.h"
#include "DWLBarraTareas.h"

//! Espacio de nombres DWL
namespace DWL {

    //! Espacio de nombres Ventanas
    namespace Ventanas {

        //! Espacio de nombres Base
        namespace Base {


			


            //! Clase base para los eventos de ventanas / dialogos padre
            template <typename TIPO_DEVUELTO, const long VALOR_DEVUELTO = 0> class DWLEventosPadre : public DWLEventosBase<TIPO_DEVUELTO, VALOR_DEVUELTO> {
             public :
		                                        //! Constructor
                                                /*! Constructor por defecto.
		                                                \fn			DWLEventosPadre(void);
                                                        \return     No devuelve nada
                                                */
                                                DWLEventosPadre(void) : DWLEventosBase<TIPO_DEVUELTO, VALOR_DEVUELTO>(), ListaTabuladores() { 
													if (_WM_TASK_BUTTON_CREATED == 0) _WM_TASK_BUTTON_CREATED = RegisterWindowMessage(TEXT("TaskbarButtonCreated"));
													BarraTareas._Enlazar(&_hWnd);
												};

		                                        //! Destructor
                                                /*! Destructor por defecto.
		                                                \fn		   ~DWLEventosPadre(void);
                                                        \return     No devuelve nada
                                                */
                                               ~DWLEventosPadre(void) { };

				DWLBarraTareas					BarraTareas;

				inline virtual TIPO_DEVUELTO    Evento_BotonBarraTareas_Creado(void) { return VALOR_DEVUELTO; };

                                                //////////////
                                                // -ArbolEx //
                                                //////////////
                                                //
							                    //! Función virtual que recibira los DobleClick del ArbolEx.
							                    /*! Esta función virtual recibira los DobleClick del ArbolEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ArbolEx_Mouse_DobleClick(const UINT nBoton, const int cX, const int cY, DWL::ControlesEx::DWLArbolEx_Nodo *nNodo, const UINT nIDArbolEx);
									                    \param[in]	nBoton		: Boton presionado, los botones del mouse extendidos empiezan a partir del 3.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	nNodo		: Nodo presionado en el arbol (Puede ser NULL).
									                    \param[in]	IDArbolEx	: ID del ArbolEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
                inline virtual TIPO_DEVUELTO    Evento_ArbolEx_Mouse_DobleClick(const UINT nBoton, const int cX, const int cY, DWL::ControlesEx::DWLArbolEx_Nodo *nNodo, const UINT nIDArbolEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los Click del ArbolEx.
							                    /*! Esta función virtual recibira los Click del ArbolEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ArbolEx_Mouse_Click(const UINT nBoton, const int cX, const int cY, DWL::ControlesEx::DWLArbolEx_Nodo *nNodo, const UINT nIDArbolEx);
									                    \param[in]	nBoton		: Boton presionado, los botones del mouse extendidos empiezan a partir del 3.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	nNodo		: Nodo presionado en el arbol (Puede ser NULL).
									                    \param[in]	IDArbolEx	: ID del ArbolEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
			    inline virtual TIPO_DEVUELTO    Evento_ArbolEx_Mouse_Click(const UINT Boton, const int cX, const int cY, DWL::ControlesEx::DWLArbolEx_Nodo *nNodo, const UINT IDArbolEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYDOWN del ArbolEx.
							                    /*! Esta función virtual recibira los mensajes WM_KEYDOWN del ArbolEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ArbolEx_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDArbolEx);
									                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
									                    \param[in]	IDArbolEx		: ID del ArbolEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
                inline virtual TIPO_DEVUELTO    Evento_ArbolEx_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDArbolEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYUP del ArbolEx.
							                    /*! Esta función virtual recibira los mensajes WM_KEYUP del ArbolEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ArbolEx_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDArbolEx);
									                    \param[in]	TeclaVirtual	: Tecla virtual soltada.
									                    \param[in]	IDArbolEx		: ID del ArbolEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
			    inline virtual TIPO_DEVUELTO    Evento_ArbolEx_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDArbolEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira cuando se presiona la tecla Intro en el ArbolEx.
							                    /*! Esta función virtual recibira cuando se presiona la tecla Intro en el ArbolEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ArbolEx_Teclado_Intro(const UINT IDArbolEx);
									                    \param[in]	IDArbolEx	: ID del ArbolEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
			    inline virtual TIPO_DEVUELTO    Evento_ArbolEx_Teclado_Intro(const UINT IDArbolEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira cuando se empieza la edición de un nodo del ArbolEx.
							                    /*! Esta función virtual recibira cuando se empieza la edición de un nodo del ArbolEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ArbolEx_LabelEdit_Inicio(DWL::ControlesEx::DWLArbolEx_Nodo *eNodo, const UINT IDArbolEx);
									                    \param[in]	eNodo		: Nodo que se va a empezar a editar.
									                    \param[in]	IDArbolEx	: ID del ArbolEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
			    inline virtual TIPO_DEVUELTO    Evento_ArbolEx_LabelEdit_Inicio(DWL::ControlesEx::DWLArbolEx_Nodo *eNodo, const UINT IDArbolEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira cuando se termina la edición de un nodo del ArbolEx.
							                    /*! Esta función virtual recibira cuando se termina la edición de un nodo del ArbolEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ArbolEx_LabelEdit_Fin(DWL::ControlesEx::DWLArbolEx_TerminarLabelEdit *nEdicion, const UINT IDArbolEx);
									                    \param[in]	nEdicion	: Clase DWL::ControlesEx::DWLArbolEx_TerminarLabelEdit que contiene los datos del nodo editado, y funciones para retocar el resultado.
									                    \param[in]	IDArbolEx	: ID del ArbolEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
			    inline virtual TIPO_DEVUELTO    Evento_ArbolEx_LabelEdit_Fin(DWL::ControlesEx::DWLArbolEx_TerminarLabelEdit *nEdicion, const UINT IDArbolEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira cuando se cancela la edición de un nodo del ArbolEx.
							                    /*! Esta función virtual recibira cuando se cancela la edición de un nodo del ArbolEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ArbolEx_LabelEdit_Cancelado(DWL::ControlesEx::DWLArbolEx_Nodo *eNodo, const UINT IDArbolEx);
									                    \param[in]	eNodo		: Nodo del que se ha cancelado la edición.
									                    \param[in]	IDArbolEx	: ID del ArbolEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
			    inline virtual TIPO_DEVUELTO    Evento_ArbolEx_LabelEdit_Cancelado(DWL::ControlesEx::DWLArbolEx_Nodo *eNodo, const UINT IDArbolEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_SETFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_SETFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ArbolEx_Foco_Obtenido(const UINT IDArbolEx);
									                    \param[in]	IDArbolEx	: ID del ArbolEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
			    inline virtual TIPO_DEVUELTO    Evento_ArbolEx_Foco_Obtenido(const UINT IDArbolEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_KILLFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_KILLFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ArbolEx_Foco_Perdido(const UINT IDArbolEx);
									                    \param[in]	IDArbolEx	: ID del ArbolEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
			    inline virtual TIPO_DEVUELTO    Evento_ArbolEx_Foco_Perdido(const UINT IDArbolEx) { return VALOR_DEVUELTO; };


                                                //////////////
                                                // -BarraEx //
                                                //////////////

						                        //! Función virtual que recibira cuando la barra cambia de valor.
						                        /*! Esta función virtual recibira cuando la barra cambia de valor.
								                        \fn			virtual TIPO_DEVUELTO Evento_BarraEx_CambioValor(const UINT IDBarraEx);
								                        \param[in]	IDBarraEx	: ID de la BarraEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                        */
		        inline virtual TIPO_DEVUELTO	Evento_BarraEx_CambioValor(const UINT IDBarraEx) { return VALOR_DEVUELTO; };

						                        //! Función virtual que recibira los mensajes WM_*MOUSEUP.
						                        /*! Esta función virtual recibira los mensajes WM_*MOUSEUP.
								                        \fn			virtual TIPO_DEVUELTO Evento_BarraEx_Mouse_BotonSoltado(const UINT IDBarraEx, const UINT nBoton);
								                        \param[in]	IDBarraEx	: ID de la BarraEx que manda el evento.
								                        \param[in]	nBoton		: Boton del mouse que se ha presionado.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                        */
		        inline virtual TIPO_DEVUELTO    Evento_BarraEx_Mouse_BotonSoltado(const UINT IDBarraEx, const UINT nBoton) { return VALOR_DEVUELTO; };


						                        //! Función virtual que recibira el mensaje DWL_BARRASCROLLEX_BOTONEX_CLICK.
						                        /*! Esta función virtual recibira el mensaje DWL_BARRASCROLLEX_BOTONEX_CLICK que indica que se ha presionado un boton extendido de la barra de scroll.
								                        \fn			virtual TIPO_DEVUELTO Evento_BarraScrollEx_BotonEx_Click(const UINT IDBarraEx, const UINT nBoton);
								                        \param[in]	IDBotonEx	: ID del boton extendido presionado dentro de la barra de scroll.
								                        \param[in]	nBoton		: Boton del mouse que se ha presionado.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                        */
		        inline virtual TIPO_DEVUELTO    Evento_BarraScrollEx_BotonEx_Click(const UINT IDBotonEx, const UINT nBoton) { return VALOR_DEVUELTO; };

                                                //////////////
                                                // -BotonEx //
                                                //////////////

							                    //! Función virtual que recibira cuando se hace click con el mouse en el BotonEx.
							                    /*! Esta función virtual recibira cuando se hace click con el mouse en el BotonEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_BotonEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDBotonEx, const UINT Param);
									                    \param[in]	Boton		: Boton presionado, los botones del mouse extendidos empiezan a partir del 3.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	IDBotonEx	: ID del boton extendido.
									                    \param[in]	Param    	: Teclas del sistema presionadas.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
               inline virtual TIPO_DEVUELTO     Evento_BotonEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDBotonEx, const UINT Param) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira cuando se suelta un boton del mouse en el BotonEx.
							                    /*! Esta función virtual recibira cuando se suelta un boton del mouse en el BotonEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_BotonEx_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT IDBotonEx, const UINT Param);
									                    \param[in]	nBoton		: Boton presionado, los botones del mouse extendidos empiezan a partir del 3.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	IDBotonEx	: ID del boton extendido.
									                    \param[in]	Param    	: Teclas del sistema presionadas.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
               inline virtual TIPO_DEVUELTO     Evento_BotonEx_Mouse_BotonPresionado(const UINT Boton, const int cX, const int cY, const UINT IDBotonEx, const UINT Param) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira cuando se suelta un boton del mouse en el BotonEx.
							                    /*! Esta función virtual recibira cuando se suelta un boton del mouse en el BotonEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_BotonEx_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT IDBotonEx, const UINT Param);
									                    \param[in]	nBoton		: Boton presionado, los botones del mouse extendidos empiezan a partir del 3.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	IDBotonEx	: ID del boton extendido.
									                    \param[in]	Param    	: Teclas del sistema presionadas.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
               inline virtual TIPO_DEVUELTO     Evento_BotonEx_Mouse_BotonSoltado(const UINT Boton, const int cX, const int cY, const UINT IDBotonEx, const UINT Param) { return VALOR_DEVUELTO; };

           							            //! Función virtual que recibira cuando se suelta un boton del mouse en el BotonEx.
							                    /*! Esta función virtual recibira cuando se suelta un boton del mouse en el BotonEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_BotonEx_Mouse_Movimiento(const int cX, const int cY, const UINT IDBotonEx);
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	IDBotonEx	: ID del boton extendido.
									                    \param[in]	Param    	: Teclas del sistema presionadas.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
               inline virtual TIPO_DEVUELTO     Evento_BotonEx_Mouse_Movimiento(const int cX, const int cY, const UINT IDBotonEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYDOWN del BotonEx.
							                    /*! Esta función virtual recibira los mensajes WM_KEYDOWN del BotonEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_BotonEx_Teclado_TeclaPresionada(const UINT Caracter, const UINT IDBotonEx);
									                    \param[in]	Caracter	: Tecla virtual soltada.
									                    \param[in]	IDBotonEx	: ID del BotonEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
               inline virtual TIPO_DEVUELTO     Evento_BotonEx_Teclado_TeclaPresionada(const UINT Caracter, const UINT IDBotonEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYUP del BotonEx.
							                    /*! Esta función virtual recibira los mensajes WM_KEYUP del BotonEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_BotonEx_Teclado_TeclaSoltada(const UINT Caracter, const UINT IDBotonEx);
									                    \param[in]	Caracter	: Tecla virtual soltada.
									                    \param[in]	IDBotonEx	: ID del BotonEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
               inline virtual TIPO_DEVUELTO     Evento_BotonEx_Teclado_TeclaSoltada(const UINT Caracter, const UINT IDBotonEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_SETFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_SETFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_BotonEx_Foco_Obtenido(const UINT IDBotonEx);
									                    \param[in]	IDBotonEx	: ID del BotonEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
               inline virtual TIPO_DEVUELTO     Evento_BotonEx_Foco_Obtenido(const UINT IDBotonEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_KILLFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_KILLFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_BotonEx_Foco_Perdido(const UINT IDBotonEx);
									                    \param[in]	IDBotonEx	: ID del BotonEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
               inline virtual TIPO_DEVUELTO     Evento_BotonEx_Foco_Perdido(const UINT IDBotonEx) { return VALOR_DEVUELTO; };


                                                ///////////////////////////
                                                // -EdicionDesplegableEx //
                                                ///////////////////////////

							                    //! Función virtual que recibira cuando cambia el texto en el control EdicionDesplegableEx.
							                    /*! Esta función virtual recibira cuando cambia el texto en el control EdicionDesplegableEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_EdicionDesplegableEx_CambioSeleccion(const TCHAR *NuevoTexto, const UINT IDEdicionTexto);
									                    \param[in]	NuevoTexto	    : Nuevo texto principal en el control.
									                    \param[in]	IDEdicionTexto	: ID del control.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
               inline virtual TIPO_DEVUELTO     Evento_EdicionDesplegableEx_CambioSeleccion(const TCHAR *NuevoTexto, const UINT IDEdicionTexto) { return VALOR_DEVUELTO; };


                                                //////////////
                                                // -ListaEx //
                                                //////////////

							                    //! Función virtual que recibira los DobleClick de la ListaEx.
							                    /*! Esta función virtual recibira los DobleClick de la ListaEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListaEx_Mouse_DobleClick(const UINT nBoton, const int cX, const int cY, DWL::ControlesEx::DWLListaEx_Item *Item, const UINT IDListaEx);
									                    \param[in]	nBoton		: Boton presionado, los botones del mouse extendidos empiezan a partir del 3.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	Item		: Item presionado en la lista (Puede ser NULL).
									                    \param[in]	IDListaEx	: ID de la ListaEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO	    Evento_ListaEx_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, DWL::ControlesEx::DWLListaEx_Item *Item, const UINT IDListaEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los Click de la ListaEx.
							                    /*! Esta función virtual recibira los Click de la ListaEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListaEx_Mouse_Click(const UINT nBoton, const int cX, const int cY, DWL::ControlesEx::DWLListaEx_Item *Item, const UINT IDListaEx);
									                    \param[in]	nBoton		: Boton presionado, los botones del mouse extendidos empiezan a partir del 3.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	Item		: Item presionado en la lista (Puede ser NULL).
									                    \param[in]	IDListaEx	: ID de la ListaEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
               inline virtual TIPO_DEVUELTO     Evento_ListaEx_Mouse_Click(const UINT Boton, const int cX, const int cY, DWL::ControlesEx::DWLListaEx_Item *Item, const UINT IDListaEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYDOWN de la ListaEx.
							                    /*! Esta función virtual recibira los mensajes WM_KEYDOWN de la ListaEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListaEx_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDListaEx);
									                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
									                    \param[in]	IDListaEx		: ID de la ListaEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO	    Evento_ListaEx_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDListaEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYUP de la ListaEx.
							                    /*! Esta función virtual recibira los mensajes WM_KEYUP de la ListaEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListaEx_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDListaEx);
									                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
									                    \param[in]	IDListaEx		: ID de la ListaEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO	    Evento_ListaEx_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDListaEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira cuando se presiona el Intro en la ListaEx.
							                    /*! Esta función virtual que recibira cuando se presiona el Intro en la ListaEx..
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListaEx_Teclado_Intro(const UINT IDListaEx);
									                    \param[in]	IDListaEx		: ID de la ListaEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_ListaEx_Teclado_Intro(const UINT IDListaEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira cuando se empieza la edición de un item de la ListaEx.
							                    /*! Esta función virtual recibira cuando se empieza la edición de un item de la ListaEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListaEx_LabelEdit_Inicio(DWL::ControlesEx::DWLListaEx_ParametrosLabelEdit *Edicion, const UINT IDListaEx);
									                    \param[in]	nEdicion	: Clase DWL::ControlesEx::DWLListaEx_ParametrosLabelEdit que contiene los datos del item a editar.
									                    \param[in]	IDListaEx	: ID de la ListaEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO	    Evento_ListaEx_LabelEdit_Inicio(DWL::ControlesEx::DWLListaEx_ParametrosLabelEdit *Edicion, const UINT IDListaEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira cuando se termina la edición de un Item de la ListaEx.
							                    /*! Esta función virtual recibira cuando se termina la edición de un Item de la ListaEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListaEx_LabelEdit_Fin(DWL::ControlesEx::DWLListaEx_ParametrosLabelEdit *nEdicion, const UINT IDListaEx);
									                    \param[in]	nEdicion	: Clase DWL::ControlesEx::DWLListaEx_ParametrosLabelEdit que contiene los datos del item editado, y funciones para retocar el resultado.
									                    \param[in]	IDListaEx	: ID de la ListaEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO 	Evento_ListaEx_LabelEdit_Fin(DWL::ControlesEx::DWLListaEx_ParametrosLabelEdit *Edicion, const UINT IDListaEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira cuando se cancela la edición de un item de la ListaEx.
							                    /*! Esta función virtual recibira cuando se cancela la edición de un item de la ListaEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListaEx_LabelEdit_Cancelado(const UINT eItem, const UINT eSubItem, const UINT IDListaEx);
									                    \param[in]	eItem   	: Item que se estaba editando.
									                    \param[in]	eSubItem	: SubItem que se estaba editando.
									                    \param[in]	IDListaEx	: ID de la ListaEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
               inline virtual TIPO_DEVUELTO     Evento_ListaEx_LabelEdit_Cancelado(const UINT eItem, const UINT eSubItem, const UINT IDListaEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_SETFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_SETFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListaEx_Foco_Obtenido(const UINT IDListaEx);
									                    \param[in]	IDListaEx	: ID de la ListaEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO	    Evento_ListaEx_Foco_Obtenido(const UINT IDListaEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_KILLFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_KILLFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListaEx_Foco_Perdido(const UINT IDListaEx);
									                    \param[in]	IDListaEx	: ID de la ListaEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_ListaEx_Foco_Perdido(const UINT IDListaEx) { return VALOR_DEVUELTO; };


                                                //////////////
                                                // -MarcaEx //
                                                //////////////

							                    //! Función virtual que recibira cuando se hace click en la MarcaEx.
							                    /*! Esta función virtual recibira cuando se hace click en la MarcaEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_MarcaEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDMarcaEx);
									                    \param[in]	Boton	  : Boton presionado del mouse.
									                    \param[in]	cX	      : Coordenada X del mouse.
									                    \param[in]	cY	      : Coordenada Y del mouse.
									                    \param[in]	IDMarcaEx : ID del control MarcaEx que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
               inline virtual TIPO_DEVUELTO     Evento_MarcaEx_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDMarcaEx) { return VALOR_DEVUELTO; };


                                                /////////////
                                                // -MenuEx //
                                                /////////////

							                    //! Función virtual que recibira cuando se pulsa encima de un MenuEx.
							                    /*! Esta función virtual recibira cuando se pulsa encima de un MenuEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_MenuEx_Menu_Pulsado(DWL::ControlesEx::DWLMenuEx *MenuPulsado, const UINT IDMenuExPadre);
									                    \param[in]	MenuPulsado	  : clase DWLMenuEx que se ha pulsado.
									                    \param[in]	IDMenuExPadre : ID del menu pulsado.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_MenuEx_Menu_Pulsado(DWL::ControlesEx::DWLMenuEx *MenuPulsado, const UINT IDMenuExPadre) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira cuando se muestra un MenuEx.
							                    /*! Esta función virtual recibira cuando se muestra un MenuEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_MenuEx_Menu_Mostrado(UINT IDMenuEx);
									                    \param[in]	IDMenuEx	  : clase DWLMenuEx que se ha mostrado.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_MenuEx_Menu_Mostrado(const UINT IDMenuEx) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira cuando se oculta un MenuEx.
							                    /*! Esta función virtual recibira cuando se oculta un MenuEx.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_MenuEx_Menu_Ocultado(UINT IDMenuEx);
									                    \param[in]	IDMenuEx	  : clase DWLMenuEx que se ha ocultado.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_MenuEx_Menu_Ocultado(const UINT IDMenuEx) { return VALOR_DEVUELTO; };


                                                ///////////////
                                                // -ComboBox //
                                                ///////////////

							                    //! Función virtual que recibira los DobleClick del ComboBox.
							                    /*! Esta función virtual recibira los DobleClick del ComboBox.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ComboBox_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT IDComboBox);
									                    \param[in]	Boton		: Boton presionado.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	IDComboBox	: ID del ComboBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO	    Evento_ComboBox_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT IDComboBox) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los Click del ComboBox.
							                    /*! Esta función virtual recibira los Click del ComboBox.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ComboBox_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDComboBox);
									                    \param[in]	Boton		: Boton presionado.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	IDComboBox	: ID del ComboBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO	    Evento_ComboBox_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDComboBox) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYDOWN del ComboBox.
							                    /*! Esta función virtual recibira los mensajes WM_KEYDOWN del ComboBox.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ComboBox_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDComboBox);
									                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
									                    \param[in]	IDComboBox		: ID del ComboBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_ComboBox_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDComboBox) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYUP del ComboBox.
							                    /*! Esta función virtual recibira los mensajes WM_KEYUP del ComboBox.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ComboBox_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDComboBox);
									                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
									                    \param[in]	IDComboBox		: ID del ComboBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_ComboBox_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDComboBox) { return VALOR_DEVUELTO; };

                                                //! Función virtual que recibira cuando se presiona el intro en el ComboBox.
                                                /*! Esta función virtual recibira cuando se presiona el intro en el ComboBox.
		                                                \fn			inline virtual TIPO_DEVUELTO Evento_ComboBox_Teclado_Intro(const UINT IDComboBox);
		                                                \param[in]	IDComboBox		: ID del ComboBox que manda el evento.
		                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                                */
               inline virtual TIPO_DEVUELTO     Evento_ComboBox_Teclado_Intro(const UINT IDComboBox) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_SETFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_SETFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ComboBox_Foco_Obtenido(const UINT IDComboBox);
									                    \param[in]	IDComboBox	: ID del ComboBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_ComboBox_Foco_Obtenido(const UINT IDComboBox) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_KILLFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_KILLFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ComboBox_Foco_Perdido(const UINT IDComboBox);
									                    \param[in]	IDComboBox	: ID del ComboBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_ComboBox_Foco_Perdido(const UINT IDComboBox) { return VALOR_DEVUELTO; };


                                                ///////////////
                                                // -EditBox  //
                                                ///////////////

							                    //! Función virtual que recibira los DobleClick del EditBox.
							                    /*! Esta función virtual recibira los DobleClick del EditBox.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_EditBox_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT IDEditBox);
									                    \param[in]	Boton		: Boton presionado.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	IDEditBox	: ID del EditBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO	    Evento_EditBox_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT IDEditBox) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los Click del EditBox.
							                    /*! Esta función virtual recibira los Click del EditBox.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_EditBox_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDEditBox);
									                    \param[in]	Boton		: Boton presionado.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	IDEditBox	: ID del EditBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO	    Evento_EditBox_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDEditBox) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYDOWN del EditBox.
							                    /*! Esta función virtual recibira los mensajes WM_KEYDOWN del EditBox.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_EditBox_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDEditBox);
									                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
									                    \param[in]	IDEditBox		: ID del EditBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_EditBox_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDEditBox) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYUP del EditBox.
							                    /*! Esta función virtual recibira los mensajes WM_KEYUP del EditBox.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_EditBox_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDEditBox);
									                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
									                    \param[in]	IDEditBox		: ID del EditBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_EditBox_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDEditBox) { return VALOR_DEVUELTO; };

                                                //! Función virtual que recibira cuando se presiona el intro en el EditBox.
                                                /*! Esta función virtual recibira cuando se presiona el intro en el EditBox.
		                                                \fn			inline virtual TIPO_DEVUELTO Evento_EditBox_Teclado_Intro(const UINT IDEditBox);
		                                                \param[in]	IDEditBox   : ID del EditBox que manda el evento.
		                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                                */
		       inline virtual TIPO_DEVUELTO     Evento_EditBox_Teclado_Intro(const UINT IDEditBox) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_SETFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_SETFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_EditBox_Foco_Obtenido(const UINT IDEditBox);
									                    \param[in]	IDEditBox	: ID del EditBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_EditBox_Foco_Obtenido(const UINT IDEditBox) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_KILLFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_KILLFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_EditBox_Foco_Perdido(const UINT IDEditBox);
									                    \param[in]	IDEditBox	: ID del EditBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_EditBox_Foco_Perdido(const UINT IDEditBox) { return VALOR_DEVUELTO; };


                                                ///////////////
                                                // -ListBox  //
                                                ///////////////

							                    //! Función virtual que recibira los DobleClick del ListBox.
							                    /*! Esta función virtual recibira los DobleClick del ListBox.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListBox_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT IDListBox);
									                    \param[in]	Boton		: Boton presionado.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	IDListBox	: ID del ListBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO	    Evento_ListBox_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT IDListBox) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los Click del ListBox.
							                    /*! Esta función virtual recibira los Click del ListBox.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListBox_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDListBox);
									                    \param[in]	Boton		: Boton presionado.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	IDListBox	: ID del ListBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO	    Evento_ListBox_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDListBox) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYDOWN del ListBox.
							                    /*! Esta función virtual recibira los mensajes WM_KEYDOWN del ListBox.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListBox_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDListBox);
									                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
									                    \param[in]	IDListBox		: ID del ListBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_ListBox_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDListBox) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYUP del ListBox.
							                    /*! Esta función virtual recibira los mensajes WM_KEYUP del ListBox.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListBox_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDListBox);
									                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
									                    \param[in]	IDListBox		: ID del ListBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_ListBox_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDListBox) { return VALOR_DEVUELTO; };

                                                //! Función virtual que recibira cuando se presiona el intro en el ListBox.
                                                /*! Esta función virtual recibira cuando se presiona el intro en el ListBox.
		                                                \fn			inline virtual TIPO_DEVUELTO Evento_ListBox_Teclado_Intro(const UINT IDListBox);
		                                                \param[in]	IDListBox   : ID del ListBox que manda el evento.
		                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                                */
		       inline virtual TIPO_DEVUELTO     Evento_ListBox_Teclado_Intro(const UINT IDListBox) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_SETFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_SETFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListBox_Foco_Obtenido(const UINT IDListBox);
									                    \param[in]	IDListBox	: ID del ListBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_ListBox_Foco_Obtenido(const UINT IDListBox) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_KILLFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_KILLFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListBox_Foco_Perdido(const UINT IDListBox);
									                    \param[in]	IDListBox	: ID del ListBox que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_ListBox_Foco_Perdido(const UINT IDListBox) { return VALOR_DEVUELTO; };


                                                ////////////////
                                                // -ListView  //
                                                ////////////////

							                    //! Función virtual que recibira los DobleClick del ListView.
							                    /*! Esta función virtual recibira los DobleClick del ListView.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT IDListView);
									                    \param[in]	Boton		: Boton presionado.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	IDListView	: ID del ListView que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_ListView_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT IDListView) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los Click del ListView.
							                    /*! Esta función virtual recibira los Click del ListView.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDListView);
									                    \param[in]	Boton		: Boton presionado.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	IDListView	: ID del ListView que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO	    Evento_ListView_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDListView) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYDOWN del ListView.
							                    /*! Esta función virtual recibira los mensajes WM_KEYDOWN del ListView.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDListView);
									                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
									                    \param[in]	IDListView		: ID del ListView que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_ListView_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDListView) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYUP del ListView.
							                    /*! Esta función virtual recibira los mensajes WM_KEYUP del ListView.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDListView);
									                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
									                    \param[in]	IDListView		: ID del ListView que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_ListView_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDListView) { return VALOR_DEVUELTO; };

                                                //! Función virtual que recibira cuando se presiona el intro en el ListView.
                                                /*! Esta función virtual recibira cuando se presiona el intro en el ListView.
		                                                \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Teclado_Intro(const UINT IDListView);
		                                                \param[in]	IDListView   : ID del ListView que manda el evento.
		                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                                */
               inline virtual TIPO_DEVUELTO     Evento_ListView_Teclado_Intro(const UINT IDListView) { return VALOR_DEVUELTO; };

                                                //! Función virtual que recibira cuando se inicia la edicion de un item en el ListView.
                                                /*! Esta función virtual recibira cuando se inicia la edicion de un item en el ListView.
		                                                \fn			inline virtual TIPO_DEVUELTO Evento_ListView_LabelEdit_Inicio(const UINT eItem, const UINT eSubItem, const UINT IDListView);
		                                                \param[in]	eItem      : Item en edicion.
		                                                \param[in]	eSubItem   : SubItem en edicion.
		                                                \param[in]	IDListView : ID del ListView que manda el evento.
		                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                                */
		       inline virtual TIPO_DEVUELTO     Evento_ListView_LabelEdit_Inicio(const UINT eItem, const UINT eSubItem, const UINT IDListView) { return VALOR_DEVUELTO; };

                                                //! Función virtual que recibira cuando se termina la edicion de un item en el ListView.
                                                /*! Esta función virtual recibira cuando se termina la edicion de un item en el ListView.
		                                                \fn			inline virtual TIPO_DEVUELTO Evento_ListView_LabelEdit_Fin(DWL::Controles::DWLListView_TerminarLabelEdit *Edicion, const UINT IDListView);
		                                                \param[in]	Edicion    : Clase que contiene metodos para modificar la edicion.
		                                                \param[in]	IDListView : ID del ListView que manda el evento.
		                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                                */
		       inline virtual TIPO_DEVUELTO     Evento_ListView_LabelEdit_Fin(DWL::Controles::DWLListView_TerminarLabelEdit *Edicion, const UINT IDListView) { return VALOR_DEVUELTO; };

                                                //! Función virtual que recibira cuando se inicia la edicion de un item en el ListView.
                                                /*! Esta función virtual recibira cuando se inicia la edicion de un item en el ListView.
		                                                \fn			inline virtual TIPO_DEVUELTO Evento_ListView_LabelEdit_Cancelado(const UINT eItem, const UINT eSubItem, const UINT IDListView);
		                                                \param[in]	eItem      : Item en edicion.
		                                                \param[in]	eSubItem   : SubItem en edicion.
		                                                \param[in]	IDListView : ID del ListView que manda el evento.
		                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                                */
		       inline virtual TIPO_DEVUELTO     Evento_ListView_LabelEdit_Cancelado(const UINT eItem, const UINT eSubItem, const UINT IDListView) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_SETFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_SETFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Foco_Obtenido(const UINT IDListView);
									                    \param[in]	IDListView	: ID del ListView que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_ListView_Foco_Obtenido(const UINT IDListView) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_KILLFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_KILLFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Foco_Perdido(const UINT IDListView);
									                    \param[in]	IDListView	: ID del ListView que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_ListView_Foco_Perdido(const UINT IDListView) { return VALOR_DEVUELTO; };


                                                ////////////////
                                                // -TreeView  //
                                                ////////////////

							                    //! Función virtual que recibira los DobleClick del TreeView.
							                    /*! Esta función virtual recibira los DobleClick del TreeView.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT IDTreeView);
									                    \param[in]	Boton		: Boton presionado.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	IDTreeView	: ID del TreeView que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO	    Evento_TreeView_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT IDTreeView) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los Click del TreeView.
							                    /*! Esta función virtual recibira los Click del TreeView.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDTreeView);
									                    \param[in]	Boton		: Boton presionado.
									                    \param[in]	cX			: Coordenada X del mouse.
									                    \param[in]	cY			: Coordenada Y del mouse.
									                    \param[in]	IDTreeView	: ID del TreeView que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO	    Evento_TreeView_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDTreeView) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYDOWN del TreeView.
							                    /*! Esta función virtual recibira los mensajes WM_KEYDOWN del TreeView.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDTreeView);
									                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
									                    \param[in]	IDTreeView		: ID del TreeView que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_TreeView_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDTreeView) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira los mensajes WM_KEYUP del TreeView.
							                    /*! Esta función virtual recibira los mensajes WM_KEYUP del TreeView.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDTreeView);
									                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
									                    \param[in]	IDTreeView		: ID del TreeView que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_TreeView_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDTreeView) { return VALOR_DEVUELTO; };

                                                //! Función virtual que recibira cuando se presiona el intro en el TreeView.
                                                /*! Esta función virtual recibira cuando se presiona el intro en el TreeView.
		                                                \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_Teclado_Intro(const UINT IDTreeView);
		                                                \param[in]	IDTreeView   : ID del TreeView que manda el evento.
		                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                                */
               inline virtual TIPO_DEVUELTO     Evento_TreeView_Teclado_Intro(const UINT IDTreeView) { return VALOR_DEVUELTO; };

                                                //! Función virtual que recibira cuando se inicia la edicion de un nodo en el TreeView.
                                                /*! Esta función virtual recibira cuando se inicia la edicion de un nodo en el TreeView.
		                                                \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_LabelEdit_Inicio(DWL::Controles::DWLTreeView_Nodo *eNodo, const UINT IDTreeView);
		                                                \param[in]	eNodo      : Nodo en edicion.
		                                                \param[in]	IDTreeView : ID del ListView que manda el evento.
		                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                                */
		       inline virtual TIPO_DEVUELTO     Evento_TreeView_LabelEdit_Inicio(DWL::Controles::DWLTreeView_Nodo *eNodo, const UINT IDTreeView) { return VALOR_DEVUELTO; };

                                                //! Función virtual que recibira cuando se termina la edicion de un nodo en el TreeView.
                                                /*! Esta función virtual recibira cuando se termina la edicion de un nodo en el TreeView.
		                                                \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_LabelEdit_Fin(DWL::Controles::DWLTreeView_TerminarLabelEdit *Edicion, const UINT IDTreeView);
		                                                \param[in]	Edicion    : Clase que contiene metodos para modificar la edicion.
		                                                \param[in]	IDTreeView : ID del ListView que manda el evento.
		                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                                */
		       inline virtual TIPO_DEVUELTO     Evento_TreeView_LabelEdit_Fin(DWL::Controles::DWLTreeView_TerminarLabelEdit *Edicion, const UINT IDTreeView) { return VALOR_DEVUELTO; };

                                                //! Función virtual que recibira cuando se cancela la edicion de un nodo en el TreeView.
                                                /*! Esta función virtual recibira cuando se cancela la edicion de un nodo en el TreeView.
		                                                \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_LabelEdit_Cancelado(DWL::Controles::DWLTreeView_Nodo *eNodo, const UINT IDTreeView);
		                                                \param[in]	eNodo      : Nodo en edicion.
		                                                \param[in]	IDTreeView : ID del ListView que manda el evento.
		                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                                */
		       inline virtual TIPO_DEVUELTO     Evento_TreeView_LabelEdit_Cancelado(DWL::Controles::DWLTreeView_Nodo *eNodo, const UINT IDTreeView) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_SETFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_SETFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_Foco_Obtenido(const UINT IDTreeView);
									                    \param[in]	IDTreeView	: ID del TreeView que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_TreeView_Foco_Obtenido(const UINT IDTreeView) { return VALOR_DEVUELTO; };

							                    //! Función virtual que recibira el mensaje WM_KILLFOCUS.
							                    /*! Esta función virtual recibira el mensaje WM_KILLFOCUS.
									                    \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_Foco_Perdido(const UINT IDTreeView);
									                    \param[in]	IDTreeView	: ID del TreeView que manda el evento.
									                    \return		Si re-emplazas esta funcion, debes retornar 0.
							                    */
		       inline virtual TIPO_DEVUELTO     Evento_TreeView_Foco_Perdido(const UINT IDTreeView) { return VALOR_DEVUELTO; };

		      protected: ///////////////////////// -Declaraciones protegidas (Solo podran usarse en la clase heredada no desde fuera)

								                //! Clase que contiene la lista de tabulaciones para esta ventana.
               DWLListaTabuladores		        ListaTabuladores;

								                //! Esqueleto para los mensajes de la ventana.
								                /*! Esta función es el esqueleto para los mensajes de la ventana.
										                \fn			inline virtual TIPO_DEVUELTO CALLBACK	GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
										                \param[in]	uMsg	: Mensaje.
										                \param[in]	wParam	: Parametro1.
										                \param[in]	lParam	: Parametro2.
										                \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
								                */
		       virtual TIPO_DEVUELTO CALLBACK   GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
													LRESULT Ret = 0;
                                                    switch (uMsg) {
														default :
															if (uMsg == _WM_TASK_BUTTON_CREATED) {
																Ret = Evento_BotonBarraTareas_Creado();
															    BarraTareas._CrearBotones();
																return Ret;
															}
															break;
                                                        // Tabulaciones
                                                        case DWL_TAB_OBTENER_POSICION :
                                                            return ListaTabuladores.ObtenerPosicion(static_cast<DWL::Ventanas::Base::DWLBaseWnd *>(LongToPtr(wParam)));
                                                        case DWL_TAB_CAMBIAR_POSICION :
                                                            ListaTabuladores.CambiarPosicion(static_cast<DWL::Ventanas::Base::DWLBaseWnd *>(LongToPtr(wParam)), static_cast<size_t>(lParam));
                                                            return FALSE;
                                                        case DWL_TAB_CAMBIO_FOCO :
                                                            ListaTabuladores.AsignarNuevaPosicion(static_cast<DWL::Ventanas::Base::DWLBaseWnd *>(LongToPtr(wParam)));
                                                            return FALSE;
                                                        case DWL_TAB_AGREGAR_CONTROL :
                                                            ListaTabuladores.AgregarControl(static_cast<DWL::Ventanas::Base::DWLBaseWnd *>(LongToPtr(wParam)));
                                                            return FALSE;
                                                        case DWL_TAB_SIGUIENTE :
                                                            ListaTabuladores.Siguiente();
                                                            return FALSE;
                                                        case DWL_TAB_ANTERIOR :
                                                            ListaTabuladores.Anterior();
                                                            return FALSE;
                                                        case DWL_TAB_BORRAR_CONTROL	:
                                                            ListaTabuladores.BorrarControl(this);
                                                            return FALSE;

                                                        // Notificacion CUSTOMDRAW para los controles estandar tipo listview y treeview
				                                        case WM_NOTIFY :
					                                        if (((LPNMHDR)lParam)->code == static_cast<UINT>(NM_CUSTOMDRAW)) return SendMessage(((LPNMHDR)lParam)->hwndFrom, DWL_CUSTOM_DRAW, wParam, lParam);
					                                        break;

				                                        // notificaciones para cambios de colores en controles estandard 
				                                        case 0x0132 :	case 0x0133 :	case 0x0134 :	case 0x0135	:	case 0x0136 :	case 0x0137 :	case 0x0138 :	case 0x0139 :
					                                        return SendMessage((HWND)lParam, uMsg, wParam, 0);

                                                        // ArbolEx
                                                        case DWL_ARBOLEX_DOBLECLICK	:
	                                                        DWL::ControlesEx::DWLArbolEx_ParametrosClick *Parametro1;
                                                            Parametro1 = reinterpret_cast<DWL::ControlesEx::DWLArbolEx_ParametrosClick *>(wParam);
	                                                        return this->Evento_ArbolEx_Mouse_DobleClick(Parametro1->Boton(), Parametro1->X(), Parametro1->Y(), Parametro1->Nodo(), Parametro1->IDArbolEx());
                                                        case DWL_ARBOLEX_CLICK :
	                                                        DWL::ControlesEx::DWLArbolEx_ParametrosClick *Parametro2;
                                                            Parametro2 = reinterpret_cast<DWL::ControlesEx::DWLArbolEx_ParametrosClick *>(wParam);
	                                                        return this->Evento_ArbolEx_Mouse_Click(Parametro2->Boton(), Parametro2->X(), Parametro2->Y(), Parametro2->Nodo(), Parametro2->IDArbolEx());
                                                        case DWL_ARBOLEX_TECLADO_PRESIONADO	:
	                                                        return this->Evento_ArbolEx_Teclado_TeclaPresionada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_ARBOLEX_TECLADO_SOLTADO :
	                                                        return this->Evento_ArbolEx_Teclado_TeclaSoltada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_ARBOLEX_TECLADO_INTRO :
	                                                        return this->Evento_ArbolEx_Teclado_Intro(static_cast<UINT>(lParam));
                                                        case DWL_ARBOLEX_LABELEDIT_INICIO :
	                                                        return this->Evento_ArbolEx_LabelEdit_Inicio(reinterpret_cast<DWL::ControlesEx::DWLArbolEx_Nodo *>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_ARBOLEX_LABELEDIT_FIN	:
	                                                        return this->Evento_ArbolEx_LabelEdit_Fin(reinterpret_cast<DWL::ControlesEx::DWLArbolEx_TerminarLabelEdit *>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_ARBOLEX_LABELEDIT_CANCELADO :
	                                                        return this->Evento_ArbolEx_LabelEdit_Cancelado(reinterpret_cast<DWL::ControlesEx::DWLArbolEx_Nodo *>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_ARBOLEX_FOCO_OBTENIDO :
	                                                        return this->Evento_ArbolEx_Foco_Obtenido(static_cast<UINT>(wParam));
                                                        case DWL_ARBOLEX_FOCO_PERDIDO :
	                                                        return this->Evento_ArbolEx_Foco_Perdido(static_cast<UINT>(wParam));

                                                        // BarraEx
                                                        case DWL_BARRAEX_NUEVO_VALOR :
	                                                        return this->Evento_BarraEx_CambioValor(static_cast<UINT>(wParam));
                                                        case DWL_BARRAEX_MOUSE_BOTONSOLTADO	:
	                                                        return this->Evento_BarraEx_Mouse_BotonSoltado(static_cast<UINT>(wParam), static_cast<UINT>(lParam));

                                                        // BarraScrollEx
                                                        case DWL_BARRASCROLLEX_BOTONEX_CLICK :
                                                            return this->Evento_BarraScrollEx_BotonEx_Click(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
                                                            break;

                                                        // BotonEx
	                                                    case DWL_BOTONEX_CLICK :
		                                                    DWL::ControlesEx::DWLBotonEx_ParametrosClick *Parametro7;
		                                                    Parametro7 = reinterpret_cast<DWL::ControlesEx::DWLBotonEx_ParametrosClick *>(wParam);
		                                                    return this->Evento_BotonEx_Mouse_Click(Parametro7->Boton(), Parametro7->X(), Parametro7->Y(), Parametro7->IDBotonEx(), Parametro7->Param());
	                                                    case DWL_BOTONEX_MOUSE_BOTONPRESIONADO :
		                                                    DWL::ControlesEx::DWLBotonEx_ParametrosClick *Parametro3;
		                                                    Parametro3 = reinterpret_cast<DWL::ControlesEx::DWLBotonEx_ParametrosClick *>(wParam);
		                                                    return this->Evento_BotonEx_Mouse_BotonPresionado(Parametro3->Boton(), Parametro3->X(), Parametro3->Y(), Parametro3->IDBotonEx(), Parametro3->Param());
	                                                    case DWL_BOTONEX_MOUSE_BOTONSOLTADO	:
		                                                    DWL::ControlesEx::DWLBotonEx_ParametrosClick *Parametro4;
		                                                    Parametro4 = reinterpret_cast<DWL::ControlesEx::DWLBotonEx_ParametrosClick *>(wParam);
		                                                    return this->Evento_BotonEx_Mouse_BotonSoltado(Parametro4->Boton(), Parametro4->X(), Parametro4->Y(), Parametro4->IDBotonEx(), Parametro4->Param());
	                                                    case DWL_BOTONEX_MOUSE_MOVIMIENTO :
		                                                    return this->Evento_BotonEx_Mouse_Movimiento(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
	                                                    case DWL_BOTONEX_TECLADO_PRESIONADO	:
		                                                    return this->Evento_BotonEx_Teclado_TeclaPresionada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_BOTONEX_TECLADO_SOLTADO :
	                                                        return this->Evento_BotonEx_Teclado_TeclaSoltada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
	                                                    case DWL_BOTONEX_FOCO_OBTENIDO :
		                                                    return this->Evento_BotonEx_Foco_Obtenido(static_cast<UINT>(wParam));
	                                                    case DWL_BOTONEX_FOCO_PERDIDO :
		                                                    return this->Evento_BotonEx_Foco_Perdido(static_cast<UINT>(wParam));

                                                        // EdicionDesplegableEx
                                                        case DWL_EDICIONDESPLEGABLEEX_CAMBIO_SELECCION :
                                                            return this->Evento_EdicionDesplegableEx_CambioSeleccion(static_cast<TCHAR *>(LongToPtr(wParam)), static_cast<UINT>(lParam));

                                                        // ListaEx
	                                                    case DWL_LISTAEX_DOBLECLICK	:
		                                                    DWL::ControlesEx::DWLListaEx_ParametrosClick *Parametro5;
                                                            Parametro5 = reinterpret_cast<DWL::ControlesEx::DWLListaEx_ParametrosClick *>(wParam);
		                                                    return this->Evento_ListaEx_Mouse_DobleClick(Parametro5->Boton(), Parametro5->X(), Parametro5->Y(), Parametro5->Item(), Parametro5->IDListaEx());
	                                                    case DWL_LISTAEX_CLICK :
		                                                    DWL::ControlesEx::DWLListaEx_ParametrosClick *Parametro6;
                                                            Parametro6 = reinterpret_cast<DWL::ControlesEx::DWLListaEx_ParametrosClick *>(wParam);
		                                                    return this->Evento_ListaEx_Mouse_Click(Parametro6->Boton(), Parametro6->X(), Parametro6->Y(), Parametro6->Item(), Parametro6->IDListaEx());
	                                                    case DWL_LISTAEX_TECLADO_PRESIONADO	:
		                                                    return this->Evento_ListaEx_Teclado_TeclaPresionada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
	                                                    case DWL_LISTAEX_TECLADO_SOLTADO :
		                                                    return this->Evento_ListaEx_Teclado_TeclaSoltada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
	                                                    case DWL_LISTAEX_TECLADO_INTRO :
		                                                    return this->Evento_ListaEx_Teclado_Intro(static_cast<UINT>(lParam));
	                                                    case DWL_LISTAEX_LABELEDIT_INICIO :
//		                                                    return this->Evento_ListaEx_LabelEdit_Inicio(LOWORD(wParam), HIWORD(wParam), static_cast<UINT>(lParam));
                                                            return this->Evento_ListaEx_LabelEdit_Inicio(reinterpret_cast<DWL::ControlesEx::DWLListaEx_ParametrosLabelEdit *>(wParam), static_cast<UINT>(lParam));
	                                                    case DWL_LISTAEX_LABELEDIT_FIN :
                                                            return this->Evento_ListaEx_LabelEdit_Fin(reinterpret_cast<DWL::ControlesEx::DWLListaEx_ParametrosLabelEdit *>(wParam), static_cast<UINT>(lParam));
	                                                    case DWL_LISTAEX_LABELEDIT_CANCELADO :
		                                                    return this->Evento_ListaEx_LabelEdit_Cancelado(LOWORD(wParam), HIWORD(wParam), static_cast<UINT>(lParam));
                                                        case DWL_LISTAEX_FOCO_OBTENIDO :
	                                                        return this->Evento_ListaEx_Foco_Obtenido(static_cast<UINT>(wParam));
	                                                    case DWL_LISTAEX_FOCO_PERDIDO :
		                                                    return this->Evento_ListaEx_Foco_Perdido(static_cast<UINT>(wParam));

                                                        // MarcaEx
	                                                    case DWL_MARCAEX_CLICK_DERECHO :
		                                                    return this->Evento_MarcaEx_Mouse_Click(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
	                                                    case DWL_MARCAEX_CLICK_IZQUIERDO :
		                                                    return this->Evento_MarcaEx_Mouse_Click(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
	                                                    case DWL_MARCAEX_CLICK_MEDIO :
		                                                    return this->Evento_MarcaEx_Mouse_Click(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));

                                                        // MenuEx
                                                        case DWL_MENUEX_MENU_PULSADO :
	                                                        return this->Evento_MenuEx_Menu_Pulsado(reinterpret_cast<DWL::ControlesEx::DWLMenuEx *>(wParam), static_cast<UINT>(lParam));
	                                                    case DWL_MENUEX_MENU_MOSTRADO :
		                                                    return this->Evento_MenuEx_Menu_Mostrado(static_cast<UINT>(wParam));
	                                                    case DWL_MENUEX_MENU_OCULTADO :
		                                                    return this->Evento_MenuEx_Menu_Ocultado(static_cast<UINT>(wParam));

                                                        // ComboBox
                                                        case DWL_COMBOBOX_DOBLECLICK_DERECHO :
                                                            return this->Evento_ComboBox_Mouse_DobleClick(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_COMBOBOX_DOBLECLICK_IZQUIERDO :
                                                            return this->Evento_ComboBox_Mouse_DobleClick(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_COMBOBOX_DOBLECLICK_MEDIO :
                                                            return this->Evento_ComboBox_Mouse_DobleClick(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_COMBOBOX_CLICK_DERECHO :
                                                            return this->Evento_ComboBox_Mouse_Click(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_COMBOBOX_CLICK_IZQUIERDO :
                                                            return this->Evento_ComboBox_Mouse_Click(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_COMBOBOX_CLICK_MEDIO :
                                                            return this->Evento_ComboBox_Mouse_Click(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_COMBOBOX_TECLADO_PRESIONADO :
                                                            return this->Evento_ComboBox_Teclado_TeclaPresionada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_COMBOBOX_TECLADO_SOLTADO :
                                                            return this->Evento_ComboBox_Teclado_TeclaSoltada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_COMBOBOX_TECLADO_INTRO :
                                                            return this->Evento_ComboBox_Teclado_Intro(static_cast<UINT>(lParam));
                                                        case DWL_COMBOBOX_FOCO_OBTENIDO :
                                                            return this->Evento_ComboBox_Foco_Obtenido(static_cast<UINT>(wParam));
                                                        case DWL_COMBOBOX_FOCO_PERDIDO :
                                                            return this->Evento_ComboBox_Foco_Perdido(static_cast<UINT>(wParam));

                                                        // EditBox
                                                        case DWL_EDITBOX_DOBLECLICK_DERECHO :
                                                            return this->Evento_EditBox_Mouse_DobleClick(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_EDITBOX_DOBLECLICK_IZQUIERDO :
                                                            return this->Evento_EditBox_Mouse_DobleClick(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_EDITBOX_DOBLECLICK_MEDIO :
                                                            return this->Evento_EditBox_Mouse_DobleClick(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_EDITBOX_CLICK_DERECHO :
                                                            return this->Evento_EditBox_Mouse_Click(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_EDITBOX_CLICK_IZQUIERDO :
                                                            return this->Evento_EditBox_Mouse_Click(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_EDITBOX_CLICK_MEDIO :
                                                            return this->Evento_EditBox_Mouse_Click(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_EDITBOX_TECLADO_PRESIONADO :
                                                            return this->Evento_EditBox_Teclado_TeclaPresionada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_EDITBOX_TECLADO_SOLTADO :
                                                            return this->Evento_EditBox_Teclado_TeclaSoltada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_EDITBOX_TECLADO_INTRO :
                                                            return this->Evento_EditBox_Teclado_Intro(static_cast<UINT>(lParam));
                                                        case DWL_EDITBOX_FOCO_OBTENIDO :
                                                            return this->Evento_EditBox_Foco_Obtenido(static_cast<UINT>(wParam));
                                                        case DWL_EDITBOX_FOCO_PERDIDO :
                                                            return this->Evento_EditBox_Foco_Perdido(static_cast<UINT>(wParam));

                                                        // ListBox
                                                        case DWL_LISTBOX_DOBLECLICK_DERECHO :
                                                            return this->Evento_ListBox_Mouse_DobleClick(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_LISTBOX_DOBLECLICK_IZQUIERDO :
                                                            return this->Evento_ListBox_Mouse_DobleClick(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_LISTBOX_DOBLECLICK_MEDIO :
                                                            return this->Evento_ListBox_Mouse_DobleClick(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_LISTBOX_CLICK_DERECHO :
                                                            return this->Evento_ListBox_Mouse_Click(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_LISTBOX_CLICK_IZQUIERDO :
                                                            return this->Evento_ListBox_Mouse_Click(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_LISTBOX_CLICK_MEDIO :
                                                            return this->Evento_ListBox_Mouse_Click(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_LISTBOX_TECLADO_PRESIONADO :
                                                            return this->Evento_ListBox_Teclado_TeclaPresionada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_LISTBOX_TECLADO_SOLTADO :
                                                            return this->Evento_ListBox_Teclado_TeclaSoltada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_LISTBOX_TECLADO_INTRO :
                                                            return this->Evento_ListBox_Teclado_Intro(static_cast<UINT>(lParam));
                                                        case DWL_LISTBOX_FOCO_OBTENIDO :
                                                            return this->Evento_ListBox_Foco_Obtenido(static_cast<UINT>(wParam));
                                                        case DWL_LISTBOX_FOCO_PERDIDO :
                                                            return this->Evento_ListBox_Foco_Perdido(static_cast<UINT>(wParam));

                                                        // ListView
                                                        case DWL_LISTVIEW_DOBLECLICK_IZQUIERDO	:
                                                            return this->Evento_ListView_Mouse_DobleClick(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_LISTVIEW_DOBLECLICK_DERECHO :
                                                            return this->Evento_ListView_Mouse_DobleClick(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_LISTVIEW_DOBLECLICK_MEDIO :
                                                            return this->Evento_ListView_Mouse_DobleClick(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_LISTVIEW_CLICK_IZQUIERDO :
                                                            return this->Evento_ListView_Mouse_Click(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_LISTVIEW_CLICK_DERECHO :
                                                            return this->Evento_ListView_Mouse_Click(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_LISTVIEW_CLICK_MEDIO :
                                                            return this->Evento_ListView_Mouse_Click(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_LISTVIEW_TECLADO_PRESIONADO :
                                                            return this->Evento_ListView_Teclado_TeclaPresionada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_LISTVIEW_TECLADO_SOLTADO :
                                                            return this->Evento_ListView_Teclado_TeclaSoltada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_LISTVIEW_TECLADO_INTRO	:
                                                            return this->Evento_ListView_Teclado_Intro(static_cast<UINT>(lParam));
                                                        case DWL_LISTVIEW_LABELEDIT_INICIO :
                                                            return this->Evento_ListView_LabelEdit_Inicio(LOWORD(wParam), HIWORD(wParam), static_cast<UINT>(lParam));
                                                        case DWL_LISTVIEW_LABELEDIT_FIN	:
                                                            return this->Evento_ListView_LabelEdit_Fin(reinterpret_cast<DWL::Controles::DWLListView_TerminarLabelEdit *>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_LISTVIEW_LABELEDIT_CANCELADO :
                                                            return this->Evento_ListView_LabelEdit_Cancelado(LOWORD(wParam), HIWORD(wParam), static_cast<UINT>(lParam));
                                                        case DWL_LISTVIEW_FOCO_OBTENIDO :
                                                            return this->Evento_ListView_Foco_Obtenido(static_cast<UINT>(wParam));
                                                        case DWL_LISTVIEW_FOCO_PERDIDO :
                                                            return this->Evento_ListView_Foco_Perdido(static_cast<UINT>(wParam));

                                                        // TreeView
                                                        case DWL_TREEVIEW_DOBLECLICK_DERECHO :
                                                            return this->Evento_TreeView_Mouse_DobleClick(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_TREEVIEW_DOBLECLICK_IZQUIERDO :
                                                            return this->Evento_TreeView_Mouse_DobleClick(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_TREEVIEW_DOBLECLICK_MEDIO :
                                                            return this->Evento_TreeView_Mouse_DobleClick(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_TREEVIEW_CLICK_DERECHO :
                                                            return this->Evento_TreeView_Mouse_Click(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_TREEVIEW_CLICK_IZQUIERDO :
                                                            return this->Evento_TreeView_Mouse_Click(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_TREEVIEW_CLICK_MEDIO :
                                                            return this->Evento_TreeView_Mouse_Click(2, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<UINT>(wParam));
                                                        case DWL_TREEVIEW_TECLADO_PRESIONADO :
                                                            return this->Evento_TreeView_Teclado_TeclaPresionada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_TREEVIEW_TECLADO_SOLTADO :
                                                            return this->Evento_TreeView_Teclado_TeclaSoltada(static_cast<UINT>(wParam), static_cast<UINT>(lParam));	break;
                                                        case DWL_TREEVIEW_TECLADO_INTRO :
                                                            return this->Evento_TreeView_Teclado_Intro(static_cast<UINT>(lParam));
                                                        case DWL_TREEVIEW_LABELEDIT_INICIO :
                                                            return this->Evento_TreeView_LabelEdit_Inicio(reinterpret_cast<DWL::Controles::DWLTreeView_Nodo *>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_TREEVIEW_LABELEDIT_FIN :
                                                            return this->Evento_TreeView_LabelEdit_Fin(reinterpret_cast<DWL::Controles::DWLTreeView_TerminarLabelEdit *>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_TREEVIEW_LABELEDIT_CANCELADO	:
                                                            return this->Evento_TreeView_LabelEdit_Cancelado(reinterpret_cast<DWL::Controles::DWLTreeView_Nodo *>(wParam), static_cast<UINT>(lParam));
                                                        case DWL_TREEVIEW_FOCO_OBTENIDO			:
                                                            return this->Evento_TreeView_Foco_Obtenido(static_cast<UINT>(wParam));
                                                        case DWL_TREEVIEW_FOCO_PERDIDO			:
                                                            return this->Evento_TreeView_Foco_Perdido(static_cast<UINT>(wParam));
                                                    }
			                                        return DWLEventosBase<TIPO_DEVUELTO>::GestorMensajes(uMsg, wParam, lParam);
                                                };

			  static DWORD                     _WM_TASK_BUTTON_CREATED;
            }; /////////////////////////////////// FIN DWLEventosPadre

//	template <class DWL_TIPO_APP> LPTOP_LEVEL_EXCEPTION_FILTER DWL_Iniciar<DWL_TIPO_APP>::_FiltroPorDefecto = NULL;
			template <typename TIPO_DEVUELTO, const long VALOR_DEVUELTO> DWORD DWLEventosPadre<TIPO_DEVUELTO, VALOR_DEVUELTO>::_WM_TASK_BUTTON_CREATED = 0;
        };
    };
};

#endif
