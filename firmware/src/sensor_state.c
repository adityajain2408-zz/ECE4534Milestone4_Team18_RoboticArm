/* ************************************************************************** */
/** sensor_state.c
 * 
 * Implementation of the state machine
 */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
#include "sensor_queue.h"
#include "sensor_state.h"


void sensorState(SENSOR_STATES * state, SensorMessage sensorMsg, int sensorVal_base, int sensorVal_joint){
    
    switch(*state){
        case SENSOR_READING_0:
            dbgOutputVal(sensorVal_base);
            
            if (sensorVal_base >= 10)
            {
                ArmMessage am_0 = {BASE_MOTOR, MOTOR_FORWARD};
                sendArmData(am_0);
            }
            else
            {
                ArmMessage am_0 = {BASE_MOTOR, MOTOR_BACKWARD};
                sendArmData(am_0);
            }
            
            *state = SENSOR_READING_1;
            break;
            
        case SENSOR_READING_1:
            dbgOutputVal(sensorVal_base);
            
            if (sensorVal_base <= 4)
            {
                ArmMessage am_1 = {BASE_MOTOR, MOTOR_BACKWARD};
                sendArmData(am_1);
                *state = SENSOR_READING_2;
            }
            break;
        
        case SENSOR_READING_2:
            dbgOutputVal(sensorVal_base);
            
            if (sensorVal_base >= 15)
            {
                ArmMessage am_2 = {BASE_MOTOR, MOTOR_FORWARD};
                sendArmData(am_2);
                *state = SENSOR_READING_1;
            }
            break;
            
        case SENSOR_READING_3:
            dbgOutputVal(sensorVal_joint);
            *state = SENSOR_READING_4;
            break;
            
        case SENSOR_READING_4:
            dbgOutputVal(sensorVal_joint);
            *state = SENSOR_READING_5;
            break;
            
        case SENSOR_READING_5:
            dbgOutputVal(sensorVal_joint);
            *state = SENSOR_READING_1;
            break;
            
        default:
            debugFail();
            break;
    }
}

/* *****************************************************************************
 End of File
 */
