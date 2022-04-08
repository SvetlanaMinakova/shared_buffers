//
// Created by svetlana on 08/04/2022.
//

#ifndef SHARED_BUFFERS_NUMARRAYAVERAGERDB_H
#define SHARED_BUFFERS_NUMARRAYAVERAGERDB_H

#include "../NumArrayAverager.h"
#include "../../../buffers/DoubleSharedBuffer.h"

class NumArrayAveragerDB: public NumArrayAverager{
public:
    void read() override;
    bool inputDataAvailable() override;
    explicit NumArrayAveragerDB(int arrayLen, int runs=1, int execDelay=0, int rwDelay=0): NumArrayAverager(arrayLen, runs, execDelay, rwDelay){};
    void addInputBufferPtr(DoubleSharedBuffer<float>* ptr);
    void addOutputBufferPtr(DoubleSharedBuffer<float>* ptr);
    void SwapReadyInputBuffers();

protected:
    std::vector<DoubleSharedBuffer<float>*> inputBufferPtrs;
    std::vector<DoubleSharedBuffer<float>*> outputBufferPtrs;
};


#endif //SHARED_BUFFERS_NUMARRAYAVERAGERDB_H
