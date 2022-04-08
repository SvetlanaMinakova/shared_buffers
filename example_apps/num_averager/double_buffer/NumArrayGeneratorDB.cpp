//
// Created by svetlana on 08/04/2022.
//

#include "NumArrayGeneratorDB.h"

/**
 * Check whether output data buffers are available for writing
 * output data buffers are available when the top part of double-buffer is empty
 * @return true, if output data buffers are available and false otherwise
 * */
bool NumArrayGeneratorDB::outputDataAvailable(){
    for (auto bufPtr:outputBufferPtrs){
        if (!bufPtr->IsTopEmpty())
            return false;
    }
    return true;
}

void NumArrayGeneratorDB::write(){
    // wait until all output data buffers are available
    while (!outputDataAvailable());
    for (auto bufPtr:outputBufferPtrs){
        //std::cout<<"prod. rate: "<<productionRate<<std::endl;
        //std::cout<<"Writer writes: "<<productionRate<<" tokens into "<<bufPtr->name<<std::endl;
        // delay writing
        delay(rwDelay*1000);
        //std::cout<<"write "<<productionRate<<" tokens to "<<bufPtr->name<<std::endl;
        bufPtr->Write(outputData, productionRate);
        //std::cout<<"buf size after writing "<<bufPtr->size<<std::endl;
        auto lock = bufPtr->lock_for_updates();
        bufPtr->setTopVisited();
    }
    SwapReadyOutputBuffers();
}

void NumArrayGeneratorDB::SwapReadyOutputBuffers(){
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


void NumArrayGeneratorDB::addInputBufferPtr(DoubleSharedBuffer<float> *ptr) {
    inputBufferPtrs.push_back(ptr);
}

void NumArrayGeneratorDB::addOutputBufferPtr(DoubleSharedBuffer<float> *ptr) {
    outputBufferPtrs.push_back(ptr);
}