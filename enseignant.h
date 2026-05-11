#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H

/*
 enseignant.h
 fonctions du mode enseignant
 authentification création et sauvegarde de QCM
*/

#include "utils.h"
 
int  verifier_mot_de_passe(void);
void menu_enseignant(void);
void creer_qcm(void);
int  sauvegarder_qcm(const QCM *qcm);
void saisir_question(Question *q, int reponses_multiples);
 
#endif
 
