#include "ADC.h"
#include "files/tm4c123gh6pm.h"
#include "Status.h" 
void  EnableInterrupts();  

void ADC0_Init(void){ 
 
    SYSCTL_RCGCGPIO_R |= (1<<4);   // Enable Clock to GPIOE or PE3/AN0 
    SYSCTL_RCGCADC_R  |= (1<<0);    // AD0 clock enable
    GPIO_PORTE_AFSEL_R  |= (1<<3);  // enable alternate function 
    GPIO_PORTE_DEN_R&= ~(1<<3);     //disable digital function 
    GPIO_PORTE_AMSEL_R  |= (1<<3);  // enable analog function 
    // sample sequencer3 
   ADC0_ACTSS_R &= ~(1<<3);      // disable SS3 during configuration 
    ADC0_EMUX_R &= ~0xF000;    //software trigger conversion 
    ADC0_SSMUX3_R  = 0;         // get input from channel 0 
    ADC0_SSCTL3_R  |= (1<<1)|(1<<2);// take one sample at a time, set flag at 1st sample , and enable interrupt 
    ADC0_IM_R |= (1<<3); // Unmask ADC0 sequence 3 interrupt
  NVIC_EN0_R |= (1<<17); // enable IRQ17 for ADC0SS3
ADC0_ACTSS_R |= (1<<3); // enable ADC0 sequencer 3 
   ADC0_PSSI_R |= (1<<3);// Enable SS3 conversion or start sampling data from AN0 
	// IRO = 17 
	// 17/4 = 4 -- 17%4=1 // 13 14 15 
 NVIC_PRI4_R = (NVIC_PRI7_R & 0xFFFF00FF)|0x00006000; // priority 3
	
  EnableInterrupts();          

}
