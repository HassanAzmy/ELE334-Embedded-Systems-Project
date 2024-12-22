#include "GPIO.h"
#include "files/tm4c123gh6pm.h"
#include "TM4C123/TM4C123GH6PM.h"

extern GPIO_Port_Configuration_t portCfg[];

GPIO_RES_t GPIO_INIT(GPIO_Port_Configuration_t* GPIOFCfg) {
		int pinNum;		
		for(pinNum = 0; pinNum < MAX_PIN_NUMBER; pinNum ++) {
			GPIO_SetDirection(pinNum, GPIOFCfg->pinsCfg[pinNum].direction);
			GPIO_SetDigitalAnalog(pinNum, GPIOFCfg->pinsCfg[pinNum].digitalAnalogSelect);
			GPIO_setPullup(pinNum, GPIOFCfg->pinsCfg[pinNum].pullUp);
			GPIO_setPulldown(pinNum, GPIOFCfg->pinsCfg[pinNum].pullDown);
			if(GPIOFCfg->pinsCfg[pinNum].interruptMask == GPIO_INTERRUPT_ENABLED) {
				GPIO_EnableDisableInterrupt(pinNum, GPIOFCfg->pinsCfg[pinNum].interruptMask);
				GPIO_SetInetrruptSensitivity(pinNum, GPIOFCfg->pinsCfg[pinNum].interruptSense);
				GPIO_SetInetrruptResponse(pinNum, GPIOFCfg->pinsCfg[pinNum].interruptBothEdge);
				GPIO_SetInetrruptEvent(pinNum, GPIOFCfg->pinsCfg[pinNum].interruptEvent);
			}			
		}	
	return GPIO_RES_OK;
}

GPIO_RES_t GPIO_SetDirection(GPIO_Pin_t pinNum, GPIO_Direction_t direction) {
		if (pinNum >= MAX_PIN_NUMBER) {
        return GPIO_RES_NOT_OK;
    }

    if (direction == GPIO_INPUT) {
        GPIOF->DIR &= ~(1 << pinNum);
    } else if (direction == GPIO_OUTPUT) {
        GPIOF->DIR |= (1 << pinNum);
    } else {
        return GPIO_RES_NOT_OK;
    }
    return GPIO_RES_OK;
}

GPIO_RES_t GPIO_SetDigitalAnalog(GPIO_Pin_t pinNum, GPIO_DigitalAnalogSelect_t digitalAnalogSelect) {
		if (pinNum >= MAX_PIN_NUMBER) {
        return GPIO_RES_NOT_OK;
    }

    if (digitalAnalogSelect == GPIO_DIGITAL) {
        GPIOF->DEN |= (1 << pinNum);  
        GPIOF->AMSEL &= ~(1 << pinNum); 
    } else if (digitalAnalogSelect == GPIO_ANALOG) {
        GPIOF->DEN &= ~(1 << pinNum);  
        GPIOF->AMSEL |= (1 << pinNum);
    } else {
        return GPIO_RES_NOT_OK;
    }
    return GPIO_RES_OK;
}


GPIO_RES_t GPIO_SetInetrruptSensitivity(GPIO_Pin_t pinNum, GPIO_Interrupt_Edge_Sense_t edgeSensitivity) {
		if (pinNum >= MAX_PIN_NUMBER) {
        return GPIO_RES_NOT_OK;
    }

    if (edgeSensitivity == GPIO_EDGE_SENSE) {
        GPIOF->IS &= ~(1 << pinNum); // Edge-sensitive
    } else if (edgeSensitivity == GPIO_LEVEL_SENSE) {
        GPIOF->IS |= (1 << pinNum); // Level-sensitive
    } else {
        return GPIO_RES_NOT_OK;
    }
    return GPIO_RES_OK;
}
GPIO_RES_t GPIO_SetInetrruptResponse(GPIO_Pin_t pinNum, GPIO_Interrupt_Both_Edge_t edgeResponse) {
		if (pinNum >= MAX_PIN_NUMBER) {
        return GPIO_RES_NOT_OK;
    }

    if (edgeResponse == GPIO_BOTH_EDGE) {
        GPIOF->IBE |= (1 << pinNum);
    } else if (edgeResponse == GPIO_ONE_EDGE) {
        GPIOF->IBE &= ~(1 << pinNum); 
    } else {
        return GPIO_RES_NOT_OK;
    }
    return GPIO_RES_OK;
}
GPIO_RES_t GPIO_SetInetrruptEvent(GPIO_Pin_t pinNum, GPIO_Interrupt_Event_t event) {
		if (pinNum >= MAX_PIN_NUMBER) {
        return GPIO_RES_NOT_OK;
    }

    if (event == GPIO_RISING_OR_HIGH) {
        GPIOF->IEV |= (1 << pinNum);
    } else if (event == GPIO_FALLING_OR_LOW) {
        GPIOF->IEV &= ~(1 << pinNum); 
    } else {
        return GPIO_RES_NOT_OK;
    }
    return GPIO_RES_OK;
}
GPIO_RES_t GPIO_EnableDisableInterrupt(GPIO_Pin_t pinNum, GPIO_Interrupt_MASK_t enableDisable) {
		if (pinNum >= MAX_PIN_NUMBER) {
        return GPIO_RES_NOT_OK;
    }

    if (enableDisable == GPIO_INTERRUPT_ENABLED) {
        GPIOF->IM |= (1 << pinNum); 
    } else if (enableDisable == GPIO_INTERRUPT_DISABLED) {
        GPIOF->IM &= ~(1 << pinNum);
    } else {
        return GPIO_RES_NOT_OK;
    }
    return GPIO_RES_OK;
}

GPIO_RES_t GPIO_setPullup(GPIO_Pin_t pinNum, GPIO_Enable_t enableDisable) {
    if (pinNum >= MAX_PIN_NUMBER) {
        return GPIO_RES_NOT_OK;
    }

    if (enableDisable == GPIO_ENABLE) {
        GPIOF->PUR |= (1 << pinNum);  
    } else if (enableDisable == GPIO_DISABLE) {
        GPIOF->PUR &= ~(1 << pinNum);
    } else {
        return GPIO_RES_NOT_OK;
    }
    return GPIO_RES_OK;
}

GPIO_RES_t GPIO_setPulldown(GPIO_Pin_t pinNum, GPIO_Enable_t enableDisable) {
    if (pinNum >= MAX_PIN_NUMBER) {
        return GPIO_RES_NOT_OK;
    }

    if (enableDisable == GPIO_ENABLE) {
        GPIOF->PDR |= (1 << pinNum);  
    } else if (enableDisable == GPIO_DISABLE) {
        GPIOF->PDR &= ~(1 << pinNum); 
    } else {
        return GPIO_RES_NOT_OK;
    }
    return GPIO_RES_OK;
}

GPIO_RES_t GPIO_interruptClear(GPIO_Pin_t pinNum, GPIO_Interrupt_Clear_t interruptClear) {
    if (pinNum >= MAX_PIN_NUMBER) {
        return GPIO_RES_NOT_OK;
    }

    if (interruptClear == GPIO_CLEARED) {
        GPIOF->ICR |= (1 << pinNum);
    } else if (interruptClear == GPIO_NOT_CLEARED) {
        GPIOF->ICR &= ~(1 << pinNum);
    } else {
        return GPIO_RES_NOT_OK;
    }
    return GPIO_RES_OK;
}

GPIO_RES_t GPIO_alternateFunctionSelect(GPIO_Pin_t pinNum, GPIO_Enable_t alternateFunctionSelection) {
    if (pinNum >= MAX_PIN_NUMBER) {
        return GPIO_RES_NOT_OK;
    }

    if (alternateFunctionSelection == GPIO_ENABLE) {
        GPIOF->AFSEL |= (1 << pinNum);  // Enable alternate function
    } else if (alternateFunctionSelection == GPIO_DISABLE) {
        GPIOF->AFSEL &= ~(1 << pinNum); // Disable alternate function
    } else {
        return GPIO_RES_NOT_OK;
    }
    return GPIO_RES_OK;
}

void GPIOF_INIT(void) {
		SYSCTL_RCGC2_R |= 0x00000020;
		GPIOF->LOCK = GPIO_LOCK_KEY;
		GPIO_PORTF_CR_R = 0x1F;
		
		// 30 / 4 => 7 (PRI7)
		// 30 % 4 => 2 => 2*8 + 5 => 21 22 23
		NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF)|0x00800000; // priority 4
		NVIC_EN0_R = 0x40000000;					             // enable interrupt 30 in NVIC;
		GPIO_INIT(portCfg);
}










