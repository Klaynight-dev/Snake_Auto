# Snake Autonome - Version 1

Ce programme implémente un jeu Snake autonome dans lequel le serpent se déplace automatiquement pour manger 10 pommes, sans intervention de l'utilisateur.

## Fonctionnalités
- **Déplacement autonome** : Le serpent trouve et mange toutes les pommes, positionnées aux coordonnées spécifiées.
- **Plateau de jeu** :
  - Dimensions : 80 caractères de large sur 40 de hauteur.
  - Bordures représentées par `#`.
- **Serpent** :
  - Taille initiale : 10 (tête représentée par `O`, corps par `X`).
  - Position de départ : (40,20), orienté à droite.
  - Permet de se croiser et de faire demi-tour.
- **Pommes** :
  - Représentées par `6`.
  - Coordonnées fournies par des tableaux.
- **Arrêt et statistiques** :
  - Le programme s'arrête automatiquement après avoir mangé 10 pommes.
  - Affiche le nombre de déplacements réalisés et le temps CPU utilisé.

## Instructions
1. Compiler le code source avec :
   ```bash
   gcc version1.c -o snake -Wall
   ```
2. Exécuter le programme :
   ```bash
   ./snake
   ```
3. Appuyer sur `a` pour interrompre l'exécution.

## Exigences
- Respect des conventions de codage (indentation, commentaires, etc.).
- Gestion efficace du déplacement autonome.

## Structure des fichiers
- `version1.c` : Code source principal.
- `README.md` : Ce fichier.

## À venir
Consultez la roadmap ci-dessous pour découvrir les améliorations prévues pour ce programme.

### Roadmap

#### Étape 1 : Implémentation de base
- [x] Déplacer le serpent vers les pommes dans l'ordre spécifié.
- [x] Gérer les bordures et éviter les erreurs de déplacement.
- [x] Ajouter une temporisation (200 ms entre les déplacements).
- [x] Arrêter le programme après avoir mangé les 10 pommes.
- [x] Afficher les statistiques (nombre de déplacements, temps CPU).

#### Étape 2 : Améliorations visuelles
- [ ] Ajouter des couleurs pour différencier le serpent, les pommes et les bordures.
- [ ] Afficher un écran de fin après avoir mangé toutes les pommes.

#### Étape 3 : Intelligence du serpent
- [ ] Implémenter un algorithme pour choisir le chemin optimal vers la prochaine pomme.
- [ ] Permettre au serpent de s'adapter si les positions des pommes changent.

#### Étape 4 : Personnalisation du jeu
- [ ] Ajouter une interface utilisateur permettant de :
  - Modifier la taille du plateau.
  - Choisir des coordonnées aléatoires pour les pommes.
- [ ] Permettre de régler la vitesse du serpent.

#### Étape 5 : Mode multiversion
- [ ] Proposer deux approches algorithmiques pour le déplacement :
  - Une approche simple basée sur la ligne droite.
  - Une approche avancée avec algorithme de recherche de chemin.

#### Étape 6 : Documentation et publication
- [ ] Améliorer le README avec des captures d'écran et des graphiques.
- [ ] Publier le projet sur un dépôt GitHub.
