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
    int num;
    int* tabExclusion;
    int nbrStep;
    int* tabPrecedence;
}t_sommet;

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


t_sommet *allouerTabSommet(int nbrSommet,char *NOMFICHIER)// alloue dynamiquement le nombre de sommets en fonction du nombre de sommet spécifié
{
    t_sommet *tabsommet;
    tabsommet = (t_sommet*) malloc(sizeof(t_sommet)*nbrSommet);
    for (int i = 0; i <= nbrSommet; i++)// initialisation pour chaque sommet
    {
        tabsommet[i].nbrStep = nbrSommet;// initialisation ici du nombre d'etape
        tabsommet[i].tabExclusion = malloc(sizeof (int ) * 2);// alloue dynamiquement un tableau d'exclusion pour le sommet i
        tabsommet[i].tabExclusion[0] = 0;
        tabsommet[i].tabPrecedence = malloc(sizeof (int ) * 2);// alloue dynamiquement un tableau dde precedence pour le sommet i
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
        return ; // Code d'erreur pour indiquer une erreur d'ouverture du fichier
    }

    int nbrLigne = detecterNombreLignes(NOMFICHER);

    for (int i = 0; i < nbrLigne ; i++)// pour chaque ligne du fichier on a:
    {

        fscanf(f, "%d", &temp1);// Lecture du nombre
        fscanf(f, " ");// Consomme l'espace après le nombre
        fscanf(f, "%d", &temp2); // Lis l'autre nombre
        fscanf(f, "\n");// Passe à la ligne suivante
        while (tabsommet[temp1].tabExclusion[compteur] != 0) // on lit les lignes du tableau jusqu'à celle correspondant à la valeur que l'on veut exclure
        {
            compteur++;
            if (tabsommet[temp1].tabExclusion[compteur] == 0) {
                break;
            }

        }
        tabsommet[temp1].tabExclusion[compteur] = temp2;// on associe les valeurs exclues
        tabsommet[temp1].tabExclusion = realloc(tabsommet[temp1].tabExclusion, sizeof(int) * (compteur + 2));// on alloue dynamiquement une nouvelle ligne
        tabsommet[temp1].tabExclusion[compteur + 1] = 0;

        printf("%d %d %d ",temp1,temp2,tabsommet[temp1].tabExclusion[compteur]);

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
        tabsommet[temp2].tabExclusion = realloc(tabsommet[temp2].tabExclusion, sizeof(int) * (compteur + 2));
        tabsommet[temp2].tabExclusion[compteur + 1] = 0;
        printf("%d \n",tabsommet[temp2].tabExclusion[compteur]);
        compteur = 0;
    }
    fclose(f);// fermeture du fichier
}

int detecterPlusGrandNombre(char *NOMFICHIER){
    FILE *f;
    int plusGrandNombre=0;
    int nombre1, nombre2;
    f = fopen(NOMFICHIER, "r");
    if (f == NULL) {
        printf("Erreur ouverture du fichier.\n");
        return -1; // Code d'erreur pour indiquer une erreur d'ouverture du fichier
    }
    for (int i = 0; i < detecterNombreLignes(NOMFICHIER); ++i) {
        fscanf(f,"%d %d\n",&nombre1,&nombre2);
        if(plusGrandNombre < nombre1){plusGrandNombre = nombre1;}
        if(plusGrandNombre < nombre2){plusGrandNombre = nombre2;}
    }
    fclose(f);
    printf("le plus grand nombre est %d\n",plusGrandNombre);
    return plusGrandNombre;
}

void BoxExclusion(t_sommet *tabsommet)
{
    int *box1;
    int tailleBox = 0;
    box1 = malloc(sizeof (int)*2);
    int compteurExclusion;
    box1[0] = 0;
    int condition = 0;
    printf("----------------------------------\n");
    printf("_________Box 1 : ");
    for (int i = 1; i <= tabsommet[0].nbrStep; i++)
    {
        condition = 0;

        for (int j = 0; j <= tailleBox; j++)
        {
            compteurExclusion = 0;


            while (tabsommet[i].tabExclusion[compteurExclusion]!=0)
            {
                if (tabsommet[i].tabExclusion[compteurExclusion] == box1[j])
                {
                    condition = 1;
                }
                compteurExclusion++;
            }
        }
        if (!condition)
        {

            box1[tailleBox] = i;
            printf(" %d ",box1[tailleBox]);
            tailleBox++;
            box1 = realloc(box1,sizeof (int )* (tailleBox+2));
            box1[tailleBox] = 0;
        }
    }
    printf("__________\n");
    free(box1);
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

    for (int i = 1; i <= nbOperations; i++){
        while (tabsommet[i].tabPrecedence[compteur] != 0) ///
        {
            compteur++;
            if (tabsommet[i].tabPrecedence[compteur] == 0) {
                break;
            }

        }
       printf("\n %d a %d antecedant",i,compteur); /// TODO pourquoi element 35 possede un antecedant alors qu'il n'existe pas ?
        compteur=0; /// TODO sinon juste baisser boucle de 1
    }
    free(box1); // libere l'espace des boxs
}
