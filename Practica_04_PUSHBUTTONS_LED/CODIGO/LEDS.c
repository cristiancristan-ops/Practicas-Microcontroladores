#include <xc.h>

#pragma config FOSC = XT
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

unsigned char Estado1, Estado2, Estado3;

void main(void){
    ANSEL = 0;
    ANSELH = 0;
    
    OPTION_REG = OPTION_REG & 0b01111111;
    
    TRISB = 0xFF;
    TRISD = 0;
    
    while(1){
        PORTDbits.RD0 = !PORTBbits.RB0;
        PORTDbits.RD1 = !PORTBbits.RB1;
        PORTDbits.RD2 = !PORTBbits.RB2;
    }
}
