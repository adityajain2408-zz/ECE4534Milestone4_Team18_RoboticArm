/* 
 * File:   communication_json_parse.h
 * Author: anamalhotra
 *
 * Created on March 20, 2019, 6:28 PM
 */

#ifndef COMMUNICATION_JSON_PARSE_H
#define	COMMUNICATION_JSON_PARSE_H

#include <stdio.h>
#include <string.h>

#include "jsmn.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    int jsoneq(const char * json_string, jsmntok_t * t, const char * s);
    int json_getVal(const char * json_string, jsmntok_t * t, int rVal, char * valOf, char * val);
    

#ifdef	__cplusplus
}
#endif

#endif	/* COMMUNICATION_JSON_PARSE_H */

