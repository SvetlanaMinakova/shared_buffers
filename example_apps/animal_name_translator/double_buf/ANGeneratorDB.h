//
// Created by svetlana on 01/04/2022.
//

#ifndef SHARED_BUFFERS_ANGENERATORDB_H
#define SHARED_BUFFERS_ANGENERATORDB_H

#include "../ANGenerator.h"
#include "../../../buffers/DoubleSharedBuffer.h"

class ANGeneratorDB: public ANGenerator{
public:
    ANGeneratorDB(const std::string& name, std::map<std::string, std::string>& animalNames, int runs=1, int execDelay=0,
                  int rwDelay=0, int prodRate=1, int consRate=1): ANGenerator(name, animalNames, runs, execDelay, rwDelay, prodRate, consRate){};
    bool outputDataAvailable() override;
    void write() override;
    void SwapReadyOutputBuffers();
    void addInputBufferPtr(DoubleSharedBuffer<char>* ptr);
    void addOutputBufferPtr(DoubleSharedBuffer<char>* ptr);

protected:
    std::vector<DoubleSharedBuffer<char>*> inputBufferPtrs;
    std::vector<DoubleSharedBuffer<char>*> outputBufferPtrs;
};


#endif //SHARED_BUFFERS_ANGENERATORDB_H
