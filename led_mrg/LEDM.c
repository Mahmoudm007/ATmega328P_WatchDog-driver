/*
 * LEDM.c
 *
 *  Created on: Jun 20, 2024
 *      Author: Mahmoud
 */

#include "LEDM.h"

/*******************************************************************************
 *************************   Global variables Start      ***********************
 *******************************************************************************/
static uint32_t timeToggle = 0;		// Store the last toggling time from Timer1
static uint8_t togglingState = 1;	// The led current data that change every 500ms
/*******************************************************************************
 *************************   Global variables end      ***********************
 *******************************************************************************/


/**
 * @brief
 * this function call the gpio init function to configure the led as output
 * then write a high voltage on the led and turn it on and get the time of the toggling
 * */
void LEDM_Init(void)
{
	GPIO_Init();
	GPIO_Write(LED_TOGGLE_LED, togglingState);
	timeToggle = HAL_GetTick();
}

/**
 * @brief This function is to manage the led toggling calling in main function
 * and toggle the led every 500ms as required and get the current toggling led
 * from the variable current_led that changes in main.c
 */
void LEDM_Manage(void)
{
	GPIO_Write(LED_MANAGE_LED, HIGH);
	uint32_t currentTime = HAL_GetTick();
	/**
	 * the LED blinking periodicity to be 500ms for each stage
	 */
	if (currentTime - timeToggle >= 500) {
		togglingState = ~togglingState & 1;
		GPIO_Write(LED_TOGGLE_LED, togglingState);
		timeToggle = currentTime;
	}
	// Increment the call count of the main WDG
	/**
	 * @if we commenting WDGM_AlivenessIndication the WDG reset( system reset )
	 * after  ~ 114ms
	 */
	GPIO_Write(LED_MANAGE_LED, LOW);
	WDGM_AlivenessIndication();
}
