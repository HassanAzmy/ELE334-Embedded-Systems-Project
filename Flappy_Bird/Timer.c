#include "Timer.h"
#include "Port.h"
#include "Status.h" 
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "files/tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "TExaS.h"
#include <stdbool.h>
#include <stdlib.h>



void Timer0_delay(unsigned long period){ 
	int i;
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate timer0
  //delay = SYSCTL_RCGCTIMER_R;
 // TimerCountt = 0;
 // Semaphoree = 0;
  TIMER0_CTL_R &=~0x00000000;    // 1) disable timer2A during setup
  TIMER0_CFG_R  = 0x00000000;    // 2) configure for 32-bit mode
  TIMER0_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER0_TAILR_R = 1600000-1;    // 4) reload value
	
	TIMER0_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
             
  TIMER0_CTL_R |= 0x00000001;    // 10) enable timer2A
		
	 for(i = 0; i < period; i++) 
	{
		while ((TIMER0_RIS_R & 0x1) == 0) ;      /* wait for TimerA timeout flag */
        TIMER0_ICR_R = 0x1;      /* clear the TimerA timeout flag */
  }
}


void Timer2_Init(unsigned long period){ 
  unsigned long volatile delay0;
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
  delay0 = SYSCTL_RCGCTIMER_R;
  //TimerCount = 0;
  //Semaphore = 0;
  TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
	
	// 23 / 4 => 5
	// 23 % 4 =? 3 => 3*8+5 => 29 30 31
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0xC0000000; // 8) priority 6
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC	// interrupts enabled in the main program after all devices initialized	// vector number 39, interrupt number 23
  TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}

