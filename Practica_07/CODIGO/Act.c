#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <stdbool.h>
#include "lcd.h"

//=============================================================================
// CONFIGURACIÓN DE BITS
//=============================================================================

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 4000000

// 0 = Voltaje
// 1 = Porcentaje
// 2 = ADC
volatile unsigned char modo = 0;
volatile unsigned char cambiar_pantalla = 1;
volatile unsigned char boton_bloqueado = 0;

void ADC_Init()
{
    ANSEL = 0x01;      // AN0 analogico
    ANSELH = 0x00;     // Los demas digitales, incluyendo RB0

    ADCON0 = 0x81;     // ADC encendido, canal AN0
    ADCON1 = 0x80;     // Justificado a la derecha
}

unsigned int ADC_Read()
{
    __delay_us(5);

    GO_nDONE = 1;

    while(GO_nDONE);

    return ((unsigned int)ADRESH << 8) + ADRESL;
}

void main(void)
{
    char buffer[16];

    unsigned int adc_result = 0;

    unsigned int volt = 0;
    unsigned int part_int = 0;
    unsigned int part_dec = 0;

    unsigned int porcentaje = 0;

    LCD lcd = {&PORTC, 2, 3, 4, 5, 6, 7};

    ADC_Init();

    // Boton en RB0/INT
    TRISBbits.TRISB0 = 1;

    // Pull-up interno de RB0
    OPTION_REGbits.nRBPU = 0;
    WPUBbits.WPUB0 = 1;

    // Interrupcion externa RB0/INT
    INTCONbits.GIE = 0;
    INTCONbits.INTF = 0;
    OPTION_REGbits.INTEDG = 0;   // Flanco de bajada, boton hacia GND
    INTCONbits.INTE = 1;
    INTCONbits.GIE = 1;

    LCD_Init(lcd);

    while(1)
    {
        adc_result = ADC_Read();

        LCD_Clear();
        LCD_Set_Cursor(0, 0);

        if(modo == 0)
        {
            LCD_putrs("Voltaje:");

            volt = ((unsigned long)adc_result * 50000) / 1023;

            part_int = volt / 10000;
            part_dec = volt % 10000;

            LCD_Set_Cursor(0, 9);
            sprintf(buffer, "%u.%04u", part_int, part_dec);
            LCD_puts(buffer);
        }
        else if(modo == 1)
        {
            LCD_putrs("Porcentaje:");

            porcentaje = ((unsigned long)adc_result * 100) / 1023;

            LCD_Set_Cursor(0, 12);
            sprintf(buffer, "%u%%", porcentaje);
            LCD_puts(buffer);
        }
        else if(modo == 2)
        {
            LCD_putrs("Valor ADC:");

            LCD_Set_Cursor(0, 11);
            sprintf(buffer, "%u", adc_result);
            LCD_puts(buffer);
        }

        // Se desbloquea el boton hasta que lo sueltes
        if((boton_bloqueado == 1) && (PORTBbits.RB0 == 1))
        {
            boton_bloqueado = 0;
            INTCONbits.INTF = 0;
            INTCONbits.INTE = 1;
        }

        __delay_ms(200);
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

            modo++;

            if(modo > 2)
            {
                modo = 0;
            }

            cambiar_pantalla = 1;
        }

        INTCONbits.INTF = 0;
    }
}

