/* ************************************************************************** */
/** debug.h
 * 
 * Header file for debug routines.
 */
/* ************************************************************************** */
#ifndef _DEBUG_H    /* Guard against multiple inclusion */
#define _DEBUG_H

/* This section lists the other files that are included in this file.
 */
#include "peripheral/peripheral.h"
#include "app.h"
#include "arm.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
// Debug Constants
#define DLOC_ABS_FAILURE 0x00
    
#define DLOC_TASK_ENTERED_APP 0x01 
#define DLOC_TASK_ENTERED_ARM 0x02
    
#define DLOC_BEFORE_WHILE_APP 0x10
#define DLOC_BEFORE_WHILE_ARM 0x11
    
#define DLOC_ISR_ADC_ENTERED 0x20
#define DLOC_ISR_ADC_LEAVING 0x21
    
#define DLOC_ISR_ADC_QUEUE_TX_BEFORE 0x22
#define DLOC_ISR_ADC_QUEUE_TX_AFTER 0x23

#define DLOC_ISR_QUEUE_TX_BEFORE 0x30
#define DLOC_ISR_QUEUE_TX_AFTER 0x31
#define DLOC_ISR_QUEUE_RX_BEFORE 0x32
#define DLOC_ISR_QUEUE_RX_AFTER 0x33  
    
#define SENSOR_QUEUE_TX_BEGIN 0x40
#define SENSOR_QUEUE_TX_END 0x41
#define SENSOR_QUEUE_RX_BEGIN 0x42
#define SENSOR_QUEUE_RX_END 0x43

#define ARM_QUEUE_TX_BEGIN 0x50
#define ARM_QUEUE_TX_END 0x51
#define ARM_QUEUE_RX_BEGIN 0x52
#define ARM_QUEUE_RX_END 0x53
    /*
     * Write a value to 7 output lines and toggle an 8th. outVal must be < 127 unsigned
     */
    void dbgOutputVal(int outVal);
    /*
     * Write a character to the UART
     */
    void dbgUARTVal(unsigned char outVal);
    /*
     * Write a value to 7 DIFFERENT lines and toggle the 8th. outVal must be < 127 unsigned
     */
    void dbgOutputLoc(unsigned int outVal);
    /*
     * Stop everything, something bad has happened
     */
    void debugFail();
    
    
    void dbgUARTString(const unsigned char* outVal);
    /**
    * Send a UART string
    */
    char str[256];
    #define dbgUARTString(outVal, ...)\
    {\
       sprintf(str, outVal, ##__VA_ARGS__);\
       int i;\
       for (i = 0; i < 256; i++)\
       {\
           char c = str[i];\
           if (c == '\0')\
           {\
               break;\
           }\
           dbgUARTVal(c);\
       }\
    }

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif
#endif /* _DEBUG_H */
/* *****************************************************************************
 End of File
 */