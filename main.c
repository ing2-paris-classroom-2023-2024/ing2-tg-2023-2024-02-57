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

    tabsommet = allouerTabSommet(precedences, operation, exclusion, tempCycle);

    printf("\n"
           " __       __  ________  __    __  __    __ \n"
           "|  \\     /  \\|        \\|  \\  |  \\|  \\  |  \\\n"
           "| $$\\   /  $$| $$$$$$$$| $$\\ | $$| $$  | $$\n"
           "| $$$\\ /  $$$| $$__    | $$$\\| $$| $$  | $$\n"
           "| $$$$\\  $$$$| $$  \\   | $$$$\\ $$| $$  | $$\n"
           "| $$\\$$ $$ $$| $$$$$   | $$\\$$ $$| $$  | $$\n"
           "| $$ \\$$$| $$| $$_____ | $$ \\$$$$| $$__/ $$\n"
           "| $$  \\$ | $$| $$     \\| $$  \\$$$ \\$$    $$\n"
           " \\$$      \\$$ \\$$$$$$$$ \\$$   \\$$  \\$$$$$$ \n"
           "                                           \n"
           "                                           \n"
           "                                           \n");
    printf("----------------------------------------------------------------------------------\n");
    do {
        printf("|||(1) total ||| (2) exclusion ||| (3) temps ||| (4) precendences |||\n");
        scanf("%d",&choix);
    }while(choix != 1 && choix != 2 && choix != 3 && choix != 4);
    printf("----------------------------------------------------------------------------------\n");
    if(choix == 1 )
    {
        trieBOXtot(tabsommet);
    }
    if(choix == 2 )
    {
        BoxExclusion(tabsommet);
    }
    if(choix == 3 )
    {
        BoxExclusion(tabsommet);
    }
    if(choix == 4 )
    {
        BOXPRECEDENCES(tabsommet);
    }


    return 6969;
};