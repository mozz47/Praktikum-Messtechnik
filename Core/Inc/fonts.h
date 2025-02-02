/*!
 *
 * \file fonts.h
 * \author Pascal Gollor until 2019-04
 * \author Olivier Van den Eede(4ilo)
 * \date 2019-04-17
 *
 */


#ifndef Fonts
#define Fonts

#include "stm32f4xx_hal.h"

/*!
 * \addtogroup FGMesstechnik_Libraries
 * \{
 */

/*!
 * \defgroup Font_Library Fonts for Display Library
 * \brief    Fonts for Display Library
 * \{
 *
 */

/*!
 * \defgroup Font_Typedefs Typedefs
 * \brief    Library Typedefs
 * \{
 */

//! Font struct to handle data and size
typedef struct {
	const uint8_t FontWidth;    /*!< Font width in pixels */
	uint8_t FontHeight;   /*!< Font height in pixels */
	const uint16_t *data; /*!< Pointer to data font data array */
} FontDef;

/*!
 * \}
 */


/*!
 * \defgroup Font_Variables Exported Variables
 * \brief    Library Variables
 * \{
 */

extern FontDef Font_7x10; //!< 7x10 pixel font
extern FontDef Font_11x18; //!< 11x18 pixel font
extern FontDef Font_16x26; //!< 16x26 pixel font

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

