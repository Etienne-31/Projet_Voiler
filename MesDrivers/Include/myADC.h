#ifndef MYADC_H
#define MYADC_H
#include "stm32f10x.h"
void MyADC_Init (ADC_TypeDef *ADC, char channel) ;
void MyADC_Active_IT (ADC_TypeDef *ADC , char Prio, void(*Fonction_IT)(void)) ;
int ConvertChannel(ADC_TypeDef *ADC, char channel) ;
#endif