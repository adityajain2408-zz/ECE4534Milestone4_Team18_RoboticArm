#include "communication_stat_calculation.h"

StatsMessage calc_stats(int rec, int seq_recv, int seq_exp) {

    StatsMessage sm = {0, 0, 0};

    sm.missed = (seq_recv - seq_exp);
    sm.sent = 0; // needs to be handled in TX Task
    sm.received = rec;

    return sm;
}