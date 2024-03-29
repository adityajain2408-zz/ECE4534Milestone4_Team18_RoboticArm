/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    communication_test.c

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

#include "communication_test.h"

void COMMUNICATION_TEST_Initialize ( void )
{
    createTestThreadQueue();
}


/******************************************************************************
  Function:
    void COMMUNICATION_TEST_Tasks ( void )

  Remarks:
    See prototype in communication_test.h.
 */

void COMMUNICATION_TEST_Tasks ( void )
{
    dbgOutputLoc(TEST_BEFORE_WHILE);
    
    int message_switch = 0;
    
    dbgOutputLoc(TEST_ENTERED_WHILE);
    while (1){
        TestThreadMessage test_message = receiveTestThreadValue();
        
        if(test_message.msg != NULL){
            //We want to send something specific to the server
            SendMessage transmit_message = {"", "", "", ""}; //initializing message to be sent 
            if(*test_message.msg == '0') // ask server the block details
            {
                transmit_message.method = "GET";
                transmit_message.url = "arm_block_status";
                transmit_message.parameters = "pic2";
                sendSendValue(transmit_message);
            }
            else if(*test_message.msg == '1') // tell server that the block is picked up
            {
                transmit_message.method = "POST";
                transmit_message.url = "arm_block_update";
                transmit_message.parameters = "pic2";
                transmit_message.body = "\"msg\": \"Block picked up\"";
                sendSendValue(transmit_message);
            }
            else if(*test_message.msg == '2') //tell server that the block is dropped off
            {
                transmit_message.method = "POST";
                transmit_message.url = "arm_block_update";
                transmit_message.parameters = "pic2";
                transmit_message.body = "\"msg\": \"Block dropped off\"";
                sendSendValue(transmit_message);
            }
        } 
        else 
        {
            SendMessage test_message = {"", "", "", ""};
            switch(message_switch){
                case(0):
                    test_message.method = "POST";
                    test_message.url = "upload";
                    test_message.body = "\"msg\": \"this should work\"";
                    break;

                case(1):
                    test_message.method = "GET";
                    test_message.url = "download";
                    test_message.parameters = "pic2";
                    break;
                    
                case(2):
                    test_message.method = "POST";
                    test_message.url = "upload";
                    
                    static char longMessage[512] = "\"msg\": \"this is going to be longer than 256 bytes 123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\"";
                    test_message.body = longMessage;
                    break;
                    
                case(3):
                    test_message.method = "GET";
                    test_message.url = "download";
                    test_message.parameters = "pic2";
                    break;
            }
            sendSendValue(test_message);
            
            //roll back to 0
            message_switch++;
            if(message_switch > 3){
                message_switch = 0;
            }
        }
    }
}

 

/*******************************************************************************
 End of File
 */
