// Modulo que contiene la clase DWLIcono que es un derivado del objeto HICON de windows.
// Esta clase se ha creado pensando en facilitar la vida al programador, por ello incluye Funciónes para interactuar con varios objetos.
// Ultima modificación 28/04/2009
// Version 1.0

#ifndef DWL_GDI_ICONO_H
#define DWL_GDI_ICONO_H
 
#include "DWLEnumsGDI.h"
#include "DWLhDC.h"

namespace DWL {
	namespace GDI {

		// Clase para usar objetos de tipo HICON
		class DWLIcono {
		 public : //////////// Miembros publicos
                            //
                            // Constructor
                            // DWLIcono(void);
                            DWLIcono(void) : _Icono(NULL) {
                            };
                            //
                            // Constructor Icono de los recursos
                            // DWLIcono(const int ResIcono);
                            DWLIcono(const int ResIcono) : _Icono(NULL) {
                                _Icono = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(ResIcono));
                            };
                            //
                            // Constructor Iconos externos
                            // DWLIcono(TCHAR *Path);
                            DWLIcono(TCHAR *Path) : _Icono(NULL) {
                                _Icono = LoadIcon(GetModuleHandle(NULL), Path);
                            };
                            //
                            // Constructor Icono de los recursos con tamaño
                            // DWLIcono(const int ResIcono, const int Ancho, const int Alto);
                            DWLIcono(const int ResIcono, const int Ancho, const int Alto) : _Icono(NULL) {
                                _Icono = static_cast<HICON>(LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(ResIcono), IMAGE_ICON, Ancho, Alto, LR_DEFAULTCOLOR));
                            };
                            //
                            // Constructor Iconos externos con tamaño
                            // DWLIcono(TCHAR *Path, const int Ancho, const int Alto);
                            DWLIcono(TCHAR *Path, const int Ancho, const int Alto) : _Icono(NULL) {
                                _Icono = static_cast<HICON>(LoadImage(GetModuleHandle(NULL), Path, IMAGE_ICON, Ancho, Alto, LR_DEFAULTCOLOR));
                            };
                            //
                            // Destructor
                            // ~DWLIcono(void);
                           ~DWLIcono(void) {
                               if (_Icono != NULL) DestroyIcon(_Icono);
                               _Icono = NULL;
                            };
                            //
                            // Función para cargar un icono de los recursos
                            // inline void CargarIcono(const int ResIcono);
		 inline void        CargarIcono(const int ResIcono) {
                                _Icono = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(ResIcono));
                            };
                            //
                            // Función para cargar un icono externo
                            // inline void CargarIcono(TCHAR *Path);
		 inline void        CargarIcono(TCHAR *Path) {
                                _Icono = LoadIcon(GetModuleHandle(NULL), Path);
                            };
                            //
                            // Función para cargar un icono de los recursos con tamaño
                            // inline void CargarIcono(const int ResIcono, const int Ancho, const int Alto);
		 inline void        CargarIcono(const int ResIcono, const int Ancho, const int Alto) {
                                _Icono = static_cast<HICON>(LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(ResIcono), IMAGE_ICON, Ancho, Alto, LR_DEFAULTCOLOR));
                            };
                            //
                            // Función para cargar un icono externo con tamaño
                            // inline void CargarIcono(TCHAR *Path, const int Ancho, const int Alto);
		 inline void        CargarIcono(TCHAR *Path, const int Ancho, const int Alto) {
                                _Icono = static_cast<HICON>(LoadImage(GetModuleHandle(NULL), Path, IMAGE_ICON, Ancho, Alto, LR_DEFAULTCOLOR));
                            };
                            //
                            // Función para borrar el icono interno
                            // inline void BorrarIcono(void);
		 inline void        BorrarIcono(void) {
                                if (_Icono != NULL) DestroyIcon(_Icono);
                                _Icono = NULL;
                            };
                            //
                            // Función para pintar el icono en un DWLhDC
                            // void PintarIcono(DWLhDC *hDC, const int X, const int Y, const int Ancho, const int Alto);
		 void               PintarIcono(DWLhDC *hDC, const int X, const int Y, const int Ancho, const int Alto);
                            //
                            // Función para pintar el icono en un hDC
                            // inline void PintarIcono(HDC hDC, const int X, const int Y, const int Ancho, const int Alto);
		 inline void        PintarIcono(HDC hDC, const int X, const int Y, const int Ancho, const int Alto) {
                                DrawIconEx(hDC, X, Y, _Icono, Ancho, Alto, 0, 0, DI_NORMAL);
                            };
                            //
                            // Función que retorna el icono interno de esta clase
                            // inline HICON Icono(void);
		 inline HICON       Icono(void) {
                                return _Icono;
                            };
                            //
                            // Operador que retorna el icono interno de esta clase
                            // inline HICON operator() (void);
		 inline HICON       operator() (void) {
                                return _Icono;
                            };
		private : //////////// Metodos privados

                            // Constructor copia des-habilitado
                            DWLIcono(const DWL::GDI::DWLIcono &) : _Icono(NULL) { };
                            // Operador = des-habilitado
		 inline DWLIcono   &operator=(const DWL::GDI::DWLIcono &) { return *this; };
                            //
                            // Icono interno de esta clase
		 HICON             _Icono;
		};				    //
		////////////////////// Fin DWLIcono
	};
};

#endif
