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

volatile unsigned int tiempo = 0, contador = 0;
volatile char actualizar = 1;
char txt[8];
unsigned int adc, volt;

void Timer0_Init(){
    OPTION_REG = 0x07;
    TMR0 = 178;
    T0IE = 1;
    GIE = 1;
}

void ADC_Init(){
    ANSEL = 0x01;
    ANSELH = 0;
    TRISA = 0x01;
    ADCON0 = 0b01000001;
    ADCON1 = 0b10000000;
}

unsigned int ADC_Read(){
    GO_nDONE = 1;
    while(GO_nDONE);
    return ((unsigned int)ADRESH << 8) + ADRESL;
}

void __interrupt() ISR(void){
    if(T0IF){
        contador++;
        if(contador >= 100){
            tiempo++;
            contador = 0;
            actualizar = 1;
        }
        TMR0 = 178;
        T0IF = 0;
    }
}

void main(void){
    LCD lcd = {&PORTC,2,3,4,5,6,7};

    TRISC = 0;
    ADC_Init();
    Timer0_Init();
    LCD_Init(lcd);
    LCD_Clear();

    while(1){
        adc = ADC_Read();
        volt = adc * 500UL / 1023;

        LCD_Set_Cursor(0,0);
        sprintf(txt,"V:%u.%02u",volt/100,volt%100);
        LCD_putrs(txt);

        if(actualizar){
            actualizar = 0;
            LCD_Set_Cursor(1,11);
            sprintf(txt,"%02u:%02u",tiempo/60,tiempo%60);
            LCD_putrs(txt);
        }
    }
}