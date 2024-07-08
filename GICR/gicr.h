/*
 * Gicr.h
 *
 *  Created on: Jun 18, 2024
 *      Author: Mahmoud
 */

#ifndef GICR_H_
#define GICR_H_

#include <avr/io.h>


/*******************************************************************************
 ******************************   Macros Start      ****************************
 *******************************************************************************/
// External Interrupt Request 0 (INT0) on PD2
#define INT0_PIN PD2
#define INT0_PORT PORTD
#define INT0_DDR DDRD

// External Interrupt Request 1 (INT1) on PD3
#define INT1_PIN PD3
#define INT1_PORT PORTD
#define INT1_DDR DDRD
/*******************************************************************************
 ******************************   Macros End        ****************************
 *******************************************************************************/

typedef enum {
    GICR_INT0 = 0,
    GICR_INT1 = 1
} GICR_Line;

typedef enum {
    GICR_RISING_EDGE,
    GICR_FALLING_EDGE,
    GICR_RISING_FALLING_EDGES
} GICR_Edge;



/*******************************************************************************
 *************************   Functions prototype Start   ***********************
 *******************************************************************************/
void Gicr_Init(GICR_Line line, GICR_Edge edge);
void Gicr_EnableInterrupt(GICR_Line line);
void Gicr_DisableInterrupt(GICR_Line line);
void Gicr_ClearInterruptFlag(GICR_Line line);
uint8_t Gicr_IsInterruptActive(GICR_Line line);
/*******************************************************************************
 *************************   Functions prototype End     ***********************
 *******************************************************************************/

#endif /* GICR_H_ */
