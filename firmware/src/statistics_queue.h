/* ************************************************************************** */
/** statistics_queue.h
 * 
 * Contains definitions of stats queue helper functions
 */
/* ************************************************************************** */

#include "FreeRTOS.h"
#include "queue.h"
#include "debug.h"

#include "communication_stat_calculation.h"

#ifndef _STATS_H    /* Guard against multiple inclusion */
#define _STATS_H


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

void createStats_Queue();

StatsMessage receiveStatsValue();

void sendStatsValueFromISR(StatsMessage data, BaseType_t* xHigherPriorityTaskWoken);

StatsMessage receiveStatsValueFromISR(BaseType_t* xHigherPriorityTaskWoken);

void sendStatsValue(StatsMessage data);

BaseType_t statsQueueIsEmptyFromISR();


/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */