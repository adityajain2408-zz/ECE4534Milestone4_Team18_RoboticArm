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
#define DLOC_ABS_FAILURE                0x00
    
#define DLOC_TASK_ENTERED_APP           0x01 
#define DLOC_TASK_ENTERED_ARM           0x02

#define COMS_RX_BEFORE_WHILE            0x03
#define COMS_RX_ENTERED_WHILE           0x04
    
#define COMS_TX_BEFORE_WHILE            0x05
#define COMS_TX_ENTERED_WHILE           0x06
    
#define DLOC_BEFORE_WHILE_APP           0x10
#define DLOC_BEFORE_WHILE_ARM           0x11

#define STATS_BEFORE_WHILE              0x12
#define STATS_ENTERED_WHILE             0x13
    
#define TEST_BEFORE_WHILE               0x14
#define TEST_ENTERED_WHILE              0x15          

#define DLOC_ISR_ADC_ENTERED            0x20
#define DLOC_ISR_ADC_LEAVING            0x21
    
#define DLOC_ISR_ADC_QUEUE_TX_BEFORE    0x22
#define DLOC_ISR_ADC_QUEUE_TX_AFTER     0x23

#define DLOC_ISR_TIMER_ENTERED          0x24
#define DLOC_ISR_TIMER_LEAVING          0x25

#define DLOC_ISR_QUEUE_TX_BEFORE        0x30
#define DLOC_ISR_QUEUE_TX_AFTER         0x31
#define DLOC_ISR_QUEUE_RX_BEFORE        0x32
#define DLOC_ISR_QUEUE_RX_AFTER         0x33  
    
#define SENSOR_QUEUE_TX_BEGIN           0x34
#define SENSOR_QUEUE_TX_END             0x35
#define SENSOR_QUEUE_RX_BEGIN           0x36
#define SENSOR_QUEUE_RX_END             0x37

#define STATS_QUEUE_RX_BEGIN            0x38
#define STATS_QUEUE_RX_END              0x39
#define STATS_QUEUE_TX_ISR_BEGIN        0x3A
#define STATS_QUEUE_TX_ISR_END          0x3B
#define STATS_QUEUE_RX_ISR_BEGIN        0x3C
#define STATS_QUEUE_RX_ISR_END          0x3D
#define STATS_QUEUE_TX_BEGIN            0x3E
#define STATS_QUEUE_TX_END              0x3F

#define WIFLYTX_QUEUE_TX_BEGIN          0x40
#define WIFLYTX_QUEUE_TX_END            0x41
#define WIFLYTX_QUEUE_RX_BEGIN          0x42
#define WIFLYTX_QUEUE_RX_END            0x43
#define WIFLYTX_REC_FROMISR_BEGIN       0x44
#define WIFLYTX_REC_FROMISR_END         0x45
#define WIFLYTX_QUEUE_TX_FROMISR_BEGIN  0x46
#define WIFLYTX_QUEUE_TX_FROMISR_END    0x47
    
#define WIFLYRX_QUEUE_TX_BEGIN          0x48
#define WIFLYRX_QUEUE_TX_END            0x49
#define WIFLYRX_QUEUE_RX_BEGIN          0x4A
#define WIFLYRX_QUEUE_RX_END            0x4B
#define WIFLYRX_REC_FROMISR_BEGIN       0x4C
#define WIFLYRX_REC_FROMISR_END         0x4D
#define WIFLYRX_QUEUE_TX_FROMISR_BEGIN  0x4E
#define WIFLYRX_QUEUE_TX_FROMISR_END    0x4F   
    
#define ARM_QUEUE_TX_BEGIN              0x50
#define ARM_QUEUE_TX_END                0x51
#define ARM_QUEUE_RX_BEGIN              0x52
#define ARM_QUEUE_RX_END                0x53

#define DLOC_ISR_UART_ENTERED           0x54
#define DLOC_ISR_UART_LEAVING           0x55
#define DLOC_ISR_UART_TX_ENTERED        0x56
#define DLOC_ISR_UART_TX_QUEUE_RECV     0x57
#define DLOC_ISR_UART_RX_QUEUE_TRANS    0x58
#define DLOC_ISR_UART_RX_ENTERED        0x59
    
#define COMM_SEND_QUEUE_TX_BEGIN        0x60
#define COMM_SEND_QUEUE_TX_END          0x61
#define COMM_SEND_QUEUE_RX_BEGIN        0x62
#define COMM_SEND_QUEUE_RX_END          0x63
#define COMM_SEND_QUEUE_TX_ISR_BEGIN    0x64
#define COMM_SEND_QUEUE_TX_ISR_END      0x65
    
#define TEST_THREAD_QUEUE_TX_BEGIN      0x66
#define TEST_THREAD_QUEUE_TX_END        0x67
#define TEST_THREAD_QUEUE_RX_BEGIN      0x68
#define TEST_THREAD_QUEUE_RX_END        0x69
#define TEST_THREAD_QUEUE_TX_ISR_BEGIN  0x6A
#define TEST_THREAD_QUEUE_TX_ISR_END    0x6B
    
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