/*
* Nom: robotv2.c
*
* Description : Ce fichier comporte tous les fonctions par rapport à robot rouge(SAMbot)
*
* Date de création : 03.01.2018
*
* Version : 1.0
*/

#include <msp430g2553.h>
#include "robotv2.h"



//------------------------------------------------------------------------------
//Init_Robot :  Faire l'appel au début du programme permet d'initialiser les ports
//de contrôler le robot.(fonction  permettant d'initialiser le timer avec deux sortie PWM
// sur les voies P2.2 et P2.4. Cette fonction initialise aussi les lignes P2.1 et P2.5
// qui définit le   sens de rotation des moteurs)
//
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------

void Init_Robot()
{
    P2DIR |= BIT2 | BIT4;                //P2.2 et P2.4 (PWM moteurs) en sortie(2 pwm)
    
    P2SEL |= BIT2 | BIT4;                // sortie PWM sur P2.2 et P2.4 (moteurs)
    P2SEL2 &= ~(BIT2| BIT4);             // selection fonction TA1.1 sur P2.2 et TA.2 sur P2.4
                        

    P2DIR |= (BIT1 | BIT5);              // P2.1,P2.5 output : sens moteurs A et B(sortir de moteur gauche et droit)
    
    TA1CTL = TASSEL_2 | MC_1;            // select TimerA source SMCLK, set mode to up-counting
    
    TA1CCR0 = 200;                       // periode du signal PWM 5KHz
    
}


//------------------------------------------------------------------------------
//Choix_direction :  Faire l'appel lorsque nous avons besoin
//de définir le sens de robot. Donc 0 pour avancer,1 pour tourner à gauche, 2 pour
//reculer,3 pour tourner à droit
//
// IN:        unsigned char sens
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------


void Choix_direction(unsigned char sens)
{
  P2OUT &= ~BIT1;                      // P2.1 a 0 (sens rotation moteur 1)
  P2OUT &= ~BIT5;                      // P2.5 a 0 (sens rotation moteur 2)
  P2OUT = P2OUT + (((sens<<1)+(sens<<4))& 0x22);  // algorithme pour définit le sens de robot
}

//------------------------------------------------------------------------------
//Vitesse_moteurs :  Faire l'appel lorsque nous avons besoin
//de modifier la vitesse de robot. La vitesse doit compris entre 0 à 200
//
// IN:        unsigned int vit_gauche, unsigned int vit_droite
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------

void Vitesse_moteurs(unsigned int vit_gauche, unsigned int vit_droite)
{
  TA1CCR1 = vit_gauche;                      // rapport cyclique moteur 1
  TA1CCR2 = vit_droite;                      // rapport cyclique moteur 2
}

//------------------------------------------------------------------------------
//Arret_robot :  Faire l'appel lorsque nous avons besoin
//d'arrêter le robot.
//
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------

void Arret_robot()
{
  TA1CCTL1 = OUTMOD_0;                 // select timer compare mode
  TA1CCTL2 = OUTMOD_0;                 // select timer compare mode
}


//------------------------------------------------------------------------------
//Demarrer_robot :  Faire l'appel lorsque nous avons besoin
//de démarrer le robot.
//
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------

void Demarrer_robot()
{
  TA1CCTL1 = OUTMOD_7;                 // select timer compare mode
  TA1CCTL2 = OUTMOD_7;                 // select timer compare mode
}

//------------------------------------------------------------------------------
//tempo :  Faire l'appel lorsque nous avons besoin
//de créer un temp d'attendre bien convertir en ms(au lieu de cycle du programme).
//
// IN:        unsigned int ms
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------/

void tempo( unsigned int ms)
{
  unsigned int i=0;
  for (i=0;i<ms;i++)  {
    __delay_cycles(1000); }
  
}
