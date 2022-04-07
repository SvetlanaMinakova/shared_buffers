//
// Created by svetlana on 07/04/2022.
//

#ifndef SHARED_BUFFERS_NUMARRAYGENERATORSB_H
#define SHARED_BUFFERS_NUMARRAYGENERATORSB_H

#include "../NumArrayGenerator.h"
class NumArrayGeneratorSB: public NumArrayGenerator {
public:
    void write() override;
    explicit NumArrayGeneratorSB(int arrayLen, int runs=1, int execDelay=0, int rwDelay=0): NumArrayGenerator(arrayLen, runs, execDelay, rwDelay){}
};


#endif //SHARED_BUFFERS_NUMARRAYGENERATORSB_H
