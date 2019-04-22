/* 
 * File:   communication_checksum.h
 * Author: anamalhotra
 *
 * Created on March 26, 2019, 1:16 AM
 */

#include <string.h>

#include <stdio.h>
#include <stdlib.h>

#ifndef COMMUNICATION_CHECKSUM_H
#define	COMMUNICATION_CHECKSUM_H

#ifdef	__cplusplus
extern "C" {
#endif

    unsigned int getChecksum(char * json_statement);
    unsigned int computeChecksum(char * json_string);


#ifdef	__cplusplus
}
#endif

#endif	/* COMMUNICATION_CHECKSUM_H */

