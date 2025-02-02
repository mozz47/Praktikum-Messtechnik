/*!
 * \file dht11.c
 * \author Kevin Stede
 * \author Pascal Gollor
 * \date 2020-04-19
 */

#include "dht11.h"


void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Delay_us(TIM_HandleTypeDef *htimx, uint32_t time)
{
	// reset counter
	__HAL_TIM_SET_COUNTER(htimx, 0);

	while((__HAL_TIM_GET_COUNTER(htimx)) < time);
}

void dht11_StartSignal(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, TIM_HandleTypeDef *htimx)
{
	// stop timer
	HAL_TIM_Base_Stop(htimx);

	// reset timer
	HAL_TIM_Base_Init(htimx);

	// start timer
	HAL_TIM_Base_Start(htimx);

	Set_Pin_Output(GPIOx, GPIO_Pin);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, 0);
	Delay_us(htimx, 18000);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, 1);
	Set_Pin_Input(GPIOx, GPIO_Pin);
}

int8_t dht11_Reply(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, TIM_HandleTypeDef *htimx)
{
	int8_t reply = 0;
	Delay_us(htimx, 40);
	if(!(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)))
	{
		Delay_us(htimx, 80);
		if((HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)))
		{
			reply = 1;
		} else reply = -1; // Fehlerkondition
	}
	while((HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)));
	return reply;
}

uint8_t dht11_ReadData(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, TIM_HandleTypeDef *htimx)
{
	uint8_t data;
	for(int i=0; i<8; i++)
	{
		while(!(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)));
		Delay_us(htimx, 45);
		if(!(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)))
		{
			data &= ~(1<<(7-i));
		} else data |= (1<<(7-i));
		while((HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)));
	}
	return data;
}




