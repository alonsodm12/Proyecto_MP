/***************************************************************************/
//PROYECTO
//
//CLASE->FECHA
//
//AUTOR:ALONSO DOÑA MARTINEZ
//
//Archivo -> Contiene las declaraciones de la clase Fecha.cpp
//...........................................................................

#include <iostream>
#include <iomanip>
#include <string>
#include "Fecha.h"
#include <time.h>
#include "Utils.h"
#include <ctime>

using namespace std;


/***************************************************************************/
// Constructor sin argumentos. 
// Necesario para crear arrays o matrices u objetos RegistroDemarca.

Fecha :: Fecha (void){ 
	
	tm my_time;
	
	dia= my_time.tm_mday;
	
	mes= my_time.tm_mon;

	anio = my_time.tm_year;
}

/***************************************************************************/
// Constructor directo. 
// Parámetros: trivial. 
// PRE: 1 <= el_dia <= 31 
// PRE: 1 <= el_mes <= 12
// PRE: 1900 <= el_anio	

Fecha :: Fecha (int el_dia, int el_mes, int el_anio)
		        : dia (el_dia), mes (el_mes), anio (el_anio)
{ }

/***************************************************************************/
// Constructor desde un string.
// Parámetros: cad, string con la fecha. 
// PRE: cad contiene una fecha CORRECTA en formato dd/mm/aaaa 
// PRE: cad.length() == 10	

Fecha :: Fecha (string cad)
{
	dia  = stoi(cad.substr(0,2));	 
	mes  = stoi(cad.substr(3,2));	  	
	anio = stoi(cad.substr(6,4));	 
}

/****************************************************************************/
//Metodos de comparacion entre dos fechas
//.........................................................................../

//Operador >
bool Fecha :: operator > (const Fecha & otro) 
{
	bool condicion=true;
		if(otro.GetAnio() == anio){
		
			if(otro.GetMes() == mes){
			
					if(otro.GetDia() < dia)
						condicion = true;
					
					else
						condicion = false;
								
			}
			else if(otro.GetMes() < mes)
				condicion = true;
		
			else
				condicion = false;
			
		}
	
		else if(otro.GetAnio() < anio)
			condicion = true;
		else
			condicion = false;

return condicion;


}

/****************************************************************************/
//Operador <
bool Fecha :: operator < (const Fecha & otro) 
{

	return(!((*this) > otro) && !((*this) == otro));

}

/****************************************************************************/
//Operador ==
bool Fecha :: operator == (const Fecha & otro) 
{

		bool condicion=true;

		if(otro.GetAnio() == anio){
		
			if(otro.GetMes() == mes){
			
					if(otro.GetDia() == dia)
						condicion = true;
					
					else
						condicion = false;
								
			}
			else
			condicion = false;
			
		}else
			condicion = false;

return condicion;


}

/****************************************************************************/
//Operador !=
bool Fecha :: operator != (const Fecha & otro) 
{
return (!((*this) == otro));

}

/****************************************************************************/
// Operador <=
bool Fecha :: operator <= (const Fecha & otro)
{
return (!((*this) > otro));
}

/****************************************************************************/
// Operador >=
bool Fecha :: operator >= (const Fecha & otro)
{
return (((*this) > otro) || ((*this) == otro));
}

/**************************************************************************/
/**************************************************************************/

/**************************************************************************/
// Métodos Get

int Fecha :: GetDia (void) const
{
	return dia; 
}

int Fecha :: GetMes (void) const
{
	return mes; 
}

int Fecha :: GetAnio (void) const
{
	return anio; 
}

/***************************************************************************/
// Serializa un dato Fecha.

string Fecha :: ToString (void) const
{
	const string MESES[] = {"Enero     ", "Febrero   ", "Marzo     ", 
							"Abril     ", "Mayo      ", "Junio     ", 
							"Julio     ", "Agosto    ", "Septiembre", 
							"Octubre   ", "Noviembre ", "Diciembre "};
	string cad; 
	
	cad = cad + ::ToString(dia,  2, ' ') + " " +  MESES[mes-1] + " " + 
		        ::ToString(anio, 4, ' ');
	
	return cad; 
}

/*****************************************************************************/
//OPERADOR <<
/*****************************************************************************/

// Inserta en un flujo de texto de salida el contenido de un
// dato "Fecha".
// Parámetros: out, el flujo de salida.
// fecha, el dato a insertar.

ostream & operator << (ostream & out, const Fecha & fecha)
{
	out<<setfill('0')<<setw(2)<<fecha.dia<<"/";
	
	out<<setfill('0')<<setw(2)<<fecha.mes<<"/";
	
	out<<fecha.anio<<" ";
	
	return out; 
}


/*****************************************************************************/
//OPERADOR >>
/*****************************************************************************/

// Lee los datos de un objeto "Fecha" desde un flujo de texto.

istream & operator >> (istream & in,  Fecha & fecha)
{

	string cad;
	
	in >> cad;
	
	fecha.dia  = stoi(cad.substr(0,2));	 
	fecha.mes  = stoi(cad.substr(3,2));	  	
	fecha.anio = stoi(cad.substr(6,4));	

	return in; 
}

/***************************************************************************/
/***************************************************************************/



