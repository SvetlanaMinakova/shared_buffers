//
// Created by svetlana on 23/03/2022.
//

#ifndef SHARED_BUFFERS_MYPROCESS_H
#define SHARED_BUFFERS_MYPROCESS_H
#include <string>
#include "SharedCharBuffer.h"
#include "vector"

class MyProcess {
public:
    std::string name;
    int execDelay;
    int runs;

    void SayHi() const;

    void exec() const;
    void read();
    void write();

    void addInputBufferPtr(SharedCharBuffer* ptr);
    void addOutputBufferPtr(SharedCharBuffer* ptr);
    void printInputBufferNames();
    void printOutputBufferNames();
    bool inputDataAvailable();
    bool outputDataAvailable();
    int productionRate;
    int consumptionRate;

    // main function executed in a thread
    void main(void *par);

    // constructor and destructor
    explicit MyProcess(std::string name, int runs=1, int execDelay=0, int prodRate=1, int consRate=1);

protected:
    std::vector<SharedCharBuffer*> inputBufferPtrs;
    std::vector<SharedCharBuffer*> outputBufferPtrs;
};


#endif //SHARED_BUFFERS_MYPROCESS_H
