#include "myADC.h"
#include "stm32f10x.h"

void(*ADC1_Interrupt)(void) = 0;

void MyADC_Init (ADC_TypeDef * ADC, char channel){
	
	//Active clock ADC1 et ADC 2 
	RCC->APB2ENR |= (1<<9) | (1<<10);
	
	RCC->CFGR |=10<<14 ;
	ADC->SQR3|= (channel<<0x0);
	ADC->CR2 |= (0x1<<0);
	ADC->CR2 |= (0x1<<2);
	while(ADC->CR2 & (1<<2)){//Recalibration
	}
} 


void MyADC_Active_IT (ADC_TypeDef *ADC , char Prio, void(*Fonction_IT)(void)) {
	ADC->CR1 |= (1<<5);
	NVIC->ISER[0]|= 1<<18;
	NVIC->IP[18] = Prio<<4;
	ADC1_Interrupt = Fonction_IT;
}

void ADC1_2_IRQHandler  (void) {
	//ADC->SR |= (1<<1);
	ADC1->SR &= ~(1<<1);
}

int ConvertChannel(ADC_TypeDef *ADC) {
	while ( ADC->SR && 1<<1 != (1<<1) ) {}
	return ADC->DR ;
}



