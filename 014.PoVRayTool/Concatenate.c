// Description : Concatenation de fichiers textes 
// Author : m.s. 
// Date : Mai 2008




#include <stdio.h>
    int i;
    int count = 1;
    char c;
    char *filename = "C:\\output.txt";
// ici : combiner avec le path du folder de l'appli
    FILE *fin;
    FILE *fout;
    
int main(int argc, char *argv[])
  {
          
if (argc == 1)
   {
printf(" \nDescription : Concatenation de fichiers textes \n");
printf(" Author : m.s.\n"); 
printf(" Date : Mai 2008 \n");
printf(" \nWill combine any text file (dropped or argument) \n");
printf("into a new destination file : %s \n", filename);
        getch();
        exit(1);
     }       


// ouverture du fichier destination
    if ((fout= fopen(filename,"wt"))== NULL )
      { 
        printf("Impossible d'ouvrir le fichier: ' %s '. \n", filename);
        getch();
        exit(1); 
      }
// pour chacun des fichiers sources
    while (count < argc)
      {
// ouverture d'un fichier source
        if (( fin = fopen(argv[count],"r"))== NULL )
          { 
            printf("Impossible d'ouvrir le fichier: %s.\n",argv[count]);
            getch();
            exit(1); 
          } 
// copie des caracteres jusqu'à la fin du fichier
        while ((c = fgetc(fin)) != EOF){
          putc(c,fout); /* write to fout file */
          }  
// fermeture fichier source en cours  
        fclose(fin);
        count++; 
      } 
// fermeture fichier destination en cours  
      fclose (fout);
      printf("%d fichiers assembles dans le fichier :\n %s",count-1, filename);
      getch();
      return 0;
  }

