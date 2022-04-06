//
// Created by svetlana on 01/04/2022.
//

#ifndef SHARED_BUFFERS_ANRECEIVERSB_H
#define SHARED_BUFFERS_ANRECEIVERSB_H

#include "../ANReceiver.h"

class ANReceiverSB: public ANReceiver{
public:
    ANReceiverSB(const std::string& name, std::map<std::string, std::string>& animalNames, int runs=1, int execDelay=0, int rwDelay=0,
                 int prodRate=1, int consRate=1): ANReceiver(name, animalNames, runs,execDelay, rwDelay, prodRate, consRate){};
    bool inputDataAvailable() override;
    void read() override;
};


#endif //SHARED_BUFFERS_ANRECEIVERSB_H
