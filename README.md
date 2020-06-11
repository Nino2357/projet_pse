# Projet_PSE

## Description du projet

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


