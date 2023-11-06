#include "stm32f10x.h"
#include "Driver_GPIO.h"

int main(void){
	
	
	/*
	GPIOA->CRH &= ~(0x01 << 16) & ~(0x01 << 17) & ~(0x01 << 18) & ~(0x01 << 19);
	GPIOA->CRH |= (0x01 << 19);
	
	GPIOB->CRL &= ~(0x0f << 28);
	GPIOB->CRL |= (0x01 << 28);*/
	
	MyGPIO_Init(GPIOA, 12, In_PullDown);
	MyGPIO_Init(GPIOB, 7, Out_Ppull);
	
	do{
		if((MyGPIO_Read(GPIOA, 12))){
			
			MyGPIO_Set(GPIOB, 7);
		}else{
			MyGPIO_Reset(GPIOB, 7);		
		}
			//MyGPIO_Toggle(GPIOB, 7);
		//}
	}while(1);
}
