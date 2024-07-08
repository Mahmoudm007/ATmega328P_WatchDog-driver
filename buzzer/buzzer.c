/*
 * buzzer.c
 *
 *  Created on: Jun 18, 2024
 *      Author: Mahmoud
 */

#include "buzzer.h"


/**
 * @brief Initializes the buzzer by configuring its GPIO pin as an output.
 *
 * This function sets up the GPIO pin connected to the buzzer as an output pin with
 * push-pull configuration. It should be called once during the system initialization
 * to prepare the buzzer for use.
 *
 * @param None
 * @return None
 */
void Buzzer_Init(void) {
    // Configure the buzzer pin as an output
	Gpio_ConfigPin(BUZZER_PORT, BUZZER_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
}

/**
 * @brief Turns the buzzer on by setting its GPIO pin to high.
 *
 * This function sets the GPIO pin connected to the buzzer to a high state, causing
 * the buzzer to emit sound. It can be called whenever the buzzer needs to be turned on.
 *
 * @param None
 * @return None
 */
void Buzzer_On(void) {
    // Set the buzzer pin to high
	GPIO_Write( BUZZER_PIN, HIGH);
}

/**
 * @brief Turns the buzzer off by setting its GPIO pin to low.
 *
 * This function sets the GPIO pin connected to the buzzer to a low state, stopping
 * the buzzer from emitting sound. It can be called whenever the buzzer needs to be turned off.
 *
 * @param None
 * @return None
 */
void Buzzer_Off(void) {
    // Set the buzzer pin to low
	GPIO_Write(BUZZER_PIN, LOW);
}


/**
 * @brief Toggles the state of the buzzer.
 *
 * This function changes the state of the GPIO pin connected to the buzzer from high to low
 * or from low to high, effectively toggling the buzzer on and off. It can be used to create
 * a toggling sound effect or for debugging purposes.
 *
 * @param None
 * @return None
 */
void Buzzer_Toggle(void) {
    // Toggle the buzzer pin
	Gpio_TogglePin(BUZZER_PORT, BUZZER_PIN);
}
