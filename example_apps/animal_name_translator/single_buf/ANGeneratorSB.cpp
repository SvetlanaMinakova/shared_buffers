//
// Created by svetlana on 01/04/2022.
//

#include "ANGeneratorSB.h"

/**
 * Check whether output data buffers are available for writing
 * output data buffers are available when they are empty
 * @return true, if output data buffers are available and false otherwise
 * */
bool ANGeneratorSB::outputDataAvailable(){
    for (auto bufPtr:outputBufferPtrs){
        if (!bufPtr->IsEmpty())
            return false;
    }
    return true;
}

void ANGeneratorSB::write(){
    //wait until all output data is available
    while (!outputDataAvailable());

    for (auto bufPtr:outputBufferPtrs){
        //lock output buffer for writing
        auto lock = bufPtr->lock_for_updates();

        productionRate = int(generatedAnimalName.length());
        //std::cout<<"prod. rate: "<<productionRate<<std::endl;
        char* currentAnimalNameAsArr = &generatedAnimalName[0];
        bufPtr->Write(currentAnimalNameAsArr,productionRate);
    }
}