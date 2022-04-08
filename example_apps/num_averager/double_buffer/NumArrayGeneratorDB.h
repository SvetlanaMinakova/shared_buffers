//
// Created by svetlana on 08/04/2022.
//

#ifndef SHARED_BUFFERS_NUMARRAYGENERATORDB_H
#define SHARED_BUFFERS_NUMARRAYGENERATORDB_H

#include "../NumArrayGenerator.h"
#include "../../../buffers/DoubleSharedBuffer.h"

class NumArrayGeneratorDB: public NumArrayGenerator{
public:
    void write() override;
    explicit NumArrayGeneratorDB(int arrayLen, int runs=1, int execDelay=0, int rwDelay=0): NumArrayGenerator(arrayLen, runs, execDelay, rwDelay){}
    void SwapReadyOutputBuffers();
    bool outputDataAvailable() override;
    void addInputBufferPtr(DoubleSharedBuffer<float>* ptr);
    void addOutputBufferPtr(DoubleSharedBuffer<float>* ptr);

protected:
    std::vector<DoubleSharedBuffer<float>*> inputBufferPtrs;
    std::vector<DoubleSharedBuffer<float>*> outputBufferPtrs;

};


#endif //SHARED_BUFFERS_NUMARRAYGENERATORDB_H
