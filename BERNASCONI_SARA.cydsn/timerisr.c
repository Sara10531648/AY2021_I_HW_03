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

#include "timerisr.h"
#include "Timer_1.h"
extern uint8_t time;

CY_ISR(Custom_TIMER_RX_ISR)
{
    //Read the time status register to bring interrupt line low
    Timer_1_ReadStatusRegister();
    time=1;
}
/* [] END OF FILE */
