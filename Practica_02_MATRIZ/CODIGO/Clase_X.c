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
#define _XTAL_FREQ 8000000      // Frecuencia del oscilador para __delay_ms()

unsigned char patrones[8] = {
    0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81
};

void main(void)
{
    ANSEL = 0;
    ANSELH = 0;

    TRISB = 0;
    TRISD = 0;

    PORTB = 0;
    PORTD = 0;

    while(1)
    {
        for(unsigned char i = 0; i < 8; i++)
        {
            if(i == 0)
                PORTB = 0b10000000;
            else
                PORTB = 1 << (i-1);

            PORTD = patrones[i];
            __delay_ms(1);
        }
    }
}