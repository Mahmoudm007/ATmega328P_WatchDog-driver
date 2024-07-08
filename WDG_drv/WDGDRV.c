/*
 * WDGDRV.c
 *
 *  Created on: Jun 18, 2024
 *      Author: Mahmoud
 */

#include "WDGDrv.h"



/**
 * @brief:
 * Enable Global Interrupt: The enable_global_interrupt function sets
 * the global interrupt enable bit (I-bit) in the Status Register (SREG).
 * By setting this bit, the microcontroller is allowed to process interrupts.
 */
void enable_global_interrupt(void){
	SREG |= (1 << 7);		// Enable interrupts back
}


/**
 * @brief:
 * Disable Global Interrupt: The disable_global_interrupt function clears the I-bit in the SREG.
 * This effectively prevents the microcontroller from processing any interrupts,
 * which can be useful to ensure critical code sections are not interrupted.
 */
void disable_global_interrupt(void){
	SREG &= ~(1 << 7);			// Disable interrupts temporarily
}



/**
 * Steps of enabling the WDT in ATMega328P:
	1) Disable interrupts temporarily to prevent interference during initialization.
	2) Reset the Watchdog Timer to ensure it starts in a known state = Zero.
	3) Clear the Watchdog System Reset Flag (WDRF) to acknowledge any previous resets.
	4) Reset the Watchdog Control Register (WDTCSR) to initial state (0x00) to avoid any garbage values in any register.
	5) Enable the Watchdog Timer by initiating a timed sequence (WDCE and WDE bits set).
	6) Within the timed sequence, set the WDE bit to enable the Watchdog Timer.
	7) Set WDIE bit to enable Watchdog Interrupt Enable mode.
	8) Set WDP1 bit to configure the prescaler for a 64-milliseconds timeout from data sheet.
	9) Re-enable interrupts to resume normal operation.
 * */
void WDGDrv_Init(void) {
	GPIO_Write(WDT_COUNTER_RESET_LED, HIGH);
    disable_global_interrupt(); 	// Disable interrupts
    wdt_reset();
    // Clear watchdog reset flag
    MCUSR &= ~(1 << WDRF);
    // clear the register to avoid any garbage values
    WDTCSR = 0x00;
    // Enable watchdog timer (change enable bit must be set in a timed sequence)
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    // Enable interrupt mode, watchdog enable, and pre-scaler "WDP1 -> 64ms"
    WDTCSR = (1 << WDIE) | (1 << WDE) | (1 << WDP1); // 0b01001010
    sei();
    GPIO_Write(WDT_COUNTER_RESET_LED, LOW);
    enable_global_interrupt();		// Enable interrupts
}


/**
 * @brief:
 * if the function not stacked and the status of the WDT is ok so the 64ms
 * the WDG counter/timeout will reset and start from the first point
 * and also check the providedState of the WDG
 */
void WDGDrv_IsrNotification(void) {
	providedStatus = WDGM_ProvideSupervisionStatus();

    if (status == OK && (!providedStatus) &&  WDGM_MainFunction_Stuck) {
    	GPIO_Write(WDT_COUNTER_RESET_LED, HIGH);
        wdt_reset();
    }
}


/** TO disable the WDG timer steps:
 * 1) Set bit 3 and bit 4 in the same line
 * 2) Clear Bit 3
 * */
void WDGDrv_Disable(void) {
    cli(); // Disable interrupts temporarily

    WDTCSR |= (1 << WDCE) | (1 << WDE); // Start timed sequence, disable watchdog
    WDTCSR = 0x00; // Turn off watchdog timer
    sei(); // Enable interrupts back
}
