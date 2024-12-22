#include "Port.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "files/tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "TExaS.h"
#include <stdbool.h>
#include <stdlib.h>


#define sw2 (GPIO_PORTF_RIS_R & (1 << 0))
#define sw1 (GPIO_PORTF_RIS_R & (1 << 4))

// Initializes Port F
void PortF_Init(void){ 
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0    

 // interrupt  
	 GPIO_PORTF_IS_R &= ~(1 << 0) ; //(1 << 0 | 1 << 4);					// PF4 is edge sensitive
	 GPIO_PORTF_IBE_R &= ~(1 << 0) ; //(1 << 0 | 1 << 4);				// PF4 is not both edges
	 GPIO_PORTF_IEV_R &= ~(1 << 0) ; //(1 << 0 | 1 << 4);				// falling edge
	 GPIO_PORTF_ICR_R = (1 << 0) ; // (1 << 0 | 1 << 4);					// clear flag4
	 GPIO_PORTF_IM_R |=(1 << 0) ; // (1 << 0 | 1 << 4);					// arm interrupt on PF4 and PF0
	// 30 / 4 => 7 (PRI7)
	// 30 % 4 => 2 => 2*8 + 5 => 21 22 23
	 NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF)|0x00800000; // priority 4
	 NVIC_EN0_R = 0x40000000;					             // enable interrupt 30 in NVIC;
}



void PortB_Init(void){ 
  SYSCTL_RCGC2_R |= 0x00000002;     // 1) F clock
  GPIO_PORTB_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTB_CR_R = 0x30;           // allow changes to PF4-0       
  GPIO_PORTB_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTB_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTB_DIR_R = 0xFF;          // 5) PF4,PF0 PF3,PF2 input, , PF1 PF0 output   
  GPIO_PORTB_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTB_PUR_R = 0x00;          // enable pullup resistors on PF4,PF0   
  GPIO_PORTB_PDR_R = 0x00; 	
  GPIO_PORTB_DEN_R = 0xFF;          // 7) enable digital pins PF4-PF0        
}
