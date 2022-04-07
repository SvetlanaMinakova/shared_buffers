//
// Created by svetlana on 06/04/2022.
//

#ifndef SHARED_BUFFERS_CONVEXAMPLE_H
#define SHARED_BUFFERS_CONVEXAMPLE_H

#include "DataLayer.h"
#include "ConvLayer.h"
#include <utility>
#include <vector>
#include "ImageWorker.h"

class ConvExample {
public:
    int run(int mocImagesNum);
    // int run(std::vector<float*> inputImages);

    ConvExample(int imC, int imH, int imW,
                int kC,int kH, int kW, int stride,
                int runs, int execDelay=0, int rwDelay=0){
        dataLayer = DataLayer(imH, imW, imC, execDelay, rwDelay);
        convLayer = ConvLayer(imH, imW, imC, kH, kW, kC, stride, runs, execDelay, rwDelay);
    }

protected:
    DataLayer dataLayer = DataLayer(0, 0, 0);
    ConvLayer convLayer = ConvLayer(0, 0, 0, 0, 0, 0);
    virtual int run();
};


#endif //SHARED_BUFFERS_CONVEXAMPLE_H
