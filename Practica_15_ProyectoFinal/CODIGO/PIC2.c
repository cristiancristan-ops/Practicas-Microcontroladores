#include <xc.h>
#include <stdbool.h>
#include "lcd.h"

#pragma config FOSC = INTRC_NOCLKOUT
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

LCD lcd = {&PORTD, 2, 3, 4, 5, 6, 7};

/* Personaje */
const unsigned char monito[8] =
{
    0b00100,
    0b01110,
    0b00100,
    0b01110,
    0b10101,
    0b00100,
    0b01010,
    0b10001
};

/* Obstáculo */
const unsigned char obstaculo[8] =
{
    0b00100,
    0b10101,
    0b10101,
    0b11111,
    0b00100,
    0b00100,
    0b01110,
    0b11111
};

void UART_Init(void)
{
    TRISCbits.TRISC7 = 1;

    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;

    BAUDCTLbits.BRG16 = 0;
    SPBRG = 51;                // 9600 baudios a 8 MHz

    RCSTAbits.SPEN = 1;
    RCSTAbits.CREN = 1;
}

unsigned char UART_Recibir(void)
{
    if(RCSTAbits.OERR)
    {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }

    if(PIR1bits.RCIF)
        return RCREG;

    return 0;
}

void Crear_Caracter(
        unsigned char posicion,
        const unsigned char dibujo[])
{
    unsigned char i;

    LCD_Cmd(0x40 + posicion * 8);

    for(i = 0; i < 8; i++)
        LCD_putc(dibujo[i] & 0x1F);

    LCD_Cmd(0x80);
}

void Mostrar_Numero(unsigned int numero)
{
    unsigned int divisor = 1;

    while(numero / divisor >= 10)
        divisor *= 10;

    do
    {
        LCD_putc((numero / divisor) + '0');

        numero %= divisor;
        divisor /= 10;
    }
    while(divisor > 0);
}

void Pantalla_Inicio(void)
{
    LCD_Clear();

    LCD_Set_Cursor(1, 1);
    LCD_putrs("PRESIONA BOTON");

    LCD_Set_Cursor(2, 1);
    LCD_putrs("PARA INICIAR");
}

void Pantalla_GameOver(unsigned int puntos)
{
    LCD_Clear();

    LCD_Set_Cursor(1, 4);
    LCD_putrs("GAME OVER");

    LCD_Set_Cursor(2, 1);
    LCD_putrs("PUNTOS: ");
    Mostrar_Numero(puntos);
}

void Iniciar_Juego(void)
{
    LCD_Clear();

    LCD_Set_Cursor(2, 2);
    LCD_putc(1);

    LCD_Set_Cursor(2, 16);
    LCD_putc(2);
}

void Subir_Monito(void)
{
    LCD_Set_Cursor(2, 2);
    LCD_putc(' ');

    LCD_Set_Cursor(1, 2);
    LCD_putc(1);
}

void Bajar_Monito(void)
{
    LCD_Set_Cursor(1, 2);
    LCD_putc(' ');

    LCD_Set_Cursor(2, 2);
    LCD_putc(1);
}

void Mover_Obstaculo(
        unsigned char columnaAnterior,
        unsigned char columnaNueva)
{
    LCD_Set_Cursor(2, columnaAnterior);
    LCD_putc(' ');

    if(columnaAnterior == 2)
    {
        LCD_Set_Cursor(2, 2);
        LCD_putc(1);
    }

    LCD_Set_Cursor(2, columnaNueva);
    LCD_putc(2);
}

void Morir(void)
{
    PORTBbits.RB0 = 1;        // LED rojo
    PORTBbits.RB1 = 1;        // Buzzer

    __delay_ms(500);

    PORTBbits.RB1 = 0;
}

void main(void)
{
    unsigned char dato;
    unsigned char jugando = 0;
    unsigned char saltando = 0;

    unsigned char columnaObstaculo = 16;
    unsigned char columnaAnterior = 16;

    unsigned char contadorObstaculo = 0;
    unsigned char contadorSalto = 0;
    unsigned char velocidad = 15;

    unsigned int puntos = 0;

    /* Oscilador interno de 8 MHz */
    OSCCONbits.IRCF = 0b111;
    OSCCONbits.SCS = 1;

    /* Espera a que el oscilador sea estable */
    while(OSCCONbits.HTS == 0);

    ANSEL = 0;
    ANSELH = 0;

    /* LCD en PORTD */
    TRISD = 0x00;
    PORTD = 0x00;

    /* LED y buzzer */
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;

    PORTBbits.RB0 = 0;
    PORTBbits.RB1 = 0;

    UART_Init();

    LCD_Init(lcd);

    Crear_Caracter(1, monito);
    Crear_Caracter(2, obstaculo);

    Pantalla_Inicio();

    while(1)
    {
        dato = UART_Recibir();

        if(jugando == 0)
        {
            if(dato == 'B')
            {
                jugando = 1;
                saltando = 0;

                columnaObstaculo = 16;
                columnaAnterior = 16;

                contadorObstaculo = 0;
                contadorSalto = 0;

                velocidad = 15;
                puntos = 0;

                PORTBbits.RB0 = 0;
                PORTBbits.RB1 = 0;

                Crear_Caracter(1, monito);
                Crear_Caracter(2, obstaculo);

                Iniciar_Juego();
            }
        }
        else
        {
            if(dato == 'U' && saltando == 0)
            {
                saltando = 1;
                contadorSalto = 0;

                Subir_Monito();
            }

            if(saltando == 1)
            {
                contadorSalto++;

                if(contadorSalto >= 25)
                {
                    saltando = 0;
                    contadorSalto = 0;

                    Bajar_Monito();
                }
            }

            contadorObstaculo++;

            if(contadorObstaculo >= velocidad)
            {
                contadorObstaculo = 0;
                columnaAnterior = columnaObstaculo;

                if(columnaObstaculo > 1)
                    columnaObstaculo--;

                if(columnaObstaculo == 2 &&
                   saltando == 0)
                {
                    Morir();

                    jugando = 0;

                    Pantalla_GameOver(puntos);
                }
                else
                {
                    Mover_Obstaculo(
                        columnaAnterior,
                        columnaObstaculo
                    );

                    if(columnaObstaculo == 1)
                    {
                        LCD_Set_Cursor(2, 1);
                        LCD_putc(' ');

                        puntos++;

                        columnaObstaculo = 16;
                        columnaAnterior = 16;

                        LCD_Set_Cursor(2, 16);
                        LCD_putc(2);

                        if(puntos >= 15)
                            velocidad = 5;
                        else if(puntos >= 10)
                            velocidad = 7;
                        else if(puntos >= 5)
                            velocidad = 10;
                        else
                            velocidad = 15;
                    }
                }
            }
        }

        __delay_ms(20);
    }
}