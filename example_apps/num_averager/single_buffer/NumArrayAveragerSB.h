//
// Created by svetlana on 07/04/2022.
//

#ifndef SHARED_BUFFERS_NUMARRAYAVERAGERSB_H
#define SHARED_BUFFERS_NUMARRAYAVERAGERSB_H

#include "../NumArrayAverager.h"

class NumArrayAveragerSB: public NumArrayAverager{
public:
    void read() override;
    explicit NumArrayAveragerSB(int arrayLen, int runs=1, int execDelay=0, int rwDelay=0): NumArrayAverager(arrayLen, runs, execDelay, rwDelay){};
};


#endif //SHARED_BUFFERS_NUMARRAYAVERAGERSB_H
