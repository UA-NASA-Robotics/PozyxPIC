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
//void timerOne(void)
//{
//
//    T1CONbits.TCKPS = 0b10; // 64 divider
//    PR1 = 938;              // 0.001s timer
//    IPC0bits.T1IP = 1;      // interrupt priority level 1
//    IFS0bits.T1IF = 0;      // clear interrupt flag
//    IEC0bits.T1IE = 1;      // enable timer 1 interrupt
//    T1CONbits.TON = 1;      // turn on timer
//}
//void timerTwo(void)
//{
//    T2CONbits.TCKPS = 0b11; // 256 divider
//    PR2 = 2350; // 0.01s timer
//    IPC1bits.T2IP = 1; // interrupt priority level 1
//    IFS0bits.T2IF = 0; // clear interrupt flag
//    IEC0bits.T2IE = 1; // enable timer 2 interrupt
//    T2CONbits.TON = 1; // turn on timer
//    
//}
//void init_SPI()
//{
//    SPI1STATbits.SPIEN = 0;     //disables the module and configures SCK1, SDO1, SDI1, and SS1 as serial port pins
//    SPI1CON1bits.MODE16 = 0;    //Communication is byte-wide (8bits))
//    SPI1CON1bits.DISSDO = 0;    //SDO1 pin is controlled by the module
//    SPI1CON1bits.CKE = 0;       //Serial output data changes on transition from active clock state to Idle clock state (refer to bit 6)
//    SPI1CON1bits.CKP = 1;       // Idle state for clock is a high level; active state is a low level
//    SPI1CON1bits.SSEN = 0;      //SS1 pin is not used by the module; pin is controlled by port function
//    SPI1CON1bits.SPRE = 0;      //Secondary Prescale
//    SPI1CON1bits.PPRE = 2;      //Primary Prescale
//    SPI1CON1bits.MSTEN = 1;     //Master Mode bit Enabled
//    SPI1CON2bits.FRMEN = 0;     // FRAMEN = 1, SPIFSD = 0,  //make the clock line continously oscillate when set to 1
//    SPI1CON2bits.SPIFSD = 0;    //0 = Frame Sync pulse output (master)                 
//    SPI1CON2bits.FRMPOL = 1;    //Polarity of Frame sync pulse
//   // SPI1STATbits.SISEL = 0b101; //Interrupt when the last bit is shifted out of SPI1SR and the transmit is complete          //interrupt bits
//   // IFS0bits.SPI1IF = 0;        //Setting the interrupt flag
//    SPI1STATbits.SPIEN = 1;     //Enables the module and configures SCK1, SDO1, SDI1, and SS1 as serial port pins
//}
