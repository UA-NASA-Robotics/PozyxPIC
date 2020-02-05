/* 
 * File:   initialize.h
 * Author: John
 *
 * Created on February 22, 2017, 7:30 AM
 */

#ifndef INITIALIZE_H
#define	INITIALIZE_H



#include <xc.h>



#define FCY 60000000UL

#define OFF 0
#define ON 1

#define INPUT 1
#define OUTPUT 0

#define LED1 LATBbits.LATB10
#define LED2 LATBbits.LATB11
#define LED3 LATBbits.LATB12
#define LED4 LATBbits.LATB13
#define LED5 LATAbits.LATA10
#define LED6 LATAbits.LATA7
#define LED7 LATBbits.LATB14
#define LED8 LATBbits.LATB15

#define pinModeLED1 TRISBbits.TRISB10
#define pinModeLED2 TRISBbits.TRISB11
#define pinModeLED3 TRISBbits.TRISB12
#define pinModeLED4 TRISBbits.TRISB13
#define pinModeLED5 TRISAbits.TRISA10
#define pinModeLED6 TRISAbits.TRISA7
#define pinModeLED7 TRISBbits.TRISB14
#define pinModeLED8 TRISBbits.TRISB15
//END OF LED DEFINITIONS



//bool Initialize();
void Start_Initialization();
//switches the clock from the FRC to the external HS oscillator
void oscillator(void);
void timerOne(void);
void timerTwo(void);

void init_SPI();


#endif	/* INITIALIZE_H */

