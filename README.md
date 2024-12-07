### README
## Jeu du Serpent

Ce projet est une implémentation simple du jeu classique du Serpent. Le jeu est écrit en C et est conçu pour être joué dans un terminal.

### Fonctionnalités

- Déplacez le serpent à l'aide du clavier.
- Mangez des pommes pour faire grandir le serpent.
- Évitez de heurter les murs ou le corps du serpent.
- Gagnez le jeu en mangeant toutes les pommes.

### Prérequis

- GCC (GNU Compiler Collection)
- Make

### Installation

1. Clonez le dépôt :
    ```sh
    git clone <repository_url>
    cd <repository_directory>
    ```

2. Construisez le projet :
    ```sh
    make
    ```

### Utilisation

1. Lancez le jeu :
    ```sh
    ./main
    ```

2. Utilisez les touches suivantes pour contrôler le serpent :
    - `d` : Aller à droite
    - `q` : Aller à gauche
    - `z` : Aller en haut
    - `s` : Aller en bas
    - `a` : Quitter le jeu

### Structure du Projet

```
.vscode/
    c_cpp_properties.json
    launch.json
    settings.json
build/
    Debug/
        version1.o
defconst.h
main
propal2.c
version1.c
```

### Fonctions

- `void succesJeu()`: Gère la fin du jeu lorsque l'utilisateur gagne.
- `void echecJeu()`: Gère la fin du jeu lorsque l'utilisateur perd.
- `int kbhit()`: Vérifie si une touche a été pressée.

### Licence

Ce projet est sous licence MIT.
