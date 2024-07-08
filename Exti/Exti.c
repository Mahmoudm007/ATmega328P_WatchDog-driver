/*
 * Exti.c
 *
 *  Created on: Jun 16, 2024
 *      Author: Mahmoud
 */

#include "Exti.h"

/**
 * @brief Array of function pointers for external interrupt callbacks.
 *
 * This array holds the function pointers for the callbacks associated with external
 * interrupts INT0 and INT1. It is initialized with NULL pointers.
 */
void (*EXTI_Callbacks[2])(void) = {0}; // Only two external interrupts on Atmega328p (INT0 and INT1)


/**
 * @brief Initializes the specified external interrupt line with the given edge trigger.
 *
 * This function configures the specified external interrupt line (INT0 or INT1) to trigger
 * on the specified edge (rising, falling, or any logical change). It disables global interrupts
 * while making changes to ensure atomic operation.
 *
 * @param extiLine The external interrupt line to configure (EXTI_INT0 or EXTI_INT1).
 * @param edge The edge trigger to configure (EXTI_RISING_EDGE, EXTI_FALLING_EDGE, or EXTI_RISING_FALLING_EDGES).
 * @return None
 */
void Exti_Init(EXTI_Line extiLine, EXTI_Edge edge) {
    cli(); // Disable global interrupts

    switch (extiLine) {
        case EXTI_INT0:
            if (edge == EXTI_RISING_EDGE) {
                EICRA |= (1 << ISC00) | (1 << ISC01);  // Rising edge
            } else if (edge == EXTI_FALLING_EDGE) {
                EICRA &= ~(1 << ISC00);
                EICRA |= (1 << ISC01);  // Falling edge
            } else if (edge == EXTI_RISING_FALLING_EDGES) {
                EICRA |= (1 << ISC00);
                EICRA &= ~(1 << ISC01);  // Any logical change
            }
            break;

        case EXTI_INT1:
            if (edge == EXTI_RISING_EDGE) {
                EICRA |= (1 << ISC10) | (1 << ISC11);  // Rising edge
            } else if (edge == EXTI_FALLING_EDGE) {
                EICRA &= ~(1 << ISC10);
                EICRA |= (1 << ISC11);  // Falling edge
            } else if (edge == EXTI_RISING_FALLING_EDGES) {
                EICRA |= (1 << ISC10);
                EICRA &= ~(1 << ISC11);  // Any logical change
            }
            break;

        default:
            // Invalid EXTI line
            break;
    }

    sei(); // Re-enable global interrupts
}


/**
 * @brief Deinitializes the specified external interrupt line.
 *
 * This function disables the specified external interrupt line (INT0 or INT1) by calling
 * the EXTI_Disable function.
 *
 * @param extiLine The external interrupt line to deinitialize (EXTI_INT0 or EXTI_INT1).
 * @return None
 */
void Exti_Deinit(EXTI_Line extiLine) {
    EXTI_Disable(extiLine);
}


/**
 * @brief Enables the specified external interrupt line.
 *
 * This function enables the specified external interrupt line (INT0 or INT1) by setting
 * the appropriate bit in the external interrupt mask register.
 *
 * @param extiLine The external interrupt line to enable (EXTI_INT0 or EXTI_INT1).
 * @return None
 */
void EXTI_Enable(EXTI_Line extiLine) {
    if (extiLine == EXTI_INT0) {
        EIMSK |= (1 << INT0);  // Enable INT0
    } else if (extiLine == EXTI_INT1) {
        EIMSK |= (1 << INT1);  // Enable INT1
    }
}


/**
 * @brief Disables the specified external interrupt line.
 *
 * This function disables the specified external interrupt line (INT0 or INT1) by clearing
 * the appropriate bit in the external interrupt mask register.
 *
 * @param extiLine The external interrupt line to disable (EXTI_INT0 or EXTI_INT1).
 * @return None
 */
void EXTI_Disable(EXTI_Line extiLine) {
    if (extiLine == EXTI_INT0) {
        EIMSK &= ~(1 << INT0);  // Disable INT0
    } else if (extiLine == EXTI_INT1) {
        EIMSK &= ~(1 << INT1);  // Disable INT1
    }
}



/**
 * @brief Registers a callback function for the specified external interrupt line.
 *
 * This function registers a callback function to be called when the specified external
 * interrupt line (INT0 or INT1) triggers. The callback function pointer is stored in the
 * EXTI_Callbacks array.
 *
 * @param extiLine The external interrupt line to register the callback for (EXTI_INT0 or EXTI_INT1).
 * @param P_IRQ_Callback The callback function to register.
 * @return None
 */
void EXTI_RegisterCallback(EXTI_Line extiLine, void (*P_IRQ_Callback)(void)) {
    if (extiLine < 2) {
        EXTI_Callbacks[extiLine] = P_IRQ_Callback;
    }
}


/**
 * @brief ISR for external interrupt 0 (INT0).
 *
 * This ISR is triggered when the external interrupt 0 (INT0) occurs. It checks if a callback
 * function is registered for INT0 and calls it if available.
 */
ISR(INT0_vect) {
    if (EXTI_Callbacks[EXTI_INT0] != NULL) {
        EXTI_Callbacks[EXTI_INT0]();
    }
}



/**
 * @brief ISR for external interrupt 1 (INT1).
 *
 * This ISR is triggered when the external interrupt 1 (INT1) occurs. It checks if a callback
 * function is registered for INT1 and calls it if available.
 */
ISR(INT1_vect) {
    if (EXTI_Callbacks[EXTI_INT1] != NULL) {
        EXTI_Callbacks[EXTI_INT1]();
    }
}
