#include <msp430.h> 

unsigned int adc_value =0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    /**
     * Initialization inspired by TI resource center.
     */
    /* Configures Timer*/
    TA0CTL = TASSEL_2 + MC_1 ;       // SMCLK / Upmode
    TA0CCTL0 = (CCIE);              //CCTL1 Compare/Capture Interrupt Enable
    TA0CCR0 = 1000-1;                        // PWM Frequency 10 kHz


    //Configure the port to be used as ADC input
    P6SEL |= 0x01;  // Port 6.1

    REFCTL0 &= ~REFMSTR; //Reset REFMSTR to hand over control of internal reference
    //voltages to ADC12_A control registers
    //Initialize the control register ADC12CTL0
    ADC12CTL0 = ADC12SHT0_4         // 64 ADC12CLK cycles in the sampling period
            // for registers ADC12MEM0
            +ADC12REFON         // ADC12_A reference generator on
            +ADC12REF2_5V     // Set ADC12_A reference generator voltage to 2.5V
            +ADC12ON;           // ADC12_A on

    //Initialize the control register ADC12CTL1
    ADC12CTL1=ADC12SHP;     // SAMPCON signal is sourced from the sampling timer.

    //Set conversion memory control register
    ADC12MCTL0 = ADC12SREF_1+ADC12INCH0;   //Select reference: VR+ = VREF+ and VR- = AVSS

    ADC12IE = 0x01; //enable interrupt
    ADC12CTL0 |= ADC12ENC; //enable conversion

    /*Configures UART*/
    P3SEL |= BIT3;          // UART TX
    P3SEL |= BIT4;          // UART RX
    UCA0CTL1 |= UCSWRST;    // Resets state machine
    UCA0CTL1 |= UCSSEL_2;   // SMCLK
    UCA0BR0 = 6;            // 9600 Baud Rate
    UCA0BR1 = 0;            // 9600 Baud Rate
    UCA0MCTL |= UCBRS_0;    // Modulation
    UCA0MCTL |= UCBRF_13;   // Modulation
    UCA0MCTL |= UCOS16;     // Modulation
    UCA0CTL1 &= ~UCSWRST;   // Initializes the state machine
    UCA0IE |= UCRXIE;

    //Start sampling



    __bis_SR_register(GIE); // Enter LPM0, interrupts enabled
    __no_operation(); // For debugger
}

// Echo back RXed character, confirm TX buffer is ready first
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{

    while (!(UCA0IFG&UCTXIFG)); // USCI_A0 TX buffer ready?
    if(UCA0RXBUF == 100)  // Input 'd' from keyboard to get data
        UCA0TXBUF = ADC12MEM0 >> 4; // Get the ADC12 value send it shift to read MSB
    else
        UCA0TXBUF = 1; // Show that the wrong button is pressed
}
// ADC Interrupt
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    __bic_SR_register_on_exit(CPUOFF);
}
/* Timer Interrupt*/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{
    /*Tells ADC to read values*/
    __delay_cycles(1000);
    ADC12CTL0 |= ADC12SC;                   // Start sampling/conversion
    __bis_SR_register(LPM0_bits + GIE);     // LPM0, ADC12_ISR will force exit
    __no_operation();                       // For debugger
}
