/*!
 \file
 \page Général

 \author GOURDON Gabriel & PASSEREAU Elouan
 \version 2.0
 \date last 12 décembre 2024
 \brief Un snake pour la SAE 1.02 Comparaison d'Approches Algorithmiques
  Afin de démarrer avec GCC sans erreur, il vous faut effectuer la commande si dessous : 
 -> gcc ./version3.c -o main -Wall -lm
 -> main -h | main -v | main -d | main -s | main -ds etc
    Il permette : -h pour l'aide, -v pour la version, -d pour le mode debug, -s pour le mode speedrun
**/

// Bibliotèques
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>

#include "defconst.h"


/**
 * \fn int main()
 * \brief Programme principal.
 * \return Code de sortie du programme (0 : sortie normale).
 *
 * Le programme principal exécute le code du jeu
 */
int main(int argc, char *argv[])
{

	int positionsX[TAILLE_MAX_SERPENT];
	int positionsY[TAILLE_MAX_SERPENT];
	int x, y;
	char direction = DIRECTION_INITIALE;
	bool devraitQuitter = false;
	bool aQuitte = false;
	bool estMort = false;
	bool aGagne = false;
	bool debug = false; // Mode debug
	tempsCPUDepart = clock(); // Calculer le temps CPU utilisé


	x = X_DEBUT;
	y = Y_DEBUT;

    effacerEcran(); // Préparer le jeu

	if (argc >= 2) {
		for (int i = 1; i < argc; i++) {
			if (argv[i][0] == '-') {
				for (int j = 1; argv[i][j] != '\0'; j++) {
					if (argv[i][j] == 'd') { // Si l'utilisateur a passé l'argument -d, activer le mode debug
						debug = true;
					} else if (argv[i][j] == 's') { // Si l'utilisateur a passé l'argument -s, activer le mode speedrun
						speed = true;
					} else if (argv[i][j] == 'h') { // Si l'utilisateur a passé l'argument -h, afficher l'aide
						printf("Aide :\n");
						printf("  -d : Activer le mode debug\n");
						printf("  -s : Activer le mode speedrun\n");
						printf("  -h : Afficher l'aide\n");
						printf("  -v : Afficher la version\n");
						return EXIT_SUCCESS;
					} else if (argv[i][j] == 'v') { // Si l'utilisateur a passé l'argument -v, afficher la version
						printf("Version 3.51\n");
						return EXIT_SUCCESS;
					}
				}
			}
		}
	}

    genererSerpent(positionsX, positionsY, x, y);
    initPlateau();

	serpentDansTab(positionsX, positionsY);
	genererPaves(positionsX, positionsY);
	srand((unsigned int)time(NULL)); // Initialiser l'aléatoire

    dessinerPlateau(); // Afficher le tableau de jeu initial
	ajouterPomme(nbPommesMangees);
	detecterPomme(&pommeDetecX, &pommeDetecY);
    disableEcho();

    while (!devraitQuitter) // Boucle du jeu
    {
		if (speed) // Si le mode speedrun est activé, accélérer le jeu
		{
			usleep((__useconds_t)VITESSE_SPEEDRUN);
		} else {
			usleep((__useconds_t)vitesseJeu);
		}
		

		aQuitte = checkAKeyPress(); // Si l'utilisateur veut quitter, mettre aQuitte = true
		
		// if(tailleSerpent >= TAILLE_MAX_SERPENT)
		// {aGagne = true;} // Si la taille de l'utilisateur dépasse la taille maximale autorisée, il a gagné
		
		if (nbPommesMangees == NB_POMMES) { // Si l'utilisateur a mangé toutes les pommes, il a gagné 
			aGagne = true;
		}

        if (checkAKeyPress() || estMort || aGagne)
        {
            devraitQuitter = true; // Si la touche d'arrêt est pressée, quitter
        }
		
        changerDirection(&direction, positionsX, positionsY); // Met à jour la direction du serpent

        effacerSerpent(positionsX, positionsY); // Effacer le serpent avant de le déplacer

		progresser(positionsX, positionsY, direction, &estMort); // Faire avancer le serpent

        // Met à jour l'état du serpent dans le tableau
		serpentDansTab(positionsX, positionsY); 

        dessinerPlateau(); // Redessiner le tableau de jeu avec le serpent mis à jour
		detecterPomme(&pommeDetecX, &pommeDetecY);

		if(debug)
		{
	        devInfo(positionsX, positionsY, direction); // Afficher les informations du jeu à l'écran

		}
    }

    enableEcho(); // Réactiver l'écho
    printf("\n");
	if(aGagne)
	{
		succesJeu();
	}
	else if(estMort)
	{
		echecJeu();
	}
	else if(aQuitte)
	{
		quitterJeu();
	}

    return EXIT_SUCCESS;
}

void devInfo(int positionsX[20], int positionsY[20], char direction)
{
    // Afficher les informations du jeu
    printf("\nScore :%d/%d\t", nbPommesMangees, NB_POMMES);
    printf("Mouvements : %d\t\t", nbrMouvements);
    printf("Temps : %f\t\t", (double)(clock() - tempsCPUDepart) / CLOCKS_PER_SEC);
    printf("Position : %d, %d\t\t", positionsX[0], positionsY[0]);
    printf("Direction : %s\t\t", direction == TOUCHE_DROITE ? "Droite" : direction == TOUCHE_GAUCHE ? "Gauche"
                                                                   : direction == TOUCHE_HAUT     ? "Haut"
                                                                                                  : "Bas");
	printf("Pomme : %d, %d\n", pommeDetecX, pommeDetecY);
	printf("\033[A\033[2K"); // Efface la ligne précédente

	//printf("Distance directe: %d\t\t", distanceDirecte);
    //printf("Distance via trou droit: %d\t\t", distanceViaTrouD);
    //printf("Distance via trou gauche: %d\t\t", distanceViaTrouG);
    //printf("Distance via trou haut: %d\t\t", distanceViaTrouH);
    //printf("Distance via trou bas: %d\t\t", distanceViaTrouB);
	//printf("Cible choisie : (%d, %d)\n", cible[0], cible[1]);
	//printf("\033[A\033[2K"); // Efface la ligne précédente
}

/**
 * \fn void initTableau()
 * \brief Initialise le tableau de jeu
 * \return Code de sortie du programme (0 : sortie normale).
 *
 * Le programme principal exécute le code du jeu
 */
void initPlateau()
{
	for (int i = 0; i < TAILLE_TABLEAU_Y; i++)
	{
		for (int j = 0; j < TAILLE_TABLEAU_X; j++)
		{
			// Placer des bordures sur les bords du tableau
            if (i == 1 || i == TAILLE_TABLEAU_Y - 1 || j == 1 || j == TAILLE_TABLEAU_X - 1) {
                tableau[i][j] = CHAR_BORDURE;  // Bordure
            } else {
                tableau[i][j] = CHAR_VIDE;  // Espace vide à l'intérieur
            }
		}
	}
	genererTrous();
	dessinerPlateau();
}

/**
 * \fn void dessinerPlateau()
 * \brief Dessine le plateau sur l'écran
 *
 * Dessine le plateau sur l'écran
 */
void dessinerPlateau()
{
	for (int i = 0; i < TAILLE_TABLEAU_Y; i++)
	{
		for (int j = 0; j < TAILLE_TABLEAU_X; j++)
		{
			afficher(j, i, tableau[i][j]);
		}
	}
}
/**
 * \fn void effacerSerpent(int positionsX[TAILLE_SERPENT], int positionsY[TAILLE_SERPENT])
 * \brief Efface le serpent dans le tableau
 *
 * Met toutes les positions du serpent dans le tableau à la valeur de CHAR_VIDE
 */
void effacerSerpent(int positionsX[TAILLE_MAX_SERPENT], int positionsY[TAILLE_MAX_SERPENT])
{
	for (int i = 0; i < TAILLE_MAX_SERPENT; i++)
	{
		tableau[positionsY[i]][positionsX[i]] = CHAR_VIDE;
		afficher(positionsX[i], positionsY[i], CHAR_VIDE);
	}
}

/**
 * \fn void changerDirection(char* direction)
 * \brief Met le curseur aux coordonnées x et y
 *
 * Met le curseur aux coordonnées x et y passées en paramètre d'entrée
 */
void changerDirection(char* direction, int positionsX[TAILLE_MAX_SERPENT], int positionsY[TAILLE_MAX_SERPENT])
{
	int cible[2]; // 0 = X 1 =void	determinerCible(cible, positionsX, positionsY);
	determinerCible(cible, positionsX, positionsY);
	*direction = choisirDirection(positionsX[0], positionsY[0], *direction, cible[0], cible[1]);
}
/*!
 \fn int checkAKeyPress()
 \brief La fonction qui vérifie si la touche A est appuyée
 \return true si la touche A est appuyée, false sinon

 La fonction qui vérifie si A est appuyé, en utilisant kbhit
*/
int checkAKeyPress()
{
	int ch;
	if(kbhit())
	{
		ch = getchar();
	}
	if (ch == TOUCHE_ARRET) // Si la touche détectée est celle d'arrêt, retourner true
	{
		return true;
	}
	return false;
}

// Definition des fonctions demandées
void afficher(int x, int y, char c)
{
	gotoXY(x, y);
	printf("%c", c);
}

// Efface un caractère
void effacer(int x, int y)
{
	tableau[x][y] = CHAR_VIDE;
}

void disableEcho()
{
	struct termios tty;

	// Obtenir les attributs du terminal
	if (tcgetattr(STDIN_FILENO, &tty) == -1) {
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}

	// Desactiver le flag ECHO
	tty.c_lflag &= (tcflag_t)~ECHO;

	// Appliquer les nouvelles configurations
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) == -1) {
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

void enableEcho()
{
	struct termios tty;

	// Obtenir les attributs du terminal
	if (tcgetattr(STDIN_FILENO, &tty) == -1) {
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}

	// Reactiver le flag ECHO
	tty.c_lflag |= ECHO;

	// Appliquer les nouvelles configurations
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) == -1) {
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

// Efface l'écran
void effacerEcran()
{
	system("clear");
}

/*!
 \fn void ajouterPomme()
 \brief La fonction qui ajoute une pomme à un endroit aléatoire de l'écran

 Génère deux coordonnées, et si le caractère de la case correspondante est CHAR_VIDE, ajoute une pomme et affiche le caractère CHAR_POMME, sinon, recommence
*/
void ajouterPomme(int indice)
{
	int x, y;
	x = lesPommesX[indice];
	y = lesPommesY[indice];
	// while (tableau[y][x] != CHAR_VIDE)
	// {
	// 	x = (rand() % TAILLE_TABLEAU_X - 2) + 2;
	// 	y = (rand() % TAILLE_TABLEAU_Y - 2) + 2;
	// }
	tableau[y][x] = CHAR_POMME;
	afficher(x, y, CHAR_POMME);
	fflush(stdout);

}

/*!
 \fn void genererSerpent(int positionsX[TAILLE_SERPENT], int positionsY[TAILLE_SERPENT], int x, int y)
 \brief La fonction qui génère le serpent
 \param positionsX La liste des positionsX du serpent
 \param positionsY La liste des positionsY du serpent
 \param x Le X de la tête du serpent
 \param y Le Y de la tête du serpent

 Cette fonction créé la liste des positions (positionsX, positionsY) du serpent dans la liste en argument en utilisant x et y
*/
void genererSerpent(int positionsX[TAILLE_MAX_SERPENT], int positionsY[TAILLE_MAX_SERPENT], int x, int y)
{
	for (int nbCellule = 0; nbCellule < TAILLE_MAX_SERPENT; nbCellule++) // Génerer des coordonées de x à (x + TAILLE_SERPENT) pour le serpent
	{
		positionsX[nbCellule] = x - nbCellule;
		positionsY[nbCellule] = y;
	}
}

/*!
 \fn void serpentDansTab(int positionsX[TAILLE_SERPENT], int positionsY[TAILLE_SERPENT])
 \brief La fonction qui met les positions du serpent dans le tableau de jeu
 \param positionsX La liste des positionsX du serpent
 \param positionsY La liste des positionsY du serpent

 Cette fonction transfère toutes les positions du serpent (positionsX et positionsY) dans le tableau de jeu
*/
void serpentDansTab(int positionsX[TAILLE_MAX_SERPENT], int positionsY[TAILLE_MAX_SERPENT])
{
	for (int iDessine = 0; iDessine < tailleSerpent; iDessine++)
	{
		int aDessinerX = positionsX[iDessine];
		int aDessinerY = positionsY[iDessine];

		// Vérifier que les coordonnées sont dans les limites de l'écran
		if (aDessinerX >= 0 && aDessinerX < TAILLE_TABLEAU_X &&
			aDessinerY >= 0 && aDessinerY < TAILLE_TABLEAU_Y)
		{
			// Dessiner la tête ou le corps en fonction de la position dans le tableau
			if (iDessine == 0)
			{
				tableau[aDessinerY][aDessinerX] = CHAR_TETE;
			}
			else
			{
				tableau[aDessinerY][aDessinerX] = CHAR_CORPS;
			}
		}
	}
}


/*!
 \fn void genererTrous()
 \brief La fonction qui génère les trous dans les bords du plateau
C
*/
void genererTrous()
{
	tableau[1][TAILLE_TABLEAU_X / 2] = CHAR_VIDE;
	tableau[TAILLE_TABLEAU_Y - 1][TAILLE_TABLEAU_X / 2] = CHAR_VIDE;

	tableau[TAILLE_TABLEAU_Y / 2][1] = CHAR_VIDE;
	tableau[TAILLE_TABLEAU_Y / 2][TAILLE_TABLEAU_X - 1] = CHAR_VIDE;
}

/*!
 \fn void progresser(int positionsX[TAILLE_SERPENT], int positionsY[TAILLE_SERPENT], char direction)
 \brief La fonction qui fait avancer le jeu d'une étape
 \param positionsX La liste des positions X du serpent
 \param positionsY La liste des positions Y du serpent
 \param direction La direction dans laquelle le serpent avance

 La fonction qui fait avancer le corps du serpent, puis bouge la tête dans la direction dans laquelle elle est sensée avancer
*/
void progresser(int positionsX[TAILLE_MAX_SERPENT], int positionsY[TAILLE_MAX_SERPENT], char direction, bool* detecCollision) {
    int nouveauX = positionsX[0];
    int nouveauY = positionsY[0];

    // Calcul de la nouvelle position
    switch (direction) {
        case TOUCHE_DROITE: nouveauX++; break;
        case TOUCHE_HAUT: nouveauY--; break;
        case TOUCHE_GAUCHE: nouveauX--; break;
        case TOUCHE_BAS: nouveauY++; break;
        default: break;
    }

    // Gestion des portes (trous)
    if (nouveauX < 1 && direction == TOUCHE_GAUCHE && (nouveauY == TAILLE_TABLEAU_Y / 2)) {
        nouveauX = TAILLE_TABLEAU_X - 2;
    }
    if (nouveauX > TAILLE_TABLEAU_X - 2 && direction == TOUCHE_DROITE && (nouveauY == TAILLE_TABLEAU_Y / 2)) {
        nouveauX = 1;
    }
    if (nouveauY < 1 && direction == TOUCHE_HAUT && (nouveauX == TAILLE_TABLEAU_X / 2)) {
        nouveauY = TAILLE_TABLEAU_Y - 2;
    }
    if (nouveauY > TAILLE_TABLEAU_Y - 2 && direction == TOUCHE_BAS && (nouveauX == TAILLE_TABLEAU_X / 2)) {
        nouveauY = 1;
    }

    // Vérification des collisions
    if (tableau[nouveauY][nouveauX] == CHAR_OBSTACLE || tableau[nouveauY][nouveauX] == CHAR_CORPS) {
        *detecCollision = true;
        return;
    }

    // Vérification des pommes
    if (tableau[nouveauY][nouveauX] == CHAR_POMME) {
        nbPommesMangees++;
        if (nbPommesMangees < NB_POMMES) {
            ajouterPomme(nbPommesMangees);
        }
    }

    // Déplacement du serpent
    for (int i = tailleSerpent - 1; i > 0; i--) {
        positionsX[i] = positionsX[i - 1];
        positionsY[i] = positionsY[i - 1];
    }
    positionsX[0] = nouveauX;
    positionsY[0] = nouveauY;
	nbrMouvements++;
}




int kbhit()
{
	// la fonction retourne :
	// 1 si un caractere est present
	// 0 si pas de caractere present
	
	int unCaractere=0;
	struct termios oldt, newt;
	int ch;
	int oldf;

	// mettre le terminal en mode non bloquant
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= (tcflag_t)~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	// restaurer le mode du terminal
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF){
		ungetc(ch, stdin);
		unCaractere=1;
	} 
	return unCaractere;
}

/*!
 \fn void succesJeu()
 \brief La fonction qui gère la fin du jeu quand l'utilisateur le gagne

 Efface l'écran et dit bravo
*/
void succesJeu()
{
	system("clear");
	tempsCPUFin = clock(); // Calculer le temps CPU utilisé
	printf("Vous avez gagné, bravo !\n");
	printf("Vous avez mis %d mouvements pour gagner\n", nbrMouvements);
	printf("Vous avez mis %f secondes pour gagner\n", (double)(tempsCPUFin - tempsCPUDepart) / CLOCKS_PER_SEC);
}

/*!
 \fn void echecJeu()
 \brief La fonction qui gère la fin du jeu quand l'utilisateur le perd

 Efface l'écran et dit dommage
*/
void echecJeu()
{
	system("clear");
	printf("Vous avez perdu, dommage !\n");
}

/*!
 \fn void quitterJeu()
 \brief La fonction qui gère la fin du jeu quand l'utilisateur le quitte manuellement

 Efface l'écran et dit au revoir
*/
void quitterJeu()
{
	system("clear");
	printf("Au revoir !\n");
}

/**
 * \fn void gotoXY(int x, int y) 
 * \brief Met le curseur aux coordonnées x et y
 *
 * Met le curseur aux coordonnées x et y passées en paramètre d'entrée
 */
void gotoXY(int x, int y)
{
	printf("\033[%d;%df", y, x);
}

/*!
 \fn int genererEntierDansBornes(int min, int max)
 \brief La fonction qui génère un entier de min à max
 \param min Le minimum de l'intervalle
 \param max Le maximum de l'intervalle

Retourne un entier aleatoire entre min et max
*/
int genererEntierDansBornes(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

void detecterPomme(int* pommeX, int* pommeY)
{
	if (tableau[*pommeY][*pommeX] != CHAR_POMME) {// La pomme est toujours à la même position
		for (int i = 0; i < TAILLE_TABLEAU_Y; i++)
		{
			for (int j = 0; j < TAILLE_TABLEAU_X; j++)
			{
				if (tableau[i][j] == CHAR_POMME)
				{
					*pommeX = j;
					*pommeY = i;
					return;
				}
			}
		}
	}
}


// La fonction utilise le théorème de Pythagore pour trouver la distance entre la (x1, y1) et (x2, y2) et la retourne sous forme d'un int
int distanceCarree(int x1, int y1, int x2, int y2) {
    return (int)pow(x1 - x2, 2) + (int)pow(y1 - y2, 2); // Théorème de Pythagore
}

// Cette fonction gère la logique du changement de direction, avec la cible et les trous

int getNodeIndex(int x, int y) {
	return y * TAILLE_TABLEAU_X + x;
}

int heuristic(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

Node* getLowestFCostNode() {
	int lowestFCost = INT_MAX;
	Node* lowestNode = NULL;
	for (int i = 0; i < MAX_NODES; i++) {
		if (openSet[i] && nodes[i].fCost < lowestFCost) {
			lowestFCost = nodes[i].fCost;
			lowestNode = &nodes[i];
		}
	}
	return lowestNode;
}

void reconstructPath(Node* current, int* pathX, int* pathY, int* pathLength) {
	*pathLength = 0;
	while (current != NULL) {
		pathX[*pathLength] = current->x;
		pathY[*pathLength] = current->y;
		(*pathLength)++;
		current = current->parent;
	}
	// Reverse the path
	for (int i = 0; i < *pathLength / 2; i++) {
		int tempX = pathX[i];
		int tempY = pathY[i];
		pathX[i] = pathX[*pathLength - 1 - i];
		pathY[i] = pathY[*pathLength - 1 - i];
		pathX[*pathLength - 1 - i] = tempX;
		pathY[*pathLength - 1 - i] = tempY;
	}
}

bool aStar(int startX, int startY, int goalX, int goalY, int* pathX, int* pathY, int* pathLength) {
	for (int i = 0; i < MAX_NODES; i++) {
		openSet[i] = false;
		closedSet[i] = false;
		nodes[i].parent = NULL;
		nodes[i].gCost = INT_MAX;
		nodes[i].hCost = 0;
		nodes[i].fCost = INT_MAX;
	}

	int startIndex = getNodeIndex(startX, startY);
	nodes[startIndex].x = startX;
	nodes[startIndex].y = startY;
	nodes[startIndex].gCost = 0;
	nodes[startIndex].hCost = heuristic(startX, startY, goalX, goalY);
	nodes[startIndex].fCost = nodes[startIndex].hCost;
	openSet[startIndex] = true;

	while (true) {
		Node* current = getLowestFCostNode();
		if (current == NULL) {
			return false; // No path found
		}

		int currentIndex = getNodeIndex(current->x, current->y);
		if (current->x == goalX && current->y == goalY) {
			reconstructPath(current, pathX, pathY, pathLength);
			return true;
		}

		openSet[currentIndex] = false;
		closedSet[currentIndex] = true;

		int neighbors[4][2] = {
			{current->x + 1, current->y},
			{current->x - 1, current->y},
			{current->x, current->y + 1},
			{current->x, current->y - 1}
		};

		for (int i = 0; i < 4; i++) {
			int neighborX = neighbors[i][0];
			int neighborY = neighbors[i][1];
			if (neighborX < 0 || neighborX >= TAILLE_TABLEAU_X || neighborY < 0 || neighborY >= TAILLE_TABLEAU_Y) {
				continue;
			}
			if (tableau[neighborY][neighborX] == CHAR_OBSTACLE || tableau[neighborY][neighborX] == CHAR_CORPS) {
				continue;
			}

			int neighborIndex = getNodeIndex(neighborX, neighborY);
			if (closedSet[neighborIndex]) {
				continue;
			}

			int tentativeGCost = current->gCost + 1;
			if (!openSet[neighborIndex]) {
				openSet[neighborIndex] = true;
			} else if (tentativeGCost >= nodes[neighborIndex].gCost) {
				continue;
			}

			nodes[neighborIndex].x = neighborX;
			nodes[neighborIndex].y = neighborY;
			nodes[neighborIndex].gCost = tentativeGCost;
			nodes[neighborIndex].hCost = heuristic(neighborX, neighborY, goalX, goalY);
			nodes[neighborIndex].fCost = nodes[neighborIndex].gCost + nodes[neighborIndex].hCost;
			nodes[neighborIndex].parent = current;
		}
	}
}

char choisirDirection(int xTete, int yTete, char directionActuelle, int cibleX, int cibleY) {
	int pathX[TAILLE_TABLEAU_X * TAILLE_TABLEAU_Y];
	int pathY[TAILLE_TABLEAU_X * TAILLE_TABLEAU_Y];
	int pathLength;

	if (aStar(xTete, yTete, cibleX, cibleY, pathX, pathY, &pathLength) && pathLength > 1) {
		int nextX = pathX[1];
		int nextY = pathY[1];

		if (nextX > xTete) return TOUCHE_DROITE;
		if (nextX < xTete) return TOUCHE_GAUCHE;
		if (nextY > yTete) return TOUCHE_BAS;
		if (nextY < yTete) return TOUCHE_HAUT;
	}

	return directionActuelle;
}

// Cette fonction détermine la cible vers laquelle le serpent doit se diriger, en tenant compte des trous
void determinerCible(int cible[2], int positionsX[TAILLE_MAX_SERPENT], int positionsY[TAILLE_MAX_SERPENT])
{
	int xTeteSerpent = positionsX[0];
	int yTeteSerpent = positionsY[0];

	int distanceDirecte = distanceCarree(xTeteSerpent, yTeteSerpent, pommeDetecX, pommeDetecY);

	int distanceViaTrouD = distanceCarree(xTeteSerpent, yTeteSerpent, TAILLE_TABLEAU_X - 1, MOITIE_HAUTEUR_TABLEAU) +
						   distanceCarree(1, MOITIE_HAUTEUR_TABLEAU, pommeDetecX, pommeDetecY);
	int distanceViaTrouG = distanceCarree(xTeteSerpent, yTeteSerpent, 1, MOITIE_HAUTEUR_TABLEAU) +
						   distanceCarree(TAILLE_TABLEAU_X - 2, MOITIE_HAUTEUR_TABLEAU, pommeDetecX, pommeDetecY);
	int distanceViaTrouH = distanceCarree(xTeteSerpent, yTeteSerpent, MOITIE_LARGEUR_TABLEAU, 1) +
						   distanceCarree(MOITIE_LARGEUR_TABLEAU, TAILLE_TABLEAU_Y - 2, pommeDetecX, pommeDetecY);
	int distanceViaTrouB = distanceCarree(xTeteSerpent, yTeteSerpent, MOITIE_LARGEUR_TABLEAU, TAILLE_TABLEAU_Y - 1) +
						   distanceCarree(MOITIE_LARGEUR_TABLEAU, 2, pommeDetecX, pommeDetecY);

	int distanceMin = distanceDirecte;
	cible[0] = pommeDetecX;
	cible[1] = pommeDetecY;

	if (distanceViaTrouD < distanceMin) {
		distanceMin = distanceViaTrouD;
		cible[0] = TAILLE_TABLEAU_X - 1;
		cible[1] = MOITIE_HAUTEUR_TABLEAU;
	}
	if (distanceViaTrouG < distanceMin) {
		distanceMin = distanceViaTrouG;
		cible[0] = 1;
		cible[1] = MOITIE_HAUTEUR_TABLEAU;
	}
	if (distanceViaTrouH < distanceMin) {
		distanceMin = distanceViaTrouH;
		cible[0] = MOITIE_LARGEUR_TABLEAU;
		cible[1] = 1;
	}
	if (distanceViaTrouB < distanceMin) {
		distanceMin = distanceViaTrouB;
		cible[0] = MOITIE_LARGEUR_TABLEAU;
		cible[1] = TAILLE_TABLEAU_Y - 1;
	}
}

void genererPaves()
{
	for (int i = 0; i < NB_PAVES; i++)
	{
		int x = lesPavesX[i];
		int y = lesPavesY[i];

		for (int j = 0; j < TAILLE_PAVE_Y; j++)
		{
			for (int k = 0; k < TAILLE_PAVE_X; k++)
			{
				if (x + k < TAILLE_TABLEAU_X && y + j < TAILLE_TABLEAU_Y)
				{
					tableau[y + j][x + k] = CHAR_OBSTACLE;
				}
			}
		}
	}
}