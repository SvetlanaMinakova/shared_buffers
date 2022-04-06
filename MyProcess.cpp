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

// Constructor
MyProcess::MyProcess(std::string name, int runs, int execDelay, int rwDelay, int prodRate, int consRate) {
    this->name = std::move(name);
    this->runs = runs;
    this->execDelay = execDelay;
    this->rwDelay = rwDelay;
    this->productionRate = prodRate;
    this->consumptionRate = consRate;
}

// Manage I/O buffers
void MyProcess::addInputBufferPtr(SharedCharBuffer* ptr){
    inputBufferPtrs.push_back(ptr);
}

void MyProcess::addOutputBufferPtr(SharedCharBuffer* ptr){
    outputBufferPtrs.push_back(ptr);
}

void MyProcess::printInputBufferNames(){
    for (auto bufPtr:inputBufferPtrs){
        std::cout<<bufPtr->name<<std::endl;
    }
}

void MyProcess::printOutputBufferNames(){
    for (auto bufPtr:outputBufferPtrs){
        std::cout<<bufPtr->name<<std::endl;
    }
}

bool MyProcess::inputDataAvailable(){
    for (auto bufPtr:inputBufferPtrs){
        if (bufPtr->StoredTokens() < consumptionRate)
            return false;
    }
    return true;
}

bool MyProcess::outputDataAvailable(){
    for (auto bufPtr:outputBufferPtrs){
        if (bufPtr->FreeTokens() < productionRate)
            return false;
    }
    return true;
}

// read, write, execute primitives
void MyProcess::read(){
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

void MyProcess::write(){
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

void MyProcess::sayHi() {
    std::cout<<"Hi, I am "<< this->name<<std::endl;
}

void MyProcess::delay(int timeMS) {
    std::this_thread::sleep_for(std::chrono::milliseconds(timeMS));
}

void MyProcess::exec() {
    delay((execDelay * 1000));
    sayHi();
}

/** INFERENCE HERE **/
void MyProcess::main(void *vpar) {
    for(int run =0; run < runs; run++){

        //read input data
        read();

        //execute process
        exec();

        //write output data
        write();
    }
}


