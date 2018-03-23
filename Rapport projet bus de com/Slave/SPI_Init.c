/*
 * Nom : SPI_Init.c
 *
 * Description : ce fichier comporte tous les fonctions pour le SPI (reçue)
 *
 * Date de création : 03.15.2018
 *
 * Version : 1.5
 */

/*
 *  Nom: Init_SPI
 *
 *  Description : initialiser les registers pour faire la commuication SPI
 *
 *  in : none.
 *
 *  out : none.
 *
 */
#include <msp430.h>

typedef char char;

void Init_SPI(void){
      USICTL0 |= USISWRST;                          /* start config */
      USICTL0 |= USIPE7 + USIPE6 + USIPE5 + USIOE;  /* Port, SPI slave */
      USICTL1 |= USIIE;                             /* Counter interrupt, flag remains set */
      USICNT = 8;                                   /* init-load counter */
      USICTL1 |= USICKPL;                       /* Setup clock polarity --> keep low */
      USICTL1 |= USICKPH;                           /* Setup phase */
      USICTL0 &= ~USISWRST;                         /* USI released for operation stop config */

}
/*
 * Nom : RX_Data
 *
 * Description : permet de recevoir l'information
 *
 * in : none.
 *
 * out : unsigned char USISRL(information reçues)
 *
 */

char RX_Data(void){
      while((USICTL1 & USIIFG) != BIT0)			/* Scrutation */
	{}; 								
      return USISRL;
}


