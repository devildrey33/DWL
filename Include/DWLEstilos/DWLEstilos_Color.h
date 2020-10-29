/*! \file DWLEstilos_Color.h
	\brief		 Archivo que contiene una clase para enlazar los colores globales con los controles extendidos.
    */ 
#ifndef DWL_ESTILOS_COLOR_H
#define DWL_ESTILOS_COLOR_H


//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres Estilos
    namespace SO {

	    //! Clase que contiene un color que puede ser enlazado SOLO para los controles extendidos
	    class DWLEstilos_Color {
	     public : //////////////// Miembros publicos

                                    //! Constructor por defecto.
                                    /*! Constructor por defecto que inicializa la clase.
                                            \fn		DWLEstilos_Color(void);
                                            \return	No devuelve nada.
                                    */
                                    DWLEstilos_Color(void) : 
										_ColorPropio(false),
										_Color(NULL) {
                                    };

                                    //! Constructor copia.
                                    /*! Constructor copia.
                                            \fn		DWLEstilos_Color(void);
                                            \return	No devuelve nada.
                                    */
                                    DWLEstilos_Color(const COLORREF &ColorNuevo) : 
										_ColorPropio(true), 
										_Color(new COLORREF(ColorNuevo)) {
										//_Color = new COLORREF(ColorNuevo);
                                    };

                                    //! Constructor que enlaza el color.
                                    /*! Constructor que enlaza el color.
                                            \fn		DWLEstilos_Color(COLORREF *ColorNuevo);
                                            \return	No devuelve nada.
                                    */
                                    DWLEstilos_Color(COLORREF *ColorNuevo) : _ColorPropio(false), _Color(ColorNuevo) {
                                    };

                                    //! Destructor.
                                    /*! Destructor.
                                            \fn		~DWLEstilos_Color(void);
                                            \return	No devuelve nada.
                                    */
                                   ~DWLEstilos_Color(void) {
                                        if (_ColorPropio == true) delete _Color;
                                        _ColorPropio = false;
                                    };

                                    //! Función que se usa para enlazar un color del aspecto grafico general.
                                    /*!	Esta función enlaza un color de la clase DWLEstilos a esta.
                                            \fn			inline void Enlazar(COLORREF *ColorNuevo);
                                            \param[in]	ColorNuevo : COLORREF al que vamos a enlazar esta clase.
                                            \return		No devuelve nada.
                                    */
	      inline void			    Enlazar(COLORREF *ColorNuevo) {
                                        if (_ColorPropio == true) delete _Color;
                                        _Color = ColorNuevo;
                                        _ColorPropio = false;
                                    };

                                    //! Operador que asigna un nuevo color.
                                    /*!	Este operador asigna un nuevo color que sera propio y mas adelante esta clase debera asegurarse de borrar.
                                            \fn			inline DWLEstilos_Color &operator = (COLORREF ColorNuevo);
                                            \param[in]	ColorNuevo : COLORREF al que vamos a enlazar esta clase.
                                            \return		No devuelve nada.
                                    */
	      inline DWLEstilos_Color  &operator = (COLORREF ColorNuevo) {
                                        if (_ColorPropio == false) _Color = new COLORREF;
                                        _ColorPropio = true;
                                        *_Color = ColorNuevo;
                                        return *this;
                                    };

                                    //! Operador que retorna el color/enlace asignado a esta clase.
                                    /*!	Este operador devuelve el color/enlace que se ha asignado a esta clase.
                                            \fn			inline COLORREF	operator () (void);
                                            \return		Devuelve el color que contiene esta clase.
                                    */
	      inline COLORREF	        operator () (void) {
                                        return *_Color;
                                    };

                                    //! Función que retorna si el color de esta clase es propio o enlazado.
                                    /*!	Esta función devuelve si el color es un enlace o es un color propio.
                                            \fn			inline bool ColorPropio(void);
                                            \return		True si el color es propio, false si el color es enlazado.
                                    */
	      inline bool		        ColorPropio(void) {
                                        return _ColorPropio;
                                    };
	     protected : /////////////////

                                    //! Constructor copia des-habilitado
                                    DWLEstilos_Color(const DWL::SO::DWLEstilos_Color &) : _ColorPropio(false), _Color(NULL) { };

                                    //! Operador = des-habilitado
		  inline DWLEstilos_Color  &operator=(const DWL::SO::DWLEstilos_Color &) { };

                                    //! Miembro para saber si es un color propio, o un enlace.
	      bool			           _ColorPropio;

							        //! Color de esta clase.
	      COLORREF		          *_Color;
	    };					    	//
	    //////////////////////////////
    };
};

#endif
