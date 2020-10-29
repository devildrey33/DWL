/*! \file DWL.h
	\brief		Cabecera base de la DReY Windows Lib.

	\details	Esta cabecera contiene todas las definiciones basicas para la DReY Windows Lib.															\n
																																						\n
	\author		devildrey33
	\version	0.96
	\date		05/06/2010

	\remarks
				Archivo creado por devildrey33 el dia [09/12/2009] para http://www.devildrey33.es														\n
				Este archivo es parte de la DWL (DReY Windows Lib) y se distribuye bajo la licencia GPL, para mas información consulta estos enlaces :	\n
				 - http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
				 - http://www.viti.es/gnu/licenses/gpl.html (Castellano, traduccion no oficial)															\n
				 - http://www.softcatala.cat/wiki/GPL3		(Catalá, traduccion no oficial)																\n

*/

#ifndef DeVilDReY33_Windows_Lib
    #define DeVilDReY33_Windows_Lib

	// Definiciones para los compiladores soportados para esta libreria
	//! Compilador VC10 (Visual Studio 2010)
	#define COMPILADOR_VC10	  0
	//! Compilador VC9  (Visual Studio 2008)
	#define COMPILADOR_VC9	  1
	//! Compilador VC8  (Visual Studio 2005)
	#define COMPILADOR_VC8	  2
	//! Compilador VC7  (Visual Studio 2003)
	#define COMPILADOR_VC7	  3
	//! Compilador Visual C++ 6 (1997)
	#define COMPILADOR_VC6	  4
	//! Compilador MINGW
	#define COMPILADOR_MINGW  5

	// Miramos el compilador que se usa
	#if defined __MINGW32__
		#define COMPILADOR COMPILADOR_MINGW	// MINGW
        #include "./Compiladores/DWL_Compilador_MINGW.h"
//		#pragma message("Compilador MINGW32...\n")
	#elif defined _MSC_VER
		#if _MSC_VER == 1200
			#define COMPILADOR COMPILADOR_VC6	// Version 6 de VC
            #include "./Compiladores/DWL_Compilador_MSC1200.h"
		#elif _MSC_VER == 1300
			#define COMPILADOR COMPILADOR_VC7	// Version 7 de VC
            #include "./Compiladores/DWL_Compilador_MSC1300.h"
//			#pragma message("Compilador desconocido!!, aplicando configuración para VC6...\n")
		#elif _MSC_VER == 1400
			#define COMPILADOR COMPILADOR_VC8git	// Version 8 de VC
            #include "./Compiladores/DWL_Compilador_MSC1400.h"
		#elif _MSC_VER == 1500
			#define COMPILADOR COMPILADOR_VC9	// Version 9 de VC
            #include "./Compiladores/DWL_Compilador_MSC1500.h"
		#elif _MSC_VER >= 1600
			#define COMPILADOR COMPILADOR_VC10	// Version 10 de VC
            #include "./Compiladores/DWL_Compilador_MSC1600.h"
		#endif
	#else
		#pragma message("Compilador desconocido!!, aplicando configuración para VC6...\n")
		#define COMPILADOR COMPILADOR_VC6	// Version 6 de VC
        #include "./Compiladores/DWL_Compilador_MSC1200.h"
	#endif


	// Definiciones para pintar degradados
    #define DWLGRADIENT_FILL_RECT_H    0x00000000
    #define DWLGRADIENT_FILL_RECT_V    0x00000001


	#define DWLSRand()	 srand(GetTickCount())
	#define DWLRand(Max) rand()%Max

	#if defined _DEBUG
		#include "DWLDebug.h"
 		#define SOLO_DEBUG(sd) sd
	#else
 		#define SOLO_DEBUG(sd)
	#endif

	#define DWL_TECLA_PRESIONADA 0x8000 

	// Mensajes de ventanas / controles extendidos.
	// ComboBox ////////////////////////////////////////////////////////////
	#define DWL_COMBOBOX_CLICK_IZQUIERDO					WM_USER + 1
	#define DWL_COMBOBOX_CLICK_DERECHO						WM_USER + 2
	#define DWL_COMBOBOX_CLICK_MEDIO						WM_USER + 3
	#define DWL_COMBOBOX_DOBLECLICK_IZQUIERDO				WM_USER + 4
	#define DWL_COMBOBOX_DOBLECLICK_DERECHO					WM_USER + 5
	#define DWL_COMBOBOX_DOBLECLICK_MEDIO					WM_USER + 6
	#define DWL_COMBOBOX_TECLADO_PRESIONADO					WM_USER + 7
	#define DWL_COMBOBOX_TECLADO_SOLTADO					WM_USER + 8
	#define DWL_COMBOBOX_TECLADO_INTRO						WM_USER + 9
	#define DWL_COMBOBOX_FOCO_OBTENIDO						WM_USER + 10
	#define DWL_COMBOBOX_FOCO_PERDIDO						WM_USER + 11
	// EditBox /////////////////////////////////////////////////////////////
	#define DWL_EDITBOX_CLICK_IZQUIERDO						WM_USER + 12
	#define DWL_EDITBOX_CLICK_DERECHO						WM_USER + 13
	#define DWL_EDITBOX_CLICK_MEDIO							WM_USER + 14
	#define DWL_EDITBOX_DOBLECLICK_IZQUIERDO				WM_USER + 15
	#define DWL_EDITBOX_DOBLECLICK_DERECHO					WM_USER + 16
	#define DWL_EDITBOX_DOBLECLICK_MEDIO					WM_USER + 17
	#define DWL_EDITBOX_TECLADO_PRESIONADO					WM_USER + 18
	#define DWL_EDITBOX_TECLADO_SOLTADO						WM_USER + 19
	#define DWL_EDITBOX_TECLADO_INTRO						WM_USER + 20
	#define DWL_EDITBOX_FOCO_OBTENIDO						WM_USER + 21
	#define DWL_EDITBOX_FOCO_PERDIDO						WM_USER + 22
	// ListBox /////////////////////////////////////////////////////////////
	#define DWL_LISTBOX_CLICK_IZQUIERDO						WM_USER + 23
	#define DWL_LISTBOX_CLICK_DERECHO						WM_USER + 24
	#define DWL_LISTBOX_CLICK_MEDIO							WM_USER + 25
	#define DWL_LISTBOX_DOBLECLICK_IZQUIERDO				WM_USER + 26
	#define DWL_LISTBOX_DOBLECLICK_DERECHO					WM_USER + 27
	#define DWL_LISTBOX_DOBLECLICK_MEDIO					WM_USER + 28
	#define DWL_LISTBOX_TECLADO_PRESIONADO					WM_USER + 29
	#define DWL_LISTBOX_TECLADO_SOLTADO						WM_USER + 30
	#define DWL_LISTBOX_TECLADO_INTRO						WM_USER + 31
	#define DWL_LISTBOX_FOCO_OBTENIDO						WM_USER + 32
	#define DWL_LISTBOX_FOCO_PERDIDO						WM_USER + 33
	// ListView ////////////////////////////////////////////////////////////
	#define DWL_LISTVIEW_CLICK_IZQUIERDO					WM_USER + 34
	#define DWL_LISTVIEW_CLICK_DERECHO						WM_USER + 35
	#define DWL_LISTVIEW_CLICK_MEDIO						WM_USER + 36
	#define DWL_LISTVIEW_DOBLECLICK_IZQUIERDO				WM_USER + 37
	#define DWL_LISTVIEW_DOBLECLICK_DERECHO					WM_USER + 38
	#define DWL_LISTVIEW_DOBLECLICK_MEDIO					WM_USER + 39
	#define DWL_LISTVIEW_TECLADO_PRESIONADO					WM_USER + 40
	#define DWL_LISTVIEW_TECLADO_SOLTADO					WM_USER + 41
	#define DWL_LISTVIEW_TECLADO_INTRO						WM_USER + 42
	#define DWL_LISTVIEW_LABELEDIT_INICIO					WM_USER + 43
	#define DWL_LISTVIEW_LABELEDIT_FIN						WM_USER + 44
	#define DWL_LISTVIEW_LABELEDIT_CANCELADO				WM_USER + 45
	#define DWL_LISTVIEW_FOCO_OBTENIDO						WM_USER + 46
	#define DWL_LISTVIEW_FOCO_PERDIDO						WM_USER + 47
	// StaticText //////////////////////////////////////////////////////////
	#define DWL_STATICTEXT_CLICK_IZQUIERDO					WM_USER + 48
	#define DWL_STATICTEXT_CLICK_DERECHO					WM_USER + 49
	#define DWL_STATICTEXT_CLICK_MEDIO						WM_USER + 50
	#define DWL_STATICTEXT_DOBLECLICK_IZQUIERDO				WM_USER + 51
	#define DWL_STATICTEXT_DOBLECLICK_DERECHO				WM_USER + 52
	#define DWL_STATICTEXT_DOBLECLICK_MEDIO					WM_USER + 53
	// TreeView ////////////////////////////////////////////////////////////
	#define DWL_TREEVIEW_CLICK_IZQUIERDO					WM_USER + 54
	#define DWL_TREEVIEW_CLICK_DERECHO						WM_USER + 55
	#define DWL_TREEVIEW_CLICK_MEDIO						WM_USER + 56
	#define DWL_TREEVIEW_DOBLECLICK_IZQUIERDO				WM_USER + 57
	#define DWL_TREEVIEW_DOBLECLICK_DERECHO					WM_USER + 58
	#define DWL_TREEVIEW_DOBLECLICK_MEDIO					WM_USER + 59
	#define DWL_TREEVIEW_TECLADO_PRESIONADO					WM_USER + 60
	#define DWL_TREEVIEW_TECLADO_SOLTADO					WM_USER + 61
	#define DWL_TREEVIEW_TECLADO_INTRO						WM_USER + 62
	#define DWL_TREEVIEW_LABELEDIT_INICIO					WM_USER + 63
	#define DWL_TREEVIEW_LABELEDIT_FIN						WM_USER + 64
	#define DWL_TREEVIEW_LABELEDIT_CANCELADO				WM_USER + 65
	#define DWL_TREEVIEW_FOCO_OBTENIDO						WM_USER + 66
	#define DWL_TREEVIEW_FOCO_PERDIDO						WM_USER + 67
	// ArbolEx /////////////////////////////////////////////////////////////
	#define DWL_ARBOLEX_CLICK								WM_USER + 68  //! Mensaje para un click
	#define DWL_ARBOLEX_DOBLECLICK							WM_USER + 69  //! Mensaje para un doble click
	#define DWL_ARBOLEX_TECLADO_PRESIONADO					WM_USER + 70  //! Mensaje para el teclado presionado
	#define DWL_ARBOLEX_TECLADO_SOLTADO						WM_USER + 71  //! Mensaje para el teclado soltado
	#define DWL_ARBOLEX_TECLADO_INTRO						WM_USER + 72  //! Mensaje para el intro del teclado
	#define DWL_ARBOLEX_LABELEDIT_INICIO					WM_USER + 73  //! Mensaje para empezar un label edit
	#define DWL_ARBOLEX_LABELEDIT_FIN						WM_USER + 74  //! Mensaje para terminar un label edit
	#define DWL_ARBOLEX_LABELEDIT_CANCELADO					WM_USER + 75  //! Mensaje para cancelar un label edit
	#define DWL_ARBOLEX_FOCO_OBTENIDO						WM_USER + 76  //! Mensaje para cuando se obtiene el foco
	#define DWL_ARBOLEX_FOCO_PERDIDO						WM_USER + 77  //! Mensaje para cuando se pierde el foco
	// BarraEx /////////////////////////////////////////////////////////////
	#define DWL_BARRAEX_NUEVO_VALOR							WM_USER + 78
	#define DWL_BARRAEX_MOUSE_BOTONSOLTADO					WM_USER + 79
	// BarraScrollEx ///////////////////////////////////////////////////////
	#define DWL_BARRASCROLLEX_BOTONEX_CLICK					WM_USER + 80  //! Mensaje para los botones extendidos
	// BotonEx /////////////////////////////////////////////////////////////
	#define DWL_BOTONEX_MOUSE_BOTONPRESIONADO				WM_USER + 81
	#define DWL_BOTONEX_MOUSE_BOTONSOLTADO					WM_USER + 82
	#define DWL_BOTONEX_CLICK								WM_USER + 83
	#define DWL_BOTONEX_MOUSE_MOVIMIENTO					WM_USER + 84
	#define DWL_BOTONEX_TECLADO_PRESIONADO					WM_USER + 85
	#define DWL_BOTONEX_TECLADO_SOLTADO						WM_USER + 86
	#define DWL_BOTONEX_FOCO_OBTENIDO						WM_USER + 87
	#define DWL_BOTONEX_FOCO_PERDIDO						WM_USER + 88
	// DWLListaEx //////////////////////////////////////////////////////////
	#define DWL_LISTAEX_CLICK								WM_USER + 89  //! Mensaje para un click
	#define DWL_LISTAEX_DOBLECLICK							WM_USER + 90  //! Mensaje para el dobleclick
	#define DWL_LISTAEX_TECLADO_PRESIONADO					WM_USER + 91  //! Mensaje para el teclado presionado
	#define DWL_LISTAEX_TECLADO_SOLTADO						WM_USER + 92  //! Mensaje para el teclado soltado
	#define DWL_LISTAEX_TECLADO_INTRO						WM_USER + 93  //! Mensaje para el intro del teclado
	#define DWL_LISTAEX_LABELEDIT_INICIO					WM_USER + 94  //! Mensaje para empezar un label edit
	#define DWL_LISTAEX_LABELEDIT_FIN						WM_USER + 95  //! Mensaje para terminar un label edit
	#define DWL_LISTAEX_LABELEDIT_CANCELADO					WM_USER + 96  //! Mensaje para cancelar un label edit
	#define DWL_LISTAEX_FOCO_OBTENIDO						WM_USER + 97  //! Mensaje para cuando se obtiene el foco
	#define DWL_LISTAEX_FOCO_PERDIDO						WM_USER + 98  //! Mensaje para cuando se pierde el foco
	// DWLMarcaEx //////////////////////////////////////////////////////////
	//! Mensaje para un click izquierdo
	#define DWL_MARCAEX_CLICK_IZQUIERDO						WM_USER + 99
	//! Mensaje para un click derecho	
	#define DWL_MARCAEX_CLICK_DERECHO						WM_USER + 100
	//! Mensaje para un click medio
	#define DWL_MARCAEX_CLICK_MEDIO							WM_USER + 101
	// DWLMenuEx ///////////////////////////////////////////////////////////
	#define DWL_MENUEX_MENU_PULSADO							WM_USER + 102
	#define DWL_MENUEX_MENU_MOSTRADO						WM_USER + 103 
	#define DWL_MENUEX_MENU_OCULTADO						WM_USER + 104 
	#define DWL_MENUEX_ESMENU								WM_USER + 105
	// DWLEdicionDesplegableEx /////////////////////////////////////////////
	#define DWL_EDICIONDESPLEGABLEEX_CAMBIO_SELECCION_LISTA	WM_USER + 106
	#define DWL_EDICIONDESPLEGABLEEX_CAMBIO_SELECCION_ARBOL	WM_USER + 107
	#define DWL_EDICIONDESPLEGABLEEX_CAMBIO_SELECCION		WM_USER + 108
	#define DWL_EDICIONDESPLEGABLEEX_LISTA_OCULTADA         WM_USER + 109
	// DWLToolTipEx ////////////////////////////////////////////////////////
	#define DWL_TOOLTIPEX_MOSTRAR							WM_USER + 110
	#define DWL_TOOLTIPEX_OCULTAR							WM_USER + 111
	// DWLBaseWnd //////////////////////////////////////////////////////////
	#define DWL_CUSTOM_DRAW									WM_USER + 112 //! Mensaje para responder a notificaciones de colores (solo para controles estandar de windows)
	#define DWL_TAB_CAMBIO_FOCO								WM_USER + 113 //! Mensaje para cuando se cambia el foco de la tabulacion
	#define DWL_TAB_AGREGAR_CONTROL							WM_USER + 114 //! Mensaje para agregar un control a la lista de tabulaciones
	#define DWL_TAB_SIGUIENTE								WM_USER + 115 //! Mensaje para saltar al siguiente control
	#define DWL_TAB_ANTERIOR								WM_USER + 116 //! Mensaje para saltar al control anterior
	#define DWL_TAB_CAMBIAR_POSICION						WM_USER + 117 //! Mensaje para cambiar la posicion del control dentro de la lista de tabulaciones
	#define DWL_TAB_OBTENER_POSICION						WM_USER + 118 //! Mensaje para obtener la posicion del control dentro de la lista de tabulaciones
	#define DWL_TAB_BORRAR_CONTROL							WM_USER + 119 //! Mensaje para borrar un control de la lista de tabulaciones
	#define DWL_USAR_GESTOR_POR_DEFECTO						WM_USER + 120 //! Macro para definir el valor que debera devolver el GestorMensajes si queremos llamar a la función por defecto del windowprocedure.
	// DWLEdicionEx ////////////////////////////////////////////////////////
	#define DWL_EDICIONEX_TEMPORIZADOR_CURSOR				WM_USER + 121 //! ID del temporizador para el cursor del EdicionEx

#endif

// Pagina principal de la documentación (DOXYGEN) 
/*! \mainpage					DReY Windows Lib
	\section intro_sec			Introducción :
								 - DReY Windows Lib es una libreria que nacio por la necesidad de crear ventanas y controles competentes fuera del look estandard de windows. La idea era tener un conjunto de clases que facilitaran la programación con el API de windows, un concepto similar al MFC pero con un toque personal.	\n
								 - La primera version de la libreria fue creada en el 2002 por Jose Antonio Bover Comas (devildrey33), y desde entonces que ha ido creciendo y adaptandose a los nuevos tiempos.				\n
								 - Actualmente esta libreria tiene soporte para los controles estandar de windows como son EdtiBox, ListBox, ComboBox, StaticText, Menu, etc... ademas de algunos common controls como el TreeView, el ListView y el ImageList. \n
								 - Aparte de dar soporte a los controles de windows, esta libreria dispone de sus propios controles extendidos. Estos controles tienen practicamente las mismas funciones que los controles originales de windows, pero ademas tienen la ventaja de ser muy configurables en su aspecto grafico. \n
								 - Esta libreria se desarrolla en paralelo con el reproductor de audio / video BubaTronik, este reproductor es la plataforma de pruebas donde se desarrolla la mayoria de funciones de la DWL, y por ello es la aplicacion con la que podemos ver todo el potencial de esta libreria. Puedes descargar el codigo de BubaTronik en http://bubatronik.devildrey33.es \n\n
								 - La <b>DReY Windows Lib se distribuye bajo la licencia GPL</b>, para mas información consulta estos enlaces : \n
									 http://www.gnu.org/licenses/gpl.html     (Ingles, documento oficial)																	\n
									 http://www.viti.es/gnu/licenses/gpl.html (Castellano, traducción no oficial)															\n
									 http://www.softcatala.cat/wiki/GPL3	  (Catalá, traducción no oficial)																\n

	\n\n
    \htmlonly
     <?php Generar_TablaDescargar_Inicio("Descarga la última versión de la DWL!.", "DWL.zip", "DReY Windows Lib", "http://www.devildrey33.es/Graficos/WinRar.gif"); ?>
      <p>Contenido del directorio DWL :<br />
		<table width="100%" border="0" cellpadding="0" cellspacing="0">
		<tr><td width="250px">
			<b> "\Ejemplos\ArbolEx\" </b><br>
			<b> "\Ejemplos\BarraEx\" </b><br>
			<b> "\Ejemplos\BotonEx\" </b><br>
			<b> "\Ejemplos\Contenedor Pruebas\" </b><br>
			<b> "\Ejemplos\EdicionEx\" </b><br>
			<b> "\Ejemplos\LimpiadorProyectos\" </b><br>
			<b> "\Ejemplos\ListaEx\" </b><br>
			<b> "\Ejemplos\MarcaEx\" </b><br>
			<b> "\Ejemplos\MenuEx\" </b><br>
			<b> "\Include\" </b><br>
			<b> "\Release\" </b><br>
			<b> "\Iconos\" </b><br>
			<b> "\DWL.dev" </b><br>
			<b> "\DWL.dsw" </b><br>
			<b> "\DWL.dsp" </b><br>
			<b> "\DWL.sln" </b><br>
			<b> "\DWL.vcproj" </b><br>
			<b> "\DWL Ejemplos.sln" </b><br>
			<b> "\DWL Ejemplos.dsw" </b><br>
		</td>
		<td>
			Carpeta con un ejemplo de la clase DWL::ControlesEx::DWLArbolEx<br>
			Carpeta con un ejemplo de la clase DWL::ControlesEx::DWLBarraEx<br>
			Carpeta con un ejemplo de la clase DWL::ControlesEx::DWLBotonEx<br>
			Carpeta que contiene la aplicación Contenedor Pruebas<br>
			Carpeta con un ejemplo de la clase DWL::ControlesEx::DWLEdicionEx<br>
			Carpeta con un ejemplo de la clase DWL::Archivos::DWLBusquedaRecursiva<br>
			Carpeta con un ejemplo de la clase DWL::ControlesEx::DWLListaEx<br>
			Carpeta con un ejemplo de la clase DWL::ControlesEx::DWLMarcaEx<br>
			Carpeta con un ejemplo de la clase DWL::ControlesEx::DWLMenuEx<br>
			Carpeta con todo el codigo de la DWL<br>
			Carpeta donde se guardaran los objetos y los ejecutables<br>
			Algunos iconos para los ejemplos<br>
			Proyecto DWL para DevCpp 4.9.9.2<br>
			Espacio de trabajo DWL para VisualC++ 6<br>
			Proyecto DWL para VisualC++ 6<br>
			Solucion DWL para VisualC++ 9<br>
			Proyecto DWL para VisualC++ 9<br>
			Solucion que contiene todos los ejemplos para VisualC++ 9<br>
			Espacio de trabajo contiene todos los ejemplos para VisualC++ 6<br>
		</td></tr>
		</table>
	  </p>
      <?php Generar_TablaDescargar_Fin(); ?>
    \endhtmlonly

	\n\n
	\section install_sec		Instalación :
								- <b> Microsoft Visual Studio 2008 </b> (VC9) :  																																																																													\n
								 <b>1</b> : Descomprimir la libreria en un directorio adecuado, por ejemplo "c:\Programacion\DWL\".																																																																	\n
								 <b>2</b> : Añadir el directorio "c:\Programacion\DWL\Include\" en el menu <tt>Herramientas</tt> -> <tt>Opciones</tt> -> <tt>Proyectos y Soluciones</tt> -> <tt>Directorios de VC++</tt> -> <tt>Archivos de Inclusión</tt>.																																			\n
								<table border = 0><tr><td> \image html InstalarVC9.jpg </td></tr></table>

								- <b> Microsoft Visual C++ 6  </b> : 																																																																																\n
								 <b>1</b> : Descomprimir la libreria en un directorio adecuado, por ejemplo "c:\Programacion\DWL\".																																																																	\n
								 <b>2</b> : Añadir el directorio "c:\Programacion\DWL\Include\" en el menu <tt>Herramientas</tt> -> <tt>Opciones</tt> -> <tt>Directorios</tt> -> <tt>Archivos de Inclusión</tt>.																																													\n
								 <b> NOTA : </b> La version para VC6 de esta libreria tiene algunas limitaciones, en especial aquellas funciones de windows que son para sistemas operativos superiores a Win98. Para todas las tareas que se requieran un sistema operativo superior no se puede asegurar que funcione en este compilador. \n
								<table border = 0><tr><td> \image html InstalarVC6.jpg </td></tr></table>


								- <b> Bloodshed Dev-C++ 4.9.9.2 </b> : 																																																																																\n
								 <b>1</b> : Descomprimir la libreria en un directorio adecuado, por ejemplo "c:\Programacion\DWL\".																																																																	\n
								 <b>2</b> : Añadir el directorio "c:\Programacion\DWL\Include\" en el menu <tt>Herramientas</tt> -> <tt>Opciones del compilador</tt> -> <tt>Directorios</tt> -> <tt>Includes C++</tt>.																																												\n
								 <b> NOTA : </b> Para compilar este codigo necesitareis aseguraros en cada proyecto de que teneis bien especificados los paths para las siguientes librerias : <tt>libcommctl32.a</tt>, <tt>libole32.a</tt>, <tt>libmpr.a</tt>, <tt>libshell32.a</tt>, y <tt>libmsimg32.a</tt>. Estas librerias las encontraras dentro del directorio <tt>"\Lib\"</tt> del DevCpp.	\n
								<table border = 0><tr><td> \image html InstalarDevCpp.jpg </td></tr></table>

	\n\n
	\section index_sec			Indice de controles extendidos :
    \htmlonly                   <table border="0" cellspacing="0" cellpadding="2" class='TablaSoportado'>
                                <tr><td class="TablaSoportadoTituloR" width="140" border="1px">
    \endhtmlonly                DWLArbolEx.h
    \htmlonly                   </td><td class="TablaSoportadoTitulo" border="1px">Control que simula un treeview de windows.</td></tr>
                                <tr><td class="TablaSoportadoTituloR" width="140" border="1px">
    \endhtmlonly                DWLBarraEx.h
    \htmlonly                   </td><td class="TablaSoportadoTitulo" border="1px">Control que sirve tanto para una barra de progreso, como para una barra de desplazamiento.</td></tr>
                                <tr><td class="TablaSoportadoTituloR" width="140" border="1px">
    \endhtmlonly                DWLBarraScrollEx.h
    \htmlonly                   </td><td class="TablaSoportadoTitulo" border="1px">Parte basica para controles que requieran scrollbars de la DWL.</td></tr>
                                <tr><td class="TablaSoportadoTituloR" width="140" border="1px">
    \endhtmlonly                DWLBotonEx.h
    \htmlonly                   </td><td class="TablaSoportadoTitulo" border="1px">Control que sirve como boton estandar.</td></tr>
                                <tr><td class="TablaSoportadoTituloR" width="140" border="1px">
    \endhtmlonly                DWLEdicionEx.h
    \htmlonly                   </td><td class="TablaSoportadoTitulo" border="1px">Control que simula un editbox de windows.</td></tr>
                                <tr><td class="TablaSoportadoTituloR" width="140" border="1px">
    \endhtmlonly                DWLEdicionDesplegableEx.h
    \htmlonly                   </td><td class="TablaSoportadoTitulo" border="1px">Control que simula una combobox de windows.</td></tr>
                                <tr><td class="TablaSoportadoTituloR" width="140" border="1px">
    \endhtmlonly                DWLExplorarDirectorios.h
    \htmlonly                   </td><td class="TablaSoportadoTitulo" border="1px">Control a partir de un ArbolEx nos ofrece la lista de directorios de la maquina.</td></tr>
                                <tr><td class="TablaSoportadoTituloR" width="140" border="1px">
    \endhtmlonly                DWLListaEx.h
    \htmlonly                   </td><td class="TablaSoportadoTitulo" border="1px">Control que simula un listview de windows.</td></tr>
                                <tr><td class="TablaSoportadoTituloR" width="140" border="1px">
    \endhtmlonly                DWLMarcaEx.h
    \htmlonly                   </td><td class="TablaSoportadoTitulo" border="1px">Control que se usa para mostrar opciones booleanas (true / false).</td></tr>
                                <tr><td class="TablaSoportadoTituloR" width="140" border="1px">
    \endhtmlonly                DWLMenuEx.h
    \htmlonly                   </td><td class="TablaSoportadoTitulo" border="1px">Control que simula un popupmenu de windows.</td></tr>
                                <tr><td class="TablaSoportadoTituloB" width="140" border="1px">
    \endhtmlonly                DWLToolTipEx.h
    \htmlonly                   </td><td class="">Control que simula tooltip en el cual podemos añadir varias lineas facilmente.</td></tr>
                                </table>
    \endhtmlonly

	\n\n
	\section use_sec			Empezando a usar la libreria :
									- <b> Crear nuestra clase aplicación </b> :																																																																														\n
									  Lo primero que debemos hacer es crear nuestra clase aplicación, para ello heredaremos de la clase DWLAplicacion. Existen 3 funciones virtuales que puedes re-emplazar segun tus necesidades : DWL::DWLAplicacion::Inicio(), DWL::DWLAplicacion::Fin(), y  DWL::DWLAplicacion::BucleMensajes().																\n
									  Las dos primeras se usan para iniciar / destruir nuestra aplicacion, por ello nunca debemos usar el constructor y el destructor de esta clase. Solo remarcar que si retornamos FALSE en la funcion Inicio, saltaremos el bucle de mensajes y la funcion Fin, de forma que saldremos de la aplicación.															\n
									  La función BucleMensajes es un bucle estandar que usa las apis GetMessage, TranslateMessage, y DispatchMessage para procesar los mensajes las ventanas de esta aplicacion.<br><br>
    \htmlonly
        <?php PintarCodigoC("../EjemplosDWLDoxygen.cpp", "MiAplicacion"); ?><br>
    \endhtmlonly
									- <b> Iniciar la libreria desde el WinMain </b> :																										\n
									  Llegados a este punto solo nos queda enlazar el inicio de la libreria con el WinMain, para ello se usara la funcion plantilla DWL::DWL_Iniciar. En ella especificaremos nuestra plantilla aplicacion, en este caso MiAplicacion.<br><br>
    \htmlonly
        <?php PintarCodigoC("../EjemplosDWLDoxygen.cpp", "WinMain"); ?><br>
    \endhtmlonly
                                    - <b> NOTA </b> : \n
									  Remarcar que si no iniciamos la libreria con la función plantilla DWL::DWL_Iniciar muchos controles no se iniciaran correctamente, y algunas apis especificas del sistema operativo podrían no funcionar bien.


*/


