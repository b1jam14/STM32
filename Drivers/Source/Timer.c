#include "Timer.h"
#include "Driver_GPIO.h"

void (*funcIT)(void);

void MyTimer_Base_Init(TIM_TypeDef * Timer, unsigned short ARR, unsigned short PSC){
	if(Timer == TIM1){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	}else if(Timer == TIM2){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	}else if(Timer == TIM3){
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	}else if(Timer == TIM4){
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	}
	Timer->ARR=ARR; //5999
	Timer->PSC=PSC; //5999
	Timer->CR1 &= ~TIM_CR1_DIR;
}

void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio,void (*functionIT)(void)){
	Timer->DIER |= TIM_DIER_UIE;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_28;
	NVIC->IP[28] = Prio<<4;
	funcIT = functionIT;
}

void TIM2_IRQHandler(void){
		TIM2->SR &= ~TIM_SR_UIF;
		(*funcIT)();
}

void MyTimer_PWM(TIM_TypeDef * Timer , char Channel){
	switch(Channel){
		
		case 1:
			MyGPIO_Init (GPIOA, 0, AltOut_Ppull);
			Timer->CCER |= TIM_CCER_CC1E;
			Timer->CCMR1 &= ~(0x11);
			Timer->CCMR1 &= ~(0xF<<4);
			Timer->CCMR1 |= (0xE<<4);
			break;
		case 2:
			MyGPIO_Init (GPIOA, 1, AltOut_Ppull);
			Timer->CCER |= TIM_CCER_CC2E;
			Timer->CCMR1 &= ~(0x11<<8);
			Timer->CCMR1 &= ~(0xF<<12);
			Timer->CCMR1 |= (0xE<<12);
			break;
		case 3:
			MyGPIO_Init (GPIOA, 2, AltOut_Ppull);
			Timer->CCER |= TIM_CCER_CC3E;
			Timer->CCMR2 &= ~(0x11);
			Timer->CCMR2 &= ~(0xF<<4);
			Timer->CCMR2 |= (0xE<<4);
			break;
		case 4:
			MyGPIO_Init (GPIOA, 3, AltOut_Ppull);
			Timer->CCER |= TIM_CCER_CC4E;
			Timer->CCMR2 &= ~(0x11<<8);	
			Timer->CCMR2 &= ~(0xF<<12);
			Timer->CCMR2 |= (0xE<<12);
			break;
	}
}

void PWM_set_cycle(TIM_TypeDef * Timer, int cycle){
	Timer->CCR1 = ((Timer->ARR)*cycle)/100;    // cycle % 
}
