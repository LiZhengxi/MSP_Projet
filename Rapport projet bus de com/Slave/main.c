#include <msp430.h> 
#include <intrinsics.h>
#include "Driver_Motor_IR.h"
#include "SPI_Init.h"


/*
 * Nom : main
 *
 * Description: Ce main permet de gerer tous les actions de slave. Une fois le master envoyer l'information
 * et le slave a reçue. Le slave va demander le servomoteur tourner à 0°, 90°, 180° d'après différents informations
 * reçues
 *
 * Description 2: cette fonction comporte tous inialisation de slave y compris initialisation de SPI et servomoteur(PWM)
 * et aussi l'interruption si SPI a reçue les informations
 */
int main( void )
{
    /* Stop watchdog timer to prevent time out reset */
    WDTCTL = WDTPW | WDTHOLD;

 if(CALBC1_1MHZ==0xFF (||) CALDCO_1MHZ==0xFF)
    {
        __bis_SR_register(LPM4_bits);
    }
    else
    {
        /* Factory Set */
        DCOCTL = 0;
        BCSCTL1 = CALBC1_1MHZ;
        DCOCTL = (0 | CALDCO_1MHZ);
    }

    /* --------------- Secure mode */
    P1SEL = 0x00;        /* GPIO */
    P1DIR = 0x00;         /* IN */

    /* Led */
    P1DIR |=  BIT0;
    P1OUT &= ~BIT0;
    Init_SPI();
    Motor_IR_Init();
    (uint_32)TACCR1 = Motor_Set_Deg(90);   	/* turn to 90бу */
    __delay_cycles(800000);		/* Wait */
        __bis_SR_register(LPM4_bits | GIE); 	/* general interrupts enable & Low Power Mode */
    }


/* --------------------------- R O U T I N E S   D ' I N T E R R U P T I O N S */

/* ************************************************************************* */
/* VECTEUR INTERRUPTION USI                                                  */
/* ************************************************************************* */
#pragma vector=USI_VECTOR
__interrupt void USCI0RX_ISR(void)
{

	if (RX_Data()== (uint_32)0x30) /* if the input buffer is 0x30 (mainly to read the buffer) */
	{
		 (uint_32)TACCR1 = Motor_Set_Deg(0);   /* turn to 0бу */
		 __delay_cycles(80000);		/* Wait */
	}
	else if (RX_Data()== (uint_32)0x32)
	{
		(uint_32)TACCR1 = Motor_Set_Deg(180);   /* turn to 180бу */
	 	__delay_cycles(80000);		/* Wait */

	}
	else if (RX_Data()== (uint_32)0x31)
	{
		(uint_32)TACCR1 = Motor_Set_Deg(90);   /* turn to 90бу */
		 __delay_cycles(80000);			/* Wait */

	}
	else
	{
		(uint_32)TACCR1 = Motor_Set_Deg(0);   /* turn to 0бу */
		 __delay_cycles(80000);			/* Wait */

	}
}
/*------------------------------------------------------------------ End ISR */
