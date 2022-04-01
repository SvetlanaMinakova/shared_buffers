//
// Created by svetlana on 01/04/2022.
//

#ifndef SHARED_BUFFERS_ANGENERATORSB_H
#define SHARED_BUFFERS_ANGENERATORSB_H

#include "../ANGenerator.h"

class ANGeneratorSB: public ANGenerator{
public:
    ANGeneratorSB(const std::string& name, std::map<std::string, std::string>& animalNames, int runs=1, int execDelay=0, int prodRate=1, int consRate=1): ANGenerator(name, animalNames, runs,execDelay, prodRate, consRate){};
    bool outputDataAvailable() override;
    void write() override;
};


#endif //SHARED_BUFFERS_ANGENERATORSB_H
