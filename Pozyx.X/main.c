#include "Config.h"
#include <stdbool.h>
#include <xc.h>
#include "Initialize.h"

#define FCY 60000000UL

#include <libpic30.h>


#define DelayVal 50
int main(void)
{
    //__delay_ms(50);
    Start_Initialization();
    //SYSTEM_Initialize();
    


   
    while(1)
    {
        LED1 = ON;
    __delay_ms(DelayVal);
    LED2 = ON;
    __delay_ms(DelayVal);
    LED3 = ON;
    __delay_ms(DelayVal);
    LED4 = ON;
    __delay_ms(DelayVal);
    LED5 = ON;
    __delay_ms(DelayVal);
    LED6 = ON;
    __delay_ms(DelayVal);
    LED7 = ON;
    __delay_ms(DelayVal);
    LED8 = ON;
    __delay_ms(DelayVal);

    LED1 = OFF;
    __delay_ms(DelayVal);
    LED2 = OFF;
    __delay_ms(DelayVal);
    LED3 = OFF;
    __delay_ms(DelayVal);
    LED4 = OFF;
    __delay_ms(DelayVal);
    LED5 = OFF;
    __delay_ms(DelayVal);
    LED6 = OFF;
    __delay_ms(DelayVal);
    LED7 = OFF;
    __delay_ms(DelayVal);
    LED8 = OFF;
    __delay_ms(DelayVal);
    }
}

