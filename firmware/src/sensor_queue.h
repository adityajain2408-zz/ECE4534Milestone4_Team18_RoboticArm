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
    int sensorValue;
    char *unit;
} SensorMessage;


void createSensorQueue();

SensorMessage receiveSensorData();

void sendSensorData(SensorMessage data, BaseType_t* xHigherPriorityTaskWoken);
    
/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
