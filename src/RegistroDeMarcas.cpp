/***************************************************************************/
//PROYECTO
//
//AUTOR:ALONSO DOÑA MARTINEZ
//
//Archivo -> RegistroDeMarcas.cpp
//...........................................................................

#include <iostream>
#include <iomanip>
#include <string>
#include "RegistroDeMarcas.h"
#include "Utils.h"

using namespace std;

/*****************************************************************************/
// Constructor sin argumentos. 
// Necesario para crear arrays o matrices.

RegistroDeMarca :: RegistroDeMarca (void)
	:fecha_marca(),
	licencia(),
	tiempo_marca()
	{}

/*****************************************************************************/
// Constructor con argumentos. 
// Parámetros: triviales. 

RegistroDeMarca :: RegistroDeMarca (Fecha la_fecha_marca, 
	                                Licencia la_licencia, 
	             				    Tiempo el_tiempo_marca) 
				: fecha_marca (la_fecha_marca), 
	              licencia (la_licencia), 
	       		  tiempo_marca (el_tiempo_marca)
{} 

/*****************************************************************************/
// Métodos Get

Fecha  RegistroDeMarca :: GetFecha (void) const
{
	return fecha_marca;
}

Licencia RegistroDeMarca :: GetLicencia (void) const
{
	return licencia;
}

Tiempo RegistroDeMarca :: GetTiempo (void) const
{
	return tiempo_marca;
}

/*****************************************************************************/
//Metodos comparacion
/*****************************************************************************/

/*****************************************************************************/
//Metodo de comparacion de menor a mayor
//PRE: controlador(int) indica el criterio de comparacion 
// controlador->1 se ordenara por tiempo
// controlador->2 se ordenara por fecha
// controlador->3 se ordenara por licencia

bool RegistroDeMarca :: EsMenor(const RegistroDeMarca & otro,int controlador)
{
	return (!((*this).EsMayor(otro,controlador)) && 
			!((*this).EsIgual(otro,controlador)));
}

/*****************************************************************************/
//Metodo de comparacion de mayor a menor
//PRE: controlador(int) indica el criterio de comparacion 
// controlador->1 se ordenara por tiempo
// controlador->2 se ordenara por fecha
// controlador->3 se ordenara por licencia

bool RegistroDeMarca :: EsMayor(const RegistroDeMarca & otro,int controlador)
{
	bool condicion=true;
	
	if(controlador==1){
	
		if(tiempo_marca>(otro.tiempo_marca))
			condicion=true;
		else
			condicion=false;
	}
	
	else if(controlador==2){
		if(fecha_marca>(otro.fecha_marca))
			condicion=true;
		else
			condicion=false;
	}
	else if (controlador==3){
		if(licencia<(otro.licencia))
				condicion=true;
		else
			condicion=false;
		
	}
	
return condicion;
} 

/*****************************************************************************/
//Metodo de comparacion, compara si son iguales el objeto implicito RegistroDeMarca
// y el explicito otro
//PRE: controlador(int) indica el criterio de comparacion 
// controlador->1 se ordenara por tiempo
// controlador->2 se ordenara por fecha
// controlador->3 se ordenara por licencia

bool RegistroDeMarca :: EsIgual(const RegistroDeMarca & otro,int controlador) 
{
	bool condicion=true;
	
	if(controlador==1){
		
		if(tiempo_marca==(otro.tiempo_marca))
			condicion=true;
		
		else
			condicion=false;
	}	
		
	else if(controlador==2){
		
		if(fecha_marca==(otro.fecha_marca))
			condicion=true;
		
		else
			condicion=false;
	
	}
	else{
	
		if(licencia==(otro.licencia))
			condicion=true;
		else
			condicion=false;
	
	}
	
return condicion;	
}

/*****************************************************************************/
//Metodo de comparacion, compara si son iguales el objeto implicito RegistroDeMarca
// y el explicito otro
//PRE: controlador(int) indica el criterio de comparacion 
// controlador->1 se ordenara por tiempo
// controlador->2 se ordenara por fecha
// controlador->3 se ordenara por licencia

bool RegistroDeMarca :: NoEsIgual(const RegistroDeMarca & otro,int contador) 
{
return(!EsIgual(otro,contador));	
}

/***************************************************************************/
// Serializa un dato RegistroDeMarca.

string RegistroDeMarca :: ToString (void) const
{
	string cad = ::ToString(GetLicencia().Get_licencia(),12) + "   " + 
	               GetFecha().ToString() + "  " + 
	               GetTiempo().ToString(CategoriaTiempo::minutos);
	return cad;
}

/***************************************************************************/


////////////////////////////////////////////////////////////////////////////
//////////////////////////////OPERADORES////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/*****************************************************************************/
//OPERADOR <<
/*****************************************************************************/

// Inserta en un flujo de texto de salida el contenido de un
// dato "RegistroDeMarca".
// Parámetros: out, el flujo de salida.
// r, el dato a insertar.

ostream & operator << (ostream & out, const RegistroDeMarca & r)
{
	out.setf (ios::fixed);
	out.setf (ios::showpoint);
	out << r.fecha_marca; // Operador << de "Fecha"
	out << r.licencia; // Operador << de "Licencia"
	out << r.tiempo_marca; // Operador << de "Tiempo"

return (out);
}


/*****************************************************************************/
//OPERADOR >>
/*****************************************************************************/
// Lee los datos de un objeto "RegistroDeMarca" desde un flujo de texto.

istream & operator >> (istream & in,  RegistroDeMarca & r)
{
		cout<<"Introduce fecha en formato dd/mm/aaaa "<<endl;
		in>>r.fecha_marca;
		cout<<"Introduce licencia "<<endl;	 
		in>>r.licencia;
		cout<<"Introduce tiempo en formato hh:mm:ss:mmm "<<endl;	  	
		in>>r.tiempo_marca;	
	
	return in; 
}

/***************************************************************************/
/***************************************************************************/


