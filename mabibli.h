//
// Created by eudes on 22/11/2023.
//

#ifndef ING2_TG_2023_2024_02_57_MABIBLI_H
#define ING2_TG_2023_2024_02_57_MABIBLI_H

#endif //ING2_TG_2023_2024_02_57_MABIBLI_H

#include "time.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct sommet
{
    int num;              // identifiant du sommet
    int nbExclu;          // nb de sommets exclus
    int boxexclu;         // le numero du box contenant ce sommet
    int* tabExclusion;    // tableau des noms des sommets en exclusion
    int nbrStep;          // nombre de sommets total
    int* tabPrecedence;   // tableau des noms des sommets précédence
} t_sommet;

int detecterNombreLignes(char* NOMFICHIER) {
    FILE *f;
    int nombrePresent;
    int nombreLignes = 0;

    f = fopen(NOMFICHIER, "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return -1; // Code d'erreur pour indiquer une erreur d'ouverture du fichier
    }

    while (fscanf(f, "%d%*[^\n]", &nombrePresent) == 1) {
        fgetc(f); // Lire et ignorer le saut de ligne
        nombreLignes++; // Incrémente le compteur pour chaque ligne commençant par un nombre
    }

    fclose(f); // Ferme le fichier
    // printf("Nombre de lignes %d\n", nombreLignes);
    return nombreLignes;
}


t_sommet *allouerTabSommet(int nbrSommet)
// alloue dynamiquement le nombre de sommets en fonction du nombre de sommet spécifié
{
    t_sommet *tabsommet;
    tabsommet = (t_sommet*) malloc(sizeof(t_sommet)*(nbrSommet+1));
    for (int i = 0; i <= nbrSommet; i++)// initialisation pour chaque sommet
    {
        tabsommet[i].num = i;
        tabsommet[i].boxexclu = 0;
        tabsommet[i].nbrStep = nbrSommet;// initialisation ici du nombre d'etape
        tabsommet[i].tabExclusion = malloc(nbrSommet * sizeof (int ));// alloue dynamiquement un tableau d'exclusion pour le sommet i
        for (int j = 0; j < nbrSommet; j++) {
            tabsommet[i].tabExclusion[j] = 0;
        }

        tabsommet[i].tabPrecedence = malloc(sizeof (int ));// alloue dynamiquement un tableau dde precedence pour le sommet i
        tabsommet[i].tabPrecedence[0]=0;


    }

    return tabsommet;// renvoie l'initialisation de chaque sommet

}

void exclusion(char* NOMFICHER,t_sommet* tabsommet)
{
    FILE *f;
    int temp1,temp2;
    int compteur = 0;
    f = fopen(NOMFICHER,"r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(-1) ; // Code d'erreur pour indiquer une erreur d'ouverture du fichier
    }

    int nbrLigne = detecterNombreLignes(NOMFICHER);
    printf("nombre de ligne : %d\n",nbrLigne);


    for (int i = 0; i < nbrLigne ; i++)// pour chaque ligne du fichier on a:
    {

        fscanf(f, "%d", &temp1);// Lecture du nombre
        fscanf(f, " ");// Consomme l'espace après le nombre
        fscanf(f, "%d", &temp2); // Lis l'autre nombre
        fscanf(f, "\n");// Passe à la ligne suivante
        while (tabsommet[temp1].tabExclusion[compteur] != 0) // on lit les lignes du tableau jusqu'à celle correspondant à la valeur que l'on veut exclure
        {
            compteur++;
            if (tabsommet[temp1].tabExclusion[compteur] == 0)
            {
                break;
            }
        }
        tabsommet[temp1].tabExclusion[compteur] = temp2;// on associe les valeurs exclues
        //tabsommet[temp1].tabExclusion =(int *) realloc(tabsommet[temp1].tabExclusion, (compteur + 1) * sizeof(int) );// on alloue dynamiquement une nouvelle ligne
        tabsommet[temp1].tabExclusion[compteur + 1] = 0;

        printf("%d / %d %d %d ",compteur,temp1,temp2,tabsommet[temp1].tabExclusion[compteur]);

        compteur = 0;
        while (tabsommet[temp2].tabExclusion[compteur] != 0)// on recommence le processus précédent dans l'autre sens, en effet l'exclusion se fait dans les deux sens
        {
            compteur++;
            if (tabsommet[temp2].tabExclusion[compteur] == 0)
            {
                break;
            }
        }
        tabsommet[temp2].tabExclusion[compteur] = temp1;
        //tabsommet[temp2].tabExclusion = (int *) realloc(tabsommet[temp2].tabExclusion, (compteur + 1) * sizeof(int));
        tabsommet[temp2].tabExclusion[compteur + 1] = 0;

        printf("%d / %d  \ttemp1 : %d\n",tabsommet[temp2].tabExclusion[compteur],compteur,temp1);
        compteur = 0;
    }

    fclose(f);// fermeture du fichier



}

int detecterPlusGrandNombre(char *NOMFICHIER){// le but ici est de detecter le plus grand ombre du fichier afin de donnaitre le nombre d'étape
    FILE *f;
    int plusGrandNombre=0;
    int nombre1, nombre2;
    f = fopen(NOMFICHIER, "r");// ouverture du fichier
    if (f == NULL) {
        printf("Erreur ouverture du fichier.\n");
        return -1; // Code d'erreur pour indiquer une erreur d'ouverture du fichier
    }
    for (int i = 0; i < detecterNombreLignes(NOMFICHIER); ++i) {// tant que le nombre de ligne du fichier n'est pas atteinte:
        fscanf(f,"%d %d\n",&nombre1,&nombre2);// scanner les deux nombres présents sur une ligne
        if(plusGrandNombre < nombre1){plusGrandNombre = nombre1;}// si la variable 'plusGrandNombre' est plus petite que nombre1 alors elle prend cette valeur
        if(plusGrandNombre < nombre2){plusGrandNombre = nombre2;}// meme processus pour le nombre 2
    }
    fclose(f);
    printf("le plus grand nombre est %d\n",plusGrandNombre);// affichage du plus grand nombre
    return plusGrandNombre;// on renvoie le plus grand nombre
}
///fonction qui renvoie 1 tant que tous les sommets du tableau n'ont pas une box assigné


int sommetsAttrib(t_sommet* tabsommet)
{
    for (int i = 1; i <= tabsommet[0].nbrStep; i++)
    {
        if(!tabsommet[i].boxexclu)
        {
            return 1;
        }
    }
    return 0;
}

void BoxExclusion(t_sommet *tabsommet)
{
    int *tailleBox;

    int nbrBox = 0;

    tailleBox = malloc(sizeof (int )*(nbrBox+2));

    tailleBox[0] = 0;

    nbrBox = 1;

    t_sommet **BOX;

    //printf("test\n");


    BOX = malloc(sizeof (t_sommet*) * 2);

    //printf("test\n");



    for (int i = 0; i < 2; i++)
    {
        BOX[i] = malloc(sizeof (t_sommet) * 2);
        BOX[i][0] = tabsommet[0];
        //printf("test\n");

        if (!BOX[i])
        {
            //printf("test box \n");
            printf("erreur allocation BOX %d",i);
            return;
        }
    }


    //printf("test sortie \n");



    //box1 = malloc(sizeof (int)*2);

    //printf("teSSTT\n");
    int compteurExclusion;
    //box1[0] = 0;
    int condition = 0;

    //// RÉPARTITION DES SOMMETS DANS LES BOX  ////

    do {
        for (int i = 1; i <= tabsommet[0].nbrStep; i++)
        {

            condition = 0;
            //printf("test %d\n",tabsommet[i].boxexclu);

            if(tabsommet[i].boxexclu == 0)
            {
                for (int j = 0; j <= tailleBox[nbrBox]; j++)
                {
                    compteurExclusion = 0;
                    while (tabsommet[i].tabExclusion[compteurExclusion]!=0)
                    {
                        if (tabsommet[i].tabExclusion[compteurExclusion] == BOX[nbrBox][j].num)
                        {
                            condition = 1;
                            break;
                        }

                        printf("comptuer exclu : %d\n",compteurExclusion);
                        compteurExclusion++;
                    }
                    if(condition)
                        break;
                }
                printf("test");

                if (!condition)
                {
                    printf("%d\n",tailleBox[nbrBox]);
                    tabsommet[i].boxexclu = nbrBox ;
                    BOX[nbrBox][tailleBox[nbrBox]] = tabsommet[i];
                    printf("%d %d\n",nbrBox,tabsommet[i].num);
                    tailleBox[nbrBox]++;
                    BOX[nbrBox] = realloc(BOX[nbrBox],sizeof (t_sommet ) * (tailleBox[nbrBox]+2));
                    BOX[nbrBox][tailleBox[nbrBox]] = tabsommet[0];
                }
            }
        }
        if(sommetsAttrib(tabsommet))
        {
            //printf("taille box %d %d\n",nbrBox,tailleBox[nbrBox]);
            nbrBox++;
            tailleBox = realloc(tailleBox,sizeof (int)*(nbrBox+2));
            tailleBox[nbrBox] = 0;
            BOX = realloc(BOX,sizeof (t_sommet*) *(nbrBox+2));
            BOX[nbrBox] = malloc(sizeof (t_sommet)*(tailleBox[nbrBox]+2));
            //printf("test %d %d \n",tailleBox[nbrBox-1],tailleBox[nbrBox]);
        }
        //printf("taille box %d %d\n",nbrBox,tailleBox[nbrBox]);

    } while (sommetsAttrib(tabsommet));

    //printf("nombre box : %d\n",nbrBox);


    ///                     AFFICHAGE DES BOX                                  ////

    for (int compteur = 1; compteur <=nbrBox ; compteur++)
    {
        //printf("taille box %d : %d\n",compteur,tailleBox[compteur]);
        for (int i = 0; i <= tailleBox[compteur]; i++)
        {
            printf("----");
        }
        printf("------------------------\n");

        printf("Box %d :\t\t ",compteur);

        for (int i = 0; i < tailleBox[compteur] ; i++)
        {
            printf(" %d ",BOX[compteur][i].num);
        }

        printf("\n");

    }



    free(BOX);
}

void precedences(char *NOMFICHIER,t_sommet *tabsommet){ // lis precedences et cree un tableau de precedence pour chaque sommet
    FILE *f;
    int temp1,temp2;
    int compteur = 0;
    f = fopen(NOMFICHIER,"r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return ; // Code d'erreur pour indiquer une erreur d'ouverture du fichier
    }

    int nbrLigne = detecterNombreLignes(NOMFICHIER); // detecte le nombre de ligne du fichier precedences.txt
    for (int i = 0; i < nbrLigne; ++i) {
        fscanf(f,"%d %d\n",&temp1,&temp2); // lis l'element puis son predecesseur
        //  printf("%d %d\n",temp1,temp2);
        while (tabsommet[temp2].tabPrecedence[compteur] != 0)
        {
            compteur++;
            if (tabsommet[temp2].tabPrecedence[compteur] == 0) { //deroule jusqu'a la fin du tableau de precedences
                break;
            }
        }
        tabsommet[temp2].tabPrecedence[compteur]=temp1; // rajoute l'element a la fin
        tabsommet[temp2].tabPrecedence = realloc(tabsommet[temp2].tabPrecedence, sizeof(int) * (compteur + 2)); // realloue un nouvelle espace plus grand
        tabsommet[temp2].tabPrecedence[compteur + 1] = 0; //initialise l'element suivant a 0
        compteur = 0; // remet le compteur a 0 pour que le prochain tableau soit de nouveau parcouru a partir de 0
    }
    fclose(f);
}
void boxPrecedences(t_sommet *tabsommet){
    int* box1;
    int tailleBox=0;
    box1 = malloc(sizeof (int)*2);
    box1[0]=0;
    int condition = 0;
    int compteur = 0;
    printf("----------------------------------\n");
    printf("_________Box 1 : ");
    int nbOperations= tabsommet[0].nbrStep;


    free(box1); // libere l'espace des boxs
}

void impressionSommetPrecedence(t_sommet *tabsommet){
    int nbOperations= tabsommet[0].nbrStep;
    int compteur = 0;
    for (int i = 1; i <= nbOperations; i++){
        while (tabsommet[i].tabPrecedence[compteur] != 0)
        {
            printf("%d a comme antecedant %d\n",i,tabsommet[i].tabPrecedence[compteur]); ///montre les precedences de chaque tache
            compteur++;
            if (tabsommet[i].tabPrecedence[compteur] == 0) {
                break; // parcourt le tableau de precedence jusqua la fin
            }

        }
        printf("  %d a %d antecedant\n\n",i,compteur); /// montre combien de precedence a cette tache
        compteur=0;
    }
}