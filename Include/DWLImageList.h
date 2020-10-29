/*! \file DWLImageList.h
	\brief		Archivo que contiene funciones para la utilización de un imagelist en windows.


	\details	Clase diseñada para poder controlar un imagelist de windows.																			\n
				Esta clase en breve no formara parte del proyecto y por lo tanto no recibira actualizaciones.											\n
				Para los controles ListaEx y ArbolEx no es necesario crear ninguna lista de imagenes, ya que estos controles lo hacen internamente.		\n
				Para la version 1.0 de la DWL esta clase probablemente desaparecera.																	\n

																																						\n
	\author		devildrey33
	\version	0.95
	\date		28/07/2005

	\remarks
				Archivo creado por devildrey33 el dia [21/03/2004] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n	
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n	
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n	

*/
 
#ifndef DWL_IMAGELIST_H
#define DWL_IMAGELIST_H

#include "DWL.h"

//! Espacio de nombres DWL
namespace DWL {
	//! Espacio de nombres Controles
	namespace Controles {
		//! Clase para controlar un ImageList de windows.
		class DWLImageList {
		public : ///////////////////// Miembros publicos
									//
									//! Constructor (vacio)
									//  DWLImageList(void);
									DWLImageList(void) { 
										_ImgList = NULL;
									};
									//
									//! Destructor que borra el ImageList y los Iconos
	 								// ~DWLImageList(void);
								   ~DWLImageList(void)            { 
										if (_ImgList != NULL) {
											ImageList_Destroy(_ImgList); 
											_ImgList = NULL;
											for (unsigned int i = 0; i < _Ikos.size(); i++) {  
												if (_Eliminable[i] == true) DestroyIcon(_Ikos[i]); 
											} 
										}
									};
									//
									//! Función para crear el ImageList
									//  inline void Crear(const unsigned short Tam);
		 inline void                Crear(const unsigned short Tam = 16) { 
										_ImgList = ImageList_Create(Tam, Tam, ILC_COLORDDB | ILC_MASK, 1, 0);
										_Tam = Tam; 
									};
									//
									//! Función para destruir el ImageList
									//  inline void Destruir(void);
		 inline void		        Destruir(void) {
										if (_ImgList != NULL) {
											ImageList_Destroy(_ImgList); 
											for (unsigned int i = 0; i < _Ikos.size(); i++) {  
												if (_Eliminable[i] == true) DestroyIcon(_Ikos[i]); 
											} 
											_ImgList = NULL;
											_Ikos.resize(0);
										}
									};
									//
									//! Función para agregar un Icono (Este se NO borrara automaticamente, deberas borrarlo tu mas tarde la ma memoria!)
									//  inline const unsigned int AgregarIcono(HICON nIcono);
		 inline const unsigned int  AgregarIcono(HICON nIcono) {
										_Ikos.push_back(nIcono); 
										_Eliminable.push_back(false);
										ImageList_AddIcon(_ImgList, nIcono); 
										return static_cast<unsigned int>(_Ikos.size()) -1;
									};
									//
									//! Función para agregar un Icono de los recursos (Este se borrara automaticamente)
									//  inline const unsigned int AgregarIconoRecursos(const int cID);
		 inline const unsigned int  AgregarIconoRecursos(const int cID) {
										HICON hIcon;
										hIcon = (HICON) LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(cID), IMAGE_ICON, _Tam, _Tam, LR_DEFAULTCOLOR);
										_Ikos.push_back(hIcon); 
										_Eliminable.push_back(true);
										ImageList_AddIcon(_ImgList, hIcon); 
										return static_cast<unsigned int>(_Ikos.size()) -1;
									};
									//
									//! Función para eliminar un icono del Imagelist (Este se borrara o no dependiendo de como se haya añadido)
									//  inline void BorrarIcono(const int Pos);
		 inline const bool			BorrarIcono(const unsigned int Pos) {
										bool Ret = _Eliminable[Pos];
										if (_Eliminable[Pos] == true) DestroyIcon(_Ikos[Pos]); 
										_Ikos.erase(_Ikos.begin() + Pos);
										_Eliminable.erase(_Eliminable.begin() + Pos);
										return Ret;
									};
									//
									//! Función que retorna el Handle de este imagelist
									//  inline HIMAGELIST hImageList(void);
		 inline HIMAGELIST			hImageList(void) {
										return _ImgList; 
									};
									//
									//! Función que retorna el icono especificado por la posicion
									//  inline HICON Icono(const unsigned int Pos);
		 inline HICON			    Icono(const unsigned int Pos) {
										return _Ikos[Pos];
									};
									//
									//! Función que retorna el icono especificado por la posicion
									//  inline const unsigned int TotalIconos(void);
		 inline const unsigned int	TotalIconos(void) {
										return static_cast<unsigned int>(_Ikos.size());
									};
		protected : ////////////////// Miembros protegidos
									//
									//! ImageList
		 HIMAGELIST                _ImgList;
									//
									//! Vector de Iconos
		 std::vector<HICON>        _Ikos;
									//
									//! Vector igual de grande que los iconos que especifica si se puede eliminar el icono.
		 std::vector<bool>         _Eliminable;
									//
									//! Tamaño del Imagelist (16, 32, etc...)
		 unsigned short            _Tam;
		};			                //
		////////////////////////////// Fin ClaseImageList
	}
}

#endif // DWL_CLASEIMAGELIST_H


// Version 0.95
//  Hay varios cambios en esta version.
//  Para empezar haora se puede borrar un icono de esta clase, cosa que antes no (BorrarIcono).
//  Haora existen 2 formas de añadir iconos :
//   -La primera lo añade partiendo de los recursos de tu aplicacion (AgregarIconoRecursos)
//   -La segunda es pasarle el HICON directamente.
//  Al permitir utilizar HICON directamente en esta clase hay que tener en cuenta una cosa :
//   Si añades un icono de los recursos este se borrara automaticamente de la memoria, pero si añades un HICON deberas borrarlo tu!.
//  Y por ultimo se han añadido tres Funciónes mas :
//   -Destruir, que elimina este ImageList de la memoria junto con todos los iconos que pueda borrar.
//   -Icono, que retorna el icono de la posicion especificada.
//   -TotalIconos, que retorna el total de iconos que contiene este imagelist.