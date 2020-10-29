// Modulo que contiene la clase DWLColor que es un derivado del objeto COLORREF de windows.
// Esta clase se ha creado pensando en facilitar la vida al programador de forma que se puedan modificar los canales por separado.
// Ultima modificación 28/04/2009
// Version 1.0

#ifndef DWL_GDI_COLOR_H
#define DWL_GDI_COLOR_H

#include "DWLEnumsGDI.h"
 
//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres GDI
	namespace GDI {
		//! Clase que encapsula el tipo COLORREF
		class DWLColor {
		 public : //////////// Metodos publicos

							//! Constructor por defecto (asigna el color a negro).
							/*!	Constructor por defecto (asigna el color a negro).
									\fn		DWLColor(void);
									\return	No devuelve nada.
							*/
       						DWLColor(void) : _Color(0) {
							};

							//! Constructor para asignar un color del sistema.
							/*!	Constructor que asigna un color del sistema.
									\fn		   DWLColor(const DWLColoresSistema nColor);
                                    \param[in] nColor : Nuevo color del sistema.
									\return	   No devuelve nada.
                                    \sa        DWLColoresSistema
							*/
							DWLColor(const DWLColoresSistema nColor) : _Color(0) {
								_Color = GetSysColor(nColor);
							};

							//! Constructor para asignar un color por canales RGB.
							/*!	Constructor que asigna un color por canales RGB.
									\fn		   DWLColor(const BYTE R, const BYTE V, const BYTE A);
                                    \param[in] R : Canal rojo (0-255).
                                    \param[in] G : Canal verde (0-255).
                                    \param[in] B : Canal azul (0-255).
									\return	   No devuelve nada.
							*/
							DWLColor(const BYTE R, const BYTE V, const BYTE A) : _Color(0) {
								_Color = RGB(R, V, A);
							};

							//! Constructor para asignar un COLORREF.
							/*!	Constructor que asigna un COLORREF.
									\fn		   DWLColor(COLORREF nColor);
                                    \param[in] nColor : Nuevo color.
									\return	   No devuelve nada.
							*/
							DWLColor(COLORREF nColor) : _Color(nColor) {
							};

							//! Destructor.
							/*!	Destructor.
									\fn		   ~DWLColor(void);
									\return	   No devuelve nada.
							*/
						   ~DWLColor(void) {
							};

							//! Función para asignar un color del sistema.
							/*!	Esta función asigna un color del sistema.
									\fn		   inline void AsignarSysColor(const DWLColoresSistema nColor);
                                    \param[in] nColor : Nuevo color del sistema.
									\return	   No devuelve nada.
                                    \sa        DWLColoresSistema
							*/
		 inline void		AsignarSysColor(const DWLColoresSistema nColor) {
								_Color = GetSysColor(nColor);
							};

							//! Función para asignar un COLORREF.
							/*!	Esta función asigna un COLORREF.
									\fn		   inline void AsignarColor(COLORREF nColor);
                                    \param[in] nColor : Nuevo color.
									\return	   No devuelve nada.
							*/
		 inline void		AsignarColor(COLORREF nColor) {
								_Color = nColor;
							};

							//! Función para asignar un color por canales RGB.
							/*!	Esta función asigna un color por canales RGB.
									\fn		   inline void AsignarColor(const BYTE R, const BYTE V, const BYTE A);
                                    \param[in] R : Canal rojo (0-255).
                                    \param[in] G : Canal verde (0-255).
                                    \param[in] B : Canal azul (0-255).
									\return	   No devuelve nada.
							*/
		 inline void		AsignarColor(const BYTE R, const BYTE V, const BYTE A) {
								_Color = RGB(R, V, A);
							};

							//! Función para asignar el canal rojo del color.
							/*!	Esta función asigna el canal rojo del color.
									\fn		   inline void Rojo(const BYTE Val);
                                    \param[in] Val : Canal rojo (0-255).
									\return	   No devuelve nada.
							*/
		 inline void		Rojo(const BYTE Val) {
								_Color = RGB(Val, GetGValue(_Color), GetBValue(_Color));
							};

							//! Función para asignar el canal verde del color.
							/*!	Esta función asigna el canal verde del color.
									\fn		   inline void Verde(const BYTE Val);
                                    \param[in] Val : Canal verde (0-255).
									\return	   No devuelve nada.
							*/
		 inline void		Verde(const BYTE Val) {
								_Color = RGB(GetRValue(_Color), Val, GetBValue(_Color));
							};

							//! Función para asignar el canal azul del color.
							/*!	Esta función asigna el canal azul del color.
									\fn		   inline void Azul(const BYTE Val);
                                    \param[in] Val : Canal azul (0-255).
									\return	   No devuelve nada.
							*/
		 inline void		Azul(const BYTE Val) {
								_Color = RGB(GetRValue(_Color), GetGValue(_Color), Val);
							};

							//! Función para obtener el canal rojo del color.
							/*!	Esta función obtiene el canal rojo del color.
									\fn		   inline BYTE Rojo(void) const;
									\return	   Devuelve el canal rojo del color.
							*/
		 inline BYTE	    Rojo(void) const {
								return GetRValue(_Color);
							};

							//! Función para obtener el canal verde del color.
							/*!	Esta función obtiene el canal verde del color.
									\fn		   inline BYTE Verde(void) const;
									\return	   Devuelve el canal verde del color.
							*/
		 inline BYTE	    Verde(void) const {
								return GetGValue(_Color);
							};

							//! Función para obtener el canal azul del color.
							/*!	Esta función obtiene el canal azul del color.
									\fn		   inline BYTE Azul(void) const;
									\return	   Devuelve el canal azul del color.
							*/
		 inline BYTE	    Azul(void) const {
								return GetBValue(_Color);
							};

							//! Función para obtener el COLORREF de esta clase.
							/*!	Esta función obtiene el COLORREF de esta clase.
									\fn		   inline COLORREF Color(void);
									\return	   Devuelve el COLORREF de esta clase.
							*/
		 inline COLORREF	Color(void)	{
								return _Color;
							};

							//! Operador para obtener el COLORREF de esta clase.
							/*!	Esta operador obtiene el COLORREF de esta clase.
									\fn		   inline COLORREF operator () (void);
									\return	   Devuelve el COLORREF de esta clase.
							*/
		 inline COLORREF	operator () (void) {
								return _Color;
							};

							//! Operador para asignar el COLORREF de esta clase.
							/*!	Esta operador asigna el COLORREF de esta clase.
									\fn		   inline void operator () (COLORREF NColor);
                                    \param[in] NColor : Nuevo color.
									\return	   No devuelve nada.
							*/
		 inline void		operator () (COLORREF NColor) {
								_Color = NColor;
							};

							//! Operador para asignar una clase DWLColor a esta clase.
							/*!	Esta operador asigna una clase DWLColor a esta clase.
									\fn		   inline DWLColor &operator = (DWLColor &nCol);
                                    \param[in] nCol : Nuevo color.
									\return	   No devuelve nada.
							*/
		 inline DWLColor   &operator = (DWLColor &nCol) {
								_Color = nCol.Color();
								return *this;
							};

							//! Operador para asignar el COLORREF de esta clase.
							/*!	Esta operador asigna el COLORREF de esta clase.
									\fn		   inline DWLColor &operator = (COLORREF nCol);
                                    \param[in] nCol : Nuevo color.
									\return	   No devuelve nada.
							*/
		 inline DWLColor   &operator = (COLORREF nCol) {
								_Color = nCol;
								return *this;
							};

							//! Operador para comparar una clase DWLColor con esta clase.
							/*!	Esta operador compara una clase DWLColor con esta clase.
									\fn		   inline BOOL operator == (DWLColor &nCol) const;
                                    \param[in] nCol : Color a comparar.
									\return	   No devuelve nada.
							*/
		 inline BOOL		operator == (DWLColor &nCol) const {
								if (_Color == nCol.Color())  return TRUE;
								return FALSE;
							};

							//! Operador para comparar un COLORREF con esta clase.
							/*!	Esta operador compara un COLORREF con esta clase.
									\fn		   inline BOOL operator == (COLORREF nCol);
                                    \param[in] nCol : Color a comparar.
									\return	   No devuelve nada.
							*/
		 inline BOOL		operator == (COLORREF nCol) const {
								if (_Color == nCol) return TRUE;
								return FALSE;
							};
		 private: //////////// Miembros privados
                            // Constructor copia des-habilitado
                            DWLColor(const DWL::GDI::DWLColor &): _Color(0) { };
                            // Operador = des-habilitado
//		 inline HFONT       operator=(const DWL::GDI::DWLColor &) { };

							//! Color de esta clase
		 COLORREF          _Color;
		};
        ////////////////////// FIN DWLColor
	};
};

#endif
