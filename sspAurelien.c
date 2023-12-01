//
// Created by antoi on 30/11/2023.
//

#include "mabibli.h"

void operation(char *NOMFICHIER,t_sommet *tabsommet){
    FILE *f;
    int numSommet;
    float temps;
    int compteur=0;
    f = fopen(NOMFICHIER,"r");

    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return ; // Code d'erreur pour indiquer une erreur d'ouverture du fichier
    }


    int nbrLigne = detecterNombreLignes(NOMFICHIER); // detecte le nombre de ligne du fichier operation.txt
    for (int i = 0; i < nbrLigne ; i++)// pour chaque ligne du fichier on a:
    {
        fscanf(f, "%d", &numSommet);// Lecture du nombre
        fscanf(f, " ");// Consume l'espace après le nombre
        fscanf(f, "%f", &temps); // Lis l'autre nombre
        fscanf(f, "\n");// Passe à la ligne suivante
        tabsommet[compteur].tabOperationTemps = temps;
        printf("%d %.2f \n", numSommet, tabsommet[compteur].tabOperationTemps);
        compteur++;
    }
    fclose(f);// fermeture du fichier
}

void tempsCycle(char *NOMFICHIER, t_sommet *tabsommet){
    FILE *f;
    int temp1;
    f = fopen(NOMFICHIER, "r");
    if(f==NULL){
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    for(int i=0; i< detecterNombreLignes(NOMFICHIER); i++){
        fscanf(f, "%d", &temp1);
        tabsommet[i].tabTemps_cycle = temp1;
        printf("Le temps du cycle est de %.2f secondes\n", tabsommet[i].tabTemps_cycle);
    }
    fclose(f);
}


void calcule_temps_tabsommet(t_sommet **box, int nbrBox,int *tailleBox)
{
    float time_to_return;
    for(int i=1; i<=nbrBox; i++){
        time_to_return=0;
        for(int j = 0; j < tailleBox[i]; j++)
        {
            if(time_to_return < box[i][j].tabOperationTemps)
            {
                time_to_return = box[i][j].tabOperationTemps;
            }
        }
        printf("La box %d a pour temps: %.2f\n", i, time_to_return);
    }
}

