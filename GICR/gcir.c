/*
 * Gicr.c
 *
 *  Created on: Jun 18, 2024
 *      Author: Mahmoud
 */

#include "gicr.h"
#include <avr/interrupt.h>

/**
 * @brief Initializes the specified external interrupt line with the given edge trigger.
 *
 * This function configures the specified external interrupt line (INT0 or INT1) to trigger
 * on the specified edge (rising, falling, or any logical change). It disables global interrupts
 * while making changes to ensure atomic operation.
 *
 * @param line The external interrupt line to configure (GICR_INT0 or GICR_INT1).
 * @param edge The edge trigger to configure (GICR_RISING_EDGE, GICR_FALLING_EDGE, or GICR_RISING_FALLING_EDGES).
 * @return None
 */
void Gicr_Init(GICR_Line line, GICR_Edge edge) {
    cli(); // Disable global interrupts

    switch (line) {
        case GICR_INT0:
            // Configure INT0 pin as input
            INT0_DDR &= ~(1 << INT0_PIN);

            if (edge == GICR_RISING_EDGE) {
                EICRA |= (1 << ISC00) | (1 << ISC01);  // Rising edge
            } else if (edge == GICR_FALLING_EDGE) {
                EICRA &= ~(1 << ISC00);
                EICRA |= (1 << ISC01);  // Falling edge
            } else if (edge == GICR_RISING_FALLING_EDGES) {
                EICRA |= (1 << ISC00);
                EICRA &= ~(1 << ISC01);  // Any logical change
            }
            break;

        case GICR_INT1:
            // Configure INT1 pin as input
            INT1_DDR &= ~(1 << INT1_PIN);

            if (edge == GICR_RISING_EDGE) {
                EICRA |= (1 << ISC10) | (1 << ISC11);  // Rising edge
            } else if (edge == GICR_FALLING_EDGE) {
                EICRA &= ~(1 << ISC10);
                EICRA |= (1 << ISC11);  // Falling edge
            } else if (edge == GICR_RISING_FALLING_EDGES) {
                EICRA |= (1 << ISC10);
                EICRA &= ~(1 << ISC11);  // Any logical change
            }
            break;

        default:
            // Invalid interrupt line
            break;
    }

    sei(); // Re-enable global interrupts
}

/**
 * @brief Enables the specified external interrupt line.
 *
 * This function enables the specified external interrupt line (INT0 or INT1) by setting
 * the appropriate bit in the external interrupt mask register.
 *
 * @param line The external interrupt line to enable (GICR_INT0 or GICR_INT1).
 * @return None
 */
void Gicr_EnableInterrupt(GICR_Line line) {
    if (line == GICR_INT0) {
        EIMSK |= (1 << INT0);  // Enable INT0
    } else if (line == GICR_INT1) {
        EIMSK |= (1 << INT1);  // Enable INT1
    }
}

/**
 * @brief Disables the specified external interrupt line.
 *
 * This function disables the specified external interrupt line (INT0 or INT1) by clearing
 * the appropriate bit in the external interrupt mask register.
 *
 * @param line The external interrupt line to disable (GICR_INT0 or GICR_INT1).
 * @return None
 */
void Gicr_DisableInterrupt(GICR_Line line) {
    if (line == GICR_INT0) {
        EIMSK &= ~(1 << INT0);  // Disable INT0
    } else if (line == GICR_INT1) {
        EIMSK &= ~(1 << INT1);  // Disable INT1
    }
}

/**
 * @brief Clears the interrupt flag for the specified external interrupt line.
 *
 * This function clears the interrupt flag for the specified external interrupt line (INT0 or INT1)
 * by setting the appropriate bit in the external interrupt flag register.
 *
 * @param line The external interrupt line for which to clear the flag (GICR_INT0 or GICR_INT1).
 * @return None
 */
void Gicr_ClearInterruptFlag(GICR_Line line) {
    if (line == GICR_INT0) {
        EIFR |= (1 << INTF0);  // Clear INT0 flag
    } else if (line == GICR_INT1) {
        EIFR |= (1 << INTF1);  // Clear INT1 flag
    }
}

/**
 * @brief Checks if the specified external interrupt line is active.
 *
 * This function checks if the interrupt flag for the specified external interrupt line (INT0 or INT1)
 * is set, indicating that the interrupt is active.
 *
 * @param line The external interrupt line to check (GICR_INT0 or GICR_INT1).
 * @return 1 if the interrupt is active, 0 otherwise.
 */
uint8_t Gicr_IsInterruptActive(GICR_Line line) {
    if (line == GICR_INT0) {
        return (EIFR & (1 << INTF0)) ? 1 : 0;  // Check if INT0 is active
    } else if (line == GICR_INT1) {
        return (EIFR & (1 << INTF1)) ? 1 : 0;  // Check if INT1 is active
    }
    return 0;
}
