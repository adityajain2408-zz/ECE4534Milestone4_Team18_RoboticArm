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


void sensorState(SENSOR_STATES * state, SensorMessage sensorMsg, int potVal){
    
    switch(*state){
        case SENSOR_READING_0:
            read_basePot();
            dbgOutputVal(potVal);
            
            if (potVal >= 9)
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
            dbgOutputVal(potVal);
            
            if (potVal <= 3)
            {
                ArmMessage am_1 = {BASE_MOTOR, MOTOR_BACKWARD};
                sendArmData(am_1);
                *state = SENSOR_READING_2;
            }
            break;
        
        case SENSOR_READING_2:
            dbgOutputVal(potVal);
            
            if (potVal >= 14)
            {
                ArmMessage am_2 = {BASE_MOTOR, MOTOR_FORWARD};
                sendArmData(am_2);
                *state = SENSOR_READING_3;
            }
            break;
            
        case SENSOR_READING_3:
            dbgOutputVal(potVal);
            ArmMessage am_2 = {BASE_MOTOR, MOTOR_STOP};
            sendArmData(am_2);
            read_jointPot();
            *state = SENSOR_READING_4;
            break;
            
        case SENSOR_READING_4:
            dbgOutputVal(potVal);
            
            if (potVal <= 6)
            {
                ArmMessage am = {JOINT_MOTOR, MOTOR_UP};
                sendArmData(am);
                *state = SENSOR_READING_5;
            }
            break;
            
        case SENSOR_READING_5:
            dbgOutputVal(potVal);
            
            if (potVal <= 3)
            {
                ArmMessage am_1 = {JOINT_MOTOR, MOTOR_DOWN};
                sendArmData(am_1);
                *state = SENSOR_READING_6;
            }
            break;
        
        case SENSOR_READING_6:
            dbgOutputVal(potVal);
            
            if (potVal >= 6)
            {
                ArmMessage am_2 = {JOINT_MOTOR, MOTOR_STOP};
                sendArmData(am_2);
                *state = SENSOR_READING_7;
            }
            break;
        
        case SENSOR_READING_7:
            dbgOutputVal(potVal);
            *state = SENSOR_READING_7;
            break;
            
        default:
            debugFail();
            break;
    }
}

/* *****************************************************************************
 End of File
 */
