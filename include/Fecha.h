/****************************************************************************/
//PROYECTO
//
//AUTOR:ALONSO DOÑA MARTINEZ
//DECLARACIONES DE LA CLASE Fecha.cpp
//
//............................................................................

#ifndef CLASES_FECHA
#define CLASES_FECHA

#include <string>
using namespace std;

/////////////////////////////////////////////////////////////////////////////

class Fecha {

private: 

	int dia;	// 1 <= dia <= 31 
	int mes; 	// 1 <= mes <= 12
	int anio; 	// 1900 <= anio	

public : 

	/***********************************************************************/
	// Constructor sin argumentos. 
	// Necesario para crear arrays o matrices u objetos RegistroDemarca.

	Fecha (void);

	/***********************************************************************/
	// Constructor directo. 
	// Parámetros: trivial. 
	// PRE: 1 <= el_dia <= 31 
	// PRE: 1 <= el_mes <= 12
	// PRE: 1900 <= el_anio	

	Fecha (int el_dia, int el_mes, int el_anio);

	/***********************************************************************/
	// Constructor desde un string.
	// Parámetros: cad, string con la fecha. 
	// PRE: cad contiene una fecha CORRECTA en formato dd/mm/aaaa 
	// PRE: cad.length() == 10	

	Fecha (string cad);

	/***********************************************************************/
	// Métodos Get

	//Obtenemos el dia en formato entero
	int GetDia  (void) const;
	
	//Obtenemos el mes en formato entero
	int GetMes  (void) const;
	
	//Obtenemos el año en formato entero
	int GetAnio (void) const;

	/***********************************************************************/
	// Serializa un dato Fecha.

	string ToString (void) const; 

	/***********************************************************************/
	
	// Operadores relacionales
	// Compara dos datos "Fecha"
	// Devuelve: un valor bool

	bool operator == (const Fecha & otro);
	bool operator != (const Fecha & otro);
	bool operator > (const Fecha & otro);
	bool operator <= (const Fecha & otro);
	bool operator < (const Fecha & otro);
	bool operator >= (const Fecha & otro);
	
	/***********************************************************************/
	
	// Sobrecarga de los operadores >> y << 
	
	// Lee los datos de un objeto "Fecha" desde un flujo de texto.
    friend istream & operator >> (istream & in, Fecha & fecha); 
    
    // Inserta en un flujo de texto de salida el contenido de un
	// dato "Fecha".
    friend ostream & operator << (ostream & out, const Fecha & fecha);  

	/***********************************************************************/
	
};

#endif

/////////////////////////////////////////////////////////////////////////////

