//
// Created by svetlana on 07/04/2022.
//

#ifndef SHARED_BUFFERS_NUMAVERAGERSB_H
#define SHARED_BUFFERS_NUMAVERAGERSB_H

#include "../../../MyProcess.h"
#include "NumArrayGeneratorSB.h"
#include "NumArrayAveragerSB.h"
#include "../../../buffers/SingleSharedBuffer.h"

class NumAveragerSB {
public:
    int run();
    explicit NumAveragerSB(int arrayLen, int runs=1, int execDelay=0, int rwDelay=0){

        generator = NumArrayGeneratorSB(arrayLen, runs, execDelay, rwDelay);
        averager = NumArrayAveragerSB(arrayLen, runs, execDelay, rwDelay);

        // production/consumption rates
        generator.productionRate = arrayLen;
        generator.consumptionRate = 0;
        averager.productionRate = 0;
        averager.consumptionRate = arrayLen;

        //shared buffer
        this->buffer.init("buffer", arrayLen);
    }

protected:
    NumArrayGeneratorSB generator = NumArrayGeneratorSB(0, 0, 0, 0);
    NumArrayAveragerSB averager = NumArrayAveragerSB(0, 0, 0, 0);
    SingleSharedBuffer<float> buffer =  SingleSharedBuffer<float>();
};


#endif //SHARED_BUFFERS_NUMAVERAGERSB_H
