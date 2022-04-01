//
// Created by svetlana on 01/04/2022.
//

#include "ANReceiverSB.h"

bool ANReceiverSB::inputDataAvailable(){
    for (auto bufPtr:inputBufferPtrs){
        if (bufPtr->IsEmpty())
            return false;
    }
    return true;
}

// Read, write, execute primitives
void ANReceiverSB::read(){
    //wait until all input data is available
    while (!inputDataAvailable());

    for (auto bufPtr:inputBufferPtrs){
        // lock input buffer for reading
        auto bufLock = bufPtr->lock_for_reading();
        consumptionRate = bufPtr->StoredTokens();
        // std::cout<<"cons. rate: "<<consumptionRate<<std::endl;
        char tmpBuf[consumptionRate];
        bufPtr->Read(tmpBuf,consumptionRate);
        receivedAnimalName = convertToString(tmpBuf, consumptionRate);
    }
}
