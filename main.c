//
// Created by eudes on 22/11/2023.
//


#include "mabibli.h"

int main()
{
    char NAMEFILE[32];
    strcpy(NAMEFILE,"../precedences.txt");
    char NOMFICHIER[32];
    strcpy(NOMFICHIER,"../exclusion.txt");
    char FILENAME[32];
    strcpy(FILENAME,"../operation.txt");
    char FILENAMEE[32];
    strcpy(FILENAMEE,"../temps_de_cycle.txt");

    t_sommet *tabsommet;

    tabsommet = allouerTabSommet(NAMEFILE,FILENAME,NOMFICHIER);

    tempsCycle(FILENAMEE,tabsommet);

    //printf("%d\n",tabsommet[0].nbrStep);
    //BoxExclusion(tabsommet);
    //printf("testaamen");
    //precedences(NAMEFILE,tabsommet);
    //printf("test\n");

    trieBOXtot(tabsommet);
    //strcpy(NOMFICHIER,"../precedences.txt");
    //precedences(NOMFICHIER,tabsommet);
    //impressionSommetPrecedence(tabsommet);
    //boxPrecedences(tabsommet);
    //free(tabsommet); //libere l'espace du tableau de sommet
    //strcpy(NOMFICHIER, "../temps_de_cycle.txt");
    //tempsCycle(NOMFICHIER, tabsommet);

    return 6969;
};