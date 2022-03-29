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
    bool outputDataAvailable() override;
    void read() override;
    // void write() override;
    void exec() const override;

private:
    std::string currentAnimalName;

};



#endif //SHARED_BUFFERS_ANGENERATOR_H
