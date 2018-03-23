/*
 * Bibliotheque pour tous les fonctions de servomoteur
 */
#ifndef DRIVER_MOTOR_IR_HEADER
#define DRIVER_MOTOR_IR_HEADER

#include <msp430g2231.h>

#define IR_MOTOR BIT2   /*P1.2 bit signal de servomoteur*/
#define MOTOR_INIT_DEG 500  /*rapport cyclique iniale*/
#define MOTOR_MAX_DEG 2500  /*rapoort cyclique max*/

typedef unsigned int uint_32;


void Motor_IR_Init(void);

void Motor_PWM_Init(void);

void Motor_Stop(void);

void Motor_Start(void);

uint_32 Motor_Set_Deg(uint_32 deg);

#endif
