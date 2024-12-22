#include "PLL.h"
#include "GamePlay.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
//void Timer2_Init(unsigned long period);
unsigned long TimerCount;
unsigned long Semaphore;
unsigned long SpeedLevel ;  


// *************************** Images ***************************



// *************************** Capture image dimensions out of BMP**********


int main(void){
	 PLL_Init();            // Set clock
TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
  Nokia5110_Init(); //initilize nokia display
  Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();   			   // draw buffer

 //default drop of bird is 1 pixel/frame
	PortF_Init();   
	PortB_Init();
	ADC0_Init();

	Nokia5110_Clear();
	Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer(); 
	
	reset();
	Game_Init();
	
SpeedLevel = UART_Start() ;
	
	Timer2_Init(SpeedLevel);  //5M 
	
	while(1){
  }
}
