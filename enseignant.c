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
int verifier_mot_de_passe() {
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
static int saisir_oui_non() {
    char c;
    scanf(" %c", &c);
    vider_buffer();
    return (c == 'o' || c == 'O') ? 1 : 0;
}

/* 
 saisir_question
 Remplit une Question : intitule, propositions, bonnes reponses.
 reponses_multiples : 1 = plusieurs bonnes reponses possibles.
 */
void saisir_question(Question *q, int reponses_multiples) {
    int i, index, ok;
    char lettre;
 
    /* Intitule de la question */
    printf(CYAN "  Intitule de la question : " RESET);
    lire_ligne(q->intitule, sizeof(q->intitule));
 
    /* Nombre de propositions */
    do {
        ok = 1;
        printf(CYAN "  Nombre de propositions (2 a %d) : " RESET, MAX_PROPOSITIONS);
        if (scanf("%d", &q->nb_propositions) != 1) {
            afficher_erreur("Entier attendu.");
            vider_buffer();
            ok = 0;
            continue;
        }
        vider_buffer();
        if (q->nb_propositions < 2 || q->nb_propositions > MAX_PROPOSITIONS) {
            afficher_erreur("Valeur hors limites.");
            ok = 0;
        }
    } while (!ok);
 
    /* Texte de chaque proposition */
    for (i = 0; i < q->nb_propositions; i++) {
        printf(CYAN "  Proposition %c : " RESET, 'A' + i);
        lire_ligne(q->propositions[i], sizeof(q->propositions[i]));
        q->bonnes_reponses[i] = 0; /* fausse par defaut */
    }
 
    /* Identification des bonnes reponses */
    q->nb_bonnes_reponses = 0;
 
    if (reponses_multiples) {
        /* On demande o/n pour chaque proposition */
        printf(JAUNE "  Indiquez les bonnes reponses (o/n) :\n" RESET);
        for (i = 0; i < q->nb_propositions; i++) {
            printf(CYAN "  Proposition %c correcte ? (o/n) : " RESET, 'A' + i);
            if (saisir_oui_non()) {
                q->bonnes_reponses[i] = 1;
                q->nb_bonnes_reponses++;
            }
        }
    } else {
        /* Une seule bonne reponse : l'enseignant entre la lettre */
        do {
            ok = 1;
            printf(CYAN "  Lettre de la bonne reponse (A-%c) : " RESET,
                   'A' + q->nb_propositions - 1);
            if (scanf(" %c", &lettre) != 1) {
                afficher_erreur("Caractere attendu.");
                vider_buffer();
                ok = 0;
                continue;
            }
            vider_buffer();
            if (lettre >= 'a' && lettre <= 'z') lettre = lettre - 'a' + 'A';
            index = lettre - 'A';
            if (index < 0 || index >= q->nb_propositions) {
                afficher_erreur("Lettre hors plage.");
                ok = 0;
            }
        } while (!ok);
 
        q->bonnes_reponses[index] = 1;
        q->nb_bonnes_reponses     = 1;
    }
 
    /* Securite : au moins une bonne reponse */
    if (q->nb_bonnes_reponses == 0) {
        afficher_erreur("Aucune bonne reponse : A definie par defaut.");
        q->bonnes_reponses[0]  = 1;
        q->nb_bonnes_reponses  = 1;
    }
}
 
/* 
 sauvegarder_qcm
 Ecrit le QCM dans un fichier texte : qcm/<nom>.txt
 Format : nom / parametres / nb_questions / questions
 Retourne 1 si succes, 0 sinon.
 */
int sauvegarder_qcm(const QCM *qcm) {
    int  i, j;
    char chemin[MAX_NOM * 2];
    FILE *f;
 
    construire_chemin(chemin, qcm->nom);
    f = fopen(chemin, "w");
    if (f == NULL) {
        printf(ROUGE "Chemin tente : %s\n" RESET, chemin);
        afficher_erreur("Impossible de creer le fichier. Verifiez que le dossier qcm/ existe.");
        return 0;
    }
 
    fprintf(f, "%s\n", qcm->nom);
    fprintf(f, "%d %d %d\n",
            qcm->points_negatifs,
            qcm->reponses_multiples,
            qcm->mode_sequentiel);
    fprintf(f, "%d\n", qcm->nb_questions);
 
    for (i = 0; i < qcm->nb_questions; i++) {
        const Question *q = &qcm->questions[i];
        fprintf(f, "%s\n", q->intitule);
        fprintf(f, "%d\n", q->nb_propositions);
        for (j = 0; j < q->nb_propositions; j++) {
            fprintf(f, "%s\t%d\n", q->propositions[j], q->bonnes_reponses[j]);
        }
    }
 
    fclose(f);
    return 1;
}
 
/*
  creer_qcm
  construire un QCM depuis zero.
 */
void creer_qcm(void) {
    QCM qcm;
    int i, ok;
 
    memset(&qcm, 0, sizeof(QCM));
 
    printf("\n");
    afficher_separateur();
    printf(FOND_MG BLANC GRAS " CREATION D'UN NOUVEAU QCM " RESET "\n");
    afficher_separateur();
 
    /* Nom du QCM */
    printf(JAUNE "Nom du QCM (sans espaces) : " RESET);
    if (!lire_mot(qcm.nom, sizeof(qcm.nom))) {
        afficher_erreur("Nom invalide.");
        return;
    }
 
    /* Parametres du QCM */
    printf(JAUNE "Points negatifs ? (o/n) : " RESET);
    qcm.points_negatifs = saisir_oui_non();
 
    printf(JAUNE "Reponses multiples ? (o/n) : " RESET);
    qcm.reponses_multiples = saisir_oui_non();
 
    printf(JAUNE "Mode sequentiel (obliger a repondre) ? (o/n) : " RESET);
    qcm.mode_sequentiel = saisir_oui_non();
 
    /* Nombre de questions */
    do {
        ok = 1;
        printf(JAUNE "Nombre de questions (1 a %d) : " RESET, MAX_QUESTIONS);
        if (scanf("%d", &qcm.nb_questions) != 1) {
            afficher_erreur("Entier attendu.");
            vider_buffer();
            ok = 0;
            continue;
        }
        vider_buffer();
        if (qcm.nb_questions < 1 || qcm.nb_questions > MAX_QUESTIONS) {
            afficher_erreur("Valeur hors limites.");
            ok = 0;
        }
    } while (!ok);
 
    /* Saisie des questions */
    for (i = 0; i < qcm.nb_questions; i++) {
        printf(MAGENTA "\n-- Question %d/%d --\n" RESET, i + 1, qcm.nb_questions);
        saisir_question(&qcm.questions[i], qcm.reponses_multiples);
    }
 
    /* Sauvegarde */
    printf("\n");
    if (sauvegarder_qcm(&qcm)) {
        afficher_succes("QCM sauvegarde avec succes !");
        printf(VERT "  Fichier : qcm/%s.txt\n" RESET, qcm.nom);
    }
    attendre_entree();
}
 
/*
 menu_enseignant
 Boucle du menu enseignant.
 */
void menu_enseignant(void) {
    int choix, continuer = 1;
 
    while (continuer) {
        printf("\n");
        afficher_separateur();
        printf(FOND_MG BLANC GRAS " MODE ENSEIGNANT " RESET "\n");
        afficher_separateur();
        printf(MAGENTA "  1." RESET " Creer un nouveau QCM\n");
        printf(MAGENTA "  2." RESET " Retour au menu principal\n");
        afficher_separateur();
        printf(JAUNE "Votre choix : " RESET);
 
        if (scanf("%d", &choix) != 1) {
            afficher_erreur("Entier attendu.");
            vider_buffer();
            continue;
        }
        vider_buffer();
 
        switch (choix) {
            case 1: creer_qcm(); break;
            case 2: continuer = 0; break;
            default: afficher_erreur("Choisissez 1 ou 2.");
        }
    }
}
 
