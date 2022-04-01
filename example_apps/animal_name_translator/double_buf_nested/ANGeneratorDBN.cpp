//
// Created by svetlana on 01/04/2022.
//

#include "ANGeneratorDBN.h"
#include <iostream>
/**
 * Check whether output data buffers are available for writing
 * output data buffers are available when the top part of double-buffer is empty
 * @return true, if output data buffers are available and false otherwise
 * */
bool ANGeneratorDBN::outputDataAvailable(){
    for (auto bufPtr:outputBufferPtrs){
        if (!bufPtr->IsTopEmpty())
            return false;
    }
    return true;
}

void ANGeneratorDBN::write(){
    // wait until all output data is available
    while (!outputDataAvailable());

    for (auto bufPtr:outputBufferPtrs){
        productionRate = int(generatedAnimalName.length());
        //std::cout<<"prod. rate: "<<productionRate<<std::endl;
        char* currentAnimalNameAsArr = &generatedAnimalName[0];
        bufPtr->Write(currentAnimalNameAsArr,productionRate);
        // manual "data written" flag
        auto lock = bufPtr->lock_for_updates();
        bufPtr->setTopVisited();
    }
    SwapReadyOutputBuffers();
}

void ANGeneratorDBN::SwapReadyOutputBuffers(){
    for (auto bufPtr:outputBufferPtrs){
        std::cout<<"Writer swaps!"<<std::endl;
        if (bufPtr->IsTopVisited() and bufPtr->IsBottomVisited()){
            // lock output buffer for writing
            auto lock = bufPtr->lock_for_updates();
            bufPtr->Swap();
            // buffer status is reset after writing
            bufPtr->setTopUnvisited();
            bufPtr->setBottomUnvisited();
        }
    }
}

void ANGeneratorDBN::addInputBufferPtr(DoubleNestedCharBuffer *ptr) {
    inputBufferPtrs.push_back(ptr);
}

void ANGeneratorDBN::addOutputBufferPtr(DoubleNestedCharBuffer *ptr) {
    outputBufferPtrs.push_back(ptr);
}
