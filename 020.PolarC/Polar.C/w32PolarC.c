/*    TODO (#1#):
      le default de choose1 réecrit les 3 lignes filtrer les mauvaises touches et biper seulemnt
      dans "sortie : attente puis quitte puis ouvre gt.txt
      dans "saveresult" ecriture dans le fichier (ou pas) à la suite
      checker l'input de volume detecter 'esc' et les filtrer les non numeriques
      les 4 lignes du haut sont dediées à la commande (ou 4 lignes en bas ???
*/

#define VERSION "200 11 07"  /* remplacer par la date de la compil du programme en 10 caracteres exactement */
#include <stdio.h>
#include <conio2.h>

#include <math.h>


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
highvideo();
printf("calcul du tonnage brut                                           ");
lowvideo();
printf("VPLP ");
printf(VERSION);
printf("\n");
printf("\n");	
printf("                        --- ---                        - \n");
printf("                  - -- ---- ---- -- -                  - \n");
printf("               -- --- ----- ----- --- --               - \n");
printf("             --- ---- ----- ------ --- ---             - \n");
printf("           ---- ---- ------ ------- ---- ----          - 30\n");
printf("          ---- ---- ------- ------- ----- ----         - \n");
printf("        ---- ----- -------- -------- ----- ----        - \n");
printf("       ---- ------ -------- -------- ------ ----       - \n");
printf("       ---- ------ -------- -------- ------ ----       - \n");
printf("       ---- ------ -------- -------- ------ ----       - \n");
printf("       ---- ------ -------- -------- ------ ----       - \n");
printf("       ---- ------ -------- -------- ------ ----       - \n");
printf("       . . . . . . . . . . . . . . . . . . . . .         \n"); 
printf("       | | | | | | | | | | | | | | | | | | | | |         \n");
printf("                               +25           \n");
printf("\n");
printf("\n");
}


void choose1(){
lowvideo();
printf("       'left' et 'right'   pour faire varier l'azimut\n" );	
printf("       'up' et 'down'>'    pour faire varier la hauteur\n" );	
printf("       'esc'      pour quitter \n" );
printf("       'espace'   pour un autre calcul " );
gotoxy(15,37);
reponse=getch();

}

                                 */

void sortie() {
exit(0);
}

int main()
{
/*setbk(1); couleur du fond */

choose1();
switch (reponse)
{
case  ' ':                         /* 'espace' = continue */
           sortie();


case  (13):                         /* 'enter' = continue */
           sortie();


case (27):                          /* 'esc' = quitte */
            clrscr ();
            sortie();
default:
            printf("\n\n");
            sortie();

}
return(0);
}
