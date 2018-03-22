/*
 *  nom: ADC.h
 *
 *  Description : bibliothe de ADC(infrarouge), permet d'initialiser ADC, convertir le valeur capturer par
 *  infrarouge, et aussi initialiser les ports peuvent utiliser par infrarouge
 */

#ifndef ADC_H_
#define ADC_H_

void ADC_init(void);

void ADC_Demarrer_conversion(unsigned char voie);

int ADC_Lire_resultat ();

void initline();
#endif /* ADC_H_ */
