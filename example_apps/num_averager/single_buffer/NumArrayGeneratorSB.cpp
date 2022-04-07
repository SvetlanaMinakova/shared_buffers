//
// Created by svetlana on 07/04/2022.
//

#include "NumArrayGeneratorSB.h"

void NumArrayGeneratorSB::write() {
    //wait until all output data is available
    while (!outputBuffersFree());
    for (auto bufPtr:outputBufferPtrs){
        //lock output buffer for writing
        auto lock = bufPtr->lock_for_updates();
        // delay writing
        delay(rwDelay*1000);
        //std::cout<<"write "<<productionRate<<" tokens to "<<bufPtr->name<<std::endl;
        bufPtr->Write(outputData, productionRate);
        //std::cout<<"buf size after writing "<<bufPtr->size<<std::endl;
    }
}
