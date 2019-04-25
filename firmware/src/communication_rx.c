#include "communication_rx.h"
#include "communication_json_parse.h"
#include "communication_stat_calculation.h"
#include "communication_checksum.h"

void COMMUNICATION_RX_Initialize(void) {
    createWifly_rx_Queue();
    //commented the above out to test RX stuff on its own
}

void COMMUNICATION_RX_Tasks(void) {
    dbgOutputLoc(COMS_RX_BEFORE_WHILE);
    
    bool json_complete = false;
    static char json_statement[BUFFER_ARRAY_SIZE];
    rx_state state = H;

    bool valid_json = true;
    bool valid_checksum = true;

    int received = 0;
    int seq_exp = 0;

    StatsMessage stats_msg;

    dbgOutputLoc(COMS_RX_ENTERED_WHILE);
    while (1) {
        //read from the queue
        valid_json = true;
        valid_checksum = true;
        
        char rx_byte = receiveWifly_rx_Value();
        state = rx_state_machine(state, rx_byte, &json_complete, json_statement);

        //Identified and read a full HTTP message
        if (json_complete) {
            // parse json
            jsmn_parser p;
            jsmntok_t tokens[128]; // max 128 tokens, we can probably make this smaller
            jsmn_init(&p);
            int rVal = jsmn_parse(&p, json_statement, strlen(json_statement), tokens, sizeof(tokens)/sizeof(tokens[0]));

            dbgOutputLoc(0x07);
            // check validity
            if (rVal < 0) {
                valid_json = false;
            } else {
                // extract checksum received
                char checksum_recv_string[128];
                if(json_getVal(json_statement, tokens, rVal, "checksum", checksum_recv_string) < 0){
                    valid_json = false;
                } else {
                    int checksum_recv = atoi(checksum_recv_string);
                    if (getChecksum(json_statement) != checksum_recv) {
                        // invalid checksum error
                        valid_checksum = false;
                    }
                }
            }
            char msg[512];
            if(json_getVal(json_statement, tokens, rVal, "status", msg) == 0){
                    //Grab value from ADC -> convert using routine in sensorQueue.c
                    int pot_value = convertToDegrees(DRV_ADC_SamplesRead(14));
                    SensorMessage sm = {pot_value, msg, "degrees"};

                    //Send to sensor queue
                    dbgOutputLoc(DLOC_ISR_ADC_QUEUE_TX_BEFORE);
                    sendSensorData(sm);
                    dbgOutputLoc(DLOC_ISR_ADC_QUEUE_TX_AFTER);

                    dbgOutputLoc(DLOC_ISR_ADC_LEAVING);
                }
            
            if (valid_json && valid_checksum) {
                received++;
                // extract seq number received
                char seq_recv_string[128];
                json_getVal(json_statement, tokens, rVal, "sequence", seq_recv_string);
                
                int seq_recv = atoi(seq_recv_string);
                
                //If first receive, sync with the server
                if(seq_exp == 0){
                    seq_exp = seq_recv;
                }

                // update statistics
                stats_msg = calc_stats(received, seq_recv, seq_exp);
                sendStatsValue(stats_msg);
                
                // update expected seq number
                seq_exp = seq_recv + 1;
                
                //extract data
                /*char msg[512];
                if(json_getVal(json_statement, tokens, rVal, "msg", msg) == 0){
                    //TestThreadMessage data;
                    //data.msg = msg;
                    //sendTestThreadValue(data);
                }
                 */
            }
        }
    }
}
