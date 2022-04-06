//
// Created by svetlana on 01/04/2022.
//

#ifndef SHARED_BUFFERS_ANRECEIVERDB_H
#define SHARED_BUFFERS_ANRECEIVERDB_H

#include "../ANReceiver.h"
#include "../../../buffers/DoubleSharedBuffer.h"

class ANReceiverDB: public ANReceiver {
public:
    ANReceiverDB(const std::string& name, std::map<std::string, std::string>& animalNames, int runs=1, int execDelay=0,
                 int rwDelay=0, int prodRate=1, int consRate=1): ANReceiver(name, animalNames, runs,execDelay, rwDelay, prodRate, consRate){};
    bool inputDataAvailable() override;
    void read() override;
    void SwapReadyInputBuffers();
    void addInputBufferPtr(DoubleSharedBuffer<char>* ptr);
    void addOutputBufferPtr(DoubleSharedBuffer<char>* ptr);

protected:
    std::vector<DoubleSharedBuffer<char>*> inputBufferPtrs;
    std::vector<DoubleSharedBuffer<char>*> outputBufferPtrs;
};


#endif //SHARED_BUFFERS_ANRECEIVERDB_H
