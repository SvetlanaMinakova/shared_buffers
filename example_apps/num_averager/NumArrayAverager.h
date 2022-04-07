//
// Created by svetlana on 07/04/2022.
//

#ifndef SHARED_BUFFERS_NUMARRAYAVERAGER_H
#define SHARED_BUFFERS_NUMARRAYAVERAGER_H

#include "../../MyProcess.h"

class NumArrayAverager: public MyProcess<float> {
public:
    void exec() override;
    void read()override=0;
    void write() override;
    explicit NumArrayAverager(int arrayLen, int runs=1, int execDelay=0, int rwDelay=0): MyProcess<float>("dataLayer", runs, execDelay, rwDelay){
        this->arrayLen = arrayLen;
    }
    virtual void init();
    ~NumArrayAverager();

protected:
    int arrayLen;
    float* inputData = nullptr;
};


#endif //SHARED_BUFFERS_NUMARRAYAVERAGER_H
