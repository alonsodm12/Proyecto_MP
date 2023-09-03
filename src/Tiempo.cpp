//...........................................................................
//
//AUTOR:ALONSO DOÑA MARTINEZ
//PROYECTO
//CLASE TIEMPO
//ARCHIVO->Tiempo.cpp
//...........................................................................

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Tiempo.h"
#include "Utils.h"

using namespace std;


/***************************************************************************/
// Constructor sin argumentos. 
// Necesario para crear arrays o matrices u objetos RegistroDemarca.

Tiempo :: Tiempo (void) 
				 : horas(0),minutos(0),segundos(0),milesimas(0)

{}

/***************************************************************************/
// Constructor directo. 
// Parámetros: trivial. 
// PRE: 0 <= la_hora <= 24 
// PRE: 0 <= los_minutos <= 60
// PRE: 0 <= los_segundos <= 60
// PRE: 0 <= las_milesimas <= 1000

Tiempo :: Tiempo (int la_hora, int los_minutos, 
				  int los_segundos, int las_milesimas) 
		          : horas (la_hora), minutos (los_minutos), 
		            segundos (los_segundos), milesimas (las_milesimas) 
{} 

/***************************************************************************/
// Constructor desde un string.
// Parámetros: cad, string con la fecha. 
// PRE: cad contiene un tiempo CORRECTO en formato hh:mm:ss:mmm 
// PRE: cad.length() == 12	

Tiempo :: Tiempo (string cad)
{
	horas     = stoi(cad.substr(0,2));	 
	minutos   = stoi(cad.substr(3,2));	 
	segundos  = stoi(cad.substr(6,2));	 	
	milesimas = stoi(cad.substr(9,3));	 
}

/***********************************************************************/
// Métodos Get

int Tiempo :: GetHoras (void) const
{
	return horas; 
}

int Tiempo :: GetMinutos (void) const
{
	return minutos; 
}

int Tiempo :: GetSegundos (void) const
{
	return segundos; 
}

int Tiempo :: GetMilesimas (void) const
{
	return milesimas; 
}

long Tiempo :: GetTiempoMilisegundos (void) const
{
	return (horas*MILISEGS_HORA + minutos*MILISEGS_MIN + 
			segundos*MILISEGS_SEG + milesimas);	
}

/***************************************************************************/
/***************************************************************************/
//Metodos comparacion entre dos objetos tiempo
//Operadores Relacionales

//Operador >
bool Tiempo :: operator > (const Tiempo & otro) 
{
	long int milisegs_1, milisegs_2;
	
	milisegs_1 = GetTiempoMilisegundos(); 
	milisegs_2 = otro.GetTiempoMilisegundos(); 
				 
	return (milisegs_1 > milisegs_2);
}	
/****************************************************************************/
//Operador <
bool Tiempo :: operator < (const Tiempo & otro)
{

	return (!((*this) > otro) && !((*this) == otro));

}
/****************************************************************************/
//Operador ==
bool Tiempo :: operator == (const Tiempo & otro) 
{

	long int milisegs_1, milisegs_2;
	
	milisegs_1 = GetTiempoMilisegundos(); 
	milisegs_2 = otro.GetTiempoMilisegundos(); 
				 
	return (milisegs_1 == milisegs_2);

}
/****************************************************************************/
//Operador !=
bool Tiempo :: operator != (const Tiempo & otro) 
{

	return ((*this)!=otro);

}

/*******************************************************/
// Operador <=
bool Tiempo :: operator <= (const Tiempo & otro)
{
return (!((*this) > otro));
}

/*******************************************************/
// Operador >=
bool Tiempo :: operator >= (const Tiempo & otro)
{
return (((*this) > otro) || ((*this) == otro));
}
/*******************************************************/

/****************************************************************************/

/***************************************************************************/
// Serializa un dato Tiempo.

string Tiempo :: ToString (CategoriaTiempo tipo_tiempo) const
{
	string cad; 
	
	switch (tipo_tiempo) {
		
		case (CategoriaTiempo::horas) : {
			cad = cad + ::ToString(GetHoras(), 2, '0') + ":"; 
		}
		case (CategoriaTiempo::minutos) : {
			cad = cad + ::ToString(GetMinutos(), 2, '0') + ":"; 
		}		
		default: {
			cad = cad + ::ToString(GetSegundos(), 2, '0') + ":" + 
		  		        ::ToString(GetMilesimas(), 3, '0');
			break;
		} 
	}

	return cad; 
}

/*****************************************************************************/
//OPERADOR <<
/*****************************************************************************/

// Inserta en un flujo de texto de salida el contenido de un
// dato "Tiempo".
// Parámetros: out, el flujo de salida.
// tiempo, el dato a insertar.

ostream & operator << (ostream & out, const Tiempo & tiempo)
{
	
	if(tiempo.horas<10)	
		out<<setfill('0')<<setw(2)<<tiempo.horas<<":";
	else
		out<<tiempo.horas << ":";
		
	if(tiempo.minutos<10)	
		out<<setfill('0')<<setw(2)<<tiempo.minutos<<":";
	else
		out<<tiempo.minutos<<":";
	
	if(tiempo.segundos<10)	
		out<<setfill('0')<<setw(2)<<tiempo.segundos<<":";
	else
		out<<tiempo.segundos<<":";
	
	if(tiempo.milesimas<100 && tiempo.milesimas>=10)	
		out<<setfill('0')<<setw(2)<<tiempo.milesimas;
	
	else if(tiempo.milesimas<10)
		out<<setfill('0')<<setw(3)<<tiempo.milesimas;
	else
		out<<tiempo.milesimas<<" ";
	
	return out; 
}

/*****************************************************************************/
//OPERADOR >>
/*****************************************************************************/
// Lee los datos de un objeto "Tiempo" desde un flujo de texto.

istream & operator >> (istream & in,  Tiempo & tiempo)
{

	string cad;
	
	in >> cad;
	
	tiempo.horas     = stoi(cad.substr(0,2));	 
	tiempo.minutos   = stoi(cad.substr(3,2));	 
	tiempo.segundos  = stoi(cad.substr(6,2));	 	
	tiempo.milesimas = stoi(cad.substr(9,3));	

	return in; 
}

/***************************************************************************/
/***************************************************************************/


/***************************************************************************/

