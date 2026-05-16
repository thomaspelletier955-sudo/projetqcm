#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "enseignant.h"
#include "etudiant.h"

int main(void) {
    int choix;

    /* Cree le dossier qcm/ s'il n'existe pas */
    system("mkdir -p " DOSSIER_QCM);

    while (1) {
        printf("\n");
        titre();
        printf(BLEU "  1." RESET " Mode Etudiant   - Passer un QCM\n");
        printf(BLEU "  2." RESET " Mode Enseignant  - Creer un QCM\n");
        printf(BLEU "  3." RESET " Quitter\n");
        sep();
        printf(JAUNE "Choix : " RESET);
        choix = lire_int();

        if      (choix == 1) menu_etudiant();
        else if (choix == 2) { if (verifier_mot_de_passe()) menu_enseignant(); }
        else if (choix == 3) { printf(VERT "\nAu revoir !\n\n" RESET); break; }
        else                 erreur("Choisissez 1, 2 ou 3.");
    }
    return EXIT_SUCCESS;
}
