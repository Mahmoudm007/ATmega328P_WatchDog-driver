#ifndef LEDM_H
#define LEDM_H

/*******************************************************************************
 ******************************   includes Start    ****************************
 *******************************************************************************/
#include "Std_types.h"
#include <util/delay.h>
#include "timer.h"
#include "WDGM.h"
#include <avr/io.h>
#include "GPIO.h"

/*******************************************************************************
 ******************************   includes end    ****************************
 *******************************************************************************/



/*******************************************************************************
 ******************************   Macros Start      ****************************
 *******************************************************************************/
// Define LED-related macros with specific register addresses
#define LED_Dir  (*(volatile uint8_t *)(GPIOB_BASE_ADDR - GPIO_DDR_OFFSET))  /* Define LED port direction */
#define LED_Port (*(volatile uint8_t *)(GPIOB_BASE_ADDR))                    /* Define LED port */

/*******************************************************************************
 ******************************   Macros end        ****************************
 *******************************************************************************/


/*******************************************************************************
 *************************   Functions prototype start   ***********************
 *******************************************************************************/

/**
 * @brief Initializes the LED manager module.
 * This function initializes the GPIO module and sets the initial state of the LED.
 * It also records the initial time for toggling the LED.
 */
void LEDM_Init(void);

/**
 * @brief This function is to manage the led toggling calling in main function
 * and toggle the led every 500ms as required and get the current toggling led
 * from the variable current_led that changes in main.c
 */
void LEDM_Manage(void);
/*******************************************************************************
 *************************   Functions prototype start   ***********************
 *******************************************************************************/

#endif
