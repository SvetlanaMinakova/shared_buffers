//
// Created by svetlana on 07/04/2022.
//

#include "ImageWorker.h"
#include <cstdlib>
#include <iostream>

void ImageWorker::initRandomCHW(float *image, int imC, int imH, int imW) {
    int pixelId=0;
    for (int c=0;c<imC;c++){
        for (int h=0;h<imH;h++){
            for (int w=0;w<imW;w++){
                // init pixel with random number between 0 and 1
                image[pixelId] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                pixelId++;
            }
        }
    }
}

void ImageWorker::printCHW(float *image, int imC, int imH, int imW) {
    int pixelId=0;
    for (int c=0;c<imC;c++){
        for (int h=0;h<imH;h++){
            for (int w=0;w<imW;w++){
                std::cout<<image[pixelId]<<" ";
                pixelId++;
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }
}

void ImageWorker::initNaturalOrderCHW(float *image, int imC, int imH, int imW, int startValue) {
    int pixelId=0;
    // std::cout<<"initialize image of len "<<(imH*imW*imC)<<std::endl;
    for (int c=0;c<imC;c++){
        for (int h=0;h<imH;h++){
            for (int w=0;w<imW;w++){
                // init pixel with float pixel id
                //std::cout<<" initialize pixel "<<pixelId<<"...";
                image[pixelId] = float ((pixelId+startValue));
                //std::cout<<"pixel "<<pixelId<<" is initialized"<<std::endl;
                pixelId++;
            }
        }
    }
}
