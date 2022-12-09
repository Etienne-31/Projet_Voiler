#include "stm32f10x.h"
#include "myTimer.h"
#include "OrientationVent.h" 
#include "myGPIO.h"
 
	
	float alpha;  
	float alpha1;  
	float angle_voiles;  
	float pourcentage_pwm;
	
void init_bordage() {
	//Configuration du TIM4
	unsigned short ARR=65535;	  
	unsigned short PSC= (72*1000000)/((ARR+1)*50) -1; //FREQUENCE pwm a 50Hz (20ms)
	MyTimer_Base_Init (TIM4, ARR, PSC);
	MyTimer_Base_Start(TIM4); 
	TIM4->CCER |= (1<<8);
	
	// init Orientation vent
	orientation();
}
	


void bordage(void) { 
	 
	//Configuration PWM
	MyTimer_PWM( TIM4 , 3 ); 
	MyGPIO_Init ( GPIOB , 8, AltOut_Ppull);
	
	
		alpha= TIM3->CNT;   
		alpha1= (alpha/2.);    
		if (alpha1 < 45.0 || alpha1 > 315.){
			angle_voiles = 0.0;
		}
		else if (alpha1 <= 180.){
			angle_voiles = (90.0/135.0)*(alpha1-45.0);
		}
		else {
			angle_voiles = (90.0/135.0)*(360.-alpha1-45.0);
		}
		
		pourcentage_pwm = (1.0/18.0)*angle_voiles+5.0;
		
		Set_Cycle(TIM4 ,3, (char)pourcentage_pwm);  
	
}
