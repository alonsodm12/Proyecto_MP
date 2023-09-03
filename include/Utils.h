/***************************************************************************/
//PROYECTO
//
//AUTOR:ALONSO DOÑA MARTINEZ
//
//Archivo -> Declaraciones de Utils.cpp
//...........................................................................


#ifndef Utils 
#define Utils
#include "Tiempo.h"
#include "Fecha.h"
#include "RegistroDeMarcas.h"


using namespace std;

/*****************************************************************************/
/*****************************************************************************/

// Tipo enumerado para representar tipos de redimensionamiento
enum class TipoRedimension {DeUnoEnUno, EnBloques, Duplicando};

// Capacidad inicial
const int TAM_INICIAL = 10;

// Tamanio del bloque para redimensionar (modalidad EnBloques)
const int TAM_BLOQUE = 5;

/***************************************************************************/
// Convierte el dato int "entero" a un string con "num_casillas" casillas 
// que contiene el valor textual de "entero".
// 
// Recibe: 	entero, el valor a transformar.
//			num_casillas, número total de casillas que tendrá el resultado.
//			relleno, el carácter que se emplea para rellenar los huecos. 
// Devuelve: el string compuesto.  
//
// NOTAS: Si el número de casillas solicitado es mayor que el que se necesita, 
//	  	se completa al principio con "relleno" hasta alcanzar un tamaño de 
//	  	"num_casillas". Si el valor tuviera "per se" más de "num_casillas" 
//		se devuelve tal cual.  

string ToString (int entero, int num_casillas, char relleno); 

/***************************************************************************/
// Convierte el dato string "la_cadena" a un string con "num_casillas" 
// casillas rellenando con el caracter "relleno" por la izquierda.
// 
// Recibe: 	la_cadena, el valor a transformar.
//			num_casillas, número total de casillas que tendrá el resultado.
//			relleno, el carácter que se emplea para rellenar los huecos. 
// Devuelve: el string compuesto.  
//
// NOTAS: Si el número de casillas solicitado es mayor que el que se necesita, 
//	  	se completa al principio con "relleno" hasta alcanzar un tamaño de 
//	  	"num_casillas". Si el valor tuviera "per se" más de "num_casillas" 
//		se devuelve tal cual.  

string ToString (string la_cadena, int num_casillas, char relleno=' '); 

/////////////////////////////////////////////////////////////////////////////
/***************************************************************************/
// Comprueba la  existencia y disponibilidad de un fichero

bool ExisteFichero (const string & nombre);

/***************************************************************************/
/***************************************************************************/
// Calcula el tamaño (número de bytes) de un fichero. 

int TamanioFichero (const string & nombre);

/**************************************************************************/

#endif
