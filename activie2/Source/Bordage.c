#include "stm32f10x.h"
#include "U:\4 IR\ProjetVoilier\Projet_Voilier\MesDrivers\Include\myTimer.h"
#include "U:\4 IR\ProjetVoilier\Projet_Voilier\MesDrivers\Include\OrientationVent.h" 
#include "U:\4 IR\ProjetVoilier\Projet_Voilier\MesDrivers\Include\myGPIO.h"
 
	
	int alpha;  
	int alpha1;  
	int angle_voiles; 
	
int main ( void ) { 
	//Configuration du TIM2 
	unsigned short ARR=65535;	  
	unsigned short PSC= (72*1000000)/((ARR+1)*50) -1; //FREQUENCE pwm a 50Hz (20ms)
	MyTimer_Base_Init (TIM4, ARR, PSC);
	MyTimer_Base_Start(TIM4); 
	TIM4->CCER |= (1<<8);
	 
	// init Orientation vent
	 orientation();
	 
	 
	//Configuration PWM
	MyTimer_PWM( TIM4 , 3 ); 
	MyGPIO_Init ( GPIOB , 8, AltOut_Ppull);
	 
	while(1) {
		alpha= TIM3->CNT;   
		alpha1= alpha%180;  
		if ((alpha1 >=0) && (alpha1 <45)) { 
			angle_voiles=5;
		} else { 
			angle_voiles= alpha1*0.037+3.34;
		}
		Set_Cycle(TIM4 ,3, (char)angle_voiles);  
	}
}
