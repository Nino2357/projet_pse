# Projet_PSE

## Description du projet

Ce projet simule la phase de préparation d'un partie de coinche. 
Le projet comprends les fonctionnalités suivantes :
- Connexion des joueurs au serveur
- Saisie du nom des joueurs
- Construction du paquet de cartes
- Affichage des cartes constituant le jeu
- Construction et affichage des équipes
- Mélange du paquet de carte aléatoirement
- Distribution des cartes
- Affichage de la main de chaque joueur
- Phase d'annonce correspondant aux regles de la coinche ou de la contrée


## Utilisation du programme

Il faut tout d'abord se placer dans le dossier projet
`cd projet`
Puis compiler avec la commande
`make`  -> 2 fichiers sont crées (serveur_coinche et client_coinche)

Ensuite, il faut ouvrir 5 terminals pour simuler une partie :

+ 1 pour le serveur
`./serveur_coinche` 
Il ne faut rien écrire sur ce terminal, il affiche seulement les infos sur la partie

+ 4 pour les clients (joueurs) 
Il en faut 4 obligatoirement (1 par joueur)
`./client_coinche` 
Il faut suivre les instructions: 
(Il faut bien que chaque client fasse ses actions pour avancer dans le programme) 

### Structure des dossiers

- include/lib/modules provenant du cours de pse
- projet : ensemble des fichiers utiles au programmes
    + makefile
    + client
    + serveur
    + headers
- fic_unused
    +le reste des fichiers non implantés dans le programme
- documentations + README

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
