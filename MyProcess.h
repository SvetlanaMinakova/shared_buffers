//
// Created by svetlana on 23/03/2022.
//

#ifndef SHARED_BUFFERS_MYPROCESS_H
#define SHARED_BUFFERS_MYPROCESS_H
#include <string>
#include "buffers/SharedCharBuffer.h"
#include "vector"

class MyProcess {
public:
    std::string name;
    int execDelay;
    int rwDelay=0;
    int runs;

    void sayHi();

    void delay(int timeMS);
    virtual void exec();
    virtual void read();
    virtual void write();

    virtual void addInputBufferPtr(SharedCharBuffer* ptr);
    virtual void addOutputBufferPtr(SharedCharBuffer* ptr);
    void printInputBufferNames();
    void printOutputBufferNames();
    virtual bool inputDataAvailable();
    virtual bool outputDataAvailable();
    int productionRate;
    int consumptionRate;

    // main function executed in a thread
    virtual void main(void *par);

    // constructor and destructor
    explicit MyProcess(std::string name, int runs=1, int execDelay=0, int rwDelay=0, int prodRate=1, int consRate=1);

protected:
    std::vector<SharedCharBuffer*> inputBufferPtrs;
    std::vector<SharedCharBuffer*> outputBufferPtrs;
};


#endif //SHARED_BUFFERS_MYPROCESS_H
