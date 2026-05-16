#include <stdio.h>
#include <string.h>
#include "utils.h"

void vider_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void sep(void) {
    printf(CYAN "==========================================\n" RESET);
}

void titre(void) {
    sep();
    printf(FBLEU GRAS BLANC "   QUESTIONS POUR UN TEKIEN - Gestion QCM   " RESET "\n");
    printf(BLEU "        CY Tech - preING1 - 2025-2026\n" RESET);
    sep();
}

void erreur(const char *msg) {
    printf(ROUGE "[ERREUR] %s\n" RESET, msg);
}

void ok(const char *msg) {
    printf(VERT "[OK] %s\n" RESET, msg);
}

void attendre(void) {
    printf(JAUNE "\nAppuyez sur Entree..." RESET);
    vider_buffer();
}

/* Lit une ligne entiere avec fgets et enleve le \n */
void lire(char *buf, int taille) {
    if (fgets(buf, taille, stdin) != NULL)
        buf[strcspn(buf, "\n")] = '\0';
}

/* Lit un entier, vide le buffer et retourne la valeur (-1 si erreur) */
int lire_int(void) {
    int n;
    char reste;
    /* On verifie que la saisie est bien un entier et rien d autre */
    if (scanf("%d%c", &n, &reste) != 2 || reste != '\n') {
        vider_buffer();
        return -1;
    }
    return n;
}
