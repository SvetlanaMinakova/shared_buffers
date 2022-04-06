//
// Created by svetlana on 06/04/2022.
//

#ifndef SHARED_BUFFERS_DATALAYER_H
#define SHARED_BUFFERS_DATALAYER_H

#include <vector>
#include "../../MyProcess.h"

class DataLayer: public MyProcess<float>{
public:
    // image height, width, and number of channels
    int imH;
    int imW;
    int imC;

    unsigned long countImages();
    void addImage(float** image);

    DataLayer(int imH, int imW, int imC, int runs=1, int execDelay=0, int rwDelay=0): MyProcess<float>("dataLayer", runs, execDelay, rwDelay) {
        this->imH = imH;
        this->imW = imW;
        this->imC = imC;
        productionRate = imH * imW * imC;
        consumptionRate = 0;
    };

protected:
    float** curImage = nullptr;
    std::vector<float**> images;
};


#endif //SHARED_BUFFERS_DATALAYER_H
