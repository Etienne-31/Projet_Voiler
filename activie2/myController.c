#include "stm32f10x.h"
#include "myGPIO.h"
#include "myTimer.h"
#include "myADC.h"

uint8_t UART2_Getchar(void){
	uint8_t Temp;
	while ((USART2->SR & (1<<5)) != 1 <<5);//attendre que rxne soit mis a 1 pour voir s'il est pret a recevoir 
	Temp= USART2->DR; //read data 

	USART2->SR &=  ~(1<<5);
	return Temp;
}

char toto ;

int main ( void )
{
	MyGPIO_Init ( GPIOA, 3,3);
	RCC->APB1ENR |=  RCC_APB1ENR_USART2EN ;//(1<<18);
	USART2->CR1 = 0x00; //clear all
	USART2->CR1 |= (1<<13); //UE=1 enable usart
	USART2->BRR = (227<<4) | (14<<0);// mantisse 227 et fraction 14 
	USART2->CR1 |= (1<<2); // RE=1 enable receiver 

	while (1) {
		toto=UART2_Getchar();
	}
//mettre une interruption au lieu de while pour quand on recoit un truc on le met dans data et abaisser le flag
	}
