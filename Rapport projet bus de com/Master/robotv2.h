/*
*  Bibliotheque de fonction pour tous les fonctions par rapport à robot rouge(SAMbot)
*/

typedef unsigned int UINT_32;
typedef unsigned char UCHAR;
typedef signed int SINT_32;
/*.............................................................................*/
/* Fonction  permettant d'initialiser le timer avec deux sortie PWM            */
/* sur les voies P2.2 et P2.4                                                  */
/* Cette fonction initialise aussi les lignes P2.1 et P2.5 qui d閠erminent le  */
/* sens de rotation des moteurs                                                */
/*.............................................................................*/ 
void Init_Robot(void);



/*............................................................................*/
/* Fonction  permettant de choisir le sens de fonctionnement des moteurs      */
/*  Il y a quatre possibilit閟 permettant d'avancer, reculer, tourner �       */
/*  gauche ou � droite.                                                       */
/*............................................................................*/

void Choix_direction(UCHAR sens);


/*............................................................................*/
/* Fonction  permettant de d閒inir la vitesse des moteurs                     */
/*  Pour compenser les disparit閟 des moteurs il faut envoyer deux vitesses   */
/*  gauche et droite. Les valeurs doivent 阾re comprises entre 0 et 200       */
/*............................................................................*/

void Vitesse_moteurs(UINT_32vit_gauche, UINT_32 vit_droite);


/*............................................................................*/
/* Fonction  permettant de stopper le robot par arr阾 des commandes moteurs   */
/*............................................................................*/

void Arret_robot(void);



/*............................................................................*/
/* Fonction  permettant de d閙arrer le robot par envoi des commandes moteurs  */
/*............................................................................*/

void Demarrer_robot(void);


/*............................................................................*/
/* Fonction r閍lisant une temporisation param鑤r閑 en millisecondes max:65535 */
/*............................................................................*/

void tempo( UINT_32);
