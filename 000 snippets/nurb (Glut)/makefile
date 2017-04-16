############################################################
# µ5 septembre 2008
# makefile pour essais glut
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

