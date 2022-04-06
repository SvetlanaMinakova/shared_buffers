//
// Created by svetlana on 01/04/2022.
//

#include "ANReceiverSB.h"
/**
 * Check whether input data is available
 * input data is available when there is data stored in the buffer
 * @return true, if input data is available and false otherwise
 * */
bool ANReceiverSB::inputDataAvailable(){
    for (auto bufPtr:inputBufferPtrs){
        if (bufPtr->IsEmpty())
        // if (bufPtr->StoredTokens()<consumptionRate) //this check would require pre-determined or constant consumption rate
            return false;
    }
    return true;
}

// read, write, execute primitives
void ANReceiverSB::read(){
    //wait until all input data is available
    while (!inputDataAvailable());
    for (auto bufPtr:inputBufferPtrs){
        // lock input buffer for reading
        auto bufLock = bufPtr->lock_for_reading();
        consumptionRate = bufPtr->StoredTokens();
        // std::cout<<"cons. rate: "<<consumptionRate<<std::endl;
        // delay reading
        delay((rwDelay*1000));
        char tmpBuf[consumptionRate];
        bufPtr->Read(tmpBuf,consumptionRate);
        receivedAnimalName = convertToString(tmpBuf, consumptionRate);
    }
}
