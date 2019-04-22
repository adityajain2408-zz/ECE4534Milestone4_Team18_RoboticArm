/* 
 * File:   rx_state_machine.h
 * Author: Jkhawk117
 *
 * Created on March 18, 2019, 5:09 PM
 */

#include <stdbool.h>
#include <stddef.h>

#ifndef COMMUNICATION_RX_STATE_MACHINE_H
#define	COMMUNICATION_RX_STATE_MACHINE_H

#ifdef	__cplusplus
extern "C" {
#endif

    #define BUFFER_ARRAY_SIZE 512
    #define JSON_LOOKING_TIMEOUT 400
    
    typedef enum {
        H,
        T1,
        T2,
        P,
        SLASH,
        JSON_LOOKING,
        JSON_GRABBING, 
    } rx_state;
    
    rx_state rx_state_machine_run(rx_state state, char c, bool * json_ready, char * json_string);


#ifdef	__cplusplus
}
#endif

#endif	/* RX_STATE_MACHINE_H */

