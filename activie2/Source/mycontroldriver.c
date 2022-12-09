#define MYCONTROLDRIVER_H
#include "stm32f10x.h"
#include "myGPIO.h" 
#include "myTimer.h"
#include <stdio.h>
#include <stdlib.h>

signed char puissance;

void(*Usart1_Interrupt)(void) = 0;
void(*Usart3_Interrupt)(void) = 0;

void MyUsart_Base_Init ( USART_TypeDef*Usart) {
	MyGPIO_Init(GPIOB, 11,1);//  USART  input pull up // Pourquoi cette pin la ?
	if (Usart==USART3){
		RCC->APB1ENR |=  RCC_APB1ENR_USART3EN ;//(1<<18);
		USART3->CR1 = 0x00; // On reset tous les bit de CR1 à 0 pour "réinitialier" le registre
		USART3->CR1 |= (1<<13); //UE=1 ENABLE l'USART via le 13eme bit du registre CR1
		USART3->BRR = (234<<4) + (6<<0);// mantisse 234 et fraction 6 -> 9600 = ( 36MHz ) / ( 16* Mantisse ) -> Mantisse = (36 000 000)/(9600*16) = 234.375 -> x/16 = 0.375 -> x = 6 
		USART3->CR1 |= (1<<2); // RE=1 on ENABLE la reception de l'USART qui commence alors à chercher un bit de commencement
	} else if (Usart==USART1){
		RCC->APB1ENR |=  RCC_APB2ENR_USART1EN ;//(1<<18);
		USART1->CR1 = 0x00; //clear all
		USART1->CR1 |= (1<<13); //UE=1 enable usart
		USART1->BRR = (227<<4) | (14<<0);// mantisse 227 et fraction 14 
		USART1->CR1 |= (1<<2); // RE=1 enable receiver 
	}
	
	//init gpio sens 
	MyGPIO_Init (GPIOA, 8, Out_Ppull);//output bit sens
	//init moteur plateau
	MyGPIO_Init (GPIOA, 0, AltOut_Ppull); //pour la pwm du t cycle psc de la pwm  // Cette pin à cause du re mappig ?
	
}

void MyUsart_Active_IT ( USART_TypeDef*Usart , char Prio,void(*Fonction_IT)(void) ){
	unsigned short PSC = 0;	  
	unsigned short ARR = (72*10)/(PSC+1)-1; //FREQUENCE a 20kHZ
	MyTimer_Base_Init (TIM2, ARR, PSC);
	MyTimer_Base_Start(TIM2);
	MyTimer_PWM( TIM2, 1 );
	
	
	Usart->CR1 |= 1<<5 ;
	if (Usart==USART3){
		NVIC->ISER[1]|= 1<<7;             // On active l'interruption au niveau du registre ISER 
		NVIC->IP[39] = Prio<<4;          // On donne la prio voulu pour l'interruption de l'USART (39eme sur le tableau NVIC )
		Usart3_Interrupt = Fonction_IT;   // On donne la Fonction à executer par le handler en cas de l'interruption
	} else if (Usart==USART1){
		NVIC->ISER[1]|= 1<<5;
		NVIC->IP[37] = Prio<<4;
		Usart1_Interrupt = Fonction_IT;
	}
}


void USART1_IRQHandler (void){
	USART1->SR &=  ~(1<<5);
	if(Usart1_Interrupt != 0){
		(*Usart1_Interrupt)();
	}
}
void USART3_IRQHandler (void){
	USART3->SR &=  ~(1<<5);
	if(Usart3_Interrupt != 0){
		(*Usart3_Interrupt)();
	}
}

void getPuissance(){ // Renomer en fonction lire USART  DATA REGISTER 
	puissance = USART3->DR; //read data contiens le pourcentage de puissance pour faire tourner le bateau via la pwm
}

void setPuissance () {
	if(puissance<0){//sens du plateau
			Set_Cycle(TIM2,1,abs(puissance) ); // On change ce bit pour connaitre le sens de rotation
			MyGPIO_Set(GPIOA,8);
	}else {
			Set_Cycle(TIM2,1,puissance );
			MyGPIO_Reset(GPIOA,8);
	}
	
}
