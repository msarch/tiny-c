/*    TODO (#1#):
      le default de choose1 réecrit les 3 lignes filtrer les mauvaises touches et biper seulemnt
      dans "sortie : attente puis quitte puis ouvre gt.txt
      dans "saveresult" ecriture dans le fichier (ou pas) à la suite
      checker l'input de volume detecter 'esc' et les filtrer les non numeriques
      les 4 lignes du haut sont dediées à la commande (ou 4 lignes en bas ???
*/

#define VERSION "2005 11 07"  /* remplacer par la date de la compil du programme en 10 caracteres exactement */
include <stdio.h>
include <math.h>

void intro();
void calcul();
void plotresult();
void choose1();
void saveresult();
void sortie();

float volume,coeff,grosston;
int choice1;
char reponse;

void intro(){

printf("calcul du tonnage brut                                           ");

printf("VPLP ");
printf(VERSION);
printf("\n");
printf("        GT = V*(0.2+(0.02*(Log10(V))), avec V (m3) volume des espaces fermes.  \n");
printf("        (formule du tonnage brut suivant la convention internationale de 1969) \n");
printf("        Les espaces fermes sont limites par la coque, par les ponts, les       \n");
printf("        cloisons fixes ou amovibles, les toitures d'abri autre que des tauds.  \n");
printf("        Sont compris les appendices. Sont exclus les espaces ouverts a la mer, \n");
printf("        n'ayant sur les cotes exposes que les supports necessaires a leur      \n");
printf("        solidite.                                                              \n");
printf("        Pour les navires en metal: V est mesure face interieure borde ou tole  \n");
printf("        d'entourage de structure. Pour les navires en materiau autre V est     \n");
printf("        mesure exterieur borde ou interieur surfaces d'entourage de structure. \n");
printf("\n");
}

void choose1(){

printf("       'esc'      pour quitter \n" );
printf("       'espace'   pour un autre calcul " );
reponse=getch();
}

void calcul() {

printf("\n\n");
printf("volume (m3):    ");
scanf ("%f" , &volume);
coeff = (0.2 + (0.02*( log10(volume))));
grosston = volume * coeff;
}

void plotresult() {

printf("coeff :         %.4f\n", coeff);
printf("gross ton :     %.4f\n\n", grosston);
}

/*
void saveresult() {
printf("(resultats sauvegardes dans 'gt.log')\n");
printf("\n");
}                                   */

void sortie() {
exit(0);
}

int main()
{
/*setbk(1); couleur du fond */

intro();
debut:
calcul ();
plotresult();
question:
choose1();
switch (reponse)
{
case  ' ':                         /* 'espace' = continue */
           goto debut;

case  (13):                         /* 'enter' = continue */
           goto debut;

case (27):                          /* 'esc' = quitte */
            clrscr ();
            sortie();
default:
            printf("\n\n");
            goto question;
}
return(0);
}
