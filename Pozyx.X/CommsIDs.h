/* 
 * File:   commsReceive.h
 * Author: John, Alex
 *
 * Created on February 14, 2020, 5:31 PM
 */

#ifndef COMMSIDS_H
#define	COMMSIDS_H

#include <stdbool.h>
#include <stdint.h>
#include "mcc_generated_files/can_types.h"
#include "FastTransfer/ring_buffer.h"
#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum {
        CONTROL_BOX = 1,
        POZYX,
        JUICE_BOARD,
        ROUTER_CARD,
        MASTER_CONTROLLER,
        MOTOR_CONTROLLER,
        GYRO_CONTROLLER,
        STRAIN_SENSOR,
        OPTICAL_FLOW,
        RASP_PI,
        LED_CARD,
        LIDAR,
        GLOBAL_ADDRESS = 31
    } Addresses_t;
#ifndef GBL_DEV_IDX
#define GBL_DEV_IDX

    typedef enum {
        DEVICE_STATUS = 0,
        DEVICE_MACRO,
        DATA_0,
        DATA_1,
        DATA_2,
        DATA_3,
        DATA_4
    } GlobalDeviceData_t;

#define GLOBAL_DEVICES 11
#define GLOBAL_DATA_INDEX_PER_DEVICE 7
#define getGBL_START_INDEX(c) c*GLOBAL_DATA_INDEX_PER_DEVICE
#define getGBL_DEVICE_STATUS(c) c*GLOBAL_DATA_INDEX_PER_DEVICE + DEVICE_STATUS
#define getGBL_MACRO_INDEX(c) c*GLOBAL_DATA_INDEX_PER_DEVICE + DEVICE_MACRO
#define getGBL_INDEX(c,d)  c*GLOBAL_DATA_INDEX_PER_DEVICE + d

#endif
    // fast transfer handle and all necessary local variables

    typedef struct FTC_t {
        // address of device
        uint8_t address;
        // can module number (1 or 2)
        int8_t can_id;
        bool(*transmit)(CAN_TX_PRIOIRTY _p, uCAN_MSG* _msg);
        bool(*receive)(uCAN_MSG* _msg);
        ring_buffer_t transmit_buffer_CAN, send_buffer_CAN_FT, rx_buffer_CAN;
        ring_buffer_t rx_buffer_CAN_Global;
        int receiveMode;
        bool dataReceived[2];
        int newDataFlag;
        int * receiveArrayAddressCAN[2];
        bool * receiveArrayAddressCAN_Flag[2];
        uint8_t moduleAddressCAN[2];
        unsigned int MaxIndex[2];
        int receiveArrayCAN[10];
        bool CAN_FT_recievedFlag[10];
        int newDataFlag_Global[2];
        int receiveArrayCAN_Global[GLOBAL_DEVICES*GLOBAL_DATA_INDEX_PER_DEVICE + 1];
        bool GBL_CAN_FT_recievedFlag[GLOBAL_DEVICES*GLOBAL_DATA_INDEX_PER_DEVICE + 1];

    } FTC_t;

#ifdef	__cplusplus
}
#endif

#endif	/* COMMSIDS_H */