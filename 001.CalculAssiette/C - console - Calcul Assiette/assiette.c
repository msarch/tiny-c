/*
//============================================================================
// Name        : Assiette.cpp
// Author      : ms
// Version     :
// Copyright   : ms 2008
// Description : C, Ansi-style
//============================================================================
/*    TODO (#1#):
      le default de choose1 réecrit les 3 lignes
      filtrer les erreurs et biper
      proposer un nouveau calcul en ne rentrant que la nouvelle masse
      dans "sortie : attente puis quitte puis ouvre gt.txt
      dans "saveresult" ecriture dans le fichier (ou pas) à la suite
      checker l'input de volume detecter 'esc' et les filtrer les non numeriques
      proposer le calcul du coeff correcteur à p de données lpa
      les 4 lignes du haut sont dediées à la commande (ou 4 lignes en bas ???

C:\MingW\bin\gcc.exe assiette.c -o assiette.exe -lconio -ansi -fexpensive-optimizations  -fexpensive-optimizations -Os -O3 -O2 -O1 -s
*/

#define VERSION "2006.12.14"  /* date en 10 caracteres exactement */
#include <stdio.h>
/* #include <conio2.h>  */

#include <math.h>

void splash_screen();
void calcul();
void plotresult();
void choose1();
void saveresult();
void sortie();

float x_cg,wpa_x_arr,wpa_x_avt,bb,masse,x;                              /* inputs */
float alpha_rad,alpha_deg,enfoncement,deplacement_etrave,deplacement_tableau;   /* resultats */
float pi;                                                                       /* constantes */
float a1,a2,b,x1,x2,aire1,aire2,coeff,moment_total;                             /* intermediaires */
int choice1,bateau_defini;
char reponse;

/***************************************************************************************/
void splash_screen(){
    clrscr ();
    highvideo();
    printf("  ...........................................................................  \n");
    printf("  .                                                                         .  \n");
    printf("  .   variation d'assiette d'un catamaran avec une surcharge ponctuelle     .  \n");
    printf("  .                             VPLP ");
    printf(VERSION);
    printf("                             .  \n");
    printf("  .                                                                         .  \n");
    printf("  ...........................................................................  \n");
    printf("  .                                                                         .  \n");
    printf("  .  A partir d'informations geometriques simples, ce programme estime la   .  \n");
    printf("  .  variation d'assiette correspondant a des surcharges ponctuelles pour   .  \n");
    printf("  .  un catamaran initialement a l'equilibre.                               .  \n");
    printf("  .                                                                         .  \n");
    printf("  .   restrictions:                                                         .  \n");
    printf("  .                                                                         .  \n");
    printf("  .  - la masse ajoutee doit rester tres inferieure au deplacement.         .  \n");
    printf("  .  - l'angle donne en resultat doit rester petit pour etre valable.       .  \n");
    printf("  .  - la forme de la partie du plan de flottaison en arriere du lcg doit   .  \n");
    printf("  .    pouvoir etre assimilable a une demi-ellipse (idem en avant du lcg).  .  \n");
    printf("  .                                                                         .  \n");
    printf("  ...........................................................................  \n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    lowvideo();
    printf("  appuyez sur une touche pour continuer, 'esc' pour quitter :" );
    reponse=getch();
    switch (reponse)
        {
        case (27):                          /* 'esc' = quitte */
                 clrscr ();
                 sortie();
        default:
                 clrscr ();
        }
}
/***************************************************************************************/
void choose1(){
    lowvideo();
    gotoxy(1,21);
    printf("  '+'     pour ajouter une masse supplementaire.\n" );
    printf("  'enter' pour un autre calcul en conservant les caracteristiques bateau.\n" );
    printf("  'space' pour un nouveau calcul. \n" );
    printf("  'esc'   pour quitter. " );
    reponse=getch();
}

/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
void calcul() {
    highvideo();
    switch (bateau_defini)
    {
        case (0):                          /* entree de toutes les caracteristiques */
            goto get_infos_bateau;
        case (1):                          /* entree de la masse seulement */
            goto get_infos_masse;
        default:
            goto get_infos_bateau;
    }
        /*********************** ici : les inputs bateau  *****************************/
        get_infos_bateau:
        clrscr ();
        printf("  ...........................................................................  \n");
        printf("\n");
        printf("  x arriere du plan de flottaison (mm): ---------- ");
        scanf ("%f" , &wpa_x_arr);
        printf("  x avant du plan de flottaison (mm): ------------ ");
        scanf ("%f" , &wpa_x_avt);
        printf("  x du centre de carene (mm): -------------------- ");
        scanf ("%f" , &x_cg);
        printf("  largeur maximum du plan de flottaison (mm): ---- ");
        scanf ("%f" , &bb);
        printf("\n");
        printf("  ...........................................................................  \n");

        /************************ici : calcul parametres bateau**********************/

        wpa_x_arr=wpa_x_arr/1000;       /* conversion en metres */
        wpa_x_avt=wpa_x_avt/1000;       /* conversion en metres */
        x_cg=x_cg/1000;                 /* conversion en metres */
        bb=bb/1000;                     /* conversion en metres */
        b=bb/2;                         /* le b de l'ellipse est sa demi-largeur*/
        a1 = wpa_x_arr-x_cg;            /* longueur de la demi-ellipse arriere */
        a2 = wpa_x_avt-x_cg;            /* longueur de la demi-ellipse avant */
        x1 = (4*a1)/(3*pi);             /* centre geometrique demi-ellipse arriere dans repere cg */
        x2 = (4*a2)/(3*pi);             /* centre geometrique demi-ellipse avant dans repere cg  */
        aire1= -(pi*a1*b)/2;            /* aire demi-ellipse avant */
        aire2= (pi*a2*b)/2;             /* aire demi-ellipse arriere */
        coeff=(1025*4*pi*(x1*a1*a1*b)+(x2*a2*a2*b))/(3*360);

        /*********************** ici : les inputs masses  ******************************/

        get_infos_masse:
        gotoxy(1,10);
        printf("  masse supplementaire (kg): --------------------- ");
        scanf ("%f" , &masse);
        printf("  position en x (mm): ---------------------------- ");
        scanf ("%f" , &x);
        printf("\n");
        printf("  ...........................................................................  \n");

        /*********************** ici : les calculs masses  *****************************/

        masse=masse/2;                                          /* ramené à une seule coque */
        x=x/1000;                                               /* conversion en metres */
        x=x-x_cg;                                               /* recalage dans repère cg */
        moment_total=moment_total+(masse*x);                    /* increment du moment */
        enfoncement= enfoncement+(masse/(aire1+aire2));         /* increment de l'enfoncement */

        /*********************** ici : le calculs assiette  ****************************/

        alpha_deg=moment_total/coeff;
        alpha_rad= (2*pi/360)*alpha_deg;
        deplacement_etrave= enfoncement-(1000*a2*sin(alpha_rad));
        deplacement_tableau= enfoncement-(1000*a1*sin(alpha_rad));

/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
}

void plotresult()
{

    /*
     ............... pour debug.................
    gotoxy(1,15);
    printf("a1 : %.2f\n", a1);
    printf("a2 : %.2f\n", a2);
    printf("x1 : %.2f\n", x1);
    printf("x2 : %.2f\n", x2);
    printf("pi : %.2f\n", pi);
    printf("aire1 : %.2f\n", aire1);
    printf("aire2 : %.2f\n", aire2);
    printf("b : %.2f\n", b);
    printf("moment_total : %.2f\n", moment_total);
    printf("coeff : %.2f\n\n", coeff);
    getch();
   */

    gotoxy(1,15);
    highvideo();
    printf("        angle : ---------------------------------- %.2f degres \n", alpha_deg);
    printf("        enfoncement : ---------------------------- %.0f mm \n", enfoncement);
    printf("        deplacement vertical de l'etrave : ------- %.0f mm \n", deplacement_etrave);
    printf("        deplacement vertical du tableau : -------- %.0f mm \n", deplacement_tableau);

}

/*
à faire:
void saveresult() {
printf("(resultats sauvegardes dans 'gt.log')\n");
printf("\n");
}
*/

void sortie()
{
    exit(0);
}

int main()
{
    /*setbk(1); couleur du fond */
    pi = 3.1415927;
    bateau_defini=0;
    moment_total=0;
    enfoncement=0;

    splash_screen();
    debut:
    calcul ();
    plotresult();
    question:
    choose1();
    switch (reponse)
    {
        case '+':                          /* '+' = ajoute une masse avec meme bateau */
                gotoxy(1,10);
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               ");
                bateau_defini= 1;
                goto debut;

        case  ' ':                         /* 'espace' =continue nouveau bateau */
                bateau_defini= 0;
                moment_total=0;
                enfoncement=0;
                goto debut;

        case  (13):                        /* 'enter' = reprend avec meme bateau  */
                gotoxy(1,10);
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               \n");
                printf("                                                                               ");
                masse=0;
                bateau_defini= 1;
                moment_total=0;
                enfoncement=0;
                goto debut;

        case (27):                          /* 'esc' = quitte */
                clrscr ();
                sortie();
        default:
            goto question;
    }

    return(0);
}








