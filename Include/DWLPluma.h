// Modulo que contiene la clase DWLPluma que es un derivado del objeto HPEN de windows.
// Esta clase se ha creado pensando en facilitar la vida al programador, por ello incluye Funciónes para interactuar con varios objetos.
// Ultima modificación 28/04/2009
// Version 1.0

#ifndef DWL_GDI_PLUMA_H
#define DWL_GDI_PLUMA_H

#include "DWLEnumsGDI.h"
#include "DWLhDC.h"
 
namespace DWL {
	namespace GDI {

		// Clase para controlar objetos de tipo HPEN
		class DWLPluma {
		public: ////////////// Miembros publicos
                            //
                            // Constructor
                            // DWLPluma(void);
                            DWLPluma(void) : _Pluma(NULL), _SysColor(false) {
                            };
                            //
                            // Constructor COLORREF
                            // DWLPluma(COLORREF Color, const int Estilo, const int Tam);
                            DWLPluma(COLORREF Color, const int Estilo, const int Tam) : _Pluma(NULL), _SysColor(false)  {
                                _Pluma = CreatePen(Estilo, Tam, Color);
                            };
                            //
                            // Constructor para crear una pluma con un color del sistema
                            // DWLPluma(DWLColoresSistema SColor, const int Estilo, const int Tam);
                            DWLPluma(DWLColoresSistema SColor, const int Estilo, const int Tam) : _Pluma(NULL), _SysColor(false) {
                                _Pluma = CreatePen(Estilo, Tam, GetSysColor(SColor));
                            };
                            //
                            // Constructor para obtener plumas del Stock
                            // DWLPluma(DWLPlumasStock StockColor);
                            DWLPluma(DWLPlumasStock StockColor) : _Pluma(NULL), _SysColor(true) {
                                _Pluma = (HPEN) GetStockObject(StockColor);
                            };
                            //
                            // Destructor
                            // ~DWLPluma(void);
                           ~DWLPluma(void) {
                                if (_Pluma != NULL && _SysColor == false) {
                                    DeleteObject(_Pluma);
                                }
                            };
                            //
                            // Función para borrar la pluma
                            // inline void Borrar(void);
		 inline void        Borrar(void) {
                                if (_Pluma != NULL && _SysColor == false) DeleteObject(_Pluma);
                                _SysColor = false;
                                _Pluma = NULL;
                            };
                            //
                            // Función para asignar/ canviar el color de la pluma
                            //
		 inline void        AsignarColor(COLORREF Color, const int Estilo, const int Tam) {
                                if (_Pluma != NULL && _SysColor == false) DeleteObject(_Pluma);
                                _Pluma = CreatePen(Estilo, Tam, Color);
                                _SysColor = false;
                            };
                            //
                            // Función para canviar / asignar un color del sistema a la pluma
                            // inline void AsignarSysColor(DWLColoresSistema SColor, const int Estilo, const int Tam);
		 inline void        AsignarSysColor(DWLColoresSistema SColor, const int Estilo, const int Tam) {
                                if (_Pluma != NULL && _SysColor == false) DeleteObject(_Pluma);
                                _Pluma = CreatePen(Estilo, Tam, GetSysColor(SColor));
                                _SysColor = false;
                            };
                            //
                            // Función para obtener un color del Stock en nuestra pluma
                            // inline void AsignarStockColor(DWLPlumasStock StockColor)
		 inline void        AsignarStockColor(DWLPlumasStock StockColor) {
                                if (_Pluma != NULL && _SysColor == false) DeleteObject(_Pluma);
                                _Pluma = (HPEN) GetStockObject(StockColor);
                                _SysColor = true;
                            };
                            //
                            // Función que dibuja una linea
                            // inline void PintarLinea(HDC hDC, const int X, const int Y, const int X2, const int Y2);
		 inline void        PintarLinea(HDC hDC, const int X, const int Y, const int X2, const int Y2) {
                                HPEN Viejo = NULL;
                                if (_Pluma != static_cast<HPEN>(GetCurrentObject(hDC, OBJ_PEN))) Viejo = (HPEN)SelectObject(hDC, _Pluma);
                                MoveToEx(hDC, X, Y, NULL);
                                LineTo(hDC, X2, Y2);
                                if (Viejo != NULL) SelectObject(hDC, Viejo);
                            };
                            //
                            // Función que dibuja una linea
                            // void PintarLinea(DWLhDC *hDC, const int X, const int Y, const int X2, const int Y2);
		 void               PintarLinea(DWLhDC *hDC, const int X, const int Y, const int X2, const int Y2);
                            //
                            // Función que retorna la pluma de esta Clase
                            // inline HPEN Pluma(void);
		 inline HPEN        Pluma(void) {
                                return _Pluma;
                            };
                            //
                            // Operador quie retorna la pluma interna de esta clase
                            // inline HPEN operator () (void);
		 inline HPEN        operator () (void) {
                                return _Pluma;
                            };
		private: ///////////// Miembros privados

                            // Constructor copia des-habilitado
                            DWLPluma(DWL::GDI::DWLPluma &) : _Pluma(NULL), _SysColor(false) { };

                            // Operador = des-habilitado
		 inline DWLPluma    &operator=(DWL::GDI::DWLPluma &) { return *this; };
                            //
                            // Pluma de esta clase
		 HPEN              _Pluma;
                            //
                            // Valor para saber si es una pluma del Stock
		 bool              _SysColor;
		};				    //
		////////////////////// Fin DWLPluma
	};
};

#endif
