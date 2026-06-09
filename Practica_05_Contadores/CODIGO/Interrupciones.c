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
#define LED PORTCbits.RC0
// Tabla para display 7 segmentos cátodo común
// Orden de bits: 0b0gfedcba
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

void blink_led(){
    for(int i = 0; i < 4; i++){
        LED = 1;
        __delay_ms(500);
        LED = 0;
        __delay_ms(500);
    }
}

void main(void){
    ANSEL = 0;
    ANSELH = 0;
    OPTION_REG = OPTION_REG & 0b01111111;
    
    TRISC = 0;
    TRISD = 0;
    TRISB = 0xFF;
    
    PORTD = 0;
    PORTC = 0;
    
    unsigned char count = 0;
    
    GIE = 1;
    INTE = 1;
    INTEDG = 0;
    while(1){
        PORTD = patron[count];
        count = (count+1)%10;
        __delay_ms(500);
    }
}

void __interrupt() ISR(void){
    if(INTF){
        GIE = 0; //Desactivar todas las interrupciones
        blink_led(); //Ejectur todas las funciones de la interrupcion
        GIE = 1;
        INTF = 0;
    }
}