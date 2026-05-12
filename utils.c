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
    /* Lire la ligne avec fgets */
    if (fgets(buf, taille, stdin) != NULL) {
        
        /* Trouver le '\n' et le supprimer */
        char *p = strchr(buf, '\n');
        if (p) {
            *p = '\0';
        }
        return 1; // Tout s'est bien passé
    }
    
    return 0; // Erreur ou fin de fichier
}
