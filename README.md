# Projet_PSE

## Simulation d'une partie de coinche en réseau local

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