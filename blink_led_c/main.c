// Platform MSP432P401R
// Compiler TI v20 2.5 LTS
// Date 13.JUL.2021
// Authour: VU3VWV

#include "msp.h"

#define red_off 0x00
#define red_on 0x01

#define green_off 0b00000000
#define green_on 0b00000010

#define blue_off 0b00000000
#define blue_on 0b00000100



void LED_Init(void){
    P2->SEL0 = 0x00;  // configure as gpio
    P2->SEL1 = 0x00;
    P2->DIR =0b00000111;   //configure as output
    }

void delay(){
    int i;
    
    for(i=1;i<50000;i++);
    }  

void main(){
    LED_Init();
    P2->OUT=0x00;           // Switchoff all
    
for(;;){
    P2->OUT=red_on;                //Switching on red led
    delay();
    P2->OUT=green_on;             //Switching on green led
    delay();
    P2->OUT= blue_on;             //Switching on blue led
    delay();
    }
    
}

    