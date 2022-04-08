//
// Created by svetlana on 08/04/2022.
//

#ifndef SHARED_BUFFERS_NUMAVERAGERDB_H
#define SHARED_BUFFERS_NUMAVERAGERDB_H


#include "NumArrayGeneratorDB.h"
#include "NumArrayAveragerDB.h"
#include "../../../buffers/DoubleSharedBuffer.h"

class NumAveragerDB {
public:
    int run();
    explicit NumAveragerDB(int arrayLen, int runs=1, int execDelay=0, int rwDelay=0){

    generator = NumArrayGeneratorDB(arrayLen, runs, execDelay, rwDelay);
    averager = NumArrayAveragerDB(arrayLen, runs, execDelay, rwDelay);

    // production/consumption rates
    generator.productionRate = arrayLen;
    generator.consumptionRate = 0;
    averager.productionRate = 0;
    averager.consumptionRate = arrayLen;

    //shared buffer
    this->buffer.init("buffer", arrayLen);
    buffer.setBottomVisited(); //required to start double buffer
}

protected:
    NumArrayGeneratorDB generator = NumArrayGeneratorDB(0, 0, 0, 0);
    NumArrayAveragerDB averager = NumArrayAveragerDB(0, 0, 0, 0);
    DoubleSharedBuffer<float> buffer =  DoubleSharedBuffer<float>();
};


#endif //SHARED_BUFFERS_NUMAVERAGERDB_H
