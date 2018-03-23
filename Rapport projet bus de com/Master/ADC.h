/*
 *  nom: ADC.h
 *
 *  Description : bibliothe de ADC(infrarouge), permet d'initialiser ADC, convertir le valeur capturer par
 *  infrarouge, et aussi initialiser les ports peuvent utiliser par infrarouge
 */

#ifndef ADC_H_
#define ADC_H_
typedef UCHAR;
typedef unsigned int UINT_32;
void ADC_init(void);

void ADC_Demarrer_conversion(UCHAR voie);

UINT_32 ADC_Lire_resultat (void);

void initline(void);
#endif /* ADC_H_ */
