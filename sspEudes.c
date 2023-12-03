//
// Created by antoi on 30/11/2023.
//

#include "mabibli.h"

///TODO Eudes transfert tes programmes ici et mets comme j'ai fait dans la biblio sinon depuis les
///TODO autres bibliotheques on peut pas appeler les autre programmes (apres supprimes ton .h)

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
        //fgetc(f); // Lire et ignorer le saut de ligne
        nombreLignes++; // Incrémente le compteur pour chaque ligne commençant par un nombre
    }

    fclose(f); // Ferme le fichier
    // printf("Nombre de lignes %d\n", nombreLignes);
    return nombreLignes;
}


int detecterPlusGrandNombre(char *NOMFICHIER)
{// le but ici est de detecter le plus grand ombre du fichier afin de donnaitre le nombre d'étape
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
    //printf("le plus grand nombre est %d\n",plusGrandNombre);// affichage du plus grand nombre
    return plusGrandNombre;// on renvoie le plus grand nombre
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

    int indice2 = 0;
    int indice1 = 0;

    int nbrLigne = detecterNombreLignes(NOMFICHIER); // detecte le nombre de ligne du fichier precedences.txt
    for (int i = 0; i < nbrLigne; ++i)
    {

        fscanf(f,"%d %d\n",&temp1,&temp2); // lis l'element puis son predecesseur



        indice2 = renvoie_sommet(temp2,tabsommet);
        //indice1 = renvoie_sommet(temp1,tabsommet);

        //printf("test %d %d %d %d %d\n",i,temp2,indice2,temp1,tabsommet[indice2].tabPrecedence[0]);

        compteur = 0;

        while (tabsommet[indice2].tabPrecedence[compteur] != 0)
        {

            compteur++;
        }

        tabsommet[indice2].tabPrecedence[compteur] = temp1; // rajoute l'element a la fin
        tabsommet[indice2].tabPrecedence = realloc(tabsommet[indice2].tabPrecedence,(compteur+2)*sizeof(int)); // realloue un nouvelle espace plus grand
        //printf("%d\n",tabsommet[indice2].tabPrecedence[0]);
        tabsommet[indice2].tabPrecedence[compteur + 1] = 0; //initialise l'element suivant a 0
        // remet le compteur a 0 pour que le prochain tableau soit de nouveau parcouru a partir de 0
    }
    fclose(f);
}