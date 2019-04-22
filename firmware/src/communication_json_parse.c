#include "communication_json_parse.h"

int jsoneq(const char * json_string, jsmntok_t * t, const char * s) {
	if (t->type == JSMN_STRING && (int) strlen(s) == t->end - t->start &&
			strncmp(json_string + t->start, s, t->end - t->start) == 0) {
		return 0;
	}
	return -1;
}

int json_getVal(const char * json_string, jsmntok_t * t, int rVal, char * valOf, char * val){

    int i;
    for (i = 1; i < rVal; i++) {
		if (jsoneq(json_string, &t[i], valOf) == 0) {
			/* We may use strndup() to fetch string value */
			sprintf(val,"%.*s", t[i+1].end-t[i+1].start, json_string + t[i+1].start);
            return 0;
		}
    }
    
    sprintf(val,"ERROR_UNEXPECTED_KEY"); 
    return -1;
}