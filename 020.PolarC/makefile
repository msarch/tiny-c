# makefile :2008-09-07.�5
# projet : GrossTon
# ce makefile simple ne gere pas les fichiers d'en-tete .h
# il compile automatiquement tous les fichier .c du repertoire

CC=gcc
EXEC=PolarC
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
	
	
