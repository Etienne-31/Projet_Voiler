#include "stm32f10x.h"
#include "myGPIO.h"
#include "myTimer.h"

int main ( void ) {
	//Configuration du TIM2
	unsigned short PSC = 0;	  
	unsigned short ARR = 360 ; // définition de la période de l'overflow qui correspond au nombre de degré des rings
 
	MyTimer_Base_Init (TIM3, ARR, PSC);
	MyTimer_Base_Start(TIM3);
	
	//Configuration du Channel 
	TIM3->CCR1 = 1;
	TIM3->CCMR1 |= (2<<0); //config A : channel 1 , sur TI 1 
	TIM3->CCMR1 |= (1<<8); //config B : channel 2 , sur TI 2
	//Enable clock
	TIM3->CCER |= (1<<0);

}


