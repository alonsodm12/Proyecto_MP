/***************************************************************************/
//PROYECTO
//
//AUTOR:ALONSO DOÑA MARTINEZ
//
//Clase -> LICENCIA
//
//Archivo -> Licencia.cpp
//...........................................................................

#include <iostream>
#include <iomanip>
#include <string>
#include "Fecha.h"
#include <time.h>
#include "Utils.h"


using namespace std;

/***************************************************************************/
// Constructor sin argumentos. 
// Necesario para crear arrays o matrices u objetos Licencia.

Licencia :: Licencia (void) 
				 : licencia("0")

{}

/***************************************************************************/
// Constructor directo. 
// Parámetros: 
// string licencia

Licencia :: Licencia (string cad_licencia) 
				 : licencia(cad_licencia)

{}


/*****************************************************************************/
//OPERADOR <<
/*****************************************************************************/
// Inserta en un flujo de texto de salida el contenido de un
// dato "Licencia".
// Parámetros: out, el flujo de salida.
// tiempo, el dato a insertar.

ostream & operator << (ostream & out, const Licencia & l)
{
		
	out<<l.licencia<<" ";
	
	return out; 
}


/*****************************************************************************/
//OPERADOR >>
/*****************************************************************************/
// Lee los datos de un objeto "Licencia" desde un flujo de texto.

istream & operator >> (istream & in,  Licencia & l)
{

	string cad;
	
	in >> cad;
	l.licencia=cad;
	
	return in; 
}


/***************************************************************************/
// Serializa un dato Licencia.

string Licencia :: ToString (void) const
{
	string cad; 
	
	cad = cad + licencia;
	
	return cad; 
}

// Metodo que devuelve el dato licencia

string Licencia :: Get_licencia() const
{

	return (licencia);
}

//OPERADORES RELACIONALES

//Metodos de comparacion entre dos licencias
//.........................................................................../

//Operador >
bool Licencia :: operator > (const Licencia & otro)
{
	bool condicion=true;
		if(otro.Get_licencia() < licencia)
			condicion=true;
		
	
		else if(otro.Get_licencia() > licencia)
			condicion = false;
		

return condicion;
}
/****************************************************************************/
//Operador <

bool Licencia :: operator < (const Licencia & otro)
{

	return (!((*this) > otro) && !((*this) == otro));

}
/****************************************************************************/
//Operador ==
bool Licencia :: operator == (const Licencia & otro) 
{

		bool condicion=true;
		if(otro.Get_licencia() == licencia)
			condicion=true;
		
	
		else if(otro.Get_licencia() != licencia)
			condicion = false;
		

return condicion;
}
/****************************************************************************/
//Operador !=
bool Licencia :: operator != (const Licencia & otro) 
{

	return ((*this)!=otro);

}

/*******************************************************/
// Operador <=
bool Licencia :: operator <= (const Licencia & otro)
{
return (!((*this) > otro));
}

/*******************************************************/
// Operador >=
bool Licencia :: operator >= (const Licencia & otro)
{
return (((*this) > otro) || ((*this) == otro));
}
/*******************************************************/

/****************************************************************************/


