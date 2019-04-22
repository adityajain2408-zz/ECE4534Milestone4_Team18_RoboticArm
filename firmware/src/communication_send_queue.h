/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _COMMUNICATION_SEND_QUEUE_H    /* Guard against multiple inclusion */
#define _COMMUNICATION_SEND_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "debug.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char *method;
    char *url;
    char *parameters;
    char *body;
} SendMessage;

void createSendQueue();

SendMessage receiveSendValue();

void sendSendValueFromISR(SendMessage data, BaseType_t* xHigherPriorityTaskWoken);

void sendSendValue(SendMessage data);



/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
