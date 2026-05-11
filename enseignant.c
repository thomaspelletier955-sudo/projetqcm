/* 
 enseignant.c
 mode enseignant : authentification,création de QCM et sauvegarde dans des fichiers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enseignant.h"
#include "utils.h"

/* 
  verifier_mot_de_passe
  Lit le mot de passe avec scanf %s et le compare a la constante.
  Retourne 1 si correct, 0 sinon.
 */
int verifier_mot_de_passe(void) {
    char saisie[MAX_NOM];
    printf(JAUNE "Mot de passe enseignant : " RESET);
    if (!lire_mot(saisie, sizeof(saisie))) {
        return 0;
    }
    if (strcmp(saisie, MOT_DE_PASSE) == 0) {
        afficher_succes("Authentification reussie !");
        return 1;
    }
    afficher_erreur("Mot de passe incorrect.");
    return 0;
}
 
/*
  saisir_oui_non
  Lit un caractere o/n avec scanf %c.
  Retourne 1 pour oui, 0 pour non.
  */
static int saisir_oui_non(void) {
    char c;
    scanf(" %c", &c);
    vider_buffer();
    return (c == 'o' || c == 'O') ? 1 : 0;
}
