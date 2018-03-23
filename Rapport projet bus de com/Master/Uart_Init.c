/*
 *  Nom: Uart_Init.c
 *
 *  Description : Ce fichier comporte tous les fonctions pour UART
 *
 *  Date de cr¨¦ation : 2.16
 *
 *  Version : 1.0
 *
 *
 */

#include <msp430g2553.h>
#include "Uart_Init.h"

/*
 * initialiser UART
 * P1.1 comme RXD , P1.2 comme TXD
 * baudrate : 9600
 * fr¨¦quence du microp: 1MHz
 * Activer l'interrupteur USCI_A0 RX
 */
void InitUART(void) {

    P1SEL |= (BIT1 + BIT2);                 /* P1.1 = RXD, P1.2=TXD*/
    P1SEL2 |= (BIT1 + BIT2);                /* P1.1 = RXD, P1.2=TXD*/
    UCA0CTL1 |= UCSSEL_2;                   /* SMCLK*/
    UCA0BR0 = 104;                          /*1MHz, 9600*/
    UCA0BR1 = 0;                            /* 1MHz, 9600*/
    UCA0CTL0 &= ~UCPEN & ~UCPAR & ~UCMSB;
    UCA0CTL0 &= ~UC7BIT & ~UCSPB & ~UCMODE1;
    UCA0CTL0 &= ~UCMODE0 & ~UCSYNC;
    UCA0CTL1 &= ~UCSWRST;                   / **Initialize USCI state machine**/


    IE2 |= UCA0RXIE;                        /* Enable USCI_A0 RX interrupt*/
}
/*
 * initialiser ports
 * P1.0 et P1.6 comme sortie
 */
void InitPort(void) {
    P1SEL &= (~BIT0 | ~BIT6);                 /* P1.0 P1.6 output*/
    P1SEL2 &= (~BIT0 | ~BIT6);
    P1DIR |= BIT0;
}
/*
 * envoyer une caractere
 */
void TXdata(UCHAR c) {
    while (!(IFG2 & UCA0TXIFG))  /* USCI_A0 TX buffer ready?*/
    {
};
	UCA0TXBUF = c;              /*TX -> RXed character*/
}

/*
 * envoyer la chaine des carateres
 */
void print_str(UCHAR *c)
{
    while (*c) {
        TXdata(*c++);
    }
}
