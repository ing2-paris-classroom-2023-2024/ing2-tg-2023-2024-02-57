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
    int boxexclu;
    int* tabExclusion;
    int nbrStep;
    int* tabPrecedence;
    float tabOperationTemps;
    float tabTemps_cycle;
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
///fonction qui renvoie 1 tant que tous les sommets du tableau n'ont pas une box assigné


t_sommet *allouerTabSommet(char *NOMFICHIER)
{
    t_sommet *tabsommet;
    int test1,test2;
    int temp1,temp2;
    int plusgrandnombre = 0;
    int compteur_nombre_sommet = 0;
    int *tabnumsommet;

    plusgrandnombre = detecterPlusGrandNombre(NOMFICHIER);

    tabnumsommet = (int *) malloc(sizeof (int ) * (plusgrandnombre + 1 ) );

    FILE *f;

    f = fopen(NOMFICHIER,"r");

    if(f==NULL)
    {
        printf("erreur ouverture fichier allouer tableau sommet");
        exit(-1);
    }
    for (int i = 0; i < detecterNombreLignes(NOMFICHIER); i++)
    {

        test1 = 0;
        test2 = 0;
        fscanf(f,"%d %d\n",&temp1,&temp2);
        for (int j = 0; j <= compteur_nombre_sommet; j++)
        {
            if (temp1 == tabnumsommet[j])
            {
                test1 = 1;
            }
            if (temp2 == tabnumsommet[j])
            {
                test2 = 1;
            }
        }
        if(!test1)
        {
            printf("nouveau sommet : %d\n",temp1);
            tabnumsommet[compteur_nombre_sommet] = temp1;
            compteur_nombre_sommet++;
            tabnumsommet[compteur_nombre_sommet] = 0;
            test1 = 1;

        }
        if(!test2)
        {
            printf("nouveau sommet : %d\n",temp2);
            tabnumsommet[compteur_nombre_sommet] = temp2;
            compteur_nombre_sommet++;
            tabnumsommet[compteur_nombre_sommet] = 0;
            test2 = 1;

        }
    }
    tabsommet = (t_sommet *) malloc((compteur_nombre_sommet+1)*sizeof(t_sommet));

    for (int i = 0; i < compteur_nombre_sommet; i++)
    {
        tabsommet[i].num = tabnumsommet[i];
        tabsommet[i].boxexclu = 0;
        tabsommet[i].nbrStep = compteur_nombre_sommet;// initialisation ici du nombre d'etape
        tabsommet[i].tabExclusion = malloc(compteur_nombre_sommet * sizeof (int ));// alloue dynamiquement un tableau d'exclusion pour le sommet i

        for (int j = 0; j < compteur_nombre_sommet; j++)
        {
            tabsommet[i].tabExclusion[j] = 0;
        }

        tabsommet[i].tabPrecedence = malloc(sizeof (int ));// alloue dynamiquement un tableau dde precedence pour le sommet i
        tabsommet[i].tabPrecedence[0]=0;
        tabsommet[i].boxexclu = 0;
        // tabsommet[i].tabOperationTemps = malloc(sizeof (float ) * 2);
        // tabsommet[i].tabOperationTemps[0]=0;
    }

///une fois qu'on a tous les sommets on cherche donc a le re classer dans l'ordre
///pour ca on fait un buffer de sommet

    t_sommet buffer;

    for (int i = 0; i < compteur_nombre_sommet; i++)
    {
        for (int j = 0; j < compteur_nombre_sommet; j++)
        {
            if(tabsommet[i].num < tabsommet[j].num)
            {
                buffer = tabsommet[i];
                tabsommet[i] = tabsommet[j];
                tabsommet[j] = buffer;

            }
        }
    }
    ///ici on fait des printf afin de verifier si les sommets sont bien trié
    printf("nombre de sommets : %d\n",compteur_nombre_sommet);
    for (int i = 0; i < compteur_nombre_sommet; i++)
    {
        printf("sommet n %d a comme nom %d\n",i,tabsommet[i].num);
    }

    /// trie validé

    return tabsommet;// renvoie l'initialisation de chaque sommet



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
        tabsommet[i].num=i;
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
void boxPrecedences(t_sommet *tabsommet) {
    int nbOperations = tabsommet[0].nbrStep;
    t_sommet** box = malloc(sizeof(t_sommet*) * 4); // Allocation de quatre pointeurs pour les boîtes
    int* tailleBox = malloc(sizeof(int) * 4); // Allocation de quatre entiers pour les tailles de boîtes
    for (int i = 0; i < 4; ++i) {
        tailleBox[i] = 0;
    }

    if (box == NULL || tailleBox == NULL) {
        printf("Erreur lors de l'allocation de memoire.\n");
        return;
    }

    for (int i = 0; i < 4; ++i) {
        box[i] = malloc(sizeof(t_sommet) * (nbOperations + 1)); // Allocation des boîtes
        if (box[i] == NULL) {
            printf("Erreur lors de l'allocation de memoire pour box[%d].\n", i);
            for (int j = 0; j < i; ++j) {
                free(box[j]);
            }
            free(box);
            free(tailleBox);
            return;
        }
    }

    for (int i = 0; i < nbOperations; ++i) {
        if (tabsommet[i].tabPrecedence[0] == 0) {
            box[0][tailleBox[0]] = tabsommet[i];
            printf("ajout box 1\n");
            tailleBox[0]++;
        } else {
            int allPrecedencesFound = 1;
            for (int compteur = 0; tabsommet[i].tabPrecedence[compteur] != 0; ++compteur) {
                int precedencesFound = 0;
                for (int j = 0; j < tailleBox[0]; ++j) {
                    if (tabsommet[i].tabPrecedence[compteur] == box[0][j].num) {
                        precedencesFound = 1;
                        break;
                    }
                }
                if (!precedencesFound) {
                    allPrecedencesFound = 0;
                    break;
                }
            }
            if (allPrecedencesFound) {
                box[1][tailleBox[1]] = tabsommet[i];
                printf("ajout box 2\n");
                tailleBox[1]++;
            } else {
                allPrecedencesFound = 1;
                for (int compteur = 0; tabsommet[i].tabPrecedence[compteur] != 0; ++compteur) {
                    int precedencesFound = 0;
                    for (int j = 0; j < tailleBox[1]; ++j) {
                        if (tabsommet[i].tabPrecedence[compteur] == box[1][j].num) {
                            precedencesFound = 1;
                            break;
                        }
                    }
                    if (!precedencesFound) {
                        allPrecedencesFound = 0;
                        break;
                    }
                }
                if (allPrecedencesFound) {
                    box[2][tailleBox[2]] = tabsommet[i];
                    printf("ajout box 3\n");
                    tailleBox[2]++;
                } else {
                    allPrecedencesFound = 1;
                    for (int compteur = 0; tabsommet[i].tabPrecedence[compteur] != 0; ++compteur) {
                        int precedencesFound = 0;
                        for (int j = 0; j < tailleBox[2]; ++j) {
                            if (tabsommet[i].tabPrecedence[compteur] == box[2][j].num) {
                                precedencesFound = 1;
                                break;
                            }
                        }
                        if (!precedencesFound) {
                            allPrecedencesFound = 0;
                            break;
                        }
                    }
                    if (allPrecedencesFound) {
                        box[3][tailleBox[3]] = tabsommet[i];
                        printf("ajout box 4\n");
                        tailleBox[3]++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        printf("\n_________Box %d : ", i + 1);
        for (int j = 0; j < tailleBox[i]; ++j) {
            printf(" %d ", box[i][j].num);
        }
    }

    for (int i = 0; i < 4; ++i) {
        free(box[i]); // Libération de la mémoire allouée pour les boîtes
    }
    free(box);
    free(tailleBox); // Libération de la mémoire allouée pour les tableaux de tailles
}



void impressionSommetPrecedence(t_sommet *tabsommet){
    int nbOperations= tabsommet[0].nbrStep;   //variable permettant de compter le nb d'antécédent de chaque tache
    int compteur = 0;
    for (int i = 1; i <= nbOperations; i++){
        compteur=0;
        while (tabsommet[i].tabPrecedence[compteur] != 0)
        {
            printf("%d a comme antecedant %d\n",i,tabsommet[i].tabPrecedence[compteur]); ///montre les precedences de chaque tache
            compteur++;
            if (tabsommet[i].tabPrecedence[compteur] == 0 ) {
                break; // parcourt le tableau de precedence jusqua la fin
            }
        }
        printf("  %d a %d antecedant\n\n",i,compteur); // affiche le nombre de précédence de chaque tache
    }
}
