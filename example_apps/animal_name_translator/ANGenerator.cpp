//
// Created by svetlana on 29/03/2022.
//

#include "ANGenerator.h"
#include <cstdlib>
#include <iostream>
#include <string>


std::string ANGenerator::pickRandomAnimal() {
    int randomIndex = int(rand() % animalNames.size());
    auto it = animalNames.begin();
    std::advance(it, randomIndex);
    return it->first;

}

void ANGenerator::exec() {
    int execDelayMS = execDelay * 1000;
    delay(execDelayMS);
    // select random animal name
    generatedAnimalName = pickRandomAnimal();
    std::cout << "generator says " << generatedAnimalName << std::endl;
}

void ANGenerator::main(void *par){
    for(int run =0; run < runs; run++){
        //execute process
        exec();

        //write output data
        write();
    }
}
