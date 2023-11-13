#include "Timer.h"
#include "Driver_GPIO.h"
#include "ADC.h"

void ADC_Base_Init (ADC_TypeDef * adc){
	if(adc == ADC1){
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	}else{
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	}
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	
	adc->CR2 |= ADC_CR2_ADON;
	
	adc->CR2 |= ADC_CR2_SWSTART;
	
	adc->CR2 |= ADC_CR2_EXTTRIG;
	
	adc->CR2 |= (ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0);
	
	adc->SMPR1 |= (ADC_SMPR1_SMP10_2 | ADC_SMPR1_SMP10_1 | ADC_SMPR1_SMP10_0);
	 
}

//sortie sur DR => ADC_DR
//set a 1 le exttrig sur CR2
//ADC prescaler
//chanel 10