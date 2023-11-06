#include "Driver_GPIO.h"

void MyGPIO_Init (GPIO_TypeDef  * GPIO, char GPIO_PIN, char GPIO_Conf) {
	if (GPIO == GPIOA) {
		RCC->APB2ENR |= (0x01 << 2);
	}else if(GPIO == GPIOB){
		RCC->APB2ENR |= (0x01 << 3);
	}else if(GPIO == GPIOC){
		RCC->APB2ENR |= (0x01 << 4);
	}
	
	if(GPIO_PIN < 8){
		GPIO->CRL &= ~(0xf) << (4*GPIO_PIN);
		GPIO->CRL |= (GPIO_Conf << (4*GPIO_PIN));
		if (GPIO_Conf == In_PullDown){
			GPIO->ODR &= ~(1 << GPIO_PIN) ;
		}else if (GPIO_Conf == In_PullUp){
			GPIO->ODR |= (1 << GPIO_PIN) ;
		}
		
	}else{
		GPIO->CRH &= ~(0xf) << (4*GPIO_PIN-8);
		GPIO->CRH |= (GPIO_Conf << (4*(GPIO_PIN-8)));
		if (GPIO_Conf == In_PullDown){
			GPIO->ODR &= ~(1 << GPIO_PIN) ;
		}else if (GPIO_Conf == In_PullUp){
			GPIO->ODR |= (1 << GPIO_PIN) ;
		}
	}
}
	
int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) { // renvoie 0 ou autre chose different de 0
	 return (GPIO->IDR & (1 << GPIO_Pin))>>GPIO_Pin;
}

void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->ODR |= (0x01 << GPIO_Pin);
}

void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->ODR &= ~(0x01 << GPIO_Pin);
}

void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->ODR ^= (0x01<<GPIO_Pin);
}
