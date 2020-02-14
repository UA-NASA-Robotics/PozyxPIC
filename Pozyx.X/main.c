#include "Config.h"
#include <stdbool.h>
#include <xc.h>
#include "Initialize.h"
#include "Pozyx_definitions.h"
#include "PozyxPIC_I2C.h"



#define DelayVal 50

int main(void) {
    //__delay_ms(50);
    Start_Initialization();
    InitI2C();
    //Pozyx_begin();
    char rxDATA[3];
    ReceiveI2C(POZYX_I2C_ADDRESS, POZYX_WHO_AM_I, rxDATA, sizeof (rxDATA));
    while (1) {
        LED1^=1;
        __delay_ms(500);

    }
}

