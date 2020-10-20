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
#ifndef __UART_ISR_H
    #define __UART_ISR_H
    #include "cytypes.h"
    
    CY_ISR_PROTO(Custom_UART_RX_ISR);
    //Function to set the LED as OFF when the PSOC is on
    void RGB_LED_on(void);
    
    //Structure to save RED,GREEN,BLU value
    typedef struct {
        uint8_t red;    ///< Red value   0 - 255
        uint8_t green;  ///< Green value 0 - 255
        uint8_t blu;    ///< Blu value   0 - 255
    } Color;
    
    //Function to start the PWM'S
    void RGBLed_Start(void);
    //Function to start the PWM'S
    void RGBLed_Stop(void);
    //Function to write the new color
    void RGBLed_WriteColor(Color c);
   
  #endif
/* [] END OF FILE */
