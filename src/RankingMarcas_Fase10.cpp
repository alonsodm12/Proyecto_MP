//FASE 2 PROYECTO MP
//**************************************************************//
//AUTOR:ALONSO DOÑA MARTINEZ
//..............................................................//
//Archivo:RankingMarcas_Fase10.cpp(main)
//..............................................................//
//**************************************************************//

#include <iostream>
#include <string>
#include "VectorMarcas.h"
#include "MatrizMarcas.h"
#include "Tiempo.h"
#include "Fecha.h"
#include "RegistroDeMarcas.h"
#include "Licencia.h"
#include "Utils.h"
#include "fstream"
using namespace std;
/***************************************************************************/
/***************************************************************************/

int main (int argc, char ** argv)
{
    cout.setf(ios::fixed);		// Notación de punto fijo para los reales
	cout.setf(ios::showpoint);	// Mostrar siempre decimales

	//.........................................................................
	// Procesar línea de órdenes

	if (argc < 2 || argc > 3) {
		cerr << endl;
		cerr << "Error: Número incorrecto de argumentos." << endl; 
		cerr << "Uso: " << argv[0] << " <fich_marcas_entrada> "
			 << "[<fich_marcas_salida>]" << endl;
		cerr << endl;
		exit (1);
	} 

	string fuente  = argv[1];
	string destino;

	if (!ExisteFichero(fuente)) {
		cerr << endl;
		cerr << "Error: El fichero "<< fuente << " no existe o "; 
		cerr << "los permisos no son correctos." << endl;
		cerr << endl;
		exit (2);	
	}

	cerr << endl; 
	cerr << "Las marcas se leen de los archivos indicados en el ";
	cerr << "fichero: " << fuente << endl; 

	if (argc==3)  {
		destino = argv[2];
		cerr << "Las marcas se guardan en el fichero: " << destino << endl; 	
	}
	cerr << endl; 
	
	//.........................................................................
	
	// LECTURA
	// Crear la matriz de marcas tomando los datos de un fichero de texto
	// con nombres de ficheros donde debe de haber contenidas pruebas
	
	ifstream fi(fuente);
	
	string cadena;
		
	getline(fi,cadena);		//Lectura anticipada
	
	MatrizMarcas marcas;
	
	while(!fi.eof()){
	
		if(ExisteFichero(cadena)){		//Comprobamos que existe el fichero
			
			MatrizMarcas nueva_marcas(cadena);
		
			marcas+=nueva_marcas;				//Vamos añadiendo a la matriz
		}
		else
			cout << "No existe el fichero "<<cadena<<endl;
				
		getline(fi,cadena);				//Continuamos leyendo
	}
	
	// MOSTRAR RESULTADO


	cout << endl;

	if (marcas.EstaVacia()) cout << "Matriz vacia." << endl; 

	else {
	
		// Mostrar contenido de "marcas" a través de ToString()
		cout << marcas.ToString ("Marcas leidas") << endl;

		// Ordenar
		//Si 1 argumento == 1 se ordenara de forma decreciente
		//Si 1 argumento == 2 se ordenara de forma creciente
		//
		//Si 2 argumento == 1 se ordenara por tiempo
		//Si 2 argumento == 2 se ordenara por fecha
		//Si 2 argumento == 3 se ordenara por licencia
		
		marcas.Orden (1,1);
		
		cout << marcas.ToString ("Ranking - marcas ordenadas") << endl;

		if (argc==3){  // Guardar una copia después de ordenar
			
			cout << "Se guardara una copia de la matriz ordenada en ";
			cout << "el fichero "<<destino<<endl;
			marcas.EscribirMatrizMarcas (destino,true);
		}
		
	}
	
	//.......................................................................

	return 0;
}

/***************************************************************************/

/***************************************************************************/
