//
// Created by svetlana on 06/04/2022.
//

#include "ConvExample.h"
#include "ImageWorker.h"
#include <memory>
#include <iostream>

int ConvExample::run(int mocImagesNum) {
    int imLen = dataLayer.imC*dataLayer.imH*dataLayer.imW;
    std::cout<<"Create "<<mocImagesNum<<" moc images of len "<<imLen<<std::endl;
    float mocImages[mocImagesNum][imLen];

    for (int imId=0; imId<mocImagesNum; imId++){
        // std::cout<<"  - init image "<<imId<<std::endl;
        ImageWorker::initNaturalOrderCHW(mocImages[imId],dataLayer.imC, dataLayer.imH, dataLayer.imW, (imId*imLen));
        dataLayer.addImage(mocImages[imId]);
    }
    // show generated images
    // dataLayer.printImages();

    int result = run();
    return result;
}

int ConvExample::run(){
    std::cout<<"Run Conv Example"<<std::endl;
    return 0;
}
