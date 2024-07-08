/*
 * 	Bit_Operations.h
 *
 *	Created on: Sat Apr 19 2024
 *  Author    : Mahmoud
 */

#ifndef BIT_OPERATIONS_H
#define BIT_OPERATIONS_H


// Generic macros for GPIO operations
#define SET_PIN(port, pin) ((port)->PORT |= (1 << (pin)))
#define CLEAR_PIN(port, pin) ((port)->PORT &= ~(1 << (pin)))
#define TOGGLE_PIN(port, pin) (*(port) ^= (1 << (pin)))
#define READ_PIN(port, pin) (((port)->PIN & (1 << (pin))) >> (pin))
#define SET_DIRECTION_INPUT(port, pin) ((port)->DDR &= ~(1 << (pin)))
#define SET_DIRECTION_OUTPUT(port, pin) ((port)->DDR |= (1 << (pin)))
#define TOGGLE_BIT(state)  state ^= 1;

#endif /* BIT_OPERATIONS_H */
