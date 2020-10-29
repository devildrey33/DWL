#ifndef DWL_EDICIONEX_NUCLEO_H
#define DWL_EDICIONEX_NUCLEO_H

#include "..\DWLBarraScrollEx.h"
#include "..\DWLString.h"
#include <vector>
#include "DWLEdicionEx_Objeto.h"

#include "DWLEdicionEx_Estilos.h"
 

namespace DWL {
	namespace ControlesEx {


		class DWLEdicionEx_Nucleo : public DWLBarraScrollEx_Nucleo {
          public :
													DWLEdicionEx_Nucleo(void);
                                                   ~DWLEdicionEx_Nucleo(void);
			inline void                             EdicionEx_Activado(const bool nActivar) { _EdicionEx_Activado = nActivar; };
			inline bool                             EdicionEx_Activado(void) const { return _EdicionEx_Activado; };

//			void									EdicionEx_NuevoTexto(HWND hWndControl, const TCHAR *nTexto, const bool CursorAlFinal = true);
			const TCHAR                            *EdicionEx_ObtenerTexto(void);

			void                                    EdicionEx_AgregarTexto(HWND hWndControl, const TCHAR *nTexto);
			void                                    EdicionEx_AgregarFuente(HWND hWndControl, HFONT nFuente);
			void                                    EdicionEx_AgregarColorFondo(COLORREF nColor);
			void                                    EdicionEx_AgregarColorTexto(COLORREF nColor);

			void                                    EdicionEx_AgregarTextoCursor(HWND hWndControl, const TCHAR *nTexto);
			void									EdicionEx_AgregarFuenteCursor(HWND hWndControl, HFONT nFuente);
			void                                    EdicionEx_AgregarColorFondoCursor(COLORREF nColor);
			void                                    EdicionEx_AgregarColorTextoCursor(COLORREF nColor);

			UINT            						EdicionEx_LongitudTexto(void) const;
            void									EdicionEx_BorrarTexto(void);
            void									EdicionEx_Pintar(HDC hDC, RECT *Espacio, const bool TieneFoco, const bool PintarConMascara);
            void									EdicionEx_Teclado_TeclaPresionada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params);
            void									EdicionEx_Teclado_TeclaSoltada(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params);
            void									EdicionEx_Teclado_Caracter(HWND hWndControl, const UINT Caracter, const UINT Repeticion, const UINT Params);
	        const BOOL								EdicionEx_Mouse_Movimiento(HWND hWndControl, RECT *RectaControl, const int cX, const int cY, const UINT wParam);
            const BOOL								EdicionEx_Mouse_BotonPresionado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
            const BOOL								EdicionEx_Mouse_BotonSoltado(HWND hWndControl, RECT *RectaControl, const UINT Boton, const int cX, const int cY, const UINT Param);
			const BOOL								EdicionEx_Mouse_Rueda(const short Delta, const short cX, const short cY, const UINT VirtKey);
			DWL::ControlesEx::DWLEdicionEx_Estilos	EdicionEx_Estilos;
          protected :
			const long                             _EdicionEx_PintarTexto(HDC hDCDest, HDC Buffer, DWLString &Txt, const int cX, const int cY, DWLEdicionEx_ObjetoSaltoLinea *SaltoLinea, DWLEdicionEx_ObjetoFuente *Fuente, COLORREF nColorFondo, COLORREF nColorTexto);
			const long                             _EdicionEx_ObtenerObjetoCoordenadas(HWND hWndControl, const int cX, const int cY);
			void			                       _EdicionEx_CrearCursor(const long nPosCursor);
			void		                           _EdicionEx_EliminarCursor(void);
			void								   _EdicionEx_CalcularLinea(HWND hWndControl, DWLEdicionEx_ObjetoSaltoLinea *nSaltoLinea);
			void     			                   _EdicionEx_LimpiarSeleccion(void);
			void     			                   _EdicionEx_BorrarCursor(void);
			void     			                   _EdicionEx_PosicionSeleccion(long &PosSel1, long &PosSel2);
			const long			                   _EdicionEx_PosicionCursor(void);
												    // Devuelve el salto de linea que hay detras de Pos
			const long                             _EdicionEx_SaltoLineaAnterior(const long Pos);
											    	// Devuelve el salto de linea que hay delante de Pos o -1 si se llega al final
			const long                             _EdicionEx_SaltoLineaSiguiente(const long Pos);

			const SIZE                             _EdicionEx_CalcularScrolls(HWND hWndControl, const long ValorV = 0, const long ValorH = 0, const bool HacerVisibleCursor = false);
			void                                   _EdicionEx_HacerVisibleCursor(HWND hWndControl);

			void                                   _EdicionEx_AgregarCaracter(HWND hWndControl, const TCHAR nCaracter);
			void                                   _EdicionEx_AgregarIntro(HWND hWndControl);
			void                                   _EdicionEx_BorrarCaracter(HWND hWndControl, const bool TeclaSuprimir = false);

			const bool                             _EdicionEx_Tecla_Inicio(void);
			const bool                             _EdicionEx_Tecla_Fin(void);
			const bool                             _EdicionEx_Tecla_Arriba(void);
			const bool                             _EdicionEx_Tecla_Abajo(void);
			const bool                             _EdicionEx_Tecla_Derecha(void);
			const bool                             _EdicionEx_Tecla_Izquierda(void);

            std::vector<DWLEdicionEx_Objeto *>     _EdicionEx_Objetos;

			long                                   _EdicionEx_UltimoObjetoMouse;
            int                                    _EdicionEx_CursorX;
			bool                                   _EdicionEx_TeclaShiftPresionada;
			bool                                   _EdicionEx_TeclaControlPresionada;
			bool                                   _EdicionEx_Activado;
			bool                                   _EdicionEx_CursorVisible;

			DWLString                              _EdicionEx_TmpTxt;

			long                                   _EdicionEx_MaximoAltoLinea;
			long                                   _EdicionEx_MaximoAnchoLinea;

        };
	};
};

#endif