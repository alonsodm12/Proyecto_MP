/***************************************************************************/
//PROYECTO
//
//AUTOR:ALONSO DOÑA MARTINEZ
//
//Archivo->VectorMarcas.cpp
// Contiene las definiciones de los métodos de la clase VectorMarcas 
//...........................................................................

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include "VectorMarcas.h"
#include "RegistroDeMarcas.h"
#include "MatrizMarcas.h"

using namespace std; 

/*****************************************************************************/
//Constructores

//Constructor sin argumentos

VectorMarcas :: VectorMarcas (void)
	:capacidad(0),
	num_marcas(0),
	etiqueta("0")
	{	
		las_marcas = new RegistroDeMarca[capacidad];
	}

/*****************************************************************************/
//Constructor a partir de un objeto RegistroDeMarca

VectorMarcas :: VectorMarcas (RegistroDeMarca m)
	{
		etiqueta="0";
		las_marcas = new RegistroDeMarca [1];

		capacidad = 1;			//Solo tendra una casilla ocupada
		num_marcas = 1;
		
		las_marcas[0]=m;
	}

/*****************************************************************************/	
//Constructor de copia
	
VectorMarcas :: VectorMarcas (const VectorMarcas & otro)
{
	ReservaMemoria (otro.capacidad);
	CopiarDatos (otro);
}

/*****************************************************************************/
//Constructor que toma valores desde un fichero

VectorMarcas :: VectorMarcas (const string & nombre)
{
	(*this).LeerVectorMarcas(nombre);
}

/*****************************************************************************/
//Constructor que toma valores desde un fichero de MatrizMarcas, se extraeran
// las marcas cuya etiqueta coincide con el string nombre_prueba 
	
VectorMarcas :: VectorMarcas (const string & nombre_fichero_marcas,
							  const string & nombre_prueba)
{

	MatrizMarcas m;		//Creamos MatrizMarcas

	m.LeerMatrizMarcas(nombre_fichero_marcas);	//Leemos la matriz del archivo 
												// de datos

	int posicion=0;
	for(int i=0;i<m.NumPruebas();i++)			//Encontramos la fila que 
		if(m.Etiqueta(i)==nombre_prueba)		//queremos guardar en el 
			posicion=i;							//VectorMarcas
	
	ReservaMemoria(m(posicion+1).capacidad);	//Guardamos la fila en el
	CopiarDatos(m(posicion+1));					//VectorMarcas implicito
	
}

/*****************************************************************************/	
// Destructor 

VectorMarcas :: ~VectorMarcas (void)
{
	LiberaMemoria();
}

/*****************************************************************************/
//Métodos Básicos de la clase MatrizMarcas
/*****************************************************************************/

/*****************************************************************************/
//Devuelve el numero de marcas que contiene el VectorMarcas
//Si se utiliza como lvalue se podra modificar el numero de marcas del VectorMarcas
//Si se utiliza como rvalue se podra consultar el numero de marcas del VectorMarcas

int & VectorMarcas :: NumMarcas (void)
{	
	return(num_marcas);
}

/*****************************************************************************/	
//Devuelve la capacidad total del VectorMarcas
//Si se utiliza como lvalue se podra modificar la capacidad del VectorMarcas
//Si se utiliza como rvalue se podra consultar la capacidad del VectorMarcas

int & VectorMarcas :: Capacidad (void)
{		
	return (capacidad);
}

/***************************************************************************/	
// "Destruye" el vector y la deja en un estado no útil (vacía). 
// Parámetros: 
// POST: El vector queda vacía (todos sus campos a cero)

void VectorMarcas :: DestruyeVector (void)
{
	LiberaMemoria ();
}


/***************************************************************************/		
//Devuelve la etiqueta del vector

string  & VectorMarcas :: Etiqueta_Vec (void)
{		
	return (etiqueta);
}

/*****************************************************************************/
//Reajusta el tamaño de vector marcas 
//PRE: num_marcas==capacidad
	
void VectorMarcas :: Reajusta (void){
	
	int nueva_capacidad = capacidad +TAM_BLOQUE;
	
	// Pedir memoria para el nuevo almacen 
	RegistroDeMarca * tmp = new RegistroDeMarca[nueva_capacidad]; 
	
	//Rellenamos el nuevo almacen con los valores del antiguo almacen
	for (int i=0; i<num_marcas; i++)
		tmp[i]=las_marcas[i];
		
	// Liberar la memoria del antiguo almacén
	delete [] las_marcas;

	las_marcas=tmp;
	
	//Actualizamos capacidad
	capacidad=nueva_capacidad;
	
}

/***************************************************************************/
//METODOS DE ORDENACION
/***************************************************************************/

/***************************************************************************/
//Ordena dos objetos VectorMarcas atendiendo a los parametros pasados
// como argumento
// sentido(int)-->1 ordena de forma decreciente
// sentido(int)-->2 ordena de forma creciente

//criterio(int)-->1 la ordenacion sera por tiempo
//criterio(int)-->2 la ordenacion sera por fecha
//criterio(int)-->3 la ordenacion sera por licencia
//PRE-> en el caso de que el usuario no pasase como argumento alguno de los
// establecidos se ordenara por defecto de forma decreciente

bool VectorMarcas :: Ordena (int pos1,int pos2, int sentido, int criterio)
{
bool condicion;

	if(sentido==1)
	
		condicion=OrdenaDeCreciente(pos1,pos2,criterio);
	
	else if(sentido==2)
		condicion=OrdenaCreciente(pos1,pos2,criterio);
		
	else
		condicion=condicion=OrdenaDeCreciente(pos1,pos2,criterio);;
		
return(condicion);
}

/***************************************************************************/
// Serializa un dato VectorMarcas.

string VectorMarcas :: ToString (void) const
{
	string cad;

	string delimitador = "..................................";
	
	cad = "\n" + delimitador + "\n";
	
	cad = cad + "Prueba = " + etiqueta + " Numero de marcas = " +
		  to_string(num_marcas) + "\n\n";
	for(int f=0;f<num_marcas;f++){	  
	
		cad = cad + to_string(f+1) + las_marcas[f].ToString();
		cad = cad + "\n";
	}
	
	cad = cad + delimitador + "\n\n";

	return cad;
}


/***********************************************************************/
// Método que guarda el contenido de una "VectorMarcas" en un fichero de 
// texto llamado "nombre".

void VectorMarcas:: EscribirVectorMarcas (const string & nombre) const
{

	ofstream fo (nombre);

	if (!fo) {
		cerr << "Error: no pudo crearse " << nombre << endl;
		exit (1);
	}

	fo.setf (ios::fixed);
	fo.setf (ios::showpoint);
	
	fo << "PRUEBA" << endl;

	fo << (*this); 

	fo.close();

}

/***********************************************************************/
/***********************************************************************/
// Método que rellena un VectorMarcas (que ya existe) a partir de
// los datos presentes en el fichero de texto llamado "nombre".
//
// Este método NO es un constructor: el objeto sobre el que se aplica
// ya existe, por lo tanto, lo primero que debe hacerse es "limpiarlo"
// y después, leer los valores a guardar en la VectorMarcas de los datos 
// almacenados en el fichero llamado "nombre"

void VectorMarcas :: LeerVectorMarcas (const string & nombre)
{

	// Limpiar el objeto: Liberar memoria reservada previamente
	LiberaMemoria ();
	
	ifstream fi (nombre);
	if (!fi) {
		cerr << "Error: no puede abrirse " << nombre << endl;
		exit (1);
	}
	
	const int MAX_CADENA = 100;
	char cadena[MAX_CADENA];

	fi.getline(cadena, MAX_CADENA);	// Lectura palabra mágica
	
	if (!strcmp(cadena, "PRUEBA")) {	// CORRECTO --> Seguir leyendo
		fi.getline(cadena, MAX_CADENA);	// Lectura Adelantada

		while (cadena[0]=='#') 
			fi.getline(cadena,MAX_CADENA);		// Nueva lectura
		
		
		cout<<cadena<<endl;
		fi >> (*this);
	}
	else {
		cerr << "Error en fichero " << nombre << ": ";
		cerr << "No es un fichero PRUEBA" << endl; 
	}

	fi.close();

}

/*****************************************************************************/
//Método que comprueba si un VectorMarcas esta vacio o no
//POST: Devuelve un bool, true si esta vacia, false sino esta vacia
//
bool VectorMarcas :: EstaVacio (void)
{
	bool vacio;
	
	if(las_marcas==nullptr)
		vacio=true;
	else
		vacio= false;
		
	return ((vacio) ? true : false);

}

/*****************************************************************************/

//.........................................................................
//OPERADORES
//.........................................................................

/*****************************************************************************/
//OPERADOR >>
/*****************************************************************************/

// Lee los datos de un objeto "VectorMarcas" desde un flujo de texto.

istream & operator >> (istream & in,  VectorMarcas & v)
{	
	string cad;
	int numero; 

	in >> cad;    			//Leemos la etiqueta
	in >>numero;			//Leemos el numero de marcas que tendra
	
	v.etiqueta=cad;			//Guardamos la etiqueta
	
	v.ReservaMemoria (numero);	
	
	v.num_marcas=numero;	//Guardamos el numero de marcas
	
	int controlador=0;	  //Nos indicara la posicion en donde insertar los datos 
		
	string cad_fecha, cad_licencia, cad_tiempo;	
	
	//Lectura adelantada
	in >> cad_fecha;
	
	while(!in.eof()){
		
		in >> cad_licencia;			//Leemos la licencia
		in >> cad_tiempo;			//Leemos el tiempo
	
		Tiempo tiempo(cad_tiempo);	//Creamos objeto Tiempo a partir de cad_tiempo
		
		Licencia licencia(cad_licencia);	//Creamos objeto licencia
		
		Fecha fecha(cad_fecha);		//Creamos objeto Fecha a partir de cad_fecha
		
		RegistroDeMarca r(fecha,licencia,tiempo);	//Creamos RegistroDeMarca
    	
    	v.las_marcas[controlador]=r;	//Añadimos el objeto RegistroDeMarca 
    	
    	controlador++;					//Aumentamos posicion
    	
    	in >> cad_fecha;
    }  
	
	return in; 
}

/*****************************************************************************/
//OPERADOR <<
/*****************************************************************************/

// Inserta en un flujo de texto de salida el contenido de un
// dato "VectorMarcas".
// Parámetros: out, el flujo de salida.
// v, el dato a insertar.

ostream & operator << (ostream & out, const VectorMarcas & v)
{
	out<<endl;
	out<<v.etiqueta<<" "<<v.num_marcas<<endl;
	
	
	for(int f=0;f<v.num_marcas;f++){	  
	
		out<<v.las_marcas[f];
		out<<endl;
	}

	return (out);
}

/***********************************************************************/
// OPERADOR =
// Operador de asignación desde otro dato VectorMarcas
// Parámetros: otro (referencia), objeto que sirve de modelo. 

VectorMarcas & VectorMarcas :: operator = (const VectorMarcas & otro)
{
	if(this!=&otro){
		
		LiberaMemoria();
		ReservaMemoria(otro.capacidad);
		CopiarDatos(otro);
	
	}

return(*this);
}


/***********************************************************************/
// OPERADOR ()
// Metodo de acceso individual a elementos
// Metodo de lectura/escritura
// PRE: 1 <= fils && 1 <= cols

RegistroDeMarca & VectorMarcas :: operator () (const int pos)
{

	return(las_marcas[pos-1]);

}

/*****************************************************************************/
/*****************************************************************************/
//OPERADORES ARITMETICOS
/*****************************************************************************/
/*****************************************************************************/
//OPERADOR +
//
//VERSION 1
// VectorMarcas + VectorMarcas
// Permite la suma de dos vectoresmarcas
// Los valores del segundo objeto vectormarcas se añadiran al final del primero


VectorMarcas operator + (const VectorMarcas & v1 , const VectorMarcas & v2)
{
	//Vector local, para el resultado, sera una copia de vector v1
	
	VectorMarcas tmp(v1);
	
	
	for(int i=0;i<v2.num_marcas;i++){
	
		//Comprobamos si es necesario reajustar
		if(tmp.num_marcas==tmp.capacidad)			
			tmp.Reajusta();
			
		//Introducimos los valores en el vector	local
		tmp.las_marcas[tmp.num_marcas]=v2.las_marcas[i];
		
		//Aumentamos el numero de marcas
		tmp.num_marcas++;
		
	}
	
	return (tmp); 
}

/*****************************************************************************/
//VERSION 2
// VectorMarcas + RegistroDeMarca
// Permite la suma de un vectormarcas y un registrodemarcas
// El registrodemarca se añade al final del vectormarcas

VectorMarcas operator + (const VectorMarcas & v1,const RegistroDeMarca & m2)
{
	//Creamos un vectormarcas a partir del registrodemarca
	VectorMarcas tmp2(m2);	
	
	return (v1+tmp2);	//Usamos operador de suma version 1
}

/*****************************************************************************/
//VERSION 3
// RegistroDeMarca + VectorMarcas
//
// Permite la suma de un registrodemarcas y un vectormarcas
// El registrodemarca ocupara la primera posicion del nuevo vector 
// añadiendose al final el resto de valor del vectormarcas

VectorMarcas operator + (const RegistroDeMarca & m2, const VectorMarcas & v1)
{
	
	//Creamos un vector a partir del registrodemarca
	VectorMarcas tmp2(m2);
	
	//Creamos vector local a partir de v1
	VectorMarcas tmp(v1);
	
	tmp2.etiqueta=tmp.etiqueta;
	
	return(tmp2+tmp); //Usamos operador de suma version 1
}

/*****************************************************************************/
//OPERADOR -
//
//VERSION 1
// VectorMarcas - string(licencia)
// Permite la eliminacion del vectormarcas de un competidor a partir de su licencia

VectorMarcas VectorMarcas :: operator - (string licencia)
{
	//Vectormarcas local, para el resultado
	VectorMarcas tmp;
	
	
	for(int i=0;i<num_marcas;i++){
		//Comprobamos que la licencia no sea igual a la pasada como argumento
		if (las_marcas[i].GetLicencia().Get_licencia()!=licencia) {
			
			//Reajustamos el nuevo vectormarcas cuando sea necesario
			if(tmp.num_marcas==tmp.capacidad)
				tmp.Reajusta();
			
			//Añadimos al vectormarcas local la marca
			tmp.etiqueta=(*this).etiqueta;
			tmp.las_marcas[tmp.num_marcas] = las_marcas[i];	
			
			//Aumentamos el numero de marcas del vectormarcas local
         	tmp.num_marcas++;
        }  
    }
        
	return (tmp); 
}

/*****************************************************************************/
//OPERADORES COMBINADOS
/*****************************************************************************/

//Operador +=

//VERSION 1
// VectorMarcas += VectorMarcas
// Permite la suma de dos vectoresmarcas
// Los nuevos valores se añadiran al final del vector implicito

VectorMarcas & VectorMarcas :: operator += (const VectorMarcas & v1)
{
	(*this) = (*this) + v1;	//Operador binario + (Version 1)
	
	 return (*this);
}

/*****************************************************************************/
//VERSION 2 : VectorMarcas += RegistroDeMarca
//
// Permite la suma de un vectormarcas y un registrodemarca,
// El registrodemarca se añadira al final del vectormarcas implicito

VectorMarcas & VectorMarcas :: operator += (const RegistroDeMarca & marca)
{

	(*this) = (*this) + marca;	//Operador binario + (Version 2)
	
	return (*this);

} 

/*****************************************************************************/
//Operador -=

//VERSION 1 : VectorMarcas -= string(licencia)
//
// Permite la resta de un vectormarcas y un registrodemarcas
// Se eliminaran del vectormarcas aquellas marcas que coincidan con la licencia
// pasada como argumento

VectorMarcas & VectorMarcas :: operator -= (const string licencia)
{

	(*this) = (*this) - licencia;	//Operador binario - (Version 1)
	
	return (*this);

} 


/***************************************************************************/
/***************************************************************************/
//METODOS PRIVADOS
/***************************************************************************/
/***************************************************************************/

// Pide memoria para guardar "ncapacidad" datos		
void VectorMarcas :: ReservaMemoria (const int ncapacidad)
{ 

	// Por defecto, matriz vacía
	
	capacidad = 0;
	num_marcas = 0;
	
	// Solo si se cumplen las precondiciones se reserva memoria 

	if (ncapacidad>0) {

		// "matriz" apuntará a un vector de punteros a las filas
		las_marcas = new RegistroDeMarca [ncapacidad];

		capacidad = ncapacidad;
		
	}

}

/***************************************************************************/

// Copiar datos desde otro objeto de la clase
// PRE: Se ha reservado memoria para los datos

void VectorMarcas :: CopiarDatos(const VectorMarcas & otro)
{
	capacidad=otro.capacidad;
	num_marcas=otro.num_marcas;
	etiqueta=otro.etiqueta;
	
	for(int f=0;f<num_marcas;f++)
		las_marcas[f]=otro.las_marcas[f];
}

/***************************************************************************/
	
//Libera memoria
	
void VectorMarcas :: LiberaMemoria(void)
{

	if (las_marcas) {
		// Liberar cada una de las filas
 		// Liberar el vector de punteros
 		
 		delete [] las_marcas;
 		
 		num_marcas=0;
 		capacidad=0;	
 	}
}

//Ordena de forma decreciente
//Decide el criterio de ordenacion
//critierio-->1 la ordenacion sera por tiempo
//critierio-->2 la ordenacion sera por fecha
//critierio-->3 la ordenacion sera por licencia

bool VectorMarcas :: OrdenaDeCreciente (int pos1,int pos2,int criterio)
{ 
	
	if(las_marcas[pos1-1].EsMenor(las_marcas[pos2-1],criterio))
		return true;
	
	else
		return false;		

}

/***************************************************************************/

//Ordena de forma creciente
//Decide el criterio de ordenacion
//critierio-->1 la ordenacion sera por tiempo
//critierio-->2 la ordenacion sera por fecha
//critierio-->3 la ordenacion sera por licencia

bool VectorMarcas :: OrdenaCreciente (int pos1,int pos2,int criterio)
{ 
	
	if(las_marcas[pos1-1].EsMayor(las_marcas[pos2-1],criterio))
		return true;
	
	else
		return false;		

}


/***************************************************************************/
/***************************************************************************/
	
	
