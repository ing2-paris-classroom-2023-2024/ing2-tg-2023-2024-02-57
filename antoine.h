//
// Created by antoi on 29/11/2023.
//

#ifndef ING2_TG_2023_2024_02_57_ANTOINE_H
#define ING2_TG_2023_2024_02_57_ANTOINE_H

#endif //ING2_TG_2023_2024_02_57_ANTOINE_H



///fonction qui renvoie 1 tant que tous les sommets du tableau n'ont pas une box assigné
int sommetsAttrib(t_sommet* tabsommet)
{
    for (int i = 1; i <= tabsommet[0].nbrStep; i++)
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
        for (int j = 0; j < tabsommet[0].nbrStep; j++)
        {
            if (tabsommet[j].num == temp1)
                indice1 = j;
            if (tabsommet[j].num == temp2)
                indice2 = j;
        }
        while (tabsommet[indice1].tabExclusion[compteur] != 0) // on lit les lignes du tableau jusqu'à celle correspondant à la valeur que l'on veut exclure
        {
            compteur++;
            if (tabsommet[indice1].tabExclusion[compteur] == 0)
            {
                break;
            }
        }
        tabsommet[indice1].tabExclusion[compteur] = temp2;// on associe les valeurs exclues
        //tabsommet[temp1].tabExclusion =(int *) realloc(tabsommet[temp1].tabExclusion, (compteur + 1) * sizeof(int) );// on alloue dynamiquement une nouvelle ligne
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
        //tabsommet[temp2].tabExclusion = (int *) realloc(tabsommet[temp2].tabExclusion, (compteur + 1) * sizeof(int));
        tabsommet[indice2].tabExclusion[compteur + 1] = 0;

        printf("%d / %d  \ttemp1 : %d\n",tabsommet[indice2].tabExclusion[compteur],compteur,temp1);
        compteur = 0;
    }

    fclose(f);// fermeture du fichier



}

void BoxExclusion(t_sommet *tabsommet)
{
    int *tailleBox;

    int nbrBox = 1;

    tailleBox = malloc(sizeof (int )*(nbrBox));

    nbrBox = 0;

    tailleBox[0] = 0;




    t_sommet **BOX;

    //printf("test\n");


    BOX = malloc(sizeof (t_sommet*) * 2);

    //printf("test\n");



    for (int i = 0; i < 2; i++)
    {
        BOX[i] = malloc(sizeof (t_sommet) * 2);
        BOX[i][0] = tabsommet[0];
        //printf("test\n");

        if (!BOX[i])
        {
            //printf("test box \n");
            printf("erreur allocation BOX %d",i);
            return;
        }
    }


    //printf("test sortie \n");



    //box1 = malloc(sizeof (int)*2);

    //printf("teSSTT\n");
    int compteurExclusion;
    //box1[0] = 0;
    int condition = 0;

    //// RÉPARTITION DES SOMMETS DANS LES BOX  ////

    do {
        for (int i = 0; i <= tabsommet[0].nbrStep; i++)
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
                        printf(" i : %d , condition %d , BOX[nbrBox][J].num %d \n",i,condition,BOX[nbrBox][j].num);
                        compteurExclusion++;
                    }
                    if(condition)
                        break;
                }
                //printf("test");

                if (!condition)
                {
                    printf("%d\n",tailleBox[nbrBox]);
                    tabsommet[i].boxexclu = nbrBox ;
                    BOX[nbrBox][tailleBox[nbrBox]] = tabsommet[i];
                    //printf("%d %d\n",nbrBox,tabsommet[i].num);
                    tailleBox[nbrBox]++;
                    BOX[nbrBox] = realloc(BOX[nbrBox],sizeof (t_sommet ) * (tailleBox[nbrBox]+2));
                    BOX[nbrBox][tailleBox[nbrBox]] = tabsommet[0];
                }
            }
        }
        if(sommetsAttrib(tabsommet))
        {
            //printf("taille box %d %d\n",nbrBox,tailleBox[nbrBox]);
            nbrBox++;
            tailleBox = realloc(tailleBox,sizeof (int)*(nbrBox+2));
            tailleBox[nbrBox] = 0;
            BOX = realloc(BOX,sizeof (t_sommet*) *(nbrBox+2));
            BOX[nbrBox] = malloc(sizeof (t_sommet)*(tailleBox[nbrBox]+2));
            //printf("test %d %d \n",tailleBox[nbrBox-1],tailleBox[nbrBox]);
        }
        //printf("taille box %d %d\n",nbrBox,tailleBox[nbrBox]);

    } while (sommetsAttrib(tabsommet));

    //printf("nombre box : %d\n",nbrBox);


    ///                     AFFICHAGE DES BOX                                  ////

    for (int compteur = 1; compteur <=nbrBox ; compteur++)
    {
        //printf("taille box %d : %d\n",compteur,tailleBox[compteur]);
        for (int i = 0; i <= tailleBox[compteur]; i++)
        {
            printf("----");
        }
        printf("------------------------\n");

        printf("Box %d :\t\t ",compteur);

        for (int i = 0; i < tailleBox[compteur] ; i++)
        {
            printf(" %d ",BOX[compteur][i].num);
        }

        printf("\n");

    }



    free(BOX);
}
