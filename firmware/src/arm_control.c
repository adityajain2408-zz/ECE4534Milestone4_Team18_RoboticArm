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
    
    /*
     * Start moving jointMotor Up
     */
    void jointMotor_Up()
    {
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3, true); //Turning the LED on 
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_1, true); // green on - relay module - pic pin # 5
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2, false); // black off - relay module - pic pin # 6
              
    }

    /*
     * Start moving jointMotor Down
     */
    void jointMotor_Down()
    {
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3, true); //Turning the LED on 
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_1, false); // green off - relay module - pic pin # 5
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2, true); //black on - relay module - pic pin # 6
    }

    /*
     * Stop the joint motor
     */
    void jointMotor_Stop()
    {
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2, false); //black off - relay module - pic pin # 6
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_1, false); // green off - relay module  - pic pin #5 
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3, false); //Turning the LED off 
    }
    
    /*
     * Open the gripper
     */
    void gripperMotor_Open()
    {
        
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_12, false); //Gray off - relay module - pic pin # 8
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_3, true); //black on - relay module - pic pin # 9
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3, true); //Turning the LED on 
    }
    
    /*
     * Close the gripper
     */
    void gripperMotor_Close()
    {
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_12, true); //Gray on - relay module - pic pin # 8
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_3, false); //black off - relay module - pic pin # 9
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3, true); //Turning the LED on
    }
    
    /*
     * Stop the gripper motor
     */
    void gripperMotor_Stop()
    {
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_12, false); //Gray off - relay module - pic pin # 8
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_3, false); //black off - relay module - pic pin # 9
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3, false); //Turning the LED off 
    }
    
    /*
     * Start Reading Joint Pot
     */
    void read_jointPot()
    {
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_8, true); // Brown on - relay module  - pic pin #3 
    }
    
    /*
     * Start Reading Joint
     */
    void read_basePot()
    {
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_8, false); // Brown off - relay module  - pic pin #3 
    }
    
    void processArmMessage(MotorType someMotorType, MotorDirection someMotorDirection)
    {   
        //Base Motor
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
        
        //Joint Motor
        if (someMotorType == JOINT_MOTOR && someMotorDirection == MOTOR_STOP)
        {
            jointMotor_Stop();
        }
        if (someMotorType == JOINT_MOTOR && someMotorDirection == MOTOR_UP)
        {
            jointMotor_Up();
        }
        if (someMotorType == JOINT_MOTOR && someMotorDirection == MOTOR_DOWN)
        {
            jointMotor_Down();
        }
        
        // GRIPPER MOTOR
        
        //Joint Motor
        if (someMotorType == GRIPPER_MOTOR && someMotorDirection == MOTOR_STOP)
        {
            gripperMotor_Stop();
        }
        if (someMotorType == GRIPPER_MOTOR && someMotorDirection == MOTOR_OPEN)
        {
            gripperMotor_Open();
        }
        if (someMotorType == GRIPPER_MOTOR && someMotorDirection == MOTOR_CLOSE)
        {
            gripperMotor_Close();
        }
    }
/* *****************************************************************************
 End of File
 */
