//
// Created by svetlana on 23/03/2022.
//

#include "MyProcess.h"
#include <string>
#include <utility>
#include <iostream>
#include "types.h"
#include <chrono>
#include <thread>
#include <shared_mutex>

// Constructor
MyProcess::MyProcess(std::string name, int runs, int execDelay) {
    this->name = std::move(name);
    this->runs = runs;
    this->execDelay = execDelay;
}

// Manage I/O buffers
void MyProcess::addInputBufferPtr(SharedCharBuffer* ptr){
    inputBufferPtrs.push_back(ptr);
}
void MyProcess::addOutputBufferPtr(SharedCharBuffer* ptr){
    outputBufferPtrs.push_back(ptr);
}

bool MyProcess::inputDataAvailable(){
    for (auto bufPtr:inputBufferPtrs){
        if (bufPtr->StoredTokens() < consumptionRate)
            return false;
    }
    // once input data is available, notify thread
    //cv.notify_all();
    return true;
}

bool MyProcess::outputDataAvailable(){
    for (auto bufPtr:outputBufferPtrs){
        if (bufPtr->FreeTokens() < productionRate)
            return false;
    }
    // once output data is available, notify thread
    //cv.notify_all();
    return true;
}

// cv.wait(lck,shipment_available);

// Read, write, execute primitives
void MyProcess::read(){
    //lock the process until all input data is available
    while (!inputDataAvailable());
    // auto procLock = lock_data_waiter();
    // cv.wait(procLock, inputDataAvailable());

    for (auto bufPtr:inputBufferPtrs){
        // lock input buffer for reading
        auto bufLock = bufPtr->lock_for_reading();
        bufPtr->Read(consumptionRate);
    }
}

void MyProcess::write(){
    //lock the process until all output data is available
    while (!outputDataAvailable());
    // auto procLock = lock_data_waiter();
    // cv.wait(procLock, outputDataAvailable());

    for (auto bufPtr:outputBufferPtrs){
        //lock output buffer for writing
        auto lock = bufPtr->lock_for_updates();
        bufPtr->Write(productionRate);
    }
}

void MyProcess::SayHi() const{
    std::cout<<"Hi, I am "<< this->name<<std::endl;
}

void MyProcess::exec() const{
    int execDelayMS = execDelay * 1000;
    std::this_thread::sleep_for(std::chrono::milliseconds(execDelayMS));
    SayHi();
}

/** INFERENCE HERE **/
void MyProcess::main(void *vpar) {
    for(int run =0; run < runs; run++){

        //read input data
        //read();

        //execute process
        exec();

        //write output data
        //write();
    }
}


