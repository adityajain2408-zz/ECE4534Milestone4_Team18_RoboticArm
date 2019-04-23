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
                TestThreadMessage d = {"1"}; //Transmit value that arm has picked up the block
                sendTestThreadValue(d);
                
                *state = SENSOR_READING_1;
            }
            else
            {
                ArmMessage am_0 = {BASE_MOTOR, MOTOR_BACKWARD};
                sendArmData(am_0);
                
                TestThreadMessage d = {"2"}; //Transmit value that arm has dropped the block
                sendTestThreadValue(d);
                *state = SENSOR_READING_2;
            }
            
            
            break;
            
        case SENSOR_READING_1: //STOP base motor coming from left
            dbgOutputVal(potVal);
            
            if (potVal <= 3)
            {
                ArmMessage am_2 = {BASE_MOTOR, MOTOR_STOP};
                sendArmData(am_2);
                read_jointPot();
                *state = SENSOR_READING_5;
            }
            break;
        
        case SENSOR_READING_2: //STOP base motor coming from right
            dbgOutputVal(potVal);
            
            if (potVal >= 14)
            {
                ArmMessage am_2 = {BASE_MOTOR, MOTOR_STOP};
                sendArmData(am_2);
                read_jointPot();
                *state = SENSOR_READING_5;
            }
            break;
            
        case SENSOR_READING_3: // gripper
            dbgOutputVal(potVal);
            read_jointPot();
            *state = SENSOR_READING_4;
            break;
            
        case SENSOR_READING_4: //Joint UP
            dbgOutputVal(potVal);
            
            if (potVal <= 6)
            {
                ArmMessage am = {JOINT_MOTOR, MOTOR_UP};
                sendArmData(am);
                *state = SENSOR_READING_7;
            }
            break;
            
        case SENSOR_READING_5: //Joint DOWN
            dbgOutputVal(potVal);
            
            if (potVal >= 3)
            {
                ArmMessage am_1 = {JOINT_MOTOR, MOTOR_DOWN};
                sendArmData(am_1);
                *state = SENSOR_READING_6;
            }
            break;
        
        case SENSOR_READING_6: //STOP Joint Motor coming from up (Joint Position DOWN)
            dbgOutputVal(potVal);
            
            if (potVal >= 6)
            {
                ArmMessage am_2 = {JOINT_MOTOR, MOTOR_STOP};
                sendArmData(am_2);
                read_basePot();
                *state = SENSOR_READING_3;
            }
            break;
        
        case SENSOR_READING_7: //STOP Joint Motor coming from down (Joint Position UP)
            dbgOutputVal(potVal);
            
            if (potVal <= 3)
            {
                ArmMessage am_2 = {JOINT_MOTOR, MOTOR_STOP};
                sendArmData(am_2);
                read_basePot();
                *state = SENSOR_READING_0;
            }
            
            break;
            
        default:
            debugFail();
            break;
    }
}

/* *****************************************************************************
 End of File
 */
