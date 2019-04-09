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


void sensorState(SENSOR_STATES * state, SensorMessage sensorMsg, int sensorVal, int * valSum){
    int value = 0;
    //ArmMessage am = {BASE_MOTOR, MOTOR_FORWARD};
    
    switch(*state){       
        case SENSOR_READING_1:
            //dbgOutputVal(sensorVal);
            
            value = convertToDegrees(DRV_ADC_SamplesRead(14));
            dbgOutputVal(convertToDegrees(DRV_ADC_SamplesRead(14)));
            
            ArmMessage am_1 = {BASE_MOTOR, MOTOR_BACKWARD};
            sendArmData(am_1);
            
            if (value <= 5)
            {
                ArmMessage am_1 = {BASE_MOTOR, MOTOR_STOP};
                sendArmData(am_1);
                *state = SENSOR_READING_2;
            }
                    
            *valSum = sensorVal;
            break;
        
        case SENSOR_READING_2:
            //dbgOutputVal(sensorVal);
            
            value = convertToDegrees(DRV_ADC_SamplesRead(14));
            dbgOutputVal(convertToDegrees(DRV_ADC_SamplesRead(14)));
            
            ArmMessage am_2 = {BASE_MOTOR, MOTOR_FORWARD};
            sendArmData(am_2);
            if (value >= 13)
            {
                ArmMessage am_2 = {BASE_MOTOR, MOTOR_STOP};
                sendArmData(am_2);
                *state = SENSOR_READING_1;
            }
            
            *valSum += sensorVal;
            //*state = SENSOR_READING_3;
            break;
            
        case SENSOR_READING_3:
            dbgOutputVal(sensorVal);
            *valSum += sensorVal;
            *state = SENSOR_READING_4;
            break;
            
        case SENSOR_READING_4:
            dbgOutputVal(sensorVal);
            *valSum += sensorVal;
            *state = SENSOR_READING_5;
            break;
            
        case SENSOR_READING_5:
            dbgOutputVal(sensorVal);
            *valSum += sensorVal;
            unsigned int valAvg = *valSum / 5;
            dbgUARTString("%u %s", valAvg, sensorMsg.unit);
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
