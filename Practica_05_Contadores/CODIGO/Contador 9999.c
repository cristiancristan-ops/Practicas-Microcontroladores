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

// Tabla para display 7 segmentos cátodo común
// Orden de bits: 0b0gfedcba
unsigned char patron[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

void main(void) {

    int num = 0;
    int mil = 0;
    int cen = 0;
    int dec = 0;
    int uni = 0;
    int i = 0;

    ANSEL = 0;
    ANSELH = 0;

    TRISD = 0;
    TRISC = 0;

    PORTD = 0;
    PORTC = 0b11111111;

    while(1) {

        mil = num / 1000;
        cen = (num / 100) % 10;
        dec = (num / 10) % 10;
        uni = num % 10;

        // Inicia multiplexación
        // Mientras más bajo sea este número, más rápido cuenta
        for(i = 0; i < 2; i++) {

            // Mostrar millares
            PORTC = 0b11110111;
            PORTD = patron[mil];
            __delay_ms(1);

            // Mostrar centenas
            PORTC = 0b11111011;
            PORTD = patron[cen];
            __delay_ms(1);

            // Mostrar decenas
            PORTC = 0b11111101;
            PORTD = patron[dec];
            __delay_ms(1);

            // Mostrar unidades
            PORTC = 0b11111110;
            PORTD = patron[uni];
            __delay_ms(1);
        }

        num++;

        if(num > 9999) {
            num = 0;
        }
    }
}
