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

const char hex[]={
0x3F, //0
0x06, //1
0x5B, //2
0x4F, //3
0x66, //4
0x6D, //5
0x7D, //6
0x07, //7
0x7F, //8
0x6F, //9
0x77, //A
0x7C, //b
0x39, //C
0x5E, //d
0x79, //E
0x71  //F
};

void main()
{
    ANSEL=0;
    ANSELH=0;
    TRISD=0;

    while(1)
        for(char i=0;i<16;i++)
        {
            PORTD=hex[i];
            __delay_ms(100);
        }
}