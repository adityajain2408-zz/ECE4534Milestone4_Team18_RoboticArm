#include "communication_rx_state_machine.h"
#include "jsmn.h"

/*
	-Need to add more error checking for interrupted coms
	-Maybe add nested JSON feature
    -Maybe add HTTP error support?
    -Add content length parse support for timeout feature?
    
    -PROBLEM: if responses are short and a } is dropped it will grab the 
              whole next response
*/

rx_state rx_state_machine(rx_state state, char c, bool * json_ready, char * json_string) {

	static int json_index = 0;
    static int timeout = 0;

	switch (state) {
        case(H):
            *json_ready = false;
            if (c == 'H') {
                state = T1;
            }
            break;

        case(T1):
            if (c == 'T') {
                state = T2;
            }
            else {
                state = H;
            }
            break;

        case(T2):
            if (c == 'T') {
                state = P;
            }
            else {
                state = H;
            }
            break;

        case(P):
            if (c == 'P') {
                state = SLASH;
            }
            else {
                state = H;
            }
            break;

        case(SLASH):
            if (c == '/') {
                state = JSON_LOOKING;
            }
            else {
                state = H;
            }
            break;

        case(JSON_LOOKING):
            if (c == '{') {
                /*
                 Found the beginning of the JSON string
                 * -start grabbing the string
                 */
                state = JSON_GRABBING;
                json_string[0] = '{';
                json_index++;
                timeout = 0;
            } else if(timeout > JSON_LOOKING_TIMEOUT) {
                
                /*
                 Never found the beginning of the JSON string
                 *  -reset back to H
                 */
                
                state = H;
                timeout = 0;
            } else {
                
                /*
                 Still looking for start of JSON string
                 */
                
                timeout++;
            }
            break;

        case(JSON_GRABBING):
            if(json_index >= BUFFER_ARRAY_SIZE - 1){
                
                /*
                 We never found the end of the JSON string
                 * -communication error or buffer to small
                 */
                
                json_index = 0;
                state = H;
            } else {
                
                /*
                 Continue grabbing JSON string
                 */
                
                json_string[json_index] = c;
                json_index++;

                if (c == '}') {
                    state = H;
                    json_string[json_index] = '\0';
                    json_index = 0;
                    *json_ready = true;
                }
            }
            
            break;

        default:
            //Should never get here
            debugFail();
            break;
	}

	return state;
}
