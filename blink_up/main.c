/*This program blinks LED using Timer and Interrupt.(Up Mode)*/
#include "driverlib.h"

const Timer_A_UpModeConfig up_mode_config={
     TIMER_A_CLOCKSOURCE_ACLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_1,
     65500,                                 //ccr value
     TIMER_A_TAIE_INTERRUPT_ENABLE,
     TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,
     TIMER_A_DO_CLEAR
};
void main(void)
{
    GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN1|GPIO_PIN0);            //configuring the LEDs
    GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0);

    CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);         //Configuring the oscillator and clock
    CS_initClockSignal(CS_ACLK,CS_REFOCLK_SELECT,CS_CLOCK_DIVIDER_4);

    Timer_A_configureUpMode(TIMER_A0_BASE,&up_mode_config);             //up mode configuration
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);          //clear ccr flag

    Interrupt_enableSleepOnIsrExit();
    Interrupt_enableInterrupt(INT_TA0_0);

    Interrupt_enableMaster();

    Timer_A_startCounter(TIMER_A0_BASE,TIMER_A_UP_MODE);

     while(1)
      {
            __WFI();
       }


}

void TA0_0_IRQHandler()
{
    GPIO_toggleOutputOnPin(GPIO_PORT_P2,GPIO_PIN1|GPIO_PIN0);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_0);
}
