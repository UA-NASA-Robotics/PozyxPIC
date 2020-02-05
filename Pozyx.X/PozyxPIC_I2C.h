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
///void InitI2Ctwo(void);

bool SendI2C(unsigned char s_address, unsigned char d_address, unsigned char * dat, unsigned char how_much);
//bool SendI2Ctwo(unsigned char s_address,  unsigned char d_address, unsigned char * dat, unsigned char how_much);

bool ReceiveI2C(unsigned char s_address, unsigned char d_address, unsigned char * dat, unsigned char how_much);
//bool ReceiveI2Ctwo(unsigned char s_address, unsigned char d_address, unsigned char * dat, unsigned char how_much);

void SendSlaveAddressI2C(void);
//void SendSlaveAddressI2Ctwo(void);

void SendDataAddressI2C(void);
//void SendDataAddressI2Ctwo(void);

void SendRestartI2C(void);
//void SendRestartI2Ctwo(void);

void SendStartI2C(void);
//void SendStartI2Ctwo(void);

void SendDataI2C(void);
//void SendDataI2Ctwo(void);

void StopFunctionI2C(void);
//void StopFunctionI2Ctwo(void);

void FailFunctionI2C(void);
//void FailFunctionI2Ctwo(void);

void SuccessFunctionI2C(void);
//void SuccessFunctionI2Ctwo(void);

void EnableReceiveI2C(void);
//void EnableReceiveI2Ctwo(void);

void SendReadRequestI2C(void);
//void SendReadRequestI2Ctwo(void);

void FirstReceiveI2C(void);
//void FirstReceiveI2Ctwo(void);

void ReceiveByteI2C(void);
//void ReceiveByteI2Ctwo(void);

unsigned char StatusI2C(void);
//unsigned char StatusI2Ctwo(void);

void NACKFollowUpI2C(void);
//void NACKFollowUpI2Ctwo(void);

bool writeBits(char devAddr, char regAddr, char bitStart, char length, char data);
bool writeBit(char devAddr, char regAddr, char bitNum, char data);

#endif	/* PozyxPIC_I2C_H */

