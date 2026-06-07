#include <xc.h>        // Biblioteca principal del compilador XC8

//==============================================================================
// CONFIGURACIÓN DE BITS DE CONFIGURACIÓN (FUSES)
//==============================================================================
// Selección de oscilador (usar XT si estás usando un cristal de 4 MHz)
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (disabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection (disabled)
#pragma config WRT = OFF        // Flash Program Memory Write Enable (disabled)
#pragma config CP = OFF         // Flash Program Memory Code Protection (disabled)

//==============================================================================
// DEFINICIONES
//==============================================================================
#define _XTAL_FREQ 4000000      // Frecuencia del oscilador para __delay_ms()

// Letras C R E D
unsigned char patronesC[8] = {0xC3, 0xBD, 0xFE, 0xFE, 0xFE, 0xFE, 0xBD, 0xC3};
unsigned char patronesR[8] = {0xC0, 0xBE, 0xBE, 0xC0, 0xF6, 0xEE, 0xDE, 0xBE};
unsigned char patronesE[8] = {0x80, 0xFE, 0xFE, 0xC0, 0xFE, 0xFE, 0xFE, 0x80};
unsigned char patronesD[8] = {0xC0, 0xBE, 0x7E, 0x7E, 0x7E, 0x7E, 0xBE, 0xC0};

void mostrarLetra(unsigned char letra[8])
{
    for(int t = 0; t < 250; t++)
    {
        for(unsigned char i = 0; i < 8; i++)
        {
            if(i == 0)
                PORTB = 0b10000000;
            else
                PORTB = 1 << (i - 1);

            PORTD = ~letra[i];
            __delay_ms(1);
        }
    }
}

void limpiarPantalla()
{
    PORTB = 0x00;
    PORTD = 0xFF;
    __delay_ms(100);
}

void main(void)
{
    ANSEL = 0;
    ANSELH = 0;

    TRISB = 0x00;
    TRISD = 0x00;

    PORTB = 0x00;
    PORTD = 0xFF;

    while(1)
    {
        mostrarLetra(patronesC);
        limpiarPantalla();

        mostrarLetra(patronesR);
        limpiarPantalla();

        mostrarLetra(patronesE);
        limpiarPantalla();

        mostrarLetra(patronesD);
        limpiarPantalla();
    }
}