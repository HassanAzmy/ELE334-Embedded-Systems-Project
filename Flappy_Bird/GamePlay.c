#include "GamePlay.h"

#define STATE_START 0
#define STATE_PLAY 1
#define STATE_HIT 2
#define STATE_END 3


int st_flag = 1 ;

long level = 10000000 ;
int gravity;
int brid_y_pos;
int pole_x_pos;
int pole_id;
int current_state = 0;
int current_pole_id;
int SW2;
int random_number;
int score = 10;
int topscore = 0;
int adc_value ; 
int current_lvl = 1;
int rnd;

//create 6  pole objects
PoleObject PoleLvl3[6];
PoleObject PoleLvl2[6];
PoleObject PoleLvl1[6];

int clearenceLvl3[6] = {4, 9, 12, 14, 18, 22};
int clearenceLvl2[6] = {9, 4, -1, 14, 19, 24};
int clearenceLvl1[6] = {9, 4, -1, 14, 19, 24};


void DisableInterrupts(void); 
void EnableInterrupts(void); 

int i ;
void Game_Init(void){	
		PoleLvl3[0].image = pole_0;
		PoleLvl3[1].image = pole_1;
		PoleLvl3[2].image = pole_2;
		PoleLvl3[3].image = pole_3;
		PoleLvl3[4].image = pole_4;
		PoleLvl3[5].image = pole_5;
		for(i=0; i<6; i++){		
			PoleLvl3[i].x = 83 + 30 * i;
			PoleLvl3[i].y = 47;
			PoleLvl3[i].pole_active = 1;
		}
		
		PoleLvl2[0].image = pole_6;
		PoleLvl2[1].image = pole_7;
		PoleLvl2[2].image = pole_8;
		PoleLvl2[3].image = pole_9;
		PoleLvl2[4].image = pole_10;
		PoleLvl2[5].image = pole_11;
		for(i=0; i<6; i++){		
			PoleLvl2[i].x = 83 + 30 * i;
			PoleLvl2[i].y = 47;
			PoleLvl2[i].pole_active = 1;
		}
	
		PoleLvl1[0].image = pole_12;
		PoleLvl1[1].image = pole_13;
		PoleLvl1[2].image = pole_14;
		PoleLvl1[3].image = pole_15;
		PoleLvl1[4].image = pole_16;
		PoleLvl1[5].image = pole_17;
		for(i=0; i<6; i++){		
			PoleLvl1[i].x = 83 + 30 * i;
			PoleLvl1[i].y = 47;
			PoleLvl1[i].pole_active = 1;
		}
		
		DisplayPole(PoleLvl1);		// initial display
			gravity = 1; 
}

//display pole on screen
void DisplayPole(PoleObject poles[]){
	Nokia5110_ClearBuffer();
		for (i=0; i<6; i++){
			if (poles[i].pole_active > 0){
				//rnd = rand() % 6;
				Nokia5110_PrintBMP(poles[i].x, poles[i].y, poles[i].image,0);
			}
		}
	Nokia5110_DisplayBuffer();
}

void display_game_screen(int brid_y_pos, PoleObject poles[]){
	Nokia5110_ClearBuffer();
	for (i=0; i<6; i++){
			//rnd = rand() % 6;
			Nokia5110_PrintBMP(poles[i].x, poles[i].y, poles[i].image,0);
	}
	Nokia5110_PrintBMP(BIRD_X_POS, brid_y_pos, flappy, 0);
	Nokia5110_DisplayBuffer(); 
	//Delay100ms(1); 	
	//Timer0_delay(2);
}

int get_clearance(int pole_id){
	if(current_lvl == 1)
		return clearenceLvl1[pole_id];
	if(current_lvl == 2)
		return clearenceLvl2[pole_id];
	return clearenceLvl3[pole_id];
}

// collision state
void check_collision(int bird_y_pos, int pole_id, int pole_x_pos){
	int clearance_up = get_clearance(pole_id);
	int clearance_down;
	if(current_lvl == 1)
		clearance_down = clearance_up + POLE_CLEARANCE_LVL1;
	else if(current_lvl == 2)
		clearance_down = clearance_up + POLE_CLEARANCE_LVL2;
	else
		clearance_down = clearance_up + POLE_CLEARANCE_LVL3;
	
	//check if bird hits the top
	if ((bird_y_pos - BIRD_HEIGHT) <= SCREEN_TOP){
		current_state = STATE_HIT;
	}
	
	//check if bird hits the bot
	if (bird_y_pos >= SCREEN_BOT){
		current_state = STATE_HIT;
	}
	
	if((pole_x_pos < BIRD_X_POS + BIRD_WIDTH) && (pole_x_pos > BIRD_X_POS) ){
		//if bird is between clearance up and down ---> state=play
		//else state =hit
		if((bird_y_pos - BIRD_HEIGHT >= clearance_up) && (bird_y_pos <= clearance_down)){
//			GPIO_PORTB_DATA_R=0x30;
			current_state = STATE_PLAY;
		}
		else{
			current_state = STATE_HIT;
			//GPIO_PORTB_DATA_R=(1<<1);
		}
	}
}

void move_bird_pole(PoleObject poles[]){


//move the pole to left. 
	
	for (i=0; i<6; i++){
		if(poles[i].x == 0){
			poles[i].x = 180; 				//put it back in the array
			poles[i].pole_active = 1;
		}
		else{
			poles[i].x -= 1;
		}
		
		if (poles[i].x< BIRD_X_POS){
			poles[i].pole_active = 0; //pole is not active 
		}		
	}
	
	//get current pole_x_pos for the next active pole
	for (i=0; i<6; i++){
		if (poles[i].pole_active == 1 && poles[i].x <= BIRD_X_POS + BIRD_WIDTH){
			pole_x_pos = poles[i].x;
			pole_id = i;
		}
		if(poles[i].x + POLE_WIDTH == BIRD_X_POS){
			score ++;
			//GPIO_PORTB_DATA_R=(1<<0); // tuen on the led --  green 
		}
	}
	
	
	if( (GPIO_PORTF_DATA_R&1<<4) == 0){ // up
		brid_y_pos = brid_y_pos - 1;
	}
	else{
		brid_y_pos = brid_y_pos + gravity;//gravity; // down 
	}
	
	check_collision(brid_y_pos, pole_id, pole_x_pos);
	display_game_screen(brid_y_pos, poles);
}

void display_start_screen(){
	if(st_flag){
	Nokia5110_Clear();
	Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();	
	
	Nokia5110_SetCursor(1, 0);
	Nokia5110_OutString("Flappy Bird");
	Nokia5110_SetCursor(1, 2);
	Nokia5110_SetCursor(2, 5);
	Nokia5110_OutString("Press SW2");
		st_flag =0 ;
	}
}


void reset(){
  pole_x_pos = 83;
	brid_y_pos = 29;
	Game_Init();
	score=0;
}

void display_end_screen(int score){
	if (score > topscore)
	{
		topscore = score; 
	}
	
	if(st_flag) {
		Nokia5110_Clear();
		Nokia5110_ClearBuffer();
		Nokia5110_DisplayBuffer(); 
		
		//display current score, and display highest score from the memory
		Nokia5110_SetCursor(0, 0);
		Nokia5110_OutString("HIT!!");
		Nokia5110_SetCursor(0, 1);
		Nokia5110_OutString("Score:");
		Nokia5110_SetCursor(6, 1);
		Nokia5110_OutUDec(score);
		Nokia5110_SetCursor(0, 2);
		Nokia5110_OutString("Top:");
		Nokia5110_SetCursor(6, 2);
		Nokia5110_OutUDec(topscore);
		Nokia5110_SetCursor(0, 4);
		Nokia5110_OutString("Press sw2 to play again");
		st_flag=0 ;
	}
}
void display_hit_screen(){
	GPIO_PORTB_DATA_R=0x00;
	Nokia5110_Clear();
	Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer(); 

	Nokia5110_SetCursor(2, 2);
	Nokia5110_OutString("*********");
	Nokia5110_SetCursor(2, 3);
	Nokia5110_OutString("***HIT***");
	Nokia5110_SetCursor(2, 4);
	Nokia5110_OutString("*********");
	GPIO_PORTB_DATA_R |= (1<<3);	
	 Timer0_delay(40);
	 GPIO_PORTB_DATA_R &= ~(1<<3);
	current_state = STATE_END;
}



void GPIOPortF_Handler(void) {
	
	if(GPIO_PORTF_RIS_R & (1 << 0) && (current_state == STATE_START || current_state == STATE_END)){
		if(current_state == STATE_END)
			reset();
		current_state = STATE_PLAY;
		st_flag=1 ;
	}

	/*
	else{
		brid_y_pos = brid_y_pos -3;
	}
	*/ 
	GPIO_PORTF_ICR_R = (1 << 0 | 1 << 4);

}


void ADC0Seq3_Handler(void){
  
  adc_value =ADC0_SSFIFO3_R; /* read adc coversion result from SS3 FIFO*/
   ADC0_ISC_R= 8;          /* clear coversion clear flag bit*/
  ADC0_PSSI_R  |= (1<<3);        /* Enable SS3 conversion or start sampling data from AN0 data from AN0 */
	
			if (adc_value<=1023){
			gravity = 1 ;
	} else if (adc_value > 1023 && adc_value < 3071) {
		 gravity = 2 ; 
	} else if (adc_value>3071){
		 gravity = 3 ; 
	}

}


void Timer2A_Handler(void){ 
  TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
	
	if(score < 6) 
	{
				Nokia5110_ClearBuffer();
		current_lvl =1;
	}
	else if(score >= 6 && score<12) {
		Nokia5110_ClearBuffer();
		current_lvl = 2;
	}
	else if(score >= 12) {
		Nokia5110_ClearBuffer();
		current_lvl = 3;
	}
	

	switch(current_state)
		{
		case STATE_START: //start screen, ask to push switch to start game
			
			display_start_screen();
			break;
		case STATE_PLAY: //in-game, refresh screen constantly and update position of bird (based on user input)and pole
			if(current_lvl == 1){
				TurnOnLvl1Led();
				move_bird_pole(PoleLvl1);
			}
			else if(current_lvl == 2) {
				//DisplayPole(PoleLvl2);
				TurnOnLvl2Led();
				move_bird_pole(PoleLvl2);
			}
			else {
				//DisplayPole(PoleLvl3);
				TurnOnLvl3Led();
				move_bird_pole(PoleLvl3);
			}
			break;
		case STATE_HIT:  //bird either hit the top, bottom, or pole. Hit screen will show up
			TurnOffAllLeds();
			display_hit_screen();
			break;
		case STATE_END:  //display final score and maximum available score
			display_end_screen(score);
			break;
		//case STATE_password:  //ask user for password before start screen appears (PW: "awesome")
			//UART_password();
			break;
		default:
			display_start_screen();			
	}
}




