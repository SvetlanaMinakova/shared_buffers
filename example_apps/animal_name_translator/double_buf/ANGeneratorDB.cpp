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
    // wait until all output data buffers are available
    while (!outputDataAvailable());

    for (auto bufPtr:outputBufferPtrs){
        productionRate = int(generatedAnimalName.length());
        //std::cout<<"prod. rate: "<<productionRate<<std::endl;
        //std::cout<<"Writer writes: "<<productionRate<<" tokens into "<<bufPtr->name<<std::endl;
        char* currentAnimalNameAsArr = &generatedAnimalName[0];
        // delay writing
        delay((rwDelay*1000));
        bufPtr->Write(currentAnimalNameAsArr,productionRate);
        // manual "data written" flag
        auto lock = bufPtr->lock_for_updates();
        bufPtr->setTopVisited();
    }
    SwapReadyOutputBuffers();
}

void ANGeneratorDB::SwapReadyOutputBuffers(){
    for (auto bufPtr:outputBufferPtrs){
        if (bufPtr->IsTopVisited() and bufPtr->IsBottomVisited()){
            // lock output buffer for writing
            //std::cout<<"Writer swaps: "<<bufPtr->name<<std::endl;
            auto lock = bufPtr->lock_for_updates();
            bufPtr->Swap();
            // buffer status is reset after writing
            bufPtr->setTopUnvisited();
            bufPtr->setBottomUnvisited();
        }
    }
}

void ANGeneratorDB::addInputBufferPtr(DoubleSharedCharBuffer *ptr) {
    inputBufferPtrs.push_back(ptr);
}

void ANGeneratorDB::addOutputBufferPtr(DoubleSharedCharBuffer *ptr) {
    outputBufferPtrs.push_back(ptr);
}
