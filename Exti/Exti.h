/*
 * Exti.h
 *
 *  Created on: Jun 16, 2024
 *      Author: Mahmoud
 */

#ifndef EXTI_H_
#define EXTI_H_

/*******************************************************************************
 ******************************   includes Start    ****************************
 *******************************************************************************/
#include "Exti_private.h"
/*******************************************************************************
 ******************************   includes End      ****************************
 *******************************************************************************/



/*******************************************************************************
 *************************   Functions prototype Start   ***********************
 *******************************************************************************/
// Define EXTI configurations
extern void (*EXTI_Callbacks[2])(void);  // Array to hold callback functions for INT0 and INT1

// Function Prototypes
void Exti_Init(EXTI_Line extiLine, EXTI_Edge edge);
void Exti_Deinit(EXTI_Line extiLine);

void EXTI_Enable(EXTI_Line extiLine);
void EXTI_Disable(EXTI_Line extiLine);

void EXTI_RegisterCallback(EXTI_Line extiLine, void (*P_IRQ_Callback)(void));
/*******************************************************************************
 *************************   Functions prototype End     ***********************
 *******************************************************************************/

#endif /* EXTI_H_ */
