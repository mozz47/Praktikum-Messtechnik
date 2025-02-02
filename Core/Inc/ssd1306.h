/*!
 *
 * \file ssd1306.h
 * \author Pascal Gollor until 2019-04
 * \author Olivier Van den Eede(4ilo)
 * \date 2019-04-17
 *
 */

#ifndef ssd1306
#define ssd1306

/*!
 * \addtogroup FGMesstechnik_Libraries
 * \{
 */

/*!
 * \defgroup SSD1306_Library SSD1306
 * \brief    Library for OLED display SSD1306 via I2C
 * \{
 *
 * SSD1306 OLED I2C Display Library
 *
 * This library provide functions to fill the SSD1306 OLED Display and will be <a href="https://git.mt.e-technik.uni-kassel.de:1337/EmbeddedSystems/lib_ssd1306">provided</a> by <a target="_blank" rel="noopener" href="http://www.uni-kassel.de/eecs/fachgebiete/messtechnik/startseite.html">FG Messtechnik</a> for usage at the Lab C/Embedded System.
 *
 *	\section usage Usage
 *
 *	Include in `main.c`:
\code{.c}
#include "ssd1306.h"
#include "fonts.h"
\endcode
 *
 * Example usage:
\code{.c}
ssd1306_Init(&hi2c1);
ssd1306_Fill(DISPLAY_COLOR_DARK);
ssd1306_SetCursor(0,0);
ssd1306_WriteString("Display", Font_11x18, DISPLAY_COLOR_LIGHT);
ssd1306_SetCursor(0,20);
ssd1306_WriteString("FG Messtechnik", Font_7x10, DISPLAY_COLOR_LIGHT);
ssd1306_SetCursor(0,32);
ssd1306_WriteString("0123456789", Font_16x26, DISPLAY_COLOR_LIGHT);
ssd1306_UpdateScreen();
\endcode
 *
 * \section fonts Fonts
 * There are 3 different fonts you can use:
 * \li \link Font_7x10 \endlink
 * \li \link Font_11x18 \endlink
 * \li \link Font_16x26 \endlink
 *
 *
 * \par Dependencies
 * \li STM32F4xx (stm32f4xx_hal.h)
 * \li STM32F4xx I2C HAL (stm32f4xx_hal_i2c.h)
 * \li fonts.h
 *
*/


#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include "fonts.h"


/*!
 * \defgroup SSD1306_definitions Definitions
 * \brief    Library definitions and enumerates
 * \{
 */

//! I2C address
#define SSD1306_I2C_ADDR        0x78

//! SSD1306 width in pixels
#define SSD1306_WIDTH           128

//! SSD1306 LCD height in pixels
#define SSD1306_HEIGHT          64

//! Display color
typedef enum {
	DISPLAY_COLOR_DARK = 0x00, //!< Black color, no pixel
	DISPLAY_COLOR_LIGHT = 0x01 //!< Pixel is set. Color depends on LCD
} SSD1306_COLOR;

/*!
 * \}
 */



/*!
 * \defgroup SSD1306_Typedefs Typedefs
 * \brief    Library Typedefs
 * \{
 */

//! Library internal struct
typedef struct {
	uint16_t CurrentX; //!< current x position
	uint16_t CurrentY; //!< current y position
	uint8_t Inverted; //!< inverted color flag
	uint8_t Initialized; //!< initialized flag
} SSD1306_t;

/*!
 * \}
 */


/*!
 * \defgroup SSD1306_Functions Functions
 * \brief    Library Functions
 * \{
 */

/*!
 * \brief Initialize the Display
 * \param[in] hi2c HAL I2C Handle
 */
void ssd1306_Init(I2C_HandleTypeDef* hi2c);

/*!
 * \brief Fill hole Display with given color
 * \param[in] color Color from type \ref SSD1306_COLOR
 */
void ssd1306_Fill(SSD1306_COLOR color);

/*!
 * \brief Fill library buffer from external to print an image or so
 * \param[in] data Buffer address with size \ref SSD1306_WIDTH * \ref SSD1306_HEIGHT / 8
 */
void ssd1306_FillBuffer(uint8_t *data);

/*!
 * \brief Update display screen (write Buffer to display)
 */
void ssd1306_UpdateScreen(void);

/*!
 * \brief Draw Pixel on position
 * \param[in] x x coordinate start by 0
 * \param[in] y y coordinate start by 0
 * \param[in] color Color from \ref SSD1306_COLOR
 */
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);

/*!
 * \brief Write one char at current cursor position
 * \param[in] ch Char to write
 * \param[in] Font Font Size \link Font_7x10 \endlink , \link Font_11x18 \endlink or \link Font_16x26 \endlink
 * \param[in] color Color from type \ref SSD1306_COLOR
 * \return 0 for fault and written char for validation on success
 */
char ssd1306_WriteChar(char ch, FontDef Font, SSD1306_COLOR color);

/*!
 * \brief Write string at current cursor position
 * \param[in] str String to write
 * \param[in] Font Font Size \link Font_7x10 \endlink , \link Font_11x18 \endlink or \link Font_16x26 \endlink
 * \param[in] color Color from type \ref SSD1306_COLOR
 * \return current char pointer
 */
char ssd1306_WriteString(char* str, FontDef Font, SSD1306_COLOR color);

/*!
 * \brief Set cursor positions
 * \param[in] x x coordinate start by 0
 * \param[in] y y coordinate start by 0
 */
void ssd1306_SetCursor(uint8_t x, uint8_t y);


/*!
 * \brief Clear one Displayline from y until y + vertival fontsize
 * \param[in] y Line start point
 * \param[in] Font Font Size \ref Font_7x10 , \ref Font_11x18 or \ref Font_16x26
 * \param[in] color Color to fill with from type \ref SSD1306_COLOR
 *
 * Cursor is automatically set to (0, y) at start and end.
 */
void ssd1306_ClearLine(uint8_t y, FontDef Font, SSD1306_COLOR color);

/*!
 * \}
 */

/*!
 * \}
 */

/*!
 * \}
 */



#endif
