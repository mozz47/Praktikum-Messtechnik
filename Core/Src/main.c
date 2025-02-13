/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dht11.h"
#include "ssd1306.h"
#include "fonts.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int timercounter4;
char integer_buffer_hum[4];
char decimal_buffer_hum[3];
char integer_buffer_tem[4];
char decimal_buffer_tem[3];
char checksum_buffer[2];
float voltage;
int BUFFER_SIZE=10;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM12_Init();
  MX_DMA_Init();
  MX_DAC_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim4);
  HAL_TIM_Base_Start_IT(&htim12);
  //display init
  HAL_TIM_Base_Start_IT(&htim2);
  ssd1306_Init(&hi2c1);
  HAL_ADC_Start_IT(&hadc1);

  ssd1306_Fill(DISPLAY_COLOR_DARK);
  HAL_GPIO_TogglePin(LD2_GPIO_Port , LD2_Pin);
  ssd1306_SetCursor(0,30);
  ssd1306_WriteString("Herz: 10", Font_7x10, DISPLAY_COLOR_LIGHT);


  //DAC init
  const uint16_t aSine12bit_Buffer[2] = {
                        2047, 2447};

  HAL_DAC_Start_DMA( &hdac, DAC_CHANNEL_1,(uint32_t*)aSine12bit_Buffer, 2, DAC_ALIGN_12B_R);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */
	  test();
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLRCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void UART_Output(void){
	     //Output per UART
	  	 // Termparatur UART
		 HAL_UART_Transmit(&huart2,"Temperatur: ",13,HAL_MAX_DELAY);
		 HAL_UART_Transmit(&huart2,&integer_buffer_tem,2,HAL_MAX_DELAY);
		 HAL_UART_Transmit(&huart2,".",1,HAL_MAX_DELAY);
		 HAL_UART_Transmit(&huart2,&decimal_buffer_tem,2,HAL_MAX_DELAY);
		 HAL_UART_Transmit(&huart2,"'C \n",4,HAL_MAX_DELAY);

		 // Humidity UART
		 HAL_UART_Transmit(&huart2,"Humidity: ",13,HAL_MAX_DELAY);
		 HAL_UART_Transmit(&huart2,&integer_buffer_hum,2,HAL_MAX_DELAY);
		 HAL_UART_Transmit(&huart2,".",1,HAL_MAX_DELAY);
		 HAL_UART_Transmit(&huart2,&decimal_buffer_hum,2,HAL_MAX_DELAY);
		 HAL_UART_Transmit(&huart2,"% \n",3,HAL_MAX_DELAY);

		 // Checksum UART

		 HAL_UART_Transmit(&huart2,"Checksum: ",10,HAL_MAX_DELAY);
		 HAL_UART_Transmit(&huart2,&checksum_buffer,2,HAL_MAX_DELAY);
}


void Display_Output(void){

    //Temperatur Display
	  ssd1306_SetCursor(0,0);
	  ssd1306_WriteString("Temparatur: ", Font_7x10, DISPLAY_COLOR_LIGHT);
	  ssd1306_WriteString(&integer_buffer_tem, Font_7x10, DISPLAY_COLOR_LIGHT);
	  ssd1306_WriteString(".", Font_7x10, DISPLAY_COLOR_LIGHT);
	  ssd1306_WriteString(&decimal_buffer_tem, Font_7x10, DISPLAY_COLOR_LIGHT);
	  ssd1306_WriteString("'C", Font_7x10, DISPLAY_COLOR_LIGHT);

	  //Humudity Display
	  ssd1306_SetCursor(0,15);
	  ssd1306_WriteString("Humidity: ", Font_7x10, DISPLAY_COLOR_LIGHT);
	  ssd1306_WriteString(&integer_buffer_hum, Font_7x10, DISPLAY_COLOR_LIGHT);
	  ssd1306_WriteString(".", Font_7x10, DISPLAY_COLOR_LIGHT);
	  ssd1306_WriteString(&decimal_buffer_hum, Font_7x10, DISPLAY_COLOR_LIGHT);
	  ssd1306_WriteString("%", Font_7x10, DISPLAY_COLOR_LIGHT);


	  ssd1306_UpdateScreen();
}

void Read_Data(void) {
	 dht11_StartSignal(DHT11_GPIO_Port, DHT11_Pin, &htim3);
		 /** start timer*/
		 if (dht11_Reply(DHT11_GPIO_Port, DHT11_Pin, &htim3) == 1) {
			 uint8_t RH_Int_Byte = dht11_ReadData(DHT11_GPIO_Port, DHT11_Pin, &htim3);   // Saves first byte
			 uint8_t RH_Dec_Byte = dht11_ReadData(DHT11_GPIO_Port, DHT11_Pin, &htim3);   // Saves second byte
			 uint8_t Temp_Int_Byte = dht11_ReadData(DHT11_GPIO_Port, DHT11_Pin, &htim3);   // Saves third byte
			 uint8_t Temp_Dec_Byte = dht11_ReadData(DHT11_GPIO_Port, DHT11_Pin, &htim3);   // Saves fourth byte
			 uint8_t Check_Byte = dht11_ReadData(DHT11_GPIO_Port, DHT11_Pin, &htim3);  // Saves fifth byte

			 itoa(RH_Int_Byte,&integer_buffer_hum,10);
			 itoa(RH_Dec_Byte,&decimal_buffer_hum,10);
			 // Temparatur buffer
			 itoa(Temp_Dec_Byte,&decimal_buffer_tem,10);
			 itoa(Temp_Int_Byte,&integer_buffer_tem,10);
			 // Checksum buffer
			 itoa(Check_Byte,&checksum_buffer,10);
		 }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	//Beim drücken Wert des Timers auslesen

	timercounter4 = __HAL_TIM_GET_COUNTER(&htim4);

	//Wenn Timer zu groß wieder runtersetzen
	if (timercounter4 > 30) {
		__HAL_TIM_SET_COUNTER(&htim4, 30);
		timercounter4 = 30;
	}

	//HAL_UART_Transmit(&huart2, &timercounter4, 1, HAL_MAX_DELAY);

	//HERZFREQUENZ SETZEN
	int hz = (int)1000/timercounter4;
	HAL_TIM_Base_Stop_IT(&htim12);
	__HAL_TIM_SET_AUTORELOAD(&htim12, hz/2);
	__HAL_TIM_SET_COUNTER(&htim12, 0);
	HAL_TIM_Base_Start_IT(&htim12);

	//Danach Screen updaten
	ssd1306_SetCursor(0,30);
	char hertz_buffer[20];
	int n = sprintf(hertz_buffer, "Hertz: %d " , timercounter4);
	ssd1306_WriteString(&hertz_buffer, Font_7x10, DISPLAY_COLOR_LIGHT);
	ssd1306_UpdateScreen;
}
void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef *hdac){
	HAL_DAC_SetValue(hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,(int)voltage);
}

void ADC_DAC_Output(void){
	//ADC



	uint32_t adc = HAL_ADC_GetValue(&hadc1);
	if (adc > 4095) {
			adc = 4095;
		}
	voltage = ((3.3)/(4095)) * (int) adc;
	uint32_t  voltageArray[1];
	voltageArray[0] = 1000;



	int integer_wert = (int) voltage;
	int deci_wert = (voltage - integer_wert)*100;
	char ausgabe[20];
	itoa(deci_wert, &ausgabe,10);
	int z = sprintf(ausgabe, "%d,%d", integer_wert, deci_wert);
	ssd1306_SetCursor(0,45);
	ssd1306_WriteString("Voltage: ", Font_7x10, DISPLAY_COLOR_LIGHT);
	ssd1306_WriteString(&ausgabe, Font_7x10, DISPLAY_COLOR_LIGHT);
	ssd1306_UpdateScreen();

	//DAC




}
void test() {
	uint32_t adc = HAL_ADC_GetValue(&hadc1);
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,adc);
	HAL_DAC_Start_DMA( &hdac, DAC_CHANNEL_1, 1, DAC_ALIGN_12B_R);

}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
