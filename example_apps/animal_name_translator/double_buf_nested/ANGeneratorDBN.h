//
// Created by svetlana on 01/04/2022.
//

#ifndef SHARED_BUFFERS_ANGENERATORDBN_H
#define SHARED_BUFFERS_ANGENERATORDBN_H

#include "../ANGenerator.h"
#include "../../../buffers/DoubleNestedCharBuffer.h"

class ANGeneratorDBN: public ANGenerator{
public:
    ANGeneratorDBN(const std::string& name, std::map<std::string, std::string>& animalNames, int runs=1, int execDelay=0, int prodRate=1, int consRate=1): ANGenerator(name, animalNames, runs,execDelay, prodRate, consRate){};
    bool outputDataAvailable() override;
    void write() override;
    void SwapReadyOutputBuffers();
    void addInputBufferPtr(DoubleNestedCharBuffer* ptr);
    void addOutputBufferPtr(DoubleNestedCharBuffer* ptr);

protected:
    std::vector<DoubleNestedCharBuffer*> inputBufferPtrs;
    std::vector<DoubleNestedCharBuffer*> outputBufferPtrs;
};


#endif //SHARED_BUFFERS_ANGENERATORDBN_H
