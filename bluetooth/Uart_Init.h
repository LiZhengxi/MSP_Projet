/*
 * Nom: Uart_Init.h
 *
 * Description : Le bibliothe pour tous les fonctions peuvent utiliser en UART
 */

#ifndef UART_INIT_H_
#define UART_INIT_H_


void InitPort(void);
void InitUART(void);
void print_str(unsigned char *c);
void TXdata(unsigned char c);

#endif /* UART_INIT_H_ */
