/////////////////////////////////////////////////////////////////////////////////////////////////
// Esta clase han sido creada por [\DReY\] el dia 01/04/2006 y es uno de los ejemplos de       //
// http://www.webpersonal.net/devildrey33 (DReY Visual C++ page)                               //
// Puedes modificar esta clase a tu gusto. Si realizas alguna modificacion que creas que es    //
// mejor para esta clase porfavor mandamela por e-mail para que pueda verla :)                 // 
// E-Mail & MSN Messenger : devildrey33@hotmail.com                                            //
//                                                                                             //
// Version 0.2                                                                                 //
// Ultima modificación : 01/04/2006                                                            //
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef DWL_REGISTRO_H
#define DWL_REGISTRO_H

#define KEY_ALL   KEY_QUERY_VALUE | KEY_SET_VALUE | KEY_CREATE_SUB_KEY | KEY_ENUMERATE_SUB_KEYS | KEY_NOTIFY | KEY_CREATE_LINK | READ_CONTROL 

//#include "DWL.h"
#include "DWLString.h"
#include <shlobj.h>
#include "DWLDebug.h"

namespace DWL { 
	namespace SO {
		class DWLRegistro {
		public : ///////// Miembros publicos
						//
						// Constructor
						// DWLRegistro(void);
						DWLRegistro(void) {
						};
						//
						// Destructor
						// ~DWLRegistro(void);
					   ~DWLRegistro(void) {
						};
						//
						// Función que agrega / modifica un valor tipo string del registro 
						// static LONG AsignarValor_String(HKEY Root, const TCHAR *Key, const TCHAR *Nombre, TCHAR *TextoAGuardar);
		 static LONG	AsignarValor_String(HKEY Root, const TCHAR *Key, const TCHAR *Nombre, const TCHAR *TextoAGuardar) {             //
							HKEY                hParentKey;                                                                       // Clave a guardar
							SECURITY_ATTRIBUTES SA;                                                                               // Atributos de Seguridad
							SA.nLength = sizeof(SA);																		      // Longitud de la estructura
							SA.lpSecurityDescriptor = NULL;																	      // Seguridad Nula
							SA.bInheritHandle = true;																		      //
							
							DWORD Len = sizeof(TCHAR) * DWLStrLen(TextoAGuardar);
							LONG L = RegCreateKeyEx(Root, Key, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL, &SA, &hParentKey, NULL);		  // Creo / Abro la clave
							LONG Ret = RegSetValueEx(hParentKey, Nombre, 0, REG_SZ, reinterpret_cast<const BYTE *>(TextoAGuardar), Len); // Guardo los datos
							SOLO_DEBUG(
								if (Ret != ERROR_SUCCESS) DWL::DWLDebug::MostrarUltimoError(TEXT("DWLRegistro::AsignarValor_String ->"));
									);
							RegCloseKey(hParentKey);																		      // Cierro la clave
                            return Ret;
						};
						//
						// Función que agrega / modifica un valor tipo string del registro 
						// static LONG AsignarValor_String(HKEY Root, const TCHAR *Key, const TCHAR *Nombre, TCHAR *TextoAGuardar);
		 static LONG	AsignarValor_DWORD(HKEY Root, const TCHAR *Key, const TCHAR *Nombre, DWORD DWORDAGuardar) {             //
							HKEY                hParentKey;                                                                       // Clave a guardar
							SECURITY_ATTRIBUTES SA;                                                                               // Atributos de Seguridad
							SA.nLength = sizeof(SA);																		      // Longitud de la estructura
							SA.lpSecurityDescriptor = NULL;																	      // Seguridad Nula
							SA.bInheritHandle = true;																		      //
							
							LONG L = RegCreateKeyEx(Root, Key, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL, &SA, &hParentKey, NULL);		  // Creo / Abro la clave
							LONG Ret = RegSetValueEx(hParentKey, Nombre, 0, REG_DWORD, (BYTE *)&DWORDAGuardar, sizeof(DWORD)); // Guardo los datos
							SOLO_DEBUG(
								if (Ret != ERROR_SUCCESS) DWL::DWLDebug::MostrarUltimoError(TEXT("DWLRegistro::AsignarValor_DWORD ->"));
									);
							RegCloseKey(hParentKey);																		      // Cierro la clave
                            return Ret;
						};
	/*					//
						// Función que agrega / modifica un valor tipo string del registro 
						// static void AsignarValor_String(HKEY Root, const TCHAR *Key, const TCHAR *Nombre, DWLStdString &TextoAGuardar);
		 static void	AsignarValor_String(HKEY Root, const TCHAR *Key, const TCHAR *Nombre, DWLString &TextoAGuardar) {
							HKEY hParentKey;																										// Clave a guardar
							SECURITY_ATTRIBUTES SA;																									// Atributos de Seguridad
							SA.nLength = sizeof(SA);																								// Longitud de la estructura
							SA.lpSecurityDescriptor = NULL;																							// Seguridad Nula
							SA.bInheritHandle = true;																								//
							RegCreateKeyEx(Root, Key, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL, &SA, &hParentKey, NULL);							// Creo / Abro la clave
							RegSetValueEx(hParentKey, Nombre, 0, REG_SZ, (BYTE *)TextoAGuardar(), static_cast<DWORD>(TextoAGuardar.Tam()));	// Guardo los datos
							RegCloseKey(hParentKey);																								// Cierro la clave
						};*/
						//
						// Función para obtener el valor de un string del registro
						// static LONG ObtenerValor_String(HKEY Root, const TCHAR *Key, const TCHAR *Nombre, TCHAR *Resultado, DWORD ResTam);
		 static LONG	ObtenerValor_String(HKEY Root, const TCHAR *Key, const TCHAR *Nombre, TCHAR *Resultado, DWORD ResTam) {
							HKEY hParentKey;				                                            // Clave a abrir
							RegOpenKeyEx(Root, Key, 0, KEY_READ, &hParentKey);                          // Abro la clave
							LONG Ret = RegQueryValueEx(hParentKey, Nombre, 0, NULL, (BYTE *)Resultado , &ResTam);	// Obtengo los datos
							RegCloseKey(hParentKey);                                                    // Cierro la Clave
                            return Ret;
						};
						//
						// Función para obtener el valor de un string del registro
						// static LONG ObtenerValor_String(HKEY Root, const TCHAR *Key, const TCHAR *Nombre, DWLString &Resultado);
		 static LONG	ObtenerValor_String(HKEY Root, const TCHAR *Key, const TCHAR *Nombre, DWLString &Resultado) {
							HKEY			hParentKey;													// Clave a abrir
							TCHAR			Tmp[1024] = TEXT("");									    // String temporal
							DWORD			Tam = 1024;													
							RegOpenKeyEx(Root, Key, 0, KEY_READ, &hParentKey);							// Abro la clave
							LONG Ret = RegQueryValueEx(hParentKey, Nombre, 0, NULL, (BYTE *)Tmp , &Tam);			// Obtengo los datos
							RegCloseKey(hParentKey);													// Cierro la Clave
							Resultado = Tmp;															// Copio el string al resultado
                            return Ret;
						};
						//
						// Función para eliminar un valor del registro de cualquier tipo
						//  static LONG EliminarValor(HKEY Root, const TCHAR *Key, const TCHAR *Nombre);
		 static LONG    EliminarValor(HKEY Root, const TCHAR *Key, const TCHAR *Nombre) {
							HKEY hParentKey;										// Clave a borrar
							RegOpenKeyEx(Root, Key, 0, KEY_ALL, &hParentKey);		// Abro la clave
							LONG Ret = RegDeleteValue(hParentKey, Nombre);			// Borro los datos
							SOLO_DEBUG(
								if (Ret != ERROR_SUCCESS) DWL::DWLDebug::MostrarUltimoError(TEXT("DWLRegistro::EliminarValor ->"));
									);
							RegCloseKey(hParentKey);								// Cierro la clave
                            return Ret;
						};
						//
						// Función para eliminar un valor del registro de cualquier tipo
						//  static LONG EliminarValor(HKEY Root, const TCHAR *Key, const TCHAR *Nombre);
		 static LONG    EliminarClave(HKEY Root, const TCHAR *Key, const TCHAR *Nombre) {
							HKEY hParentKey = NULL;										// Clave a borrar
							RegOpenKeyEx(Root, Key, 0, KEY_ALL, &hParentKey);		// Abro la clave padre
							LONG Ret = RegDeleteKey(hParentKey, Nombre);			// Borro la clave
							SOLO_DEBUG(
								if (Ret != ERROR_SUCCESS) DWL::DWLDebug::MostrarUltimoError(TEXT("DWLRegistro::EliminarClave ->"));
									);
							RegCloseKey(hParentKey);								// Cierro la clave
                            return Ret;
						};
		};
		////////////////// Fin DWLRegistro
	}
}

#endif // DWL_Registro_H
