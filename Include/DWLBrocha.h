// Modulo que contiene la clase DWLBrocha que es un derivado del objeto HBRUSH de windows.
// Esta clase se ha creado pensando en facilitar la vida al programador de forma que se puedan pintar objetos rapidamente.
// Ademas esta clase soporta perfectamente los objetos basicos utilizados en el GDI de windows como son HDC, HRNG, RECT, etc...
// Ultima modificaci�n 28/04/2009
// Version 1.0

#ifndef DWL_BROCHA_H
#define DWL_BROCHA_H

#include "DWLColor.h"

//! Espacio de nombres DWL
namespace DWL {
    //! Espacio de nombres GDI
	namespace GDI {

		class DWLhDC;
		class DWLRecta;
		class DWLRegion;
 
        //! Clase que encapsula un objeto HBRUSH
		class DWLBrocha {
		 public : //////////// Miembors publicos

                            //! Constructor.
                            /*!	Constructor por defecto.
                                    \fn		DWLBrocha(void);
                                    \return	No devuelve nada.
                            */
                            DWLBrocha(void) : _Brocha(NULL), _SysColor(false) {
                            };

                            //! Constructor COLORREF.
                            /*!	Constructor COLORREF.
                                    \fn		   DWLBrocha(COLORREF nColor);
                                    \param[in] nColor : Color RGB para la brocha.
                                    \return	   No devuelve nada.
                            */
                            DWLBrocha(COLORREF nColor) : _Brocha(NULL), _SysColor(false){
                                _Brocha = CreateSolidBrush(nColor);
                            };

                            //! Constructor DWLColor.
                            /*!	Constructor DWLColor.
                                    \fn		   DWLBrocha(DWLColor &nColor);
                                    \param[in] nColor : Clase DWLColor que contiene el color para la brocha.
                                    \return	   No devuelve nada.
                            */
                            DWLBrocha(DWLColor &nColor) : _Brocha(NULL), _SysColor(false) {
                                _Brocha = CreateSolidBrush(nColor.Color());
                            };

                            //! Constructor color del sistema.
                            /*!	Constructor color del sistema.
                                    \fn		   DWLBrocha(const DWLColoresSistema SysColor);
                                    \param[in] SysColor : Color del sistema para la brocha.
                                    \return	   No devuelve nada.
                            */
                            DWLBrocha(const DWLColoresSistema SysColor) : _Brocha(NULL), _SysColor(true) {
                                _Brocha = GetSysColorBrush(SysColor);
                            };

                            //! Constructor objeto stock.
                            /*!	Constructor objeto stock.
                                    \fn		   DWLBrocha(const DWLBrochasStock StockColor);
                                    \param[in] StockColor : Color del stock para la brocha.
                                    \return	   No devuelve nada.
                            */
                            DWLBrocha(const DWLBrochasStock StockColor) : _Brocha(NULL), _SysColor(true) {
                                _Brocha = static_cast<HBRUSH>(GetStockObject(StockColor));
                            };

                            //! Destructor.
                            /*!	Destructor.
                                    \fn		~DWLBrocha(void);
                                    \return	No devuelve nada.
                            */
                           ~DWLBrocha(void) {
                               if (_Brocha != NULL && _SysColor != true) DeleteObject(_Brocha);
                            };

                            //! Funci�n para borrar la brocha.
                            /*!	Esta funci�n borra la brocha.
                                    \fn		inline void Borrar(void);
                                    \return	No devuelve nada.
                            */
		 inline void        Borrar(void) {
                                if (_Brocha != NULL && _SysColor != true) DeleteObject(_Brocha);
                                _Brocha = NULL;
                                _SysColor = false;
                            };

                            //! Funci�n para pintar un RECT en un HDC.
                            /*!	Esta funci�n pinta un RECT en un HDC.
                                    \fn		   inline void PintarRecta(HDC hDC, RECT *R);
                                    \param[in] hDC : HDC donde se va a pintar.
                                    \param[in] R   : RECT que contiene el espacio a pintar.
                                    \return    No devuelve nada.
                            */
		 inline void        PintarRecta(HDC hDC, RECT *R) {
                                FillRect(hDC, R, _Brocha);
                            };

                            //! Funci�n para pintar una clase DWLRecta en una clase DWLhDC.
                            /*!	Esta funci�n pinta una clase DWLRecta en una clase DWLhDC.
                                    \fn		   inline void PintarRecta(DWLhDC &hDC, DWLRecta &R);
                                    \param[in] hDC : clase DWLhDC donde se va a pintar.
                                    \param[in] R   : clase DWLRecta que contiene el espacio a pintar.
                                    \return    No devuelve nada.
                            */
		 void               PintarRecta(DWLhDC &hDC, DWLRecta &R);

                            //! Funci�n para pintar un HRGN en un HDC.
                            /*!	Esta funci�n pinta un HRGN en un HDC.
                                    \fn		   inline void PintarRegion(HDC hDC, HRGN R);
                                    \param[in] hDC : HDC donde se va a pintar.
                                    \param[in] R   : HRGN que contiene el espacio a pintar.
                                    \return    No devuelve nada.
                            */
		 inline void        PintarRegion(HDC hDC, HRGN R) {
                                FillRgn(hDC, R, _Brocha);
                            };

                            //! Funci�n para pintar una clase DWLRegion en una clase DWLhDC.
                            /*!	Esta funci�n pinta una clase DWLRegion en una clase DWLhDC.
                                    \fn		   inline void PintarRegion(DWLhDC &hDC, DWLRegion &R);
                                    \param[in] hDC : clase DWLhDC donde se va a pintar.
                                    \param[in] R   : clase DWLRecta que contiene el espacio a pintar.
                                    \return    No devuelve nada.
                            */
		 void               PintarRegion(DWLhDC &hDC, DWLRegion &R);

                            //! Funci�n para enmarcar un RECT en un HDC.
                            /*!	Esta funci�n enmarca un RECT en un HDC.
                                    \fn		   inline void EnmarcarRecta(HDC hDC, RECT *R);
                                    \param[in] hDC : HDC donde se va a pintar.
                                    \param[in] R   : RECT que contiene el espacio a enmarcar.
                                    \return    No devuelve nada.
                            */
		 inline void        EnmarcarRecta(HDC hDC, RECT *R) {
                                FrameRect(hDC, R, _Brocha);
                            };

                            //! Funci�n para enmarcar una clase DWLRecta en una clase DWLhDC.
                            /*!	Esta funci�n enmarca una clase DWLRecta en una clase DWLhDC.
                                    \fn		   inline void EnmarcarRecta(DWLhDC &hDC, DWLRecta &R);
                                    \param[in] hDC : clase DWLhDC donde se va a pintar.
                                    \param[in] R   : clase DWLRecta que contiene el espacio a enmarcar.
                                    \return    No devuelve nada.
                            */
		 void               EnmarcarRecta(DWLhDC &hDC, DWLRecta &R);

                            //! Funci�n para enmarcar un HRGN en un HDC.
                            /*!	Esta funci�n enmarca un HRGN en un HDC.
                                    \fn		   inline void EnmarcarRegion(HDC hDC, HRGN R, const int cAncho = 1, const int cAlto = 1);
                                    \param[in] hDC    : HDC donde se va a pintar.
                                    \param[in] R      : HRGN que contiene el espacio a enmarcar.
                                    \param[in] cAncho : Ancho en pixeles (1 por defecto).
                                    \param[in] cAlto  : Altura en pixeles (1 por defecto).
                                    \return    No devuelve nada.
                            */
         inline void        EnmarcarRegion(HDC hDC, HRGN R, const int cAncho = 1, const int cAlto = 1) {
                                FrameRgn(hDC, R, _Brocha, cAncho, cAlto);
                            };

                            //! Funci�n para enmarcar una clase DWLRegion en una clase DWLhDC.
                            /*!	Esta funci�n enmarca una clase DWLRegion en una clase DWLhDC.
                                    \fn		   inline void EnmarcarRegion(DWLhDC &hDC, DWLRegion &R, const int cAncho = 1, const int cAlto = 1)
                                    \param[in] hDC    : clase DWLhDC donde se va a pintar.
                                    \param[in] R      : clase DWLRegion que contiene el espacio a enmarcar.
                                    \param[in] cAncho : Ancho en pixeles (1 por defecto).
                                    \param[in] cAlto  : Altura en pixeles (1 por defecto).
                                    \return    No devuelve nada.
                            */
		 void               EnmarcarRegion(DWLhDC &hDC, DWLRegion &R, const int cAncho = 1, const int cAlto = 1);

                            //! Funci�n para asignar un COLORREF a la brocha.
                            /*!	Esta funci�n asigna un COLORREF a la brocha.
                                    \fn		   inline void AsignarColor(COLORREF nColor);
                                    \param[in] nColor : Nuevo color para la brocha.
                                    \return    No devuelve nada.
                            */
		 inline void        AsignarColor(COLORREF nColor) {
                                if (_Brocha != NULL && _SysColor != true) DeleteObject(_Brocha);
                                _SysColor = false;
                                _Brocha = CreateSolidBrush(nColor);
                            };

                            //! Funci�n para asignar una clase DWLColor a la brocha.
                            /*!	Esta funci�n asigna una clase DWLColor a la brocha.
                                    \fn		   inline void AsignarColor(DWLColor &Color);
                                    \param[in] nColor : Nuevo color para la brocha.
                                    \return    No devuelve nada.
                                    \sa        DWLColor
                            */
		 inline void        AsignarColor(DWLColor &Color) {
                                if (_Brocha != NULL && _SysColor != true) DeleteObject(_Brocha);
                                _SysColor = false;
                                _Brocha = CreateSolidBrush(Color.Color());
                            };

                            //! Funci�n para asignar un color del sistema a la brocha.
                            /*!	Esta funci�n asigna un color del sistema a la brocha.
                                    \fn		   inline void AsignarSysColor(const DWLColoresSistema SysColor);
                                    \param[in] SysColor : Nuevo color del sistema para la brocha.
                                    \return    No devuelve nada.
                                    \sa        DWLColoresSistema
                            */
		 inline void        AsignarSysColor(const DWLColoresSistema SysColor) {
                                if (_Brocha != NULL && _SysColor != true) DeleteObject(_Brocha);
                                _SysColor = true;
                                _Brocha = GetSysColorBrush(SysColor);
                            };

                            //! Funci�n para asignar una brocha del stock a la brocha.
                            /*!	Esta funci�n asigna una brocha del stock a la brocha.
                                    \fn		   inline void AsignarStockColor(const DWLBrochasStock StockColor);
                                    \param[in] StockColor : Nueva brocha del stock.
                                    \return    No devuelve nada.
                                    \sa        DWLBrochasStock
                            */
		 inline void        AsignarStockColor(const DWLBrochasStock StockColor) {
                                if (_Brocha != NULL && _SysColor != true) DeleteObject(_Brocha);
                                _SysColor = true;
                                _Brocha = static_cast<HBRUSH>(GetStockObject(StockColor));
                            };

                            //! Funci�n que retorna el HBRUSH de esta clase.
                            /*!	Esta funci�n retorna el HBRUSH de esta clase.
                                    \fn		   inline HBRUSH Brocha(void);
                                    \return    Devuelve el HBRUSH que contiene esta clase.
                            */
		 inline HBRUSH      Brocha(void) {
                                return _Brocha;
                            };

                            //! Operador que retorna el HBRUSH de esta clase.
                            /*!	Este operador retorna el HBRUSH de esta clase.
                                    \fn		   inline HBRUSH operator () (void);
                                    \return    Devuelve el HBRUSH que contiene esta clase.
                            */
		 inline HBRUSH      operator () (void) {
                                return _Brocha;
                            };
		protected: /////////// Miembros protegidos

                            //! Brocha de esta clase
		 HBRUSH            _Brocha;

                            //! Valor para saber si es una brocha del sistema
		 bool              _SysColor;
        private: ///////////// Miembros privados
                            // Constructor copia des-habilitado
                            DWLBrocha(const DWL::GDI::DWLBrocha &) : _Brocha(NULL), _SysColor(false) { };
                            // Operador = des-habilitado
		 inline DWLBrocha  &operator=(const DWL::GDI::DWLBrocha &) { return *this; };

		#if COMPILADOR != COMPILADOR_MINGW
		 friend class	DWLBrocha;
		#endif
		};				//
		////////////////// Fin DWLBrocha


	};
};

#endif
