#include <stdbool.h>
#include <stdlib.h>
#include "files/tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "Random.h"
#include "TExaS.h"
#include "Port.h"
#include "Timer.h"
#include "ADC.h" 
#include "image.h"
#include "UART.h"
#include "Leds.h"
#include "Status.h"

#define POLE_CLEARANCE_LVL3 15
#define POLE_CLEARANCE_LVL2 20
#define POLE_CLEARANCE_LVL1 25
#define POLE_WIDTH 6
#define SCREEN_TOP 0
#define SCREEN_BOT 48
#define BIRD_HEIGHT 10
#define BIRD_WIDTH 10
#define BIRD_X_POS 30



void Game_Init(void) ;
void DisplayPole(PoleObject poles[]); 
void display_game_screen(int brid_y_pos, PoleObject poles[]) ;
int get_clearance(int pole_id) ;
void check_collision(int bird_y_pos, int pole_id, int pole_x_pos) ;
void move_bird_pole(PoleObject poles[]) ;
void display_start_screen() ;
void reset() ;
void display_end_screen(int score);
void display_hit_screen() ;

void GPIOPortF_Handler(void);
void ADC0Seq3_Handler(void);
void Timer2A_Handler(void);
