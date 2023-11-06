#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Timer.h"


void fonctionIT (void){
		MyGPIO_Toggle(GPIOB, 7);
}

int main(void){
	MyGPIO_Init(GPIOB, 7, Out_Ppull);
	MyTimer_Base_Init(TIM2, 5999, 5999);
	MyTimer_ActiveIT(TIM2, 10, fonctionIT);
	MyTimer_Base_Start(TIM2);
	MyTimer_PWM(TIM2, 1);
	PWM_set_cycle(TIM2,25);
	while(1){}	
}
