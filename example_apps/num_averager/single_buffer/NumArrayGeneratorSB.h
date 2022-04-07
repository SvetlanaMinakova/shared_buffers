//
// Created by svetlana on 07/04/2022.
//

#ifndef SHARED_BUFFERS_NUMARRAYGENERATORSB_H
#define SHARED_BUFFERS_NUMARRAYGENERATORSB_H

#include "../../../MyProcess.h"
class NumArrayGeneratorSB: public MyProcess<float> {
public:
    void exec() override;
    void read() override;
    void write() override;
    explicit NumArrayGeneratorSB(int arrayLen, int runs=1, int execDelay=0, int rwDelay=0): MyProcess<float>("dataLayer", runs, execDelay, rwDelay){
        this->arrayLen = arrayLen;
    }
    void init();
    ~NumArrayGeneratorSB();

protected:
    int arrayLen;
    float* outputData = nullptr;
    int maxValue=100;
    float startValue=0.0;
};


#endif //SHARED_BUFFERS_NUMARRAYGENERATORSB_H
