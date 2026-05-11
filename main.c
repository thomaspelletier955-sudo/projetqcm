/*
 main.c
 centre du programme "Questions pour un Tekien".
 Affiche le menu principal et oriente l'utilisateur vers le mode Enseignant ou le mode Étudiant.
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "enseignant.h"
#include "etudiant.h"
 
int main(void) {
    int choix, continuer = 1;
 
    /* Cree le dossier qcm/ s'il n'existe pas.
    */
    system("mkdir -p " DOSSIER_QCM);





