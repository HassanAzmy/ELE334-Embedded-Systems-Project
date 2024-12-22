#include "GPIO_CFG.h"

typedef enum GPIO_Res_e {	
	GPIO_RES_NOT_OK,
	GPIO_RES_OK
}GPIO_RES_t;

typedef enum GPIO_Port_e {	
	GPIO_PORT_A,
	GPIO_PORT_B,
	GPIO_PORT_C,
	GPIO_PORT_D,
	GPIO_PORT_E,
	GPIO_PORT_F
}GPIO_Port_t;

typedef enum GPIO_Pin_e {	
	GPIO_PIN_0,
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7
}GPIO_Pin_t;

typedef enum GPIO_Direction_e {	
	GPIO_INPUT,
	GPIO_OUTPUT,
}GPIO_Direction_t;

typedef enum GPIO_Interrupt_Edge_Sense_e {	
	GPIO_EDGE_SENSE,
	GPIO_LEVEL_SENSE,
}GPIO_Interrupt_Edge_Sense_t;

typedef enum GPIO_Interrupt_Both_Edge_e {	
	GPIO_BOTH_EDGE,
	GPIO_ONE_EDGE,
}GPIO_Interrupt_Both_Edge_t;

typedef enum GPIO_Interrupt_Event_e {	
	GPIO_FALLING_OR_LOW,
	GPIO_RISING_OR_HIGH,
}GPIO_Interrupt_Event_t;

typedef enum GPIO_Interrupt_MASK_e {	
	GPIO_INTERRUPT_DISABLED,
	GPIO_INTERRUPT_ENABLED,
}GPIO_Interrupt_MASK_t;

typedef enum GPIO_DigitalAnalogSelect_e {	
	GPIO_DIGITAL,
	GPIO_ANALOG
}GPIO_DigitalAnalogSelect_t;

typedef enum GPIO_Enable_e {	
	GPIO_DISABLE,
	GPIO_ENABLE
}GPIO_Enable_t;

typedef enum GPIO_Interrupt_Clear_e {	
	GPIO_CLEARED,
	GPIO_NOT_CLEARED
}GPIO_Interrupt_Clear_t;

typedef struct GPIO_Pin_Configuration_s {	
	GPIO_DigitalAnalogSelect_t digitalAnalogSelect;
	GPIO_Direction_t direction;
	GPIO_Enable_t pullUp;
	GPIO_Enable_t pullDown;
	GPIO_Enable_t enableDisableAlternateFunction;
	GPIO_Interrupt_MASK_t interruptMask;
	GPIO_Interrupt_Edge_Sense_t interruptSense;
	GPIO_Interrupt_Both_Edge_t interruptBothEdge;
	GPIO_Interrupt_Event_t interruptEvent;
	GPIO_Interrupt_Clear_t clearInterrupt;
	
	
}GPIO_Pin_Configuration_t;

typedef struct GPIO_Port_Configuration_s {	
	GPIO_Pin_Configuration_t pinsCfg[MAX_PIN_NUMBER];
}GPIO_Port_Configuration_t;


GPIO_RES_t GPIO_INIT(GPIO_Port_Configuration_t* GPIOFCfg);
GPIO_RES_t GPIO_SetDigitalAnalog(GPIO_Pin_t pinNum, GPIO_DigitalAnalogSelect_t digitalAnalogSelect);
GPIO_RES_t GPIO_SetDirection(GPIO_Pin_t pinNum, GPIO_Direction_t direction);
GPIO_RES_t GPIO_setPullup(GPIO_Pin_t pinNum, GPIO_Enable_t enableDisable);
GPIO_RES_t GPIO_setPulldown(GPIO_Pin_t pinNum, GPIO_Enable_t enableDisable);
GPIO_RES_t GPIO_EnableDisableInterrupt(GPIO_Pin_t pinNum, GPIO_Interrupt_MASK_t enableDisable);
GPIO_RES_t GPIO_SetInetrruptSensitivity(GPIO_Pin_t pinNum, GPIO_Interrupt_Edge_Sense_t edgeSensitivity);
GPIO_RES_t GPIO_SetInetrruptResponse(GPIO_Pin_t pinNum, GPIO_Interrupt_Both_Edge_t edgeResponse);
GPIO_RES_t GPIO_SetInetrruptEvent(GPIO_Pin_t pinNum, GPIO_Interrupt_Event_t event);
GPIO_RES_t GPIO_interruptClear(GPIO_Pin_t pinNum, GPIO_Interrupt_Clear_t interruptClear);
GPIO_RES_t GPIO_alternateFunctionSelect(GPIO_Pin_t pinNum, GPIO_Enable_t alternateFunctionSelection);
void GPIOF_INIT(void);