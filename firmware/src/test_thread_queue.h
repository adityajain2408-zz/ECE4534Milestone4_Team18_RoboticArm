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

#ifndef _TEST_THREAD_QUEUE_H    /* Guard against multiple inclusion */
#define _TEST_THREAD_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "debug.h"
#include "communication_send_queue.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        char * msg;
    } TestThreadMessage;

    void createTestThreadQueue();

    TestThreadMessage receiveTestThreadValue();

    void sendTestThreadValueFromISR(TestThreadMessage data, BaseType_t* xHigherPriorityTaskWoken);

    void sendTestThreadValue(TestThreadMessage data);
    
/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
