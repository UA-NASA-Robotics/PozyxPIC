


#include "Config.h"
#include <stdbool.h>
#include <xc.h>
#include "Initialize.h"
#include "Pozyx_definitions.h"
#include "Pozyx.h"
#include "PozyxWrapper.h"
#include "FastTransfer_CAN.h"
#include "uart1_config.h"
#include "FastTransfer/ft.h"
#include "DataPublishing.h"
/*MCC_GENERATED_FILES - move into separate folder/include environment for cleanliness?*/
#include "mcc_generated_files/can1.h"
#include "mcc_generated_files/dma.h"
#include "mcc_generated_files/ecan1.h"

#define DelayVal 50
enum{
    GetRanges=0,
    CalculateHeading,
    CalculateCenter,
}PozyxUpdateStates_t;
int main(void) {
    //__delay_ms(50);
    /* initialize the system peripherals this includes clocks and timers */
    Start_Initialization();
    __delay_ms(1000);
    LED1 = 1;
    /* Initialize the I2C system peripheral that will handle coms with pozyx*/
    InitI2C();
    LED2 = 1;

    /* Boot the Pozyx and initialize the system*/
    PozyxBoot();
    LED3 = 1;

    /*Initialize FastTransfer for uart processes*/
    FT_Init(getFThandle(), ROUTER_CARD, uart1_put_c, uart1_get, uart1_rx_empty);
    LED4 = 1;

    /*Initialize FastTransfer_CAN processes*/
    //FTC_Init(&ftc_handle, ROUTER_CARD, 1, CAN1_Initialize, CAN1_transmit, CAN1_receive);
    canFTbegin();
    LED5 = 1;

    /* Get the dead band for the gyro to eliminate drift*/

    //Calibrate Gyro for header
    calibrateGyro();
    LED6 = 1;

    initGlobalData(1, getPozyx_X, 300);
    initGlobalData(2, getPozyx_Y, 300);
    initGlobalData(3, getPozyx_H, 300);
    LEDPattern();
    while (1) {
        /* Get the range data from the Pozyx and calculate the location */
        updateStatus();
        /* Getting the heading of the robot based on the pozyx devices */
        updateHeading();
        /* use the Gyro to adjust the heading found in 'updateHeading()' */
        adjustHeading();
        /* Calculate the location of the robot with the center as the base point */
        calculateCenter();
        
        /* Putting the Pozyx Data on the can bus */
        printCH();
        /* Publish the data on the Global Can Bus */
        publishData();

        LED1 ^= 1;
        //__delay_ms(500);

    }
}

/*
.____       _____      _____ ________________________________                                 
|    |     /  _  \    /     \\______   \_   _____/\_   _____/                                 
|    |    /  /_\  \  /  \ /  \|     ___/|    __)_  |    __)_                                  
|    |___/    |    \/    Y    \    |    |        \ |        \                                 
|_______ \____|__  /\____|__  /____|   /_______  //_______  /                                 
        \/       \/         \/                 \/         \/                                  
  _________               __                                                                  
 /   _____/__ __  _______/  |_  ____   _____   ______                                         
 \_____  <   |  |/  ___/\   __\/ __ \ /     \ /  ___/                                         
 /        \___  |\___ \  |  | \  ___/|  Y Y  \\___ \                                          
/_______  / ____/____  > |__|  \___  >__|_|  /____  >                                         
        \/\/         \/            \/      \/     \/                                          
__________                                                                                    
\______   \___.__.                                                                            
 |    |  _<   |  |                                                                            
 |    |   \\___  |                                                                            
 |______  // ____|                                                                            
        \/ \/                                                                                 
  _________       __   __      _________                                    __                
 /   _____/ _____/  |_|  |__   \_   ___ \_____ _____________   ____   _____/  |_  ___________ 
 \_____  \_/ __ \   __\  |  \  /    \  \/\__  \\_  __ \____ \_/ __ \ /    \   __\/ __ \_  __ \
 /        \  ___/|  | |   Y  \ \     \____/ __ \|  | \/  |_> >  ___/|   |  \  | \  ___/|  | \/
/_______  /\___  >__| |___|  /  \______  (____  /__|  |   __/ \___  >___|  /__|  \___  >__|   
        \/     \/          \/          \/     \/      |__|        \/     \/          \/       
 */