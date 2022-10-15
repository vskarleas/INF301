#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"

/*
 *  Auteur(s) : 
 *  Date :
 *  Suivi des Modifications :
 *
 */

bool silent_mode = false;


cellule_t* nouvelleCellule (void) // Créé une nouvelle cellule
{
    cellule_t *cell = malloc (sizeof (cellule_t));
    return cell;
}


void detruireCellule (cellule_t* cel)
{
    free(cel);
}

/* Acte I.1 */
void conversion (char *texte, sequence_t *seq) // Converti une chaine de caractere en sequence (liste chainee) de caracteres
{
    cellule_t *cell;
    int lg_texte = strlen(texte);
    for (int i = lg_texte; i >= 0; i--)
    {
        cell = nouvelleCellule();
        cell->valeur.l = texte[i];
        cell->type_valeur = CHAR;
        ajout_debut(seq, cell);
    }
}
/* ----------- */

void afficher (sequence_t* seq)
{
    assert (seq); /* Le pointeur doit être valide */
    cellule_t *cell_actuelle = seq->tete;
    while (cell_actuelle != NULL)
    {
        if (cell_actuelle->type_valeur == INT){
            printf("%d ", cell_actuelle->valeur.n);
        }
        if (cell_actuelle->type_valeur == CHAR)
        {
            printf("%c ", cell_actuelle->valeur.l);
        }
        if (cell_actuelle->type_valeur == CHAR_LISTE)
        {
            afficher(cell_actuelle->valeur.s);
        }
        cell_actuelle = cell_actuelle->suivant;
    }
    printf("\n");
}

void ajout_debut(sequence_t * seq, cellule_t *nouvelle_tete) // Ajoute une nouvelle cellule avec la commande passée en argument au debut de la sequence
{
    // Insertion en modifiant les references
    nouvelle_tete->suivant = seq->tete;
    seq->tete = nouvelle_tete;
}

/* Acte II */
void empiler_int(sequence_t *pile, int n) //Ajout au debut de notre pile un entier
{
    cellule_t *cell = nouvelleCellule();
    cell->valeur.n = n;
    cell->type_valeur = INT; //definit que le typage de notre action d'empilage est un entier
    empiler(pile, cell);
}

void empiler_char(sequence_t *pile, char n) //Ajout au debut de notre pile un caracter
{
    cellule_t *cell = nouvelleCellule();
    cell->valeur.l = n;
    cell->type_valeur = CHAR; //definit que le typage de notre action d'empilage est un caracter
    empiler(pile, cell);
}

void empiler_seq(sequence_t *pile, sequence_t *n) //Ajout au debut de notre pile une sequence
{
    cellule_t *cell = nouvelleCellule();
    cell->valeur.s = n;
    cell->type_valeur = CHAR_LISTE; //definit que le typage de notre action d'empilage est une sequence
    empiler(pile, cell);
}

void retirer_tete(sequence_t *seq) //Supprime le tete de la sequence en definisant comme tete l'ement suivant de la sequence
{
    seq->tete = seq->tete->suivant;
}

cellule_t *tete(sequence_t *seq) //Retourne le tete de notre sequence comme une cellule
{
    return seq->tete;
}

cellule_t *depiler(sequence_t *seq) //
{
    cellule_t *cell = tete(seq);
    retirer_tete(seq);
    return cell;
}

int depiler_int(sequence_t *pile) //Suprime le premier element (entier) par le pile tout en retournant sa valeur
{
    return depiler(pile)->valeur.n;
}

char depiler_char(sequence_t *pile) //Suprime le premier element (character) par le pile tout en retournant sa valeur
{
    return depiler(pile)->valeur.l;
}

sequence_t *depiler_seq(sequence_t *pile) //Suprime le premier element (character) par le pile tout en retournant sa valeur
{
    return depiler(pile)->valeur.s;
}

void addition(sequence_t *pile) //Addition entre deux elements de la pile (le resulat est empile sur le pile)
{
    int x = depiler_int(pile);
    int y = depiler_int(pile);
    empiler_int(pile, x + y);
}

void soustraction(sequence_t *pile) //Soustraction entre deux elements de la pile (le resulat est empile sur le pile)
{
    int x = depiler_int(pile);
    int y = depiler_int(pile);
    empiler_int(pile, x - y);
}

void multiplication(sequence_t *pile) //Multiplication entre deux elements de la pile (le resulat est empile sur le pile)
{
    int x = depiler_int(pile);
    int y = depiler_int(pile);
    empiler_int(pile, x * y); 
}

/* Acte V */
/*
void clone(sequence_t *pile)
{
    if (depiler(pile)->type_valeur == INT){
        cellule_t *cell = tete(pile);

    }
    else if (depiler(pile)->type_valeur == CHAR){

    }
    else if (depiler(pile)->type_valeur == CHAR_LISTE)
    {

    }
}
*/

/*
//Il me semble beaucoup à la fonctionalité retirer_tete
void ignore(sequence_t *pile)
{
    retirer_tete(pile);
}
*/

/*
void echange(sequence_t *pile)
{
    if (depiler(pile)->type_valeur == INT){
        int x = depiler_int(pile);
        int y = depiler_int(pile);
        empiler_int(pile, x); 
        empiler_int(pile, y); 
    }
    else if (depiler(pile)->type_valeur == CHAR){
        char xi = depiler_char(pile);
        char yi = depiler_char(pile);
        empiler_char(pile, xi); 
        empiler_char(pile, yi); 
    }
    else if (depiler(pile)->type_valeur == CHAR_LISTE)
    {
        cellule_t *cell1 = depiler_seq(pile);
        cellule_t *cell2 = depiler_seq(pile);
        empiler_seq(pile, cell1);
        empiler_seq(pile, cell1);
    }
}
*/