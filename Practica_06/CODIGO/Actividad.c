#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
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

LCD mi_lcd = {&PORTC, 2, 3, 4, 5, 6, 7};   // PORT, RS, EN, D4, D5, D6, D7

volatile unsigned char pantalla = 0;
volatile unsigned char cambiar_pantalla = 1;
volatile unsigned char boton_bloqueado = 0;

// Variables para escribir HELLO WORLD sin bloquear
unsigned char indice_texto = 0;
unsigned int contador_animacion = 0;
char texto_hello[] = "ABCDEFGHIJKLMNOP";

// ====== CARACTERES ESPECIALES ======

// 0 = carrito parte trasera
unsigned char carro_izq[8] = {
    0b00000,
    0b00000,
    0b01111,
    0b11111,
    0b11111,
    0b01010,
    0b00000,
    0b00000
};

// 1 = carrito parte delantera
unsigned char carro_der[8] = {
    0b00000,
    0b00000,
    0b11110,
    0b11111,
    0b11111,
    0b01010,
    0b00000,
    0b00000
};

// 2 = corazon
unsigned char corazon[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};

// 3 = estrella
unsigned char estrella[8] = {
    0b00100,
    0b10101,
    0b01110,
    0b11111,
    0b01110,
    0b10101,
    0b00100,
    0b00000
};

void LCD_Crear_Caracter(unsigned char posicion, unsigned char caracter[])
{
    unsigned char i;

    posicion = posicion & 0x07;
    LCD_Cmd(0x40 + (posicion * 8));

    for(i = 0; i < 8; i++)
    {
        LCD_putc(caracter[i]);
    }

    LCD_Cmd(0x80);
}

void cargar_caracteres(void)
{
    LCD_Crear_Caracter(0, carro_izq);
    LCD_Crear_Caracter(1, carro_der);
    LCD_Crear_Caracter(2, corazon);
    LCD_Crear_Caracter(3, estrella);
}

void iniciar_pantalla_0(void)
{
    LCD_Clear();

    LCD_Set_Cursor(0, 0);
    LCD_putrs("HELLO WORLD!");

    LCD_Set_Cursor(1, 0);

    indice_texto = 0;
    contador_animacion = 0;
}

void actualizar_pantalla_0(void)
{
    if(indice_texto < 16)
    {
        contador_animacion++;

        if(contador_animacion >= 3000)
        {
            contador_animacion = 0;

            LCD_Set_Cursor(1, indice_texto);
            LCD_putc(texto_hello[indice_texto]);

            indice_texto++;
        }
    }
}

void mostrar_pantalla_1(void)
{
    LCD_Clear();

    LCD_Set_Cursor(0, 0);
    LCD_putrs("CARRITOS:");

    LCD_Set_Cursor(1, 0);

    LCD_putc(0);
    LCD_putc(1);
    LCD_putc(' ');

    LCD_putc(0);
    LCD_putc(1);
    LCD_putc(' ');

    LCD_putc(0);
    LCD_putc(1);
    LCD_putc(' ');

    LCD_putc(0);
    LCD_putc(1);
}

void mostrar_pantalla_2(void)
{
    LCD_Clear();

    LCD_Set_Cursor(0, 0);
    LCD_putrs("SIMBOLOS:");

    LCD_Set_Cursor(1, 0);

    LCD_putc(2); // corazon
    LCD_putc(' ');
    LCD_putc(3); // estrella
    LCD_putc(' ');
    LCD_putc(2);
    LCD_putc(' ');
    LCD_putc(3);
    LCD_putc(' ');
    LCD_putc(2);
    LCD_putc(' ');
    LCD_putc(3);
    LCD_putc(' ');
    LCD_putc(2);
}

void main(void)
{
    ANSEL = 0;
    ANSELH = 0;

    TRISC = 0x00;             // LCD
    TRISBbits.TRISB0 = 1;     // Boton en RB0

    PORTC = 0x00;

    // Pull-up interno en RB0
    OPTION_REGbits.nRBPU = 0;
    WPUBbits.WPUB0 = 1;

    // Interrupcion externa RB0/INT
    INTCONbits.GIE = 0;
    INTCONbits.INTF = 0;
    OPTION_REGbits.INTEDG = 0;   // Flanco de bajada
    INTCONbits.INTE = 1;
    INTCONbits.GIE = 1;

    LCD_Init(mi_lcd);
    cargar_caracteres();

    while(1)
    {
        if(cambiar_pantalla == 1)
        {
            cambiar_pantalla = 0;

            if(pantalla == 0)
            {
                iniciar_pantalla_0();
            }
            else if(pantalla == 1)
            {
                mostrar_pantalla_1();
            }
            else
            {
                mostrar_pantalla_2();
            }
        }

        // Escribe HELLO WORLD sin bloquear el boton
        if(pantalla == 0)
        {
            actualizar_pantalla_0();
        }

        // Se desbloquea cuando sueltas el boton
        if((boton_bloqueado == 1) && (PORTBbits.RB0 == 1))
        {
            boton_bloqueado = 0;
            INTCONbits.INTF = 0;
            INTCONbits.INTE = 1;
        }
    }
}

void __interrupt() ISR(void)
{
    if(INTCONbits.INTF == 1)
    {
        if(boton_bloqueado == 0)
        {
            boton_bloqueado = 1;
            INTCONbits.INTE = 0;

            pantalla++;

            if(pantalla > 2)
            {
                pantalla = 0;
            }

            cambiar_pantalla = 1;
        }

        INTCONbits.INTF = 0;
    }
}