/*
 utils.c
 Implémentation des fonctions utilitaires : affichage, construction de chemins de fichiers.
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"


/* Vide le buffer stdin jusqu'au prochain \n ou EOF */
void vider_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
 
void afficher_separateur(void) {
    printf(CYAN "================================================\n" RESET);
}

void afficher_erreur(const char *msg) {
    printf(ROUGE GRAS "[ERREUR] " RESET ROUGE "%s\n" RESET, msg);
}
 
void afficher_succes(const char *msg) {
    printf(VERT GRAS "[OK] " RESET VERT "%s\n" RESET, msg);
}
 
void attendre_entree(void) {
    printf(JAUNE "\nAppuyez sur Entree pour continuer..." RESET);
    vider_buffer();
}
 
/* Construit le chemin complet : qcm/<nom>.txt */
void construire_chemin(char *chemin, const char *nom) {
    snprintf(chemin, MAX_NOM * 2, "%s%s.txt", DOSSIER_QCM, nom);
}

/* 
 lire_ligne
 Lit une ligne entiere via fgets
 Consomme dabord le \n residuel eventuel laisse par un
 scanf precedent, puis lit la ligne et supprime son \n.
 Retourne 1 si ok, 0 sinon.
 */
int lire_ligne(char *buf, int taille) {
    int c;
    /* Consommer le \n ou les espaces residuels avant la ligne */
    c = getchar();
    if (c == EOF) { buf[0] = '\0'; return 0; }
    /* Si ce n'est pas un \n, c'est le debut de la ligne : on remet
     * le caractere "dans le buffer" en le copiant en premier */
    if (c != '\n') {
        buf[0] = (char)c;
        if (fgets(buf + 1, taille - 1, stdin) == NULL) {
            buf[strcspn(buf, "\n")] = '\0';
            return 1; /* on a deja le premier char */
        }
    } else {
        /* Le \n etait residuel, on lit la vraie ligne */
        if (fgets(buf, taille, stdin) == NULL) {
            buf[0] = '\0';
            return 0;
        }
    }
    buf[strcspn(buf, "\n")] = '\0';
    return 1;
}


