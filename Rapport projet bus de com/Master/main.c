#include <msp430g2553.h>
#include "robotv2.h"
#include "SPI_Init.h"
#include "ADC.h"
#include "Uart_Init.h"

unsigned char UCHAR;
unsigned int UINT_32;

const UCHAR menu1[] =
		"\n- 'z' pour avancer \r\n"
		"- 's' pour reculer\r\n"
		"- 'q' pour tourner a gauche\r\n"
        "-'d' pour tourner a droit\r\n"
        "-'n' pour arreter le robot"
		"Entrez votre choix\r\n";
const UCHAR menu0[] =
        "\n- 'a' pour mode autonome  \r\n"
        "\n -m' pour mode  manuel\r\n"
        "Entrez votre choix\r\n";

const UCHAR erreur[] = "\r\nIl y a une erreur!!\r\n";
UINT_32 infrarouge;

void automatique(void)
{   UCHAR c;
while(1)
 {    __delay_cycles(100000);
     Choix_direction(2);  /* 2 avancer, 0 tourner 锟� droit ,1 reculer , 3 tourner 锟� gauche*/
     Demarrer_robot();
     do
         {
         ADC_Demarrer_conversion(0x00);
         infrarouge=ADC_Lire_resultat ();
         }while(infrarouge<=500U);
         Arret_robot();

         while (!(IFG2&UCB0TXIFG))
{
};
               UCB0TXBUF = 0x30;     /* Transmit first character*/

               __delay_cycles(1000000);
               ADC_Demarrer_conversion(0x00);
               infrarouge=ADC_Lire_resultat ();
               if(infrarouge>=500U)
               {
               while (!(IFG2&UCB0TXIFG))
{
};
                   UCB0TXBUF = 0x32;                     /* Transmit first character*/
                 __delay_cycles(2000000);
                 ADC_Demarrer_conversion(0x00);
                   infrarouge=ADC_Lire_resultat ();
                if(infrarouge<=500U)
                    {
                         Choix_direction(3);  /* 2 avancer, 0 tourner 锟� droit ,1 reculer , 3 tourner 锟� gauche*/
                         Demarrer_robot();
                          tempo(400);
                               }
                else
                {
                    Arret_robot();
                }
               }
               else
               {
                    UCB0TXBUF = 0x31;                     /* Transmit first character*/
                    __delay_cycles(500000);
                    Choix_direction(0);  /* 2 avancer, 0 tourner 锟� droit ,1 reculer , 3 tourner 锟� gauche*/
                    Demarrer_robot();
                    tempo(400);
               }

               UCB0TXBUF = 0x31;


 }
}


/*
 *
 *  Nom: main
 *
 *  Description : ce fonction permet d'à la fois contrôler le mouvement du robot, capturer le valeur d'infrarouge,
 *  envoyer l'inforamation au slave par SPI et aussi envoyer et recevoir l'information par UART(bluetooth). En gros,
 *  il y a deux type de fonctionnement, mode autonome et mode manuel. En mode autonome, le robot va détecter soi-même
 *  les obstacle devant ou à côté. En mode manuel, vous pouvez contrôler le robot directement par bluetooth.
 *
 *  Description de fonction : ce fonction comporte tous les iniation de chaque fonctionalité et l'envoie et reçue de UART
 *  et aussi intégré dessus.
 */
int main(void) {

	WDTCTL = WDTPW + WDTHOLD;	/* Stop WDT*/
	DCOCTL= 0;				
	BCSCTL1 = CALBC1_1MHZ;      /* Set DCO to 1Mhz*/
	DCOCTL = CALDCO_1MHZ;       /* Set DCO to 1Mhz*/
	P1OUT |= BIT0;

	InitPort();
	ADC_init();
	SPI_Init();
	InitUART();
	Init_Robot();
	initline();
    Vitesse_moteurs(190, 190);
	__bis_SR_register(GIE); /* interrupts enabled*/

	print_str(menu0);
	while (1)
{
};
}
/*
 *  Description : cette interruption permet d'activer lorsque le UART a reçue l'info
 */

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {
	UCHAR c;
	c = UCA0RXBUF;
	TXdata(c);
	if(c=='m')
	{
	print_str(menu1);   /* le robot va tomber en mode manuel*/
	}

	else if (c == 'z') {

	    Choix_direction(2);  /* 2 pour avancer*/
	     Demarrer_robot();
	}
	else if(c=='a')
	{
	    automatique();  /*si on tape 'a', le robot va entrer dans le mode autonome*/
	}
	else if (c == 's') {

		Choix_direction(1);  /* 1 pour reculer*/
		Demarrer_robot();

	} else if (c == 'q') {
	    Choix_direction(3);  /* 3 pour tourner à gauche*/
	    Demarrer_robot();
	    tempo(400);
	    Arret_robot();
	    Choix_direction(2);  /* 2 pour avancer*/
	    Demarrer_robot();
	}
	else if (c == 'd') {
	        Choix_direction(0);  /* 0 pour tourner à droit*/
	        Demarrer_robot();
	        tempo(400);
	        Arret_robot();
	        Choix_direction(2);  /* 2 pour  avancer*/
	        Demarrer_robot();
	    }
	else if (c == 'n') {
	    Arret_robot();  /* Si on tape 'n', le robot va arrêter*/
	}
	else {
		UINT_32 i;
		i=1;
	}
	}

