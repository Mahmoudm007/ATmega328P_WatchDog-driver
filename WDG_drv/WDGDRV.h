#ifndef WDDRV_H
#define WDDRV_H

/*******************************************************************************
 ******************************   includes Start    ****************************
 *******************************************************************************/
#include "Std_Types.h"
#include "WDGM.h"
#include "stdint.h"
#include "GPIO.h"
#include "timer.h"
#include "Bit_Operations.h"
#include <avr/io.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/*******************************************************************************
 ******************************   includes end    ****************************
 *******************************************************************************/



/*******************************************************************************
 ******************************   Macros Start      ****************************
 *******************************************************************************/
// WDG reset Macro
#define wdt_reset()   __asm__ __volatile__ ("wdr")

#define WDTO_15MS    0
#define WDTO_30MS    1
#define WDTO_60MS    2
#define WDTO_120MS   3
#define WDTO_250MS   4
#define WDTO_500MS   5
#define WDTO_1S   	 6
#define WDTO_2S      7
#define WDTO_4S      8
#define WDTO_8S      9

// Define Watchdog Timer Control and Status Register (WDTCSR) address and bits
#define WDTCSR_ADDR (*(volatile uint8_t *)(0x60))
#define WDIF 7
#define WDIE 6
#define WDP3 5
#define WDCE 4
#define WDE  3
#define WDP2 2
#define WDP1 1
#define WDP0 0



// Define Watchdog Timer Reset Flag Register (WDTCR) address and bits
#define WDTCR_ADDR (*(volatile uint8_t *)(0x55))
#define WDRF_BIT 3
/*******************************************************************************
 ******************************   Macros End      ****************************
 *******************************************************************************/


/*******************************************************************************
 *************************   Global variables Start      ***********************
 *******************************************************************************/
extern volatile WDGM_StatusType status;
extern volatile WDGM_StatusType providedStatus;
extern vuint8 WDGM_MainFunction_Stuck;
/*******************************************************************************
 *************************   Global variables end      ***********************
 *******************************************************************************/


/*******************************************************************************
 *************************   Functions prototype start   ***********************
 *******************************************************************************/
// Global interrupt registers setting functions
void enable_global_interrupt(void);
void disable_global_interrupt(void);


// WDG driver functions
void WDGDrv_Init(void);
void WDGDrv_IsrNotification(void);
void WDGDrv_Disable(void);
/*******************************************************************************
 *************************   Functions prototype start   ***********************
 *******************************************************************************/

#endif
