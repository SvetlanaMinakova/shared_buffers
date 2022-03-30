//
// Created by svetlana on 29/03/2022.
//

#include "ANGenerator.h"
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>


std::string ANGenerator::pickRandomAnimal() {
    int randomIndex = int(rand() % animalNames.size());
    auto it = animalNames.begin();
    std::advance(it, randomIndex);
    return it->first;

}

void ANGenerator::exec() {
    delayExec();
    // select random animal name
    generatedAnimalName = pickRandomAnimal();
    std::cout << "generator says " << generatedAnimalName << std::endl;
}

bool ANGenerator::outputDataAvailable(){
    for (auto bufPtr:outputBufferPtrs){
        if (!bufPtr->IsEmpty())
            return false;
    }
    return true;
}

void ANGenerator::write(){
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

void ANGenerator::main(void *par){
    for(int run =0; run < runs; run++){
        //execute process
        exec();

        //write output data
        write();
    }
}
