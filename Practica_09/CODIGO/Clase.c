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
volatile unsigned int tiempo = 0;
volatile unsigned int contador = 0;
char exec[6];

void Timer0_Init(){
    OPTION_REG = 0x07;
    TMR0 = 178;
    T0IE = 1;
    GIE = 1;
}

void __interrupt() ISR(void){
    if(T0IF){
        contador++;
        if (contador>100){
            tiempo++;
            contador = 0;
        }
        TMR0 = 178;
        T0IF = 0;
    }
}

void main(void){
    Timer0_Init();
    LCD lcd = {&PORTC,2 ,3 ,4 ,5 ,6 ,7};
    LCD_Init(lcd);
    
    LCD_Clear();
    LCD_Set_Cursor(0,0);
    LCD_putrs("Tiempo: ");
    LCD_Set_Cursor(1,0);
    LCD_putrs("00:00");
    
    while(1){
        LCD_Set_Cursor(1,0);
        sprintf(exec,"%02u:%02u",tiempo/60,tiempo%60);
        LCD_putrs(exec);
    }
}