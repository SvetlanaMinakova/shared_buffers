//
// Created by svetlana on 29/03/2022.
//

#ifndef SHARED_BUFFERS_ANGENERATOR_H
#define SHARED_BUFFERS_ANGENERATOR_H

#include "../../MyProcess.h"
#include <map>
#include <string>

class ANGenerator: public MyProcess{
public:
    ANGenerator(const std::string& name, std::map<std::string, std::string>& animalNames, int runs=1, int execDelay=0, int prodRate=1, int consRate=1): MyProcess(name, runs,execDelay, prodRate, consRate){
        this->animalNames=animalNames;
    };
    [[nodiscard]] std::string pickRandomAnimal();
    bool outputDataAvailable() override;
    void write() override;
    void exec() override;
    void main(void *par) override;

private:
    std::map<std::string, std::string> animalNames;
    std::string generatedAnimalName;
};



#endif //SHARED_BUFFERS_ANGENERATOR_H