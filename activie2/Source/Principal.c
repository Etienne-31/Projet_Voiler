#include "stm32f10x.h"
#include "myADC.h" 
#include "nivBatterie.h" 
#include "Bordage.h" 
#include "OrientationVent.h" 
#include "mycontroldriver.h" 
#include "myGPIO.h" 
#include "myTimer.h"

int cpt=0;

void handler(void){
	
	bordage(); //orientation vent + bordage
	
	if (cpt == 10){ //Batterie
		callBack_Batterie();
		cpt = 0;		
	}
	
	setPuissance(); //USART
	
	cpt++; //compteur
}


int main ( void ){
	unsigned short PSC= 0;	  
	unsigned short ARR=   ((200*10^(-3))*(72*10^6)/(PSC+1))-1;   // ca c'est faux (72*1000000)/(5*(PSC+1))-1; //Periode a 200 ms ; Formule choisi avec Periode Timer = ((PSC+1)*(ARR+1))/Frequence Horloge
	// Cet ARR doit être pour l'ordonnanceur, j'ai fais en sorte qu'ici la période du timer 1 utilisé ici ai une période de 200 ms
	
	/*
	*USART
	*/
	MyUsart_Base_Init(USART3) ;
	MyUsart_Active_IT(USART3 , 1, getPuissance);
	
	/*
	* BATTERIE
	*/
	niveauBatterie();
	
	/*
	* BORDAGE
	*/
	init_bordage();
	
	/*
	* ORDRDONNANCEUR
	*/

	MyTimer_Base_Init (TIM1, ARR, PSC);
	MyTimer_Base_Start(TIM1);
	MyTimer_Active_IT(TIM1,3,handler);
	
	do {}while(1);
}
		
