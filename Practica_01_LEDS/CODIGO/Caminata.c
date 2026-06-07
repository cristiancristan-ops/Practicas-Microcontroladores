#include <xc.h>         // Biblioteca principal del compilador XC8

//=============================================================================
// CONFIGURACI N DE BITS DE CONFIGURACI N (FUSES)
//=============================================================================

// Selecci n de oscilador (usar XT si est s usando un cristal de 4 MHz)
#pragma config FOSC = HS        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (disabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection (disabled)
#pragma config WRT = OFF        // Flash Program Memory Write Enable (disabled)
#pragma config CP = OFF         // Flash Program Memory Code Protection (disabled)

//=============================================================================
// DEFINICIONES
//=============================================================================

#define _XTAL_FREQ 8000000      // Frecuencia del oscilador (para __delay_ms y __delay_us)

void main(void)
{
    ANSEL = 0;
    ANSELH = 0;

    TRISD = 0b00000000;
    PORTD = 0b00000000;

    unsigned char led = 0b00000001;

    while(1)
    {
        for(char i = 0; i < 5; i++)
        {
            PORTD = led;
            __delay_ms(300);
            led = led << 1;
        }

        PORTD = led;
        __delay_ms(300);

        for(char i = 0; i < 5; i++)
        {
            led = led >> 1;
            PORTD = led;
            __delay_ms(300);
        }

        led = 0b00000001;
    }
}