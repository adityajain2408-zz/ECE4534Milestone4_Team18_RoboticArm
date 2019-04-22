/* ************************************************************************** */
/** motor_uart_queue.h
 * 
 * Contains definitions of motor queue helper functions
 */
/* ************************************************************************** */

#include "FreeRTOS.h"
#include "queue.h"
#include "debug.h"

#ifndef _WIFLYQUEUE_H    /* Guard against multiple inclusion */
#define _WIFLYQUEUE_H


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
void createWifly_tx_Queue();

char receiveWifly_tx_Value();

void sendWifly_tx_ValueFromISR(char data, BaseType_t* xHigherPriorityTaskWoken);

char receiveWifly_tx_ValueFromISR(BaseType_t* xHigherPriorityTaskWoken);

void sendWifly_tx_Value(char data);

BaseType_t wifly_tx_QueueIsEmptyFromISR();

//////////////////////

void createWifly_rx_Queue();

char receiveWifly_rx_Value();

void sendWifly_rx_ValueFromISR(char data, BaseType_t* xHigherPriorityTaskWoken);

char receiveWifly_rx_ValueFromISR(BaseType_t* xHigherPriorityTaskWoken);

void sendWifly_rx_Value(char data);

BaseType_t wifly_rx_QueueIsEmptyFromISR();

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
