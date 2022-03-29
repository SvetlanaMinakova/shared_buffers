//
// Created by svetlana on 29/03/2022.
//

#include "ANGenerator.h"
#include "AnimalNames.h"

bool ANGenerator::outputDataAvailable(){
    for (auto bufPtr:outputBufferPtrs){
        if (!bufPtr->IsEmpty())
            return false;
    }
    return true;
}

// ANGenerator does not read data
void ANGenerator::read() {

}

void ANGenerator::exec() const {
    delayExec();
    // select random animal name
    // currentAnimalName = animalNames
}
