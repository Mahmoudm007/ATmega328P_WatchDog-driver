/*
 * main.c
 *
 *  Created on: Jun 18, 2024
 *      Author: Mahmoud
 */
/*******************************************************************************
 ******************************   includes Start    ****************************
 *******************************************************************************/
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "GPIO.h"			/* General Purpose Input Output driver*/
#include "LEDM.h"			/* Light Emitting Diode driver*/
#include "timer.h" 			/* Timer API */
#include "WDGDRV.h"			/* Watchdog API */
#include "WDGM.h"			/* Watchdog API manager */
#include "lcd.h"			/* Liquid Crystal Display driver*/
#include "Bit_Operations.h"	/* Bit Masking Operations */
#include "Std_types.h"		/* Standard Types file*/
#include "Utils.h"			/* Utils file*/
#include "buzzer.h"			/* Buzzer and Speaker driver*/
#include "Exti.h"			/* Eternal Interrupt driver*/
#include "gicr.h"			/* General Interrupt Control Register driver */
/*******************************************************************************
 ******************************   includes End      ****************************
 *******************************************************************************/


/*******************************************************************************
 *************************   Global variables Start      ***********************
 *******************************************************************************/
static vuint32_t checkLedTime = 0;
static vuint32_t checkWDGTime = 0;

char resetTimes[10];
uint8 resets = 0;
/*******************************************************************************
 *************************   Global variables end      ***********************
 *******************************************************************************/

/*******************************************************************************
 *******************************   Main start    *******************************
 *******************************************************************************/
int main() {
	/**
	 *
	 * @if the buzzer make noise and turn ON and OFF very rapid,
	 * this mean that the WDG is correctly reset the system
	 * @if the buzzer make a continuous sound that mean that the WDG didn't reset
	 *
	 */
	Buzzer_Init();

	/**
	 * The initialization of LCD make some delay in the time
	 * but we can use it in another project that display the number of WDG resets
	 */
//	LCD_Init();
//	LCD_String_xy(0,0, "WDG reset times");
//	utoa(resets, resetTimes);   //function to convert from char to string to display it
//	LCD_String(resetTimes);


    LEDM_Init();
    GPIO_Write(PROJECT_START_LED, HIGH);
    timers_init();
    WDGDrv_Init();
    WDGM_Init();
    GPIO_Write(PROJECT_START_LED, LOW);

    while(1) {

    	// get the current time
        uint32_t currentTimerTime = HAL_GetTick();

        /**
         *
         * Check and manage LED if it's time : in the first three scenarios led time >= 10ms
         * In the fourth scenario the led time is >= 5ms
         *
         */

        /**
         *
		 * @if We changing the checking time of the LED
		 * from                                10ms          to         5ms
		 * the reset time changed from       ~64.11ms        to        ~114ms
		 *
		 */
        if (currentTimerTime - checkLedTime >= 10) {
            LEDM_Manage();
            // update the LED time checker
            checkLedTime = currentTimerTime;
        }

        /**
         *
         * The WDGM_MainFunction shall be called periodically every 20ms.
         * Check and run watchdog main function if it's time
         *
         * */
        if (currentTimerTime - checkWDGTime >= 20) {
        	/**
        	 *
        	 * @if We commenting WDGM_MainFunction the WDG reset( system reset )
        	 * after 64ms
        	 *
        	 */
            WDGM_MainFunction();
            // update the WGDT time checker
            checkWDGTime = currentTimerTime;
        }
    }

    return 0;
}
/*******************************************************************************
 ******************************     Main End     *******************************
 *******************************************************************************/

/**
 * @brief
 * Interrupt service routine of the WDG timer
 * Increments the number of resets every time the WDG reset the system
 * then we display the number of resets on the LCD
 *
 * */
ISR(WDT_vect){
	GPIO_Write(MCU_reset_LED, HIGH);
	resets++;
	GPIO_Write(MCU_reset_LED, LOW);

}
