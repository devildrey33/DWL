#ifndef DIMAGELIST_H
    #define DIMAGELIST_H

    #include "DObjeto.h"
    #include <vector>
	#include <string>
    #include <commctrl.h>
    #include <shlobj.h>

    namespace DWL {
        // Tipos de imagen
/*        enum DEnum_ImageList_TipoImagen {
            DEnum_ImageList_TipoImagen_Indefinido = 0,
            DEnum_ImageList_TipoImagen_Icono,
            DEnum_ImageList_TipoImagen_IconoCSLID,
            DEnum_ImageList_TipoImagen_IconoRecursos
        };

        // Base para las posibles imagenes
        class DImageList_Imagen { 
          public :
                                                DImageList_Imagen(void) : _Tipo(DEnum_ImageList_TipoImagen_Indefinido) { };
            const DEnum_ImageList_TipoImagen    Tipo(void) { return _Tipo; }
          protected :
            DEnum_ImageList_TipoImagen         _Tipo;
        };

        // Icono externo (el icono no se borra automáticamente)
        class DImageList_ImagenIcono : public DImageList_Imagen { 
          public :
                            DImageList_ImagenIcono(HICON nIcono) : DImageList_Imagen(), _Icono(nIcono) { _Tipo = DEnum_ImageList_TipoImagen_Icono; };
            HICON           Icono(void) { return _Icono; };
          protected :
                            DImageList_ImagenIcono(void) : DImageList_Imagen(), _Icono(NULL) { _Tipo = DEnum_ImageList_TipoImagen_Icono; };
            HICON          _Icono;
        };

        // Icono de los recursos (el icono se crea y se borra automáticamente)
        class DImageList_ImagenIconoRecursos : public DImageList_Imagen { 
          public :
                            DImageList_ImagenIconoRecursos(const int IDRecursos, const int cAncho, const int cAlto);
                           ~DImageList_ImagenIconoRecursos(void);
            HICON           Icono(void) { return _Icono; };
          protected :
                            DImageList_ImagenIconoRecursos(void) : DImageList_Imagen(), _Icono(NULL) { _Tipo = DEnum_ImageList_TipoImagen_IconoRecursos; };
            HICON          _Icono;
        };

        // Icono de los recursos (el icono se crea y se borra automáticamente)
        class DImageList_ImagenIconoCSLID : public DImageList_Imagen { 
          public :
                            DImageList_ImagenIconoCSLID(HICON nIcono);
                           ~DImageList_ImagenIconoCSLID(void);
            HICON           Icono(void) { return _Icono; };
          protected :
                            DImageList_ImagenIconoCSLID(void) : DImageList_Imagen(), _Icono(NULL) { _Tipo = DEnum_ImageList_TipoImagen_IconoCSLID; };
            HICON          _Icono;
        };

        // Lista de imagenes
        class DImageList2 : public DObjeto {
          public:
            DWL_DECLARAR_DOBJETO(TEXT("DImageList"), DEnum_Objeto_ImageList);
                                                DImageList(void) : _ImageList(NULL) { };
                                               ~DImageList(void) { Destruir(); };

            void                                Crear(const int cAncho, const int cAlto);
            void                                Destruir(void);

            void                                AgregarIconoCSLID(const int CSIDL);
            void                                AgregarIconoRecursos(const int cID);

            const size_t                        TotalImagenes(void) { 
                                                    return _ListaImagenes.size(); 
                                                };

            HIMAGELIST                          operator () (void) { 
                                                    return _ImageList;
                                                };
          protected:
            HIMAGELIST                         _ImageList;
            std::vector<DImageList_Imagen *>   _ListaImagenes;
        };*/

        class DImageList_ID {
          public:
							DImageList_ID(const TCHAR *nPath = NULL, const int nPosIco = 0) : PosIco(nPosIco) { 
							    if (nPath != NULL) Path = nPath; 
							};
            std::wstring	Path;
            int				PosIco;
        };

		class DImageList {
          public:
			virtual const DEnum_Objeto			Objeto_Tipo(void) { return DEnum_Objeto_ImageList; };
												DImageList(void) : _ImageList(NULL) { };
                                               ~DImageList(void) { Destruir(); };

            void                                Crear(const int cAncho, const int cAlto);
            void                                Destruir(void);

            const int                           AgregarIconoCSLID(const int CSIDL);
            const int                           AgregarIconoRecursos(const int cID);
                                                // Función que carga el icono correspondiente a la ruta especificada
                                                // Por ejemplo si le pasamos "c:\main.cpp" buscara el icono que se utiliza con los archivos cpp
            const int                           AgregarIconoExplorador(const TCHAR *nPath);

            HIMAGELIST                          operator () (void) { 
                                                    return _ImageList;
                                                };
          protected:
            const int                          _BuscarID(const TCHAR *nPath, const int PosIco);
            HIMAGELIST                         _ImageList;

            std::vector<DImageList_ID>         _ListaImagenes;

        };
    };

#endif