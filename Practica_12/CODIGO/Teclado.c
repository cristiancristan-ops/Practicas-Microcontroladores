#include <xc.h>
#include <stdbool.h>
#include "lcd.h"

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

LCD lcd = {&PORTC, 2, 3, 4, 5, 6, 7};

unsigned char Leer_Teclado(void)
{
    // Fila 1
    PORTB = 0b11111110;

    if (!PORTBbits.RB4) return '1';
    if (!PORTBbits.RB5) return '2';
    if (!PORTBbits.RB6) return '3';
    if (!PORTBbits.RB7) return 'A';

    // Fila 2
    PORTB = 0b11111101;

    if (!PORTBbits.RB4) return '4';
    if (!PORTBbits.RB5) return '5';
    if (!PORTBbits.RB6) return '6';
    if (!PORTBbits.RB7) return 'B';

    // Fila 3
    PORTB = 0b11111011;

    if (!PORTBbits.RB4) return '7';
    if (!PORTBbits.RB5) return '8';
    if (!PORTBbits.RB6) return '9';
    if (!PORTBbits.RB7) return 'C';

    // Fila 4
    PORTB = 0b11110111;

    if (!PORTBbits.RB4) return '*';
    if (!PORTBbits.RB5) return '0';
    if (!PORTBbits.RB6) return '#';
    if (!PORTBbits.RB7) return 'D';

    PORTB = 0b11111111;

    return 0;
}

void main(void)
{
    unsigned char tecla;
    unsigned char posicion = 0;

    ANSEL = 0;
    ANSELH = 0;

    // LCD en PORTC
    TRISC = 0;
    PORTC = 0;

    // RB0-RB3 salidas y RB4-RB7 entradas
    TRISB = 0b11110000;
    PORTB = 0b11111111;

    // Resistencias pull-up internas en RB4-RB7
    WPUB = 0b11110000;
    OPTION_REGbits.nRBPU = 0;

    LCD_Init(lcd);
    LCD_Clear();
    LCD_Set_Cursor(1, 1);

    while (1)
    {
        tecla = Leer_Teclado();

        if (tecla != 0)
        {
            LCD_putc(tecla);
            posicion++;

            // Esperar hasta soltar la tecla
            while (Leer_Teclado() != 0);

            __delay_ms(20);

            // Después de 16 caracteres pasa a la segunda fila
            if (posicion == 16)
                LCD_Set_Cursor(2, 1);

            // Después de llenar la LCD, limpia y comienza otra vez
            if (posicion == 32)
            {
                __delay_ms(300);
                LCD_Clear();
                LCD_Set_Cursor(1, 1);
                posicion = 0;
            }
        }
    }
}