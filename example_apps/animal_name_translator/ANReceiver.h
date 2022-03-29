//
// Created by svetlana on 29/03/2022.
//

#ifndef SHARED_BUFFERS_ANRECEIVER_H
#define SHARED_BUFFERS_ANRECEIVER_H

#include "../../MyProcess.h"

class ANReceiver : public MyProcess{
public:
    bool inputDataAvailable() override;
};


#endif //SHARED_BUFFERS_ANRECEIVER_H
