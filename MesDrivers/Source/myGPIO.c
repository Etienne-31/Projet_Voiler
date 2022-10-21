#define MYGPIO_H
#include "stm32f10x.h"




void MyGPIO_Init ( GPIO_TypeDef * GPIO, char GPIO_Pin, char GPIO_Conf){
		char conf_hexa;
		
		if(GPIO == GPIOA){
			RCC->APB2ENR |= (0x1 << 2);
		}
		else if(GPIO == GPIOB){
			RCC->APB2ENR |= (0x1 << 3);
		}
		else if(GPIO == GPIOC){
			RCC->APB2ENR |= (0x1 << 4);
		}
		else if(GPIO == GPIOD){
			RCC->APB2ENR |= (0x1 << 5);
		}
	
	
		switch(GPIO_Conf){
			case 1 : 
				{conf_hexa = 0x4;break;}
			case 2 :  
				conf_hexa = 0x8;
				break;
			case 3 : 
				conf_hexa = 0x8;
			  break;
			case 4 :  
				conf_hexa = 0x0;
				break;
			case 5 : 
				conf_hexa = 0x1;
				break;
			case 6 :  
				conf_hexa = 0x6;
				break;
			case 7 : 
				{conf_hexa = 0xb;break;}
			case 8 :  
				conf_hexa = 0x8;
				break;
			
		}
		if(GPIO_Pin<8){
			GPIO->CRL &=  ~(0xF<<GPIO_Pin*4);
			GPIO->CRL |= (conf_hexa<<GPIO_Pin*4);
		}
		else{
			GPIO->CRH &=  ~(0xF<<GPIO_Pin*4);
			GPIO->CRH |= (conf_hexa<<GPIO_Pin*4);
		}
		if(conf_hexa ==  2){
			GPIO->ODR &= ~(0x1<< GPIO_Pin);
		}
		else if(conf_hexa == 3) {
			GPIO->ODR |= (0x1<< GPIO_Pin);
		}	
	return;
}



int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	return ((GPIO->IDR & (0x01<<GPIO_Pin))== 0 );
}


void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	GPIO->BSRR = (1<<GPIO_Pin); 
	return;
}

void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	GPIO->BRR = (1<<GPIO_Pin); 
	return;
}

void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	if (MyGPIO_Read(GPIO, GPIO_Pin)!=0) {
		MyGPIO_Set(GPIO,GPIO_Pin);
	} else {
		MyGPIO_Reset(GPIO,GPIO_Pin);
	}
	
}
