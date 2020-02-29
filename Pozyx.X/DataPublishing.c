#include <stddef.h>
#include "DataPublishing.h"
//#include "CAN_Handler/CANFastTransfer.h"
#include "Initialize.h"
#include "Timers.h"

#define isINITbit   0
#define DATA_ELEMENTS_COUNT 7
timers_t dataPeriodTimer[DATA_ELEMENTS_COUNT];
int (*dataRetrievalFunc[DATA_ELEMENTS_COUNT])();

void initGlobalData(GlobalDeviceData_t _index, int (*getFuncPointer)(void), unsigned long _interval) {
    setTimerInterval(&dataPeriodTimer[_index], _interval);
    dataRetrievalFunc[_index] = getFuncPointer;

}

bool publishData() {
    int i;
    bool validData = false;
    // Loop through all the elements that we could potentially send
    for (i = 0; i < DATA_ELEMENTS_COUNT; i++) {
        // if an data element hasn't been initialized then the pointer to the data retrieval function will be NULL
        if (dataRetrievalFunc[i] != NULL) {

            // Make sure the interval that we want to send the data out on has ellapsed
            if (timerDone(&dataPeriodTimer[i])) {
                // Making sure we actually have data to send
                validData = true;
                //Send the data on the can bus
#ifdef _CAN_FAST_TRANSFER_H
                ToSendCAN(i + DATA_ELEMENTS_COUNT*MOTOR_CONTROLLER, (dataRetrievalFunc[i])());
#endif
            }
        }
    }
    if (validData) {
#ifdef _CAN_FAST_TRANSFER_H
        sendDataCAN(GLOBAL_ADDRESS);
#endif
        LED2 ^= 1;
    }
    return validData;
}
/* forces the publishing of an index of data regardless of the linked timer */
void publishDataIndex(int _index) {
#ifdef _CAN_FAST_TRANSFER_H
    //Send the data on the can bus
    ToSendCAN(_index + DATA_ELEMENTS_COUNT*MOTOR_CONTROLLER, (dataRetrievalFunc[_index])());
    sendDataCAN(GLOBAL_ADDRESS);
#endif
}