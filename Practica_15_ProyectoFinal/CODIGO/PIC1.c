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

void UART_Init(void)
{
    TRISCbits.TRISC6 = 0;   // TX como salida
    TRISCbits.TRISC7 = 1;   // RX como entrada

    TXSTAbits.SYNC = 0;     // UART asíncrono
    TXSTAbits.BRGH = 1;     // Alta velocidad
    BAUDCTLbits.BRG16 = 0;

    SPBRG = 51;             // 9600 baudios con 8 MHz

    RCSTAbits.SPEN = 1;
    TXSTAbits.TXEN = 1;
}

void UART_Enviar(unsigned char dato)
{
    while(!PIR1bits.TXIF);
    TXREG = dato;
}

unsigned int ADC_Leer(void)
{
    __delay_us(20);

    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE);

    return ((unsigned int)ADRESH << 8) | ADRESL;
}

void main(void)
{
    unsigned int joystick;
    unsigned char movimiento = 'S';
    unsigned char anterior = 'X';

    ANSEL = 0b00000001;     // AN0 analógico
    ANSELH = 0;

    TRISAbits.TRISA0 = 1;
    TRISBbits.TRISB0 = 1;

    WPUBbits.WPUB0 = 1;
    OPTION_REGbits.nRBPU = 0;

    ADCON1 = 0b10000000;
    ADCON0 = 0b10000001;    // AN0, ADC encendido

    UART_Init();

    while(1)
    {
        joystick = ADC_Leer();

        if(joystick < 350)
            movimiento = 'U';     // Arriba
        else if(joystick > 700)
            movimiento = 'D';     // Abajo
        else
            movimiento = 'S';     // Centro

        // Solo transmite cuando cambia la posición
        if(movimiento != anterior)
        {
            UART_Enviar(movimiento);
            anterior = movimiento;
        }

        // Botón del joystick
        if(PORTBbits.RB0 == 0)
        {
            __delay_ms(30);

            if(PORTBbits.RB0 == 0)
            {
                UART_Enviar('B');

                while(PORTBbits.RB0 == 0);
                __delay_ms(30);
            }
        }

        __delay_ms(20);
    }
}