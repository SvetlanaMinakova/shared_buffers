//
// Created by svetlana on 06/04/2022.
//

#ifndef SHARED_BUFFERS_CONVEXAMPLE_H
#define SHARED_BUFFERS_CONVEXAMPLE_H

#include "DataLayer.h"
#include "ConvLayer.h"

class ConvExample {
public:
    virtual int run()=0;
    ConvExample(int imH, int imW, int imC,
                int kH, int kW, int kC, int stride,
                int runs, int execDelay=0, int rwDelay=0){
        dataLayer = DataLayer(imH, imW, imC, execDelay, rwDelay);
        convLayer = ConvLayer(imH, imW, imC, kH, kW, kC, stride, runs, execDelay, rwDelay);
    }

protected:
    DataLayer dataLayer = DataLayer(0, 0, 0);
    ConvLayer convLayer = ConvLayer(0, 0, 0, 0, 0, 0);
};


#endif //SHARED_BUFFERS_CONVEXAMPLE_H
