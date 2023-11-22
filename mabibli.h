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


void allouerTabSommet(int nbrSommet,t_sommet *tabsommet,char *NOMFICHIER)
{
    tabsommet = (t_sommet*) malloc(sizeof(t_sommet)*nbrSommet);
    for (int i = 0; i < nbrSommet; i++)
    {
        tabsommet[i].nbrStep = detecterNombreLignes(NOMFICHIER);
    }

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
        tabsommet[temp1].tabExclusion = realloc(tabsommet[temp1].tabExclusion,(compteur+1)* sizeof(int));
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

int detecterPlusGrandNombre(char *NOMFICHIER){
    FILE *f;
    int plusGrandNombre=0;
    int nombre1, nombre2;
    char poubelle;
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
    printf("le plus grand nombre est %d\n",plusGrandNombre);
    return plusGrandNombre;
}

void BoxExclusion(t_sommet *tabsommet)
{
    printf("----------------------------------");
    printf("_________Box 1 : ");
    for (int i = 0; i < tabsommet[0].nbrStep; ++i) {

    }
}
