#include "stm32f10x.h"
#include "myADC.h"
#include "nivBatterie.h" 
#include "myTimer.h"

int res;

void callBack_Batterie(){
	//MyGPIO_Toggle(GPIOA,5);
	res = ConvertChannel(ADC1) ;
	
	//TO-DO  conversion
	
}
void niveauBatterie (void){
	//ADC : recup le niveau de la batterie   
	//Configuration du TIM2 dans main
	MyADC_Init (ADC1,10) ;	

}

