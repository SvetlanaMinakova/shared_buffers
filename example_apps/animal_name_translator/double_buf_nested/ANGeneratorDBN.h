//
// Created by svetlana on 01/04/2022.
//

#ifndef SHARED_BUFFERS_ANGENERATORDBN_H
#define SHARED_BUFFERS_ANGENERATORDBN_H

#include "../ANGenerator.h"
#include "../../../buffers/DoubleSharedCharBuffer.h"

class ANGeneratorDBN: public ANGenerator{
public:
    ANGeneratorDBN(const std::string& name, std::map<std::string, std::string>& animalNames, int runs=1, int execDelay=0,
                   int rwDelay=0, int prodRate=1, int consRate=1): ANGenerator(name, animalNames, runs, execDelay, rwDelay, prodRate, consRate){};
    bool outputDataAvailable() override;
    void write() override;
    void SwapReadyOutputBuffers();
    void addInputBufferPtr(DoubleSharedCharBuffer* ptr);
    void addOutputBufferPtr(DoubleSharedCharBuffer* ptr);

protected:
    std::vector<DoubleSharedCharBuffer*> inputBufferPtrs;
    std::vector<DoubleSharedCharBuffer*> outputBufferPtrs;
};


#endif //SHARED_BUFFERS_ANGENERATORDBN_H
