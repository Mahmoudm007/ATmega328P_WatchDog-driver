#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

/*******************************************************************************
 ******************************   includes Start    ****************************
 *******************************************************************************/
#include <stdint.h>
#include "Std_types.h"
#include "Bit_Operations.h"
#include <avr/io.h>
/*******************************************************************************
 ******************************   includes end    ****************************
 *******************************************************************************/


/*******************************************************************************
 ******************************   Macros Start      ****************************
 *******************************************************************************/
// Define base addresses for ATmega328P GPIO ports
#define GPIOB_BASE_ADDR 	0x25 // PORTB base address
#define GPIOC_BASE_ADDR 	0x28 // PORTC base address
#define GPIOD_BASE_ADDR 	0x2B // PORTD base address

// Define offsets for the GPIO registers
#define GPIO_DDR_OFFSET 	0x01
#define GPIO_PIN_OFFSET		0x00
#define GPIO_PORT_OFFSET    0x02

// Define GPIO ports with base addresses and register offsets
#define GPIOB ((GpioType){(volatile uint8_t *)(GPIOB_BASE_ADDR - GPIO_DDR_OFFSET), \
                          (volatile uint8_t *)(GPIOB_BASE_ADDR - GPIO_PIN_OFFSET), \
                          (volatile uint8_t *)(GPIOB_BASE_ADDR)})

#define GPIOC ((GpioType){(volatile uint8_t *)(GPIOC_BASE_ADDR - GPIO_DDR_OFFSET), \
                          (volatile uint8_t *)(GPIOC_BASE_ADDR - GPIO_PIN_OFFSET), \
                          (volatile uint8_t *)(GPIOC_BASE_ADDR)})

#define GPIOD ((GpioType){(volatile uint8_t *)(GPIOD_BASE_ADDR - GPIO_DDR_OFFSET), \
                          (volatile uint8_t *)(GPIOD_BASE_ADDR - GPIO_PIN_OFFSET), \
                          (volatile uint8_t *)(GPIOD_BASE_ADDR)})
/*******************************************************************************
 ******************************   Macros End        ****************************
 *******************************************************************************/

typedef struct {
    volatile uint8_t *DDR;   // Data Direction Register
    volatile uint8_t *PIN;   // Input Pins Register
    volatile uint8_t *PORT;  // Data Register
} GpioType;



#endif /* GPIO_PRIVATE_H */
