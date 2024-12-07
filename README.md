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

Pour installer GCC et Make sur Debian/Ubuntu, utilisez les commandes suivantes :
```sh
sudo apt update
sudo apt install gcc make
```

### Installation

1. Clonez le dépôt :
    ```sh
    git clone https://github.com/Klaynight-dev/Snake_Auto.git
    cd Snake_Auto
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
defconst.h
propal2.c
version1.c
```

### Fonctions

- `void succesJeu()`: Gère la fin du jeu lorsque l'utilisateur gagne.
- `void echecJeu()`: Gère la fin du jeu lorsque l'utilisateur perd.
- `int kbhit()`: Vérifie si une touche a été pressée.
- `char trouverDirectionOptimale(int xTete, int yTete, char directionActuelle)`: Fonction qui trouve la direction optimale pour le serpent.
- `char choisirDirection(int xTete, int yTete, char directionActuelle)`: Fonction qui choisit la direction du serpent.
- `int distanceCarree(int x1, int y1, int x2, int y2)`: Fonction qui calcule la distance entre deux points.

### Contribution

Les contributions sont les bienvenues ! Veuillez suivre les étapes ci-dessous pour contribuer :

1. Forkez le projet.
2. Créez votre branche de fonctionnalité (`git checkout -b feature/AmazingFeature`).
3. Commitez vos changements (`git commit -m 'Add some AmazingFeature'`).
4. Poussez vos commits (`git push origin feature/AmazingFeature`).
5. Ouvrez une Pull Request.

### Auteurs

- **Klaynight-dev** - *Créateur initial* - [Klaynight-dev](https://github.com/Klaynight-dev)

### Licence

Ce projet est sous licence MIT. Voir le fichier [LICENSE](LICENSE) pour plus de détails.
