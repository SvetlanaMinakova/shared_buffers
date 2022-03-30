//
// Created by svetlana on 29/03/2022.
//

#ifndef SHARED_BUFFERS_ANRECEIVER_H
#define SHARED_BUFFERS_ANRECEIVER_H

#include "../../MyProcess.h"
#include<map>

class ANReceiver : public MyProcess{
public:
    ANReceiver(const std::string& name, std::map<std::string, std::string>& animalNames, int runs=1, int execDelay=0, int prodRate=1, int consRate=1): MyProcess(name, runs,execDelay, prodRate, consRate){
        this->animalNames=animalNames;
    };
    bool inputDataAvailable() override;
    void read() override;
    std::string translate(std::string animalName);
    void exec() override;
    void main(void *par) override;

private:
    std::string convertToString(char* a, int size);
    std::map<std::string, std::string> animalNames;
    std::string receivedAnimalName;
};


#endif //SHARED_BUFFERS_ANRECEIVER_H
