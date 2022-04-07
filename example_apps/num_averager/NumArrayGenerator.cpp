//
// Created by svetlana on 07/04/2022.
//

#include "NumArrayGenerator.h"

#include <cstdlib>
#include <iostream>

// generator does not do any reading
void NumArrayGenerator::read() {}

void NumArrayGenerator::exec() {
    delay((execDelay * 1000));
    for (int i=0;i<arrayLen;i++) {
        //int randomValue = float(int(rand() % maxValue));
        float value = float(i)/10 + startValue;
        outputData[i] = value;
    }
    startValue += float(arrayLen)/10;
}

void NumArrayGenerator::init() {
    delete [] this->outputData;
    if (arrayLen>0)
        this->outputData = new float [arrayLen];
    else
        this->outputData = nullptr;
}

NumArrayGenerator::~NumArrayGenerator() {
    delete [] this->outputData;
}