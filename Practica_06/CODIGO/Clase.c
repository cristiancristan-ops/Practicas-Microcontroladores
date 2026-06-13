#include <stdio.h>
#include <stdlib.h>
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

void main(void){
    LCD lcd = {&PORTC,2 ,3 ,4, 5, 6, 7}; //PORT, RS, EN, D4, D5, D6, D7
    
    LCD_Init(lcd);
    
    while(1){
        LCD_Clear();
        LCD_Set_Cursor(0,0);
        LCD_putrs("HELLO WORLD! ");
        
        LCD_Set_Cursor(1,0);
        for(char c = 'A'; c < 'Q'; c++){
            LCD_putc(c);
            __delay_ms(300);
        }
        __delay_ms(1000);
    }
}