/*
 * lcd.c
 *
 *  Created on: Jun 18, 2024
 *      Author: Mahmoud
 */


#include "lcd.h"


/**
 * @brief Sends a command to the LCD.
 *
 * This function sends a command to the LCD by setting the appropriate control
 * pins and writing the command data to the LCD data port.
 *
 * @param cmnd The command to be sent to the LCD.
 * @return None
 */
void LCD_Command( unsigned char cmnd )
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */
	LCD_Port &= ~ (1<<RS);		/* RS=0, command reg. */
	LCD_Port |= (1<<EN);		/* Enable pulse */
	LCD_Port &= ~ (1<<EN);
	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);  /* sending lower nibble */
	LCD_Port |= (1<<EN);
	LCD_Port &= ~ (1<<EN);
}


/**
 * @brief Displays a character on the LCD.
 *
 * This function sends a character to the LCD for display by setting the
 * appropriate control pins and writing the character data to the LCD data port.
 *
 * @param data The character to be displayed on the LCD.
 * @return None
 */
void LCD_Char( unsigned char data )
{
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
	LCD_Port |= (1<<RS);		/* RS=1, data reg. */
	LCD_Port|= (1<<EN);
	LCD_Port &= ~ (1<<EN);
	LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
	LCD_Port |= (1<<EN);
	LCD_Port &= ~ (1<<EN);
}


/**
 * @brief Initializes the LCD.
 *
 * This function initializes the LCD by configuring the necessary GPIO pins
 * and sending the initialization commands to the LCD.
 *
 * @return None
 */
void LCD_Init (void)				/* LCD Initialize function */
{
	LCD_Clear();
	LCD_Dir = 0xFF;					/* Make LCD port direction as o/p */
	LCD_Command(0x02);				/* send for 4 bit initialization of LCD  */
	LCD_Command(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
	LCD_Command(0x0c);              /* Display on cursor off*/
	LCD_Command(0x06);              /* Increment cursor (shift cursor to right)*/
	LCD_Command(0x01);              /* Clear display screen*/
}


/**
 * @brief Displays a string on the LCD.
 *
 * This function displays a null-terminated string on the LCD by sending each
 * character in the string to the LCD.
 *
 * @param str The string to be displayed on the LCD.
 * @return None
 */
void LCD_String (char *str)			/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)			/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}


/**
 * @brief Displays a string on the LCD at a specific position.
 *
 * This function sets the cursor to a specific position on the LCD and then
 * displays a null-terminated string at that position.
 *
 * @param row The row number (0 or 1) where the string will be displayed.
 * @param pos The column position where the string will start.
 * @param str The string to be displayed on the LCD.
 * @return None
 */
void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);					/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);					/* Command of first row and required position<16 */
	LCD_String(str);								/* Call LCD string function */
}


/**
 * @brief Clears the LCD display.
 *
 * This function clears the LCD display by sending the appropriate command
 * to the LCD.
 *
 * @return None
 */
void LCD_Clear()
{
	LCD_Command (0x01);		/* Clear display */
	LCD_Command (0x80);		/* Cursor at home position */
}


/**
 * @brief Reverses a string in place.
 *
 * This function reverses the characters in a string in place.
 *
 * @param str The string to be reversed.
 * @param length The length of the string to be reversed.
 * @return None
 */
void reverse(char *str, uint8_t length) {
    uint8_t start = 0;
    uint8_t end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}


/**
 * @brief Converts an unsigned integer to a string with the specified base.
 *
 * This function converts an unsigned integer value to a null-terminated string
 * using the specified base.
 *
 * @param value The unsigned integer value to convert.
 * @param str The buffer where the resulting string will be stored.
 * @param base The numerical base to use for the conversion (e.g., 10 for decimal).
 * @return A pointer to the resulting null-terminated string.
 */
char* utoa(unsigned int value, char *str, int base) {
    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }

    uint8_t index = 0;
    do {
        int digit = value % base;
        str[index++] = (digit > 9) ? (digit - 10) + 'a' : digit + '0';
        value /= base;
    } while (value > 0);

    str[index] = '\0';
    reverse(str, index);
    return str;
}
