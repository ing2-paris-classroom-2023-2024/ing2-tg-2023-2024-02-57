//
// Created by antoi on 30/11/2023.
//

#include "mabibli.h"

/// ENREGISTRE LE NOMS DES OPERATIONS ET LEUR TEMPS D'EXECUTION
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
        //printf("%d %.2f \n", numSommet, tabsommet[compteur].tabOperationTemps);
        compteur++;
    }
    fclose(f);// fermeture du fichier
}
/// ENREGISTRE LE TEMPS DE CYCLE TOTALE
void tempsCycle(char *NOMFICHIER, t_sommet *tabsommet){
    FILE *f;
    float temp1;
    f = fopen(NOMFICHIER, "r");
    if(f==NULL){
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(-1);
    }
    fscanf(f, "%f", &temp1);
    for(int i=0; i < tabsommet[0].nbrStep ; i++)
    {
        tabsommet[i].tabTemps_cycle = temp1;
    }
    fclose(f);
}

/// CALCULE LE TEMPS MAXIMALE POUR QUE TOUTES LES STATIONS D'UNE BOXE SOIT EXECUTES
void calcule_temps_tabsommet(t_sommet **box, int nbrBox,int *tailleBox, t_sommet *tabsommet)
{
    char NOMFICHIER[32];
    strcpy(NOMFICHIER,"../temps_de_cycle.txt");
    float addition_temps= 0;
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
        addition_temps += time_to_return;
        printf("La box %d a pour temps: %.2f\n", i, time_to_return);
    }
    printf("Le temps totale de cycle est de: %.2f\n", addition_temps);
    printf("Le temps de cycle maximale etait de %.2f ", tabsommet[0].tabTemps_cycle);
    if(addition_temps < tabsommet[0].tabTemps_cycle){
       printf("donc le temps de cycle est finalement plus court que celui attendu\n");
    }
    else{
       printf("donc le temps de cycle depasse malheureusement les attentes\n");
    }
}

