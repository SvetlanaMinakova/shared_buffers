//
// Created by svetlana on 07/04/2022.
//

#include "NumArrayGeneratorSB.h"
#include <cstdlib>
#include <iostream>

// generator does not do any reading
void NumArrayGeneratorSB::read() {}

void NumArrayGeneratorSB::exec() {
    delay((execDelay * 1000));
    for (int i=0;i<arrayLen;i++) {
        //int randomValue = float(int(rand() % maxValue));
        float value = float(i)/10 + startValue;
        outputData[i] = value;
    }
    startValue += float(arrayLen)/10;
}

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

NumArrayGeneratorSB::~NumArrayGeneratorSB() {
    delete [] this->outputData;
}

void NumArrayGeneratorSB::init() {
    delete [] this->outputData;
    if (arrayLen>0)
        this->outputData = new float [arrayLen];
    else
        this->outputData = nullptr;
}
