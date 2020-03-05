#include "Config.h"
#include <stdbool.h>
#include <xc.h>
#include "Initialize.h"
#include "Pozyx_definitions.h"
#include "Pozyx.h"
#include "PozyxWrapper.h"
#include "FastTransfer_CAN.h"
#include "uart1_config.h"

/*MCC_GENERATED_FILES - move into separate folder/include environment for cleanliness?*/
#include "mcc_generated_files/can1.h"
#include "mcc_generated_files/dma.h"
#include "mcc_generated_files/ecan1.h"

#define DelayVal 50

int main(void) {
    //__delay_ms(50);
    /* initialize the system peripherals this includes clocks and timers */
    Start_Initialization();
    /* Initialize the I2C system peripheral that will handle coms with pozyx*/
    InitI2C();
    /* Boot the Pozyx and initialize the system*/
    //PozyxBoot();
    /* Get the dead band for the gyro to eliminate drift*/

    /*Initialize FastTransfer_CAN processes*/
    initCANFT();

    /*Initialize uart1 processes*/
    uart1_init();

    /*MCC GENERATED FILE STARTUP*/

    //Initialize Can1
    CAN1_Initialize();

    //Initialize DMA
    DMA_Initialize();
    
    //Initialize Transmissions from Can1
    CAN1_TransmitEnable();
    CAN1_ReceiveEnable();

    //Calibrate Gyro for header
    //calibrateGyro();

//    initGlobalData(1, getPozyx_X, 300);
//    initGlobalData(2, getPozyx_Y, 300);
//    initGlobalData(3, getPozyx_H, 300);
    uCAN_MSG msg;
    msg.frame.id = 06;
    msg.frame.idType = CAN_FRAME_STD;
    msg.frame.msgtype = 0;
    msg.frame.dlc = 1;
    msg.frame.data0 = 0x55;
    while (1) {
        //CAN1_transmit(CAN_PRIORITY_HIGH, &msg);
        //uart1_put(0x69);
        U1TXREG = 0x69;
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