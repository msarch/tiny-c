    
1.Makefile simple, pour 1 fichier
_________________________________

#
# µ5, septembre 2008
# Makefile simple, pour 1 fichier
#

CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS= -lconio
EXEC=grosston
SRC= grosston.c

# Pour chaque fichier .c contenu dans SRC nous ajoutons à OBJ un fichier de même nom mais portant l'extension .o :

OBJ= $(SRC:.c=.o)

# all : généralement la première cible du fichier, elle regroupe dans ces dépendances l'ensemble des exécutables à produire :

all: $(EXEC)

$(EXEC): $(OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS)
	
# Make permet également de créer des règles génériques (par exemple construire un .o à partir d'un .c) qui se verront appelées par défaut. Une telle règle se présente sous la forme suivante : %.o: %.c
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
clean:
	rm -rf *.o
  





2.Makefile conditionel pour debug, pour 1 fichier.
___________________________________________________

#
# µ5, septembre 2008
# Makefile conditionel pour debug, pour 1 fichier
#

DEBUG=yes

CC=gcc
LDFLAGS=-lconio
EXEC=grosston
SRC= grosston.c
OBJ= $(SRC:.c=.o)

# definition des flags de compilation suivant la valeur de debug:

ifeq ($(DEBUG),yes)

# flags de compilation en mode debug :
CFLAGS=-W -Wall -ansi -pedantic -g3 -ggdb
else

# flags de compilation en mode release :
CFLAGS=-W -Wall -ansi -pedantic
endif


all: $(EXEC)

$(EXEC): $(OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS) 
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) 
clean:
	rm -rf *.o





3.Makefile simple, compile automatiquement le repertoire courant
_________________________________________________________________

#
# µ5, septembre 2008
# makefile simple, (ne gere pas les fichiers d'en-tete .h)
# compile automatiquement tout fichier .c du repertoire courant
#

CC=gcc
EXEC=grosston
LDFLAGS=-lconio
CFLAGS=-W -Wall -ansi -pedantic

# il peut être utile de gérer la liste des fichiers sources de manière automatique; Pour ce faire nous allons faire remplir la variable SRC avec les différents fichiers .c du répertoire (attention toutefois à la gestion des dépendances vis à vis des fichiers d'entête .h) :

SRC= $(wildcard *.c)

# Pour chaque fichier .c contenu dans SRC nous ajoutons à OBJ un fichier de même nom mais portant l'extension .o :

OBJ= $(SRC:.c=.o)

# all : généralement la première cible du fichier, elle regroupe dans ces dépendances l'ensemble des exécutables à produire :

all: $(EXEC)

$(EXEC): $(OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS) 
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) 
	
# il existe une cible particulière nommée .PHONY dont les dépendances sont systématiquement reconstruites :

.PHONY: clean mrproper

#clean : permet de supprimer tout les fichiers intermédiaires :

clean:
	@rm -rf *.o
	
# mrproper : supprime tout ce qui peut être régénéré et permet une reconstruction complète du projet :

mrproper: clean
	@rm -rf $(EXEC)






4.Makefile simple, compile automatiquement le repertoire 'src'
______________________________________________________________

##############################################
# µ5, septembre 2008
# makefile simple, ne gere pas les fichiers d'en-tete .h
# compile automatiquement tous fichier .c du repertoire 'src'
##############################################


CC=gcc
EXEC=ascii
INCLUDES=-I/project/include -I/general/include
LDFLAGS=-lconio
CFLAGS=-Wall -ansi -pedantic $(INCLUDES)
# sous repertoire pour les fichiers source
SRC_DIR=src

SRC= $(wildcard $(SRC_DIR)/*.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)
$(EXEC): $(OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS) 
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) 


.PHONY: clean mrproper

clean:
	@rm -rf *.o
	
mrproper: clean
	@rm -rf $(EXEC)
	
	
5.Makefile simple, utilise des sous-repertoires src, bin, obj.
______________________________________________________________

############################################################
# µ5 septembre 2008
# makefile pour essais glut
# utilise des sous repertoires
############################################################

CC=gcc
EXEC=app
# INCLUDES=-I/project/include -I/general/include
LIBS := -lglut32 -lglu32 -lopengl32 -lgdi32 -lwinmm -mwindows
CFLAGS= -Wall -ansi -pedantic 

OBJ_DIR=obj
BIN_DIR=bin
SRC_DIR=src
	
# si les sources sont rangées dans le repertoire /src, utiliser:
# SRC= $(wildcard $(SRC_DIR)/*.c)
# sinon pour des sources à la racine, utiliser :
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: create_directories $(EXEC) 

$(EXEC): $(OBJ) 
	$(CC) -o $(BIN_DIR)/$@ $(OBJ_DIR)/$^  $(INCLUDES) $(LIBS)
%.o: %.c
	$(CC) -o $(OBJ_DIR)/$@ -c $< $(CFLAGS) 

# creation préalable des sous-repertoires
# - devant mkdir (-mkdir) fait en sorte que les erreurs seront ignorées
# si par exemple les dossiers existent déjà.
create_directories: 
	-mkdir $(BIN_DIR) 
	-mkdir $(OBJ_DIR) 
#	-mkdir $(SRC_DIR)

.PHONY: clean propre

clean:
	@rm -rf $(OBJ_DIR)/*.o
	
propre: clean
	@rm -rf $(BIN_DIR)/$(EXEC).exe







