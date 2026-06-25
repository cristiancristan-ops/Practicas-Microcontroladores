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

#define SERVO PORTDbits.RD0

#define PULSO_MIN 500
#define PULSO_MAX 2500
#define PASO 5

volatile unsigned int pulso = PULSO_MIN;
volatile unsigned char estado = 1;
volatile unsigned char direccion = 1;

void cargarTimer1(unsigned int tiempo)
{
    unsigned int carga = 65536 - tiempo;

    TMR1H = carga >> 8;
    TMR1L = carga & 0xFF;
}

void __interrupt() ISR(void)
{
    if(PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF = 0;

        if(estado == 1)
        {
            SERVO = 0;
            cargarTimer1(20000 - pulso);
            estado = 0;
        }
        else
        {
            if(direccion == 1)
            {
                if(pulso + PASO >= PULSO_MAX)
                {
                    pulso = PULSO_MAX;
                    direccion = 0;
                }
                else
                {
                    pulso += PASO;
                }
            }
            else
            {
                if(pulso <= PULSO_MIN + PASO)
                {
                    pulso = PULSO_MIN;
                    direccion = 1;
                }
                else
                {
                    pulso -= PASO;
                }
            }

            SERVO = 1;
            cargarTimer1(pulso);
            estado = 1;
        }
    }
}

void main(void)
{
    ANSEL = 0;
    ANSELH = 0;

    TRISDbits.TRISD0 = 0;
    SERVO = 1;

    T1CON = 0b00010000;

    cargarTimer1(pulso);

    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;

    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    T1CONbits.TMR1ON = 1;

    while(1)
    {
    }
}