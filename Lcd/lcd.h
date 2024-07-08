/*
 * lcd.h
 *
 *  Created on: Jun 18, 2024
 *      Author: Mahmoud
 */

#ifndef LCD_H_
#define LCD_H_


/*******************************************************************************
 ******************************   Macros Start      ****************************
 *******************************************************************************/
#include "Bit_Operations.h"
#include "gpio.h"

// Define LCD-related macros with specific register addresses
#define LCD_Dir  (*(volatile uint8_t *)(GPIOD_BASE_ADDR - GPIO_DDR_OFFSET))  /* Define LCD data port direction */
#define LCD_Port (*(volatile uint8_t *)(GPIOD_BASE_ADDR))                    /* Define LCD data port */
#define RS 2                                                                  /* Define Register Select pin */
#define EN 3                                                                  /* Define Register Enable pin */
/*******************************************************************************
 ******************************   Macros End        ****************************
 *******************************************************************************/


/*******************************************************************************
 ******************************   Function Prototype Start      ****************
 *******************************************************************************/
void LCD_Command( unsigned char cmnd );
void LCD_Char( unsigned char data );
void LCD_Init (void);
void LCD_String (char *str);
void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear();

char* utoa(unsigned int value, char *str, int base);
void reverse(char *str, uint8_t length);
/*******************************************************************************
 ******************************   Function Prototype End        ****************
 *******************************************************************************/


#endif /* LCD_H_ */
