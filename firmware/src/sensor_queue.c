/* ************************************************************************** */
/** sensorQueue.c
 * 
 * Contains implementation of sensor queue helper functions
 */
/* ************************************************************************** */

#include "sensor_queue.h"

static QueueHandle_t sensorQueueHandle = NULL;

//Move me outside of interrupt file (project requirement)
unsigned int convertToCentimeters(unsigned int ADCValue){
    unsigned int val = (5461 / (ADCValue - 17)) - 4;
    
    return val > 127 ? 127 : val; 
}

int convertTable(unsigned int ADCValue){
    // ADCValue, distance (cm)
    int table[16] = {
        460, 10,
        256, 20,
        184, 30,
        154, 40,
        123, 50,
        102, 60,
        92,  70,
        84,  60,
    };
    
    //interpolate ADC value with known table values
    //return val
    int x;
    for (x = 0; x < 14; x = x+2){
        if(ADCValue >= table[x]){
            return table[x+1];
        }
        
        if (ADCValue <= table[x] && ADCValue >= table[x+2]){
            return (table[x+1]+table[x+3])/2;
        }
    }
    
    return table[15];
}

void createSensorQueue() {
    if(sensorQueueHandle == NULL){
        if((sensorQueueHandle = xQueueCreate(64, sizeof(SensorMessage))) == NULL){
            debugFail();
        }
    } 
    else{
        debugFail();
    }
} 

SensorMessage receiveSensorData(){ 
    SensorMessage data;
    dbgOutputLoc(SENSOR_QUEUE_RX_BEGIN);
    if (sensorQueueHandle == NULL){
        debugFail();
    }
    if (!xQueueReceive(sensorQueueHandle, &data, portMAX_DELAY)){
        debugFail();
    }
    dbgOutputLoc(SENSOR_QUEUE_RX_END);
    return data;
}

void sendSensorData(SensorMessage data, BaseType_t* xHigherPriorityTaskWoken) {
    dbgOutputLoc(SENSOR_QUEUE_TX_BEGIN);
    if (sensorQueueHandle == NULL){
        debugFail();
    }
    if (xQueueSendFromISR(sensorQueueHandle, &data, xHigherPriorityTaskWoken) != pdTRUE){
        debugFail();
    }
    dbgOutputLoc(SENSOR_QUEUE_TX_END);
}

