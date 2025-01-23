
// Déclaration des constantes
/**
 * \def TAILLE_TABLEAU
 * \brief La taille du tableau dans lequel le serpent va évoluer
 */
#define TAILLE_TABLEAU_X 81
#define TAILLE_TABLEAU_Y 41

/**
 * \def TAILLE_SERPENT
 * \brief La taille du serpent
 * Elle ne changera pas pour le moment
 */
#define TAILLE_SERPENT 10

/**
 * \def VITESSE_JEU
 * \brief La vitesse à laquelle le jeu va avancer (en nanosecondes)
 */
#define VITESSE_JEU_INITIALE 100000
#define VITESSE_SPEEDRUN 10000

/**
 * \def TOUCHE_ARRET
 * \brief La touche sur laquelle appuyer pour arrêter le jeu
 */
#define TOUCHE_ARRET 'a'

/**
 * \def CHAR_TETE
 * \brief Le caractère qui correspond à la tête du serpent
 */
#define CHAR_TETE_1 '1'

/**
 * \def CHAR_TETE
 * \brief Le caractère qui correspond à la tête du serpent
 */
#define CHAR_TETE_2 '2'

/**
 * \def CHAR_CORPS
 * \brief Le caractère qui correspond au corps du serpent
 */
#define CHAR_CORPS 'X'

/**
 * \def CHAR_OBSTACLE
 * \brief Le caractère qui correspond aux obstacles à éviter
 */
#define CHAR_OBSTACLE '#'

/**
 * \def CHAR_VIDE
 * \brief Le caractère qui correspond aux espaces vides dans lesquels le serpent peut aller
 */
#define CHAR_VIDE ' '

/**
 * \def CHAR_VIDE
 * \brief Le caractère qui correspond aux espaces vides dans lesquels le serpent peut aller
 */
#define CHAR_POMME '6'

/**
 * \def DIRECTION_INITIALE
 * \brief La direction dans laquelle le serpent doit se déplacer au départ
 */
#define DIRECTION_INITIALE 'g'

/**
 * \def TOUCHE_DROITE
 * \brief La touche à appuyer pour aller vers la droite
 */
#define TOUCHE_DROITE 'd'

/**
 * \def TOUCHE_GAUCHE
 * \brief La touche à appuyer pour aller vers la gauche
 */
#define TOUCHE_GAUCHE 'q'

/**
 * \def TOUCHE_HAUT
 * \brief La touche à appuyer pour aller vers le haut
 */
#define TOUCHE_HAUT 'z'

/**
 * \def TOUCHE_BAS
 * \brief La touche à appuyer pour aller vers le bas
 */
#define TOUCHE_BAS 's'

/**
 * \def X_DEBUT
 * \brief La position horizontale à laquelle le serpent doit démarrer
 */
#define X_DEBUT_1 40

/**
 * \def Y_DEBUT
 * \brief La position horizontale à laquelle le serpent doit démarrer
 */
#define Y_DEBUT_1 13

/**
 * \def X_DEBUT
 * \brief La position horizontale à laquelle le serpent doit démarrer
 */
#define X_DEBUT_2 40

/**
 * \def Y_DEBUT
 * \brief La position horizontale à laquelle le serpent doit démarrer
 */
#define Y_DEBUT_2 27

/**
 * \def NOMBRE_PAVES
 * \brief Le nombre de pavés à génerer
 */
#define NOMBRE_PAVES 4

/**
 * \def TAILLE_PAVE_X
 * \brief La taille horizontale des pavés
 */
#define TAILLE_PAVE_X 5

/**
 * \def TAILLE_PAVE_Y
 * \brief La taille verticale des pavés
 */
#define TAILLE_PAVE_Y 5

#define TAILLE_MAX_SERPENT 20

#define ACCEL_SERPENT 15000

#define NB_POMMES 10

#define CHAR_BORDURE '#'

#define MOITIE_HAUTEUR_TABLEAU (TAILLE_TABLEAU_Y / 2)
#define MOITIE_LARGEUR_TABLEAU (TAILLE_TABLEAU_X / 2)

#define NB_PAVES 6

#define MAX_NODES (TAILLE_TABLEAU_X * TAILLE_TABLEAU_Y)

/************************************************
 *                                              *
 *          Définition des fonctions            *
 *                                              *
 ************************************************/
// Déclaration des fonctions fournies
void gotoXY(int x, int y);
// Déclaration des fonctions demandées
void afficher(int x, int y, char c);
void effacer(int x, int y);			
void effacerEcran();				

int kbhit();
void enableEcho();
void disableEcho();

// Déclaration des fonctions demandées
void afficher(int x, int y, char c);
void effacer(int x, int y);			
void effacerEcran();				

int checkAKeyPress();
void genererSerpent(int positionsX[TAILLE_MAX_SERPENT], int positionsY[TAILLE_MAX_SERPENT], int x, int y, char direction);
void initPlateau();
void devInfo(int positionsX[20], int positionsY[20], char direction);

void dessinerPlateau();
void afficherSerpent(int positionsX[TAILLE_MAX_SERPENT], int positionsY[TAILLE_MAX_SERPENT]);
void effacerSerpent(int positionsX[TAILLE_MAX_SERPENT], int positionsY[TAILLE_MAX_SERPENT]);
void progresser(int positionsX[TAILLE_MAX_SERPENT], int positionsY[TAILLE_MAX_SERPENT], char direction, bool* detecCollision, int numSerpent);
void serpentDansTab(int positionsX[TAILLE_MAX_SERPENT], int positionsY[TAILLE_MAX_SERPENT], int numSerpent);

void changerDirection(char* direction, int positionsX[TAILLE_MAX_SERPENT], int positionsY[TAILLE_MAX_SERPENT]);	
int genererEntierDansBornes(int min, int max);
void genererPaves();
void genererTrous();
void ajouterPomme(int indice);
void succesJeu();
void echecJeu();
void quitterJeu();

void detecterPomme(int* pommeX, int* pommeY);

char choisirDirection(int xTete, int yTete, char directionActuelle, int cibleX, int cibleY); // Fonction qui choisit la direction du serpent
int distanceCarree(int x1, int y1, int x2, int y2); // Fonction qui calcule la distance entre deux points
void determinerCible(int cible[2], int positionsX[TAILLE_MAX_SERPENT], int positionsY[TAILLE_MAX_SERPENT]);


typedef char t_plateau[TAILLE_TABLEAU_Y][TAILLE_TABLEAU_X];
typedef struct Node {
    int x, y;
    int gCost, hCost, fCost;
    struct Node* parent;
} Node;

Node nodes[MAX_NODES];
bool openSet[MAX_NODES];
bool closedSet[MAX_NODES];

t_plateau tableau;
int tailleSerpent = TAILLE_SERPENT;
int vitesseJeu = VITESSE_JEU_INITIALE;
int lesPommesX[NB_POMMES] = {75, 75, 78, 2, 8, 78, 74, 2, 72, 5};
int lesPommesY[NB_POMMES] = {8, 39, 2, 2, 5, 39, 33, 38, 35, 2};
int lesPavesX[NB_PAVES] = { 3, 74, 3, 74, 38, 38};
int lesPavesY[NB_PAVES] = { 3, 3, 34, 34, 21, 15};
int pommeDetecX = 0;
int pommeDetecY = 0;
int nbPommesMangees = 0; // On traque combien de pommes on mange pour pouvoir faire apparaitre la bonne une fois mangée

bool speed = false; // Mode speedrun
bool debug = false; // Mode debug
bool affichage = true; // Mode affichage

int nbrMouvements1 = 0;
int nbrMouvements2 = 0;
int nbrPommes1 = 0;
int nbrPommes2 = 0;
clock_t tempsCPUDepart = 0;
clock_t tempsCPUFin = 0;