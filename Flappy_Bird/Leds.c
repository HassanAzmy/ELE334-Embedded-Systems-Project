#include "Leds.h"
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


void TurnOnLvl1Led(void) 
{
GPIO_PORTB_DATA_R=(1<<0); // trun on red led 
	//GPIO_PORTB_DATA_R = 0xFF;
}

void TurnOnLvl2Led(void) 
{
GPIO_PORTB_DATA_R=(1<<5); // trun on green led 
}

void TurnOnLvl3Led(void)
{
GPIO_PORTB_DATA_R=(1<<0)|(1<<5); // trun on yellow led 
}

void TurnOffAllLeds(void) 
{
GPIO_PORTB_DATA_R=0; // trunoff all leds
}

