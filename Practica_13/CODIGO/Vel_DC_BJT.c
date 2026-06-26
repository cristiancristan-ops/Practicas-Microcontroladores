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

void cambiarPWM(unsigned int valor)
{
    CCPR1L = valor >> 2;
    CCP1CONbits.DC1B0 = valor & 1;
    CCP1CONbits.DC1B1 = (valor >> 1) & 1;
}

void main(void)
{
    unsigned int valor;

    ANSEL = 0b00000001;
    ANSELH = 0;

    TRISAbits.TRISA0 = 1;
    TRISCbits.TRISC2 = 0;

    PORTCbits.RC2 = 0;

    // ADC
    ADCON1 = 0b10000000;
    ADCON0 = 0b10000001;

    // PWM con CCP1 y Timer2
    PR2 = 255;
    CCP1CON = 0b00001100;
    CCPR1L = 0;

    // Timer2 encendido, preescalador 1:16
    T2CON = 0b00000110;

    while(1)
    {
        valor = leerADC();
        cambiarPWM(valor);
        __delay_ms(5);
    }
}