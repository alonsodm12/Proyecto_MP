/****************************************************************************/
//PROYECTO
//
//AUTOR:ALONSO DOÑA MARTINEZ
//DECLARACIONES DE LA CLASE MatrizMarcas.cpp
//
//............................................................................
#ifndef MATRIZ_MARCAS
#define MATRIZ_MARCAS

#include <string>
#include "VectorMarcas.h"
#include "RegistroDeMarcas.h"

using namespace std;


class MatrizMarcas{

	private:
	
		int num_pruebas;	//numero de filas de la matriz
							//PRE->Debe ser mayor que 0
	
		VectorMarcas *pruebas=0;	//accede a las filas de la matriz

	public:
	
// Constructor unificado:
//	a) Constructor sin argumentos, que crea una matriz vacía.
//  b) Constructor con un argumento, que crea una matriz con un número de 
//		filas indicado en el argumento.
//
// Crea una matriz  con "filas" nodos. 
// Parámetros:
//  	filas, número de filas que se van a crear. 
//	Devuelve: un dato de tipo MatrizMarcas.
//
// PRE:  filas >= 0 
// NOTA: Si filas==0 la matriz queda vacía. 

		MatrizMarcas(int filas=0);
		
/*****************************************************************************/

//Constructor de copia
		
		MatrizMarcas (const MatrizMarcas & otro);

/*****************************************************************************/

		
//Constructor a partir de un objeto VectorMarcas
		
		MatrizMarcas (const VectorMarcas & otro);

/*****************************************************************************/
		
//Constructor que toma valores desde un fichero
//PRE: el fichero puede ser tanto txt como binario

    	MatrizMarcas (const string & nombre);

/*****************************************************************************/
		
//Destructor
		
		~MatrizMarcas(void);
		
/*****************************************************************************/
		
//Consulta ó modifica el numero de pruebas. Si se utiliza como 
//rvalue se emplea para consultar el contenido de "num_pruebas". 
//Si se utiliza como lvalue se emplea para modificar el valor de "num_pruebas".
//	POST->devuelve un dato de tipo int

		int & NumPruebas(void);
		
/*****************************************************************************/
		
// Indica el numero de marcas contenidas en la matrizmarcas
		
		int NumMarcas (void) const;
		
/*****************************************************************************/
		
// "Destruye" la matriz y la deja en un estado no útil (vacía). 
// POST: La matriz queda vacía (todos sus campos a cero)

		void DestruyeMatriz (void);
		
/*****************************************************************************/
		
//Consulta ó modifica la etiqueta de una posicion dada.
//Si se utiliza como rvalue se emplea para consultar el 
//contenido de "etiqueta". Si se utiliza como lvalue se 
//emplea para modificar el valor de "etiqueta". 
// Argumentos: 	 
//		posicion, fila en la que estamos interesados obtener de su etiqueta.
//		posicion >=0 & posicion < num_pruebas
//POST->devuelve un dato de tipo string
		
		string & Etiqueta (int posicion);
		
/*****************************************************************************/
		
//Funcion que devuelve el dato MatrizMarcas serializado
		
		string ToString(const char * const msg=" ");
		
/*****************************************************************************/
// Añade un valor a MatrizMarcas
// Argumentos: 	
//marca(RegistroDeMarca), referencia al objeto que se va a añadir a la matriz. 
//fila(int), fila donde se va a añadir la marca
 
// NOTA: Si no hay espacio libre, la función pide espacio adicional  
// usando la función RedimensionaVectorDinamico. 
		
		void Aniade(RegistroDeMarca marca,string fila);
		
/*****************************************************************************/
//Ordena la matrizmarcas segun el criterio especificado por contador
//PRE:
//Si sentido == 1 se ordenara de forma decreciente
//Si sentido == 2 se ordenara de forma creciente
//
//Si criterio == 1 se ordenara por tiempo
//Si criterio == 2 se ordenara por fecha
//Si criterio == 3 se ordenara por licencia
	
		void Orden(int sentido,int criterio);
		
/*****************************************************************************/
//Método que comprueba si una MatrizMarcas esta vacio o no
//POST: Devuelve un bool, true si esta vacia, false sino esta vacia

		bool EstaVacia(void);
	
/*****************************************************************************/
// Métodos de E/S
/*****************************************************************************/
		 
// Guardan/recuperan el contenido de una MatrizMarcas en/de un 
// fichero
// ARGUMENTOS
//  txt(bool)-> indica el tipo de fichero en el que queremos escribir
//  txt=true-> se escribira en un txt
//  txt=false-> se escribira en un archivo binario

    	void EscribirMatrizMarcas (const string & nombre, bool txt=true) const;
    	
    	void LeerMatrizMarcas (const string & nombre, bool txt=true);

/*****************************************************************************/

/*****************************************************************************/		
// OPERADORES
/*****************************************************************************/
		
/*****************************************************************************/

//OPERADOR >>
// Inserta en un flujo de texto de salida el contenido de un dato "MatrizMarcas".
// Parámetros: out, el flujo de salida.
// v, el dato a insertar.

    	friend istream & operator >> (istream & in, MatrizMarcas & m); 
    	
/*****************************************************************************/

//OPERADOR <<
// Lee los datos de un objeto "MatrizMarcas" desde un flujo de texto.
   		
    	friend ostream & operator << (ostream & out, const MatrizMarcas & m);

/*****************************************************************************/
		
//OPERADOR =
// Operador de asignación desde otro dato MatrizMarcas
// Parámetros: otro (referencia), objeto que sirve de modelo. 
						
		MatrizMarcas & operator = (const MatrizMarcas & otro);

/*****************************************************************************/
		
//OPERADOR ()
// Metodo de acceso individual a elementos: operator ()
// Metodo de escritura / lectura
// PRE: 1 <= fils && 1 <= cols
    
    	VectorMarcas & operator () (const int fila);
		
		RegistroDeMarca & operator () (const int fila, const int col);

/*****************************************************************************/
		
//OPERADOR +

//VERSION 1
// MatrizMarcas + MatrizMarcas
// Permite la suma de dos MatrizMarcas añadiendo los valores de la 
// segunda a la primera manteniendo el orden de los datos
//PRE: Las etiquetas de las pruebas de ambas matrices pueden ser distintas,
// en el caso que ocurra se añadiran al final de la matriz

		
     	friend MatrizMarcas operator + (const MatrizMarcas & m1, 
     								const MatrizMarcas & m2);
//VERSION 2
// MatrizMarcas + VectorMarcas
// Permite la suma de una MatrizMarcas con un VectorMarcas insertando 
// al final de la matriz la nueva fila
  
   	  	friend MatrizMarcas operator + (const MatrizMarcas & m1, 
     								const VectorMarcas & v2);
     
//VERSION 3
// MatrizMarcas + VectorMarcas
// Permite la suma de un VectorMarcas con una MatrizMarcas 
// añadiendo al inicio de la matriz la nueva fila
      
     	friend MatrizMarcas operator + (const VectorMarcas & v1, 
     								const MatrizMarcas & m1);

/*****************************************************************************/
     
//OPERADOR -
  
// MatrizMarcas - string(licencia)
// Elimina todas las marcas cuyo campo licencia sea igual al valor dado
// PRE: si no hay ninguna marca que coincida con la licencia pasada
// como argumento, la MatrizMarcas se queda igual
// ARGUMENTOS:
//	licencia(string)-> nombre de la marca que queremos eliminar
        
     	MatrizMarcas operator - (const string licencia);
 
/*****************************************************************************/

//OPERADORES COMBINADOS
//OPERADOR +=
     
//VERSION 1
// MatrizMarcas += MatrizMarcas
// Permite la suma de dos MatrizMarcas las filas de la matriz explicita que 
// coincidan con las filas de la implicita se añadiran manteniendo el orden
     
     	MatrizMarcas & operator += (const MatrizMarcas & m1);
     
//VERSION 2 : MatrizMarcas += VectorMarcas
// Permite la suma de una MatrizMarcas y un VectorMarcas
// Se añade una nueva fila al final de la MatrizMarcas implicta
    	
    	MatrizMarcas & operator += (const VectorMarcas & v1);
     
/*****************************************************************************/

//OPERADOR -=
//VERSION 1 : MatrizMarcas -= string(licencia)
// Permite la eliminacion de una marca a partir de su licencia
// Se eliminaran las marcas de la matriz implicita que coincidan en licencia
// con la pasada como argumento
// ARGUMENTOS:
// licencia(string)
//POST: En el caso de que licencia(string) no coincida con la licencia de
// ninguna marca, la matriz quedara igual

     
     	MatrizMarcas & operator -= (const string licencia);
     
/*****************************************************************************/


/*****************************************************************************/
/*****************************************************************************/
			
///////////////////////////////////////////////////////////////////////////////
//FUNCIONES AMBITO PRIVADO
///////////////////////////////////////////////////////////////////////////////
	
	private: 
		
//Pide memoria para guardar "nfilas" datos	
		
		void ReservaMemoria (int nfils);
		
/*****************************************************************************/
		
//Libera memoria
		
		void LiberaMemoria(void);
		
/*****************************************************************************/
		
// Copiar datos desde otro objeto de la clase
// PRE: Se ha reservado memoria para los datos

		void CopiarDatos (const MatrizMarcas & otro);
	
/*****************************************************************************/
			
// Guardan/recuperan el contenido de una MatrizMarcas en/de un 
// fichero de texto. El nombre del fichero se pasa como argumento

		void EscribirMatrizMarcasTxt (const string & nombre) const;
    	
    	void LeerMatrizMarcasTxt (const string & nombre);
	
/*****************************************************************************/
	
// Guardan/recuperan el contenido de una MatrizMarcas en/de un 
// fichero binario. El nombre del fichero se pasa como argumento

		void EscribirMatrizMarcasBin (const string & nombre) const;
    	
    	void LeerMatrizMarcasBin (const string & nombre);

/*****************************************************************************/
//Permite añadir una fila al final de la MatrizMarcas, para ello
//se creara una nueva matriz de las dimensiones requeridas, se copiaran
//los datos de la matriz y se añadirá al final los datos de la nueva fila.
//Parametros:
// v(VectorMarcas) fila que queremos insertar al final
	
		void AniadeFila (const VectorMarcas & v);

/*****************************************************************************/	
//Permite insertar una fila en la posicion deseada de la MatrizMarcas
//Parametros:
// posicion(int) indica la posicion donde deseamos insertar la nueva fila
// v(VectorMarcas) fila que deseamos insertar
//PRE: posicion >= 1 & posicion <= num_pruebas-1
		
		void InsertarFila (const VectorMarcas & v, int posicion);
    	
};


#endif

