#include "stm32f10x.h"
#include "myGPIO.h"
#include "myTimer.h"
#include "myADC.h"
#include "MySPI.h"
#define VALOUT 2

char result ;
/*
void CallBack(){
	//MyGPIO_Toggle(GPIOA,5);
	result = ConvertChannel(ADC1,3) ;
}*/

int main ( void )
{
	
	
	//char result;
	MySPI_Init(SPI1);  //Init de :la spi
	MySPI_Clear_NSS();
	MySPI_Send(0x00);
	MySPI_Set_NSS();
	MySPI_Clear_NSS();
	result= MySPI_Read();
	MySPI_Set_NSS();// pour recup id E5
	//SPI1->POWER_CTL |= (1<<3);
	//measure a 1 
/*	MySPI_Send(0x2D);
	MySPI_Send((1<<3));
	MySPI_Set_NSS();
	//X0
	while(1){
		MySPI_Clear_NSS();
		MySPI_Send(0x32);
		MySPI_Set_NSS();
		MySPI_Clear_NSS();
		result= MySPI_Read();
		MySPI_Set_NSS();
	}*/
	
/*	MyGPIO_Init(GPIOA,VALOUT,5);
	MyTimer_Base_Init(TIM2,0x6000,0x6000);
	MyTimer_Base_Start(TIM2);
	RCC->CFGR |= (10<<14);
	MyTimer_Active_IT ( TIM2 , 1,CallBack );
	MyADC_Init(ADC1,3);
	*/
	
/*	MyGPIO_Init(GPIOA,0,7);
	MyTimer_Base_Init(TIM2,0x6000,0x6000);
	MyTimer_Base_Start(TIM2);
	MyTimer_PWM(  TIM2 , 1 );
	Set_Cycle(TIM2,1,50);*/
	

				do
				{
					
				}while(1);
			}

