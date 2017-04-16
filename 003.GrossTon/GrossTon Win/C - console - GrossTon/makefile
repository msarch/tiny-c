# makefile :2008-09-07.µ5
# projet : GrossTon
# ce makefile simple ne gere pas les fichiers d'en-tete .h
# il compile automatiquement tous les fichier .c du repertoire

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
	
	
