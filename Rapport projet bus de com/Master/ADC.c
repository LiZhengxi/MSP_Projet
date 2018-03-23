/*
 *  Nom :  ADC.c
 *
 *  Description : Ce fichier comporte tous les fonctions pour le capteur infrarouge(ADC)
 *
 *  Date de cr��ation : 03.06.2018
 *
 *  Version : 1.0
 *
 */

#include "msp430g2553.h"
#include "ADC.h"

/*
 * Nom:  ADC_init
 *
 * Description : Permet de initialiser le ADC
 *
 * in : none.
 *
 * out : none.
 */
void ADC_init(void)
{
      ADC10CTL0  = 0;
	ADC10CTL1  = 1;

/* Choix de la r锟絝锟絩ence de tension Vcc GND
 *R锟絝锟絩ence interne active et g锟絥锟絩ateur 锟� 2,5 Volts  ADC10 actif
 *Les autres bits sont suppos锟絪 锟� 0*/

     ADC10CTL0 =  SREF_0 + ADC10SHT_0  + REF2_5V + REFON + ADC10ON;  ;

/*Choix du diviseur par 1 pour l'horloge, d锟絤arrage conversion logiciel
 Horloge de conversion 1MHz, conversion monovoie-monocoup*/

      ADC10CTL1 =  ADC10DIV_0 + ADC10SSEL_2 +  SHS_0 + CONSEQ_0 ;

}
/*
 * nom: ADC_Demarrer_conversion
 *
 * Description : permet de convertire le chiffre capturer par infrarouge
 *
 * in : unsigned char voie
 *
 * out : none.
 */
void ADC_Demarrer_conversion(UCHAR voie)
{
    ADC10CTL1 = (voie * 0x1000U)+ ADC10DIV_0 + ADC10SSEL_2 +  SHS_0 + CONSEQ_0 ;
    ADC10CTL0 |= ENC + ADC10SC;     /* Sampling and conversion start*/
 }
/*
 * nom : ADC_Lire_resultat
 *
 * Description : permet de retourner le valeur lire par infrarouge
 * et convertir en format int
 *
 * in : none.
 *
 * out: int ADC10MEM
 */

UINT_32 ADC_Lire_resultat (void)
{
    while (ADC10CTL1 & ADC10BUSY) /* Tant que ADC occup锟� on attend*/
{
};  
    ADC10CTL0 &= ~ENC;      /* Conversion finie alors Disable ADC conversion*/

        return (UINT_32)ADC10MEM;            /* Return Conversion value*/
}
/*
 * nom: initline
 *
 * description : permet de inialiser les ports peuvent utilis�� par infrarouge
 *
 * in : none
 *
 * out : none
 */
void initline(void){
    P1SEL &= ~(BIT0);
    P1SEL2 &= ~(BIT0);
    P1DIR &= ~(BIT0);/* pin 1.0 input*/
    ADC10AE0 |= BIT0;

    P1SEL &= ~(BIT6);
       P1SEL2 &= ~(BIT6);
       P1DIR &= ~(BIT6);/* pin 1.6 input*/
       ADC10AE0 |= BIT6;
}

