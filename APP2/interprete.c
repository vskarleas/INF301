#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"

/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

void stop(void)
{
    char enter = '\0';
    printf("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n')
    {
        enter = getchar();
    }
}

/* Acte I.2 */
int interprete(sequence_t *seq, bool debug)
{
    // Version temporaire a remplacer par une lecture des commandes dans la
    // liste chainee et leur interpretation.

    char commande;
    sequence_t *pile = malloc(sizeof(sequence_t));

    //debug = true; /* À enlever par la suite et utiliser "-d" sur la ligne de commandes */

    printf("Programme:");
    afficher(seq);
    printf("\n");
    if (debug)
        stop();

    // À partir d'ici, beaucoup de choses à modifier dans la suite.
    commande = depiler(seq)->valeur.l;
    int ret; // utilisée pour les valeurs de retour

    while (seq->tete != NULL)
    { //à modifier: condition de boucle

        switch (commande)
        {
            /* Ici on avance tout le temps, à compléter pour gérer d'autres commandes */

        case 'A':
            ret = avance();
            if (ret == VICTOIRE)
                return VICTOIRE; /* on a atteint la cible */
            if (ret == RATE)
                return RATE; /* tombé dans l'eau ou sur un rocher */
            break;           /* à ne jamais oublier !!! */
        case 'G':
            gauche();
            break;
        case 'D':
            droite();
            break;
        case '+':
            addition(pile); /* Addition: depile les deux éléments en haut de la pile, les sommer, puis ré-empiler le résultat. */
            break;
        case '-':
            soustraction(pile); /* Soustraction: depile les deux éléments en haut de la pile, les soustraire, puis ré-empiler le résultat. */
            break;
        case '*':
            multiplication(pile); /* Multiplication: depile les deux éléments en haut de la pile, les sommer, puis ré-empiler le résultat. */
            break;
        case 'M':
            mesure(depiler_int(pile));
            break;
        case 'P':
            pose(depiler_int(pile));
            break;
        default:
            empiler_int(pile, commande-48); //pas joli !!! (soit faire - '0' soit faire un sscanf!)
            break;
        }

        /* Affichage pour faciliter le debug */
        afficherCarte();
        printf("Programme:");
        afficher(seq);
        printf("\n");
        if (debug)
            stop();
        commande = depiler(seq)->valeur.l;
    }

    /* Si on sort de la boucle sans arriver sur la cible,
     * c'est raté :-( */

    return CIBLERATEE;
}