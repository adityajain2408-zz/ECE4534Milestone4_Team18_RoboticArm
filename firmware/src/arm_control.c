/* ************************************************************************** */
/** arm_control.c
 * 
 * Implementation of debug routines
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "arm_control.h"

    /*
     * Start moving baseMotor Forward
     */
    void baseMotor_Fwd()
    {
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3, true); //Turning the LED on 
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, false); // orange off - relay module - pic pin # 4
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_0, true); // black on - relay module - pic pin # 3
              
    }

    /*
     * Start moving baseMotor Backward
     */
    void baseMotor_Bwd()
    {
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3, true); //Turning the LED on 
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, true); // orange on - relay module - pic pin # 4
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_0, false); //black off - relay module - pic pin # 3
    }

    /*
     * Stop the base motor
     */
    void baseMotor_Stop()
    {
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_0, false); //black off - relay module - pic pin # 3
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, false); // orange off - relay module  - pic pin #4 
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3, false); //Turning the LED off 
    }

    
    void processArmMessage(MotorType someMotorType, MotorDirection someMotorDirection)
    {
        if (someMotorType == BASE_MOTOR && someMotorDirection == MOTOR_FORWARD)
        {
            baseMotor_Fwd();
        }
        if (someMotorType == BASE_MOTOR && someMotorDirection == MOTOR_BACKWARD)
        {
            baseMotor_Bwd();
        }
        if (someMotorType == BASE_MOTOR && someMotorDirection == MOTOR_STOP)
        {
            baseMotor_Stop();
        }
    }
/* *****************************************************************************
 End of File
 */
