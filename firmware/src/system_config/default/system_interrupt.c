/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system/common/sys_common.h"
#include "app.h"
#include "arm.h"
#include "communication_tx.h"
#include "communication_rx.h"
#include "communication_stats.h"
#include "communication_test.h"
#include "system_definitions.h"
#include "debug.h"
#include "wifly_uart_queues.h"
#include "limits.h"
#include "sensor_queue.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************
 


void IntHandlerDrvTmrInstance0(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    /*
    dbgOutputLoc(DLOC_ISR_ADC_ENTERED);
    
    //Grab value from ADC -> convert using routine in sensorQueue.c
    int pot_value = convertToDegrees(DRV_ADC_SamplesRead(14));
    SensorMessage sm = {pot_value, "degrees"};
    
    //Send to sensor queue
    dbgOutputLoc(DLOC_ISR_ADC_QUEUE_TX_BEFORE);
    sendSensorDataFromISR(sm, &xHigherPriorityTaskWoken);
    dbgOutputLoc(DLOC_ISR_ADC_QUEUE_TX_AFTER);
    
    dbgOutputLoc(DLOC_ISR_ADC_LEAVING);
    
    */
    dbgOutputLoc(DLOC_ISR_TIMER_ENTERED);
    
    static int count = 0;
    //Every 2 seconds send statistics
    //Every 0.1 seconds send a message
    if(count % 20 == 0){
        StatsMessage time = {INT_MIN, INT_MIN, INT_MIN};
        sendStatsValueFromISR(time, &xHigherPriorityTaskWoken);
    } else {
        TestThreadMessage d = {"0"};
        sendTestThreadValueFromISR(d, &xHigherPriorityTaskWoken);
    }
    count++;
    
    dbgOutputLoc(DLOC_ISR_TIMER_LEAVING);
    
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_2);
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

void __ISR(_UART_1_VECTOR, IPL1AUTO) UART1Handler(void)
{
    dbgOutputLoc(DLOC_ISR_UART_ENTERED);
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    //check for errors
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_ERROR))
    {
        debugFail();
    }
    
    //receiving on UART 1
    else if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_RECEIVE)){
        dbgOutputLoc(DLOC_ISR_UART_RX_ENTERED);
        if (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1))
        {
            dbgOutputLoc(DLOC_ISR_UART_RX_QUEUE_TRANS);
            char c = PLIB_USART_ReceiverByteReceive(USART_ID_1);
            sendWifly_rx_ValueFromISR(c, &xHigherPriorityTaskWoken);
            PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);
        }
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);
    }
    
    //transmitting on UART 1
    else if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT))
    {
        dbgOutputLoc(DLOC_ISR_UART_TX_ENTERED);
        
        if (wifly_tx_QueueIsEmptyFromISR()) //something went wrong, return
        {
            PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
        }
        else if (PLIB_USART_TransmitterIsEmpty(USART_ID_1)) //we can send something
        {
            dbgOutputLoc(DLOC_ISR_UART_TX_QUEUE_RECV);
            char outVal = receiveWifly_tx_ValueFromISR(&xHigherPriorityTaskWoken); 
            PLIB_USART_TransmitterByteSend(USART_ID_1, outVal);
            PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
        }
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }
    else
    {
        debugFail();
    }
    dbgOutputLoc(DLOC_ISR_UART_LEAVING);
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

 /*******************************************************************************
 End of File
*/
