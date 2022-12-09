#include "stm32f10x.h"
#include "myTimer.h"
#include "myGPIO.h" 

 void orientation ( void ) {
	//Configuration du TIM3
	unsigned short PSC = 0;	  
	unsigned short ARR = 719 ; // définition de la période de l'overflow qui correspond au nombre de degré des rings
 
	MyTimer_Base_Init (TIM3, ARR, PSC);
	MyTimer_Base_Start(TIM3);
	
	//Configuration du Channel 
	TIM3->CCMR1 |= 1<<0; //config A : channel 1 , sur TI 1. PA6 
	TIM3->CCMR1 |= 1<<8; //config B : channel 2 , sur TI 2. PA7
	TIM3->SMCR  |= 1<<0; // set SMS : encodeur 2 -> que les rises
	//Enable clock
	TIM3->CCER |= (1<<0);
 
 
	// boucle sur l'index => tant qu'il est pas passe a 1 j'attends 
	MyGPIO_Init (GPIOC, 3, In_Floating);
	 
	while ( MyGPIO_Read(GPIOC,3) != 1){}
		
	TIM3->CNT = 0 ; 
 
	 
}


