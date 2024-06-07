# Snake-EI3-2024

## Introduction
Ce projet a été réalisé dans le cadre de mes études à l'université. J'ai développé un bot pour le jeu Snake capable de se déplacer de manière autonome dans une arène, en évitant les obstacles, les murs et lui-même, grâce à diverses stratégies et algorithmes.


## But du jeu
Ce jeu reprend les bases du célèbre Snake. Deux serpents s'affrontent dans une arène, évitant murs, adversaires et eux-mêmes. Le but est de coder un serpent qui reste en vie le plus longtemps possible pour gagner la partie. Que le meilleur programme gagne !

## Règles de base
- TTaille de l’arène : Variable (L x H), communiquée par le serveur au début du jeu.
- Position de départ : Joueur 0 commence à (2, H/2) et Joueur 1 à (L-3, H/2).
- Croissance des serpents : Chaque serpent grandit d'une case tous les 10 tours (incluant le tour 0).

*Tous les mouvements seront exécutés sur un serveur distant qui renverra les informations de mises à jour aux joueurs via l’API fournit. Il n'est donc pas possible d'exécuter de mouvements invalides.*

## Utilisation de l’API
Une API en C est fournie pour communiquer avec le serveur. Elle inclut des fonctions pour initier la communication, démarrer une partie, jouer un coup, recevoir les coups de l’adversaire, etc. Pour plus d'informations, référez-vous aux commentaires dans le fichier `snakeAPI.h`.


