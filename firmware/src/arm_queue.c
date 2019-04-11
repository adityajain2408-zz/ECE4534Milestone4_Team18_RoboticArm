/* ************************************************************************** */
/** arm_queue.c
 * 
 * Contains implementation of sensor queue helper functions
 */
/* ************************************************************************** */

#include "arm_queue.h"

static QueueHandle_t armQueueHandle = NULL;

unsigned int convertToDegrees(unsigned int ADCValue){
    unsigned int val = (5461 / (ADCValue - 17)) - 4;
    return val > 127 ? 127 : val; 
}

void createArmQueue(){
    if(armQueueHandle == NULL){
        if((armQueueHandle = xQueueCreate(64, sizeof(ArmMessage))) == NULL){
            debugFail();
        }
    } 
    else{
        debugFail();
    }
} 

ArmMessage receiveArmData(){ 
    ArmMessage data;
    dbgOutputLoc(ARM_QUEUE_RX_BEGIN);
    if (armQueueHandle == NULL){
        debugFail();
    }
    if (!xQueueReceive(armQueueHandle, &data, portMAX_DELAY)){
        debugFail();
    }
    dbgOutputLoc(ARM_QUEUE_RX_END);
    return data;
}

void sendArmData(ArmMessage data) {
    dbgOutputLoc(ARM_QUEUE_TX_BEGIN);
    if (armQueueHandle == NULL){
        debugFail();
    }
    if (xQueueSendToBack(armQueueHandle, &data, (TickType_t) 2) != pdPASS){ //Wait for armQueueHandle to create space if available
        debugFail();
    }
    dbgOutputLoc(ARM_QUEUE_TX_END);
}


