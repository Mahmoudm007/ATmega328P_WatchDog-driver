/*
 * GPIO.c
 *
 *  Created on: Jun 16, 2024
 *      Author: Mahmoud
 */

#include "GPIO.h"


/**
 * GPIO struct to define which PORT is the activated port
 */
#define GET_GPIO_STRUCT(PORT_NAME) ((PORT_NAME == GPIO_B) ? &GPIOB : \
                                    (PORT_NAME == GPIO_C) ? &GPIOC : &GPIOD)


/**
 * @brief Initializes the GPIO pins for the application.
 *
 * This function configures specific GPIO pins (LED_PIN_0 and LED_PIN_5) on port GPIO_B
 * as output pins with push-pull configuration.
 *
 * @return None
 */
void GPIO_Init(void)
{
    Gpio_ConfigPin(GPIO_B, MCU_reset_LED, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_ConfigPin(GPIO_B, WDT_COUNTER_RESET_LED, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_ConfigPin(GPIO_B, LED_MANAGE_LED, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_ConfigPin(GPIO_B, WDGM_LED, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_ConfigPin(GPIO_B, PROJECT_START_LED, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_ConfigPin(GPIO_B, LED_TOGGLE_LED, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_ConfigPin(GPIO_B, TIMER50MS_LED, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_ConfigPin(GPIO_B, TIMER1MS_LED, GPIO_OUTPUT, GPIO_PUSH_PULL);
}



/**
 * @brief Configures a specific GPIO pin.
 *
 * This function configures a specific GPIO pin on the specified port with the given mode
 * and default state. It sets the data direction register (DDR) and port register appropriately.
 *
 * @param PortName The port to which the pin belongs (e.g., GPIO_B, GPIO_C).
 * @param PinNum The pin number to configure.
 * @param PinMode The mode to set for the pin (e.g., GPIO_OUTPUT).
 * @param DefaultState The default state for the pin (e.g., GPIO_PULL_UP).
 * @return None
 */
void Gpio_ConfigPin(uint8 PortName, uint8 PinNum, uint8 PinMode, uint8 DefaultState) {
//    GpioType* gpio = GET_GPIO_STRUCT(PortName);
//    volatile uint8_t *ddr = gpio->DDR;
//    volatile uint8_t *port = gpio->PORT;

    if (PinMode == GPIO_OUTPUT) {
    	LED_DDR |= (1 << PinNum);
    	BUZZER_DDR |= (1 << BUZZER_PIN);
    } else {
    	LED_DDR &= ~(1 << PinNum);
    }

    if (DefaultState == GPIO_PULL_UP) {
    	LED_PORT|= (1 << PinNum);
    	BUZZER_PORT |= (1<< BUZZER_PIN);
    } else {
    	LED_PORT &= ~(1 << PinNum);
    	BUZZER_PORT &= ~(1<< BUZZER_PIN);
    }
}



/**
 * @brief Writes data to a specific GPIO pin.
 *
 * This function sets or clears the specified GPIO pin on the given port based on the
 * provided pin data.
 *
 * @param PinId The pin number to write to.
 * @param PinData The data to write to the pin (1 to set, 0 to clear).
 * @return None
 */
void GPIO_Write(uint8 PinId, uint8 PinData)
{
    if (PinData) {
    	LED_PORT 	|= (1 << PinId);
    	BUZZER_PORT |= (1<< BUZZER_PIN);
    } else {
    	LED_PORT &= ~(1 << PinId);
    }
}


/**
 * @brief Reads the state of a specific GPIO pin.
 *
 * This function reads and returns the state of the specified GPIO pin on the given port.
 *
 * @param PortName The port to which the pin belongs (e.g., GPIO_B, GPIO_C).
 * @param PinNum The pin number to read from.
 * @return The state of the pin (1 if set, 0 if clear).
 */
// TODO : Check why the struct logic is valid and correct on proteus 8.13, and on't correct on proteus 8.9
uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNum) {
//    GpioType* gpio = GET_GPIO_STRUCT(PortName);
//    volatile uint8_t *pin = gpio->PIN;
//	return ((*pin & (1 << PinNum)) >> PinNum);
    return ((LED_PIN & (1 << PinNum)) >> PinNum);
}


/**
 * @brief Toggles the state of a specific GPIO pin.
 *
 * This function toggles the state of the specified GPIO pin on the given port.
 *
 * @param PortName The port to which the pin belongs (e.g., GPIO_B, GPIO_C).
 * @param PinNum The pin number to toggle.
 * @return None
 */
void Gpio_TogglePin(uint8 PortName, uint8 PinNum) {
//    GpioType* gpio = GET_GPIO_STRUCT(PortName);
//    volatile uint8_t *port = gpio->PORT;
//    *port ^= (1 << PinNum);
    LED_PORT ^= (1 << PinNum);
}



/**
 * @brief Disables all pins on the specified GPIO port.
 *
 * This function disables all pins on the specified GPIO port by setting the port
 * data register and data direction register to 0.
 *
 * @param PortName The port to disable (e.g., GPIO_B, GPIO_C).
 * @return None
 */
void Gpio_DisablePins(uint8 PortName) {
//    GpioType* gpio = GET_GPIO_STRUCT(PortName);
//    volatile uint8_t *port = gpio->PORT;
//    volatile uint8_t *ddr = gpio->DDR;

    LED_PORT = 0x00;
    LED_DDR = 0x00;
}
