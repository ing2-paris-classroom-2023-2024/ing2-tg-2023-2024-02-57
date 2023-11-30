//
// Created by eudes on 22/11/2023.
//

#ifndef ING2_TG_2023_2024_02_57_MABIBLI_H
#define ING2_TG_2023_2024_02_57_MABIBLI_H

#endif //ING2_TG_2023_2024_02_57_MABIBLI_H

#include "time.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct sommet
{
    int num;
    int boxexclu;
    int* tabExclusion;
    int nbrStep;
    int* tabPrecedence;
    float tabOperationTemps;
    float tabTemps_cycle;
}t_sommet;

int detecterNombreLignes(char* NOMFICHIER);
t_sommet *allouerTabSommet(char *NOMFICHIER,char *FILENAME);
int renvoie_sommet(int num, t_sommet *tabsommet);
int sommetsAttrib(t_sommet* tabsommet);
void exclusion(char* NOMFICHER,t_sommet* tabsommet);
void BoxExclusion(t_sommet *tabsommet);
void operation(char *NOMFICHIER,t_sommet *tabsommet);
void tempsCycle(char *NOMFICHIER, t_sommet *tabsommet);
float calcule_temps_tabsommet(t_sommet *tabsommet);
void boxPrecedences(t_sommet *tabsommet);
void precedences(char *NOMFICHIER,t_sommet *tabsommet);
void impressionSommetPrecedence(t_sommet *tabsommet);
int detecterPlusGrandNombre(char *NOMFICHIER);

