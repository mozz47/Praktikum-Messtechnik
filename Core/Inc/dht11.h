/*!
 * \file DHT11.h
 * \author Kevin Stede
 * \author Pascal Gollor
 * \date 2020-04-19
 */

#ifndef SRC_DHT11_H_
#define SRC_DHT11_H_


/*!
 * \addtogroup FGMesstechnik_Libraries
 * \{
 */

/*!
 * \defgroup DHT11_Library DHT11
 * \brief    Library for DHT11 1-wire temperature and humidity sensor
 * \{
 *
 * This <a href="https://extgit.mt.e-technik.uni-kassel.de/EmbeddedSystems/lib_dht11">library</a> provides functions to read out data from the DHT11 temperature and humidity sensor and is provided by <a target="_blank" rel="noopener" href="http://www.uni-kassel.de/eecs/fachgebiete/messtechnik/startseite.html">FG Messtechnik</a> for usage at the Lab C/Embedded Systems.
 *
 *	\section usage Usage
 *
 * Copy \ref dht11.c and \ref dht11.h into your `Src` and `Inc` project directory.
 * After that configure your controller.
 *
 * \attention You need a Timer for the following functions and this timer should run at 1 MHz and a high ARR entry for the \ref Delay_us() function to work.
 *
 * \subsection usage_config Configuration
 *
 * First of all we need a pin defined as GPIO_Output which is connected to the 1-wire bus.
 * In the following example the Pin was renamed to DHT11.
 * \image html pinout.png
 *
 * After that the code requires an timer with 1 MHz clock. The following tim konfiguration works with 180 MHz system clock and TIM3.
 * Other timers need a different configuration.
 * \image html timConfig.png
 *
 * \subsection usage_code Code
 *
 * Example usage with TIM3:
 *
 * *	Include in `main.c`:
\code{.c}
#include "dht11.h"
\endcode
 *
\code{.c}
dht11_StartSignal(DHT11_GPIO_Port, DHT11_Pin, &htim3); 				// Sends start signal to the sensor
// Checks sensor response  [1] = Working, [-1] = Error
if (dht11_Reply(DHT11_GPIO_Port, DHT11_Pin, &htim3) == 1)
{
	uint8_t RH_Int_Byte = dht11_ReadData(DHT11_GPIO_Port, DHT11_Pin, &htim3); 	// Saves first byte
	uint8_t RH_Dec_Byte = dht11_ReadData(DHT11_GPIO_Port, DHT11_Pin, &htim3); 	// Saves second byte
	uint8_t Temp_Int_Byte = dht11_ReadData(DHT11_GPIO_Port, DHT11_Pin, &htim3); 	// Saves third byte
	uint8_t Temp_Dec_Byte = dht11_ReadData(DHT11_GPIO_Port, DHT11_Pin, &htim3); 	// Saves fourth byte
	uint8_t Check_Byte = dht11_ReadData(DHT11_GPIO_Port, DHT11_Pin, &htim3); 	// Saves fifth byte
}
\endcode
*
* You can transmit the data over the UART and should get the following output:
* \image html uartOutput.png
*
* \par Dependencies
* \li STM32F4xx (stm32f4xx_hal.h)
* \li STM32F4xx TIM (stm32f4xx_hal_tim.h)
*
*/

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"


/*!
 * \defgroup DHT11_Functions Functions
 * \brief    Library Functions
 * \{
 */


/*!
 * \brief Sets given GPIO Pin mode to Input
 * \param GPIOx GPIO Port
 * \param GPIO_Pin GPIO Pin
 */
void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);


/*!
 * \brief Sets given GPIO Pin mode to Output
 * \param GPIOx GPIO Port
 * \param GPIO_Pin GPIO Pin
 */
void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);



/*!
 * \brief Wait for given microseconds
 * \param htimx TIM Handle
 * \param time Wait time in microseconds
 */
void Delay_us(TIM_HandleTypeDef *htimx, uint32_t time);


/*!
 * \brief Sends the start signal to the Sensor:
 * \param GPIOx GPIO Port
 * \param GPIO_Pin GPIO Pin
 * \param htimx TIM Handle
 *
 * \li Sets GPIO Pin as Output
 * \li Pull data bus to Low for 18ms
 * \li Sets data bus back to High
 * \li Sets GPIO Pin as Input to check the sensor response
 */
void dht11_StartSignal(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, TIM_HandleTypeDef *htimx);


/*!
 * \brief Checks the sensor response
 * \param GPIOx GPIO Port
 * \param GPIO_Pin GPIO Pin
 * \param htimx TIM Handle
 * \retval 1 if sensor is working, -1 when an error occurs
 *
 * \li Waits 40us and checks if data bus is at Low
 * \li Waits 80us and checks if data bus is at High
 * \li Returns 1 if sensor is working, -1 when an error occurs
 */
int8_t dht11_Reply(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, TIM_HandleTypeDef *htimx);


/*!
 * \brief read one byte from sensors
 * \param GPIOx GPIO Port
 * \param GPIO_Pin GPIO Pin
 * \param htimx TIM Handle
 * \retval received byte
 */
uint8_t dht11_ReadData(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, TIM_HandleTypeDef *htimx);


/*!
 * \}
 */

/*!
 * \}
 */

/*!
 * \}
 */



#endif /* SRC_DHT11_H_ */
