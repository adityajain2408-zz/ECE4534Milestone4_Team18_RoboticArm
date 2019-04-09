/* ************************************************************************** */
/** sensorQueue.h
 * 
 * Contains definitions of sensor queue helper functions
 */
/* ************************************************************************** */

#include "FreeRTOS.h"
#include "queue.h"
#include "debug.h"
#include "arm.h"
#include "arm_queue.h"

#ifndef _ARM_CONTROL_H    /* Guard against multiple inclusion */
#define _ARM_CONTROL_H


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
void baseMotor_Fwd();

void baseMotor_Stop();

void baseMotor_Bwd();

void processArmMessage(MotorType someMotorType, MotorDirection someMotorDirection);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _ARM_CONTROL_H */

/* *****************************************************************************
 End of File
 */
