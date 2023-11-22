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

}t_sommet;

int detecterNombreLignes(char* NOMFICHIER){
    FILE *f;
    int nombrePresent;
    int nombreLignes = 0;

    f = fopen(NOMFICHIER,"r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return -1; // Code d'erreur pour indiquer une erreur d'ouverture du fichier
    }

    do {
        fscanf(f,"%d",&nombrePresent); // Lecture du nombre
        fscanf(f," "); // Consomme l'espace après le nombre
        fscanf(f,"%d"); // Lis l'autre nombre
        fscanf(f,"\n"); // Passe à la ligne suivante

        if (nombrePresent != 0) {
            nombreLignes++; // Incrémente le compteur si le nombre est différent de zero ou nul
        }
    } while (nombrePresent != 0); // Continue jusqu'à ce que le nombre lu soit zero

    fclose(f); // Ferme le fichier
    printf("nombre de lignes est %d", nombreLignes);
    return nombreLignes;
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
    for (int i = 0; i < tabsommet[0].nbrStep ; i++)
    {
        fscanf(f,"%d",&temp1);// Lecture du nombre
        fscanf(f," ");// Consomme l'espace après le nombre
        fscanf(f,"%d",&temp2); // Lis l'autre nombre
        fscanf(f,"\n");// Passe à la ligne suivante
        while (tabsommet[temp1].tabExclusion[compteur] != NULL) ///
        {
            compteur++;
        }
        tabsommet[temp1].tabExclusion[compteur] = realloc(tabsommet[temp1].tabExclusion,compteur+1);
        }
        tabsommet[temp1].tabExclusion[compteur] = temp2;
        compteur = 0;
        while (tabsommet[temp2].tabExclusion[compteur] != NULL)
        {
            compteur++;
            if(tabsommet[temp2].tabExclusion[compteur] == NULL)
            {

            }
        }
        tabsommet[temp2].tabExclusion[compteur] = temp1;
        compteur = 0;
    }

}