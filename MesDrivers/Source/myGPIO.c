#include "stm32f10x.h" 
#include "myGPIO.h"





void MyGPIO_Init ( GPIO_TypeDef * GPIO, char GPIO_Pin, char GPIO_Conf){

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

	if ( GPIO_Pin<8) {  
		GPIO->CRL &= ~(0xF << (4*  GPIO_Pin));   
		GPIO->CRL |=   GPIO_Conf << (4*  GPIO_Pin) ;

	} else if ( GPIO_Pin<15) { 
		GPIO->CRH &= ~(0xF << (4* ( GPIO_Pin-8)));   
		GPIO->CRH |=   GPIO_Conf << (4* ( GPIO_Pin-8)) ;
	}  else { 

	}

	if (GPIO_Conf == In_PullDown) {
		GPIOC->ODR &=   ~(1 << GPIO_Pin);
	} else if (GPIO_Conf == In_PullUp) {
		GPIOC->ODR |=  0x1 << GPIO_Pin ;
	} 
}



int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	return ((GPIO->IDR & (0x01<<GPIO_Pin))== 0 );
}


void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	GPIO->BSRR = (1<<GPIO_Pin); 
}

void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	GPIO->BRR = (1<<GPIO_Pin); 
}

void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	if (MyGPIO_Read(GPIO, GPIO_Pin)!=0) {
		MyGPIO_Set(GPIO,GPIO_Pin);
	} else {
		MyGPIO_Reset(GPIO,GPIO_Pin);
	}
	
}
