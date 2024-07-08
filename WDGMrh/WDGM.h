#ifndef WDGM_H
#define WDGM_H

#include "Std_types.h"

/*******************************************************************************
 ******************************   Macros Start      ****************************
 *******************************************************************************/
#define WDGM_PERIOD_MS 			 100
#define LEDM_CALLS_OK_MIN		 8
#define LEDM_CALLS_OK_MAX 		 12
/*******************************************************************************
 ******************************   Macros End        ****************************
 *******************************************************************************/

typedef enum {
    OK = 0,
    NOK = 1
} WDGM_StatusType;


/*******************************************************************************
 ******************************   Function Prototype Start      ****************
 *******************************************************************************/
void WDGM_Init(void);

void WDGM_MainFunction(void);

WDGM_StatusType WDGM_ProvideSupervisionStatus(void);

void WDGM_AlivenessIndication(void);
/*******************************************************************************
 ******************************   Function Prototype End      ******************
 *******************************************************************************/

#endif // WDGM_H