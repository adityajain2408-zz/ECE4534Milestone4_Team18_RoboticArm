/* ************************************************************************** */
/** sensorQueue.h
 * 
 * Contains definitions of sensor queue helper functions
 */
/* ************************************************************************** */

#include "FreeRTOS.h"
#include "queue.h"
#include "debug.h"

#ifndef _SENSORQUEUE_H    /* Guard against multiple inclusion */
#define _SENSORQUEUE_H


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
    
//Sensor Message Struct - Struct passed in sensor queue    
typedef struct {
    int sensorValue_base;
    int sensorValue_joint;
    char *unit;
} SensorMessage;


void createSensorQueue();

SensorMessage receiveSensorData();

void sendSensorData(SensorMessage data, BaseType_t* xHigherPriorityTaskWoken);
    
/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _SENSOR_QUEUE_H */

/* *****************************************************************************
 End of File
 */
