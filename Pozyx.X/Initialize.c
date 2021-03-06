#include <xc.h>
#include <stdbool.h>
#include "Initialize.h"
#include <stdio.h>
#include "mcc_generated_files/can1.h"
#include "mcc_generated_files/dma.h"
#include "uart1_config.h"



#define GLOBAL_INTERRUPTS  INTCON2bits.GIE
int receiveArray[20];

void Start_Initialization() {

    //GLOBAL_INTERRUPTS = OFF;
    //Initialization Function Calls go in here<GLOBAL_INTERRUPTS(OFF)/> to <GLOBAL_INTERRUPTS(ON)>
    oscillator();
    timerOne();
    
    TRISA = 0x0797;
    TRISB = 0xFFFF;
    TRISC = 0x03BE;
    
    pinModeLED1 = OUTPUT;
    pinModeLED2 = OUTPUT;
    pinModeLED3 = OUTPUT;
    pinModeLED4 = OUTPUT;
    pinModeLED5 = OUTPUT;
    pinModeLED6 = OUTPUT;
    pinModeLED7 = OUTPUT;
    pinModeLED8 = OUTPUT;

    ANSELC = 0xD;

    /* Set the PPS */
    __builtin_write_OSCCONL(OSCCON & 0xbf);

    RPOR6bits.RP54R = 0x000E; //CAN TX
    RPINR26bits.C1RXR = 0x0037; //CAN RX

    RPINR18bits.U1RXR = 0x0031; //RC1-> UART1:U1RX
    RPOR5bits.RP48R = 0x0001; //RC0-> UART1:U1TX

    __builtin_write_OSCCONL(OSCCON | 0x40);
    DMA_Initialize();
    CAN1_TransmitEnable();
    CAN1_ReceiveEnable();
    /*Initialize uart1 processes*/
    uart1_init();
    __builtin_enable_interrupts();
    

}

void oscillator(void) {
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

void timerOne(void) {

    T1CONbits.TCKPS = 0b10; // 64 divider
    PR1 = 469; // 0.001s timer
    IPC0bits.T1IP = 1; // interrupt priority level 1
    IFS0bits.T1IF = 0; // clear interrupt flag
    IEC0bits.T1IE = 1; // enable timer 1 interrupt
    T1CONbits.TON = 1; // turn on timer
}

void LEDPattern() {
    LED1 = 1;
    __delay_ms(100);
    LED2 = 1;
    __delay_ms(100);
    LED3 = 1;
    __delay_ms(100);
    LED4 = 1;
    __delay_ms(100);
    LED5 = 1;
    __delay_ms(100);
    LED6 = 1;
    __delay_ms(100);
    LED7 = 1;
    __delay_ms(100);
    LED8 = 1;
    __delay_ms(100);
    LED1 = 0;
    __delay_ms(100);
    LED2 = 0;
    __delay_ms(100);
    LED3 = 0;
    __delay_ms(100);
    LED4 = 0;
    __delay_ms(100);
    LED5 = 0;
    __delay_ms(100);
    LED6 = 0;
    __delay_ms(100);
    LED7 = 0;
    __delay_ms(100);
    LED8 = 0;
}