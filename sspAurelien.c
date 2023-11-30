//
// Created by antoi on 30/11/2023.
//

#include "mabibli.h"

void operation(char *NOMFICHIER,t_sommet *tabsommet){
    FILE *f;
    int numSommet;
    float temps;
    float totale;
    int compteur=1;
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
        if(numSommet != compteur){
            do{
                tabsommet[compteur].tabOperationTemps = 0;
                compteur++;
            }while(numSommet != compteur);
        }
        tabsommet[compteur].tabOperationTemps = temps;
        printf("%d %.2f \n", numSommet, tabsommet[compteur].tabOperationTemps);
        compteur++;
    }
    fclose(f);// fermeture du fichier
    compteur=1;
    for(int i=0; i < nbrLigne; i++){
        if(tabsommet[compteur].tabOperationTemps== 0){
            do{
                compteur++;
            }while(tabsommet[compteur].tabOperationTemps==0);
        }
        totale = totale + tabsommet[compteur].tabOperationTemps;
        printf("%.2f\n", totale);
        compteur++;
    }
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


float calcule_temps_tabsommet(t_sommet *tabsommet)
{
    float time_to_return = 0;
    int indice= 0;
    do{
        if(time_to_return < tabsommet[indice]. tabOperationTemps){
            time_to_return = tabsommet[indice].tabOperationTemps;
        }
        indice++;
    }while(tabsommet[indice].num != 0);
    return time_to_return;
}

