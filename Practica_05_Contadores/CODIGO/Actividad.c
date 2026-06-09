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
// Orden: 0b0gfedcba
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

// Variable que cambia con el botón
// 0 = cuenta hacia arriba
// 1 = cuenta hacia abajo
volatile unsigned char direccion = 0;

void mostrar_numero(unsigned int num)
{
    unsigned char mil;
    unsigned char cen;
    unsigned char dec;
    unsigned char uni;

    mil = num / 1000;
    cen = (num / 100) % 10;
    dec = (num / 10) % 10;
    uni = num % 10;

    // Millares - RC3
    PORTC = 0b11111111;
    PORTD = patron[mil];
    PORTC = 0b11110111;
    __delay_ms(1);

    // Centenas - RC2
    PORTC = 0b11111111;
    PORTD = patron[cen];
    PORTC = 0b11111011;
    __delay_ms(1);

    // Decenas - RC1
    PORTC = 0b11111111;
    PORTD = patron[dec];
    PORTC = 0b11111101;
    __delay_ms(1);

    // Unidades - RC0
    PORTC = 0b11111111;
    PORTD = patron[uni];
    PORTC = 0b11111110;
    __delay_ms(1);
}

void main(void)
{
    unsigned int num = 0;
    unsigned char i = 0;

    ANSEL = 0;
    ANSELH = 0;

    TRISD = 0x00;   // Segmentos
    TRISC = 0x00;   // Control de displays
    TRISB = 0xFF;   // Botón en RB0

    PORTD = 0;
    PORTC = 0b11111111;

    // Activar pull-ups internos del PORTB
    OPTION_REG = OPTION_REG & 0b01111111;
    WPUB = 0b00000001; // Pull-up en RB0

    // Interrupción externa en RB0/INT
    GIE = 1;
    INTE = 1;
    INTF = 0;
    INTEDG = 0; // Interrupción cuando presionas botón hacia GND

    while(1)
    {
        // Este for controla la velocidad
        // Más alto = más lento
        // Más bajo = más rápido
        for(i = 0; i < 10; i++)
        {
            mostrar_numero(num);
        }

        if(direccion == 0)
        {
            num++;

            if(num > 9999)
            {
                num = 0;
            }
        }
        else
        {
            if(num == 0)
            {
                num = 9999;
            }
            else
            {
                num--;
            }
        }
    }
}

void __interrupt() ISR(void)
{
    if(INTF)
    {
        __delay_ms(50); // Antirrebote simple

        if(RB0 == 0)
        {
            direccion = !direccion;
        }

        INTF = 0;
    }
}