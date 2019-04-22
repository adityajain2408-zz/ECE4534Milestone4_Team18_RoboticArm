/* 
 * File:   communication_stat_calculation.h
 * Author: anamalhotra
 *
 * Created on March 20, 2019, 9:31 PM
 */

#ifndef COMMUNICATION_STAT_CALCULATION_H
#define	COMMUNICATION_STAT_CALCULATION_H

#include <string.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef struct {
    int missed;
    int sent;
    int received;
} StatsMessage;

StatsMessage calc_stats(int rec, int seq_recv, int seq_exp);

#ifdef	__cplusplus
}
#endif

#endif	/* COMMUNICATION_STAT_CALCULATION_H */

