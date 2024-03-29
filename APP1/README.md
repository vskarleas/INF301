# Calendrier

> Le projet APP1 est bien terminé. Vous pouvez telecharger le fichier ZIP avec le code de tous les clients, le Makefile et les algos à **http://dev.madebyvasilis.site/inf301-app1.zip**

## 13/9/2022 Premier seance TD

- Departition des roles
- Probleme
  - On veut decrypter des messages qui sont echnagé entre Alice et Bob. Ils sont utlise des lettres majuscules et miniscules.
- Discussion sur l'alorythme (du groupe)) suivante
  - Paer definiton on a une fonctionne qui lit un ligne
  - On a evidement besoin une deuxieme fonctinne qui lit les characteres de la ligne on utilise la logique suivante qui etait proposé penandt la premiere seance. On considere un 2-uplet (u,v)) pour chaque lettre lu par la fonctione specifique. u=lettre lu & v=nombre de decalage (pour l'instant on sait le decalage ~ *il sera etre modifié par une autre fonctionne*):
    - Si ce n'est pas un lettre (ex: point, espace, ! etc.) on ne touche pas, sinon
    - On verifie si c'est un lettre majuscule ou miniscule et on avance selon:
      - Si c'est un lettre majuscule, alors on reste entre les limites des indices de code d'ASCII pour les lettres najuscules
        - On applique la formule qu'on a trouvé:
          ```
          ((lettre-'A')+decalage)%26 + 'A'
          ```
      - Si c'est un lettre miniscule, alors on reste entre les limites des indices de code d'ASCII pour les lettres miniscules
        - On applique la formule qu'on a trouvé:
          ```
          ((lettre-'a')+decalage)%26 + 'a'
          ```
- Creation du programme qui prend un message et qui le decrypte selon un decalage donne pour l'alphabet. Le code est sur le fichier **algo1.c**.
- L'algorythme est le suivante:
  - ```
    #include <stdio.h>
    #include <string.h>
    char remplacer_lettre(char lettre, int decalage){
        if(lettre>='A' && lettre<='Z'){
            return (((lettre-'A')+decalage)%26+'A');
        }else if(lettre>='a' && lettre<='z'){
            return (((lettre - 'a') + decalage) % 26 + 'a');
        }else{
            return lettre;
        }
    }

    void remplacer_texte(char* nom_fichier_code, int decalage){
        FILE* fichier_code = fopen(nom_fichier_code,"r");
        char nom_fichier_decode[512];
        strcpy(nom_fichier_decode,nom_fichier_code);
        strcat(nom_fichier_decode, "_decode");
        FILE *fichier_decode = fopen(nom_fichier_decode, "w");
        char lettre;
        fscanf(fichier_code, "%c", &lettre);
        while(!feof(fichier_code)){
            char lettre_decode = remplacer_lettre(lettre, decalage);
            fprintf(fichier_decode, "%c", lettre_decode);
            fscanf(fichier_code, "%c", &lettre);
        }
        fclose(fichier_code);
        fclose(fichier_decode);
    }

    int main() {
        remplacer_texte("message-secret_Caseine.txt", 21);
    }
    ```

## 15/9/2022 Premier seance de TP

* Exercise pereparatoire est veirfié avec des tests
* Travail sur le decodage du programme
* tutoriel est terminé
* TUTORIEL est terminé
* projectX est terminé
* But pour la prochaine seance est de trouver an algorythm qui crypte un message.
* Le message projectX de Bob et Alice est decrypté

  ```
  Chere Alice,

  Je crois que nous sommes sur ecoute, nous allons devoir changer notre methode 
  de chiffrement. J'ai une petite idee derriere la tete pour cela. Vu la 
  situation, nous ne pouvons etre trop prudents avant de passer au plan prevu.
  Je te laisse un prochain message dans l'exercice 'crypteMove', reste vigilante 
  et efface tes traces.

  Au fait, la solution pour reussir projetX est d'envoyer "veni vidi vici" au serveur. Tu 
  auras ainsi acces a l'exercice 'crypteMove'.

  Bien a toi,
  Bob.

  PS : Si tu as le temps, j'ai mis des codes secrets pour ce que tu sais dans 
  l'exercice challenge 'planB' mais ce n'est pas la priorite pour l'instant. En 
  cas de doute, retrouve-moi plutot rapidement sur crypteMove.
  ```

## 20/9/2022 Seance TD

* Discussion sur l'agorithme CrypteMove par l'APP1.
* Les indices de l'agorytme sont les suivantes (on a les pris via l'AppoLab):

  ```

  >>>recu >>> Durant l'encryption, nous allons modifier l'ordre des lettres du texte selon>>> recu >>> des regles bien etablies. Voici le principe :
  >>> recu >>> - soit TXT la sequence des caracteres a encrypter
  >>> recu >>> - soit ENC la sequence de sortie
  >>> recu >>>   (au debut, ENC est vide)
  >>> recu >>> - j'effectue ensuite la manipulation suivante:
  >>> recu >>>   * je prends C le premier caractere de TXT et le rajoute a la fin de ENC
  >>> recu >>>   * soit X le code ASCII de C modulo 8 (par exemple pour la lettre 'b', son
  >>> recu >>>     code ASCII est 98 donc X = 2)
  >>> recu >>>   * je prends les X premiers caracteres de TXT et les deplace a la fin de TXT
  >>> recu >>>     (s'il reste au moins X caracteres dans TXT)
  >>> recu >>>   * je recommence jusqu'a ce que TXT soit vide
  >>> recu >>> - a la fin, ENC contiendra le message encrypte.
  >>> recu >>>
  >>> recu >>> Je te donne un exemple sur le message suivant :
  >>> recu >>>       "Petit message court."

  >>>recu >>> PS: Pour t'aider, voici la trace d'execution sur "Petit message court."
  >>>recu >>> 
  >>>recu >>> TXT:Petit message court.
  >>>recu >>> ENC: <vide>
  >>>recu >>> C = P
  >>>recu >>> 
  >>>recu >>> TXT:etit message court.
  >>>recu >>> ENC:P
  >>>recu >>> C = e
  >>>recu >>> 
  >>>recu >>> TXT:essage court.tit m
  >>>recu >>> ENC:Pe
  >>>recu >>> C = e
  >>>recu >>> 
  >>>recu >>> TXT: court.tit mssage
  >>>recu >>> ENC:Pee
  >>>recu >>> C =  
  >>>recu >>> 
  >>>recu >>> TXT:court.tit mssage
  >>>recu >>> ENC:Pee 
  >>>recu >>> C = c
  >>>recu >>> 
  >>>recu >>> TXT:t.tit mssageour
  >>>recu >>> ENC:Pee c
  >>>recu >>> C = t
  >>>recu >>> 
  >>>recu >>> TXT: mssageour.tit
  >>>recu >>> ENC:Pee ct
  >>>recu >>> C =  
  >>>recu >>> 
  >>>recu >>> TXT:mssageour.tit
  >>>recu >>> ENC:Pee ct 
  >>>recu >>> C = m
  >>>recu >>> 
  >>>recu >>> TXT:our.titssage
  >>>recu >>> ENC:Pee ct m
  >>>recu >>> C = o
  >>>recu >>> 
  >>>recu >>> TXT:sageur.tits
  >>>recu >>> ENC:Pee ct mo
  >>>recu >>> C = s
  >>>recu >>> 
  >>>recu >>> TXT:ur.titsage
  >>>recu >>> ENC:Pee ct mos
  >>>recu >>> C = u
  >>>recu >>> 
  >>>recu >>> TXT:sager.tit
  >>>recu >>> ENC:Pee ct mosu
  >>>recu >>> C = s
  >>>recu >>> 
  >>>recu >>> TXT:r.titage
  >>>recu >>> ENC:Pee ct mosus
  >>>recu >>> C = r
  >>>recu >>> 
  >>>recu >>> TXT:itage.t
  >>>recu >>> ENC:Pee ct mosusr
  >>>recu >>> C = i
  >>>recu >>> 
  >>>recu >>> TXT:age.tt
  >>>recu >>> ENC:Pee ct mosusri
  >>>recu >>> C = a
  >>>recu >>> 
  >>>recu >>> TXT:e.ttg
  >>>recu >>> ENC:Pee ct mosusria
  >>>recu >>> C = e
  >>>recu >>> 
  >>>recu >>> TXT:.ttg
  >>>recu >>> ENC:Pee ct mosusriae
  >>>recu >>> C = .
  >>>recu >>> 
  >>>recu >>> TXT:ttg
  >>>recu >>> ENC:Pee ct mosusriae.
  >>>recu >>> C = t
  >>>recu >>> 
  >>>recu >>> TXT:tg
  >>>recu >>> ENC:Pee ct mosusriae.t
  >>>recu >>> C = t
  >>>recu >>> 
  >>>recu >>> TXT:g
  >>>recu >>> ENC:Pee ct mosusriae.tt
  >>>recu >>> C = g
  >>>recu >>> 
  >>>recu >>> TXT: <vide>
  >>>recu >>> ENC:Pee ct mosusriae.ttg
  ```
* Le texte qu'on doit crypter est le suivante:

  * ```
    >>>recu >>> Chere Alice,
    >>>recu >>> 
    >>>recu >>> Nous devons etre plus prudents, il faut anticiper avant que nous ne soyons 
    >>>recu >>> reperes. J'ai termine dans l'urgence mon nouveau schema de chiffrement que j'ai 
    >>>recu >>> appele 'crypteMove'.
    >>>recu >>> Durant l'encryption, nous allons modifier l'ordre des lettres du texte selon 
    >>>recu >>> des regles bien etablies. Voici le principe :
    >>>recu >>> - soit TXT la sequence des caracteres a encrypter
    >>>recu >>> - soit ENC la sequence de sortie
    >>>recu >>>   (au debut, ENC est vide)
    >>>recu >>> - j'effectue ensuite la manipulation suivante:
    >>>recu >>>   * je prends C le premier caractere de TXT et le rajoute a la fin de ENC
    >>>recu >>>   * soit X le code ASCII de C modulo 8 (par exemple pour la lettre 'b', son 
    >>>recu >>>     code ASCII est 98 donc X = 2)
    >>>recu >>>   * je prends les X premiers caracteres de TXT et les deplace a la fin de TXT
    >>>recu >>>     (s'il reste au moins X caracteres dans TXT)
    >>>recu >>>   * je recommence jusqu'a ce que TXT soit vide
    >>>recu >>> - a la fin, ENC contiendra le message encrypte.
    >>>recu >>> 
    >>>recu >>> Je te donne un exemple sur le message suivant :
    >>>recu >>>       "Petit message court."
    >>>recu >>> Devient :
    >>>recu >>>       "Pee ct mosusriae.ttg"
    >>>recu >>> 
    >>>recu >>> Je sais que tu es l'une des rares personnes a pouvoir mettre en oeuvre une 
    >>>recu >>> technique complexe comme celle-ci, cela devrait mieux nous proteger que le code 
    >>>recu >>> de cesar que nous utilisions jusqu'a present. Cependant, pour me montrer que tu 
    >>>recu >>> as bien compris ma methode, il faut dans un premier temps que tu me renvoies ce 
    >>>recu >>> message complet crypte comme je viens de te l'expliquer.
    >>>recu >>> 
    >>>recu >>> Bien a toi,
    >>>recu >>> Bob.
    ```
* Une des algorithmes est le suivante:

  * ```
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    void remove_lettre(char *str){
        memmove(str, str+1, strlen(str));
    }
    void swap_last(char *str) {
        const size_t len = strlen(str);
        if (len >1) {
            const char first=str[0];
            memmove(str, str+1, len-1);
            str[len-1]=first;
        }
    }
    int decalage(char *str) {
        return str[0]%8;
    }
    void premierLettre(char *str, char *coded) {
        char premlettre = str[0];
        coded[0]=premlettre;
    }
    int main() {
        char texte_originale[50000]="Petit message court."; //On doit trouver une maniere pour l'appliquer sur le texte d'aide qui normalment doit le metttre dans un fichier, mais je ne suis pas sure.
        char texte_code[10000];
        premierLettre(texte_originale, texte_code);
        remove_lettre(texte_originale);
        const size_t len = strlen(texte_originale);
        int dec;
        char lte;
        while(texte_originale[0]!='\0'){
            lte=texte_originale[0];
            dec=decalage(texte_originale);
            if (dec<strlen(texte_originale)){
                texte_code[strlen(texte_code)]=lte;
                remove_lettre(texte_originale);
                for (int i=0; i<dec; i++){
                    swap_last(texte_originale);
                }
            }
            else {
                remove_lettre(texte_originale);
                texte_code[strlen(texte_code)]=lte;
            }
        }
        printf("%s\n", texte_code);
    }
    ```

# 22/9/22 Seance TP No 2

* On a travaillé sur la correction de l'agorythme CrypteMove
* On a cree l'agorytme de decryptage de CrypteMove
* On a finnis avec le programme BayOfPigs

# 27/9/2022 Seance TD No 3

* On a designe le tableu pour l'algorithme "Decrypter CrypteMove"

# 28/9/2022

* Creation d'algorithme pour cryptage de l'exercice crypteSeq

# 29/9/2022 Seance TP No 3

* On a avance sur le programme de CrypteSeq cryptage et decryptage
* On a commence avec le programme Northwoods

# 30/9/2022

* Northwoods est complet
* On a commencé avec Last Cause mais on n'a pas reussi 100% pour le moment
* Addition des commentaires sur le code

# Caseine

Ici vous pouvez trouver tous les resolutions des exercises du Caseine. Les membres de l'equipe ont contribué.

## Exercice préparatoire (C) : Décalage de César

```
#include <stdio.h>

/*
 *  Auteur(s) :
 *  Date :
 *
 */


int main (void)
{
    char lettreLue;
    char lettreSuivante3;

    printf ("Donner une lettre \n");
    scanf ("%c",&lettreLue);
    if (lettreLue >= 'A' && lettreLue <= 'Z') {
        lettreSuivante3 = (((lettreLue - 'A')+3)%26+'A');
  
    }
    else if (lettreLue >= 'a' && lettreLue <= 'z') {
        lettreSuivante3 = (((lettreLue-'a')+3)%26+'a');
    }
    else {
        lettreSuivante3 = lettreLue;
    }
    //completer ici le calcul de la lettre suivante (3 rang plus loin)
  
    printf("\n%c\n",lettreSuivante3);

    return 0;
}

```

## Decryption V1.0

```

```
