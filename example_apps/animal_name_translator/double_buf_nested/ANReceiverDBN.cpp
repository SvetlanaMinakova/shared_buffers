//
// Created by svetlana on 01/04/2022.
//

#include "ANReceiverDBN.h"
#include "iostream"

/**
 * Check whether input data is available
 * input data is available when there is data stored in the buffer
 * @return true, if input data is available and false otherwise
 * */
bool ANReceiverDBN::inputDataAvailable(){
    for (auto bufPtr:inputBufferPtrs){
        if (bufPtr->StoredBottomTokens()==0)
            // if (bufPtr->StoredTokens()<consumptionRate) //this check would require pre-determined or constant consumption rate
            return false;
    }
    return true;
}

// Read, write, execute primitives
void ANReceiverDBN::read(){
    //wait until all input data is available
    while (!inputDataAvailable());

    for (auto bufPtr:inputBufferPtrs){
        // lock input buffer for reading
        // auto bufLock = bufPtr->lock_bottom_for_reading();
        consumptionRate = bufPtr->StoredBottomTokens();
        std::cout<<"cons. rate: "<<consumptionRate<<std::endl;
        char tmpBuf[consumptionRate];
        bufPtr->Read(tmpBuf,consumptionRate);
        receivedAnimalName = convertToString(tmpBuf, consumptionRate);
        // manual "data read" flag
        auto lock = bufPtr->lock_for_updates();
        bufPtr->setBottomVisited();
    }
    SwapReadyInputBuffers();
}

void ANReceiverDBN::SwapReadyInputBuffers() {
    for (auto bufPtr:inputBufferPtrs){
        if (bufPtr->IsTopVisited() and bufPtr->IsBottomVisited()){
            std::cout<<"Reader swaps!"<<std::endl;
            // lock output buffer for writing
            auto lock = bufPtr->lock_for_updates();
            bufPtr->Swap();
            // buffer status is reset after writing
            bufPtr->setTopUnvisited();
            bufPtr->setBottomUnvisited();
        }
    }
}

void ANReceiverDBN::addInputBufferPtr(DoubleNestedCharBuffer *ptr) {
    inputBufferPtrs.push_back(ptr);
}

void ANReceiverDBN::addOutputBufferPtr(DoubleNestedCharBuffer *ptr) {
    outputBufferPtrs.push_back(ptr);
}
