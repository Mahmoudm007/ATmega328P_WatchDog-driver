[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/tOuFQ3QF)

# LED Blinking with Watchdog Supervision Project

## Project Overview

This project implements a LED blinking system with a watchdog supervision capability, using various software components to manage different hardware drivers and functionalities. The primary goal is to ensure the LED blinks with precise periodicity while being supervised by a watchdog timer to detect and recover from potential system failures.

## Components

1. **GPIO Management (GPIOMgr)**
    - **GPIO_Init:** Initializes GPIO configuration for the pin controlling the LED.
    - **GPIO_Write:** Writes a specific value (0 or 1) to the pin to control the LED state.

2. **LED Management (LEDMgr)**
    - **LED_Init:** Initializes internal variables of the LED component.
    - **LED_Manage:** Manages LED blinking actions using the GPIO_Write function, called every 10ms to ensure a 500ms on/off cycle for the LED.

3. **Watchdog Driver (WDGDrv)**
    - **WDGDrv_Init:** Configures the watchdog driver with the following features:
        - Sets the maximum timeout value to 50ms.
        - Disables window mode.
        - Enables the early interrupt feature.
        - Activates the watchdog.
    - **WDGDrv_IsrNotification:** Checks if WDGM_MainFunction is not stuck and if WDGM state is OK to refresh the watchdog timer; otherwise, allows the system to reset.

4. **Watchdog Management (WDGM)**
    - **WDGM_Init:** Initializes internal variables of the watchdog management component.
    - **WDGM_MainFunction:** Periodically called every 20ms to supervise the LEDM entity by checking the number of calls to LEDM_Manage within a 100ms period.
    - **WDGM_ProvideSupervisionStatus:** Provides the supervision status of the LEDM entity to the WDGDrv.
    - **WDGM_AlivenessIndication:** Called from LEDM_Manage to confirm timely execution of LEDM_Manage.

5. **Timer Drivers**
    - **Timer1:** Generates an interrupt every 1ms.
    - **Timer2:** Generates an interrupt every 50ms.

6. **Other Drivers**
    - **LED Driver:** Controls the LED state.
    - **Buzzer Driver:** Manages buzzer operations.
    - **EXTI Driver:** Handles external interrupt configurations.
    - **Interrupt Driver:** Manages general interrupt handling mechanisms.
    - **LCD Driver:** Manages operations related to the LCD display.

## Project Statement

The project implements an LED blinking capability with watchdog supervision. The LED blinking is handled by two software components: LEDMgr and GPIO. GPIO provides initialization and write functions to control the LED. LEDMgr manages the LED blinking actions, ensuring the LED toggles every 500ms, called from a super loop every 10ms.

Watchdog management is handled by WDGDrv and WDGM. WDGDrv implements a complete driver for the watchdog peripheral, configuring it with a 50ms timeout, early interrupt feature, and activation of the watchdog. It uses the WDGDrv_IsrNotification to refresh the watchdog timer based on the status provided by WDGM.

WDGM provides supervision for the LEDM entity, ensuring it functions correctly within a 100ms period. It initializes internal variables, checks the status of LEDM_MainFunction calls, and provides this status to WDGDrv. WDGM also includes an aliveness indication function to confirm timely execution of LEDM_Manage.

The overall system ensures reliable LED blinking with precise timing, supervised by the watchdog timer to detect and recover from any failures, maintaining system robustness and stability.


## Project Scenario
1. **Positive Scenario**

-that checks the periodicity of the LED Blinking, Call of the
LEDM_Manage, Call of the WDGM_MainFunction and refreshment of the WDGDrv.

![Alt Text](assets/1.gif)

2. **Negative Scenario 1**

-that comments the call of the WDGM_MainFunction and checks that
the watchdog reset occurred after 50ms.

![Alt Text](assets/2.gif)


3. **Negative Scenario 2**

- that comments the call of the WDGM_AlivenessIndication from the
LEDM_Manage while the WDGM_MainFunction is executed periodically and checks that
the watchdog reset occurs after 100ms.

![Alt Text](assets/3.gif)

4. **Negative Scenario 3**

-that changes the periodicity of the call of the LEDM_MainFunction to
be every 5ms and checks that watchdog reset occurs after 100ms.

![Alt Text](assets/4.gif)
