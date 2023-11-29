//
// Created by aurel on 29/11/2023.
//

#ifndef ING2_TG_2023_2024_02_57_AURELIEN_H
#define ING2_TG_2023_2024_02_57_AURELIEN_H

#endif //ING2_TG_2023_2024_02_57_AURELIEN_H

void operation(char *NOMFICHIER,t_sommet *tabsommet){
    FILE *f;
    int temp1;
    float temp2;
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
        fscanf(f, "%d", &temp1);// Lecture du nombre
        fscanf(f, " ");// Consume l'espace après le nombre
        fscanf(f, "%f", &temp2); // Lis l'autre nombre
        fscanf(f, "\n");// Passe à la ligne suivante
        if(temp1!= compteur){
            do{
                tabsommet[compteur].tabOperationTemps = 0;
                compteur++;
            }while(temp1!=compteur);
        }
        tabsommet[compteur].tabOperationTemps = temp2;
        printf("%d %.2f \n",temp1,tabsommet[compteur].tabOperationTemps);
        compteur++;
    }
    fclose(f);// fermeture du fichier
    compteur=1;
    for(int i=0; i < nbrLigne; i++){
        if(tabsommet[compteur].tabOperationTemps== 0){
            do{
                totale = totale;
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


float calcule_temps_boites(){

}