#include <msp430.h>

#define ADC10 BIT7 //ADC10 is on BIT7
#define RXD BIT1    //UART RX is on BIT1
#define TXD BIT2     //UART TX is on BIT2

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

    /**
     * Initialization inspired by TI resource center.
     */
    /*
     * Configure Timer
     */
    TA0CCTL0 = CCIE;                          // Enable interrupt
    TA0CCR0 = 5;                         // PWM Period
    TACCTL1 = OUTMOD_3;                       // set/reset
    TACCR1 = 3;                             // default frequency, not needed
    TA0CTL = TASSEL_1 + MC_1 + ID_3;          // ACLK, continuous

    /*
     * Configure ADC10
     */
    ADC10CTL1 = INCH_7 + SHS_1;             // Start sampling
    ADC10AE0 = ADC10;

    /*
     * Configure UART
     */
    if (CALBC1_1MHZ==0xFF)                    // If calibration constant erased
    {
        while(1);
    }

    P1SEL = RXD + TXD;                    // SET RX and TX to not GPIO
    P1SEL2 = RXD + TXD;                  // Same as above.

    UCA0CTL1 |= UCSSEL_2;                   // SMCLK
    UCA0BR0 = 104;                          // 9600 baud
    UCA0BR1 = 0;                            // 9600 baud
    UCA0MCTL = UCBRS0;                      // Modulation UCBRSx = 1
    UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt

    /*
     * Timer for UART
     */
    DCOCTL = 0;                             // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;                  // Set DCO
    DCOCTL = CALDCO_1MHZ;

    __enable_interrupt();
    __bis_SR_register(GIE);       //interrupt enable
    while(1){ //  Debugger
    }
}

/*
 * UART Interrupt
 */
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    while (!(IFG2&UCA0TXIFG));                //TX Bus Rdy?

    if(UCA0RXBUF == 100)  // Input 'd'
        UCA0TXBUF = ADC10MEM >> 4; // Get the ADC10 value and transfer it
    else
        UCA0TXBUF = 1; // Wrong but
}
//Timer Interrupt
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)

{
    //From TI
    Gets ADC read value ready
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + REFON + ADC10ON;

    ADC10CTL0 |= ENC;                         // ADC10 enable set
}
