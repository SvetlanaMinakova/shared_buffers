//
// Created by svetlana on 29/03/2022.
//

#include "ANReceiver.h"
#include <iostream>
#include <map>
// converts character array
// to string and returns it
std::string ANReceiver::convertToString(char* a, int size)
{
    int i;
    std::string s;
    for (i = 0; i < size; i++) {
        s += a[i];
    }
    return s;
}

std::string ANReceiver::translate(std::string animalName){
    if (animalNames.find(animalName) != animalNames.end()){
        return animalNames.at(animalName);
    }
    return "unknown";
}

void ANReceiver::exec() {
    int execDelayMS = execDelay * 1000;
    delay(execDelayMS);
    std::string translatedAnimalName = translate(receivedAnimalName);
    std::cout<<"receiver says "<<translatedAnimalName<<std::endl;
}

void ANReceiver::main(void *par){
    for(int run =0; run < runs; run++){
        //read input data
        read();
        //execute process
        exec();
    }
}

