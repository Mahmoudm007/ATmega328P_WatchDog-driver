/*
 * Exti_private.h
 *
 *  Created on: Jun 16, 2024
 *      Author: Mahmoud
 */

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "Bit_Operations.h"
#include "Std_Types.h"


/*******************************************************************************
 ******************************   Macros Start      ****************************
 *******************************************************************************/
#define FALLING_EDGE                0
#define RISING_EDGE                 1
#define RISING_FALLING              2

#define EXTI_DISABLE                0
#define EXTI_ENABLE                 1
/*******************************************************************************
 ******************************   Macros End        ****************************
 *******************************************************************************/


typedef enum {
    EXTI_INT0 = 0,
    EXTI_INT1 = 1
} EXTI_Line;

typedef enum {
    EXTI_RISING_EDGE,
    EXTI_FALLING_EDGE,
    EXTI_RISING_FALLING_EDGES
} EXTI_Edge;

#endif /* EXTI_PRIVATE_H_ */
