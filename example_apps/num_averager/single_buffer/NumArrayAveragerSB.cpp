//
// Created by svetlana on 07/04/2022.
//

#include "NumArrayAveragerSB.h"

void NumArrayAveragerSB::read() {
    //wait until all input data is available
    while (!inputBuffersFull());

    for (auto bufPtr:inputBufferPtrs){
        // lock input buffer for reading
        auto bufLock = bufPtr->lock_for_reading();
        // delay reading
        delay(rwDelay*1000);
        bufPtr->Read(inputData,consumptionRate);
    }
}