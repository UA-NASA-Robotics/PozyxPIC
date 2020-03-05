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
/*MCC_GENERATED_FILES - move into separate folder/include environment for cleanliness?*/
#include "mcc_generated_files/can1.h"
#include "mcc_generated_files/dma.h"
#include "mcc_generated_files/ecan1.h"

#define DelayVal 50
FT_t FT_handle;
FTC_t ftc_handle;

int main(void) {
    //__delay_ms(50);
    /* initialize the system peripherals this includes clocks and timers */
    Start_Initialization();
    /* Initialize the I2C system peripheral that will handle coms with pozyx*/
    InitI2C();
    /* Boot the Pozyx and initialize the system*/
    //PozyxBoot();
/*Initialize FastTransfer for uart processes*/
    FT_Init(&FT_handle, ROUTER_CARD, uart1_put_c, uart1_get, uart1_rx_empty);
    /*Initialize FastTransfer_CAN processes*/
    FTC_Init(&ftc_handle, ROUTER_CARD, 1, CAN1_Initialize, CAN1_transmit, CAN1_receive);
    
    
    /* Get the dead band for the gyro to eliminate drift*/

    //Calibrate Gyro for header
    //calibrateGyro();

    //    initGlobalData(1, getPozyx_X, 300);
    //    initGlobalData(2, getPozyx_Y, 300);
    //    initGlobalData(3, getPozyx_H, 300);

    while (1) {
        FT_ToSend(&FT_handle, 0, 11);
        FT_ToSend(&FT_handle, 1, 0xffff);
        FT_Send(&FT_handle, 6);
        //ToSendCAN(4, 0x55AA);
        //sendDataCAN(6);
        FTC_ToSend(&ftc_handle, 4, 0x55AA);
        FTC_Send(&ftc_handle, 6);
        //LATBbits.LATB10 ^= 1;
        //CommunicationsHandle();
        //        /* Get the range data from the Pozyx and calculate the location */
        //        updateStatus();
        //        /* Calculate the location of the robot with the center as the base point */
        //        calculateCenter();
        //        /* Getting the heading of the robot based on the pozyx devices */
        //        updateHeading();
        //        /* use the Gyro to adjust the heading found in 'updateHeading()' */
        //        adjustHeading();
        //        /* Publish the data on the Global Can Bus */
        //        publishData();

        LED1 ^= 1;
        __delay_ms(500);

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
 /   _____/__.__. _______/  |_  ____   _____   ______                                         
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
  _________       __  .__      _________                                    __                
 /   _____/ _____/  |_|  |__   \_   ___ \_____ _____________   ____   _____/  |_  ___________ 
 \_____  \_/ __ \   __\  |  \  /    \  \/\__  \\_  __ \____ \_/ __ \ /    \   __\/ __ \_  __ \
 /        \  ___/|  | |   Y  \ \     \____/ __ \|  | \/  |_> >  ___/|   |  \  | \  ___/|  | \/
/_______  /\___  >__| |___|  /  \______  (____  /__|  |   __/ \___  >___|  /__|  \___  >__|   
        \/     \/          \/          \/     \/      |__|        \/     \/          \/       
 */