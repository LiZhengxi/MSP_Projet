//------------------------------------------------------------------------------
// uart_simple.c
//Appuyer h pour le menu
//Appuyer sur 'a' pour allumer leds
//Appuyer sur 'e' pour eteindre deux leds
//Si ça ne correspend pas, afficher 'eurreur'
//------------------------------------------------------------------------------
#include <msp430g2553.h>
unsigned char c[] = "\n appuyer h pour affichage de l’aide\r\n ";
unsigned char m[] ="\r\na)Allumer LED1 et LED 2\r\nb)Allumer LED1 \r\nc)Eteindre LED1\r\ne)Eteindre LED1 et LED 2\r\n";
unsigned char e[] = "\r\nErreur\r\n";


void InitUART(void) {
    P1SEL |= (BIT1 + BIT2);                 // P1.1 = RXD, P1.2=TXD
    P1SEL2 |= (BIT1 + BIT2);                // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2;                   // SMCLK
    UCA0BR0 = 104;                          // 1MHz, 9600
    UCA0BR1 = 0;                            // 1MHz, 9600
    UCA0CTL0 &= ~UCPEN & ~UCPAR & ~UCMSB;
    UCA0CTL0 &= ~UC7BIT & ~UCSPB & ~UCMODE1;
    UCA0CTL0 &= ~UCMODE0 & ~UCSYNC;
    UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                        // Enable USCI_A0 RX interrupt
}

void Initport() {
    P1SEL &= ~(BIT0 + BIT6);
    P1SEL2 &= ~(BIT0 + BIT6);
    P1DIR |= (BIT0 + BIT6);
}

void TXdata(unsigned char c) {
    while (!(IFG2 & UCA0TXIFG));  // USCI_A0 TX buffer ready?
    UCA0TXBUF = c;              // TX -> RXed character
}
void send_str(unsigned char *c) {
    while (*c != '\0') {
        TXdata(*c++);
    }
}

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    BCSCTL1 = CALBC1_1MHZ;      // Set DCO to 1Mhz
    DCOCTL = CALDCO_1MHZ;       // Set DCO to 1Mhz
    P1DIR = BIT0;

    Initport();
    InitUART();

    __bis_SR_register(GIE); // interrupts enabled
    send_str(c);
    while (1);
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {
    unsigned char c;
    int i;
    c = UCA0RXBUF;
    TXdata(c);
    if (c == 'h') {
        send_str(m);
    } else if (c == 'a') {
       P1OUT |= (BIT0+BIT6);
       send_str("\r\nAllumé\r\n");
    } else if (c == 'e') {
       P1OUT &= ~(BIT0+BIT6);
       send_str("\r\nEteint\r\n");
    }
      else if(c=='b')
      {
          P1OUT |=BIT0;
          send_str("\r\Allumén\r\n");
      }
      else if(c=='c')
      {
          P1OUT &=~BIT0;
          send_str("\r\nEteint\r\n");
      }
    else {
        send_str(e);
    }

}


