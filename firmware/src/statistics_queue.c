/* ************************************************************************** */
/** statistics_queue.c
 * 
 * Contains implementation of motor queue helper functions
 */
/* ************************************************************************** */

#include "statistics_queue.h"

static QueueHandle_t statsQueueHandle = NULL;

void createStats_Queue() {
    if(statsQueueHandle == NULL){
        if((statsQueueHandle = xQueueCreate(64, sizeof(StatsMessage))) == NULL){
            debugFail();
        }
    } 
    else{
        debugFail();
    }
} 

StatsMessage receiveStatsValue(){ 
    StatsMessage data;        
    dbgOutputLoc(STATS_QUEUE_RX_BEGIN);
    
    if (statsQueueHandle == NULL){
        debugFail();
    }
    if (!xQueueReceive(statsQueueHandle, &data, portMAX_DELAY)){
        debugFail();
    }
    return data;
    
    dbgOutputLoc(STATS_QUEUE_RX_END);
}

void sendStatsValueFromISR(StatsMessage data, BaseType_t* xHigherPriorityTaskWoken){
    dbgOutputLoc(STATS_QUEUE_TX_ISR_BEGIN);
    
    if (statsQueueHandle == NULL){
        debugFail();
    }
    if (xQueueSendFromISR(statsQueueHandle, &data, xHigherPriorityTaskWoken) != pdTRUE){
        debugFail();
    }
    
    dbgOutputLoc(STATS_QUEUE_TX_ISR_BEGIN);
}

StatsMessage receiveStatsValueFromISR(BaseType_t* xHigherPriorityTaskWoken)
{
    dbgOutputLoc(STATS_QUEUE_RX_ISR_BEGIN);
    StatsMessage message;
    if (xQueueReceiveFromISR(statsQueueHandle, &message, xHigherPriorityTaskWoken) != pdTRUE){
        debugFail();
    }
    dbgOutputLoc(STATS_QUEUE_RX_ISR_END);
    return message;
}

void sendStatsValue(StatsMessage data){
    dbgOutputLoc(STATS_QUEUE_TX_BEGIN);
   
    if (statsQueueHandle == NULL){
        debugFail();
    }
    if (xQueueSend(statsQueueHandle, &data, portMAX_DELAY) != pdTRUE){
        debugFail();
    }
    
    dbgOutputLoc(STATS_QUEUE_TX_END);
}

BaseType_t statsQueueIsEmptyFromISR(){
    return xQueueIsQueueEmptyFromISR(statsQueueHandle);
}