/***************************************************************************/
//AUTOR:ALONSO DOÑA MARTINEZ
//
//Declaraciones de la clase VectorMarcas.cpp
//
//Archivo: VectorMarcas.h
//........................................................................../

#ifndef VECTOR_MARCAS
#define VECTOR_MARCAS

#include <iostream>
#include <string>
#include "RegistroDeMarcas.h"
#include "Utils.h"
using namespace std;



class VectorMarcas {

	private:
	
		string etiqueta;	//etiqueta de la prueba
		
		RegistroDeMarca *las_marcas=0;	//puntero para acceder a las marcas 
										//de la prueba
		
		int num_marcas=0;	//numero de marcas registradas de la prueba
							// num_marcas>=0
	
		int capacidad=0;	//numero de casillas reservadas para alojar objetos
							// capacidad>=0

	public:
		
/*****************************************************************************/
//Constructor sin argumentos
		
		VectorMarcas (void);
		
//Constructor de copia
			
		VectorMarcas (const VectorMarcas & otro);
		
//Constructor a partir de RegistroDeMarca
// Parámetros: m1, RegistroDeMarca.
		
		VectorMarcas (RegistroDeMarca m1);
		
/*****************************************************************************/
// Constructor que toma valores desde un fichero

    	VectorMarcas (const string & nombre);
		
/*****************************************************************************/
//	Constructor que toma valores desde un fichero Marcas y que extrae
//	la informacion de la prueba correspondiente a nombre_prueba
//Argumentos:
//	nombre_fichero_marcas->fichero de tipo Marcas
//	nombre_prueba-> nombre de una prueba, ej:200ML
		
		VectorMarcas (const string & nombre_fichero_marcas, 
					  const string & nombre_prueba);
		
//Destructor
	
		~VectorMarcas (void);
		
/*****************************************************************************/
			
// Consulta ó modifica la capacidad. Si se utiliza como 
// rvalue se emplea para consultar el contenido de "capacidad". 
// Si se utiliza como lvalue se emplea para modificar el valor de 
// "capacidad".
// 
//POST->devuelve un dato de tipo int

		int & Capacidad (void);
		
/*****************************************************************************/
// "Destruye" el vector y la deja en un estado no útil (vacía). 
// Parámetros: 
// POST: El vector queda vacía (todos sus campos a cero)

		void DestruyeVector (void);
		
/*****************************************************************************/
		
// Consulta ó modifica el numero de marcas. Si se utiliza como 
// rvalue se emplea para consultar el contenido de "num_marcas". 
// Si se utiliza como lvalue se emplea para modificar el valor de "num_marcas".
// 
//POST->devuelve un dato de tipo int
		
		int & NumMarcas (void);
				
/*****************************************************************************/
// Consulta ó modifica una etiqueta. Si se utiliza como 
// rvalue se emplea para consultar el contenido de "etiqueta". 
// Si se utiliza como lvalue se emplea para modificar el valor de 
// "etiqueta".
// 
//POST->devuelve un dato de tipo string

		string & Etiqueta_Vec (void);
		
/*****************************************************************************/
		
//Reajusta el tamaño de VectorMarcas 
//PRE: num_marcas==capacidad

		void Reajusta (void);
		
/*****************************************************************************/
//Ordena dos objetos VectorMarcas atendiendo a los parametros pasados
// como argumento
// sentido(int)-->1 ordena de forma decreciente
// sentido(int)-->2 ordena de forma creciente

//criterio(int)-->1 la ordenacion sera por tiempo
//criterio(int)-->2 la ordenacion sera por fecha
//criterio(int)-->3 la ordenacion sera por licencia
//PRE-> en el caso de que el usuario no pasase como argumento alguno de los
// establecidos se ordenara por defecto de forma decreciente
 		
		bool Ordena(int pos1,int pos2,int sentido, int criterio);
		
/*****************************************************************************/
//Consulta si un objeto VectorMarcas esta vacio
		
		bool EstaVacio(void);
		
/*****************************************************************************/
//Serializa un tipo de dato VectorMarcas
		
		string ToString(void) const;
		
/*****************************************************************************/
// Métodos de E/S
/*****************************************************************************/
		 
// Guardan/recuperan el contenido de un VectorMarcas en/de un 
// fichero de texto. El nombre del fichero se pasa como argumento

		void EscribirVectorMarcas (const string & nombre) const;
    	void LeerVectorMarcas (const string & nombre);
		
		
/*****************************************************************************/
// OPERADORES
/*****************************************************************************/
		
//OPERADOR =
// Operador de asignación desde otro dato VectorMarcas
// Parámetros: otro (referencia), objeto que sirve de modelo. 
		
/*****************************************************************************/
		
		VectorMarcas & operator = (const VectorMarcas & otro);
		
/*****************************************************************************/
//OPERADOR ()
// Metodo de acceso individual a elementos: operator ()
// Metodo de escritura / lectura
// PRE: 1 <= num_marcas && 1 <= num_marcas
    
    	RegistroDeMarca & operator () (const int pos);
		
/*****************************************************************************/
//OPERADOR >>
// Inserta en un flujo de texto de salida el contenido de un
// dato "VectorMarcas".
// Parámetros: out, el flujo de salida.
// v, el dato a insertar.

		friend istream & operator >> (istream & in, VectorMarcas & m); 
   		
/*****************************************************************************/
//OPERADOR <<
// Lee los datos de un objeto "VectorMarcas" desde un flujo de texto.
   		
   		friend ostream & operator << (ostream & out, const VectorMarcas & v);
		
/*********************************************************************/
//OPERADORES ARITMETICOS
/*********************************************************************/
		
//OPERADOR +
//....................................................................
//Crea un VectorMarcas compuesto por ambos VectoresMarcas
     
     	friend VectorMarcas operator + (const VectorMarcas & v1, 
     									const VectorMarcas & v2);
     
//Aniade un valor al VectorMarcas
     	friend VectorMarcas operator + (const VectorMarcas & v1,
     								 	const RegistroDeMarca & m2);
     
//Inserta un valor al VectorMarcas  
     	friend VectorMarcas operator + (const RegistroDeMarca & m2,
     									const VectorMarcas & v1);
     
//OPERADOR -
//.............................................................................
     
//Elimina el valor del VectorMarcas igual que licencia
//POST:	Si no hubiese ninguna marca igual que licencia no se modifica nada
        
     	VectorMarcas operator - (const string licencia);
     
	
//OPERADORES COMBINADOS
//+=
     
//Crea un VectorMarcas compuesto por ambos VectoresMarcas
     
     	VectorMarcas & operator += (const VectorMarcas & v1);
     
//Aniade un valor al VectorMarcas
     	  
     	VectorMarcas & operator += (const RegistroDeMarca & marca);
     
//-=
     
//Elimina los valores contenidos en el VectorMarcas implicito que 
//sean igual que la marca licencia
//POST: Sino se repite ningun valor no se modifica nada
     
     	VectorMarcas & operator -= (const string licencia);
     
/*****************************************************************************/
/*****************************************************************************/
		
///////////////////////////////////////////////////////////////////////////////
//METODOS AMBITO PRIVADO DE LA CLASE
///////////////////////////////////////////////////////////////////////////////
		
	private :
		
//Libera memoria
		void LiberaMemoria (void);
		
/*********************************************************************/
// Copiar datos desde otro objeto de la clase
// PRE: Se ha reservado memoria para los datos

		void CopiarDatos(const VectorMarcas & otro);
		
/*********************************************************************/		
// Pide memoria para guardar "ncapacidad" datos	
		void ReservaMemoria (const int ncapacidad);
		
/***************************************************************************/

//Ordena de forma decreciente
//Decide el criterio de ordenacion
//critierio-->1 la ordenacion sera por tiempo
//critierio-->2 la ordenacion sera por fecha
//critierio-->3 la ordenacion sera por licencia

		bool OrdenaDeCreciente (int pos1,int pos2,int criterio);

/***************************************************************************/

//Ordena de forma creciente
//Decide el criterio de ordenacion
//critierio-->1 la ordenacion sera por tiempo
//critierio-->2 la ordenacion sera por fecha
//critierio-->3 la ordenacion sera por licencia
		 
		bool OrdenaCreciente (int pos1,int pos2,int criterio);
		
};

#endif
