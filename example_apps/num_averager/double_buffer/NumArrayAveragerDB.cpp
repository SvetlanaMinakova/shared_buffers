//
// Created by svetlana on 08/04/2022.
//

#include "NumArrayAveragerDB.h"


bool NumArrayAveragerDB::inputDataAvailable() {
    for (auto bufPtr:inputBufferPtrs){
        if (!bufPtr->IsBottomFull())
            return false;
    }
    return true;
}

void NumArrayAveragerDB::read() {
    //wait until all input data is available
    while (!inputDataAvailable());

    for (auto bufPtr:inputBufferPtrs){
        // lock input buffer for reading
        // auto bufLock = bufPtr->lock_bottom_for_reading();
        consumptionRate = bufPtr->StoredBottomTokens();
        // delay reading
        delay((rwDelay*1000));
        // std::cout<<"consume "<<consumptionRate<<" tokens from "<<bufPtr->name<<std::endl;
        bufPtr->Read(inputData,consumptionRate);
        // manual "data read" flag
        auto lock = bufPtr->lock_for_updates();
        bufPtr->setBottomVisited();
    }
    SwapReadyInputBuffers();
}

void NumArrayAveragerDB::addInputBufferPtr(DoubleSharedBuffer<float> *ptr) {
    inputBufferPtrs.push_back(ptr);
}

void NumArrayAveragerDB::addOutputBufferPtr(DoubleSharedBuffer<float> *ptr) {
    outputBufferPtrs.push_back(ptr);
}


void NumArrayAveragerDB::SwapReadyInputBuffers() {
    for (auto bufPtr:inputBufferPtrs){
        if (bufPtr->IsTopVisited() and bufPtr->IsBottomVisited()){
            //std::cout<<"Reader swaps buffer: "<<bufPtr->name<<"!"<<std::endl;
            // lock output buffer for writing
            auto lock = bufPtr->lock_for_updates();
            bufPtr->Swap();
            // buffer status is reset after writing
            bufPtr->setTopUnvisited();
            bufPtr->setBottomUnvisited();
        }
    }
}
