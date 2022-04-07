//
// Created by svetlana on 23/03/2022.
//

#ifndef SHARED_BUFFERS_MYPROCESS_H
#define SHARED_BUFFERS_MYPROCESS_H
#include <string>
#include "buffers/SingleSharedBuffer.h"
#include "vector"
#include <utility>
#include <iostream>
#include "types.h"
#include <chrono>
#include <thread>

template <class T>
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

    virtual void addInputBufferPtr(SingleSharedBuffer<T>* ptr);
    virtual void addOutputBufferPtr(SingleSharedBuffer<T>* ptr);
    void printInputBufferNames();
    void printOutputBufferNames();
    virtual bool inputDataAvailable();
    virtual bool inputBuffersFull();
    virtual bool outputDataAvailable();
    virtual bool outputBuffersFree();
    int productionRate;
    int consumptionRate;

    // main function executed in a thread
    virtual void main(void *par);

    // constructor and destructor
    explicit MyProcess(std::string name, int runs=1, int execDelay=0, int rwDelay=0, int prodRate=1, int consRate=1);

protected:
    std::vector<SingleSharedBuffer<T>*> inputBufferPtrs;
    std::vector<SingleSharedBuffer<T>*> outputBufferPtrs;
};


// Constructor
template<class T>
MyProcess<T>::MyProcess(std::string name, int runs, int execDelay, int rwDelay, int prodRate, int consRate) {
    this->name = std::move(name);
    this->runs = runs;
    this->execDelay = execDelay;
    this->rwDelay = rwDelay;
    this->productionRate = prodRate;
    this->consumptionRate = consRate;
}

// Manage I/O buffers
template<class T>
void MyProcess<T>::addInputBufferPtr(SingleSharedBuffer<T>* ptr){
    inputBufferPtrs.push_back(ptr);
}

template<class T>
void MyProcess<T>::addOutputBufferPtr(SingleSharedBuffer<T>* ptr){
    outputBufferPtrs.push_back(ptr);
}

template<class T>
void MyProcess<T>::printInputBufferNames(){
    for (auto bufPtr:inputBufferPtrs){
        std::cout<<bufPtr->name<<std::endl;
    }
}

template<class T>
void MyProcess<T>::printOutputBufferNames(){
    for (auto bufPtr:outputBufferPtrs){
        std::cout<<bufPtr->name<<std::endl;
    }
}

template<class T>
bool MyProcess<T>::inputDataAvailable(){
    for (auto bufPtr:inputBufferPtrs){
        if (bufPtr->StoredTokens() < consumptionRate)
            return false;
    }
    return true;
}

template<class T>
bool MyProcess<T>::inputBuffersFull() {
    for (auto bufPtr:inputBufferPtrs){
        if (!bufPtr->IsFull())
            return false;
    }
    return true;
}

template<class T>
bool MyProcess<T>::outputDataAvailable(){
    for (auto bufPtr:outputBufferPtrs){
        if (bufPtr->FreeTokens() < productionRate)
            return false;
    }
    return true;
}

template<class T>
bool MyProcess<T>::outputBuffersFree() {
    for (auto bufPtr:outputBufferPtrs){
        if (!bufPtr->IsEmpty())
            return false;
    }
    return true;
}

// read, write, execute primitives
template<class T>
void MyProcess<T>::read(){
    //wait until all input data is available
    while (!inputDataAvailable());

    for (auto bufPtr:inputBufferPtrs){
        // lock input buffer for reading
        auto bufLock = bufPtr->lock_for_reading();
        // delay reading
        delay(rwDelay*1000);
        bufPtr->ReadSim(consumptionRate);
    }
}

template<class T>
void MyProcess<T>::write(){
    //wait until all output data is available
    while (!outputDataAvailable());

    for (auto bufPtr:outputBufferPtrs){
        //lock output buffer for writing
        auto lock = bufPtr->lock_for_updates();
        // delay writing
        delay(rwDelay*1000);
        bufPtr->WriteSim(productionRate);
    }
}

template<class T>
void MyProcess<T>::sayHi() {
    std::cout<<"Hi, I am "<< this->name<<std::endl;
}

template<class T>
void MyProcess<T>::delay(int timeMS) {
    std::this_thread::sleep_for(std::chrono::milliseconds(timeMS));
}

template<class T>
void MyProcess<T>::exec() {
    delay((execDelay * 1000));
    sayHi();
}

/** INFERENCE HERE **/
template<class T>
void MyProcess<T>::main(void *vpar) {
    for(int run =0; run < runs; run++){

        //read input data
        read();

        //execute process
        exec();

        //write output data
        write();
    }
}

#endif //SHARED_BUFFERS_MYPROCESS_H
