/*
*  Bibliotheque de fonction pour tous les fonctions par rapport à robot rouge(SAMbot)
*/


/*.............................................................................*/
/* Fonction  permettant d'initialiser le timer avec deux sortie PWM            */
/* sur les voies P2.2 et P2.4                                                  */
/* Cette fonction initialise aussi les lignes P2.1 et P2.5 qui d閠erminent le  */
/* sens de rotation des moteurs                                                */
/*.............................................................................*/ 
void Init_Robot();



/*............................................................................*/
/* Fonction  permettant de choisir le sens de fonctionnement des moteurs      */
/*  Il y a quatre possibilit閟 permettant d'avancer, reculer, tourner �       */
/*  gauche ou � droite.                                                       */
/*............................................................................*/

void Choix_direction(unsigned char sens);


/*............................................................................*/
/* Fonction  permettant de d閒inir la vitesse des moteurs                     */
/*  Pour compenser les disparit閟 des moteurs il faut envoyer deux vitesses   */
/*  gauche et droite. Les valeurs doivent 阾re comprises entre 0 et 200       */
/*............................................................................*/

void Vitesse_moteurs(unsigned int vit_gauche, unsigned int vit_droite);


/*............................................................................*/
/* Fonction  permettant de stopper le robot par arr阾 des commandes moteurs   */
/*............................................................................*/

void Arret_robot();



/*............................................................................*/
/* Fonction  permettant de d閙arrer le robot par envoi des commandes moteurs  */
/*............................................................................*/

void Demarrer_robot();


/*............................................................................*/
/* Fonction r閍lisant une temporisation param鑤r閑 en millisecondes max:65535 */
/*............................................................................*/

void tempo( unsigned int ms);
