#ifndef MYCONTROLDRIVE_H
#define MYCONTROLDRIVE_H
#include "stm32f10x.h"
typedef struct
{
	USART_TypeDef * Usart ;

} MyUsart_Struct_TypeDef ;

void MyUsart_Base_Init ( USART_TypeDef*Usart) ;
void MyUsart_Active_IT ( USART_TypeDef*Usart , char Prio,void(*Fonction_IT)(void) );

#endif
