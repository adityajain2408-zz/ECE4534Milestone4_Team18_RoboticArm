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

#include "test_thread_queue.h"

static QueueHandle_t testThreadQueueHandle = NULL;

void createTestThreadQueue(){
    if(testThreadQueueHandle == NULL){
        if((testThreadQueueHandle = xQueueCreate(64, sizeof(TestThreadMessage))) == NULL){
            debugFail();
        }
    } 
    else{
        debugFail();
    }
}

TestThreadMessage receiveTestThreadValue(){
    TestThreadMessage data;        
    dbgOutputLoc(TEST_THREAD_QUEUE_RX_BEGIN);
    
    if (testThreadQueueHandle == NULL){
        debugFail();
    }
    if (!xQueueReceive(testThreadQueueHandle, &data, portMAX_DELAY)){
        debugFail();
    }
    return data;
    
    dbgOutputLoc(TEST_THREAD_QUEUE_RX_END);
}

void sendTestThreadValueFromISR(TestThreadMessage data, BaseType_t* xHigherPriorityTaskWoken){
    dbgOutputLoc(TEST_THREAD_QUEUE_TX_ISR_BEGIN);
    
    if (testThreadQueueHandle == NULL){
        debugFail();
    }
    if (xQueueSendFromISR(testThreadQueueHandle, &data, xHigherPriorityTaskWoken) != pdTRUE){
        debugFail();
    }
    
    dbgOutputLoc(TEST_THREAD_QUEUE_TX_ISR_END);
}

void sendTestThreadValue(TestThreadMessage data){
    dbgOutputLoc(TEST_THREAD_QUEUE_TX_BEGIN);
   
    if (testThreadQueueHandle == NULL){
        debugFail();
    }
    if (xQueueSend(testThreadQueueHandle, &data, portMAX_DELAY) != pdTRUE){
        debugFail();
    }
    
    dbgOutputLoc(TEST_THREAD_QUEUE_TX_END);
}


/* *****************************************************************************
 End of File
 */
