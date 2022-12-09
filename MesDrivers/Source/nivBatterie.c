#include "stm32f10x.h"
#include "myADC.h"
#include "nivBatterie.h" 
#include "myTimer.h"
#include "myGPIO.h"

float res;

void callBack_Batterie(){
	//MyGPIO_Toggle(GPIOA,5);
	res = ConvertChannel(ADC1) ;
	
	//conversion?
}
void niveauBatterie (void){
	//ADC : recup le niveau de la batterie   
	//Configuration du TIM2 dans main
	MyGPIO_Init(GPIOC, 0, In_Analog);
	MyADC_Init (ADC1,10) ;	

}

