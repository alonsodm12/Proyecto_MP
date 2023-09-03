/***************************************************************************/
//AUTOR: ALONSO DOÑA MARTINEZ
//
//
//PROYECTO
//
//ARCHIVO->DEFINICIONES DE LA CLASE MatrizMarcas.cpp
//...........................................................................

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include "MatrizMarcas.h"
#include "VectorMarcas.h"
#include "RegistroDeMarcas.h" 

using namespace std; 

/***********************************************************************/
// Constructores

// Constructor unificado:
//	a) Constructor sin argumentos, que crea una matriz vacía.
//  b) Constructor con un argumento, que crea una matriz con un número de 
//		filas indicado en el argumento.
//
// Crea una matriz  con "filas" pruebas. 
// Parámetros:
//  	filas, número de filas que se van a crear. 
//	Devuelve: un dato de tipo MatrizMarcas.
//
// PRE:  filas >= 0 
// NOTA: Si filas==0 la matriz queda vacía. 

MatrizMarcas :: MatrizMarcas (int filas)
	: num_pruebas (filas)
{
		ReservaMemoria(filas);		
}

/*****************************************************************************/
//Constructor de copia

MatrizMarcas :: MatrizMarcas (const MatrizMarcas & otro)
{
	ReservaMemoria (otro.num_pruebas);
	CopiarDatos (otro);
}

/*****************************************************************************/
//Constructor a partir de un objeto VectorMarcas
//PRE: Como esta formado a partir de un único VectorMarcas, 
// tendra solo una unica fila

MatrizMarcas :: MatrizMarcas (const VectorMarcas & otro)
{
	VectorMarcas copia (otro);
	
	num_pruebas = 1;		//Solo tendra una unica fila
	
	ReservaMemoria (num_pruebas);
	
	// Copiar los valores de los datos	
		pruebas[0].Etiqueta_Vec()=copia.Etiqueta_Vec();
		pruebas[0]=copia;	
		
}

/*****************************************************************************/
//Constructor que toma valores desde un fichero

MatrizMarcas :: MatrizMarcas (const string & nombre)
{
	
	ifstream fi (nombre);
	if (!fi) {
		cout<<"nombre que no pude abrirse: "<<nombre<<endl;
		cerr << "Error: no puede abrirse " << nombre << endl;
		exit (1);
	}
	
	const int MAX_CADENA = 100;
	char cadena[MAX_CADENA];

	fi.getline(cadena, MAX_CADENA);	// Lectura palabra mágica
	
	bool condicion;
	
	//Comprobamos si el archivo es binario o de texto
	
	if (!strcmp(cadena, "MARCAS")) {	// CORRECTO --> Seguir leyendo
		condicion=true;
		LeerMatrizMarcas(nombre,condicion);
	}
	
	else if(!strcmp(cadena, "MARCAS_BIN")) {	//CORRECTO --> Seguir leyendo
		condicion=false;
		LeerMatrizMarcas(nombre,condicion);
	}

	else {
		cerr << "Error en fichero " << nombre << ": ";
		cerr << "No es un fichero MARCAS" << endl; 
	}

	fi.close();
}

// Destructor 

MatrizMarcas :: ~MatrizMarcas (void)
{
	LiberaMemoria();
}

/*****************************************************************************/
/*****************************************************************************/
//Métodos Básicos de la clase MatrizMarcas
/*****************************************************************************/
/*****************************************************************************/

// Consulta ó modifica el numero de pruebas. Si se utiliza como 
// rvalue se emplea para consultar el contenido de "num_pruebas". 
// Si se utiliza como lvalue se emplea para modificar el valor de 
// "num_pruebas".
// 
//POST->devuelve un dato de tipo int

int & MatrizMarcas :: NumPruebas (void)
{
	return (num_pruebas);
}

/*****************************************************************************/
// Consulta ó modifica la etiqueta de una posicion dada. Si se utiliza como 
// rvalue se emplea para consultar el contenido de "etiqueta". 
// Si se utiliza como lvalue se emplea para modificar el valor de 
// "etiqueta".
// 
// Argumentos: 	 
//		posicion, fila en la que estamos interesados obtener de su etiqueta.
//		posicion >=0 & posicion < num_pruebas
//POST->devuelve un dato de tipo string

string & MatrizMarcas :: Etiqueta (int posicion)
{
	return (pruebas[posicion].Etiqueta_Vec());
}

/*****************************************************************************/
// "Destruye" la matriz y la deja en un estado no útil (vacía). 
// Parámetros: 
// POST: La matriz queda vacía (todos sus campos a cero)


void MatrizMarcas :: DestruyeMatriz (void)
{
	LiberaMemoria ();
}
/*****************************************************************************/		
// Indica el numero de marcas contenidas en la matrizmarcas
//POST -> devuelve un int

int MatrizMarcas :: NumMarcas (void) const
{
	int num_marcas = 0;
	
	//Contamos el numero de valores
	for (int i = 0; i < num_pruebas; i++)
		num_marcas += pruebas[i].NumMarcas();

	return (num_marcas);
}

/*****************************************************************************/		
//Funcion que devuelve el dato MatrizMarcas serializado

string MatrizMarcas :: ToString(const char * const msg){
	
  string cad;
   
  cad = cad + msg + "\n";
   
  cad = cad + '\n' + "Numero de pruebas: " + to_string(num_pruebas) + '\n';
        
  for (int i = 0 ; i < num_pruebas ; i++){
    cad += '\n' + pruebas[i].Etiqueta_Vec() + '\n';
       
        //Mostramos la informacion contenida en las marcas de cada vectormarca
        
        for (int j = 1 ; j <= pruebas[i].NumMarcas() ; j++){
        	cad += to_string(j);
        	cad += pruebas[i](j).ToString();
        	cad += '\n';
        }
    }
    return cad;
}

/*****************************************************************************/
// Añade un objeto RegistroDeMarca a una fila de la MatrizMarcas
// Argumentos: 	
//	marca(RegistroDeMarca), referencia al objeto que se va a añadir a la matriz. 
//	etiqueta(string), fila donde se va a añadir la marca
 
// NOTA: Si no hay espacio libre, la función pide espacio adicional usando 
//		 la función Reajusta. 

void MatrizMarcas :: Aniade (RegistroDeMarca marca, string etiqueta)
{

	for(int i=0;i<num_pruebas;i++){
		if(pruebas[i].Etiqueta_Vec()==etiqueta){
			if(pruebas[i].Capacidad()==pruebas[i].NumMarcas()){
				pruebas[i].Reajusta();
			}
				
				pruebas[i](pruebas[i].NumMarcas()+1)=marca;	
				pruebas[i].NumMarcas()=pruebas[i].NumMarcas()+1;
		}
	}

}

/*****************************************************************************/
//Ordena la matrizmarcas segun el criterio especificado por contador
//PRE:
//Si sentido == 1 se ordenara de forma decreciente
//Si sentido == 2 se ordenara de forma creciente
//
//Si criterio == 1 se ordenara por tiempo
//Si criterio == 2 se ordenara por fecha
//Si criterio == 3 se ordenara por licencia

void MatrizMarcas :: Orden(int sentido,int criterio)
{
	for(int i=0;i<num_pruebas;i++){
	
		for(int e=1;e<pruebas[i].NumMarcas();e++)
		
			for(int j=e+1;j<=pruebas[i].NumMarcas();j++){
			
				if(pruebas[i].Ordena(e,j,sentido,criterio)){
									
						//Creamos el objeto transito de tipo registrodemarca
						RegistroDeMarca transito;
						
						transito=pruebas[i](e);
						pruebas[i](e)=pruebas[i](j);
						pruebas[i](j)=transito;
				}
			
			}
	}
}

/*****************************************************************************/
// Método que rellena una MatrizMarcas (que ya existe) a partir de
// los datos presentes en el fichero llamado "nombre". El fichero puede ser
// tanto de texto como binario
//
// ARGUMENTOS:
//	txt(bool)-> indica el tipo de fichero del que queremos leer los datos
//  txt=true-> se escribira en un txt
//  txt=false-> se escribira en un archivo binario

void MatrizMarcas :: LeerMatrizMarcas (const string & nombre, bool txt)
{

	if(txt==true)
		LeerMatrizMarcasTxt(nombre);
	else
		LeerMatrizMarcasBin(nombre);
}


/***********************************************************************/
// Método que guarda el contenido de una "MatrizMarcas" en un fichero 
// llamado "nombre".
// ARGUMENTOS:
//	txt(bool)-> indica el tipo de fichero en el que queremos escribir
//  txt=true-> se escribira en un txt
//  txt=false-> se escribira en un archivo binario

void MatrizMarcas :: EscribirMatrizMarcas (const string & nombre,
bool txt) const
{

	if(txt==true)
		EscribirMatrizMarcasTxt(nombre);
	else
		EscribirMatrizMarcasBin(nombre);

}

/*****************************************************************************/
/*****************************************************************************/
//Método que comprueba si una MatrizMarcas esta vacia o no
//POST: Devuelve un bool, true si esta vacia, false sino esta vacia

bool MatrizMarcas :: EstaVacia (void)
{
	bool vacio;
	
	if(pruebas==nullptr)
		vacio=true;
	else
		vacio= false;
		
	return ((vacio) ? true : false);

}

///////////////////////////////////////////////////////////////////////////////
////////////////////////////OPERADORES/////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/*****************************************************************************/
//OPERADOR <<
/*****************************************************************************/

// Inserta en un flujo de texto de salida el contenido de un
// dato "MatrizMarca".
// Parámetros: out, el flujo de salida.
// m, el dato a insertar.

ostream & operator << (ostream & out, const MatrizMarcas & m)
{
	out<<endl;
	out.setf (ios::fixed);
	out.setf (ios::showpoint);
	
	out << m.num_pruebas<<" ";			//Escribimos el numero de pruebas	
	
	for (int i=0;i<m.num_pruebas;i++)
		out<<m.pruebas[i].Etiqueta_Vec()<<" ";	//Escribimos las etiquetas
	
	out<<endl;
	
	for (int i=0;i<m.num_pruebas;i++)
		for (int j=1; j<=m.pruebas[i].NumMarcas();j++){
			out<<m.pruebas[i].Etiqueta_Vec()<<" "<<m.pruebas[i](j);
			out<<endl;
		}
	
return (out);

}

/*****************************************************************************/
//OPERADOR >>
/*****************************************************************************/

// Lee los datos de un objeto "MatrizMarcas" desde un flujo de texto.

istream & operator >> (istream & in,  MatrizMarcas & m)
{	
	int num_pruebas; 

	// Leer número de pruebas 
	in >> num_pruebas;

	m.ReservaMemoria(num_pruebas);		//Reservamos memoria para el numero 

    string nombre_prueba; 
	
	//Rellenamos las etiquetas
	for (int fila=0; fila<num_pruebas; fila++) {

		in >> nombre_prueba;			//Leemos el nombre de la prueba
		
		m.Etiqueta(fila) = nombre_prueba;	//Introducimos el nombre
	}

	// Leemos y añadimos marcas a "m"

	// Cada elemento de una marca (prueba, fecha, licencia y tiempo) 
	// se lee en un dato string.
	 
	string cad_prueba, cad_fecha, cad_licencia, cad_tiempo;	
	
	in >> cad_prueba; 	// Lectura adelantada
	
    while(!in.eof()){
      	   
        //Obtenemos fecha 
        
        in>> cad_fecha;
        
        //Obtenemos licencia
        
        in >> cad_licencia;
        
        //Obtenemos tiempo
        
        in >> cad_tiempo;
        
        //Inicializamos objeto fecha
       
        Fecha fecha_carrera(cad_fecha);
       
        //Inicializamos objeto tiempo
        
        Tiempo tiempo_carrera(cad_tiempo);
        
        //Inicializamos objeto licencia
        
        Licencia licencia_carrera(cad_licencia);
        
        //Inicializamos un objeto de RegistroDeMarca con los datos extraidos
        RegistroDeMarca registro(fecha_carrera,licencia_carrera,tiempo_carrera);
     
        //Añadimos a la matriz el objeto de RegistroDeMarca
        
        m.Aniade(registro,cad_prueba);
        
        //Obtenemos etiqueta
        
        in >> cad_prueba;
   }  

	return in; 
}

/***********************************************************************/

//OPERADOR =
// Operador de asignación desde otro dato MatrizMarcas
// Parámetros: otro (referencia), objeto que sirve de modelo. 

MatrizMarcas & MatrizMarcas :: operator = (const MatrizMarcas & otro)
{
	
	MatrizMarcas tmp(otro);
	
	if(this!=&otro){		//Se comprueba que las matrices no sean la misma
		
		LiberaMemoria();
		
		ReservaMemoria(otro.num_pruebas);
		
		CopiarDatos(otro);	
		
	}
	
return(*this);
}

//...........................................................................
//OPERADORES DE ACCESO
//...........................................................................

//OPERADOR ()
// Metodo de acceso individual a elementos
// Metodo de lectura/escritura
// PRE: 1 <= fils && 1 <= cols

VectorMarcas & MatrizMarcas :: operator () (const int fila)
{

	return(pruebas[fila-1]);

}

RegistroDeMarca & MatrizMarcas :: operator () (const int fila,const int col)
{
	return(pruebas[fila-1](col-1));
}

//...........................................................................		
//...........................................................................
//OPERADORES ARITMETICOS
//...........................................................................
//...........................................................................

/*****************************************************************************/
//OPERADOR +
//
//VERSION 1
// MatrizMarcas + MatrizMarcas
// Permite la suma de dos matricesmarcas añadiendo los valores de la segunda
// a la primera manteniendo el orden de los datos

MatrizMarcas operator + (const MatrizMarcas & m1 , const MatrizMarcas & m2)
{
	
	//Matriz local para el resultado
	
	MatrizMarcas tmp;
	
	MatrizMarcas otro(m1);
	
	int tam_menor=0;
	
	//1 caso que la m1 sea mayor o igual que m2
	
	//.........................................................................
		
	bool encontrado;
	
	if(m1.num_pruebas>=m2.num_pruebas){
		
		tam_menor=m2.num_pruebas;
		
		tmp=m1;		//Matriz local sera igual a m1
		
		//Procedemos a añadir los valores de m2 en las filas correspondientes de tmp
	
		for(int i=0;i<tam_menor;i++){
			 encontrado=false;
			
			for(int j=0;j<tmp.num_pruebas;j++){
				
				if(m2.pruebas[i].Etiqueta_Vec() == tmp.pruebas[j].Etiqueta_Vec()){
					tmp.pruebas[j]+=m2.pruebas[i];
					encontrado=true;
				}
			}
			
			//Si no tuviesen las mismas pruebas se añaden al final de la matriz
			
			if(!encontrado)		
				tmp.AniadeFila(m2.pruebas[i]);
				
		}
	}
	
	//.......................................................................
	//2 caso que m2 sea mayor que m1
	//.......................................................................
	
	else{
	
		tam_menor=m1.num_pruebas;
		
		tmp=m2;		//Matriz local sera igual a m2
		
	//Procedemos a añadir los valores de m1 en las filas correspondientes de tmp
		for(int i=0;i<tam_menor;i++){
		 	encontrado=false;
			for(int j=0;j<tmp.num_pruebas;j++){
				if(tmp(j+1).Etiqueta_Vec()==otro(i+1).Etiqueta_Vec())
				{	
					tmp.pruebas[j]+=otro.pruebas[i];	
					encontrado=true;
				}
			}
			if(!encontrado)
				tmp.AniadeFila(m1.pruebas[i]);
		}
	}
	
	//Usamos en ambos casos el operador += version -> vectormarcas + vectormarcas
	
	return (tmp);

}

//VERSION 2
// MatrizMarcas + VectorMarcas
// Permite la suma de una MatrizMarcas con un VectorMarcas añadiendo al final de
// la matriz la nueva fila
//..............................................................................

MatrizMarcas operator + (const MatrizMarcas & m1 , const VectorMarcas & v1)
{
	MatrizMarcas tmp(m1);	//Constructor de MatrizMarcas a partir de 
							//VectorMarcas
	tmp.AniadeFila(v1);
	
	return(tmp);			//Operador + version 1
	
}

//VERSION 3
// MatrizMarcas + VectorMarcas
// Permite la suma de un VectorMarcas con una MatrizMarcas con un  añadiendo al 
// inicio de la matriz la nueva fila
//.............................................................................

MatrizMarcas operator + ( const VectorMarcas & v1,const MatrizMarcas & m1)
{
	MatrizMarcas tmp(m1);
	
	tmp.InsertarFila(v1,tmp.num_pruebas);	//Insertamos el VectorMarcas en la
											//ultima fila
	return(tmp);
	
}

//Operador -
// Metodo de MatrizMarcas - string(licencia)
// Elimina todas las marcas cuyo campo licencia sea igual al valor dado
//.............................................................................

MatrizMarcas MatrizMarcas :: operator - (string licencia)
{
	MatrizMarcas tmp((*this));
	
		//USO DEL OPERADOR ()
		for(int i=0;i<num_pruebas;i++)
			tmp(i+1)=tmp(i+1)-licencia;	
		
	return(tmp);
}

//.............................................................................
//OPERADORES COMBINADOS
//.............................................................................

//Operador +=

//VERSION 1
// MatrizMarcas += MatrizMarcas
// Permite la suma de dos MatrizMarcas las filas de la matriz explicita se 
// añadiran al final de las filas de la matriz implicita
//

MatrizMarcas & MatrizMarcas :: operator += (const MatrizMarcas & m1)
{
	(*this) = (*this) + m1;	//Operador binario + (Version 1)
	
	 return (*this);
}

/*****************************************************************************/

//VERSION 2 : MatrizMarcas += VectorMarcas
//
// Permite la suma de una MatrizMarcas y un VectorMarcas
// Se añade una nueva fila al final de la MatrizMarcas implicta

MatrizMarcas & MatrizMarcas :: operator += (const VectorMarcas & v1)
{

	(*this) = (*this) + v1;	//Operador binario + (Version 2)
	
	return (*this);

} 

/*****************************************************************************/
//Operador -=

//VERSION 1 : MatrizMarcas -= string(licencia)
//
// Permite la eliminacion de una marca a partir de su licencia
// Se eliminara una marca de la matriz implicita


MatrizMarcas & MatrizMarcas :: operator -= (const string licencia)
{

	(*this) = (*this) - licencia;	//Operador binario - (Version 1)
	
	return (*this);

} 


/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
//METODOS PRIVADOS	
//////////////////////////////////////////////////////////////////////////////

// Libera memoria
void MatrizMarcas :: LiberaMemoria(void)
{
	if (pruebas!=nullptr) {
			
			//delete [] pruebas;
			
			for(int f=0;f<num_pruebas;f++)
				pruebas[f].DestruyeVector();
			
			// Liberar cada una de las filas
 			// Liberar el vector de punteros
 			
 			num_pruebas=0;			
 	
 	}
 }


/***********************************************************************/

// Pide memoria para guardar "nfilas" datos	
void MatrizMarcas :: ReservaMemoria (int nfilas)
{
	pruebas=new VectorMarcas[nfilas];
		
	num_pruebas=nfilas;	
}	

/*****************************************************************************/

// Copiar datos desde otro objeto de la clase
// PRE: Se ha reservado memoria para los datos

void MatrizMarcas :: CopiarDatos (const MatrizMarcas & otro)
{
	
	// Copia los valores de los campos privados desde "otro" 
	
	num_pruebas=otro.num_pruebas;
	
	// Copiar los valores de los datos
	for(int f=0; f<num_pruebas; f++){
		pruebas[f].Etiqueta_Vec()=otro.pruebas[f].Etiqueta_Vec();
		pruebas[f]=otro.pruebas[f];
	}

		
}

/*****************************************************************************/
// Método que rellena una MatrizMarcas (que ya existe) a partir de
// los datos presentes en el fichero de texto llamado "nombre".
//
// Este método NO es un constructor: el objeto sobre el que se aplica
// ya existe, por lo tanto, lo primero que debe hacerse es "limpiarlo"
// y después, leer los valores a guardar en la MatrizMarcas de los datos 
// almacenados en el fichero llamado "nombre"

void MatrizMarcas :: LeerMatrizMarcasTxt (const string & nombre)
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
	

	if (!strcmp(cadena, "MARCAS")) {	// CORRECTO --> Seguir leyendo
		
		fi.getline(cadena, MAX_CADENA);	// Lectura Adelantada
		
		while (cadena[0]=='#') 
			fi.getline(cadena,MAX_CADENA);		// Nueva lectura
	
		fi >> (*this);
	}
	
	else {
		cerr << "Error en fichero " << nombre << ": ";
		cerr << "No es un fichero MARCAS" << endl; 
	}

	fi.close();

}


/***********************************************************************/
// Método que guarda el contenido de una "MatrizMarcas" en un fichero de 
// texto llamado "nombre".

void MatrizMarcas:: EscribirMatrizMarcasTxt (const string & nombre) const
{
	if(pruebas!=nullptr)
	{
		ofstream fo (nombre);

		if (!fo) {
			cerr << "Error: no pudo crearse " << nombre << endl;
			exit (1);
		}

		fo.setf (ios::fixed);
		fo.setf (ios::showpoint);
	
		fo << "MARCAS" << endl;

		fo << (*this); 

		fo.close();
	}
	else
		cerr << "Matriz vacia no se creo nuevo fichero"<<endl;

}

/*****************************************************************************/
// Método que guarda el contenido de una "MatrizMarcas" en un fichero de 
// binario llamado "nombre".
		
void MatrizMarcas :: EscribirMatrizMarcasBin (const string & nombre) const
{		
	if(pruebas!=nullptr)
	{
		ofstream fo (nombre,ios::binary);	//Creamos el archivo en formato
											//binario
		if (!fo) {
			cerr << "Error: no pudo crearse " << nombre << endl;
			exit (1);
		}
		
		//Escribimos la palabra mágica
		
		fo << "MARCAS_BIN" << endl;
	
		//Escribmos el numero de pruebas registradas
		
		int numero_de_pruebas;
		
		numero_de_pruebas=num_pruebas;
		
		fo.write(reinterpret_cast<char*> (&numero_de_pruebas), sizeof(int));
		
		//Procedemos a escribir la longitud de cada etiqueta 
		//y la propia etiqueta de cada prueba
			
		for(int i=0;i<num_pruebas;i++){
		
			string nombre_prueba;
			
			nombre_prueba=pruebas[i].Etiqueta_Vec();
			
			int longitud_prueba=nombre_prueba.size();
			
			//Escribimos la longitud de la etiqueta
			
			fo.write (reinterpret_cast<char*> (&longitud_prueba), sizeof(int));
			
			//Escribimos la etiqueta
			fo.write (reinterpret_cast<const char*> (nombre_prueba.c_str()),
			 nombre_prueba.size());
		}
		
		//Una vez escritos el numero de pruebas y las etiquetas de las pruebas
		//Pasamos a escribir los datos
		
		for(int i=0;i<num_pruebas;i++){	
			
			for(int j=1;j<=pruebas[i].NumMarcas();j++){
				
				string nombre_prueba=pruebas[i].Etiqueta_Vec();
				
				//Calculamos la longitud de la etiqueta
				int longitud_prueba=nombre_prueba.size();
				
				fo.write (reinterpret_cast<char*> (&longitud_prueba), sizeof(int));
				
				//Escribimos la etiqueta
				
				fo.write (reinterpret_cast<const char*> (nombre_prueba.c_str()),
						  longitud_prueba);
				
				/*************************************************************/
				Fecha la_fecha=pruebas[i](j).GetFecha();
				
				//Escribimos la fecha
				
				fo.write(reinterpret_cast<char*>(&la_fecha),sizeof(Fecha));
				
				/*************************************************************/
				
				string la_licencia=pruebas[i](j).GetLicencia().Get_licencia();
				
				longitud_prueba=la_licencia.size();
				
				fo.write (reinterpret_cast<char*> (&longitud_prueba), sizeof(int));
				
				//Escribimos la licencia
				
				fo.write(reinterpret_cast<const char*>(la_licencia.c_str()),
						longitud_prueba);
			
				/*************************************************************/
				
				Tiempo el_tiempo=pruebas[i](j).GetTiempo();
				
				//Escribimos el tiempo
				
				fo.write(reinterpret_cast<char*>(&el_tiempo),sizeof(Tiempo));
			}
		}
		
		fo.close();
	}
	else
		cerr << "Matriz vacia no se creo nuevo fichero"<<endl;
	
}

/*****************************************************************************/
// Método que rellena una MatrizMarcas (que ya existe) a partir de
// los datos presentes en el fichero binario llamado "nombre".
//
// Este método NO es un constructor: el objeto sobre el que se aplica
// ya existe, por lo tanto, lo primero que debe hacerse es "limpiarlo"
// y después, leer los valores a guardar en la MatrizMarcas de los datos 
// almacenados en el fichero llamado "nombre"

void MatrizMarcas :: LeerMatrizMarcasBin (const string & nombre)
{

	// Limpiar el objeto: Liberar memoria reservada previamente
	LiberaMemoria ();
	
	ifstream fi (nombre,ios::binary);
	if (!fi) {
		cerr << "Error: no puede abrirse " << nombre << endl;
		exit (1);
	}

	const int MAX_CADENA = 256;
	
	string cadena;	
	
	getline(fi,cadena);			// Lectura palabra mágica
		
	if(cadena == "MARCAS_BIN"){
		
		//Guardamos la posicion inicial en la que estamos antes de leer los
		//comentarios
		int pos_inicial = fi.tellg();
		
		getline(fi,cadena);		//Lectura adelantada
		
		//Leemos los comentarios
		while (cadena[0]=='#') {
			
			pos_inicial = fi.tellg();
			getline(fi,cadena);
		}
		
		int posicion_actual = fi.tellg();
		
		//Restamos para obtener	las posiciones a retroceder
		int posicion_final = posicion_actual - pos_inicial; 
		
		//Retrocedemos hasta al final de los comentarios, sino hubiese ningun
		//comentario iriamos al principio de los datos del fichero
		 
		fi.seekg(-posicion_final, ios::cur);	
		
		//Comenzamos a leer las pruebas
												
		int numero_de_pruebas;
	
		fi.read(reinterpret_cast<char*> (&numero_de_pruebas), sizeof(int));
	
		//Obtenemos el numero de pruebas
	
		ReservaMemoria(numero_de_pruebas);
	
		//Una vez reservada memoria obtenemos las etiquetas de las pruebas
	
		char etiqueta_prueba[MAX_CADENA];
	
		int tamanio_prueba;

		for (int fila=0; fila<numero_de_pruebas; fila++) {
		
		//Leemos el tamaño de la etiqueta
		
			fi.read(reinterpret_cast<char*> (&tamanio_prueba), sizeof(int));
		
		//Leemos la etiqueta
		
			fi.read(reinterpret_cast<char*> (etiqueta_prueba),tamanio_prueba);
		
			etiqueta_prueba[tamanio_prueba] = '\0';
		
			pruebas[fila].Etiqueta_Vec()=etiqueta_prueba;
		}
	
	///////////////////////////////////////////////////////////////////////////
	
		//Ya tendriamos la MatrizMarcas con sus filas reservadas y con sus 
		//respectivas etiquetas introducidas guardadas
	
		//Obtenemos la informacion de las marcas a continuacion

		//Hacemos lectura adelantada
	
		int p;	
		
		//Leemos tam de la etiqueta
		
		fi.read(reinterpret_cast<char*> (&p), sizeof(int));
	
		char cad_prueba[MAX_CADENA];
		
		//Leemos la etiqueta
	
		fi.read(reinterpret_cast<char*> (cad_prueba), p);
	
		cad_prueba[p] = '\0';
	
		while(!fi.eof()){
		
			int q;

			//Procedemos a leer la fecha
	
			char cad_fecha[MAX_CADENA];
	
			Fecha fecha_carrera;
	
			fi.read(reinterpret_cast<char*> (&fecha_carrera), sizeof(Fecha));
	
			//Procedemos a leer la licencia 
	
			fi.read(reinterpret_cast<char*> (&q), sizeof(int));

			char cad_licencia[MAX_CADENA];
		
			fi.read(reinterpret_cast<char*> (cad_licencia), q);
	
			cad_licencia[q] = '\0';
	
			Licencia licencia_carrera(cad_licencia);

			//Procedemos a leer el tiempo
	
			Tiempo tiempo_carrera;
			fi.read(reinterpret_cast<char*> (&tiempo_carrera), sizeof(Tiempo));
	
			RegistroDeMarca registro(fecha_carrera,licencia_carrera,tiempo_carrera);
     
    		//Añadimos a la matriz el objeto de RegistroDeMarca
      
    		(*this).Aniade(registro,cad_prueba);

			//Obtenemos el nombre de la prueba
	
			fi.read(reinterpret_cast<char*> (&p), sizeof(int));
		
			fi.read(reinterpret_cast<char*> (cad_prueba), p);
	
			cad_prueba[p] = '\0';
		
		}
		
	}else {
		cerr << "Error en fichero " << nombre << ": ";
		cerr << "No es un fichero MARCAS_BIN" << endl; 
	}
	
	fi.close();
}

/*****************************************************************************/
//Permite añadir una fila al final de la MatrizMarcas, para ello
//se creara una nueva matriz de las dimensiones requeridas, se copiaran
//los datos de la matriz y se añadirá al final los datos de la nueva fila.
//Parametros:
// v(VectorMarcas) fila que queremos insertar al final

void MatrizMarcas :: AniadeFila (const VectorMarcas & v)
{
	
	MatrizMarcas tmp;
	
	tmp.ReservaMemoria(num_pruebas+1);
	
	tmp.CopiarDatos(*this);
	
	tmp.num_pruebas=tmp.num_pruebas+1;
	
	tmp.pruebas[tmp.num_pruebas-1]=v;
	
	(*this)=tmp;
}

/*****************************************************************************/

//Permite insertar una fila en la posicion deseada de la MatrizMarcas
//Parametros:
// posicion(int) indica la posicion donde deseamos insertar la nueva fila
// v(VectorMarcas) fila que deseamos insertar
//PRE: posicion >= 1 & posicion <= num_pruebas-1

void MatrizMarcas :: InsertarFila (const VectorMarcas & v, int posicion)
{
	
	MatrizMarcas tmp;
	tmp.ReservaMemoria(num_pruebas+1);
	
	for(int f=0;f<posicion-1;f++){
		tmp.pruebas[f].Etiqueta_Vec()=pruebas[f].Etiqueta_Vec();
		tmp.pruebas[f]=pruebas[f];
	}
	tmp.pruebas[num_pruebas]=v;

	for(int f=num_pruebas;f<num_pruebas;f++){
		tmp.pruebas[f+1].Etiqueta_Vec()=pruebas[f].Etiqueta_Vec();
		tmp.pruebas[f+1]=pruebas[f];
	}
	
	(*this)=tmp;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


    
