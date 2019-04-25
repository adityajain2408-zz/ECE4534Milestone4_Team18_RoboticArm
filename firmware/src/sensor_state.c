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


void sensorState(SENSOR_STATES * state, SensorMessage sensorMsg, int potVal, int * count){
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
            
        case SENSOR_READING_1: // STOP base motor coming from left
            dbgOutputVal(potVal);
            
            if (potVal <= 3)
            {
                ArmMessage am_2 = {BASE_MOTOR, MOTOR_STOP};
                sendArmData(am_2);
                read_jointPot();
                *state = SENSOR_READING_5;
            }
            break;
        
        case SENSOR_READING_2: // STOP base motor coming from right
            dbgOutputVal(potVal);
            
            if (potVal >= 14)
            {
                ArmMessage am_2 = {BASE_MOTOR, MOTOR_STOP};
                sendArmData(am_2);
                read_jointPot();
                *state = SENSOR_READING_5;
            }
            break;
            
        case SENSOR_READING_3: // after gripper movement
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
                *state = SENSOR_READING_10;
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
            
        case SENSOR_READING_8: //Gripper motor open
            if (*count == 10) // after 1.5 s 
            {
                ArmMessage am_3 = {GRIPPER_MOTOR, MOTOR_OPEN};
                sendArmData(am_3);
            }
            if (*count == 20) // after 3 s
            {
                ArmMessage am_3 = {GRIPPER_MOTOR, MOTOR_STOP};
                sendArmData(am_3);
                *count = 0;
                *state = SENSOR_READING_3;
            }
            *count = *count + 1;            
            break;
        
        case SENSOR_READING_9: //Gripper motor close
            if (*count == 10) // after 1.5 s 
            {
                ArmMessage am_3 = {GRIPPER_MOTOR, MOTOR_CLOSE};
                sendArmData(am_3);
            }
            if (*count == 20) // after 3 s
            {
                ArmMessage am_3 = {GRIPPER_MOTOR, MOTOR_STOP};
                sendArmData(am_3);
                *count = 0;
                *state = SENSOR_READING_3;
            }
            *count = *count + 1;            
            break;
        
        case SENSOR_READING_10: // Check base motor position and guide gripper to open or close
            dbgOutputVal(potVal);
            
            if (potVal >= 9)
            {
                *state = SENSOR_READING_9;
            }
            else
            {
                *state = SENSOR_READING_8;
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
