#include "communication_tx_routines.h"

void comms_tx_initialize(){
    DRV_TMR0_Start();

    //set SS pin high due to reset pin tie on wifly shield
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_9, 1);
    
    //Debug set ground 0 in case of error
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_10, 0); 
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_7, 0);
    
    //UART initialize
    PLIB_USART_BaudRateSet(USART_ID_1, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_2), 57600);
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_UART1, INT_PRIORITY_LEVEL1);

    PLIB_USART_ReceiverInterruptModeSelect(USART_ID_1, USART_RECEIVE_FIFO_ONE_CHAR);
    PLIB_USART_TransmitterInterruptModeSelect(USART_ID_1, USART_TRANSMIT_FIFO_NOT_FULL);
    
    PLIB_USART_Enable(USART_ID_1);
    PLIB_USART_TransmitterEnable(USART_ID_1);
    PLIB_USART_ReceiverEnable(USART_ID_1);
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);

    //Create byte Queue for Wifly Transmit
    createWifly_tx_Queue();
    
    //Create Queue for threads to send requests over Wifly
    createSendQueue();
}

void createHTTPString(char* method, char* url, char* params, char* body, int sequence, char* http_formatted){
    if(strcmp(method, "GET") == 0){
        //GET - add sequence and checksum to params ?sequence=%d&pic=1
        char param_text[100];
        sprintf(param_text, "sequence=%d&pic=%s&want=%s", sequence, params, "pic1");
        sprintf(http_formatted, "%s /%s?%s HTTP/1.1\r\nHost: 192.168.0.10\r\nChecksum: %d\r\n\r\n",
                method,
                url,
                param_text,
                computeChecksum(param_text));
    } else {
        //PUT/POST
        static char json_body[400];
        sprintf(json_body, "{%s, \"sent\": %d, \"pic\": \"pic1\", \"sequence\": %d}", body, sequence, sequence);
        sprintf(http_formatted, "%s /%s HTTP/1.1\r\nHost: 192.168.0.10\r\nContent-Type: application/json\r\nContent-Length: %d\r\nChecksum: %d\r\n\r\n%s\r\n\r\n",
                method,
                url,
                strlen(json_body),
                computeChecksum(json_body),
                json_body);
    }
}


void sendHTTPString(char* http_string){

    char* temp = http_string;
    
    while(*temp != '\0')
    {
        sendWifly_tx_Value(*temp);
        PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
        temp++;
    }
}