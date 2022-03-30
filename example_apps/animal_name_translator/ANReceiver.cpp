//
// Created by svetlana on 29/03/2022.
//

#include "ANReceiver.h"
#include <iostream>
bool ANReceiver::inputDataAvailable(){
    for (auto bufPtr:inputBufferPtrs){
        if (bufPtr->IsEmpty())
            return false;
    }
    return true;
}

// Read, write, execute primitives
void ANReceiver::read(){
    //wait until all input data is available
    while (!inputDataAvailable());

    for (auto bufPtr:inputBufferPtrs){
        // lock input buffer for reading
        auto bufLock = bufPtr->lock_for_reading();
        consumptionRate = bufPtr->StoredTokens();
        std::cout<<"cons. rate: "<<consumptionRate<<std::endl;
        char tmpBuf[consumptionRate];
        bufPtr->Read(tmpBuf,consumptionRate);
        receivedAnimalName = tmpBuf;
    }
}

void ANReceiver::exec() {
    delayExec();
    std::cout<<"receiver says "<<receivedAnimalName<<std::endl;
}

void ANReceiver::main(void *par){
    for(int run =0; run < runs; run++){
        //read input data
        read();
        //execute process
        exec();
    }
}

