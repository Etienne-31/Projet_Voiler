#include "stm32f10x.h"
#include "myGPIO.h"
#include "myTimer.h"
#include "myADC.h"
#define VALOUT 2

int result ;

void CallBack(){
	//MyGPIO_Toggle(GPIOA,5);
	result = ConvertChannel(ADC1,3) ;
}
/*
int main ( void )
{

	MyGPIO_Init(GPIOA,VALOUT,5);
	MyTimer_Base_Init(TIM2,0x6000,0x6000);
	MyTimer_Base_Start(TIM2);
	RCC->CFGR |= (10<<14);
	MyTimer_Active_IT ( TIM2 , 1,CallBack );
	MyADC_Init(ADC1,3);
	
	

MyGPIO_Init(GPIOA,0,7);
	MyTimer_Base_Init(TIM2,0x6000,0x6000);
	MyTimer_Base_Start(TIM2);
	MyTimer_PWM(  TIM2 , 1 );
	Set_Cycle(TIM2,1,50);
	

				do
				{
					
				}while(1);
			}

*/
