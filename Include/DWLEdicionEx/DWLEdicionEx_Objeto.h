#ifndef DWL_EDICIONEX_OBJETOS_H
#define DWL_EDICIONEX_OBJETOS_H

#include "../DWL.h"

enum DWL_Enum_EdicionEx_TipoObjeto {
	DWL_Enum_EdicionEx_TipoObjeto_Caracter	 = 0,
	DWL_Enum_EdicionEx_TipoObjeto_Fuente	 = 1,
	DWL_Enum_EdicionEx_TipoObjeto_ColorTexto = 2,
	DWL_Enum_EdicionEx_TipoObjeto_ColorFondo = 3,
	DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea = 4,
	DWL_Enum_EdicionEx_TipoObjeto_Cursor     = 5,
	DWL_Enum_EdicionEx_TipoObjeto_INICIO     = 6,
	DWL_Enum_EdicionEx_TipoObjeto_FINAL      = 7,
	DWL_Enum_EdicionEx_TipoObjeto_Seleccion  = 8
};

namespace DWL {
	namespace ControlesEx {

		class DWLEdicionEx_ObjetoFuente {
		  public :
					DWLEdicionEx_ObjetoFuente(HFONT nFuente = NULL, long nAscent = 0, long nDescent = 0) : Fuente(nFuente), Ascent(nAscent), Descent(nDescent) { };
			HFONT	Fuente;
			long	Ascent;
			long	Descent; // NO SE USA
		};

		class DWLEdicionEx_ObjetoSaltoLinea {
		  public :
					DWLEdicionEx_ObjetoSaltoLinea(const long nTamX = 0, const long nTamY = 0, const long nLineaBase = 0) : TamX(nTamX), TamY(nTamY), LineaBase(nLineaBase) { };
			long	TamX;
			long	TamY;
			long	LineaBase;
			// añadir alineacion
		};
		
		class DWLEdicionEx_Objeto {
		  public :
													DWLEdicionEx_Objeto(DWL_Enum_EdicionEx_TipoObjeto nTipo, LPVOID nObjeto) : _Tipo(nTipo), _Objeto(nObjeto) {
														SOLO_DEBUG(_DEBUG_Color		 = reinterpret_cast<COLORREF *>(&_Objeto));
														SOLO_DEBUG(_DEBUG_Caracter	 = reinterpret_cast<TCHAR *>(&_Objeto));
														SOLO_DEBUG(_DEBUG_SaltoLinea = static_cast<DWLEdicionEx_ObjetoSaltoLinea *>(_Objeto));
														SOLO_DEBUG(_DEBUG_Fuente	 = static_cast<DWLEdicionEx_ObjetoFuente *>(_Objeto));
													};

												   ~DWLEdicionEx_Objeto(void) { 
														switch (_Tipo) {
															case DWL_Enum_EdicionEx_TipoObjeto_SaltoLinea :	case DWL_Enum_EdicionEx_TipoObjeto_INICIO :
																delete static_cast<DWLEdicionEx_ObjetoSaltoLinea *>(_Objeto);
																break;
															case DWL_Enum_EdicionEx_TipoObjeto_Fuente :
																delete static_cast<DWLEdicionEx_ObjetoFuente *>(_Objeto);
																break;
															case DWL_Enum_EdicionEx_TipoObjeto_Caracter :
																delete static_cast<TCHAR *>(_Objeto);
																break;
														}
													};

			inline DWL_Enum_EdicionEx_TipoObjeto	Tipo(void) { return _Tipo; };
			inline COLORREF                         ColorTexto(void) { return reinterpret_cast<COLORREF>(_Objeto); };
			inline COLORREF                         ColorFondo(void) { return reinterpret_cast<COLORREF>(_Objeto); };
			inline DWLEdicionEx_ObjetoFuente       *Fuente(void) { return static_cast<DWLEdicionEx_ObjetoFuente *>(_Objeto); };
			inline TCHAR                            Caracter(void) { return *static_cast<TCHAR *>(_Objeto); }; // NB ERROR
			inline DWLEdicionEx_ObjetoSaltoLinea   *SaltoLinea(void) { return static_cast<DWLEdicionEx_ObjetoSaltoLinea *>(_Objeto); };
		  protected :
			LPVOID                                 _Objeto;
		    DWL_Enum_EdicionEx_TipoObjeto          _Tipo;
		  private :
			// Parametros creados para ver bien el objeto durante la depuracion NO DEBEN USARSE EN NINGUN MOMENTO PARA NADA
			SOLO_DEBUG(COLORREF                      *_DEBUG_Color);
			SOLO_DEBUG(DWLEdicionEx_ObjetoFuente     *_DEBUG_Fuente);
			SOLO_DEBUG(DWLEdicionEx_ObjetoSaltoLinea *_DEBUG_SaltoLinea);
			SOLO_DEBUG(TCHAR                         *_DEBUG_Caracter);
		};
	};
};
 
#endif