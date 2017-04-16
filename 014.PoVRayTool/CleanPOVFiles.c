
#include <stdio.h>

int main(int argc, char *argv[])
  {
    int i;
    int j = 1;
    char c;
    char *filename = "C:\\output.txt";
// ici : combiner avec le path du folder de l'appli
    FILE *fin;
    FILE *fout;
 
    if ((fout= fopen(filename,"wt"))== NULL )
      { 
        printf("Impossible d'ouvrir le fichier: ' %s '. \n", filename);
        getch();
        exit(1); 
      }
/* lignes suivantes pour debug */
        printf("\nLe fichier:' %s ' est ouvert.\n", filename);
    getch();
  
    for (i = 1; i < argc; i++) 
      { printf("parameter %d \n value is %s\n", i, argv[i]); }
    getch();
/* fin code pour debug  */


    while (j < argc)
      {
/* lignes suivantes pour debug */     
         printf("parameter %d value is %s\n", j, argv[j]); 
/* fin code pour debug */
        if (( fin = fopen(argv[j],"r"))== NULL )
          { 
            printf("Impossible d'ouvrir le fichier: %s.\n",argv[j]);
            getch();
            exit(1); 
          } 
/* lignes suivantes pour debug */         
        printf("Le fichier:' %s ' est ouvert.\n", argv[j]);
        getch();  
/* fin code pour debug */         
        fprintf(fout,"\n\\\\objet %d \n",j); //numero objet
        while ((c = fgetc(fin)) != EOF){
          putc(c,fout); /* write to fout file */
/* lignes suivantes pour debug */               
          putchar(c); /* copy the character on the screen */
/* fin code pour debug */
          printf("\n");
          }
        fclose(fin);

        j++;
      } 
      fclose (fout);
      printf("Le fichier: %s est fermé.\n", filename);
      getch();
      return 0;
  }

