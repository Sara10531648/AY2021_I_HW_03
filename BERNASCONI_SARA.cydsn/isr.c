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
#include "isr.h"

#include "UART_1.h"

#include "project.h"
#include "stdio.h"

static char message[20] = {'\0'};
char recived;
CY_ISR(Custom_UART_RX_ISR)
{
    if (UART_1_ReadRxStatus() == UART_1_RX_STS_FIFO_NOTEMPTY)
    {// Con questo comando leggo ciò che ho scritto dal pc
        recived = UART_1_ReadRxData();
        if (recived == 'v')
        //stringa di comando
            sprintf(message,"RGB LED Program $$$\r\n");
        else
            sprintf(message,"Errore\r\n");
        //stanmpo stringa
        UART_1_PutString(message);
    }
}

void RGB_LED_start()
{
    Pin_B_Write(0);
    Pin_R_Write(0);
    Pin_G_Write(0);
}
    
/* [] END OF FILE */
