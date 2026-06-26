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

unsigned int Leer_ADC(unsigned char canal)
{
    ADCON0 = (ADCON0 & 0b11000011) | (canal << 2);

    __delay_us(20);

    ADCON0bits.GO_nDONE = 1;

    while(ADCON0bits.GO_nDONE);

    return ((unsigned int)ADRESH << 8) | ADRESL;
}

void Cambiar_PWM1(unsigned int valor)
{
    CCPR1L = valor >> 2;

    CCP1CONbits.DC1B0 = valor & 1;
    CCP1CONbits.DC1B1 = (valor >> 1) & 1;
}

void Cambiar_PWM2(unsigned int valor)
{
    CCPR2L = valor >> 2;

    CCP2CONbits.DC2B0 = valor & 1;
    CCP2CONbits.DC2B1 = (valor >> 1) & 1;
}

void main(void)
{
    unsigned int pot1, pot2;

    ANSEL = 0b00000011;
    ANSELH = 0;

    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;

    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;

    PORTCbits.RC1 = 0;
    PORTCbits.RC2 = 0;

    // Configuración ADC
    ADCON1 = 0b10000000;
    ADCON0 = 0b10000001;

    // Configuración de los dos PWM
    PR2 = 255;

    CCP1CON = 0b00001100;
    CCP2CON = 0b00001100;

    CCPR1L = 0;
    CCPR2L = 0;

    // Timer2 encendido con preescalador 1:16
    T2CON = 0b00000110;

    while(1)
    {
        pot1 = Leer_ADC(0);
        pot2 = Leer_ADC(1);

        Cambiar_PWM1(pot1);
        Cambiar_PWM2(pot2);

        __delay_ms(5);
    }
}