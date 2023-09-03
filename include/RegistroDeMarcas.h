/****************************************************************************/
//PROYECTO
//
//AUTOR:ALONSO DOÑA MARTINEZ
//DECLARACIONES DE LA CLASE RegistroDeMarcas.cpp
//
//............................................................................
#ifndef CLASES_REGISTRO
#define CLASES_REGISTRO

/////////////////////////////////////////////////////////////////////////////

#include <string>
#include "Tiempo.h"
#include "Fecha.h"
#include "Licencia.h"

using namespace std;

class RegistroDeMarca {

private: 
	Fecha fecha_marca;		// Fecha de la marca 
	Licencia licencia;		// Licencia del atleta
	Tiempo tiempo_marca;	// Tiempo registrado

public : 

	/***********************************************************************/
	// Constructor sin argumentos. 
	// Necesario para crear arrays o matrices.

	RegistroDeMarca (void); 

	/***********************************************************************/
	// Constructor directo. 
	// Parámetros: trivial. 

	RegistroDeMarca (Fecha la_fecha_marca, Licencia la_licencia, 
		             Tiempo el_tiempo_marca);


	/***********************************************************************/
	// Métodos Get

	Fecha  GetFecha    (void) const;
	Licencia GetLicencia (void) const;
	Tiempo GetTiempo   (void) const;
	
	/***********************************************************************/
	// Comparaciones
	//Comparan dos objetos RegistroDeMarca, devuelven un bool

	bool EsMayor(const RegistroDeMarca & otro,int contador) ;
	
	bool EsMenor(const RegistroDeMarca & otro,int contador);
	
	bool EsIgual(const RegistroDeMarca & otro,int contador) ;
		
	bool NoEsIgual(const RegistroDeMarca & otro,int contador);
	
	/***********************************************************************/
	
	// Sobrecarga de los operadores >> y << 

	// Lee los datos de un objeto "RegistroDeMarca" desde un flujo de texto.
    friend istream & operator >> (istream & in, RegistroDeMarca & r); 
    
     // Inserta en un flujo de texto de salida el contenido de un
	// dato "RegistroDeMarca".
    friend ostream & operator << (ostream & out, const RegistroDeMarca & r);  

	
	/***********************************************************************/
	// Serializa un dato RegistroDeMarca.

	string  ToString (void) const;

	/***********************************************************************/
 
};

/////////////////////////////////////////////////////////////////////////////

#endif
