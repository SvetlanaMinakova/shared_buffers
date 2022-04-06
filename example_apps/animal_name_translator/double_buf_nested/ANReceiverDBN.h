//
// Created by svetlana on 01/04/2022.
//

#ifndef SHARED_BUFFERS_ANRECEIVERDBN_H
#define SHARED_BUFFERS_ANRECEIVERDBN_H

#include "../ANReceiver.h"
#include "../../../buffers/DoubleSharedCharBuffer.h"

class ANReceiverDBN: public ANReceiver {
public:
    ANReceiverDBN(const std::string& name, std::map<std::string, std::string>& animalNames, int runs=1, int execDelay=0,
                  int rwDelay=0, int prodRate=1, int consRate=1): ANReceiver(name, animalNames, runs,execDelay, rwDelay, prodRate, consRate){};
    bool inputDataAvailable() override;
    void read() override;
    void SwapReadyInputBuffers();
    void addInputBufferPtr(DoubleSharedCharBuffer* ptr);
    void addOutputBufferPtr(DoubleSharedCharBuffer* ptr);

protected:
    std::vector<DoubleSharedCharBuffer*> inputBufferPtrs;
    std::vector<DoubleSharedCharBuffer*> outputBufferPtrs;
};


#endif //SHARED_BUFFERS_ANRECEIVERDBN_H
