
/*
 etudiant.c
 mode étudiant : listing des QCM
 chargement depuis fichier, qcm interactif et calcul automatique de la note sur 20 points.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etudiant.h"
#include "utils.h"

/* Fichier temporaire utilise pour lister les QCM disponibles */
#define FICHIER_LISTE "/tmp/qcm_liste.txt"

/*
 lister_qcm
 Utilise system() pour lister les .txt du dossier qcm/ dans un fichier temporaire, puis le lit avec fscanf.
 Retourne le nombre de QCM trouves.
*/
int lister_qcm(char noms[MAX_QCM][MAX_NOM]) {
    FILE *f;
    int nb = 0;
    char nom_fichier[MAX_NOM];
    char commande[128];
    int len;

    /* Generer la liste des .txt dans un fichier temporaire */
    snprintf(commande, sizeof(commande),"ls %s*.txt",DOSSIER_QCM, FICHIER_LISTE);
    system(commande);

    f = fopen(FICHIER_LISTE, "r");
    if (f == NULL) {
        afficher_erreur("Impossible de lister les QCM.");
        return 0;
    }

    /* Chaque ligne contient un nom de fichier type "MonQCM.txt" */
    while (nb < MAX_QCM && fscanf(f, "%63s", nom_fichier) == 1) {
        len = (int)strlen(nom_fichier);
        /* Supprimer l'extension .txt */
        if (len > 4 && strcmp(nom_fichier + len - 4, ".txt") == 0) {
            strncpy(noms[nb], nom_fichier, len - 4);
            noms[nb][len - 4] = '\0';
            nb++;
        }
    }



