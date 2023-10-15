#############################################################################
#
# METODOLOGIA DE LA PROGRAMACION
#
# Autor: Alonso Doña Martinez
#
# makefile.mak
#
# makefile para el proyecto 
#
#############################################################################

SESION = "Proyecto"

HOME = .
HOME_CLASES_UTILS = .

BIN = $(HOME)/bin
SRC = $(HOME)/src
OBJ = $(HOME)/obj
LIB = $(HOME)/lib
INCLUDE = $(HOME)/include

SRC_CLASES_UTILS =  $(HOME_CLASES_UTILS)/src
OBJ_CLASES_UTILS =  $(HOME_CLASES_UTILS)/obj
LIB_CLASES_UTILS =  $(HOME_CLASES_UTILS)/lib
INCLUDE_CLASES_UTILS = $(HOME_CLASES_UTILS)/include

#................................................
all:  preambulo \
      $(BIN)/RankingMarcas_Fase10 \
      clean \
      final

#................................................
preambulo:
	@echo
	@echo ------------------------------------------------------------
	@echo $(SESION)	
	@echo
	@echo METODOLOGÍA DE LA PROGRAMACIÓN
	@echo
	@echo Autor: Alonso Doña Martinez
	@echo ------------------------------------------------------------
	@echo

#................................................
final: 
	@echo

#................................................
# EJECUTABLES

$(BIN)/RankingMarcas_Fase10 : \
           $(OBJ)/RankingMarcas_Fase10.o \
           $(OBJ)/Utils.o $(LIB)/libProyecto.a
	@echo 
	@echo Creando ejecutable:RankingMarcas_Fase10 
	@echo 
	g++ -o $(BIN)/RankingMarcas_Fase10 \
	       $(OBJ)/RankingMarcas_Fase10.o \
	       $(OBJ)/Utils.o \
	       -L$(LIB) -lProyecto -I$(INCLUDE)
	              
#................................................
# OBJETOS 
	          	          
$(OBJ)/RankingMarcas_Fase10.o : $(SRC)/RankingMarcas_Fase10.cpp
	@echo 
	@echo Creando objeto: RankingMarcas_Fase10.o
	@echo 
	
	g++ -c -o $(OBJ)/RankingMarcas_Fase10.o \
	          $(SRC)/RankingMarcas_Fase10.cpp -I$(INCLUDE) -std=c++14

$(OBJ)/Utils.o : $(SRC)/Utils.cpp
	@echo
	@echo Creando objeto: Utils.o
	@echo 	
	g++ -c -o $(OBJ)/Utils.o \
	          $(SRC)/Utils.cpp -I$(INCLUDE) -std=c++14


#................................................

#................................................
# BIBLIOTECAS

# (Funciones para procesar una Matriz Dinamica) ........................

$(LIB)/libProyecto.a : $(OBJ)/Tiempo.o $(OBJ)/RegistroDeMarcas.o $(OBJ)/Fecha.o \
						$(OBJ)/MatrizMarcas.o $(OBJ)/VectorMarcas.o $(OBJ)/Licencia.o
	@echo
	@echo 
	@echo Creando biblioteca: libProyecto.a 
	@echo  
	ar rvs $(LIB)/libProyecto.a \
		   $(OBJ)/Tiempo.o \
		   $(OBJ)/Fecha.o \
		   $(OBJ)/Licencia.o \
		   $(OBJ)/RegistroDeMarcas.o \
		   $(OBJ)/MatrizMarcas.o \
		   $(OBJ)/VectorMarcas.o

$(OBJ)/Tiempo.o : $(SRC)/Tiempo.cpp $(INCLUDE)/Tiempo.h
	@echo 
	@echo Creando objeto: Tiempo.o
	@echo 
	g++ -c -o $(OBJ)/Tiempo.o $(SRC)/Tiempo.cpp -I$(INCLUDE) -std=c++14
	

$(OBJ)/Licencia.o : $(SRC)/Licencia.cpp $(INCLUDE)/Licencia.h
	@echo 
	@echo Creando objeto: Licencia.o
	@echo 
	g++ -c -o $(OBJ)/Licencia.o $(SRC)/Licencia.cpp -I$(INCLUDE) -std=c++14
	

$(OBJ)/Fecha.o : $(SRC)/Fecha.cpp $(INCLUDE)/Fecha.h
	@echo 
	@echo Creando objeto: Fecha.o
	@echo 
	g++ -c -o $(OBJ)/Fecha.o $(SRC)/Fecha.cpp -I$(INCLUDE) -std=c++14

$(OBJ)/RegistroDeMarcas.o : $(SRC)/RegistroDeMarcas.cpp \
							$(INCLUDE)/RegistroDeMarcas.h
	@echo 
	@echo Creando objeto: RegistroDeMarcas.o
	@echo 
	g++ -c -o $(OBJ)/RegistroDeMarcas.o $(SRC)/RegistroDeMarcas.cpp \
			-I$(INCLUDE) -std=c++14
			
$(OBJ)/MatrizMarcas.o : $(SRC)/MatrizMarcas.cpp \
							$(INCLUDE)/MatrizMarcas.h
	@echo 
	@echo Creando objeto: MatrizMarcas.o
	@echo 
	g++ -c -o $(OBJ)/MatrizMarcas.o $(SRC)/MatrizMarcas.cpp \
			-I$(INCLUDE) -std=c++14

$(OBJ)/VectorMarcas.o : $(SRC)/VectorMarcas.cpp \
							$(INCLUDE)/VectorMarcas.h
	@echo 
	@echo Creando objeto: VectorMarcas.o
	@echo 
	g++ -c -o $(OBJ)/VectorMarcas.o $(SRC)/VectorMarcas.cpp \
			-I$(INCLUDE) -std=c++14
		
#................................................

#................................................
# LIMPEZA

clean: clean-objs clean-libs

clean-objs:
	@echo
	@echo Borrando objetos de la sesion de practicas $(SESION)...
	@echo
	
	-rm $(OBJ)/MatrizMarcas.o
	-rm $(OBJ)/VectorMarcas.o  
	-rm $(OBJ)/Fecha.o
	-rm $(OBJ)/Tiempo.o
	-rm $(OBJ)/RegistroDeMarcas.o
	-rm $(OBJ)/RankingMarcas_Fase10.o
	-rm $(OBJ)/Utils.o
	-rm $(OBJ)/Licencia.o
	@echo ...Borrados objetos del $(SESION)
	@echo 

clean-libs:
	@echo Borrando bibliotecas ...

	-rm $(LIB)/libProyecto.a

	@echo ...Borradas bibliotecas 
	@echo 


clean-bins : 
	@echo Borrando ejecutables de la sesion de practicas $(SESION)...

	@echo ...Borrados ejecutables de la sesion de practicas $(SESION)

mr.proper:  clean-objs clean-libs clean-bins

