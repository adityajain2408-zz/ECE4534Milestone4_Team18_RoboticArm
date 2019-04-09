/* ************************************************************************** */
/** debug.c
 * 
 * Implementation of debug routines
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "debug.h"

 /*
     * Write a value to 7 output lines and toggle an 8th. outVal must be < 127 unsigned
     */
    void dbgOutputVal( int outVal){
        static bool toggleBit = true;
        if (outVal <= 0x7F) //127 in hex 
        {
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0, outVal & 0b1); 
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_1, outVal >> 1 & 0b1); 
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6, outVal >> 2 & 0b1); 
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_8, outVal >> 3 & 0b1); 
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_11, outVal >> 4 & 0b1); 
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_7, outVal >> 5 & 0b1); 
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_8, outVal >> 6 & 0b1); 

            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_6, toggleBit); 
            toggleBit = !toggleBit;
        }
        else
        {
            debugFail();
        }
    }

    /*
     * Write a character to the UART (blocking)
     */
    void dbgUARTVal(unsigned char outVal)
    {
        PLIB_USART_BaudRateSet(USART_ID_1, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_2), 9600);
        PLIB_USART_Enable(USART_ID_1);
        PLIB_USART_TransmitterEnable(USART_ID_1);
        // Wait for the Transmit buffer to be empty.
        while(PLIB_USART_TransmitterBufferIsFull(USART_ID_1));
        // Transmit the character.
        PLIB_USART_TransmitterByteSend(USART_ID_1, outVal);
    }

    /*
     * Write a value to 7 DIFFERENT lines and toggle the 8th. outVal must be < 127 unsigned
     */
    void dbgOutputLoc(unsigned int outVal){
        static bool toggleBit = true;
        if (outVal <= 0x7F) //127 in hex 
        {
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_6, outVal & 0b1); 
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_5, outVal >> 1 & 0b1); 
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_4, outVal >> 2 & 0b1); 
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_3, outVal >> 3 & 0b1); 
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_2, outVal >> 4 & 0b1); 
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_1, outVal >> 5 & 0b1); 
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_0, outVal >> 6 & 0b1);
            
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_10, toggleBit);
            toggleBit = !toggleBit;
        }
        else
        {
            debugFail();
        }
    }

    /*
     * Stop everything, something bad has happened
     */
    void debugFail(){
        dbgOutputLoc(DLOC_ABS_FAILURE);
        taskENTER_CRITICAL(); //Should disable interrupts
        while (1)
        {
            int count = 0;
            for (; count < 20000000; count++){
                continue;
            }
            PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3);
        }
    }


/* *****************************************************************************
 End of File
 */
