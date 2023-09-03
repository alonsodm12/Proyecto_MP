/****************************************************************************/
//PROYECTO
//
//AUTOR:ALONSO DOÑA MARTINEZ
//DECLARACIONES DE LA CLASE Licencia.cpp
//
//............................................................................

#ifndef CLASES_LICENCIA
#define CLASES_LICENCIA

#include <string>
using namespace std;

/////////////////////////////////////////////////////////////////////////////

class Licencia {

private: 

	string licencia;
	
public : 

	/***********************************************************************/
	// Constructor sin argumentos. 
	// Necesario para crear arrays o matrices u objetos RegistroDemarca.

	Licencia (void);

	/***********************************************************************/ 
	// Constructor desde un string.
	// Parámetros: cad_licencia, string con la licencia.

	Licencia (string cad_licencia);
	
	/***********************************************************************/
	// Serializa un dato Licencia.

	string ToString (void) const; 
	
	/***********************************************************************/
	//	Devuelve la licencia
	
	string Get_licencia(void) const;

	/***********************************************************************/
	/***********************************************************************/
	/***********************************************************************/
	
	// Sobrecarga de los operadores >> y << 
	
	// Lee los datos de un objeto "Licencia" desde un flujo de texto.
    friend istream & operator >> (istream & in, Licencia & l); 
    
    // Inserta en un flujo de texto de salida el contenido de un
	// dato "Licencia".
    friend ostream & operator << (ostream & out, const Licencia & l);  

	/***********************************************************************/
	
	// Operadores relacionales
	// Compara dos datos "Licencia"
	// Devuelve: un valor bool
	
	bool operator == (const Licencia & otro);
	bool operator != (const Licencia & otro);
	bool operator > (const Licencia & otro);
	
	bool operator < (const Licencia & otro);
	
	bool operator <= (const Licencia & otro);
	bool operator >= (const Licencia & otro);	
	
};

#endif

/////////////////////////////////////////////////////////////////////////////

