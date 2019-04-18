/* ************************************************************************** */
/** arm_queue.h
 * 
 * Contains definitions of sensor queue helper functions
 */
/* ************************************************************************** */

#include "FreeRTOS.h"
#include "queue.h"
#include "debug.h"

#ifndef _ARM_QUEUE_H    /* Guard against multiple inclusion */
#define _ARM_QUEUE_H


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
typedef enum _m_type {BASE_MOTOR, GRIPPER_MOTOR, JOINT_MOTOR} 
    MotorType;
        
typedef enum _m_direction {MOTOR_FORWARD, MOTOR_BACKWARD, MOTOR_STOP, MOTOR_UP, MOTOR_DOWN} 
    MotorDirection;
    
//Arm Message Struct - Struct passed in arm queue    
typedef struct {
    MotorType motorType;
    MotorDirection motorDirection;
} ArmMessage;


void createArmQueue();

ArmMessage receiveArmData();

void sendArmData(ArmMessage data);
    
/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _ARM_QUEUE_H */

/* *****************************************************************************
 End of File
 */
