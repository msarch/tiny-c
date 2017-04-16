/*
 ============================================================================
 Name        : Stamp.c
 Author      : ms
 Version     :
 Copyright   : ms 2008
 Description :   
	glisser sur l'exe un ou des fichiers (une cinquantaine maxi ??)
	pour le(s)renommer d'après le nom de l'exe.
	ou glisser un dossier pour renommer tout son contenu.
  
	le nom du exe peut etre quelconque, avec plusieurs exceptions, par ex :
	"caps.exe" =>  capitalise le nom du fichier
	"timestamp_.exe"  => ajoute la date avant le nom des fichiers
	"_timestamp.exe"  => ajoute la date après le nom des fichiers
	"no_extension.exe" => remove extension 
	"extension_iii" => change les extensioons en .iii
	double clic sans fichier  => affiche l'aide
 
 Compilation : gcc stamp.c -o  stamp.exe -ansi -fexpensive-optimizations -O3
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

char *p;
char *this_exe_long_filename;
char *this_exe_path_only;
char *this_exe_name_only;
char *this_exe_suffix_only;
char *longfilename;
char *newname;
char *p; 
char *tmp;
int i;

int main(int argc, char *argv[])
{


    this_exe_long_filename = argv[0];
    printf("Nom complet du programme : %s.\n",this_exe_long_filename);
    /* Affiche le nom du programme : */    

    *this_exe_long_filename = tout_en_minuscule(this_exe_long_filename);
    printf("Nom en minuscules : %s.\n", this_exe_long_filename);
    /* Affiche le nom du programme en minuscule: */

    *this_exe_long_filename = tout_en_majuscule(this_exe_long_filename);
    printf("Nom en majuscules : %s.\n", this_exe_long_filename);
   /* Affiche le nom du programme en majuscule: */ 
	
	for (i=1; i<argc; ++i)
	{
		printf("Argument %d : %s.\n",i, argv[i]);
		printf ("Nom complet du programme : %s.\n" ,argv[i]);
		printf ("%s" ,strrchr(argv[i],'\\'));
	}

/* 	
 *      *this_exe_name_only= name_only(this_exe_long_filename);
 *      printf ("Nom court du programme :%s\n" ,this_exe_name_only);
 */




    
 
	/* Affiche les arguments de la ligne de commande : */

        system("PAUSE");
        return 0;
        /* Tout s'est bien passé : on renvoie 0 ! */      

	}





int tout_en_minuscule(char*tmp)
{
	for( i = 0; tmp[ i ]; i++) 
  tmp[ i ] = tolower( tmp[i]);
  return *tmp;      
}


int tout_en_majuscule(char*tmp)
{
	for( i = 0; tmp[ i ]; i++) 
  tmp[ i ] = toupper( tmp[i]);
  return *tmp;      
}