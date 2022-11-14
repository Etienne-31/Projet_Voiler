#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"


	typedef struct{
		GPIO_TypeDef * GPIO ;
		char GPIO_Pin ; //numero de 0 a 15
		char GPIO_Conf ; // voir ci dessous
	} MyGPIO_Struct_TypeDef;
	
#define In_Floating 0x4 
#define In_PullDown 0x8
#define In_PullUp 0x8 
#define In_Analog 0x0
#define Out_Ppull 0x2
#define Out_OD 0x6 
#define AltOut_Ppull 0xA
#define AltOut_OD 0xD
	
#define In_Floating_Nb 1
#define In_PullDown_Nb 2
#define In_PullUp_Nb 3
#define In_Analog_Nb 4
#define Out_Ppull_Nb 5
#define Out_OD_Nb 6
#define AltOut_Ppull_Nb 7
#define AltOut_OD_Nb 8

	
void MyGPIO_Init (GPIO_TypeDef * GPIO, char GPIO_Pin, char GPIO_Conf) ;
int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ; // renvoie 0 ou autre chose different de 0
void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
#endif
