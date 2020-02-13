/* 
 * File:   I2C_API_GYRO.h
 * Author: Igor(modified by Seth Carpenter)
 *
 * Created on December 14, 2014, 8:04 PM(modified: April 27, 2016)
 */

#ifndef PozyxPIC_I2C_H
#define	PozyxPIC_I2C_H

#define PENDING 0
#define SUCCESS 1
#define FAILED 2
#define TRANSMIT 1
#define RECEIVE 2

int get_dataIndex();


void InitI2C(void);
bool SendI2CRepeatStart(unsigned char s_address, unsigned char d_address, unsigned char * dat, unsigned char how_much);
bool SendI2C(unsigned char s_address, unsigned char d_address, unsigned char * dat, unsigned char how_much);

bool ReceiveI2C(unsigned char s_address, unsigned char d_address, unsigned char * dat, unsigned char how_much);

//////////////////////////
//                      //
//  SUPPORT FUNCTIONS   //
//                      //
//////////////////////////

void SendSlaveAddressI2C(void);

void SendDataAddressI2C(void);

void SendRestartI2C(void);

void SendStartI2C(void);

void SendDataI2C(void);

void StopFunctionI2C(void);

void FailFunctionI2C(void);

void SuccessFunctionI2C(void);

void EnableReceiveI2C(void);

void SendReadRequestI2C(void);

void FirstReceiveI2C(void);

void ReceiveByteI2C(void);

unsigned char StatusI2C(void);

void NACKFollowUpI2C(void);

bool writeBits(char devAddr, char regAddr, char bitStart, char length, char data);
bool writeBit(char devAddr, char regAddr, char bitNum, char data);

#endif	/* PozyxPIC_I2C_H */

