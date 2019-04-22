/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#include "communication_send_queue.h"

static QueueHandle_t sendQueueHandle = NULL;

void createSendQueue(){
    if(sendQueueHandle == NULL){
        if((sendQueueHandle = xQueueCreate(64, sizeof(SendMessage))) == NULL){
            debugFail();
        }
    } 
    else{
        debugFail();
    }
}

SendMessage receiveSendValue(){
    SendMessage data;        
    dbgOutputLoc(COMM_SEND_QUEUE_RX_BEGIN);
    
    if (sendQueueHandle == NULL){
        debugFail();
    }
    if (!xQueueReceive(sendQueueHandle, &data, portMAX_DELAY)){
        debugFail();
    }
    return data;
    
    dbgOutputLoc(COMM_SEND_QUEUE_RX_END);
}

void sendSendValueFromISR(SendMessage data, BaseType_t* xHigherPriorityTaskWoken){
    dbgOutputLoc(COMM_SEND_QUEUE_TX_ISR_BEGIN);
    
    if (sendQueueHandle == NULL){
        debugFail();
    }
    if (xQueueSendFromISR(sendQueueHandle, &data, xHigherPriorityTaskWoken) != pdTRUE){
        debugFail();
    }
    
    dbgOutputLoc(COMM_SEND_QUEUE_TX_ISR_END);
}

void sendSendValue(SendMessage data){
    dbgOutputLoc(COMM_SEND_QUEUE_TX_BEGIN);
   
    if (sendQueueHandle == NULL){
        debugFail();
    }
    if (xQueueSend(sendQueueHandle, &data, portMAX_DELAY) != pdTRUE){
        debugFail();
    }
    
    dbgOutputLoc(COMM_SEND_QUEUE_TX_END);
}

/* *****************************************************************************
 End of File
 */
