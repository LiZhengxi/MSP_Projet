/*
 *  Nom : Driver_Motor_IR
 *
 *  Description : ce fichier comporte tous les fonctions pour contrôler le servomoteur
 *
 *  Date de création : 15.03.2018
 *
 */

#include "Driver_Motor_IR.h"


/*
 *  Nom : Motor_IR_Init
 *
 *  Description : Permet d'effectuer le fonction Motor_Start() et fonction Motor_PWM_Init()
 *
 *  in : none.
 *
 *  out : none.
 */
void Motor_IR_Init(void){
	/*Motor management*/
	Motor_Start();

	/*PWM init*/
	Motor_PWM_Init();
}
/*
 * Nom : Motor_PWM_Init
 *
 * Description : Permet de créer un PWM de période 2000
 *
 * in : none.
 *
 * out : none.
 */

void Motor_PWM_Init(void){
	BCSCTL1 = CALBC1_1MHZ; 				/*Clock frequency 1MHz*/
	DCOCTL 	= CALDCO_1MHZ; 				/*Clock frequency 1MHz*/
	TACTL 	= (TASSEL_2 | MC_1 | ID_0);
	TACCTL1 = OUTMOD_7;
	TACCR0 	= 20000;
	TACCR1 	= MOTOR_INIT_DEG;

	__enable_interrupt();
}

/*
 *  Nom : Motor_stop
 *
 *  Description: Permet de arrêter le servomoteur(mettre le P1.2 en entrer)
 *
 *  in : none.
 *
 *  out :none.
 */
void Motor_Stop(void){
	P1DIR &= ~(IR_MOTOR);
}

/*  Nom: Motor_Start
 *
 *  Description : Permet de démarrer le servomoteur(mettre le P1.2 en sortir)
 *
 *  in : none.
 *
 *  out : none.
 */
void Motor_Start(void){
	P1SEL |= IR_MOTOR;
	P1DIR |= IR_MOTOR;
}

/*
 * Nom: Motor_Set_Deg
 *
 * Description : permet de laiser le servomoteur de tourner un certain angle(0°,45°,90°,135°,180°)
 *
 * in : int deg
 *
 * out : int taccr(pour définir le rapport cyclique)
 */

uint_32 Motor_Set_Deg(uint_32 deg){
	uint_32 taccr = 0;

	/* < 45 */
	if(deg == (uint_32)0){
		taccr = (uint_32)((uint_32)MOTOR_MAX_DEG / (uint_32)5);
	/* > 0 & < 45 */
	}else if(deg > (uint_32)0 (&&) deg <= (uint_32)45){
		taccr = (uint_32)(((uint_32)2 * (uint_32)MOTOR_MAX_DEG) / (uint_32)5);
	/* > 45 & < 90 */
	}else if(deg > (uint_32)45 (&&) deg <= (uint_32)90){
		taccr = (uint_32)(((uint_32)3 * (uint_32)MOTOR_MAX_DEG) / (uint_32)5);
	/* > 90 & < 135 */
	}else if(deg > (uint_32)90 (&&) deg <= (uint_32)135){
		taccr = (uint_32)(((uint_32)4 * (uint_32)MOTOR_MAX_DEG) / (uint_32)5);
	/* > 135 & 180 */
	}else if(deg > (uint_32)135 (&&) deg <= (uint_32)180){
		taccr = (uint_32)MOTOR_MAX_DEG;
	}
	else{
		taccr = (uint_32)MOTOR_MAX_DEG;
	}

	return taccr;
}
