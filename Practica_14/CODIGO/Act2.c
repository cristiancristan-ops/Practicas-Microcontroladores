#include <xc.h>

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 8000000

unsigned int leerADC(void)
{
    __delay_us(20);

    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE);

    return ((unsigned int)ADRESH << 8) | ADRESL;
}

void esperarTimer1(unsigned int cuentas)
{
    unsigned int inicio = 65536 - cuentas;

    T1CONbits.TMR1ON = 0;

    TMR1H = inicio >> 8;
    TMR1L = inicio;

    PIR1bits.TMR1IF = 0;
    T1CONbits.TMR1ON = 1;

    while(!PIR1bits.TMR1IF);

    T1CONbits.TMR1ON = 0;
}

void main(void)
{
    unsigned int adc;
    unsigned int pulso;

    ANSEL = 0b00000001;       // AN0 analógico
    ANSELH = 0;

    TRISAbits.TRISA0 = 1;     // Potenciómetro
    TRISCbits.TRISC2 = 0;     // Señal del servo

    PORTCbits.RC2 = 0;

    ADCON1 = 0b10000000;
    ADCON0 = 0b10000001;

    T1CON = 0b00110000;

    while(1)
    {
        adc = leerADC();

        pulso = 125 + ((unsigned long)adc * 500) / 1023;

        // Pulso alto del servo
        PORTCbits.RC2 = 1;
        esperarTimer1(pulso);

        PORTCbits.RC2 = 0;
        esperarTimer1(5000 - pulso);
    }
}