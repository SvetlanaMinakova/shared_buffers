//
// Created by svetlana on 06/04/2022.
//

#ifndef SHARED_BUFFERS_CONVLAYER_H
#define SHARED_BUFFERS_CONVLAYER_H

#include "../../MyProcess.h"

class ConvLayer: public MyProcess<float>{
public:
    // image height, width, and number of channels
    int imH;
    int imW;
    int imC;

    // kernel height, width, and number of channels
    int kH;
    int kW;
    int kC;

    int stride;

    ConvLayer(int imH, int imW, int imC,
              int kH, int kW, int kC, int stride=1,
              int runs=1, int execDelay=0, int rwDelay=0): MyProcess<float>("dataLayer", runs, execDelay, rwDelay) {
        this->imH = imH;
        this->imW = imW;
        this->imC = imC;
        this->kH = kH;
        this->kW = kW;
        this->kC = kC;
        this->stride = stride;

        consumptionRate = imH * imW * imC;
        productionRate = imH * imW * imC;
    };

protected:
    float** kernel;
};


#endif //SHARED_BUFFERS_CONVLAYER_H
