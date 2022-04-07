//
// Created by svetlana on 07/04/2022.
//

#include "NumArrayAverager.h"
#include <iostream>

void NumArrayAverager::exec() {
    delay((execDelay * 1000));
    float avg = 0;
    for(int i=0; i<arrayLen;i++){
        avg += inputData[i];
    }
    avg/=float(arrayLen);

    //print
    std::cout<<avg<<" is an average for array: "<<std::endl;
    for(int i=0; i<arrayLen;i++){
        std::cout<<inputData[i]<<" ";
    }
    std::cout<<std::endl;
}

// averager does not do writing
void NumArrayAverager::write() {}

NumArrayAverager::~NumArrayAverager() {
    delete [] this->inputData;
}

void NumArrayAverager::init() {
    delete [] this->inputData;
    if (arrayLen>0)
        this->inputData = new float [arrayLen];
    else
        this->inputData = nullptr;
}
