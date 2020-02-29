#include <xc.h>
#include <stdbool.h>

//#include "Initialize.h"


#define FOSC    (60000000ULL)
#define FCY     (FOSC/2)
#include <libpic30.h>

#include "PozyxPIC_I2C.h"

typedef enum {
    WriteWrite = 0,
    WriteRead,
    Normal
} TransMissionMode_t;
// general struct for storing settings

struct operator_values {
    unsigned char slave_address;
    unsigned char data_address;
    unsigned char * Rxdata;
    unsigned char * Txdata;
    unsigned char Rxcount;
    unsigned char Txcount;
    unsigned char Rxdata_index;
    unsigned char Txdata_index;
    unsigned char direction;
    unsigned char status;
    TransMissionMode_t transMode;
};

// initialize the setting struct
static struct operator_values I2C_1_values = {0, 0, 0, 0, 0, 0, 1, Normal};

// function pointer for transition functions
void (*FunctionI2C)(void);

void InitI2C(void) {

    // Continues module operation in Idle mode
    I2C2CONbits.I2CSIDL = 0;
    I2C2BRG = 500.8; //591*4; // set baud rate (edited back FROM 591*4)

    IPC12bits.MI2C2IP = 2; // priority level 2
    IFS3bits.MI2C2IF = 0; // clear flag
    IEC3bits.MI2C2IE = 1; // enable interrupt flag
    // Enable the I2C2 module and configures the SDA2 and SCL2 pins as serial ports pins
    I2C2CONbits.I2CEN = 1;
    I2C_1_values.status = SUCCESS;
}




// initiates a send of an array containing a set number of data

bool SendI2CRepeatStart(unsigned char s_address, unsigned char d_address, unsigned char * dat, unsigned char how_much) {
    //LED3 ^= 1;
    // see if a transmit or receive is in prograss
    if ((I2C_1_values.status == SUCCESS) || (I2C_1_values.status == FAILED)) {
        //populate struct with needed data
        I2C_1_values.slave_address = s_address << 1;
        I2C_1_values.data_address = d_address;
        I2C_1_values.Txdata = dat;
        I2C_1_values.Txcount = how_much;
        I2C_1_values.Txdata_index = 0;
        I2C_1_values.direction = RECEIVE;
        I2C_1_values.status = PENDING;
        I2C_1_values.transMode = WriteWrite;
        FunctionI2C = &SendSlaveAddressI2C; // load the send slave address function
        I2C2CONbits.SEN = 1; // send start condition
        while (!(I2C_1_values.status == SUCCESS || I2C_1_values.status == FAILED));
        if (I2C_1_values.status == SUCCESS)
            return true; // return successful
        else
            return false;
    } else {
        return false; // return failed if an i2c request is already running
    }
}

bool SendReadI2C(unsigned char s_address, unsigned char d_address, unsigned char * dat, unsigned char how_much, unsigned char * rxdat, unsigned char rxhow_much) {
    //LED3 ^= 1;
    // see if a transmit or receive is in prograss
    if ((I2C_1_values.status == SUCCESS) || (I2C_1_values.status == FAILED)) {
        //populate struct with needed data
        I2C_1_values.slave_address = s_address << 1;
        I2C_1_values.data_address = d_address;
        I2C_1_values.Txdata = dat;
        I2C_1_values.Txcount = how_much;
        I2C_1_values.Txdata_index = 0;
        I2C_1_values.Rxdata = rxdat;
        I2C_1_values.Rxcount = rxhow_much;
        I2C_1_values.Rxdata_index = 0;
        I2C_1_values.direction = TRANSMIT;
        I2C_1_values.status = PENDING;
        I2C_1_values.transMode = WriteRead;
        if (how_much == 0) {
            I2C_1_values.direction = RECEIVE;
            I2C_1_values.transMode = Normal;
        }
        FunctionI2C = &SendSlaveAddressI2C; // load the send slave address function
        I2C2CONbits.SEN = 1; // send start condition
        while (!(I2C_1_values.status == SUCCESS || I2C_1_values.status == FAILED));
        if (I2C_1_values.status == SUCCESS)
            return true; // return successful
        else
            return false;
    } else {
        return false; // return failed if an i2c request is already running
    }
}

bool SendI2C(unsigned char s_address, unsigned char d_address, unsigned char * dat, unsigned char how_much) {
    //LED3 ^= 1;
    // see if a transmit or receive is in prograss
    if ((I2C_1_values.status == SUCCESS) || (I2C_1_values.status == FAILED)) {
        //populate struct with needed data
        I2C_1_values.slave_address = s_address << 1;
        I2C_1_values.data_address = d_address;
        I2C_1_values.Txdata = dat;
        I2C_1_values.Txcount = how_much;
        I2C_1_values.Txdata_index = 0;
        I2C_1_values.direction = TRANSMIT;
        I2C_1_values.status = PENDING;
        I2C_1_values.transMode = Normal;
        FunctionI2C = &SendSlaveAddressI2C; // load the send slave address function
        I2C2CONbits.SEN = 1; // send start condition
        while (!(I2C_1_values.status == SUCCESS || I2C_1_values.status == FAILED));
        if (I2C_1_values.status == SUCCESS)
            return true; // return successful
        else
            return false;
    } else {
        return false; // return failed if an i2c request is already running
    }
}
// initiate a receive moving data to an array of a set number of data

bool ReceiveI2C(unsigned char s_address, unsigned char d_address, unsigned char * dat, unsigned char how_much) {

    //see if a transmit or receive is in prograss
    if ((I2C_1_values.status == SUCCESS) || (I2C_1_values.status == FAILED)) {
        //LATEbits.LATE5 ^= 1;
        // __delay_ms(100);
        //populate struct with needed data
        I2C_1_values.slave_address = s_address << 1;
        I2C_1_values.data_address = d_address;
        I2C_1_values.Rxdata = dat;
        I2C_1_values.Rxcount = how_much;
        I2C_1_values.Rxdata_index = 0;
        I2C_1_values.direction = RECEIVE;
        I2C_1_values.status = PENDING;
        I2C_1_values.transMode = Normal;
        FunctionI2C = &SendSlaveAddressI2C; // load the send slave address function
        I2C2CONbits.SEN = 1; // send start condition
        while (!(I2C_1_values.status == SUCCESS || I2C_1_values.status == FAILED));
        if (I2C_1_values.status == SUCCESS)
            return true; // return successful
        else
            return false;
    } else {
        return false; // return failed if an i2c request is already running
    }
}

// send the slave address

void SendSlaveAddressI2C(void) {
    if (I2C_1_values.direction == RECEIVE) {
        I2C2TRN = I2C_1_values.slave_address | 0x00; // load slave address into buffer
    } else {

        I2C2TRN = I2C_1_values.slave_address | 0x00; // load slave address into buffer
    }
    if (I2C_1_values.transMode == WriteWrite && I2C_1_values.direction == TRANSMIT) {
        FunctionI2C = &SendDataI2C; // load function that will continue sending
    } else {
        FunctionI2C = &SendDataAddressI2C; // load the send data address function
    }


}

// send data address if receiving or send files byte if sending

void SendDataAddressI2C(void) {
    // if ack is recieved then slave responded
    if (I2C2STATbits.ACKSTAT == 0) //ack received
    {

        // check the direction sending or receiving
        if (I2C_1_values.direction == RECEIVE) // receiving
        {
            I2C2TRN = I2C_1_values.data_address; // load data address value
            FunctionI2C = &SendStartI2C; // load send restart function
        } else if (I2C_1_values.direction == TRANSMIT) // transmitting
        {
            I2C2TRN = I2C_1_values.data_address; // load data address value
            //if (I2C_1_values.writeRS == true) {
            FunctionI2C = &SendDataI2C; // load function that will continue sending
            //}
        } else //neither transmit or receive (just in case)
        {
            StopFunctionI2C(); // initiate stop
            FunctionI2C = &FailFunctionI2C; // load fail function
        }

    } else //nack received
    {
        StopFunctionI2C(); // since nack redeived stop the buss
        FunctionI2C = &FailFunctionI2C; // load fail function
        // LATGbits.LATG8 ^= 1;
    }
}

void SendDataI2C(void) {
    if (I2C2STATbits.ACKSTAT == 0) //ack received
    {
        //if index is less than how much data, send data and increment index
        if (I2C_1_values.Txdata_index < I2C_1_values.Txcount) {
            I2C2TRN = I2C_1_values.Txdata[I2C_1_values.Txdata_index]; // load data into buffer
            I2C_1_values.Txdata_index++; // increment index
        }
        else //all data has been sent
        {
            if (I2C_1_values.transMode == WriteRead && I2C_1_values.direction == TRANSMIT) {
                I2C2CONbits.SEN = 1; // send start condition
                FunctionI2C = &SendReadRequestI2C;
                I2C_1_values.direction = RECEIVE;
            } else {
                StopFunctionI2C(); // since all data hase been sent initiate stop
                FunctionI2C = &SuccessFunctionI2C; // load sucess function
            }
        }
    } else //nack received
    {
        StopFunctionI2C(); // since nack redeived stop the buss
        FunctionI2C = &FailFunctionI2C; // load fail function
    }
}

// send a stop to then later send start

void SendRestartI2C(void) {
    I2C2CONbits.PEN = 1; //send stop
    FunctionI2C = &SendStartI2C; // load start function
}

// send start as a followup to the restart

void SendStartI2C(void) {
    I2C2CONbits.SEN = 1; // send start condition
    if (I2C_1_values.transMode == WriteWrite) {
        FunctionI2C = &SendSlaveAddressI2C;
        I2C_1_values.direction = TRANSMIT;
    } else
        FunctionI2C = &SendReadRequestI2C; // load send read request function

}


// send read request

void SendReadRequestI2C(void) {
    I2C2TRN = (I2C_1_values.slave_address + 1); // send slave address plus 1
    FunctionI2C = &FirstReceiveI2C; // load first receive function
}

void FirstReceiveI2C(void) {

    if (I2C2STATbits.ACKSTAT == 0) //ack received
    {
        I2C2CONbits.RCEN = 1; // enable receive
        FunctionI2C = &ReceiveByteI2C;
    } else //nack received
    {
        StopFunctionI2C();
        FunctionI2C = &FailFunctionI2C;
    }
}

void ReceiveByteI2C(void) {
    I2C_1_values.Rxdata[I2C_1_values.Rxdata_index] = I2C2RCV;
    I2C_1_values.Rxdata_index++;
    if (I2C_1_values.Rxdata_index < I2C_1_values.Rxcount) {
        I2C2CONbits.ACKDT = 0; //Setup ACK (EDITED()
        I2C2CONbits.ACKEN = 1; // send ACK
        FunctionI2C = &EnableReceiveI2C;
    } else {
        I2C2CONbits.ACKDT = 1; //Setup NACK (EDITED()
        I2C2CONbits.ACKEN = 1; // send NACK
        FunctionI2C = &NACKFollowUpI2C;
    }
}

void EnableReceiveI2C(void) {
    I2C2CONbits.RCEN = 1; // enable receive
    FunctionI2C = &ReceiveByteI2C;
}

void NACKFollowUpI2C(void) {
    StopFunctionI2C();
    FunctionI2C = &SuccessFunctionI2C;
}

void StopFunctionI2C(void) {

    I2C2CONbits.PEN = 1; //send stop
}

void FailFunctionI2C(void) {

    I2C_1_values.status = FAILED;

}

void SuccessFunctionI2C(void) {
    I2C_1_values.status = SUCCESS;

}

unsigned char StatusI2C(void) {
    return I2C_1_values.status;
}

void __attribute__((interrupt, no_auto_psv)) _MI2C2Interrupt(void) {
    //LED2 ^= 1;
    if (I2C2STATbits.BCL == 1) {
        StopFunctionI2C();
        FunctionI2C = &FailFunctionI2C;
        I2C2STATbits.BCL = 0;

    } else {
        FunctionI2C();
        //LATEbits.LATE7 ^= 1;
    }
    IFS3bits.MI2C2IF = 0; // clear interrupt flag
}

bool writeBits(char devAddr, char regAddr, char bitStart, char length, char data) {
    //      010 value to write
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    // 00011100 mask byte
    // 10101111 original value (sample)
    // 10100011 original & ~mask
    // 10101011 masked | value
    int b;
    if (ReceiveI2C(devAddr, regAddr, (unsigned char *) &b, 1) != 0) {
        char mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1); // shift data into correct position
        data &= mask; // zero all non-important bits in data
        b &= ~(mask); // zero all important bits in existing byte
        b |= data; // combine data with existing byte
        return SendI2C(devAddr, regAddr, (unsigned char *) &b, 1);
    } else {
        return false;
    }
}

bool writeBit(char devAddr, char regAddr, char bitNum, char data) {
    char b;

    //    ReceiveI2C(devAddr, regAddr,(unsigned char *) &b, 1);
    //    while(StatusI2C() == PENDING);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    return SendI2C(devAddr, regAddr, (unsigned char *) &b, 1);
}
