//
// Created by svetlana on 29/03/2022.
//

#include "ANReceiver.h"
#include <iostream>
#include <map>
bool ANReceiver::inputDataAvailable(){
    for (auto bufPtr:inputBufferPtrs){
        if (bufPtr->IsEmpty())
            return false;
    }
    return true;
}

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

// Read, write, execute primitives
void ANReceiver::read(){
    //wait until all input data is available
    while (!inputDataAvailable());

    for (auto bufPtr:inputBufferPtrs){
        // lock input buffer for reading
        auto bufLock = bufPtr->lock_for_reading();
        consumptionRate = bufPtr->StoredTokens();
        // std::cout<<"cons. rate: "<<consumptionRate<<std::endl;
        char tmpBuf[consumptionRate];
        bufPtr->Read(tmpBuf,consumptionRate);
        receivedAnimalName = convertToString(tmpBuf, consumptionRate);
    }
}

std::string ANReceiver::translate(std::string animalName){
    if (animalNames.find(animalName) != animalNames.end()){
        return animalNames.at(animalName);
    }
    return "unknown";
}

void ANReceiver::exec() {
    delayExec();
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

