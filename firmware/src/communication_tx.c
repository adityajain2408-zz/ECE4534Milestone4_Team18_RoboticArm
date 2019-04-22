/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    communication_tx.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

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

#include "communication_tx.h"

void COMMUNICATION_TX_Initialize ( void )
{
    comms_tx_initialize();
}


/******************************************************************************
  Function:
    void COMMUNICATION_TX_Tasks ( void )

  Remarks:
    See prototype in communication_tx.h.
 */

void COMMUNICATION_TX_Tasks ( void )
{
    dbgOutputLoc(COMS_TX_BEFORE_WHILE);
    
    int sequence = 0;
    
    dbgOutputLoc(COMS_TX_ENTERED_WHILE);
    while (1){
        //blocking receive on communication_send queue 
        SendMessage unpacked_message = receiveSendValue();
        
        // creating empty string to be over written
        static char http_string[512];
        
        //call subroutine to parse the message into http string
        createHTTPString(unpacked_message.method, 
                            unpacked_message.url, 
                            unpacked_message.parameters, 
                            unpacked_message.body, 
                            sequence,
                            http_string);
        
        //call subroutine to send the string to Wifly_tx_Queue() (bytes)
        sendHTTPString(http_string);
        sequence++;
    }
}

 

/*******************************************************************************
 End of File
 */
