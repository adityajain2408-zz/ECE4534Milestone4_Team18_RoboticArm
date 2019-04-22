/* 
 * File:   communication_tx_routines.h
 * Author: Jkhawk117
 *
 * Created on March 20, 2019, 7:03 PM
 */


/*
 Includes
 */

#include <stdbool.h>
#include <stddef.h>

#include "communication_tx.h"
#include "communication_send_queue.h"
#include "debug.h"
#include "communication_checksum.h"


#ifndef COMMUNICATION_TX_ROUTINES_H
#define	COMMUNICATION_TX_ROUTINES_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    
void comms_tx_initialize();

void createHTTPString(char* method, char* url, char* params, char* body, int sequence, char* http_formatted);

void sendHTTPString(char* HTTP_string);


#ifdef	__cplusplus
}
#endif

#endif	/* COMMUNICATION_TX_ROUTINES_H */

