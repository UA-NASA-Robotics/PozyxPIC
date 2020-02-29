#include <xc.h>
#include <stdbool.h>
#include "Initialize.h"




#define GLOBAL_INTERRUPTS  INTCON2bits.GIE
int receiveArray[20];
void Start_Initialization()
{
    
    //GLOBAL_INTERRUPTS = OFF;
    //Initialization Function Calls go in here<GLOBAL_INTERRUPTS(OFF)/> to <GLOBAL_INTERRUPTS(ON)>
    oscillator();
    timerOne();
    pinModeLED1 = OUTPUT;
    pinModeLED2 = OUTPUT;
    pinModeLED3 = OUTPUT;
    pinModeLED4 = OUTPUT;
    pinModeLED5 = OUTPUT;
    pinModeLED6 = OUTPUT;
    pinModeLED7 = OUTPUT;
    pinModeLED8 = OUTPUT;
     __builtin_enable_interrupts();
}


void oscillator(void)
{
    // FRCDIV FRC/1; PLLPRE 3; DOZE 1:8; PLLPOST 1:2; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3001;
    // TUN Center frequency; 
    OSCTUN = 0x00;
    // ROON disabled; ROSEL FOSC; RODIV 0; ROSSLP disabled; 
    REFOCON = 0x00;
    // PLLDIV 13; 
    PLLFBD = 0x0D;
    // AD1MD enabled; PWMMD enabled; T3MD enabled; T4MD enabled; T1MD enabled; U2MD enabled; T2MD enabled; U1MD enabled; QEI1MD enabled; SPI2MD enabled; SPI1MD enabled; C2MD enabled; C1MD enabled; DCIMD enabled; T5MD enabled; I2C1MD enabled; 
    PMD1 = 0x00;
    // OC5MD enabled; OC6MD enabled; OC7MD enabled; OC8MD enabled; OC1MD enabled; IC2MD enabled; OC2MD enabled; IC1MD enabled; OC3MD enabled; OC4MD enabled; IC6MD enabled; IC7MD enabled; IC5MD enabled; IC8MD enabled; IC4MD enabled; IC3MD enabled; 
    PMD2 = 0x00;
    // ADC2MD enabled; PMPMD enabled; U3MD enabled; QEI2MD enabled; RTCCMD enabled; CMPMD enabled; T9MD enabled; T8MD enabled; CRCMD enabled; T7MD enabled; I2C2MD enabled; T6MD enabled; 
    PMD3 = 0x00;
    // U4MD enabled; CTMUMD enabled; REFOMD enabled; 
    PMD4 = 0x00;
    // PWM2MD enabled; PWM1MD enabled; PWM4MD enabled; SPI3MD enabled; PWM3MD enabled; PWM6MD enabled; PWM5MD enabled; 
    PMD6 = 0x00;
    // PTGMD enabled; DMA0MD enabled; 
    PMD7 = 0x00;
    // CF no clock failure; NOSC PRIPLL; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
    __builtin_write_OSCCONH((uint8_t) (0x03));
    __builtin_write_OSCCONL((uint8_t) (0x01));
    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN != 0);
    while (OSCCONbits.LOCK != 1);
}
void timerOne(void)
{

    T1CONbits.TCKPS = 0b10; // 64 divider
    PR1 = 469;              // 0.001s timer
    IPC0bits.T1IP = 1;      // interrupt priority level 1
    IFS0bits.T1IF = 0;      // clear interrupt flag
    IEC0bits.T1IE = 1;      // enable timer 1 interrupt
    T1CONbits.TON = 1;      // turn on timer
}
