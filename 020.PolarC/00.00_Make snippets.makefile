    
1.Makefile simple, pour 1 fichier
_________________________________

#
# �5, septembre 2008
# Makefile simple, pour 1 fichier
#

CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS= -lconio
EXEC=grosston
SRC= grosston.c

# Pour chaque fichier .c contenu dans SRC nous ajoutons � OBJ un fichier de m�me nom mais portant l'extension .o :

OBJ= $(SRC:.c=.o)

# all : g�n�ralement la premi�re cible du fichier, elle regroupe dans ces d�pendances l'ensemble des ex�cutables � produire :

all: $(EXEC)

$(EXEC): $(OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS)
	
# Make permet �galement de cr�er des r�gles g�n�riques (par exemple construire un .o � partir d'un .c) qui se verront appel�es par d�faut. Une telle r�gle se pr�sente sous la forme suivante : %.o: %.c
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
clean:
	rm -rf *.o
  





2.Makefile conditionel pour debug, pour 1 fichier.
___________________________________________________

#
# �5, septembre 2008
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
# �5, septembre 2008
# makefile simple, (ne gere pas les fichiers d'en-tete .h)
# compile automatiquement tout fichier .c du repertoire courant
#

CC=gcc
EXEC=grosston
LDFLAGS=-lconio
CFLAGS=-W -Wall -ansi -pedantic

# il peut �tre utile de g�rer la liste des fichiers sources de mani�re automatique; Pour ce faire nous allons faire remplir la variable SRC avec les diff�rents fichiers .c du r�pertoire (attention toutefois � la gestion des d�pendances vis � vis des fichiers d'ent�te .h) :

SRC= $(wildcard *.c)

# Pour chaque fichier .c contenu dans SRC nous ajoutons � OBJ un fichier de m�me nom mais portant l'extension .o :

OBJ= $(SRC:.c=.o)

# all : g�n�ralement la premi�re cible du fichier, elle regroupe dans ces d�pendances l'ensemble des ex�cutables � produire :

all: $(EXEC)

$(EXEC): $(OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS) 
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) 
	
# il existe une cible particuli�re nomm�e .PHONY dont les d�pendances sont syst�matiquement reconstruites :

.PHONY: clean mrproper

#clean : permet de supprimer tout les fichiers interm�diaires :

clean:
	@rm -rf *.o
	
# mrproper : supprime tout ce qui peut �tre r�g�n�r� et permet une reconstruction compl�te du projet :

mrproper: clean
	@rm -rf $(EXEC)






4.Makefile simple, compile automatiquement le repertoire 'src'
______________________________________________________________

##############################################
# �5, septembre 2008
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
# �5 septembre 2008
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
	
# si les sources sont rang�es dans le repertoire /src, utiliser:
# SRC= $(wildcard $(SRC_DIR)/*.c)
# sinon pour des sources � la racine, utiliser :
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: create_directories $(EXEC) 

$(EXEC): $(OBJ) 
	$(CC) -o $(BIN_DIR)/$@ $(OBJ_DIR)/$^  $(INCLUDES) $(LIBS)
%.o: %.c
	$(CC) -o $(OBJ_DIR)/$@ -c $< $(CFLAGS) 

# creation pr�alable des sous-repertoires
# - devant mkdir (-mkdir) fait en sorte que les erreurs seront ignor�es
# si par exemple les dossiers existent d�j�.
create_directories: 
	-mkdir $(BIN_DIR) 
	-mkdir $(OBJ_DIR) 
#	-mkdir $(SRC_DIR)

.PHONY: clean propre

clean:
	@rm -rf $(OBJ_DIR)/*.o
	
propre: clean
	@rm -rf $(BIN_DIR)/$(EXEC).exe







