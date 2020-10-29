#ifndef DWL_TOOLTIPEX_OBJETO_H
#define DWL_TOOLTIPEX_OBJETO_H

#include "DWLToolTipEx_ObjetoIconoTexto.h"
#include "DWLToolTipEx_ObjetoTextoCaracterIcono.h"
#include "DWLToolTipEx_ObjetoTextoCaracterTexto.h"
 

//! Enumeración de los tipos de objeto para el tooltip
enum DWL_Enum_ToolTipEx_TiposObjeto {
	Enum_ToolTipEx_TiposObjeto_Texto,
	Enum_ToolTipEx_TiposObjeto_TextoNegrita,
	Enum_ToolTipEx_TiposObjeto_TextoCaracterTexto,
	Enum_ToolTipEx_TiposObjeto_TextoCaracterIcono,
	Enum_ToolTipEx_TiposObjeto_IconoTexto
};

namespace DWL {
	namespace ControlesEx {

		//! Clase base que engloba todos los objetos del tooltip
		class DWLToolTipEx_Objeto {
		public: ////////////////////////////////////////// Miembros publicos

														//! Constructor.
														/*! Constructor.
																\fn			DWLToolTipEx_Objeto(void);
																\return		No devuelve nada.
														*/
														DWLToolTipEx_Objeto(void) : _Tipo(Enum_ToolTipEx_TiposObjeto_Texto), _Objeto(0) {
														};

														//! Constructor asignador.
														/*! Constructor asignador.
																\fn			DWLToolTipEx_Objeto(LONG_PTR nObjeto, DWL_Enum_ToolTipEx_TiposObjeto nTipo);
																\param[in]	nObjeto : Puntero al objeto que va a contener.
																\param[in]  nTipo	: Tipo de clase que almacenara este objeto.
																\return		No devuelve nada.
														*/
														DWLToolTipEx_Objeto(LONG_PTR nObjeto, DWL_Enum_ToolTipEx_TiposObjeto nTipo) : _Tipo(nTipo), _Objeto(nObjeto) {
														};

														//! Destructor.
														/*! Destructor.
																\fn			~DWLToolTipEx_Objeto(void);
																\return		No devuelve nada.
														*/
													   ~DWLToolTipEx_Objeto(void) {
														   if (_Objeto != 0) {
															   switch (_Tipo) {
																   case Enum_ToolTipEx_TiposObjeto_Texto			    :  delete reinterpret_cast<DWLString *>(_Objeto);								break;
																   case Enum_ToolTipEx_TiposObjeto_TextoNegrita			:  delete reinterpret_cast<DWLString *>(_Objeto);								break;
																   case Enum_ToolTipEx_TiposObjeto_TextoCaracterTexto	:  delete reinterpret_cast<DWLToolTipEx_ObjetoTextoCaracterTexto *>(_Objeto);	break;
																   case Enum_ToolTipEx_TiposObjeto_TextoCaracterIcono	:  delete reinterpret_cast<DWLToolTipEx_ObjetoTextoCaracterIcono *>(_Objeto);	break;
																   case Enum_ToolTipEx_TiposObjeto_IconoTexto			:  delete reinterpret_cast<DWLToolTipEx_ObjetoIconoTexto *>(_Objeto);			break;
															   }
														   }
														};


														//! Función que retorna el objeto en forma de texto.
														/*! Esta función devuelve el objeto en forma de texto.
																\fn			inline DWLString *ObtenerTexto(void);
																\return		Devuelve una clase DWLString que contiene el texto del objeto.
														*/
		inline DWLString							   *ObtenerTexto(void) {
															return reinterpret_cast<DWLString *>(_Objeto);
														};

														//! Función que retorna el objeto en forma de texto en negrita.
														/*! Esta función devuelve el objeto en forma de texto en negrita.
																\fn			inline DWLString *ObtenerTextoNegrita(void);
																\return		Devuelve una clase DWLString que contiene el texto negrita del objeto.
														*/
		inline DWLString							   *ObtenerTextoNegrita(void) {
															return reinterpret_cast<DWLString *>(_Objeto);
														};

														//! Función que retorna el objeto en forma de clase Texto Caracter Texto.
														/*! Esta función devuelve el objeto en forma de clase Texto Caracter Texto.
																\fn			inline DWLToolTipEx_ObjetoTextoCaracterTexto *ObtenerTextoCaracterTexto(void);
																\return		Devuelve una clase DWLToolTipEx_ObjetoTextoCaracterTexto con los datos de este objeto.
														*/
		inline DWLToolTipEx_ObjetoTextoCaracterTexto   *ObtenerTextoCaracterTexto(void) {
															return reinterpret_cast<DWLToolTipEx_ObjetoTextoCaracterTexto *>(_Objeto);
														};

														//! Función que retorna el objeto en forma de clase Texto Caracter Icono.
														/*! Esta función devuelve el objeto en forma de clase Texto Caracter Icono.
																\fn			inline DWLToolTipEx_ObjetoTextoCaracterIcono *ObtenerTextoCaracterIcono(void);
																\return		Devuelve una clase DWLToolTipEx_ObjetoTextoCaracterIcono con los datos de este objeto.
														*/
		inline DWLToolTipEx_ObjetoTextoCaracterIcono   *ObtenerTextoCaracterIcono(void) {
															return reinterpret_cast<DWLToolTipEx_ObjetoTextoCaracterIcono *>(_Objeto);
														};

														//! Función que retorna el objeto en forma de clase Icono Texto.
														/*! Esta función devuelve el objeto en forma de clase Icono Texto.
																\fn			inline DWLToolTipEx_ObjetoIconoTexto *ObtenerIconoTexto(void);
																\return		Devuelve una clase DWLToolTipEx_ObjetoIconoTexto con los datos de este objeto.
														*/
		inline DWLToolTipEx_ObjetoIconoTexto		   *ObtenerIconoTexto(void) {
															return reinterpret_cast<DWLToolTipEx_ObjetoIconoTexto *>(_Objeto);
														};

														//! Función que retorna el tipo de objeto que contiene esta clase.
														/*! Esta función devuelve el tipo de objeto que contiene esta clase.
																\fn			inline DWL_Enum_ToolTipEx_TiposObjeto Tipo(void);
																\return		Devuelve el tipo de objeto que contiene esta clase.
														*/
		inline DWL_Enum_ToolTipEx_TiposObjeto				Tipo(void) {
															return _Tipo;
														};

		protected ://///////////////////////////////////// Miembros protegidos

														//! Tipo de objeto que contiene esta clase.
		 DWL_Enum_ToolTipEx_TiposObjeto					   _Tipo;

														//! Puntero al objeto creado para esta clase.
		 LONG_PTR									   _Objeto;
		};												//
		////////////////////////////////////////////////// Fin DWLToolTipEx_Objeto

    };
};

#endif
