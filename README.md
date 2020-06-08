# Projet_PSE

## Simulation d'une partie de coinche en réseau local

### A faire

Debugger les fonctions play_hand et play_round

Finir d'implementer la partie serveur/client pour tout les parties du programmes restantes (distribuer, annonce, play_hand, play-round)

### Notes 

Il y a des warnings quand on fait make mais c'est pas un probleme, c'est juste en attendant qu'on utilise toutes les variables

### Utilisation

`cd serveur`
`make` -> 2 fichiers sont crées (serveur_coinche et client_coinche)
+ Pour le serveur
`./serveur_coinche` (rien à écrire, le programme gere le serveur)
+ Pour le client (Il en faut 4 obligatoirement - 1 par joueur)
`./client_coinche` suivre les instructions 
(Il faut bien que chaque client fasse ses actions pour avancer dans le programme) 

### Structure du dossier

- include/lib/modules provenant du cours de pse
- projet : ensemble des fichiers utiles au programmes
    + Main
    + Préparation
    + Annonce
    + Client 
    + Serveur
- serveur : ensemble des fichiers utiles pour jouer au jeu en mode serveur
    + Serveur_coinche
    + Client_coinche

- documentations + fichiers non utilisés

### Phases de la coinche

* Préparation de la partie
    - Formation des équipes
    - Créer un liste de l'ordre
    - Choisir une tete de liste
    - Choix du score à atteindre
    - Affichage des règles
    - Création d'un tas aléatoire (v,c) de 32 cartes

* Boucle tant que le score des 2 equipes est inférieur au score à atteindre:

    - Distribution des 8 cartes 
        + Coupe du tas
            * Génération un nb aléatoire entre 5 et 27
            * Coupe à cet endroit précis
        + Distribution dans l'ordre du tas

    - Choix des mises (couleur + score)
        + chaque joueur propose (couple (couleur,mise (>80 et precedent)); coinche;  passe) jusqu'a ce que 3 joueurs d'affilés ne proposent rien

    - Boucle, jeu en 8 tours :
        + Chaque joueur place une carte dans l'ordre de la table
            - Le premier tour le jour de tete commence sinon celui qui a la main au tour précédent
            - Si possible ajout de la restriction en fonction des règles
            - Définir le joueur qui a la main
        + Calcul des points (à la fin d'un tour)
        + Les cartes sont ajoutés au tas de l'équipe qui remporte

    
    - Calcul des scores (à la fin d'une donne)
        + comparaison du score avec l'annonce
        + ajout du score au score global
        + affichage des scores 

    - Changer de tete de liste

### Structure

* Carte
    -couleur (4 couleurs: ...)
    -valeur (8 valeurs)

* Mise 
    - Couleur
    - Montant (dans une liste)
    
* Equipe
    - Joueur 1
    - Joueur 2
    - Score
    - Tas de l'équipe

* Joueur 
    - id du joueur
    - Main du joueur

* Tas de carte
    -taille
    -liste (taille 32)