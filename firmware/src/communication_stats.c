/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    communication_stats.c

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

#include "communication_stats.h"
#include "limits.h"

/*******************************************************************************
  Function:
    void COMMUNICATION_STATS_Initialize ( void )

  Remarks:
    See prototype in communication_stats.h.
 */

void COMMUNICATION_STATS_Initialize ( void )
{
    createStats_Queue();
}


/******************************************************************************
  Function:
    void COMMUNICATION_STATS_Tasks ( void )

  Remarks:
    See prototype in communication_stats.h.
 */

void COMMUNICATION_STATS_Tasks ( void )
{
    dbgOutputLoc(STATS_BEFORE_WHILE);
    
    static int rec = 0;
    StatsMessage saved = {0, 0, 0};
    
    dbgOutputLoc(STATS_ENTERED_WHILE);
    while (1){
        StatsMessage message = receiveStatsValue();
        if(message.missed == INT_MIN){
            SendMessage stat_update = {"", "", "", ""};
            
            stat_update.method = "POST";
            stat_update.url = "stats";
            
            char statBody[100];
            sprintf(statBody, "\"missed\": %d, \"received\": %d",
                    saved.missed,
                    rec);
            
            stat_update.body = statBody;

            sendSendValue(stat_update);
        } else {
            saved.sent += message.sent;
            rec = message.received;
            saved.missed += message.missed;
        }
        
        
    }
}

 

/*******************************************************************************
 End of File
 */
