/*
 * WDGM.c
 *
 *  Created on: Jun 18, 2024
 *      Author: Amir
 */

#include "WDGM.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "timer.h"
#include "Std_types.h"


/*******************************************************************************
 *************************   Global variables Start      ***********************
 *******************************************************************************/
static vuint32_t WDGM_LEDM_CallCount = 0;
static vuint32_t last_time_checked = 0;

vuint8 WDGM_MainFunction_Stuck = 0;
volatile bool WDGM_LEDM_Alive = false;

volatile  WDGM_StatusType status = OK;
volatile  WDGM_StatusType providedStatus = OK;
/*******************************************************************************
 *************************   Global variables end      ***********************
 *******************************************************************************/

/**
 * @brief Initializes the Watchdog Manager (WDGM).
 *
 * This function initializes the variables used by the WDGM. It sets the call count to zero,
 * marks the LED Manager as not alive, sets the status to OK, and records the current time.
 *
 * @return None
 */
void WDGM_Init(void) {
	WDGM_LEDM_CallCount = 0;
	WDGM_LEDM_Alive = false;
	status = OK;
    last_time_checked = HAL_GetTick();
}



/**
 * @brief Main function of the Watchdog Manager (WDGM).
 *
 * This function checks the aliveness of the LED Manager. It is called periodically.
 * If the time elapsed since the last check exceeds the watchdog period, it evaluates
 * the call count of the LED Manager. If the call count is within the acceptable range,
 * it marks the status as OK and the LED Manager as alive. Otherwise, it marks the status as NOK
 * and the LED Manager as not alive. It then resets the call count and updates the last checked time.
 *
 * @return None
 */
void WDGM_MainFunction(void) {
	// The function is stuck until it end
	WDGM_MainFunction_Stuck = OK;

	// Check when the compiler execute this function
	GPIO_Write(WDGM_LED, HIGH); //Ch.4 Ocs.1
	// HAL_GetTick() -> function to get the milliseconds in the timer driver
    uint32_t currentTime = HAL_GetTick();

    if ((currentTime - last_time_checked) >= WDGM_PERIOD_MS) {
    	/**
    	 * If the number of calls is between 8 and 12 then the status is OK.
    	 */
        if (WDGM_LEDM_CallCount >= LEDM_CALLS_OK_MIN && WDGM_LEDM_CallCount <= LEDM_CALLS_OK_MAX) {
        	status = OK;
        	WDGM_LEDM_Alive = true;
        } else {
        	status = NOK;
        	WDGM_LEDM_Alive = false;
        }
        WDGM_LEDM_CallCount = 0;			// Reset the call counter
        last_time_checked = currentTime;	// update the last checked time
    }
    // the function now is not stucked
    GPIO_Write(WDGM_LED, LOW); //Ch.4 Ocs.1

    WDGM_MainFunction_Stuck = NOK;
}



/**
 * @brief Provides the supervision status of the Watchdog Manager (WDGM).
 *
 * This function checks if the LED Manager is alive and refreshes the watchdog timer
 * to avoid a system reset if the LED Manager is alive.
 *
 * @return The current status of the WDGM (OK or NOK).
 */
WDGM_StatusType WDGM_ProvideSupervisionStatus(void) {
    return status;
}


/**
 * @brief Indicates the aliveness of the LED Manager.
 *
 * This function increments the call count variable to check if it's within the acceptable range.
 * It should be called by the LED Manager to indicate that it is alive.
 *
 * @return None
 */
void WDGM_AlivenessIndication(void) {
	// increment the call count variable to check if it's between 8 and 12
	WDGM_LEDM_CallCount++;
}
