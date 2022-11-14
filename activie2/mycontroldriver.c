#define MYCONTROLDRIVER_H
#include "stm32f10x.h"


void(*Usart1_Interrupt)(void) = 0;
void(*Usart3_Interrupt)(void) = 0;

void MyUsart_Base_Init ( USART_TypeDef*Usart) {
	if (Usart==USART3){
		RCC->APB1ENR |=  RCC_APB1ENR_USART3EN ;//(1<<18);
		USART3->CR1 = 0x00; //clear all
		USART3->CR1 |= (1<<13); //UE=1 enable usart
		USART3->BRR = (234<<4) + (6<<0);// mantisse 227 et fraction 14 
		USART3->CR1 |= (1<<2); // RE=1 enable receiver 
	} else if (Usart==USART1){
		RCC->APB1ENR |=  RCC_APB2ENR_USART1EN ;//(1<<18);
		USART1->CR1 = 0x00; //clear all
		USART1->CR1 |= (1<<13); //UE=1 enable usart
		USART1->BRR = (227<<4) | (14<<0);// mantisse 227 et fraction 14 
		USART1->CR1 |= (1<<2); // RE=1 enable receiver 
	}
}

void MyUsart_Active_IT ( USART_TypeDef*Usart , char Prio,void(*Fonction_IT)(void) ){
	Usart->CR1 |= 1<<5 ;
	if (Usart==USART3){
		NVIC->ISER[1]|= 1<<7;
		NVIC->IP[39] = Prio<<4;
		Usart3_Interrupt = Fonction_IT;
	} else if (Usart==USART1){
		NVIC->ISER[1]|= 1<<5;
		NVIC->IP[37] = Prio<<4;
		Usart1_Interrupt = Fonction_IT;
	}
}


void USART1_IRQHandler (void){
					USART1->SR &=  ~(1<<5);
						if(Usart1_Interrupt != 0){
							(*Usart1_Interrupt)();
						}
					}
void USART3_IRQHandler (void){
					USART3->SR &=  ~(1<<5);
						if(Usart3_Interrupt != 0){
							(*Usart3_Interrupt)();
						}
						
					}
