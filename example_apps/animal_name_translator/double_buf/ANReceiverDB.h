//
// Created by svetlana on 01/04/2022.
//

#ifndef SHARED_BUFFERS_ANRECEIVERDB_H
#define SHARED_BUFFERS_ANRECEIVERDB_H

#include "../ANReceiver.h"
#include "../../../buffers/DoubleSharedCharBuffer.h"

class ANReceiverDB: public ANReceiver {
public:
    ANReceiverDB(const std::string& name, std::map<std::string, std::string>& animalNames, int runs=1, int execDelay=0, int prodRate=1, int consRate=1): ANReceiver(name, animalNames, runs,execDelay, prodRate, consRate){};
    bool inputDataAvailable() override;
    void read() override;
    void SwapReadyInputBuffers();
    void addInputBufferPtr(DoubleSharedCharBuffer* ptr);
    void addOutputBufferPtr(DoubleSharedCharBuffer* ptr);

protected:
    std::vector<DoubleSharedCharBuffer*> inputBufferPtrs;
    std::vector<DoubleSharedCharBuffer*> outputBufferPtrs;
};
#endif //SHARED_BUFFERS_ANRECEIVERDB_H
