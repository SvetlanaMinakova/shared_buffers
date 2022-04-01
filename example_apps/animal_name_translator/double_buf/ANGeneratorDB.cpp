//
// Created by svetlana on 01/04/2022.
//

#include "ANGeneratorDB.h"
#include <iostream>
/**
 * Check whether output data buffers are available for writing
 * output data buffers are available when the top part of double-buffer is empty
 * @return true, if output data buffers are available and false otherwise
 * */
bool ANGeneratorDB::outputDataAvailable(){
    for (auto bufPtr:outputBufferPtrs){
        if (!bufPtr->IsTopEmpty())
            return false;
    }
    return true;
}

void ANGeneratorDB::write(){
    // wait until all output data is available
    while (!outputDataAvailable());

    for (auto bufPtr:outputBufferPtrs){
        productionRate = int(generatedAnimalName.length());
        //std::cout<<"prod. rate: "<<productionRate<<std::endl;
        char* currentAnimalNameAsArr = &generatedAnimalName[0];
        bufPtr->Write(currentAnimalNameAsArr,productionRate);
        // manual "data written" flag
        bufPtr->topDataWritten = true;
    }
    SwapReadyOutputBuffers();
}

void ANGeneratorDB::SwapReadyOutputBuffers(){
    for (auto bufPtr:outputBufferPtrs){
        std::cout<<"Writer swaps!"<<std::endl;
        if (bufPtr->topDataWritten and bufPtr->bottomDataRead){
            // lock output buffer for writing
            auto lock = bufPtr->lock_for_updates();
            bufPtr->Swap();
            // buffer status is reset after writing
            bufPtr->topDataWritten = false;
            bufPtr->bottomDataRead = false;
        }
    }
}

void ANGeneratorDB::addInputBufferPtr(DoubleSharedCharBuffer *ptr) {
    inputBufferPtrs.push_back(ptr);
}

void ANGeneratorDB::addOutputBufferPtr(DoubleSharedCharBuffer *ptr) {
    outputBufferPtrs.push_back(ptr);
}
