/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "project.h"

#include "UARTisr.h"
#include "timerisr.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
//Start of PWM's, UART & initialization of Timer
RGBLed_Start();
RGB_LED_on();
UART_1_Start();
Timer_1_Init();
//String to help the user to start update the Color of RGB LED
UART_1_PutString("If you want to update send 'v'\r\n");

isr_1_StartEx(Custom_UART_RX_ISR);
isr_2_StartEx(Custom_TIMER_RX_ISR);



    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
