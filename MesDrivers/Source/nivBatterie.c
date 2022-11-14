#include "stm32f10x.h"
#include "myADC.h"
#include "nivBatterie.h"

int res;

void CallBack(){
	//MyGPIO_Toggle(GPIOA,5);
	res = ConvertChannel(ADC1) ;
}
void niveauBatterie(void){
	//ADC : recup le niveau de la batterie  
	 
	MyADC_Init (ADC1,10) ;
	MyADC_Active_IT (ADC1 , 3 , CallBack) ; // Channel choisi


	

}

