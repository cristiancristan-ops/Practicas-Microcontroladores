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

#define BTN_SUMAR  PORTBbits.RB0
#define BTN_RESTAR PORTBbits.RB1
#define BTN_RESET  PORTBbits.RB2

unsigned char contador = 0;

// Tabla para display 7 segmentos cátodo común
// Orden de bits: 0b0gfedcba
unsigned char numeros[10] = {
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

void actualizarDisplays(void) {
    unsigned char unidades;
    unsigned char decenas;

    unidades = contador % 10;
    decenas = contador / 10;

    PORTC = numeros[unidades]; // Display de unidades
    PORTD = numeros[decenas];  // Display de decenas
}

void main(void) {
    ANSEL = 0;
    ANSELH = 0;

    // Pull-ups internos activados en PORTB
    OPTION_REGbits.nRBPU = 0;
    WPUB = 0b00000111; // Pull-up en RB0, RB1 y RB2

    TRISB = 0b00000111; // RB0, RB1 y RB2 como entradas
    TRISC = 0x00;       // PORTC como salida, unidades
    TRISD = 0x00;       // PORTD como salida, decenas

    PORTC = 0x00;
    PORTD = 0x00;

    actualizarDisplays();

    while(1) {

        // Botón sumar
        if(BTN_SUMAR == 0) {
            __delay_ms(50);

            if(BTN_SUMAR == 0) {
                if(contador >= 99) {
                    contador = 0;
                } else {
                    contador++;
                }

                actualizarDisplays();

                while(BTN_SUMAR == 0);
                __delay_ms(50);
            }
        }

        // Botón restar
        if(BTN_RESTAR == 0) {
            __delay_ms(50);

            if(BTN_RESTAR == 0) {
                if(contador == 0) {
                    contador = 99;
                } else {
                    contador--;
                }

                actualizarDisplays();

                while(BTN_RESTAR == 0);
                __delay_ms(50);
            }
        }

        // Botón reset
        if(BTN_RESET == 0) {
            __delay_ms(50);

            if(BTN_RESET == 0) {
                contador = 0;

                actualizarDisplays();

                while(BTN_RESET == 0);
                __delay_ms(50);
            }
        }
    }
}
