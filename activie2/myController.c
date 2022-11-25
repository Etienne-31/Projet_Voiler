#include "stm32f10x.h"
#include "myGPIO.h"
#include "myTimer.h"
#include "myADC.h"
#include "mycontroldriver.h"
#include <stdio.h>
#include <stdlib.h>


signed char temp;

void flag(){ // Renomer en fonction lire USART  DATA REGISTER  
	temp= USART3->DR; //read data contiens le pourcentage de puissance pour faire tourner le bateau via la pwm

	if(temp<0){//sens du plateau
			Set_Cycle(TIM2,1,abs(temp) ); // On change ce bit pour connaitre le sens de rotation
			MyGPIO_Set(GPIOA,8);
	}else {
			Set_Cycle(TIM2,1,temp );
			MyGPIO_Reset(GPIOA,8);
	}
	
}



//char toto ;

int main ( void )
{
	//init usart
	MyGPIO_Init ( GPIOB, 11,1);//  USART  input pull up
	MyUsart_Base_Init (USART3) ;
	//init gpio sens 
	MyGPIO_Init (GPIOA, 8, 5);//output bit sens
	//init moteur plateau
	MyGPIO_Init (GPIOA, 0, 7); //pour la pwm dutycycle psc de la pwm  // Cette pin à cause du re mappig ?
	MyTimer_Base_Init ( TIM2, 3599,0);//20khz  //Quelle calcul ? 
	MyTimer_Base_Start ( TIM2);
	MyTimer_PWM( TIM2, 1 );
	MyUsart_Active_IT ( USART3 , 1,flag );
	
		do
				{
					
				}while(1);
			}
		

	