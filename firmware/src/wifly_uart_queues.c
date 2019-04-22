/* ************************************************************************** */
/** wifly_uart_queues.c
 * 
 * Contains implementation of motor queue helper functions
 */
/* ************************************************************************** */

#include "wifly_uart_queues.h"

static QueueHandle_t wiflyQueueTXHandle = NULL;

void createWifly_tx_Queue() {
    if(wiflyQueueTXHandle == NULL){
        if((wiflyQueueTXHandle = xQueueCreate(128, sizeof(char))) == NULL){
            debugFail();
        }
    } 
    else{
        debugFail();
    }
} 

char receiveWifly_tx_Value(){ 
    char data;        
    dbgOutputLoc(WIFLYTX_QUEUE_RX_BEGIN);
    
    if (wiflyQueueTXHandle == NULL){
        debugFail();
    }
    if (!xQueueReceive(wiflyQueueTXHandle, &data, portMAX_DELAY)){
        debugFail();
    }
    return data;
    
    dbgOutputLoc(WIFLYTX_QUEUE_RX_END);
}

void sendWifly_tx_ValueFromISR(char data, BaseType_t* xHigherPriorityTaskWoken){
    dbgOutputLoc(WIFLYTX_QUEUE_TX_FROMISR_BEGIN);
    
    if (wiflyQueueTXHandle == NULL){
        debugFail();
    }
    if (xQueueSendFromISR(wiflyQueueTXHandle, &data, xHigherPriorityTaskWoken) != pdTRUE){
        debugFail();
    }
    
    dbgOutputLoc(WIFLYTX_QUEUE_TX_FROMISR_END);
}

char receiveWifly_tx_ValueFromISR(BaseType_t* xHigherPriorityTaskWoken)
{
    dbgOutputLoc(WIFLYTX_REC_FROMISR_BEGIN);
    char message;
    if (xQueueReceiveFromISR(wiflyQueueTXHandle, &message, xHigherPriorityTaskWoken) != pdTRUE){
        debugFail();
    }
    dbgOutputLoc(WIFLYTX_QUEUE_TX_FROMISR_END);
    return message;
}

void sendWifly_tx_Value(char data){
    dbgOutputLoc(WIFLYTX_QUEUE_TX_BEGIN);
   
    if (wiflyQueueTXHandle == NULL){
        debugFail();
    }
    if (xQueueSend(wiflyQueueTXHandle, &data, portMAX_DELAY) != pdTRUE){
        debugFail();
    }
    
    dbgOutputLoc(WIFLYTX_QUEUE_TX_END);
}

BaseType_t wifly_tx_QueueIsEmptyFromISR(){
    return xQueueIsQueueEmptyFromISR(wiflyQueueTXHandle);
}

///////////////////////////////////

static QueueHandle_t wiflyQueueRXHandle = NULL;

void createWifly_rx_Queue() {
    if(wiflyQueueRXHandle == NULL){
        if((wiflyQueueRXHandle = xQueueCreate(128, sizeof(char))) == NULL){
            debugFail();
        }
    } 
    else{
        debugFail();
    }
} 

char receiveWifly_rx_Value(){ 
    char data;
    dbgOutputLoc(WIFLYRX_QUEUE_RX_BEGIN);
    if (wiflyQueueRXHandle == NULL){
        debugFail();
    }
    if (!xQueueReceive(wiflyQueueRXHandle, &data, portMAX_DELAY)){
        debugFail();
    }
    dbgOutputLoc(WIFLYRX_QUEUE_RX_END);
    return data;
}

void sendWifly_rx_ValueFromISR(char data, BaseType_t* xHigherPriorityTaskWoken) {
    dbgOutputLoc(WIFLYRX_QUEUE_TX_FROMISR_BEGIN);
    if (wiflyQueueRXHandle == NULL){
        debugFail();
    }
    if (xQueueSendFromISR(wiflyQueueRXHandle, &data, xHigherPriorityTaskWoken) != pdTRUE){
        debugFail();
    }
    dbgOutputLoc(WIFLYRX_QUEUE_TX_FROMISR_END);
}

char receiveWifly_rx_ValueFromISR(BaseType_t* xHigherPriorityTaskWoken)
{
    dbgOutputLoc(WIFLYRX_REC_FROMISR_BEGIN);
    char message;
    if (xQueueReceiveFromISR(wiflyQueueRXHandle, &message, xHigherPriorityTaskWoken) != pdTRUE){
        debugFail();
    }
    dbgOutputLoc(WIFLYRX_REC_FROMISR_END);
    return message;
}

void sendWifly_rx_Value(char data){
    dbgOutputLoc(WIFLYRX_QUEUE_TX_BEGIN);
    if (wiflyQueueRXHandle == NULL){
        debugFail();
    }
    if (xQueueSend(wiflyQueueRXHandle, &data, portMAX_DELAY) != pdTRUE){
        debugFail();
    }
    dbgOutputLoc(WIFLYRX_QUEUE_TX_END);
}

BaseType_t wifly_rx_QueueIsEmptyFromISR(){
    return xQueueIsQueueEmptyFromISR(wiflyQueueRXHandle);
}