//
// Created by antoi on 30/11/2023.
//

#include "mabibli.h"

int renvoie_sommet(int num, t_sommet *tabsommet)
{
    for (int i = 0; i < tabsommet[0].nbrStep; i++)
    {
        if(tabsommet[i].num == num)
            return i;
    }
}

///fonction qui renvoie 1 tant que tous les sommets du tableau n'ont pas une box assigné
int sommetsAttrib(t_sommet* tabsommet)
{
    for (int i = 1; i < tabsommet[0].nbrStep; i++)
    {
        if(!tabsommet[i].boxexclu)
        {
            return 1;
        }
    }
    return 0;
}

void exclusion(char* NOMFICHER,t_sommet* tabsommet)
{
    FILE *f;
    int temp1,temp2;
    int indice1,indice2;
    int compteur = 0;
    f = fopen(NOMFICHER,"r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(-1) ; // Code d'erreur pour indiquer une erreur d'ouverture du fichier
    }

    int nbrLigne = detecterNombreLignes(NOMFICHER);
    printf("nombre de ligne : %d\n",nbrLigne);


    for (int i = 0; i < nbrLigne ; i++)// pour chaque ligne du fichier on a:
    {
        indice1 = 0;
        indice2 = 0;
        fscanf(f, "%d", &temp1);// Lecture du nombre
        fscanf(f, " ");// Consomme l'espace après le nombre
        fscanf(f, "%d", &temp2); // Lis l'autre nombre
        fscanf(f, "\n");// Passe à la ligne suivante
        //printf("test");

        printf("temp 1 :%d\t temp 2 : %d\n",temp1,temp2);

        indice1 = renvoie_sommet(temp1,tabsommet);
        indice2 = renvoie_sommet(temp2,tabsommet);

        while (tabsommet[indice1].tabExclusion[compteur] != 0) // on lit les lignes du tableau jusqu'à celle correspondant à la valeur que l'on veut exclure
        {
            compteur++;
            if (tabsommet[indice1].tabExclusion[compteur] == 0)
            {
                break;
            }
        }
        tabsommet[indice1].tabExclusion[compteur] = temp2;// on associe les valeurs exclues
        tabsommet[indice1].tabExclusion[compteur + 1] = 0;

        printf("%d / %d %d %d ",compteur,temp1,temp2,tabsommet[indice1].tabExclusion[compteur]);

        compteur = 0;
        while (tabsommet[indice2].tabExclusion[compteur] != 0)// on recommence le processus précédent dans l'autre sens, en effet l'exclusion se fait dans les deux sens
        {
            compteur++;
            if (tabsommet[indice2].tabExclusion[compteur] == 0)
            {
                break;
            }
        }
        tabsommet[indice2].tabExclusion[compteur] = temp1;
        tabsommet[indice2].tabExclusion[compteur + 1] = 0;

        printf("%d / %d  \ttemp1 : %d\n",tabsommet[indice2].tabExclusion[compteur],compteur,temp1);
        compteur = 0;
    }

    fclose(f);// fermeture du fichier



}

void BoxExclusion(t_sommet *tabsommet)
{

    int *tailleBox;
    int nbrBox = 2;
    tailleBox = malloc(sizeof (int )*(nbrBox));
    nbrBox = 0;
    tailleBox[0] = 0;
    t_sommet **BOX;

    BOX = malloc(sizeof (t_sommet*));

    for (int i = 0; i <= 1; i++)
    {
        BOX[i] = malloc(sizeof (t_sommet));
        BOX[i][0] = tabsommet[0];
        BOX[i][0].num = 0;

        if (!BOX[i])
        {
            printf("erreur allocation BOX %d",i);
            return;
        }
    }
    int compteurExclusion;
    int condition = 0;

    //// RÉPARTITION DES SOMMETS DANS LES BOX  ////

    do {
        for (int i = 0; i < tabsommet[0].nbrStep; i++)
        {

            condition = 0;

            if(tabsommet[i].boxexclu == 0)
            {
                for (int j = 0; j <= tailleBox[nbrBox]; j++)
                {
                    compteurExclusion = 0;
                    while (tabsommet[i].tabExclusion[compteurExclusion]!=0)
                    {
                        if (tabsommet[i].tabExclusion[compteurExclusion] == BOX[nbrBox][j].num)
                        {
                            condition = 1;
                            break;
                        }
                        compteurExclusion++;
                    }


                    if(condition)
                        break;
                }

                if (!condition)
                {
                    printf("box %d taille %d \n",nbrBox,tailleBox[nbrBox]);
                    for (int j = 0; j < tailleBox[nbrBox]; j++)
                    {
                        printf("sommet box %d, num %d, nom %d\n",nbrBox,j,BOX[nbrBox][j].num);
                    }
                    tabsommet[i].boxexclu = nbrBox ;
                    BOX[nbrBox][tailleBox[nbrBox]] = tabsommet[i];
                    tailleBox[nbrBox]++;
                    BOX[nbrBox] = realloc(BOX[nbrBox],sizeof (t_sommet ) * (tailleBox[nbrBox]+2));
                    BOX[nbrBox][tailleBox[nbrBox]] = tabsommet[0];
                }
            }
        }
        if(sommetsAttrib(tabsommet))
        {
            nbrBox++;
            tailleBox = realloc(tailleBox,sizeof (int)*(nbrBox+2));
            tailleBox[nbrBox] = 0;
            BOX = realloc(BOX,sizeof (t_sommet*) *(nbrBox+2));
            BOX[nbrBox] = malloc(sizeof (t_sommet)*(tailleBox[nbrBox]+2));
        } else
        {
            break;
        }
        printf("ATTRIB SOMMET : %d", sommetsAttrib(tabsommet));

    } while (sommetsAttrib(tabsommet));



    ///                     AFFICHAGE DES BOX                                  ////

    for (int compteur = 1 ; compteur <= nbrBox ; compteur++)
    {
        for (int i = 0; i <= tailleBox[compteur]; i++)
        {
            printf("----");
        }
        printf("------------------------\n");

        printf("Box %d :\t\t ",compteur);

        for (int i = 0; i < tailleBox[compteur] ; i++)
        {
            printf(" %d (%.2f)",BOX[compteur][i].num,BOX[compteur][i].tabOperationTemps);
        }

        printf("\n");

    }
    calcule_temps_tabsommet(BOX,nbrBox,tailleBox, tabsommet);
    free(BOX);
}

t_sommet *allouerTabSommet(char *NOMFICHIER,char *FILENAME,char *EXCLUSION)
{
    t_sommet *tabsommet;
    int test1,test2;
    int temp1,temp2;
    int plusgrandnombre;
    int compteur_nombre_sommet = 0;
    int *tabnumsommet;      //tableau permettant de stocker les sommets

    plusgrandnombre = detecterPlusGrandNombre(NOMFICHIER); //detecte le plus grand sommet

    tabnumsommet = (int *) malloc(sizeof (int ) * (plusgrandnombre /*+ 1*/ ) );

    FILE *f;

    f = fopen(NOMFICHIER,"r");

    if(f==NULL)
    {
        printf("erreur ouverture fichier allouer tableau sommet");
        exit(-1);
    }
    for (int i = 0; i < detecterNombreLignes(NOMFICHIER); i++)
    {

        test1 = 0;
        test2 = 0;
        fscanf(f,"%d %d\n",&temp1,&temp2);
        for (int j = 0; j <= compteur_nombre_sommet; j++)
        {
            if (temp1 == tabnumsommet[j])
            {
                test1 = 1;
            }
            if (temp2 == tabnumsommet[j])
            {
                test2 = 1;
            }
        }
        if(!test1)
        {
            printf("nouveau sommet : %d\n",temp1);
            tabnumsommet[compteur_nombre_sommet] = temp1;
            compteur_nombre_sommet++;
            /*tabnumsommet[compteur_nombre_sommet] = 0*/;
            test1 = 1;

        }
        if(!test2)
        {
            printf("nouveau sommet : %d\n",temp2);
            tabnumsommet[compteur_nombre_sommet] = temp2;
            compteur_nombre_sommet++;
            /*tabnumsommet[compteur_nombre_sommet] = 0*/;
            test2 = 1;

        }
    }
    fclose(f);

    tabsommet = (t_sommet *) malloc((compteur_nombre_sommet/*+1*/)*sizeof(t_sommet));

    for (int i = 0; i <= compteur_nombre_sommet; i++)
    {
        tabsommet[i].num = tabnumsommet[i];
        tabsommet[i].boxexclu = 0;
        tabsommet[i].nbrStep = compteur_nombre_sommet;// initialisation ici du nombre d'etape
        tabsommet[i].tabExclusion = malloc(compteur_nombre_sommet * sizeof (int ));// alloue dynamiquement un tableau d'exclusion pour le sommet i

        for (int j = 0; j < compteur_nombre_sommet; j++)
        {
            tabsommet[i].tabExclusion[j] = 0;
        }

        tabsommet[i].tabPrecedence = malloc(sizeof (int ));// alloue dynamiquement un tableau dde precedence pour le sommet i
        tabsommet[i].tabPrecedence[0]=0;
        tabsommet[i].boxexclu = 0;
        tabsommet[i].box = 0;
    }



///une fois qu'on a tous les sommets on cherche donc a le re classer dans l'ordre
///pour ca on fait un buffer de sommet

    t_sommet buffer;

    for (int i = 0; i < compteur_nombre_sommet; i++)
    {
        for (int j = 0; j < compteur_nombre_sommet; j++)
        {
            if(tabsommet[i].num < tabsommet[j].num)
            {
                buffer = tabsommet[i];
                tabsommet[i] = tabsommet[j];
                tabsommet[j] = buffer;
            }
        }
    }


    ///ici on fait des printf afin de verifier si les sommets sont bien trié
    printf("nombre de sommets : %d\n",compteur_nombre_sommet);
    for (int i = 0; i < compteur_nombre_sommet; i++)
    {
        printf("sommet n %d a comme nom %d\n",i,tabsommet[i].num);
    }
    /// tri validé

    ///on associe maintenant a chaque étape un temps

    precedences(NOMFICHIER,tabsommet);
    exclusion(EXCLUSION,tabsommet);
    operation(FILENAME,tabsommet);



    return tabsommet;
    /// renvoie l'initialisation de chaque sommet
}
///fonction qui renvoie 0 si tous les sommets ne sont pas attribuer a un box
///1 si tous les sommets sont placées dans un box
int attribTOT(t_sommet *tabsommet)
{
    for (int i = 0; i < tabsommet[0].nbrStep; i++)
    {
        if (tabsommet[i].box == 0)
            return 0;
    }
    return 1;
}


void trieBOXtot(t_sommet *tabsommet)
{
    ///On commence par voir les précédences puis apres on regarde les exclusions
    int condition = 0;
    float temps = 0;
    int compteurExclusion = 0;
    int test = 0;
    ///le test a pour valeur 0 si il ne remplis pas une des demande il prend la valeur de 1
    ///il se réinitialise a chaque changement de boucle
    int *tailleBox;
    int nbrBox = 1;
    tailleBox = malloc(sizeof (int )*(nbrBox+1));
    tailleBox[0] = 0;
    tailleBox[1] = 0;

    t_sommet **box;
    box = (t_sommet**) malloc(sizeof (t_sommet *)*2);
    box[0] = malloc(sizeof (t_sommet));
    box[1] = malloc(sizeof (t_sommet));

    int nbrPrecedences;
    int compteur_precedences;
    do {
        for (int i = 0 ; i < tabsommet[0].nbrStep; i++)
        {
            if(tabsommet[i].box == 0)
            {

                ///on commence par reegarder si le sommet a des précédances
                compteur_precedences = 0;
                nbrPrecedences = 0;
                test = 0;




                while (tabsommet[i].tabPrecedence[compteur_precedences] != 0) {
                    for (int j = 1; j <= nbrBox; j++) {
                        for (int k = 0; k < tailleBox[j]; k++)
                        {
                            printf("taille box %d : %d %u\n",j,k,box[j][k]);
                            if (tabsommet[i].tabPrecedence[compteur_precedences] == box[j][k].num) {
                              //  printf("BBBBBBBBBBBBBBBBBB\n");
                                nbrPrecedences++;
                            }
                        }
                    }
                    compteur_precedences++;
                }



                ///cela signifie que tous les sommets de précédences ont été placé dans chaque box
                if (nbrPrecedences == compteur_precedences) {
                    test = 0;

                } else
                    test = 1;

                printf("%d %d     %d %d\n",test,i,compteur_precedences,nbrPrecedences);


                ///si le sommet a passer les test de précédences alors on regarde la contrainte d'exclusion
                if (!test) {

                    condition = 0;


                    for (int j = 0; j < tailleBox[nbrBox]; j++) {
                        compteurExclusion = 0;
                        while (tabsommet[i].tabExclusion[compteurExclusion] != 0) {

                            if (tabsommet[i].tabExclusion[compteurExclusion] == box[nbrBox][j].num) {
                                condition = 1;
                                break;
                            }
                            compteurExclusion++;
                        }


                        if (condition)
                            break;

                    }

                    if (!condition) {

                        tabsommet[i].box = nbrBox;
                        //printf("AAAAAAAAAAAAAAAAAAA %.2f %d %d\n",tabsommet[i].tabOperationTemps,tailleBox[nbrBox],nbrBox);

                        box[nbrBox][tailleBox[nbrBox]] = tabsommet[i];


                        tailleBox[nbrBox]++;

                        //printf("box %d taille %d \n", nbrBox, tailleBox[nbrBox]);

                        for (int j = 0; j < tailleBox[nbrBox]; j++) {
                            printf("sommet box %d, num %d, nom %d, nom i : %d %d\n", nbrBox, j, box[nbrBox][j].num,tabsommet[i].num, i);
                        }
                        box[nbrBox] = realloc(box[nbrBox], sizeof(t_sommet) * (tailleBox[nbrBox] + 2));
                        box[nbrBox][tailleBox[nbrBox]] = tabsommet[0];
                        box[nbrBox][tailleBox[nbrBox]].num = 0;

                    }
                }
            }
        }
        if (!attribTOT(tabsommet))
        {
            ///on crée alors une nouvelle box
            nbrBox++;
            tailleBox =(int*) realloc(tailleBox,(nbrBox+2)*sizeof(int ));
            tailleBox[nbrBox] = 0;
            box = realloc(box,sizeof(t_sommet*) * (nbrBox+2));
            box[nbrBox] = malloc(sizeof(t_sommet)*(tailleBox[nbrBox]+2));

        }
    } while (!attribTOT(tabsommet));

                         /// MAINTENANT ON CHERCHE A AFFICHER NOS RESULTATS ///

    for (int i = 1; i <= nbrBox; i++)
    {
        temps = tempOpe(box[i],tailleBox[i]);
        printf("----------------------------------------------------------------------------------------\n");
        printf("||| STATION : %d |||  Nombre Operation : %d ||| Temp global : %.2f\n",i,tailleBox[i],temps);
        printf("----------------------------------------------------------------------------------------\n");

        for (int j = 0; j < tailleBox[i]; j++)
        {
            printf("%d\t",box[i][j].num);
        }
        printf("\n");
        printf("----------------------------------------------------------------------------------------\n");
        printf("\n");
        printf("\n");


    }
}

float tempOpe(t_sommet *tabsommet,int taille)
{
    float time_to_return = 0;
    for (int i = 0; i < taille; i++)
    {
        time_to_return += tabsommet[i].tabOperationTemps;

    }
    return time_to_return;
}
