/*
 *  Nom:  SPI_Init.c
 *
 *  Desctiption: Ce fichier comporte tous les fonctions pour faire la communication SPI
 *
 *  de partie Master
 *
 *  Date de cr¨¦ation : 3.11
 *
 *  Version 1.2
 *
 */

#include"SPI_Init.h"
#include "msp430g2553.h"

/*
 * Nom : SPI_Init
 *
 * Description : Permet d'initialiser le register UCB0 comme le master et le UCA0 est occup¨¦ par
 * le UART. Donc on ne peut pas d'utiliser
 *
 * In : none.
 *
 * Out : none.
 */
void SPI_Init(void)
{
	 UCB0CTL1 |= UCSWRST;
	 P1DIR |= BIT5;                     
      P1SEL = BIT5 +BIT6+ BIT7;      /*BIT5 horloge ,BIT7 TX*/
      P1SEL2 = BIT5 + BIT6+BIT7;
      UCB0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC;  /* 3-pin, 8-bit SPI master*/
      UCB0CTL1 |= UCSSEL_2;                     /* SMCLK*/
      UCB0BR0 |= 0x02;                          /*mini diviser par 2*/
      UCB0BR1 = 0;                              
      UCB0CTL1 &= ~UCSWRST;                     / **Initialize USCI state machine**/
      __delay_cycles(75);                       /* Wait for slave to initialize*/

}
