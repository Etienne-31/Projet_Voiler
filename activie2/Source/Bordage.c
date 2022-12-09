#include "stm32f10x.h"
#include "myTimer.h"
#include "OrientationVent.h" 
#include "myGPIO.h"
 
	
	int alpha;  
	int alpha1;  
	int angle_voiles; 
	
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
	
	
	while(1) {
		alpha= TIM3->CNT;   
		alpha1= (alpha/2);  
		if ((alpha1 <45) || ((alpha1 >(180-45))&& (alpha1< (180+45))) || (alpha1>315))  { 
			angle_voiles=5;
		} else { 
			angle_voiles= alpha1*0.037+3.34;
		}
		Set_Cycle(TIM4 ,3, (char)angle_voiles);  
	}
}
