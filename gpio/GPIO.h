#ifndef GPIO_H
#define GPIO_H
/*******************************************************************************
 ******************************   includes Start    ****************************
 *******************************************************************************/
#include "GPIO_private.h"
/*******************************************************************************
 ******************************   includes end    ****************************
 *******************************************************************************/

/*******************************************************************************
 ******************************   Macros Start      ****************************
 *******************************************************************************/
#define GPIO_B 'B'
#define GPIO_C 'C'
#define GPIO_D 'D'

/* PinMode */
#define GPIO_INPUT                0x00
#define GPIO_OUTPUT               0x01

/* DefaultState */
#define GPIO_PUSH_PULL            0x00
#define GPIO_NO_PULL              0x00
#define GPIO_PULL_UP              0x01

#define LOW    0x00
#define HIGH   0x01


#define LED_PORT (*(volatile uint8_t*)0x25)  // PORTB address
#define LED_DDR  (*(volatile uint8_t*)0x24)  // DDRB address
#define LED_PIN  5                           // Pin number for PB5


#define MCU_reset_LED  			0   /* Define LED pin (PB0) */
#define WDT_COUNTER_RESET_LED  	1   /* Define LED pin (PB1) */
#define LED_MANAGE_LED  		2   /* Define LED pin (PB2) */
#define WDGM_LED  				3	/* Define LED pin (PB3) */
#define PROJECT_START_LED  		4   /* Define LED pin (PB4) */
#define LED_TOGGLE_LED  		5	/* Define LED pin (PB5) */
#define TIMER50MS_LED			6	/* Define LED pin (PB6) */
#define TIMER1MS_LED			7	/* Define LED pin (PB7) */
// Define the buzzer port and pin
#define BUZZER_PORT PORTD
#define BUZZER_PIN  PB1
#define BUZZER_DDR 	DDRD
/*******************************************************************************
 ******************************   Macros End      ****************************
 *******************************************************************************/


/*******************************************************************************
 *************************   Functions prototype start   ***********************
 *******************************************************************************/

/**
 * initialize the gpio port and pins as inputs or outputs
 * */
void GPIO_Init(void);


/** @param : PortName -> GPIOB, PinNum -> 0 & 5, PinMode -> Output, DefaultState -> GPIO_PUSH_PULL
 * 	Called by GPIO_Init and configure the GPIO pin as output and set the default mode
 * */
void Gpio_ConfigPin(uint8 PortName, uint8 PinNum, uint8 PinMode, uint8 DefaultState);


/** @param : PortName -> GPIOB, PinNum -> 0 & 5, PinData -> HIGH or LOW
 * 	set a pin to high or low to toggle the pin in the main function
 * */
void GPIO_Write(uint8 PinId, uint8 PinData);

uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNum);
void Gpio_TogglePin(uint8 PortName, uint8 PinNum);
void Gpio_DisablePins(uint8 PortName);

/*******************************************************************************
 *************************   Functions prototype start   ***********************
 *******************************************************************************/

#endif
