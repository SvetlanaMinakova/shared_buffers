//
// Created by svetlana on 07/04/2022.
//

#ifndef SHARED_BUFFERS_DETECTEDGESSB_H
#define SHARED_BUFFERS_DETECTEDGESSB_H

#include "../../ConvExample.h"
#include "../../kernelsLib.h"

class DetectEdgesSB: ConvExample{
public:
    DetectEdgesSB(int imC, int imH, int imW,
                  int runs, int execDelay=0, int rwDelay=0): ConvExample(imC, imH, imW, 1, 3, 3, 1, runs, execDelay, rwDelay){
        float* kernel = detectEdgesKernel;
        convLayer.setKernel(kernel);
    };
protected:
    int run() override;
};


#endif //SHARED_BUFFERS_DETECTEDGESSB_H
