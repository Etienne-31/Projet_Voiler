#include "stm32f10x.h"
#include "U:\4 IR\ProjetVoilier\Projet_Voilier\MesDrivers\Include\myTimer.h"

 void orientation ( void ) {
	//Configuration du TIM3
	unsigned short PSC = 0;	  
	unsigned short ARR = 719 ; // définition de la période de l'overflow qui correspond au nombre de degré des rings
 
	MyTimer_Base_Init (TIM3, ARR, PSC);
	MyTimer_Base_Start(TIM3);
	
	//Configuration du Channel 
	TIM3->CCMR1 |= 1<<0; //config A : channel 1 , sur TI 1. PA6 
	TIM3->CCMR1 |= 1<<8; //config B : channel 2 , sur TI 2. PA7
	TIM3->SMCR  |= 3<<0; // set SMS : both inputs set at rise
	//Enable clock
	TIM3->CCER |= (1<<0);
 
}


