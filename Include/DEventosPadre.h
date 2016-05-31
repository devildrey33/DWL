/*! \file DEventosPadre.h
	\brief Archivo que contiene los eventos basicos para cualquier ventana padre.
*/
#ifndef DEVENTOSPADRE_H
    #define DEVENTOSPADRE_H

    #include "DEventosBase.h"
    #include "DAplicacion.h"

    //! Espacio de nombres DWL
    namespace DWL {
    
        class DTreeView_Nodo;
        class DTreeView_TerminarLabelEdit;
		class DTreeView_DatosClick;
		class DListView_DatosClick;
		class DListView_DatosEdicion;

        //! Clase base para los eventos de ventanas / dialogos padre
        template <typename TIPO_DEVUELTO> class DEventosPadre : public DEventosBase<TIPO_DEVUELTO> {
            public :
			virtual const DEnum_Objeto		Objeto_Tipo(void) { return DEnum_Objeto::DEnum_Objeto_EventosPadre; };

											//! Constructor 
                                            /*! Constructor por defecto.
		                                            \fn			DEventosPadre(void);
                                                    \return     No devuelve nada
                                            */
                                            DEventosPadre(void) : DEventosBase<TIPO_DEVUELTO>() { 
										    };

		                                    //! Destructor
                                            /*! Destructor por defecto.
		                                            \fn		   ~DEventosPadre(void);
                                                    \return     No devuelve nada
                                            */
                                           ~DEventosPadre(void) { };

						                    //! Función virtual que recibira cuando se crea la ventana / dialogo.
						                    /*! Esta función virtual recibira cuando se crea la ventana / dialogo.
								                    \fn			virtual TIPO_DEVUELTO Evento_Crear(void);
									                \return		Si re-emplazas esta función, debes retornar TRUE.
						                    */
            inline virtual TIPO_DEVUELTO    Evento_Crear(void) { return TRUE; };


                                            /////////////
                                            // -Button //
                                            /////////////

						                    //! Función virtual que recibira cuando el usuario presiona sobre la flecha de un button del tipo split. (BCN_DROPDOWN)
						                    /*! Esta función virtual recibira cuando el usuario presiona sobre la flecha de un button del tipo split. (BCN_DROPDOWN)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_Button_Desplegar(const RECT RectaBoton, const UINT cID);
								                    \param[in]	RectaBoton		Recta cliente del button presionado.
								                    \param[in]	cID     	    ID del Button que manda el evento.
								                    \return		Si re-emplazas esta función, debes retornar 0.
						                    */
            inline virtual TIPO_DEVUELTO    Evento_Button_Desplegar(const RECT RectaBoton, const UINT cID) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira cuando el mouse entra en el button. (BCN_HOTITEMCHANGE)
						                    /*! Esta función virtual recibira cuando el mouse entra en el button. (BCN_HOTITEMCHANGE)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_Button_Mouse_Entrando(const UINT cID);
								                    \param[in]	cID     	    ID del Button que manda el evento.
								                    \return		Si re-emplazas esta función, debes retornar 0.
						                    */
            inline virtual TIPO_DEVUELTO    Evento_Button_Mouse_Entrando(const UINT cID) { return DWL_EVENTOS_VALOR_DEVUELTO; }; 

						                    //! Función virtual que recibira cuando el mouse sale del button. (BCN_HOTITEMCHANGE)
						                    /*! Esta función virtual recibira cuando el mouse sale del button. (BCN_HOTITEMCHANGE)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_Button_Mouse_Saliendo(const UINT cID);
								                    \param[in]	cID     	    ID del Button que manda el evento.
								                    \return		Si re-emplazas esta función, debes retornar 0.
						                    */
            inline virtual TIPO_DEVUELTO    Evento_Button_Mouse_Saliendo(const UINT cID) { return DWL_EVENTOS_VALOR_DEVUELTO; };     

						                    //! Función virtual que recibira cuando se hace click en el button. (BN_CLICKED)
						                    /*! Esta función virtual recibira cuando se hace click en el button. (BN_CLICKED)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_Button_Mouse_Click(const UINT cID);
								                    \param[in]	cID     	    ID del Button que manda el evento.
								                    \return		Si re-emplazas esta función, debes retornar 0.
						                    */
            inline virtual TIPO_DEVUELTO    Evento_Button_Mouse_Click(const UINT cID)  { return DWL_EVENTOS_VALOR_DEVUELTO; };        

						                    //! Función virtual que recibira cuando se hace doble click en el button. (BN_DBLCLK y BN_DOUBLECLICKED)
						                    /*! Esta función virtual recibira cuando se hace doble click en el button. (BN_DBLCLK y BN_DOUBLECLICKED)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_Button_Mouse_DobleClick(const UINT cID);
								                    \param[in]	cID     	    ID del Button que manda el evento.
								                    \return		Si re-emplazas esta función, debes retornar 0.
                                                    \remarks    Solo se recibira esta notificación si el button tiene el estilo BS_NOTIFY asignado.
						                    */
            inline virtual TIPO_DEVUELTO    Evento_Button_Mouse_DobleClick(const UINT cID) { return DWL_EVENTOS_VALOR_DEVUELTO; };    

						                    //! Función virtual que recibira cuando el button obtiene el foco. (BN_SETFOCUS)
						                    /*! Esta función virtual recibira cuando button obtiene el foco. (BN_SETFOCUS)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_Button_Foco_Obtenido(const UINT cID);
								                    \param[in]	cID     	    ID del Button que manda el evento.
								                    \return		Si re-emplazas esta función, debes retornar 0.
                                                    \remarks    Solo se recibira esta notificación si el button tiene el estilo BS_NOTIFY asignado.
						                    */
            inline virtual TIPO_DEVUELTO    Evento_Button_Foco_Obtenido(const UINT cID) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira cuando el button pierde el foco. (BN_KILLFOCUS)
						                    /*! Esta función virtual recibira cuando button pierde el foco. (BN_KILLFOCUS)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_Button_Foco_Perdido(const UINT cID);
								                    \param[in]	cID     	    ID del Button que manda el evento.
								                    \return		Si re-emplazas esta función, debes retornar 0.
                                                    \remarks    Solo se recibira esta notificación si el button tiene el estilo BS_NOTIFY asignado.
						                    */
            inline virtual TIPO_DEVUELTO    Evento_Button_Foco_Perdido(const UINT cID) { return DWL_EVENTOS_VALOR_DEVUELTO; };

                                            ///////////////
                                            // -ComboBox //
                                            ///////////////

                                            //! Función virtual que recibira la notificación CBN_SELCHANGE la cual indica que se ha seleccionado otro item en la lista.
						                    /*! Esta función virtual recibira la notificación CBN_SELCHANGE la cual indica que se ha seleccionado otro item en la lista.
								                    \fn			inline virtual TIPO_DEVUELTO Evento_ComboBox_CambioSeleccion(const UINT IDComboBox);
								                    \param[in]	IDComboBox	: ID del ComboBox que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_ComboBox_CambioSeleccion(const UINT IDComboBox) { return DWL_EVENTOS_VALOR_DEVUELTO; };

            inline virtual TIPO_DEVUELTO    Evento_ComboBox_Lista_Ocultar(const UINT IDComboBox) { return DWL_EVENTOS_VALOR_DEVUELTO; };
            inline virtual TIPO_DEVUELTO    Evento_ComboBox_Lista_DobleClick(const UINT IDComboBox) { return DWL_EVENTOS_VALOR_DEVUELTO; };
            inline virtual TIPO_DEVUELTO    Evento_ComboBox_Lista_Mostrar(const UINT IDComboBox) { return DWL_EVENTOS_VALOR_DEVUELTO; };
            inline virtual TIPO_DEVUELTO    Evento_ComboBox_Edit_Cambiado(const UINT IDComboBox) { return DWL_EVENTOS_VALOR_DEVUELTO; };
            inline virtual TIPO_DEVUELTO    Evento_ComboBox_Edit_Cambiando(const UINT IDComboBox) { return DWL_EVENTOS_VALOR_DEVUELTO; };
            inline virtual TIPO_DEVUELTO    Evento_ComboBox_Foco_Perdido(const UINT IDComboBox) { return DWL_EVENTOS_VALOR_DEVUELTO; };
            inline virtual TIPO_DEVUELTO    Evento_ComboBox_Foco_Obtenido(const UINT IDComboBox) { return DWL_EVENTOS_VALOR_DEVUELTO; };


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
	        inline virtual TIPO_DEVUELTO	Evento_EditBox_Mouse_DobleClick(const UINT Boton, const int cX, const int cY, const UINT IDEditBox) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira los Click del EditBox.
						                    /*! Esta función virtual recibira los Click del EditBox.
								                    \fn			inline virtual TIPO_DEVUELTO Evento_EditBox_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDEditBox);
								                    \param[in]	Boton		: Boton presionado.
								                    \param[in]	cX			: Coordenada X del mouse.
								                    \param[in]	cY			: Coordenada Y del mouse.
								                    \param[in]	IDEditBox	: ID del EditBox que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO	Evento_EditBox_Mouse_Click(const UINT Boton, const int cX, const int cY, const UINT IDEditBox) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira los mensajes WM_KEYDOWN del EditBox.
						                    /*! Esta función virtual recibira los mensajes WM_KEYDOWN del EditBox.
								                    \fn			inline virtual TIPO_DEVUELTO Evento_EditBox_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDEditBox);
								                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
								                    \param[in]	IDEditBox		: ID del EditBox que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_EditBox_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDEditBox) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira los mensajes WM_KEYUP del EditBox.
						                    /*! Esta función virtual recibira los mensajes WM_KEYUP del EditBox.
								                    \fn			inline virtual TIPO_DEVUELTO Evento_EditBox_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDEditBox);
								                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
								                    \param[in]	IDEditBox		: ID del EditBox que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_EditBox_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDEditBox) { return DWL_EVENTOS_VALOR_DEVUELTO; };

                                            //! Función virtual que recibira cuando se presiona el intro en el EditBox.
                                            /*! Esta función virtual recibira cuando se presiona el intro en el EditBox.
	                                                \fn			inline virtual TIPO_DEVUELTO Evento_EditBox_Teclado_Intro(const UINT IDEditBox);
	                                                \param[in]	IDEditBox   : ID del EditBox que manda el evento.
	                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                            */
	        inline virtual TIPO_DEVUELTO    Evento_EditBox_Teclado_Intro(const UINT IDEditBox) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira el mensaje WM_SETFOCUS.
						                    /*! Esta función virtual recibira el mensaje WM_SETFOCUS.
								                    \fn			inline virtual TIPO_DEVUELTO Evento_EditBox_Foco_Obtenido(const UINT IDEditBox);
								                    \param[in]	IDEditBox	: ID del EditBox que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_EditBox_Foco_Obtenido(const UINT IDEditBox) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira el mensaje WM_KILLFOCUS.
						                    /*! Esta función virtual recibira el mensaje WM_KILLFOCUS.
								                    \fn			inline virtual TIPO_DEVUELTO Evento_EditBox_Foco_Perdido(const UINT IDEditBox);
								                    \param[in]	IDEditBox	: ID del EditBox que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_EditBox_Foco_Perdido(const UINT IDEditBox) { return DWL_EVENTOS_VALOR_DEVUELTO; };


                                            ////////////////
                                            // -ListView  //
                                            ////////////////

						                    //! Función virtual que recibira cuando se empieza una operacion de arrastrar y soltar interna. (LVN_BEGINDRAG)
						                    /*! Esta función virtual recibira cuando se empieza una operacion de arrastrar y soltar interna. (LVN_BEGINDRAG)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_ArrastrarSoltar_Empezar(const int nBoton, const int nItem, const UINT IDListView);
								                    \param[in]	nBoton		 Boton del mouse utilizado (0 izquierdo, 1 derecho)
								                    \param[in]	nItem		 Posición del item que se va a arrastrar.
								                    \param[in]	IDListView	 ID del ListView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_ListView_ArrastrarSoltar_Empezar(const int nBoton, const int nItem, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira cuando se empieza a usar la barra de scroll dentro del listview. (LVN_BEGINSCROLL)
						                    /*! Esta función virtual recibira cuando se empieza a usar la barra de scroll dentro del listview. (LVN_BEGINSCROLL)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Scroll_Empezar(const int dX, const int dY, const UINT IDListView);
								                    \param[in]	dX	         Posición horizontal en pixeles donde empieza el scroll.
								                    \param[in]	dY	         Posición vertical en pixeles donde empieza el scroll.
								                    \param[in]	IDListView	 ID del ListView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_ListView_Scroll_Empezar(const int dX, const int dY, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira cuando se termina a usar la barra de scroll dentro del listview. (LVN_ENDSCROLL)
						                    /*! Esta función virtual recibira cuando se termina a usar la barra de scroll dentro del listview. (LVN_ENDSCROLL)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Scroll_Terminar(const int dX, const int dY, const UINT IDListView);
								                    \param[in]	dX	         Posición horizontal en pixeles donde termina el scroll.
								                    \param[in]	dY	         Posición vertical en pixeles donde termina el scroll.
								                    \param[in]	IDListView	 ID del ListView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_ListView_Scroll_Terminar(const int dX, const int dY, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira cuando se hace click en una columna del listview. (LVN_COLUMNCLICK)
						                    /*! Esta función virtual recibira cuando se hace click en una columna del listview. (LVN_COLUMNCLICK)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Columna_Click(const int nColumna, const UINT IDListView);
								                    \param[in]	nColumna     Posición de la columna.
								                    \param[in]	IDListView	 ID del ListView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_ListView_Columna_Click(const int nColumna, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira cuando se van a borrar todos los items. (LVN_DELETEALLITEMS)
						                    /*! Esta función virtual recibira cuando se van a borrar todos los items. (LVN_DELETEALLITEMS)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Item_BorrarTodos(const UINT IDListView);
								                    \param[in]	IDListView	 ID del ListView que manda el evento.
								                    \return		Devuelve FALSE para recibir cuando se borra cada item, o true para no recibir ninguna notificación.
						                    */
	        inline virtual TIPO_DEVUELTO	Evento_ListView_Item_BorrarTodos(const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira cuando se va a borrar un item. (LVN_DELETEITEM)
						                    /*! Esta función virtual recibira cuando se va a borrar un item. (LVN_DELETEITEM)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Item_Borrar(const UINT TeclaVirtual, const UINT IDListView);
								                    \param[in]	nItem       	 Posicion del item que se va a borrar.
								                    \param[in]	IDListView		 ID del ListView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
                                                    \remarks    No añadas, borres o modifiques un item mientras procesas esta notificación.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_ListView_Item_Borrar(const int nItem, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira cuando el mouse pasa por encima de un item. (LVN_HOTTRACK)
						                    /*! Esta función virtual recibira cuando el mouse pasa por encima de un item. Esta notificación requiere que el listview tenga el estilo LVS_EX_TRACKSELECT. (LVN_HOTTRACK)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Mouse_Movimiento(const int nItem, const int nSubItem, const int cX, const int cY, const UINT IDListView);
								                    \param[in]	nItem	     Posición del item (Si es -1 indica que no hay item debajo del mouse).
								                    \param[in]	nSubItem	 Posición del subitem.
								                    \param[in]	cX	         Coordenada X relativa al control donde se encuentra el mouse.
								                    \param[in]	cY	         Coordenada Y relativa al control donde se encuentra el mouse.
								                    \param[in]	IDListView	 ID del ListView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_ListView_Mouse_Movimiento(const int nItem, const int nSubItem, const int nX, const int nY, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

                                            //! Función virtual que recibira cuando se agrega un item al ListView. (LVN_INSERTITEM)
                                            /*! Esta función virtual recibira cuando se agrega un item al ListView. (LVN_INSERTITEM)
	                                                \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Item_Agregar(const int nItem, const UINT IDListView);
	                                                \param[in]	nItem         Posición donde se ha agregado el item.
	                                                \param[in]	IDListView    ID del ListView que manda el evento.
	                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                            */
            inline virtual TIPO_DEVUELTO    Evento_ListView_Item_Agregar(const int nItem, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

                                            //! Función virtual que recibira cuando se activa un item. (LVN_ITEMACTIVATE)
                                            /*! Esta función virtual recibira cuando se activa un item. (LVN_ITEMACTIVATE)
	                                                \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Item_Activado(const int nItem, const int nSubItem, const UINT nNuevoEstado, const UINT nUltimoEstado, const UINT nMascara, const int nX, const int nY, LPARAM nParams, const UINT nTeclado, const UINT IDListView);
	                                                \param[in]	nItem          Posición del item activado.
	                                                \param[in]	nSubItem       Posición del subitem activado.
	                                                \param[in]	nNuevoEstado   Nuevo estado para el item.
	                                                \param[in]	nUltimoEstado  Ultimo estado del item.
	                                                \param[in]	nMascara       Mascara de atributos que han cambiado, que puede ser uno o varios de los siguientes valores : LVIF_COLFMT, LVIF_COLUMNS, LVIF_DI_SETITEM, LVIF_GROUPID, LVIF_IMAGE, LVIF_INDENT, LVIF_NORECOMPUTE, LVIF_PARAM, LVIF_STATE, LVIF_TEXT
	                                                \param[in]	nX             Coordenada X relativa al control donde se encuentra el mouse.
	                                                \param[in]	nY             Coordenada Y relativa al control donde se encuentra el mouse.
	                                                \param[in]	nParams        Parametros extras definidos por el usuario.
	                                                \param[in]	nTeclado       Mascara de teclas presionadas que puede ser uno o varios de los siguientes valores : LVKF_ALT, LVKF_CONTROL, LVKF_SHIFT.
	                                                \param[in]	IDListView     ID del ListView que manda el evento.
	                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                            */
            inline virtual TIPO_DEVUELTO    Evento_ListView_Item_Activado(const int nItem, const int nSubItem, const UINT nNuevoEstado, const UINT nUltimoEstado, const UINT nMascara, const int nX, const int nY, LPARAM nParams, const UINT nTeclado, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

                                            //! Función virtual que recibira se ha cambiado un item. (LVN_ITEMCHANGED)
                                            /*! Esta función virtual recibira se ha cambiado un item. (LVN_ITEMCHANGED)
	                                                \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Item_Cambiado(const int nItem, const UINT IDListView);
	                                                \param[in]	nItem         Posición donde se ha cambiado el item. Si el valor es -1, se han cambiado todos los items del listview.
	                                                \param[in]	IDListView    ID del ListView que manda el evento.
	                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                            */
            inline virtual TIPO_DEVUELTO    Evento_ListView_Item_Cambiado(const int nItem, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

                                            //! Función virtual que recibira se esta cambiado un item. (LVN_ITEMCHANGING)
                                            /*! Esta función virtual recibira se esta cambiado un item. (LVN_ITEMCHANGING)
	                                                \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Item_Cambiando(const int nItem, const int nSubItem, const UINT nNuevoEstado, const UINT nUltimoEstado, const UINT nMascara, const int nX, const int nY, LPARAM nParams, const UINT IDListView);
	                                                \param[in]	nItem          Posición del item.
	                                                \param[in]	nSubItem       Posición del subitemo.
	                                                \param[in]	nNuevoEstado   Nuevo estado para el item.
	                                                \param[in]	nUltimoEstado  Ultimo estado del item.
	                                                \param[in]	nMascara       Mascara de atributos que han cambiado, que puede ser uno o varios de los siguientes valores : LVIF_COLFMT, LVIF_COLUMNS, LVIF_DI_SETITEM, LVIF_GROUPID, LVIF_IMAGE, LVIF_INDENT, LVIF_NORECOMPUTE, LVIF_PARAM, LVIF_STATE, LVIF_TEXT
	                                                \param[in]	nX             Coordenada X relativa al control donde se encuentra el mouse.
	                                                \param[in]	nY             Coordenada Y relativa al control donde se encuentra el mouse.
	                                                \param[in]	nParams        Parametros extras definidos por el usuario.
	                                                \param[in]	IDListView     ID del ListView que manda el evento.
	                                                \return		Debes retornar FALSE para completar los cambios, o TRUE para cancelar los cambios.
                                            */
            inline virtual TIPO_DEVUELTO    Evento_ListView_Item_Cambiando(const int nItem, const int nSubItem, const UINT nNuevoEstado, const UINT nUltimoEstado, const UINT nMascara, const int nX, const int nY, LPARAM nParams, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };


                                            //! Función virtual que recibira se ha presionado una tecla en el ListView. (LVN_KEYDOWN)
                                            /*! Esta función virtual recibira se ha presionado una tecla en el ListView. (LVN_KEYDOWN)
	                                                \fn			inline virtual TIPO_DEVUELTO Evento_ListView_TeclaPresionada(const WORD TeclaVirtual, const UINT IDListView);
	                                                \param[in]	TeclaVirtual   Tecla presionada.
	                                                \param[in]	IDListView     ID del ListView que manda el evento.
	                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                            */
            inline virtual TIPO_DEVUELTO    Evento_ListView_TeclaPresionada(const WORD TeclaVirtual, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };
            
                                            //! Función virtual que recibira cuando se inicia la edicion de un item en el ListView.
                                            /*! Esta función virtual recibira cuando se inicia la edicion de un item en el ListView.
	                                                \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Edicion_Empezar(DListView_DatosEdicion *DatosEdicion, const UINT IDListView);
	                                                \param[in]	DatosEdicion    Clase que contiene metodos para modificar la edición.
	                                                \param[in]	IDListView      ID del ListView que manda el evento.
	                                                \return		Si re-emplazas esta funcion, debes retornar 0 para continuar con la edicion. Si retornas cualquier otro valor se cancelara la edición.
                                            */
	        inline virtual TIPO_DEVUELTO    Evento_ListView_Edicion_Empezar(DListView_DatosEdicion *DatosEdicion, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

                                            //! Función virtual que recibira cuando se termina la edicion de un item en el ListView.
                                            /*! Esta función virtual recibira cuando se termina la edicion de un item en el ListView.
	                                                \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Edicion_Terminar(DListView_DatosEdicion *DatosEdicion, const UINT IDListView);
	                                                \param[in]	DatosEdicion    Clase que contiene metodos para modificar la edición.
	                                                \param[in]	IDListView      ID del ListView que manda el evento.
	                                                \return		Si re-emplazas esta funcion, debes retornar 0 para que los datos se guarden. Si retornas cualquier otro valor se tomara como una cancelación de la edición.
                                            */
	        inline virtual TIPO_DEVUELTO    Evento_ListView_Edicion_Terminar(DListView_DatosEdicion *DatosEdicion, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

                                            //! Función virtual que recibira cuando se cancela la edicion de un item en el ListView.
                                            /*! Esta función virtual recibira cuando se cancela la edicion de un item en el ListView.
	                                                \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Edicion_Cancelar(DListView_DatosEdicion *DatosEdicion, const UINT IDListView);
	                                                \param[in]	DatosEdicion    Clase que contiene metodos para modificar la edición.
	                                                \param[in]	IDListView      ID del ListView que manda el evento.
	                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                            */
	        inline virtual TIPO_DEVUELTO    Evento_ListView_Edicion_Cancelar(DListView_DatosEdicion *DatosEdicion, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibe cuando se hace un click en el ListView. (NM_CLICK)
						                    /*! Esta función virtual que recibe cuando se hace un click en el ListView.
								                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Mouse_Click(DListView_DatosClick *DatosClick, const UINT IDListView);
								                    \param[in]	DatosClick      Clase que contiene el item, subitem, boton y las coordenadas para este mensaje.
								                    \param[in]	IDListView      ID del ListView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_ListView_Mouse_Click(DListView_DatosClick *DatosClick, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibe cuando se hace un doble click en el ListView. (NM_DBLCLK)
						                    /*! Esta función virtual que recibe cuando se hace un doble click en el ListView.
								                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Mouse_DobleClick(DListView_DatosClick *DatosClick, const UINT IDListView);
								                    \param[in]	DatosClick      Clase que contiene el item, subitem, boton y las coordenadas para este mensaje.
								                    \param[in]	IDListView      ID del ListView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_ListView_Mouse_DobleClick(DListView_DatosClick *DatosClick, const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que es llamada cuando el listview recibe el foco. (NM_SETFOCUS)
						                    /*! Esta función virtual es llamada cuando el listview recibe el foco. (NM_SETFOCUS)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Foco_Obtenido(const UINT IDListView);
								                    \param[in]	IDListView	    ID del ListView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_ListView_Foco_Obtenido(const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que es llamada cuando el lilstview pierde el foco. (NM_KILLFOCUS)
						                    /*! Esta función virtual es llamada cuando el lilstview pierde el foco. (NM_KILLFOCUS)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Foco_Perdido(const UINT IDListView);
								                    \param[in]	IDListView	    ID del ListView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_ListView_Foco_Perdido(const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibe cuando un item va a ser resaltado. (NM_HOVER)
						                    /*! Esta función virtual recibe cuando un item va a ser resaltado. (NM_HOVER)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_ItemResaltado(const UINT IDListView);
								                    \param[in]	IDListView	    ID del ListView que manda el evento.
								                    \return		Devuelve 0 para que se procese el resatado con normalidad, o cualquier otro valor para evitar que se resalte el item.
						                    */
//	        inline virtual TIPO_DEVUELTO    Evento_ListView_ItemResaltado(const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibe cuando se termina la captura del teclado / ReleaseCapture. (NM_RELEASECAPTURE)
						                    /*! Esta función virtual recibe cuando se termina la captura del teclado / ReleaseCapture. (NM_RELEASECAPTURE)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_TerminarCaptura(const UINT IDListView);
								                    \param[in]	IDListView	    ID del ListView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_ListView_TerminarCaptura(const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibe cuando se presiona intro en el listview. (NM_RETURN)
						                    /*! Esta función virtual recibe cuando se presiona intro en el listview. (NM_RETURN)
								                    \fn			inline virtual TIPO_DEVUELTO Evento_ListView_Teclado_Intro(const UINT IDListView);
								                    \param[in]	IDListView	    ID del ListView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_ListView_Teclado_Intro(const UINT IDListView) { return DWL_EVENTOS_VALOR_DEVUELTO; };


                                            ////////////////
                                            // -TreeView  //
                                            ////////////////

											//! Función virtual que recibe cuando se hace un click en el TreeView. (NM_CLICK)
											/*! Esta función virtual que recibe cuando se hace un click en el TreeView.
													\fn			inline virtual TIPO_DEVUELTO Evento_TreeView_Mouse_Click(DTreeView_DatosClick *DatosClick, const UINT IDTreeView);
													\param[in]	DatosClick      Clase que contiene el nodo, boton y las coordenadas para este mensaje.
													\param[in]	IDTreeView      ID del TreeView que manda el evento.
													\return		Si re-emplazas esta funcion, debes retornar 0.
											*/
			inline virtual TIPO_DEVUELTO    Evento_TreeView_Mouse_Click(DTreeView_DatosClick *DatosClick, const UINT IDTreeView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

											//! Función virtual que recibe cuando se hace un doble click en el TreeView. (NM_DBLCLK)
											/*! Esta función virtual que recibe cuando se hace un doble click en el TreeView.
													\fn			inline virtual TIPO_DEVUELTO Evento_TreeView_Mouse_DobleClick(DTreeView_DatosClick *DatosClick, const UINT IDTreeView);
													\param[in]	DatosClick      Clase que contiene el nodo, boton y las coordenadas para este mensaje.
													\param[in]	IDTreeView      ID del TreeView que manda el evento.
													\return		Si re-emplazas esta funcion, debes retornar 0.
											*/
			inline virtual TIPO_DEVUELTO    Evento_TreeView_Mouse_DobleClick(DTreeView_DatosClick *DatosClick, const UINT IDTreeView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

											//! Función virtual que recibira los mensajes WM_KEYDOWN del TreeView.
						                    /*! Esta función virtual recibira los mensajes WM_KEYDOWN del TreeView.
								                    \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDTreeView);
								                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
								                    \param[in]	IDTreeView		: ID del TreeView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_TreeView_Teclado_TeclaPresionada(const UINT TeclaVirtual, const UINT IDTreeView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira los mensajes WM_KEYUP del TreeView.
						                    /*! Esta función virtual recibira los mensajes WM_KEYUP del TreeView.
								                    \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDTreeView);
								                    \param[in]	TeclaVirtual	: Tecla virtual presionada.
								                    \param[in]	IDTreeView		: ID del TreeView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_TreeView_Teclado_TeclaSoltada(const UINT TeclaVirtual, const UINT IDTreeView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

                                            //! Función virtual que recibira cuando se presiona el intro en el TreeView.
                                            /*! Esta función virtual recibira cuando se presiona el intro en el TreeView.
	                                                \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_Teclado_Intro(const UINT IDTreeView);
	                                                \param[in]	IDTreeView   : ID del TreeView que manda el evento.
	                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                            */
            inline virtual TIPO_DEVUELTO    Evento_TreeView_Teclado_Intro(const UINT IDTreeView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

                                            //! Función virtual que recibira cuando se va a expandir o contraer un nodo del TreeView.
                                            /*! Esta función virtual recibira cuando se va a expandir o contraer un nodo del TreeView.
	                                                \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_Nodo_Expandiendo(DTreeView_Nodo *eNodo, const UINT IDTreeView);
	                                                \param[in]	eNodo      : Nodo a expandir / contraer.
	                                                \param[in]	IDTreeView : ID del TreeView que manda el evento.
	                                                \return		Si re-emplazas esta funcion, debes retornar FALSE para que se expanga / contraiga el item. Retorna TRUE si no quieres expandir / contraer el nodo.
                                            */
	        inline virtual TIPO_DEVUELTO    Evento_TreeView_Nodo_Expandiendo(DTreeView_Nodo *eNodo, const UINT IDTreeView) { return FALSE; };

                                            //! Función virtual que recibira cuando se inicia la edicion de un nodo en el TreeView.
                                            /*! Esta función virtual recibira cuando se inicia la edicion de un nodo en el TreeView.
	                                                \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_LabelEdit_Inicio(DTreeView_Nodo *eNodo, const UINT IDTreeView);
	                                                \param[in]	eNodo      : Nodo en edicion.
	                                                \param[in]	IDTreeView : ID del TreeView que manda el evento.
	                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                            */
	        inline virtual TIPO_DEVUELTO    Evento_TreeView_LabelEdit_Inicio(DTreeView_Nodo *eNodo, const UINT IDTreeView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

                                            //! Función virtual que recibira cuando se termina la edicion de un nodo en el TreeView.
                                            /*! Esta función virtual recibira cuando se termina la edicion de un nodo en el TreeView.
	                                                \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_LabelEdit_Fin(DTreeView_TerminarLabelEdit *Edicion, const UINT IDTreeView);
	                                                \param[in]	Edicion    : Clase que contiene metodos para modificar la edicion.
	                                                \param[in]	IDTreeView : ID del TreeView que manda el evento.
	                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                            */
	        inline virtual TIPO_DEVUELTO    Evento_TreeView_LabelEdit_Fin(DTreeView_TerminarLabelEdit *Edicion, const UINT IDTreeView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

                                            //! Función virtual que recibira cuando se cancela la edicion de un nodo en el TreeView.
                                            /*! Esta función virtual recibira cuando se cancela la edicion de un nodo en el TreeView.
	                                                \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_LabelEdit_Cancelado(DTreeView_Nodo *eNodo, const UINT IDTreeView);
	                                                \param[in]	eNodo      : Nodo en edicion.
	                                                \param[in]	IDTreeView : ID del TreeView que manda el evento.
	                                                \return		Si re-emplazas esta funcion, debes retornar 0.
                                            */
	        inline virtual TIPO_DEVUELTO    Evento_TreeView_LabelEdit_Cancelado(DTreeView_Nodo *eNodo, const UINT IDTreeView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira el mensaje WM_SETFOCUS.
						                    /*! Esta función virtual recibira el mensaje WM_SETFOCUS.
								                    \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_Foco_Obtenido(const UINT IDTreeView);
								                    \param[in]	IDTreeView	: ID del TreeView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_TreeView_Foco_Obtenido(const UINT IDTreeView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira el mensaje WM_KILLFOCUS.
						                    /*! Esta función virtual recibira el mensaje WM_KILLFOCUS.
								                    \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_Foco_Perdido(const UINT IDTreeView);
								                    \param[in]	IDTreeView	: ID del TreeView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
	        inline virtual TIPO_DEVUELTO    Evento_TreeView_Foco_Perdido(const UINT IDTreeView) { return DWL_EVENTOS_VALOR_DEVUELTO; };

						                    //! Función virtual que recibira la notificación TVN_SELCHANGED que indica que se ha cambiado la selección.
						                    /*! Esta función virtual recibira la notificación TVN_SELCHANGED que indica que se ha cambiado la selección.
								                    \fn			inline virtual TIPO_DEVUELTO Evento_TreeView_CambioSeleccion(DTreeView_Nodo *NuevoNodo, const UINT IDTreeView);
	                                                \param[in]	NuevoNodo    : Nuevo nodo seleccionado (puede ser NULL).
								                    \param[in]	IDTreeView	 : ID del TreeView que manda el evento.
								                    \return		Si re-emplazas esta funcion, debes retornar 0.
						                    */
            inline virtual TIPO_DEVUELTO    Evento_TreeView_CambioSeleccion(DTreeView_Nodo *NuevoNodo, const UINT IDTreeView) { return DWL_EVENTOS_VALOR_DEVUELTO; };


	      protected: ///////////////////////// -Declaraciones protegidas (Solo podran usarse en la clase heredada no desde fuera)

								            //! Esqueleto para los mensajes de la ventana.
								            /*! Esta función es el esqueleto para los mensajes de la ventana.
										            \fn			inline virtual TIPO_DEVUELTO CALLBACK	GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam);
										            \param[in]	uMsg	: Mensaje.
										            \param[in]	wParam	: Parametro1.
										            \param[in]	lParam	: Parametro2.
										            \return		Dependiendo del mensaje y los parametros devuelve una cosa o otra.
								            */
		    virtual TIPO_DEVUELTO CALLBACK  GestorMensajes(UINT uMsg, WPARAM wParam, LPARAM lParam) {
											    LRESULT Ret = 0;
												DBaseWnd *Bwnd = NULL;
												switch (uMsg) {
													case WM_COMMAND:
														Bwnd = reinterpret_cast<DBaseWnd *>(GetWindowLongPtr((HWND)(lParam), GWLP_USERDATA));
														if (Bwnd) {
															switch (Bwnd->Objeto_Tipo()) {
																case DEnum_Objeto_Button:     // Button
																	switch (HIWORD(wParam)) {      ////////////////////////////////////////////////
																		case BN_CLICKED:           // Button click
																			return this->Evento_Button_Mouse_Click(LOWORD(wParam));
																		case BN_DOUBLECLICKED:     // Button dobleclick
																			return this->Evento_Button_Mouse_DobleClick(LOWORD(wParam));
																		case BN_KILLFOCUS:         // Button pierde foco
																			return this->Evento_Button_Foco_Perdido(LOWORD(wParam));
																		case BN_SETFOCUS:          // Button obtiene foco
																			return this->Evento_Button_Foco_Obtenido(LOWORD(wParam));
																	}
																	break;
																case DEnum_Objeto_ComboBox:   // ComboBox
																	switch (HIWORD(wParam)) {      ////////////////////////////////////////////////
																		case CBN_SELCHANGE:        // Cambio de selección en el ComboBox
																			return this->Evento_ComboBox_CambioSeleccion(LOWORD(wParam));
																		case CBN_CLOSEUP:          // Ocultar lista del ComboBox
																			return this->Evento_ComboBox_Lista_Ocultar(LOWORD(wParam));
																		case CBN_DBLCLK:           // Dobleclick en la lista del ComboBox
																			return this->Evento_ComboBox_Lista_DobleClick(LOWORD(wParam));
																		case CBN_DROPDOWN:         // Mostrar lista del ComboBox
																			return this->Evento_ComboBox_Lista_Mostrar(LOWORD(wParam));
																		case CBN_EDITCHANGE:       // Ha cambiado el EditBox del ComboBox
																			return this->Evento_ComboBox_Edit_Cambiado(LOWORD(wParam));
																		case CBN_EDITUPDATE:       // Va a cambiar el EditBox del ComboBox
																			return this->Evento_ComboBox_Edit_Cambiando(LOWORD(wParam));
																		case CBN_KILLFOCUS:        // Se ha perdido el foco del ComboBox
																			return this->Evento_ComboBox_Foco_Perdido(LOWORD(wParam));
																		case CBN_SETFOCUS:         // Se ha obtenido el foco en el ComboBox
																			return this->Evento_ComboBox_Foco_Obtenido(LOWORD(wParam));
																	}                              ////////////////////////////////////////////////
																	break;
															}
														}
														break;

			                                        case WM_NOTIFY :
                                                        switch (((LPNMHDR)lParam)->code) {
                                                            /////////////////////////////
                                                            // Notificaciones Button : //
                                                            /////////////////////////////
                                                            case BCN_DROPDOWN :
                                                                return this->Evento_Button_Desplegar(((LPNMBCDROPDOWN)lParam)->rcButton, static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
                                                            case BCN_HOTITEMCHANGE :
                                                                if (((LPNMBCHOTITEM)lParam)->dwFlags == (HICF_ENTERING | HICF_MOUSE))   return this->Evento_Button_Mouse_Entrando(static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
                                                                else                                                                    return this->Evento_Button_Mouse_Saliendo(static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
                                                            ///////////////////////////////
                                                            // Notificaciones ListView : //
                                                            ///////////////////////////////
                                                            case LVN_BEGINDRAG :        // Empezar Drag&Drop de un item interno (boton izquierdo)  (NMLISTVIEW iItem)
                                                                return this->Evento_ListView_ArrastrarSoltar_Empezar(0, ((LPNMLISTVIEW)lParam)->iItem, static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
                                                            case LVN_BEGINRDRAG :       // Empezar Drag&Drop de un item interno (boton derecho)   (NMLISTVIEW iItem)
                                                                return this->Evento_ListView_ArrastrarSoltar_Empezar(1, ((LPNMLISTVIEW)lParam)->iItem, static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
                                                            case LVN_BEGINLABELEDIT :   // Empezar labeledit del listview     (ANULAR devolver TRUE, POR HACER : probar de utilizar EmpezarEdicion del ListView)
                                                                return TRUE;
                                                            case LVN_BEGINSCROLL :      // Empieza una operacion de scroll en el listview    (NMLVSCROLL dx o dy)
                                                                return this->Evento_ListView_Scroll_Empezar(((LPNMLVSCROLL)lParam)->dx, ((LPNMLVSCROLL)lParam)->dy, static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
                                                            case LVN_COLUMNCLICK :      // Click en una culumna  (NMLISTVIEW iSubItem)
                                                                return this->Evento_ListView_Columna_Click(((LPNMLISTVIEW)lParam)->iSubItem, static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
                                                            case LVN_DELETEALLITEMS :   // Apunto de borrar todos los items (devolver true para recibir cuando se va a borrar cada item, false para no recibir nada)
                                                                return this->Evento_ListView_Item_BorrarTodos(static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
                                                            case LVN_DELETEITEM :       // apunto de borrar un item (NMLISTVIEW iItem)
                                                                return this->Evento_ListView_Item_Borrar(((LPNMLISTVIEW)lParam)->iItem, static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
                                                            case LVN_ENDSCROLL :        // termina una operacion de scroll (NMLVSCROLL dx o dy)
                                                                return this->Evento_ListView_Scroll_Terminar(((LPNMLVSCROLL)lParam)->dx, ((LPNMLVSCROLL)lParam)->dy, static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
                                                            case LVN_HOTTRACK :         // Indica que el mouse esta encima de un item (NMLISTVIEW iItem, iSubItem, ptAction   retornar 0 para continuar con la operación, o cualquier valor para que no se seleccione el item)
                                                                return this->Evento_ListView_Mouse_Movimiento(((LPNMLISTVIEW)lParam)->iItem, ((LPNMLISTVIEW)lParam)->iSubItem, ((LPNMLISTVIEW)lParam)->ptAction.x, ((LPNMLISTVIEW)lParam)->ptAction.y, static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
                                                            case LVN_INSERTITEM :       // Informa que se ha agregado un item (NMLISTVIEW iItem)
                                                                return this->Evento_ListView_Item_Agregar(((LPNMLISTVIEW)lParam)->iItem, static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
                                                            case LVN_ITEMACTIVATE :     // Informa que se ha activado un item... (NMITEMACTIVATE TODA)
                                                                return this->Evento_ListView_Item_Activado(((LPNMITEMACTIVATE)lParam)->iItem, ((LPNMITEMACTIVATE)lParam)->iSubItem, ((LPNMITEMACTIVATE)lParam)->uNewState, ((LPNMITEMACTIVATE)lParam)->uOldState, ((LPNMITEMACTIVATE)lParam)->uChanged, ((LPNMITEMACTIVATE)lParam)->ptAction.x, ((LPNMITEMACTIVATE)lParam)->ptAction.y, ((LPNMITEMACTIVATE)lParam)->lParam, ((LPNMITEMACTIVATE)lParam)->uKeyFlags, static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
                                                            case LVN_ITEMCHANGED :      // Informa que se ha cambiado un item.... (NMLISTVIEW iItem [si es -1 es que se ha realizado un cambio a todos los items])
                                                                return this->Evento_ListView_Item_Cambiado(((LPNMLISTVIEW)lParam)->iItem, static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
                                                            case LVN_ITEMCHANGING :     // Informa que se va a cambiar un item (NMLISTVIEW que dice los atributos que se van a cambiar)
                                                                return this->Evento_ListView_Item_Cambiando(((LPNMLISTVIEW)lParam)->iItem, ((LPNMLISTVIEW)lParam)->iSubItem, ((LPNMLISTVIEW)lParam)->uNewState, ((LPNMLISTVIEW)lParam)->uOldState, ((LPNMLISTVIEW)lParam)->uChanged, ((LPNMLISTVIEW)lParam)->ptAction.x, ((LPNMLISTVIEW)lParam)->ptAction.y, ((LPNMLISTVIEW)lParam)->lParam, static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
                                                            case LVN_KEYDOWN :          // Tecla presionada (NMLVKEYDOWN wVKey)
                                                                return this->Evento_ListView_TeclaPresionada(((LPNMLVKEYDOWN)lParam)->wVKey, static_cast<UINT>(GetWindowLongPtr(((LPNMHDR)lParam)->hwndFrom, GWLP_ID)));
//                                                            case LVN_COLUMNDROPDOWN :         // columna desplegable??? (NMLISTVIEW iSubItem) (win vista o superior....)
//                                                            case LVN_COLUMNOVERFLOWCLICK :    // MSDN : Sent by a list-view control when its overflow button is clicked. :O   NMLISTVIEW iSubItem) (win vista o superior....)
//                                                            case LVN_ENDLABELEDIT :           // terminar labeledit (no deberia recibirse ya que anulamos el principio)
//                                                            case LVN_GETDISPINFO :            // obtener informacion necesaria para mostrar o ordenar un item (yo me la ahorraria....)
//                                                            case LVN_GETEMPTYMARKUP :         // enviada cuando no tiene items, es una peticion para saber como marcar el texto :O (windows vista o superior... yo me la saltaba tambien..)
//                                                            case LVN_GETINFOTIP :             // Enviada solo con el modo LARGE_ICON, y es una peticion para obtener informacion adicional para mostrar en un tooltip
//                                                            case LVN_INCREMENTALSEARCH :      // Notifica que se esta haciendo una busqueda incremetal? :O (WIndows vista o superior, otra que pasare...)
//                                                            case LVN_LINKCLICK :              // Notifica que se ha echo click en un link :O (windows vista o superior... otra que pasare...)
//                                                            case LVN_ODCACHEHINT :            // Enviada por un listview virtual para notificar que su contenido ha cambiado.... (pasando...)
//                                                            case LVN_ODFINDITEM :             // Enviada por un listview virtual para buscar un item... (pasando...)
//                                                            case LVN_ODSTATECHANGED :         // Enviada por un listview virtual para notificar que uno o varios items han cambiado (pasando...)
//                                                            case LVN_SETDISPINFO :            // Notifica que se va a actualizar la informacion que mantiene para un item??? (otra que pasare...)
//                                                            case NM_CUSTROMDRAW :             // Se controla en los windowprocedures de DVentana, DDialogo y DDialogoModal porque dependiendo de si es una ventana o un dialogo hay que contestar distinto......
//                                                            case LVN_MARQUEEBEGIN :           // MSDN : Notifies a list-view control's parent window that a bounding box (marquee) selection has begun. (To accept the notification code, return zero. To quit the bounding box selection, return nonzero.)
//                                                                                              //          Remarks : A bounding box selection is the process of clicking the list-view window's client area and dragging to select multiple items simultaneously.
															///////////////////////////////
															// Notificaciones TreeView : // TODO hacer lista completa como en el listview y crear todos los eventos posibles
															///////////////////////////////
															case TVN_DELETEITEM:		// Borrar item del TreeView																
																SendMessage( ((LPNMTREEVIEW)lParam)->hdr.hwndFrom, DWL_TREEVIEW_BORRARNODO, 0, ((LPNMTREEVIEW)lParam)->itemOld.lParam);
																break;
                                                            ////////////////////////////////
                                                            // Notificaciones Estandard : //
                                                            ////////////////////////////////
                                                            case NM_CLICK :
                                                            case NM_DBLCLK :
//                                                            case NM_HOVER :
                                                            case NM_KILLFOCUS :
                                                            case NM_RCLICK :
                                                            case NM_RDBLCLK :
                                                            case NM_RELEASEDCAPTURE :
                                                            case NM_RETURN :
                                                            case NM_SETFOCUS :
                                                                // Tanto el ListView como el TreeView procesan los mensajes WM_?BUTTONUP internamente y no pasan por el WindowProcedure de estos.
                                                                // Segun la MSDN cuando recibe un WM_?BUTTONDOWN estos controles entran en un bucle de mensajes interno para determinar si la operación involucra un Click o un Drag&Drop....
                                                                // Por desgracia si quiero habilitar funcionabilidades extras como editar un SubItem con una ComboBox necesito obtener cuando se suelta el mouse...
                                                                // A causa de esto cuando recibo un NM_CLICK lo devuelvo a su control (que sera un TreeView o un ListView, y asi consigo saber cuando se suelta el boton del mouse.
                                                                SendMessage(((LPNMHDR)lParam)->hwndFrom, DWL_NOTIFICACION, wParam, lParam);
                                                                break;

                                                            // Notificación TVN_ITEMEXPANDING para recibir cuando se expande un nodo del treeview
                                                            // Se necesita especificamente para la clase DTreeViewDirectorios ya que al expandir un nodo hay que escanear el directorio al que hace referencia.
                                                            case TVN_ITEMEXPANDING :
                                                                return SendMessage(((LPNMHDR)lParam)->hwndFrom, DWL_TREEVIEW_NODO_EXPANDIENDO, wParam, lParam);
                                                            // Cambio de selección en el TreeView
                                                            case TVN_SELCHANGED :
                                                                return SendMessage(((LPNMHDR)lParam)->hwndFrom, DWL_TREEVIEW_NODO_CAMBIOSELECCION, wParam, lParam);
                                                        }
//				                                        if (((LPNMHDR)lParam)->code == static_cast<UINT>(NM_CUSTOMDRAW)) return SendMessage(((LPNMHDR)lParam)->hwndFrom, DWL_CUSTOM_DRAW, wParam, lParam);
				                                        break;

                                                    // ComboBox
/*                                                    case DWL_COMBOBOX_DOBLECLICK_DERECHO :
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
                                                        return this->Evento_ComboBox_Foco_Perdido(static_cast<UINT>(wParam));*/

                                                    // ListView
                                                    case DWL_LISTVIEW_CLICK :
                                                        return this->Evento_ListView_Mouse_Click(reinterpret_cast<DListView_DatosClick *>(lParam), static_cast<UINT>(wParam));
                                                    case DWL_LISTVIEW_DOBLECLICK :
                                                        return this->Evento_ListView_Mouse_DobleClick(reinterpret_cast<DListView_DatosClick *>(lParam), static_cast<UINT>(wParam));
                                                    case DWL_LISTVIEW_EMPEZAR_EDICION :
                                                        return this->Evento_ListView_Edicion_Empezar(reinterpret_cast<DListView_DatosEdicion *>(lParam), static_cast<UINT>(wParam));
                                                    case DWL_LISTVIEW_TERMINAR_EDICION :
                                                        return this->Evento_ListView_Edicion_Terminar(reinterpret_cast<DListView_DatosEdicion *>(lParam), static_cast<UINT>(wParam));
                                                    case DWL_LISTVIEW_CANCELAR_EDICION :
                                                        return this->Evento_ListView_Edicion_Cancelar(reinterpret_cast<DListView_DatosEdicion *>(lParam), static_cast<UINT>(wParam));
                                                    case DWL_LISTVIEW_FOCO_OBTENIDO :
                                                        return this->Evento_ListView_Foco_Obtenido(static_cast<UINT>(wParam));
                                                    case DWL_LISTVIEW_FOCO_PERDIDO :
                                                        return this->Evento_ListView_Foco_Perdido(static_cast<UINT>(wParam));
                                                    case DWL_LISTVIEW_TERMINAR_CAPTURA :
                                                        return this->Evento_ListView_TerminarCaptura(static_cast<UINT>(wParam));
//                                                    case DWL_LISTVIEW_RESALTAR_ITEM :
  //                                                      return this->Evento_ListView_ItemResaltado(static_cast<UINT>(wParam));
                                                    case DWL_LISTVIEW_TECLADO_INTRO :
                                                        return this->Evento_ListView_Teclado_Intro(static_cast<UINT>(wParam));


													case DWL_TREEVIEW_NODO_EXPANDIENDO:
														return this->Evento_TreeView_Nodo_Expandiendo(reinterpret_cast<DTreeView_Nodo *>(wParam), static_cast<UINT>(lParam));
													case DWL_TREEVIEW_CLICK:
														return this->Evento_TreeView_Mouse_Click(reinterpret_cast<DTreeView_DatosClick *>(lParam), static_cast<UINT>(wParam));
													case DWL_TREEVIEW_DOBLECLICK:
														return this->Evento_TreeView_Mouse_DobleClick(reinterpret_cast<DTreeView_DatosClick *>(lParam), static_cast<UINT>(wParam));
														/*
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
                                                        return this->Evento_TreeView_LabelEdit_Inicio(reinterpret_cast<DTreeView_Nodo *>(wParam), static_cast<UINT>(lParam));
                                                    case DWL_TREEVIEW_LABELEDIT_FIN :
                                                        return this->Evento_TreeView_LabelEdit_Fin(reinterpret_cast<DTreeView_TerminarLabelEdit *>(wParam), static_cast<UINT>(lParam));
                                                    case DWL_TREEVIEW_LABELEDIT_CANCELADO	:
                                                        return this->Evento_TreeView_LabelEdit_Cancelado(reinterpret_cast<DTreeView_Nodo *>(wParam), static_cast<UINT>(lParam));
                                                    case DWL_TREEVIEW_FOCO_OBTENIDO			:
                                                        return this->Evento_TreeView_Foco_Obtenido(static_cast<UINT>(wParam));
                                                    case DWL_TREEVIEW_FOCO_PERDIDO			:
                                                        return this->Evento_TreeView_Foco_Perdido(static_cast<UINT>(wParam));
                                                    case DWL_TREEVIEW_NODO_CAMBIOSELECCION :
                                                        return this->Evento_TreeView_CambioSeleccion(reinterpret_cast<DTreeView_Nodo *>(wParam), static_cast<UINT>(lParam));
														*/
                                                }
			                                    return DEventosBase<TIPO_DEVUELTO>::GestorMensajes(uMsg, wParam, lParam);
                                            };

        }; /////////////////////////////////// FIN DEventosPadre

    };

#endif
