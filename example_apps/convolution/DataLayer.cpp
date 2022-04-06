//
// Created by svetlana on 06/04/2022.
//

#include "DataLayer.h"

void DataLayer::addImage(float **image) {
    images.push_back(image);
}

unsigned long DataLayer::countImages() {
    return images.size();
}
