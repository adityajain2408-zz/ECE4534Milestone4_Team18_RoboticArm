/* ************************************************************************** */
/** sensor_state.h
 * 
 * Contains definitions of functions used for state machine.
 */
/* ************************************************************************** */

#ifndef _SENSOR_STATE_H    /* Guard against multiple inclusion */
#define _SENSOR_STATE_H


/* This section lists the other files that are included in this file.
 */
#include "debug.h"
#include "arm.h"
#include "arm_control.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

/* States for the sensor state machine */
typedef enum
{   
    SENSOR_READING_0,
    SENSOR_READING_1,
    SENSOR_READING_2,
    SENSOR_READING_3,
    SENSOR_READING_4,
    SENSOR_READING_5,
    SENSOR_READING_6,
    SENSOR_READING_7,
    SENSOR_READING_8,
    SENSOR_READING_9,
    SENSOR_READING_10,
} SENSOR_STATES;

void sensorState(SENSOR_STATES * state, SensorMessage sensorMsg, int potVal, int * count);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
