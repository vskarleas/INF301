#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12108112 TREHIN", reponse);
    //On evoie en order les commandes suivantes
    char messages[100][100] = {"load projetX", "aide", "start", "veni vidi vici"}; //veni vidi vici etait decrypte en utilisant le l'agolirthme decryptage cesar pour le text de caseine
    int messages_len = 4;
    for (int i = 0; i < messages_len; i++)
    {
        envoyer_recevoir(messages[i], reponse);
    }

    

    printf ("Réponse du serveur: %s", reponse);

    //Connection termine
    printf ("Fin de la connection au serveur\n");
    return 0;
}
