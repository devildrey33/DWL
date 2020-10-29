/*! \file DWLBarraTareas.cpp
	\brief		 Archivo que contiene las declaraciones para modificar la barra de tareas de windows 7.
    */ 
#ifndef DWL_BARRATAREAS_CPP
#define DWL_BARRATAREAS_CPP

#include "DWLBarraTareas.h"
#include "DWLListaIconos.h"

//#include "Shobjidl.h"


//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Ventanas
    namespace Ventanas {
        //! Espacio de nombres Base
        namespace Base {
			DWLBarraTareas::DWLBarraTareas(void) {
				_BarraTareas = NULL;
			};
			// Win98 +
			void DWLBarraTareas::Resaltar(void) {
				FlashWindow(*_hWnd, TRUE);
				Sleep(300);
				FlashWindow(*_hWnd, TRUE);
			}

			// Win7 +
			void DWLBarraTareas::BarraProgreso_Ocultar(void)  { 
				if (_BarraTareas != NULL) _BarraTareas->SetProgressState(*_hWnd, TBPF_NOPROGRESS);
			};

			void DWLBarraTareas::BarraProgreso_Estado_Normal(void)  { 
				if (_BarraTareas != NULL) _BarraTareas->SetProgressState(*_hWnd, TBPF_NORMAL);
			};

			void DWLBarraTareas::BarraProgreso_Estado_Pausa(void)  {
				if (_BarraTareas != NULL) _BarraTareas->SetProgressState(*_hWnd, TBPF_PAUSED); 
			};

			void DWLBarraTareas::BarraProgreso_Estado_Error(void)  { 
				if (_BarraTareas != NULL) _BarraTareas->SetProgressState(*_hWnd, TBPF_ERROR);
			};

			void DWLBarraTareas::BarraProgreso_Valor(const UINT nValor, const UINT nMaximo) { 
				if (_BarraTareas != NULL) _BarraTareas->SetProgressValue(*_hWnd, nValor, nMaximo);
			};

			// Los botones se tienen que agregar antes de recibir el evento Evento_BotonBarraTareas_Creado
			void DWLBarraTareas::Boton_Agregar(UINT nIDIcono, const TCHAR *nTextoToolTip, const UINT nID) {
				DWLBarraTareas_Boton nBoton(nIDIcono, nTextoToolTip, nID);
				_Botones.push_back(nBoton);
			};

			void DWLBarraTareas::Boton_Icono(const UINT nID, const UINT IDIcono) {
				if (_BarraTareas != NULL) {
					THUMBBUTTON Boton;
					Boton.dwMask	= THB_ICON;
					Boton.iId		= nID;
					Boton.hIcon		= DWL::SO::DWLListaIconos::BuscarIcono(IDIcono, 16, 16)->Icono();
					HRESULT Ret = _BarraTareas->ThumbBarUpdateButtons(*_hWnd, 1, &Boton);
				}
			}

			void DWLBarraTareas::Boton_Activado(const UINT nID, const bool nActivado) {
				if (_BarraTareas != NULL) {
					THUMBBUTTON Boton;
					Boton.dwMask	= THB_FLAGS;
					Boton.iId		= nID;
					if (nActivado == true)	Boton.dwFlags = THBF_ENABLED;
					else					Boton.dwFlags = THBF_DISABLED;				
					HRESULT Ret = _BarraTareas->ThumbBarUpdateButtons(*_hWnd, 1, &Boton);
				}
			}

			void DWLBarraTareas::Boton_Visible(const UINT nID, const bool nVisible) {
				if (_BarraTareas != NULL) {
					THUMBBUTTON Boton;
					Boton.dwMask	= THB_FLAGS;
					Boton.iId		= nID;
					if (nVisible == true)	Boton.dwFlags = THBF_ENABLED;
					else					Boton.dwFlags = THBF_HIDDEN;
					HRESULT Ret = _BarraTareas->ThumbBarUpdateButtons(*_hWnd, 1, &Boton);
				}
			}

			void DWLBarraTareas::_CrearBotones(void) {
				_ObtenerTaskBarList3(); 
				if (_Botones.size() == 0) return;
				if (_BarraTareas != NULL) {
					THUMBBUTTON *nBotones = new THUMBBUTTON[_Botones.size()];
					for (size_t i = 0; i < _Botones.size(); i++) {
						nBotones[i].dwMask	= THB_ICON | THB_TOOLTIP | THB_FLAGS;
						nBotones[i].iId		= _Botones[i].ID;
						nBotones[i].hIcon	= DWL::SO::DWLListaIconos::BuscarIcono(_Botones[i].IDIcono, 16, 16)->Icono();
						nBotones[i].dwFlags = THBF_ENABLED;
						wcscpy_s(nBotones[i].szTip, 260, _Botones[i].TextoToolTip());
					}
					HRESULT Ret = _BarraTareas->ThumbBarAddButtons(*_hWnd, _Botones.size(), nBotones);
					delete [] nBotones;
					_Botones.resize(0);
				}
			}

			void DWLBarraTareas::_ObtenerTaskBarList3(void) { 
				if (CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList3, (void**)&_BarraTareas) == S_OK) {
					if (_BarraTareas != NULL) _BarraTareas->HrInit();
				}
				else { // No se ha encontrado el interface (WinVista o inferior)
					_BarraTareas = NULL;
				}
			};

			void DWLBarraTareas::_Enlazar(HWND *hWnd) {
				_hWnd = hWnd;
			};

		};
	};
};

#endif
