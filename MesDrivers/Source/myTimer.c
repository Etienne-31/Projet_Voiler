#define MYTIMER_H
#include "myGPIO.h"
#include "stm32f10x.h"
typedef struct
{
	TIM_TypeDef * Timer ; // TIM1 à TIM4
	unsigned short ARR ;
	unsigned short PSC ;
} MyTimer_Struct_TypeDef ;
/*
*****************************************************************************************
* @brie f
* @param -> Paramè t r e sous forme d ’ une s t r u c t u r e ( son a d re s se ) con ten an t l e s
i n f o rm a ti o n s de base
* @Note -> F onc ti on à l a n c e r s y s t ématiquement avan t d ’ a l l e r pl u s en dé t a i l dans l e s
con f pl u s f i n e s (PWM, codeur i n c . . . )
*************************************************************************************************
*/
void(*Timer1_Interrupt)(void) = 0;
void(*Timer2_Interrupt)(void) = 0;
void(*Timer3_Interrupt)(void) = 0;
void(*Timer4_Interrupt)(void) = 0;

void MyTimer_Base_Init ( TIM_TypeDef*Timer, unsigned short ARR, unsigned short PSC ) {
			if(Timer == TIM1){
			RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
		}
		else if(Timer == TIM2){
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
			
		}
		else if(Timer == TIM3){
			RCC->APB1ENR |= 1<<1; 
		}
		else if(Timer == TIM4){
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN ;
		}
		Timer->PSC = PSC;
		Timer->ARR = ARR;
}

void MyTimer_Base_Start ( TIM_TypeDef*Timer ) {
		Timer->CR1 |= TIM_CR1_CEN;
}
void MyTimer_Base_Stop (TIM_TypeDef*Timer ) {
		Timer->CR1 &= ~(TIM_CR1_CEN);
}
void MyTimer_Active_IT ( TIM_TypeDef * Timer , char Prio, void(*Fonction_IT)(void)) {
	Timer->DIER|= TIM_DIER_UIE;
	if(Timer == TIM1){
		NVIC->ISER[0]|= 1<<25;
		NVIC->IP[25] = Prio<<4;
		Timer1_Interrupt = Fonction_IT;
	} else if(Timer == TIM2){
			NVIC->ISER[0]|= 1<<28;
			NVIC->IP[28] = Prio<<4;
			Timer2_Interrupt = Fonction_IT;
	
	} else if(Timer == TIM3){
			NVIC->ISER[0]|= 1<<29;
			NVIC->IP[29] = Prio<<4;
			Timer3_Interrupt = Fonction_IT;
	}else if(Timer == TIM4){
			NVIC->ISER[0]|= 1<<30;
			NVIC->IP[30] = Prio<<4;
			Timer4_Interrupt = Fonction_IT;
	}	
}

void MyTimer_PWM( TIM_TypeDef * Timer , char Channel ){
	switch(Channel){
		case 1:
			Timer->CCMR1 |= (0x6<<4);
			Timer->CCER |= (1<<0);
			break;
		case 2:
			Timer->CCMR1 |= (0x6<<12);
			Timer->CCER |= (1<<4);
			break;
		case 3:
			Timer->CCMR2 |= (0x6<<4);
			Timer->CCER |= (1<<12);
			break;
		case 4:
			Timer->CCMR2 |= (0x6<<12);
			Timer->CCER |= (1<<16);
		  break;
	}
}
void Set_Cycle(TIM_TypeDef * Timer, char Channel, char Percent){
	uint16_t CCR = (Percent*(Timer->ARR))/100;
	switch(Channel){
		case 1:
			Timer->CCR1 = CCR;
		 	break;
		case 2:
			Timer->CCR2 = CCR;
		  break;
		case 3:
			Timer->CCR3 = CCR;
		  break;
		case 4:
			Timer->CCR4 = CCR;
		  break;
	}
}

void TIM1_UP_IRQHandler(void){
		TIM1->SR &= ~(1<<0);
		if(Timer1_Interrupt != 0){
			(*Timer1_Interrupt)();
		}

					
}  

void TIM2_IRQHandler(void){
						TIM2->SR &= ~(1<<0);
						if(Timer2_Interrupt != 0){
							(*Timer2_Interrupt)();
						}
					}				
void TIM3_IRQHandler(void){
						TIM3->SR &= ~(1<<0);
						if(Timer3_Interrupt != 0){
							(*Timer3_Interrupt)();
						}
	
					
}  
void TIM4_IRQHandler(void){
						TIM4->SR &= ~(1<<0);
						if(Timer4_Interrupt != 0){
							(*Timer4_Interrupt)();
						}
					
}  










