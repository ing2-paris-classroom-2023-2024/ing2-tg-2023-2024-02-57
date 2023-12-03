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
        fgetc(f); // Lire et ignorer le saut de ligne
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
    printf("le plus grand nombre est %d\n",plusGrandNombre);// affichage du plus grand nombre
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

        printf("test %d %d %d %d %d\n",i,temp2,indice2,temp1,tabsommet[indice2].tabPrecedence[0]);

        compteur = 0;

        while (tabsommet[indice2].tabPrecedence[compteur] != 0)
        {

            compteur++;
        }

        tabsommet[indice2].tabPrecedence[compteur] = temp1; // rajoute l'element a la fin
        tabsommet[indice2].tabPrecedence = realloc(tabsommet[indice2].tabPrecedence,(compteur+2)*sizeof(int)); // realloue un nouvelle espace plus grand
        printf("%d\n",tabsommet[indice2].tabPrecedence[0]);
        tabsommet[indice2].tabPrecedence[compteur + 1] = 0; //initialise l'element suivant a 0
        // remet le compteur a 0 pour que le prochain tableau soit de nouveau parcouru a partir de 0
    }
    fclose(f);
}

void boxPrecedences(t_sommet *tabsommet) {
    int nbOperations = tabsommet[0].nbrStep;
    t_sommet** box = malloc(sizeof(t_sommet*) * 10); // Allocation de 10 pointeurs pour les boîtes
    int* tailleBox = malloc(sizeof(int) * 10); // Allocation de 10 entiers pour les tailles de boîtes
    for (int i = 0; i < 10; ++i) {
        tailleBox[i] = 0;
    }

    if (box == NULL || tailleBox == NULL) {
        printf("Erreur lors de l'allocation de memoire.\n");
        return;
    }

    for (int i = 0; i < 10; ++i) {
        box[i] = malloc(sizeof(t_sommet) * (nbOperations + 1)); // Allocation des boîtes
        if (box[i] == NULL) {
            printf("Erreur lors de l'allocation de memoire pour box[%d].\n", i);
            for (int j = 0; j < i; ++j) {
                free(box[j]);
            }
            free(box);
            free(tailleBox);
            return;
        }
    }
    for (int i = 0; i < nbOperations; ++i) {
        for (int precedenceATROUVER = 0; tabsommet[i].tabPrecedence[precedenceATROUVER] != 0; ++precedenceATROUVER) {
            printf("nombre preceddence a trouver%d\n",precedenceATROUVER);
        }
    }
    /*   for (int i = 0; i < nbOperations; ++i) {
           if (tabsommet[i].tabPrecedence[0] == 0) {
               box[0][tailleBox[0]] = tabsommet[i];
               printf("ajout box 1\n");
               tailleBox[0]++;
           } else {
               int allPrecedencesFound = 1;
               for (int compteur = 0; tabsommet[i].tabPrecedence[compteur] != 0; ++compteur) {
                   int precedencesFound = 0;
                   for (int j = 0; j < tailleBox[0]; ++j) {
                       if (tabsommet[i].tabPrecedence[compteur] == box[0][j].num) {
                           precedencesFound = 1;
                           break;
                       }
                   }
                   if (!precedencesFound) {
                       allPrecedencesFound = 0;
                       break;
                   }
               }
               if (allPrecedencesFound) {
                   box[1][tailleBox[1]] = tabsommet[i];
                   printf("ajout box 2\n");
                   tailleBox[1]++;
               } else {
                   allPrecedencesFound = 1;
                   for (int compteur = 0; tabsommet[i].tabPrecedence[compteur] != 0; ++compteur) {
                       int precedencesFound = 0;
                       for (int j = 0; j < tailleBox[1]; ++j) {
                           if (tabsommet[i].tabPrecedence[compteur] == box[1][j].num) {
                               precedencesFound = 1;
                               break;
                           }
                       }
                       if (!precedencesFound) {
                           allPrecedencesFound = 0;
                           break;
                       }
                   }
                   if (allPrecedencesFound) {
                       box[2][tailleBox[2]] = tabsommet[i];
                       printf("ajout box 3\n");
                       tailleBox[2]++;
                   } else {
                       allPrecedencesFound = 1;
                       for (int compteur = 0; tabsommet[i].tabPrecedence[compteur] != 0; ++compteur) {
                           int precedencesFound = 0;
                           for (int j = 0; j < tailleBox[2]; ++j) {
                               if (tabsommet[i].tabPrecedence[compteur] == box[2][j].num) {
                                   precedencesFound = 1;
                                   break;
                               }
                           }
                           if (!precedencesFound) {
                               allPrecedencesFound = 0;
                               break;
                           }
                       }
                       if (allPrecedencesFound) {
                           box[3][tailleBox[3]] = tabsommet[i];
                           printf("ajout box 4\n");
                           tailleBox[3]++;
                       }
                   }
               }
           }
       }
   */
    for (int i = 0; i < 4; ++i) {
        printf("\n_________Box %d : ", i + 1);
        for (int j = 0; j < tailleBox[i]; ++j) {
            printf(" %d ", box[i][j].num);
        }
    }

    for (int i = 0; i < 4; ++i) {
        free(box[i]); // Libération de la mémoire allouée pour les boîtes
    }
    free(box);
    free(tailleBox); // Libération de la mémoire allouée pour les tableaux de tailles
}



void impressionSommetPrecedence(t_sommet *tabsommet){
    int nbOperations= tabsommet[0].nbrStep;
    int compteur = 0;
    for (int i = 1; i <= nbOperations; i++){
        compteur=0;
        while (tabsommet[i].tabPrecedence[compteur] != 0)
        {
            printf("%d a comme antecedant %d\n",i,tabsommet[i].tabPrecedence[compteur]); ///montre les precedences de chaque tache
            compteur++;
            if (tabsommet[i].tabPrecedence[compteur] == 0 ) {
                break; // parcourt le tableau de precedence jusqua la fin
            }
        }
        printf("  %d a %d antecedant\n\n",i,compteur); /// montre combien de precedence a cette tache
    }
}