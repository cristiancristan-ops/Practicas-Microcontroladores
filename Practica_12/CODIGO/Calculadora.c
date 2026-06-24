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

unsigned char teclado(void)
{
    PORTB = 0b11111110;
    __delay_us(20);
    if(!PORTBbits.RB4) return '7';
    if(!PORTBbits.RB5) return '8';
    if(!PORTBbits.RB6) return '9';
    if(!PORTBbits.RB7) return '/';

    PORTB = 0b11111101;
    __delay_us(20);
    if(!PORTBbits.RB4) return '4';
    if(!PORTBbits.RB5) return '5';
    if(!PORTBbits.RB6) return '6';
    if(!PORTBbits.RB7) return '*';

    PORTB = 0b11111011;
    __delay_us(20);
    if(!PORTBbits.RB4) return '1';
    if(!PORTBbits.RB5) return '2';
    if(!PORTBbits.RB6) return '3';
    if(!PORTBbits.RB7) return '-';

    PORTB = 0b11110111;
    __delay_us(20);
    if(!PORTBbits.RB4) return 'C';
    if(!PORTBbits.RB5) return '0';
    if(!PORTBbits.RB6) return '=';
    if(!PORTBbits.RB7) return '+';

    PORTB = 0b11111111;
    return 0;
}

void mostrarNumero(int numero)
{
    if(numero < 0)
    {
        LCD_putc('-');
        numero = -numero;
    }

    if(numero >= 10)
        LCD_putc((numero / 10) + '0');

    LCD_putc((numero % 10) + '0');
}

void main(void)
{
    unsigned char tecla;
    unsigned char estado = 0;
    unsigned char operacion = 0;

    int numero1 = 0;
    int numero2 = 0;
    int resultado = 0;

    ANSEL = 0;
    ANSELH = 0;

    TRISC = 0;
    PORTC = 0;

    TRISB = 0b11110000;
    PORTB = 0b11111111;

    WPUB = 0b11110000;
    OPTION_REGbits.nRBPU = 0;

    LCD_Init(lcd);
    LCD_Clear();

    while(1)
    {
        tecla = teclado();

        if(tecla != 0)
        {
            __delay_ms(30);

            if(tecla >= '0' && tecla <= '9')
            {
                if(estado == 0)
                    numero1 = tecla - '0';

                else if(estado == 1)
                    numero2 = tecla - '0';

                LCD_Clear();
                LCD_Set_Cursor(1, 1);
                LCD_putc(tecla);
            }

            else if((tecla == '+' || tecla == '-' ||
                     tecla == '*' || tecla == '/') && estado == 0)
            {
                operacion = tecla;
                estado = 1;

                LCD_Clear();
                LCD_Set_Cursor(1, 1);
                LCD_putc(tecla);

                __delay_ms(500);
                LCD_Clear();
            }

            else if(tecla == '=' && estado == 1)
            {
                LCD_Clear();
                LCD_Set_Cursor(1, 1);

                if(operacion == '+')
                    resultado = numero1 + numero2;

                else if(operacion == '-')
                    resultado = numero1 - numero2;

                else if(operacion == '*')
                    resultado = numero1 * numero2;

                else if(operacion == '/')
                {
                    if(numero2 == 0)
                    {
                        LCD_putrs("ERROR");
                        estado = 2;

                        while(teclado() != 0);
                        __delay_ms(30);
                        continue;
                    }

                    resultado = numero1 / numero2;
                }

                mostrarNumero(resultado);
                estado = 2;
            }

            else if(tecla == 'C')
            {
                numero1 = 0;
                numero2 = 0;
                resultado = 0;
                operacion = 0;
                estado = 0;
                LCD_Clear();
            }

            while(teclado() != 0);
            __delay_ms(30);
        }
    }
}