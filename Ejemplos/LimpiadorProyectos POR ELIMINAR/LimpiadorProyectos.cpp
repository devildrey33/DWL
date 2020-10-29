// LimpiadorProyectos.cpp: define el punto de entrada de la aplicación.
//

#include "stdafx.h"
#include "LimpiadorProyectos.h"
#include "..\..\Include\DWLAplicacion.h"
#include "..\..\Include\DWLBusquedaRecursiva.h"
#include "..\..\Include\DWLDebug.h"


class MiBusqueda : public DWL::Archivos::DWLBusquedaRecursiva {
public:
			MiBusqueda(void) { Eliminados = 0; };
		   ~MiBusqueda(void) { };
 void		EncontradoArchivo(const TCHAR *Path, DWORD Atributos) {
				DWL::DWLString	Extension;
				bool			Eliminar = false;
				for (size_t i = DWLStrLen(Path); i != 0; i--) {
					if (Path[i] == TEXT('.')) {
						Extension = &Path[i + 1];
						break;
					}
				}
				// VisualC++
				if (Extension.Comparar(TEXT("ncb")) == true)		Eliminar = true;
				if (Extension.Comparar(TEXT("obj")) == true)		Eliminar = true;
				if (Extension.Comparar(TEXT("res")) == true)		Eliminar = true;
				if (Extension.Comparar(TEXT("pdb")) == true)		Eliminar = true;
				if (Extension.Comparar(TEXT("pch")) == true)		Eliminar = true;
				if (Extension.Comparar(TEXT("idb")) == true)		Eliminar = true;
				if (Extension.Comparar(TEXT("ilk")) == true)		Eliminar = true;
				if (Extension.Comparar(TEXT("lib")) == true)		Eliminar = true;
				if (Extension.Comparar(TEXT("ncb")) == true)		Eliminar = true;
				if (Extension.Comparar(TEXT("manifest")) == true)	Eliminar = true;
				if (Extension.Comparar(TEXT("dep")) == true)		Eliminar = true;
				if (Extension.Comparar(TEXT("sbr")) == true)		Eliminar = true;
				// DevCpp
				if (Extension.Comparar(TEXT("layout")) == true)		Eliminar = true;
				if (Extension.Comparar(TEXT("win")) == true)		Eliminar = true;
				if (Extension.Comparar(TEXT("a")) == true)			Eliminar = true;
				if (Extension.Comparar(TEXT("o")) == true)			Eliminar = true;

				if (Extension.Comparar(TEXT("exe")) == true)		Eliminar = true;
				if (Extension.Comparar(TEXT("dll")) == true)		Eliminar = true;
				
				if (Eliminar == true) {
					if (DeleteFile(Path) != 0)	Eliminados ++;
					else 						DWL::DWLDebug::MostrarUltimoError(Path);
				}
		    };
 int		Eliminados;
};


class LimpiadorProyectosApp : public DWL::DWLAplicacion {
public:
				LimpiadorProyectosApp(void) { };
	           ~LimpiadorProyectosApp(void) { };
	const BOOL  Inicio(void) {
					MiBusqueda Buscar;
					DWL::DWLString PathApp;
					DWL::DWLString TmpStr;
					Directorio(PathApp);
					MessageBox(NULL, PathApp(), TEXT("path"), MB_OK);
					if (MessageBox(NULL, TEXT("Se va a proceder a limpiar todos los objetos y recursos que contiene esta carpeta. Esta operacion tambien eliminara ejecutables y dlls, estas seguro?"), TEXT("ATENCION"), MB_OKCANCEL) == IDCANCEL) return FALSE;
					
					size_t t = Buscar.Buscar(PathApp());
					TmpStr.Parsear(TEXT("Se han eliminado "), Buscar.Eliminados, TEXT(" Archivos en : "), PathApp());
					MessageBox(NULL, TmpStr(), TEXT("Proceso terminado"), MB_OK);
					return FALSE;
				};
};




int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	return DWL::DWL_Iniciar<LimpiadorProyectosApp>();
}
