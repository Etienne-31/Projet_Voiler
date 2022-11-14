#include "stm32f10x.h"
#include "U:\4 IR\ProjetVoilier\Projet_Voilier\MesDrivers\Include\nivBatterie.h"
#include "U:\4 IR\ProjetVoilier\Projet_Voilier\MesDrivers\Include\myADC.h" 

int res;

void CallBack(){
	//MyGPIO_Toggle(GPIOA,5);
	res = ConvertChannel(ADC1) ;
}
void niveau(void){
	//ADC : recup le niveau de la batterie  
	 
	MyADC_Init (ADC1,10) ;
	MyADC_Active_IT (ADC1 , 3 , CallBack) ; // Channel choisi


	

}

