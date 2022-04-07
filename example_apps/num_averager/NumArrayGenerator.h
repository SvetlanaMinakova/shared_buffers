//
// Created by svetlana on 07/04/2022.
//

#ifndef SHARED_BUFFERS_NUMARRAYGENERATOR_H
#define SHARED_BUFFERS_NUMARRAYGENERATOR_H

#include "../../MyProcess.h"

class NumArrayGenerator: public MyProcess<float>{
public:
    void exec() override;
    void read() override;
    explicit NumArrayGenerator(int arrayLen, int runs=1, int execDelay=0, int rwDelay=0): MyProcess<float>("dataLayer", runs, execDelay, rwDelay){
        this->arrayLen = arrayLen;
    }
    void init();
    ~NumArrayGenerator();

protected:
    int arrayLen;
    float* outputData = nullptr;
    int maxValue=100;
    float startValue=0.0;
};


#endif //SHARED_BUFFERS_NUMARRAYGENERATOR_H
