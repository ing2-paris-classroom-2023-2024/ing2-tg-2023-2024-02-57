//
// Created by eudes on 22/11/2023.
//


#include "mabibli.h"

int main()
{
    char NOMFICHIER[32];
    strcpy(NOMFICHIER,"../exclusion.txt");
    printf("hello ECE %d\n",detecterNombreLignes(NOMFICHIER));
    detecterPlusGrandNombre(NOMFICHIER);

    t_sommet *tabsommet;

    tabsommet = allouerTabSommet(detecterPlusGrandNombre(NOMFICHIER),NOMFICHIER);

    //printf("%d\n",tabsommet[0].nbrStep);

    exclusion(NOMFICHIER,tabsommet);

    BoxExclusion(tabsommet);
    //strcpy(NOMFICHIER,"../precedences.txt");
    //precedences(NOMFICHIER,tabsommet);
    //impressionSommetPrecedence(tabsommet);
    //boxPrecedences(tabsommet);
    free(tabsommet); //libere l'espace du tableau de sommet
    return 17;
};