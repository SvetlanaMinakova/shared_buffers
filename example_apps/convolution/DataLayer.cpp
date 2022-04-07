//
// Created by svetlana on 06/04/2022.
//

#include "DataLayer.h"
#include "ImageWorker.h"
//#include <opencv2/opencv.hpp>

void DataLayer::addImage(float *image) {
    images.push_back(image);
}

unsigned long DataLayer::countImages() {
    return images.size();
}

void DataLayer::printImages() {
    for (auto im:images){
        ImageWorker::printCHW(im, imC, imH, imW);
    }
}
