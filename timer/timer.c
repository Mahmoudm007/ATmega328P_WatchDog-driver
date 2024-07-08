/*
 * timer.c
 *
 *  Created on: Jun 20, 2024
 *      Author: Mahmoud
 */

#include "timer.h"

vsint32_t millis = 0;


/**
 * @brief Initializes Timer1 and Timer2.
 *
 * This function sets up Timer1 and Timer2 for CTC (Clear Timer on Compare Match) mode.
 * Timer1 is configured to trigger an interrupt every ~52.2ms and Timer2 is configured
 * to trigger an interrupt every 1ms. The global interrupts are also enabled at the end
 * of this function.
 *
 * @return None
 */
void timers_init() {
	/**
	 * TIMER1A initialization
	 */
    // Set Timer1 to CTC (Clear Timer on Compare Match) mode
    TCCR1B |= (1 << WGM12);

    // Set the compare match register to value for 52.2ms interrupt at 1 MHz
    /**
     * P.101 in datasheet
     * Calculation: OCR1A = (desired interrupt period * CPU frequency / prescaler) - 1
     * FocnA = (Fclk_I/O) / ( 2 * Prescaler * ( 1 + OCRnA ))
     * For 52.2 ms interrupt: OCR1A = (0.0522 * 1000000 / 64) - 1 = ~815
     * we choose ~52ms not 50ms to avoid the sharp edge of the reseting time
     * */
    OCR1A = 815; // output compare registers

    // Enable Timer1 compare interrupt A
    TIMSK1 |= (1 << OCIE1A);

    // Set prescaler to 64 and start Timer1
    TCCR1B |= (1 << CS11) | (1 << CS10); // Prescaler = 64


	/**
	 * TIMER2A initialization
	 */
    // Set Timer2 to CTC (Clear Timer on Compare Match) mode
	TCCR2A |= (1 << WGM21);

	/**
	 * P.121 In datasheet
	 * Calculation: OCR2A = (desired interrupt period * CPU frequency / prescaler) - 1
	 * Focnx = (Fclk_I/O) / ( 2 * Prescaler * ( 1 + OCRnx )
	 * For 1 ms interrupt: OCR2A = ((0.001 * 1000000 / 64) + 1) = 15.7 * 2 = 31.4 ~ 31
	 *
	 */
	OCR2A = 31; // output compare registers

	// Enable Timer2 compare interrupt A
	TIMSK2 |= (1 << OCIE2A);

	// Set prescaler to 64 and start Timer2
	TCCR2B |= (1 << CS21) | (1 << CS20);  // Prescaler = 64
    // Enable global interrupts
    enable_global_interrupt();
}


/**
 * @brief Returns the number of milliseconds since the program started.
 *
 * This function retrieves the value of the `millis` variable, which is incremented
 * by the Timer2 compare match interrupt. It temporarily disables global interrupts
 * to ensure a consistent read of the `millis` variable.
 *
 * @return The number of milliseconds since the program started.
 */
uint32_t HAL_GetTick() {
    uint32_t MilliSeconds;
    disable_global_interrupt();  // Disable global interrupts
    // Store the millis that incremented by the ISR(TIMER2_COMPA_vect)
    MilliSeconds = millis;
    enable_global_interrupt();  // Enable global interrupts
    return MilliSeconds;
}


/**
 * @brief Timer1 compare match interrupt service routine.
 *
 * This ISR is called when Timer1 reaches the compare match value.
 * It calls the watchdog driver ISR notification function.
 *
 * @return None
 */
ISR(TIMER1_COMPA_vect) {
	GPIO_Write(TIMER50MS_LED, HIGH);
    WDGDrv_IsrNotification();  // Call ISR function of WDG every ~50 ms
    GPIO_Write(TIMER50MS_LED, LOW);
}


/**
 * @brief Timer2 compare match interrupt service routine.
 *
 * This ISR is called when Timer2 reaches the compare match value.
 * It increments the `millis` variable every 1ms to keep track of time.
 *
 * @return None
 */
ISR(TIMER2_COMPA_vect) {
	GPIO_Write(TIMER1MS_LED, HIGH);
	millis++;  // Increment millis
	GPIO_Write(TIMER1MS_LED, LOW);
}
