
// Déclaration des constantes
/**
 * \def TAILLE_TABLEAU
 * \brief La taille du tableau dans lequel le serpent va évoluer
 */
#define TAILLE_TABLEAU_X 80
#define TAILLE_TABLEAU_Y 40

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
#define VITESSE_JEU_INITIALE 200000

/**
 * \def TOUCHE_ARRET
 * \brief La touche sur laquelle appuyer pour arrêter le jeu
 */
#define TOUCHE_ARRET 'a'

/**
 * \def CHAR_TETE
 * \brief Le caractère qui correspond à la tête du serpent
 */
#define CHAR_TETE 'O'

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
#define DIRECTION_INITIALE 'd'

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
#define X_DEBUT 40

/**
 * \def Y_DEBUT
 * \brief La position horizontale à laquelle le serpent doit démarrer
 */
#define Y_DEBUT 20

/**
 * \def DIRECTION_INITIALE
 * \brief La direction dans laquelle le serpent doit se déplacer au début
 */
#define DIRECTION_INITIALE 'd'

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