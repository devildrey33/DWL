#pragma once

#include <vector>
#include "DWL.h"
#include "DWLString.h"
 
namespace DWL {
	namespace SO {
		class DWLListaIconos;

		class DWLListaIconos_Icono {
		public :
                                        DWLListaIconos_Icono(void) : _ID(0), _Icono(0), _PosicionStr(-1), _Ancho(16), _Alto(16), _IDStr() {
                                        };

                                        DWLListaIconos_Icono(HICON nIcono, const int nID, const int nAncho, const int nAlto, const TCHAR *nIDStr = NULL, const int nPosicionStr = -1)  : _ID(nID), _Icono(nIcono), _PosicionStr(nPosicionStr), _Ancho(nAncho), _Alto(nAlto) {
											_IDStr = nIDStr;
										};

                                       ~DWLListaIconos_Icono(void) {
                                        };

		inline HICON		            Icono(void)	{
                                            return _Icono;
                                        };

		inline int	                    ID(void) const {
                                            return _ID;
                                        };
		protected :
		 int			               _Ancho;
		 int			               _Alto;
		 int                           _ID;
		 HICON	                       _Icono;
		 DWLString		               _IDStr;
		 int			               _PosicionStr;
        private :
                                        //! Constructor copia des-habilitado
                                        DWLListaIconos_Icono(const DWLListaIconos_Icono &)  : _ID(0), _Icono(0), _PosicionStr(-1), _Ancho(16), _Alto(16), _IDStr() { };
                                        //! Operador = des-habilitado
		 inline DWLListaIconos_Icono   &operator=(const DWLListaIconos_Icono &) { return *this; };

		 friend class DWLListaIconos;
		};

		class DWLListaIconos {
			public:
															DWLListaIconos(void);
											               ~DWLListaIconos(void);
															// Función que pinta el icono especificado en el DC
															// Si el icono no fue cargado se carga automaticamente de los recursos y permanece hasta el fin de la aplicacion.
			 static void									PintarIcono(HDC hDC, const int cX, const int cY, const int cAnchoIco, const int cAltoIco, const int IDIco);
															// Función que pinta el icono especificado en el DC con un reborde resaltado
			 static void                                    PintarIconoResaltado(HDC hDC, const int cX, const int cY, const int cAnchoIco, const int cAltoIco, const int IDIco, COLORREF ColorResaltado);
															// Esta función agrega un icono externo a la lista de iconos
			 static DWLListaIconos_Icono				   *AgregarIconoExterno(HICON Icono, const int IDNegativa, const int cAnchoIco, const int cAltoIco, const TCHAR *nIDStr, const int nPosicionStr);
															// Función que elimina todos los iconos de la memoria
			 static void									Borrar(void);
			 static DWLListaIconos_Icono				   *BuscarIcono(const int bID, const int bAncho, const int bAlto);
			 static DWLListaIconos_Icono				   *BuscarIDStr(const TCHAR *nIDStr, const int nPosicionStr);
		                                                    //! Función que carga un icono de un ejecutable.
	                                                        /*! Esta funcion carga un icono de un ejecutable.
			                                                        \fn			const int CargarIcono(const TCHAR *Path);
			                                                        \param[in]	Path : HWND de la ventana que recibira el foco despues de esta.
	                                                                \return		Devuelve el indice del icono en la lista de iconos.
	                                                        */
        	 static int                                     CargarIcono(const TCHAR *Path);

		                                                    //! Función que carga un icono de un CSIDL.
		                                                    /*! Esta funcion carga un icono de un CSIDL.
				                                                    \fn			const int CargarIcono(const int CSIDL);
				                                                    \param[in]	CSIDL : ID del icono correspondiente.
		                                                            \return		Devuelve el indice del icono en la lista de iconos.
		                                                    */
    		 static int                                     CargarIcono(const int CSIDL);
			private:
			 static std::vector<DWLListaIconos_Icono *>    _Iconos;
             static int                                    _IDActual;
			 //friend class DWLListaIconos_Icono;
		};
	};
};
