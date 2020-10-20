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
#include "UARTisr.h"
#include "timerisr.h"

#include "UART_1.h"
#include "PWM_B.h"
#include "PWM_RG.h"
#include "Timer_1.h"

//Glabal variable:used in timerisr
uint8_t time=0;

char recived;
uint8_t byte=0;
uint8_t ok=0;
uint8_t BYTE1;
uint8_t BYTER;
uint8_t BYTEG;
uint8_t BYTEB;
uint8_t BYTE2;

static void RGBLed_WriteRed(uint8_t red);       // Write new red value
static void RGBLed_WriteGreen(uint8_t green);   // Write new green value
static void RGBLed_WriteBlu(uint8_t blu);       // Write new blu value


CY_ISR(Custom_UART_RX_ISR)
{   //ok is equal to zero only when the devise is powered on,the application is not connected yet
    if(ok==0)
    {   //Save the byte recived
        recived=UART_1_ReadRxData();
        if(recived=='v')
        {
            //If it is correct we can start to Update Color
            UART_1_PutString("RGB LED Program $$$\r\n");
            ok=1;
        } 
    }
    else if (ok==1)
    {
        //The Timer stops every time a new byte arrived
        Timer_1_Stop();
        Timer_1_WriteCounter(255);
        //Check if the time interval between the arrival of 2 consecutive bytes is grater than 5s
        if (time==1)
           {
              //UART_1_PutString("TOO SLOW\r\n");
                //The Color choice must start again
                byte=0;
                //Set time to 0 again
                time=0;
            }
       else
            {
            //If time between bytes is enough short we can restart the timer
            Timer_1_Start();
            //Every time we sand a new byte the counter is incremented
            byte++;
            switch (byte)
            {
                case 1:
                //I'm sending the first byte:header
                BYTE1=UART_1_ReadRxData();   
                if (BYTE1!=0XA0)
                {   Timer_1_Stop();
                    Timer_1_WriteCounter(255);
                    //If Header is not correct start again to send the 5 bytes
                    byte=0;
                }
                
                break;
                case 2:
                //Save RED channel configuration 
                    BYTER=UART_1_ReadRxData();
                break;
                case 3:
                //Save RED channel configuration 
                    BYTEG=UART_1_ReadRxData();
                break;
                case 4:
                //Save RED channel configuration 
                    BYTEB=UART_1_ReadRxData();
                break;
                default:
                    {
                    BYTE2=UART_1_ReadRxData();
                    if (BYTE2==0XC0)
                    {
                    //If the TAIL is correct, save the 3 Values for theRGB channels
                     const Color COLORE = {BYTER,BYTEG,BYTEB};
                     RGBLed_WriteColor(COLORE);}
                    
                    else
                    {
                        Timer_1_Stop();
                        Timer_1_WriteCounter(255);}
                     byte=0;
                break;
                    }
            } 
    }  
    }
}

  void RGB_LED_on(void)
{
    //All'accensione il LED deve essere spento (PS:Output 1 è il verde)
    PWM_RG_WriteCompare1(255);
    PWM_RG_WriteCompare2(255);
    PWM_B_WriteCompare(255);
}
void RGBLed_Start()
{
    // Start PWM Components
    PWM_RG_Start(); // Start PWM connected to red and green channels
    PWM_B_Start();  // Start PWM connected to blu channel
}

void RGBLed_Stop()
{
    // Stop PWM Components
    PWM_RG_Stop(); // Stop PWM connected to red and green channels
    PWM_B_Stop();  // Stop PWM connected to blu channel
}

void RGBLed_WriteColor(Color c)
{
    RGBLed_WriteRed(c.red);
    RGBLed_WriteGreen(c.green);
    RGBLed_WriteBlu(c.blu);
}

static void RGBLed_WriteRed(uint8_t red)
{
    PWM_RG_WriteCompare2(255-red);
}

static void RGBLed_WriteGreen(uint8_t green)
{
    PWM_RG_WriteCompare1(255-green);
}

static void RGBLed_WriteBlu(uint8_t blu)
{
    PWM_B_WriteCompare(255-blu);
}   


/* [] END OF FILE */
