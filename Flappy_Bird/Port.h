//create a struct to hold x, y coordinates of the pole, and image pointer
typedef struct {
	unsigned long x; // x coordinate of the pole
	unsigned long y; // y coordinate of the pole = 47 
	unsigned int pole_active; //0= passed, greater than 0= active
	const unsigned char *image;
}PoleObject;


//initializing port F for inputs , B for output 
void PortF_Init(void);  //for sw2
void PortB_Init(void);


