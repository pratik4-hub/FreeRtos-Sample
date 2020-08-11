# ProjectWorkspace
This project is based on STM32F446RE Nucleo-64 board. FreeRTOS is used for sheduling multiple task at a time.
Vtaskstartshedular() manage to handle all the sheduled tasks.
UART is coonected to pin PA2 and PA3 which is used for serial communication.
Commands must be given to switch on or off the relay according to the need.
13 tasks are sheduled in which one task is running continueously for UART Interrupt Signals.
Remaining 12 tasks are in self-suspended mode until they get call from ISR.
To run the project, enter commands over UART e.g. SR(1,ON,5000), SR(10,OFF,40000) in which,
first parameter is task number(upto 12),second is status(ON/OFF), third one is time in milliseconds.
See the Enabled GPIO Pins in main.c for each task
