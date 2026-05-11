#ifndef UTILS_H
#define UTILS_H

/*
 utils.h
 Constantes globales (#define) et prototype des fonctions
 utilitaires partagées dans tout le projet
 code couleur ANSI
*/
/* Mot de passe enseignant */
#define MOT_DE_PASSE "cytech2025"


/* Codes couleurs ANSI */
#define RESET    "\033[0m"
#define GRAS     "\033[1m"
#define ROUGE    "\033[31m"
#define VERT     "\033[32m"
#define JAUNE    "\033[33m"
#define BLEU     "\033[34m"
#define MAGENTA  "\033[35m"
#define CYAN     "\033[36m"
#define BLANC    "\033[37m"
#define FOND_BL  "\033[44m"
#define FOND_MG  "\033[45m"

/* Limites */
#define MAX_NOM          64
#define MAX_QUESTION     256
#define MAX_CHOIX        64
#define MAX_QUESTIONS    50
#define MAX_PROPOSITIONS 6



/* ============================================================
 * Structures
 * ============================================================ */
 
typedef struct {
    char intitule[MAX_QUESTION];
    char propositions[MAX_PROPOSITIONS][MAX_CHOIX];
    int  nb_propositions;
    int  bonnes_reponses[MAX_PROPOSITIONS];
    int  nb_bonnes_reponses;
} Question;
 
typedef struct {
    char     nom[MAX_NOM];
    int      nb_questions;
    Question questions[MAX_QUESTIONS];
    int      points_negatifs;
    int      reponses_multiples;
    int      mode_sequentiel;
} QCM;

